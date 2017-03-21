# Microsoft Developer Studio Project File - Name="pprint" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=pprint - Win32 COA Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pprint.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pprint.mak" CFG="pprint - Win32 COA Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pprint - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "pprint - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "pprint - Win32 AOC Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "pprint - Win32 COA Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "pprint - Win32 AOC Release" (based on "Win32 (x86) Console Application")
!MESSAGE "pprint - Win32 COA Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "pprint___Win32_AOC_Debug"
# PROP BASE Intermediate_Dir "pprint___Win32_AOC_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AOCDebug"
# PROP Intermediate_Dir "AOCDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "SPLIT_STACK" /D "ANSI" /D "USE_ITU_SCCP" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"AOCDebug/pprintAOCD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "pprint___Win32_COA_Debug"
# PROP BASE Intermediate_Dir "pprint___Win32_COA_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "COADebug"
# PROP Intermediate_Dir "COADebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "SPLIT_STACK" /D "CCITT" /D "USE_ANSI_SCCP" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"COADebug/pprintCOAD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "pprint___Win32_AOC_Release"
# PROP BASE Intermediate_Dir "pprint___Win32_AOC_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AOCRelease"
# PROP Intermediate_Dir "AOCRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "SPLIT_STACK" /D "ANSI" /D "USE_ITU_SCCP" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"AOCRelease/pprintAOC.exe"

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "pprint___Win32_COA_Release"
# PROP BASE Intermediate_Dir "pprint___Win32_COA_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "COARelease"
# PROP Intermediate_Dir "COARelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../common/include" /I "../../TCAP/include" /I "../../SCCP/include" /I "../../ISUP/include" /I "../../MTP3/include" /I "../../MTP2/include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "SPLIT_STACK" /D "CCITT" /D "USE_ANSI_SCCP" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"COARelease/pprintCOA.exe"

!ENDIF 

# Begin Target

# Name "pprint - Win32 Release"
# Name "pprint - Win32 Debug"
# Name "pprint - Win32 AOC Debug"
# Name "pprint - Win32 COA Debug"
# Name "pprint - Win32 AOC Release"
# Name "pprint - Win32 COA Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\pprint.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Library Files"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\common\lib\VFrameD.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\ENGINED.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\VFrame.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\ENGINE.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\common\lib\DSM-STUBD.lib"

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\common\lib\DSM-STUB.lib"

!IF  "$(CFG)" == "pprint - Win32 Release"

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AOCVFrameD.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AOCVFrame.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\COAVFrame.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\COAVFrameD.lib

!IF  "$(CFG)" == "pprint - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 AOC Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pprint - Win32 COA Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\test.dat
# End Source File
# End Target
# End Project
