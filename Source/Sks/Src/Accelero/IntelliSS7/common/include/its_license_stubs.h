/****************************************************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 22:40:18  mmiers
 * LOG: Dead code removal
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/03/28 01:47:12  mmiers
 * LOG: Warning removal (dsmqueue on linux).
 * LOG: License optimizations when capability checking is not desired.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/04/30 23:14:02  mmiers
 * LOG: Prep for release.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 *
 ****************************************************************************/

/*
 *  File (contains stub declarations) to be substituted to original file 
 *  its_licence.h for source code distribution.
 */

#ifndef ITS_LICENSE_H
#define ITS_LICENSE_H

#include <its.h>
#include <its_object.h>

#ident "$Id: its_license_stubs.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * licensable APIs
 */
#define ITS_LIC_CAP_ANSI_MTP3   0
#define ITS_LIC_CAP_ITU_MTP3    1
#define ITS_LIC_CAP_ANSI_ISUP   2
#define ITS_LIC_CAP_ITU_ISUP    3
#define ITS_LIC_CAP_ANSI_SCCP   4
#define ITS_LIC_CAP_ITU_SCCP    5
#define ITS_LIC_CAP_ANSI_TCAP   6
#define ITS_LIC_CAP_ITU_TCAP    7
#define ITS_LIC_CAP_INAP        8
#define ITS_LIC_CAP_IS41        9
#define ITS_LIC_CAP_IS634       10
#define ITS_LIC_CAP_AIN         11
#define ITS_LIC_CAP_GSMMAP      12
#define ITS_LIC_CAP_IS651       13
#define ITS_LIC_CAP_LIDB        14
#define ITS_LIC_CAP_LNP         15
#define ITS_LIC_CAP_ANSI_SNMM   16
#define ITS_LIC_CAP_ITU_SNMM    17
#define ITS_LIC_CAP_ANSI_SLTM   18
#define ITS_LIC_CAP_ITU_SLTM    19

/*
 * replacements
 */
#define LICENSE_Validate()          (ITS_SUCCESS)
#define LICENSE_CheckExpiry()       (ITS_SUCCESS)
#define LICENSE_VerifyCapability(x) (ITS_TRUE)
#define LICENSE_AddLink()           (ITS_SUCCESS)
#define LICENSE_RemLink()
#define LICENSE_Exiting()           (ITS_FALSE)

typedef ITS_ClassRec        LICENSE_ClassRec;

#define LICENSE_CLASS_NAME  "LICENSE_CLASS"

extern LICENSE_ClassRec     itsLICENSE_ClassRec;
extern ITS_Class            itsLICENSE_Class;

#ifdef __cplusplus
}
#endif

#endif /* ITS_LICENSE_H */
