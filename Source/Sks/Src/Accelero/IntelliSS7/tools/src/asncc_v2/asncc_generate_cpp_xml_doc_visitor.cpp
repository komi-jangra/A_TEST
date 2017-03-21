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
// LOG: Revision 9.1  2005/03/23 12:54:14  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:00  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.5  2002/01/07 23:00:00  hdivoux
// LOG: Update for firt shot at XER encoding.
// LOG:
// LOG: Revision 5.4  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_generate_cpp_xml_doc_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"

#include <stdarg.h>

#include <asncc_generate_cpp_xml_doc_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)



////////////////////////////////////////////////////////////////////////////////
//
//  GenerateCppXmlDocVisitor implementation.
//

void 
GenerateCppXmlDocVisitor::VisitModuleBegin(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);
}


void 
GenerateCppXmlDocVisitor::VisitModuleEnd(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);

    GenerateXmlAsnModuleSummary();

    GenerateXmlAsnModuleClassList();

    GenerateXmlAsnModuleMakeHtml();
}


void 
GenerateCppXmlDocVisitor::VisitImportedModule(ImportedModule* importedModule)
{
    REQUIRE(importedModule != NULL);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCppXmlDocVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{
    // Cleaning of contents (xml source).

    GetXml().erase(GetXml().begin(), GetXml().end());


    SetCurrentTypeDef(typeDef);
    SetCurrentType(typeDef->GetType());
    SetCurrentTypeName(typeDef->GetDefinedName());
    SetLevel(0); // Module types are at level zero.
}


void 
GenerateCppXmlDocVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitTypeBegin(Type* type)
{
    SetCurrentType(type);

    constraintInstructionList.clear();
}


void 
GenerateCppXmlDocVisitor::VisitTypeEnd(Type* type)
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
    case TYPE_BASE_STRING:
    case TYPE_REAL:
    case TYPE_SEQUENCE:
    case TYPE_SEQUENCE_OF:
    case TYPE_SET:
    case TYPE_SET_OF:
    case TYPE_USEFUL:
    case TYPE_ANY:
    case TYPE_ANY_DEFINED_BY:
    {
        string moduleName = module->GetName();

        if (xmlModuleNameG != "")
        {
            moduleName = xmlModuleNameG;
        }

        moduleName = AdaptNameToLowercase(moduleName);

        string fileNameCore     = "";

        fileNameCore.append(moduleName);
        fileNameCore.append("_");
        fileNameCore.append(GetScopeUnderscoreString());

        fileNameCore = AdaptNameToLowercase(fileNameCore);

        string directoryName = moduleName + "_doc";

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
GenerateCppXmlDocVisitor::VisitTypeDefaultValue(Type* type, Value* value)
{   

}


void 
GenerateCppXmlDocVisitor::VisitBitStringTypeBegin(BitStringType* bitStringType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitBitStringTypeEnd(BitStringType* bitStringType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnBitString",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

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
                "Set%s",
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "void Set%s()",
                definedName.c_str()));

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
                "Reset%s",
                definedName.c_str()));


        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "void Reset%s()",
                definedName.c_str()));

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
                "Is%sSet",
                definedName.c_str()));


        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "bool Is%sSet() const",
                definedName.c_str()));

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
                "Is%sDefined",
                definedName.c_str()));


        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "bool Is%sDefined() const",
                definedName.c_str()));

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
GenerateCppXmlDocVisitor::VisitBooleanType(BooleanType* booleanType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnBoolean",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnBoolean");
}


void 
GenerateCppXmlDocVisitor::VisitChoiceTypeBegin(ChoiceType* choiceType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitChoiceTypeEnd(ChoiceType* choiceType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnChoice",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Class(es) //////////

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

    ////////// End Nested Class(es) //////////

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

            // Generate XML elements for "memberFunctionSetChoice".

            GenerateXmlBeginTag("memberFunctionSetChoice");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "SetChoice%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void SetChoice%s(%s* choice)",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str()));

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
                adaptedElementTypeName);

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionSetChoice");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionSetChoiceWithRef".

            GenerateXmlBeginTag("memberFunctionSetChoiceWithRef");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "SetChoice%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void SetChoice%s(const %s& choice)",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str()));

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
                adaptedElementTypeName);

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionSetChoiceWithRef");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionGetChoice".

            GenerateXmlBeginTag("memberFunctionGetChoice");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "GetChoice%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "const %s& GetChoice%s() const",
                    adaptedElementTypeName.c_str(),
                    adaptedName.c_str()));

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
                adaptedElementTypeName);

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
                    "Choice%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "bool Choice%s() const",
                    adaptedName.c_str()));

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
                adaptedElementTypeName);

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
GenerateCppXmlDocVisitor::VisitChoiceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnEnumerated",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

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

        string name = namedNumber->GetName();
        string definedName = AdaptName(namedNumber->GetName());

        // Generate XML elements for "memberFunctionSet".

        GenerateXmlBeginTag("memberFunctionSet");

        XmlNewLine();

        GenerateXmlElement(
            "name", 
            GetVarArgsString(
                "Set%s",
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "void Set%s()",
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "enumItemName",
            name);

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
                "Is%s",
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "bool Is%s() const",
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "enumItemName",
            name);

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
GenerateCppXmlDocVisitor::VisitIntegerTypeBegin(IntegerType* integerType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitIntegerTypeEnd(IntegerType* integerType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnInteger",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnInteger");
}


