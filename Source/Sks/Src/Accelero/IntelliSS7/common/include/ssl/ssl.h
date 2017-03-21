/*  *********************************************************************
    File: ssl.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: ssl.h        Main header for use of SSLRef 3.0

    This file should be the only one directly included by the SSLRef
    client; all data structures and routines not found in here or in the
    headers this includes are private and not for use by clients.

    ****************************************************************** */

#ifndef _SSL_H_
#define _SSL_H_

#if !defined(MAC) && !defined(WIN32) && !defined(UNIX)
#define MAC 1
#endif

#ifndef _SSLERRS_H_
#include "sslerrs.h"
#endif

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef signed long         sint32;
typedef struct
{   uint32  high;
    uint32  low;
}                           uint64;

#ifndef _SSLDEBUG_H_
#include "ssldebug.h"
#endif

typedef struct
{   uint32  length;
    uint8   *data;
} SSLBuffer;

typedef enum
{   SSL_ServerSide = 1,
    SSL_ClientSide = 2
} SSLProtocolSide;

typedef enum
{   SSL_Version_Undetermined = 0,
    SSL_Version_3_0_With_2_0_Hello = 100,
    SSL_Version_3_0_Only = 101,
    SSL_Version_2_0 = 0x0002,
    SSL_Version_3_0 = 0x0300
} SSLProtocolVersion;

struct                      SSLContext;
typedef struct SSLContext   SSLContext;

#ifndef _SSLCRYPT_H_
#include "sslcrypt.h"
#endif

/* User provided functions */
typedef SSLErr (*SSLAllocFunc) (SSLBuffer *buf, void *allocRef);
typedef SSLErr (*SSLFreeFunc) (SSLBuffer *buf, void *allocRef);
typedef SSLErr (*SSLReallocFunc) (SSLBuffer *buf, uint32 newSize, void *allocRef);
typedef SSLErr (*SSLIOFunc) (SSLBuffer data, uint32 *processed, void *connRef);
typedef SSLErr (*SSLRandomFunc) (SSLBuffer data, void *randomRef);
typedef SSLErr (*SSLTimeFunc) (uint32 *time, void *timeRef);
typedef SSLErr (*SSLConvertTimeFunc) (uint32 *time, void *timeRef);
typedef SSLErr (*SSLAddSessionFunc) (SSLBuffer sessionKey, SSLBuffer sessionData, void *sessionRef);
typedef SSLErr (*SSLGetSessionFunc) (SSLBuffer sessionKey, SSLBuffer *sessionData, void *sessionRef);
typedef SSLErr (*SSLDeleteSessionFunc) (SSLBuffer sessionKey, void *sessionRef);
typedef SSLErr (*SSLCheckCertificateFunc) (int certCount, SSLBuffer *derCerts, void *checkCertificateRef);

/* SSLREF API */
/* Context creation & deletion APIs */
uint32 SSLContextSize(void);
SSLErr SSLInitContext(SSLContext *ctx);
SSLErr SSLDeleteContext(SSLContext *ctx);
SSLErr SSLDuplicateContext(SSLContext *src, SSLContext *dest, void *ioRef);

/* Connection configuration APIs */
SSLErr SSLSetProtocolSide(SSLContext *ctx, SSLProtocolSide side);
SSLErr SSLSetProtocolVersion(SSLContext *ctx, SSLProtocolVersion version);
SSLErr SSLSetPrivateKey(SSLContext *ctx, SSLRSAPrivateKey *privKey);
SSLErr SSLSetExportPrivateKey(SSLContext *ctx, SSLRSAPrivateKey *privKey);
SSLErr SSLSetDHAnonParams(SSLContext *ctx, SSLDHParams *dhAnonParams);
SSLErr SSLSetRequestClientCert(SSLContext *ctx, int requestClientCert);
SSLErr SSLAddCertificate(SSLContext *ctx, SSLBuffer derCert, int parent, int complete);
SSLErr SSLAddDistinguishedName(SSLContext *ctx, SSLBuffer derDN);
SSLErr SSLSetPeerID(SSLContext *ctx, SSLBuffer peerID);

/* Context configuration APIs */
SSLErr SSLSetAllocFunc(SSLContext *ctx, SSLAllocFunc alloc);
SSLErr SSLSetFreeFunc(SSLContext *ctx, SSLFreeFunc free);
SSLErr SSLSetReallocFunc(SSLContext *ctx, SSLReallocFunc realloc);
SSLErr SSLSetAllocRef(SSLContext *ctx, void* allocRef);
SSLErr SSLSetTimeFunc(SSLContext *ctx, SSLTimeFunc time);
SSLErr SSLSetConvertTimeFunc(SSLContext *ctx, SSLConvertTimeFunc convertTime);
SSLErr SSLSetTimeRef(SSLContext *ctx, void* timeRef);
SSLErr SSLSetRandomFunc(SSLContext *ctx, SSLRandomFunc random);
SSLErr SSLSetRandomRef(SSLContext *ctx, void* randomRef);
SSLErr SSLSetReadFunc(SSLContext *ctx, SSLIOFunc read);
SSLErr SSLSetWriteFunc(SSLContext *ctx, SSLIOFunc write);
SSLErr SSLSetIORef(SSLContext *ctx, void *ioRef);
SSLErr SSLSetAddSessionFunc(SSLContext *ctx, SSLAddSessionFunc addSession);
SSLErr SSLSetGetSessionFunc(SSLContext *ctx, SSLGetSessionFunc getSession);
SSLErr SSLSetDeleteSessionFunc(SSLContext *ctx, SSLDeleteSessionFunc deleteSession);
SSLErr SSLSetSessionRef(SSLContext *ctx, void *sessionRef);
SSLErr SSLSetCheckCertificateFunc(SSLContext *ctx, SSLCheckCertificateFunc checkCertificate);
SSLErr SSLSetCheckCertificateRef(SSLContext *ctx, void *checkCertificateRef);

/* Context access APIs */
SSLErr SSLGetProtocolVersion(SSLContext *ctx, SSLProtocolVersion *version);
SSLErr SSLGetPeerCertificateChainLength(SSLContext *ctx, int *chainLen);
SSLErr SSLGetPeerCertificate(SSLContext *ctx, int index, SSLBuffer *derCert);
SSLErr SSLGetNegotiatedCipher(SSLContext *ctx, uint16 *cipherSuite);
SSLErr SSLGetWritePendingSize(SSLContext *ctx, uint32 *waitingBytes);
SSLErr SSLGetReadPendingSize(SSLContext *ctx, uint32 *waitingBytes);

/* I/O APIs */
SSLErr SSLHandshake(SSLContext *ctx);
SSLErr SSLServiceWriteQueue(SSLContext *ctx);
SSLErr SSLWrite(void *data, uint32 *length, SSLContext *ctx);
SSLErr SSLRead(void *data, uint32 *length, SSLContext *ctx);
SSLErr SSLClose(SSLContext *ctx);

#endif /* _SSL_H_ */
