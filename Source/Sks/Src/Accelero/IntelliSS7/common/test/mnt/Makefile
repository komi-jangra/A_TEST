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
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:03 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:37  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:17  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:31  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:00  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:42  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:12  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/04/26 18:22:39  hdivoux
# LOG: Update for IntelliSS7 changes (PR >= 6).
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:17  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.2  2001/08/09 21:14:34  hdivoux
# LOG: Update for linking.
# LOG:
# LOG: Revision 1.1  2001/08/09 19:27:34  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars

CXXOBJS = test_mnt_main.o

ITS_LIBS = -lMNT$(DBGSUFFIX)           \
           -lGCS-CLIENT$(DBGSUFFIX)    \
           -lCORE$(DBGSUFFIX)          \
           -lSUPPORT$(DBGSUFFIX)       \
           -lCORE$(DBGSUFFIX)
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib 

CXXFLAGS := $(CXXFLAGS) -I. -I$(ITS_ROOT)/common/include \
            -I$(ITS_ROOT)/common/include/mnt

all: test_mnt$(DBGSUFFIX)

test_mnt$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) $(LDFLAGS) -o test_mnt$(DBGSUFFIX)               \
                    $(CXXOBJS)                              \
                    $(ITS_LIBS)                             \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    

clean:
	$(RM) test_mnt$(DBGSUFFIX) $(CXXOBJS) .depend


include $(ITS_ROOT)/config.rules

