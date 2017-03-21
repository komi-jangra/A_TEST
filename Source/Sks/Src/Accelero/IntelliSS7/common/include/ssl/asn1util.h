/*  *********************************************************************
    File: asn1util.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: asn1util.h   Prototypes for functions in asn1util.c


    ****************************************************************** */

#ifndef _ASN1UTIL_H_
#define _ASN1UTIL_H_ 1

#ifndef _ASN1TYPE_H_
#include "asn1type.h"
#endif

ASNErr  ASNParseBER(SSLBuffer ber, ASN1Type *asnList, int *listSize);
ASNErr  ASNCountBERElements(SSLBuffer ber, int *listSize);
ASNErr  ASNDecodeInteger(SSLBuffer data, sint32 *value);
ASNErr  ASNDecodeObjectID(SSLBuffer data, ASN1ObjectID *oid);
ASNErr  ASNDecodeUTCTime(SSLBuffer data, ASNUTCTime *timeResult);


#endif /* _ASN1UTIL_H_ */
