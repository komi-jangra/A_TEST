/*  *********************************************************************
    File: sslalert.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslalert.h   Alert layer functions and values

    Prototypes for functions in sslalert.c and alert layer equates.

    ****************************************************************** */

#ifndef _SSLALERT_H_
#define _SSLALERT_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif

#ifndef _SSLREC_H_
#include "sslrec.h"
#endif

typedef enum
{   alert_warning = 1,
    alert_fatal = 2
} AlertLevel;

typedef enum
{   alert_close_notify = 0,
    alert_unexpected_message = 10,
    alert_bad_record_mac = 20,
    alert_decompression_failure = 30,
    alert_handshake_failure = 40,
    alert_no_certificate = 41,
    alert_bad_certificate = 42,
    alert_unsupported_certificate = 43,
    alert_certificate_revoked = 44,
    alert_certificate_expired = 45,
    alert_certificate_unknown = 46,
    alert_illegal_parameter = 47
} AlertDescription;

SSLErr SSLProcessAlert(SSLRecord rec, SSLContext *ctx);
SSLErr SSLSendAlert(AlertLevel level, AlertDescription desc, SSLContext *ctx);
SSLErr SSLEncodeAlert(SSLRecord *rec, AlertLevel level, AlertDescription desc, SSLContext *ctx);
SSLErr SSLFatalSessionAlert(AlertDescription desc, SSLContext *ctx);

#endif /* _SSLALERT_H_ */
