############################################################################
#                                                                          #
#     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:53:30  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:51:51  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.2  2002/11/14 20:41:59  mmiers
# LOG: New tools
# LOG:
# LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.3  2002/08/22 16:22:44  pmandal
# LOG: undo changes
# LOG:
# LOG: Revision 6.2  2002/08/20 15:53:04  mmiers
# LOG: Update the clean target for china
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.2  2001/08/09 20:06:26  hdivoux
# LOG: Port to Unix (Sun CC).
# LOG:
# LOG: Revision 1.1  2001/08/09 19:28:00  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars
CFLAGS := $(CFLAGS) -I../../include \
        -I${BPM_INC}  \
        -I${BPM_INC}/../Sys  \
        -I${BPM_INC}/../Ipc


CXXOBJS=    mnt_parser.o              \
            mnt_lexer.o               \
            mnt_command.o             \
            mnt_constructs.o          \
            mnt_evaluator.o           \
            mnt_exception.o           \
            mnt_helpers.o             \
            mnt_interpreter.o         \
            mnt_messages.o            \
            mnt_mnt.o                 \
            mnt_predefined_commands.o
         
CXXFLAGS := $(CXXFLAGS) -I. -I../../include -I../../include/mnt

all: ../../lib/libMNT$(DBGSUFFIX).a

../../lib/libMNT$(DBGSUFFIX).a: $(CXXOBJS)
	$(CXXAR) $(CXXARFLAGS) ../../lib/libMNT$(DBGSUFFIX).a $(CXXOBJS) 

mnt_lexer.cpp: mnt_lexer.l
	$(LEX) -omnt_lexer.cpp mnt_lexer.l

mnt_parser.cpp mnt_parser.h: mnt_parser.y
	$(YACC) mnt_parser.y -t -v -d -o mnt_parser.cpp
	mv mnt_parser.hpp mnt_parser.h

clean:
	$(RM) *.o ../../lib/libMNT$(DBGSUFFIX).a .depend \
    mnt_parser.cpp mnt_parser.h mnt_lexer.cpp


#
# get the rules
#
include $(ITS_ROOT)/config.rules
