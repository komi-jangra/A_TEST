# Microsoft Developer Studio Project File - Name="AsnC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AsnC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AsnC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsnC.mak" CFG="AsnC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsnC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AsnC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AsnC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/AsnC.lib"

!ELSEIF  "$(CFG)" == "AsnC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/AsnCD.lib"

!ENDIF 

# Begin Target

# Name "AsnC - Win32 Release"
# Name "AsnC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=.\asprintf.c
# End Source File
# Begin Source File

SOURCE=.\bit2prim.c
# End Source File
# Begin Source File

SOURCE=.\bit_ops.c
# End Source File
# Begin Source File

SOURCE=.\bitstr2strb.c
# End Source File
# Begin Source File

SOURCE=.\dec.c
# End Source File
# Begin Source File

SOURCE=.\enc.c
# End Source File
# Begin Source File

SOURCE=.\flag2prim.c
# End Source File
# Begin Source File

SOURCE=.\fre.c
# End Source File
# Begin Source File

SOURCE=.\general.c
# End Source File
# Begin Source File

SOURCE=.\gtime.c
# End Source File
# Begin Source File

SOURCE=.\int2strb.c
# End Source File
# Begin Source File

SOURCE=.\isobject.c
# End Source File
# Begin Source File

SOURCE=.\num2prim.c
# End Source File
# Begin Source File

SOURCE=.\obj2prim.c
# End Source File
# Begin Source File

SOURCE=.\objectbyname.c
# End Source File
# Begin Source File

SOURCE=.\objectbyoid.c
# End Source File
# Begin Source File

SOURCE=.\ode2oid.c
# End Source File
# Begin Source File

SOURCE=.\oid2ode.c
# End Source File
# Begin Source File

SOURCE=.\oid_cmp.c
# End Source File
# Begin Source File

SOURCE=.\oid_cpy.c
# End Source File
# Begin Source File

SOURCE=.\oid_free.c
# End Source File
# Begin Source File

SOURCE=.\pe2ps.c
# End Source File
# Begin Source File

SOURCE=.\pe2qb_f.c
# End Source File
# Begin Source File

SOURCE=.\pe2ssdu.c
# End Source File
# Begin Source File

SOURCE=.\pe_alloc.c
# End Source File
# Begin Source File

SOURCE=.\pe_cpy.c
# End Source File
# Begin Source File

SOURCE=.\pe_error.c
# End Source File
# Begin Source File

SOURCE=.\pe_free.c
# End Source File
# Begin Source File

SOURCE=.\prim2bit.c
# End Source File
# Begin Source File

SOURCE=.\prim2flag.c
# End Source File
# Begin Source File

SOURCE=.\prim2num.c
# End Source File
# Begin Source File

SOURCE=.\prim2oid.c
# End Source File
# Begin Source File

SOURCE=.\prim2qb.c
# End Source File
# Begin Source File

SOURCE=.\prim2real.c
# End Source File
# Begin Source File

SOURCE=.\prim2set.c
# End Source File
# Begin Source File

SOURCE=.\prim2str.c
# End Source File
# Begin Source File

SOURCE=.\prim2time.c
# End Source File
# Begin Source File

SOURCE=.\prnt.c
# End Source File
# Begin Source File

SOURCE=.\ps2pe.c
# End Source File
# Begin Source File

SOURCE=.\ps_alloc.c
# End Source File
# Begin Source File

SOURCE=.\ps_error.c
# End Source File
# Begin Source File

SOURCE=.\ps_flush.c
# End Source File
# Begin Source File

SOURCE=.\ps_free.c
# End Source File
# Begin Source File

SOURCE=.\ps_get_abs.c
# End Source File
# Begin Source File

SOURCE=.\ps_io.c
# End Source File
# Begin Source File

SOURCE=.\ps_prime.c
# End Source File
# Begin Source File

SOURCE=.\qb2pe.c
# End Source File
# Begin Source File

SOURCE=.\qb2prim.c
# End Source File
# Begin Source File

SOURCE=.\qb2str.c
# End Source File
# Begin Source File

SOURCE=.\qb_free.c
# End Source File
# Begin Source File

SOURCE=.\qb_pullup.c
# End Source File
# Begin Source File

SOURCE=.\qbuf2pe.c
# End Source File
# Begin Source File

SOURCE=.\qbuf2ps.c
# End Source File
# Begin Source File

SOURCE=.\rcmd_srch.c
# End Source File
# Begin Source File

SOURCE=.\real2prim.c
# End Source File
# Begin Source File

SOURCE=.\seq_add.c
# End Source File
# Begin Source File

SOURCE=.\seq_addon.c
# End Source File
# Begin Source File

SOURCE=.\set_add.c
# End Source File
# Begin Source File

SOURCE=.\set_addon.c
# End Source File
# Begin Source File

SOURCE=.\set_find.c
# End Source File
# Begin Source File

SOURCE=.\smalloc.c
# End Source File
# Begin Source File

SOURCE=.\sprintoid.c
# End Source File
# Begin Source File

SOURCE=.\ssdu2pe.c
# End Source File
# Begin Source File

SOURCE=.\std2ps.c
# End Source File
# Begin Source File

SOURCE=.\str2elem.c
# End Source File
# Begin Source File

SOURCE=.\str2oid.c
# End Source File
# Begin Source File

SOURCE=.\str2pe.c
# End Source File
# Begin Source File

SOURCE=.\str2prim.c
# End Source File
# Begin Source File

SOURCE=.\str2ps.c
# End Source File
# Begin Source File

SOURCE=.\str2qb.c
# End Source File
# Begin Source File

SOURCE=.\str2vec.c
# End Source File
# Begin Source File

SOURCE=.\strb2bitstr.c
# End Source File
# Begin Source File

SOURCE=.\strb2int.c
# End Source File
# Begin Source File

SOURCE=.\time2prim.c
# End Source File
# Begin Source File

SOURCE=.\time2str.c
# End Source File
# Begin Source File

SOURCE=.\tm2ut.c
# End Source File
# Begin Source File

SOURCE=.\ut2tm.c
# End Source File
# Begin Source File

SOURCE=.\util.c
# End Source File
# Begin Source File

SOURCE=.\vprint.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\cmd_srch.h
# End Source File
# Begin Source File

SOURCE=".\pepsy-driver.h"
# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UNIV_tables.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\univ.asn

!IF  "$(CFG)" == "AsnC - Win32 Release"

# Begin Custom Build
InputPath=.\univ.asn

BuildCmds= \
	..\..\..\tools\bin\asnc -A -a -f univ.asn \
	copy UNIV-types.h ..\..\include\asn-c \
	

".\UNIV_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\UNIV-types.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnC - Win32 Debug"

# Begin Custom Build
InputPath=.\univ.asn

BuildCmds= \
	..\..\..\tools\bin\asnc -A -a -f univ.asn \
	copy UNIV-types.h ..\..\include\asn-c \
	

".\UNIV_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\UNIV-types.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
