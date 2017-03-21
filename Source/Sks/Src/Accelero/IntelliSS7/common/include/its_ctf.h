/*********************************-*-C-*-************************************
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
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:34:27  mmanikandan
 * LOG: New line is added at end of the file.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:08  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.1  2005/01/04 13:11:03  mmanikandan
 * LOG: CTF Initial Commit.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#if defined (WIN32)
#if defined (CTF_IMPLEMENTATION)
#define CTFDLLAPI __declspec(dllexport)
#else
#define CTFDLLAPI __declspec(dllimport)
#endif
#else
#define CTFDLLAPI
#endif

CTFDLLAPI ITS_INT CTF_TraceEvent (ITS_USHORT src, 
                                  ITS_USHORT dest, 
                                  ITS_UINT output,
                                  ITS_EVENT* event);

