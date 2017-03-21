/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 * ID: $Id: bssap-msc.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 *
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_BASE_H_
#define  _BSSAP_BSSAP_H_

#include<its.h>
#include<its++.h>
#include <its_singleton.h>
#include <its_types.h>
#include <its_transports.h>
#include <its_tq_trans.h>
#include<engine.h>

using namespace its;
using namespace std;


extern TRACE_Data* BSSAP_TraceData;



#define BSSAP_CRITICAL_STRING        ITS_CRITICAL_STRING
#define BSSAP_ERROR_STRING           ITS_ERROR_STRING
#define BSSAP_WARNING_STRING         ITS_WARNING_STRING
#define BSSAP_DEBUG_STRING           ITS_DEBUG_STRING
#define BSSAP_EVENT_STRING           ITS_EVENT_STRING

#define BSSAP_STDOUT_STRING          ITS_STDOUT_STRING
#define BSSAP_SYSLOG_STRING          ITS_SYSLOG_STRING
#define BSSAP_FILE_STRING            ITS_FILE_STRING

#define BSSAP_TRACE_CRITICAL_FILE    (void*)".itu-bssap-traceCritical"
#define BSSAP_TRACE_ERROR_FILE       (void*)".itu-bssap-traceError"
#define BSSAP_TRACE_WARNING_FILE     (void*)".itu-bssap-traceWarning"
#define BSSAP_TRACE_DEBUG_FILE       (void*)".itu-bssap-traceDebug"
#define BSSAP_TRACE_EVENT_FILE       (void*)".itu-bssap-traceEvent"

#define BSSAP_TRACE_CRITICAL  0
#define BSSAP_TRACE_ERROR     1
#define BSSAP_TRACE_WARNING   2
#define BSSAP_TRACE_DEBUG     3
#define BSSAP_TRACE_EVENT     4

#define BSSAP_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING
#define BSSAP_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define BSSAP_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define BSSAP_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING


#define BSSAP_CRITICAL(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_CRITICAL, args)

#define BSSAP_ERROR(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_ERROR, args)

#define BSSAP_WARNING(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_WARNING, args)

#define BSSAP_DEBUG(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_DEBUG, args)

#define BSSAP_EVENT(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_EVENT, args)


#endif
