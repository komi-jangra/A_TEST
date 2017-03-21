/*  *********************************************************************
    File: x509type.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: x509type.h   X.509 Types

    Types which support a structural description of an X.509 Certificate.

    ****************************************************************** */

#ifndef _X509TYPE_H_
#define _X509TYPE_H_ 91

#ifndef _ASN1TYPE_H_
#include "asn1type.h"
#endif

typedef struct
{   ASN1ObjectID    algorithm;
    ASN1Type        parameters;
} X509AlgID;

typedef struct X509AVA
{   struct X509AVA      *next;
    ASN1ObjectID        type;
    ASN1Type            value;
} X509AVA;

typedef struct X509RDName
{   struct X509RDName   *next;
    uint32              avaCount;
    X509AVA             *avaList;
} X509RDName;

typedef struct
{   uint32      rdNameCount;
    X509RDName  *rdNameList;
} X509Name;

typedef struct
{   X509AlgID       algorithm;
    SSLBuffer       publicKey;
} X509PubKey;

typedef struct X509Extension
{   struct X509Extension    *next;
    ASN1ObjectID            id;
    uint8                   critical;
    SSLBuffer               contents;
} X509Extension;

typedef struct
{   sint32          version;
    SSLBuffer       serialNumber;
    X509AlgID       algorithm;
    X509Name        issuer;
    ASNUTCTime      startTime;
    ASNUTCTime      endTime;
    X509Name        subject;
    X509PubKey      pubKey;
    SSLBuffer       issuerUniqueID;
    SSLBuffer       subjectUniqueID;
    X509Extension   *extensions;
    SSLBuffer       signedData;
    X509AlgID       sigAlgorithm;
    SSLBuffer       signature;
} X509Cert;

typedef struct SSLCertificate
{   struct SSLCertificate   *next;
    SSLBuffer               derCert;
    X509Cert                cert;
} SSLCertificate;

#endif /* _X509TYPE_H_*/
