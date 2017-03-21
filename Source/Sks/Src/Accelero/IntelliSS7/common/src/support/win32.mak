#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:53:41  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:52:03  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:10:04  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:24  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:12  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:17  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:05:49  mmiers
#
# Begin round 4.
#
# Revision 1.4  2000/06/15 19:34:42  npopov
# Updated for new files.
#
# Revision 1.3  2000/05/18 13:47:36  npopov
# Added new source files.
#
# Revision 1.2  2000/03/28 16:22:47  npopov
# Added Id & Log macros for CVS
#
#


SUPPORT = $(ITS_ROOT)\common\src\support
COMMON_INCLUDE = $(ITS_ROOT)\common\include
MTP3_INCLUDE = $(ITS_ROOT)\mtp3\include
SCCP_INCLUDE = $(ITS_ROOT)\sccp\include
TCAP_INCLUDE = $(ITS_ROOT)\tcap\include
IMPLIB   = lib
CC       = cl
LINK        = link
IMPLIB      = lib

!ifndef debug
debug = yes
!endif

!if "$(debug)" == "yes"
!else if "$(debug)" == "no"
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifndef msdebug
msdebug = yes
!endif

!if "$(msdebug)" == "yes"
RTSL = -MTd
RTDL = -MDd
!else
RTSL = -MT
RTDL = -MD
!endif

CPU = ix86
POPT = -GB
OOPT = -GF -Gi- -Gm- -GR- -GX- -Gy -Oxsy -Zl

!if "$(debug)" == "yes"
MAINFLAGS = -c -W3 -Od -Z7 $(POPT) -Ze -D_WIN32 -DWIN32 -D_WIN32_WINNT=0x0400\
		-DWIN32_EXTRA_LEAN -DVC_EXTRALEAN -I$(COMMON_INCLUDE)\
		-I$(MTP3_INCLUDE) -I$(SCCP_INCLUDE) -I$(TCAP_INCLUDE)
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -D_WIN32_WINNT=0x0400\
		-DWIN32_EXTRA_LEAN -DVC_EXTRALEAN -I$(COMMON_INCLUDE)\
		-I$(MTP3_INCLUDE) -I$(SCCP_INCLUDE) -I$(TCAP_INCLUDE)
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifdef t
MTYPE = $(t)
!else
MTYPE = d
mt = d
!endif

!if "$(MTYPE)" == "s"
CFLAGS = $(RTSL) $(MAINFLAGS)
CPLUSPLUSFLAGS = $(RTSL) $(MAINFLAGS) -GX
!if "$(msdebug)" == "yes"
TYPE = d
CONLIBS = libcmtd.lib kernel32.lib
!else
TYPE =
CONLIBS = libcmt.lib kernel32.lib
!endif
!else if "$(MTYPE)" == "d"
CFLAGS = $(RTDL) $(MAINFLAGS)
CPLUSPLUSFLAGS = $(RTDL) $(MAINFLAGS) -GX
!if "$(msdebug)" == "yes"
CONLIBS = msvcrtd.lib kernel32.lib
TYPE = mdd
!else
CONLIBS = msvcrt.lib kernel32.lib
TYPE = md
!endif
!else
!ERROR The macro "t" incorrectly defined!
!endif

!message Current libraries are support$(TYPE).lib and support++$(TYPE).lib...
!message

C_OBJECTS = its_adler.obj its_condvar.obj its_disp_both.obj\
		its_disp_ss7_ansi.obj its_disp_ss7_ccitt.obj its_dispatch.obj\
		its_emlist.obj its_fifo.obj its_fifo_trans.obj\
		its_gdi_trans.obj its_gfifo_trans.obj its_hash.obj\
		its_imal_trans.obj its_ip_trans.obj its_ipc_semaphore.obj\
		its_kasock_trans.obj its_list.obj its_lockable.obj\
		its_mlist.obj its_route.obj its_rudp.obj its_rwlock.obj\
		its_sctp_trans.obj its_semaphore.obj its_serv-common.obj\
		its_serv.obj its_sockets.obj its_ss7_trans.obj\
		its_tali_trans.obj its_task_trans.obj its_thread.obj\
		its_thread_pool.obj its_timers.obj its_transports.obj\
		its_worker.obj
		

