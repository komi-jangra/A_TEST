/*  *********************************************************************
    File: privkey.c

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: privkey.c    Extremely primitive implementation of PKCS 5 and 7

    This code is used to load the private key from a binary encoded file
    which contains a PKCS 7 message with a password-protected RSA private
    key in it.

    ****************************************************************** */

#ifndef _ASN1UTIL_H_
#include "asn1util.h"
#endif

#ifndef _SSLCRYPT_H_
#include "sslcrypt.h"
#endif

#ifndef _SSLCTX_H_
#include "sslctx.h"
#endif

#ifndef _SSLALLOC_H_
#include "sslalloc.h"
#endif

#ifndef _CRYPTYPE_H_
#include "cryptype.h"
#endif

#include <string.h>

SSLErr SSLDecodePrivateKey(SSLBuffer privateKey, SSLBuffer password, SSLRSAPrivateKey *rsakey, SSLContext *ctx);
SSLErr SSLParsePrivateKey(SSLBuffer privateKey, SSLRSAPrivateKey *rsakey, SSLContext *ctx);

#if RSAREF

	#include "deseay.h"

	static void SSLCopyIntegerToByteArray(SSLBuffer integer, uint8 *dest, uint32 destLen);

#endif /* RSAREF */

SSLErr
SSLDecodePrivateKey(SSLBuffer privateKey, SSLBuffer password, SSLRSAPrivateKey *rsakey, SSLContext *ctx)
{	SSLErr				err;
	ASN1Type			outer, pkcs7[2], encryptedData[2], encryptionAlg[2],
						desParams[2];
	SSLBuffer			hashCtx, hash1, hash2, privKeyBuf;
	uint8				md5Hash1[16], md5Hash2[16];
	sint32				iterations;
	int 				size;
	
	hash1.data = md5Hash1;
	hash1.length = 16;
	hash2.data = md5Hash2;
	hash2.length = 16;
	size = 1;
	if ((err = ASNParseBER(privateKey, &outer, &size)) != 0)
		return err;
	size = 2;
	if ((err = ASNParseBER(outer.contents, pkcs7, &size)) != 0 || size != 2)
		return err;
	if ((err = ASNParseBER(pkcs7[1].contents, encryptedData, &size)) != 0 || size != 2)
		return err;
	if ((err = ASNParseBER(encryptedData[0].contents, encryptionAlg, &size)) != 0 || size != 2)
		return err;
	if ((err = ASNParseBER(encryptionAlg[1].contents, desParams, &size)) != 0 || size != 2)
		return err;
	if ((err = ASNDecodeInteger(desParams[1].contents, &iterations)) != 0)
		return err;
	if ((err = SSLAllocBuffer(&hashCtx, SSLHashMD5.contextSize, &ctx->sysCtx)) != 0)
		return err;
	if ((err = SSLHashMD5.init(hashCtx)) != 0)
		return err;
	if ((err = SSLHashMD5.update(hashCtx, password)) != 0)
		return err;
	if ((err = SSLHashMD5.update(hashCtx, desParams[0].contents)) != 0)
		return err;
	if ((err = SSLHashMD5.final(hashCtx, hash1)) != 0)
		return err;
	while (--iterations)
	{	if ((err = SSLHashMD5.init(hashCtx)) != 0)
			return err;
		if ((err = SSLHashMD5.update(hashCtx, hash1)) != 0)
			return err;
		if ((err = SSLHashMD5.final(hashCtx, hash2)) != 0)
			return err;
		memcpy(md5Hash1, md5Hash2, 16);
	}
	if ((err = SSLFreeBuffer(&hashCtx, &ctx->sysCtx)) != 0)
		return err;
	
	privKeyBuf = encryptedData[1].contents;
	
#if RSAREF
	{	des_key_schedule	key;
		int 				i, padLength;
		
		des_set_odd_parity((des_cblock*)md5Hash1);
		des_key_sched((des_cblock*)md5Hash1,key);
		des_cbc_encrypt((des_cblock*)privKeyBuf.data,(des_cblock*)privKeyBuf.data,
						privKeyBuf.length,key,(des_cblock*)(md5Hash1+8),0);
		if (privKeyBuf.data[0] != 0x30)
			return SSLUnknownErr;
		
		padLength = privKeyBuf.data[privKeyBuf.length - 1];
		for (i = 2; i <= padLength; i++)
			if (privKeyBuf.data[privKeyBuf.length - i] != padLength)
				return SSLUnknownErr;
		
		privKeyBuf.length -= padLength;
		
		return SSLParsePrivateKey(privKeyBuf, rsakey, ctx);
	}
#elif BSAFE
	{	int 				rsaErr;
		unsigned int		outLen, totalOut;
		B_KEY_OBJ			desKey;
		B_ALGORITHM_OBJ 	des;
		B_ALGORITHM_METHOD	*chooser[] = { &AM_DES_CBC_DECRYPT, 0 };
		
		if ((rsaErr = B_CreateAlgorithmObject(&des)) != 0)
			return SSLUnknownErr;
		if ((rsaErr = B_SetAlgorithmInfo(des, AI_DES_CBCPadIV8, md5Hash1+8)) != 0)
			return SSLUnknownErr;
		if ((rsaErr = B_CreateKeyObject(&desKey)) != 0)
			return SSLUnknownErr;
		if ((rsaErr = B_SetKeyInfo(desKey, KI_DES8, md5Hash1)) != 0)
			return SSLUnknownErr;
		if ((rsaErr = B_DecryptInit(des, desKey, chooser, NO_SURR)) != 0)
			return SSLUnknownErr;
		B_DestroyKeyObject(&desKey);
		if ((rsaErr = B_DecryptUpdate(des, privKeyBuf.data, &outLen, privKeyBuf.length,
					privKeyBuf.data, privKeyBuf.length, NO_RAND, NO_SURR)) != 0)
			return SSLUnknownErr;
		totalOut = outLen;
		if ((rsaErr = B_DecryptFinal(des, privKeyBuf.data+totalOut, &outLen,
					privKeyBuf.length-totalOut, NO_RAND, NO_SURR)) != 0)
			return SSLUnknownErr;
		privKeyBuf.length = totalOut + outLen;
		B_DestroyAlgorithmObject(&des);
		
		return SSLParsePrivateKey(privKeyBuf, rsakey, ctx);
	}
#else
	#error "Neither RSAREF not BSAFE defined"
#endif
}

