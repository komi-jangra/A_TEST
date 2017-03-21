############################################################################
#                                                                          #
#     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:23:49  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:13:08  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:52:05  cvsadmin
# Begin PR6.5
#
# Revision 1.2  2005/03/23 07:26:07  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 1.1.2.5.6.1  2004/01/05 09:51:59  sjaddu
# Merged code from tcs isup branch.
#
# Revision 1.1.2.5.2.5  2003/11/03 05:09:05  sjaddu
# Added debug suffix.
#
# Revision 1.1.2.5.2.4  2003/09/18 06:11:00  akumar
# Final shot.
#
# Revision 1.1.2.5.2.3  2003/09/15 11:18:45  akumar
# Variant problem fixed.
#
# Revision 1.1.2.5.2.2  2003/08/29 09:59:08  akumar
# Just to work with GCS.
#
# Revision 1.1.2.5.2.1  2003/08/28 15:18:29  sjaddu
# Changed the isup lib isup codec lib.
#
# Revision 1.1.2.5  2003/07/22 06:16:38  sjaddu
# testing testing
#
# Revision 1.1.2.4  2003/06/30 05:01:05  sjaddu
# Removed printCIC.o form makefile.
#
# Revision 1.1.2.3  2003/06/26 04:18:55  sjaddu
# ansi 95 compile flag added.
#
# Revision 1.1.2.2  2003/06/18 09:05:23  tsanthosh
# Added more functionality.
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

ifeq ($(PROTOCOL),ANSI)
VARIANT=95
else
VARIANT=97
endif

DEFINES:=$(DEFINES) 

#-DANSI_ISUP_95 
CFLAGS:=$(CFLAGS) -g -I./include -DUSE_HEAP -DUNIX -DSOLARIS -D$(PROTOCOL) -D$(PROTOCOL)_ISUP_$(VARIANT) \
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/ISUP/include/ansi      \
        -I$(ITS_ROOT)/TCAP/include      \
        -I ../include \
	-I$(ITS_ROOT)/tools/include  \
        -I$(ITS_ROOT)/ISUP/client \
        -I$(ITS_ROOT)/ISUP/test

FROM:= ../

ISUPLIBS = -l$(PROTOCOL)-ISUP$(VARIANT)_CODEC$(DBGSUFFIX) -l$(PROTOCOL)-ClientLayer$(DBGSUFFIX) 

LIBS:= -L ../../lib  \
       -L $(ITS_ROOT)/common/lib \
       -L $(ITS_ROOT)/tools/lib \
       -L $(ITS_ROOT)/MTP3/lib \
       -L $(ITS_ROOT)/ISUP/lib \
       -L $(ITS_ROOT)/TCAP/lib \
       -L $(ITS_ROOT)/SCCP/lib \
       -L $(ITS_ROOT)/SLTM/lib  \
       -L $(ITS_ROOT)/SNMM/lib  \
       -L $(VENDOR_ROOT)/IntelliNet/lib \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lDSM-GCS$(DBGSUFFIX) \
       -lGCS-CLIENT$(DBGSUFFIX) \
       $(ISUPLIBS) \
       -lthread -lnsl -lsocket -lmtmalloc



OBJS:= $(FROM)sendISUPMsg.o $(FROM)printISUPMsg.o $(FROM)readISUPMsg.o dbc_server.o test.o

# Restrict the user to give explicit targets
all:   test$(DBGSUFFIX)

test$(DBGSUFFIX): $(OBJS)
			$(CC) $(CFLAGS) -o \
			$@ $(OBJS) $(LIBS) -ldl -lrt

clean:
	$(RM) *.o *.so $(OBJS)

#
# get the rules
#
include	$(ITS_ROOT)/config.rules

