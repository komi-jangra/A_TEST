# Microsoft Developer Studio Project File - Name="dsm_gcs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=dsm_gcs - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dsm_gcs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dsm_gcs.mak" CFG="dsm_gcs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dsm_gcs - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsm_gcs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dsm_gcs - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "dsm_gcs___Win32_Release"
# PROP BASE Intermediate_Dir "dsm_gcs___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "DSM_GCS_Win32_Release"
# PROP Intermediate_Dir "DSM_GCS_Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSM_GCS_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\MTP2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSM_GCS_EXPORTS" /D "GCS_IMPLEMENTATION" /D "DSM_IMPLEMENTATION" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386 /out:"../../lib/DSM-GCS.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy DSM_GCS_Win32_Release\DSM-GCS.lib ..\..\lib	copy DSM_GCS_Win32_Release\DSM-GCS.exp ..\..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "dsm_gcs - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "dsm_gcs___Win32_Debug"
# PROP BASE Intermediate_Dir "dsm_gcs___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DSM_GCS_Win32_Debug"
# PROP Intermediate_Dir "DSM_GCS_Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSM_GCS_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "../../include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\MTP2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSM_GCS_EXPORTS" /D "DEBUG" /D "GCS_IMPLEMENTATION" /D "DSM_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /out:"../../lib/DSM-GCSD.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy DSM_GCS_Win32_Debug\DSM-GCSD.lib ..\..\lib	copy DSM_GCS_Win32_Debug\DSM-GCSD.exp ..\..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "dsm_gcs - Win32 Release"
# Name "dsm_gcs - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dsm_gcs_impl.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dsm_gcs_impl.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\lib\ENGINED.lib

!IF  "$(CFG)" == "dsm_gcs - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "dsm_gcs - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\GCS-CLIENT-FOR-ENGINED.lib"

!IF  "$(CFG)" == "dsm_gcs - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "dsm_gcs - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\ENGINE.lib

!IF  "$(CFG)" == "dsm_gcs - Win32 Release"

!ELSEIF  "$(CFG)" == "dsm_gcs - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\lib\GCS-CLIENT-FOR-ENGINE.lib"

!IF  "$(CFG)" == "dsm_gcs - Win32 Release"

!ELSEIF  "$(CFG)" == "dsm_gcs - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