SSLErr
SSLParsePrivateKey(SSLBuffer privateKey, SSLRSAPrivateKey *key, SSLContext *ctx)
{	SSLErr		err;
	ASN1Type	outer, privKeyInfo[4], rsaKeyOuter, rsaKey[9];
	int 		count;
	
	count = 1;
	if ((err = ASNParseBER(privateKey, &outer, &count)) != 0 || count != 1)
		return err;
	count = 4;
	if ((err = ASNParseBER(outer.contents, privKeyInfo, &count)) != 0 || count < 3)
		return err;
	count = 1;
	if ((err = ASNParseBER(privKeyInfo[2].contents, &rsaKeyOuter, &count)) != 0 || count != 1)
		return err;
	count = 9;
	if ((err = ASNParseBER(rsaKeyOuter.contents, rsaKey, &count)) != 0 || count != 9)
		return err;
	
#if RSAREF
	{	int 		bitAdjust;
		uint8		c;
		
		memset(key, 0, sizeof(R_RSA_PRIVATE_KEY));
		SSLCopyIntegerToByteArray(rsaKey[1].contents, key->modulus, sizeof(key->modulus));
		SSLCopyIntegerToByteArray(rsaKey[2].contents, key->publicExponent, sizeof(key->publicExponent));
		SSLCopyIntegerToByteArray(rsaKey[3].contents, key->exponent, sizeof(key->exponent));
		SSLCopyIntegerToByteArray(rsaKey[4].contents, key->prime[0], sizeof(key->prime[0]));
		SSLCopyIntegerToByteArray(rsaKey[5].contents, key->prime[1], sizeof(key->prime[1]));
		SSLCopyIntegerToByteArray(rsaKey[6].contents, key->primeExponent[0], sizeof(key->primeExponent[0]));
		SSLCopyIntegerToByteArray(rsaKey[7].contents, key->primeExponent[1], sizeof(key->primeExponent[1]));
		SSLCopyIntegerToByteArray(rsaKey[8].contents, key->coefficient, sizeof(key->coefficient));
		
		c = rsaKey[1].contents.data[0];
		
		bitAdjust = 8;
		while (c != 0)
		{	--bitAdjust;
			c >>= 1;
		}
		key->bits = rsaKey[1].contents.length * 8 - bitAdjust;
	}
#elif BSAFE
	{	A_PKCS_RSA_PRIVATE_KEY	privKey;
		int 					rsaErr;
	
#define COPY_SSLBUFFER_TO_ITEM(b,i) i.data = b.data; i.len = b.length;
	
		COPY_SSLBUFFER_TO_ITEM(rsaKey[1].contents, privKey.modulus);
		COPY_SSLBUFFER_TO_ITEM(rsaKey[2].contents, privKey.publicExponent);
		COPY_SSLBUFFER_TO_ITEM(rsaKey[3].contents, privKey.privateExponent);
		COPY_SSLBUFFER_TO_ITEM(rsaKey[4].contents, privKey.prime[0]);
		COPY_SSLBUFFER_TO_ITEM(rsaKey[5].contents, privKey.prime[1]);
		COPY_SSLBUFFER_TO_ITEM(rsaKey[6].contents, privKey.primeExponent[0]);
		COPY_SSLBUFFER_TO_ITEM(rsaKey[7].contents, privKey.primeExponent[1]);
		COPY_SSLBUFFER_TO_ITEM(rsaKey[8].contents, privKey.coefficient);
		
		if ((rsaErr = B_CreateKeyObject(key)) != 0)
			return SSLUnknownErr;
		if ((rsaErr = B_SetKeyInfo(*key, KI_PKCS_RSAPrivate, (POINTER)&privKey)) != 0)
			return SSLUnknownErr;
	}	
#endif
	return SSLNoErr;
}

#if RSAREF
static void
SSLCopyIntegerToByteArray(SSLBuffer integer, uint8 *dest, uint32 destLen)
{	if (integer.data[0] == 0)
		memcpy(dest + destLen - (integer.length - 1), integer.data + 1, integer.length - 1);
	else
		memcpy(dest + destLen - integer.length, integer.data, integer.length);
}
#endif /* RSAREF */
