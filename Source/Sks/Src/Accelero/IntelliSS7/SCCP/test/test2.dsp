# Microsoft Developer Studio Project File - Name="test2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test2.mak" CFG="test2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test2 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../MTP3/include" /I "../include" /I "../../common/include" /I "../../tools/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test2___"
# PROP BASE Intermediate_Dir "test2___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug2"
# PROP Intermediate_Dir "Debug2"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../include" /I "../../common/include" /I "../../tools/include" /I "../../MTP3/include" /D "ANSI" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "test2 - Win32 Release"
# Name "test2 - Win32 Debug"
# Begin Source File

SOURCE="..\..\MTP3\lib\ANSI-MTP3.lib"

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP3\lib\ANSI-MTP3D.lib"

!IF  "$(CFG)" == "test2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\ANSI-SCCP.lib"

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\ANSI-SCCPD.lib"

!IF  "$(CFG)" == "test2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\ANSI-TCAP.lib"

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\ANSI-TCAPD.lib"
# End Source File
# Begin Source File

SOURCE=..\..\..\vendors\IntelliNet\lib\ANSIVendor.lib

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\vendors\IntelliNet\lib\ANSIVendorD.lib

!IF  "$(CFG)" == "test2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnC.lib

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnCD.lib

!IF  "$(CFG)" == "test2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\common\lib\CORE++D.lib"
# End Source File
# Begin Source File

SOURCE=..\..\common\lib\CORED.lib

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\common\lib\Support++.lib"

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\common\lib\Support++D.lib"

!IF  "$(CFG)" == "test2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\test2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\tools\lib\unittest.lib

!IF  "$(CFG)" == "test2 - Win32 Release"

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\tools\lib\UnitTestD.lib

!IF  "$(CFG)" == "test2 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test2 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
