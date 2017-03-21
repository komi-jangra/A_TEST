/*****************************************************************************

 @(#) $RCSfile: xti_udp.h,v $ $Name: not supported by cvs2svn $($Revision: 1.1.1.1 $) $Date: 2007-10-08 11:11:34 $

 -----------------------------------------------------------------------------

 Copyright (c) 2001-2004  OpenSS7 Corporation <http://www.openss7.com>
 Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This library is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free
 Software Foundation; either version 2.1 of the License, or (at your option)
 any later version.

 This library is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Lesser Public License for more
 details.

 You should have received a copy of the GNU Lesser General Public License
 along with this library; if not, write to the Free Software Foundation, Inc.,
 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any success regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 -----------------------------------------------------------------------------

 Last Modified $Date: 2007-10-08 11:11:34 $ by $Author: bsccs2 $

 $Log: not supported by cvs2svn $
 Revision 1.1.1.1  2007/10/04 13:24:04  bsccs2
 init tree

 Revision 1.1  2007/09/24 05:48:18  ankur.sharda
 *** empty log message ***

 Revision 1.1.2.1  2004/04/13 12:12:52  brian
 - Rearranged header files.

 *****************************************************************************/

#ifndef _SYS_XTI_UDP_H
#define _SYS_XTI_UDP_H

#ident "@(#) $RCSfile: xti_udp.h,v $ $Name: not supported by cvs2svn $($Revision: 1.1.1.1 $) Copyright (c) 1997-2004 OpenSS7 Corporation."

/* 
 * UDP level
 */
#define T_INET_UDP		17	/* UDP level (same as protocol number) */

/* 
 * UDP level Options
 */
#define T_UDP_CHECKSUM		1	/* checksum computation (???) */

#endif				/* _SYS_XTI_UDP_H */

