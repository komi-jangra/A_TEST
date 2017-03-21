############################################################################
#                                                                          #
#     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:34  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:27  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:53  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:34  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.1  2000/08/16 00:06:28  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 1.4  2000/03/29 16:44:25  hdivoux
# LOG: Continue port to Unix (Solaris).
# LOG:
# LOG: Revision 1.3  2000/03/29 15:14:30  hdivoux
# LOG: Work in progress.
# LOG:
# LOG: Revision 1.2  2000/03/28 22:11:36  hdivoux
# LOG:
# LOG: Begin port to Unix.
# LOG:
# LOG: Revision 1.1  2000/03/28 21:52:49  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -DDEBUG -I$(ITS_ROOT)/common/include \
            -I$(ITS_ROOT)/common/include/asn-c

LDFLAGS = -L../../../lib

all: test_runtime

test_runtime: main.c \
              ../../../lib/libSUPPORTD.a \
              ../../../lib/libCORED.a \
              ../../../lib/libASN_V2D.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o test_runtime main.c \
		-lASN_V2D -lSUPPORTD -lCORED \
		$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)
                
clean:
	$(RM) *.o test_runtime                


#
#
# get the rules
#
include $(ITS_ROOT)/config.rules
