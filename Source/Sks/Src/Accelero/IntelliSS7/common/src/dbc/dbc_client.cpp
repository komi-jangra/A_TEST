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
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:14  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:57  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:21  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1.14.1  2004/08/09 05:48:51  sswami
// LOG: Fix for CTRL+D probelm.
// LOG: [When ctrl+D is pressed DBGConsole was spitting into ">>" in loop infinitly]
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/07/25 18:32:19  ngoel
// LOG: add support for command output redirection
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.4  2001/03/02 23:04:04  mmiers
// LOG: Cross platform cleanup.
// LOG:
// LOG: Revision 3.3  2001/02/15 15:58:23  mmiers
// LOG: Ident
// LOG:
// LOG: Revision 3.2  2000/08/24 23:06:37  mmiers
// LOG:
// LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:04:53  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.7  2000/08/04 22:40:16  rsonak
// LOG:
// LOG: If putevent fails, ProcessCommandsFromStream doesnt block
// LOG:
// LOG: Revision 2.6  2000/08/04 22:17:21  rsonak
// LOG:
// LOG: Reconnect and Enter working... Reconnect still has some problem....
// LOG:
// LOG: Revision 2.5  2000/06/13 19:15:55  mmiers
// LOG:
// LOG: C++ assertion no longer throws exception by default.
// LOG:
// LOG: Revision 2.4  2000/04/27 16:54:21  mmiers
// LOG:
// LOG:
// LOG: Remove dead include file.
// LOG:
// LOG: Revision 2.3  2000/03/10 17:19:08  mmiers
// LOG:
// LOG:
// LOG: Remove GDI stubs, they are dead.
// LOG:
// LOG: Revision 2.2  1999/12/16 02:19:19  mmiers
// LOG:
// LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
// LOG: though.
// LOG:
// LOG: Revision 2.1  1999/12/04 00:32:00  mmiers
// LOG:
// LOG:
// LOG: Include GDI stubs (for now).
// LOG:
// LOG: Revision 2.0  1999/12/03 23:27:12  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.6  1999/11/10 18:06:44  mmiers
// LOG:
// LOG:
// LOG: Update after GDI.
// LOG:
// LOG: Revision 1.5  1999/10/29 20:46:08  mmiers
// LOG:
// LOG:
// LOG: Initial GDI implementation.  Needs work still.
// LOG:
// LOG: Revision 1.4  1999/07/16 21:23:15  mmiers
// LOG:
// LOG:
// LOG: Update to work on UNIX.
// LOG:
// LOG: Revision 1.3  1999/07/14 19:52:35  hdivoux
// LOG: Improved synchronization for dbc client and console.
// LOG:
// LOG: Revision 1.2  1999/07/09 23:39:56  hdivoux
// LOG: General update for improved version.
// LOG:
// LOG: Revision 1.1  1999/07/02 16:56:18  mmiers
// LOG:
// LOG:
// LOG: Make this look like other subsystems to automate the NT build.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

//
//  DBC Client implementation.
//


#include <its++.h>
#include <its_transports.h>
#include <its_exception.h>

#ident "$Id: dbc_client.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

#include <dbc.h>
#include <dbc_client.h>

////////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)

//
//  Template getlinefixed.
//
//  The VC++ getline template has a bug: it reads one extra character at the
//  end. This is a copy of that macro with the bug fixed.
//
//  See file [ ...\DevStudio\VC\include\STRING ] for original version.
//

namespace std {

template<class _E, class _TYPE, class _A> inline
	basic_istream<_E, _TYPE>& getlinefixed(basic_istream<_E, _TYPE>& _I,
		basic_string<_E, _TYPE, _A>& _X, const _E _D)
	{ios_base::iostate _St = ios_base::goodbit;
	bool _Chg = false;
	_X.erase();
	const basic_istream<_E, _TYPE>::sentry _Ok(_I, true);
	if (_Ok)
		{_TRY_IO_BEGIN
		_TYPE::int_type _C = _I.rdbuf()->sgetc();
		for (; ; _C = _I.rdbuf()->snextc())
			if (_TYPE::eq_int_type(_TYPE::eof(), _C))
				{_St |= ios_base::eofbit;
				break; }
			else if (_TYPE::eq(_C, _D))
				{_Chg = true;
                _I.rdbuf()->sbumpc();   // Bug was here: used to call snextc(). 
				break; }
			else if (_X.max_size() <= _X.size())
				{_St |= ios_base::failbit;
				break; }
			else
				_X += _TYPE::to_char_type(_C), _Chg = true;
		_CATCH_IO_(_I); }
	if (!_Chg)
		_St |= ios_base::failbit;
	_I.setstate(_St);
	return (_I); }

}   // Namespace std.

