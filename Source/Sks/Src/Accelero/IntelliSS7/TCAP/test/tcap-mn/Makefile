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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:29 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:23:59  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:55  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:34  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:41  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:50:39  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:34  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.2  2001/10/19 19:53:27  hdivoux
# LOG: Update for working version (from PR5).
# LOG:
# LOG: Revision 1.1  2001/10/19 16:16:53  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars

ifeq ($(PROTOCOL),CCITT)

all: test_tcap_mn_itu$(DBGSUFFIX)

ITS_LIBS = -lENGINE$(DBGSUFFIX)     \
           -lDRIVER++$(DBGSUFFIX)   \
           -lMNT$(DBGSUFFIX)        \
           -lGCS-CLIENT$(DBGSUFFIX)
                      
EXESUFFIX = _itu

else

ifeq ($(TARGET),ANSI)

all: test_tcap_mn_ansi$(DBGSUFFIX)

ITS_LIBS = -lENGINE$(DBGSUFFIX)     \
           -lDRIVER++$(DBGSUFFIX)   \
           -lMNT$(DBGSUFFIX)        \
           -lGCS-CLIENT$(DBGSUFFIX)

EXESUFFIX = _ansi

else

all:
	echo "missing PROTOCOL choice (CCITT or ANSI)!"

endif
endif

CXXOBJS = test_tcap_mn_main.o
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib

CFLAGS := $(CFLAGS) -I. -I$(ITS_ROOT)/common/include        \
                        -I$(ITS_ROOT)/common/include/mnt    \
                        -I$(ITS_ROOT)/TCAP/include          \
                        -I$(ITS_ROOT)/SCCP/include          \
                        -I$(ITS_ROOT)/MTP3/include          \
                        -I$(ITS_ROOT)/MTP2/include

test_tcap_mn$(EXESUFFIX)$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) $(LDFLAGS) $(CXXOBJS) -o test_tcap_mn$(EXESUFFIX)$(DBGSUFFIX)    \
                    $(OBJS)                                                 \
                    $(ITS_LIBS)                                             \
                    $(SOCKLIBS)                                             \
                    $(THREADLIBS)                                           \
                    $(SYSLIBS)
                    

clean:
	$(RM) test_tcap_mn_itu$(DBGSUFFIX)  \
          test_tcap_mn_ansi$(DBGSUFFIX) \
          $(CXXOBJS) .depend

include $(ITS_ROOT)/config.rules

