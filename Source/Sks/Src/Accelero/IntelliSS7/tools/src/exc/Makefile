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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:43  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:20  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:55  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1.8.1  2005/11/30 09:58:39  sjaddu
# LOG: Porting to MVL on power pc.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:17  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.5  2005/03/21 13:53:07  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:24  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.2  2000/11/29 23:44:17  mmiers
# LOG: Portability repairs.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:08:36  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:30:25  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.10  1999/06/28 19:13:58  skarmakar
# LOG:
# LOG:
# LOG: Update with awareness of throw specifier, behavior control defines
# LOG: in its++.h.
# LOG:
# LOG: Revision 1.9  1999/05/13 22:12:21  mmiers
# LOG:
# LOG:
# LOG: Temporary until dual building works.
# LOG:
# LOG: Revision 1.8  1998/10/01 01:48:33  mmiers
# LOG: Clean this up slightly.
# LOG:
# LOG: Revision 1.7  1998/06/23 02:31:10  mmiers
# LOG: Update Solaris build environment.  Part of getting SCCP working.
# LOG:
# LOG: Revision 1.6  1998/05/21 20:04:16  mmiers
# LOG: Optimize for UNIX.
# LOG:
# LOG: Revision 1.5  1998/05/21 19:38:44  mmiers
# LOG: Gee whiz.  Building on NT with a real make facility.  What a concept.
# LOG:
# LOG: Revision 1.4  1998/05/20 02:45:24  mmiers
# LOG: Back port to UNIX from that wannabe OS.
# LOG:
# LOG: Revision 1.3  1998/05/20 02:04:22  mmiers
# LOG: Tree cleanup.
# LOG:
# LOG: Revision 1.2  1998/05/20 01:54:35  mmiers
# LOG: General tree cleanup.
# LOG:
# LOG: Revision 1.1  1998/05/19 23:43:51  mmiers
# LOG: Fix for UNIX builds.
# LOG:
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

LDG=$(LD)

ifeq ($(PLATFORM),mvlppc)
CCG=$(CC)
CXXG=$(CXX)
CC := gcc -D_GNU_SOURCE -pipe -Wno-deprecated
CXX := g++ -D_GNU_SOURCE -pipe -Wno-deprecated
LDG=g++
endif


OBJS= exc_lex.$(OEXT) 

CXXOBJS= exc_assert.$(OEXT) exc_generate.$(OEXT) \
         exc_main.$(OEXT) exc_yacc.tab.$(OEXT)

CFLAGS := $(CFLAGS)
CXXFLAGS := $(CXXFLAGS) -DFLEX -DYY_USE_PROTOS -DC_FLEX \
		-DDONT_INCLUDE_ITS_EVENT

all: ../../bin/exc$(DBGSUFFIX)

clean:
	$(RM) *.$(OEXT) ../../bin/exc $(OBJS) $(CXXOBJS) \
		exc_lex.c exc_yacc.tab.h exc_yacc.tab.cpp *.output \
		*.acts *.tmp y.tab.c y.tab.h *.debug .depend

../../bin/exc$(DBGSUFFIX): $(CXXOBJS) $(OBJS)
	$(LDG) -o   ../../bin/exc$(DBGSUFFIX) $(LDFLAGS) $(OBJS) $(CXXOBJS)

ifeq ($(PLATFORM),mvlppc)
CC := $(CCG)
CXX := $(CXXG)
endif

exc_lex.c: exc_lex.l
	$(LEX) exc_lex.l
	mv lex.yy.c exc_lex.c

exc_yacc.tab.cpp exc_yacc.tab.h: exc_yacc.y
	$(YACC) -d -bexc_yacc exc_yacc.y
	mv exc_yacc.tab.c exc_yacc.tab.cpp
#
# get the rules
#
include $(ITS_ROOT)/config.rules
