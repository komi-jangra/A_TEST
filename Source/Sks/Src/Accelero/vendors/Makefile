	
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
#  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
#
# LOG: $Log: not supported by cvs2svn $
# LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
# LOG: init tree
# LOG:
# LOG: Revision 1.1.1.1  2007/08/03 06:49:23  cvsadmin
# LOG: BscCs2
# LOG:
# LOG: Revision 1.1.1.1  2007/03/08 15:15:01  cvsadmin
# LOG: BSC project
# LOG:
# LOG: Revision 9.2  2005/04/07 17:17:23  cvsadmin
# LOG: testing
# LOG:
# LOG: Revision 9.1  2005/03/23 12:54:25  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:53:18  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:46:26  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 4.1  2001/05/04 16:22:01  mmiers
# LOG: Start PR5.
# LOG:
# LOG: Revision 3.1  2000/08/16 00:09:21  mmiers
# LOG:
# LOG: Begin round 4.
# LOG:
# LOG: Revision 2.0  1999/12/03 23:31:15  mmiers
# LOG:
# LOG: Begin third iteration.
# LOG:
# LOG: Revision 1.7  1999/10/12 23:08:57  labuser
# LOG:
# LOG:
# LOG: Correct the build setting on DEBUG.
# LOG:
# LOG: Revision 1.6  1999/09/30 19:58:24  ssharma
# LOG:
# LOG:
# LOG: Commit Wichita Makefile
# LOG:
# LOG: Revision 1.5  1998/11/17 23:10:52  mmiers
# LOG: Change vendor target.
# LOG:
# LOG: Revision 1.4  1998/11/17 23:09:31  mmiers
# LOG: Change target vendor
# LOG:
# LOG: Revision 1.3  1998/11/17 16:54:31  jrao
# LOG: Added facility to produce Release and Debug versions of the library.
# LOG:
# LOG: Revision 1.2  1998/01/27 15:42:03  mmiers
# LOG: Update for NMS
# LOG:
# LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
# LOG: Baseline
# LOG:
#
############################################################################

#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

ifeq ($(VENDOR),)
VENDOR=IntelliNet
endif

all:
	(cd $(VENDOR)/src && $(MAKE) DEBUG_BUILD=yes clean)
	(cd $(VENDOR)/src && $(MAKE) DEBUG_BUILD=yes)
	(cd $(VENDOR)/src && $(MAKE) DEBUG_BUILD=no clean)
	(cd $(VENDOR)/src && $(MAKE) DEBUG_BUILD=no)

clean:
	(cd $(VENDOR)/src && $(MAKE) DEBUG_BUILD=yes clean)
	(cd $(VENDOR)/src && $(MAKE) DEBUG_BUILD=no clean)
  
#
# get the rules
#
include $(VENDOR_ROOT)/config.rules
