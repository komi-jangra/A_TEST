/*  *********************************************************************
    File: x509.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: x509.h       X.509 Prototypes

    Prototypes for functions in x509.c

    ****************************************************************** */

#ifndef _X509_H_
#define _X509_H_ 1

#ifndef _X509TYPE_H_
#include "x509type.h"
#endif

#ifndef _SSLCRYPT_H_
#include "sslcrypt.h"
#endif

#ifndef _SSLALLOC_H_
#include "sslalloc.h"
#endif

ASNErr  ASNParseX509Certificate(SSLBuffer certData, X509Cert *certResult, SSLContext *ctx);
ASNErr  ASNFreeX509Cert(X509Cert *cert, SystemContext *sysCtx);
ASNErr  FreeNameList(X509Name *name, SystemContext *sysCtx);
ASNErr  X509DecodeName(SSLBuffer nameStructure, X509Name *name, SystemContext *sysCtx);
SSLErr  X509VerifySignature(X509Cert *parent, X509Cert *child);
SSLErr  X509ExtractPublicKey(X509PubKey *asnKey, SSLRSAPublicKey *pubKey);
SSLErr  X509CompareNames(X509Name *n1, X509Name *n2);
SSLErr  X509VerifyCertChain(SSLCertificate *chain, SSLContext *ctx);

#endif /* _X509_H_ */
