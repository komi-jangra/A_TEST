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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:28 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:23:57  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:32  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:40  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:50:38  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:53  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.5  2000/09/02 01:39:30  mmiers
# LOG: Use default value for MAKE, update tests.
# LOG:
# LOG: Revision 3.4  2000/09/01 23:31:37  lbana
# LOG:
# LOG:
# LOG: Tracking down bugs.
# LOG:
# LOG: Revision 3.3  2000/09/01 20:56:29  mmiers
# LOG: Debugging zero copy.
# LOG:
# LOG: Revision 3.2  2000/08/31 19:18:38  lbana
# LOG: Something foul here.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:02:50  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.1  2000/07/27 18:41:30  mmiers
# LOG:
# LOG:
# LOG: Cleanup for rev3 build.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:25:15  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.5  1998/10/23 17:31:09  jrao
# LOG: HP build.
# LOG:
# LOG: Revision 1.4  1998/10/23 17:14:57  jrao
# LOG: Update for HPUX build
# LOG:
# LOG: Revision 1.3  1998/10/23 17:08:51  jrao
# LOG: Update Makefile for UNIX build.
# LOG:
# LOG: Revision 1.2  1998/09/22 23:56:31  jrao
# LOG: Changes made to accomodate HPUX code
# LOG:
# LOG: Revision 1.1  1998/06/23 02:31:07  mmiers
# LOG: Update Solaris build environment.  Part of getting SCCP working.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

OBJS=    test.o
OBJS2=   test2.o
CFLAGS := $(CFLAGS) -I../include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/tools/include -I$(ITS_ROOT)/TCAP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include
CXXFLAGS := $(CXXFLAGS) -I../include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/tools/include -I$(ITS_ROOT)/TCAP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include

all: test

clean:
	$(RM) $(OBJS) .depend

test: $(OBJS)
	$(CXX) $(CXXFLAGS) -o test $(OBJS) -L../lib -L$(ITS_ROOT)/SCCP/lib \
          -L$(ITS_ROOT)/MTP3/lib -L$(ITS_ROOT)/ISUP/lib -L$(ITS_ROOT)/SLTM/lib \
          -L$(ITS_ROOT)/common/lib \
          -L$(ITS_ROOT)/tools/lib -L$(VENDOR_ROOT)/$(VENDOR)/lib \
          -lCCITT-TCAPD -lCCITT-SCCPD -lCCITT-ISUPD -lCCITT-MTP3D -lCCITT-SLTMD \
          -lSUPPORT++D -lCCITT-VENDORD -lASND -lCORE++D -lCCITT-IMALD \
          -lCCITT-TCAPD -lCCITT-SCCPD -lCCITT-ISUPD -lCCITT-MTP3D -lCCITT-SLTMD \
          -lSUPPORT++D -lCCITT-VENDORD -lASND -lCORE++D -lCCITT-IMALD \
          -lCCITT-TCAPD -lCCITT-SCCPD -lCCITT-ISUPD -lCCITT-MTP3D -lCCITT-SLTMD \
          -lSUPPORT++D -lCCITT-VENDORD -lASND -lCORE++D -lCCITT-IMALD \
          -lUNITTEST $(SOCKLIBS) $(THREADLIBS)

test2: $(OBJS2)
	$(CXX) $(CXXFLAGS) -o test2 $(OBJS2) -L../lib -L$(ITS_ROOT)/SCCP/lib \
          -L$(ITS_ROOT)/MTP3/lib -L$(ITS_ROOT)/ISUP/lib -L$(ITS_ROOT)/SLTM/lib \
          -L$(ITS_ROOT)/common/lib \
          -L$(ITS_ROOT)/tools/lib -L$(VENDOR_ROOT)/$(VENDOR)/lib \
          -lCCITT-TCAPD -lCCITT-SCCPD -lCCITT-ISUPD -lCCITT-MTP3D -lCCITT-SLTMD \
          -lSUPPORT++D -lCCITT-VENDORD -lASND -lCORE++D -lCCITT-IMALD -lCORE++D \
          -lCCITT-TCAPD -lCCITT-SCCPD -lCCITT-ISUPD -lCCITT-MTP3D -lCCITT-SLTMD \
          -lSUPPORT++D -lCCITT-VENDORD -lASND -lCORE++D -lCCITT-IMALD \
          -lCCITT-TCAPD -lCCITT-SCCPD -lCCITT-ISUPD -lCCITT-MTP3D -lCCITT-SLTMD \
          -lSUPPORT++D -lCCITT-VENDORD -lASND -lCORE++D -lCCITT-IMALD \
          -lUNITTEST $(SOCKLIBS) $(THREADLIBS)
#
# get the rules
#
include $(ITS_ROOT)/config.rules
