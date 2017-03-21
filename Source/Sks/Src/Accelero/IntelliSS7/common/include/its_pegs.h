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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/06/11 21:42:52  yranade
 * LOG: Get it to compile. Missing opening braces.
 * LOG: Seen when compiling with C++ compiler.
 * LOG:
 * LOG: Revision 6.2  2002/03/01 23:12:56  mmiers
 * LOG: Pegs and alarms
 * LOG:
 * LOG: Revision 6.1  2002/02/28 23:29:04  mmiers
 * LOG: Add to alarm API, add peg API.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_PEGS_H)
#define ITS_PEGS_H

#include <its.h>

/*
 * Really simple structure
 */
typedef struct
{
    char        *name;
    ITS_UINT    numPegs;
    ITS_UINT    *pegs;
}
PEG_Manager;

#define PEGS_DECL_SUBSYS(s, p) \
    PEG_Manager s##_PEGS = { #s, sizeof(p) / sizeof(ITS_UINT), (p) }

#if defined(__cplusplus)
extern "C"
{
#endif

ITSDLLAPI void      PEG_AddToPeg(PEG_Manager *m, ITS_UINT p, ITS_UINT hm);
ITSDLLAPI void      PEG_RemFromPeg(PEG_Manager *m, ITS_UINT p, ITS_UINT hm);
ITSDLLAPI void      PEG_ClearPeg(PEG_Manager *m, ITS_UINT p);
ITSDLLAPI void      PEG_ClearBlock(PEG_Manager *m);
ITSDLLAPI ITS_UINT  PEG_GetPeg(PEG_Manager *m, ITS_UINT p);

#if defined(__cplusplus)
}
#endif

/*
 * these can be done as macros
 */
#define PEG_IncrPeg(m, p)   PEG_AddToPeg((m), (p), 1)
#define PEG_DecrPeg(m, p)   PEG_RemFromPeg((m), (p), 1)

#endif /* ITS_PEGS_H */
