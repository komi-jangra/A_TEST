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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:10 bsccs2 Exp $
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

CXXOBJS=main.o                                                  \
        test15_collected_digits.o                               \
        test15_collected_info.o                                 \
        test15_error_treatment.o                                \
        test15_event_report_bcsm_arg.o                          \
        test15_event_type_bcsm.o                                \
        test15_misc_call_info.o                                 \
        test15_prompt_and_collect_user_information_arg.o
        
CXXSRCS=main.cpp                                                \
        test15_collected_digits.cpp                             \
        test15_collected_info.cpp                               \
        test15_error_treatment.cpp                              \
        test15_event_report_bcsm_arg.cpp                        \
        test15_event_type_bcsm.cpp                              \
        test15_misc_call_info.cpp                               \
        test15_prompt_and_collect_user_information_arg.cpp

CPPSRCSAUX=test15_collected_digits.cpp                          \
        test15_collected_info.cpp                               \
        test15_error_treatment.cpp                              \
        test15_event_report_bcsm_arg.cpp                        \
        test15_event_type_bcsm.cpp                              \
        test15_misc_call_info.cpp                               \
        test15_prompt_and_collect_user_information_arg.cpp

        
ITS_LIBS = -lASN++$(DBGSUFFIX) -lCORE$(DBGSUFFIX) \
	       -lSUPPORT$(DBGSUFFIX) -lCORE$(DBGSUFFIX) 

LINK_FLAG = -L$(ITS_ROOT)/common/lib

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp

all: test15$(DBGSUFFIX)

test15$(DBGSUFFIX): $(CPPSRCSAUX) $(CXXOBJS)
	$(CXX) -g $(LDFLAGS) \
	$(LINK_FLAG) -o test15$(DBGSUFFIX) $(CXXOBJS) \
	$(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS)

$(CPPSRCSAUX): $(ITS_ROOT)/tools/bin/asncc_useful.asn
	$(ITS_ROOT)/tools/bin/asncc_v2$(DBGSUFFIX) -cpp -cppNamespace test15 \
	-u $(ITS_ROOT)/tools/bin/asncc_useful.asn test15.asn

clean:
	$(RM) $(CXXOBJS) test15$(DBGSUFFIX) $(CPPSRCSAUX) *.err .depend
            
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