void
GenerateCppXmlDocVisitor::VisitObjectIdentifierType(
                                ObjectIdentifierType* objectIdentifierType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnObjectIdentifier",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnObjectIdentifier");
}


void
GenerateCppXmlDocVisitor::VisitNullType(NullType* nullType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnNull",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnNull");
}


void
GenerateCppXmlDocVisitor::VisitRealType(RealType* realType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnReal",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnReal");
}


void 
GenerateCppXmlDocVisitor::VisitSequenceTypeBegin(SequenceType* sequenceType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSequenceTypeEnd(SequenceType* sequenceType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnSequence",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Class(es) //////////

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

    ////////// End Nested Class(es) //////////

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

            // Generate XML elements for "memberFunctionSet".

            GenerateXmlBeginTag("memberFunctionSet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "Set%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void Set%s(%s* element)",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str()));

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
                adaptedElementTypeName);

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

            // Generate XML elements for "memberFunctionSetWithRef".

            GenerateXmlBeginTag("memberFunctionSetWithRef");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "Set%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void Set%s(const %s& element)",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str()));

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
                adaptedElementTypeName);

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

            GenerateXmlEndTag("memberFunctionSetWithRef");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionGet".

            GenerateXmlBeginTag("memberFunctionGet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "Get%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "const %s& Get%s() const",
                    adaptedElementTypeName.c_str(),
                    adaptedName.c_str()));

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
                adaptedElementTypeName);

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
                        "Option%s",
                        adaptedName.c_str()));

                XmlNewLine();

                GenerateXmlElement(
                    "signature", 
                    GetVarArgsString(
                        "bool Option%s() const",
                        adaptedName.c_str()));

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
                    adaptedElementTypeName);

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
GenerateCppXmlDocVisitor::VisitSequenceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnSequenceOf",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Class //////////

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

    ////////// End Nested Class //////////

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elements for "memberFunctionAdd".

    GenerateXmlBeginTag("memberFunctionAdd");

    XmlNewLine();

    GenerateXmlElement("name", "AddElement");

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "void AddElement(%s* element)",
            eltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement("elementTypeName", eltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAdd");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elements for "memberFunctionAddWithRef".

    GenerateXmlBeginTag("memberFunctionAddWithRef");

    XmlNewLine();

    GenerateXmlElement("name", "AddElement");

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "void AddElement(const %s& element)",
            eltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement("elementTypeName", eltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAddWithRef");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elments for "memberFunctionAt".

    GenerateXmlBeginTag("memberFunctionAt");

    XmlNewLine();

    GenerateXmlElement("name", "ElementAt");

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "const %s& ElementAt(size_t index) const",
            eltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement("elementTypeName", eltTypeName);

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
GenerateCppXmlDocVisitor::VisitSequenceOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitSequenceOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSetTypeBegin(SetType* setType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSetTypeEnd(SetType* setType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnSet",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Class(es) //////////\n");

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

    ////////// End Nested Class(es) //////////

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

            // Generate XML elements for "memberFunctionSet".

            GenerateXmlBeginTag("memberFunctionSet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "Set%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void Set%s(%s* element)",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str()));

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
                adaptedElementTypeName);

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

            // Generate XML elements for "memberFunctionSetWithRef".

            GenerateXmlBeginTag("memberFunctionSetWithRef");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "Set%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void Set%s(const %s& element)",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str()));

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
                adaptedElementTypeName);

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

            GenerateXmlEndTag("memberFunctionSetWithRef");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionGet".

            GenerateXmlBeginTag("memberFunctionGet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "Get%s",
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "const %s& Get%s() const",
                    adaptedElementTypeName.c_str(),
                    adaptedName.c_str()));

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
                adaptedElementTypeName);

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
                        "Option%s",
                        adaptedName.c_str()));

                XmlNewLine();

                GenerateXmlElement(
                    "signature", 
                    GetVarArgsString(
                        "bool Option%s() const",
                        adaptedName.c_str()));

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
                    adaptedElementTypeName);

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
GenerateCppXmlDocVisitor::VisitSetTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSetOfTypeBegin(SetOfType* setOfType)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSetOfTypeEnd(SetOfType* setOfType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnSetOf",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Class //////////

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

    ////////// End Nested Class //////////

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elements for "memberFunctionAdd".

    GenerateXmlBeginTag("memberFunctionAdd");

    XmlNewLine();

    GenerateXmlElement("name", "AddElement");

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "void AddElement(%s* element)",
            eltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement("elementTypeName", eltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAdd");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elements for "memberFunctionAddWithRef".

    GenerateXmlBeginTag("memberFunctionAddWithRef");

    XmlNewLine();

    GenerateXmlElement("name", "AddElement");

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "void AddElement(const %s& element)",
            eltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement("elementTypeName", eltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAddWithRef");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elments for "memberFunctionAt".

    GenerateXmlBeginTag("memberFunctionAt");

    XmlNewLine();

    GenerateXmlElement("name", "ElementAt");

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "const %s& ElementAt(size_t index) const",
            eltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement("elementTypeName", eltTypeName);

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
GenerateCppXmlDocVisitor::VisitSetOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitSetOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitOctetStringType(OctetStringType* octetStringType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnOctetString",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnOctetString");
}


void
GenerateCppXmlDocVisitor::VisitDefinedType(DefinedType* definedType)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitAnyType(AnyType* anyType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnAny",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnAny");
}


void
GenerateCppXmlDocVisitor::VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType)
{
    string typeName = AdaptName(GetCurrentTypeName());

    string moduleName = AdaptModuleName(module->GetName());

    GenerateTypeXmlBeginPart(
                        "asnAny",
                        GetScopeString(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(GetScopeString(), GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnAny");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GenerateCppXmlDocVisitor::VisitValueDefBegin(ValueDef* valueDef)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitValueDefEnd(ValueDef* valueDef)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitValueDefType(ValueDef* valueDef, Type* type)
{
    // Must do nothing (i.e. must not generate code).
}


void 
GenerateCppXmlDocVisitor::VisitValueBegin(Value* value)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitValueEnd(Value* value)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitBitStringValue(BitStringValue* bitStringValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitBooleanValue(BooleanValue* booleanValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitCharacterStringValue(
                            CharacterStringValue* characterStringValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitChoiceValue(ChoiceValue* choiceValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitEnumeratedValue(EnumeratedValue* enumeratedValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitIntegerValue(IntegerValue* integerValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitObjectIdentifierValue(
                            ObjectIdentifierValue* objectIdentifierValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitOctetStringValue(OctetStringValue* octetStringValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitMaxValue(MaxValue* maxValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitMinValue(MinValue* minValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitNullValue(NullValue* nullValue)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitRealValue(RealValue* realValue)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSequenceValueBegin(SequenceValue* sequenceValue)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitSequenceValueEnd(SequenceValue* sequenceValue)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitDefinedValue(DefinedValue* definedValue)
{
    // Nothing to do.
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCppXmlDocVisitor::VisitNamedNumberBegin(NamedNumber* namedNumber)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitNamedNumberEnd(NamedNumber* namedNumber)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitTag(Tag* tag)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitConstraintBegin(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCppXmlDocVisitor::VisitConstraintEnd(Constraint* constraint)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitSingleValueConstraintElementBegin(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitSingleValueConstraintElementEnd(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitValueRangeConstraintElementBegin(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitValueRangeConstraintElementMiddle(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    // Nothing to do.
}


void
GenerateCppXmlDocVisitor::VisitValueRangeConstraintElementEnd(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    // Nothing to do.
}


void GenerateCppXmlDocVisitor::VisitSizeConstraintElementBegin(
                            SizeConstraintElement* 
                                sizeConstraintElement)
{
    // Nothing to do.
}


void GenerateCppXmlDocVisitor::VisitSizeConstraintElementEnd(
                            SizeConstraintElement*
                                sizeConstraintElement)
{
    // Nothing to do.
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void 
GenerateCppXmlDocVisitor::GenerateTypeXmlBeginPart(
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

    if (xmlModuleNameG == "")
    {
        GenerateXmlElement(
            "moduleName", 
            AdaptModuleName(module->GetName()));
    }
    else
    {
        GenerateXmlElement(
            "moduleName", 
            AdaptModuleName(xmlModuleNameG));
    }

    XmlNewLine();
    XmlNewLine();
}


void 
GenerateCppXmlDocVisitor::GenerateTypeXmlEndPart(const std::string& xmlType)
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
GenerateCppXmlDocVisitor::GenerateXmlElement(
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
GenerateCppXmlDocVisitor::GenerateXmlBeginTag(
                                    const std::string& tagName)
{
    XmlPrint(0,
            "<%s>",
            tagName.c_str());
}


void 
GenerateCppXmlDocVisitor::GenerateXmlEndTag(
                                    const std::string& tagName)
{
    XmlPrint(0,
            "</%s>",
            tagName.c_str());
}


void
GenerateCppXmlDocVisitor::GenerateXmlAsnDefinition()
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
GenerateCppXmlDocVisitor::GenerateXmlAsnModuleSummary()
{
    // Cleaning of contents (xml source).

    GetXml().erase(GetXml().begin(), GetXml().end());

    GetXml().insert(0, GetXmlHeaderString());

    XmlNewLine();

    GenerateXmlBeginTag("asnModuleSummary");

    XmlNewLine();
    XmlNewLine();

    string moduleName = module->GetName();

    if (xmlModuleNameG != "")
    {
        moduleName = xmlModuleNameG;
    }

    moduleName = AdaptNameToLowercase(moduleName);

    string fileNamePrefix = moduleName;
    fileNamePrefix.append("_");

    if (xmlModuleNameG == "")
    {
        GenerateXmlElement(
            "moduleName", 
            AdaptModuleName(module->GetName()));
    }
    else
    {
        GenerateXmlElement(
            "moduleName", 
            AdaptModuleName(xmlModuleNameG));
    }

    XmlNewLine();
    XmlNewLine();

    asnTypeInfoList.sort();

    for (AsnTypeInfoList::iterator iter = asnTypeInfoList.begin();
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

    string directoryName = moduleName + "_doc";

    WriteTextToFile(
                directoryName,
                "AsnModuleSummary",
                "xml",
                GetXml());
}


void 
GenerateCppXmlDocVisitor::GenerateXmlAsnModuleClassList()
{
    // Cleaning of contents (xml source).

    GetXml().erase(GetXml().begin(), GetXml().end());

    GetXml().insert(0, GetXmlHeaderString());

    XmlNewLine();

    GenerateXmlBeginTag("asnModuleClassList");

    XmlNewLine();
    XmlNewLine();

    asnTypeInfoList.sort();

    string moduleName = module->GetName();

    if (xmlModuleNameG != "")
    {
        moduleName = xmlModuleNameG;
    }

    moduleName = AdaptNameToLowercase(moduleName);

    string fileNamePrefix = moduleName;
    fileNamePrefix.append("_");

    for (AsnTypeInfoList::iterator iter = asnTypeInfoList.begin();
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

    string directoryName = moduleName + "_doc";

    WriteTextToFile(
                directoryName,
                "AsnModuleClassList",
                "xml",
                GetXml());
}


void 
GenerateCppXmlDocVisitor::GenerateXmlAsnModuleMakeHtml()
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
        "Rem (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.\n");
    XmlPrint(0, 
        "Rem\n");
    XmlPrint(0, 
        "Rem\n");

    XmlNewLine();
    XmlNewLine();


    // Copy XML to HTML script to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/cpp/AsnccXml2Html.js .");

    XmlNewLine();
    XmlNewLine();

    // Copy XSL transformation files to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/cpp/*.xsl .");

    XmlNewLine();
    XmlNewLine();

    // Copy all HTML documents to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/cpp/*.html .");

    XmlNewLine();
    XmlNewLine();

    // Copy default IntelliSS7 icon to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/cpp/AsnModuleLogo.jpg .");

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

    string moduleName = module->GetName();

    if (xmlModuleNameG != "")
    {
        moduleName = xmlModuleNameG;
    }

    moduleName = AdaptNameToLowercase(moduleName);

    string fileNamePrefix = moduleName;
    fileNamePrefix.append("_");

    for (AsnTypeInfoList::iterator iter = asnTypeInfoList.begin();
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

    string directoryName = moduleName + "_doc";

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
GenerateCppXmlDocVisitor::XmlPrint(int n, const char* format, ...)
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
GenerateCppXmlDocVisitor::SubstituteXmlSpecialCharacters(const string& str)
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
GenerateCppXmlDocVisitor::GetXmlHeaderString()
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
        "<!-- (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved. "
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
GenerateCppXmlDocVisitor::GetXmlEndString()
{
    string result;

    result.reserve(SIZE_TINY);

    result.append("\n");
    result.append("\n");

    return result;
}


string 
GenerateCppXmlDocVisitor::GetScopeString()
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

            result.append("::");
        }
    }

    return result;
}


string 
GenerateCppXmlDocVisitor::GetAsnScopeString()
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
GenerateCppXmlDocVisitor::GetScopeUnderscoreString()
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
GenerateCppXmlDocVisitor::GetAsnScopeUnderscoreString()
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
GenerateCppXmlDocVisitor::PushContext()
{
    GenerateCppVisitor::PushContext();   

    xmlStack.push_front(xml);

    xml.erase(xml.begin(), xml.end());
}


void 
GenerateCppXmlDocVisitor::PopContext()
{
    xml = xmlStack.front();

    xmlStack.pop_front();

    GenerateCppVisitor::PopContext();
}


