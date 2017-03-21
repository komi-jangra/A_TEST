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
//  ID: $Id: asncc_ast.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  Abstract syntax type implementations.
//

#include <asncc_ast.h>
#include <asncc_parser.h>
#include <asncc_util.h>
#include <asncc_check_semantic_visitor.h>
#include <asncc_components_of_visitor.h>
#include <asncc_evaluate_visitor.h>
#include <asncc_generate_cpp_visitor.h>
#include <asncc_link_visitor.h>
#include <asncc_normalize_visitor.h>
#include <asncc_print_visitor.h>
#include <asncc_recursive_visitor.h>
#include <asncc_merge_visitor.h>
#include <asncc_generate_cpp_xml_doc_visitor.h>
#include <asncc_generate_c_visitor.h>
#include <asncc_generate_c_xml_doc_visitor.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

////////////////////////////////////////////////////////////////////////////////
//
//  TypeDef implementation.
//

TypeDef::TypeDef(const string& definedNameParam, Type* typeParam)
:   definedName(definedNameParam), 
    type(typeParam),
    isParameterized(false),
    isValueSet(false),
    isRecursive(false),
    isMarked(false),
    isExported(false),
    isCommon(false),
    localRefCount(0),
    importRefCount(0)
{
    parameterList           = new list<string*>();
    constraintElementList   = new ConstraintElementList();
}


