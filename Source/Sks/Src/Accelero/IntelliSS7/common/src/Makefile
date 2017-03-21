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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:10  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:00  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:57  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:57  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:51:08  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:44  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:00  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
# LOG: Make sure files end with newline
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.6  2001/01/03 22:48:02  hdivoux
# LOG: Set up a source build system for partial builds
# LOG:
# LOG: Revision 3.5  2000/12/19 20:18:24  mmiers
# LOG: Update for UAL
# LOG:
# LOG: Revision 3.4  2000/11/15 22:50:10  mmiers
# LOG: Accidentally checked in src Makefile with asn-cpp disabled
# LOG:
# LOG: Revision 3.3  2000/10/05 21:17:52  mmiers
# LOG: Update other platforms.
# LOG:
# LOG: Revision 3.2  2000/08/24 23:06:36  mmiers
# LOG:
# LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:04:02  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.5  2000/05/23 21:39:04  mmiers
# LOG:
# LOG:
# LOG: Include SCTP in build.
# LOG:
# LOG: Revision 2.4  2000/05/10 23:53:37  mmiers
# LOG:
# LOG:
# LOG: Update for TALI
# LOG:
# LOG: Revision 2.3  2000/05/10 23:52:19  mmiers
# LOG:
# LOG:
# LOG: Update makefiles.
# LOG:
# LOG: Revision 2.2  2000/02/10 01:47:56  mmiers
# LOG: Cross platform cleanup.
# LOG:
# LOG: Revision 2.1  1999/12/04 00:12:15  mmiers
# LOG:
# LOG:
# LOG: Add GDI to make.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:26:15  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.16  1999/09/20 17:00:26  labuser
# LOG:
# LOG:
# LOG: Change "make" to dollar-make
# LOG:
# LOG: Revision 1.15  1999/07/16 16:12:01  mmiers
# LOG: Update for newer dbc tree.
# LOG:
# LOG: Revision 1.14  1999/07/02 17:42:57  skarmakar
# LOG:
# LOG:
# LOG: Adjust dbc make to reflect a flat hierarchy
# LOG:
# LOG: Revision 1.13  1999/06/29 23:39:25  mmiers
# LOG:
# LOG:
# LOG: More portability fixes.
# LOG:
# LOG: Revision 1.12  1999/06/29 22:08:07  mmiers
# LOG:
# LOG:
# LOG: Build debug and release at the same time.
# LOG:
# LOG: Revision 1.11  1999/06/17 15:56:53  labuser
# LOG:
# LOG:
# LOG: Add building itscore
# LOG:
# LOG: Revision 1.10  1999/04/26 22:23:54  skarmakar
# LOG:
# LOG:
# LOG: Save build changes, update LIDB test.
# LOG:
# LOG: Revision 1.9  1998/11/18 00:23:42  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.8  1998/11/17 19:03:56  jrao
# LOG: Corrections pending after the move of dbc from tools to common are now made.
# LOG:
# LOG: Revision 1.7  1998/11/17 17:48:58  jrao
# LOG: Added the dbc targets.
# LOG:
# LOG: Revision 1.6  1998/10/27 16:40:18  mmiers
# LOG: Remove dead pepsy dirs.
# LOG:
# LOG: Revision 1.5  1998/10/21 19:33:50  mmiers
# LOG: Tweaks for autobuild.
# LOG:
# LOG: Revision 1.4  1998/05/20 02:55:31  mmiers
# LOG: Update the Makefile for common.
# LOG:
# LOG: Revision 1.3  1998/04/24 02:00:38  mmiers
# LOG: Build on Digital UNIX.
# LOG:
# LOG: Revision 1.2  1998/04/24 01:41:33  mmiers
# LOG: General cleanup of the build system.  Need to verify on Digital Unix
# LOG: to make sure this is ok.
# LOG:
# LOG: Revision 1.1  1998/01/24 22:38:50  mmiers
# LOG: New makefile for building common
# LOG:
# LOG: Revision 1.1  1998/01/24 22:36:54  mmiers
# LOG: Tree cleanup.
# LOG:
# LOG: Revision 1.1  1998/01/24 22:33:43  mmiers
# LOG: Top level makefile
# LOG:
# LOG: Revision 1.2  1998/01/24 21:30:53  mmiers
# LOG: Add DK code from DIN project
# LOG:
# LOG: Revision 1.1  1998/01/24 21:01:44  mmiers
# LOG: add build rules for vendor specific stuff.
# LOG:
# LOG: Revision 1.1  1998/01/24 20:24:59  mmiers
# LOG: Add vendor dependent SCCP library.
# LOG:
# LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
# LOG: Baseline
# LOG:
#
############################################################################

SDIRS=`cat ssubs`
BDIRS=`cat bsubs`
DDIRS=`cat dsubs`

all:
	for dir in $(SDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes all);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no all);	\
	done
	for dir in $(DDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes all);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no all);	\
	done
	for dir in $(BDIRS);						    \
	do								    \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=yes clean);  \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=yes all);    \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=no clean);   \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=no all);     \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=yes clean); \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=yes all);   \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=no clean);  \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=no all);    \
	done

debug:
	for dir in $(SDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes all);	\
	done
	for dir in $(DDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes all);	\
	done
	for dir in $(BDIRS);						    \
	do								    \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=yes clean);  \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=yes all);    \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=yes clean); \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=yes all);   \
	done

release:
	for dir in $(SDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no all);	\
	done
	for dir in $(DDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no all);	\
	done
	for dir in $(BDIRS);						    \
	do								    \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=no clean);   \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=no all);     \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=no clean);  \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=no all);    \
	done

depend:
	for dir in $(SDIRS) $(DDIRS) $(BDIRS);			\
	do							\
		(cd $$dir && $(MAKE) depend);			\
		(cd $$dir && $(MAKE) PROTOCOL=ANSI depend);	\
		(cd $$dir && $(MAKE) PROTOCOL=CCITT depend);	\
	done

clean:
	for dir in $(SDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no clean);	\
	done
	for dir in $(DDIRS);					\
	do							\
		(cd $$dir && $(MAKE) DEBUG_BUILD=yes clean);	\
		(cd $$dir && $(MAKE) DEBUG_BUILD=no clean);	\
	done
	for dir in $(BDIRS);						    \
	do								    \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=yes clean);  \
		(cd $$dir && $(MAKE) PROTOCOL=ANSI DEBUG_BUILD=yes clean);  \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=no clean);  \
		(cd $$dir && $(MAKE) PROTOCOL=CCITT DEBUG_BUILD=no clean);  \
	done

