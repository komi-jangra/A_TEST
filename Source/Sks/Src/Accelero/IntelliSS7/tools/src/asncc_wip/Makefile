############################################################################
#                                                                          #
#     Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

LDG=$(LD)

ifeq ($(PLATFORM),mvlppc)
CCG=$(CC)
CXXG=$(CXX)
CC := gcc -D_GNU_SOURCE -pipe -Wno-deprecated
CXX := g++ -D_GNU_SOURCE -pipe -Wno-deprecated
LDG=g++
endif


CXXOBJS =   asncc_parser.$(OEXT)                        \
            asncc_lexer.$(OEXT)                         \
            asncc_assertion.$(OEXT)                     \
            asncc_ast.$(OEXT)                           \
            asncc_check_semantic_visitor.$(OEXT)        \
            asncc_components_of_visitor.$(OEXT)         \
            asncc_evaluate_visitor.$(OEXT)              \
            asncc_generate_cpp_visitor.$(OEXT)          \
            asncc_generate_cpp_xml_doc_visitor.$(OEXT)  \
            asncc_generate_c_visitor.$(OEXT)            \
            asncc_generate_c_xml_doc_visitor.$(OEXT)    \
            asncc_link_visitor.$(OEXT)                  \
            asncc_main.$(OEXT)                          \
            asncc_normalize_visitor.$(OEXT)             \
            asncc_print_visitor.$(OEXT)                 \
            asncc_recursive_visitor.$(OEXT)             \
            asncc_tag.$(OEXT)                           \
            asncc_util.$(OEXT)                          \
            asncc_visitor.$(OEXT)                       \
	    asncc_merge_visitor.$(OEXT)                 \
            asncc_command_file.$(OEXT)                  \
            asncc_command_interpreter.$(OEXT)


CFLAGS := $(CFLAGS)
CXXFLAGS := $(CXXFLAGS) -DYY_NEVER_INTERACTIVE -DDONT_INCLUDE_ITS_EVENT \
		-DYY_USE_PROTOS -DFLEX -DC_FLEX -DYYDEBUG

all: ../../bin/asncc_wip$(DBGSUFFIX)

../../bin/asncc_wip$(DBGSUFFIX): asncc_parser.h $(CXXOBJS)
	$(LDG) -o   ../../bin/asncc_wip$(DBGSUFFIX) $(LDFLAGS) $(CXXOBJS)

ifeq ($(PLATFORM),mvlppc)
CC := $(CCG)
CXX := $(CXXG)
endif


asncc_lexer.cpp: asn1.lex
	$(LEX) -oasncc_lexer.cpp asn1.lex


asncc_parser.cpp asncc_parser.h: asn1.yacc
	$(YACC) asn1.yacc -t -v -d -o asncc_parser.cpp
	mv asncc_parser.cpp.h asncc_parser.h

clean:
	$(RM) *.$(OEXT) ../../bin/asncc_wip$(DBGSUFFIX) ../../bin/asncc_wip \
		$(OBJS) $(CXXOBJS) asncc_lexer.cpp asncc_parser.h asncc_parser.cpp \
		 *.output *.acts *.tmp y.tab.c y.tab.h *.debug .depend

#
# get the rules
#
include $(ITS_ROOT)/config.rules
