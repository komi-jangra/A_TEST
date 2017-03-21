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
# LOG: Revision 7.1  2002/08/26 22:10:30  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/05/20 16:18:58  sjaddu
# LOG: Merge from PR6.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.4.2.1  2002/05/09 18:38:10  labuser
# LOG: Merge from ISUP_APR_19_2002 branch to PR6.
# LOG:
# LOG: Revision 1.4.4.1  2002/04/27 01:04:18  labuser
# LOG: fixed syntax error in Makefile
# LOG:
# LOG: Revision 1.4  2002/02/13 23:36:43  mmiers
# LOG: Build the variants better.
# LOG:
# LOG: Revision 1.3  2002/02/13 23:28:24  mmiers
# LOG: Build the right targets
# LOG:
# LOG: Revision 1.2  2002/02/13 23:24:05  mmiers
# LOG: Debug
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

OBJS	=itu-isup_china.o

#
# PROTOCOL type
#
ifeq ($(PROTOCOL),CCITT)
all: ../../lib/libITU_CHINA$(DBGSUFFIX).a \
     ../../lib/libITU_CHINA$(DBGSUFFIX).so
else
all:
endif

../../lib/libITU_CHINA$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libITU_CHINA$(DBGSUFFIX).a $(OBJS)

../../lib/libITU_CHINA$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libITU_CHINA$(DBGSUFFIX).so \
		$(OBJS)

ifeq ($(PROTOCOL),CCITT)
clean:
	$(RM) $(OBJS) \
		../../lib/libITU_CHINA$(DBGSUFFIX).a \
		../../lib/libITU_CHINA$(DBGSUFFIX).so
else
clean:
endif

#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
