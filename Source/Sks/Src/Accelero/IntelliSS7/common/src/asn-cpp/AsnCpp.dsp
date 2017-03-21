# Microsoft Developer Studio Project File - Name="AsnCpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AsnCpp - Win32 Debug For Engine
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AsnCpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsnCpp.mak" CFG="AsnCpp - Win32 Debug For Engine"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsnCpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AsnCpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AsnCpp - Win32 Debug For Engine" (based on "Win32 (x86) Static Library")
!MESSAGE "AsnCpp - Win32 Release For Engine" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AsnCpp - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\include\asn-cpp" /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "ITS_IMPLEMENTATION" /YX"Asn.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/ASN++.lib"

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\include" /I "..\..\include\asn-cpp" /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"Asn.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../lib/ASN++D.lib"

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Debug For Engine"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AsnCpp___Win32_Debug_For_Engine"
# PROP BASE Intermediate_Dir "AsnCpp___Win32_Debug_For_Engine"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32_Debug_For_Engine"
# PROP Intermediate_Dir "Win32_Debug_For_Engine"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\include" /I "..\..\include\asn-cpp" /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ITS_IMPLEMENTATION" /YX"Asn.h" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "..\..\include" /I "..\..\include\asn-cpp" /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"Asn.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/AsnCppD.lib"
# ADD LIB32 /nologo /out:"../../lib/ASN++FOR-ENGINED.lib"

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Release For Engine"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AsnCpp___Win32_Release_For_Engine"
# PROP BASE Intermediate_Dir "AsnCpp___Win32_Release_For_Engine"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_Release_For_Engine"
# PROP Intermediate_Dir "Win32_Release_For_Engine"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\include\asn-cpp" /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "ITS_IMPLEMENTATION" /YX"Asn.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\include\asn-cpp" /I "$(ITS_ROOT)/common/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX"Asn.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../lib/AsnCpp.lib"
# ADD LIB32 /nologo /out:"../../lib/ASN++FOR-ENGINE.lib"

!ENDIF 

# Begin Target

# Name "AsnCpp - Win32 Release"
# Name "AsnCpp - Win32 Debug"
# Name "AsnCpp - Win32 Debug For Engine"
# Name "AsnCpp - Win32 Release For Engine"
# Begin Group "Source Files"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\Asn.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnAny.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnBaseString.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnBitString.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnBoolean.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescAny.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescBaseString.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescBitString.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescBoolean.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescEnumerated.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescInteger.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescNull.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescObject.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescObjectIdentifier.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescOctetString.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescOpenType.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescReal.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescRelativeOid.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescSequenceOf.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnDescSetOf.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnEnumerated.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnError.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnException.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnInteger.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnNull.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnObject.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnObjectIdentifier.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnOctetString.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnOpenType.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnPack.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnReal.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnRelativeOid.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnSequenceOf.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnSetOf.cpp
# End Source File
# Begin Source File

SOURCE=.\AsnXml.cpp
# End Source File
# Begin Source File

SOURCE=.\BMPString.cpp
# End Source File
# Begin Source File

SOURCE=.\CHARACTER_STRING.cpp
# End Source File
# Begin Source File

SOURCE=.\Characters.cpp
# End Source File
# Begin Source File

SOURCE=.\EMBEDDED_PDV.cpp
# End Source File
# Begin Source File

SOURCE=.\EXTERNAL.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralizedTime.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralString.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicString.cpp
# End Source File
# Begin Source File

SOURCE=.\IA5String.cpp
# End Source File
# Begin Source File

SOURCE=.\ISO646String.cpp
# End Source File
# Begin Source File

SOURCE=.\Length.cpp
# End Source File
# Begin Source File

SOURCE=.\NumericString.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectDescriptor.cpp
# End Source File
# Begin Source File

SOURCE=.\Octets.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintableString.cpp
# End Source File
# Begin Source File

SOURCE=.\T61String.cpp
# End Source File
# Begin Source File

SOURCE=.\Tag.cpp
# End Source File
# Begin Source File

SOURCE=.\TeletexString.cpp
# End Source File
# Begin Source File

SOURCE=.\UniversalString.cpp
# End Source File
# Begin Source File

SOURCE=.\UTCTime.cpp
# End Source File
# Begin Source File

SOURCE=.\UTF8String.cpp
# End Source File
# Begin Source File

SOURCE=.\VideotexString.cpp
# End Source File
# Begin Source File

SOURCE=.\VisibleString.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE="..\..\include\asn-cpp\Asn.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnAny.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnBaseString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnBitString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnBoolean.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnChoice.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescAny.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescBaseString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescBitString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescBoolean.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescChoice.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescEnumerated.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescInteger.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescNull.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescObject.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescObjectIdentifier.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescOctetString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescOpenType.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescReal.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescRelativeOid.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescSequence.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescSequenceOf.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescSet.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnDescSetOf.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnEnumerated.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnError.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnException.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnInteger.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnNull.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnObject.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnObjectIdentifier.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnOctetString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnOpenType.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnPack.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnReal.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnRelativeOid.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnSequence.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnSequenceOf.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnSet.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnSetOf.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\AsnXml.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\BMPString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\CHARACTER_STRING.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\Characters.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\EMBEDDED_PDV.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\EXTERNAL.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\GeneralizedTime.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\GeneralString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\GraphicString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\IA5String.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\ISO646String.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\Length.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\NumericString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\ObjectDescriptor.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\Octets.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\PrintableString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\T61String.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\Tag.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\TeletexString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\UniversalString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\UTCTime.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\UTF8String.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\VideotexString.h"
# End Source File
# Begin Source File

