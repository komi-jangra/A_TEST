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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:32  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:23  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:50  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:22  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.2  2002/10/28 20:43:44  mmiers
# LOG: Update tests
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.5  2002/02/27 23:01:31  vnitin
# LOG: Adding sctp test code for retrieve buffer and SSN
# LOG:
# LOG: Revision 5.4  2001/11/01 01:40:29  mmiers
# LOG: Debugging changeback.
# LOG:
# LOG: Revision 5.3  2001/09/19 01:06:20  mmiers
# LOG: msec timers work.
# LOG:
# LOG: Revision 5.2  2001/09/19 00:53:36  mmiers
# LOG: Bugs found in cross platform build.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.14  2001/04/04 22:01:31  mmiers
# LOG: Finish debugging.
# LOG:
# LOG: Revision 3.13  2001/04/02 21:22:21  mmiers
# LOG: Remove my stuff.
# LOG:
# LOG: Revision 3.12  2001/03/30 21:03:34  mmiers
# LOG: Testing.
# LOG:
# LOG: Revision 3.11  2001/03/13 02:26:22  mmiers
# LOG: UNIX build is a heck of a lot easier to set up.
# LOG:
# LOG: Revision 3.10  2001/03/06 22:24:37  mmiers
# LOG: Convert to SUPPORT only
# LOG:
# LOG: Revision 3.9  2001/03/06 02:28:38  mmiers
# LOG: Add dynamic link lib.  Straighten out include order.  Remove instance
# LOG: of CORE++.
# LOG:
# LOG: Revision 3.8  2001/01/19 19:33:08  mmiers
# LOG: Mysteries
# LOG:
# LOG: Revision 3.7  2001/01/18 23:19:23  mmiers
# LOG: Profiling
# LOG:
# LOG: Revision 3.6  2001/01/10 19:44:00  mmiers
# LOG: Debug new implementation.
# LOG:
# LOG: Revision 3.5  2001/01/10 00:28:22  mmiers
# LOG: Clean up the test.
# LOG:
# LOG: Revision 3.4  2000/12/20 17:49:49  mmiers
# LOG: Solaris debugging.
# LOG:
# LOG: Revision 3.3  2000/11/13 19:50:43  mmiers
# LOG: Add clean target
# LOG:
# LOG: Revision 3.2  2000/11/13 19:28:30  mmiers
# LOG: Try to recover
# LOG:
# LOG: Revision 3.5  2000/10/30 16:18:23  mmiers
# LOG: Post bakeoff.  Now to clean up.
# LOG:
# LOG: Revision 3.4  2000/10/21 23:49:26  mmiers
# LOG: Final version for bakeoff.
# LOG:
# LOG: Revision 3.3  2000/10/21 22:45:07  mmiers
# LOG: Surprising results running with efence.
# LOG:
# LOG: Revision 3.2  2000/10/09 17:39:49  mmiers
# LOG: Test cleanup.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:06:08  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.12  2000/07/17 15:23:17  mmiers
# LOG:
# LOG: IMAL test.
# LOG:
# LOG: Revision 2.11  2000/06/20 23:27:29  mmiers
# LOG:
# LOG:
# LOG: Add platform independent usleep.
# LOG:
# LOG: Revision 2.10  2000/06/02 15:51:35  mmiers
# LOG:
# LOG:
# LOG: More sockets testing.
# LOG:
# LOG: Revision 2.9  2000/05/24 22:01:13  mmiers
# LOG:
# LOG:
# LOG: More fixes for raw sockets.  Now 3 platforms down.
# LOG:
# LOG: Revision 2.8  2000/05/23 23:06:07  mmiers
# LOG:
# LOG:
# LOG: Add new tests.
# LOG:
# LOG: Revision 2.7  2000/04/25 23:03:33  mmiers
# LOG:
# LOG:
# LOG: Update C service test.
# LOG:
# LOG: Revision 2.6  2000/04/25 16:49:25  mmiers
# LOG:
# LOG:
# LOG: Update to current code base.
# LOG:
# LOG: Revision 2.5  2000/04/25 16:46:41  mmiers
# LOG:
# LOG:
# LOG: Update to current code base.
# LOG:
# LOG: Revision 2.4  2000/02/10 02:18:10  mmiers
# LOG: Fix some nasty bugs that didn't show up on NT.
# LOG:
# LOG: Revision 2.3  2000/02/10 01:47:58  mmiers
# LOG: Cross platform cleanup.
# LOG:
# LOG: Revision 2.2  1999/12/18 00:35:38  mmiers
# LOG: Continued tweaks.
# LOG:
# LOG: Revision 2.1  1999/12/17 21:55:26  mmiers
# LOG: Try this on DECUNIX
# LOG:
# LOG: Revision 2.0  1999/12/03 23:28:25  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.14  1999/12/02 21:20:32  labuser
# LOG:
# LOG:
# LOG: Update test6 to latest environ
# LOG:
# LOG: Revision 1.13  1999/08/25 02:03:45  mmiers
# LOG:
# LOG:
# LOG: Try to build on Linux.
# LOG:
# LOG: Revision 1.12  1999/08/22 21:56:49  labuser
# LOG:
# LOG:
# LOG: Integration fixes.
# LOG:
# LOG: Revision 1.11  1998/11/09 22:01:57  rsonak
# LOG: Update for successful HP build.
# LOG:
# LOG: Revision 1.10  1998/10/29 18:10:48  mmiers
# LOG: Remove pepsy from Makefile
# LOG:
# LOG: Revision 1.9  1998/09/23 22:04:30  jrao
# LOG: Updates from HPUX.
# LOG:
# LOG: Revision 1.8  1998/09/22 23:56:32  jrao
# LOG: Changes made to accomodate HPUX code
# LOG:
# LOG: Revision 1.7  1998/06/30 01:50:10  mmiers
# LOG: IS634: Clean up some warnings from a GCC build (ANSI "for" scope rule).
# LOG: The rest is cleanup.  We can add Linux as a platform, but it is not
# LOG: safe multithreaded (yet).
# LOG:
# LOG: Revision 1.6  1998/05/31 22:20:16  mmiers
# LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
# LOG: Solaris.
# LOG:
# LOG: Revision 1.5  1998/05/29 03:31:38  mmiers
# LOG: More work on documentation.  Most of this is just adding interface
# LOG: description boxes without actually adding text.  Some of this is
# LOG: genuine bug fixing.
# LOG:
# LOG: Revision 1.4  1998/05/21 02:15:28  mmiers
# LOG: General cleanup to reflect TCAP changes (INAP, IS41).  Some missing
# LOG: files in builds.  Update the test to include the SCCP library.  I'll
# LOG: have to modify TCAP tomorrow to use SCCP_SendEvent instead of
# LOG: TRANSPORT_PutEvent().  Less efficient, but more useable with someone
# LOG: else's SCCP.
# LOG:
# LOG: Revision 1.3  1998/04/19 02:42:52  mmiers
# LOG: Pretty close to having the basic worker architecture for the HLR
# LOG: done.
# LOG:
# LOG: Revision 1.2  1998/04/17 02:13:54  mmiers
# LOG: Add sixth test.
# LOG:
# LOG: Revision 1.1  1998/04/13 22:19:22  mmiers
# LOG: Fifo (named pipe) implementation.  For portability, fifos can be
# LOG: RDONLY or WRONLY, but not both (i.e., not bidirectional).  For
# LOG: bidirectional communication, use two fifos.
# LOG:
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/IS41/include \
	  -I$(ITS_ROOT)/MTP2/include
CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/IS41/include \
	  -I$(ITS_ROOT)/MTP2/include
LDFLAGS = -L../lib \
          -L$(ITS_ROOT)/TCAP/lib -L$(ITS_ROOT)/SCCP/lib \
	  -L$(ITS_ROOT)/MTP3/lib -L$(ITS_ROOT)/SLTM/lib \
          -L$(VENDOR_ROOT)/IntelliNet/lib
#CXXBASELIBS=-lCORED -lSUPPORTD -lCORED -lSUPPORTD
CXXBASELIBS=-lCORE -lSUPPORT -lCORE -lSUPPORT
#BASELIBS=-lSUPPORTD -lCORED -lSUPPORTD -lCORED
BASELIBS=-lSUPPORT -lCORE -lSUPPORT -lCORE
#STACKLIBS=-lVFrameD
STACKLIBS=-lVFrame

all: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 \
     test11 test12 test13 test14 test15 test16 test17 test18 test19 test20 \
     test21 test22 test23 test24 test25 test26 test 27 test28 test 29 test30

clean:
	$(RM) *.o test1 test2 test3 test4 test5 test6 test7 test8 test9 \
		test10 test11 test12 test13 test14 test15 test16 test17 \
		test18 test19 test20 test21 test22 test23 test24 test25 \
		test26 test27 test28 test29 test30

