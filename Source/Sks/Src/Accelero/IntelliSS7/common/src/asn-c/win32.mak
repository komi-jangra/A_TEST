#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:24:12  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:49:02  cvsadmin
# BscCs2
#
# Revision 1.1  2007/03/30 04:51:08  cvsadmin
# *** empty log message ***
#
# Revision 1.1.1.1  2006/12/22 13:34:21  cvsadmin
# Initialising sources in CVS
#
# Revision 8.2  2005/03/21 13:51:17  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:09:45  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:14:18  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:46:02  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:15  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/16 00:04:38  mmiers
#
# Begin round 4.
#
# Revision 1.3  2000/04/24 13:46:56  npopov
# Added the V2 C runtime.
#
# Revision 1.2  2000/03/28 16:20:49  npopov
# Added Id & Log macros for CVS
#
#


ASN1C_RUNTIME = $(ITS_ROOT)\common\src\asn-c
ASN1C_INCLUDE = $(ITS_ROOT)\common\include
IMPLIB   = lib
CC       = cl
LINK        = link
IMPLIB      = lib

!ifndef debug
debug = yes
!endif

!if "$(debug)" == "yes"
!else if "$(debug)" == "no"
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifndef msdebug
msdebug = yes
!endif

!if "$(msdebug)" == "yes"
RTSL = -MTd
RTDL = -MDd
!else
RTSL = -MT
RTDL = -MD
!endif

CPU = ix86
POPT = -GB
OOPT = -GF -Gi- -Gm- -GR- -GX- -Gy -Oxsy -Zl

!if "$(debug)" == "yes"
MAINFLAGS = -c -W3 -Od -Z7 $(POPT) -Ze -D_WIN32 -DWIN32 -I$(ASN1C_RUNTIME)\
		-I$(ASN1C_INCLUDE) -I$(ASN1C_INCLUDE)\asn-c
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -I$(ASN1C_RUNTIME)\
		-I$(ASN1C_INCLUDE) -I$(ASN1C_INCLUDE)\asn-c
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifdef t
MTYPE = $(t)
!else
MTYPE = d
mt = d
!endif

!if "$(MTYPE)" == "s"
CFLAGS = $(RTSL) $(MAINFLAGS)
!if "$(msdebug)" == "yes"
TYPE = d
CONLIBS = libcmtd.lib kernel32.lib
!else
TYPE =
CONLIBS = libcmt.lib kernel32.lib
!endif
!else if "$(MTYPE)" == "d"
CFLAGS = $(RTDL) $(MAINFLAGS)
!if "$(msdebug)" == "yes"
CONLIBS = msvcrtd.lib kernel32.lib
TYPE = mdd
!else
CONLIBS = msvcrt.lib kernel32.lib
TYPE = md
!endif
!else
!ERROR The macro "t" incorrectly defined!
!endif

!message Current library is asnc$(TYPE).lib & asnc_v2$(TYPE).lib...
!message

OBJECTS = asprintf.obj bit2prim.obj bit_ops.obj bitstr2strb.obj dec.obj\
		enc.obj flag2prim.obj fre.obj general.obj gtime.obj\
		int2strb.obj isobject.obj num2prim.obj obj2prim.obj\
		ode2oid.obj oid2ode.obj oid_cmp.obj oid_cpy.obj oid_free.obj\
		pe2ps.obj pe2qb_f.obj pe2ssdu.obj pe_alloc.obj pe_cpy.obj\
		pe_error.obj pe_free.obj prim2bit.obj prim2flag.obj\
		prim2num.obj prim2oid.obj prim2qb.obj prim2real.obj\
		prim2set.obj prim2str.obj prim2time.obj prnt.obj ps2pe.obj\
		ps_alloc.obj ps_error.obj ps_flush.obj ps_free.obj\
		ps_get_abs.obj ps_io.obj ps_prime.obj qb2pe.obj qb2prim.obj\
		qb2str.obj qb_free.obj qb_pullup.obj qbuf2pe.obj qbuf2ps.obj\
		rcmd_srch.obj real2prim.obj seq_add.obj seq_addon.obj\
		set_add.obj set_addon.obj set_find.obj smalloc.obj\
		sprintoid.obj ssdu2pe.obj std2ps.obj str2elem.obj str2oid.obj\
		str2pe.obj str2prim.obj str2ps.obj str2qb.obj str2vec.obj\
		strb2bitstr.obj strb2int.obj time2prim.obj time2str.obj\
		tm2ut.obj ut2tm.obj util.obj vprint.obj univ_tables.obj

OBJECTS_V2 = asn_any.obj asn_assertion.obj asn_bit_string.obj asn_boolean.obj\
		asn_choice.obj asn_common.obj asn_desc_any.obj\
		asn_desc_bit_string.obj asn_desc_boolean.obj asn_desc_choice.obj\
		asn_desc_enumerated.obj asn_desc_integer.obj asn_desc_null.obj\
		asn_desc_object.obj asn_desc_object_identifier.obj\
		asn_desc_octet_string.obj asn_desc_real.obj asn_desc_sequence.obj\
		asn_desc_sequence_of.obj asn_desc_set.obj asn_desc_set_of.obj\
		asn_enumerated.obj asn_error.obj asn_external_c.obj\
		asn_general_string_c.obj asn_generalized_time_c.obj\
		asn_graphic_string_c.obj asn_ia5_string_c.obj\
		asn_integer.obj asn_iso646_string_c.obj asn_its_feature_class_c.obj\
		asn_length.obj asn_linked_list.obj asn_null.obj\
		asn_numeric_string_c.obj asn_object.obj asn_object_descriptor_c.obj\
		asn_object_identifier.obj asn_octet_string.obj asn_octets.obj\
		asn_printable_string_c.obj asn_real.obj asn_sequence.obj\
		asn_sequence_of.obj asn_set.obj asn_set_of.obj\
		asn_t61_string_c.obj asn_tag.obj asn_teletex_string_c.obj\
		asn_utc_time_c.obj asn_videotex_string_c.obj\
		asn_visible_string_c.obj


.c.obj::
	$(CC) $(CFLAGS) $<


all:	univ.ph\
	asnc$(TYPE).lib\
	asnc_v2$(TYPE).lib


asnc$(TYPE).lib: $(OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(OBJECTS)
		mv $@ $(ITS_ROOT)\runtime

asnc_v2$(TYPE).lib: $(OBJECTS_V2)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(OBJECTS_V2)
		mv $@ $(ITS_ROOT)\runtime

univ.ph: univ.asn
		sh -c "$(ITS_ROOT)/tools/bin/asnc.exe -A -a -f univ.asn"
		mv univ-types.h ..\..\include\asn-c

asn_external_c.c:
		sh -c "$(ITS_ROOT)/tools/bin/asncc_v2.exe -c -cModuleName ASN  ../asn-cpp/AsnUseful.asn"
		mv asn_*.h ..\..\include\asn-c


clean:
	@if exist *.obj           rm *.obj
	@if exist *.pdb           rm *.pdb
	@if exist *.rbj           rm *.rbj
	@if exist *.res           rm *.res
	@if exist *.ph            rm *.ph
	@if exist asn_*_c.c       rm asn_*_c.c
	@if exist $(ITS_ROOT)/common/include/asn-c/asn_*_c.h rm $(ITS_ROOT)/common/include/asn-c/asn_*_c.h
	@if exist $(ITS_ROOT)/runtime/asnc$(TYPE).lib        rm $(ITS_ROOT)/runtime/asnc$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/asnc_v2$(TYPE).lib     rm $(ITS_ROOT)/runtime/asnc_v2$(TYPE).lib
	@echo Done