bool
TypeDef::Equals(const TypeDef& rhs) const
{
    if (definedName != rhs.definedName)
    {
        return false;
    }

    if (type == NULL && rhs.type != NULL)
    {
        return false;
    }

    if (type != NULL && rhs.type == NULL)
    {
        return false;
    }

    if (type != NULL && rhs.type != NULL)
    {
        if (!type->Equals(*rhs.type))
        {
            return false;
        }
    }

    if (isParameterized != rhs.isParameterized)
    {
        return false;
    }

    {
        std::list<std::string*>::const_iterator iter1 =
            parameterList->begin();

        std::list<std::string*>::const_iterator iter2 = 
            rhs.parameterList->begin();

        while (true)
        {
           if (iter1 != parameterList->end() &&
                iter2 == rhs.parameterList->end())
            {
                return false;
            }

            if (iter1 == parameterList->end() &&
                iter2 != rhs.parameterList->end())
            {
                return false;
            }

            if (iter1 == parameterList->end() &&
                iter2 == rhs.parameterList->end())
            {
                break;
            }

            string* str1 = *iter1;
            string* str2 = *iter2;

            if (!(*str1 == *str2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    if (isValueSet != rhs.isValueSet)
    {
        return false;
    }

    ConstraintElementList::const_iterator iter1 = 
        constraintElementList->begin();

    ConstraintElementList::const_iterator iter2 = 
        rhs.constraintElementList->begin();

    while (true)
    {
        if (iter1 != constraintElementList->end() &&
            iter2 == rhs.constraintElementList->end())
        {
            return false;
        }

        if (iter1 == constraintElementList->end() &&
            iter2 != rhs.constraintElementList->end())
        {
            return false;
        }

        if (iter1 == constraintElementList->end() &&
            iter2 == rhs.constraintElementList->end())
        {
            break;
        }

        ConstraintElement* constraintElement1 = *iter1;
        ConstraintElement* constraintElement2 = *iter2;

        if (!constraintElement1->Equals(*constraintElement2))
        {
            return false;
        }

        iter1++;
        iter2++;
    }

    return true;
}


void
TypeDef::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    visitor->VisitTypeDefBegin(this);

    type->Accept(visitor);

    visitor->VisitTypeDefEnd(this);
}


string
TypeDef::ToString() const
{
    ostrstream ostrs;

    Print(ostrs);

    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    return result;
}


void
TypeDef::Print(ostream& os) const
{
    PrintVisitor printVisitor(os);

    (const_cast<TypeDef*> (this))->Accept(&printVisitor);
}


////////////////////////////////////////////////////////////////////////////////
//
// TypeDef ostream operator<< implementation.

ostream& operator<<(ostream& os, const TypeDef& typeDef)
{
    typeDef.Print(os);
    return os;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Type implementation.
//

Type::Type()
:   isReferenced(false),
    isConstrained(false),
    isNamed(false),
    isOptional(false),
    isComponentsOf(false),
    isFromComponentsOf(false),
    isFromSelectionType(false),
    hasLineNumber(false),
    isParameterized(false),
    isCommon(false),
    name(""),
    hasDefaultValue(false),
    defaultValue(NULL),
    lineNumber(0),
    hasComponentsOfOrigin(false),
    hasSelectionTypeOrigin(false),
    componentsOfOrigin(NULL),
    selectionTypeOrigin(NULL),
    hasModule(false),
    module(NULL)
{
    tagList         = new TagList();
    constraintList  = new ConstraintList();
    parameterList   = new list<string*>();
}


bool
Type::Equals(const Type& rhs) const
{
    if (GetType() != rhs.GetType())
    {
        return false;
    }

    if (isConstrained != rhs.isConstrained)
    {
        return false;
    }

    if (isNamed != rhs.isNamed)
    {
        return false;
    }

    if (isOptional != rhs.isOptional)
    {
        return false;
    }

    if (isComponentsOf != rhs.isComponentsOf)
    {
        return false;
    }

    if (isFromComponentsOf != rhs.isFromComponentsOf)
    {
        return false;
    }

    if (isFromSelectionType != rhs.isFromSelectionType)
    {
        return false;
    }

    if (isParameterized != rhs.isParameterized)
    {
        return false;
    }

    if (name != rhs.name)
    {
        return false;
    }

    if (hasDefaultValue != rhs.hasDefaultValue)
    {
        return false;
    }

    if (defaultValue == NULL && rhs.defaultValue != NULL ||
        defaultValue != NULL && rhs.defaultValue == NULL)
    {
        return false;
    }

    if (defaultValue != NULL && rhs.defaultValue != NULL)
    {
        if (!defaultValue->Equals(*rhs.defaultValue))
        {
            return false;
        }
    }

    {
        TagList::const_iterator iter1 =
            tagList->begin();

        TagList::const_iterator iter2 = 
            rhs.tagList->begin();

        while (true)
        {
           if (iter1 != tagList->end() &&
                iter2 == rhs.tagList->end())
            {
                return false;
            }

            if (iter1 == tagList->end() &&
                iter2 != rhs.tagList->end())
            {
                return false;
            }

            if (iter1 == tagList->end() &&
                iter2 == rhs.tagList->end())
            {
                break;
            }

            Tag* tag1 = *iter1;
            Tag* tag2 = *iter2;

            if (!tag1->Equals(*tag2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    {
        ConstraintList::const_iterator iter1 = 
            constraintList->begin();

        ConstraintList::const_iterator iter2 = 
            rhs.constraintList->begin();

        while (true)
        {
            if (iter1 != constraintList->end() &&
                iter2 == rhs.constraintList->end())
            {
                return false;
            }

            if (iter1 == constraintList->end() &&
                iter2 != rhs.constraintList->end())
            {
                return false;
            }

            if (iter1 == constraintList->end() &&
                iter2 == rhs.constraintList->end())
            {
                break;
            }

            Constraint* constraint1 = *iter1;
            Constraint* constraint2 = *iter2;

            if (!constraint1->Equals(*constraint2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    {
        std::list<std::string*>::const_iterator iter1 =
            parameterList->begin();

        std::list<std::string*>::const_iterator iter2 = 
            rhs.parameterList->begin();

        while (true)
        {
           if (iter1 != parameterList->end() &&
                iter2 == rhs.parameterList->end())
            {
                return false;
            }

            if (iter1 == parameterList->end() &&
                iter2 != rhs.parameterList->end())
            {
                return false;
            }

            if (iter1 == parameterList->end() &&
                iter2 == rhs.parameterList->end())
            {
                break;
            }

            string* str1 = *iter1;
            string* str2 = *iter2;

            if (!(*str1 == *str2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    //  TODO: review. May not be needed. Recursivity.

/*

    if (hasComponentsOfOrigin != rhs.hasComponentsOfOrigin)
    {
        return false;
    }

    if (hasSelectionTypeOrigin != rhs.hasSelectionTypeOrigin)
    {
        return false;
    }

    if (componentsOfOrigin != NULL && rhs.componentsOfOrigin == NULL ||
        componentsOfOrigin == NULL && rhs.componentsOfOrigin != NULL)
    {
        return false;
    }

    if (componentsOfOrigin != NULL && rhs.componentsOfOrigin != NULL)
    {
        if (!componentsOfOrigin->Equals(*rhs.componentsOfOrigin))
        {
            return false;
        }
    }

    if (selectionTypeOrigin != NULL && rhs.selectionTypeOrigin == NULL ||
        selectionTypeOrigin == NULL && rhs.selectionTypeOrigin != NULL)
    {
        return false;
    }

    if (selectionTypeOrigin != NULL && rhs.selectionTypeOrigin != NULL)
    {
        if (!selectionTypeOrigin->Equals(*rhs.selectionTypeOrigin))
        {
            return false;
        }
    }

*/

    {
        TypeList::const_iterator iter1 = 
            componentsOfList.begin();

        TypeList::const_iterator iter2 = 
            rhs.componentsOfList.begin();

        while (true)
        {
            if (iter1 != componentsOfList.end() &&
                iter2 == rhs.componentsOfList.end())
            {
                return false;
            }

            if (iter1 == componentsOfList.end() &&
                iter2 != rhs.componentsOfList.end())
            {
                return false;
            }

            if (iter1 == componentsOfList.end() &&
                iter2 == rhs.componentsOfList.end())
            {
                break;
            }

            Type* type1 = *iter1;
            Type* type2 = *iter2;

            if (!type1->Equals(*type2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    return true;
}


int 
Type::GetIdentifierTokenContext() const
{
    return TK_IDENTIFIER;
}


Type*
Type::GetBaseType() const
{
    Type* result = const_cast<Type*> (this);

    bool stop = false;

    while(!stop)
    {
        switch (result->GetType())
        {
        case TYPE_DEFINED:
        {
            DefinedType* definedType = static_cast<DefinedType*> (result);

            ASSERT(definedType->IsLinked());

            result = definedType->GetLink();

            break;
        }
        case TYPE_SELECTION:
        {
            // TODO: to be done.

            stop = true;
            
            break;
        }
        default:
        {
            stop = true;

            break;
        }
        }
    }

    ENSURE(result != NULL);

    return result;
}


void
Type::SetCommonRecursively()
{
    SetCommon();

    // Find associated typedef and mark it as common if any.

    TypeDefList* typeDefList = module->GetTypeDefList();

    for (TypeDefList::iterator iter = typeDefList->begin();
         iter != typeDefList->end();
         iter++)
    {
        TypeDef* typeDef = *iter;
        
        if (typeDef->GetType() == this)
        {
            typeDef->SetCommon();
        }
    }
}
    


TagList*
Type::GetFullTagList() const
{ 
    TagList* result = new TagList(*tagList);

    Type* baseType = GetBaseType();

    if (baseType->HasUniversalTag())
    {
        result->push_back(baseType->GetUniversalTag());
    }

    return result;
}


TagList*
Type::GetAdjustedTagList() const
{
    TagList* fullTagList = GetFullTagList();

    // [1]  Get a deep clone full tag list (ftList).

    TagList ftList;

    for (TagList::iterator iter = fullTagList->begin();
         iter != fullTagList->end();
         iter++)
    {
        ftList.push_back((*iter)->Clone());
    }

    ASSERT(ftList.size() == fullTagList->size());

    // [2]  Get a reversed copy of full tag list (rftList). Note that ftList and
    //      rftList share the same tag objects (i.e. reference to tag objects).

    TagList rftList(ftList);

    rftList.reverse();

    ASSERT(rftList.size() == ftList.size());
    
    if (rftList.size() == 0)
    {
        // [3]  If rftList is empty return an empty tag list.

        TagList* result = new TagList();

        return result;
    }
    else if (rftList.size() == 1)
    {
        // [4]  If rftList contains exactly one tag return a tag list containing
        //      the only tag.

        Tag* tag = rftList.front();

        // [4-1]    If base type is choice then tag must be constructed (rule 
        //          for nested tagging).

        if (GetBaseType()->GetType() == TYPE_CHOICE)
        {
            tag->SetTagType(Tag::TYPE_CONSTRUCTED);
        }

        // [4-2]    If base type is any or any defined by then tag must be
        //          constructed (any type has already a tag even if not
        //          universal).

        if (GetBaseType()->GetType() == TYPE_ANY ||
            GetBaseType()->GetType() == TYPE_ANY_DEFINED_BY)
        {
            tag->SetTagType(Tag::TYPE_CONSTRUCTED);
        }

        TagList* result = new TagList();

        result->push_back(tag);

        return result;
    }
    else // rftList.size() >= 2.
    {
        ASSERT(rftList.size() >= 2);

        // [5]  If rftList contains more than one tag process according to 
        //      following algorithm.

        TagList* result = new TagList();

        // [5-1]    If first tag of rftList is constructed adjust all tags of
        //          rftList as constructed. If first tag of rftList is primitive
        //          adjust all tags of rftList a primitive.

        if (rftList.front()->GetTagType() == Tag::TYPE_CONSTRUCTED)
        {
            for (TagList::iterator rftIter = rftList.begin();
                 rftIter != rftList.end();
                 rftIter++)
            {
                (*rftIter)->SetTagType(Tag::TYPE_CONSTRUCTED);
            }
        }
        else if (rftList.front()->GetTagType() == Tag::TYPE_PRIMITIVE)
        {
            for (TagList::iterator rftIter = rftList.begin();
                 rftIter != rftList.end();
                 rftIter++)
            {
                (*rftIter)->SetTagType(Tag::TYPE_PRIMITIVE);
            }
        }
        else
        {
            bool must_not_be_reached = false;
            ASSERT(must_not_be_reached);
        }

        // [5-2]    If base type is choice and module default tag mode is
        //          implicit and option boolean bForceExplicitChoiceG is true
        //          then adjust all tags to explicit mode.

        if (GetBaseType()->GetType() == TYPE_CHOICE &&
            GetModule()->GetDefaultTagMode() == Tag::MODE_IMPLICIT &&
            bForceExplicitChoiceG)
        {
            for (TagList::iterator rftIter = rftList.begin();
                 rftIter != rftList.end();
                 rftIter++)
            {
                (*rftIter)->SetTagMode(Tag::MODE_EXPLICIT);
            }
        }

        // [5-3]    If base type is any and module default tag mode is implicit
        //          and option boolean bForceExplicitAnyG is true then adjust
        //          all tags to explicit mode.

        if ((GetBaseType()->GetType() == TYPE_ANY ||
             GetBaseType()->GetType() == TYPE_ANY_DEFINED_BY) &&
            GetModule()->GetDefaultTagMode() == Tag::MODE_IMPLICIT &&
            bForceExplicitAnyG)
        {
            for (TagList::iterator rftIter = rftList.begin();
                 rftIter != rftList.end();
                 rftIter++)
            {
                (*rftIter)->SetTagMode(Tag::MODE_EXPLICIT);
            }
        }

        // [5-4]    Build resulting list of tags (removing implicit tags).

        for (TagList::iterator rftIter = rftList.begin();
             rftIter != rftList.end();
             rftIter++)
        {
            if ((++rftIter != rftList.end()) &&
                ((*rftIter)->GetTagMode() == Tag::MODE_IMPLICIT))
            {
                --rftIter;

                // Nothing to do (do not add current tag to resulting list).
            }
            else
            {
                --rftIter;

                result->push_front(*rftIter); // Using rftList (reverse needed).
            }
        }

        // [5-5]    If more than one resulting tag then all the resulting tags
        //          except the last one must be constructed (rule for nested 
        //          tagging).
        
        if (result->size() > 1)
        {
            for (TagList::iterator resIter = result->begin();
                 resIter != result->end();
                 resIter++)
            {
                if (++resIter == result->end())
                {
                    --resIter;

                    // Nothing to do (keep as it is).
                }
                else
                {
                    --resIter;

                    (*resIter)->SetTagType(Tag::TYPE_CONSTRUCTED);
                }
            }
        }

        // [5-6]    If base type is choice then all the resulting tags must be
        //          constructed (rule for nested tagging).

        if (GetBaseType()->GetType() == TYPE_CHOICE)
        {
            for (TagList::iterator resIter = result->begin();
                 resIter != result->end();
                 resIter++)
            {
                (*resIter)->SetTagType(Tag::TYPE_CONSTRUCTED);
            }
        }

        // [5-7]    If base type is any or any defined by then all the resulting
        //          tags must be constructed (rule for nested tagging). Any type
        //          has already a tag even if not universal.

        if (GetBaseType()->GetType() == TYPE_ANY ||
            GetBaseType()->GetType() == TYPE_ANY_DEFINED_BY)
        {
            for (TagList::iterator resIter = result->begin();
                 resIter != result->end();
                 resIter++)
            {
                (*resIter)->SetTagType(Tag::TYPE_CONSTRUCTED);
            }
        }

        return result;
    }

    bool must_not_be_reached = false;
    ASSERT(must_not_be_reached);

    return NULL; // Not reached.
}


void 
Type::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    if (hasDefaultValue)
    {
        visitor->VisitTypeDefaultValue(this, defaultValue);
    }

    if (!(constraintList->empty()))
    {
        visitor->VisitTypeConstraintList(constraintList);
    }

    // TODO: to be completed with other member variables.
}


string
Type::ToString() const
{
    ostrstream ostrs;

    Print(ostrs);

    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    return result;
}
    

void
Type::Print(ostream& os) const
{
    PrintVisitor printVisitor(os);

    (const_cast<Type*> (this))->Accept(&printVisitor);
}


////////////////////////////////////////////////////////////////////////////////
//
// Type ostream operator<< implementation.

ostream& operator<<(ostream& os, const Type& type)
{
    type.Print(os);
    return os;
}


////////////////////////////////////////////////////////////////////////////////
//
//  BitStringType implementation.
//

BitStringType::BitStringType()
{
    namedNumberList = new NamedNumberList();
}


BitStringType::BitStringType(NamedNumberList* namedNumberListParam)
:   namedNumberList(namedNumberListParam)
{
}


bool
BitStringType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const BitStringType& other = 
        static_cast<const BitStringType&> (rhs);

    NamedNumberList::const_iterator iter1 = 
        namedNumberList->begin();

    NamedNumberList::const_iterator iter2 = 
        other.namedNumberList->begin();

    while (true)
    {
        if (iter1 != namedNumberList->end() &&
            iter2 == other.namedNumberList->end())
        {
            return false;
        }

        if (iter1 == namedNumberList->end() &&
            iter2 != other.namedNumberList->end())
        {
            return false;
        }

        if (iter1 == namedNumberList->end() &&
            iter2 == other.namedNumberList->end())
        {
            break;
        }

        NamedNumber* namedNumber1 = *iter1;
        NamedNumber* namedNumber2 = *iter2;

        if (!namedNumber1->Equals(*namedNumber2))
        {
            return false;
        }

        iter1++;
        iter2++;
    }

    return true;
}


int
BitStringType::GetIdentifierTokenContext() const
{
    return TK_OID_IDENTIFIER;
}


int
BitStringType::GetBraceTokenContext() const
{
    return TK_BIT_STRING_BRACE;
}


Tag* 
BitStringType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_BIT_STRING,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
BitStringType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitBitStringTypeBegin(this);

    visitor->PushIterContext();

    visitor->SetIterSize(namedNumberList->size());

    for (NamedNumberList::iterator nnIter = namedNumberList->begin();
         nnIter != namedNumberList->end();
         nnIter++)
    {
        if (nnIter == namedNumberList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++nnIter == namedNumberList->end())
        {
            --nnIter;
            visitor->SetIterEnd();
        }
        else
        {
            --nnIter;
            visitor->SetIterMiddle();
        }

        (*nnIter)->Accept(visitor);
    }

    visitor->PopIterContext();

    visitor->VisitBitStringTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  BooleanType implementation.
//

BooleanType::BooleanType()
{
}


bool
BooleanType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
BooleanType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitBooleanType(this);

    visitor->VisitTypeEnd(this);
}


Tag* 
BooleanType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_BOOLEAN,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  CharacterStringType implementation.
//

CharacterStringType::CharacterStringType()
{
}


bool
CharacterStringType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


int 
CharacterStringType::GetBraceTokenContext() const
{
    return TK_STRING_BRACE;
}


////////////////////////////////////////////////////////////////////////////////
//
//  ChoiceType implementation.
//

ChoiceType::ChoiceType(TypeList* typeListParam)
:   typeList(typeListParam),
    extendable(false),
    extensions(new TypeList())
{
}


ChoiceType::ChoiceType(TypeList* typeListParam, bool extendableParam)
:   typeList(typeListParam), 
    extendable(extendableParam),
    extensions(new TypeList())
{
}


ChoiceType::ChoiceType(
                TypeList* typeListParam, 
                bool extendableParam, 
                TypeList* extensionsParam)
:   typeList(typeListParam), 
    extendable(extendableParam), 
    extensions(extensionsParam)
{
}


bool
ChoiceType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const ChoiceType& other =
        static_cast<const ChoiceType&> (rhs);

    {
        TypeList::const_iterator iter1 = 
            typeList->begin();

        TypeList::const_iterator iter2 = 
            other.typeList->begin();

        while (true)
        {
            if (iter1 != typeList->end() &&
                iter2 == other.typeList->end())
            {
                if (bCppMergeWithExtensionsG    &&
                    extendable                  &&
                    other.extendable)
                {
                    while (iter1 != typeList->end())
                    {
                        if (!(*iter1)->IsOptional())
                        {
                            return false;
                        }

                        iter1++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == typeList->end() &&
                iter2 != other.typeList->end())
            {
                if (bCppMergeWithExtensionsG    &&
                    extendable                  &&
                    other.extendable)
                {
                    while (iter2 != other.typeList->end())
                    {
                        if (!(*iter2)->IsOptional())
                        {
                            return false;
                        }

                        iter2++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == typeList->end() &&
                iter2 == other.typeList->end())
            {
                break;
            }

            Type* type1 = *iter1;
            Type* type2 = *iter2;

            if (!type1->Equals(*type2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    {
        TypeList::const_iterator iter1 = 
            extensions->begin();

        TypeList::const_iterator iter2 = 
            other.extensions->begin();

        while (true)
        {
            if (iter1 != extensions->end() &&
                iter2 == other.extensions->end())
            {
                if (bCppMergeWithExtensionsG    &&
                    extendable                  &&
                    other.extendable)
                {
                    while (iter1 != extensions->end())
                    {
                        if (!(*iter1)->IsOptional())
                        {
                            return false;
                        }

                        iter1++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == extensions->end() &&
                iter2 != other.extensions->end())
            {
                if (bCppMergeWithExtensionsG    &&
                    extendable                  &&
                    other.extendable)
                {
                    while (iter2 != other.extensions->end())
                    {
                        if (!(*iter2)->IsOptional())
                        {
                            return false;
                        }

                        iter2++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == extensions->end() &&
                iter2 == other.extensions->end())
            {
                break;
            }

            Type* type1 = *iter1;
            Type* type2 = *iter2;

            if (!type1->Equals(*type2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    if (extendable != other.extendable)
    {
        return false;
    }

    return true;
}


void
ChoiceType::SetCommonRecursively()
{
    Type::SetCommonRecursively();

    TypeList* ftl = GetFlattenedTypeList();

    for (TypeList::iterator iter = ftl->begin();
         iter != ftl->end();
         iter++)
    {
        Type* type = *iter;

        if (type->GetModule() == GetModule())
        {
            type->SetCommonRecursively();
        }
    }
}


TypeList*
ChoiceType::GetFlattenedTypeList()
{
    flattenedTypeList.clear();

    for (TypeList::iterator iter = typeList->begin();
         iter != typeList->end();
         iter++)
    {
        if ((*iter)->IsComponentsOf())
        {
            TypeList* localComponentsOfList = (*iter)->GetComponentsOfList();

            for (TypeList::iterator cptIter = localComponentsOfList->begin();
                 cptIter != localComponentsOfList->end();
                 cptIter++)
            {
                flattenedTypeList.push_back(*cptIter);
            }
        }
        else
        {
            flattenedTypeList.push_back(*iter);
        }
    }

    if (extendable)
    {
        for (TypeList::iterator iter = extensions->begin();
             iter != extensions->end();
             iter++)
        {
            if ((*iter)->IsComponentsOf())
            {
                TypeList* localComponentsOfList = (*iter)->GetComponentsOfList();

                for (TypeList::iterator cptIter = localComponentsOfList->begin();
                     cptIter != localComponentsOfList->end();
                     cptIter++)
                {
                    flattenedTypeList.push_back(*cptIter);
                }
            }
            else
            {
                flattenedTypeList.push_back(*iter);
            }
        }
    }

    return &flattenedTypeList;
}


void
ChoiceType::MakeNamedTypeTable()
{
    TypeList* ftl = GetFlattenedTypeList();

    for (TypeList::iterator iter = ftl->begin();
         iter != ftl->end();
         iter++)
    {
        Type* type = *iter;

        if (type->IsNamed())
        {
            // Check for duplicate name definitions.

            if (HasNamedType(type->GetName()))
            {
                PrintErrLoc(
                    module->GetAsn1SrcFileName(), 
                    GetLineNumber());
                cerr << "ERROR - CHOICE type contains duplicate alternative ";
                cerr << "name \"";
                cerr << type->GetName();
                cerr << "\".";
                cerr << endl;

                module->AddError(Module::MODULE_SEMANTIC_ERROR);
            }
            else
            {
                namedTypeTable.
                    insert(
                        NamedTypeTable::
                            value_type(
                                type->GetName(),
                                type));
            }
        }
        else
        {
            // TODO: add compiler error, inconsistent with grammar.
        }
    }
}


TagList* 
ChoiceType::GetPossibleTagList()
{
    TagList* result = new TagList();

    TypeList* ftl = GetFlattenedTypeList();

    for (TypeList::iterator iter = ftl->begin();
         iter != ftl->end();
         iter++)
    {
        TagList* adjustedTagList = (*iter)->GetAdjustedTagList();

        if (adjustedTagList->size() == 0)
        {
            Type* baseType = (*iter)->GetBaseType();

            if (baseType->GetType() == TYPE_CHOICE)
            {
                adjustedTagList = baseType->GetAdjustedTagList();

                result->insert(
                            result->end(),
                            adjustedTagList->begin(),
                            adjustedTagList->end());
            }
            else if (baseType->GetType() == TYPE_ANY ||
                     baseType->GetType() == TYPE_ANY_DEFINED_BY)
            {
                Tag* anyTag = new Tag();
                anyTag->SetAny();

                result->push_back(anyTag);
            }
            else
            {
                // Nothing to do. 

                // TODO: check if really nothing to do. How type has no tag?
            }
        }
        else
        {
            result->insert(
                        result->end(), 
                        adjustedTagList->begin(), 
                        adjustedTagList->end());
        }
    }

    return result;
}


Tag* 
ChoiceType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());
    return NULL; // Not reached.
}


void
ChoiceType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    TypeList* typeListToVisit = NULL;

    if (visitor->VisitFlattened())
    {
        typeListToVisit = GetFlattenedTypeList();
    }
    else
    {
        typeListToVisit = new TypeList();

        typeListToVisit->insert(
            typeListToVisit->end(), 
                GetTypeList()->begin(), 
                    GetTypeList()->end());

        if (IsExtendable())
        {
            typeListToVisit->insert(
                typeListToVisit->end(),
                    GetExtensions()->begin(),
                        GetExtensions()->end());
        }
    }

    ASSERT(typeListToVisit != NULL);

    visitor->VisitTypeBegin(this);

    visitor->VisitChoiceTypeBegin(this);

    visitor->VisitChoiceTypeList(typeListToVisit);

    visitor->VisitChoiceTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  EmbeddedPDVType implementation.
//

EmbeddedPDVType::EmbeddedPDVType()
{
}


bool
EmbeddedPDVType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


Tag* 
EmbeddedPDVType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_EMBEDDED_PDV,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  EnumeratedType implementation.
//

EnumeratedType::EnumeratedType(
                    NamedNumberList* namedNumberListParam,
                    bool extendableParam,
                    NamedNumberList* extensionsParam)
:   namedNumberList(namedNumberListParam),
    extendable(extendableParam),
    extensions(extensionsParam)
{
}


bool
EnumeratedType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const EnumeratedType& other = 
        static_cast<const EnumeratedType&> (rhs);

    {
        NamedNumberList::const_iterator iter1 = 
            namedNumberList->begin();

        NamedNumberList::const_iterator iter2 = 
            other.namedNumberList->begin();

        while (true)
        {
            if (iter1 != namedNumberList->end() &&
                iter2 == other.namedNumberList->end())
            {
                return false;
            }

            if (iter1 == namedNumberList->end() &&
                iter2 != other.namedNumberList->end())
            {
                return false;
            }

            if (iter1 == namedNumberList->end() &&
                iter2 == other.namedNumberList->end())
            {
                break;
            }

            NamedNumber* namedNumber1 = *iter1;
            NamedNumber* namedNumber2 = *iter2;

            if (!namedNumber1->Equals(*namedNumber2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    {
        NamedNumberList::const_iterator iter1 = 
            extensions->begin();

        NamedNumberList::const_iterator iter2 = 
            other.extensions->begin();

        while (true)
        {
            if (iter1 != extensions->end() &&
                iter2 == other.extensions->end())
            {
                return false;
            }

            if (iter1 == extensions->end() &&
                iter2 != other.extensions->end())
            {
                return false;
            }

            if (iter1 == extensions->end() &&
                iter2 == other.extensions->end())
            {
                break;
            }

            NamedNumber* namedNumber1 = *iter1;
            NamedNumber* namedNumber2 = *iter2;

            if (!namedNumber1->Equals(*namedNumber2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    if (extendable != other.extendable)
    {
        return false;
    }

    return true;
}


void
EnumeratedType::MakeNamedNumberTable()
{
    for (NamedNumberList::iterator iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        // Check for duplicate names.

        if (HasNamedNumber(namedNumber->GetName()))
        {
            PrintErrLoc(
                module->GetAsn1SrcFileName(),
                GetLineNumber());
            cerr << "ERROR - ENUMERATED type contains duplicate name \"";
            cerr << namedNumber->GetName();
            cerr << "\".";
            cerr << endl;

            module->AddError(Module::MODULE_SEMANTIC_ERROR);
        }
        else
        {
            namedNumberTable.
                insert(
                    NamedNumberTable::
                        value_type(
                            namedNumber->GetName(),
                            namedNumber));
        }
    }

    if (extendable)
    {
        for (NamedNumberList::iterator iter = extensions->begin();
             iter != extensions->end();
             iter++)
        {
            NamedNumber* namedNumber = *iter;

            // Check for duplcate names.

            if (HasNamedNumber(namedNumber->GetName()))
            {
                PrintErrLoc(
                    module->GetAsn1SrcFileName(),
                    GetLineNumber());
                cerr << "ERROR - ENUMERATED type contains duplicate name \"";
                cerr << namedNumber->GetName();
                cerr << "\".";
                cerr << endl;

                module->AddError(Module::MODULE_SEMANTIC_ERROR);
            }
            else
            {
                namedNumberTable.
                    insert(
                        NamedNumberTable::
                            value_type(
                                namedNumber->GetName(),
                                namedNumber));
            }
        }
    }
}


Tag* 
EnumeratedType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_ENUMERATED,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
EnumeratedType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitEnumeratedTypeBegin(this);

    visitor->PushIterContext();

    visitor->SetIterSize(namedNumberList->size());

    for (NamedNumberList::iterator nnIter = namedNumberList->begin();
         nnIter != namedNumberList->end();
         nnIter++)
    {
        if (nnIter == namedNumberList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++nnIter == namedNumberList->end())
        {
            --nnIter;
            visitor->SetIterEnd();
        }
        else
        {
            --nnIter;
            visitor->SetIterMiddle();
        }

        (*nnIter)->Accept(visitor);
    }

    visitor->PopIterContext();

    visitor->VisitEnumeratedTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  InstanceOfType implementation.
//

InstanceOfType::InstanceOfType()
{
}


bool
InstanceOfType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
//  IntegerType implementation.
//

IntegerType::IntegerType()
:   namedNumberList(new NamedNumberList())
{
}


IntegerType::IntegerType(NamedNumberList* namedNumberListParam)
:   namedNumberList(namedNumberListParam)
{
}


bool
IntegerType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const IntegerType& other = 
        static_cast<const IntegerType&> (rhs);

    NamedNumberList::const_iterator iter1 = 
        namedNumberList->begin();

    NamedNumberList::const_iterator iter2 = 
        other.namedNumberList->begin();

    while (true)
    {
        if (iter1 != namedNumberList->end() &&
            iter2 == other.namedNumberList->end())
        {
            return false;
        }

        if (iter1 == namedNumberList->end() &&
            iter2 != other.namedNumberList->end())
        {
            return false;
        }

        if (iter1 == namedNumberList->end() &&
            iter2 == other.namedNumberList->end())
        {
            break;
        }

        NamedNumber* namedNumber1 = *iter1;
        NamedNumber* namedNumber2 = *iter2;

        if (!namedNumber1->Equals(*namedNumber2))
        {
            return false;
        }

        iter1++;
        iter2++;
    }

    return true;
}


Tag* 
IntegerType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_INTEGER,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
IntegerType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitIntegerTypeBegin(this);

    visitor->PushIterContext();

    visitor->SetIterSize(namedNumberList->size());

    if (!(namedNumberList->empty()))
    {
        for (NamedNumberList::iterator nnIter = namedNumberList->begin();
             nnIter != namedNumberList->end();
             nnIter++)
        {
            if (nnIter == namedNumberList->begin())
            {
                visitor->SetIterBegin();
            }
            else if (++nnIter == namedNumberList->end())
            {
                --nnIter;
                visitor->SetIterEnd();
            }
            else
            {
                --nnIter;
                visitor->SetIterMiddle();
            }

            (*nnIter)->Accept(visitor);
        }
    }

    visitor->PopIterContext();

    visitor->VisitIntegerTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  NullType implementation.
//

NullType::NullType()
{
}


bool
NullType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


Tag* 
NullType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_NULL,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
NullType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitNullType(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectClassFieldType implementation.
//

ObjectClassFieldType::ObjectClassFieldType(
                        const string& objectClassNameParam, 
                        const string& objectClassFieldParam)
:   objectClassName(objectClassNameParam),
    objectClassField(objectClassFieldParam)
{
}


bool
ObjectClassFieldType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const ObjectClassFieldType& other = 
        static_cast<const ObjectClassFieldType&> (rhs);

    if (objectClassName != other.objectClassName)
    {
        return false;
    }

    if (objectClassField != other.objectClassField)
    {
        return false;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectIdentifierType implementation.
//

ObjectIdentifierType::ObjectIdentifierType()
{
}


bool
ObjectIdentifierType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


int 
ObjectIdentifierType::GetIdentifierTokenContext() const
{
    return TK_OID_IDENTIFIER;
}


int
ObjectIdentifierType::GetBraceTokenContext() const
{
    return TK_OID_BRACE;
}


Tag* 
ObjectIdentifierType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_OBJECT_IDENTIFIER,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
ObjectIdentifierType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitObjectIdentifierType(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  OctetStringType implementation.
//

OctetStringType::OctetStringType()
{
}


bool
OctetStringType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


Tag* 
OctetStringType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_OCTET_STRING,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
OctetStringType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitOctetStringType(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  RealType implementation.
//

RealType::RealType()
{
}


bool
RealType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


Tag* 
RealType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_REAL,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
RealType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitRealType(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SequenceType implementation.
//

SequenceType::SequenceType(
                TypeList* typeListParam, 
                bool extendableParam, 
                TypeList* extensionsParam)
:   typeList(typeListParam),
    extendable(extendableParam),
    extensions(extensionsParam)
{
}


bool
SequenceType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const SequenceType& other =
        static_cast<const SequenceType&> (rhs);

    {
        TypeList::const_iterator iter1 = 
            typeList->begin();

        TypeList::const_iterator iter2 = 
            other.typeList->begin();

        while (true)
        {
            if (iter1 != typeList->end() &&
                iter2 == other.typeList->end())
            {
                if (bCppMergeWithExtensionsG    && 
                    extendable                  && 
                    other.extendable)
                {
                    while (iter1 != typeList->end())
                    {
                        if (!(*iter1)->IsOptional())
                        {
                            return false;
                        }

                        iter1++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == typeList->end() &&
                iter2 != other.typeList->end())
            {
                if (bCppMergeWithExtensionsG    &&
                    extendable                  &&
                    other.extendable)
                {
                    while (iter2 != other.typeList->end())
                    {
                        if (!(*iter2)->IsOptional())
                        {
                            return false;
                        }

                        iter2++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == typeList->end() &&
                iter2 == other.typeList->end())
            {
                break;
            }

            Type* type1 = *iter1;
            Type* type2 = *iter2;

            if (!type1->Equals(*type2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    {
        TypeList::const_iterator iter1 = 
            extensions->begin();

        TypeList::const_iterator iter2 = 
            other.extensions->begin();

        while (true)
        {
            if (iter1 != extensions->end() &&
                iter2 == other.extensions->end())
            {
                if (bCppMergeWithExtensionsG    &&
                    extendable                  &&
                    other.extendable)
                {
                    while (iter1 != extensions->end())
                    {
                        if (!(*iter1)->IsOptional())
                        {
                            return false;
                        }

                        iter1++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == extensions->end() &&
                iter2 != other.extensions->end())
            {
                if (bCppMergeWithExtensionsG    &&
                    extendable                  &&
                    other.extendable)
                {
                    while (iter2 != other.extensions->end())
                    {
                        if (!(*iter2)->IsOptional())
                        {
                            return false;
                        }

                        iter2++;
                    }

                    break;
                }
                else
                {
                    return false;
                }
            }

            if (iter1 == extensions->end() &&
                iter2 == other.extensions->end())
            {
                break;
            }

            Type* type1 = *iter1;
            Type* type2 = *iter2;

            if (!type1->Equals(*type2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    if (extendable != other.extendable)
    {
        return false;
    }

    return true;
}


void
SequenceType::SetCommonRecursively()
{
    Type::SetCommonRecursively();

    TypeList* ftl = GetFlattenedTypeList();

    for (TypeList::iterator iter = ftl->begin();
         iter != ftl->end();
         iter++)
    {
        Type* type = *iter;

        if (type->GetModule() == GetModule())
        {
            type->SetCommonRecursively();
        }
    }
}


TypeList*
SequenceType::GetFlattenedTypeList()
{
    flattenedTypeList.clear();

    for (TypeList::iterator iter = typeList->begin();
         iter != typeList->end();
         iter++)
    {
        if ((*iter)->IsComponentsOf())
        {
            TypeList* localComponentsOfList = (*iter)->GetComponentsOfList();

            for (TypeList::iterator cptIter = localComponentsOfList->begin();
                 cptIter != localComponentsOfList->end();
                 cptIter++)
            {
                flattenedTypeList.push_back(*cptIter);
            }
        }
        else
        {
            flattenedTypeList.push_back(*iter);
        }
    }

    if (extendable)
    {
        for (TypeList::iterator iter = extensions->begin();
             iter != extensions->end();
             iter++)
        {
            if ((*iter)->IsComponentsOf())
            {
                TypeList* localComponentsOfList = (*iter)->GetComponentsOfList();

                for (TypeList::iterator cptIter = localComponentsOfList->begin();
                     cptIter != localComponentsOfList->end();
                     cptIter++)
                {
                    flattenedTypeList.push_back(*cptIter);
                }
            }
            else
            {
                flattenedTypeList.push_back(*iter);
            }
        }
    }

    return &flattenedTypeList;
}


void
SequenceType::MakeNamedTypeTable()
{
    TypeList* ftl = GetFlattenedTypeList();

    for (TypeList::iterator iter = ftl->begin();
         iter != ftl->end();
         iter++)
    {
        Type* type = *iter;

        if (type->IsNamed())
        {
            // Check for duplicate name definitions.

            if (HasNamedType(type->GetName()))
            {
                PrintErrLoc(
                    module->GetAsn1SrcFileName(), 
                    GetLineNumber());
                cerr << "ERROR - SEQUENCE or SET type contains duplicate ";
                cerr << "component name \"";
                cerr << type->GetName();
                cerr << "\".";
                cerr << endl;

                module->AddError(Module::MODULE_SEMANTIC_ERROR);
            }
            else
            {
                namedTypeTable.
                    insert(
                        NamedTypeTable::
                            value_type(
                                type->GetName(),
                                type));
            }
        }
        else
        {
            // TODO: add compiler error, inconsistent with grammar.
        }
    }
}


Tag* 
SequenceType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_SEQUENCE,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_CONSTRUCTED);

    return result;
}


void
SequenceType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    TypeList* typeListToVisit = NULL;

    if (visitor->VisitFlattened())
    {
        typeListToVisit = GetFlattenedTypeList();
    }
    else
    {
        typeListToVisit = new TypeList();

        typeListToVisit->insert(
            typeListToVisit->end(), 
                GetTypeList()->begin(), 
                    GetTypeList()->end());

        if (IsExtendable())
        {
            typeListToVisit->insert(
                typeListToVisit->end(),
                    GetExtensions()->begin(),
                        GetExtensions()->end());
        }
    }

    ASSERT(typeListToVisit != NULL);

    visitor->VisitTypeBegin(this);

    visitor->VisitSequenceTypeBegin(this);

    visitor->VisitSequenceTypeList(typeListToVisit);

    visitor->VisitSequenceTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SequenceOfType implementation.
//

SequenceOfType::SequenceOfType(Type* typeParam, Constraint* constraintParam)
:   type(typeParam),
    constraint(constraintParam)
{
    REQUIRE(typeParam != NULL);

    if (constraintParam != NULL)
    {
        hasConstraint = true;
    }
    else
    {
        hasConstraint = false;
    }
}


bool
SequenceOfType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const SequenceOfType& other = 
        static_cast<const SequenceOfType&> (rhs);

    if (type != NULL && other.type == NULL ||
        type == NULL && other.type != NULL)
    {
        return false;
    }

    if (type != NULL && other.type != NULL)
    {
        if (!type->Equals(*other.type))
        {
            return false;
        }
    }

    if (hasConstraint != other.hasConstraint)
    {
        return false;
    }

    if (constraint != NULL && other.constraint == NULL ||
        constraint == NULL && other.constraint != NULL)
    {
        return false;
    }

    if (constraint != NULL && other.constraint != NULL)
    {
        if (!constraint->Equals(*other.constraint))
        {
            return false;
        }
    }

    return true;
}


void
SequenceOfType::SetCommonRecursively()
{
    Type::SetCommonRecursively();

    if (type->GetModule() == GetModule())
    {
        type->SetCommonRecursively();
    }
}


Tag* 
SequenceOfType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_SEQUENCE,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_CONSTRUCTED);

    return result;
}


void
SequenceOfType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    if (hasConstraint)
    {
        visitor->VisitSequenceOfConstraint(constraint);
    }

    visitor->VisitSequenceOfTypeBegin(this);

    visitor->VisitSequenceOfTypeType(type);

    visitor->VisitSequenceOfTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SetType implementation.
//

SetType::SetType()
:   SequenceType(new TypeList(), false, new TypeList())
{
}

SetType::SetType(SequenceType* sequenceTypeParam)
:   SequenceType(*sequenceTypeParam)
{
}

SetType::SetType(
            TypeList* typeListParam, 
            bool extendableParam, 
            TypeList* extensionsParam)
:   SequenceType(typeListParam, extendableParam, extensionsParam)
{
}


bool
SetType::Equals(const Type& rhs) const
{
    if (!SequenceType::Equals(rhs))
    {
        return false;
    }

    return true;
}


Tag* 
SetType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_SET,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_CONSTRUCTED);

    return result;
}


void
SetType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    TypeList* typeListToVisit = NULL;

    if (visitor->VisitFlattened())
    {
        typeListToVisit = GetFlattenedTypeList();
    }
    else
    {
        typeListToVisit = new TypeList();

        typeListToVisit->insert(
            typeListToVisit->end(), 
                GetTypeList()->begin(), 
                    GetTypeList()->end());

        if (IsExtendable())
        {
            typeListToVisit->insert(
                typeListToVisit->end(),
                    GetExtensions()->begin(),
                        GetExtensions()->end());
        }
    }

    ASSERT(typeListToVisit != NULL);

    visitor->VisitTypeBegin(this);

    visitor->VisitSetTypeBegin(this);

    visitor->VisitSetTypeList(typeListToVisit);

    visitor->VisitSetTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SetOfType implementation.
//

SetOfType::SetOfType(Type* typeParam, Constraint* constraintParam)
:   type(typeParam),
    constraint(constraintParam)
{
    REQUIRE(typeParam != NULL);

    if (constraintParam != NULL)
    {
        hasConstraint = true;
    }
    else
    {
        hasConstraint = false;
    }
}


bool
SetOfType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const SetOfType& other = 
        static_cast<const SetOfType&> (rhs);

    if (type != NULL && other.type == NULL ||
        type == NULL && other.type != NULL)
    {
        return false;
    }

    if (type != NULL && other.type != NULL)
    {
        if (!type->Equals(*other.type))
        {
            return false;
        }
    }

    if (hasConstraint != other.hasConstraint)
    {
        return false;
    }

    if (constraint != NULL && other.constraint == NULL ||
        constraint == NULL && other.constraint != NULL)
    {
        return false;
    }

    if (constraint != NULL && other.constraint != NULL)
    {
        if (!constraint->Equals(*other.constraint))
        {
            return false;
        }
    }

    return true;
}


void
SetOfType::SetCommonRecursively()
{
    Type::SetCommonRecursively();

    if (type->GetModule() == GetModule())
    {
        type->SetCommonRecursively();
    }
}


Tag* 
SetOfType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_SET,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_CONSTRUCTED);

    return result;
}


void
SetOfType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    if (hasConstraint)
    {
        visitor->VisitSetOfConstraint(constraint);
    }

    visitor->VisitSetOfTypeBegin(this);

    visitor->VisitSetOfTypeType(type);

    visitor->VisitSetOfTypeEnd(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ImportedType implementation.
//

ImportedType::ImportedType(const string& nameParam, bool isParameterizedParam)
:   name(nameParam),
    isParameterized(isParameterizedParam)
{
}


bool
ImportedType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const ImportedType& other = 
        static_cast<const ImportedType&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    if (isParameterized != other.isParameterized)
    {
        return false;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
//  DefinedType implementation.
//

DefinedType::DefinedType(const string& nameParam, bool notUsedParam)
:   name(nameParam),
    isLinked(false),
    link(NULL)
{
}


bool
DefinedType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const DefinedType& other =
        static_cast<const DefinedType&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    if (isLinked != other.isLinked)
    {
        return false;
    }

    if (link != NULL && other.link == NULL ||
        link == NULL && other.link != NULL)
    {
        return false;
    }

    if (link != NULL && other.link != NULL)
    {
        if (!link->Equals(*other.link))
        {
            return false;
        }
    }

    if (typeDefLink != NULL && other.typeDefLink == NULL ||
        typeDefLink == NULL && other.typeDefLink != NULL)
    {
        return false;
    }

    if (typeDefLink != NULL && other.typeDefLink != NULL)
    {
        if (!typeDefLink->Equals(*other.typeDefLink))
        {
            return false;
        }
    }

    return true;
}
 

void
DefinedType::SetCommonRecursively()
{ 
    Type::SetCommonRecursively();

    if (IsLinked())
    {
        if (link->GetModule() == GetModule())
        {
            link->SetCommonRecursively();
            typeDefLink->SetCommon();
        }
    }
}


TagList*
DefinedType::GetFullTagList() const
{
    REQUIRE(IsLinked());

    TagList* result = new TagList();

    result->insert(result->end(), tagList->begin(), tagList->end());

    TagList* linkTagList = link->GetFullTagList();

    result->insert(result->end(), linkTagList->begin(), linkTagList->end());

    return result;
}


Tag* 
DefinedType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    return NULL; // Not reached.
}


void
DefinedType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitDefinedType(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ParameterizedType implementation.
//

ParameterizedType::ParameterizedType(const string& nameParam, TypeList* typeListParam)
:   DefinedType(nameParam),
    typeList(typeListParam)
{
}


bool
ParameterizedType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const ParameterizedType& other =
        static_cast<const ParameterizedType&> (rhs);

    TypeList::const_iterator iter1 = 
        typeList->begin();

    TypeList::const_iterator iter2 = 
        other.typeList->begin();

    while (true)
    {
        if (iter1 != typeList->end() &&
            iter2 == other.typeList->end())
        {
            return false;
        }

        if (iter1 == typeList->end() &&
            iter2 != other.typeList->end())
        {
            return false;
        }

        if (iter1 == typeList->end() &&
            iter2 == other.typeList->end())
        {
            break;
        }

        Type* type1 = *iter1;
        Type* type2 = *iter2;

        if (!type1->Equals(*type2))
        {
            return false;
        }

        iter1++;
        iter2++;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
//  SelectionType implementation.
//

SelectionType::SelectionType(const string& nameParam, Type* typeParam)
:   name(nameParam),
    type(typeParam)
{
}


bool
SelectionType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const SelectionType& other =
        static_cast<const SelectionType&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    if (type != NULL && other.type == NULL ||
        type == NULL && other.type != NULL)
    {
        return false;
    }

    if (type != NULL && other.type != NULL)
    {
        if (!type->Equals(*other.type))
        {
            return false;
        }
    }

    return true;
}


TagList*
SelectionType::GetFullTagList() const
{
    bool not_implemented = false;

    ASSERT(not_implemented);

    // TODO: to be implemented.

    return NULL; // Not reached.
}


////////////////////////////////////////////////////////////////////////////////
//
//  UsefulType implementation.
//

UsefulType::UsefulType()
{
}


bool
UsefulType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
//  AnyType implementation.
//

AnyType::AnyType()
{
}


bool
AnyType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
AnyType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitAnyType(this);

    visitor->VisitTypeEnd(this);
}



////////////////////////////////////////////////////////////////////////////////
//
//  AnyDefinedByType implementation.
//

AnyDefinedByType::AnyDefinedByType(const string& nameParam)
:   name(nameParam)
{
}


bool
AnyDefinedByType::Equals(const Type& rhs) const
{
    if (!Type::Equals(rhs))
    {
        return false;
    }

    const AnyDefinedByType& other =
        static_cast<const AnyDefinedByType&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    return true;
}


void
AnyDefinedByType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitAnyDefinedByType(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ValueDef implementation.
//

ValueDef::ValueDef(
                const std::string& definedNameParam,
                Type* typeParam,
                Value* valueParam)
:   definedName(definedNameParam),
    type(typeParam),
    value(valueParam),
    isRecursive(false),
    isMarked(false),
    isExported(false),
    localRefCount(0),
    importRefCount(0)
{
}


bool
ValueDef::Equals(const ValueDef& rhs) const
{
    if (definedName != rhs.definedName)
    {
        return false;
    }

    if (type == NULL && rhs.type != NULL)
    {
        return false;
    }

    if (type != NULL && rhs.type == NULL)
    {
        return false;
    }

    if (type != NULL && rhs.type != NULL)
    {
        if (!type->Equals(*rhs.type))
        {
            return false;
        }
    }

    if (value == NULL && rhs.value != NULL)
    {
        return false;
    }

    if (value != NULL && rhs.value == NULL)
    {
        return false;
    }

    if (value != NULL && rhs.value != NULL)
    {
        if (!value->Equals(*rhs.value))
        {
            return false;
        }
    }

    return true;
}


Value*
Value::GetBaseValue() const
{
    Value* result = const_cast<Value*> (this);

    bool stop = false;

    while(!stop)
    {
        switch (result->GetValueType())
        {
        case VALUE_DEFINED:
        {
            DefinedValue* definedValue = static_cast<DefinedValue*> (result);

            if (definedValue->IsLinked())
            {
                result = definedValue->GetLink();
            }
            else
            {
                result  = definedValue;
                stop    = true;
            }

            break;
        }
        default:
        {
            stop = true;
        }
        }
    }

    ENSURE(result != NULL);

    return result;
}


void
ValueDef::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    visitor->VisitValueDefBegin(this);

    visitor->VisitValueDefType(this, type);

    visitor->VisitValueDefMiddle(this);

    value->Accept(visitor);

    visitor->VisitValueDefEnd(this);
}


string
ValueDef::ToString() const
{
    ostrstream ostrs;

    Print(ostrs);

    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    return result;
}


void
ValueDef::Print(ostream& os) const
{
    PrintVisitor printVisitor(os);

    (const_cast<ValueDef*> (this))->Accept(&printVisitor);
}


////////////////////////////////////////////////////////////////////////////////
//
// ValueDef ostream operator<< implementation.

ostream& operator<<(ostream& os, const ValueDef& valueDef)
{
    valueDef.Print(os);
    return os;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Value implementation.
//

Value::Value()
:   isNamed(false),
    hasLineNumber(false),
    name(""),
    lineNumber(0),
    hasModule(false),
    module(NULL),
    hasAssociatedType(false),
    associatedType(NULL)
{
}


bool
Value::Equals(const Value& rhs) const
{
    if (GetValueType() != rhs.GetValueType())
    {
        return false;
    }

    if (isNamed != rhs.isNamed)
    {
        return false;
    }

    if (hasAssociatedType != rhs.hasAssociatedType)
    {
        return false;
    }

    if (associatedType == NULL && rhs.associatedType != NULL)
    {
        return false;
    }

    if (associatedType != NULL && rhs.associatedType == NULL)
    {
        return false;
    }

    if (associatedType != NULL && rhs.associatedType != NULL)
    {
        if (!associatedType->Equals(*rhs.associatedType))
        {
            return false;
        }
    }

    return true;
}


void
Value::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    // TODO: to be completed.
}


string
Value::ToString() const
{
    ostrstream ostrs;

    Print(ostrs);

    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    return result;
}
    

void
Value::Print(ostream& os) const
{
    PrintVisitor printVisitor(os);

    (const_cast<Value*> (this))->Accept(&printVisitor);
}


////////////////////////////////////////////////////////////////////////////////
//
// Value ostream operator<< implementation.

ostream& operator<<(ostream& os, const Value& value)
{
    value.Print(os);
    return os;
}


////////////////////////////////////////////////////////////////////////////////
//
//  BooleanValue implementation.
//

BooleanValue::BooleanValue(bool valueParam)
:   value(valueParam)
{
}


bool
BooleanValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const BooleanValue& other =
        static_cast<const BooleanValue&> (rhs);

    if (value != other.value)
    {
        return false;
    }

    return true;
}


void
BooleanValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitBooleanValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ChoiceValue implementation.
//

ChoiceValue::ChoiceValue(const string& nameParam, Value* valueParam)
:   name(nameParam),
    value(valueParam)
{
    REQUIRE(valueParam != NULL);
}


bool
ChoiceValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const ChoiceValue& other =
        static_cast<const ChoiceValue&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    if (value == NULL && other.value != NULL)
    {
        return false;
    }

    if (value != NULL && other.value == NULL)
    {
        return false;
    }

    if (value != NULL && other.value != NULL)
    {
        if (!value->Equals(*other.value))
        {
            return false;
        }
    }

    return false;
}


void
ChoiceValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitChoiceValue(this);

    value->Accept(visitor);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  EnumeratedValue implementation.
//

EnumeratedValue::EnumeratedValue(const string& nameParam)
:   name(nameParam)
{
}


bool
EnumeratedValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const EnumeratedValue& other =
        static_cast<const EnumeratedValue&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    return true;
}


void
EnumeratedValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitEnumeratedValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  IntegerValue implementation.
//

IntegerValue::IntegerValue(long valueParam)
:   value(valueParam)
{
}


bool
IntegerValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const IntegerValue& other =
        static_cast<const IntegerValue&> (rhs);

    if (value != other.value)
    {
        return false;
    }

    return true;
}


void
IntegerValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitIntegerValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  RealValue implementation.
//

RealValue::RealValue(double valueParam)
:   value(valueParam)
{
}


bool
RealValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const RealValue& other =
        static_cast<const RealValue&> (rhs);

    if (value != other.value)
    {
        return false;
    }

    return true;
}


void
RealValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitRealValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  OctetStringValue implementation.
//


OctetStringValue::OctetStringValue()
:   value("")
{
}


OctetStringValue::OctetStringValue(const string& valueParam)
:   value(valueParam)
{
}


bool
OctetStringValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const OctetStringValue& other =
        static_cast<const OctetStringValue&> (rhs);

    if (value != other.value)
    {
        return false;
    }

    return true;
}


void
OctetStringValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitOctetStringValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  BitStringValue implementation.
//

BitStringValue::BitStringValue()
:   value("")
{
}


BitStringValue::BitStringValue(const string& valueParam)
:   value(valueParam)
{
}


BitStringValue::BitStringValue(list<string*>* listParam)
:   value("")
{
    // TODO: to be done.
}


bool
BitStringValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const BitStringValue& other =
        static_cast<const BitStringValue&> (rhs);

    if (value != other.value)
    {
        return false;
    }

    return true;
}


void
BitStringValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitBitStringValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  NullValue implementation.
//

NullValue::NullValue()
{
}


bool
NullValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
NullValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitNullValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  CharacterStringValue implementation.
//

CharacterStringValue::CharacterStringValue()
:   value("")
{
}


CharacterStringValue::CharacterStringValue(const string& valueParam)
:   value(valueParam)
{
}


CharacterStringValue::CharacterStringValue(list<string*>* listParam)
:   value("")
{
    // TODO: to be done.
}


bool
CharacterStringValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const CharacterStringValue& other =
        static_cast<const CharacterStringValue&> (rhs);

    if (value != other.value)
    {
        return false;
    }

    return true;;
}


void
CharacterStringValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitCharacterStringValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectIdentifierValue implementation.
//

ObjectIdentifierValue::ObjectIdentifierValue(const string& valueParam)
:   value(valueParam)
{
}


bool
ObjectIdentifierValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const ObjectIdentifierValue& other =
        static_cast<const ObjectIdentifierValue&> (rhs);

    if (value != other.value)
    {
        return false;
    }

    if (componentList != other.componentList)
    {
        return false;
    }

    return true;
}


void ObjectIdentifierValue::MakeComponentList()
{
    //
    // Note: since validated by lexer value string has the following format 
    // " xxx(nn1) yyy(nn2) zzz(nn3) " where nn1, nn2 ... are numbers. 
    // 

    string numberStr;

    numberStr.reserve(32);

    bool inNumber = false;

    for (size_t i = 0; i < value.size(); i++)
    {
        char c = value[i];

        if (c == '(')
        {
            inNumber = true;
        }

        if (inNumber && (c != '(') && (c != ')') && (c != ' '))
        {
            numberStr.append(1, c);
        }

        if (c == ')')
        {
            inNumber = false;

            long componentValue = 0;

            int res = sscanf(numberStr.c_str(), "%ld", &componentValue);

            ASSERT(res == 1); // Must read exactly one field.

            componentList.push_back(componentValue);

            numberStr.erase();
        }
    }
}

void
ObjectIdentifierValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitObjectIdentifierValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  MinValue implementation.
//

MinValue::MinValue()
{
}


bool
MinValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
MinValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitMinValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  MaxValue implementation.
//

MaxValue::MaxValue()
{
}


bool
MaxValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
MaxValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitMaxValue(this);

    visitor->VisitValueEnd(this);
}



////////////////////////////////////////////////////////////////////////////////
//
//  SequenceValue implementation.
//

SequenceValue::SequenceValue()
:   valueList(new ValueList()),
    polymorphValueType(VALUE_SEQUENCE),
    hasUnnamedValue(false),
    hasNamedValue(false)
{
}


SequenceValue::SequenceValue(ValueList* valueListParam)
:   valueList(valueListParam),
    polymorphValueType(VALUE_SEQUENCE),
    hasUnnamedValue(false),
    hasNamedValue(false)
{
    REQUIRE(valueListParam != NULL);
}


bool
SequenceValue::Equals(const Value& rhs) const
{
    bool not_implemented = false;
    ASSERT(not_implemented);

    return false;
}


void
SequenceValue::MakeNamedValueTable()
{
    for (ValueList::iterator iter = valueList->begin();
         iter != valueList->end();
         iter++)
    {
        Value* value = *iter;

        if (value->IsNamed())
        {
            if (value->GetName() == "--AsnCC-Unnamed--")
            {
                hasUnnamedValue = true;
            }
            else
            {
                hasNamedValue = true;

                if (HasNamedValue(value->GetName()))
                {
                    PrintErrLoc(
                        module->GetAsn1SrcFileName(),
                        GetLineNumber());
                    cerr << "ERROR - SEQUENCE, SEQUENCE OF, SET or SET OF has ";
                    cerr << "duplicate value name \"";
                    cerr << value->GetName();
                    cerr << "\".";
                    cerr << endl;
                }
                else
                {
                    namedValueTable.
                        insert(
                            NamedValueTable::
                                value_type(
                                    value->GetName(),
                                    value));
                }
            }
        }
        else
        {
            hasUnnamedValue = true;
        }
    }
}


void
SequenceValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitSequenceValueBegin(this);

    visitor->PushIterContext();

    visitor->SetIterSize(valueList->size());

    for (ValueList::iterator vIter = valueList->begin();
         vIter != valueList->end();
         vIter++)
    {
        if (vIter == valueList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++vIter == valueList->end())
        {
            --vIter;
            visitor->SetIterEnd();
        }
        else
        {
            --vIter;
            visitor->SetIterMiddle();
        }

        (*vIter)->Accept(visitor);
    }

    visitor->PopIterContext();

    visitor->VisitSequenceValueEnd(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SequenceOfValue implementation.
//

SequenceOfValue::SequenceOfValue(ValueList* valueListParam)
:   valueList(valueListParam)
{
    REQUIRE(valueListParam != NULL);

    bool must_not_be_used = false; // SequenceValue is used.
    ASSERT(must_not_be_used);
}


bool
SequenceOfValue::Equals(const Value& rhs) const
{
    bool not_implemented = false;
    ASSERT(not_implemented);

    return false;
}


void
SequenceOfValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    bool must_not_be_used = false; // SequenceValue is used.
    ASSERT(must_not_be_used);
}

////////////////////////////////////////////////////////////////////////////////
//
//  SetValue implementation.
//

SetValue::SetValue(ValueList* valueListParam)
:   valueList(valueListParam)
{
    REQUIRE(valueListParam != NULL);

    bool must_not_be_used = false; // SequenceValue is used.
    ASSERT(must_not_be_used);
}


bool
SetValue::Equals(const Value& rhs) const
{
    bool not_implemented = false;
    ASSERT(not_implemented);

    return false;
}


void
SetValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    bool must_not_be_used = false; // SequenceValue is used.
    ASSERT(must_not_be_used);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SetOfValue implementation.
//

SetOfValue::SetOfValue(ValueList* valueListParam)
:   valueList(valueListParam)
{
    REQUIRE(valueListParam != NULL);

    bool must_not_be_used = false; // SequenceValue is used.
    ASSERT(must_not_be_used);
}


bool
SetOfValue::Equals(const Value& rhs) const
{
    bool not_implemented = false;
    ASSERT(not_implemented);

    return false;
}


void
SetOfValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    bool must_not_be_used = false; // SequenceValue is used.
    ASSERT(must_not_be_used);
}


////////////////////////////////////////////////////////////////////////////////
//
//  DefinedValue implementation.
//

DefinedValue::DefinedValue(const string& nameParam)
:   name(nameParam),
    isLinked(false),
    link(NULL),
    isEnumeratedValue(false)
{
}


bool
DefinedValue::Equals(const Value& rhs) const
{
    if (!Value::Equals(rhs))
    {
        return false;
    }

    const DefinedValue& other =
        static_cast<const DefinedValue&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    if (isLinked != other.isLinked)
    {
        return false;
    }

    if (link != NULL && other.link == NULL ||
        link == NULL && other.link != NULL)
    {
        return false;
    }

    if (link != NULL && other.link != NULL)
    {
        if (!link->Equals(*other.link))
        {
            return false;
        }
    }

    if (valueDefLink != NULL && other.valueDefLink == NULL ||
        valueDefLink == NULL && other.valueDefLink != NULL)
    {
        return false;
    }

    if (valueDefLink != NULL && other.valueDefLink != NULL)
    {
        if (!valueDefLink->Equals(*other.valueDefLink))
        {
            return false;
        }
    }

    if (isEnumeratedValue != other.isEnumeratedValue)
    {
        return false;
    }

    return true;
}


void
DefinedValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitDefinedValue(this);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  AnyValue implementation.
//

AnyValue::AnyValue(Type* typeParam, Value* valueParam)
:   type(typeParam),
    value(valueParam)
{
}


bool
AnyValue::Equals(const Value& rhs) const
{
    bool not_implemented = false;
    ASSERT(not_implemented);

    return false;
}


void
AnyValue::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Value::Accept(visitor);

    visitor->VisitValueBegin(this);

    visitor->VisitAnyValue(this);

    value->Accept(visitor);

    visitor->VisitValueEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  NamedNumber implementation.
//

NamedNumber::NamedNumber(const string& nameParam)
:   name(nameParam),
    number(0),
    definedValue(NULL),
    hasNumber(false),
    hasDefinedValue(false),
    isAutoNumber(false)
{
}


NamedNumber::NamedNumber(const string& nameParam, long numberParam)
:   name(nameParam),
    number(numberParam),
    definedValue(NULL),
    hasNumber(true),
    hasDefinedValue(false),
    isAutoNumber(false)
{
}


NamedNumber::NamedNumber(
                    const string& nameParam, 
                    DefinedValue* definedValueParam)
:   name(nameParam),
    number(0),
    definedValue(definedValueParam),
    hasNumber(false),
    hasDefinedValue(true),
    isAutoNumber(false)
{
}


bool
NamedNumber::Equals(const NamedNumber& rhs) const
{
    if (name != rhs.name)
    {
        return false;
    }

    if (number != rhs.number)
    {
        return false;
    }

    if (definedValue != NULL && rhs.definedValue == NULL ||
        definedValue == NULL && rhs.definedValue != NULL)
    {
        return false;
    }

    if (definedValue != NULL && rhs.definedValue != NULL)
    {
        if (!definedValue->Equals(*rhs.definedValue))
        {
            return false;
        }
    }

    if (hasNumber != rhs.hasNumber)
    {
        return false;
    }

    if (hasDefinedValue != rhs.hasDefinedValue)
    {
        return false;
    }

    if (isAutoNumber != rhs.isAutoNumber)
    {
        return false;
    }

    return true;
}


void
NamedNumber::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    visitor->VisitNamedNumberBegin(this);

    if (hasDefinedValue)
    {
        definedValue->Accept(visitor);
    }

    visitor->VisitNamedNumberEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  Constraint implementation.
//

Constraint::Constraint(ConstraintElement* constraintElementParam)
:   isExtendable(false),
    hasExtensions(false),
    extensions(NULL)
{
    REQUIRE(constraintElementParam != NULL);
    constraintElementList = new ConstraintElementList();
    constraintElementList->push_back(constraintElementParam);
}


Constraint::Constraint(
                ConstraintElementList* constraintElementListParam, 
                bool isExtendableParam, 
                ConstraintElementList* extensionsParam)
:   constraintElementList(constraintElementListParam),
    isExtendable(isExtendableParam),
    extensions(extensionsParam)
{
    REQUIRE(constraintElementListParam != NULL);

    if (extensionsParam == NULL)
    {
        hasExtensions = false;
    }
    else
    {
        hasExtensions = true;
    }
}


bool 
Constraint::Equals(const Constraint& rhs) const
{
    {
        ConstraintElementList::const_iterator iter1 = 
            constraintElementList->begin();

        ConstraintElementList::const_iterator iter2 = 
            rhs.constraintElementList->begin();

        while (true)
        {
            if (iter1 != constraintElementList->end() &&
                iter2 == rhs.constraintElementList->end())
            {
                return false;
            }

            if (iter1 == constraintElementList->end() &&
                iter2 != rhs.constraintElementList->end())
            {
                return false;
            }

            if (iter1 == constraintElementList->end() &&
                iter2 == rhs.constraintElementList->end())
            {
                break;
            }

            ConstraintElement* constraintElement1 = *iter1;
            ConstraintElement* constraintElement2 = *iter2;

            if (!constraintElement1->Equals(*constraintElement2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    if (isExtendable != rhs.isExtendable)
    {
        return false;
    }

    if (hasExtensions != rhs.hasExtensions)
    {
        return false;
    }

    if (hasExtensions && rhs.hasExtensions)
    {
        ASSERT(extensions != NULL);
        ASSERT(rhs.extensions != NULL);

        ConstraintElementList::const_iterator iter1 = 
            extensions->begin();

        ConstraintElementList::const_iterator iter2 = 
            rhs.extensions->begin();

        while (true)
        {
            if (iter1 != extensions->end() &&
                iter2 == rhs.extensions->end())
            {
                return false;
            }

            if (iter1 == extensions->end() &&
                iter2 != rhs.extensions->end())
            {
                return false;
            }

            if (iter1 == extensions->end() &&
                iter2 == rhs.extensions->end())
            {
                break;
            }

            ConstraintElement* constraintElement1 = *iter1;
            ConstraintElement* constraintElement2 = *iter2;

            if (!constraintElement1->Equals(*constraintElement2))
            {
                return false;
            }

            iter1++;
            iter2++;
        }
    }

    return true;
}


void
Constraint::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    visitor->VisitConstraintBegin(this);

    visitor->PushIterContext();

    visitor->SetIterSize(constraintElementList->size());

    for (ConstraintElementList::iterator ceIter = 
            constraintElementList->begin();
         ceIter != constraintElementList->end();
         ceIter++)
    {
        if (ceIter == constraintElementList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++ceIter == constraintElementList->end())
        {
            --ceIter;
            visitor->SetIterEnd();
        }
        else
        {
            --ceIter;
            visitor->SetIterMiddle();
        }

        (*ceIter)->Accept(visitor);
    }

    visitor->PopIterContext();

    visitor->VisitConstraintEnd(this);
}


string
Constraint::ToString() const
{
    ostrstream ostrs;

    Print(ostrs);

    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    return result;
}
    

void
Constraint::Print(ostream& os) const
{
    PrintVisitor printVisitor(os);

    (const_cast<Constraint*> (this))->Accept(&printVisitor);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ConstraintElement implementation.
//
    
ConstraintElement::ConstraintElement()
:   hasExclusions(false),
    exclusions(NULL)
{
}


bool 
ConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (GetType() != rhs.GetType())
    {
        return false;
    }

    if (hasExclusions != rhs.hasExclusions)
    {
        return false;
    }

    if (exclusions == NULL && rhs.exclusions != NULL)
    {
        return false;
    }

    if (exclusions != NULL && rhs.exclusions == NULL)
    {
        return false;
    }

    if (exclusions != NULL && rhs.exclusions != NULL)
    {
        if (!exclusions->Equals(*rhs.exclusions))
        {
            return false;
        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
//  ConstrainAllConstraintElement implementation.
//

ConstrainAllConstraintElement::ConstrainAllConstraintElement(
                                    ConstraintElement* exclusionsParam)
{
    REQUIRE(exclusionsParam != NULL);
    SetExclusions(exclusionsParam);
}


bool 
ConstrainAllConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!ConstraintElement::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
ConstrainAllConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitConstrainAllConstraintElementBegin(this);

    visitor->VisitConstrainAllConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ElementListConstraintElement implementation.
//

ElementListConstraintElement::ElementListConstraintElement(
                            ConstraintElementList* constraintElementListParam)
:   constraintElementList(constraintElementListParam)
{
    REQUIRE(constraintElementListParam != NULL);
}


bool 
ElementListConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!ConstraintElement::Equals(rhs))
    {
        return false;
    }

    const ElementListConstraintElement& other =
        static_cast<const ElementListConstraintElement&> (rhs);

    ConstraintElementList::const_iterator iter1 = 
        constraintElementList->begin();

    ConstraintElementList::const_iterator iter2 = 
        other.constraintElementList->begin();

    while (true)
    {
        if (iter1 != constraintElementList->end() &&
            iter2 == other.constraintElementList->end())
        {
            return false;
        }

        if (iter1 == constraintElementList->end() &&
            iter2 != other.constraintElementList->end())
        {
            return false;
        }

        if (iter1 == constraintElementList->end() &&
            iter2 == other.constraintElementList->end())
        {
            break;
        }

        ConstraintElement* constraintElement1 = *iter1;
        ConstraintElement* constraintElement2 = *iter2;

        if (!constraintElement1->Equals(*constraintElement2))
        {
            return false;
        }

        iter1++;
        iter2++;
    }

    return true;
}


void
ElementListConstraintElement::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    visitor->VisitElementListConstraintElementBegin(this);

    visitor->PushIterContext();

    visitor->SetIterSize(constraintElementList->size());

    for (ConstraintElementList::iterator ceIter = 
            constraintElementList->begin();
         ceIter != constraintElementList->end();
         ceIter++)
    {
        if (ceIter == constraintElementList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++ceIter == constraintElementList->end())
        {
            --ceIter;
            visitor->SetIterEnd();
        }
        else
        {
            --ceIter;
            visitor->SetIterMiddle();
        }

        (*ceIter)->Accept(visitor);
    }

    visitor->PopIterContext();

    visitor->VisitElementListConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SingleValueConstraintElement implementation.
//

SingleValueConstraintElement::SingleValueConstraintElement(Value* valueParam)
:   value(valueParam)
{
    REQUIRE(valueParam != NULL);
}


bool 
SingleValueConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!ConstraintElement::Equals(rhs))
    {
        return false;
    }

    const SingleValueConstraintElement& other =
        static_cast<const SingleValueConstraintElement&> (rhs);

    if (value != NULL && other.value == NULL ||
        value == NULL && other.value != NULL)
    {
        return false;
    }

    if (value != NULL && other.value != NULL)
    {
        if (!value->Equals(*other.value))
        {
            return false;
        }
    }

    return true;
}


void
SingleValueConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitSingleValueConstraintElementBegin(this);

    value->Accept(visitor);

    visitor->VisitSingleValueConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ValueRangeConstraintElement implementation.
//

ValueRangeConstraintElement::ValueRangeConstraintElement(
                                            Value* lowerParam, 
                                            Value* upperParam)
:   lower(lowerParam),
    upper(upperParam)
{
    REQUIRE(lowerParam != NULL);
    REQUIRE(upperParam != NULL);
}


bool 
ValueRangeConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!ConstraintElement::Equals(rhs))
    {
        return false;
    }

    const ValueRangeConstraintElement& other =
        static_cast<const ValueRangeConstraintElement&> (rhs);

    if (lower != NULL && other.lower == NULL ||
        lower == NULL && other.lower != NULL)
    {
        return false;
    }

    if (lower != NULL && other.lower != NULL)
    {
        if (!lower->Equals(*other.lower))
        {
            return false;
        }
    }

    if (upper != NULL && other.upper == NULL ||
        upper == NULL && other.upper != NULL)
    {
        return false;
    }

    if (upper != NULL && other.upper != NULL)
    {
        if (!upper->Equals(*other.upper))
        {
            return false;
        }
    }

    return true;
}


void
ValueRangeConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitValueRangeConstraintElementBegin(this);

    lower->Accept(visitor);

    visitor->VisitValueRangeConstraintElementMiddle(this);

    upper->Accept(visitor);

    visitor->VisitValueRangeConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  NestedConstraintConstraintElement implementation.
//

NestedConstraintConstraintElement::NestedConstraintConstraintElement(
                                                    Constraint* constraintParam)
:   constraint(constraintParam)
{
    REQUIRE(constraintParam != NULL);
}


bool 
NestedConstraintConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!ConstraintElement::Equals(rhs))
    {
        return false;
    }

    const NestedConstraintConstraintElement& other =
        static_cast<const NestedConstraintConstraintElement&> (rhs);

    if (constraint != NULL && other.constraint == NULL ||
        constraint == NULL && other.constraint != NULL)
    {
        return false;
    }

    if (constraint != NULL && other.constraint != NULL)
    {
        if (!constraint->Equals(*other.constraint))
        {
            return false;
        }
    }

    return true;
}


void
NestedConstraintConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitNestedConstraintConstraintElementBegin(this);

    visitor->VisitConstraintBegin(constraint);

    visitor->VisitConstraintEnd(constraint);

    visitor->VisitNestedConstraintConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SizeConstraintElement implementation.
//

SizeConstraintElement::SizeConstraintElement(Constraint* constraintParam)
:   NestedConstraintConstraintElement(constraintParam)
{
    REQUIRE(constraintParam != NULL);
}


bool 
SizeConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!NestedConstraintConstraintElement::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
SizeConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitSizeConstraintElementBegin(this);

    constraint->Accept(visitor);

    visitor->VisitSizeConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  FromConstraintElement implementation.
//

FromConstraintElement::FromConstraintElement(Constraint* constraintParam)
:   NestedConstraintConstraintElement(constraintParam)
{
    REQUIRE(constraintParam != NULL);
}


bool 
FromConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!NestedConstraintConstraintElement::Equals(rhs))
    {
        return false;
    }

    return true;
}


void
FromConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitFromConstraintElementBegin(this);

    visitor->VisitFromConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  WithComponentConstraintElement implementation.
//

WithComponentConstraintElement::WithComponentConstraintElement(
                                                const string& nameParam, 
                                                Constraint* constraintParam, 
                                                int presenceParam)
:   NestedConstraintConstraintElement(constraintParam),
    name(nameParam),
    presence(presenceParam)
{
    REQUIRE(constraintParam != NULL);
}


bool 
WithComponentConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!NestedConstraintConstraintElement::Equals(rhs))
    {
        return false;
    }

    const WithComponentConstraintElement& other =
        static_cast<const WithComponentConstraintElement&> (rhs);

    if (name != other.name)
    {
        return false;
    }

    if (presence != other.presence)
    {
        return false;
    }

    return true;
}


void
WithComponentConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitWithComponentConstraintElementBegin(this);

    visitor->VisitWithComponentConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  InnerTypeConstraintElement implementation.
//

InnerTypeConstraintElement::InnerTypeConstraintElement(
                        ConstraintElementList* constraintElementListParam, 
                        bool partialParam)
:   ElementListConstraintElement(constraintElementListParam),
    partial(partialParam)
{
    REQUIRE(constraintElementListParam != NULL);
}


bool 
InnerTypeConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!ElementListConstraintElement::Equals(rhs))
    {
        return false;
    }

    const InnerTypeConstraintElement& other =
        static_cast<const InnerTypeConstraintElement&> (rhs);

    if (partial != other.partial)
    {
        return false;
    }

    return true;
}


void
InnerTypeConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitInnerTypeConstraintElementBegin(this);

    visitor->VisitInnerTypeConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  UserDefinedConstraintElement implementation.
//

UserDefinedConstraintElement::UserDefinedConstraintElement(
                                            TypeList* typeListParam)
:   typeList(typeListParam)
{
    REQUIRE(typeListParam != NULL);
}


bool 
UserDefinedConstraintElement::Equals(const ConstraintElement& rhs) const
{
    bool not_implemented = false;
    ASSERT(not_implemented);

    return false;
}


void
UserDefinedConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitUserDefinedConstraintElementBegin(this);

    visitor->VisitUserDefinedConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  SubTypeConstraintElement implementation.
//

SubTypeConstraintElement::SubTypeConstraintElement(Type* subtypeParam)
:   subtype(subtypeParam)
{
    REQUIRE(subtypeParam != NULL);
}


bool 
SubTypeConstraintElement::Equals(const ConstraintElement& rhs) const
{
    if (!ConstraintElement::Equals(rhs))
    {
        return false;
    }

    const SubTypeConstraintElement& other =
        static_cast<const SubTypeConstraintElement&> (rhs);

    if (subtype != NULL && other.subtype == NULL ||
        subtype == NULL && other.subtype != NULL)
    {
        return false;
    }

    if (subtype != NULL && other.subtype != NULL)
    {
        if (!subtype->Equals(*other.subtype))
        {
            return false;
        }
    }

    return true;
}


void
SubTypeConstraintElement::Accept(Visitor* visitor)
{
    visitor->VisitSubTypeConstraintElementBegin(this);

    visitor->VisitSubTypeConstraintElementEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  ImportedModule implementation.
//

ImportedModule::ImportedModule(
                            const string& nameParam, 
                            TypeList* importedSymbolListParam)
:   name(nameParam),
    importedSymbolList(importedSymbolListParam)
{
}


void
ImportedModule::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    visitor->VisitImportedModule(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  Module implementation.
//

Module::Module(
            const string& nameParam,
            list<string*>* definitiveIdParam, 
            Tag::TagMode defaultTagModeParam)
:   name(nameParam),
    definitiveId(definitiveIdParam),
    specifiedName(""),
    specifiedNamespace(""),
    defaultTagMode(defaultTagModeParam),
    exportAll(false),
    asn1SrcFileName("")
{
    exportedSymbolList  = new TypeList();
    importedModuleList  = new ImportedModuleList();
    typeDefList         = new TypeDefList();
    valueDefList        = new ValueDefList();
}

void
Module::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    visitor->VisitModuleBegin(this);

    visitor->PushIterContext();

    visitor->SetIterSize(importedModuleList->size());

    for (ImportedModuleList::iterator imIter = importedModuleList->begin();
         imIter != importedModuleList->end();
         imIter++)
    {
        if (imIter == importedModuleList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++imIter == importedModuleList->end())
        {
            --imIter;
            visitor->SetIterEnd();
        }
        else
        {
            --imIter;
            visitor->SetIterMiddle();
        }
        
        (*imIter)->Accept(visitor);
    }

    visitor->PopIterContext();

    visitor->PushIterContext();

    visitor->SetIterSize(typeDefList->size());

    for (TypeDefList::iterator tdIter = typeDefList->begin();
         tdIter != typeDefList->end();
         tdIter++)
    {
        if (tdIter == typeDefList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++tdIter == typeDefList->end())
        {
            --tdIter;
            visitor->SetIterEnd();
        }
        else
        {
            --tdIter;
            visitor->SetIterMiddle();
        }

        if (!((*tdIter)->IsRecursive()) ||
            ((*tdIter)->IsRecursive() && visitor->VisitRecursive()))
        {
            (*tdIter)->Accept(visitor);
        }
    }

    visitor->PopIterContext();

    visitor->PushIterContext();

    visitor->SetIterSize(valueDefList->size());
    
    for (ValueDefList::iterator vdIter = valueDefList->begin();
         vdIter != valueDefList->end();
         vdIter++)
    {
        if (vdIter == valueDefList->begin())
        {
            visitor->SetIterBegin();
        }
        else if (++vdIter == valueDefList->end())
        {
            --vdIter;
            visitor->SetIterEnd();
        }
        else
        {
            --vdIter;
            visitor->SetIterMiddle();
        }

        if (!((*vdIter)->IsRecursive()) ||
            ((*vdIter)->IsRecursive() && visitor->VisitRecursive()))
        {
            (*vdIter)->Accept(visitor);
        }
    }

    visitor->PopIterContext();

    visitor->VisitModuleEnd(this);
}


string
Module::ToString() const
{
    ostrstream ostrs;

    Print(ostrs);

    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    return result;
}


void
Module::Print(ostream& os) const
{
    PrintVisitor printVisitor(os);

    (const_cast<Module*> (this))->Accept(&printVisitor);
}


void
Module::PrintFlattened(ostream& os) const
{
    PrintVisitor printVisitor(os);

    printVisitor.SetVisitFlattened();

    (const_cast<Module*> (this))->Accept(&printVisitor);
}



void 
Module::MakeTypeDefTable()
{
    for (TypeDefList::iterator iter = typeDefList->begin();
         iter != typeDefList->end();
         iter++)
    {
        TypeDef* typeDef = *iter;

        // Check for duplicate type definitions.

        if (HasTypeDef(typeDef->GetDefinedName()))
        {
            TypeDef* typeDefOther = 
                RetrieveTypeDef(typeDef->GetDefinedName());

            PrintErrLoc(asn1SrcFileName, typeDef->GetType()->GetLineNumber());
            cerr << "ERROR - type \"" << typeDef->GetDefinedName() << "\" ";
            cerr << "already defined on line ";
            cerr << typeDefOther->GetType()->GetLineNumber();
            cerr << "." << endl;

            cerr << "AsnCC Status : ERROR - conflicting type definition names,";
            cerr << "cannot proceed." << endl;

            exit(EXIT_FAILURE);
        }
        else
        {
            typeDefTable.
                insert(
                    TypeDefTable::
                        value_type(
                            typeDef->GetDefinedName(), 
                            typeDef));
        }
    }
}


void 
Module::MakeValueDefTable()
{
    for (ValueDefList::iterator iter = valueDefList->begin();
         iter != valueDefList->end();
         iter++)
    {
        ValueDef* valueDef = *iter;

        // Check for duplicate value definitions.

        if (HasValueDef(valueDef->GetDefinedName()))
        {
            ValueDef* valueDefOther = 
                RetrieveValueDef(valueDef->GetDefinedName());

            PrintErrLoc(asn1SrcFileName, valueDef->GetValue()->GetLineNumber());
            cerr << "ERROR - value \"" << valueDef->GetDefinedName() << "\" ";
            cerr << "already defined on line ";
            cerr << valueDefOther->GetValue()->GetLineNumber();
            cerr << "." << endl;

            cerr << "AsnCC Status : ERROR - conflicting value definition ";
            cerr << "names, cannot proceed." << endl;

            exit(EXIT_FAILURE);
        }
        else
        {
            valueDefTable.
                insert(
                    ValueDefTable::
                        value_type(
                            valueDef->GetDefinedName(),
                            valueDef));
        }
    }
}


void 
Module::MakeExportedTypeDefTable()
{
    if (exportAll)
    {
        for (TypeDefList::iterator iter = typeDefList->begin();
             iter != typeDefList->end();
             iter++)
        {
            exportedTypeDefTable.
                insert(
                    TypeDefTable::
                        value_type(
                            (*iter)->GetDefinedName(),
                            *iter));
        }
    }
    else
    {
        for (TypeList::iterator iter = exportedSymbolList->begin();
             iter != exportedSymbolList->end();
             iter++)
        {   
            if ((*iter)->GetType() == TYPE_IMPORTED)
            {
                ImportedType* exportedSymbol = 
                    static_cast<ImportedType*> (*iter);

                string exportedSymbolName = exportedSymbol->GetName();

                if (HasTypeDef(exportedSymbolName))
                {
                    TypeDef* exportedTypeDef = 
                        RetrieveTypeDef(exportedSymbolName);

                    exportedTypeDefTable.
                        insert(
                            TypeDefTable::
                                value_type(
                                    exportedSymbolName,
                                    exportedTypeDef));
                }
            }
            else
            {
                // TODO: add compiler error. Inconsistent with grammar.
            }
        }
        
    }
}


void 
Module::MakeExportedValueDefTable()
{
    if (exportAll)
    {
        for (ValueDefList::iterator iter = valueDefList->begin();
             iter != valueDefList->end();
             iter++)
        {
            exportedValueDefTable.
                insert(
                    ValueDefTable::
                        value_type(
                            (*iter)->GetDefinedName(),
                            *iter));
        }
    }
    else
    {
        for (TypeList::iterator iter = exportedSymbolList->begin();
             iter != exportedSymbolList->end();
             iter++)
        {   
            if ((*iter)->GetType() == TYPE_IMPORTED)
            {
                ImportedType* exportedSymbol = 
                    static_cast<ImportedType*> (*iter);

                string exportedSymbolName = exportedSymbol->GetName();

                if (HasValueDef(exportedSymbolName))
                {
                    ValueDef* exportedValueDef = 
                        RetrieveValueDef(exportedSymbolName);

                    exportedValueDefTable.
                        insert(
                            ValueDefTable::
                                value_type(
                                    exportedSymbolName,
                                    exportedValueDef));
                }
            }
            else
            {
                // TODO: add compiler error. Inconsistent with grammar.
            }
        }
    }
}


void 
Module::MakeImportedSymbolTable()
{
    for (ImportedModuleList::iterator imIter = importedModuleList->begin();
         imIter != importedModuleList->end();
         imIter++)
    {
        string importedModuleName =  (*imIter)->GetName();
        
        ImportedModule* importedModule = *imIter;

        TypeList* importedSymbolList = 
            importedModule->
                GetImportedSymbolList();

        for (TypeList::iterator iter = importedSymbolList->begin();
             iter != importedSymbolList->end();
             iter++)
        {   
            if ((*iter)->GetType() == TYPE_IMPORTED)
            {
                ImportedType* importedSymbol = 
                    static_cast<ImportedType*> (*iter);

                string importedSymbolName = importedSymbol->GetName();

                if (HasImportedSymbol(importedSymbolName))
                {
                    PrintErrLoc(
                        asn1SrcFileName, 
                        importedSymbol->GetLineNumber());
                    cerr << "WARNING - symbol \"";
                    cerr << importedSymbol->GetName();
                    cerr << "\" is imported more than once." << endl;
                }
                else
                {
                    importedSymbolTable.
                        insert(
                            ImportedSymbolTable::
                                value_type(
                                    importedSymbolName,
                                    importedModuleName));
                }
            }
            else
            {
                // TODO: add compiler error. Inconsistent with grammar.
            }
        }
    }
}


void
Module::Link(AsnCC& asnCC)
{
    LinkVisitor linkVisitor(asnCC, this);

    Accept(&linkVisitor);
}


void
Module::NormalizeComponentsOf(AsnCC& asnCC)
{
    ComponentsOfVisitor componentsOfVisitor(asnCC, this);

    Accept(&componentsOfVisitor);
}


void
Module::MarkRecursive(AsnCC& asnCC)
{
    RecursiveVisitor recursiveVisitor(asnCC, this);

    Accept(&recursiveVisitor);
}


void
Module::CheckSemantic(AsnCC& asnCC)
{
    CheckSemanticVisitor checkSemanticVisitor(asnCC, this);

    Accept(&checkSemanticVisitor);
}


void
Module::Normalize(AsnCC& asnCC)
{
    NormalizeVisitor normalizeVisitor(asnCC, this);

    Accept(&normalizeVisitor);
}


void
Module::Evaluate(AsnCC& asnCC)
{
    EvaluateVisitor evaluateVisitor(asnCC, this);

    Accept(&evaluateVisitor);
}


void
Module::Merge(AsnCC& asnCC)
{
    MergeVisitor mergeVisitor(asnCC, this);

    Accept(&mergeVisitor);
}


void
Module::GenerateCpp(AsnCC& asnCC)
{
    GenerateCppVisitor generateCppVisitor(asnCC, this);

    Accept(&generateCppVisitor);
}


void
Module::GenerateCppXmlDoc(AsnCC& asnCC)
{
    GenerateCppXmlDocVisitor generateCppXmlDocVisitor(asnCC, this);

    Accept(&generateCppXmlDocVisitor);
}


void
Module::GenerateC(AsnCC& asnCC)
{
    GenerateCVisitor generateCVisitor(asnCC, this);

    Accept(&generateCVisitor);
}


void
Module::GenerateCXmlDoc(AsnCC& asnCC)
{
    GenerateCXmlDocVisitor generateCXmlDocVisitor(asnCC, this);

    Accept(&generateCXmlDocVisitor);
}


////////////////////////////////////////////////////////////////////////////////
//
// Module ostream operator<< implementation.
//

ostream& operator<<(ostream& os, const Module& module)
{
    module.Print(os);
    return os;
}
















































