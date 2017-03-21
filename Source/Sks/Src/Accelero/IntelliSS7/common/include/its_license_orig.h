/****************************************************************************
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
 * LOG: Revision 1.1  2007/05/23 07:32:31  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.3.6.2.4.1  2004/12/16 03:26:18  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.3.2.3.6.2  2004/10/06 13:16:09  mmanikandan
 * LOG: License class exported.
 * LOG:
 * LOG: Revision 7.3.2.3.6.1  2004/07/26 06:52:27  mmanikandan
 * LOG: License support for BSSAP.
 * LOG:
 * LOG: Revision 7.3.2.3  2003/08/05 13:32:43  mmanikandan
 * LOG: Support for temporary license.
 * LOG:
 * LOG: Revision 7.3.2.2  2003/07/07 12:19:40  mmanikandan
 * LOG: License capability is added for IS652, IS653, IS826, WIN, JSTD.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/06/16 11:11:03  sjaddu
 * LOG: Added CAMEL license capability.
 * LOG:
 * LOG: Revision 7.3  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.2  2002/09/20 15:44:08  mmiers
 * LOG: Fix the licensing binaries
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/07/10 19:10:25  mmiers
 * LOG: Buggy license printing fixes
 * LOG:
 * LOG: Revision 6.4  2002/07/03 16:37:45  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.3  2002/03/28 01:47:12  mmiers
 * LOG: Warning removal (dsmqueue on linux).
 * LOG: License optimizations when capability checking is not desired.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 18:01:34  mmiers
 * LOG: license fixes, new behaviors implementation, timer block
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/07 17:08:19  mmiers
 * LOG: Add link count to licensing.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.5  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
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
 * LOG: Revision 3.1  2000/08/16 00:03:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/07/27 19:59:16  mmiers
 * LOG:
 * LOG: Move things around so we can publish the license API.
 * LOG:
 * LOG: Revision 2.5  2000/07/17 15:24:19  mmiers
 * LOG:
 * LOG:
 * LOG: Small API changes, mostly typing.
 * LOG:
 * LOG: Revision 2.4  2000/07/03 22:40:15  mmiers
 * LOG:
 * LOG:
 * LOG: Add message digest
 * LOG:
 * LOG: Revision 2.3  2000/07/03 22:06:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add secure hash.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:32  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  2000/02/01 23:09:12  mmiers
 * LOG:
 * LOG:
 * LOG: Auto start the license system.  Can do away with standalone *now*.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:40  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/10/06 22:19:46  mmiers
 * LOG:
 * LOG:
 * LOG: Update new user part, integrate into licensing scheme.
 * LOG:
 * LOG: Revision 1.7  1999/03/24 22:45:26  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.6  1999/03/13 00:12:28  mmiers
 * LOG:
 * LOG:
 * LOG: Add capabilities test to license generation.
 * LOG:
 * LOG: Revision 1.5  1999/03/12 18:20:08  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.4  1999/02/04 22:26:37  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.3  1998/05/14 01:22:43  mmiers
 * LOG: General cleanup.  Remove dead files.  Adjust include comments.
 * LOG:
 * LOG: Revision 1.2  1998/05/01 00:24:32  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 19:00:10  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_LICENSE_H
#define ITS_LICENSE_H

#include <its.h>
#include <its_object.h>

#ident "$Id: its_license_orig.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"
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
#define ITS_LIC_CAP_PRC_MTP3    20
#define ITS_LIC_CAP_PRC_ISUP    21
#define ITS_LIC_CAP_PRC_SCCP    22
#define ITS_LIC_CAP_PRC_TCAP    23
#define ITS_LIC_CAP_PRC_SNMM    24
#define ITS_LIC_CAP_PRC_SLTM    25
#define ITS_LIC_CAP_CAMEL       26
#define ITS_LIC_CAP_IS652       27
#define ITS_LIC_CAP_IS653       28
#define ITS_LIC_CAP_IS826       29
#define ITS_LIC_CAP_WIN         30 
#define ITS_LIC_CAP_JSTD        31 
#define ITS_LIC_CAP_BSSAP       32 
#define ITS_LIC_CAP_TTC_MTP3    33
#define ITS_LIC_CAP_TTC_ISUP    34 
#define ITS_LIC_CAP_TTC_SCCP    35 
#define ITS_LIC_CAP_TTC_TCAP    36
#define ITS_LIC_CAP_TTC_SNMM    37
#define ITS_LIC_CAP_TTC_SLTM    38 
#
/*
 * prototypes
 */
#if defined(__cplusplus)
extern "C"
{
#endif

ITSDLLAPI ITS_BOOLEAN LICENSE_Exiting();
ITSDLLAPI void        LICENSE_Load();
ITSDLLAPI void        LICENSE_Update();
ITSDLLAPI int         LICENSE_Validate(void);
ITSDLLAPI int         LICENSE_Revalidate(void);
ITSDLLAPI int         LICENSE_CheckExpiry(void);

#if defined(EXCLUDE_CAPABILITIES)
#define LICENSE_VerifyCapability(x)	(ITS_TRUE)
#define LICENSE_CheckCapability(x)      (ITS_TRUE)
#else
ITSDLLAPI ITS_BOOLEAN LICENSE_VerifyCapability(int capability);
ITSDLLAPI ITS_BOOLEAN LICENSE_CheckCapability(int capability);
#endif

#if defined(EXCLUDE_LINK_COUNTING)
#define LICENSE_AddLink()    (ITS_SUCCESS)
#define LICENSE_RemLink()
#else
ITSDLLAPI int         LICENSE_AddLink();
ITSDLLAPI void        LICENSE_RemLink();
#endif

typedef ITS_ClassRec        LICENSE_ClassRec;

#define LICENSE_CLASS_NAME  "LICENSE_CLASS"

extern LICENSE_ClassRec     itsLICENSE_ClassRec;
extern ITSDLLAPI ITS_Class            itsLICENSE_Class;

#ifdef __cplusplus
}
#endif

#endif /* ITS_LICENSE_H */
