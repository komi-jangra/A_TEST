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
# $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:23 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:59  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:15:18  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:55:16  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:54:28  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:10:39  mmiers
# Begin PR6.2
#
# Revision 1.2  2002/05/20 15:58:50  sjaddu
# Merge from PR6, remove unwanted directories.
#
# Revision 1.1.2.1  2002/04/13 04:43:13  hbalimid
# ISUP load test with NMS MTP3 baseline
#
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) -DTRANSPORT_SS7

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL)\
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/TCAP/include      \
	-I$(ITS_ROOT)/tools/include

NMSCFLAGS:= -I$(VENDOR_ROOT)/nms/include

SBECFLAGS:= -I$(VENDOR_ROOT)/sbe/include

ADAXCFLAGS:= -I$(VENDOR_ROOT)/adax/include

LIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/tools/lib \
       -L$(ITS_ROOT)/MTP3/lib  \
       -L$(ITS_ROOT)/ISUP/lib  \
       -L$(ITS_ROOT)/SCCP/lib  \
       -L$(ITS_ROOT)/TCAP/lib  \
       -L$(ITS_ROOT)/SLTM/lib  \
       -L$(ITS_ROOT)/SNMM/lib  \
       -L$(VENDOR_ROOT)/IntelliNet/lib \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX) \
       -lthread -lnsl

NMSLIBS:= -L$(VENDOR_ROOT)/nms/lib \
          -L/opt/nmstx/lib         \
          -L/opt/nms/lib           \
          -lcta -lctal -lctacl -lcpi -lmtp3api \
          -lss7mapi -lhmiapi -lhmimgr

SBELIBS:= -L$(VENDOR_ROOT)/sbe/lw/lib \
          -lSBEVendor$(DBGSUFFIX) -lsbe

ADAXLIBS:= -L$(VENDOR_ROOT)/adax/lib \
          -lADAXVendor$(DBGSUFFIX)


LIBOBJS:= load.o

# Restrict the user to give explicit targets
all:
	@echo "\nPlease specify one of the following targets:"
	@echo "nmsmtp2 sbemtp2 adaxmtp2\n"

# ISUP with IntelliNet MTP3 and NMS MTP2
nmsmtp2: nmsmtp2/load-nms3-nms2-$(PROTOCOL) \
         nmsmtp2/libload-nms3-nms2-$(PROTOCOL).so

nmsmtp2/libload-nms3-nms2-$(PROTOCOL).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS)

nmsmtp2/load-nms3-nms2-$(PROTOCOL): main.o
	$(CC) $(CFLAGS) $(NMSCFLAGS) -o $@ main.o \
	$(LIBS) $(NMSLIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt


# ISUP with IntelliNet MTP3 and SBE MTP2
sbemtp2: sbemtp2/load-nms3-sbe2-$(PROTOCOL) \
         sbemtp2/libload-nms3-sbe2-$(PROTOCOL).so

sbemtp2/libload-nms3-sbe2-$(PROTOCOL).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS)

sbemtp2/load-nms3-sbe2-$(PROTOCOL): main.o
	$(CC) $(CFLAGS) $(SBEFLAGS) -o $@ main.o \
	$(LIBS) $(SBELIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt


# ISUP with IntelliNet MTP3 and ADAX MTP2
adaxmtp2: adaxmtp2/load-nms3-adax2-$(PROTOCOL) \
         adaxmtp2/libload-nms3-adax2-$(PROTOCOL).so

adaxmtp2/libload-nms3-adax2-$(PROTOCOL).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS)

adaxmtp2/load-nms3-adax2-$(PROTOCOL): main.o
	$(CC) $(CFLAGS) $(SBEFLAGS) -o $@ main.o \
	$(LIBS) $(SBELIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt

# All cleans here

clean:
	@echo "\nPlease specify one of the following targets:"
	@echo "nmsclean sbeclean adaxclean\n"

nmsclean:
	$(RM) $(LIBOBJS) nmsmtp2/libload-nms3-nms2-$(PROTOCOL).so
	$(RM) main.o nmsmtp2/load-nms3-nms2-$(PROTOCOL)

sbeclean:
	$(RM) $(LIBOBJS) sbemtp2/libload-nms3-sbe2-$(PROTOCOL).so
	$(RM) main.o sbemtp2/load-nms3-sbe2-$(PROTOCOL)

adaxclean:
	$(RM) $(LIBOBJS) adaxmtp2/libload-nms3-adax2-$(PROTOCOL).so
	$(RM) main.o adaxmtp2/load-nms3-adax2-$(PROTOCOL)

#
# get the rules
#
include	$(ITS_ROOT)/config.rules
