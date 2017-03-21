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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:23  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:11  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:21  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 1.1  2003/09/23 19:59:25  mmiers
# LOG: New implementation for POSIX shared memory (more later).
# LOG: Bug fix for index ranges in stub.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars


OBJS=dsm_posix_impl.o

CFLAGS := $(CFLAGS) -DDSM_IMPLEMENTATION

all: ../../lib/libDSM-POSIX$(DBGSUFFIX).so

clean:
	$(RM) *.o \
		../../lib/libDSM-POSIX$(DBGSUFFIX).so \
		../../lib/libDSM-POSIX$(DBGSUFFIX).a

../../lib/libDSM-POSIX$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	../../lib/libDSM-POSIX$(DBGSUFFIX).so \
	$(OBJS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
