# Microsoft Developer Studio Project File - Name="test6_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test6_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test6_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test6_c.mak" CFG="test6_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test6_c - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test6_c - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test6_c - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "test6_c - Win32 Debug"

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

# Name "test6_c - Win32 Release"
# Name "test6_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_group_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_category_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cli_restriction_option_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_index_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_interlock_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_inter_cug_restrictions_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_intra_cug_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_subaddress_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_reply_condition_time_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_general_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_hplmn_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_override_category_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_subscription_option_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_list_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\map_v4_basic_service_code_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_group_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_code_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_info_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_category_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cli_restriction_option_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_index_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_info_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_interlock_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_info_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_options_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_inter_cug_restrictions_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_intra_cug_options_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_address_string_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_subaddress_string_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_reply_condition_time_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_data_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_general_data_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_hplmn_data_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_override_category_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_code_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_data_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_status_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_subscription_option_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_status_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_code_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_list_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_c.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_list_c.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\..\..\common\lib\AsnC_V2D.lib

!IF  "$(CFG)" == "test6_c - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "test6_c - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\SupportD.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\CORED.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\test6.asn

!IF  "$(CFG)" == "test6_c - Win32 Release"

!ELSEIF  "$(CFG)" == "test6_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\test6.asn

".\map_v4_bearer_service_code_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -c -cModuleName MAP-V4 -u $(ITS_ROOT)\tools\bin\asncc_useful.asn test6.asn

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
