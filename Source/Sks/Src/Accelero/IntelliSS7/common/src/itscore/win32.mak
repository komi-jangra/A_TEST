#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#

#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:53:30  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:51:50  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:09:54  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:23  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:07  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:16  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:05:08  mmiers
#
# Begin round 4.
#
# Revision 1.4  2000/06/15 19:34:31  npopov
# Updated for new files.
#
# Revision 1.3  2000/03/28 16:09:48  npopov
# Added Id & Log macros for CVS
#
#

COMMON_INCLUDE = $(ITS_ROOT)\common\include
IMPLIB   = lib
CC       = cl
LINK        = link
IMPLIB      = lib

!ifndef debug
debug = yes
!endif

!if "$(debug)" == "yes"
LDEBUG = -debug:full -debugtype:cv
LINKOPTIONS = -pdb:none -release
!else if "$(debug)" == "no"
LDEBUG =
LINKOPTIONS = -pdb:none -release
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
OOPT = -GF -Gi- -Gm- -GR- -GX- -Gy -Oxsy

!if "$(debug)" == "yes"
MAINFLAGS = -c -W3 -Od -Z7 $(POPT) -Ze -D_WIN32 -DWIN32 -I$(COMMON_INCLUDE)\
		-D_WIN32_WINNT=0x0400 -DNO_TIME_STAMP
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -I$(COMMON_INCLUDE)\
		-D_WIN32_WINNT=0x0400 -DNO_TIME_STAMP
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
CONLIBS = libcmtd.lib kernel32.lib advapi32.lib
!else
TYPE =
CONLIBS = libcmt.lib kernel32.lib advapi32.lib
!endif
!else if "$(MTYPE)" == "d"
CFLAGS = $(RTDL) $(MAINFLAGS)
CPLUSPLUSFLAGS = $(RTDL) $(MAINFLAGS) -GX
!if "$(msdebug)" == "yes"
CONLIBS = msvcrtd.lib kernel32.lib advapi32.lib
TYPE = mdd
!else
CONLIBS = msvcrt.lib kernel32.lib advapi32.lib
TYPE = md
!endif
!else
!ERROR The macro "t" incorrectly defined!
!endif

!message Current library is core++$(TYPE).lib...
!message

COREPLUSPLUS_OBJECTS = its++.obj its_app.obj its_assertion.obj its_callback.obj\
		its_classes.obj its_error.obj its_features.obj\
		its_iniparse++.obj its_iniparse.obj its_license.obj\
		its_mutex++.obj its_mutex.obj its_object.obj its_trace++.obj\
		its_trace.obj
C_OBJECTS = its.obj its_app.obj its_callback.obj its_classes.obj its_error.obj\
		its_features.obj its_iniparse.obj its_license.obj its_mutex.obj\
		its_object.obj its_trace.obj
SCOREPLUSPLUS_OBJECTS = its_app.obj its_assertion.obj its_callback.obj\
		its_classes.obj its_error.obj its_features.obj\
		its_iniparse++.obj its_iniparse.obj its_license.obj\
		its_mutex++.obj its_mutex.obj its_object.obj its_standalone.obj\
		its_trace++.obj its_trace.obj
SC_OBJECTS = its_app.obj its_assertion.obj its_callback.obj its_classes.obj\
		its_error.obj its_features.obj its_iniparse.obj its_license.obj\
		its_mutex.obj its_object.obj its_standalone.obj its_trace.obj


.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<


all:	core$(TYPE).lib\
	core++$(TYPE).lib\
	score++$(TYPE).lib\
	score$(TYPE).lib\
	crlicense.exe\
	prlicense.exe\
	vrlicense.exe


core++$(TYPE).lib: $(COREPLUSPLUS_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(COREPLUSPLUS_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime

score++$(TYPE).lib: $(SCOREPLUSPLUS_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(SCOREPLUSPLUS_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime

core$(TYPE).lib: $(C_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(C_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime

score$(TYPE).lib: $(SC_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(SC_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime

crlicense.exe:	crlicense.obj
		$(LINK) $(LINKOPTIONS) $(LDEBUG) -out:$@ $*.obj\
			$(ITS_ROOT)/runtime/score$(TYPE).lib $(CONLIBS)
		cp $@ ..\..\bin

prlicense.exe:	prlicense.obj
		$(LINK) $(LINKOPTIONS) $(LDEBUG) -out:$@ $*.obj\
			$(ITS_ROOT)/runtime/score$(TYPE).lib $(CONLIBS)
		cp $@ ..\..\bin

vrlicense.exe:	vrlicense.obj
		$(LINK) $(LINKOPTIONS) $(LDEBUG) -out:$@ $*.obj\
			$(ITS_ROOT)/runtime/score$(TYPE).lib $(CONLIBS)
		cp $@ ..\..\bin

its_mutex.obj: platforms/win32/its_mutex.c
		$(CC) $(CFLAGS) platforms/win32/$*.c



clean:
	@if exist *.obj              rm *.obj
	@if exist *.pdb              rm *.pdb
	@if exist $(ITS_ROOT)/runtime/core$(TYPE).lib    rm $(ITS_ROOT)/runtime/core$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/core++$(TYPE).lib  rm $(ITS_ROOT)/runtime/core++$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/score++$(TYPE).lib rm $(ITS_ROOT)/runtime/score++$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/score$(TYPE).lib   rm $(ITS_ROOT)/runtime/score$(TYPE).lib
	@if exist crlicense.exe      rm crlicense.exe
	@if exist prlicense.exe      rm prlicense.exe
	@echo Done