test1: test1.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test1 test1.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test2: test2.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test2 test2.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test3: test3.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test3 test3.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test4: test4.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test4 test4.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test5: test5.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test5 test5.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test6: test6.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test6 test6.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test7: test7.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test7 test7.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test8: test8.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test8 test8.cpp \
		$(STACKLIBS) $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test9: test9.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test9 test9.c \
		$(STACKLIBS) $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test10: test10.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test10 test10.cpp \
		$(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test11: test11.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test11 test11.c \
		-lANSI-GDID $(STACKLIBS) $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test12: test12.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test12 test12.c $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test13: test13.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test13 test13.c $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test14: test14.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test14 test14.cpp $(CXXBASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test15: test15.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test15 test15.c $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test16: test16.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test12 test12.c $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test17: test17.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test17 test17.c -lRUDPD $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test18: test18.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test18 test18.c -lRUDPD $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test19: test19.c
	$(CC) $(CFLAGS) -I../../IS41/include $(LDFLAGS) -o test19 \
		test19.c $(BASELIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test20: test20.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test20 test20.cpp \
		-lSUPPORTD -lCORED $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test21: test21.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test21 test21.cpp \
		-lSUPPORTD -lCORED $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) \
		-lSUPPORTD -lCORED $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test22: test22.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test22 test22.cpp \
		-lSUPPORTD -lCORED $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test23: test23.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test23 test23.cpp \
		-lSUPPORTD -lCORED $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test24: test24.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test24 test24.c \
		-lENGINE $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test25: test25.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test25 test25.c \
		-lCORED -lSUPPORTD -lCORED -lCCITT-IMALD \
		-lCCITT-MTP3D -lCCITT-SLTMD \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test26: test26.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test26 test26.c \
		-lSUPPORTD -lCORED -lSUPPORTD -lCCITT-IMALD \
		-lCCITT-MTP3D -lCCITT-SLTMD \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test27: test27.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test27 test27.c \
		-lSCTPD -lSUPPORTD -lCORED -lDSM-STUBD -lrt \
		-lSCTPD -lSUPPORTD -lCORED \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test28: test28.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test28 test28.c \
		-lSUPPORTD -lCORED \
		-lSUPPORTD -lCORED \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test30: test30.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test30 test30.c \
		-lSUPPORTD -lCORED \
		-lSUPPORTD -lCORED \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test31: test31.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test31 test31.c \
		-lSUPPORTD -lCORED \
		-lSUPPORTD -lCORED \

test32: test32.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test32 test32.c \
		-lSUPPORTD -lCORED -lDSM-STUBD \
		-lSUPPORTD -lCORED -lDSM-STUBD \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test33: test33.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test33 test33.c \
		-lSUPPORTD -lCORED -lDSM-STUBD \
		-lSUPPORTD -lCORED -lDSM-STUBD \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

#
#
# get the rules
#
include $(ITS_ROOT)/config.rules
