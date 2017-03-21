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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:04 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:38  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:17  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:33  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:01  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:43  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:15  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:17  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.3  2001/05/16 20:10:53  mmiers
# LOG: Locating bottlenecks.
# LOG:
# LOG: Revision 4.2  2001/05/16 01:52:56  mmiers
# LOG: Try to get this working again.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:20  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 1.2  2001/04/30 20:55:12  mmiers
# LOG: Checkin test.
# LOG:
# LOG: Revision 1.1  2001/04/10 17:13:13  mmiers
# LOG: Throughput test.
# LOG:
# LOG: Revision 1.6  2001/04/04 22:01:31  mmiers
# LOG: Finish debugging.
# LOG:
# LOG: Revision 1.5  2001/04/03 23:56:56  mmiers
# LOG: Debugging.
# LOG:
# LOG: Revision 1.4  2001/04/03 01:11:57  mmiers
# LOG:
# LOG: Debugging.
# LOG:
# LOG: Revision 1.3  2001/03/30 23:38:00  mmiers
# LOG: More engine debugging.
# LOG:
# LOG: Revision 1.2  2001/03/30 21:03:34  mmiers
# LOG: Testing.
# LOG:
# LOG: Revision 1.1  2001/03/29 03:07:34  mmiers
# LOG: Start debugging.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include
LIBS=-L../../lib -lENGINE

all: test libTHROUGH.so

clean:
	$(RM) *.o *.so test

test: test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test test.c $(LIBS) \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

libTHROUGH.so: through.o
	$(SHAREDAR) $(SHAREDARFLAGS) libTHROUGH.so through.o

#
# get the rules
#
include $(ITS_ROOT)/config.rules
