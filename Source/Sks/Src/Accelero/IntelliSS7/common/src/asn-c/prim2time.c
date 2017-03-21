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
 * LOG: Revision 1.1  2007/03/30 04:50:19  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:19  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 21:05:15  mmiers
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
 * LOG: Revision 3.1  2000/08/16 00:04:27  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:40  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:35  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/06/01 17:15:07  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 15:41:08  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Solaris C++ build.
 * LOG:
 * LOG: Revision 1.2  1999/02/26 00:47:58  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:41  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.7  1998/10/22 19:28:11  mmiers
 * LOG: Continue making PSAP threadsafe.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:33  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 04:30:55  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:03  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:33:01  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * prim2time.c - presentation element to time string
 */
#include <asn-c/AsnC.h>

#ident "$Id: prim2time.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

#define	YEAR(y)		((y) >= 100 ? (y) : (y) + 1900)

static long	get_usec (char **, int *);

/*  */

UTC
prim2time (PE pe, int generalized)
{
    int     len;
    char  *cp;
    UTC    u = NULL;
    int	   (*aux) (UTC u, char *cp, int len);
    
    aux = generalized ? str2gent : str2utct;
    switch (pe->pe_form)
    {
    case PE_FORM_PRIM: 
        if (pe->pe_prim == NULL)
        {
            return (UTC)pe_seterr (pe, PE_ERR_PRIM, NULL);
        }
        
        u = (UTC)smalloc(sizeof(UTCtime));
        (*aux) (u, (char *) pe->pe_prim, (int) pe->pe_len);
        break;
        
    case PE_FORM_CONS: 
        if ((cp = prim2str (pe, &len)) == NULL)
        {
            return NULL;
        }

        if (len)
        {
            u = (UTC)smalloc(sizeof(UTCtime));
            (*aux) (u, cp, len);
        }
        free (cp);
        break;
    }
    
    return (u
              ? u
              : (UTC)pe_seterr (pe, generalized
                                 ? PE_ERR_GENT
                                 : PE_ERR_UTCT, NULL));
}

int
str2utct (UTC u, char *cp, int len)
{
    int     year, hours, mins;
    int    zone;
    
    memset ((char *) u, 0, sizeof *u);
    
    if (sscanf (cp, "%2d%2d%2d%2d%2d", &year, &u->ut_mon,
        &u->ut_mday, &u->ut_hour, &u->ut_min) != 5)
    {
        return ITS_EINVALIDARGS;
    }
    
    cp += 10, len -= 10;
    u->ut_year = YEAR (year);
    
    if (len > 0 && isdigit ((ITS_OCTET) *cp))
    {
        if (sscanf (cp, "%2d", &u->ut_sec) != 1)
        {
            return ITS_EINVALIDARGS;
        }
        
        u->ut_flags |= UT_SEC;
        cp += 2, len -= 2;
    }
    
    if (len > 0)
    {
        switch (*cp)
        {
        case 'Z': 
            cp++, len--;
            break;
            
        case '+': 
        case '-': 
            if (sscanf (cp + 1, "%2d%2d", &hours, &mins) != 2)
            {
                return ITS_EINVALIDARGS;
            }
            zone = hours * 60 + mins;
            u->ut_zone = *cp == '+' ? zone : -zone;
            cp += 5, len -= 5;
            break;
            
        default: 
            return ITS_EINVALIDARGS;
        }
        
        u->ut_flags |= UT_ZONE;
    }
    
    if (len != 0)
    {
        return ITS_EINVALIDARGS;
    }
    
    return ITS_SUCCESS;
}

int
str2gent (UTC u, char *cp, int len)
{
    int     hours, mins;
    long    usec;
    int    zone;
    
    memset ((char *) u, 0, sizeof *u);
    
    if (sscanf (cp, "%4d%2d%2d%2d", &u->ut_year, &u->ut_mon,
        &u->ut_mday, &u->ut_hour) != 4)
    {
        return ITS_EINVALIDARGS;
    }
    
    cp += 10, len -= 10;
    
    if (len > 0)
    {
        switch (*cp)
        {
        case '.':
        case ',':
            cp++, len--;
            if ((usec = get_usec (&cp, &len)) < 0)
            {
                return ITS_EINVALIDARGS;
            }
            
            u->ut_min = (u->ut_sec = usec / 1000000) / 60;
            u->ut_sec %= 60;
            u->ut_usec = usec % 1000000;
            u->ut_flags |= UT_SEC | UT_USEC;
            goto get_zone;
            
        default:
            if (isdigit ((ITS_OCTET) *cp))
            {
                if (sscanf (cp, "%2d", &u->ut_min) != 1)
                {
                    return ITS_EINVALIDARGS;
                }
                
                cp += 2, len -= 2;
            }
            break;
        }
    }
    
    if (len > 0)
    {
        switch (*cp)
        {
        case '.':
        case ',':
            cp++, len--;
            if ((usec = get_usec (&cp, &len)) < 0)
            {
                return ITS_EINVALIDARGS;
            }
            
            if ((u->ut_sec = usec / 1000000) >= 60)
            {
                return ITS_EINVALIDARGS;
            }
            u->ut_usec = usec % 1000000;
            u->ut_flags |= UT_SEC | UT_USEC;
            goto get_zone;
            
        default:
            if (isdigit ((ITS_OCTET) *cp))
            {
                if (sscanf (cp, "%2d", &u->ut_sec) != 1)
                {
                    return ITS_EINVALIDARGS;
                }
                u->ut_flags |= UT_SEC;
                cp += 2, len -= 2;
            }
            break;
        }
    }
    
    if (len > 0)
    {
        switch (*cp)
        {
        case '.':
        case ',':
            cp++, len--;
            if ((usec = get_usec (&cp, &len)) < 0)
            {
                return ITS_EINVALIDARGS;
            }
            if ((u->ut_usec = usec) >= 1000000)
            {
                return ITS_EINVALIDARGS;
            }
            u->ut_flags |= UT_USEC;
            goto get_zone;
            
        default:
            break;
        }
    }
    
get_zone:
    if (len > 0)
    {
        switch (*cp)
        {
        case 'Z': 
            cp++, len--;
            break;
            
        case '+': 
        case '-': 
            if (sscanf (cp + 1, "%2d%2d", &hours, &mins) != 2)
            {
                return ITS_EINVALIDARGS;
            }
            
            zone = hours * 60 + mins;
            u->ut_zone = *cp == '+' ? zone : -zone;
            cp += 5, len -= 5;
            break;
            
        default: 
            return ITS_EINVALIDARGS;
        }
        
        u->ut_flags |= UT_ZONE;
    }
    
    if (len != 0)
    {
        return ITS_EINVALIDARGS;
    }
    
    return ITS_SUCCESS;
}

/*
 * not perfect, but what is?
 */
static long
get_usec (char **cp, int *len)
{
    int    j;
    long   i;
    char  *dp;
    
    i = 0L;
    for (dp = *cp, j = 0; isdigit ((ITS_OCTET) *dp); dp++, j++)
    {
        if (j < 6)
        {
            i = i * 10L + (long) (*dp - '0');
        }
    }
    
    *cp = dp, *len -= j;
    
    while (j++ < 6)
    {
        i *= 10L;
    }
    
    return i;
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

