//////////////////////////////////-*-C-*-////////////////////////////////////
//                                                                         //
//             Copyright 1997,1998 IntelliNet Technologies, Inc.           //
//                            All Rights Reserved.                         //
//             Manufactured in the United States of America.               //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.      //
//                                                                         //
//   This product and related documentation is protected by copyright and  //
//   distributed under licenses restricting its use, copying, distribution //
//   and decompilation.  No part of this product or related documentation  //
//   may be reproduced in any form by any means without prior written      //
//   authorization of IntelliNet Technologies and its licensors, if any.   //
//                                                                         //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     //
//   government is subject to restrictions as set forth in subparagraph    //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software      //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// CONTRACT: INTERNAL                                                      //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: dbc_command_client.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $
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
// LOG: Revision 8.2  2005/03/21 13:51:22  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
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
// LOG: Revision 3.1  2000/08/16 00:04:53  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 1.4  2000/06/13 19:15:56  mmiers
// LOG:
// LOG: C++ assertion no longer throws exception by default.
// LOG:
// LOG: Revision 1.3  2000/03/29 18:20:42  ahanda
// LOG: Need them for HNS Vlr Cache Dump
// LOG:
// LOG: Revision 1.2  1999/02/08 17:07:53  rsonak
// LOG:
// LOG: Got DBC Command working
// LOG:
// LOG: Revision 1.1  1999/02/04 22:03:00  rsonak
// LOG:
// LOG: DBC Commandline Utility. Does the same work od DBC console through command line.
// LOG:
// LOG: Revision 1.1  1998/11/17 17:44:26  mmiers
// LOG: Move DBC into common to sanitize the build.
// LOG:
// LOG: Revision 1.3  1998/11/05 21:29:52  mmiers
// LOG: Build on HPUX.
// LOG:
// LOG: Revision 1.2  1998/11/05 21:20:51  mmiers
// LOG: Portability build.
// LOG:
//
/////////////////////////////////////////////////////////////////////////////

//
//  DBC Client implementation.
//


#include <its++.h>
#include <its_transports.h>
#include <its_exception.h>

#include <dbc.h>
#include <dbc_command_client.h>

//////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)

//
//  Template getlinefixed.
//
//  The VC++ getline template has a bug: it reads
//  one extra character at the end.  This is a copy
//  of that macro with the bug fixed.
//
//  See file [ ...\DevStudio\VC\include\STRING ].
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

#endif

//////////////////////////////////////////////////////////////////////////////


#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

// Since the code rely on the standard C++ library,
// the following must be accepted by the compiler.
#if !defined(HPUX)
using namespace std;
#endif


void
DbcClient::ProcessCommandsFromStream(std::istream& inputStream,
                                     bool isInteractive)
{
    int res = ITS_SUCCESS;

    while(true)
    {
        if (inputStream.eof())
        {
            break;
        }

        // Read command line.

        string commandLine;

        // Acquire and immediately release cout lock: if lock is acquired then
        // ProcessCommandsResult has finished its current work and is waiting
        // for a new event.

        res = coutLock.Acquire();

        if (res != ITS_SUCCESS)
        { 
            ITS_THROW_ERROR(res);
        }

        res = coutLock.Release();

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

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

        // Truncate line at # comment.

        string::size_type firstPound = commandLine.find('#');
        if (firstPound != string::npos)
        {
            commandLine.erase(firstPound);
        }

        currentCommand = commandLine;

        SendCommand();
    }
}

void
DbcClient::ProcessCommandsResult()
{
    ITS_THROW_ASSERT(worker != NULL);

    int res = ITS_SUCCESS;

    ITS_Event event;

    bool coutLocked = false;

    while(!worker->GetExit())
    {
        res = worker->GetNextEvent(event);

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

        if (!coutLocked)
        {
            res = coutLock.Acquire();

            if (res != ITS_SUCCESS)
            {
                ITS_THROW_ERROR(res);
            }

            coutLocked = true;
        }

        if (event.GetSource() == DBC_QUIT_EVT)
        {
            if (coutLocked)
            {
                res = coutLock.Release();

                if (res != ITS_SUCCESS)
                {
                    ITS_THROW_ERROR(res);
                }
            }

            exit(EXIT_SUCCESS);
        }

        ITS_USHORT length = event.GetLength();

        char str[ITS_MAX_EVENT_DATA_LEN + 1];

        memset((void*)str, 0, ITS_MAX_EVENT_DATA_LEN);

        memcpy(str, event.GetData(), length);

        str[ITS_MAX_EVENT_DATA_LEN] = '\0';

        cout << str;

        if (event.GetSource() == DBC_LAST_EVT)
        {
            if (isInteractive)
            {
                cout << endl;
                cout << ">> ";
            }

			commandsResultCounter++;

            res = coutLock.Release();

            if (res != ITS_SUCCESS)
            {
                ITS_THROW_ERROR(res);
            }

            coutLocked = false;
        }
    }

}

void 
DbcClient::SendCommand()
{
    ITS_THROW_ASSERT(worker != NULL);

    ITS_Event event;
    size_t size = currentCommand.size() + 1;

    ITS_ASSERT(size <= ITS_MAX_EVENT_DATA_LEN);

    event.SetSource(DBC_LAST_EVT);
    event.SetLength(currentCommand.size() + 1);
    event.SetData((unsigned char*)currentCommand.c_str(),
                  currentCommand.size() + 1);

    int res = ITS_Transport::PutEvent(worker->GetInstance(), event);

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}



#if defined(ITS_NAMESPACE)
}
#endif  
