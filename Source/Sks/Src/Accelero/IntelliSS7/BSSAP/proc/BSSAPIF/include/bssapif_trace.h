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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/06/28 04:11:38  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:10:13  adutta
 * LOG: Initial implementation
 * LOG:
 * LOG:
 *
 * ID: $Id: bssapif_trace.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_trace.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $"

#ifndef BSSAPIF_TRACE_H
#define BSSAPIF_TRACE_H

#include <its++.h>
#include <its_trace.h>

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif

#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif


/*
 * Define macros for trace variables.
 */

#define BSSAPIF_DEBUG          ITS_DEBUG_STRING 
#define BSSAPIF_ERROR          ITS_ERROR_STRING 
#define BSSAPIF_WARNING        ITS_WARNING_STRING 
#define BSSAPIF_CRITICAL       ITS_CRITICAL_STRING 

#define BSSAPIF_TRACE_DEBUG(x) \
              ITS_TRACE(BSSAPIF_DEBUG, x)


#ifdef LOGGER_IMR
#define BSSAPIF_TRACE_CRITICAL(x) \
    LOG_PRINT_CRITICAL x;
#else
#define BSSAPIF_TRACE_CRITICAL(x) \
            ITS_TRACE(BSSAPIF_CRITICAL, x)
#endif

#ifdef LOGGER_IMR
#define BSSAPIF_TRACE_ERROR(x) \
    LOG_PRINT_CRITICAL x ;
#else
#define BSSAPIF_TRACE_ERROR(x) \
              ITS_TRACE(BSSAPIF_ERROR, x)
#endif

#ifdef LOGGER_IMR
#define BSSAPIF_TRACE_WARNING(x) \
   LOG_PRINT_MAJOR x;
#else
#define BSSAPIF_TRACE_WARNING(x) \
              ITS_TRACE(BSSAPIF_WARNING, x)
#endif




void EnableBSSAPIFTracing();
void DisableBSSAPIFracing();

#endif
