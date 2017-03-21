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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
#
################################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

  
CFLAGS := $(CFLAGS) -I../../include/GSM/ -I$(ITS_ROOT)/common/inlude

OBJS= abis_traffic_management.o  \
      abis_network_management.o  \
      abis_layer2_management.o   \
      abis_rr_management.o       \
      abis_traffic_management_printIE.o \
      abis_rr_management_printIE.o \
      abis_network_management_printIE.o
	
all: ../../lib/libABISCODEC$(DBGSUFFIX).a \
     ../../lib/libABISCODEC$(DBGSUFFIX).so


clean:
	$(RM) *.o ../../lib/libABISCODEC$(DBGSUFFIX).a .depend \
        ../../lib/libABISCODEC$(DBGSUFFIX).so


../../lib/libABISCODEC$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libABISCODEC$(DBGSUFFIX).a $(OBJS) 

../../lib/libABISCODEC$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libABISCODEC$(DBGSUFFIX).so $(OBJS) \
	$(LIBS)


#
# get the rules
#
include $(ITS_ROOT)/config.rules
