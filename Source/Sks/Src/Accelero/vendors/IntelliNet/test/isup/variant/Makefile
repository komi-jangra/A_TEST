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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:25:02  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:22  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:54:36  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 1.2  2002/02/05 20:19:53  ssharma
# LOG: IntelliNet ISUP stack test directory.
# LOG:
# LOG: Revision 1.1.2.2  2002/01/30 21:05:35  ssharma
# LOG: Compile and link errors.
# LOG:
# LOG: Revision 1.1.2.1  2002/01/29 20:28:47  ssharma
# LOG: ISUP variant logic test.
# LOG:
# LOG: Revision 1.1.2.1  2002/01/23 18:05:10  ssharma
# LOG: ISUP variant support test.
# LOG:
# LOG: Revision 3.1  2000/08/15 23:59:31  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.7  2000/06/21 15:23:08  labuser
# LOG: Use /newnet/lib
# LOG:
# LOG: Revision 2.6  2000/05/16 15:11:32  labuser
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 2.5  2000/02/08 14:15:57  labuser
# LOG: ISUP Test now only uses MTP3 & ISUP libraries.
# LOG:
# LOG: Revision 2.4  2000/01/11 22:35:15  labuser
# LOG: Just use the same executable for instance 1 & 2 of the test program.
# LOG:
# LOG: Revision 2.3  2000/01/11 18:11:17  labuser
# LOG: Almost done with pass thru messages.
# LOG:
# LOG: Revision 2.2  1999/12/30 15:54:11  labuser
# LOG: Clean up...
# LOG:
# LOG: Revision 2.1  1999/12/07 00:40:02  cbascon
# LOG: Encoded and sent the messages below successfully:
# LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO
# LOG:
# LOG: Received and decoded the messages below successfully:
# LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO, UCIC
# LOG:
# LOG: Revision 2.0  1999/12/03 23:21:33  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.4  1999/11/24 19:22:04  cbascon
# LOG: Added object file for printISUPMsg.c
# LOG:
# LOG: Revision 1.3  1999/11/11 17:59:54  labuser
# LOG: cbascon: Successful link with newnet vendor lib.
# LOG:
# LOG: Revision 1.2  1999/11/06 17:41:56  labuser
# LOG: First successful build.
# LOG:
# LOG: Revision 1.1  1999/11/02 23:48:22  labuser
# LOG: Base for makefile.
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) \
       -DINCLUDE_ISUP \
       -I$(ITS_ROOT)/common/include \
       -I$(ITS_ROOT)/tools/include \
       -I$(ITS_ROOT)/ISUP/include \
       -I$(ITS_ROOT)/MTP2/include \
       -I$(ITS_ROOT)/MTP3/include \
       -I$(ITS_ROOT)/SCCP/include \
       -I$(ITS_ROOT)/TCAP/include \
       -I$(VENDOR_ROOT)/IntelliNet/include \
       -L$(ITS_ROOT)/common/lib \
       -L$(VENDOR_ROOT)/IntelliNet/lib \
       -L$(ITS_ROOT)/MTP3/lib \
       -L$(ITS_ROOT)/SCCP/lib \
       -L$(ITS_ROOT)/TCAP/lib \
       -L$(ITS_ROOT)/ISUP/lib

OBJS = variant_test.o 

LIBS = -lCORE$(DBGSUFFIX) \
       -lDSM-STUB$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) \
       -lCORE$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX) \
       -l$(PROTOCOL)-MTP3$(DBGSUFFIX) \
       -l$(PROTOCOL)-SCCP$(DBGSUFFIX) \
       -l$(PROTOCOL)-TCAP$(DBGSUFFIX) \
       -lASN$(DBGSUFFIX) \
       -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) \
       -lSUPPORT$(DBGSUFFIX) \
       -lCORE$(DBGSUFFIX) \
       $(SYSLIBS) $(THREADLIBS)

all: isuptest

clean:
	$(RM) $(OBJS) isuptest

isuptest: $(OBJS)
	$(CC) $(CFLAGS) -o isuptest $(OBJS) \
		$(LIBS) $(SOCKLIBS) $(THREADLIBS) -lrt

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
