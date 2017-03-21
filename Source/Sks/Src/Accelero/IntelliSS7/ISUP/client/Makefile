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
# $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:19 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:23:46  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:13:05  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:52:00  cvsadmin
# Begin PR6.5
#
# Revision 1.2  2005/03/23 07:26:06  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 1.1.2.1.6.1  2004/01/05 09:48:02  sjaddu
# Merged code from tcs isup branch.
#
# Revision 1.1.2.1.2.8  2003/12/19 04:42:32  akumar
# Modified for cleanup to work fine.
#
# Revision 1.1.2.1.2.7  2003/10/15 09:04:51  akumar
# Updated to accomodate ANSI and ITU variant.
#
# Revision 1.1.2.1.2.6  2003/09/24 14:15:16  sjaddu
# Variant = 95 or 97
#
# Revision 1.1.2.1.2.5  2003/09/19 08:31:32  akumar
# Final shot at Makefile.
#
# Revision 1.1.2.1.2.4  2003/08/29 10:09:59  akumar
# CODEC suffix for ITU variants also.
#
# Revision 1.1.2.1.2.3  2003/08/29 09:53:22  akumar
# Lil' Modifications.
#
# Revision 1.1.2.1.2.2  2003/08/28 15:34:43  sjaddu
# Changed the isup lib name to coedc.
#
# Revision 1.1.2.1.2.1  2003/08/26 12:47:48  sjaddu
# Redundancy changes done.
#
# Revision 1.1.2.1  2003/06/04 13:14:10  sjaddu
# Added Makefile for isup client.
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars


DEFINES:=$(DEFINES) 

CFLAGS:=$(CFLAGS) -g -I./include -DUSE_HEAP -DUNIX -DSOLARIS -D$(PROTOCOL)\
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/TCAP/include      \
        -I../include \
	-I$(ITS_ROOT)/tools/include

LIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/ISUP/lib  \
       -lCORE$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) \
       -lthread -lnsl

#       -l$(PROTOCOL)-ISUP$(DBGSUFFIX) 

COBJS:= clientapi.o clientimpl.o

# Restrict the user to give explicit targets
all:  client ../lib/lib$(PROTOCOL)-ClientLayer$(DBGSUFFIX).so 

../lib/lib$(PROTOCOL)-ClientLayer$(DBGSUFFIX).so: $(COBJS)
			$(SHAREDAR) $(SHAREDARFLAGS) \
			$@ $(COBJS) $(LIBS)

OBJS= ../src/isup.o
VOBJS= ../src/isup_cmn.o  ../src/isup_variants.o


ifeq ($(PROTOCOL),ANSI)
VARIANT=95
ifeq ($(VARIANT),95)
client: print ../lib/lib$(PROTOCOL)-ISUP95_CODEC$(DBGSUFFIX).so
CFLAGS :=  $(CFLAGS)  -DMULTI_CLIENT -DANSI_ISUP_95
print:
	@echo ----- Building ANSI 95 VARIANT library. -----

../lib/lib$(PROTOCOL)-ISUP95_CODEC$(DBGSUFFIX).so: $(OBJS) $(VOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(OBJS) $(VOBJS)
else 
client: clean print ../lib/lib$(PROTOCOL)-ISUP92_CODEC$(DBGSUFFIX).so
print:
	@echo ----- Building ANSI 92 VARIANT library. -----

../lib/lib$(PROTOCOL)-ISUP92_CODEC$(DBGSUFFIX).so: $(OBJS) $(VOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(OBJS) $(VOBJS)
endif
else
client:
endif

ifeq ($(PROTOCOL),CCITT)
VARIANT=97
ifeq ($(VARIANT),97)
client: clean print ../lib/lib$(PROTOCOL)-ISUP97_CODEC$(DBGSUFFIX).so
CFLAGS :=  $(CFLAGS)  -DMULTI_CLIENT -DITU_ISUP_97
print:
	@echo ----- Building ITU 97 VARIANT library. -----

../lib/lib$(PROTOCOL)-ISUP97_CODEC$(DBGSUFFIX).so: $(OBJS) $(VOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(OBJS) $(VOBJS)
else 
client: clean print ../lib/lib$(PROTOCOL)-ISUP93_CODEC$(DBGSUFFIX).so
print:
	@echo ----- Building ITU 93 VARIANT library. -----

../lib/lib$(PROTOCOL)-ISUP93_CODEC$(DBGSUFFIX).so: $(OBJS) $(VOBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(OBJS) $(VOBJS)
endif
else
client:
endif

clean:
	$(RM) $(COBJS) $(OBJS) $(VOBJS) \

ifeq ($(PROTOCOL),CCITT)
	$(RM) ../lib/lib$(PROTOCOL)-ISUP97_CODEC$(DBGSUFFIX).so ../lib/lib$(PROTOCOL)-ISUP93_CODEC$(DBGSUFFIX).so ../lib/lib$(PROTOCOL)-ClientLayer$(DBGSUFFIX).so 

else
	$(RM) ../lib/lib$(PROTOCOL)-ISUP95_CODEC$(DBGSUFFIX).so ../lib/lib$(PROTOCOL)-ISUP92_CODEC$(DBGSUFFIX).so ../lib/lib$(PROTOCOL)-ClientLayer$(DBGSUFFIX).so 
endif


#
# get the rules
#
include	$(ITS_ROOT)/config.rules
