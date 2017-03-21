# Microsoft Developer Studio Project File - Name="engine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=engine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak" CFG="engine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "engine - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "engine - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "engine___Win32_Release"
# PROP BASE Intermediate_Dir "engine___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ENGINE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../../common/include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\ISUP\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ITS_IMPLEMENTATION" /D "CCITT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386 /include:"_ITS_GetErrorText" /include:"_TPOOL_InitPool" /include:"_TRACE_Current" /include:"_EVENTLOG_Log" /include:"_ADLER_Chksum32" /include:"_WORKITEMPOOL_InitPool" /include:"_WORKITEM_Create" /include:"_LOCKABLE_Lock" /include:"_itsDBC_ServerClass" /include:"_DBC_ServerCreate" /include:"_PEG_AddToPeg" /include:"_BEHAVIORS_GetBehavior" /include:"_ALARM_Callbacks" /include:"_itsFTM_CoreClass" /include:"_PPrint" /include:"_SPLAY_InitSplay" /include:"_RB_InitTree" /include:"_CTF_TraceEvent" /out:"../../common/lib/ENGINE.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\ENGINE.lib ..\..\common\lib	copy Release\ENGINE.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "engine___Win32_Debug"
# PROP BASE Intermediate_Dir "engine___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ENGINE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../include" /I "../../common/include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\ISUP\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ITS_IMPLEMENTATION" /D "DEBUG" /D "CCITT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /include:"_ITS_GetErrorText" /include:"_TPOOL_InitPool" /include:"_TRACE_Current" /include:"_EVENTLOG_Log" /include:"_ADLER_Chksum32" /include:"_WORKITEMPOOL_InitPool" /include:"_WORKITEM_Create" /include:"_LOCKABLE_Lock" /include:"_MEMPOOL_Pool" /include:"_itsDBC_ServerClass" /include:"_DBC_ServerCreate" /include:"_PEG_AddToPeg" /include:"_BEHAVIORS_GetBehavior" /include:"_ALARM_Callbacks" /include:"_itsFTM_CoreClass" /include:"_PPrint" /include:"_SPLAY_InitSplay" /include:"_RB_InitTree" /include:"_CTF_TraceEvent" /out:"../../common/lib/ENGINED.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\ENGINED.lib ..\..\common\lib	copy Debug\ENGINED.exp ..\..\common\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "engine - Win32 Release"
# Name "engine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\engine.c
# End Source File
# Begin Source File

SOURCE=.\engine_commit.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="$(ITS_ROOT)\common\include\engine++.h"
# End Source File
# Begin Source File

SOURCE="$(ITS_ROOT)\common\include\engine.h"
# End Source File
# Begin Source File

SOURCE=..\include\engine_intern.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE="$(ITS_ROOT)\common\lib\SupportD.lib"

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="$(ITS_ROOT)\common\lib\EXPAT.lib"

!IF  "$(CFG)" == "engine - Win32 Release"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="$(ITS_ROOT)\common\lib\EXPATD.lib"

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="$(ITS_ROOT)\common\lib\Support.lib"

!IF  "$(CFG)" == "engine - Win32 Release"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="$(ITS_ROOT)\common\lib\CORE.lib"

!IF  "$(CFG)" == "engine - Win32 Release"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\DBCServerCD.lib

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\DBCServerC.lib

!IF  "$(CFG)" == "engine - Win32 Release"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\CORED.lib

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\CTFD.lib

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\CTF.lib

!IF  "$(CFG)" == "engine - Win32 Release"

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\engine.dtd
# End Source File
# Begin Source File

SOURCE=.\notes.txt
# End Source File
# End Target
# End Project