#endif // defined(WIN32)

////////////////////////////////////////////////////////////////////////////////


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


void
DbcClient::ProcessCommandsFromStream()
{
    // Print initial prompt if interactive.

    if (isInteractive)
    {
        cout << ">> ";
    }

    try
    {

        while(true)
        {
            if (inputStream.eof())
            {
                break;
            }

            // Read command line.

            string commandLine;
            char cmd[ITS_PATH_MAX];
            char *buf;

            //
            //  Synchronization point.
            //
            //  Wait for ProcessCommandsResult to finish its current work (i.e.
            //  process previous command result) before enabling to send a new
            //  command.
            //

            SynchronizationWait();

    #if defined(WIN32)
            getlinefixed(inputStream, commandLine, '\n');
    #else
            getline(inputStream, commandLine, '\n');
    #endif

            // Echo the command if we are in script mode.

            if (!isInteractive)
            {
                cout << commandLine << endl;
            }

            if (!commandLine.compare(""))
            {
                if (isInteractive)
                {
                    cout << ">> ";
                }

                //
                // Enable to send a new command (see ProcessCommandsFromStream).
                //

                SynchronizationRelease();

                continue;
            }

            // Truncate line at # comment.

            string::size_type firstPound = commandLine.find('#');
            if (firstPound != string::npos)
            {
                commandLine.erase(firstPound);
            }

            // Check For Redirection 

            string::size_type firstRedirect = commandLine.find('>');
            if (firstRedirect != string::npos)
            {
                if ( isInteractive )
                {
                    strcpy(cmd, commandLine.c_str());
                    buf = strstr(cmd, ">");
                    buf++;

                    while (*buf == ' ')
                    {
                        buf++;
                    }

                    strcpy(redirectFileName, buf);
                    isOutputRedirected = true;
                }

                commandLine.erase(firstRedirect);
                
            }

            currentCommand = commandLine;

            if (SendCommand() != ITS_SUCCESS)
            {
                if (isInteractive)
                {
                    cout << ">> ";
                }                

                SynchronizationRelease();

                continue;
            }
        }
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();

        cerr << endl;
        cerr << exc.GetDescription().c_str();
        cerr << endl;
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();

        cerr << endl;
        cerr << standardExc.GetDescription().c_str();
        cerr << endl;
    }
}

void
DbcClient::ProcessCommandsResult()
{
    int res = ITS_SUCCESS;
    FILE *output = NULL;

    ITS_Event event;

    while(!GetWorker()->GetExit())
    {
        res = GetWorker()->GetNextEvent(event);

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

        if (isOutputRedirected && isInteractive && output == NULL)
        {
            output = fopen(redirectFileName, "w");

            if (output == NULL)
            {
            }
        }

        if (event.GetSource() == DBC_QUIT_EVT)
        {
            cout << endl << "Bye..." << endl;

            SynchronizationRelease();

            ResetWorker();

            exit(EXIT_SUCCESS);
        }

        ITS_USHORT length = event.GetLength();

        char *str = (char *)ITS_Calloc(length + 1,
                                       sizeof(ITS_OCTET));

        memcpy(str, event.GetData(), length);

        cout << str;
        cout.flush();

        if (output != NULL && isOutputRedirected  && isInteractive )
        {
             fputs(str, output);
        }

        ITS_Free(str);

        if (event.GetSource() == DBC_LAST_EVT)
        {
            if (isInteractive)
            {
                if (output != NULL)
                {
                    fclose(output);
                    output = NULL;
                    isOutputRedirected = false;
                }

                cout << endl;
                cout << ">> ";
            }

            //
            // Enable to send a new command (see ProcessCommandsFromStream).
            //

            SynchronizationRelease();
        }
    }
}

int 
DbcClient::SendCommand()
{
    try
    {
        ITS_Event event;

        size_t size = currentCommand.size() + 1;

        ITS_THROW_ASSERT(size <= ITS_MAX_EVENT_SIZE);

        event.SetSource(DBC_LAST_EVT);
        event.SetLength(currentCommand.size() + 1);
        event.SetData((unsigned char*)currentCommand.c_str(),
                      currentCommand.size() + 1);

        int res = ITS_Transport::PutEvent(GetWorker()->GetInstance(), event);

        return res;
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();

        cerr << endl;
        cerr << exc.GetDescription().c_str();
        cerr << endl;
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();

        cerr << endl;
        cerr << standardExc.GetDescription().c_str();
        cerr << endl;
    }

    return !ITS_SUCCESS;
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)
