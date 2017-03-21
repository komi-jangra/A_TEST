############################################################################
#                                                                          #
#     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    #
#             Manufactured in the United States of America.                #
#       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       #
#                                                                          #
#   This product and related documentation is protected by copyright and   #
#   distributed under licenses restricting its use, copying, distribution  #
#   and decompilation.  No part of this product or related documentation   #
#   may be reproduced in any form by any means without prior written       #
#   authorization of IntelliNet Technologies and its licensors, if any.    #
#                                                                          #
#   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      #
#   government is subject to restrictions as set forth in subparagraph     #
#   (c)(1)(ii) of the Rights in Technical Data and Computer Software       #
#   clause at DFARS 252.227-7013 and FAR 52.227-19.                        #
#                                                                          #
############################################################################
#                                                                          #
# CONTRACT: INTERNAL                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CPPOBJS= AsnException.o Asn.o AsnBoolean.o AsnChoice.o AsnDescBoolean.o \
         AsnDescChoice.o AsnDescEnumerated.o AsnDescInteger.o AsnDescNull.o \
         AsnDescObject.o AsnDescOctetString.o AsnDescSequence.o \
         AsnDescSequenceOf.o AsnDescSet.o AsnEnumerated.o AsnError.o \
         AsnInteger.o AsnNull.o AsnObject.o AsnOctetString.o \
         Length.o Octets.o Tag.o AsnSequence.o AsnSequenceOf.o AsnSet.o \
         AsnSetOf.o AsnAny.o AsnBitString.o AsnDescAny.o AsnDescBitString.o \
         AsnDescObjectIdentifier.o AsnDescReal.o AsnObjectIdentifier.o \
         AsnReal.o AsnDescSetOf.o AsnBaseString.o AsnDescBaseString.o \
         Characters.o AsnXml.o AsnOpenType.o AsnDescOpenType.o \
         AsnRelativeOid.o AsnDescRelativeOid.o AsnPack.o
         
         
CPPOBJSAUX=EXTERNAL.o GeneralizedTime.o GeneralString.o GraphicString.o \
           IA5String.o ISO646String.o NumericString.o ObjectDescriptor.o \
           PrintableString.o T61String.o TeletexString.o UTCTime.o \
           VideotexString.o VisibleString.o UTF8String.o UniversalString.o \
           BMPString.o EMBEDDED_PDV.o CHARACTER_STRING.o
           
CPPSRCSAUX=EXTERNAL.cpp GeneralizedTime.cpp GeneralString.cpp GraphicString.cpp \
           IA5String.cpp ISO646String.cpp NumericString.cpp ObjectDescriptor.cpp \
           PrintableString.cpp T61String.cpp TeletexString.cpp UTCTime.cpp \
           VideotexString.cpp VisibleString.cpp UTF8String.cpp UniversalString.cpp \
           BMPString.cpp EMBEDDED_PDV.cpp CHARACTER_STRING.cpp
           
CFLAGS := $(CFLAGS) -I../../include/asn-cpp
CXXFLAGS := $(CXXFLAGS) -I../../include/asn-cpp

all: ../../lib/libASN++$(DBGSUFFIX).a ../../lib/libASN++$(DBGSUFFIX).so

clean:
	$(RM) *.o ../../lib/libASN++$(DBGSUFFIX).a ../../lib/libASN++$(DBGSUFFIX).so \
        .depend AsnException.cpp ../../include/asn-cpp/AsnException.h $(CPPSRCSAUX) 

#../../lib/libASN++$(DBGSUFFIX).a: $(CPPOBJS) $(CPPOBJSAUX)
#	$(CXXAR) $(CXXARFLAGS) ../../lib/libASN++$(DBGSUFFIX).a $(OBJS) \
            $(CPPOBJS) $(CPPOBJSAUX)

#../../lib/libASN++$(DBGSUFFIX).so: $(CPPOBJS) $(CPPOBJSAUX)
#	$(CXX) $(CXXSHAREDARFLAGS) $@ $(OBJS) \
#            $(CPPOBJS) $(CPPOBJSAUX) $(CXXSHAREDARFLAGSEND)

#AsnException.cpp \
#$(ITS_ROOT)/common/include/AsnException.h: AsnException.exc
#	$(EXC) AsnException.exc
#	$(MV) AsnException.h ../../include/asn-cpp

$(CPPSRCSAUX): AsnUseful.asn
#	$(ITS_ROOT)/tools/bin/asncc_v2$(DBGSUFFIX) -cpp -cppNamespace its \
#            -cppFileNamesNoPrefix -cppFileNamesMixedCase ./AsnUseful.asn
	$(MV) -f *.h ../../include/asn-cpp

#
# get the rules
#
include $(ITS_ROOT)/config.rules
