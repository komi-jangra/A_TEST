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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:19  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1.8.2  2005/11/30 10:06:28  sjaddu
# LOG: Porting to MVL on power pc.
# LOG:
# LOG: Revision 9.1.8.1  2005/09/14 16:38:15  lbana
# LOG: added platform variable for montavista
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:37  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.4  2005/03/21 13:51:57  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.5  2003/01/16 16:18:34  mmiers
# LOG: Code reorganization.
# LOG:
# LOG: Revision 7.4  2002/12/20 19:40:41  mmiers
# LOG: Move files.
# LOG:
# LOG: Revision 7.3  2002/11/21 01:50:59  pmandal
# LOG: start building 64 bit solaris
# LOG:
# LOG: Revision 7.2  2002/11/09 21:26:09  randresol
# LOG: Add its_route_rwlock.o
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.5  2002/04/16 21:20:30  hdivoux
# LOG: FT/HA integration.
# LOG:
# LOG: Revision 6.4  2002/03/26 18:07:26  randresol
# LOG: Add its_dsmqueue.o
# LOG:
# LOG: Revision 6.3  2002/03/14 18:01:34  mmiers
# LOG: license fixes, new behaviors implementation, timer block
# LOG:
# LOG: Revision 6.2  2002/02/28 23:29:04  mmiers
# LOG: Add to alarm API, add peg API.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.4  2001/11/07 22:42:14  mmiers
# LOG: Add IPC mutex.
# LOG:
# LOG: Revision 5.3  2001/09/04 23:38:23  mmiers
# LOG: Add the link functions.
# LOG:
# LOG: Revision 5.2  2001/08/17 15:03:24  mmiers
# LOG: Need target in both sections of if
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:10  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.15  2001/08/16 19:42:59  lbana
# LOG: Get make to work for vxworks.
# LOG:
# LOG: Revision 4.14  2001/08/16 19:07:33  mmiers
# LOG: Fix vxWorks.
# LOG:
# LOG: Revision 4.13  2001/08/16 18:57:57  lbana
# LOG: ON host NT file is not expanding in phony target, for vxworks builds
# LOG:
# LOG: Revision 4.12  2001/08/13 22:39:43  mmiers
# LOG: Acknowledge the split in the makefile.
# LOG:
# LOG: Revision 4.11  2001/07/03 21:16:22  mmiers
# LOG: Move RM and DSM.
# LOG:
# LOG: Revision 4.10  2001/06/20 19:55:41  mmiers
# LOG: Split DSM out into a separate library.
# LOG:
# LOG: Revision 4.9  2001/06/14 21:54:43  mmiers
# LOG: Use macro (can't use size directly).
# LOG:
# LOG: Revision 4.8  2001/06/14 21:29:15  mmiers
# LOG: Don't commit stubs comment, dammit.
# LOG:
# LOG: Revision 4.7  2001/06/14 21:28:53  mmiers
# LOG: Print copy error.
# LOG:
# LOG: Revision 4.6  2001/06/14 19:03:37  mmiers
# LOG: Don't commit commented stubs.
# LOG:
# LOG: Revision 4.5  2001/06/14 19:02:51  mmiers
# LOG: Give instance a size.
# LOG:
# LOG: Revision 4.4  2001/05/10 00:54:20  mmiers
# LOG: Correct a missing file, remove warnings.
# LOG:
# LOG: Revision 4.3  2001/05/04 21:25:21  mmiers
# LOG: Start with platform independence.  May lose this later.
# LOG:
# LOG: Revision 4.2  2001/05/04 18:30:28  mmiers
# LOG: Move these back.  Support can't be dynamically loaded due to
# LOG: WIN32.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.20  2001/05/01 00:40:03  mmiers
# LOG: Prep for PR5.
# LOG:
# LOG: Revision 3.19  2001/04/10 19:57:19  mmiers
# LOG: Still debugging.
# LOG:
# LOG: Revision 3.18  2001/03/06 22:19:30  mmiers
# LOG: Cross-platform cleanup.
# LOG:
# LOG: Revision 3.17  2001/03/06 22:01:23  mmiers
# LOG: New statics file for CPP globals.  Down to one SUPPORT lib.
# LOG:
# LOG: Revision 3.16  2001/03/06 02:17:17  mmiers
# LOG: Work on circular dependencies, down to one cpp file.  Need to
# LOG: modify exception compiler to get rid of this last dependency.
# LOG: Then we get to eliminate two more lib copies.
# LOG:
# LOG: Revision 3.15  2001/03/02 23:04:04  mmiers
# LOG: Cross platform cleanup.
# LOG:
# LOG: Revision 3.14  2001/03/02 22:44:15  mmiers
# LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
# LOG: always.  The rest will be loaded on demand.
# LOG:
# LOG: Revision 3.13  2001/03/02 20:56:06  mmiers
# LOG: Add the WorkItemPool.
# LOG:
# LOG: Revision 3.12  2001/02/08 22:48:56  mmiers
# LOG: Get it to work on Linux.
# LOG:
# LOG: Revision 3.11  2001/01/20 00:02:50  mmiers
# LOG: Ditch the non STL lists.  STL deque is faster.
# LOG:
# LOG: Revision 3.10  2001/01/18 18:46:28  mmiers
# LOG: CPP service based on C service.
# LOG:
# LOG: Revision 3.9  2001/01/17 01:01:34  mmiers
# LOG: Convert event log to C.  Add dispatch project.
# LOG:
# LOG: Revision 3.8  2001/01/16 21:39:25  mmiers
# LOG: Reorganize so that support is completely standalone
# LOG:
# LOG: Revision 3.7  2001/01/09 23:54:55  mmiers
# LOG: Remove the last vestiges of the C++ basis (for VxWorks)
# LOG:
# LOG: Revision 3.6  2000/12/20 22:12:35  mmiers
# LOG: Still condvar problems on Solaris
# LOG:
# LOG: Revision 3.5  2000/11/29 20:08:06  mmiers
# LOG: Add SCTP transport
# LOG:
# LOG: Revision 3.4  2000/10/03 21:17:08  mmiers
# LOG: Today's installment.  Getting real close now.
# LOG:
# LOG: Revision 3.3  2000/09/01 15:35:53  mmiers
# LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
# LOG:
# LOG: Revision 3.2  2000/08/17 23:27:22  mmiers
# LOG: Add user data to list remove procs
# LOG: Add memory pool for quick reclamation
# LOG: Add object creation into user supplied buffer
# LOG:
# LOG: Revision 3.1  2000/08/16 00:05:20  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.19  2000/08/09 22:53:21  mmiers
# LOG: Typo in dependencies
# LOG:
# LOG: Revision 2.18  2000/08/09 00:08:23  mmiers
# LOG:
# LOG: Semaphore is now platform neutral.
# LOG: Add new error code.
# LOG: Work on SCTP
# LOG: Make CONDVAR take a timeout on wait.
# LOG: Add new entry point to TIMERS.
# LOG:
# LOG: Revision 2.17  2000/05/22 18:27:36  mmiers
# LOG:
# LOG:
# LOG: Add framework for SCTP transports.
# LOG:
# LOG: Revision 2.16  2000/05/22 17:02:17  mmiers
# LOG:
# LOG:
# LOG: Add adler target.
# LOG:
# LOG: Revision 2.15  2000/05/11 02:06:13  mmiers
# LOG:
# LOG:
# LOG: tools: warning removal.  Hubert needs to take over for the comps.
# LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
# LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
# LOG: perspective, but IMAL class needs implementation.
# LOG: config.vars: correct platform flags for Linux.
# LOG:
# LOG: Revision 2.14  2000/05/10 23:52:19  mmiers
# LOG:
# LOG:
# LOG: Update makefiles.
# LOG:
# LOG: Revision 2.13  2000/05/03 21:07:15  mmiers
# LOG:
# LOG:
# LOG: Start adding support for reader/writer locks.
# LOG: Add SOCK_GetPeerName().
# LOG:
# LOG: Revision 2.12  2000/04/25 14:52:53  mmiers
# LOG:
# LOG:
# LOG: Add condition variable type.  Also remove race from thread
# LOG: pool where allocated but not started thread could miss pool
# LOG: destruction [Ricardo].
# LOG:
# LOG: Revision 2.11  2000/03/01 16:30:37  ssharma
# LOG: Fixed a typo in the Makefile.
# LOG:
# LOG: Revision 2.10  2000/02/12 00:08:43  mmiers
# LOG:
# LOG: Move RESFILE to core library.  Convert RESFILE and TRACE to OO footing.
# LOG:
# LOG: Revision 2.9  2000/02/01 19:17:44  mmiers
# LOG:
# LOG:
# LOG: Straighten things out a little better (more appropriate stuff in core).
# LOG:
# LOG: Revision 2.8  2000/01/27 00:05:10  mmiers
# LOG:
# LOG: Make core lib smarter
# LOG:
# LOG: Revision 2.7  2000/01/25 02:36:16  mmiers
# LOG:
# LOG:
# LOG: UNIX update.
# LOG:
# LOG: Revision 2.6  1999/12/17 20:41:20  mmiers
# LOG:
# LOG:
# LOG: Still trying to get this to work.
# LOG:
# LOG: Revision 2.5  1999/12/17 16:44:17  mmiers
# LOG:
# LOG:
# LOG: New files.
# LOG:
# LOG: Revision 2.4  1999/12/16 16:40:40  mmiers
# LOG:
# LOG:
# LOG: Correct build, remove collided file
# LOG:
# LOG: Revision 2.3  1999/12/16 16:15:32  mmiers
# LOG: Sanitize the build environment a bit.
# LOG:
# LOG: Revision 2.2  1999/12/15 14:38:09  labuser
# LOG: Added its_object.o and its_lockable.o
# LOG:
# LOG: Revision 2.1  1999/12/04 00:09:11  mmiers
# LOG:
# LOG:
# LOG: Remove GDI from here.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:27:25  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.56  1999/11/10 18:20:33  mmiers
# LOG:
# LOG:
# LOG: Add GDI transport
# LOG:
# LOG: Revision 1.55  1999/10/25 18:55:26  mmiers
# LOG:
# LOG:
# LOG: Cross platform build.
# LOG:
# LOG: Revision 1.54  1999/09/17 16:56:05  labuser
# LOG:
# LOG:
# LOG: Fix typo in clean rule
# LOG:
# LOG: Revision 1.53  1999/08/18 01:00:02  mmiers
# LOG:
# LOG:
# LOG: More work on C services.
# LOG:
# LOG: Revision 1.52  1999/08/10 21:58:39  labuser
# LOG:
# LOG:
# LOG: Forgot the class name on the comment char method
# LOG:
# LOG: Revision 1.51  1999/07/29 02:11:42  mmiers
# LOG:
# LOG:
# LOG: Correct build errors after addressing Hubert's comments.
# LOG:
# LOG: Revision 1.50  1999/07/01 02:29:14  mmiers
# LOG:
# LOG: On Solaris, you build C++ libraries with the compiler, of all
# LOG: things.  Add new make variables accordingly.
# LOG:
# LOG: Revision 1.49  1999/06/28 20:34:22  mmiers
# LOG:
# LOG:
# LOG: Add MTP3 to CXXFLAGS include path.
# LOG:
# LOG: Revision 1.48  1999/06/28 19:13:07  skarmakar
# LOG:
# LOG:
# LOG: Update with awareness of throw specifiers.
# LOG:
# LOG: Revision 1.47  1999/06/28 16:59:27  mmiers
# LOG:
# LOG:
# LOG: Move the dispatchers to the support library for convenience.f
# LOG:
# LOG: Revision 1.46  1999/06/24 00:59:10  mmiers
# LOG:
# LOG:
# LOG: Add an IPC type semaphore
# LOG:
# LOG: Revision 1.45  1999/04/26 22:23:55  skarmakar
# LOG:
# LOG:
# LOG: Save build changes, update LIDB test.
# LOG:
# LOG: Revision 1.44  1999/03/23 21:25:10  mmiers
# LOG:
# LOG:
# LOG: Update for new core libraries.
# LOG:
# LOG: Revision 1.43  1998/11/18 03:37:57  mmiers
# LOG: Build some service classes.  Need to debug tomorrow.
# LOG:
# LOG: Revision 1.42  1998/11/18 00:52:33  mmiers
# LOG: Add event log to unix build
# LOG:
# LOG: Revision 1.41  1998/11/18 00:23:44  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.40  1998/11/17 23:57:44  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.39  1998/11/17 16:49:36  jrao
# LOG: Different name for Library suffix.
# LOG:
# LOG: Revision 1.38  1998/11/17 15:23:31  mmiers
# LOG: Multibuild (opt and debug)
# LOG:
# LOG: Revision 1.37  1998/11/03 02:23:40  mmiers
# LOG: Add callback implementation.
# LOG:
# LOG: Revision 1.36  1998/10/29 00:31:17  mmiers
# LOG: Add worker object to C build.
# LOG:
# LOG: Revision 1.35  1998/10/28 02:02:23  mmiers
# LOG: Do a test build, make the C thread pool compile.
# LOG:
# LOG: Revision 1.34  1998/09/30 02:40:12  mmiers
# LOG: Updates for SCCP.  I think I've got the compromises for SCCP routing
# LOG: down.  Need to add the routing label everywhere.
# LOG:
# LOG: Revision 1.33  1998/09/26 16:09:12  mmiers
# LOG: Use variables, not commands.
# LOG:
# LOG: Revision 1.32  1998/09/26 15:49:09  mmiers
# LOG: Move -c to config.rules
# LOG:
# LOG: Revision 1.31  1998/09/22 23:56:32  jrao
# LOG: Changes made to accomodate HPUX code
# LOG:
# LOG: Revision 1.30  1998/09/22 22:36:33  jrao
# LOG: Hacks for POSIX threads (Suspend()/Resume()).  An attempt to allow the
# LOG: user to start suspended threads.
# LOG:
# LOG: Revision 1.29  1998/09/22 16:01:28  jrao
# LOG: Port to HPUX.  Some work still needs to be done with threading -- using
# LOG: condition variables to support Suspend()/Resume().
# LOG:
# LOG: Revision 1.28  1998/06/23 02:31:09  mmiers
# LOG: Update Solaris build environment.  Part of getting SCCP working.
# LOG:
# LOG: Revision 1.27  1998/06/18 03:10:08  mmiers
# LOG: Build on Solaris.  Right now, the NT build is not OK.
# LOG:
# LOG: Revision 1.26  1998/06/18 02:37:14  mmiers
# LOG: More work on the C side for back compat.
# LOG:
# LOG: Revision 1.25  1998/05/29 03:31:34  mmiers
# LOG: More work on documentation.  Most of this is just adding interface
# LOG: description boxes without actually adding text.  Some of this is
# LOG: genuine bug fixing.
# LOG:
# LOG: Revision 1.24  1998/05/27 02:18:12  mmiers
# LOG: Reimplement fifos for NT and Solaris.  Nobody should be affected by this
# LOG: change (from a user perspective), but ITS_Worker has a new transport type,
# LOG: depending on whether or not the FIFO transport is reentrant.
# LOG:
# LOG: Revision 1.23  1998/05/22 03:28:19  mmiers
# LOG: Small update to start creating automatic documentation generation.
# LOG:
# LOG: Revision 1.22  1998/05/21 02:15:28  mmiers
# LOG: General cleanup to reflect TCAP changes (INAP, IS41).  Some missing
# LOG: files in builds.  Update the test to include the SCCP library.  I'll
# LOG: have to modify TCAP tomorrow to use SCCP_SendEvent instead of
# LOG: TRANSPORT_PutEvent().  Less efficient, but more useable with someone
# LOG: else's SCCP.
# LOG:
# LOG: Revision 1.21  1998/05/20 15:02:07  mmiers
# LOG: Minor tweaks for Solaris builds.
# LOG:
# LOG: Revision 1.20  1998/05/20 04:44:08  mmiers
# LOG: Cleanup.
# LOG: Hubert, some iterators need to be constant while others don't.  Please
# LOG: see me about this.
# LOG:
# LOG: Revision 1.19  1998/05/20 02:04:21  mmiers
# LOG: Tree cleanup.
# LOG:
# LOG: Revision 1.18  1998/05/19 23:52:14  mmiers
# LOG: Update the support library to use the exception compiler
# LOG: (UNIX platforms).
# LOG:
# LOG: Revision 1.17  1998/05/14 01:22:44  mmiers
# LOG: General cleanup.  Remove dead files.  Adjust include comments.
# LOG:
# LOG: Revision 1.16  1998/05/05 01:59:01  mmiers
# LOG: Sanitize the build environment a bit.  This gets the Solaris
# LOG: environment to build cleanly.
# LOG:
# LOG: Revision 1.15  1998/04/24 01:41:35  mmiers
# LOG: General cleanup of the build system.  Need to verify on Digital Unix
# LOG: to make sure this is ok.
# LOG:
# LOG: Revision 1.14  1998/04/23 01:34:07  mmiers
# LOG: Update after building on Solaris.
# LOG:
# LOG: Revision 1.13  1998/04/19 02:42:48  mmiers
# LOG: Pretty close to having the basic worker architecture for the HLR
# LOG: done.
# LOG:
# LOG: Revision 1.12  1998/04/17 03:36:27  mmiers
# LOG: Start with a FIRST CUT at an implementation for thread pools.
# LOG:
# LOG: Revision 1.11  1998/04/17 02:11:44  mmiers
# LOG: Fix transports on Solaris.  Add dependency computation to Makefile.
# LOG:
# LOG: Revision 1.10  1998/04/16 04:46:31  mmiers
# LOG: Fixes for WIP.
# LOG:
# LOG: Revision 1.9  1998/04/16 04:34:50  mmiers
# LOG: Add gated versions to the Makefile
# LOG:
# LOG: Revision 1.8  1998/04/13 22:19:21  mmiers
# LOG: Fifo (named pipe) implementation.  For portability, fifos can be
# LOG: RDONLY or WRONLY, but not both (i.e., not bidirectional).  For
# LOG: bidirectional communication, use two fifos.
# LOG:
# LOG: Revision 1.7  1998/04/09 01:47:20  mmiers
# LOG: Some of these are false positives, but most have had modifications.  More
# LOG: work on the infrastructure.
# LOG:
# LOG: Revision 1.6  1998/04/09 00:41:45  mmiers
# LOG: Resolve merge.
# LOG:
# LOG: Revision 1.5  1998/04/08 18:43:25  mmiers
# LOG: Get sockets to build on Solaris.
# LOG:
# LOG: Revision 1.4  1998/04/07 14:32:49  mmiers
# LOG: Update the makefile for conversion to gcc-2.8.1.
# LOG:
# LOG: Revision 1.3  1998/03/20 02:45:25  mmiers
# LOG: Add one file for the error_num to error_text translation.  Get this out of
# LOG: the vendor tree, it is shared.
# LOG:
# LOG: Revision 1.2  1998/03/13 04:11:46  mmiers
# LOG: Update files with latest code.  emlist represents portable message queues.
# LOG:
# LOG: Revision 1.1  1998/03/12 00:25:59  mmiers
# LOG: Get them to build on solaris.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars
CFLAGS := $(CFLAGS) -I${BPM_INC}  \
        -I${BPM_INC}/../Sys  \
        -I${BPM_INC}/../Ipc

