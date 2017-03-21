#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:14  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
# BscCs2
#
# Revision 1.1  2007/03/30 04:54:02  cvsadmin
# *** empty log message ***
#
# Revision 1.1.1.1  2006/12/22 13:34:23  cvsadmin
# Initialising sources in CVS
#
# Revision 8.2  2005/03/21 13:51:21  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:09:46  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:18  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:04  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:15  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:04:52  mmiers
#
# Begin round 4.
#
# Revision 1.3  2000/06/20 18:40:58  npopov
# Switch to using asncc_v2.exe.
#
# Revision 1.2  2000/03/28 16:21:40  npopov
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
MAINFLAGS = -c -W3 -Od -Z7 $(POPT) -Ze -D_WIN32 -DWIN32 -I$(COMMON_INCLUDE)\asn-cpp\
		-DWIN32_EXTRA_LEAN -DVC_EXTRALEAN -I$(COMMON_INCLUDE)
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -I$(COMMON_INCLUDE)\asn-cpp\\
		-DWIN32_EXTRA_LEAN -DVC_EXTRALEAN -I$(COMMON_INCLUDE)
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

!message Current libraries are asncpp$(TYPE).lib...
!message

OBJECTS = asn.obj asnany.obj asnbitstring.obj asnboolean.obj asnchoice.obj\
		asndescany.obj asndescbitstring.obj asndescboolean.obj\
		asndescchoice.obj asndescenumerated.obj asndescinteger.obj\
		asndescnull.obj asndescobject.obj asndescobjectidentifier.obj\
		asndescoctetstring.obj asndescreal.obj asndescsequence.obj\
		asndescsequenceof.obj asndescset.obj asndescsetof.obj\
		asnenumerated.obj asnerror.obj asnexception.obj asninteger.obj\
		asnnull.obj asnobject.obj asnobjectidentifier.obj\
		asnoctetstring.obj asnreal.obj asnsequence.obj asnsequenceof.obj\
		asnset.obj asnsetof.obj external.obj generalizedtime.obj\
		generalstring.obj graphicstring.obj ia5string.obj\
		iso646string.obj length.obj numericstring.obj\
		objectdescriptor.obj octets.obj printablestring.obj\
		t61string.obj tag.obj teletexstring.obj utctime.obj\
		videotexstring.obj visiblestring.obj


.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<



all:	ASN1_COMPILE\
	its_support_exception.cpp\
	asncpp$(TYPE).lib


asncpp$(TYPE).lib: $(OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(OBJECTS)
		mv $@ $(ITS_ROOT)/runtime


asnexception.obj: $*.cpp

asnexception.cpp: $*.exc
		sh -c "$(ITS_ROOT)/tools/bin/exc.exe $*.exc"
		mv $*.h ../../include/asn-cpp

ASN1_COMPILE: asnuseful.asn
		sh -c "$(ITS_ROOT)/tools/bin/asncc_v2 -cpp -cppNamespace its -cppFileNamesNoPrefix -cppFileNamesMixedCase AsnUseful.asn"
		mv *.h ../../include/asn-cpp

its_support_exception.cpp: ../support/its_support_exception.exc
		sh -c "$(ITS_ROOT)/tools/bin/exc.exe ../support/$*.exc"
		mv $*.h ../../include


clean:
	@if exist *.obj                      rm *.obj
	@if exist *.pdb                      rm *.pdb
	@if exist asnexception.cpp           rm asnexception.cpp
	@if exist asnexception.h             rm asnexception.h
	@if exist $(ITS_ROOT)/runtime/asncpp$(TYPE).lib rm $(ITS_ROOT)/runtime/asncpp$(TYPE).lib
	@echo Done

