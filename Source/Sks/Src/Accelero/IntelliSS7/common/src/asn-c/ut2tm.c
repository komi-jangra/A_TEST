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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:12  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:02  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:51:05  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:21  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:17  cvsadmin
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
 * LOG: Revision 3.1  2000/08/16 00:04:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:46  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:51  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/06/01 17:15:09  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.2  1999/02/26 00:48:01  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:16:15  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/22 20:29:27  mmiers
 * LOG: Finish reentrancy fixes, round one.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 17:48:46  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:23  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:33:14  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * ut2tm.c - time string to tm
 */

#include <asn-c/AsnC.h>

#ident "$Id: ut2tm.c,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

#define	UNYEAR(y)	((y) < 1900 || (y) > 1999 ? (y) : (y) - 1900)
#define isleap(y)       \
        (((y) % 4) ? 0 : (((y) % 100) ? 1 : (((y) % 400) ? 0 : 1)))

extern int dmsize[];
static  int makewkday (UTC);

struct tm
ut2tm (UTC ut)
{
    struct tm tm;

    memset ((char *)&tm, 0, sizeof tm);

    tm.tm_sec = ut->ut_sec;
    tm.tm_min = ut->ut_min;
    tm.tm_hour = ut->ut_hour;
    tm.tm_mday = ut->ut_mday;
    tm.tm_mon = ut->ut_mon - 1;
    tm.tm_year = UNYEAR (ut->ut_year);
    tm.tm_wday = makewkday (ut);
    tm.tm_yday = tm.tm_isdst = 0;

    tm.tm_hour -= ut->ut_zone / 60, tm.tm_min -= ut->ut_zone % 60;
    if (tm.tm_min < 0)
    {
	tm.tm_hour--, tm.tm_min += 60;
    }
    else
    {
	if (tm.tm_min > 59)
        {
	    tm.tm_hour++, tm.tm_min -= 60;
        }
    }


    if (tm.tm_hour < 0)
    {
	tm.tm_mday--, tm.tm_hour += 24;

	if (tm.tm_mday < 1)
        {
	    tm.tm_mday = dmsize[--tm.tm_mon];
	    if (tm.tm_mon == 1 && isleap(tm.tm_year+1900))
            {
		tm.tm_mday ++;
            }
	    if (tm.tm_mon < 0)
            {
		tm.tm_year--, tm.tm_mon = 11;
            }
	}
	
    }
    else
    {
	if (tm.tm_hour > 23)
        {
	    int mdays;

	    tm.tm_mday++, tm.tm_hour -= 24;
	    mdays = dmsize[tm.tm_mon];

	    if (tm.tm_mon == 1 && isleap (1900+tm.tm_year))
            {
		mdays ++;
            }

	    if (tm.tm_mday > mdays)
            {
		tm.tm_mon++, tm.tm_mday = 1;
		if (tm.tm_mon > 11)
                {
		    tm.tm_year++, tm.tm_mon = 0;
                }
	    }
	}
    }

    return tm;
}

#define	dysize(y)	\
	(((y) % 4) ? 365 : (((y) % 100) ? 366 : (((y) % 400) ? 365 : 366)))

#define	YEAR(y)		((y) >= 100 ? (y) : (y) + 1900)


static  int
makewkday (UTC ut)
{
    int     d, mon, year;

    mon = ut->ut_mon;
    year = YEAR (ut->ut_year);
    d = 4 + year + (year + 3) / 4;

    if (year > 1800)
    {
	d -= (year - 1701) / 100;
	d += (year - 1601) / 400;
    }

    if (year > 1752)
    {
	d += 3;
    }

    if (dysize (year) == 366 && mon > 3)
    {
	d++;
    }

    while (--mon > 0)
    {
	d += dmsize[mon - 1];
    }

    d += ut->ut_mday - 1;

    return (d % 7);
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