LINKS = links

PLCSRCS=its_thread.c its_fifo.c its_serv.c its_dlsym.c \
        its_sockets.c its_ipc_semaphore.c its_condvar.c its_ipc_mutex.c
PLCOBJS=its_thread.o its_fifo.o its_serv.o its_dlsym.o \
        its_sockets.o its_ipc_semaphore.o its_condvar.o its_ipc_mutex.o

OBJS=its_emlist.o its_timers.o its_event_log.o its_transports.o \
     its_route.o its_rwlock.o its_semaphore.o its_fifo_trans.o \
     its_gfifo_trans.o its_ip_trans.o its_ss7_trans.o its_task_trans.o \
     its_thread_pool.o its_worker.o its_mem_pool.o its_serv-common.o \
     its_transport_factory.o its_kasock_trans.o its_gdi_trans.o \
     its_worker_factory.o its_imal_trans.o its_tali_trans.o \
     its_sctp_trans.o its_work_item.o its_work_item_pool.o its_alarm.o \
     its_hmi.o its_app_route.o its_ss7_route.o its_ss7_link.o its_ftm.o \
     its_route_rwlock.o

.PHONY: $(LINKS)

all: $(LINKS) ../../lib/libSUPPORT$(DBGSUFFIX).a \
	$(ITS_ROOT)/common/include/its_support_exception.cpp \
	$(ITS_ROOT)/common/include/its_support_exception.h

