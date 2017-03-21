/*  *********************************************************************
    File: asn1type.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: asn1type.h   Types and values for ASN.1 decoding functions


    ****************************************************************** */

#ifndef _ASN1TYPE_H_
#define _ASN1TYPE_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif /* _SSL_H_ */

#ifndef _ASN1OIDS_H_
#include "asn1oids.h"
#endif /* _ASN1OIDS_H_ */

typedef struct
{   uint8       identifier;
    SSLBuffer   contents;
} ASN1Type;

typedef struct
{   ASN1OIDValue    oidValue;   /* can be initialized to constant for various known object IDs */
    SSLBuffer       objectID;   /* actual OID */
} ASN1ObjectID;

typedef SSLErr  ASNErr;
typedef uint32  ASNUTCTime;
#define ASN_CLASS_MASK      0xC0    /* class is top two bits of identifier */
#define ASN_UNIVERSAL           0x00    /*  00 */
#define ASN_APPLICATION         0x40    /*  01 */
#define ASN_CONTEXT_SPECIFIC    0x80    /*  10 */
#define ASN_PRIVATE             0xC0    /*  11 */
#define ASN_CONSTRUCTED     0x20    /* constructed is bit 6 */
#define ASN_TAG_MASK        0x1F    /* low 5 bits */

enum
{   ASN_INTEGER = 2,
    ASN_BIT_STRING = 3,
    ASN_OCTET_STRING = 4,
    ASN_NULL = 5,
    ASN_OBJECT_IDENTIFIER = 6,
    ASN_SEQUENCE = 16,
    ASN_SEQUENCE_OF = 16,
    ASN_SET = 17,
    ASN_SET_OF = 17,
    ASN_PrintableString = 19,
    ASN_T61String = 20,
    ASN_IA5String = 22,
    ASN_UTCTime = 23
};

#endif /* _ASN1TYPE_H_ */
