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
//  ID: $Id: asncc_components_of_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_components_of_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  (Normalize) ComponentsOfVisitor implementation.
//


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////


void 
ComponentsOfVisitor::VisitTypeBegin(Type* type)
{
    bool recursiveSave = recursive;

    if (!(type->IsComponentsOf()))
    {
        typeStack.push_front(type); 
    }
    else
    {
        ASSERT(!(typeStack.empty()));   // From grammar.

        if (type->GetType() != TYPE_DEFINED)
        {
            PrintErrLoc(module->GetAsn1SrcFileName(), type->GetLineNumber());
            cerr << "ERROR - COMPONENTS OF Type must be a reference.";
            cerr << endl;

            module->AddError(Module::MODULE_COMPONENTS_OF_ERROR);
        }
        else if (type->GetBaseType()->GetType() != TYPE_SET &&
                 type->GetBaseType()->GetType() != TYPE_SEQUENCE &&
                 type->GetBaseType()->GetType() != TYPE_CHOICE)
        {
            PrintErrLoc(module->GetAsn1SrcFileName(), type->GetLineNumber());
            cerr << "ERROR - COMPONENTS OF Type must reference a SET, a ";
            cerr << "SEQUENCE or a CHOICE.";
            cerr << endl;

            module->AddError(Module::MODULE_COMPONENTS_OF_ERROR);
        }
        else if(typeStack.front()->GetType() != TYPE_SET &&
                typeStack.front()->GetType() != TYPE_SEQUENCE &&
                typeStack.front()->GetType() != TYPE_CHOICE)
        {
            PrintErrLoc(module->GetAsn1SrcFileName(), type->GetLineNumber());
            cerr << "ERROR - COMPONENTS OF Type must be used only within a ";
            cerr << "SET, a SEQUENCE or a CHOICE.";
            cerr << endl;

            module->AddError(Module::MODULE_COMPONENTS_OF_ERROR);        
        }
        else if (type->GetBaseType()->GetType() == TYPE_SET &&
                 typeStack.front()->GetType() != TYPE_SET)
        {
            PrintErrLoc(module->GetAsn1SrcFileName(), type->GetLineNumber());
            cerr << "ERROR - a COMPONENTS OF Type in a SET must reference a ";
            cerr << "SET.";
            cerr << endl;

            module->AddError(Module::MODULE_COMPONENTS_OF_ERROR);
        }
        else if (type->GetBaseType()->GetType() == TYPE_SEQUENCE &&
                 typeStack.front()->GetType() != TYPE_SEQUENCE)
        {
            PrintErrLoc(module->GetAsn1SrcFileName(), type->GetLineNumber());
            cerr << "ERROR - a COMPONENTS OF Type in a SEQUENCE must reference";
            cerr << " a SEQUENCE.";
            cerr << endl;

            module->AddError(Module::MODULE_COMPONENTS_OF_ERROR);
        }
        else if (type->GetBaseType()->GetType() == TYPE_CHOICE &&
                 typeStack.front()->GetType() != TYPE_CHOICE)
        {
            PrintErrLoc(module->GetAsn1SrcFileName(), type->GetLineNumber());
            cerr << "ERROR - a COMPONENTS OF Type in a CHOICE must reference";
            cerr << " a CHOICE.";
            cerr << endl;

            module->AddError(Module::MODULE_COMPONENTS_OF_ERROR);
        }
        else
        {
            DefinedType* definedType = static_cast<DefinedType*> (type);

            definedTypeStack.push_front(definedType);

            Type* baseType = type->GetBaseType();

            if (baseType->GetType() == TYPE_SET)
            {
                SetType* setType = static_cast<SetType*> (baseType);

                TypeList* typeList = setType->GetTypeList();

                for (TypeList::iterator iter = typeList->begin();
                     iter != typeList->end();
                     iter++)
                {
                    if ((*iter)->IsComponentsOf())
                    {
                        // Recursive call to flatten recursive COMPONENTS OF
                        // constructs.

                        recursive = true;

                        Type* baseComponentsOfType = (*iter)->GetBaseType();

                        baseComponentsOfType->Accept(this);

                        recursive = false;

                        for (TypeList::iterator cptIter = 
                                componentsOfList.begin();
                             cptIter != componentsOfList.end();
                             cptIter++)
                        {
                            definedType->
                                AddComponentToComponentsOfList(*cptIter);
                        }

                    }
                    else
                    {
                        Type* component = (*iter)->Clone();
                        component->SetFromComponentsOf();
                        component->SetComponentsOfOrigin(definedType);

                        if (recursive)
                        {
                            componentsOfList.push_back(component);
                        }
                        else
                        {
                            definedType->
                                AddComponentToComponentsOfList(component);
                        }
                    }
                }
            }
            else if (baseType->GetType() == TYPE_SEQUENCE)
            {
                SequenceType* sequenceType = 
                    static_cast<SequenceType*> (baseType);

                TypeList* typeList = sequenceType->GetTypeList();

                for (TypeList::iterator iter = typeList->begin();
                     iter != typeList->end();
                     iter++)
                {
                    if ((*iter)->IsComponentsOf())
                    {
                        // Recursive call to flatten recursive COMPONENTS OF
                        // constructs.

                        recursive = true;

                        Type* baseComponentsOfType = (*iter)->GetBaseType();

                        baseComponentsOfType->Accept(this);

                        recursive = false;

                        for (TypeList::iterator cptIter = 
                                componentsOfList.begin();
                             cptIter != componentsOfList.end();
                             cptIter++)
                        {
                            definedType->
                                AddComponentToComponentsOfList(*cptIter);
                        }

                        componentsOfList.clear();
                    }
                    else
                    {
                        Type* component = (*iter)->Clone();
                        component->SetFromComponentsOf();
                        component->SetComponentsOfOrigin(definedType);

                        if (recursive)
                        {
                            componentsOfList.push_back(component);
                        }
                        else
                        {
                            definedType->
                                AddComponentToComponentsOfList(component);
                        }
                    }
                }
            }
            else if (baseType->GetType() == TYPE_CHOICE)
            {
                ChoiceType* choiceType = 
                    static_cast<ChoiceType*> (baseType);

                TypeList* typeList = choiceType->GetTypeList();

                for (TypeList::iterator iter = typeList->begin();
                     iter != typeList->end();
                     iter++)
                {
                    if ((*iter)->IsComponentsOf())
                    {
                        // Recursive call to flatten recursive COMPONENTS OF
                        // constructs.

                        recursive = true;

                        Type* baseComponentsOfType = (*iter)->GetBaseType();

                        baseComponentsOfType->Accept(this);

                        recursive = false;

                        for (TypeList::iterator cptIter = 
                                componentsOfList.begin();
                             cptIter != componentsOfList.end();
                             cptIter++)
                        {
                            definedType->
                                AddComponentToComponentsOfList(*cptIter);
                        }

                        componentsOfList.clear();
                    }
                    else
                    {
                        Type* component = (*iter)->Clone();
                        component->SetFromComponentsOf();
                        component->SetComponentsOfOrigin(definedType);

                        if (recursive)
                        {
                            componentsOfList.push_back(component);
                        }
                        else
                        {
                            definedType->
                                AddComponentToComponentsOfList(component);
                        }
                    }
                }
            }
            else
            {
                bool must_not_be_reached = false;
                ASSERT(must_not_be_reached);
            }

            definedTypeStack.pop_front();
        }
    }

    recursive = recursiveSave;
}


