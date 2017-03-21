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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:08  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:51  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:53:54  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.3.4.1  2003/05/07 10:32:01  ssingh
# LOG: Added CRM/CRA related object files.
# LOG:
# LOG: Revision 7.3  2002/10/30 08:38:37  sjaddu
# LOG: Added cot files ansi-wait_in_cot_ansi92 and ansi-wait_cot_report_ansi92.
# LOG:
# LOG: Revision 7.2  2002/09/06 22:22:40  yranade
# LOG: Remove Wall from the flags.  That will be in config.vars if it's
# LOG: relevent on this platform.
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.3  2002/08/15 20:26:11  mmiers
# LOG: Warning/error removal
# LOG:
# LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
# LOG: Merge from ISUP_PR7 branch.
# LOG:
# LOG: Revision 1.1.2.7  2002/07/13 02:29:13  hbalimid
# LOG: Added Inter-state procedures.
# LOG:
# LOG: Revision 1.1.2.6  2002/07/12 01:02:00  hbalimid
# LOG: UCIC procedures added.
# LOG:
# LOG: Revision 1.1.2.5  2002/07/10 18:41:38  hbalimid
# LOG: CPC outgoing statemachine implemented.
# LOG:
# LOG: Revision 1.1.2.4  2002/07/06 18:33:04  hbalimid
# LOG: CVTR state implemented.
# LOG:
# LOG: Revision 1.1.2.3  2002/07/06 06:09:59  hbalimid
# LOG: Tookcare of all warnings.
# LOG:
# LOG: Revision 1.1.2.2  2002/07/02 23:19:34  ssingh
# LOG: Added ANSI92 specific changes.
# LOG: Timer handling and GRS/GRA implemented.
# LOG:
# LOG: Revision 1.1.2.1  2002/07/01 20:06:35  hbalimid
# LOG: Makefile for ISUP ANSI92.
# LOG:
#
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

PROTOCOL=ANSI

CFLAGS := $(CFLAGS) \
          -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include \
	  -I../../include -I../../include/ansi -DINCLUDE_CODEC

OBJS= ansi-isup_92.o ansi-timers.o \
      ansi-wait_in_acm_ansi92.o  ansi-wait_in_anm_ansi92.o  \
      ansi-wait_in_res_ansi92.o  ansi-wait_in_rlc_ansi92.o  \
      ansi-wait_out_acm_ansi92.o ansi-wait_out_anm_ansi92.o \
      ansi-wait_out_res_ansi92.o ansi-wait_out_rlc_ansi92.o \
      ansi-rcvd_in_anm_ansi92.o  ansi-sent_out_anm_ansi92.o \
      ansi-wait_out_rel_ansi92.o ansi-idle_ansi92.o \
      ansi-wait_out_rsc_ansi92.o ansi-csc_ansi92.o \
      ansi-generic_state_ansi92.o ansi-validate_param.o \
      ansi-wait_out_gra_ansi92.o ansi-inter_state_ansi92.o \
      ansi-wait_in_cot_ansi92.o  ansi-wait_cot_report_ansi92.o \
      ansi-wait_cotreports_and_cra_ansi92.o ansi-wait_in_cra_ansi92.o \
      ansi-wait_cotreports_have_cra_ansi92.o ansi-wait_in_iam_ansi92.o \
      ansi-wait_in_cot_and_iam_ansi92.o ansi-wait_out_iam_ansi92.o

#
# PROTOCOL type
#
ifeq ($(PROTOCOL),ANSI)
all: ../../lib/libANSI_GENERIC_92$(DBGSUFFIX).a \
     ../../lib/libANSI_GENERIC_92$(DBGSUFFIX).so
else
all:
endif

../../lib/libANSI_GENERIC_92$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libANSI_GENERIC_92$(DBGSUFFIX).a $(OBJS)

../../lib/libANSI_GENERIC_92$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/libANSI_GENERIC_92$(DBGSUFFIX).so \
		$(OBJS)

ifeq ($(PROTOCOL),ANSI)
clean:
	$(RM) $(OBJS) \
		../../lib/libANSI_GENERIC_92$(DBGSUFFIX).a \
		../../lib/libANSI_GENERIC_92$(DBGSUFFIX).so
else
clean:
endif

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
