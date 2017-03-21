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
//  ID: $Id: asncc_check_semantic_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_check_semantic_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  CheckSemanticVisitor implementation.
//

// TODO: to be completed.

/*

   The following errors are checked:
   ---------------------------------

   - Components of CHOICE and SET types must have distinct tags.

   - CHOICE, ANY, and ANY DEFINED BY types cannot be implicitly tagged.

   - Type and value names within the same scope must be unique.

   - Field names in a SET, SEQUENCE or CHOICE must be distinct. If a CHOICE
     with no field name is embedded in a SET, SEQUENCE or CHOICE, then the
     embedded CHOICE's field names must be distinct from its parents to avoid
     ambiguity in value notation.

   - An APPLICATION tag can only be used once per module.

   - Each value in a named bit (BIT STRINGs) or named number (INTEGERs and
     ENUMERATEDs) list must be different.

   - Each identifier in a named bit or named number list must be different.

   - The tags on a series of one or more consecutive OPTIONAL or DEFAULT 
     SEQUENCE elements and the following element must be distinct.


   The following error checks are done by the linker:
   --------------------------------------------------

   - A COMPONENTS OF type in a SET must reference a SET.

   - A COMPONENTS OF type in a SEQUENCE must reference a SEQUENCE.
   
   - SELECTION types must reference a field of a CHOICE type.

   - Gives a warning if an ANY DEFINED BY type appears in a SET or if and ANY
     DEFINED BY appears in a SEQUENCE before its identifier (these cases make
     decoding difficult).


   The following error checks are not done yet:
   --------------------------------------------

   - Each identifier in a BIT STRING value must from that BIT STRING's named
     bit list. 

   - SET or SEQUENCE values can be empty {} only if the SET or SEQUENCE type
     was defined as empty or all of its elements are marked as OPTIONAL or
     DEFAULT.

*/


////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////

void 
CheckSemanticVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{

}


void 
CheckSemanticVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{

}


void 
CheckSemanticVisitor::VisitTypeBegin(Type* type)
{


}


void 
CheckSemanticVisitor::VisitTypeEnd(Type* type)
{


}


void 
CheckSemanticVisitor::VisitDefinedType(DefinedType* definedType)
{

}


void 
CheckSemanticVisitor::VisitSetTypeBegin(SetType* setType)
{
    TypeList* typeList = setType->GetFlattenedTypeList();

    // [1]  Build a list of all possible tags. List can contain special tag any
    //      and duplicate tags.

    TagList tagList;

    for (TypeList::iterator iter = typeList->begin();
         iter != typeList->end();
         iter++)
    {
        TagList* adjustedTagList = (*iter)->GetAdjustedTagList();

        if (adjustedTagList->size() == 0)
        {
            Type* baseType = (*iter)->GetBaseType();

            if (baseType->GetType() == TYPE_CHOICE)
            {
                ChoiceType* choiceType = static_cast<ChoiceType*> (baseType);

                TagList* possibleTagList = choiceType->GetPossibleTagList();
                
                tagList.insert(
                            tagList.end(), 
                            possibleTagList->begin(),
                            possibleTagList->end());
            }
            else if (baseType->GetType() == TYPE_ANY || 
                     baseType->GetType() == TYPE_ANY_DEFINED_BY)
            {
                Tag* anyTag = new Tag();
                anyTag->SetAny();

                tagList.push_back(anyTag);
            }
        }
        else
        {
            tagList.push_back(adjustedTagList->front());
        }
    }

    // [2]  Check if list of all possible tags contains special tag any. Copy
    //      list to new list without special tag any.

    TagList tagListNoAny;

    bool anyErrorPrinted = false;

    for (TagList::iterator tagIter = tagList.begin();
         tagIter != tagList.end();
         tagIter++)
    {
        if ((*tagIter)->IsAny())
        {
            if (!anyErrorPrinted)
            {
                anyErrorPrinted = true;

                PrintErrLoc(
                    setType->GetModule()->GetAsn1SrcFileName(),
                    setType->GetLineNumber());
                cerr << "ERROR - type SET contains directly or indirectly ";
                cerr << "(e.g. through type CHOICE) tag of type ANY.";
                cerr << endl;

                setType->GetModule()->AddError(Module::MODULE_SEMANTIC_ERROR);
            }
        }
        else
        {
            tagListNoAny.push_back(*tagIter);
        }
    }

    // [3]  Check list of all possible tags (with special tag any) for 
    //      conflict(s) (i.e. duplicate tags).

    set<long> tagSet;

    for (TagList::iterator tagIter2 = tagListNoAny.begin();
         tagIter2 != tagListNoAny.end();
         tagIter2++)
    {
        if (tagSet.find((*tagIter2)->GetNumber()) != tagSet.end())
        {
            PrintErrLoc(
                setType->GetModule()->GetAsn1SrcFileName(),
                setType->GetLineNumber());
            cerr << "ERROR - tag conflict among components of type SET. Tag ";
            cerr << "number \"";
            cerr << (*tagIter2)->GetNumber();
            cerr << "\".";
            cerr << endl;

            setType->GetModule()->AddError(Module::MODULE_SEMANTIC_ERROR);
        }
        else
        {
            tagSet.insert((*tagIter2)->GetNumber());
        }
    }
}


void 
CheckSemanticVisitor::VisitSetTypeEnd(SetType* setType)
{


}



////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
