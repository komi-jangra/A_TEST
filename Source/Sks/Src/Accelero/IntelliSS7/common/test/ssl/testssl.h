/*  *********************************************************************
    File: testssl.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: testssl.h    Prototypes for sample client


    ****************************************************************** */

#ifndef _SSLTEST_H_
#define _SSLTEST_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif

SSLErr InitDatabase(const char *filename, void **dbRef);
SSLErr DisposeDatabase(void);
SSLErr SSLAddSession (SSLBuffer sessionKey, SSLBuffer sessionData, void *sessionRef);
SSLErr SSLGetSession (SSLBuffer sessionKey, SSLBuffer *sessionData, void *sessionRef);
SSLErr SSLDeleteSession (SSLBuffer sessionKey, void *sessionRef);

SSLErr SSLAlloc (SSLBuffer *buf, void *allocRef);
SSLErr SSLFree (SSLBuffer *buf, void *allocRef);
SSLErr SSLRealloc (SSLBuffer *buf, uint32 newSize, void *allocRef);
SSLErr SSLRandom(SSLBuffer data, void *randomRef);
SSLErr SeedRandom(void **randomRef);
SSLErr SSLTime(uint32 *time, void *timeRef);
SSLErr SSLConvertTime(uint32 *time, void *timeRef);
SSLErr SocketRead(SSLBuffer buffer, uint32 *processed, void *state);
SSLErr SocketWrite(SSLBuffer buffer, uint32 *processed, void *state);

SSLErr SSLDecodePrivateKey(SSLBuffer privateKey, SSLBuffer password, SSLRSAPrivateKey *rsakey, SSLContext *ctx);

#endif
