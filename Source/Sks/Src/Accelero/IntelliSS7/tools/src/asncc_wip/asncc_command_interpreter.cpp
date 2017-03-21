////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: asncc_command_interpreter.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////



#include <asncc_command_interpreter.h>


using namespace std;


////////////////////////////////////////////////////////////////////////////////
//
//  CommandInterpreter.
//

void
CommandInterpreter::Initialize()
{
    try 
    {
        commandFile.Parse();
    }
    catch (CommandFileError& cfe)
    {
        string fileNameUndefined = "XXXXXXXX.XXX";

        PrintErrLoc(fileNameUndefined, 0);
        cerr << "ERROR - COMMAND FILE RELATED - ";
        cerr << cfe.Description().c_str();
        cerr << ".";
        cerr << endl;        
    }

    initialized = true;
}


void
CommandInterpreter::Terminate()
{
    // Nothing to do.
}


void
CommandInterpreter::ProcessModule(Module& module)
{
    string moduleName = module.GetName();

    const CommandFile& commandFile = GetCommandFile();

    if (commandFile.HasSection(moduleName))
    {
        // ObjectClassReference key(s).

        const Section& section = commandFile.GetSection(moduleName);

        if (section.HasMultiKey("ObjectClassReference"))
        {
            const Section::TypeValues& values = 
                section.GetMultiValues("ObjectClassReference");

            for (size_t i = 0; i < values.size(); i++)
            {
                module.InsertObjectClassReference(values[i]);
            }
        }

        if (section.HasMultiKey("ObjectReference"))
        {
            const Section::TypeValues& values = 
                section.GetMultiValues("ObjectReference");

            for (size_t i = 0; i < values.size(); i++)
            {
                module.InsertObjectReference(values[i]);
            }
        }

        if (section.HasMultiKey("ObjectSetReference"))
        {
            const Section::TypeValues& values = 
                section.GetMultiValues("ObjectSetReference");

            for (size_t i = 0; i < values.size(); i++)
            {
                module.InsertObjectSetReference(values[i]);
            }
        }
    }
}



