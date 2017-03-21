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
//  ID: $Id: asncc_link_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_link_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  LinkVisitor implementation.
//

// TODO: Selection Type should be linked too.


void
LinkVisitor::VisitDefinedType(DefinedType* definedType)
{
    REQUIRE(definedType != NULL);

    string definedName = definedType->GetName();

    //
    //  [1] Try to link as local symbol.
    //

    if (module->HasTypeDef(definedName))
    {
        TypeDef* typeDef = module->RetrieveTypeDef(definedName);

        Type* type = typeDef->GetType();

        definedType->SetLink(type, typeDef);

        typeDef->IncLocalRefCount();

        return;
    }


    //
    //  [2] Try to link as useful type symbol.
    //

    if (asnCC.HasUsefulModule())
    {
        Module& usefulModule = asnCC.GetUsefulModule();

        if (usefulModule.HasTypeDef(definedName))
        {
            TypeDef* typeDef = usefulModule.RetrieveTypeDef(definedName);

            Type* type = typeDef->GetType();

            definedType->SetLink(type, typeDef);

            typeDef->IncImportRefCount();

            return;
        }
        else
        {
            // Not useful type => nothing to do.
        }
    }


    //
    //  [3] Try to link as imported symbol.
    //

    if (module->HasImportedSymbol(definedName))
    {
        string fromModuleName = 
                    module->
                        RetrieveImportedFromModuleName(definedName);

        if (asnCC.HasModule(fromModuleName))
        {
            Module* fromModule = asnCC.RetrieveModule(fromModuleName);

            if (fromModule->HasExportedTypeDef(definedName))
            {
                TypeDef* typeDef = 
                    fromModule->
                        RetrieveExportedTypeDef(definedName);

                Type* type = typeDef->GetType();

                definedType->SetLink(type, typeDef);

                typeDef->IncImportRefCount();
            }
            else if (fromModule->HasTypeDef(definedName))
            {
                PrintErrLoc(
                    module->GetAsn1SrcFileName(), 
                    definedType->GetLineNumber());
                cerr << "WARNING - type definition \"";
                cerr << definedName;
                cerr << "\" imported but not exported by module";
                cerr << " \"";
                cerr << fromModule->GetName();
                cerr << "\". Link anyway.";
                cerr << endl;

                TypeDef* typeDef = fromModule->RetrieveTypeDef(definedName);

                Type* type = typeDef->GetType();

                definedType->SetLink(type, typeDef);

                typeDef->IncImportRefCount();
            }
            else
            {
                PrintErrLoc(
                    module->GetAsn1SrcFileName(),
                    definedType->GetLineNumber());
                cerr << "ERROR - type definition \"";
                cerr << definedName;
                cerr << "\" imported but not defined by module";
                cerr << " \"";
                cerr << fromModule->GetName();
                cerr << "\".";
                cerr << endl;

                module->AddError(Module::MODULE_LINK_ERROR);
            }
        }
        else
        {
            PrintErrLoc(
                module->GetAsn1SrcFileName(),
                definedType->GetLineNumber());
            cerr << "ERROR - type definition \"";
            cerr << definedName;
            cerr << "\" ";
            cerr << "imported from module \"";
            cerr << fromModuleName;
            cerr << "\" but no such module defined.";
            cerr << endl;

            module->AddError(Module::MODULE_LINK_ERROR);
        }
    }
    else
    {
        PrintErrLoc(
            module->GetAsn1SrcFileName(),
            definedType->GetLineNumber());
        cerr << "ERROR - type definition \"";
        cerr << definedName;
        cerr << "\" ";
        cerr << "used but not local and not imported.";
        cerr << endl;

        module->AddError(Module::MODULE_LINK_ERROR);
    }
}


////////////////////////////////////////////////////////////////////////////////


void 
LinkVisitor::VisitDefinedValue(DefinedValue* definedValue)
{
    REQUIRE(definedValue != NULL);

    string definedName = definedValue->GetName();

    //
    //  [1] Try to link as local symbol.
    //

    if (module->HasValueDef(definedName))
    {
        ValueDef* valueDef = module->RetrieveValueDef(definedName);

        Value* value = valueDef->GetValue();

        definedValue->SetLink(value, valueDef);

        valueDef->IncLocalRefCount();

        return;
    }

    //
    //  [2] Try to link as imported symbol.
    //

    if (module->HasImportedSymbol(definedName))
    {
        string fromModuleName = 
            module->
                RetrieveImportedFromModuleName(definedName);

        if (asnCC.HasModule(fromModuleName))
        {
            Module* fromModule = asnCC.RetrieveModule(fromModuleName);

            if (fromModule->HasExportedValueDef(definedName))
            {
                ValueDef* valueDef = 
                            fromModule->
                                RetrieveExportedValueDef(definedName);

                Value* value = valueDef->GetValue();

                definedValue->SetLink(value, valueDef);

                valueDef->IncImportRefCount();
            }
            else if (fromModule->HasValueDef(definedName))
            {
                PrintErrLoc(
                    module->GetAsn1SrcFileName(),
                    definedValue->GetLineNumber());
                cerr << "WARNING - value definition \"";
                cerr << definedName;
                cerr << "\" imported but not exported by module";
                cerr << " \"";
                cerr << fromModule->GetName();
                cerr << "\". Link anyway.";
                cerr << endl;

                ValueDef* valueDef = fromModule->RetrieveValueDef(definedName);

                Value* value = valueDef->GetValue();

                definedValue->SetLink(value, valueDef);

                valueDef->IncImportRefCount();
            }
            else
            {
                PrintErrLoc(
                    module->GetAsn1SrcFileName(),
                    definedValue->GetLineNumber());
                cerr << "ERROR - value definition \"";
                cerr << definedName;
                cerr << "\" imported but not defined by module";
                cerr << " \"";
                cerr << fromModule->GetName();
                cerr << "\".";
                cerr << endl;

                module->AddError(Module::MODULE_LINK_ERROR);
            }
        }
        else
        {
            PrintErrLoc(
                module->GetAsn1SrcFileName(),
                definedValue->GetLineNumber());
            cerr << "ERROR - value definition \"";
            cerr << definedName;
            cerr << "\" ";
            cerr << "imported from module \"";
            cerr << fromModuleName;
            cerr << "\" but no such module defined.";
            cerr << endl;

            module->AddError(Module::MODULE_LINK_ERROR);
        }
    }
    else
    {
        // TODO: must be done by evaluator (due to Enumerated values).
        /*
        PrintErrLoc(
            module->GetAsn1SrcFileName(),
            definedValue->GetLineNumber());
        cerr << "ERROR - value definition \"";
        cerr << definedName;
        cerr << "\" ";
        cerr << "used but not local and not imported.";
        cerr << endl;

        module->AddError(Module::MODULE_LINK_ERROR);
        */
    }

}

