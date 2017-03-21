# Microsoft Developer Studio Project File - Name="sua" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sua - Win32 CCITT Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sua.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sua.mak" CFG="sua - Win32 CCITT Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sua - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sua - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sua - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sua - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sua - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sua___Win32_ANSI_Debug"
# PROP BASE Intermediate_Dir "sua___Win32_ANSI_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-SUAD"
# PROP Intermediate_Dir "ANSI-SUAD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ANSI" /D "SUA_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ANSI" /D "SUA_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSI-SUAD.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-SUAD.lib"

!ELSEIF  "$(CFG)" == "sua - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "sua___Win32_ANSI_Release"
# PROP BASE Intermediate_Dir "sua___Win32_ANSI_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-SUA"
# PROP Intermediate_Dir "ANSI-SUA"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ANSI" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ANSI" /D "SUA_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/ANSI-SUA.lib"

!ELSEIF  "$(CFG)" == "sua - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sua___Win32_CCITT_Debug"
# PROP BASE Intermediate_Dir "sua___Win32_CCITT_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-SUAD"
# PROP Intermediate_Dir "CCITT-SUAD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ANSI" /D "SUA_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "CCITT" /D "SUA_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSI-SUAD.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-SUAD.lib"

!ELSEIF  "$(CFG)" == "sua - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "sua___Win32_CCITT_Release"
# PROP BASE Intermediate_Dir "sua___Win32_CCITT_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-SUA"
# PROP Intermediate_Dir "CCITT-SUA"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ANSI" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "CCITT" /D "SUA_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/CCITT-SUA.lib"

!ENDIF 

# Begin Target

# Name "sua - Win32 ANSI Debug"
# Name "sua - Win32 ANSI Release"
# Name "sua - Win32 CCITT Debug"
# Name "sua - Win32 CCITT Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\sua.c
# End Source File
# Begin Source File

SOURCE=.\sua_sccp_conv.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
