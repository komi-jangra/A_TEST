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
#  LOG: $Log: not supported by cvs2svn $
#  LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
#  LOG: init tree
#  LOG:
#  LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
#  LOG: BscCs2
#  LOG:
#  LOG: Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
#  LOG: BSC project
#  LOG:
#  LOG: Revision 1.1  2005/06/02 06:54:35  yranade
#  LOG: Linux Kernel SCTP Integration as per ACC652-SDS-LKSC-V1.0.02.
#  LOG:
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $
#
############################################################################

#ident "$Id: Makefile,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

#
# get the vars
#
include $(ITS_ROOT)/config.vars

COBJS=its_lksctp.o

LK-LIBS=/usr/lib/libsctp.a

all: ../../lib/libLKSCTP$(DBGSUFFIX).so

clean:
	$(RM) $(COBJS) .depend ../../lib/libLKSCTP$(DBGSUFFIX).so

../../lib/libLKSCTP$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libLKSCTP$(DBGSUFFIX).so $(COBJS) $(LK-LIBS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
