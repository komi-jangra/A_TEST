/*  *********************************************************************
    File: sslhdshk.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslhdshk.h   SSL Handshake Layer

    Prototypes, values, and types for the SSL handshake state machine and
    handshake decoding routines.

    ****************************************************************** */

#ifndef _SSLHDSHK_H_
#define _SSLHDSHK_H_ 72

#ifndef _SSL_H_
#include "ssl.h"
#endif

#ifndef _CRYPTYPE_H_
#include "cryptype.h"
#endif

#ifndef _SSLREC_H_
#include "sslrec.h"
#endif

typedef enum
{   SSL_hello_request = 0,
    SSL_client_hello = 1,
    SSL_server_hello = 2,
    SSL_certificate = 11,
    SSL_server_key_exchange = 12,
    SSL_certificate_request = 13,
    SSL_server_hello_done = 14,
    SSL_certificate_verify = 15,
    SSL_client_key_exchange = 16,
    SSL_finished = 20,
    SSL_MAGIC_no_certificate_alert = 100
} SSLHandshakeType;

typedef enum
{   SSL_read,
    SSL_write
} CipherSide;

typedef enum
{   SSLUninitialized,
    SSLGracefulClose,
    SSLErrorClose,
    HandshakeServerIdle,                /* No handshake underway; server side */
    HandshakeClientIdle,                /* No handshake underway; client side */
    HandshakeServerHello,               /* must get server hello; client hello sent */
    HandshakeServerHelloUnknownVersion, /* Could get SSL 2 or SSL 3 server hello back */
    HandshakeKeyExchange,               /* must get key exchange; cipher spec requires it */
    HandshakeCertificate,               /* may get certificate or certificate request (if no cert request received yet) */
    HandshakeHelloDone,                 /* must get server hello done; after key exchange or fixed DH parameters */
    HandshakeClientCertificate,         /* must get certificate or no cert alert from client */
    HandshakeClientKeyExchange,         /* must get client key exchange */
    HandshakeClientCertVerify,          /* must get certificate verify from client */
    HandshakeChangeCipherSpec,          /* time to change the cipher spec */
    HandshakeFinished,                  /* must get a finished message in the new cipher spec */
    HandshakeSSL2ClientMasterKey,
    HandshakeSSL2ClientFinished,
    HandshakeSSL2ServerHello,
    HandshakeSSL2ServerVerify,
    HandshakeSSL2ServerFinished
} SSLHandshakeState;
    
typedef struct
{   SSLHandshakeType    type;
    SSLBuffer           contents;
} SSLHandshakeMsg;

#define SSL_Finished_Sender_Server  0x53525652
#define SSL_Finished_Sender_Client  0x434C4E54

/** sslhdshk.c **/
typedef SSLErr (*EncodeMessageFunc)(SSLRecord *rec, SSLContext *ctx);
SSLErr SSLProcessHandshakeRecord(SSLRecord rec, SSLContext *ctx);
SSLErr SSLPrepareAndQueueMessage(EncodeMessageFunc msgFunc, SSLContext *ctx);
SSLErr SSLAdvanceHandshake(SSLHandshakeType processed, SSLContext *ctx);
SSLErr SSL3ReceiveSSL2ClientHello(SSLRecord rec, SSLContext *ctx);

/** hdskchgc.c **/
SSLErr SSLEncodeChangeCipherSpec(SSLRecord *rec, SSLContext *ctx);
SSLErr SSLProcessChangeCipherSpec(SSLRecord rec, SSLContext *ctx);
SSLErr SSLDisposeCipherSuite(CipherContext *cipher, SSLContext *ctx);

/** hdskcert.c **/
SSLErr SSLEncodeCertificate(SSLRecord *certificate, SSLContext *ctx);
SSLErr SSLProcessCertificate(SSLBuffer message, SSLContext *ctx);
SSLErr SSLEncodeCertificateRequest(SSLRecord *request, SSLContext *ctx);
SSLErr SSLProcessCertificateRequest(SSLBuffer message, SSLContext *ctx);
SSLErr SSLEncodeCertificateVerify(SSLRecord *verify, SSLContext *ctx);
SSLErr SSLProcessCertificateVerify(SSLBuffer message, SSLContext *ctx);

/** hdskhelo.c **/
SSLErr SSLEncodeServerHello(SSLRecord *serverHello, SSLContext *ctx);
SSLErr SSLProcessServerHello(SSLBuffer message, SSLContext *ctx);
SSLErr SSLEncodeClientHello(SSLRecord *clientHello, SSLContext *ctx);
SSLErr SSLProcessClientHello(SSLBuffer message, SSLContext *ctx);
SSLErr SSLInitMessageHashes(SSLContext *ctx);

/** hdskkyex.c **/
SSLErr SSLEncodeServerKeyExchange(SSLRecord *keyExch, SSLContext *ctx);
SSLErr SSLProcessServerKeyExchange(SSLBuffer message, SSLContext *ctx);
SSLErr SSLEncodeKeyExchange(SSLRecord *keyExchange, SSLContext *ctx);
SSLErr SSLProcessKeyExchange(SSLBuffer keyExchange, SSLContext *ctx);

/** hdskfini.c **/
SSLErr SSLEncodeFinishedMessage(SSLRecord *finished, SSLContext *ctx);
SSLErr SSLProcessFinished(SSLBuffer message, SSLContext *ctx);
SSLErr SSLEncodeServerHelloDone(SSLRecord *helloDone, SSLContext *ctx);
SSLErr SSLProcessServerHelloDone(SSLBuffer message, SSLContext *ctx);
SSLErr SSLCalculateFinishedMessage(SSLBuffer finished, SSLBuffer shaMsgState, SSLBuffer md5MsgState, uint32 senderID, SSLContext *ctx);

/** hdskkeys.c **/
SSLErr SSLEncodeRSAPremasterSecret(SSLContext *ctx);
SSLErr SSLEncodeDHPremasterSecret(SSLContext *ctx);
SSLErr SSLCalculateMasterSecret(SSLContext *ctx);
SSLErr SSLInitPendingCiphers(SSLContext *ctx);
SSLErr ReadyRandom(SSLRandomCtx *rsaRandom, SSLContext *ctx);


#endif /* _SSLHDSHK_H_ */
