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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:06  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:01  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:49:57  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.5  2002/08/05 20:29:44  ssharma
# LOG: Move CIC and dest pegs to isup_variants.h
# LOG:
# LOG: Revision 6.4  2002/08/01 15:48:46  ssharma
# LOG: Merge from ISUP_PR7.
# LOG:
# LOG: Revision 6.3  2002/07/10 17:27:55  hbalimid
# LOG: Added check for Protocol PRC for target clean.
# LOG:
# LOG: Revision 6.2  2002/07/03 19:55:10  mmiers
# LOG: China fixes
# LOG:
# LOG: Revision 6.1.4.1  2002/07/31 22:28:03  ssharma
# LOG: ITU pegs.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.5  2002/02/13 22:29:48  mmiers
# LOG: Clean step was missing targets.
# LOG:
# LOG: Revision 5.4  2002/02/13 22:28:47  mmiers
# LOG: Formatting.
# LOG:
# LOG: Revision 5.3  2002/02/13 18:27:44  mmiers
# LOG: Finish off the ISUP integration.
# LOG:
# LOG: Revision 5.2  2002/02/06 23:44:57  mmiers
# LOG: Continued ISUP integration
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:05  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.3  2001/03/28 23:23:48  mmiers
# LOG: Dead file.
# LOG:
# LOG: Revision 3.2  2000/09/01 15:35:51  mmiers
# LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
# LOG:
# LOG: Revision 3.1  2000/08/15 23:59:27  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:21:28  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.12  1999/07/01 02:28:26  mmiers
# LOG:
# LOG:
# LOG: On Solaris, you build C++ libraries with the compiler, of all
# LOG: things.  Add new make variables accordingly.
# LOG:
# LOG: Revision 1.11  1999/06/30 22:28:27  mmiers
# LOG:
# LOG:
# LOG: Correct ISUP build
# LOG:
# LOG: Revision 1.10  1999/05/25 01:06:46  mmiers
# LOG:
# LOG:
# LOG: Start cleaning up ISUP.
# LOG:
# LOG: Revision 1.9  1999/03/03 15:51:00  mmiers
# LOG:
# LOG:
# LOG: Add doc generation to Makefiles.
# LOG:
# LOG: Revision 1.8  1999/03/02 22:50:57  mmiers
# LOG:
# LOG:
# LOG: Make all four forms of ISUP.
# LOG:
# LOG: Revision 1.7  1998/11/18 00:23:41  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.6  1998/11/17 23:57:40  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.5  1998/11/17 16:42:10  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG:
# LOG: Revision 1.4  1998/09/26 15:53:53  mmiers
# LOG: Update for MTP3.
# LOG:
# LOG: Revision 1.3  1998/05/05 02:06:30  mmiers
# LOG: Add .depend target to clean rule.
# LOG:
# LOG: Revision 1.2  1998/04/24 01:41:32  mmiers
# LOG: General cleanup of the build system.  Need to verify on Digital Unix
# LOG: to make sure this is ok.
# LOG:
# LOG: Revision 1.1  1998/01/24 20:57:15  mmiers
# LOG: Add in California code.  Implementation of ITU ISUP.
# LOG:
# LOG: Revision 1.1  1998/01/24 20:24:59  mmiers
# LOG: Add vendor dependent SCCP library.
# LOG:
# LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
# LOG: Baseline
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

OBJS=isup.o
VOBJS=isup_cmn.o isup_variants.o
CXXOBJS=
CFLAGS := $(CFLAGS) -I../include -I../../MTP2/include \
          -I../../MTP3/include \
          -I../../SCCP/include -I../../TCAP/include -I../../include \
        -I${BPM_INC}  \
        -I${BPM_INC}/../Sys  \
        -I${BPM_INC}/../Ipc

ifneq ($(PROTOCOL),PRC)
all: ../lib/lib$(PROTOCOL)-ISUP$(DBGSUFFIX).a \
     ../lib/libISUP_VARIANTS$(DBGSUFFIX).a
else
all:
endif

ifneq ($(PROTOCOL),PRC)
clean:
	$(RM) $(OBJS) $(VOBJS) \
		../lib/lib$(PROTOCOL)-ISUP$(DBGSUFFIX).a \
		../lib/libISUP_VARIANTS$(DBGSUFFIX).a \
		.depend
else
clean:
endif

../lib/lib$(PROTOCOL)-ISUP$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../lib/lib$(PROTOCOL)-ISUP$(DBGSUFFIX).a $(OBJS)
	sh ./generate

../lib/libISUP_VARIANTS$(DBGSUFFIX).a: $(VOBJS)
	$(AR) $(ARFLAGS) ../lib/libISUP_VARIANTS$(DBGSUFFIX).a $(VOBJS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
