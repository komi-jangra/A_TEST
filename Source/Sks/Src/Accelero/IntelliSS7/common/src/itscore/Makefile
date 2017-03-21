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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1.8.1  2005/11/30 10:08:36  sjaddu
# LOG: Porting to MVL on power pc.
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:26  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.9  2005/03/21 13:51:45  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.8.2.2.6.1  2004/09/21 05:40:53  mmanikandan
# LOG: Propagating PPrint from current.
# LOG:
# LOG: Revision 7.8.2.2  2003/08/05 13:31:52  mmanikandan
# LOG: Support for Temporary license file.
# LOG:
# LOG: Revision 7.8.2.1  2003/02/27 23:59:56  pmandal
# LOG: Propagate changes from current
# LOG:
# LOG: Revision 8.3  2003/02/27 22:55:32  pmandal
# LOG: redirect stderr to /dev/null for ls command
# LOG: check for soft link, before linking with files in platforms directory
# LOG: create licensing binaries only when the result of ls command is not null
# LOG:
# LOG: Revision 8.2  2003/02/19 16:52:11  mmiers
# LOG: Inheritance bug fixes.  Move class method invocation out of
# LOG: hash constructor.
# LOG:
# LOG: Revision 8.1  2003/02/13 17:43:56  yranade
# LOG: Begin PR6.4
# LOG:
# LOG: Revision 7.8  2003/01/29 17:20:26  mmiers
# LOG: Put the ring buffer in the right place, test it out.
# LOG:
# LOG: Revision 7.7  2003/01/22 22:07:22  mmiers
# LOG: Add redblack tree.  Make hash, splay, and redblack use overrideable
# LOG: methods for allocation and freeing.  Update tests.
# LOG:
# LOG: Revision 7.6  2003/01/21 22:47:57  mmiers
# LOG: Warning removal, add splay tree class.
# LOG:
# LOG: Revision 7.5  2003/01/16 16:18:34  mmiers
# LOG: Code reorganization.
# LOG:
# LOG: Revision 7.4  2002/12/20 19:40:41  mmiers
# LOG: Move files.
# LOG:
# LOG: Revision 7.3  2002/11/22 02:55:52  pmandal
# LOG: start building on 64 bit solaris
# LOG:
# LOG: Revision 7.2  2002/09/06 19:29:33  yranade
# LOG: Add cflags to build
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.5  2002/08/20 15:54:02  mmiers
# LOG: Fix the clean target
# LOG:
# LOG: Revision 6.4  2002/07/09 18:59:20  yranade
# LOG: Added new targets.
# LOG:
# LOG: Revision 6.3  2002/07/09 16:24:51  mmiers
# LOG: Build new licensing files
# LOG:
# LOG: Revision 6.2  2002/05/06 15:28:03  mmiers
# LOG: Correct build procedure
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.2  2001/08/17 15:03:45  mmiers
# LOG: Need target in both sections of if
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.5  2001/08/16 19:42:45  lbana
# LOG: Get make to work for vxworks
# LOG:
# LOG: Revision 4.4  2001/08/16 19:07:45  mmiers
# LOG: Fix vxWorks.
# LOG:
# LOG: Revision 4.3  2001/05/16 00:14:14  mmiers
# LOG: Get PR5 built.
# LOG:
# LOG: Revision 4.2  2001/05/04 18:30:28  mmiers
# LOG: Move these back.  Support can't be dynamically loaded due to
# LOG: WIN32.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.9  2001/04/30 23:14:03  mmiers
# LOG: Prep for release.
# LOG:
# LOG: Revision 3.8  2001/03/05 23:54:56  mmiers
# LOG: Prep for dynamic linking.
# LOG:
# LOG: Revision 3.7  2001/03/02 23:04:04  mmiers
# LOG: Cross platform cleanup.
# LOG:
# LOG: Revision 3.6  2001/03/02 22:44:14  mmiers
# LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
# LOG: always.  The rest will be loaded on demand.
# LOG:
# LOG: Revision 3.5  2001/02/28 23:07:32  mmiers
# LOG: No more need for CORE and CORE++, only CORE now.
# LOG:
# LOG: Revision 3.4  2001/02/05 23:09:46  hxing
# LOG: Still need CPPOBJS
# LOG:
# LOG: Revision 3.3  2001/01/10 00:24:06  mmiers
# LOG: Linux build.
# LOG:
# LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
# LOG: Remove the last vestiges of the C++ basis (for VxWorks)
# LOG:
# LOG: Revision 3.1  2000/08/16 00:04:58  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.9  2000/08/02 19:29:31  labuser
# LOG: Add crypto target.
# LOG:
# LOG: Revision 2.8  2000/05/02 14:52:54  hdivoux
# LOG: Update for its_assertion.
# LOG:
# LOG: Revision 2.7  2000/03/01 16:30:37  ssharma
# LOG: Fixed a typo in the Makefile.
# LOG:
# LOG: Revision 2.6  2000/02/12 00:07:14  mmiers
# LOG:
# LOG: Move RESFILE to core library.  Convert to complete OO footing.
# LOG:
# LOG: Revision 2.5  2000/02/04 21:39:19  mmiers
# LOG:
# LOG:
# LOG: Correct makefiles to build on Solaris.
# LOG:
# LOG: Revision 2.4  2000/02/01 19:17:43  mmiers
# LOG:
# LOG:
# LOG: Straighten things out a little better (more appropriate stuff in core).
# LOG:
# LOG: Revision 2.3  2000/02/01 16:06:42  mmiers
# LOG:
# LOG:
# LOG: Update for more sanity between support and core.
# LOG:
# LOG: Revision 2.2  2000/01/27 00:02:15  mmiers
# LOG:
# LOG:
# LOG: Make core lib smarter
# LOG:
# LOG: Revision 2.1  1999/12/17 21:55:26  mmiers
# LOG: Try this on DECUNIX
# LOG:
# LOG: Revision 2.0  1999/12/03 23:27:16  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.5  1999/07/01 02:29:14  mmiers
# LOG:
# LOG: On Solaris, you build C++ libraries with the compiler, of all
# LOG: things.  Add new make variables accordingly.
# LOG:
# LOG: Revision 1.4  1999/06/29 23:39:25  mmiers
# LOG:
# LOG:
# LOG: More portability fixes.
# LOG:
# LOG: Revision 1.3  1999/06/15 15:33:47  labuser
# LOG:
# LOG:
# LOG: Add utility for printing a license file.
# LOG:
# LOG: Revision 1.2  1999/04/22 20:44:40  mmiers
# LOG:
# LOG:
# LOG: Correct vrlicense build.
# LOG:
# LOG: Revision 1.1  1999/03/23 21:25:10  mmiers
# LOG:
# LOG:
# LOG: Update for new core libraries.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I../../include \
	-I${BPM_INC}  \
        -I${BPM_INC}/../Sys  \
        -I${BPM_INC}/../Ipc
