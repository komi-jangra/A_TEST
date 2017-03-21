# Microsoft Developer Studio Project File - Name="isup" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=isup - Win32 TTC  Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "isup.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "isup.mak" CFG="isup - Win32 TTC  Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "isup - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "isup - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "isup - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "isup - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "isup - Win32 CISCO Release" (based on "Win32 (x86) Static Library")
!MESSAGE "isup - Win32 CISCO Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "isup - Win32 TTC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "isup - Win32 TTC  Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "isup - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "isup___W"
# PROP BASE Intermediate_Dir "isup___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-ISUPD"
# PROP Intermediate_Dir "CCITT-ISUPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/CCITT-ISUPD.lib"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "isup___0"
# PROP BASE Intermediate_Dir "isup___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-ISUPD"
# PROP Intermediate_Dir "ANSI-ISUPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/ANSI-ISUPD.lib"

!ELSEIF  "$(CFG)" == "isup - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "isup___1"
# PROP BASE Intermediate_Dir "isup___1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-ISUP"
# PROP Intermediate_Dir "CCITT-ISUP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-ISUP.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-ISUP.lib"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "isup___2"
# PROP BASE Intermediate_Dir "isup___2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-ISUP"
# PROP Intermediate_Dir "ANSI-ISUP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-ISUP.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-ISUP.lib"

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "isup___W"
# PROP BASE Intermediate_Dir "isup___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "isup___W"
# PROP Intermediate_Dir "isup___W"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-ISUP.lib"
# ADD LIB32 /nologo /out:"../lib/C-ISUP.lib"

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "isup___0"
# PROP BASE Intermediate_Dir "isup___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "isup___0"
# PROP Intermediate_Dir "isup___0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-ISUPD.lib"
# ADD LIB32 /nologo /out:"../lib/C-ISUPD.lib"

!ELSEIF  "$(CFG)" == "isup - Win32 TTC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "isup___Win32_TTC_Release"
# PROP BASE Intermediate_Dir "isup___Win32_TTC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "isup___Win32_TTC_Release"
# PROP Intermediate_Dir "isup___Win32_TTC_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "NDEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSI-ISUP.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-ISUP.lib"

!ELSEIF  "$(CFG)" == "isup - Win32 TTC  Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "isup___Win32_TTC__Debug"
# PROP BASE Intermediate_Dir "isup___Win32_TTC__Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "isup___Win32_TTC__Debug"
# PROP Intermediate_Dir "isup___Win32_TTC__Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\include" /I "..\..\SCCP\include" /I "..\..\TCAP\include" /I "..\..\MTP3\include" /I "..\..\MTP2\include" /D "_DEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSI-ISUPD.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-ISUPD.lib"

!ENDIF 

# Begin Target

# Name "isup - Win32 CCITT Debug"
# Name "isup - Win32 ANSI Debug"
# Name "isup - Win32 CCITT Release"
# Name "isup - Win32 ANSI Release"
# Name "isup - Win32 CISCO Release"
# Name "isup - Win32 CISCO Debug"
# Name "isup - Win32 TTC Release"
# Name "isup - Win32 TTC  Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c cpp"
# Begin Source File

SOURCE=.\isup.c

!IF  "$(CFG)" == "isup - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 TTC Release"

!ELSEIF  "$(CFG)" == "isup - Win32 TTC  Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\include\cisup.h

!IF  "$(CFG)" == "isup - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Release"

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\ansi\isup.h

!IF  "$(CFG)" == "isup - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 TTC Release"

!ELSEIF  "$(CFG)" == "isup - Win32 TTC  Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\itu\isup.h

!IF  "$(CFG)" == "isup - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 TTC Release"

!ELSEIF  "$(CFG)" == "isup - Win32 TTC  Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\isup_cmn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\isup_macros.h

!IF  "$(CFG)" == "isup - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "isup - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "isup - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 CISCO Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "isup - Win32 TTC Release"

!ELSEIF  "$(CFG)" == "isup - Win32 TTC  Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\isup_sn.h
# End Source File
# End Group
# End Target
# End Project
