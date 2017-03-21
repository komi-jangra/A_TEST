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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:29 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:23:59  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:13:34  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:52:42  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.5  2005/03/21 13:50:39  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.2.4.1.8.1.6.2  2005/01/31 09:27:29  dsatish
# LOG:  ANSI over TTC, ANSI over PRC split stack changes merged.
# LOG:
# LOG: Revision 7.2.4.1.8.1.6.1  2004/12/16 01:52:54  randresol
# LOG: Add JAPAN variant implementation
# LOG:
# LOG: Revision 7.2.4.1.8.1  2004/09/21 09:48:54  mmanikandan
# LOG: Propagating pprint from current.
# LOG:
# LOG: Revision 7.2.4.1  2003/02/14 05:53:57  labuser
# LOG: Changes for Hybrid - adutta
# LOG:
# LOG: Revision 7.2  2002/10/28 19:52:31  mmiers
# LOG: Wrong make include
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:34  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.4  2002/08/23 15:44:12  omayor
# LOG: Wrong name for libPRC-TCAP.
# LOG:
# LOG: Revision 6.3  2002/08/22 21:15:46  omayor
# LOG: Typo in PRC libs.
# LOG:
# LOG: Revision 6.2  2002/07/05 16:03:15  yranade
# LOG: Added PRC libs.
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.6  2002/02/13 22:54:46  mmiers
# LOG: Add variant lib correctly
# LOG:
# LOG: Revision 1.5  2002/02/13 22:02:51  mmiers
# LOG: Add ISUP variant lib to build.
# LOG:
# LOG: Revision 1.4  2002/01/18 22:42:41  mmiers
# LOG: Default target when SCCP protocol not defined.
# LOG:
# LOG: Revision 1.3  2002/01/18 22:40:46  mmiers
# LOG: Get the clean step right.
# LOG:
# LOG: Revision 1.2  2002/01/18 22:36:57  mmiers
# LOG: Include the right config
# LOG:
# LOG: Revision 1.1  2002/01/10 16:51:35  mmiers
# LOG: Finish the transport refcounting effort.  Move vframe from
# LOG: vendors to here.
# LOG:
# LOG: Revision 1.3  2001/12/19 18:03:02  mmiers
# LOG: Adax testing on Solaris revealed several build flaws.
# LOG:
# LOG: Revision 1.2  2001/12/18 19:17:47  mmiers
# LOG: Build on solaris
# LOG:
# LOG: Revision 1.1  2001/12/17 00:15:35  mmiers
# LOG: Get this building on UNIX
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I../include \
	  -I$(ITS_ROOT)/MTP2/include -I$(ITS_ROOT)/MTP3/include \
	  -I$(ITS_ROOT)/SNMM/include -I$(ITS_ROOT)/SLTM/include \
	  -I$(ITS_ROOT)/ISUP/include -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/common/include

SOLIBS= $(ITS_ROOT)/SLTM/lib/libANSI-SLTM$(DBGSUFFIX).a \
	$(ITS_ROOT)/SLTM/lib/libCCITT-SLTM$(DBGSUFFIX).a \
	$(ITS_ROOT)/SLTM/lib/libPRC-SLTM$(DBGSUFFIX).a \
	$(ITS_ROOT)/SLTM/lib/libTTC-SLTM$(DBGSUFFIX).a \
	$(ITS_ROOT)/SNMM/lib/libANSI-SNMM$(DBGSUFFIX).a \
	$(ITS_ROOT)/SNMM/lib/libCCITT-SNMM$(DBGSUFFIX).a \
	$(ITS_ROOT)/SNMM/lib/libPRC-SNMM$(DBGSUFFIX).a \
	$(ITS_ROOT)/SNMM/lib/libTTC-SNMM$(DBGSUFFIX).a \
	$(ITS_ROOT)/MTP2/lib/libANSI-MTP2$(DBGSUFFIX).a \
	$(ITS_ROOT)/MTP2/lib/libCCITT-MTP2$(DBGSUFFIX).a \
	$(ITS_ROOT)/MTP2/lib/libPRC-MTP2$(DBGSUFFIX).a \
	$(ITS_ROOT)/MTP3/lib/libANSI-MTP3$(DBGSUFFIX).a \
	$(ITS_ROOT)/MTP3/lib/libCCITT-MTP3$(DBGSUFFIX).a \
	$(ITS_ROOT)/MTP3/lib/libPRC-MTP3$(DBGSUFFIX).a \
	$(ITS_ROOT)/MTP3/lib/libTTC-MTP3$(DBGSUFFIX).a \
	$(ITS_ROOT)/ISUP/lib/libANSI-ISUP$(DBGSUFFIX).a \
	$(ITS_ROOT)/ISUP/lib/libCCITT-ISUP$(DBGSUFFIX).a \
	$(ITS_ROOT)/ISUP/lib/libISUP_VARIANTS$(DBGSUFFIX).a \
	$(ITS_ROOT)/SCCP/lib/libANSI-SCCP$(DBGSUFFIX).a \
	$(ITS_ROOT)/SCCP/lib/libCCITT-SCCP$(DBGSUFFIX).a \
	$(ITS_ROOT)/SCCP/lib/libPRC-SCCP$(DBGSUFFIX).a \
	$(ITS_ROOT)/SCCP/lib/libTTC-SCCP$(DBGSUFFIX).a \
	$(ITS_ROOT)/common/lib/libASN$(DBGSUFFIX).a
