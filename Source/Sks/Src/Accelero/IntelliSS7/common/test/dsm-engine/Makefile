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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:35  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:28  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:56  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:37  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.2  2001/09/19 16:48:15  hdivoux
# LOG: Update to add GCS-CLIENT library for TARGET=GCS.
# LOG:
# LOG: Revision 1.1  2001/09/18 21:03:46  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars


ifeq ($(TARGET),STUB)

all: test_dsm_engine_stub$(DBGSUFFIX)

ITS_LIBS = -lENGINE$(DBGSUFFIX)        \
           -lDRIVER++$(DBGSUFFIX)
           
EXESUFFIX = _stub

else

ifeq ($(TARGET),GCS)

all: test_dsm_engine_gcs$(DBGSUFFIX)

ITS_LIBS = -lENGINE$(DBGSUFFIX)        \
           -lDRIVER++$(DBGSUFFIX)      \
           -lGCS-CLIENT$(DBGSUFFIX)

EXESUFFIX = _gcs

else

ifeq ($(TARGET),SCI)

all: test_dsm_engine_sci$(DBGSUFFIX)

ITS_LIBS = -lENGINE$(DBGSUFFIX)        \
           -lDRIVER++$(DBGSUFFIX)
           
EXESUFFIX = _sci

else

all:
	echo "missing TARGET!"

endif
endif
endif

CXXOBJS = test_dsm_engine_main.o
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib

CFLAGS := $(CFLAGS) -I. -I$(ITS_ROOT)/common/include

test_dsm_engine$(EXESUFFIX)$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) $(LDFLAGS) $(CXXOBJS) -o test_dsm_engine$(EXESUFFIX)$(DBGSUFFIX) \
                    $(OBJS)                                                 \
                    $(ITS_LIBS)                                             \
                    $(SOCKLIBS)                                             \
                    $(THREADLIBS)                                           \
                    $(SYSLIBS)
                    

clean:
	$(RM) test_dsm_engine_stub$(DBGSUFFIX) \
          test_dsm_engine_gcs$(DBGSUFFIX)  \
          test_dsm_engine_sci$(DBGSUFFIX)  \
          $(CXXOBJS) .depend

include $(ITS_ROOT)/config.rules

