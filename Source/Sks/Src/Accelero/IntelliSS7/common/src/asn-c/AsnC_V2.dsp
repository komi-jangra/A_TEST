# Microsoft Developer Studio Project File - Name="AsnC_V2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AsnC_V2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AsnC_V2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsnC_V2.mak" CFG="AsnC_V2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsnC_V2 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AsnC_V2 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AsnC_V2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AsnC_V2_Win32_Release"
# PROP Intermediate_Dir "AsnC_V2_Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\include\asn-c" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/AsnC_V2.lib"

!ELSEIF  "$(CFG)" == "AsnC_V2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AsnC_V2___Win32_Debug"
# PROP BASE Intermediate_Dir "AsnC_V2___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AsnC_V2_Win32_Debug"
# PROP Intermediate_Dir "AsnC_V2_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /I "..\..\include\asn-c" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/AsnC_V2D.lib"

!ENDIF 

# Begin Target

# Name "AsnC_V2 - Win32 Release"
# Name "AsnC_V2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\asn_any.c
# End Source File
# Begin Source File

SOURCE=.\asn_assertion.c
# End Source File
# Begin Source File

SOURCE=.\asn_bit_string.c
# End Source File
# Begin Source File

SOURCE=.\asn_boolean.c
# End Source File
# Begin Source File

SOURCE=.\asn_choice.c
# End Source File
# Begin Source File

SOURCE=.\asn_common.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_any.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_bit_string.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_boolean.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_choice.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_enumerated.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_integer.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_null.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_object.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_object_identifier.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_octet_string.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_real.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_sequence.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_sequence_of.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_set.c
# End Source File
# Begin Source File

SOURCE=.\asn_desc_set_of.c
# End Source File
# Begin Source File

SOURCE=.\asn_enumerated.c
# End Source File
# Begin Source File

SOURCE=.\asn_error.c
# End Source File
# Begin Source File

SOURCE=.\asn_external_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_general_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_generalized_time_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_graphic_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_ia5_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_integer.c
# End Source File
# Begin Source File

SOURCE=.\asn_iso646_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_length.c
# End Source File
# Begin Source File

SOURCE=.\asn_linked_list.c
# End Source File
# Begin Source File

SOURCE=.\asn_null.c
# End Source File
# Begin Source File

SOURCE=.\asn_numeric_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_object.c
# End Source File
# Begin Source File

SOURCE=.\asn_object_descriptor_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_object_identifier.c
# End Source File
# Begin Source File

SOURCE=.\asn_octet_string.c
# End Source File
# Begin Source File

SOURCE=.\asn_octets.c
# End Source File
# Begin Source File

SOURCE=.\asn_printable_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_real.c
# End Source File
# Begin Source File

SOURCE=.\asn_sequence.c
# End Source File
# Begin Source File

SOURCE=.\asn_sequence_of.c
# End Source File
# Begin Source File

SOURCE=.\asn_set.c
# End Source File
# Begin Source File

SOURCE=.\asn_set_of.c
# End Source File
# Begin Source File

SOURCE=.\asn_t61_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_tag.c
# End Source File
# Begin Source File

SOURCE=.\asn_teletex_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_utc_time_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_videotex_string_c.c
# End Source File
# Begin Source File

SOURCE=.\asn_visible_string_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\..\include\asn-c\asn_any.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_assertion.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_bit_string.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_boolean.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_choice.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_common.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_any.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_bit_string.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_boolean.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_choice.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_enumerated.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_integer.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_null.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_object.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_object_identifier.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_octet_string.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_real.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_sequence.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_sequence_of.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_set.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_desc_set_of.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_enumerated.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_error.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_external_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_general_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_generalized_time_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_graphic_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_ia5_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_integer.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_iso646_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_its_feature_class_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_length.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_linked_list.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_null.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_numeric_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_object.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_object_descriptor_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_object_identifier.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_octet_string.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_octets.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_printable_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_real.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_sequence.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_sequence_of.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_set.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_set_of.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_t61_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_tag.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_teletex_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_utc_time_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_videotex_string_c.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-c\asn_visible_string_c.h"
# End Source File
# End Group
# Begin Source File

SOURCE="..\asn-cpp\AsnUseful.asn"

!IF  "$(CFG)" == "AsnC_V2 - Win32 Release"

# Begin Custom Build
InputPath="..\asn-cpp\AsnUseful.asn"

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 -c -cModuleName ASN  ..\asn-cpp\AsnUseful.asn \
	copy .\asn_*.h ..\..\include\asn-c \
	del .\asn_*.h \
	

"..\..\include\asn-c\asn_external_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_generalized_time_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_general_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_graphic_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_ia5_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_iso646_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_numeric_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_object_descriptor_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_printable_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_t61_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_teletex_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_utc_time_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_videotex_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_visible_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_its_feature_class_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_external_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_visible_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_general_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_generalized_time_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_graphic_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_ia5_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_iso646_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_numeric_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_object_descriptor_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_printable_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_t61_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_teletex_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_utc_time_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_videotex_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_its_feature_class_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnC_V2 - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 Useful types...
InputPath="..\asn-cpp\AsnUseful.asn"

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 -c -cModuleName ASN  ..\asn-cpp\AsnUseful.asn \
	copy .\asn_*.h ..\..\include\asn-c \
	del .\asn_*.h \
	

"..\..\include\asn-c\asn_external_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_generalized_time_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_general_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_graphic_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_ia5_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_iso646_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_numeric_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_object_descriptor_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_printable_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_t61_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_teletex_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_utc_time_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_videotex_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_visible_string_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-c\asn_its_feature_class_c.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_external_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_visible_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_general_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_generalized_time_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_graphic_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_ia5_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_iso646_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_numeric_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_object_descriptor_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_printable_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_t61_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_teletex_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_utc_time_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_videotex_string_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\asn_its_feature_class_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
