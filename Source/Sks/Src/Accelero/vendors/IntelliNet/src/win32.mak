#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:15:07  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:54:51  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:53:54  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:10:29  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:39  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:29  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/04 16:22:06  mmiers
# Start PR5.
#
# Revision 3.1  2000/08/16 00:09:44  mmiers
#
# Begin round 4.
#
# Revision 1.4  2000/04/13 17:29:55  npopov
# Added isupdummies.c.
#
# Revision 1.3  2000/04/07 15:39:54  npopov
# Fixed the build of ccittvendormdd.lib.
#
# Revision 1.2  2000/03/28 16:29:30  npopov
# Added Id & Log macros for CVS
#
#


COMMON_INCLUDE = $(ITS_ROOT)\common\include
COMMON_LIB     = $(ITS_ROOT)\common\lib
TCAP_INCLUDE   = $(ITS_ROOT)\TCAP\include
SCCP_INCLUDE   = $(ITS_ROOT)\SCCP\include
ISUP_INCLUDE   = $(ITS_ROOT)\ISUP\include
MTP3_INCLUDE   = $(ITS_ROOT)\MTP3\include
VENDOR_INCLUDE = $(CVSROOT)\vendors\intellinet\include
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
		-DVC_EXTRALEAN -I$(COMMON_INCLUDE) -I$(TCAP_INCLUDE)\
		-I$(SCCP_INCLUDE) -I$(MTP3_INCLUDE) -I$(TCAP_INCLUDE)\ansi\
		-I$(TCAP_INCLUDE)\itu -DINCLUDE_CODEC -I$(VENDOR_INCLUDE)\
		-I$(ISUP_INCLUDE)
CONFLAGS = -pdb:none
LDEBUG   = -debug:full -debugtype:cv $(LINKER)
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -DWIN32_EXTRA_LEAN\
		-DVC_EXTRALEAN -I$(COMMON_INCLUDE) -I$(TCAP_INCLUDE)\
		-I$(SCCP_INCLUDE) -I$(MTP3_INCLUDE) -I$(TCAP_INCLUDE)\ansi\
		-I$(TCAP_INCLUDE)\itu -DINCLUDE_CODEC -I$(VENDOR_INCLUDE)\
		-I$(ISUP_INCLUDE)
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

!message Current library is ansivendor$(TYPE).lib & ccittvendor$(TYPE).lib...
!message

ANSI_VENDOR_OBJECTS = ansi-mtp3.obj ansi-sccp.obj ansi-sccp_cvt.obj\
		ansi-sccp_gtt.obj ansi-sccp_ifc.obj ansi-sclc.obj\
		ansi-scmg.obj ansi-scoc.obj ansi-scrc.obj ansi-isup.obj\
		ansi-isup_ifc.obj isup-cics.obj ansi-cmp.obj ansi-tcap.obj\
		ansi-tcap_context.obj ansi-tcap_ifc.obj ansi-tpcpi.obj\
		ansi-trp.obj itu-stubs.obj ss7_features.obj
CCITT_VENDOR_OBJECTS = itu-mtp3.obj itu-sccp.obj itu-sccp_cvt.obj\
		itu-sccp_gtt.obj itu-sccp_ifc.obj itu-sclc.obj itu-scmg.obj\
		itu-scoc.obj itu-scrc.obj isup-cics.obj itu-cpc.obj\
		itu-isup.obj itu-isup_context.obj itu-isup_ifc.obj itu-mpc.obj\
		itu-sprc.obj itu-cco.obj itu-dha.obj itu-tcap.obj\
		itu-tcap_context.obj itu-tcap_ifc.obj itu-tco.obj itu-tsm.obj\
		ansi-stubs.obj ss7_features.obj isupdummies.obj


.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<



all:	ansivendor$(TYPE).lib\
	ccittvendor$(TYPE).lib


ansivendor$(TYPE).lib: $(ANSI_VENDOR_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(ANSI_VENDOR_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
ccittvendor$(TYPE).lib: $(CCITT_VENDOR_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(CCITT_VENDOR_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime




clean:
	@if exist *.obj                      rm *.obj
	@if exist *.pdb                      rm *.pdb
	@if exist $(ITS_ROOT)/runtime/ansivendor$(TYPE).lib  rm $(ITS_ROOT)/runtime/ansivendor$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/ccittvendor$(TYPE).lib rm $(ITS_ROOT)/runtime/ccittvendor$(TYPE).lib
	@echo Done

