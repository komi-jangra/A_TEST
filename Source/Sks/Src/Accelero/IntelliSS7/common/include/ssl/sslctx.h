/*  *********************************************************************
    File: sslctx.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslctx.h     Internal state of an SSL connection

    Contains the SSLContext structure which encapsulates the state of the
    connection at any time. Whenever SSLREF might have to return (mostly
    when I/O is done), this structure must completely represent the
    connection state

    ****************************************************************** */

#ifndef _SSLCTX_H_
#define _SSLCTX_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif

#ifndef _SSLALLOC_H_
#include "sslalloc.h"
#endif

typedef struct
{   SSLIOFunc           read;
    SSLIOFunc           write;
    void                *ioRef;
} IOContext;

struct SystemContext
{   SSLAllocFunc        alloc;
    SSLFreeFunc         free;
    SSLReallocFunc      realloc;
    void                *allocRef;
    SSLTimeFunc         time;
    SSLConvertTimeFunc  convertTime;
    void                *timeRef;
    SSLRandomFunc       random;
    void                *randomRef;
}; /* typedef lives in ssl.h */

typedef struct
{   SSLAddSessionFunc       addSession;
    SSLGetSessionFunc       getSession;
    SSLDeleteSessionFunc    deleteSession;
    void                    *sessionRef;
} SessionContext;

typedef struct
{   SSLCheckCertificateFunc checkCertFunc;
    void                    *checkCertRef;
} CertificateContext;

#ifndef _CRYPTYPE_H_
#include "cryptype.h"
#endif

typedef struct
{   HashReference       *hash;
    SSLSymmetricCipher  *symCipher;
    void                *symCipherState;
    uint64              sequenceNum;
    uint8               ready;
    uint8               macSecret[MAX_DIGEST_SIZE];
} CipherContext;

#ifndef _SSLHDSHK_H_
#include "sslhdshk.h"
#endif

#ifndef _SSLCRYPT_H_
#include "sslcrypt.h"
#endif

#ifndef _X509TYPE_H_
#include "x509type.h"
#endif

#ifndef _SSLUTIL_H_
#include "sslutil.h"
#endif

typedef struct WaitingRecord
{   struct WaitingRecord    *next;
    SSLBuffer               data;
    uint32                  sent;
} WaitingRecord;

typedef struct DNListElem
{   struct DNListElem   *next;
    SSLBuffer           derDN;
} DNListElem;

struct SSLContext
{   SystemContext       sysCtx;
    IOContext           ioCtx;
    SessionContext      sessionCtx;
    CertificateContext  certCtx;
    
    SSLProtocolVersion  protocolVersion;
    SSLProtocolSide     protocolSide;
    SSLCertificate      *localCert;
    SSLRSAPrivateKey    localKey;
    SSLRSAPrivateKey    exportKey;
    SSLDHParams         dhAnonParams;
    
    SSLBuffer           sessionID;
    
    SSLCertificate      *peerCert;
    SSLRSAPublicKey     peerKey;
    SSLDHParams         peerDHParams;
    SSLBuffer           dhPeerPublic;
    SSLBuffer           dhExchangePublic;
    SSLBuffer           dhPrivate;
    
    SSLBuffer           peerID;
    SSLBuffer           resumableSession;
    
    CipherContext       readCipher;
    CipherContext       writeCipher;
    CipherContext       readPending;
    CipherContext       writePending;
    
    uint16              selectedCipher;
    SSLCipherSpec       *selectedCipherSpec;
    SSLHandshakeState   state;
    
    int                 requestClientCert;
    int                 certRequested;
    int                 certSent;
    int                 certReceived;
    int                 x509Requested;
    DNListElem          *acceptableDNList;
    
    uint8               clientRandom[32];
    uint8               serverRandom[32];
    SSLBuffer           preMasterSecret;
    uint8               masterSecret[48];
    
    SSLBuffer           shaState, md5State;
    
    SSLBuffer           fragmentedMessageCache;
    
    int                 ssl2ChallengeLength;
    int                 ssl2ConnectionIDLength;
    int                 ssl2SessionMatch;
    
/* Record layer fields */
    SSLBuffer           partialReadBuffer;
    uint32              amountRead;
    
/* Transport layer fields */
    WaitingRecord       *recordWriteQueue;
    SSLBuffer           receivedDataBuffer;
    uint32              receivedDataPos;
};

#endif /* _SSLCTX_H_ */
