###############################################################################
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
# CONTRACT: Internal                                                           #
#                                                                              #
################################################################################
#
#                           README
#  1.) Need to specify M3UA version to build binaries. default is M3UA ver 10.
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $
#
################################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CB_OBJS=SGP_CB.o ASP_CB.o test_common.o 

#stats_record.o
MAIN_OBJ=Main.o

ifeq ($(M3UA_VER), 3)
CXXASPOBJS=ASPSim.o
CXXSGPOBJS=SGPSim.o
M3UA_LIBS=-l$(PROTOCOL)-M3UAMGNT$(DBGSUFFIX) -l$(PROTOCOL)-M3UA$(DBGSUFFIX)
else
CXXASPOBJS=ASP.o
CXXSGPOBJS=SGP.o
M3UA_LIBS=-lUAL$(DBGSUFFIX) -l$(PROTOCOL)-M3UA$(DBGSUFFIX)
endif

ITS_LIBS=-lENGINE$(DBGSUFFIX) \
         -lASN$(DBGSUFFIX)    \
         -lDISPATCH++$(DBGSUFFIX) \
         -lDRIVER++$(DBGSUFFIX) \
         -lVFrame$(DBGSUFFIX) \
         -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
         $(M3UA_LIBS)         \
         -lSCTP$(DBGSUFFIX)   \
         -lrt

LINK_FLAG = -L$(ITS_ROOT)/common/lib -L$(ITS_ROOT)/GSMMAP/lib \
	    -L$(VENDOR_ROOT)/IntelliNet/lib -L$(ITS_ROOT)/TCAP/lib \
            -L$(ITS_ROOT)/ISUP/lib \
	    -L$(ITS_ROOT)/SCCP/lib -L$(ITS_ROOT)/MTP3/lib 


CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I$(ITS_ROOT)/GSMMAP/include/itu \
	  -I$(ITS_ROOT)/TCAP/include \
	  -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/ISUP/include \
	  -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/MTP2/include \
	  -DUSE_INTELLINET_STACK     \
	  -DUSE_SOCKETS              \
          -D$(PROTOCOL)

ifeq ($(USE_ENGINE), yes)

all : libM3UA_TEST$(DBGSUFFIX).so app_test$(DBGSUFFIX)

libM3UA_TEST$(DBGSUFFIX).so : $(CB_OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $@ $(CB_OBJS) 

app_test$(DBGSUFFIX) : $(MAIN_OBJ)
	$(CXX) $(LD_FLAGS) $(LINK_FLAG) -o $@ $< $(ITS_LIBS) $(SOCKLIBS) \
        $(THREADLIBS) $(SYSLIBS) libM3UA_TEST$(DBGSUFFIX).so

clean :
	$(RM) $(CB_OBJS) $(MAIN_OBJ) libM3UA_TEST$(DBGSUFFIX).so app_test$(DBGSUFFIX)
else

all : asp$(DBGSUFFIX) sgp$(DBGSUFFIX)

asp$(DBGSUFFIX): $(CXXASPOBJS)
	$(CXX) -g $(LDFLAGS) \
        $(LINK_FLAG) -o asp$(DBGSUFFIX) $(CXXASPOBJS) \
        $(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

sgp$(DBGSUFFIX): $(CXXSGPOBJS)
	$(CXX) -g $(LDFLAGS) \
	$(LINK_FLAG) -o sgp$(DBGSUFFIX) $(CXXSGPOBJS) \
	$(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

clean:
	$(RM) $(CXXASPOBJS) $(CXXSGPOBJS) sgp$(DBGSUFFIX) asp$(DBGSUFFIX) \
               *.err .depend 

endif

clean:
	$(RM) $(CXXASPOBJS) $(CXXSGPOBJS) sgp$(DBGSUFFIX) \
           asp$(DBGSUFFIX) *.err .depend app_test$(DBGSUFFIX) \
           libM3UA_TEST$(DBGSUFFIX).so $(CB_OBJS)

            
#
# get the rules
#
include $(ITS_ROOT)/config.rules

