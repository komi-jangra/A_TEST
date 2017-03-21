/*  *********************************************************************
    File: asn1oids.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: asn1oids.h   ASN OID symbolic values

    Symbolic values for the Object Identifiers defined in asn1oids.c

    ****************************************************************** */

#ifndef _ASN1OIDS_H_
#define _ASN1OIDS_H_ 1

typedef enum
{   OID_noMatch = 0,
    OID_md2,
    OID_md4,
    OID_md5,
    OID_rsaEncryption,
    OID_md2WithRSA,
    OID_md4WithRSA,
    OID_md5WithRSA,
    OID_dhKeyAgreement,
    OID_pbeWithMD2AndDES_CBC,
    OID_pbeWithMD5AndDES_CBC,
    OID_emailAddress,
    OID_unstructuredName,
    OID_contentType,
    OID_messageDigest,
    OID_signingTime,
    OID_counterSignature,
    OID_challengePassword,
    OID_unstructuredAddress,
    OID_extendedCertificateAttributes,
    OID_commonName,
    OID_surName,
    OID_serialNumber,
    OID_countryName,
    OID_localityName,
    OID_stateProvinceName,
    OID_streetAddress,
    OID_organizationName,
    OID_organizationalUnitName,
    OID_title,
    OID_description,
    OID_businessCategory,
    OID_postalAddress,
    OID_postalCode,
    OID_postOfficeBox,
    OID_physicalDeliveryOfficeName,
    OID_telephoneNumber,
    OID_telexNumber,
    OID_telexTerminalIdentifier,
    OID_facsimileTelephoneNumber,
    OID_x_121Address,
    OID_internationalISDNNumber,
    OID_registeredAddress,
    OID_destinationIndicator,
    OID_preferredDeliveryMethod,
    OID_presentationAddress,
    OID_supportedApplicationContext,
    OID_member,
    OID_owner,
    OID_roleOccupant
} ASN1OIDValue;

#endif /* _ASN1OIDS_H_ */
