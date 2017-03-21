#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#

#
# $Id: bw32.mak,v 1.1.1.1 2007-10-08 11:11:10 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:12:51  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:51:00  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:49:06  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:08:30  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:13:16  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:45:05  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:52:59  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/15 23:55:35  mmiers
#
# Begin round 4.
#
# Revision 1.8  2000/06/26 20:30:00  npopov
# Added CAMEL as a build target.
#
# Revision 1.7  2000/04/24 13:48:38  npopov
# Added rules for the ASN1/C++ V2 compiler.
#
# Revision 1.6  2000/04/12 16:19:57  npopov
# Added a target to build GSMMAP regression test libraries.
#
# Revision 1.5  2000/04/03 14:43:12  npopov
# Fixed some problems with cleanup and making the runtime directory
#
# Revision 1.4  2000/03/31 16:22:19  npopov
# Added a target for update
#
# Revision 1.3  2000/03/31 15:20:16  npopov
# Added a target to build runtime only
#
# Revision 1.2  2000/03/28 16:18:26  npopov
# Added Id & Log macros for CVS
#
#


!ifndef debug
debug = yes
!endif

!ifndef msdebug
msdebug = yes
!endif

!ifndef clean
clean = yes
!endif

!ifndef ms
ms = no
!endif



all:	CreateRuntimeDirectory\
	ASN1CCompiler \
	ASN1C++Compiler\
	ASN1C++V2Compiler \
	EXCcompiler\
	ASN1CRuntime\
	ASN1C++Runtime\
	ITSCore\
	Support \
#	DBC\
#	MsgFileDll\
	INAPx\
	IS41x\
	GSMMAPx\
	MTP3x\
	SCCPx\
	TCAPx\
	CAMELx\
	VENDORx



RuntimeOnly: CreateRuntimeDirectory\
	ASN1CRuntime\
	ASN1C++Runtime\
	ITSCore\
	Support\
	INAPx\
	IS41x\
	MTP3x\
	SCCPx\
	TCAPx\
	VENDORx

Update:
	cd $(ITS_ROOT)
	cd ..
	-cvs update IntelliSS7
	-cvs update vendors

CreateRuntimeDirectory:
	cd $(ITS_ROOT)
	-@mkdir runtime

ASN1CCompiler:
	cd $(ITS_ROOT)\tools\src\asnc
	@echo Building the ASN.1/C compiler...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the ASN.1/C compiler.
	@echo.

ASN1C++Compiler:
	cd $(ITS_ROOT)\tools\src\asncc
	@echo Building the ASN.1/C++ compiler...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the ASN.1/C++ compiler.
	@echo.

ASN1C++V2Compiler:
	cd $(ITS_ROOT)\tools\src\asncc_v2
	@echo Building the ASN.1/C++ V2 compiler...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the ASN.1/C++ V2 compiler.
	@echo.

EXCcompiler:
	cd $(ITS_ROOT)\tools\src\exc
	@echo Building the exception compiler...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the exception compiler.
	@echo.

ASN1CRuntime:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\common\src\asn-c
	@echo Building the ASN.1/C runtime...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the ASN.1/C runtime.
	@echo.

ASN1C++Runtime:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\common\src\asn-cpp
	@echo Building the ASN.1/C++ runtime...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the ASN.1/C++ runtime.
	@echo.

ITSCore:
	cd $(ITS_ROOT)
	--@mkdir runtime
	cd $(ITS_ROOT)\common\src\itscore
	@echo Building the ASN.1/C++ runtime...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the ITS core.
	@echo.

Support:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\common\src\support
	@echo Building the support code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the support code.
	@echo.

DBC:
	cd $(ITS_ROOT)\common\src\dbc
	@echo Building the DBC code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the DBC code.
	@echo.

MsgFileDll:
	cd $(ITS_ROOT)\common\src\msgfiledll
	@echo Building the message file DLL...
	@echo.
!if "$(clean)" == "yes"
	nmake -f dll.mak clean
!endif
	nmake -f dll.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the message file DLL.
	@echo.

INAPx:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\INAP\src
	@echo Building the INAP code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the INAP code.
	@echo.

IS41x:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\IS41\src
	@echo Building the IS41 code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the IS41 code.
	@echo.


