#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:44  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:21  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:54:18  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:53:08  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:10:19  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:37  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:24  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:25  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:08:39  mmiers
#
# Begin round 4.
#
# Revision 1.2  2000/03/28 16:28:33  npopov
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
POPT = -GB -GX
OOPT = -GF -Gi- -Gm- -GR- -GX -Gy -Oxsy

!if "$(debug)" == "yes"
CONFLAGS = -pdb:none -release -subsystem:console,4.0
MAINFLAGS = -c -W3 -ML -Od -Z7 $(POPT) -Ze -Zp8 -D_WIN32 -DWIN32\
		-I$(ITS_ROOT)\common\include -I. -DFLEX -DYY_USE_PROTOS\
		-DC_FLEX
LDEBUG   = -debug:full -debugtype:cv
!else if "$(debug)" == "no"
CONFLAGS = -pdb:none -release -subsystem:console,4.0
MAINFLAGS = -c -W3 -ML $(OOPT) $(POPT) -Ze -Zp8 -D_WIN32 -DWIN32\
		-I$(ITS_ROOT)\common\include -I. -DFLEX -DYY_USE_PROTOS\
		-DC_FLEX
LDEBUG   =
!else
!ERROR The macro "debug" incorrectly defined!
!endif

FLAGS      = $(MAINFLAGS)


OBJECTS = exc_assert.obj exc_generate.obj exc_lex.yy.obj exc_main.obj\
		exc_yacc.tab.obj


.c.obj::
		$(CC) $(FLAGS) $<
.cpp.obj::
		$(CC) $(FLAGS) $<


all:		exc.exe


exc.exe:	$(OBJECTS)
		$(LINK) $(CONFLAGS) $(LDEBUG) -out:$@ $(OBJECTS) $(CONLIBS)
		cp $@ ..\..\bin


exc_yacc.tab.cpp: exc_yacc.y
		bison -d exc_yacc.y -o exc_yacc.tab.cpp -S bison_parser
		cmd /c mv exc_yacc.tab.cpp.h exc_yacc.tab.h

exc_lex.yy.c:	exc_lex.l
		flex exc_lex.l
		cmd /c mv lex.yy.c exc_lex.yy.c


clean:
	@if exist *.obj              del *.obj
	@if exist *.pdb              del *.pdb
	@if exist exc.exe            del exc.exe
	@if exist exc_yacc.tab.cpp   del exc_yacc.tab.cpp
	@if exist exc_yacc.tab.h     del exc_yacc.tab.h
	@if exist exc_lex.yy.c       del exc_lex.yy.c
	@echo Done

