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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:19 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:55  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:12  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:55:01  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:54:12  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.2  2003/01/22 09:14:24  akumar
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.5  2002/08/07 13:55:26  hbalimid
# LOG: removed -Wall option in CFLAGS
# LOG:
# LOG: Revision 1.4  2002/08/01 15:57:50  ssharma
# LOG: Merge from ISUP_PR7 branch.
# LOG:
# LOG: Revision 1.3.2.2  2002/07/06 20:06:42  hbalimid
# LOG: Fixed all warnings.
# LOG:
# LOG: Revision 1.3.2.1  2002/07/03 19:35:16  hbalimid
# LOG: Added/modified for wait_outgoing_gra.
# LOG:
# LOG: Revision 1.3  2002/06/18 22:17:06  hbalimid
# LOG: Updated with all the state related files.
# LOG:
# LOG: Revision 1.2  2002/05/20 15:50:06  sjaddu
# LOG: Merge from PR6.
# LOG:
# LOG: Revision 1.1.2.2  2002/05/14 17:51:59  hbalimid
# LOG: includes of itu in IntelliSS7 Isup taken care of
# LOG:
# LOG: Revision 1.1.2.1  2002/05/13 22:53:30  hbalimid
# LOG: Base-line for ITU ISUP 97
# LOG:
#
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

CFLAGS :=  $(CFLAGS) \
          -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/ISUP/include/itu \
	  -I../../include -I../../include/itu -DINCLUDE_CODEC

OBJS	=itu-isup_97.o itu-wait_in_rlc_itu97.o itu-wait_in_res_itu97.o \
         itu-wait_in_anm_itu97.o itu-wait_in_acm_itu97.o \
         itu-sent_out_anm_itu97.o itu-rcvd_in_anm_itu97.o \
         itu-idle_itu97.o itu-wait_out_rsc_itu97.o \
         itu-wait_out_rlc_itu97.o itu-wait_out_res_itu97.o \
         itu-wait_out_rel_itu97.o itu-wait_out_anm_itu97.o \
         itu-wait_out_acm_itu97.o itu-wait_out_gra_itu97.o \
         itu-wait_in_cot_itu97.o itu-wait_cot_report_itu97.o


#
# PROTOCOL type
#
ifeq ($(PROTOCOL),CCITT)
all: ../../lib/libITU_ISUP_97$(DBGSUFFIX).a \
     ../../lib/libITU_ISUP_97$(DBGSUFFIX).so
else
all:
endif

../../lib/libITU_ISUP_97$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libITU_ISUP_97$(DBGSUFFIX).a $(OBJS)

../../lib/libITU_ISUP_97$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libITU_ISUP_97$(DBGSUFFIX).so \
		$(OBJS)

ifeq ($(PROTOCOL),CCITT)
clean:
	$(RM) $(OBJS) \
		../../lib/libITU_ISUP_97$(DBGSUFFIX).a \
		../../lib/libITU_ISUP_97$(DBGSUFFIX).so
else
clean:
endif

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
