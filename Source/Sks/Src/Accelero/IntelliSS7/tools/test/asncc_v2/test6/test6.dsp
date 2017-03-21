# Microsoft Developer Studio Project File - Name="test6" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test6 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test6.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test6.mak" CFG="test6 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test6 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test6 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test6 - Win32 Release"

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

!ELSEIF  "$(CFG)" == "test6 - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(ITS_ROOT)\common\include" /I "$(ITS_ROOT)\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
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

# Name "test6 - Win32 Release"
# Name "test6 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\map_v4_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_category.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_index.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_info.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_data.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_override_category.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_code.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_data.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_status.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code.h
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_list.h
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter "lib"
# Begin Source File

SOURCE=..\..\..\..\common\lib\SUPPORTD.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\common\lib\CORED.lib
# End Source File
# Begin Source File

SOURCE="..\..\..\..\common\lib\DSM-STUBD.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\common\lib\ASN++D.lib"
# End Source File
# End Group
# Begin Source File

SOURCE=.\test6.asn

!IF  "$(CFG)" == "test6 - Win32 Release"

!ELSEIF  "$(CFG)" == "test6 - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\test6.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -xmlCppDoc -xmlModuleName MAP-V4 -cppModuleName MAP-V4 -cppNamespace map_v4  -u $(ITS_ROOT)\tools\bin\asncc_useful.asn test6.asn

"map_v4_basic_service_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_basic_service_group_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_bearer_service_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_bearer_service_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_call_barring_feature.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_call_barring_feature_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_call_barring_info.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_category.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cli_restriction_option.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_feature.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_feature_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_index.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_info.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_interlock.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_subscription.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_subscription_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_feature.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_feature_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_info.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_options.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_imsi.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_insert_subscriber_data_arg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_inter_cug_restrictions.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_intra_cug_options.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_isdn_address_string.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_isdn_subaddress_string.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_no_reply_condition_time.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_odb_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_odb_general_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_odb_hplmn_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_override_category.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_data.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_info.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_info_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_status.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_subscription_option.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_subscriber_status.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_teleservice_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_teleservice_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_zone_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_zone_code_list.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_basic_service_code.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_basic_service_group_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_bearer_service_code.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_bearer_service_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_call_barring_feature.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_call_barring_feature_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_call_barring_info.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_category.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cli_restriction_option.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_feature.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_feature_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_index.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_info.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_interlock.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_subscription.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_cug_subscription_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_feature.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_feature_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_info.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_forwarding_options.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_imsi.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_insert_subscriber_data_arg.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_inter_cug_restrictions.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_intra_cug_options.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_isdn_address_string.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_isdn_subaddress_string.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_no_reply_condition_time.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_odb_data.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_odb_general_data.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_odb_hplmn_data.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_override_category.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_code.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_data.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_info.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_info_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_status.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_ss_subscription_option.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_subscriber_status.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_teleservice_code.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_teleservice_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_zone_code.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"map_v4_zone_code_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
