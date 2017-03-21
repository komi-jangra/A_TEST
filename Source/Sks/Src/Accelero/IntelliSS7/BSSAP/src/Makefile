############################################################################
#                                                                          #
#     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: 
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

#PROTOCOL=CCITT

CXXFLAGS := $(CXXFLAGS) -I../include \
          -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include \
          -I$(ITS_ROOT)/MTP2/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I${BPM_INC}  -I${BPM_INC}/../Sys  \
          -I${BPM_INC}/../Ipc

OBJS = BSSAP++.o BSSAPPrint.o BSSAPPrintIE.o
ifeq ($(PROTOCOL),ANSI)
all: ../lib/libANSI-BSSAP++$(DBGSUFFIX).a

../lib/libANSI-BSSAP++$(DBGSUFFIX).a: $(OBJS) 
	 $(CXXAR) $(CXXARFLAGS) ../lib/libANSI-BSSAP++$(DBGSUFFIX).a $(OBJS)

clean:
	$(RM) -rf $(OBJS) ../lib/libANSI-BSSAP++$(DBGSUFFIX).a SunWS_cache

else
all: ../lib/libCCITT-BSSAP++$(DBGSUFFIX).a

../lib/libCCITT-BSSAP++$(DBGSUFFIX).a: $(OBJS) 
	 $(CXXAR) $(CXXARFLAGS) ../lib/libCCITT-BSSAP++$(DBGSUFFIX).a $(OBJS)

clean:
	$(RM) -rf $(OBJS) ../lib/libCCITT-BSSAP++$(DBGSUFFIX).a SunWS_cache
endif
#
# get the rules
#
include $(ITS_ROOT)/config.rules



