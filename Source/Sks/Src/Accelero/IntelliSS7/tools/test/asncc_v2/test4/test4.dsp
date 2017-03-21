# Microsoft Developer Studio Project File - Name="test4" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test4 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test4.mak" CFG="test4 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test4 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test4 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test4 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\common\include\asn-cpp" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "ITS_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ITS_IMPLEMENTATION" /YX /FD /GZ /c
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

# Name "test4 - Win32 Release"
# Name "test4 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_alert_code.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_carrier_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_destination_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_electronic_serial_number.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_feature_request_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_feature_result.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_group_information.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_local_termination.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_pstn_termination.cpp
# End Source File
# Begin Source File

SOURCE=.\test4_termination_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\test4_alert_code.h
# End Source File
# Begin Source File

SOURCE=.\test4_carrier_digits.h
# End Source File
# Begin Source File

SOURCE=.\test4_destination_digits.h
# End Source File
# Begin Source File

SOURCE=.\test4_electronic_serial_number.h
# End Source File
# Begin Source File

SOURCE=.\test4_feature_request_rrl.h
# End Source File
# Begin Source File

SOURCE=.\test4_feature_result.h
# End Source File
# Begin Source File

SOURCE=.\test4_group_information.h
# End Source File
# Begin Source File

SOURCE=.\test4_local_termination.h
# End Source File
# Begin Source File

SOURCE=.\test4_pstn_termination.h
# End Source File
# Begin Source File

SOURCE=.\test4_termination_list.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\..\..\common\lib\SUPPORT.lib

!IF  "$(CFG)" == "test4 - Win32 Release"

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\CORE.lib

!IF  "$(CFG)" == "test4 - Win32 Release"

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\..\common\lib\DSM-STUB.lib"

!IF  "$(CFG)" == "test4 - Win32 Release"

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\SUPPORTD.lib

!IF  "$(CFG)" == "test4 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\CORED.lib

!IF  "$(CFG)" == "test4 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\..\common\lib\DSM-STUBD.lib"

!IF  "$(CFG)" == "test4 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\..\common\lib\ASN++D.lib"

!IF  "$(CFG)" == "test4 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\..\common\lib\ASN++.lib"

!IF  "$(CFG)" == "test4 - Win32 Release"

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\test4.asn

!IF  "$(CFG)" == "test4 - Win32 Release"

!ELSEIF  "$(CFG)" == "test4 - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\test4.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 test4.asn -cpp -xmlCppDoc -u    $(ITS_ROOT)\tools\bin\asncc_useful.asn

".\test4_alert_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_carrier_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_destination_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_electronic_serial_number.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_request_rrl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_group_information.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_local_termination.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_pstn_termination.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_termination_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_alert_code.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_carrier_digits.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_destination_digits.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_electronic_serial_number.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_request_rrl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_feature_result.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_group_information.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_local_termination.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_pstn_termination.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\test4_termination_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
