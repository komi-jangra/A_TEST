############################################################################
#                                                                          #
#     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#                                                                          #
# $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:29 bsccs2 Exp $                                                                                                     #
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:23:59  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:48:55  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:13:34  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:52:42  cvsadmin
# Begin PR6.5
#
# Revision 1.2  2003/10/10 04:42:27  sswami
# TCAP related changes
#
# Revision 1.1  2003/10/07 12:40:58  sswami
# Makefile for Test application [TCAP multiple App binding]
#                                                                          #
#                                                                          #
############################################################################
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) 

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL) \
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/TCAP/include      \
        -I ../include \
	-I$(ITS_ROOT)/tools/include  \
        -I$(ITS_ROOT)/TCAP/client 

FROM:= ../

TCAPLIBS = -l$(PROTOCOL)-TCAP-Codec$(DBGSUFFIX) -lClient-Layer$(DBGSUFFIX) 

LIBS:= -L ../../lib  \
       -L $(ITS_ROOT)/common/lib \
       -L $(ITS_ROOT)/tools/lib \
       -L $(ITS_ROOT)/MTP3/lib \
       -L $(ITS_ROOT)/TCAP/lib \
       -L $(ITS_ROOT)/SCCP/lib \
       -L $(ITS_ROOT)/SLTM/lib  \
       -L $(ITS_ROOT)/SNMM/lib  \
       -L $(VENDOR_ROOT)/IntelliNet/lib \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       $(TCAPLIBS) \
       -lthread -lnsl -lsocket -lmtmalloc



OBJS:= test.o

# Restrict the user to give explicit targets
all:   test

test: $(OBJS)
			$(CC) $(CFLAGS) -o \
			$@ $(OBJS) $(LIBS) -ldl -lrt

clean:
	$(RM) *.o *.so $(OBJS) 

#
# get the rules
#
include	$(ITS_ROOT)/config.rules

