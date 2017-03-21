# Microsoft Developer Studio Project File - Name="ANSI_GENERIC_92" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ANSI_GENERIC_92 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ANSI_GENERIC_92.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ANSI_GENERIC_92.mak" CFG="ANSI_GENERIC_92 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ANSI_GENERIC_92 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ANSI_GENERIC_92 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_GENERIC_92_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(ITS_ROOT)\SNMM\include" /I "$(ITS_ROOT)\SLTM\include" /I "..\..\include" /I "..\..\include\ansi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_GENERIC_92_EXPORTS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../lib/ANSI_GENERIC_92.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\ANSI_GENERIC_92.lib ..\..\lib	copy Release\ANSI_GENERIC_92.exp ..\..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_GENERIC_92_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(ITS_ROOT)\SNMM\include" /I "$(ITS_ROOT)\SLTM\include" /I "..\..\include" /I "..\..\include\ansi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ANSI_GENERIC_92_EXPORTS" /D "INCLUDE_CODEC" /D "ITSSS7_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../lib/ANSI_GENERIC_92D.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\ANSI_GENERIC_92D.lib ..\..\lib	copy Debug\ANSI_GENERIC_92D.exp ..\..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ANSI_GENERIC_92 - Win32 Release"
# Name "ANSI_GENERIC_92 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\ansi-csc_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-generic_state_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-idle_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-inter_state_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-isup_92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-rcvd_in_anm_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-sent_out_anm_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-timers.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-validate_param.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_cot_report_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_cotreports_and_cra_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_cotreports_have_cra_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_acm_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_anm_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_cot_and_iam_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_cot_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_cra_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_iam_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_res_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_in_rlc_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_acm_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_anm_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_gra_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_iam_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_rel_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_res_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_rlc_ansi92.c"
# End Source File
# Begin Source File

SOURCE=".\ansi-wait_out_rsc_ansi92.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\ENGINED.lib

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\ANSIVendorD.lib

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\VFrameD.lib

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\..\IntelliSS7\ISUP\lib\ANSI-ISUPD.lib"

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\VFrame.lib

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\IntelliSS7\common\lib\ENGINE.lib

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\..\IntelliSS7\ISUP\lib\ANSI-ISUP.lib"

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\ANSIVendor.lib

!IF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Release"

!ELSEIF  "$(CFG)" == "ANSI_GENERIC_92 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
