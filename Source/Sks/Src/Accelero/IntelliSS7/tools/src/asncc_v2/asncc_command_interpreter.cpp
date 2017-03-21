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
// LOG: Revision 1.1.1.1  2007/03/08 15:14:45  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:13  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.3  2005/03/21 13:52:59  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_command_interpreter.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"



#include <asncc_command_interpreter.h>


#if !defined(HPUX)

using namespace std;

#endif

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



