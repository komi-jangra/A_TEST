# Microsoft Developer Studio Project File - Name="AsnCC_WIP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=AsnCC_WIP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AsnCC_WIP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsnCC_WIP.mak" CFG="AsnCC_WIP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsnCC_WIP - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AsnCC_WIP - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AsnCC_WIP - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "YY_NEVER_INTERACTIVE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"..\..\bin\asncc_wip.exe"

!ELSEIF  "$(CFG)" == "AsnCC_WIP - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "YY_NEVER_INTERACTIVE" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"..\..\bin\asncc_wip.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AsnCC_WIP - Win32 Release"
# Name "AsnCC_WIP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\asncc_assertion.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_ast.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_check_semantic_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_command_file.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_command_interpreter.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_components_of_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_evaluate_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_c_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_c_xml_doc_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_cpp_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_cpp_xml_doc_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_lexer.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_link_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_main.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_merge_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_normalize_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_print_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_recursive_visitor.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_tag.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_util.cpp
# End Source File
# Begin Source File

SOURCE=.\asncc_visitor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\asncc.h
# End Source File
# Begin Source File

SOURCE=.\asncc_assertion.h
# End Source File
# Begin Source File

SOURCE=.\asncc_ast.h
# End Source File
# Begin Source File

SOURCE=.\asncc_check_semantic_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_command_file.h
# End Source File
# Begin Source File

SOURCE=.\asncc_command_interpreter.h
# End Source File
# Begin Source File

SOURCE=.\asncc_components_of_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_evaluate_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_c_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_c_xml_doc_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_cpp_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_generate_cpp_xml_doc_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_link_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_merge_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_normalize_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_parser.h
# End Source File
# Begin Source File

SOURCE=.\asncc_print_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_recursive_visitor.h
# End Source File
# Begin Source File

SOURCE=.\asncc_tag.h
# End Source File
# Begin Source File

SOURCE=.\asncc_unistd.h
# End Source File
# Begin Source File

SOURCE=.\asncc_util.h
# End Source File
# Begin Source File

SOURCE=.\asncc_visitor.h
# End Source File
# Begin Source File

SOURCE=.\unistd.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\asn1.lex

!IF  "$(CFG)" == "AsnCC_WIP - Win32 Release"

# Begin Custom Build - Compiling Lex file...
InputPath=.\asn1.lex

".\asncc_lexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist .\asncc_unistd.h copy .\asncc_unistd.h .\unistd.h 
	if not exist \tmp mkdir \tmp 
	flex  -oasncc_lexer.cpp asn1.lex 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCC_WIP - Win32 Debug"

# Begin Custom Build - Compiling Lex file...
InputPath=.\asn1.lex

".\asncc_lexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist .\asncc_unistd.h copy .\asncc_unistd.h .\unistd.h 
	if not exist \tmp mkdir \tmp 
	flex  -oasncc_lexer.cpp asn1.lex 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asn1.yacc

!IF  "$(CFG)" == "AsnCC_WIP - Win32 Release"

# Begin Custom Build - Compiling Yacc file...
InputPath=.\asn1.yacc

BuildCmds= \
	if not exist \tmp mkdir \tmp \
	bison asn1.yacc -t -v -d -o asncc_parser.cpp -S bison_parser \
	if exist asncc_parser.cpp.h copy asncc_parser.cpp.h asncc_parser.h \
	if exist asncc_parser.cpp.h del asncc_parser.cpp.h \
	

".\asncc_parser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asncc_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCC_WIP - Win32 Debug"

# Begin Custom Build - Compiling Yacc file...
InputPath=.\asn1.yacc

BuildCmds= \
	if not exist \tmp mkdir \tmp \
	bison asn1.yacc -t -v -d -o asncc_parser.cpp -S bison_parser \
	if exist asncc_parser.cpp.h copy asncc_parser.cpp.h asncc_parser.h \
	if exist asncc_parser.cpp.h del asncc_parser.cpp.h \
	

".\asncc_parser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asncc_parser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
