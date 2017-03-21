/*  *********************************************************************
    File: testutil.c

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: testutil.c   Test client callbacks

    Callback functions for system functionality including allocation,
    random, and time.

    ****************************************************************** */


#include "testssl.h"
#include <stdlib.h>
#include <time.h>
#include "sslcrypt.h"

SSLErr
SSLAlloc(SSLBuffer *buf, void *allocRef)
{   buf->data = malloc(buf->length);
    if (!buf->data)
        return SSLMemoryErr;
    return SSLNoErr;
}

SSLErr
SSLFree(SSLBuffer *buf, void *allocRef)
{   free(buf->data);
    buf->data = 0;
    return SSLNoErr;
}

SSLErr
SSLRealloc(SSLBuffer *buf, uint32 newSize, void *allocRef)
{   unsigned char   *newData;
    newData = realloc(buf->data, newSize);
    if (!newData)
        return SSLMemoryErr;
    buf->data = newData;
    return SSLNoErr;
}

SSLErr
SSLRandom(SSLBuffer data, void *randomRef)
{   int                 result;
#if RSAREF
    R_RANDOM_STRUCT     *rsaRandom = (R_RANDOM_STRUCT*)randomRef;
    
    ASSERT(randomRef != 0);
    if ((result = R_GenerateBytes(data.data, data.length, rsaRandom)) != 0)
        return ERR(SSLUnknownErr);
#elif BSAFE
    B_ALGORITHM_OBJ random = (B_ALGORITHM_OBJ)randomRef;

    if ((result = B_GenerateRandomBytes(random, data.data, data.length, (A_SURRENDER_CTX*)NULL_PTR)) != 0)
        return ERR(SSLUnknownErr);
#endif /* BSAFE / RSAREF */
    return SSLNoErr;
}

/* Seed the random number generator with the time. This is an
 *  extremely bad way to seed a secure random number generator
 *  and basically sacrifices all security, but suffices for
 *  an implementation example. In other words, CHANGE THIS!
 */

SSLErr
SeedRandom(void **randomRef)
{   time_t                  t;
    int                     rsaResult;
#if RSAREF
    unsigned int            bytesNeeded;
    static R_RANDOM_STRUCT  rsaRandom;
    
    *randomRef = 0;
    t = time(0);
    
    if (R_RandomInit(&rsaRandom) != 0)
        return ERR(SSLUnknownErr);
    if (R_GetRandomBytesNeeded(&bytesNeeded, &rsaRandom) != 0)
        return ERR(SSLUnknownErr);
    
    while (bytesNeeded > 0)
    {   if ((rsaResult = R_RandomUpdate(&rsaRandom, (unsigned char*)&t, sizeof(time_t))) != 0)
            return ERR(SSLUnknownErr);
        
        if (bytesNeeded >= sizeof(time_t))
            bytesNeeded -= sizeof(time_t);
        else
            bytesNeeded = 0;
    }
    
    *randomRef = &rsaRandom;
#elif BSAFE
    static B_ALGORITHM_OBJ  random;
    B_ALGORITHM_METHOD      *chooser[] = { &AM_MD5_RANDOM, 0 };
    
    if ((rsaResult = B_CreateAlgorithmObject(&random)) != 0)
        return ERR(SSLUnknownErr);
    if ((rsaResult = B_SetAlgorithmInfo(random, AI_MD5Random, 0)) != 0)
        return ERR(SSLUnknownErr);
    if ((rsaResult = B_RandomInit(random, chooser, NO_SURR)) != 0)
        return ERR(SSLUnknownErr);
    
    t = time(0);
    
    if ((rsaResult = B_RandomUpdate(random, (unsigned char*)&t, sizeof(t), NO_SURR)) != 0)
        return ERR(SSLUnknownErr);
    
    *randomRef = &random;
#endif /* BSAFE / RSAREF */
    return SSLNoErr;
}

#define MAC_UNIX_TIME_DIFFERENCE    2082844800

SSLErr
SSLTime(uint32 *timeResult, void *timeRef)
{   time_t  t;
    t = time(0);
#if MAC
    *timeResult = t - MAC_UNIX_TIME_DIFFERENCE;
#else
    *timeResult = t;
#endif
    return SSLNoErr;
}
SSLErr
SSLConvertTime(uint32 *time, void *timeRef)
{
#if MAC
    *time -= MAC_UNIX_TIME_DIFFERENCE;
#endif
    return SSLNoErr;
}
