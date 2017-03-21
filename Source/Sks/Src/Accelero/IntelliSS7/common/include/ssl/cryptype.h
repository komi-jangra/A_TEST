/*  *********************************************************************
    File: cryptype.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: cryptype.h   Crypto structures and routines

    Types associated with cryptographic functionality, including hashes,
    symmetric ciphers, and cipher specs.

    ****************************************************************** */

#ifndef _CRYPTYPE_H_
#define _CRYPTYPE_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif /* _SSL_H_ */

#ifndef _ASN1TYPE_H_
#include "asn1type.h"
#endif /* _ASN1TYPE_H_ */

typedef enum
{   SSL_NULL_WITH_NULL_NULL =                   0x0000,
    SSL_RSA_WITH_NULL_MD5 =                     0x0001,
    SSL_RSA_WITH_NULL_SHA =                     0x0002,
    SSL_RSA_EXPORT_WITH_RC4_40_MD5 =            0x0003,
    SSL_RSA_WITH_RC4_128_MD5 =                  0x0004,
    SSL_RSA_WITH_RC4_128_SHA =                  0x0005,
    SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5 =        0x0006,
    SSL_RSA_WITH_IDEA_CBC_SHA =                 0x0007,
    SSL_RSA_EXPORT_WITH_DES40_CBC_SHA =         0x0008,
    SSL_RSA_WITH_DES_CBC_SHA =                  0x0009,
    SSL_RSA_WITH_3DES_EDE_CBC_SHA =             0x000A,
    SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA =      0x000B,
    SSL_DH_DSS_WITH_DES_CBC_SHA =               0x000C,
    SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA =          0x000D,
    SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA =      0x000E,
    SSL_DH_RSA_WITH_DES_CBC_SHA =               0x000F,
    SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA =          0x0010,
    SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA =     0x0011,
    SSL_DHE_DSS_WITH_DES_CBC_SHA =              0x0012,
    SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA =         0x0013,
    SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA =     0x0014,
    SSL_DHE_RSA_WITH_DES_CBC_SHA =              0x0015,
    SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA =         0x0016,
    SSL_DH_anon_EXPORT_WITH_RC4_40_MD5 =        0x0017,
    SSL_DH_anon_WITH_RC4_128_MD5 =              0x0018,
    SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA =     0x0019,
    SSL_DH_anon_WITH_DES_CBC_SHA =              0x001A,
    SSL_DH_anon_WITH_3DES_EDE_CBC_SHA =         0x001B,
    SSL_FORTEZZA_DMS_WITH_NULL_SHA =            0x001C,
    SSL_FORTEZZA_DMS_WITH_FORTEZZA_CBC_SHA =    0x001D,
    SSL_RSA_WITH_RC2_CBC_MD5 =                  0xFF80,     /* These are included to provide tags for */
    SSL_RSA_WITH_IDEA_CBC_MD5 =                 0xFF81,     /*  SSL 2 cipher kinds which are not specified */
    SSL_RSA_WITH_DES_CBC_MD5 =                  0xFF82,     /*  for SSL 3 */
    SSL_RSA_WITH_3DES_EDE_CBC_MD5 =             0xFF83,
    SSL_NO_SUCH_CIPHERSUITE =                   0xFFFF
} CipherSuite;

typedef enum
{   SSL2_RC4_128_WITH_MD5 =                 0x010080,
    SSL2_RC4_128_EXPORT_40_WITH_MD5 =       0x020080,
    SSL2_RC2_128_CBC_WITH_MD5 =             0x030080,
    SSL2_RC2_128_CBC_EXPORT40_WITH_MD5 =    0x040080,
    SSL2_IDEA_128_CBC_WITH_MD5 =            0x050080,
    SSL2_DES_64_CBC_WITH_MD5 =              0x060040,
    SSL2_DES_192_EDE3_CBC_WITH_MD5 =        0x0700C0
} SSL2CipherKind;

typedef struct
{   SSL2CipherKind  cipherKind;
    CipherSuite     cipherSuite;
} SSLCipherMapping;

typedef SSLErr (*HashInit)(SSLBuffer digestCtx);
typedef SSLErr (*HashUpdate)(SSLBuffer digestCtx, SSLBuffer data);
typedef SSLErr (*HashFinal)(SSLBuffer digestCtx, SSLBuffer digest);
typedef SSLErr (*HashClone)(SSLBuffer src, SSLBuffer dest);

typedef struct
{   uint32      contextSize;
    uint32      digestSize;
    uint32      macPadSize;
    HashInit    init;
    HashUpdate  update;
    HashFinal   final;
    HashClone   clone;
} HashReference;

extern HashReference SSLHashNull;
extern HashReference SSLHashMD5;
extern HashReference SSLHashSHA1;

typedef SSLErr (*SSLKeyFunc)(uint8 *key, uint8 *iv, void **cipherRef, SSLContext *ctx);
typedef SSLErr (*SSLCryptFunc)(SSLBuffer src, SSLBuffer dest, void *cipherRef, SSLContext *ctx);
typedef SSLErr (*SSLFinishFunc)(void *cipherRef, SSLContext *ctx);

typedef enum
{   NotExportable = 0,
    Exportable = 1
} Exportability;

typedef struct {
    uint8           keySize;            /* Sizes are in bytes */
    uint8           secretKeySize;
    uint8           ivSize;
    uint8           blockSize;
    SSLKeyFunc      initialize;
    SSLCryptFunc    encrypt;
    SSLCryptFunc    decrypt;
    SSLFinishFunc   finish;
} SSLSymmetricCipher;

#define MAX_DIGEST_SIZE 20          /* SHA digest size = 160 bits */
#define MAX_MAC_PADDING 48          /* MD5 MAC padding size = 48 bytes */
#define MASTER_SECRET_LEN 48        /* master secret = 3 x MD5 hashes concatenated */

typedef enum
{   SSL_NULL_auth,
    SSL_RSA,
    SSL_RSA_EXPORT,
    SSL_DH_DSS,
    SSL_DH_DSS_EXPORT,
    SSL_DH_RSA,
    SSL_DH_RSA_EXPORT,
    SSL_DHE_DSS,
    SSL_DHE_DSS_EXPORT,
    SSL_DHE_RSA,
    SSL_DHE_RSA_EXPORT,
    SSL_DH_anon,
    SSL_DH_anon_EXPORT,
    SSL_Fortezza
} KeyExchangeMethod;

typedef struct {
    CipherSuite         cipherSpec;
    Exportability       isExportable;
    KeyExchangeMethod   keyExchangeMethod;
    HashReference       *macAlgorithm;
    SSLSymmetricCipher  *cipher;
} SSLCipherSpec;

extern SSLCipherSpec KnownCipherSpecs[];
extern int CipherSpecCount;
extern SSLCipherMapping SSL2CipherMap[];
extern int SSL2CipherMapCount;
extern SSLCipherSpec SSL_NULL_WITH_NULL_NULL_CipherSpec;
extern uint8 SSLMACPad1[], SSLMACPad2[];

void    SSLInitMACPads(void);
SSLErr  ReadyHash(HashReference *ref, SSLBuffer *state, SSLContext *ctx);
SSLErr  CloneHashState(HashReference *ref, SSLBuffer state, SSLBuffer *newState, SSLContext *ctx);
SSLErr  FindCipherSpec(uint16 specID, SSLCipherSpec* *spec);

#endif /* _CRYPTYPE_H_ */
