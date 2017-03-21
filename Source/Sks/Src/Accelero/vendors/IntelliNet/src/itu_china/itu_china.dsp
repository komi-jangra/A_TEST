# Microsoft Developer Studio Project File - Name="itu_china" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=itu_china - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "itu_china.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "itu_china.mak" CFG="itu_china - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "itu_china - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "itu_china - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "itu_china - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ITU_CHINA_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /I "../../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "VSS7_IMPLEMENTATION" /D "DERIVED_CLASS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\..\lib\ITU_CHINA.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\ITU_CHINA.lib ..\..\lib	copy Release\ITU_CHINA.exp ..\..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "itu_china - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ITU_CHINA_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /I "../../include/itu" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /D "DERIVED_CLASS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCLUDE_CODEC" /D "VSS7_IMPLEMENTATION" /D "ITSSS7_IMPLEMENTATION" /D "PEPSY_CODEC" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\..\lib\ITU_CHINAD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\ITU_CHINAD.exp ..\..\lib	copy Debug\ITU_CHINA.exp ..\..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "itu_china - Win32 Release"
# Name "itu_china - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\itu-isup_china.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\ENGINE.lib

!IF  "$(CFG)" == "itu_china - Win32 Release"

!ELSEIF  "$(CFG)" == "itu_china - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\ENGINED.lib

!IF  "$(CFG)" == "itu_china - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "itu_china - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\VFrameD.lib

!IF  "$(CFG)" == "itu_china - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "itu_china - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\VFrame.lib

!IF  "$(CFG)" == "itu_china - Win32 Release"

!ELSEIF  "$(CFG)" == "itu_china - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\CCITTVendorD.lib

!IF  "$(CFG)" == "itu_china - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "itu_china - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\CCITTVendor.lib

!IF  "$(CFG)" == "itu_china - Win32 Release"

!ELSEIF  "$(CFG)" == "itu_china - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\ITU_GENERIC_93D.lib
# End Source File
# End Group
# End Target
# End Project
