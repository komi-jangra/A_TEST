/*  *********************************************************************
    File: sslerrs.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: sslerrs.h    Errors SSLRef can return


    ****************************************************************** */

#ifndef _SSLERRS_H_
#define _SSLERRS_H_ 1

typedef enum
{   SSLNoErr = 0,
    SSLMemoryErr = -7000,
    SSLUnsupportedErr = -6999,
    SSLOverflowErr = -6998,
    SSLUnknownErr = -6997,
    SSLProtocolErr = -6996,
    SSLNegotiationErr = -6995,
    SSLFatalAlert = -6994,
    SSLWouldBlockErr = -6993,
    SSLIOErr = -6992,
    SSLSessionNotFoundErr = -6991,
    
    SSLConnectionClosedGraceful = -6990,
    SSLConnectionClosedError = -6989,
    
    ASNBadEncodingErr = -6988,
    ASNIntegerTooBigErr = -6987,
    
    X509CertChainInvalidErr = -6986,
    X509NamesNotEqualErr = -6985
} SSLErr;

#endif
