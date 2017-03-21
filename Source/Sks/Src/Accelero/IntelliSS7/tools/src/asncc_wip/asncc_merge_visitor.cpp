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
//  ID: $Id: asncc_merge_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_merge_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  MergeVisitor implementation.
//


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

void 
MergeVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{
    //  Nothing to do.
}


void 
MergeVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{
    ModuleList& moduleList = asnCC.GetModuleList();    

    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* otherModule = *iter;

        if (otherModule->GetName() == module->GetName())
        {
            continue;   //  Nothing to do.
        }
        else
        {
            string definedName = typeDef->GetDefinedName();

            if (otherModule->HasTypeDef(definedName))
            {
                TypeDef* 
                    otherTypeDef = 
                        otherModule->
                            RetrieveTypeDef(
                                definedName);

                if (typeDef->Equals(*otherTypeDef))
                {
                    typeDef->SetCommon();
                    otherTypeDef->SetCommon();

                    typeDef->GetType()->SetCommon();
                    otherTypeDef->GetType()->SetCommon();

                    if (bCppMergeWithExtensionsG)
                    {
                        // Mark recursively as common all types on which both
                        // deep equal types are dependent on. Mark also as 
                        // common the associated type definitions. 

                        typeDef->GetType()->SetCommonRecursively();

                        otherTypeDef->GetType()->SetCommonRecursively();
                    }
                }
                else
                {
                    //  Look up for an already existing and incompatible
                    //  common type among all modules.

                    bool stop = false;

                    for (ModuleList::iterator iter2 = moduleList.begin();
                         iter2 != moduleList.end();
                         iter2++)
                    {
                        Module* otherModule2 = *iter2;

                        if (otherModule2->GetName() == module->GetName())
                        {
                            continue;   //  Nothing to do.
                        }
                        else if (otherModule2 == otherModule)
                        {
                            continue;   //  Nothing to do.
                        }
                        else
                        {
                            if (otherModule2->HasTypeDef(definedName))
                            {
                                TypeDef*
                                    otherTypeDef2 = 
                                        otherModule2->
                                            RetrieveTypeDef(
                                                definedName);

                                if (otherTypeDef2->IsCommon())
                                {
                                    stop = true;
                                }
                            }
                            else
                            {
                                //  Nothing to do.
                            }
                        }
                    }

                    if (stop)
                    {
                        //  Do not try with other modules to avoid multiple
                        //  common types.
                        
                        break;
                    }
                }
            }
            else
            {
                //  Nothing to do.
            }
        }
    }
}



////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
