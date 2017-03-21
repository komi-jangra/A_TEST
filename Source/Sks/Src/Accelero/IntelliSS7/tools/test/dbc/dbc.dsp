# Microsoft Developer Studio Project File - Name="dbc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=dbc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dbc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dbc.mak" CFG="dbc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "dbc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dbc - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "ITS_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "ITS_IMPLEMENTATION" /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "dbc - Win32 Release"
# Name "dbc - Win32 Debug"
# Begin Group "Source"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\test_dbc.cpp
# End Source File
# Begin Source File

SOURCE=.\test_main.cpp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\test_dbc.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter ".lib"
# Begin Source File

SOURCE=..\..\..\common\lib\DBCServerCD.lib

!IF  "$(CFG)" == "dbc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\common\lib\CORED.lib

!IF  "$(CFG)" == "dbc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\common\lib\SupportD.lib

!IF  "$(CFG)" == "dbc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\common\lib\DSM-STUBD.lib"

!IF  "$(CFG)" == "dbc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\common\lib\DSM-STUB.lib"

!IF  "$(CFG)" == "dbc - Win32 Release"

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\common\lib\DBCServerC.lib

!IF  "$(CFG)" == "dbc - Win32 Release"

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\common\lib\CORE.lib

!IF  "$(CFG)" == "dbc - Win32 Release"

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\common\lib\Support.lib

!IF  "$(CFG)" == "dbc - Win32 Release"

!ELSEIF  "$(CFG)" == "dbc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\DefaultName.ini
# End Source File
# End Target
# End Project
