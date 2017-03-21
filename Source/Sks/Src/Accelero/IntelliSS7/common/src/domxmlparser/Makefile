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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:50 bsccs2 Exp $
#  LOG: $Log: not supported by cvs2svn $
#  LOG: Revision 1.1.1.1  2007/10/04 13:24:21  bsccs2
#  LOG: init tree
#  LOG:
#  LOG: Revision 1.1.1.1  2007/08/03 06:49:08  cvsadmin
#  LOG: BscCs2
#  LOG:
#  LOG: Revision 1.1.1.1  2007/03/08 15:14:08  cvsadmin
#  LOG: BSC project
#  LOG:
#  LOG: Revision 9.1  2005/03/23 12:53:15  cvsadmin
#  LOG: Begin PR6.5
#  LOG:
#  LOG: Revision 1.3  2005/03/21 13:51:31  cvsadmin
#  LOG: PR6.4.2 Source Propagated to Current
#  LOG:
#  LOG: Revision 1.1.4.1  2003/04/24 07:13:33  yranade
#  LOG: Adding libxml2: DOM XML Parser to CVS.
#  LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

COBJS=SAX.o entities.o encoding.o error.o parserInternals.o parser.o \
	tree.o hash.o list.o xmlIO.o xmlmemory.o uri.o valid.o xlink.o \
	HTMLparser.o HTMLtree.o debugXML.o xpath.o xpointer.o xinclude.o \
	nanohttp.o nanoftp.o DOCBparser.o catalog.o globals.o threads.o \
	c14n.o xmlregexp.o xmlschemas.o xmlschemastypes.o xmlunicode.o \
	xmlreader.o relaxng.o

CFLAGS:=-I$(ITS_ROOT)/common/include/domxmlparser

all: ../../lib/libXML2$(DBGSUFFIX).a ../../lib/libXML2$(DBGSUFFIX).so

../../lib/libXML2$(DBGSUFFIX).a: $(COBJS)
	$(AR) $(ARFLAGS) ../../lib/libXML2$(DBGSUFFIX).a $(COBJS)

../../lib/libXML2$(DBGSUFFIX).so: $(COBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../../lib/libXML2$(DBGSUFFIX).so $(COBJS)

clean:
	$(RM) $(COBJS) .depend ../../lib/libXML2$(DBGSUFFIX).a ../../lib/libXML2$(DBGSUFFIX).so

#
# get the rules
#
include $(ITS_ROOT)/config.rules
