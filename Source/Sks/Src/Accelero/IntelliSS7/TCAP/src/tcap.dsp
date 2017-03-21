# Microsoft Developer Studio Project File - Name="TCAP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=TCAP - Win32 TTC  Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TCAP.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TCAP.MAK" CFG="TCAP - Win32 TTC  Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TCAP - Win32 ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 ANSI over CCITT Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 CCITT over ANSI Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 ANSI over CCITT Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 CCITT over ANSI Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 PRC Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 PRC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 TTC Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TCAP - Win32 TTC  Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TCAP___W"
# PROP BASE Intermediate_Dir "TCAP___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-TCAPD"
# PROP Intermediate_Dir "ANSI-TCAPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "..\include\ansi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\ansi" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\tcap.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-TCAPD.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TCAP___0"
# PROP BASE Intermediate_Dir "TCAP___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-TCAPD"
# PROP Intermediate_Dir "CCITT-TCAPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "..\include\ansi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\tcap.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-TCAPD.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TCAP___1"
# PROP BASE Intermediate_Dir "TCAP___1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-TCAP"
# PROP Intermediate_Dir "ANSI-TCAP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\ansi" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "ANSI" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/ANSI-TCAP.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TCAP___2"
# PROP BASE Intermediate_Dir "TCAP___2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-TCAP"
# PROP Intermediate_Dir "CCITT-TCAP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/CCITT-TCAP.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TCAP___W"
# PROP BASE Intermediate_Dir "TCAP___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI-CCITTD"
# PROP Intermediate_Dir "ANSI-CCITTD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "..\include\ansi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ANSI" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\ansi" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "ANSI" /D "USE_ITU_SCCP" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSI-TCAPD.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-CCITT-TCAPD.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TCAP___0"
# PROP BASE Intermediate_Dir "TCAP___0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITT-ANSID"
# PROP Intermediate_Dir "CCITT-ANSID"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "..\include\itu" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "CCITT" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "CCITT" /D "USE_ANSI_SCCP" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-TCAPD.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-ANSI-TCAPD.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TCAP___1"
# PROP BASE Intermediate_Dir "TCAP___1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI-CCITT"
# PROP Intermediate_Dir "ANSI-CCITT"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "..\include\ansi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "ANSI" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\ansi" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "ANSI" /D "USE_ITU_SCCP" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/ANSI-TCAP.lib"
# ADD LIB32 /nologo /out:"../lib/ANSI-CCITT-TCAP.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TCAP___2"
# PROP BASE Intermediate_Dir "TCAP___2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITT-ANSI"
# PROP Intermediate_Dir "CCITT-ANSI"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "..\include\itu" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "CCITT" /D "USE_ANSI_SCCP" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-TCAP.lib"
# ADD LIB32 /nologo /out:"../lib/CCITT-ANSI-TCAP.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TCAP___Win32_PRC_Debug"
# PROP BASE Intermediate_Dir "TCAP___Win32_PRC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PRC-TCAPD"
# PROP Intermediate_Dir "PRC-TCAPD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-TCAPD.lib"
# ADD LIB32 /nologo /out:"../lib/PRC-TCAPD.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TCAP___Win32_PRC_Release"
# PROP BASE Intermediate_Dir "TCAP___Win32_PRC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PRC-TCAP"
# PROP Intermediate_Dir "PRC-TCAP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "CCITT" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/CCITT-TCAP.lib"
# ADD LIB32 /nologo /out:"../lib/PRC-TCAP.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TCAP___Win32_TTC_Release"
# PROP BASE Intermediate_Dir "TCAP___Win32_TTC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "TCAP___Win32_TTC_Release"
# PROP Intermediate_Dir "TCAP___Win32_TTC_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "NDEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/PRC-TCAP.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-TCAP.lib"

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TCAP___Win32_TTC__Debug"
# PROP BASE Intermediate_Dir "TCAP___Win32_TTC__Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TCAP___Win32_TTC__Debug"
# PROP Intermediate_Dir "TCAP___Win32_TTC__Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "PRC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\SCCP\include" /I "..\..\MTP3\include" /I "..\include" /I "../../MTP2/include" /D "_DEBUG" /D "TTC" /D "WIN32" /D "_WINDOWS" /D "INCLUDE_CODEC" /D "SS7_IMPLEMENTATION" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/PRC-TCAPD.lib"
# ADD LIB32 /nologo /out:"../lib/TTC-TCAPD.lib"

!ENDIF 

# Begin Target

# Name "TCAP - Win32 ANSI Debug"
# Name "TCAP - Win32 CCITT Debug"
# Name "TCAP - Win32 ANSI Release"
# Name "TCAP - Win32 CCITT Release"
# Name "TCAP - Win32 ANSI over CCITT Debug"
# Name "TCAP - Win32 CCITT over ANSI Debug"
# Name "TCAP - Win32 ANSI over CCITT Release"
# Name "TCAP - Win32 CCITT over ANSI Release"
# Name "TCAP - Win32 PRC Debug"
# Name "TCAP - Win32 PRC Release"
# Name "TCAP - Win32 TTC Release"
# Name "TCAP - Win32 TTC  Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c,cpp"
# Begin Source File

SOURCE=".\ansi-tcap_codec.c"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ansi-tcap_cvt.c"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ANSI-TCAP_tables.c"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\cmn-tcap_codec.c"
# End Source File
# Begin Source File

SOURCE=".\ITU-TCAP-APDU_tables.c"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap_codec.c"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\itu-tcap_cvt.c"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ITU-TCAP_tables.c"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\tcap.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE="..\include\tcap++.h"
# End Source File
# Begin Source File

SOURCE=..\include\ansi\tcap.h
# End Source File
# Begin Source File

SOURCE=..\include\china\tcap.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\tcap.h
# End Source File
# Begin Source File

SOURCE=..\include\tcap_cmn.h
# End Source File
# Begin Source File

SOURCE=..\include\tcap_sn.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ansiTCAP.asn

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

# Begin Custom Build
InputPath=.\ansiTCAP.asn

"ANSI-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ansiTCAP.asn 
	copy ANSI-TCAP-types.h ..\include\ansi 
	del ANSI-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\ituTCAP-APDU.asn"

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# Begin Custom Build
InputPath=".\ituTCAP-APDU.asn"

"ITU-TCAP-APDU_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP-APDU.asn 
	copy ITU-TCAP-APDU-types.h ..\include\itu 
	del ITU-TCAP-APDU-types.h 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ituTCAP.asn

!IF  "$(CFG)" == "TCAP - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Debug"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT Release"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Debug"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Debug"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 ANSI over CCITT Release"

!ELSEIF  "$(CFG)" == "TCAP - Win32 CCITT over ANSI Release"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Debug"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 PRC Release"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC Release"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TCAP - Win32 TTC  Debug"

# Begin Custom Build
InputPath=.\ituTCAP.asn

"ITU-TCAP_tables.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asnc -A -a -f -h ituTCAP.asn 
	copy ITU-TCAP-types.h ..\include\itu 
	del ITU-TCAP-types.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
