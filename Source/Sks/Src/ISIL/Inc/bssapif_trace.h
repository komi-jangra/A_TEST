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
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:00  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:10:13  adutta
 * LOG: Initial implementation
 * LOG:
 * LOG:
 *
 * ID: $Id: bssapif_trace.h,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_trace.h,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $"

#ifndef BSSAPIF_TRACE_H
#define BSSAPIF_TRACE_H

#include <its++.h>
#include <its_trace.h>

/*
 * Define macros for trace variables.
 */

#define BSSAPIF_DEBUG          ITS_DEBUG_STRING 
#define BSSAPIF_ERROR          ITS_ERROR_STRING 
#define BSSAPIF_WARNING        ITS_WARNING_STRING 
#define BSSAPIF_CRITICAL       ITS_CRITICAL_STRING 

#define BSSAPIF_TRACE_DEBUG(x) \
              ITS_TRACE(BSSAPIF_DEBUG, x)

#define BSSAPIF_TRACE_CRITICAL(x) \
              ITS_TRACE(BSSAPIF_CRITICAL, x)

#define BSSAPIF_TRACE_ERROR(x) \
              ITS_TRACE(BSSAPIF_ERROR, x)

#define BSSAPIF_TRACE_WARNING(x) \
              ITS_TRACE(BSSAPIF_WARNING, x)

void EnableBSSAPIFTracing();
void DisableBSSAPIFracing();

#endif
