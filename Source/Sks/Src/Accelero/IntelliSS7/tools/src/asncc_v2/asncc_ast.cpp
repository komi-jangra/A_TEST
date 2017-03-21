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
// LOG: Revision 1.1.1.1  2007/03/08 15:14:39  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:13  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:52:58  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/06/17 21:51:43  hdivoux
// LOG: Added processing for default ASN.1 values.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:34  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_ast.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"

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
    localRefCount(0),
    importRefCount(0)
{
    parameterList           = new list<string*>();
    constraintElementList   = new ConstraintElementList();
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
    name(""),
    hasDefaultValue(false),
    hasDefaultValueWithCode(false),
    defaultValue(NULL),
    defaultValueWithCode(""),
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
        }
        }
    }

    ENSURE(result != NULL);

    return result;
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
    extensions(new TypeList()),
    extendable(false)
{
}


ChoiceType::ChoiceType(TypeList* typeListParam, bool extendableParam)
:   typeList(typeListParam), 
    extensions(new TypeList()),
    extendable(extendableParam)
{
}


ChoiceType::ChoiceType(
                TypeList* typeListParam, 
                bool extendableParam, 
                TypeList* extensionsParam)
:   typeList(typeListParam), 
    extensions(extensionsParam),
    extendable(extendableParam)
{
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
//  EnumeratedType implementation.
//

EnumeratedType::EnumeratedType(
                    NamedNumberList* namedNumberListParam,
                    bool extendableParam,
                    NamedNumberList* extensionsParam)
:   namedNumberList(namedNumberListParam),
    extensions(extensionsParam),
    extendable(extendableParam)
{
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


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectIdentifierType implementation.
//

ObjectIdentifierType::ObjectIdentifierType()
{
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
//  BaseStringType implementation.
//

BaseStringType::BaseStringType()
{
}


Tag* 
BaseStringType::GetUniversalTag() const
{
    REQUIRE(HasUniversalTag());

    Tag* result = new Tag(
                        Tag::CLASS_UNIVERSAL,
                        Tag::UNIVERSAL_BASE_STRING,
                        Tag::MODE_EXPLICIT);

    result->SetTagType(Tag::TYPE_PRIMITIVE);

    return result;
}


void
BaseStringType::Accept(Visitor* visitor)
{
    REQUIRE(visitor != NULL);

    Type::Accept(visitor);

    visitor->VisitTypeBegin(this);

    visitor->VisitBaseStringType(this);

    visitor->VisitTypeEnd(this);
}


////////////////////////////////////////////////////////////////////////////////
//
//  RealType implementation.
//

RealType::RealType()
{
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
    extensions(extensionsParam),
    extendable(extendableParam)
{
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


////////////////////////////////////////////////////////////////////////////////
//
//  SelectionType implementation.
//

SelectionType::SelectionType(const string& nameParam, Type* typeParam)
:   name(nameParam),
    type(typeParam)
{
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


////////////////////////////////////////////////////////////////////////////////
//
//  AnyType implementation.
//

AnyType::AnyType()
{
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
















































