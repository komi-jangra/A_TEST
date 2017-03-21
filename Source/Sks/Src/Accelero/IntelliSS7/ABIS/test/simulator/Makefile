################################################################################
#                                                                              #
#      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.       #
#              Manufactured in the United States of America.                   #
#        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.          #
#                                                                              #
#     This product and related documentation is protected by copyright and     #
#     distributed under licenses restricting its use, copying, distribution    #
#     and decompilation.  No part of this product or related documentation     #
#     may be reproduced in any form by any means without prior written         #
#     authorization of IntelliNet Technologies and its licensors, if any.      #
#                                                                              #
#     RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        #
#     government is subject to restrictions as set forth in subparagraph       #
#     (c)(1)(ii) of the Rights in Technical Data and Computer Software         #
#     clause at DFARS 252.227-7013 and FAR 52.227-19.                          #
#                                                                              #
################################################################################
#                                                                              #
# CONTRACT: INTERNAL                                                           #
#                                                                              #
################################################################################
#
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
#  $Log: not supported by cvs2svn $
#  Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
#  init tree
#
#  Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
#  BscCs2
#
#  Revision 1.1.1.1  2007/03/08 15:12:53  cvsadmin
#  BSC project
#
#  Revision 1.1.2.2  2005/09/05 12:32:04  mkrishna
#  Added network mangement simulator files - akshata & sriraghavendrasm
#
#  Revision 1.1.2.1  2005/08/29 08:59:39  mkrishna
#  Added codec simulator - hakshata & sriraghavendrasm
#
#  Revision 1.1.2.1  2005/08/16 11:41:53  mkrishna
#  Added Initial version after unit testing.
#
#
################################################################################

#
# get the vars
#
include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) \
          -I$(ITS_ROOT)/common/include \
      -I../../include/GSM 

OBJS= readDCMM.o \
      readRLLM.o \
      readCCM.o \
      readTRXM_LCS.o \
      readNETWORK_MSG.o \
      equipment_management_msg.o \
      state_management_msg.o \
      measurement_management_msg.o \
      other_messages.o \
      file_main.o 



LIBS:= -L ../../lib  \
       -L $(ITS_ROOT)/ABIS/lib  \
       -lABISCODECD \
       -lpthread -lnsl

all: sim_exe

sim_exe: $(OBJS)
	$(CC) $(CFLAGS) -o \
            $@ $(OBJS) $(LIBS) -ldl -lrt

clean:
	$(RM) -rf *.o sim_exe 


#
# get the rules
#
include $(ITS_ROOT)/config.rules
                                         
