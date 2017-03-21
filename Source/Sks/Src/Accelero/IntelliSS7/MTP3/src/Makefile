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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:23:51  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:46  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:13  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.2  2005/04/06 05:52:42  adutta
# LOG: MML changes
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:50:18  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1.30.1  2005/02/21 12:19:58  dsatish
# LOG: changes for DAUD support
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.3  2002/05/20 16:19:13  lbana
# LOG: have to include sccp/include dir in makefile.
# LOG:
# LOG: Revision 6.2  2002/05/20 16:02:50  lbana
# LOG: m3ua ver 10 codec
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:10  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.6  2001/03/29 17:36:10  mmiers
# LOG: Make shared libs.
# LOG:
# LOG: Revision 3.5  2001/03/29 16:23:40  mmiers
# LOG: Add expat to common build.
# LOG: Split UALs into different libs (avoids symbol collisions).
# LOG: Change shared lib flags.
# LOG:
# LOG: Revision 3.4  2001/03/20 19:05:15  omayor
# LOG: Build and test codec on Solaris.
# LOG:
# LOG: Revision 3.3  2001/03/13 02:26:22  mmiers
# LOG: UNIX build is a heck of a lot easier to set up.
# LOG:
# LOG: Revision 3.2  2000/09/01 15:35:52  mmiers
# LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:01:56  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:24:29  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.10  1999/07/01 02:29:13  mmiers
# LOG:
# LOG: On Solaris, you build C++ libraries with the compiler, of all
# LOG: things.  Add new make variables accordingly.
# LOG:
# LOG: Revision 1.9  1999/06/28 17:00:51  mmiers
# LOG:
# LOG:
# LOG: Move the generic dispatchers out of here.
# LOG:
# LOG: Revision 1.8  1999/06/25 19:29:20  labuser
# LOG:
# LOG:
# LOG: Fix a bunch of brain farts with generic thread dispatchers.
# LOG: This needs revisiting, as the argument type will screw up
# LOG: C++ code expecting a true thread function signature.
# LOG:
# LOG: Revision 1.7  1999/03/03 15:51:01  mmiers
# LOG:
# LOG:
# LOG: Add doc generation to Makefiles.
# LOG:
# LOG: Revision 1.6  1998/11/18 00:23:41  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.5  1998/11/17 23:57:41  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.4  1998/11/17 16:45:48  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG: Also targets for both ANSI and CCITT.
# LOG:
# LOG: Revision 1.3  1998/10/28 02:02:22  mmiers
# LOG: Do a test build, make the C thread pool compile.
# LOG:
# LOG: Revision 1.2  1998/09/26 15:48:06  mmiers
# LOG: Move -c to config.rules
# LOG:
# LOG: Revision 1.1  1998/09/26 15:45:17  mmiers
# LOG: Unix build.
# LOG:
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

ifeq ($(DAUD_SUPPORT), yes)
AppLib = M3UA$(DBGSUFFIX)-DAUD
DEFINES:=$(DEFINES) -DUSING_DAUD
else
AppLib = M3UA$(DBGSUFFIX)
endif

OBJS=mtp3.o
UOBJS=m3ua.o m3ua_config_mgnt.o
CFLAGS := $(CFLAGS) -I../include -I../../MTP2/include -I../../common/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I${BPM_INC}  -I${BPM_INC}/../Sys  \
           -I${BPM_INC}/../Ipc
CXXFLAGS := $(CXXFLAGS) -I../include -I../../MTP2/include -I../../common/include

all: ../lib/lib$(PROTOCOL)-MTP3$(DBGSUFFIX).a \
     ../lib/lib$(PROTOCOL)-$(AppLib).so

clean:
	$(RM) *.o ../lib/lib$(PROTOCOL)-MTP3$(DBGSUFFIX).a .depend \
            ../lib/lib$(PROTOCOL)-M3UA$(DBGSUFFIX).so

../lib/lib$(PROTOCOL)-MTP3$(DBGSUFFIX).a: $(OBJS)
	$(CXXAR) $(CXXARFLAGS) ../lib/lib$(PROTOCOL)-MTP3$(DBGSUFFIX).a \
		$(OBJS)
	sh ./generate

../lib/lib$(PROTOCOL)-$(AppLib).so: $(UOBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
		../lib/lib$(PROTOCOL)-$(AppLib).so $(UOBJS) $(CXXSHAREDARFLAGSEND) 
#
# get the rules
#
include $(ITS_ROOT)/config.rules
