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
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:23  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:12  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:22  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:38  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.5  2002/08/20 15:53:04  mmiers
# LOG: Update the clean target for china
# LOG:
# LOG: Revision 6.4  2002/05/08 18:34:28  mmiers
# LOG: Don't include SUPPORT and CORE in the build.  Rather, link
# LOG: with libENGINE when testing.
# LOG:
# LOG: Revision 6.3  2002/04/16 21:20:30  hdivoux
# LOG: FT/HA integration.
# LOG:
# LOG: Revision 6.2  2002/04/11 21:25:27  hdivoux
# LOG: Work in progress: upcoming FT/HA.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.8  2001/07/19 16:14:11  mmiers
# LOG: Get library makefiles right.
# LOG:
# LOG: Revision 1.7  2001/07/19 14:30:26  mmiers
# LOG: Missing extension.
# LOG:
# LOG: Revision 1.6  2001/07/10 16:12:18  mmiers
# LOG: Cross platform build.
# LOG:
# LOG: Revision 1.5  2001/07/05 21:30:27  mmiers
# LOG: These are .a's again.
# LOG:
# LOG: Revision 1.4  2001/07/03 21:16:22  mmiers
# LOG: Move RM and DSM.
# LOG:
# LOG: Revision 1.2  2001/06/26 15:20:06  mmiers
# LOG: Build into common
# LOG:
# LOG: Revision 1.1  2001/06/22 18:26:52  mmiers
# LOG: Move to ENGINE.
# LOG:
# LOG: Revision 1.2  2001/06/21 00:58:29  mmiers
# LOG: UNIX build.
# LOG:
# LOG: Revision 1.1  2001/06/20 19:55:41  mmiers
# LOG: Split DSM out into a separate library.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars


OBJS=dsm_sci_impl.o

CFLAGS := $(CFLAGS) -DDSM_IMPLEMENTATION \
		-I../../include \
		-I${BPM_INC}  \
		-I${BPM_INC}/../Sys  \
		-I${BPM_INC}/../Ipc

all: ../../lib/libDSM-SCI$(DBGSUFFIX).so

clean:
	$(RM) *.o \
		../../lib/libDSM-SCI$(DBGSUFFIX).so \
		../../lib/libDSM-SCI$(DBGSUFFIX).a

../../lib/libDSM-SCI$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
	../../lib/libDSM-SCI$(DBGSUFFIX).so $(OBJS)


#
# get the rules
#
include $(ITS_ROOT)/config.rules
