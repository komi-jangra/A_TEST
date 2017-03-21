############################################################################
#                                                                          #
#     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:53 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:24  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:14  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:26  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:42  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.3  2001/06/28 17:22:51  hdivoux
# LOG: Update for Sun cc port.
# LOG:
# LOG: Revision 1.2  2001/06/28 16:43:44  hdivoux
# LOG: Work in progress. Temp (need review).
# LOG:
# LOG: Revision 1.1  2001/06/28 15:21:54  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars
CFLAGS := $(CFLAGS) -I../../include \
        -I${BPM_INC}  \
        -I${BPM_INC}/../Sys  \
        -I${BPM_INC}/../Ipc

COBJS=gcs_client.o alarm.o events.o memory.o sp.o

ifeq ($(PROTOCOL),ANSI)
all: ../../lib/libANSI-GCS-CLIENT$(DBGSUFFIX).so
else
all: ../../lib/libCCITT-GCS-CLIENT$(DBGSUFFIX).so
endif


ifeq ($(PROTOCOL),ANSI)
clean:
	$(RM) $(COBJS) .depend ../../lib/libANSI-GCS-CLIENT$(DBGSUFFIX).so

../../lib/libANSI-GCS-CLIENT$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libANSI-GCS-CLIENT$(DBGSUFFIX).so $(COBJS) $(SHAREDARFLAGSEND)

else
clean:
	$(RM) $(COBJS) .depend ../../lib/libCCITT-GCS-CLIENT$(DBGSUFFIX).so

../../lib/libCCITT-GCS-CLIENT$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libCCITT-GCS-CLIENT$(DBGSUFFIX).so $(COBJS) $(SHAREDARFLAGSEND)
endif
#
# get the rules
#
include $(ITS_ROOT)/config.rules
