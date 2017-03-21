#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:39  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:18  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:14:36  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:54:08  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:52:49  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:10:17  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:30  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:19  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:22  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:07:24  mmiers
#
# Begin round 4.
#
# Revision 1.2  2000/03/28 16:27:29  npopov
# Added Id & Log macros for CVS
#
#


CC       = cl
LINK     = link
IMPLIB   = lib
CONLIBS  = libc.lib kernel32.lib user32.lib
!ifndef debug
debug    = yes
!endif

CPU = ix86
POPT = -GB
OOPT = -GF -Gi- -Gm- -GR- -GX- -Gy -Oxsy

!if "$(debug)" == "yes"
CONFLAGS = -pdb:none -release -subsystem:console,4.0
MAINFLAGS = -c -W3 -ML -Od -Z7 $(POPT) -Ze -Zp8 -D_WIN32 -DWIN32\
		-DUSING_FLEX -I. -I$(ITS_ROOT)\common\include
LDEBUG   = -debug:full -debugtype:cv
!else if "$(debug)" == "no"
CONFLAGS = -pdb:none -release -subsystem:console,4.0
MAINFLAGS = -c -W3 -ML $(OOPT) $(POPT) -Ze -Zp8 -D_WIN32 -DWIN32\
		-DUSING_FLEX -I. -I$(ITS_ROOT)\common\include
LDEBUG   =
!else
!ERROR The macro "debug" incorrectly defined!
!endif

FLAGS      = $(MAINFLAGS)


OBJECTS = dfns.obj dtabs.obj etabs.obj main.obj misc.obj\
		pass2.obj ptabs.obj y.tab.obj

#!include $(ITS_ROOT)\tools\src\asnc\include.mak


.c.obj::
		$(CC) $(FLAGS) $<


all:		asnc.exe


asnc.exe:	$(OBJECTS)
		$(LINK) $(CONFLAGS) $(LDEBUG) -out:$@ $(OBJECTS) $(CONLIBS)
		mv $@ ..\..\bin

y.tab.c: lex.yy.c yacc.y
		bison --yacc --defines yacc.y
	
lex.yy.c: lex.l
		flex lex.l


clean:
	@if exist *.obj              rm *.obj
	@if exist *.pdb              rm *.pdb
	@if exist asnc.exe           rm asnc.exe
	@if exist y.tab.c            rm y.tab.c
	@if exist lex.yy.c           rm lex.yy.c
	@echo Done

