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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:23:53  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:50  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:22  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:22  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.3  2005/03/21 13:50:22  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.2  2002/06/13 20:03:33  ngoel
# LOG: sua not ported to current. remove from Makefile
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:02  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:47  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
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
# LOG: Revision 3.4  2001/03/13 02:26:22  mmiers
# LOG: UNIX build is a heck of a lot easier to set up.
# LOG:
# LOG: Revision 3.3  2000/12/19 20:22:56  mmiers
# LOG: Add SUA
# LOG:
# LOG: Revision 3.2  2000/09/01 15:35:52  mmiers
# LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:02:03  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:24:39  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.13  1999/07/01 02:29:13  mmiers
# LOG:
# LOG: On Solaris, you build C++ libraries with the compiler, of all
# LOG: things.  Add new make variables accordingly.
# LOG:
# LOG: Revision 1.12  1999/03/03 15:51:02  mmiers
# LOG:
# LOG:
# LOG: Add doc generation to Makefiles.
# LOG:
# LOG: Revision 1.11  1998/11/18 00:23:42  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.10  1998/11/17 23:57:41  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.9  1998/11/17 16:42:53  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG: Also targets for both ANSI and CCITT.
# LOG:
# LOG: Revision 1.8  1998/09/26 15:47:41  mmiers
# LOG: Add MTP3
# LOG:
# LOG: Revision 1.7  1998/09/22 23:56:29  jrao
# LOG: Changes made to accomodate HPUX code
# LOG:
# LOG: Revision 1.6  1998/06/23 02:31:06  mmiers
# LOG: Update Solaris build environment.  Part of getting SCCP working.
# LOG:
# LOG: Revision 1.5  1998/05/29 03:31:26  mmiers
# LOG: More work on documentation.  Most of this is just adding interface
# LOG: description boxes without actually adding text.  Some of this is
# LOG: genuine bug fixing.
# LOG:
# LOG: Revision 1.4  1998/05/19 23:09:19  mmiers
# LOG: Modify makefile for SCCP++.
# LOG:
# LOG: Revision 1.3  1998/05/05 01:58:59  mmiers
# LOG: Sanitize the build environment a bit.  This gets the Solaris
# LOG: environment to build cleanly.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

OBJS=sccp.o
UOBJS=sua.o sua_sccp_conv.o
CFLAGS := $(CFLAGS) -I../include -I../../common/include \
          -I../../MTP2/include -I../../MTP3/include  -I../../include \
          -I${BPM_INC}  -I${BPM_INC}/../Sys  \
          -I${BPM_INC}/../Ipc
CXXFLAGS := $(CXXFLAGS) -I../include -I../../common/include \
            -I../../MTP2/include -I../../MTP3/include

all: ../lib/lib$(PROTOCOL)-SCCP$(DBGSUFFIX).a 
#     ../lib/lib$(PROTOCOL)-SUA$(DBGSUFFIX).so

clean:
	$(RM) *.o ../lib/lib$(PROTOCOL)-SCCP$(DBGSUFFIX).a .depend

../lib/lib$(PROTOCOL)-SCCP$(DBGSUFFIX).a: $(OBJS)
	$(CXXAR) $(CXXARFLAGS) ../lib/lib$(PROTOCOL)-SCCP$(DBGSUFFIX).a \
		$(OBJS)
	sh ./generate

#../lib/lib$(PROTOCOL)-SUA$(DBGSUFFIX).so: $(UOBJS)
#	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
#		../lib/lib$(PROTOCOL)-SUA$(DBGSUFFIX).so $(UOBJS)
#
# get the rules
#
include $(ITS_ROOT)/config.rules
