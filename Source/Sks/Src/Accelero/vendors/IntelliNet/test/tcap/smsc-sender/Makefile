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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:23  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:55:23  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
# LOG: PR6.4.2 sources propagated to Current.
# LOG:
# LOG: Revision 1.1.2.1  2004/12/17 04:16:26  randresol
# LOG: Add TCAP test program for TTC
# LOG:
# LOG: Revision 8.1  2003/02/13 17:44:37  yranade
# LOG: Begin PR6.4
# LOG:
# LOG: Revision 1.1  2002/11/10 00:07:46  randresol
# LOG: Add ITU test file for TCAP/SCCP/MTP3 stack
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.1  2002/07/25 14:27:35  randresol
# LOG: Add mtp3 test files
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:18  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 1.6  2001/04/04 22:01:31  mmiers
# LOG: Finish debugging.
# LOG:
# LOG: Revision 1.5  2001/04/03 23:56:56  mmiers
# LOG: Debugging.
# LOG:
# LOG: Revision 1.4  2001/04/03 01:11:57  mmiers
# LOG:
# LOG: Debugging.
# LOG:
# LOG: Revision 1.3  2001/03/30 23:38:00  mmiers
# LOG: More engine debugging.
# LOG:
# LOG: Revision 1.2  2001/03/30 21:03:34  mmiers
# LOG: Testing.
# LOG:
# LOG: Revision 1.1  2001/03/29 03:07:34  mmiers
# LOG: Start debugging.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include \
          -I$(ITS_ROOT)/ISUP/include \
          -I$(VENDOR_ROOT)/IntelliNet/include \
          -I$(ITS_ROOT)/common/include/asn-cpp \
          -I$(ITS_ROOT)/IS41/include/ansi \
          -I$(ITS_ROOT)/INAP/include/itu 

LIBS=-L. -L../../lib  -L$(ITS_ROOT)/common/lib -L$(VENDOR_ROOT)/IntelliNet/lib \
            -lENGINED -lDRIVERD  \
            -lVFrameD \
            -lDSM-GCS$(DBGSUFFIX)  \
            -lDSM-STUB$(DBGSUFFIX) \
            -lGCS-CLIENT$(DBGSUFFIX) \
            -lDBGServer$(DBGSUFFIX)            


CCITTLIBS= -lCCITT-VENDOR$(DBGSUFFIX)

TTCLIBS= -lTTC-VENDOR$(DBGSUFFIX)

ANSILIBS=  -lANSI-VENDOR$(DBGSUFFIX)

APPLLIBS= -L$(ITS_ROOT)/INAP/lib -lINAP-ETSI-CS1++D -lASN++D \
          -L$(ITS_ROOT)/IS41/lib -lANSI-41E++$(DBGSUFFIX) \
          -lASN++$(DBGSUFFIX)


all:  libsmsc.so smsc 

clean:
	$(RM) -r *.o smsc libsmsc.so SunWS_cache

#smsc.cpp is a softlink to smsc_<variant>.cpp
libsmsc.so: smsc.o
	$(CXX) $(CXXSHAREDARFLAGS) libsmsc.so smsc.o $(LIBS) $(TTCLIBS)

smsc: main.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o smsc main.cpp $(LIBS) -lsmsc \
           $(TTCLIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) 


#
# get the rules
#
include $(ITS_ROOT)/config.rules