clean:
	$(RM) *.o ../../lib/libSUPPORT$(DBGSUFFIX).a \
		../../include/its_support_exception.cpp \
		../../include/its_support_exception.h .depend \
                $(PLCSRCS)

../../lib/libSUPPORT$(DBGSUFFIX).a: $(OBJS) $(PLCOBJS)
	$(AR) $(ARFLAGS) ../../lib/libSUPPORT$(DBGSUFFIX).a $(PLCOBJS) $(OBJS)

$(ITS_ROOT)/common/include/its_support_exception.cpp \
$(ITS_ROOT)/common/include/its_support_exception.h: its_support_exception.exc
	$(EXC)$(DBGSUFFIX) its_support_exception.exc
	$(MV) its_support_exception.h ../../include
	$(MV) its_support_exception.cpp ../../include

$(PLCOBJS): $(PLCSRCS)

ifeq ($(PLATFORM),vxworks)
links:
	copy platforms\$(PLATFORM)\*.c .
else
ifeq ($(PLATFORM),montavista)
links:
	cp platforms/linux/*.c .
else
links:
	if [ $(PLATFORM) = solaris64 ]; then                            \
            if [ ! -h platforms/$(PLATFORM) ]; then                     \
                       $(LN) solaris platforms/$(PLATFORM);             \
            fi                                                          \
        fi                                                              \
        ; \
        if [ $(PLATFORM) = mvlppc ]; then                         \
           for file in $(PLCSRCS);                                      \
           do                                                           \
                if [ ! -f $$file ];                                     \
                then                                                    \
                        $(LN) platforms/linux/$$file $$file;            \
                fi                                                      \
           done;                                                      \
        else                                                               \
	   for file in $(PLCSRCS);					\
	   do								\
		if [ ! -f $$file ];					\
		then							\
			$(LN) platforms/$(PLATFORM)/$$file $$file;	\
		fi							\
	   done; \
         fi
endif
endif

#
# get the rules
#
include $(ITS_ROOT)/config.rules
