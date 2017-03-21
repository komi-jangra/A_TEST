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
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/25 06:03:56  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2007/09/24 05:33:45  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/06/29 07:46:42  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2007/06/25 12:03:28  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:19:28  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1  2006/01/25 05:33:56  yranade
 * LOG: First Cut (badri)
 * LOG:
 * LOG: Revision 1.1  2005/11/24 06:05:22  yranade
 * LOG: Create Baseline GSM-BSC Infrastructure.
 * LOG:
 *
 * ID: $Id: lapd_trace.h,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: lapd_trace.h,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $"

#ifndef LAPD_TRACE_H
#define LAPD_TRACE_H

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_msgdef.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif

/*
 * Define macros for trace variables.
 */
#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif



#ifdef LOGGER_IMR
#define LAPD_TRACE_INFO(x)    LOG_PRINT_INFO x;
#else
#define LAPD_TRACE_INFO(x) printf(x); fflush(stdout);
#endif



#ifdef LOGGER_IMR
#define LAPD_TRACE_DEBUG(x)    LOG_PRINT_DEBUG x;
#else
#define LAPD_TRACE_DEBUG(x) printf(x); fflush(stdout);
#endif


#ifdef LOGGER_IMR
#define LAPD_TRACE_CRITICAL(x)    LOG_PRINT_CRITICAL x;
#else
#define LAPD_TRACE_CRITICAL(x) printf(x); fflush(stdout);
#endif


#ifdef LOGGER_IMR
#define LAPD_TRACE_MAJOR(x)    LOG_PRINT_MAJOR x;
#else
#define LAPD_TRACE_MAJOR(x) printf(x); fflush(stdout);
#endif



#ifdef LOGGER_IMR
#define LAPD_INT_TRACE_DEBUG(x) \
    LOG_PRINT_DEBUG x;
#else
#define LAPD_INT_TRACE_DEBUG(x, y) printf(x, y); fflush(stdout);
#endif

#endif
