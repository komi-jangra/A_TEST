#
# Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:42  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:20  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:14:53  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:54:15  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:53:01  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:10:18  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:36  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:23  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:24  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:08:16  mmiers
#
# Begin round 4.
#
# Revision 1.1  2000/04/24 13:28:32  npopov
# A makefile for Win32 for regression testing.
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
		-I$(ITS_ROOT)\common\include -I. -DYY_NEVER_INTERACTIVE
LDEBUG   = -debug:full -debugtype:cv
!else if "$(debug)" == "no"
CONFLAGS = -pdb:none -release -subsystem:console,4.0
MAINFLAGS = -c -W3 -ML $(OOPT) $(POPT) -Ze -Zp8 -D_WIN32 -DWIN32\
		-I$(ITS_ROOT)\common\include -I. -DYY_NEVER_INTERACTIVE
LDEBUG   =
!else
!ERROR The macro "debug" incorrectly defined!
!endif

FLAGS      = $(MAINFLAGS)


OBJECTS = asncc_assertion.obj asncc_ast.obj asncc_check_semantic_visitor.obj\
		asncc_components_of_visitor.obj asncc_evaluate_visitor.obj\
		asncc_generate_c_visitor.obj asncc_generate_c_xml_doc_visitor.obj\
		asncc_generate_cpp_visitor.obj asncc_generate_cpp_xml_doc_visitor.obj\
		asncc_lexer.obj asncc_link_visitor.obj asncc_main.obj\
		asncc_normalize_visitor.obj asncc_parser.obj\
		asncc_print_visitor.obj asncc_recursive_visitor.obj asncc_tag.obj\
		asncc_util.obj asncc_visitor.obj


.c.obj::
		$(CC) $(FLAGS) $<
.cpp.obj::
		$(CC) $(FLAGS) $<


all:		asncc_v2.exe


asncc_v2.exe:	$(OBJECTS)
		$(LINK) $(CONFLAGS) $(LDEBUG) -out:$@ $(OBJECTS) $(CONLIBS)
		cp $@ ..\..\bin


asncc_lexer.cpp: asn1.lex
		cp asncc_unistd.h unistd.h
		flex -oasncc_lexer.cpp asn1.lex


asncc_parser.cpp: asn1.yacc
		bison asn1.yacc -t -v -d -o asncc_parser.cpp -S bison_parser
		mv asncc_parser.cpp.h asncc_parser.h


clean:
	@if exist *.obj              rm *.obj
	@if exist *.pdb              rm *.pdb
	@if exist asncc_v2.exe       rm asncc_v2.exe
	@if exist asncc_lexer.cpp    rm asncc_lexer.cpp
	@if exist asncc_parser.cpp   rm asncc_parser.cpp
	@if exist asncc_parser.h     rm asncc_parser.h
	@if exist unistd.h           rm unistd.h
	@echo Done

