/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:50  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.5  2001/06/26 16:47:14  mmiers
 * LOG: Try to get the warnings out.  It isn't possible.
 * LOG:
 * LOG: Revision 4.4  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.3  2001/06/16 01:05:50  mmiers
 * LOG: Declspecs.
 * LOG:
 * LOG: Revision 4.2  2001/06/16 00:03:42  mmiers
 * LOG: Various fixes from PR4.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/04/11 21:30:11  mmiers
 * LOG: Apparently declspecs don't apply to static member variables.
 * LOG:
 * LOG: Revision 3.3  2001/03/14 22:09:04  mmiers
 * LOG: Windowsism.
 * LOG:
 * LOG: Revision 3.2  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.1  2001/03/06 22:01:23  mmiers
 * LOG: New statics file for CPP globals.  Down to one SUPPORT lib.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_exception_log.h>
#include <its_service.h>
#include <its_trace.h>

#ident "$Id: its_statics.cpp,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*
 * NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 *
 * Include this file exactly once per executable.
 *
 * NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 */

/*
 * static class members.
 */
#if !defined(STANDALONE)

/*
 * exception implementation (nothing in it now).
 */
#include <its_support_exception.cpp>

/*
 * SUPPORT static objects.
 */
ITSDLLAPI its::Service*         its::its_intern_currentService = NULL;
ITSDLLAPI its::ExceptionLog*    its::its_intern_exceptionLog = NULL;

#endif

/*
 * CORE static objects.
 */
ITSDLLAPI its::TraceSubSystem*  its::its_intern_trace = NULL;

