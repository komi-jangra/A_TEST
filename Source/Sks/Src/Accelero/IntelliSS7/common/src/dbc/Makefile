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
# LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:51:21  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1.4.1  2003/03/28 00:47:21  randresol
# LOG: Build DBG_Console with -lDBGServer
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.3  2002/05/17 20:45:48  hdivoux
# LOG: Update for new FT/HA.
# LOG:
# LOG: Revision 6.2  2002/04/16 21:58:08  hdivoux
# LOG: FT/HA integration.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.2  2001/11/21 00:47:00  mmiers
# LOG: DBG in engine.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.2  2001/07/10 15:29:40  mmiers
# LOG: Some small updates.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.3  2001/03/06 22:24:37  mmiers
# LOG: Convert to SUPPORT only
# LOG:
# LOG: Revision 3.2  2001/03/06 02:28:38  mmiers
# LOG: Add dynamic link lib.  Straighten out include order.  Remove instance
# LOG: of CORE++.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:04:52  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.2  2000/07/21 14:25:01  labuser
# LOG:
# LOG: Add DBGServer to the targets.
# LOG:
# LOG: Revision 2.1  2000/02/04 21:39:18  mmiers
# LOG:
# LOG:
# LOG: Correct makefiles to build on Solaris.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:27:11  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.5  1999/10/25 19:04:36  mmiers
# LOG:
# LOG:
# LOG: Tweak, add missing method.
# LOG:
# LOG: Revision 1.4  1999/08/02 20:24:18  mmiers
# LOG:
# LOG:
# LOG: Fix some cross-platform issues.
# LOG:
# LOG: Revision 1.3  1999/07/16 21:23:14  mmiers
# LOG:
# LOG:
# LOG: Update to work on UNIX.
# LOG:
# LOG: Revision 1.2  1999/07/13 15:32:58  mmiers
# LOG:
# LOG:
# LOG: Correct the build rules, delete dbc_command
# LOG:
# LOG: Revision 1.1  1999/07/02 16:56:18  mmiers
# LOG:
# LOG:
# LOG: Make this look like other subsystems to automate the NT build.
# LOG:
# LOG: Revision 1.7  1999/06/30 17:16:44  mmiers
# LOG:
# LOG:
# LOG: Portability fixes.
# LOG:
# LOG: Revision 1.6  1999/06/30 17:05:57  mmiers
# LOG:
# LOG:
# LOG: Correct the Makefile
# LOG:
# LOG: Revision 1.5  1999/06/29 23:39:25  mmiers
# LOG:
# LOG:
# LOG: More portability fixes.
# LOG:
# LOG: Revision 1.4  1998/11/18 00:21:09  jrao
# LOG: Changed target name.
# LOG:
# LOG: Revision 1.3  1998/11/17 23:57:43  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.2  1998/11/17 18:05:36  jrao
# LOG: Added Library Suffixes.
# LOG:
# LOG: Revision 1.1  1998/11/17 17:44:25  mmiers
# LOG: Move DBC into common to sanitize the build.
# LOG:
# LOG: Revision 1.2  1998/11/05 21:20:51  mmiers
# LOG: Portability build.
# LOG:
# LOG: Revision 1.1  1998/11/05 17:31:31  mmiers
# LOG: Add makefiles for this stuff.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CXXOBJS= dbc_client.o dbc_console_main.o
CXXFLAGS := $(CXXFLAGS) -I../../include -L../../lib -L$(SYSEXE_ROOT)/Target/CommonLib/CP\
	-I${BPM_INC}  -I${BPM_INC}/../Sys \
	-I${BPM_INC}/../Ipc
CFLAGS := $(CFLAGS) -I../../include
COBJS=dbc_serv.o
LIBS = ../../lib/libDBGServer$(DBGSUFFIX).a

all: ../../bin/DBGConsole$(DBGSUFFIX) $(LIBS) 


clean:
	$(RM) $(CXXOBJS) $(COBJS) .depend \
		../../bin/DBGConsole$(DBGSUFFIX) $(LIBS) 

../../bin/DBGConsole$(DBGSUFFIX): $(CXXOBJS) $(LIBS) 
	$(CXX) $(CXXFLAGS) -o ../../bin/DBGConsole$(DBGSUFFIX) $(CXXOBJS)   \
		-lANSI-DSM-STUB$(DBGSUFFIX) -lSUPPORT$(DBGSUFFIX) -lCORE$(DBGSUFFIX) \
		-lSUPPORT$(DBGSUFFIX) -lCORE$(DBGSUFFIX) \
		$(LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS)  -llog

../../lib/libDBGServer$(DBGSUFFIX).a: $(COBJS)
	$(AR) $(ARFLAGS) ../../lib/libDBGServer$(DBGSUFFIX).a \
                $(COBJS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
