################################################################################
#                                                                              #
#      Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.       #
#              Manufactured in the United States of America.                   #
#        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.          #
#                                                                              #
#     This product and related documentation is protected by copyright and     #
#     distributed under licenses restricting its use, copying, distribution    #
#     and decompilation.  No part of this product or related documentation     #
#     may be reproduced in any form by any means without prior written         #
#     authorization of IntelliNet Technologies and its licensors, if any.      #
#                                                                              #
#     RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        #
#     government is subject to restrictions as set forth in subparagraph       #
#     (c)(1)(ii) of the Rights in Technical Data and Computer Software         #
#     clause at DFARS 252.227-7013 and FAR 52.227-19.                          #
#                                                                              #
################################################################################
#                                                                              #
# CONTRACT: Internal                                                           #
#                                                                              #
################################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:09 bsccs2 Exp $
#
################################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

#
# Don't build if not CCITT
#
ifeq ($(PROTOCOL),CCITT)

CXXOBJS=main.o                                \
        test12_feature_result.o               \
        test12_alert_code.o                   \
        test12_group_information.o            \
        test12_carrier_digits.o               \
        test12_local_termination.o            \
        test12_destination_digits.o           \
        test12_pstn_termination.o             \
        test12_electronic_serial_number.o     \
        test12_termination_list.o             \
        test12_feature_request_rrl.o
        
CXXSRCS=main.cpp                                \
        test12_feature_result.cpp               \
        test12_alert_code.cpp                   \
        test12_group_information.cpp            \
        test12_carrier_digits.cpp               \
        test12_local_termination.cpp            \
        test12_destination_digits.cpp           \
        test12_pstn_termination.cpp             \
        test12_electronic_serial_number.cpp     \
        test12_termination_list.cpp             \
        test12_feature_request_rrl.cpp

CPPSRCSAUX=test12_feature_result.cpp            \
        test12_alert_code.cpp                   \
        test12_group_information.cpp            \
        test12_carrier_digits.cpp               \
        test12_local_termination.cpp            \
        test12_destination_digits.cpp           \
        test12_pstn_termination.cpp             \
        test12_electronic_serial_number.cpp     \
        test12_termination_list.cpp             \
        test12_feature_request_rrl.cpp

        
ITS_LIBS = -lASN++$(DBGSUFFIX) -lCORE++$(DBGSUFFIX) \
	       -lSUPPORT++$(DBGSUFFIX) -lCORE++$(DBGSUFFIX) 

LINK_FLAG = -L$(ITS_ROOT)/common/lib

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp

all: test12$(DBGSUFFIX)

test12$(DBGSUFFIX): $(CPPSRCSAUX) $(CXXOBJS)
	$(CXX) -g $(LDFLAGS) \
	$(LINK_FLAG) -o test12$(DBGSUFFIX) $(CXXOBJS) \
	$(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS)

$(CPPSRCSAUX): $(ITS_ROOT)/tools/bin/asncc_useful.asn
	$(ITS_ROOT)/tools/bin/asncc_v2$(DBGSUFFIX) -cpp -cppNamespace test12 \
	-u $(ITS_ROOT)/tools/bin/asncc_useful.asn test12.asn

clean:
	$(RM) $(CXXOBJS) test12$(DBGSUFFIX) $(CPPSRCSAUX) *.err .depend
            
#
# get the rules
#
include $(ITS_ROOT)/config.rules

#
# Don't build if not CCITT
#
else

all:

clean:

endif
