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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:14  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:57  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.2  2005/04/11 09:14:26  mmanikandan
# LOG: clean seperated for ctf library and binary.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 1.2  2005/03/23 07:26:08  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 1.1.2.3  2005/01/28 11:57:05  mmanikandan
# LOG: INCLUDE_CODEC is added for TCAP.
# LOG:
# LOG: Revision 1.1.2.2  2005/01/05 09:47:47  mmanikandan
# LOG: CTFConsole binary compilation is removed from all.
# LOG:
# LOG: Revision 1.1.2.1  2005/01/04 13:10:25  mmanikandan
# LOG: CTF Initial commit.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -DINCLUDE_CODEC -I$(ITS_ROOT)/common/include \
                    -I$(ITS_ROOT)/MTP2/include \
                    -I$(ITS_ROOT)/MTP3/include \
                    -I$(ITS_ROOT)/SCCP/include \
                    -I$(ITS_ROOT)/TCAP/include \
                    -I$(ITS_ROOT)/ISUP/include -L../../lib

CTFOBJS= its_ctf.o
CTFCONSOBJS= ctf_console.o ctf_filter.o

all: ../../lib/libCTF$(DBGSUFFIX).a 

CTFConsole: ../../bin/CTFConsole$(DBGSUFFIX)

CTFClean:
	$(RM) $(CTFCONSOBJS) \
		../../bin/CTFConsole$(DBGSUFFIX) 

clean:
	$(RM) $(CTFOBJS) \
		../../lib/libCTF$(DBGSUFFIX).a \

../../lib/libCTF$(DBGSUFFIX).a: $(CTFOBJS) 
	$(AR) $(ARFLAGS) ../../lib/libCTF$(DBGSUFFIX).a $(CTFOBJS)

../../bin/CTFConsole$(DBGSUFFIX): $(CTFCONSOBJS)
	$(CXX) $(CXXFLAGS) -o ../../bin/CTFConsole$(DBGSUFFIX) $(CTFCONSOBJS) \
        -lDSM-STUB$(DBGSUFFIX) -lENGINE$(DBGSUFFIX) -lVFrame$(DBGSUFFIX) \
        $(LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS) 

#
# get the rules
#
include $(ITS_ROOT)/config.rules
