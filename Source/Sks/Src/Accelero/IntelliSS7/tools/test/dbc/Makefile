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
# get the vars
#
include $(ITS_ROOT)/config.vars

CXXOBJS= test_dbc.o test_main.o
CXXFLAGS := $(CXXFLAGS) -DDEBUG -D_DEBUG -I../../include -L../../../common/lib 
LIBS=../../lib/libDBCS.a

all: test_dbc

clean:
	$(RM) $(CXXOBJS) test_dbc .depend $(CXXOBJS)

test_dbc: $(CXXOBJS)
	$(CXX) $(CXXFLAGS) -o test_dbc $(CXXOBJS) $(LIBS) \
             -lSUPPORT++ $(SOCKLIBS) $(THREADLIBS)

#
# get the rules
#
include $(ITS_ROOT)/config.rules