void 
ComponentsOfVisitor::VisitTypeEnd(Type* type)
{
    if (!(type->IsComponentsOf()))
    {
        typeStack.pop_front();  
    }
}


void 
ComponentsOfVisitor::VisitSequenceTypeBegin(SequenceType* sequenceType)
{
    if (recursive)
    {
        TypeList* typeList = sequenceType->GetTypeList();

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            if ((*iter)->IsComponentsOf())
            {
                // Nothing to do (already processed recursively).
            }
            else
            {
                Type* component = (*iter)->Clone();
                component->SetFromComponentsOf();

                ASSERT(!(definedTypeStack.empty()));    // From grammar.

                component->SetComponentsOfOrigin(definedTypeStack.front());

                componentsOfList.push_back(component);
            }
        }
    }
}


void 
ComponentsOfVisitor::VisitSequenceTypeEnd(SequenceType* sequenceType)
{

}


void 
ComponentsOfVisitor::VisitSetTypeBegin(SetType* setType)
{
    if (recursive)
    {
        TypeList* typeList = setType->GetTypeList();

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            if ((*iter)->IsComponentsOf())
            {
                // Nothing to do (already processed recursively).
            }
            else
            {
                Type* component = (*iter)->Clone();
                component->SetFromComponentsOf();

                ASSERT(!(definedTypeStack.empty()));    // From grammar.

                component->SetComponentsOfOrigin(definedTypeStack.front());

                componentsOfList.push_back(component);
            }
        }
    }
}


void 
ComponentsOfVisitor::VisitSetTypeEnd(SetType* setType)
{

}


void 
ComponentsOfVisitor::VisitChoiceTypeBegin(ChoiceType* choiceType)
{
    if (recursive)
    {
        TypeList* typeList = choiceType->GetTypeList();

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            if ((*iter)->IsComponentsOf())
            {
                // Nothing to do (already processed recursively).
            }
            else
            {
                Type* component = (*iter)->Clone();
                component->SetFromComponentsOf();

                ASSERT(!(definedTypeStack.empty()));    // From grammar.

                component->SetComponentsOfOrigin(definedTypeStack.front());

                componentsOfList.push_back(component);
            }
        }
    }
}


void 
ComponentsOfVisitor::VisitChoiceTypeEnd(ChoiceType* choiceType)
{

}


////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
