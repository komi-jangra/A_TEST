/*  *********************************************************************
    File: sslcrypt.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslcrypt.h   SSL crypto header

    This header includes the relevant headers for a particular crypto
    implementation and also defines some general types which can be used
    in structures, etc., without specifying a particular crypto library.

    ****************************************************************** */

#ifndef _SSLCRYPT_H_
#define _SSLCRYPT_H_

#ifndef RSAREF
#ifndef BSAFE
    #define BSAFE 0
    #define RSAREF 1
#endif /* BSAFE */
#endif /* RSAREF */

#if RSAREF && BSAFE
    
    #error "Please set exactly one of BSAFE or RSAREF"
    
#elif RSAREF
    
    #define BSAFE 0
    #define PROTOTYPES 1
    
    #ifndef _GLOBAL_H_
    #include "global.h"
    #endif
    
    #ifndef _RSAREF_H_
    #include "rsaref.h"
    #endif
    
    #include "rsa.h"        /* Internal RSAREF routines */
    #include "r_random.h"
    
    typedef R_DH_PARAMS SSLDHParams;
    
    typedef R_RSA_PRIVATE_KEY SSLRSAPrivateKey;
    typedef R_RSA_PUBLIC_KEY SSLRSAPublicKey;
    typedef R_RANDOM_STRUCT SSLRandomCtx;
    
#elif BSAFE
    
    #define RSAREF 0
    #define PROTOTYPES 1
    
    #ifndef _GLOBAL_H_
    #include "aglobal.h"
    #endif
    
    #ifndef _BSAFE_H_
    #include "bsafe.h"
    #endif
    
    #include "md5.h"
    
    typedef B_ALGORITHM_OBJ SSLDHParams;
    
    typedef B_KEY_OBJ SSLRSAPrivateKey;
    typedef B_KEY_OBJ SSLRSAPublicKey;
    typedef B_ALGORITHM_OBJ SSLRandomCtx;
    
    #define NO_RAND ((B_ALGORITHM_OBJ)0)
    #define NO_SURR ((A_SURRENDER_CTX*)0)
    
#else
    
    #error "Please set exactly one of BSAFE or RSAREF"
    
#endif /* RSAREF, BSAFE */

#endif /* _SSLCRYPT_H_ */
