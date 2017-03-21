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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:11  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:01  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:50:22  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:19  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 21:05:16  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:02  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/24 20:37:56  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/02/14 20:44:32  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:40  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:36  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/07/22 00:34:37  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:45  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:34  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 04:30:57  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:04  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:33:01  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * ps_alloc.c - allocate a presentation stream
 */

#include <asn-c/AsnC.h>

#ident "$Id: ps_alloc.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

/* A Presentatation Stream (or PStream) is the second generation of
   "generic" I/O stream-based handling.  (For the first attempt,
   take a look at the prototype implementation of the TTI Trusted Mail
   Agent.)  The idea is to present a common, simple I/O paradigm (i.e.,
   the UNIX v7 philosophy) to protocol-translation entities regardless of
   the underlying medium (files, pipes, sockets, or strings).

   New streams are created by a call to ps_alloc().  It allocates memory
   and calls an open routine.  This routine fills in the dispatch vectors
   for read/write and (optionally) close.  It can also fill in any other
   part of the stream's structure it likes.

   Once created, I/O is done using the macros ps_read/ps_write.  These
   return either NOTOK or OK; depending on how things went. The read/write
   routines are invoked as:

	int	iofunc (ps, data, n, in_line)
	PS	ps;
	PElementData data;
	PElementLen  n;
	int	in_line;

   They should read/write upto len bytes, starting at data, and return the
   number of bytes processed, or NOTOK on error.  The routine ps_io() will
   make successive calls to fill/flush the data.  If the read/write routine
   returns NOTOK, it should set ps_errno as well.

   Streams are removed by a call to ps_free ().  It calls the close
   routine, if any, which should de-commission any parts of the stream's
   structure that are in use.  ps_free() will then free the allocated
   memory.
 */
PS
ps_alloc (OPENFP io)
{
    PS	    ps;

    if ((ps = (PS) calloc (1, sizeof *ps)) == NULL)
    {
        return NULL;
    }
    
    if ((*io)(ps) == NOTOK)
    {
        ps_free (ps);
        
        return NULL;
    }
    
    return ps;
}

/****************************************************************************
 *
 * The ISODE is openly available but is NOT in the public domain.  You
 * are allowed and encouraged to take this software and build commercial
 * products.  However, as a condition of use, you are required to ``hold
 * harmless'' all contributors.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that this notice and the reference to this notice appearing in each
 * software module be retained unaltered, and that the name of any
 * contributors shall not be used in advertising or publicity pertaining
 * to distribution of the software without specific written prior permission.
 * No contributor makes any representations about the suitability of this
 * software for any purpose.  It is provided ``as is'' without express or
 * implied warranty.
 * 
 *      ALL CONTRIBUTORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 *      SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 *      AND FITNESS FOR THE PARTICULAR PURPOSE, TITLE, AND NON-INFRINGEMENT.
 *
 *      IN NO EVENT SHALL ANY CONTRIBUTOR BE LIABLE FOR ANY SPECIAL,
 *      INDIRECT OR CONSEQUENTIAL DAMAGES, WHETHER IN CONTRACT, TORT, OR
 *      OTHER FORM OF ACTION, ARISING OUT OF OR IN CONNECTION WITH, THE
 *      USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ***************************************************************************/

