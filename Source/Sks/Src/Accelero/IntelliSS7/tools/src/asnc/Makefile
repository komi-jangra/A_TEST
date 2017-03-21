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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:04 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:39  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:18  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:35  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1.8.1  2005/11/30 09:54:28  sjaddu
# LOG: iPorting to MVL on power pc.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:07  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:48  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:17  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:30  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:19  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:22  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.1  2000/08/16 00:07:16  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:29:58  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.6  1999/06/01 17:26:40  labuser
# LOG:
# LOG:
# LOG: Get rid of Berkeley byte functions.
# LOG:
# LOG: Revision 1.5  1999/05/13 22:12:21  mmiers
# LOG:
# LOG:
# LOG: Temporary until dual building works.
# LOG:
# LOG: Revision 1.4  1999/05/11 01:27:36  mmiers
# LOG:
# LOG:
# LOG: Start on dual debug/release build rules.
# LOG:
# LOG: Revision 1.3  1998/10/21 19:20:19  mmiers
# LOG: Update for ALPHA build.
# LOG:
# LOG: Revision 1.2  1998/10/21 04:31:11  mmiers
# LOG: Cleaning up pepsy.
# LOG:
# LOG: Revision 1.1  1998/10/16 22:36:56  jpakrasi
# LOG: Build pepsy on NT.
# LOG:
# LOG: Revision 1.1.1.1  1997/11/04 20:13:20  mmiers
# LOG: Baseline
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars


ifeq ($(PLATFORM),mvlppc)
CCG=$(CC)
CXXG=$(CXX)
CC := gcc -D_GNU_SOURCE -pipe -Wno-deprecated
CXX := g++ -D_GNU_SOURCE -pipe -Wno-deprecated
endif

SRCS=main.c misc.c lex.yy.c yacc.tab.c dfns.c pass2.c etabs.c ptabs.c dtabs.c
OBJS=main.o misc.o yacc.tab.o \
     dfns.o pass2.o etabs.o \
     ptabs.o dtabs.o

CFLAGS := $(CFLAGS) -I../../../common/include

all: asnc$(DBGSUFFIX)

asnc$(DBGSUFFIX): $(OBJS)
	$(CC) $(CFLAGS) -o ../../bin/asnc$(DBGSUFFIX) $(OBJS) -lm
ifeq ($(PLATFORM),mvlppc)
CC := $(CCG)
CXX := $(CXXG)
endif
yacc.tab.c: yacc.y lex.yy.c
	$(YACC) -v -d yacc.y

lex.yy.c: lex.l
	$(LEX) lex.l

clean:
	$(RM) $(OBJS) ../../bin/asnc$(DBGSUFFIX) ../../bin/asnc \
                yacc.tab.c yacc.tab.h y.output lex.yy.c \
		TEST* UNIV* INAP* .depend

include $(ITS_ROOT)/config.rules
