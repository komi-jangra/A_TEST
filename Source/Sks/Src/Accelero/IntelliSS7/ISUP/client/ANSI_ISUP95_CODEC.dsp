# Microsoft Developer Studio Project File - Name="ANSI_ISUP95_CODEC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ANSI_ISUP95_CODEC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ANSI_ISUP95_CODEC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ANSI_ISUP95_CODEC.mak" CFG="ANSI_ISUP95_CODEC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ANSI_ISUP95_CODEC - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ANSI_ISUP95_CODEC - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI_ISUP95_CODEC___Win32_Release"
# PROP BASE Intermediate_Dir "ANSI_ISUP95_CODEC___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI95Release"
# PROP Intermediate_Dir "ANSI95Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_ISUP95_CODEC_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_ISUP95_CODEC_EXPORTS" /D "SS7_IMPLEMENTATION" /D "ANSI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../lib/ANSI-ISUP95_CODEC.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSI95Release\ANSI-ISUP95_CODEC.lib ..\lib	copy ANSI95Release\ANSI-ISUP95_CODEC.exp ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ANSI_ISUP95_CODEC___Win32_Debug"
# PROP BASE Intermediate_Dir "ANSI_ISUP95_CODEC___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI95Debug"
# PROP Intermediate_Dir "ANSI95Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_ISUP95_CODEC_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_ISUP95_CODEC_EXPORTS" /D "SS7_IMPLEMENTATION" /D "ANSI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../lib/ANSI-ISUP95_CODECD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSI95Debug\ANSI-ISUP95_CODECD.lib ..\lib	copy ANSI95Debug\ANSI-ISUP95_CODECD.exp ..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ANSI_ISUP95_CODEC - Win32 Release"
# Name "ANSI_ISUP95_CODEC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\isup.c
# End Source File
# Begin Source File

SOURCE=..\src\isup_cmn.c
# End Source File
# Begin Source File

SOURCE=..\src\isup_variants.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\common\lib\ENGINED.lib

!IF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\VFrameD.lib

!IF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\VFrame.lib

!IF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Release"

!ELSEIF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\ENGINE.lib

!IF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Release"

!ELSEIF  "$(CFG)" == "ANSI_ISUP95_CODEC - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