SOURCE="..\..\include\asn-cpp\VisibleString.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\AsnException.exc

!IF  "$(CFG)" == "AsnCpp - Win32 Release"

# Begin Custom Build
InputPath=.\AsnException.exc

BuildCmds= \
	$(ITS_ROOT)\tools\bin\exc AsnException.exc \
	copy .\AsnException.h ..\..\include\asn-cpp \
	del .\AsnException.h \
	

".\AsnException.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\AsnException.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Debug"

USERDEP__ASNEX="AsnException.exc"	"$(ITS_ROOT)/tools/bin/exc.exe"	
# Begin Custom Build - Compiling Exc file...
InputPath=.\AsnException.exc

BuildCmds= \
	$(ITS_ROOT)\tools\bin\exc AsnException.exc \
	copy .\AsnException.h ..\..\include\asn-cpp \
	del .\AsnException.h \
	

".\AsnException.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\AsnException.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Debug For Engine"

USERDEP__ASNEX="AsnException.exc"	"$(ITS_ROOT)/tools/bin/exc.exe"	
# Begin Custom Build - Compiling Exc file...
InputPath=.\AsnException.exc

BuildCmds= \
	$(ITS_ROOT)\tools\bin\exc AsnException.exc \
	copy .\AsnException.h ..\..\include\asn-cpp \
	del .\AsnException.h \
	

".\AsnException.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\AsnException.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Release For Engine"

# Begin Custom Build
InputPath=.\AsnException.exc

BuildCmds= \
	$(ITS_ROOT)\tools\bin\exc AsnException.exc \
	copy .\AsnException.h ..\..\include\asn-cpp \
	del .\AsnException.h \
	

".\AsnException.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\AsnException.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AsnUseful.asn

!IF  "$(CFG)" == "AsnCpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 Useful types...
InputPath=.\AsnUseful.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -cppNamespace its -cppFileNamesNoPrefix -cppFileNamesMixedCase .\AsnUseful.asn \
	copy .\*.h ..\..\include\asn-cpp \
	del .\*.h \
	

"..\..\include\asn-cpp\EXTERNAL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\EXTERNAL.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GeneralizedTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeneralizedTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GraphicString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GraphicString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\IA5String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\IA5String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ISO646String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ISO646String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\NumericString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\NumericString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ObjectDescriptor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ObjectDescriptor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\PrintableString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PrintableString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\T61String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\T61String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\TeletexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TeletexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\UTCTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\UTCTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VideotexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VideotexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VisibleString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VisibleString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 Useful types...
InputPath=.\AsnUseful.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -cppNamespace its -cppFileNamesNoPrefix -cppFileNamesMixedCase .\AsnUseful.asn \
	copy .\*.h ..\..\include\asn-cpp \
	del .\*.h \
	

"..\..\include\asn-cpp\EXTERNAL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\EXTERNAL.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GeneralizedTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeneralizedTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GraphicString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GraphicString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\IA5String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\IA5String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ISO646String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ISO646String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\NumericString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\NumericString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ObjectDescriptor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ObjectDescriptor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\PrintableString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PrintableString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\T61String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\T61String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\TeletexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TeletexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\UTCTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\UTCTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VideotexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VideotexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VisibleString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VisibleString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Debug For Engine"

# Begin Custom Build - Compiling ASN.1 Useful types...
InputPath=.\AsnUseful.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -cppNamespace its -cppFileNamesNoPrefix -cppFileNamesMixedCase .\AsnUseful.asn \
	copy .\*.h ..\..\include\asn-cpp \
	del .\*.h \
	

"..\..\include\asn-cpp\EXTERNAL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\EXTERNAL.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GeneralizedTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeneralizedTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GraphicString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GraphicString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\IA5String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\IA5String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ISO646String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ISO646String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\NumericString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\NumericString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ObjectDescriptor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ObjectDescriptor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\PrintableString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PrintableString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\T61String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\T61String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\TeletexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TeletexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\UTCTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\UTCTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VideotexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VideotexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VisibleString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VisibleString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AsnCpp - Win32 Release For Engine"

# Begin Custom Build - Compiling ASN.1 Useful types...
InputPath=.\AsnUseful.asn

BuildCmds= \
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -cppNamespace its -cppFileNamesNoPrefix -cppFileNamesMixedCase .\AsnUseful.asn \
	copy .\*.h ..\..\include\asn-cpp \
	del .\*.h \
	

"..\..\include\asn-cpp\EXTERNAL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\EXTERNAL.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GeneralizedTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeneralizedTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\GraphicString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GraphicString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\IA5String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\IA5String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ISO646String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ISO646String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\NumericString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\NumericString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\ObjectDescriptor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\ObjectDescriptor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\PrintableString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PrintableString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\T61String.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\T61String.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\TeletexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TeletexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\UTCTime.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\UTCTime.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VideotexString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VideotexString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\include\asn-cpp\VisibleString.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\VisibleString.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
