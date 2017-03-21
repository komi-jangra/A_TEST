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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:49 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:20  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:08  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1  2007/03/30 04:54:36  cvsadmin
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 1.1.1.1  2006/12/22 13:34:34  cvsadmin
# LOG: Initialising sources in CVS
# LOG:
# LOG: Revision 8.3  2005/03/21 13:51:27  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1.46.1  2004/12/16 03:30:35  randresol
# LOG: Add JAPAN variant implementation
# LOG:
# LOG: Revision 7.1.42.1  2004/10/25 20:39:57  randresol
# LOG: Start Implementation for Japan SS7
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:51  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/08/22 14:21:38  mmiers
# LOG: Add china dispatcher
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.2  2001/09/21 22:58:57  mmiers
# LOG: Add handlers for SS7 ISUP
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 1.3  2001/03/07 01:16:02  mmiers
# LOG: Shared lib template.  Need to test to see what happens to
# LOG: symbols in the .so that are defined in the app.
# LOG:
# LOG: Revision 1.2  2001/03/02 23:04:04  mmiers
# LOG: Cross platform cleanup.
# LOG:
# LOG: Revision 1.1  2001/01/16 21:39:25  mmiers
# LOG: Reorganize so that support is completely standalone
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
		    -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
		    -I$(ITS_ROOT)/TCAP/include -I${BPM_INC}  -I${BPM_INC}/../Sys \
			-I${BPM_INC}/../Ipc
CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
			-I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
			-I$(ITS_ROOT)/TCAP/include

OBJS=its_dispatch.o \
     its_disp_ss7_ansi.o its_disp_ss7_ccitt.o its_disp_ss7_prc.o its_disp_ss7_ttc.o
CPPOBJS=its_dispatch++.o \
     its_disp_ss7_ansi++.o its_disp_ss7_ccitt++.o its_disp_ss7_prc++.o its_disp_ss7_ttc++.o

ifeq ($(PROTOCOL),ANSI)
all: ../../lib/libANSI-DISPATCH$(DBGSUFFIX).so \
           ../../lib/libANSI-DISPATCH++$(DBGSUFFIX).so

clean:
	$(RM) *.o ../../lib/libANSI-DISPATCH$(DBGSUFFIX).so .depend \
                ../../lib/libANSI-DISPATCH++$(DBGSUFFIX).so

../../lib/libANSI-DISPATCH$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/libANSI-DISPATCH$(DBGSUFFIX).so $(OBJS) $(SHAREDARFLAGSEND)

../../lib/libANSI-DISPATCH++$(DBGSUFFIX).so: $(CPPOBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
		../../lib/libANSI-DISPATCH++$(DBGSUFFIX).so $(CPPOBJS) $(CXXSHAREDARFLAGSEND)
else
all: ../../lib/libCCITT-DISPATCH$(DBGSUFFIX).so \
           ../../lib/libCCITT-DISPATCH++$(DBGSUFFIX).so

clean:
	$(RM) *.o ../../lib/libCCITT-DISPATCH$(DBGSUFFIX).so .depend \
                ../../lib/libCCITT-DISPATCH++$(DBGSUFFIX).so

../../lib/libCCITT-DISPATCH$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
		../../lib/libCCITT-DISPATCH$(DBGSUFFIX).so $(OBJS) $(SHAREDARFLAGSEND)

../../lib/libCCITT-DISPATCH++$(DBGSUFFIX).so: $(CPPOBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
		../../lib/libCCITT-DISPATCH++$(DBGSUFFIX).so $(CPPOBJS) $(CXXSHAREDARFLAGSEND)

endif
#
# get the rules
#
include $(ITS_ROOT)/config.rules
