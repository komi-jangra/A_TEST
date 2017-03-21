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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
#
#  LOG: $Log: not supported by cvs2svn $
#  LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
#  LOG: init tree
#  LOG:
#  LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
#  LOG: BscCs2
#  LOG:
#  LOG: Revision 1.1.1.1  2007/03/08 15:14:19  cvsadmin
#  LOG: BSC project
#  LOG:
#  LOG: Revision 9.1  2005/03/23 12:53:33  cvsadmin
#  LOG: Begin PR6.5
#  LOG:
#  LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
#  LOG: PR6.4.2 Source Propagated to Current
#  LOG:
#  LOG: Revision 1.1.2.2  2004/01/27 13:44:18  sjaddu
#  LOG: Added file for active-backup redundancy.
#  LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I $(ITS_ROOT)/ISUP/include  -I $(ITS_ROOT)/MTP3/include \
          -I  $(ITS_ROOT)/MTP2/include \
	-I../../include \
	-I${BPM_INC}  \
	-I${BPM_INC}/../Sys  \
	-I${BPM_INC}/../Ipc
OBJS= its_redundancy.o

ifeq ($(PROTOCOL),ANSI)
all: ../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).a ../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).so
else
all: ../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).a ../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).so
endif

ifeq ($(PROTOCOL),ANSI)
clean:
	$(RM) *.o ../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).a  \
    ../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).so

../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).a: $(OBJS) 
	$(AR) $(ARFLAGS) ../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).a $(OBJS)

../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).so: $(OBJS) 
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libANSI-ITS-REDUNDANCY$(DBGSUFFIX).so \
    $(OBJS)  $(SHAREDARFLAGSEND)
else
clean:
	$(RM) *.o ../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).a  \
    ../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).so

../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).a: $(OBJS) 
	$(AR) $(ARFLAGS) ../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).a $(OBJS)

../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).so: $(OBJS) 
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libCCITT-ITS-REDUNDANCY$(DBGSUFFIX).so \
    $(OBJS)  $(SHAREDARFLAGSEND)
endif
#
# get the rules
#
include $(ITS_ROOT)/config.rules
