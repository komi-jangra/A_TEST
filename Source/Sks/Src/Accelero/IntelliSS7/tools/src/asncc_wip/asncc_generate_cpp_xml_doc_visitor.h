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
//  ID: $Id: asncc_generate_cpp_xml_doc_visitor.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_ASNCC_GENERATE_CPP_XML_DOC_VISITOR_H_)
#define _ASNCC_GENERATE_CPP_XML_DOC_VISITOR_H_

#include <asncc_generate_cpp_visitor.h>



////////////////////////////////////////////////////////////////////////////////
//
//  GenerateCppXmlDocVisitor interface.
//

class GenerateCppXmlDocVisitor : public GenerateCppVisitor
{
public:

    GenerateCppXmlDocVisitor(AsnCC& asnCCParam, Module* moduleParam)
    :   GenerateCppVisitor(asnCCParam, moduleParam),
        xml("")
    {
        REQUIRE(module != NULL);

        xml.reserve(SIZE_MEDIUM);
    }

    // Default copy constructor ok.

    // Default destructor ok (no memory management).

    // Default assignment operator ok.

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitModuleBegin(Module* module);
    
    virtual void VisitModuleEnd(Module* module);

    virtual void VisitImportedModule(ImportedModule* importedModule);

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitTypeDefBegin(TypeDef* typeDef);

    virtual void VisitTypeDefEnd(TypeDef* typeDef);

    virtual void VisitTypeBegin(Type* type);

    virtual void VisitTypeEnd(Type* type);

    virtual void VisitTypeDefaultValue(Type* type, Value* value);

    virtual void VisitBitStringTypeBegin(BitStringType* bitStringType);

    virtual void VisitBitStringTypeEnd(BitStringType* bitStringType);

    virtual void VisitBooleanType(BooleanType* booleanType);

    virtual void VisitChoiceTypeBegin(ChoiceType* choiceType);

    virtual void VisitChoiceTypeEnd(ChoiceType* choiceType);

    virtual void VisitChoiceTypeList(TypeList* typeList);

