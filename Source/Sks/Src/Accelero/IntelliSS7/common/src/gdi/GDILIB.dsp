# Microsoft Developer Studio Project File - Name="GDILIB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GDILIB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GDILIB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GDILIB.mak" CFG="GDILIB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GDILIB - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GDILIB - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GDILIB - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include/gdi" /I "../../include" /I "../../include/asn-cpp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\GDI-ASN.lib"

!ELSEIF  "$(CFG)" == "GDILIB - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include/gdi" /I "../../include" /I "../../include/asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\GDI-ASND.lib"

!ENDIF 

# Begin Target

# Name "GDILIB - Win32 Release"
# Name "GDILIB - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\sr_3389_action_id.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_ain_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_application_name.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_data_element.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_data_element_block.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_data_element_list.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_element_data.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_element_error.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_element_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_element_value.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_get_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_get_data_result.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_invoke_app_data.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_invoke_app_param.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_invoke_app_request.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_invoke_app_response.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_invoke_app_result.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_result_type.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_security_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_send_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_send_data_result.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_3389_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_action_id.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_application_name.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_data_element.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_data_element_block.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_data_element_list.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_element_data.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_element_error.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_element_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_element_value.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_get_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_get_data_result.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_invoke_app_data.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_invoke_app_param.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_invoke_app_request.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_invoke_app_response.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_invoke_app_result.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_result_type.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_security_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_send_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_send_data_result.cpp
# End Source File
# Begin Source File

SOURCE=.\sr_5202_service_key.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Source File

SOURCE=".\gdi-ansi.asn"

!IF  "$(CFG)" == "GDILIB - Win32 Release"

# Begin Custom Build
InputPath=".\gdi-ansi.asn"

BuildCmds= \
	../../../tools/bin/asncc_v2 -u ../../../tools/bin/asncc_useful.asn -cpp -cppNamespace sr_3389 gdi-ansi.asn \
	copy sr_3389*.h ..\..\include\gdi \
	del sr_3389*.h \
	

"sr_3389_action_id.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_ain_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_application_name.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_data_element.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_data_element_block.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_data_element_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_error.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_value.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_get_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_get_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_request.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_response.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_result_type.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_security_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_send_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_send_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_service_key.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "GDILIB - Win32 Debug"

# Begin Custom Build
InputPath=".\gdi-ansi.asn"

BuildCmds= \
	../../../tools/bin/asncc_v2 -u ../../../tools/bin/asncc_useful.asn -cpp -cppNamespace sr_3389 gdi-ansi.asn \
	copy sr_3389*.h ..\..\include\gdi \
	del sr_3389*.h \
	

"sr_3389_action_id.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_ain_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_application_name.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_data_element.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_data_element_block.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_data_element_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_error.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_element_value.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_get_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_get_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_request.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_response.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_invoke_app_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_result_type.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_security_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_send_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_send_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_3389_service_key.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\gdi-itu.asn"

!IF  "$(CFG)" == "GDILIB - Win32 Release"

# Begin Custom Build
InputPath=".\gdi-itu.asn"

BuildCmds= \
	../../../tools/bin/asncc_v2 -u ../../../tools/bin/asncc_useful.asn -cpp -cppNamespace sr_5202 gdi-itu.asn \
	copy sr_5202*.h ..\..\include\gdi \
	del sr_5202*.h \
	

"sr_5202_action_id.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_application_name.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_data_element.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_data_element_block.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_data_element_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_error.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_value.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_get_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_get_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_request.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_response.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_result_type.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_security_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_send_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_send_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_service_key.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "GDILIB - Win32 Debug"

# Begin Custom Build
InputPath=".\gdi-itu.asn"

BuildCmds= \
	../../../tools/bin/asncc_v2 -u ../../../tools/bin/asncc_useful.asn -cpp -cppNamespace sr_5202 gdi-itu.asn \
	copy sr_5202*.h ..\..\include\gdi \
	del sr_5202*.h \
	

"sr_5202_action_id.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_application_name.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_data_element.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_data_element_block.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_data_element_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_digits.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_error.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_element_value.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_get_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_get_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_request.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_response.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_invoke_app_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_result_type.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_security_identifier.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_send_data_param.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_send_data_result.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sr_5202_service_key.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
