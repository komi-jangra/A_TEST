/*  *********************************************************************
    File: sslutil.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslutil.h    Utility functions

    These functions get used in message decoding all over the place.

    ****************************************************************** */

#ifndef _SSLUTIL_H_
#define _SSLUTIL_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif

uint32  SSLDecodeInt(unsigned char *p, int length);
unsigned char *SSLEncodeInt(unsigned char *p, uint32 value, int length);
void    IncrementUInt64(uint64 *v);

#define SET_SSL_BUFFER(buf, d, l)   do { (buf).data = (d); (buf).length = (l); } while (0)

#endif