    virtual void VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType);

    virtual void VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType);

    virtual void VisitIntegerTypeBegin(IntegerType* integerType);

    virtual void VisitIntegerTypeEnd(IntegerType* integerType);

    virtual void VisitObjectIdentifierType(
                                ObjectIdentifierType* objectIdentifierType);

    virtual void VisitNullType(NullType* nullType);

    virtual void VisitRealType(RealType* realType);

    virtual void VisitSequenceTypeBegin(SequenceType* sequenceType);

    virtual void VisitSequenceTypeEnd(SequenceType* sequenceType);

    virtual void VisitSequenceTypeList(TypeList* typeList);

    virtual void VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType);

    virtual void VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType);

    virtual void VisitSequenceOfTypeType(Type* type);

    virtual void VisitSequenceOfConstraint(Constraint* constraint);

    virtual void VisitSetTypeBegin(SetType* setType);

    virtual void VisitSetTypeEnd(SetType* setType);

    virtual void VisitSetTypeList(TypeList* typeList);

    virtual void VisitSetOfTypeBegin(SetOfType* setOfType);

    virtual void VisitSetOfTypeEnd(SetOfType* setOfType);

    virtual void VisitSetOfTypeType(Type* type);

    virtual void VisitSetOfConstraint(Constraint* constraint);

    virtual void VisitOctetStringType(OctetStringType* octetStringType);

    virtual void VisitDefinedType(DefinedType* definedType);

    virtual void VisitAnyType(AnyType* anyType);

    virtual void VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType);

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitValueDefBegin(ValueDef* valueDef);

    virtual void VisitValueDefMiddle(ValueDef* valueDef);

    virtual void VisitValueDefEnd(ValueDef* valueDef);

    virtual void VisitValueDefType(ValueDef* valueDef, Type* type);

    virtual void VisitValueBegin(Value* value);

    virtual void VisitValueEnd(Value* value);

    virtual void VisitBitStringValue(BitStringValue* bitStringValue);

    virtual void VisitBooleanValue(BooleanValue* booleanValue);

    virtual void VisitCharacterStringValue(
                                CharacterStringValue* characterStringValue);

    virtual void VisitChoiceValue(ChoiceValue* choiceValue);

    virtual void VisitEnumeratedValue(EnumeratedValue* enumeratedValue);

    virtual void VisitIntegerValue(IntegerValue* integerValue);

    virtual void VisitObjectIdentifierValue(
                                ObjectIdentifierValue* objectIdentifierValue);

    virtual void VisitOctetStringValue(OctetStringValue* octetStringValue);

    virtual void VisitMaxValue(MaxValue* maxValue);

    virtual void VisitMinValue(MinValue* minValue);

    virtual void VisitNullValue(NullValue* nullValue);

    virtual void VisitRealValue(RealValue* realValue);

    virtual void VisitSequenceValueBegin(SequenceValue* sequenceValue);

    virtual void VisitSequenceValueEnd(SequenceValue* sequenceValue);

    virtual void VisitDefinedValue(DefinedValue* definedValue);

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitNamedNumberBegin(NamedNumber* namedNumber);

    virtual void VisitNamedNumberEnd(NamedNumber* namedNumber);

    virtual void VisitTag(Tag* tag);

    virtual void VisitConstraintBegin(Constraint* constraint);

    virtual void VisitConstraintEnd(Constraint* constraint);

    virtual void VisitSingleValueConstraintElementBegin(
                        SingleValueConstraintElement*
                            singleValueConstraintElement);

    virtual void VisitSingleValueConstraintElementEnd(
                        SingleValueConstraintElement*
                            singleValueConstraintElement);

    virtual void VisitValueRangeConstraintElementBegin(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement);

    virtual void VisitValueRangeConstraintElementMiddle(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement);

    virtual void VisitValueRangeConstraintElementEnd(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement);

    virtual void VisitSizeConstraintElementBegin(
                        SizeConstraintElement* 
                            sizeConstraintElement);

    virtual void VisitSizeConstraintElementEnd(
                        SizeConstraintElement*
                            sizeConstraintElement);

    ////////////////////////////////////////////////////////////////////////////


    void GenerateTypeXmlBeginPart(
                        const std::string& xmlType,
                        const std::string& className, 
                        const std::string& asnTypeName);

    void GenerateTypeXmlEndPart(const std::string& xmlType);

    void GenerateXmlElement(
                        const std::string& tagName, 
                        const std::string& value);

    void GenerateXmlBeginTag(const std::string& tagName);

    void GenerateXmlEndTag(const std::string& tagName);

    void GenerateXmlAsnDefinition();

    void GenerateXmlAsnModuleSummary();

    void GenerateXmlAsnModuleClassList();

    void GenerateXmlAsnModuleMakeHtml();


    ////////////////////////////////////////////////////////////////////////////

    // Generate XML code helper member functions.

    enum { MaxBufferSize = 65536 };

    void XmlPrint(int n, const char* format, ...);

    void 
    XmlNewLine()
    { xml.append("\n"); }

    void 
    XmlIndent(int n)
    { xml.append(GetLevelIndent(level + n)); }

    std::string SubstituteXmlSpecialCharacters(const std::string& str);

    std::string GetXmlHeaderString();

    std::string GetXmlEndString();

    std::string GetScopeString(Type* type);
    std::string GetAsnScopeString();            // Names are not adapted.

    std::string GetScopeUnderscoreString();
    std::string GetAsnScopeUnderscoreString();  // Names are not adapted.

    ////////////////////////////////////////////////////////////////////////////

    std::string& 
    GetXml()
    { return xml; }

    void PushContext();
    void PopContext();

protected:

    std::string xml;    // Contents of xml file to be generated.

    // Context push/pop.

    std::list<std::string>  xmlStack;

    class AsnTypeInfo
    {
    public:

        // Default constructor not ok (see private section).

        AsnTypeInfo(
            const std::string& classNameParam,
            const std::string& asnTypeNameParam,
            Type* typeParam,
            Module* moduleParam,
            bool commonEquivalentParam = false)
        :   className(classNameParam),
            asnTypeName(asnTypeNameParam),
            type(typeParam),
            module(moduleParam),
            commonEquivalent(commonEquivalentParam)
        {}

        // Default copy constructor ok.

        // Default destructor ok.

        // Default assignment operator ok.

        const std::string&
        GetClassName() const
        { return className; }

        const std::string&
        GetAsnTypeName() const
        { return asnTypeName; }

        Type*
        GetType() const
        { return type; }

        Module*
        GetModule() const
        { return module; }

        bool
        IsCommonEquivalent() const
        { return commonEquivalent; }

        // For sort operation.

        bool 
        operator< (const AsnTypeInfo& rhs)
        { return GetClassName() < rhs.GetClassName(); }

    protected:

        std::string className;

        std::string asnTypeName;

        Type* type;

        Module* module;

        bool commonEquivalent;

    private:

        AsnTypeInfo()
        :   className(""),
            asnTypeName(""),
            type(NULL),
            module(NULL),
            commonEquivalent(false)
        {}
    };


    // Common AsnTypeInfo list. MUST be shared accross
    // all modules (required if merge option used,
    // optional if merge option is not used) => static.

    typedef std::list<AsnTypeInfo> AsnTypeInfoList;

    static AsnTypeInfoList asnTypeInfoList;


    // Common type table (if merge option used).
    // MUST be shared accross all modules => static.

    typedef std::map<std::string, Type*> TypeTable;

    static TypeTable commonTypeTable;        
};


#endif // !defined(_ASNCC_GENERATE_CPP_XML_DOC_VISITOR_H_)
