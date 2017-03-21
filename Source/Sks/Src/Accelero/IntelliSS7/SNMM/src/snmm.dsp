# Microsoft Developer Studio Project File - Name="SNMM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SNMM - Win32 TTC  Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SNMM.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SNMM.MAK" CFG="SNMM - Win32 TTC  Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SNMM - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SNMM - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SNMM - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SNMM - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SNMM - Win32 PRC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SNMM - Win32 PRC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SNMM - Win32 TTC  Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SNMM - Win32 TTC Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SNMM - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SNMM___W"
# PROP BASE Intermediate_Dir "SNMM___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-SNMMD"
# PROP Intermediate_Dir "ANSI-SNMMD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\ANSI-SNMMD.lib"

!ELSEIF  "$(CFG)" == "SNMM - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SNMM___0"
# PROP BASE Intermediate_Dir "SNMM___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-SNMM"
# PROP Intermediate_Dir "ANSI-SNMM"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\ANSI-SNMM.lib"

!ELSEIF  "$(CFG)" == "SNMM - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SNMM___1"
# PROP BASE Intermediate_Dir "SNMM___1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-SNMMD"
# PROP Intermediate_Dir "CCITT-SNMMD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CCITT-SNMMD.lib"

!ELSEIF  "$(CFG)" == "SNMM - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SNMM___2"
# PROP BASE Intermediate_Dir "SNMM___2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-SNMM"
# PROP Intermediate_Dir "CCITT-SNMM"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CCITT-SNMM.lib"

!ELSEIF  "$(CFG)" == "SNMM - Win32 PRC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SNMM___Win32_PRC_Release"
# PROP BASE Intermediate_Dir "SNMM___Win32_PRC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRC-SNMM"
# PROP Intermediate_Dir "PRC-SNMM"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\CCITT-SNMM.lib"
# ADD LIB32 /nologo /out:"..\lib\PRC-SNMM.lib"

!ELSEIF  "$(CFG)" == "SNMM - Win32 PRC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SNMM___Win32_PRC_Debug"
# PROP BASE Intermediate_Dir "SNMM___Win32_PRC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PRC-SNMMD"
# PROP Intermediate_Dir "PRC-SNMMD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\CCITT-SNMMD.lib"
# ADD LIB32 /nologo /out:"..\lib\PRC-SNMMD.lib"

!ELSEIF  "$(CFG)" == "SNMM - Win32 TTC  Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SNMM___Win32_TTC__Debug"
# PROP BASE Intermediate_Dir "SNMM___Win32_TTC__Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SNMM___Win32_TTC__Debug"
# PROP Intermediate_Dir "SNMM___Win32_TTC__Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\PRC-SNMMD.lib"
# ADD LIB32 /nologo /out:"..\lib\TTC-SNMMD.lib"

!ELSEIF  "$(CFG)" == "SNMM - Win32 TTC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SNMM___Win32_TTC_Release"
# PROP BASE Intermediate_Dir "SNMM___Win32_TTC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SNMM___Win32_TTC_Release"
# PROP Intermediate_Dir "SNMM___Win32_TTC_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\PRC-SNMM.lib"
# ADD LIB32 /nologo /out:"..\lib\TTC-SNMM.lib"

!ENDIF 

# Begin Target

# Name "SNMM - Win32 ANSI Debug"
# Name "SNMM - Win32 ANSI Release"
# Name "SNMM - Win32 CCITT Debug"
# Name "SNMM - Win32 CCITT Release"
# Name "SNMM - Win32 PRC Release"
# Name "SNMM - Win32 PRC Debug"
# Name "SNMM - Win32 TTC  Debug"
# Name "SNMM - Win32 TTC Release"
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\include\ansi\snmm.h
# End Source File
# Begin Source File

SOURCE=..\include\china\snmm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\snmm.h
# End Source File
# Begin Source File

SOURCE=..\include\snmm_cmn.h
# End Source File
# Begin Source File

SOURCE=..\include\snmm_sn.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "c cpp"
# Begin Source File

SOURCE=.\snmm.c
# End Source File
# End Group
# End Target
# End Project
