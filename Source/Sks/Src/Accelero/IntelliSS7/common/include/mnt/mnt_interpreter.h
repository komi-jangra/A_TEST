///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
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
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:09  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:59  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:55  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:56  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:02  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:59  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.3  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:07:15  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_interpreter.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $"

//
//
// mnt_interpreter.h: MNT parser (internal to MNT).
//
//


#if !defined(_MNT_INTERPRETER_H_)
#define _MNT_INTERPRETER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <mnt.h>
#include <mnt_options.h>
#include <mnt_command.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations.
//

class Mnt;



///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations (opaque).
//

class EvalObject;


///////////////////////////////////////////////////////////////////////////////
//
//  Interpreter.
//

class Interpreter
{
public:

    Interpreter();

    // Default copy constructor not ok (see protected section).

    // Default assignment operator not ok (see protected section).

    virtual ~Interpreter();

    ///////////////////////////////////////////////////////

    bool
    HasCommand(const std::string& name) const
    {
        return _commands.find(name) != _commands.end();
    }

    void
    InsertCommand(Command* command)
    {
        ITS_REQUIRE(!HasCommand(command->GetName()));

        _commands.insert(
            Commands::value_type(
                command->GetName(),
                command));
    }

    const Command&
    RetrieveCommand(const std::string& name) const
    {
        ITS_REQUIRE(HasCommand(name));

        Commands::const_iterator iter = 
            _commands.find(name);

        return *(*iter).second;
    }

    Command&
    RetrieveCommand(const std::string& name)
    {
        ITS_REQUIRE(HasCommand(name));

        Commands::iterator iter = 
            _commands.find(name);

        return *(*iter).second;
    }

    void
    RemoveCommand(const std::string& name)
    {
        ITS_REQUIRE(HasCommand(name));

        _commands.erase(name);
    }

    std::vector<std::string>
    RetrieveCommandNames()
    {
        std::vector<std::string> result;

        for (
            Commands::const_iterator iter = _commands.begin();
            iter != _commands.end();
            iter++)
        {
            result.push_back(((*iter).second)->GetName());
        }

        return result;
    }

    ///////////////////////////////////////////////////////

    bool
    HasVariable(const std::string& name) const
    {
        return _variables.find(name) != _variables.end();
    }

    void
    InsertVariable(const std::string& name, EvalObject* value)
    {
        ITS_REQUIRE(!HasVariable(name));

        _variables.insert(
            Variables::value_type(
                name,
                value));
    }

    const EvalObject&
    RetrieveVariable(const std::string& name) const
    {
        ITS_REQUIRE(HasVariable(name));

        Variables::const_iterator iter = 
            _variables.find(name);

        return *(*iter).second;
    }

    EvalObject&
    RetrieveVariable(const std::string& name)
    {
        ITS_REQUIRE(HasVariable(name));

        Variables::iterator iter = 
            _variables.find(name);

        return *(*iter).second;
    }

    void
    RemoveVariable(const std::string& name)
    {
        ITS_REQUIRE(HasVariable(name));

        _variables.erase(name);
    }

    ///////////////////////////////////////////////////////

    void Execute(Mnt& mnt, FILE* stream);

    ///////////////////////////////////////////////////////

protected:

    typedef std::map<std::string, Command*> Commands;

    Commands _commands;

    typedef std::map<std::string, EvalObject*> Variables;

    Variables _variables;

    Interpreter(const Interpreter& rhs)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

    Interpreter& operator=(const Interpreter& rhs)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
        return *this;
    }
};


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_INTERPRETER_H_)
