#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:23:53  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:13:23  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:52:25  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:50:23  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:09:23  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:02  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:45:48  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:11  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:02:07  mmiers
#
# Begin round 4.
#
# Revision 1.2  2000/03/28 16:25:51  npopov
# Added Id & Log macros for CVS
#
#


COMMON_INCLUDE = $(ITS_ROOT)\common\include
COMMON_LIB     = $(ITS_ROOT)\common\lib
SCCP_INCLUDE   = $(ITS_ROOT)\SCCP\include
MTP3_INCLUDE   = $(ITS_ROOT)\MTP3\include
IMPLIB         = lib
CC             = cl
LINK           = link
IMPLIB         = lib

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
LINKER = -debug
!else
RTSL = -MT
RTDL = -MD
LINKER = -release
!endif

CPU = ix86
POPT = -GB
OOPT = -GF -Gi- -Gm- -GR- -GX- -Gy -Oxsy -Zl

!if "$(debug)" == "yes"
MAINFLAGS = -c -W3 -Od -Z7 $(POPT) -Ze -D_WIN32 -DWIN32 -DWIN32_EXTRA_LEAN\
		-DVC_EXTRALEAN -I$(COMMON_INCLUDE) -I$(SCCP_INCLUDE)\
		-I$(MTP3_INCLUDE)
CONFLAGS = -pdb:none
LDEBUG   = -debug:full -debugtype:cv $(LINKER)
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -DWIN32_EXTRA_LEAN\
		-DVC_EXTRALEAN -I$(COMMON_INCLUDE) -I$(SCCP_INCLUDE)\
		-I$(MTP3_INCLUDE)
CONFLAGS = -pdb:none
LDEBUG   =  $(LINKER)
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
CONLIBS = msvcrtd.lib kernel32.lib advapi32.lib ws2_32.lib
TYPE = mdd
!else
CONLIBS = msvcrt.lib kernel32.lib advapi32.lib ws2_32.lib
TYPE = md
!endif
!else
!ERROR The macro "t" incorrectly defined!
!endif

!message Current libraries are: ansi-sccp$(TYPE).lib & ccitt-sccp$(TYPE).lib...
!message

ANSI_OBJECTS = ansi_sccp.obj ansi_sccp++.obj
CCITT_OBJECTS = ccitt_sccp.obj ccitt_sccp++.obj


.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<



all:	ansi-sccp$(TYPE).lib\
	ccitt-sccp$(TYPE).lib


ansi-sccp$(TYPE).lib: $(ANSI_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(ANSI_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
ccitt-sccp$(TYPE).lib: $(CCITT_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(CCITT_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime

ansi_sccp.obj: sccp.c
	$(CC) -DANSI $(CFLAGS) -Fo$@ sccp.c
ccitt_sccp.obj: sccp.c
	$(CC) -DCCITT $(CFLAGS) -Fo$@ sccp.c
ansi_sccp++.obj: sccp++.cpp
	$(CC) -DANSI $(CPLUSPLUSFLAGS) -Fo$@ sccp++.cpp
ccitt_sccp++.obj: sccp++.cpp
	$(CC) -DCCITT $(CPLUSPLUSFLAGS) -Fo$@ sccp++.cpp






clean:
	@if exist *.obj                      rm *.obj
	@if exist *.pdb                      rm *.pdb
	@if exist $(ITS_ROOT)/runtime/ansi-sccp$(TYPE).lib rm $(ITS_ROOT)/runtime/ansi-sccp$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/ccitt-sccp$(TYPE).lib rm $(ITS_ROOT)/runtime/ccitt-sccp$(TYPE).lib
	@echo Done