CPLUSPLUS_OBJECTS = its_adler.obj its_condvar.obj its_condvar++.obj\
		its_disp_both++.obj its_disp_both.obj its_disp_ss7_ansi.obj\
		its_disp_ss7_ansi++.obj its_disp_ss7_ccitt++.obj\
		its_disp_ss7_ccitt.obj its_dispatch++.obj its_dispatch.obj\
		its_emlist++.obj its_emlist.obj its_event_log.obj\
		its_exception.obj its_exception_log.obj its_fifo++.obj\
		its_fifo.obj its_fifo_trans++.obj its_fifo_trans.obj\
		its_gdi_trans.obj its_gfifo++.obj its_gfifo_trans++.obj\
		its_gfifo_trans.obj its_gsockets++.obj its_hash.obj\
		its_imal_trans.obj its_ip_trans.obj its_ipc_semaphore++.obj\
		its_ipc_semaphore.obj its_ipclient_trans.obj its_ipeptrans.obj\
		its_ipserv_trans.obj its_kasock_trans.obj its_list++.obj\
		its_list.obj its_lockable.obj its_mlist++.obj its_mlist.obj\
		its_route.obj its_rudp.obj its_rwlock++.obj its_rwlock.obj\
		its_semaphore++.obj its_sctp_trans.obj its_semaphore.obj\
		its_serv-common.obj its_serv.obj its_service-common.obj\
		its_service.obj its_sockets++.obj its_sockets.obj\
		its_ss7_trans++.obj its_ss7_trans.obj its_support_exception.obj\
		its_tali_trans.obj its_task_trans++.obj its_task_trans.obj\
		its_thread++.obj its_thread.obj its_thread_pool++.obj\
		its_thread_pool.obj its_timers.obj its_transport_factory.obj\
		its_transports++.obj its_transports.obj its_worker++.obj\
		its_worker.obj its_worker_factory.obj



.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<



all:	support$(TYPE).lib\
	support++$(TYPE).lib


support$(TYPE).lib: $(C_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(C_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime

support++$(TYPE).lib: $(CPLUSPLUS_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(CPLUSPLUS_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime

its_support_exception.obj: its_support_exception.cpp

its_support_exception.cpp: its_support_exception.exc
		cmd.exe /c $(ITS_ROOT)/tools/bin/exc.exe $*.exc
		mv $*.h ../../include

its_fifo.obj: platforms/win32/$*.c
		$(CC) $(CFLAGS) platforms/win32/$*.c
its_ipc_semaphore.obj: platforms/win32/$*.c
		$(CC) $(CFLAGS) platforms/win32/$*.c
its_rudp.obj: ../rudp/$*.c
		$(CC) $(CFLAGS) ../rudp/$*.c
its_semaphore.obj: platforms/win32/$*.c
		$(CC) $(CFLAGS) platforms/win32/$*.c
its_serv.obj: platforms/win32/$*.c
		$(CC) $(CFLAGS) platforms/win32/$*.c
its_sockets.obj: platforms/win32/$*.c
		$(CC) $(CFLAGS) platforms/win32/$*.c
its_thread.obj: platforms/win32/$*.c
		$(CC) $(CFLAGS) platforms/win32/$*.c
its_service.obj: platforms/win32/$*.cpp
		$(CC) $(CPLUSPLUSFLAGS) platforms/win32/$*.cpp
its_condvar.obj: platforms/win32/$*.c
		$(CC) $(CFLAGS) platforms/win32/$*.c



clean:
	@if exist *.obj                      rm *.obj
	@if exist *.pdb                      rm *.pdb
	@if exist its_support_exception.cpp  rm its_support_exception.cpp
	@if exist its_support_exception.h    rm its_support_exception.h
	@if exist $(ITS_ROOT)/runtime/support$(TYPE).lib   rm $(ITS_ROOT)/runtime/support$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/support++$(TYPE).lib rm $(ITS_ROOT)/runtime/support++$(TYPE).lib
	@echo Done

