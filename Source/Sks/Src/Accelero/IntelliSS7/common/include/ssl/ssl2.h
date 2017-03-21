/*  *********************************************************************
    File: ssl2.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: ssl2.h       SSL 2 functionality header

    This file contains function prototypes and equate values for SSL2.
    The relevant functions are contained in files whose names match
    ssl2*.c

    ****************************************************************** */

#ifndef _SSL2_H_
#define _SSL2_H_

#ifndef _SSL_H_
#include "ssl.h"
#endif

#ifndef _SSLREC_H_
#include "sslrec.h"
#endif

typedef enum
{   ssl2_mt_error = 0,
    ssl2_mt_client_hello = 1,
    ssl2_mt_client_master_key = 2,
    ssl2_mt_client_finished = 3,
    ssl2_mt_server_hello = 4,
    ssl2_mt_server_verify = 5,
    ssl2_mt_server_finished = 6,
    ssl2_mt_request_certificate = 7,
    ssl2_mt_client_certificate = 8,
    ssl2_mt_kickstart_handshake = 99
} SSL2MessageType;

typedef enum
{   ssl2_pe_no_cipher = 1,
    ssl2_pe_no_certificate = 2,
    ssl2_pe_bad_certificate = 4,
    ssl2_pe_unsupported_certificate_type = 6
} SSL2ErrorCode;

typedef enum
{   ssl2_ct_x509_certificate = 1
} SSL2CertTypeCode;

#define SSL2_CONNECTION_ID_LENGTH   16

typedef SSLErr (*EncodeSSL2MessageFunc)(SSLBuffer *msg, SSLContext *ctx);
SSLErr SSL2ReadRecord(SSLRecord *rec, SSLContext *ctx);
SSLErr SSL2WriteRecord(SSLRecord rec, SSLContext *ctx);
SSLErr SSL2ProcessMessage(SSLRecord rec, SSLContext *ctx);
SSLErr SSL2SendError(SSL2ErrorCode error, SSLContext *ctx);
SSLErr SSL2AdvanceHandshake(SSL2MessageType msg, SSLContext *ctx);
SSLErr SSL2PrepareAndQueueMessage(EncodeSSL2MessageFunc encodeFunc, SSLContext *ctx);
SSLErr SSL2CompareSessionIDs(SSLContext *ctx);
SSLErr SSL2InstallSessionKey(SSLContext *ctx);
SSLErr SSL2GenerateSessionID(SSLContext *ctx);
SSLErr SSL2InitCiphers(SSLContext *ctx);

SSLErr SSL2ProcessClientHello(SSLBuffer msgContents, SSLContext *ctx);
SSLErr SSL2EncodeClientHello(SSLBuffer *msg, SSLContext *ctx);
SSLErr SSL2ProcessClientMasterKey(SSLBuffer msgContents, SSLContext *ctx);
SSLErr SSL2EncodeClientMasterKey(SSLBuffer *msg, SSLContext *ctx);
SSLErr SSL2ProcessClientFinished(SSLBuffer msgContents, SSLContext *ctx);
SSLErr SSL2EncodeClientFinished(SSLBuffer *msg, SSLContext *ctx);
SSLErr SSL2ProcessServerHello(SSLBuffer msgContents, SSLContext *ctx);
SSLErr SSL2EncodeServerHello(SSLBuffer *msg, SSLContext *ctx);
SSLErr SSL2ProcessServerVerify(SSLBuffer msgContents, SSLContext *ctx);
SSLErr SSL2EncodeServerVerify(SSLBuffer *msg, SSLContext *ctx);
SSLErr SSL2ProcessServerFinished(SSLBuffer msgContents, SSLContext *ctx);
SSLErr SSL2EncodeServerFinished(SSLBuffer *msg, SSLContext *ctx);

#endif
