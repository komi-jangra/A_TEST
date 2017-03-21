############################################################################
#                                                                          #
#     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    #
#             Manufactured in the United States of America.                #
#       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       #
#                                                                          #
#   This product and related documentation is protected by copyright and   #
#   distributed under licenses restricting its use, copying, distribution  #
#   and decompilation.  No part of this product or related documentation   #
#   may be reproduced in any form by any means without prior written       #
#   authorization of IntelliNet Technologies and its licensors, if any.    #
#                                                                          #
#   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      #
#   government is subject to restrictions as set forth in subparagraph     #
#   (c)(1)(ii) of the Rights in Technical Data and Computer Software       #
#   clause at DFARS 252.227-7013 and FAR 52.227-19.                        #
#                                                                          #
############################################################################
#                                                                          #
# CONTRACT: INTERNAL                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:10  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:00  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1  2007/03/30 04:48:57  cvsadmin
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 1.1.1.1  2006/12/22 13:34:16  cvsadmin
# LOG: Initialising sources in CVS
# LOG:
# LOG: Revision 8.2  2005/03/21 13:51:09  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:44  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:01  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
# LOG: Begin PR5
# LOG:
# LOG: Revision 3.2  2001/03/29 17:08:44  mmiers
# LOG: Missing entry points detected by correct engine build.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:04:05  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.5  2000/04/13 21:28:23  mmiers
# LOG:
# LOG:
# LOG: More changes from Saritel integration.
# LOG:
# LOG: Revision 2.4  2000/03/29 16:44:24  hdivoux
# LOG: Continue port to Unix (Solaris).
# LOG:
# LOG: Revision 2.3  2000/03/29 15:14:30  hdivoux
# LOG: Work in progress.
# LOG:
# LOG: Revision 2.2  2000/03/28 22:11:35  hdivoux
# LOG:
# LOG: Begin port to Unix.
# LOG:
# LOG: Revision 2.1  2000/03/28 20:19:27  hdivoux
# LOG: Added AsnC V2 target.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:26:19  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.8  1999/07/02 01:24:05  mmiers
# LOG:
# LOG:
# LOG: Delete generated files.
# LOG:
# LOG: Revision 1.7  1999/06/01 17:24:03  labuser
# LOG:
# LOG:
# LOG: Ditch the Berkeley byte functions.
# LOG:
# LOG: Revision 1.6  1999/04/01 17:31:18  mmiers
# LOG:
# LOG:
# LOG: Add oid_cmp back into this lib.
# LOG:
# LOG: Revision 1.5  1998/11/18 00:23:43  jrao
# LOG: Changed Library Suffix (LIBSUFFIX) to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.4  1998/11/17 23:57:42  jrao
# LOG: Changed Library Suffix (DBGSUFFIX) wherever it occured to Debug Suffix (DBGSUFFIX)
# LOG:
# LOG: Revision 1.3  1998/11/17 16:43:35  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG:
# LOG: Revision 1.2  1998/10/27 16:35:07  mmiers
# LOG: Start removing old pepsy dirs.
# LOG:
# LOG: Revision 1.1  1998/10/27 01:14:58  mmiers
# LOG: Make a new library, combining all the old ISODE stuff under one
# LOG: roof.  Use one, you have to use them all.
# LOG:
#
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

OBJS= bit2prim.o       bitstr2strb.o         flag2prim.o     int2strb.o \
      num2prim.o       obj2prim.o            ode2oid.o       oid2ode.o \
      pe2ps.o          pe2qb_f.o             pe2ssdu.o       prim2bit.o \
      prim2flag.o      prim2num.o            prim2oid.o      prim2qb.o \
      prim2real.o      prim2set.o            prim2str.o      prim2time.o \
      ps2pe.o          qb2pe.o               qb2prim.o       qb2str.o \
      qbuf2pe.o        qbuf2ps.o             real2prim.o     ssdu2pe.o \
      std2ps.o         str2oid.o             str2pe.o        str2prim.o \
      str2ps.o         str2qb.o              strb2bitstr.o   strb2int.o \
      time2prim.o      time2str.o            tm2ut.o         ut2tm.o \
      pe_alloc.o       seq_add.o             seq_addon.o     set_add.o \
      set_addon.o      oid_free.o            pe_free.o       ps_free.o \
      qb_free.o        pe_error.o            bit_ops.o       ps_alloc.o \
      ps_flush.o       ps_io.o               ps_prime.o      ps_get_abs.o \
      set_find.o       pe_cpy.o              oid_cpy.o       sprintoid.o \
      ps_error.o       gtime.o               isobject.o      qb_pullup.o \
      oid_cmp.o        UNIV_tables.o         rcmd_srch.o     asprintf.o \
      general.o        smalloc.o             str2elem.o      str2vec.o \
      enc.o            dec.o                 prnt.o          fre.o \
      util.o           vprint.o              qb_cpy.o        objectbyname.o \
      objectbyoid.o

