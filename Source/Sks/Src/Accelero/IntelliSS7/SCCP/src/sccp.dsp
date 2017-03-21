# Microsoft Developer Studio Project File - Name="sccp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sccp - Win32 TTC Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sccp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sccp.mak" CFG="sccp - Win32 TTC Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sccp - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sccp - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sccp - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sccp - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sccp - Win32 PRC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sccp - Win32 PRC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sccp - Win32 TTC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sccp - Win32 TTC Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sccp - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sccp___W"
# PROP BASE Intermediate_Dir "sccp___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-SCCPD"
# PROP Intermediate_Dir "ANSI-SCCPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/sccp.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-SCCPD.lib"

!ELSEIF  "$(CFG)" == "sccp - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sccp___0"
# PROP BASE Intermediate_Dir "sccp___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-SCCPD"
# PROP Intermediate_Dir "CCITT-SCCPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/sccp.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-SCCPD.lib"

!ELSEIF  "$(CFG)" == "sccp - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "sccp___1"
# PROP BASE Intermediate_Dir "sccp___1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-SCCP"
# PROP Intermediate_Dir "ANSI-SCCP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/ANSI-SCCP.lib"

!ELSEIF  "$(CFG)" == "sccp - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "sccp___2"
# PROP BASE Intermediate_Dir "sccp___2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-SCCP"
# PROP Intermediate_Dir "CCITT-SCCP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/CCITT-SCCP.lib"

!ELSEIF  "$(CFG)" == "sccp - Win32 PRC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "sccp___Win32_PRC_Release"
# PROP BASE Intermediate_Dir "sccp___Win32_PRC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRC-SCCP"
# PROP Intermediate_Dir "PRC-SCCP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-SCCP.lib"
# ADD LIB32 /nologo /out:"../lib/PRC-SCCP.lib"

!ELSEIF  "$(CFG)" == "sccp - Win32 PRC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sccp___Win32_PRC_Debug"
# PROP BASE Intermediate_Dir "sccp___Win32_PRC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PRC-SCCPD"
# PROP Intermediate_Dir "PRC-SCCPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-SCCPD.lib"
# ADD LIB32 /nologo /out:"../lib/PRC-SCCPD.lib"

!ELSEIF  "$(CFG)" == "sccp - Win32 TTC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sccp___Win32_TTC_Debug"
# PROP BASE Intermediate_Dir "sccp___Win32_TTC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "sccp___Win32_TTC_Debug"
# PROP Intermediate_Dir "sccp___Win32_TTC_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/PRC-SCCPD.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-SCCPD.lib"

!ELSEIF  "$(CFG)" == "sccp - Win32 TTC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sccp___Win32_TTC_Release"
# PROP BASE Intermediate_Dir "sccp___Win32_TTC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "sccp___Win32_TTC_Release"
# PROP Intermediate_Dir "sccp___Win32_TTC_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\mtp3\include" /I "../../MTP2/include" /D "_DEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/PRC-SCCPD.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-SCCP.lib"

!ENDIF 

# Begin Target

# Name "sccp - Win32 ANSI Debug"
# Name "sccp - Win32 CCITT Debug"
# Name "sccp - Win32 ANSI Release"
# Name "sccp - Win32 CCITT Release"
# Name "sccp - Win32 PRC Release"
# Name "sccp - Win32 PRC Debug"
# Name "sccp - Win32 TTC Debug"
# Name "sccp - Win32 TTC Release"
# Begin Group "Source Files"

# PROP Default_Filter "c,cpp"
# Begin Source File

SOURCE=.\sccp.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE="..\include\sccp++.h"
# End Source File
# Begin Source File

SOURCE=..\include\ansi\sccp.h
# End Source File
# Begin Source File

SOURCE=..\include\china\sccp.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\sccp.h
# End Source File
# Begin Source File

SOURCE=..\include\sccp_cmn.h
# End Source File
# Begin Source File

SOURCE=..\include\sccp_sn.h
# End Source File
# End Group
# End Target
# End Project
