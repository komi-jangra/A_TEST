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
//  ID: $Id: asncc_command_interpreter.h,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_ASNCC_COMMAND_INTERPRETER_H_)
#define _ASNCC_COMMAND_INTERPRETER_H_

#include <asncc.h>
#include <asncc_assertion.h>
#include <asncc_command_file.h>
#include <asncc_ast.h>


////////////////////////////////////////////////////////////////////////////////
//
//  CommandInterpreter.
//

class CommandInterpreter
{
public:

    explicit CommandInterpreter(const std::string& commandFilePathParam)
    :   commandFile(commandFilePathParam),
        initialized(false)
    {};

    void Initialize();

    void Terminate();

    bool 
    IsInitialized() const
    { return initialized; }

    const CommandFile& 
    GetCommandFile() const
    { return commandFile; }

    void ProcessModule(Module& module);

protected:

    CommandFile commandFile;

    bool initialized;
};



#endif  // !defined(_ASNCC_COMMAND_INTERPRETER_H_)

