# Microsoft Developer Studio Project File - Name="Test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Test - Win32 CCITT C
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Test.mak" CFG="Test - Win32 CCITT C"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Test - Win32 ANSI C" (based on "Win32 (x86) Console Application")
!MESSAGE "Test - Win32 CCITT C" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Test - Win32 ANSI C"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Test___Win32_ANSI_C"
# PROP BASE Intermediate_Dir "Test___Win32_ANSI_C"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TestANSIC"
# PROP Intermediate_Dir "TestANSIC"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Test - Win32 CCITT C"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Test___Win32_CCITT_C"
# PROP BASE Intermediate_Dir "Test___Win32_CCITT_C"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TestCCITTC"
# PROP Intermediate_Dir "TestCCITTC"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ITS_ROOT)/common/include" /I "$(ITS_ROOT)/MTP3/include" /I "$(ITS_ROOT)/SCCP/include" /I "$(ITS_ROOT)/TCAP/include" /I "../include" /I "$(ITS_ROOT)\ISUP\test\ebsheaders" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CCITT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Test - Win32 ANSI C"
# Name "Test - Win32 CCITT C"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\printISUPMsg.c
# End Source File
# Begin Source File

SOURCE=.\readISUPMsg.c
# End Source File
# Begin Source File

SOURCE=.\sendISUPMsg.c
# End Source File
# Begin Source File

SOURCE=.\test.c
# End Source File
# Begin Source File

SOURCE=.\testMain.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\printISUPMsg.h
# End Source File
# Begin Source File

SOURCE=.\readISUPMsg.h
# End Source File
# Begin Source File

SOURCE=.\sendISUPMsg.h
# End Source File
# Begin Source File

SOURCE=.\test.h
# End Source File
# End Group
# Begin Group "libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\MTP3\lib\ANSI-MTP3D.lib"

!IF  "$(CFG)" == "Test - Win32 ANSI C"

!ELSEIF  "$(CFG)" == "Test - Win32 CCITT C"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\SupportD.lib
# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnCD.lib
# End Source File
# Begin Source File

SOURCE="..\..\SCCP\lib\ANSI-SCCPD.lib"

!IF  "$(CFG)" == "Test - Win32 ANSI C"

!ELSEIF  "$(CFG)" == "Test - Win32 CCITT C"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\SCORED.lib
# End Source File
# Begin Source File

SOURCE="..\..\MTP3\lib\CCITT-MTP3D.lib"

!IF  "$(CFG)" == "Test - Win32 ANSI C"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Test - Win32 CCITT C"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\SCCP\lib\CCITT-SCCPD.lib"

!IF  "$(CFG)" == "Test - Win32 ANSI C"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Test - Win32 CCITT C"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\ANSI-ISUPD.lib"

!IF  "$(CFG)" == "Test - Win32 ANSI C"

!ELSEIF  "$(CFG)" == "Test - Win32 CCITT C"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
