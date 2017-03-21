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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CPPOBJS=    parse.o				\
            parse_aggregate.o	\
			parse_choice.o		\
			parse_construct.o	\
			parse_exception.o	\
			parse_keyword.o		\
			parse_parser.o		\
			parse_production.o	\
			parse_repetition.o	\
			parse_scanner.o		\
			parse_terminal.o	\
			parse_token.o		\
			parse_tokenizer.o	\
			parse_utilities.o
         
CXXFLAGS := $(CXXFLAGS) -I../../include/parse

all: ../../lib/libPARSE++$(DBGSUFFIX).a

clean:
	$(RM) *.o ../../lib/libPARSE++$(DBGSUFFIX).a .depend


../../lib/libPARSE++$(DBGSUFFIX).a: $(CPPOBJS)
	$(CXXAR) $(CXXARFLAGS) ../../lib/libPARSE++$(DBGSUFFIX).a $(CPPOBJS) 


#
# get the rules
#
include $(ITS_ROOT)/config.rules
