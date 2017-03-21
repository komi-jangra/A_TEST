# Microsoft Developer Studio Project File - Name="asn_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=asn_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "asn_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "asn_c.mak" CFG="asn_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "asn_c - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "asn_c - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "asn_c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "asn_c_Win32_Release"
# PROP Intermediate_Dir "asn_c_Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../common/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "USING_FLEX" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../../bin/asnc.exe"

!ELSEIF  "$(CFG)" == "asn_c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "asn_c___Win32_Debug"
# PROP BASE Intermediate_Dir "asn_c___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "asn_c_Win32_Debug"
# PROP Intermediate_Dir "asn_c_Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../common/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "USING_FLEX" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../bin/asncD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "asn_c - Win32 Release"
# Name "asn_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dfns.c
# End Source File
# Begin Source File

SOURCE=.\dtabs.c
# End Source File
# Begin Source File

SOURCE=.\etabs.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\misc.c
# End Source File
# Begin Source File

SOURCE=.\pass2.c
# End Source File
# Begin Source File

SOURCE=.\ptabs.c
# End Source File
# Begin Source File

SOURCE=.\y.tab.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\asncomp.h
# End Source File
# Begin Source File

SOURCE=.\pass2.h
# End Source File
# Begin Source File

SOURCE=.\sym.h
# End Source File
# Begin Source File

SOURCE=.\table.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\lex.l

!IF  "$(CFG)" == "asn_c - Win32 Release"

# Begin Custom Build - Compiling lex file...
InputPath=.\lex.l

".\lex.yy.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex lex.l

# End Custom Build

!ELSEIF  "$(CFG)" == "asn_c - Win32 Debug"

# Begin Custom Build - Compiling lex file...
InputPath=.\lex.l

".\lex.yy.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex lex.l

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\yacc.y

!IF  "$(CFG)" == "asn_c - Win32 Release"

# Begin Custom Build - Compiling yacc file...
InputPath=.\yacc.y

".\y.tab.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bison yacc.y --yacc --defines

# End Custom Build

!ELSEIF  "$(CFG)" == "asn_c - Win32 Debug"

# Begin Custom Build - Compiling yacc file...
InputPath=.\yacc.y

".\y.tab.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bison yacc.y --yacc --defines

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
