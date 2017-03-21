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
 *
 *  ID: $Id: app_trace.h,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:34  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:27  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:53  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.1  2005/01/31 11:12:44  kannanp
 * LOG: Sample App - initial.
 * LOG:
 ****************************************************************************/

#ifndef APP_TRACE_H
#define APP_TRACE_H

#ident "$Id: app_trace.h,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $"

#include <stdio.h>
#include <its++.h>
#include <its_trace.h>

/*
 * Define macros for trace variables.
 */
#define APP_CRITICAL   "APP_CRITICAL"
#define APP_DEBUG      "APP_DEBUG"
#define APP_ERROR      "APP_ERROR"
#define APP_WARNING    "APP_WARNING"

extern its::ITS_TraceLevel  appTraceCritical;
extern its::ITS_TraceLevel  appTraceDebug;
extern its::ITS_TraceLevel  appTraceError;
extern its::ITS_TraceLevel  appTraceWarning;

#if defined(ISS7_APP_TRACE)
#define APP_TRACE_DEBUG(x) \
              ITS_TRACE(APP_DEBUG, x)

#define APP_TRACE_CRITICAL(x) \
              ITS_TRACE(APP_CRITICAL, x)

#define APP_TRACE_ERROR(x) \
              ITS_TRACE(APP_ERROR, x)

#define APP_TRACE_WARNING(x) \
              ITS_TRACE(APP_WARNING, x)

#elif APP_STDOUT_TRACE

#define APP_TRACE_DEBUG(x) printf x ; printf("\n"); fflush(stdout)
#define APP_TRACE_CRITICAL(x) printf x ; printf("\n"); fflush(stdout)
#define APP_TRACE_ERROR(x) printf x ;  printf("\n");fflush(stdout)
#define APP_TRACE_WARNING(x) printf x ; printf("\n"); fflush(stdout)

#else

#define APP_TRACE_DEBUG(x)
#define APP_TRACE_CRITICAL(x)
#define APP_TRACE_ERROR(x) 
#define APP_TRACE_WARNING(x)

#endif
#if defined FILE_APP_TRACE
#define SPRINTF(x) sprintf x
#else
#define SPRINTF(x)
#endif


void EnableAppTracing();

#endif

