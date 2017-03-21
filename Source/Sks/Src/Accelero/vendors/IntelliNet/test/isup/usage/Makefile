############################################################################
#                                                                          #
#     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:55:20  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:54:30  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
# LOG: Merge from PR6, remove unwanted directories.
# LOG:
# LOG: Revision 1.1.2.2  2002/05/08 18:40:40  hbalimid
# LOG: Modified to include config vars
# LOG:
# LOG: Revision 1.1.2.1  2002/05/08 18:36:36  hbalimid
# LOG: sample Makefile for isup usage demo
# LOG:
#
############################################################################

#
# get the conig vars
#
include ./config.vars

DEFINES:= $(DEFINES) -DTRANSPORT_SS7

CFLAGS:= $(CFLAGS) -I. -I./includes

LIBS:= -L./libs \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lVFrame$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       -lthread -lsocket -lnsl -ldl -lrt

OBJS:= isupUsage.o printIsupMsg.o

EXE:= isup

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) $(EXE)