COMMONOBJS= its_app.o its_error.o its_license.o its_features.o its_chksum.o \
            its_object.o its_callback.o its_trace.o its_iniparse.o its_crypt.o \
            its_assertion.o its_hash.o its_dsm.o its_pegs.o its_time.o \
	    its_alarms.o its_behaviors.o its_list.o its_mlist.o its_factory.o \
	    its_lockable.o its_dsmqueue.o its_splay.o its_rb.o its_ring_buf.o its_pprint.o
            
COBJS= its.o its_classes.o
SCOBJS= its_standalone.o its_sclasses.o

ifneq ($(PLATFORM),vxworks)

CRSRCS:=$(shell /bin/ls crlicense.c 2> /dev/null)
ifeq ($(CRSRCS),crlicense.c)
CROBJS= crlicense.o
else
CROBJS=
endif

MCRSRCS:=$(shell /bin/ls mcrlicense.c 2> /dev/null)
ifeq ($(MCRSRCS),mcrlicense.c)
MCROBJS= mcrlicense.o
else
MCROBJS=
endif

VRSRCS := $(shell /bin/ls vrlicense.c 2> /dev/null)
ifeq ($(VRSRCS),vrlicense.c)
VROBJS= vrlicense.o
else
VROBJS=
endif

PRSRCS := $(shell /bin/ls prlicense.c 2> /dev/null)
ifeq ($(PRSRCS),prlicense.c)
PROBJS= prlicense.o
else
PROBJS=
endif

GKSRCS := $(shell /bin/ls genkey.c 2> /dev/null)
ifeq ($(GKSRCS),genkey.c)
GKOBJS= genkey.o
else
GKOBJS=
endif

KLSRCS := $(shell /bin/ls keylicense.c 2> /dev/null)
ifeq ($(KLSRCS),keylicense.c)
KLOBJS= keylicense.o
else
KLOBJS=
endif

endif

PLCSRCS=its_mutex.c
PLCOBJS=its_mutex.o

.PHONY: links

all: links ../../lib/libCORE$(DBGSUFFIX).a ../../lib/libSCORE$(DBGSUFFIX).a \
     ../../bin/crlicense$(DBGSUFFIX) ../../bin/vrlicense$(DBGSUFFIX) \
     ../../bin/prlicense$(DBGSUFFIX) ../../bin/genkey$(DBGSUFFIX) \
     ../../bin/keylicense$(DBGSUFFIX) ../../bin/mcrlicense$(DBGSUFFIX)

clean:
	$(RM) *.o .depend \
		../../lib/libCORE$(DBGSUFFIX).a \
		../../lib/libSCORE$(DBGSUFFIX).a \
		../../bin/crlicense$(DBGSUFFIX) \
		../../bin/mcrlicense$(DBGSUFFIX) \
		../../bin/prlicense$(DBGSUFFIX) \
		../../bin/vrlicense$(DBGSUFFIX) \
		../../bin/genkey$(DBGSUFFIX) \
		../../bin/keylicense$(DBGSUFFIX) \
		$(PLCSRCS)

../../lib/libCORE$(DBGSUFFIX).a: $(COMMONOBJS) $(COBJS) $(PLCOBJS)
	$(AR) $(ARFLAGS) ../../lib/libCORE$(DBGSUFFIX).a \
		$(COMMONOBJS) $(COBJS) $(PLCOBJS)

