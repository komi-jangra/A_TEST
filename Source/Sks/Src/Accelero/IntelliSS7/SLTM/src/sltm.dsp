# Microsoft Developer Studio Project File - Name="SLTM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SLTM - Win32 TTC Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SLTM.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SLTM.MAK" CFG="SLTM - Win32 TTC Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SLTM - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SLTM - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SLTM - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SLTM - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SLTM - Win32 PRC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SLTM - Win32 PRC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SLTM - Win32 TTC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "SLTM - Win32 TTC  Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SLTM - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SLTM___W"
# PROP BASE Intermediate_Dir "SLTM___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-SLTMD"
# PROP Intermediate_Dir "ANSI-SLTMD"
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
# ADD LIB32 /nologo /out:"..\lib\ANSI-SLTMD.lib"

!ELSEIF  "$(CFG)" == "SLTM - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SLTM___0"
# PROP BASE Intermediate_Dir "SLTM___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-SLTM"
# PROP Intermediate_Dir "ANSI-SLTM"
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
# ADD LIB32 /nologo /out:"..\lib\ANSI-SLTM.lib"

!ELSEIF  "$(CFG)" == "SLTM - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SLTM___1"
# PROP BASE Intermediate_Dir "SLTM___1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-SLTMD"
# PROP Intermediate_Dir "CCITT-SLTMD"
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
# ADD LIB32 /nologo /out:"..\lib\CCITT-SLTMD.lib"

!ELSEIF  "$(CFG)" == "SLTM - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SLTM___2"
# PROP BASE Intermediate_Dir "SLTM___2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-SLTM"
# PROP Intermediate_Dir "CCITT-SLTM"
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
# ADD LIB32 /nologo /out:"..\lib\CCITT-SLTM.lib"

!ELSEIF  "$(CFG)" == "SLTM - Win32 PRC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SLTM___Win32_PRC_Release"
# PROP BASE Intermediate_Dir "SLTM___Win32_PRC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRC-SLTM"
# PROP Intermediate_Dir "PRC-SLTM"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\CCITT-SLTM.lib"
# ADD LIB32 /nologo /out:"..\lib\PRC-SLTM.lib"

!ELSEIF  "$(CFG)" == "SLTM - Win32 PRC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SLTM___Win32_PRC_Debug"
# PROP BASE Intermediate_Dir "SLTM___Win32_PRC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PRC-SLTMD"
# PROP Intermediate_Dir "PRC-SLTMD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\CCITT-SLTMD.lib"
# ADD LIB32 /nologo /out:"..\lib\PRC-SLTMD.lib"

!ELSEIF  "$(CFG)" == "SLTM - Win32 TTC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SLTM___Win32_TTC_Debug"
# PROP BASE Intermediate_Dir "SLTM___Win32_TTC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SLTM___Win32_TTC_Debug"
# PROP Intermediate_Dir "SLTM___Win32_TTC_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\PRC-SLTMD.lib"
# ADD LIB32 /nologo /out:"..\lib\TTC-SLTMD.lib"

!ELSEIF  "$(CFG)" == "SLTM - Win32 TTC  Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SLTM___Win32_TTC__Release"
# PROP BASE Intermediate_Dir "SLTM___Win32_TTC__Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SLTM___Win32_TTC__Release"
# PROP Intermediate_Dir "SLTM___Win32_TTC__Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\MTP3\include" /I "..\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\PRC-SLTM.lib"
# ADD LIB32 /nologo /out:"..\lib\TTC-SLTM.lib"

!ENDIF 

# Begin Target

# Name "SLTM - Win32 ANSI Debug"
# Name "SLTM - Win32 ANSI Release"
# Name "SLTM - Win32 CCITT Debug"
# Name "SLTM - Win32 CCITT Release"
# Name "SLTM - Win32 PRC Release"
# Name "SLTM - Win32 PRC Debug"
# Name "SLTM - Win32 TTC Debug"
# Name "SLTM - Win32 TTC  Release"
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\include\ansi\sltm.h
# End Source File
# Begin Source File

SOURCE=..\include\china\sltm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\sltm.h
# End Source File
# Begin Source File

SOURCE=..\include\sltm_cmn.h
# End Source File
# Begin Source File

SOURCE=..\include\sltm_sn.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "c cpp"
# Begin Source File

SOURCE=.\sltm.c
# End Source File
# End Group
# End Target
# End Project
