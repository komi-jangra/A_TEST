###########################################################################
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
# ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:34  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:26  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:53  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 1.1.2.1  2005/02/08 11:38:53  kannanp
# LOG: WorkItem Initial - Hari Priya.
# LOG:
# LOG:
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := -I../include $(CFLAGS) \
          -D$(PROTOCOL) \
          -DFILE_APP_TRACE \
          -DAPP_STDOUT_TRACE \
          -I$(ITS_ROOT)/common/include\
          -I$(ITS_ROOT)/MTP2/include \
          -I$(ITS_ROOT)/MTP3/include \
          -I$(ITS_ROOT)/SNMM/include \
          -I$(ITS_ROOT)/SLTM/include \
          -I$(ITS_ROOT)/ISUP/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/TCAP/include
 

CXXFLAGS:= $(CFLAGS)
LDFLAGS := -L. $(LDFLAGS) 

CPP_OBJS= Main.o  

LIBS:= -L$(ITS_ROOT)/common/lib \
       -L. \
       -lDRIVER++$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -lDISPATCH++$(DBGSUFFIX)\
       -lpthread -ldl


#
# PROTOCOL type
#
all: ../lib/libSampleApp$(DBGSUFFIX).so \
	 SampleApp$(DBGSUFFIX)  

SampleApp$(DBGSUFFIX): $(CPP_OBJS)
	$(CXX) $(CXXFLAGS) -o \
            $@ $(CPP_OBJS) $(LIBS) 


LIB_OBJS= Callbacks.o  

../lib/libSampleApp$(DBGSUFFIX).so: $(LIB_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) ../lib/libSampleApp$(DBGSUFFIX).so $(LIB_OBJS)


%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $<


clean:
	$(RM) -rf *.o ../lib/libSampleApp$(DBGSUFFIX).so SampleApp$(DBGSUFFIX) 

#
# get the rules
#
include $(ITS_ROOT)/config.rules


