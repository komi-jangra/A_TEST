# Microsoft Developer Studio Project File - Name="IMAL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=IMAL - Win32 CCITT Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IMAL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IMAL.mak" CFG="IMAL - Win32 CCITT Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IMAL - Win32 ANSI Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IMAL - Win32 CCITT Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IMAL - Win32 ANSI Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IMAL - Win32 CCITT Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IMAL - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ANSI Debug"
# PROP BASE Intermediate_Dir "ANSI Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSIDebug"
# PROP Intermediate_Dir "ANSIDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMAL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../lib/ANSI-IMALD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSIDebug\ANSI-IMALD.exp ..\..\lib	copy ANSIDebug\ANSI-IMALD.lib ..\..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CCITT Debug"
# PROP BASE Intermediate_Dir "CCITT Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITTDebug"
# PROP Intermediate_Dir "CCITTDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMAL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CCITT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../lib/CCITT-IMALD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy CCITTDebug\CCITT-IMALD.exp ..\..\lib	copy CCITTDebug\CCITT-IMALD.lib ..\..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "IMAL - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI Release"
# PROP BASE Intermediate_Dir "ANSI Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSIRelease"
# PROP Intermediate_Dir "ANSIRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMAL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../lib/ANSI-IMAL.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSIRelease\ANSI-IMAL.exp ..\..\lib	copy ANSIRelease\ANSI-IMAL.lib ..\..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CCITT Release"
# PROP BASE Intermediate_Dir "CCITT Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITTRelease"
# PROP Intermediate_Dir "CCITTRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IMAL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CCITT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../lib/CCITT-IMAL.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy CCITTRelease\CCITT-IMAL.exp ..\..\lib	copy CCITTRelease\CCITT-IMAL.lib ..\..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "IMAL - Win32 ANSI Debug"
# Name "IMAL - Win32 CCITT Debug"
# Name "IMAL - Win32 ANSI Release"
# Name "IMAL - Win32 CCITT Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\its_imal.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Libraries"

# PROP Default_Filter ".lib,.dll"
# Begin Source File

SOURCE=..\..\lib\VFrameD.lib

!IF  "$(CFG)" == "IMAL - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "IMAL - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\VFrame.lib

!IF  "$(CFG)" == "IMAL - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "IMAL - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\ENGINED.lib

!IF  "$(CFG)" == "IMAL - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "IMAL - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\ENGINE.lib

!IF  "$(CFG)" == "IMAL - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "IMAL - Win32 ANSI Release"

!ELSEIF  "$(CFG)" == "IMAL - Win32 CCITT Release"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
