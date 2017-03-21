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
# LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:11  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:57  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:54:05  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.2  2003/01/22 09:21:52  akumar
# LOG: Modified for COT Procedure
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:30  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.4  2002/08/01 15:57:49  ssharma
# LOG: Merge from ISUP_PR7 branch.
# LOG:
# LOG: Revision 6.3.2.1  2002/07/06 20:06:42  hbalimid
# LOG: Fixed all warnings.
# LOG:
# LOG: Revision 6.3  2002/06/24 17:00:44  ssingh
# LOG: Phase 3 missing functionality and auto timer handling.
# LOG:
# LOG: Revision 6.2  2002/05/20 15:49:09  sjaddu
# LOG: Merge from PR6.
# LOG:
# LOG: Revision 1.4.2.4  2002/05/14 18:12:17  sjaddu
# LOG: Added MTP3 Indications.
# LOG:
# LOG: Revision 1.4.2.3  2002/03/28 20:55:42  ssharma
# LOG: Add new file.
# LOG:
# LOG: Revision 1.4.2.2  2002/03/19 17:38:22  ssharma
# LOG: Add itu-timers.c to build.
# LOG:
# LOG: Revision 1.4.2.1  2002/03/05 14:54:02  ssharma
# LOG: Add new file that contains parameter level validation functions.
# LOG:
# LOG: Revision 1.4  2002/02/20 23:24:21  ssharma
# LOG: Fix traces and Makefile.
# LOG:
# LOG: Revision 1.3  2002/02/13 23:36:43  mmiers
# LOG: Build the variants better.
# LOG:
# LOG: Revision 1.2  2002/02/13 23:23:05  mmiers
# LOG: Warning removal, debug.
# LOG:
# LOG: Revision 1.1  2002/02/13 18:28:33  mmiers
# LOG: Finish off the ISUP integration.  Still need to add CHINA
# LOG: variant lib.
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
	  -I../../include -I../../include/itu -DINCLUDE_CODEC

OBJS	=itu-isup_93.o  itu-validate_param.o itu-timers.o \
         itu-wait_in_acm_itu93.o  itu-wait_in_anm_itu93.o  \
         itu-wait_in_res_itu93.o  itu-wait_in_rlc_itu93.o  \
         itu-wait_out_acm_itu93.o itu-wait_out_anm_itu93.o \
         itu-wait_out_res_itu93.o itu-wait_out_rlc_itu93.o \
         itu-rcvd_in_anm_itu93.o  itu-sent_out_anm_itu93.o \
         itu-wait_out_rel_itu93.o itu-idle_itu93.o \
         itu-wait_out_rsc_itu93.o itu-csc_itu93.o \
         itu_generic_state_itu93.o itu-wait_out_gra_itu93.o \
         itu-wait_in_cot_itu93.o itu-wait_cot_report_itu93.o

#
# PROTOCOL type
#
ifeq ($(PROTOCOL),CCITT)
all: ../../lib/libITU_GENERIC_93$(DBGSUFFIX).a \
     ../../lib/libITU_GENERIC_93$(DBGSUFFIX).so
else
all:
endif

../../lib/libITU_GENERIC_93$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libITU_GENERIC_93$(DBGSUFFIX).a $(OBJS)

../../lib/libITU_GENERIC_93$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/libITU_GENERIC_93$(DBGSUFFIX).so \
		$(OBJS)

ifeq ($(PROTOCOL),CCITT)
clean:
	$(RM) $(OBJS) \
		../../lib/libITU_GENERIC_93$(DBGSUFFIX).a \
		../../lib/libITU_GENERIC_93$(DBGSUFFIX).so
else
clean:
endif

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
