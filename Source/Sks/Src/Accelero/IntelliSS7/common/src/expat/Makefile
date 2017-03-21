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
# LOG: Revision 1.1.1.1  2007/10/04 13:24:24  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:13  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1.8.1  2005/11/30 10:10:26  sjaddu
# LOG: Porting to MVL on power pc.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:25  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:51:41  cvsadmin
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
# LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 1.3  2001/03/29 03:07:34  mmiers
# LOG: Start debugging.
# LOG:
# LOG: Revision 1.2  2001/02/28 17:22:04  mmiers
# LOG: Cleanup.
# LOG:
# LOG: Revision 1.1  2001/02/28 17:16:27  mmiers
# LOG: Add standard Makefile
# LOG:
#
############################################################################

#
# get the vars
#

include $(ITS_ROOT)/config.vars

TABOBJS=gennmtab.o
COBJS=xmlparse.o xmlrole.o xmltok.o

all: ../../lib/libEXPAT$(DBGSUFFIX).a

../../lib/libEXPAT$(DBGSUFFIX).a: $(COBJS)
	$(AR) $(ARFLAGS) ../../lib/libEXPAT$(DBGSUFFIX).a $(COBJS)

$(COBJS): ascii.h asciitab.h iasciitab.h latin1tab.h nametab.h \
	utf8tab.h xmlrole.h xmltok.h xmltok_impl.h

nametab.h: gennmtab
	./gennmtab$(DBGSUFFIX) > nametab.h

CCG=$(CC)

ifeq ($(PLATFORM),mvlppc)
CCG=gcc 
endif


gennmtab:
	$(CCG) $(CFLAGS) -o gennmtab$(DBGSUFFIX) gennmtab.c \

$(TABOBJS): gennmtab.c

clean:
	$(RM) $(COBJS) gennmtab.o .depend ../../lib/libEXPAT$(DBGSUFFIX).a \
		gennmtab$(DBGSUFFIX) gennmtab

#
# get the rules
#
include $(ITS_ROOT)/config.rules
