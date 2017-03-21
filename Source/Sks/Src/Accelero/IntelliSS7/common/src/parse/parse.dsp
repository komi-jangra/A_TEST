# Microsoft Developer Studio Project File - Name="parse" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=parse - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "parse.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "parse.mak" CFG="parse - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "parse - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "parse - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "parse - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\include" /I "..\..\include\parse" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\Parse++.lib"

!ELSEIF  "$(CFG)" == "parse - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /I "..\..\include\parse" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\Parse++D.lib"

!ENDIF 

# Begin Target

# Name "parse - Win32 Release"
# Name "parse - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\parse.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_aggregate.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_construct.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_exception.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_keyword.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_production.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_repetition.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_terminal.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_token.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\parse_utilities.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\parse\parse.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_aggregate.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_choice.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_construct.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_exception.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_keyword.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_parser.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_production.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_repetition.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_scanner.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_terminal.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_token.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_tokenizer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\parse\parse_utilities.h
# End Source File
# End Group
# End Target
# End Project