STDLIBS=$(ITS_ROOT)/TCAP/lib/libANSI-TCAP$(DBGSUFFIX).a \
	$(ITS_ROOT)/TCAP/lib/libCCITT-TCAP$(DBGSUFFIX).a \
	$(ITS_ROOT)/TCAP/lib/libPRC-TCAP$(DBGSUFFIX).a \
	$(ITS_ROOT)/TCAP/lib/libTTC-TCAP$(DBGSUFFIX).a 
AOCLIBS=$(ITS_ROOT)/TCAP/lib/libANSI-CCITT-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libCCITT-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libPRC-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libTTC-TCAP$(DBGSUFFIX).a
COALIBS=$(ITS_ROOT)/TCAP/lib/libCCITT-ANSI-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libANSI-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libPRC-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libTTC-TCAP$(DBGSUFFIX).a
AOTLIBS=$(ITS_ROOT)/TCAP/lib/libANSI-TTC-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libCCITT-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libPRC-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libTTC-TCAP$(DBGSUFFIX).a
AOPLIBS=$(ITS_ROOT)/TCAP/lib/libANSI-PRC-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libCCITT-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libPRC-TCAP$(DBGSUFFIX).a \
        $(ITS_ROOT)/TCAP/lib/libTTC-TCAP$(DBGSUFFIX).a


OBJS= vframe.o

#
# SCCP type
#
ifeq ($(SCCP_PROT),$(PROTOCOL))

ifeq ($(PROTOCOL),ANSI)
all: ../../common/lib/libANSI-VFrame$(DBGSUFFIX).a \
		../../common/lib/libANSI-VFrame$(DBGSUFFIX).so
else
all: ../../common/lib/libCCITT-VFrame$(DBGSUFFIX).a \
     ../../common/lib/libCCITT-VFrame$(DBGSUFFIX).so
endif

else
ifeq ($(SCCP_PROT),ANSI)
all: ../../common/lib/libCOAVFrame$(DBGSUFFIX).a \
     ../../common/lib/libCOAVFrame$(DBGSUFFIX).so
endif
ifeq ($(SCCP_PROT),CCITT)
all: ../../common/lib/libAOCVFrame$(DBGSUFFIX).a \
     ../../common/lib/libAOCVFrame$(DBGSUFFIX).so
endif
ifeq ($(SCCP_PROT),TTC)
all: ../../common/lib/libAOTVFrame$(DBGSUFFIX).a \
     ../../common/lib/libAOTVFrame$(DBGSUFFIX).so
endif
ifeq ($(SCCP_PROT),PRC)
all: ../../common/lib/libAOPVFrame$(DBGSUFFIX).a \
     ../../common/lib/libAOPVFrame$(DBGSUFFIX).so
endif
endif

ifeq ($(PROTOCOL),ANSI)
other: ../../common/lib/libANSI-VFrame$(DBGSUFFIX).a \
       ../../common/lib/libANSI-VFrame$(DBGSUFFIX).so

../../common/lib/libANSI-VFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libANSI-VFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libANSI-VFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libANSI-VFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(STDLIBS) $(SHAREDARFLAGSEND)

../../common/lib/libCOAVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libCOAVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libCOAVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libCOAVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(COALIBS) $(SHAREDARFLAGSEND)

../../common/lib/libAOCVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libAOCVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libAOCVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libAOCVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(AOCLIBS) $(SHAREDARFLAGSEND)

../../common/lib/libAOTVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libAOTVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libAOTVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libAOTVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(AOTLIBS) $(SHAREDARFLAGSEND)

../../common/lib/libAOPVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libAOPVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libAOPVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libAOPVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(AOPLIBS) $(SHAREDARFLAGSEND)

else

other: ../../common/lib/libCCITT-VFrame$(DBGSUFFIX).a \
       ../../common/lib/libCCITT-VFrame$(DBGSUFFIX).so

../../common/lib/libCCITT-VFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libCCITT-VFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libCCITT-VFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libCCITT-VFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(STDLIBS) $(SHAREDARFLAGSEND)

../../common/lib/libCOAVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libCOAVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libCOAVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libCOAVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(COALIBS) $(SHAREDARFLAGSEND)

../../common/lib/libAOCVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libAOCVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libAOCVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libAOCVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(AOCLIBS) $(SHAREDARFLAGSEND)

../../common/lib/libAOTVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libAOTVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libAOTVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libAOTVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(AOTLIBS) $(SHAREDARFLAGSEND)

../../common/lib/libAOPVFrame$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../../common/lib/libAOPVFrame$(DBGSUFFIX).a $(OBJS)

../../common/lib/libAOPVFrame$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../common/lib/libAOPVFrame$(DBGSUFFIX).so \
                $(OBJS) $(SOLIBS) $(AOPLIBS) $(SHAREDARFLAGSEND)

endif


ifeq ($(PROTOCOL),ANSI)

clean:
	$(RM) $(OBJS) \
		../../common/lib/libANSI-VFrame$(DBGSUFFIX).a \
		../../common/lib/libANSI-VFrame$(DBGSUFFIX).so *.o
else
clean:
	$(RM) $(OBJS) \
		../../common/lib/libCCITT-VFrame$(DBGSUFFIX).a \
		../../common/lib/libCCITT-VFrame$(DBGSUFFIX).so *.o

endif

#
# get the rules
#
include $(ITS_ROOT)/config.rules
