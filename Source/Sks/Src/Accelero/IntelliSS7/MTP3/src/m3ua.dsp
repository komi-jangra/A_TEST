# Microsoft Developer Studio Project File - Name="M3UA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=M3UA - Win32 Release ANSI
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "m3ua.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "m3ua.mak" CFG="M3UA - Win32 Release ANSI"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "M3UA - Win32 Debug CCITT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "M3UA - Win32 Release CCITT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "M3UA - Win32 Debug ANSI" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "M3UA - Win32 Release ANSI" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "M3UA - Win32 Debug CCITT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug CCITT"
# PROP BASE Intermediate_Dir "Debug CCITT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugCCITT"
# PROP Intermediate_Dir "DebugCCITT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_IMPLEMENTATION" /D "CCITT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../common/lib/CCITT-M3uaD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy DebugCCITT\CCITT-M3uaD.lib ..\..\common\lib	copy DebugCCITT\CCITT-M3uaD.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release CCITT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Release CCITT"
# PROP BASE Intermediate_Dir "Release CCITT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ReleaseCCITT"
# PROP Intermediate_Dir "ReleaseCCITT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_EXPORTS" /D "M3UA_IMPLEMENTATION" /D "CCITT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../lib/CCITT-M3UA.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ReleaseCCITT\CCITT-M3ua.lib ..\..\common\lib	copy ReleaseCCITT\CCITT-M3ua.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "M3UA - Win32 Debug ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug ANSI"
# PROP BASE Intermediate_Dir "Debug ANSI"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugANSI"
# PROP Intermediate_Dir "DebugANSI"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_EXPORTS" /D "M3UA_IMPLEMENTATION" /D "ANSI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../lib/ANSI-M3UAD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy DebugANSI\ANSI-M3uaD.lib ..\..\common\lib	copy DebugANSI\ANSI-M3uaD.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Release ANSI"
# PROP BASE Intermediate_Dir "Release ANSI"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ReleaseANSI"
# PROP Intermediate_Dir "ReleaseANSI"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "M3UA_EXPORTS" /D "M3UA_IMPLEMENTATION" /D "ANSI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../lib/ANSI-M3UA.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ReleaseANSI\ANSI-M3ua.lib ..\..\common\lib	copy ReleaseANSI\ANSI-M3ua.exp ..\..\common\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "M3UA - Win32 Debug CCITT"
# Name "M3UA - Win32 Release CCITT"
# Name "M3UA - Win32 Debug ANSI"
# Name "M3UA - Win32 Release ANSI"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\m3ua.c
# End Source File
# Begin Source File

SOURCE=.\m3ua_config_mgnt.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\m3ua.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\common\lib\ENGINED.lib

!IF  "$(CFG)" == "M3UA - Win32 Debug CCITT"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Debug ANSI"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release ANSI"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\UALD.lib

!IF  "$(CFG)" == "M3UA - Win32 Debug CCITT"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Debug ANSI"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release ANSI"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\VFrameD.lib

!IF  "$(CFG)" == "M3UA - Win32 Debug CCITT"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Debug ANSI"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release ANSI"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\..\common\lib\VFrame.lib

!IF  "$(CFG)" == "M3UA - Win32 Debug CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release CCITT"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Debug ANSI"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release ANSI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\ENGINE.lib

!IF  "$(CFG)" == "M3UA - Win32 Debug CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release CCITT"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Debug ANSI"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release ANSI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\UAL.lib

!IF  "$(CFG)" == "M3UA - Win32 Debug CCITT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release CCITT"

!ELSEIF  "$(CFG)" == "M3UA - Win32 Debug ANSI"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "M3UA - Win32 Release ANSI"

!ENDIF 

# End Source File
# End Target
# End Project
