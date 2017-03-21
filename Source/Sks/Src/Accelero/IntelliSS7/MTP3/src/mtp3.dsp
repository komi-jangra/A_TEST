# Microsoft Developer Studio Project File - Name="mtp3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mtp3 - Win32 Debug TTC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mtp3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mtp3.mak" CFG="mtp3 - Win32 Debug TTC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mtp3 - Win32 Debug ANSI" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp3 - Win32 Debug CCITT" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp3 - Win32 Release ANSI" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp3 - Win32 Release CCITT" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp3 - Win32 Release PRC" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp3 - Win32 Debug PRC" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp3 - Win32 Debug TTC" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp3 - Win32 Release TTC" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mtp3 - Win32 Debug ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mtp3___W"
# PROP BASE Intermediate_Dir "mtp3___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-MTP3D"
# PROP Intermediate_Dir "ANSI-MTP3D"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "_DEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/ANSIMtp3D.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-MTP3D.lib"

!ELSEIF  "$(CFG)" == "mtp3 - Win32 Debug CCITT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mtp3___0"
# PROP BASE Intermediate_Dir "mtp3___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-MTP3D"
# PROP Intermediate_Dir "CCITT-MTP3D"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/ANSIMtp3D.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-MTP3D.lib"

!ELSEIF  "$(CFG)" == "mtp3 - Win32 Release ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp3___1"
# PROP BASE Intermediate_Dir "mtp3___1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-MTP3"
# PROP Intermediate_Dir "ANSI-MTP3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/ANSI-MTP3.lib"

!ELSEIF  "$(CFG)" == "mtp3 - Win32 Release CCITT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp3___2"
# PROP BASE Intermediate_Dir "mtp3___2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-MTP3"
# PROP Intermediate_Dir "CCITT-MTP3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/CCITT-MTP3.lib"

!ELSEIF  "$(CFG)" == "mtp3 - Win32 Release PRC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp3___Win32_Release_PRC"
# PROP BASE Intermediate_Dir "mtp3___Win32_Release_PRC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRC-MTP3"
# PROP Intermediate_Dir "PRC-MTP3"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-MTP3.lib"
# ADD LIB32 /nologo /out:"../lib/PRC-MTP3.lib"

!ELSEIF  "$(CFG)" == "mtp3 - Win32 Debug PRC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mtp3___Win32_Debug_PRC"
# PROP BASE Intermediate_Dir "mtp3___Win32_Debug_PRC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PRC-MTP3D"
# PROP Intermediate_Dir "PRC-MTP3D"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-MTP3D.lib"
# ADD LIB32 /nologo /out:"../lib/PRC-MTP3D.lib"

!ELSEIF  "$(CFG)" == "mtp3 - Win32 Debug TTC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mtp3___Win32_Debug_TTC"
# PROP BASE Intermediate_Dir "mtp3___Win32_Debug_TTC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "mtp3___Win32_Debug_TTC"
# PROP Intermediate_Dir "mtp3___Win32_Debug_TTC"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "_DEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/PRC-MTP3D.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-MTP3D.lib"

!ELSEIF  "$(CFG)" == "mtp3 - Win32 Release TTC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp3___Win32_Release_TTC"
# PROP BASE Intermediate_Dir "mtp3___Win32_Release_TTC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "mtp3___Win32_Release_TTC"
# PROP Intermediate_Dir "mtp3___Win32_Release_TTC"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../../common/include" /I "../../MTP2/include" /D "NDEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSI-MTP3.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-MTP3.lib"

!ENDIF 

# Begin Target

# Name "mtp3 - Win32 Debug ANSI"
# Name "mtp3 - Win32 Debug CCITT"
# Name "mtp3 - Win32 Release ANSI"
# Name "mtp3 - Win32 Release CCITT"
# Name "mtp3 - Win32 Release PRC"
# Name "mtp3 - Win32 Debug PRC"
# Name "mtp3 - Win32 Debug TTC"
# Name "mtp3 - Win32 Release TTC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp, c"
# Begin Source File

SOURCE=.\mtp3.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\include\mtp3++.h"
# End Source File
# Begin Source File

SOURCE=..\include\ansi\mtp3.h
# End Source File
# Begin Source File

SOURCE=..\include\china\mtp3.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\mtp3.h
# End Source File
# Begin Source File

SOURCE=..\include\mtp3_cmn.h
# End Source File
# Begin Source File

SOURCE=..\include\mtp3_sn.h
# End Source File
# End Group
# End Target
# End Project
