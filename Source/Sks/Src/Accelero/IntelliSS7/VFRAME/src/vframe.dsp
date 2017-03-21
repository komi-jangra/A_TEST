# Microsoft Developer Studio Project File - Name="vframe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vframe - Win32 COA Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vframe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vframe.mak" CFG="vframe - Win32 COA Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vframe - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vframe - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vframe - Win32 AOC Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vframe - Win32 AOC Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vframe - Win32 COA Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vframe - Win32 COA Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vframe - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VFRAME_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "ANSI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /include:"_TCAP_CvtCPTToComponentPDU_CCITT" /include:"_TCAP_CvtComponentPDUToCPT_CCITT" /include:"__ZITU_TCAP_mod" /include:"_TCAP_GetTID_CCITT" /include:"_TCAP_FindParts_CCITT" /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /include:"_ISUP_VariantToString" /include:"_VAR_GetMsgDescription" /include:"_TCAP_CvtCPTToComponentPDU_ANSI" /include:"_TCAP_CvtComponentPDUToCPT_ANSI" /include:"__ZANSI_TCAP_mod" /include:"_TCAP_GetTID_ANSI" /include:"_TCAP_FindParts_ANSI" /out:"..\..\common\lib\VFrame.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\VFrame.lib ..\..\common\lib	copy Release\VFrame.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VFRAME_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "ANSI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /include:"_TCAP_CvtCPTToComponentPDU_CCITT" /include:"_TCAP_CvtComponentPDUToCPT_CCITT" /include:"__ZITU_TCAP_mod" /include:"_TCAP_GetTID_CCITT" /include:"_TCAP_FindParts_CCITT" /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /include:"_ISUP_VariantToString" /include:"_VAR_GetMsgDescription" /include:"_TCAP_CvtCPTToComponentPDU_ANSI" /include:"_TCAP_CvtComponentPDUToCPT_ANSI" /include:"__ZANSI_TCAP_mod" /include:"_TCAP_GetTID_ANSI" /include:"_TCAP_FindParts_ANSI" /out:"..\..\common\lib\VFrameD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\VFrameD.lib ..\..\common\lib	copy Debug\VFrameD.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vframe___Win32_AOC_Debug"
# PROP BASE Intermediate_Dir "vframe___Win32_AOC_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AOCDebug"
# PROP Intermediate_Dir "AOCDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "SPLIT_STACK" /D "USE_ITU_SCCP" /D "ANSI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /out:"..\lib\VFrameD.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /include:"_ISUP_VariantToString" /include:"_VAR_GetMsgDescription" /include:"_TCAP_CvtCPTToComponentPDU_ANSI" /include:"_TCAP_CvtComponentPDUToCPT_ANSI" /include:"__ZANSI_TCAP_mod" /include:"_TCAP_GetTID_ANSI" /include:"_TCAP_FindParts_ANSI" /out:"..\..\common\lib\AOCVFrameD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy AOCDebug\AOCVFrameD.lib ..\..\common\lib	copy AOCDebug\AOCVFrameD.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vframe___Win32_AOC_Release"
# PROP BASE Intermediate_Dir "vframe___Win32_AOC_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AOCRelease"
# PROP Intermediate_Dir "AOCRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "SPLIT_STACK" /D "USE_ITU_SCCP" /D "ANSI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /out:"..\lib\VFrame.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /include:"_ISUP_VariantToString" /include:"_VAR_GetMsgDescription" /include:"_TCAP_CvtCPTToComponentPDU_ANSI" /include:"_TCAP_CvtComponentPDUToCPT_ANSI" /include:"__ZANSI_TCAP_mod" /include:"_TCAP_GetTID_ANSI" /include:"_TCAP_FindParts_ANSI" /out:"..\..\common\lib\AOCVFrame.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy AOCRelease\AOCVFrame.lib ..\..\common\lib	copy AOCRelease\AOCVFrame.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vframe___Win32_COA_Debug"
# PROP BASE Intermediate_Dir "vframe___Win32_COA_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "COADebug"
# PROP Intermediate_Dir "COADebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "SPLIT_STACK" /D "USE_ANSI_SCCP" /D "CCITT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /out:"..\lib\VFrameD.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /include:"_ISUP_VariantToString" /include:"_VAR_GetMsgDescription" /include:"_TCAP_CvtCPTToComponentPDU_CCITT" /include:"_TCAP_CvtComponentPDUToCPT_CCITT" /include:"__ZITU_TCAP_mod" /include:"_TCAP_GetTID_CCITT" /include:"_TCAP_FindParts_CCITT" /out:"..\..\common\lib\COAVFrameD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy COADebug\COAVFrameD.lib ..\..\common\lib	copy COADebug\COAVFrameD.exp ..\..\common\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vframe___Win32_COA_Release"
# PROP BASE Intermediate_Dir "vframe___Win32_COA_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "COARelease"
# PROP Intermediate_Dir "COARelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP2/include" /I "$(ITS_ROOT)/SNMM/include" /I "$(ITS_ROOT)/SLTM/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/ISUP/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SS7_IMPLEMENTATION" /D "SPLIT_STACK" /D "USE_ANSI_SCCP" /D "CCITT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /out:"..\lib\VFrame.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /include:"_SNMM_Encode_ANSI" /include:"_SLTM_Encode_ANSI" /include:"_SNMM_Encode_CCITT" /include:"_SLTM_Encode_CCITT" /include:"_ISUP_VariantToString" /include:"_VAR_GetMsgDescription" /include:"_TCAP_CvtCPTToComponentPDU_CCITT" /include:"_TCAP_CvtComponentPDUToCPT_CCITT" /include:"__ZITU_TCAP_mod" /include:"_TCAP_GetTID_CCITT" /include:"_TCAP_FindParts_CCITT" /out:"..\..\common\lib\COAVFrame.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy COARelease\COAVFrame.lib ..\..\common\lib	copy COARelease\COAVFrame.exp ..\..\common\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "vframe - Win32 Release"
# Name "vframe - Win32 Debug"
# Name "vframe - Win32 AOC Debug"
# Name "vframe - Win32 AOC Release"
# Name "vframe - Win32 COA Debug"
# Name "vframe - Win32 COA Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\vframe.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\common\include\vframe.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP2\lib\CCITT-MTP2D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\ANSI-MTP3D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP2\lib\ANSI-MTP2D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP2\lib\CCITT-MTP2.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP2\lib\ANSI-MTP2.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\CCITT-MTP3D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\CCITT-MTP3.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\MTP3\lib\ANSI-MTP3.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SCCP\lib\CCITT-SCCPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SCCP\lib\ANSI-SCCPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SCCP\lib\CCITT-SCCP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SCCP\lib\ANSI-SCCP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\CCITT-TCAPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\ANSI-TCAPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\CCITT-TCAP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\ANSI-TCAP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SLTM\lib\CCITT-SLTMD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SLTM\lib\ANSI-SLTMD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SLTM\lib\CCITT-SLTM.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SLTM\lib\ANSI-SLTM.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SNMM\lib\CCITT-SNMMD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SNMM\lib\ANSI-SNMMD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SNMM\lib\CCITT-SNMM.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\SNMM\lib\ANSI-SNMM.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\CCITT-ANSI-TCAPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\ANSI-CCITT-TCAPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\CCITT-ANSI-TCAP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\TCAP\lib\ANSI-CCITT-TCAP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\ISUP\lib\CCITT-ISUPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\ISUP\lib\CCITT-ISUP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\ISUP\lib\ANSI-ISUPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\IntelliSS7\ISUP\lib\ANSI-ISUP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINED.lib

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\IntelliSS7\common\lib\ENGINE.lib

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\ISUP\lib\ISUPVariantsD.lib

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\ISUP\lib\ISUPVariants.lib

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnCD.lib

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnC.lib

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP2\lib\PRC-MTP2.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP2\lib\PRC-MTP2D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP3\lib\PRC-MTP3D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP3\lib\PRC-MTP3.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SCCP\lib\PRC-SCCPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SCCP\lib\PRC-SCCP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\PRC-TCAPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\PRC-TCAP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SLTM\lib\PRC-SLTMD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SLTM\lib\PRC-SLTM.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SNMM\lib\PRC-SNMMD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SNMM\lib\PRC-SNMM.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP2\lib\TTC-MTP2.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP2\lib\TTC-MTP2D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SCCP\lib\TTC-SCCP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SCCP\lib\TTC-SCCPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\TTC-TCAPD.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\TTC-TCAP.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP3\lib\TTC-MTP3D.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP3\lib\TTC-MTP3.lib"

!IF  "$(CFG)" == "vframe - Win32 Release"

!ELSEIF  "$(CFG)" == "vframe - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "vframe - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
