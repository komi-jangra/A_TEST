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
# $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

PROTOCOL=CCITT
NODE=ALL
DEFINES:=$(DEFINES) 

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -D$(NODE) -DSOLARIS -D$(PROTOCOL) -DITU_ISUP_97\
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
       -lCCITT-ISUP97_CODEC$(DBGSUFFIX) \
       -lCCITT-ClientLayer$(DBGSUFFIX) \
       -lthread -lnsl -lsocket -lmtmalloc



OBJS:= load.o main.o

# Restrict the user to give explicit targets
all:   ltest$(DBGSUFFIX)

ltest$(DBGSUFFIX): $(OBJS)
	$(CC) $(CFLAGS) -o \
	$@ $(OBJS) $(LIBS) -ldl -lrt

clean:
	$(RM) *.o *.so $(OBJS)  ltest$(DBGSUFFIX)

#
# get the rules
#
include	$(ITS_ROOT)/config.rules

