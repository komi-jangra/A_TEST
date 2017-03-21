# Microsoft Developer Studio Project File - Name="test4_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test4_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test4_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test4_c.mak" CFG="test4_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test4_c - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test4_c - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test4_c - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\common\include\asn-c" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\common\include\asn-c" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "test4_c - Win32 Release"
# Name "test4_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\test4_alert_code_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_carrier_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_destination_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_electronic_serial_number_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_feature_request_rrl_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_feature_result_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_group_information_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_local_termination_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_pstn_termination_c.c
# End Source File
# Begin Source File

SOURCE=.\test4_termination_list_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\test4_alert_code_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_carrier_digits_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_destination_digits_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_electronic_serial_number_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_feature_request_rrl_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_feature_result_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_group_information_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_local_termination_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_pstn_termination_c.h
# End Source File
# Begin Source File

SOURCE=.\test4_termination_list_c.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\..\..\common\lib\AsnC_V2D.lib

!IF  "$(CFG)" == "test4_c - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\AsnC_V2.lib

!IF  "$(CFG)" == "test4_c - Win32 Release"

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\Support.lib

!IF  "$(CFG)" == "test4_c - Win32 Release"

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\CORED.lib

!IF  "$(CFG)" == "test4_c - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\CORE.lib

!IF  "$(CFG)" == "test4_c - Win32 Release"

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\SupportD.lib

!IF  "$(CFG)" == "test4_c - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\test4.asn

!IF  "$(CFG)" == "test4_c - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\test4.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 test4.asn -c

".\test4_alert_code.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_carrier_digits.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_destination_digits.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_electronic_serial_number.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_request_rrl.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_result.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_group_information.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_local_termination.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_pstn_termination.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_termination_list.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_alert_code_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_carrier_digits_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_destination_digits_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_electronic_serial_number_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_request_rrl_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_result_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_group_information_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_local_termination_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_pstn_termination_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_termination_list_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "test4_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\test4.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 test4.asn -c

".\test4_alert_code_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_carrier_digits_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_destination_digits_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_electronic_serial_number_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_request_rrl_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_result_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_group_information_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_local_termination_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_pstn_termination_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_termination_list_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_its_feature_class_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_alert_code_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_carrier_digits_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_destination_digits_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_electronic_serial_number_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_request_rrl_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_result_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_group_information_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_local_termination_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_pstn_termination_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_termination_list_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_its_feature_class_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
