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
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) -DTRANSPORT_SS7 -DANSI_ISUP_95

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL) -DANSI_ISUP_95\
	-I$(ITS_ROOT)/common/include    \
	-I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
	-I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
	-I$(ITS_ROOT)/ISUP/include      \
	-I$(ITS_ROOT)/TCAP/include      \
	-I$(ITS_ROOT)/tools/include

NMSCFLAGS:= -I$(VENDOR_ROOT)/nms/include

ifeq ($(PROTOCOL),ANSI)
VARLIBS=-lANSI_GENERIC_92$(DBGSUFFIX) -lANSI_ISUP_95$(DBGSUFFIX) -lm
endif

LIBS:= -L$(ITS_ROOT)/common/lib  \
	-L$(ITS_ROOT)/tools/lib \
	-L$(ITS_ROOT)/MTP3/lib  \
	-L$(ITS_ROOT)/ISUP/lib  \
	-L$(ITS_ROOT)/SCCP/lib  \
	-L$(ITS_ROOT)/TCAP/lib  \
	-L$(VENDOR_ROOT)/IntelliNet/lib \
	-lDSM-STUB$(DBGSUFFIX) \
	-lDSM-GCS$(DBGSUFFIX) \
	-lGCS-CLIENT$(DBGSUFFIX) \
	-lDRIVER$(DBGSUFFIX) \
	-lENGINE$(DBGSUFFIX) \
	-lVFrame$(DBGSUFFIX) \
	-l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
	-l$(PROTOCOL)-ISUP$(DBGSUFFIX) \
	$(VARLIBS) -lthread -lnsl

NMSLIBS:= -L$(VENDOR_ROOT)/nms/lib \
	-L/opt/nmstx/lib         \
	-L/opt/nms/lib           \
	-lcta -lctal -lctacl -lcpi \
	-lss7mapi -lhmiapi -lhmimgr

OBJS:= ISUP_SendMsg.o ISUP_PrintMsg.o ISUP_ReadMsg.o \
       ISUP_ProcessMsg.o ISUP_PrintCic.o ISUP_ProcessCic.o

LIBOBJS:= ISUP_Test.o

# ISUP with IntelliNet MTP3 and NMS MTP2
all: ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX) \
     libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so

libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS)

ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX): $(OBJS) $(LIBOBJS) ISUP_Main.o
	$(CC) $(CFLAGS) $(NMSCFLAGS) -o $@ $(OBJS) $(LIBOBJS) ISUP_Main.o \
	$(LIBS) $(NMSLIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt

# All cleans here

clean:
	$(RM) $(OBJS) $(LIBOBJS) ISUP_Main.o
	$(RM) libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX)

# get the rules
#
include	$(ITS_ROOT)/config.rules
