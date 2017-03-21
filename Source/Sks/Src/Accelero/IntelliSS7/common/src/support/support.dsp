# Microsoft Developer Studio Project File - Name="support" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=support - Win32 Debug Multithreaded
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "support.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "support.mak" CFG="support - Win32 Debug Multithreaded"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "support - Win32 Release Multithreaded" (based on "Win32 (x86) Static Library")
!MESSAGE "support - Win32 Debug Multithreaded" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "support - Win32 Release Multithreaded"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "support0"
# PROP BASE Intermediate_Dir "support0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "support"
# PROP Intermediate_Dir "support"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\MTP2\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0400 /D "_MT" /D "ITS_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/SUPPORT.lib"

!ELSEIF  "$(CFG)" == "support - Win32 Debug Multithreaded"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "support_"
# PROP BASE Intermediate_Dir "support_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "supportD"
# PROP Intermediate_Dir "supportD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MT" /D _WIN32_WINNT=0x0400 /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "..\..\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\MTP2\include" /D "_DEBUG" /D "_MT" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WINDOWS" /D "ITS_IMPLEMENTATION" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\support.lib"
# ADD LIB32 /nologo /out:"../../lib/SUPPORTD.lib"

!ENDIF 

# Begin Target

# Name "support - Win32 Release Multithreaded"
# Name "support - Win32 Debug Multithreaded"
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp"
# Begin Source File

SOURCE=.\its_alarm.c
# End Source File
# Begin Source File

SOURCE=.\its_app_route.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_condvar.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_dlsym.c
# End Source File
# Begin Source File

SOURCE=.\its_emlist.c
# End Source File
# Begin Source File

SOURCE=.\its_event_log.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_fifo.c
# End Source File
# Begin Source File

SOURCE=.\its_fifo_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_ftm.c
# End Source File
# Begin Source File

SOURCE=.\its_gdi_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_gfifo_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_hmi.c
# End Source File
# Begin Source File

SOURCE=.\its_imal_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_ip_trans.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_ipc_mutex.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_ipc_semaphore.c
# End Source File
# Begin Source File

SOURCE=.\its_kasock_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_mem_pool.c
# End Source File
# Begin Source File

SOURCE=.\its_route.c
# End Source File
# Begin Source File

SOURCE=.\its_route_rwlock.c
# End Source File
# Begin Source File

SOURCE=.\its_rwlock.c
# End Source File
# Begin Source File

SOURCE=.\its_sctp_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_semaphore.c
# End Source File
# Begin Source File

SOURCE=".\its_serv-common.c"
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_serv.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_sockets.c
# End Source File
# Begin Source File

SOURCE=.\its_ss7_link.c
# End Source File
# Begin Source File

SOURCE=.\its_ss7_route.c
# End Source File
# Begin Source File

SOURCE=.\its_ss7_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_tali_trans.c
# End Source File
# Begin Source File

SOURCE=.\its_task_trans.c
# End Source File
# Begin Source File

SOURCE=.\platforms\WIN32\its_thread.c
# End Source File
# Begin Source File

SOURCE=.\its_thread_pool.c
# End Source File
# Begin Source File

SOURCE=.\its_timers.c
# End Source File
# Begin Source File

SOURCE=.\its_transport_factory.c
# End Source File
# Begin Source File

SOURCE=.\its_transports.c
# End Source File
# Begin Source File

SOURCE=.\its_work_item.c
# End Source File
# Begin Source File

SOURCE=.\its_work_item_pool.c
# End Source File
# Begin Source File

SOURCE=.\its_worker.c
# End Source File
# Begin Source File

SOURCE=.\its_worker_factory.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\include\gdi_msgs.h
# End Source File
# Begin Source File

SOURCE="..\..\include\its++.h"
# End Source File
# Begin Source File

SOURCE=..\..\include\its.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_alarm.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_app.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_banner.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_bc.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_callback.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_condvar.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_consts.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_dlsym.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_dsm.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_emlist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_event_log.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_exception.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_exception_log.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_fifo.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_fifo_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_fsm.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_ftm.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_gdi_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_gfifo.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_gfifo_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_gsockets.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_hash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_hmi.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_imal_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_iniparse.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_ip_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_kasock_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_license.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_link.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_list.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_lockable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_mem_pool.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_mlist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_object.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_pegs.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_ring_buf.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_route.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_route_rwlock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_rudp.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_rwlock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_sctp.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_sctp_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_semaphore.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_service.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_singleton.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_sockets.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_ss7_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_support_exception.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_tali_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_thread.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_thread_pool.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_timers.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_tq_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_trace.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_transport_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_transports.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_types.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_work_item.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_work_item_pool.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_worker.h
# End Source File
# Begin Source File

SOURCE=..\..\include\its_worker_factory.h
# End Source File
# Begin Source File

SOURCE=..\..\include\rudp_msgs.h
# End Source File
# Begin Source File

SOURCE=..\..\include\sctp_msgs.h
# End Source File
# Begin Source File

SOURCE=..\..\include\tali_msgs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\its_support_exception.exc

!IF  "$(CFG)" == "support - Win32 Release Multithreaded"

# Begin Custom Build
InputPath=.\its_support_exception.exc

BuildCmds= \
	$(ITS_ROOT)\tools\bin\exc its_support_exception.exc \
	copy .\its_support_exception.h ..\..\include \
	del .\its_support_exception.h \
	copy .\its_support_exception.cpp ..\..\include \
	del .\its_support_exception.cpp \
	

"..\..\include\its_support_exception.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\its_support_exception.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "support - Win32 Debug Multithreaded"

USERDEP__ITS_S="its_support_exception.exc"	"$(ITS_ROOT)/tools/bin/exc.exe"	
# Begin Custom Build - Compiling Exc file...
InputPath=.\its_support_exception.exc

BuildCmds= \
	$(ITS_ROOT)\tools\bin\exc its_support_exception.exc \
	copy .\its_support_exception.h ..\..\include \
	del .\its_support_exception.h \
	copy .\its_support_exception.cpp ..\..\include \
	del .\its_support_exception.cpp \
	

"..\..\include\its_support_exception.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\its_support_exception.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
