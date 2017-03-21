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
# ID: $Id: Makefile,v 1.4 2008-02-07 10:14:23 amaresh.prasad Exp $
# 
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.3  2008/02/01 04:30:20  amaresh.prasad
# LOG: Added new alarm file
# LOG:
# LOG: Revision 1.2  2007/10/09 14:02:57  bsccs2
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
# LOG: Init Code
# LOG:
# LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.2  2007/06/28 04:11:41  cvsadmin
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 1.1.2.6  2005/12/19 05:06:34  adutta
# LOG: Changes to follow only 3GPP8.08
# LOG:
# LOG: Revision 1.1.2.5  2005/11/24 04:43:40  adutta
# LOG: Incorporated IMR review changes *.cpp
# LOG:
# LOG: Revision 1.1.2.4  2005/10/11 10:05:03  adutta
# LOG: Added MSC objects
# LOG:
# 
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

#PROTOCOL=ANSI

CXXFLAGS := $(CXXFLAGS) -I../include \
          -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include \
          -I$(ITS_ROOT)/MTP2/include \
	   -I${BPM_INC}/../Sys  \
           -I${BPM_INC}/../Ipc  \
          -I../../include \
					 -I$(SKS_ROOT)/ISIL/Inc \
          -I$(ITS_ROOT)/common/include/asn-cpp

ifeq ($(PROTOCOL),ANSI)
LIBS := -L../../lib \
        -lANSI-BSSAP++$(DBGSUFFIX)
else
LIBS := -L../../lib \
        -lCCITT-BSSAP++$(DBGSUFFIX)
endif

ifeq ($(TARGET),BSS)

OBJS =  bssap.o bssap_interface.o bssap_tqhandler.o bssap-alarm.o bssap_sccphandler.o bssap_appiddb.o\
        bssap_discriminator.o bssap_calldb.o bssap_map.o   \
        bssap_timer.o bssap_cicdb.o bssap_cfgdb.o bssap_error.o bssap_dbc.o bssap_pegs.o

else
ifeq ($(TARGET),MSC)
OBJS =  bssap-msc.o bssap_msc-interface.o bssap_msc-tqhandler.o \
        bssap_msc-sccphandler.o bssap_msc-discriminator.o \
        bssap_msc-calldb.o bssap_msc-map.o bssap_msc-timer.o \
        bssap_msc-cicdb.o bssap_msc-cfgdb.o bssap_msc-error.o \
        bssap_msc-dbc.o bssap_msc-dtap.o
endif
endif

ifeq ($(PROTOCOL),ANSI)
all: ../../lib/libANSI-BSSAPStack$(DBGSUFFIX).so

../../lib/libANSI-BSSAPStack$(DBGSUFFIX).so: $(OBJS) 
	 $(CXX) $(CXXSHAREDARFLAGS) $@ $(OBJS) $(LIBS) $(CXXSHAREDARFLAGSEND)
else
all: ../../lib/libCCITT-BSSAPStack$(DBGSUFFIX).so
../../lib/libCCITT-BSSAPStack$(DBGSUFFIX).so: $(OBJS)
	 $(CXX) $(CXXSHAREDARFLAGS) $@ $(OBJS) $(LIBS) $(CXXSHAREDARFLAGSEND)
endif


ifeq ($(PROTOCOL),ANSI)
clean:
	$(RM) -rf $(OBJS) ../../lib/libANSI-BSSAPStack$(DBGSUFFIX).so
else
clean:
	$(RM) -rf $(OBJS) ../../lib//libCCITT-BSSAPStack$(DBGSUFFIX).so
endif



#
# get the rules
#
include $(ITS_ROOT)/config.rules

