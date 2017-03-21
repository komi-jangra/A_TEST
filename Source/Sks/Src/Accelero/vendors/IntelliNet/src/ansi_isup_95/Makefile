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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:53  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:10  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:56  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:54:02  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.3.2.1  2003/05/07 10:49:27  ssingh
# LOG: Latest changes propped from Current to 6.3
# LOG:
# LOG: Revision 7.3  2002/11/28 06:17:09  sjaddu
# LOG: Added COT state files.
# LOG:
# LOG: Revision 7.2  2002/09/06 22:23:01  yranade
# LOG: Remove Wall from Makefile.  That will be in config.vars if relevent
# LOG: for this platform
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.3  2002/08/15 20:26:11  mmiers
# LOG: Warning/error removal
# LOG:
# LOG: Revision 1.2  2002/08/01 15:57:49  ssharma
# LOG: Merge from ISUP_PR7 branch.
# LOG:
# LOG: Revision 1.1.2.5  2002/07/06 20:06:42  hbalimid
# LOG: Fixed all warnings.
# LOG:
# LOG: Revision 1.1.2.4  2002/07/03 23:37:26  hbalimid
# LOG: ANSI95 Specific implementation.
# LOG:
# LOG: Revision 1.1.2.2  2002/07/02 19:56:12  hbalimid
# LOG: syntax error fixed.
# LOG:
# LOG: Revision 1.1.2.1  2002/07/02 02:12:15  hbalimid
# LOG: Makefile for ISUP ANSI95.
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
	  -I../../include -I../../include/ansi -DINCLUDE_CODEC

OBJS= ansi-isup_95.o ansi-generic_state_ansi95.o \
      ansi-idle_ansi95.o ansi-rcvd_in_anm_ansi95.o \
      ansi-sent_out_anm_ansi95.o ansi-wait_in_acm_ansi95.o \
      ansi-wait_in_anm_ansi95.o ansi-wait_out_acm_ansi95.o \
      ansi-wait_in_res_ansi95.o ansi-wait_out_rsc_ansi95.o \
      ansi-wait_out_rlc_ansi95.o ansi-wait_out_res_ansi95.o \
      ansi-wait_out_rel_ansi95.o ansi-wait_out_gra_ansi95.o \
      ansi-wait_out_anm_ansi95.o ansi-wait_in_rlc_ansi95.o \
      ansi-wait_in_cot_ansi95.o ansi-wait_cot_report_ansi95.o \
      ansi-wait_cotreports_and_cra_ansi95.o ansi-wait_in_cra_ansi95.o \
      ansi-wait_cotreports_have_cra_ansi95.o ansi-wait_in_iam_ansi95.o \
      ansi-wait_in_cot_and_iam_ansi95.o ansi-wait_out_iam_ansi95.o

#
# PROTOCOL type
#
ifeq ($(PROTOCOL),ANSI)
all: ../../lib/libANSI_ISUP_95$(DBGSUFFIX).a \
     ../../lib/libANSI_ISUP_95$(DBGSUFFIX).so
else
all:
endif

../../lib/libANSI_ISUP_95$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libANSI_ISUP_95$(DBGSUFFIX).a $(OBJS)

../../lib/libANSI_ISUP_95$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/libANSI_ISUP_95$(DBGSUFFIX).so \
		$(OBJS)

ifeq ($(PROTOCOL),ANSI)
clean:
	$(RM) $(OBJS) \
		../../lib/libANSI_ISUP_95$(DBGSUFFIX).a \
		../../lib/libANSI_ISUP_95$(DBGSUFFIX).so
else
clean:
endif

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
