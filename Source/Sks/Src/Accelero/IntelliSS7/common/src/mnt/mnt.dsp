# Microsoft Developer Studio Project File - Name="mnt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mnt - Win32 Debug For Engine
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mnt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mnt.mak" CFG="mnt - Win32 Debug For Engine"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mnt - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mnt - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mnt - Win32 Debug For Engine" (based on "Win32 (x86) Static Library")
!MESSAGE "mnt - Win32 Release For Engine" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mnt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_Release"
# PROP Intermediate_Dir "Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ITS_IMPLEMENTATION" /D "GCS_IMPLEMENTATION" /D "YY_NEVER_INTERACTIVE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/MNT.lib"

!ELSEIF  "$(CFG)" == "mnt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32_Debug"
# PROP Intermediate_Dir "Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ITS_IMPLEMENTATION" /D "GCS_IMPLEMENTATION" /D "YY_NEVER_INTERACTIVE" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/MNTD.lib"

!ELSEIF  "$(CFG)" == "mnt - Win32 Debug For Engine"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mnt___Win32_Debug_For_Engine"
# PROP BASE Intermediate_Dir "mnt___Win32_Debug_For_Engine"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32_Debug_For_Engine"
# PROP Intermediate_Dir "Win32_Debug_For_Engine"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ITS_IMPLEMENTATION" /D "GCS_IMPLEMENTATION" /D "YY_NEVER_INTERACTIVE" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "GCS_IMPLEMENTATION" /D "YY_NEVER_INTERACTIVE" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/MNTD.lib"
# ADD LIB32 /nologo /out:"../../lib/MNT-FOR-ENGINED.lib"

!ELSEIF  "$(CFG)" == "mnt - Win32 Release For Engine"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mnt___Win32_Release_For_Engine"
# PROP BASE Intermediate_Dir "mnt___Win32_Release_For_Engine"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_Release_For_Engine"
# PROP Intermediate_Dir "Win32_Release_For_Engine"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ITS_IMPLEMENTATION" /D "GCS_IMPLEMENTATION" /D "YY_NEVER_INTERACTIVE" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../include" /I "../../include/mnt" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "GCS_IMPLEMENTATION" /D "YY_NEVER_INTERACTIVE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/MNT.lib"
# ADD LIB32 /nologo /out:"../../lib/MNT-FOR-ENGINE.lib"

!ENDIF 

# Begin Target

# Name "mnt - Win32 Release"
# Name "mnt - Win32 Debug"
# Name "mnt - Win32 Debug For Engine"
# Name "mnt - Win32 Release For Engine"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mnt_command.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_constructs.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_errors.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_evaluator.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_exception.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_interpreter.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_lexer.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_messages.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_mnt.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\mnt_predefined_commands.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\mnt\mnt.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mnt\mnt_command.h
# End Source File
# Begin Source File

SOURCE=.\mnt_constructs.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mnt\mnt_errors.h
# End Source File
# Begin Source File

SOURCE=.\mnt_evaluator.h
# End Source File
# Begin Source File

SOURCE=.\mnt_exception.h
# End Source File
# Begin Source File

SOURCE=.\mnt_helpers.h
# End Source File
# Begin Source File

SOURCE=.\mnt_intern.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mnt\mnt_interpreter.h
# End Source File
# Begin Source File

SOURCE=.\mnt_messages.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mnt\mnt_mnt.h
# End Source File
# Begin Source File

SOURCE=..\..\include\mnt\mnt_options.h
# End Source File
# Begin Source File

SOURCE=.\mnt_parser.h
# End Source File
# Begin Source File

SOURCE=.\mnt_predefined_commands.h
# End Source File
# Begin Source File

SOURCE=.\mnt_unistd.h
# End Source File
# Begin Source File

SOURCE=.\unistd.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\mnt_lexer.l

!IF  "$(CFG)" == "mnt - Win32 Release"

# Begin Custom Build - Compiling Lex file...
InputPath=.\mnt_lexer.l

"./mnt_lexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist .\mnt_unistd.h copy .\mnt_unistd.h .\unistd.h 
	if not exist /tmp mkdir /tmp 
	flex  -omnt_lexer.cpp mnt_lexer.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "mnt - Win32 Debug"

# Begin Custom Build - Compiling Lex file...
InputPath=.\mnt_lexer.l

"./mnt_lexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist .\mnt_unistd.h copy .\mnt_unistd.h .\unistd.h 
	if not exist /tmp mkdir /tmp 
	flex  -omnt_lexer.cpp mnt_lexer.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "mnt - Win32 Debug For Engine"

# Begin Custom Build - Compiling Lex file...
InputPath=.\mnt_lexer.l

"./mnt_lexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist .\mnt_unistd.h copy .\mnt_unistd.h .\unistd.h 
	if not exist /tmp mkdir /tmp 
	flex  -omnt_lexer.cpp mnt_lexer.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "mnt - Win32 Release For Engine"

# Begin Custom Build - Compiling Lex file...
InputPath=.\mnt_lexer.l

"./mnt_lexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist .\mnt_unistd.h copy .\mnt_unistd.h .\unistd.h 
	if not exist /tmp mkdir /tmp 
	flex  -omnt_lexer.cpp mnt_lexer.l 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mnt_parser.y

!IF  "$(CFG)" == "mnt - Win32 Release"

# Begin Custom Build - Compiling Yacc file...
InputPath=.\mnt_parser.y

BuildCmds= \
	if not exist /tmp mkdir /tmp \
	bison mnt_parser.y -t -v -d -o mnt_parser.cpp -S bison.simple \
	if exist mnt_parser.cpp.h copy mnt_parser.cpp.h mnt_parser.h \
	if exist mnt_parser.cpp.h del mnt_parser.cpp.h \
	

"./mnt_parser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./mnt_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "mnt - Win32 Debug"

# Begin Custom Build - Compiling Yacc file...
InputPath=.\mnt_parser.y

BuildCmds= \
	if not exist /tmp mkdir /tmp \
	bison mnt_parser.y -t -v -d -o mnt_parser.cpp -S bison.simple \
	if exist mnt_parser.cpp.h copy mnt_parser.cpp.h mnt_parser.h \
	if exist mnt_parser.cpp.h del mnt_parser.cpp.h \
	

"./mnt_parser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./mnt_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "mnt - Win32 Debug For Engine"

# Begin Custom Build - Compiling Yacc file...
InputPath=.\mnt_parser.y

BuildCmds= \
	if not exist /tmp mkdir /tmp \
	bison mnt_parser.y -t -v -d -o mnt_parser.cpp -S bison.simple \
	if exist mnt_parser.cpp.h copy mnt_parser.cpp.h mnt_parser.h \
	if exist mnt_parser.cpp.h del mnt_parser.cpp.h \
	

"./mnt_parser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./mnt_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "mnt - Win32 Release For Engine"

# Begin Custom Build - Compiling Yacc file...
InputPath=.\mnt_parser.y

BuildCmds= \
	if not exist /tmp mkdir /tmp \
	bison mnt_parser.y -t -v -d -o mnt_parser.cpp -S bison.simple \
	if exist mnt_parser.cpp.h copy mnt_parser.cpp.h mnt_parser.h \
	if exist mnt_parser.cpp.h del mnt_parser.cpp.h \
	

"./mnt_parser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./mnt_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
