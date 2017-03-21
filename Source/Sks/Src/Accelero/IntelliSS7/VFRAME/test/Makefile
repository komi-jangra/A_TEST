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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:30 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:42  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 1.7  2005/03/21 13:50:41  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 1.6.2.1  2004/09/21 13:31:52  mmanikandan
# LOG: Propagating pprint from current.
# LOG:
# LOG: Revision 1.6  2004/09/21 09:47:56  mmanikandan
# LOG: Propagating pprint from current.
# LOG:
# LOG: Revision 1.5  2003/11/17 15:53:57  mmiers
# LOG: Debug build errors.
# LOG:
# LOG: Revision 1.4  2003/11/14 14:49:31  mmiers
# LOG: Tweaking.
# LOG:
# LOG: Revision 1.3  2003/11/13 16:39:16  mmiers
# LOG: Add lib test
# LOG:
# LOG: Revision 1.2  2003/11/13 15:12:53  mmiers
# LOG: Change to C++ build for linkage purposes.
# LOG:
# LOG: Revision 1.1  2003/10/29 15:20:05  mmiers
# LOG: Linux build
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CXXFLAGS := $(CXXFLAGS) -I../include \
	  -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include

LDFLAGS:=$(LDFLAGS) -L. -L../../common/lib
LIBS= -lENGINE$(DBGSUFFIX) -lDSM-STUB$(DBGSUFFIX) -lDRIVER++$(DBGSUFFIX) -lASN++$(DBGSUFFIX)
NORMLIBS=-lVFrame$(DBGSUFFIX)
AOCLIBS=-lAOCVFrame$(DBGSUFFIX)
COALIBS=-lCOAVFrame$(DBGSUFFIX)

OBJS= pprint.o

#
# SCCP type
#
ifeq ($(SCCP_PROT),)
all: pprint$(DBGSUFFIX) libptest$(DBGSUFFIX).$(SO_EXT)
endif
ifeq ($(SCCP_PROT),$(PROTOCOL))
all: pprint$(DBGSUFFIX) libptest$(DBGSUFFIX).$(SO_EXT)
else
ifeq ($(SCCP_PROT),ANSI)
CXXFLAGS := $(CXXFLAGS) -DSPLIT_STACK -DUSE_ANSI_SCCP
all: pprintCOA$(DBGSUFFIX) libptest$(DBGSUFFIX).$(SO_EXT)
endif
ifeq ($(SCCP_PROT),CCITT)
CXXFLAGS := $(CXXFLAGS) -DSPLIT_STACK -DUSE_ITU_SCCP
all: pprintAOC$(DBGSUFFIX) libptest$(DBGSUFFIX).$(SO_EXT)
endif
endif

pprint$(DBGSUFFIX): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o pprint$(DBGSUFFIX) $(OBJS) \
		$(NORMLIBS) $(LIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

pprintCOA$(DBGSUFFIX): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o pprintCOA$(DBGSUFFIX) $(OBJS) \
		$(COALIBS) $(LIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

pprintAOC$(DBGSUFFIX): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o pprintAOC$(DBGSUFFIX) $(OBJS) \
		$(AOCLIBS) $(LIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

libptest$(DBGSUFFIX).$(SO_EXT): ptest.o
	$(CXX) $(CXXSHAREDARFLAGS) libptest$(DBGSUFFIX).$(SO_EXT) \
		ptest.o

clean:
	$(RM) $(OBJS) pprint$(DBGSUFFIX) \
		pprintCOA$(DBGSUFFIX) pprintAOC$(DBGSUFFIX) \
		ptest.o libptest$(DBGSUFFIX).$(SO_EXT)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
