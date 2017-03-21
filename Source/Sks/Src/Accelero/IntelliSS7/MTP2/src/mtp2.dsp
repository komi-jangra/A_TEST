# Microsoft Developer Studio Project File - Name="mtp2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mtp2 - Win32 ANSI Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mtp2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mtp2.mak" CFG="mtp2 - Win32 ANSI Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mtp2 - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp2 - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp2 - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp2 - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp2 - Win32 PRC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp2 - Win32 PRC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp2 - Win32 TTC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mtp2 - Win32 TTC Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mtp2 - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI Debug"
# PROP BASE Intermediate_Dir "ANSI Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-MTP2D"
# PROP Intermediate_Dir "ANSI-MTP2D"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /O2 /I "../../common/include" /I "../include" /D "ANSI" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\ANSI-MTP2D.lib"

!ELSEIF  "$(CFG)" == "mtp2 - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI Release"
# PROP BASE Intermediate_Dir "ANSI Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-MTP2"
# PROP Intermediate_Dir "ANSI-MTP2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\ANSI-MTP2.lib"

!ELSEIF  "$(CFG)" == "mtp2 - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CCITT Debug"
# PROP BASE Intermediate_Dir "CCITT Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-MTP2D"
# PROP Intermediate_Dir "CCITT-MTP2D"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /O2 /I "../../common/include" /I "../include" /D "CCITT" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CCITT-MTP2D.lib"

!ELSEIF  "$(CFG)" == "mtp2 - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CCITT Release"
# PROP BASE Intermediate_Dir "CCITT Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-MTP2"
# PROP Intermediate_Dir "CCITT-MTP2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CCITT-MTP2.lib"

!ELSEIF  "$(CFG)" == "mtp2 - Win32 PRC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp2___Win32_PRC_Release"
# PROP BASE Intermediate_Dir "mtp2___Win32_PRC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRC-MTP2"
# PROP Intermediate_Dir "PRC-MTP2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\CCITT-MTP2.lib"
# ADD LIB32 /nologo /out:"..\lib\PRC-MTP2.lib"

!ELSEIF  "$(CFG)" == "mtp2 - Win32 PRC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp2___Win32_PRC_Debug"
# PROP BASE Intermediate_Dir "mtp2___Win32_PRC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRC-MTP2D"
# PROP Intermediate_Dir "PRC-MTP2D"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /O2 /I "../../common/include" /I "../include" /D "CCITT" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /O2 /I "../../common/include" /I "../include" /D "DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\CCITT-MTP2D.lib"
# ADD LIB32 /nologo /out:"..\lib\PRC-MTP2D.lib"

!ELSEIF  "$(CFG)" == "mtp2 - Win32 TTC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp2___Win32_TTC_Debug"
# PROP BASE Intermediate_Dir "mtp2___Win32_TTC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "mtp2___Win32_TTC_Debug"
# PROP Intermediate_Dir "mtp2___Win32_TTC_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /O2 /I "../../common/include" /I "../include" /D "ANSI" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /O2 /I "../../common/include" /I "../include" /D "TTC" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\ANSI-MTP2D.lib"
# ADD LIB32 /nologo /out:"..\lib\TTC-MTP2D.lib"

!ELSEIF  "$(CFG)" == "mtp2 - Win32 TTC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mtp2___Win32_TTC_Release"
# PROP BASE Intermediate_Dir "mtp2___Win32_TTC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "mtp2___Win32_TTC_Release"
# PROP Intermediate_Dir "mtp2___Win32_TTC_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../include" /D "NDEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\ANSI-MTP2.lib"
# ADD LIB32 /nologo /out:"..\lib\TTC-MTP2.lib"

!ENDIF 

# Begin Target

# Name "mtp2 - Win32 ANSI Debug"
# Name "mtp2 - Win32 ANSI Release"
# Name "mtp2 - Win32 CCITT Debug"
# Name "mtp2 - Win32 CCITT Release"
# Name "mtp2 - Win32 PRC Release"
# Name "mtp2 - Win32 PRC Debug"
# Name "mtp2 - Win32 TTC Debug"
# Name "mtp2 - Win32 TTC Release"
# Begin Group "Source Files"

# PROP Default_Filter "c cpp"
# Begin Source File

SOURCE=.\mtp2.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\include\ansi\mtp2.h
# End Source File
# Begin Source File

SOURCE=..\include\china\mtp2.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\mtp2.h
# End Source File
# Begin Source File

SOURCE=..\include\mtp2_cmn.h
# End Source File
# Begin Source File

SOURCE=..\include\mtp2_sn.h
# End Source File
# End Group
# End Target
# End Project
