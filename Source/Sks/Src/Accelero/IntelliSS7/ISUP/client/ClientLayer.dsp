# Microsoft Developer Studio Project File - Name="ClientLayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ClientLayer - Win32 ANSI Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientLayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientLayer.mak" CFG="ClientLayer - Win32 ANSI Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientLayer - Win32 CCITT Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClientLayer - Win32 ANSI Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClientLayer - Win32 CCITT Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClientLayer - Win32 ANSI Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientLayer - Win32 CCITT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CCITT Debug"
# PROP BASE Intermediate_Dir "CCITT Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CCITTDebug"
# PROP Intermediate_Dir "CCITTDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "CCITT" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "CCITT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /out:"../lib/CCITT-ClientLayerD.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /include:"_ISUP_EncodeMTP3_CCITT" /out:"../lib/CCITT-ClientLayerD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy CCITTDebug\CCITT-ClientLayerD.lib ..\lib	copy CCITTDebug\CCITT-ClientLayerD.exp ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ANSI Debug"
# PROP BASE Intermediate_Dir "ANSI Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSIDebug"
# PROP Intermediate_Dir "ANSIDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "CCITT" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "ANSI" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /out:"../lib/CCITT-ClientLayerD.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /include:"_ISUP_EncodeMTP3_ANSI" /out:"../lib/ANSI-ClientLayerD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSIDebug\ANSI-ClientLayerD.lib ..\lib	copy ANSIDebug\ANSI-ClientLayerD.exp ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 CCITT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CCITT Release"
# PROP BASE Intermediate_Dir "CCITT Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "CCITTRelease"
# PROP Intermediate_Dir "CCITTRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "CCITT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../lib/CCITT-ClientLayer.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /include:"_ISUP_EncodeMTP3_CCITT" /out:"../lib/CCITT-ClientLayer.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy CCITTRelease\CCITT-ClientLayer.lib ..\lib	copy CCITTRelease\CCITT-ClientLayer.exp ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ANSI Release"
# PROP BASE Intermediate_Dir "ANSI Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSIRelease"
# PROP Intermediate_Dir "ANSIRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "CCITT" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\MTP2\include" /I "$(ITS_ROOT)\MTP3\include" /I "$(ITS_ROOT)\SCCP\include" /I "$(ITS_ROOT)\TCAP\include" /I "$(ITS_ROOT)\ISUP\include" /I "$(VENDOR_ROOT)\IntelliNet\include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CLIENTLAYER_EXPORTS" /D "CL_IMPLEMENTATION" /D "ANSI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../lib/CCITT-ClientLayer.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /include:"_ISUP_EncodeMTP3_ANSI" /out:"../lib/ANSI-ClientLayer.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ANSIRelease\ANSI-ClientLayer.lib ..\lib	copy ANSIRelease\ANSI-ClientLayer.exp ..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ClientLayer - Win32 CCITT Debug"
# Name "ClientLayer - Win32 ANSI Debug"
# Name "ClientLayer - Win32 CCITT Release"
# Name "ClientLayer - Win32 ANSI Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\clientapi.c
# End Source File
# Begin Source File

SOURCE=.\clientimpl.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\clientapi.h
# End Source File
# Begin Source File

SOURCE=.\clientimpl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE="..\lib\ANSI-ISUPD.lib"

!IF  "$(CFG)" == "ClientLayer - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\ENGINED.lib

!IF  "$(CFG)" == "ClientLayer - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Debug"

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\CCITT-ISUPD.lib"

!IF  "$(CFG)" == "ClientLayer - Win32 CCITT Debug"

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\ANSI-ISUP.lib"

!IF  "$(CFG)" == "ClientLayer - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 CCITT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\CCITT-ISUP.lib"

!IF  "$(CFG)" == "ClientLayer - Win32 CCITT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 CCITT Release"

!ELSEIF  "$(CFG)" == "ClientLayer - Win32 ANSI Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
