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
//  ID: $Id: asncc_generate_cpp_visitor.h,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_ASNCC_GENERATE_CPP_VISITOR_H_)
#define _ASNCC_GENERATE_CPP_VISITOR_H_

#include <asncc_visitor.h>



////////////////////////////////////////////////////////////////////////////////
//
//  GenerateCppVisitor interface.
//

class GenerateCppVisitor : public Visitor
{
public:

    GenerateCppVisitor(AsnCC& asnCCParam, Module* moduleParam)
    :   asnCC(asnCCParam),
        module(moduleParam),
        level(0),
        hdr(""),
        src(""),
        currentTypeDef(NULL),
        currentType(NULL),
        currentTypeName(""),
        insideSizeConstraint(false)
    {
        REQUIRE(module != NULL);

        SetVisitFlattened();

        hdr.reserve(SIZE_HUGE);
        src.reserve(SIZE_HUGE);
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

    void GenerateDefaultConstructorBody();

    void GenerateDecodeConstructorBody();

    void GenerateNothingToDoBody();

    void GenerateInitializeMemberFunction();

    void GenerateDestructor(const std::string& typeName);

    void GenerateCloneMemberFunction(const std::string& typeName);

    void GenerateGetNameMemberFunction(const std::string& typeName);

    void GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                    const std::string& typeName, 
                                    const std::string& asnDescTypeName);

    void GenerateGetStaticDescriptionMemberFunctionEndPart();

    void GenerateTagAddLevelInstructions();

    void GenerateSetClauseSizeInstructions();

    void GenerateSetClauseOptionalInstructions();

    void GenerateSetClauseAnyTagInstructions();

    void GenerateSetClauseExtensibleInstructions();

    void GeneratePublicScope();

    void GenerateProtectedScope();

    void GenerateTypeClassBeginPart(
                        const std::string& typeName, 
                        const std::string& asnTypeName);

    void GenerateTypeClassEndPart();

    void GenerateElementStaticDescription(
                                    Type* elementType, 
                                    const std::string& elementName);


    ////////////////////////////////////////////////////////////////////////////

    // Generate code helper member functions.

    enum { MaxBufferSize = 65536 };

    void HdrPrint(int n, const char* format, ...);
    void SrcPrint(int n, const char* format, ...);

    void 
    HdrNewLine()
    { hdr.append("\n"); }

    void 
    HdrIndent(int n)
    { hdr.append(GetLevelIndent(level + n)); }

    void 
    SrcNewLine()
    { src.append("\n"); }

    void    
    SrcIndent(int n)
    { src.append(GetLevelIndent(n)); }

    static std::string GetVarArgsString(const char* format, ...);

    static std::string GetLevelIndent(int level);

    std::string GetHdrHeaderString();
    std::string GetHdrEndString();
    std::string GetSrcHeaderString();
    std::string GetSrcEndString();

    static std::string GetStandardHeaderString();

    std::string GetScopeString();
    std::string GetBasicIncludeListString();
    std::string GetReferenceIncludeListString();
    std::string GetBasicDescIncludeListString();
    std::string GetTypedefListString();

    std::string GetGeneratedTypeName(Type* type);
    std::string GetGeneratedBaseTypeName(Type* type);
    std::string GetGeneratedElementTypeName(Type* type);
    std::string GetItsNamespaceScope();

    static bool IsCommonType(Type* type);

    static bool IsAsnTypeName(const std::string& typeName);

    static bool IsAsnUsefulTypeName(const std::string& typeName);

    ////////////////////////////////////////////////////////////////////////////

    AsnCC&
    GetAsnCC()
    { return asnCC; }

    Module*
    GetModule() const
    { return module; }

    void 
    SetLevel(int levelParam)
    { level = levelParam; }

    int 
    GetLevel()
    { return level; }

    void
    SetCurrentTypeDef(TypeDef* typeDefParam)
    {
        REQUIRE(typeDefParam != NULL);

        currentTypeDef = typeDefParam;
    }

    TypeDef*
    GetCurrentTypeDef() const
    {
        TypeDef* result = currentTypeDef;

        ENSURE(result != NULL);

        return result;
    }

    void
    SetCurrentType(Type* typeParam)
    {
        REQUIRE(typeParam != NULL);
        
        currentType = typeParam;
    }

    Type*
    GetCurrentType() const
    {
        Type* result = currentType;

        ENSURE(result != NULL);

        return result;
    }

    void 
    SetCurrentTypeName(const std::string& typeNameParam)
    { currentTypeName = typeNameParam; }

    const std::string& 
    GetCurrentTypeName()
    { return currentTypeName; }

    std::string& 
    GetHdr()
    { return hdr; }

    std::string&     
    GetSrc()
    { return src; }

    std::string& 
    GetValHdr()
    { return valHdr; }

    std::string&     
    GetValSrc()
    { return valSrc; }

    void 
    InsertOnceBasicIncludeList(const std::string& str);

    void 
    InsertOnceReferenceIncludeList(const std::string& str);

    void
    InsertOnceTypedefList(const std::string& str);

    std::list<std::string>& 
    GetBasicIncludeList()
    { return basicIncludeList; }

    std::list<std::string>& 
    GetReferenceIncludeList()
    { return referenceIncludeList; }

    std::list<std::string>&
    GetTypedefList()
    { return typedefList; }

    void PushContext();
    void PopContext();

protected:

    enum {
        SIZE_TINY       = 128,
        SIZE_SMALL      = 1024,
        SIZE_MEDIUM     = 32768,
        SIZE_HUGE       = 131072
    };

    AsnCC& asnCC;

    Module* module;

    int level;

    std::string hdr;    // Contents of header file to be generated.
    std::string src;    // Contents of source file to be generated.

    std::string valHdr; // Contents of header file to be generated (value(s)).
    std::string valSrc; // Contents of source file to be generated (value(s)).

    TypeDef*    currentTypeDef;
    Type*       currentType;

    std::string currentTypeName;

    std::list<std::string>  basicIncludeList;
    std::list<std::string>  referenceIncludeList;
    std::list<std::string>  typedefList;

    // Context push/pop.

    std::list<Type*>                    typeStack;
    std::list<std::string>              typeNameStack;
    std::list<std::list<std::string> >  typedefListStack;

    // Constraint processing.

    bool insideSizeConstraint;

    std::list<std::string>  constraintInstructionList;

    // Common type definition table (if merge option used).
    // MUST be shared accross all modules => static.

    typedef std::map<std::string, TypeDef*> TypeDefTable;

    static TypeDefTable commonTypeDefTable;

};


#endif // !defined(_ASNCC_GENERATE_CPP_VISITOR_H_)
