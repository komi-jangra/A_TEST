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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:53 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:26  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:44  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.4  2001/03/13 02:26:22  mmiers
# LOG: UNIX build is a heck of a lot easier to set up.
# LOG:
# LOG: Revision 3.3  2000/09/01 15:35:53  mmiers
# LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
# LOG:
# LOG: Revision 3.2  2000/08/24 23:06:37  mmiers
# LOG:
# LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:04:56  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 1.3  1999/12/16 21:19:55  mmiers
# LOG:
# LOG:
# LOG: Complete the split.
# LOG:
# LOG: Revision 1.2  1999/12/04 00:33:49  mmiers
# LOG:
# LOG:
# LOG: Get this right.
# LOG:
# LOG: Revision 1.1  1999/12/04 00:12:15  mmiers
# LOG:
# LOG:
# LOG: Add GDI to make.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

COBJS=its_gdi.o
CFLAGS:=$(CFLAGS) -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
        -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include -I../../include \
        -I${BPM_INC}  -I${BPM_INC}/../Sys  \
        -I${BPM_INC}/../Ipc

all: ../../lib/lib$(PROTOCOL)-GDI$(DBGSUFFIX).so


clean:
	$(RM) $(COBJS) .depend ../../lib/libGDI$(DBGSUFFIX).so

../../lib/lib$(PROTOCOL)-GDI$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/lib$(PROTOCOL)-GDI$(DBGSUFFIX).so $(COBJS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