GSMMAPx:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\GSMMAP\src
	@echo Building the GSMMAP code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the GSMMAP code.
	@echo.

MTP3x:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\mtp3\src
	@echo Building the MTP3 code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the MTP3 code.
	@echo.

SCCPx:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\sccp\src
	@echo Building the SCCP code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the SCCP code.
	@echo.

TCAPx:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\tcap\src
	@echo Building the TCAP code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the TCAP code.
	@echo.

CAMELx:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(ITS_ROOT)\CAMEL\src
	@echo Building the CAMEL code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the CAMEL code.
	@echo.

VENDORx:
	cd $(ITS_ROOT)
	-@mkdir runtime
	cd $(VENDOR_ROOT)\IntelliNet\src
	@echo Building the IntelliNet vendor code...
	@echo.
!if "$(clean)" == "yes"
	nmake -f win32.mak clean
!endif
	nmake -f win32.mak debug=$(debug) msdebug=$(msdebug)
	@echo.
	@echo Done with the IntelliNet vendor code.
	@echo.





clean:
	@cd $(ITS_ROOT)\tools\src\asnc
	@echo Cleaning $(ITS_ROOT)\tools\src\asnc...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\tools\src\asnc.

	@cd $(ITS_ROOT)\tools\src\asncc
	@echo Cleaning $(ITS_ROOT)\tools\src\asncc...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\tools\src\asncc.

	@cd $(ITS_ROOT)\tools\src\asncc_v2
	@echo Cleaning $(ITS_ROOT)\tools\src\asncc_v2...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\tools\src\asncc_v2.

	@cd $(ITS_ROOT)\tools\src\exc
	@echo Cleaning $(ITS_ROOT)\tools\src\exc...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\tools\src\exc.

	@cd $(ITS_ROOT)\common\src\asn-c
	@echo Cleaning $(ITS_ROOT)\common\src\asn-c...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\common\src\asn-c.

	@cd $(ITS_ROOT)\common\src\asn-cpp
	@echo Cleaning $(ITS_ROOT)\common\src\asn-cpp...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\common\src\asn-cpp.

	@cd $(ITS_ROOT)\common\src\itscore
	@echo Cleaning $(ITS_ROOT)\common\src\itscore...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\common\src\itscore.

	@cd $(ITS_ROOT)\common\src\support
	@echo Cleaning $(ITS_ROOT)\common\src\support...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\common\src\support.

#	@cd $(ITS_ROOT)\common\src\dbc
#	@echo Cleaning $(ITS_ROOT)\common\src\dbc...
#	@nmake -f win32.mak clean
#	@echo Done with $(ITS_ROOT)\common\src\dbc.

#	@cd $(ITS_ROOT)\common\src\msgfiledll
#	@echo Cleaning $(ITS_ROOT)\common\src\msgfiledll...
#	@nmake -f dll.mak clean
#	@echo Done with $(ITS_ROOT)\common\src\msgfiledll.

	@cd $(ITS_ROOT)\INAP\src
	@echo Cleaning $(ITS_ROOT)\inap\src\...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\inap\src.

	@cd $(ITS_ROOT)\IS41\src
	@echo Cleaning $(ITS_ROOT)\IS41\src\...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\IS41\src.

	@cd $(ITS_ROOT)\GSMMAP\src
	@echo Cleaning $(ITS_ROOT)\GSMMAP\src\...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\GSMMAP\src.

	@cd $(ITS_ROOT)\mtp3\src
	@echo Cleaning $(ITS_ROOT)\mtp3\src\...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\mtp3\src.

	@cd $(ITS_ROOT)\sccp\src
	@echo Cleaning $(ITS_ROOT)\sccp\src\...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\sccp\src.

	@cd $(ITS_ROOT)\tcap\src
	@echo Cleaning $(ITS_ROOT)\tcap\src\...
	@nmake -f win32.mak clean
	@echo Done with $(ITS_ROOT)\tcap\src.

	@cd $(VENDOR_ROOT)\IntelliNet\src
	@echo Cleaning $(VENDOR_ROOT)\IntelliNet\src\...
	@nmake -f win32.mak clean
	@echo Done with $(VENDOR_ROOT)\IntelliNet\src.

