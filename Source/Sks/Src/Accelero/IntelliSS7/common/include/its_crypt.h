/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/08 22:34:52  mmiers
 * LOG: Add AES for EAP
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:12  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2000/12/29 17:57:39  mmiers
 * LOG: C++ protection
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:11  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/07/27 19:59:15  mmiers
 * LOG:
 * LOG: Move things around so we can publish the license API.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_CRYPT_H
#define ITS_CRYPT_H

#ident "$Id: its_crypt.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#include <its.h>

/*
 * stream crypt
 */
typedef struct ITS_key_t
{
     ITS_OCTET state[256];       
     ITS_OCTET x;        
     ITS_OCTET y;
}
ITS_Key;

/*
 * block crypt mode
 */
typedef enum
{
    BLOCK_MODE_ECB = 1,    /*  Are we ciphering in ECB mode?   */
    BLOCK_MODE_CBC,        /*  Are we ciphering in CBC mode?   */
    BLOCK_MODE_CFB1        /*  Are we ciphering in 1-bit CFB mode? */
}
ITS_BlockMode;

/*
 * block crypt direction
 */
typedef enum
{
    DIR_ENCRYPT,    /*  Are we encrpyting?  */
    DIR_DECRYPT     /*  Are we decrpyting?  */
}
ITS_BlockDir;

/*
 * algorithm specific defines
 */
#define MAXBC           (256/32)
#define MAXKC           (256/32)
#define MAXROUNDS       14
#define	BITSPERBLOCK    128             /* Default number of bits in a cipher block */
#define MAX_KEY_SIZE    64              /* # of ASCII char's needed to represent a key */
#define MAX_IV_SIZE     BITSPERBLOCK/8  /* # bytes needed to represent an IV  */

/*
 * The structure for key information
 */
typedef struct
{
    ITS_BlockDir    direction;	                    /* key used for encrypting or decrypting? */
    int             keyLen;                         /* length of the key  */
    char            keyMaterial[MAX_KEY_SIZE+1];    /* initial key data */
    int             blockLen;                       /* block length */
    ITS_OCTET       keySched[MAXROUNDS+1][4][MAXBC];/* key schedule		*/
}
ITS_BlockKey;

/*
 * The structure for cipher information
 */
typedef struct
{
    ITS_BlockMode   mode;            /* MODE_ECB, MODE_CBC, or MODE_CFB1 */
    ITS_OCTET       IV[MAX_IV_SIZE]; /* A possible Initialization Vector for ciphering */
    int             blockLen;        /* Handles non-128 bit block sizes (if available) */
}
ITS_BlockCipher;

/*
 * secure hash
 */
#define ITS_SHASH_BLOCKSIZE       64
#define ITS_SHASH_DIGESTSIZE      20

typedef struct
{
    ITS_UINT    digest[ITS_SHASH_DIGESTSIZE/sizeof(ITS_UINT)];
    ITS_UINT    count_lo;
    ITS_UINT    count_hi;
    ITS_UINT    data[ITS_SHASH_BLOCKSIZE/sizeof(ITS_UINT)];
}
ITS_SecHashInfo;

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * stream cipher - RC5
 */
ITSDLLAPI void CRYPT_InitKey(ITS_Key *key, ITS_OCTET *keydat, ITS_UINT keylen);
ITSDLLAPI void CRYPT_Encrypt(ITS_Key *key, ITS_OCTET *bptr, ITS_UINT blen);
ITSDLLAPI void CRYPT_Decrypt(ITS_Key *key, ITS_OCTET *bptr, ITS_UINT blen);

/*
 * block cipher - AES
 */
ITSDLLAPI int  AES_MakeKey(ITS_BlockKey *key, ITS_BlockDir direction,
                           int keyLen, char *keyMaterial);
ITSDLLAPI int  AES_CipherInit(ITS_BlockCipher *cipher, ITS_BlockMode mode,
                              char *IV);

ITSDLLAPI int  AES_BlockEncrypt(ITS_BlockCipher *cipher, ITS_BlockKey *key,
                                ITS_OCTET *input, int inputLen,
                                ITS_OCTET *outBuffer);
ITSDLLAPI int  AES_BlockDecrypt(ITS_BlockCipher *cipher, ITS_BlockKey *key,
                                ITS_OCTET *input, int inputLen,
                                ITS_OCTET *outBuffer);
ITSDLLAPI int  AES_CipherUpdateRounds(ITS_BlockCipher *cipher, ITS_BlockKey *key,
                                      ITS_OCTET *input, int inputLen,
                                      ITS_OCTET *outBuffer, int rounds);

/*
 * secure one-way hash - SHA/1
 */
ITSDLLAPI void SECHASH_Init(ITS_SecHashInfo *);
ITSDLLAPI void SECHASH_Update(ITS_SecHashInfo *, ITS_OCTET *, ITS_UINT);
ITSDLLAPI void SECHASH_Final(ITS_SecHashInfo *);

ITSDLLAPI void HMAC_Hash(ITS_OCTET *text, ITS_UINT textLen,
                         ITS_OCTET *key, ITS_UINT keyLen,
                         ITS_OCTET *digest, ITS_UINT digestLen);

#ifdef __cplusplus
}
#endif

#endif /* ITS_CRYPT_H */
