/*  *********************************************************************
    File: sslsess.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslsess.h    SSL Session Interface

    Prototypes for the SSL session interface functions in sslsess.c.

    ****************************************************************** */

#ifndef _SSLSESS_H_
#define _SSLSESS_H_ 1

#define SSL_SESSION_ID_LEN  16      /* 16 <= SSL_SESSION_ID_LEN <= 32 */

SSLErr SSLAddSessionID(SSLContext *ctx);
SSLErr SSLGetSessionID(SSLBuffer *sessionID, SSLContext *ctx);
SSLErr SSLDeleteSessionID(SSLContext *ctx);
SSLErr SSLRetrieveSessionIDIdentifier(SSLBuffer sessionID, SSLBuffer *identifier, SSLContext *ctx);
SSLErr SSLRetrieveSessionIDProtocolVersion(SSLBuffer sessionID, SSLProtocolVersion *version, SSLContext *ctx);
SSLErr SSLInstallSessionID(SSLBuffer sessionID, SSLContext *ctx);

#endif /* _SSLSESS_H_ */
