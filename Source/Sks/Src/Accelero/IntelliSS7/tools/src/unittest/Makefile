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
# LOG: Revision 1.1.1.1  2007/10/04 13:24:44  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:21  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1.8.1  2005/11/30 10:02:06  sjaddu
# LOG: Porting to MVL on power pc
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:18  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:53:09  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/08/20 15:53:04  mmiers
# LOG: Update the clean target for china
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.3  2001/07/25 20:16:10  hdivoux
# LOG: Update of Makefile and remove warning in test.cpp.
# LOG:
# LOG: Revision 4.2  2001/07/25 19:59:13  hdivoux
# LOG: Review unit tester (Makefile and ...).
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:25  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.1  2000/08/16 00:08:39  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:30:32  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.9  1999/07/01 02:29:14  mmiers
# LOG:
# LOG: On Solaris, you build C++ libraries with the compiler, of all
# LOG: things.  Add new make variables accordingly.
# LOG:
# LOG: Revision 1.8  1999/05/13 22:12:21  mmiers
# LOG:
# LOG:
# LOG: Temporary until dual building works.
# LOG:
# LOG: Revision 1.7  1998/11/18 00:23:45  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.6  1998/11/17 23:57:44  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.5  1998/11/17 16:45:16  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG:
# LOG: Revision 1.4  1998/10/01 02:00:54  mmiers
# LOG: Add CXXFLAGS into def
# LOG:
# LOG: Revision 1.3  1998/10/01 01:52:40  mmiers
# LOG: Cleanup this Makefile
# LOG:
# LOG: Revision 1.2  1998/09/30 17:11:52  jrao
# LOG: HPUX doesn't support the stdc++ file names.
# LOG:
# LOG: Revision 1.1  1998/09/26 15:50:27  mmiers
# LOG: Unit tester makefile.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CXXG=$(CXX)
CXXARG=$(CXXAR)

ifeq ($(PLATFORM),mvlppc)
CCG=$(CC)
CXXG=$(CXX)
CXXARG=$(CXXAR)

CC := gcc -D_GNU_SOURCE -pipe -Wno-deprecated
CXX := g++ -D_GNU_SOURCE -pipe -Wno-deprecated
CXXAR=ar
endif

CXXOBJS = UnitTest.o
CXXOBJS_TEST = test.o
CXXFLAGS := $(CXXFLAGS) -I../../include -I$(ITS_ROOT)/common/include
LDFLAGS := $(LDFLAGS) -L../../lib
UNITTESTLIB = -lUNITTEST$(DBGSUFFIX)

all: ../../lib/libUNITTEST$(DBGSUFFIX).a

test_target: ./unittest_test$(DBGSUFFIX)

../../lib/libUNITTEST$(DBGSUFFIX).a: $(CXXOBJS)
	$(CXXARG) $(CXXARFLAGS) ../../lib/libUNITTEST$(DBGSUFFIX).a $(CXXOBJS)

./unittest_test$(DBGSUFFIX):                             \
                $(CXXOBJS_TEST)                          \
                ../../lib/libUNITTEST$(DBGSUFFIX).a
	$(CXXG) $(CXXFLAGS) $(LDFLAGS) -o ./unittest_test$(DBGSUFFIX) \
        $(CXXOBJS_TEST) $(UNITTESTLIB)

ifeq ($(PLATFORM),mvlppc)
CC := $(CCG)
CXX := $(CXXG)
CXXAR := $(CXXARG)
endif


clean:
	$(RM) $(CXXOBJS) $(CXXOBJS_TEST) ../../lib/libUNITTEST$(DBGSUFFIX).a    \
	        ./unittest_test$(DBGSUFFIX) .depend


#
# get the rules
#
include $(ITS_ROOT)/config.rules
