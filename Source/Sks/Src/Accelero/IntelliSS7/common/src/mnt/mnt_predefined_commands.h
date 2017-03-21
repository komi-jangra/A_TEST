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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:27  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:18  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:31  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/04/29 20:45:39  hdivoux
// LOG: Typo.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.3  2001/10/09 19:17:04  hdivoux
// LOG: Added GetArraySize command and allowed for empty arrays.
// LOG:
// LOG: Revision 5.2  2001/08/29 17:12:25  hdivoux
// LOG: Added Exit predefined command.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.5  2001/08/09 19:28:19  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/07 23:25:23  hdivoux
// LOG: Update for debug related commands.
// LOG:
// LOG: Revision 1.3  2001/08/07 21:52:59  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_predefined_commands.h,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_predefined_commands.h: MNT predefined commands (internal to MNT).
//
//


#if !defined(_MNT_PREDEFINED_COMMANDS_H_)
#define _MNT_PREDEFINED_COMMANDS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <mnt.h>
#include <mnt_command.h>

#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
// Predefined command definitions.
//

MNT_DEFINE_COMMAND_CLASS(
                    CommandPrint,
                    "Print",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandSleep,
                    "Sleep",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandBreakpoint,
                    "Breakpoint",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandInitializeNodes,
                    "InitializeNodes",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandInitializeNodesSyncPoints,
                    "InitializeNodesSyncPoints",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandInitializeGcs,
                    "InitializeGcs",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTerminateNodes,
                    "TerminateNodes",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTerminateNodesSyncPoints,
                    "TerminateNodesSyncPoints",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTerminateGcs,
                    "TerminateGcs",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandWaitForNodeJoinPoint,
                    "WaitForNodeJoinPoint",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandWaitForNodeSyncPoint,
                    "WaitForNodeSyncPoint",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandPublishNodeSyncPointReached,
                    "PublishNodeSyncPointReached",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandSetInternalDebugOn,
                    "SetInternalDebugOn",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandSetInternalDebugOff,
                    "SetInternalDebugOff",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandSetInternalParserDebugOn,
                    "SetInternalParserDebugOn",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandSetInternalParserDebugOff,
                    "SetInternalParserDebugOff",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandSystem,
                    "System",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandRedirectStdout,
                    "RedirectStdout",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandPrintFile,
                    "PrintFile",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandExit,
                    "Exit",
                    "built-in");

MNT_DEFINE_COMMAND_CLASS(
                    CommandGetArraySize,
                    "GetArraySize",
                    "built-in");

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_PREDEFINED_COMMANDS_H_)