CFLAGS := $(CFLAGS) -DFunctionPrototypes -I../../include/asn-c

all: ../../lib/libASN$(DBGSUFFIX).a

../../lib/libASN$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../lib/libASN$(DBGSUFFIX).a $(OBJS)

UNIV_tables.c: univ.asn
	$(ASNC) $(ASNCFLAGS) -h univ.asn
	cp UNIV-types.h ../../include/asn-c

clean:
	$(RM) -r $(OBJS) ../../lib/libASN$(DBGSUFFIX).a \
		UNIV_tables.c *.err .depend


################################################################################
#
# AsnC V2 Begin.
#

OBJS_V2 =   asn_external_c.o \
            asn_any.o \
            asn_assertion.o \
            asn_bit_string.o \
            asn_boolean.o \
            asn_choice.o \
            asn_common.o \
            asn_desc_any.o \
            asn_desc_bit_string.o \
            asn_desc_boolean.o \
            asn_desc_choice.o \
            asn_desc_enumerated.o \
            asn_desc_integer.o \
            asn_desc_null.o \
            asn_desc_object.o \
            asn_desc_object_identifier.o \
            asn_desc_octet_string.o \
            asn_desc_real.o \
            asn_desc_sequence.o \
            asn_desc_sequence_of.o \
            asn_desc_set.o \
            asn_desc_set_of.o \
            asn_enumerated.o \
            asn_error.o \
            asn_general_string_c.o \
            asn_generalized_time_c.o \
            asn_graphic_string_c.o \
            asn_ia5_string_c.o \
            asn_integer.o \
            asn_iso646_string_c.o \
            asn_its_feature_class_c.o \
            asn_length.o \
            asn_linked_list.o \
            asn_null.o \
            asn_numeric_string_c.o \
            asn_object.o \
            asn_object_descriptor_c.o \
            asn_object_identifier.o \
            asn_octet_string.o \
            asn_octets.o \
            asn_printable_string_c.o \
            asn_real.o \
            asn_sequence.o \
            asn_sequence_of.o \
            asn_set.o \
            asn_set_of.o \
            asn_t61_string_c.o \
            asn_tag.o \
            asn_teletex_string_c.o \
            asn_utc_time_c.o \
            asn_videotex_string_c.o \
            asn_visible_string_c.o

SRCSAUX_V2 = asn_external_c.c \
            asn_general_string_c.c \
            asn_generalized_time_c.c \
            asn_graphic_string_c.c \
            asn_ia5_string_c.c \
            asn_iso646_string_c.c \
            asn_its_feature_class_c.c \
            asn_numeric_string_c.c \
            asn_object_descriptor_c.c \
            asn_printable_string_c.c \
            asn_t61_string_c.c \
            asn_teletex_string_c.c \
            asn_utc_time_c.c \
            asn_videotex_string_c.c \
            asn_visible_string_c.c


all_v2: ../../lib/libASN_V2$(DBGSUFFIX).a

../../lib/libASN_V2$(DBGSUFFIX).a: $(OBJS_V2)
	$(AR) $(ARFLAGS) ../../lib/libASN_V2$(DBGSUFFIX).a $(OBJS_V2)


$(SRCSAUX_V2): ../asn-cpp/AsnUseful.asn
	$(ITS_ROOT)/tools/bin/asncc_v2$(DBGSUFFIX) -c -cModuleName ASN \
        ../asn-cpp/AsnUseful.asn
	$(MV) -f asn_*.h ../../include/asn-c

clean_v2:
	$(RM) -r $(OBJS_V2) ../../lib/libASN_V2$(DBGSUFFIX).a \
        $(SRCSAUX_V2) *.err .depend

#
# AsnC V2 End.
#
################################################################################



#
# get the rules
#
include $(ITS_ROOT)/config.rules
