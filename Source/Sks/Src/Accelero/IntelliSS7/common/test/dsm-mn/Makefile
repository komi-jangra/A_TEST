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
# LOG: Revision 1.1.1.1  2007/10/04 13:24:35  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:16  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:28  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:56  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:52:38  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/05/01 18:40:01  hdivoux
# LOG: Update for new FT/HA.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.3  2001/08/09 19:28:19  hdivoux
# LOG: Improvements.
# LOG:
# LOG: Revision 1.2  2001/07/30 21:00:10  hdivoux
# LOG: Port to Sun Solaris CC.
# LOG:
# LOG: Revision 1.1  2001/07/30 20:04:37  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars


all: test_dsm_mn$(DBGSUFFIX)

ITS_LIBS = -lENGINE$(DBGSUFFIX)     \
           -lDRIVER++$(DBGSUFFIX)   \
           -lMNT$(DBGSUFFIX)        \
           -lGCS-CLIENT$(DBGSUFFIX) \
           -lDSM-STUB$(DBGSUFFIX)   \
           -lDSM-GCS$(DBGSUFFIX)
                               
CXXOBJS = test_dsm_mn_main.o
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib

CFLAGS := $(CFLAGS) -I. -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/common/include/mnt

test_dsm_mn$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) $(LDFLAGS) $(CXXOBJS) -o test_dsm_mn$(DBGSUFFIX) \
                    $(OBJS)                                 \
                    $(ITS_LIBS)                             \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    

clean:
	$(RM) test_dsm_mn$(DBGSUFFIX) \
          $(CXXOBJS) .depend

include $(ITS_ROOT)/config.rules