../../lib/libSCORE$(DBGSUFFIX).a: $(COMMONOBJS) $(SCOBJS) $(PLCOBJS)
	$(AR) $(ARFLAGS) ../../lib/libSCORE$(DBGSUFFIX).a \
		$(COMMONOBJS) $(SCOBJS) $(PLCOBJS)

ifneq ($(PLATFORM),vxworks)

../../bin/crlicense$(DBGSUFFIX): $(CROBJS) ../../lib/libSCORE$(DBGSUFFIX).a
	if [ -f itscore.h ]; then \
	   if [  X$(CRSRCS) != X ]; then \
		$(CC) $(CFLAGS) -o ../../bin/crlicense$(DBGSUFFIX) \
			$(CROBJS) ../../lib/libSCORE$(DBGSUFFIX).a \
			$(THREADLIBS); \
	   fi \
	fi

../../bin/mcrlicense$(DBGSUFFIX): $(MCROBJS) ../../lib/libSCORE$(DBGSUFFIX).a
	if [ -f itscore.h ]; then \
	   if [  X$(MCRSRCS) != X ]; then \
		$(CC) $(CFLAGS) -o ../../bin/mcrlicense$(DBGSUFFIX) \
			$(MCROBJS) ../../lib/libSCORE$(DBGSUFFIX).a \
			$(THREADLIBS); \
	   fi \
	fi

../../bin/vrlicense$(DBGSUFFIX): $(VROBJS) ../../lib/libSCORE$(DBGSUFFIX).a
	if [ -f itscore.h ]; then \
	   if [ X$(VRSRCS) != X ]; then \
		$(CC) $(CFLAGS) -o ../../bin/vrlicense$(DBGSUFFIX) \
			$(VROBJS) ../../lib/libSCORE$(DBGSUFFIX).a \
			$(THREADLIBS); \
	   fi \
	fi

../../bin/prlicense$(DBGSUFFIX): $(PROBJS) ../../lib/libSCORE$(DBGSUFFIX).a
	if [ -f itscore.h ]; then \
	   if [ X$(PRSRCS) != X ]; then \
		$(CC) $(CFLAGS) -o ../../bin/prlicense$(DBGSUFFIX) \
			$(PROBJS) ../../lib/libSCORE$(DBGSUFFIX).a \
			$(THREADLIBS); \
	   fi \
	fi

../../bin/genkey$(DBGSUFFIX): $(GKOBJS) ../../lib/libSCORE$(DBGSUFFIX).a
	if [ -f itscore.h ]; then \
	   if [ X$(GKSRCS) != X ]; then \
		$(CC) $(CFLAGS) -o ../../bin/genkey$(DBGSUFFIX) \
			$(GKOBJS) ../../lib/libSCORE$(DBGSUFFIX).a \
			$(THREADLIBS); \
	   fi \
	fi

../../bin/keylicense$(DBGSUFFIX): $(KLOBJS) ../../lib/libSCORE$(DBGSUFFIX).a
	if [ -f itscore.h ]; then \
	   if [ X$(KLSRCS) != X ]; then \
		$(CC) $(CFLAGS) -o ../../bin/keylicense$(DBGSUFFIX) \
			$(KLOBJS) ../../lib/libSCORE$(DBGSUFFIX).a \
			$(THREADLIBS); \
	   fi \
	fi

else

../../bin/crlicense$(DBGSUFFIX):
../../bin/mcrlicense$(DBGSUFFIX):
../../bin/vrlicense$(DBGSUFFIX):
../../bin/prlicense$(DBGSUFFIX):
../../bin/genkey$(DBGSUFFIX):
../../bin/keylicense$(DBGSUFFIX):

endif

$(PLCOBJS): $(PLCSRCS)

its_sclasses.o: its_classes.c
	$(CC) $(CFLAGS) -c -DSTANDALONE -o its_sclasses.o its_classes.c

ifeq ($(PLATFORM),vxworks)
links:
	copy platforms\$(PLATFORM)\*.c .
else
links:
	if [ $(PLATFORM) = solaris64 ]; then                            \
            if [ ! -h platforms/$(PLATFORM) ]; then                     \
                       $(LN) solaris platforms/$(PLATFORM);             \
            fi                                                          \
        fi                                                              \
        ; \
        if [ $(PLATFORM) = mvlppc ]; then                               \
           for file in $(PLCSRCS);                                      \
           do                                                           \
                if [ ! -f $$file ];                                     \
		then                                                    \
                        $(LN) platforms/linux/$$file $$file;            \
		fi                                                      \
           done;                                                        \
        fi                                                              \
        ; \
        if [ $(PLATFORM) != mvlppc ]; then                              \
           for file in $(PLCSRCS);                                      \
           do                                                           \
                if [ ! -f $$file ];                                     \
		then                                                    \
                    if [ ! -h $$file ];                                 \
		    then                                                \
                        $(LN) platforms/$(PLATFORM)/$$file $$file;      \
                    fi                                                  \
		fi                                                      \
           done                                                         \
        fi 
endif
#
# get the rules
#
include $(ITS_ROOT)/config.rules
