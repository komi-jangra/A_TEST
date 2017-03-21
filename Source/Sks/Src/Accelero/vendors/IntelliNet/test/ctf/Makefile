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
# get the vars
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
#  LOG: $Log: not supported by cvs2svn $
#  LOG: Revision 1.1.1.1  2007/10/04 13:24:56  bsccs2
#  LOG: init tree
#  LOG:
#  LOG: Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
#  LOG: BscCs2
#  LOG:
#  LOG: Revision 1.1.1.1  2007/03/08 15:15:14  cvsadmin
#  LOG: BSC project
#  LOG:
#  LOG: Revision 9.1  2005/03/23 12:55:05  cvsadmin
#  LOG: Begin PR6.5
#  LOG:
#  LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
#  LOG: PR6.4.2 sources propagated to Current.
#  LOG:
#  LOG: Revision 1.1.2.1  2004/08/10 07:52:04  ssingh
#  LOG: Initial commits for CTF Event Trace Client (base-code).
#  LOG:

include $(VENDOR_ROOT)/config.vars

PROTOCOL=ANSI

CFLAGS := $(CFLAGS) \
      -I$(ITS_ROOT)/common/include \
      -I$(ITS_ROOT)/MTP2/include \
      -I$(ITS_ROOT)/MTP3/include \
      -I$(ITS_ROOT)/SNMM/include \
      -I$(ITS_ROOT)/SLTM/include \
      -I$(ITS_ROOT)/ISUP/include \
      -I$(ITS_ROOT)/SCCP/include \
      -I$(ITS_ROOT)/TCAP/include

OBJS= TRACE_Main.o

LIBS:= -L$(ITS_ROOT)/common/lib \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -lthread -lnsl -lmtmalloc -lrt -lsocket

#
# PROTOCOL type
#
all:libClient$(DBGSUFFIX).so Client$(DBGSUFFIX)

Client$(DBGSUFFIX): $(OBJS)
	$(CC) $(CFLAGS) -o \
            $@ $(OBJS) $(LIBS) -lClient$(DBGSUFFIX) -ldl -lrt

LIB_OBJS= TRACE_Test.o

libClient$(DBGSUFFIX).so: $(LIB_OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) libClient$(DBGSUFFIX).so $(LIB_OBJS)


clean:
	$(RM) -rf *.o *.so Client$(DBGSUFFIX) 


#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
