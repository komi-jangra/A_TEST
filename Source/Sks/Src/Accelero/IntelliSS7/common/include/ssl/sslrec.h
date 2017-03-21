/*  *********************************************************************
    File: sslrec.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslrec.h     SSL Record Layer

    Prototypes, values, and types for the SSL record layer.

    ****************************************************************** */

#ifndef _SSLREC_H_
#define _SSLREC_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif /* _SSL_H_ */

enum
{   SSL_version_2_0_record,
    SSL_smallest_3_0_type = 20,
    SSL_change_cipher_spec = 20,
    SSL_alert = 21,
    SSL_handshake = 22,
    SSL_application_data = 23,
    SSL_largest_3_0_type = 23
};

typedef struct
{   uint8                   contentType;
    SSLProtocolVersion      protocolVersion;
    SSLBuffer               contents;
} SSLRecord;

#define MAX_RECORD_LENGTH   16300   /* Slightly smaller that 16384 to make room for a MAC in an SSL 2.0 3-byte header record */

#define DEFAULT_BUFFER_SIZE 4096

SSLErr  SSLReadRecord(SSLRecord *rec, SSLContext *ctx);
SSLErr  SSLWriteRecord(SSLRecord rec, SSLContext *ctx);

#endif /* _SSLREC_H_ */
