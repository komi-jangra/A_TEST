############################################################################
#                                                                          #
#     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:02 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:36  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:16  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:30  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:57  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:39  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:08  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.1  2002/06/13 22:22:26  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars

OBJS = test_dsm_sci_main.o

ITS_LIBS = -lDSM-STUB$(DBGSUFFIX)      \
           -lDSM-SCI$(DBGSUFFIX)       \
           -lENGINE$(DBGSUFFIX)        \
           -lCORE$(DBGSUFFIX)          \
           -lSUPPORT$(DBGSUFFIX)       \
           -lCORE$(DBGSUFFIX)
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib 

CFLAGS := $(CFLAGS) -I.

all: test_dsm_sci$(DBGSUFFIX)

test_dsm_sci$(DBGSUFFIX): $(OBJS)
	$(CC) $(LDFLAGS) -o test_dsm_sci$(DBGSUFFIX)            \
                    $(OBJS)                                 \
                    $(ITS_LIBS)                             \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    

clean:
	$(RM) test_dsm_sci$(DBGSUFFIX) $(OBJS) .depend


include $(ITS_ROOT)/config.rules

