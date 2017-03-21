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
# $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:21 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:58  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:28  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:15:16  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:55:07  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:54:21  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1.4.1  2003/07/04 06:30:11  gururaj
# Modified the file for Linux builds
#
# Revision 7.1  2002/08/26 22:10:39  mmiers
# Begin PR6.2
#
# Revision 1.1  2002/06/05 22:16:48  sjaddu
# Added Makefile for ISUP/SCTP.
#
# Revision 1.2  2002/05/20 15:58:49  sjaddu
# Merge from PR6, remove unwanted directories.
#
# Revision 1.1.2.4  2002/05/15 21:33:01  hbalimid
# Updated to let 97 variant compile
#
# Revision 1.1.2.3  2002/05/09 18:40:21  labuser
# Merge from ISUP_APR_19_2002 to PR6.
#
# Revision 1.1.2.2.2.1  2002/04/24 22:12:12  labuser
# modified to get CIC status
#
# Revision 1.1.2.2  2002/04/12 22:33:36  hbalimid
# updated to accomodate the new directory structure
#
# Revision 1.1.2.1  2002/04/12 20:22:28  hbalimid
# for ftest; ISUP with IntelliNet MTP3 and NMS MTP2
#
# Revision 1.1.2.1  2002/04/12 19:55:59  hbalimid
# Changed to accomodate multiple vendors at layer2
#
# Revision 1.1.2.1  2002/04/11 01:50:56  hbalimid
# Baseline for ISUP functional test - organized per MTP3 vendor
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) -DTRANSPORT_SS7 -DITU_ISUP_97

FROM:= ../

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
       -L$(ITS_ROOT)/lib \
       -lDSM-STUB$(DBGSUFFIX) \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       -lITU_GENERIC_93$(DBGSUFFIX) \
       -lITU_ISUP_97$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX) 

NMSLIBS:= -L$(VENDOR_ROOT)/nms/lib \
          -L/opt/nmstx/lib         \
          -L/opt/nms/lib           \
          -lcta -lctal -lctacl -lcpi -lmtp3api \
          -lss7mapi -lhmiapi -lhmimgr

SBELIBS:= -L$(VENDOR_ROOT)/sbe/lw/lib \
          -lSBEVendor$(DBGSUFFIX) -lsbe

ADAXLIBS:= -L$(VENDOR_ROOT)/adax/lib \
          -lADAXVendor$(DBGSUFFIX)

SCTPLIBS:=-lUAL$(DBGSUFFIX) -l$(PROTOCOL)-M3UA$(DBGSUFFIX) -lUAL$(DBGSUFFIX)


OBJS:= $(FROM)sendISUPMsg.o $(FROM)printISUPMsg.o $(FROM)readISUPMsg.o

LIBOBJS:= ../intellimtp3/ftest.o
MAINOBJS:= ../intellimtp3/main.o

# Restrict the user to give explicit targets
all:
	@echo "\nPlease specify one of the following targets:"
	@echo "nmsmtp2 sbemtp2 adaxmtp2\n"
	@echo "Note: To build packages, use \"make pkg\"\n"

# ISUP with IntelliNet MTP3 and NMS MTP2
nmsmtp2: nmsmtp2/ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX) \
         nmsmtp2/libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so

nmsmtp2/libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS)

nmsmtp2/ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX): $(OBJS) $(MAINOBJS) \
        $(FROM)printCic.o 
	$(CC) $(CFLAGS) $(NMSCFLAGS) -o $@ $(OBJS) $(MAINOBJS) $(FROM)printCic.o \
	$(LIBS) $(NMSLIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt


# ISUP with IntelliNet MTP3 and SBE MTP2
sbemtp2: sbemtp2/ftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX) \
         sbemtp2/libftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX).so

sbemtp2/libftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS)

sbemtp2/ftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX): $(OBJS) main.o $(FROM)printCic.o
	$(CC) $(CFLAGS) $(SBEFLAGS) -o $@ $(OBJS) main.o $(FROM)printCic.o \
	$(LIBS) $(SBELIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt


# ISUP with IntelliNet MTP3 and ADAX MTP2
adaxmtp2: adaxmtp2/ftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX) \
         adaxmtp2/libftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX).so

adaxmtp2/libftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	$@ $(LIBOBJS)

adaxmtp2/ftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX): $(OBJS) main.o $(FROM)printCic.o
	$(CC) $(CFLAGS) $(SBEFLAGS) -o $@ $(OBJS) main.o $(FROM)printCic.o \
	$(LIBS) $(SBELIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt

sctp: lib-SCTP$(DBGSUFFIX).so sctpD

lib-SCTP$(DBGSUFFIX).so: $(LIBOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) lib-SCTP$(DBGSUFFIX).so $(LIBOBJS)

sctpD:$(OBJS) $(MAINOBJS) $(FROM)printCic.o 
	$(CC) $(CFLAGS) -o sctpD $(OBJS) $(MAINOBJS) $(FROM)printCic.o  $(LIBS) $(SCTPLIBS) $(SOCKLIBS) $(THREADLIBS) -ldl -lrt

sctpclean:
	$(RM) *.o *.so sctpD $(OBJS) $(FROM)printCic.o
# All cleans here

clean:
	@echo "\nPlease specify one of the following targets:"
	@echo "nmsclean sbeclean adaxclean\n"

nmsclean:
	$(RM) $(LIBOBJS) nmsmtp2/libftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) main.o $(OBJS) $(FROM)printCic.o nmsmtp2/ftest-intelli3-nms2-$(PROTOCOL)$(DBGSUFFIX)

sbeclean:
	$(RM) $(LIBOBJS) sbemtp2/libftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) main.o $(OBJS) $(FROM)printCic.o sbemtp2/ftest-intelli3-sbe2-$(PROTOCOL)$(DBGSUFFIX)

adaxclean:
	$(RM) $(LIBOBJS) adaxmtp2/libftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX).so
	$(RM) main.o $(OBJS) $(FROM)printCic.o adaxmtp2/ftest-intelli3-adax2-$(PROTOCOL)$(DBGSUFFIX)
#
# get the rules
#
include	$(ITS_ROOT)/config.rules
