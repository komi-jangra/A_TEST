# Microsoft Developer Studio Project File - Name="test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test - Win32 Receive Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Receive Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Send Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Receive Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test - Win32 Release"

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

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "../include" /I "../../common/include" /I "../../tools/include" /I "../../MTP3/include" /D "ANSI" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___Win32_Send_Debug"
# PROP BASE Intermediate_Dir "test___Win32_Send_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Send_Debug"
# PROP Intermediate_Dir "Send_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Od /I "../include" /I "../../common/include" /I "../../tools/include" /I "../../MTP3/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /FD /ZI /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Od /I "../include" /I "../../common/include" /I "../../tools/include" /I "../../MTP3/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /D "SEND" /FD /ZI /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___Win32_Receive_Debug"
# PROP BASE Intermediate_Dir "test___Win32_Receive_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Receive_Debug"
# PROP Intermediate_Dir "Receive_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Od /I "../include" /I "../../common/include" /I "../../tools/include" /I "../../MTP3/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /FD /ZI /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GX /Od /I "../include" /I "../../common/include" /I "../../tools/include" /I "../../MTP3/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ANSI" /FD /ZI /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "test - Win32 Release"
# Name "test - Win32 Debug"
# Name "test - Win32 Send Debug"
# Name "test - Win32 Receive Debug"
# Begin Source File

SOURCE="..\..\MTP3\lib\ANSI-MTP3.lib"

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\MTP3\lib\ANSI-MTP3D.lib"

!IF  "$(CFG)" == "test - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\ANSI-SCCP.lib"

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\lib\ANSI-SCCPD.lib"

!IF  "$(CFG)" == "test - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\ANSI-TCAP.lib"

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\TCAP\lib\ANSI-TCAPD.lib"
# End Source File
# Begin Source File

SOURCE=..\..\..\vendors\IntelliNet\lib\ANSIVendor.lib

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\vendors\IntelliNet\lib\ANSIVendorD.lib

!IF  "$(CFG)" == "test - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnC.lib

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnCD.lib

!IF  "$(CFG)" == "test - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\common\lib\AsnCppD.lib
# End Source File
# Begin Source File

SOURCE="..\..\common\lib\CORE++D.lib"
# End Source File
# Begin Source File

SOURCE=..\..\common\lib\CORED.lib

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\common\lib\Support++.lib"

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\common\lib\Support++D.lib"

!IF  "$(CFG)" == "test - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\test.cpp
# End Source File
# Begin Source File

SOURCE=..\..\tools\lib\unittest.lib

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\tools\lib\UnitTestD.lib

!IF  "$(CFG)" == "test - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Send Debug"

!ELSEIF  "$(CFG)" == "test - Win32 Receive Debug"

!ENDIF 

# End Source File
# End Target
# End Project
