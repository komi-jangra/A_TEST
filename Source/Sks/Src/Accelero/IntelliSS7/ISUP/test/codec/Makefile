/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 *     FILE: its.h                                                          *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: Makefile,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:07  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:03  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:37  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:36  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:06  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:39  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/11/24 16:13:42  cbascon
 * LOG: Added ISUP C encode/decode test program.
 * LOG: Just ANSI for now. Need to remove obj files and license file.
 * LOG:
 *
 ***************************************************************************/

include $(ITS_ROOT)/config.vars

DBGSUFFIX= D

CFLAGS := $(CFLAGS) \
          -I.. \
          -I../include \
          -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/tools/include \
          -I$(ITS_ROOT)/MTP3/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/ISUP/include \
          -I$(ITS_ROOT)/TCAP/include \
          -L$(ITS_ROOT)/common/lib \
          -L$(ITS_ROOT)/MTP3/lib \
          -L$(ITS_ROOT)/SCCP/lib \
          -L$(ITS_ROOT)/ISUP/lib \

OBJS = testMain.o codecISUPMsg.o ../readISUPMsg.o ../printISUPMsg.o

LIBS = -lSUPPORT$(DBGSUFFIX) \
       -lCORE$(DBGSUFFIX) \
       -l$(PROTOCOL)-ISUP$(DBGSUFFIX) \
       -l$(PROTOCOL)-SCCP$(DBGSUFFIX) \
       -l$(PROTOCOL)-MTP3$(DBGSUFFIX) \
       -lASN$(DBGSUFFIX) \
       $(SYSLIBS) $(THREADLIBS)

all: codectest

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS) codectest

codectest: $(OBJS)
	$(CC) $(CFLAGS) -o codectest $(OBJS) \
		$(LIBS) $(LIBS) $(SOCKLIBS) $(THREADLIBS)

