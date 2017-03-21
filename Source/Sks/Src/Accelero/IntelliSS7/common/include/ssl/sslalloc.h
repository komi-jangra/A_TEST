/*  *********************************************************************
    File: sslalloc.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslalloc.h   Allocation shell routines

    These routines wrap the user-supplied callbacks to provide allocation
    functionality.

    ****************************************************************** */

#ifndef _SSLALLOC_H_
#define _SSLALLOC_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif

struct SystemContext;
typedef struct SystemContext SystemContext;

SSLErr SSLAllocBuffer(SSLBuffer *buf, uint32 length, SystemContext *ctx);
SSLErr SSLFreeBuffer(SSLBuffer *buf, SystemContext *ctx);
SSLErr SSLReallocBuffer(SSLBuffer *buf, uint32 newSize, SystemContext *ctx);

#endif
