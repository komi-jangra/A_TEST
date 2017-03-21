################################################################################
#                                                                              #
#      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.       #
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
# CONTRACT: INTERNAL                                                           #
#                                                                              #
################################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
#
################################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars


CXXOBJS=alloc_main.o
        
CXXSRCS=alloc_main.cpp
        
ITS_LIBS = 

LINK_FLAG = 

CXXFLAGS := $(CXXFLAGS) 

all: asn_alloc$(DBGSUFFIX)

asn_alloc$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) -g $(LDFLAGS) \
        $(LINK_FLAG) -o asn_alloc$(DBGSUFFIX) $(CXXOBJS) \
        $(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS)

clean:
	$(RM) $(CXXOBJS) asn_alloc$(DBGSUFFIX) *.err .depend
            
#
# get the rules
#
include $(ITS_ROOT)/config.rules

