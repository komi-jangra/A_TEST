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
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:57  hbalimid
 * LOG: Got here for demo isup
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
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
 * LOG: Revision 3.1  2000/08/16 00:03:10  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/08/09 00:08:19  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:31  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/07/22 00:34:34  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.1  1998/04/09 01:47:50  mmiers
 * LOG: New file (its_consts.h)
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_CONSTS_H
#define ITS_CONSTS_H

#ident "ID: $Id: its_consts.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $"

/*
 * this better never change
 */
#define ITS_BITS_PER_BYTE   8

/*
 * PATH_MAX is so inconsistently defined, I give up.  We will have to check
 * this value with new OSs
 */
#define ITS_PATH_MAX        255

#define ITS_INFINITE_WAIT   0xFFFFFFFFU

#endif /* ITS_CONSTS_H */
