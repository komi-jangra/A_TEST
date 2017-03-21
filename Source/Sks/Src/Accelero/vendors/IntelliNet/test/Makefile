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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:55  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:13  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:55:02  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:54:14  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.8  2002/02/27 23:07:44  mmiers
# LOG: Post throughput testing.
# LOG:
# LOG: Revision 1.7  2002/02/26 16:42:26  mmiers
# LOG: Add clean target
# LOG:
# LOG: Revision 1.6  2002/02/14 22:13:09  mmiers
# LOG: Commit tests as is.
# LOG:
# LOG: Revision 1.5  2002/02/01 22:12:26  mmiers
# LOG: ISUP integration
# LOG:
# LOG: Revision 1.4  2002/01/30 21:20:34  mmiers
# LOG: Change back to ANSI
# LOG:
# LOG: Revision 1.3  2001/12/28 18:43:40  mmiers
# LOG: A few mistakes to fix.
# LOG:
# LOG: Revision 1.2  2001/12/19 18:03:02  mmiers
# LOG: Adax testing on Solaris revealed several build flaws.
# LOG:
#
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

CFLAGS := $(CFLAGS) \
          -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include \
	  -I../include
LIBS=-L$(ITS_ROOT)/common/lib -lENGINE$(DBGSUFFIX) -lVFrame$(DBGSUFFIX) \
     -L../lib -lCCITT-VENDOR$(DBGSUFFIX)

all: test1 test2

test1: test1.o
	$(CC) -o test1 test1.o $(LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

test2: test2.o
	$(CC) -o test2 test2.o $(LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

clean:
	$(RM) *.o test1 test2

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules

