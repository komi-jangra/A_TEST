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
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/06/11 21:42:52  yranade
 * LOG: Get it to compile. Missing opening braces.
 * LOG: Seen when compiling with C++ compiler.
 * LOG:
 * LOG: Revision 6.4  2002/05/15 14:53:59  randresol
 * LOG: Add BEHAVIORS_CommitSharedBehaviors and BEHAVIORS_InitSharedBehaviors
 * LOG:
 * LOG: Revision 6.3  2002/03/14 21:45:30  mmiers
 * LOG: Spelling error.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 21:40:04  mmiers
 * LOG: Changes for OAM
 * LOG:
 * LOG: Revision 6.1  2002/03/14 18:01:34  mmiers
 * LOG: license fixes, new behaviors implementation, timer block
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_BEHAVIORS_H)
#define ITS_BEHAVIORS_H

#include <its.h>

/*
 * Really simple structure
 */
typedef struct
{
    char        *name;
    ITS_UINT    numBehaviors;
    ITS_BOOLEAN *behaviors;
}
BEHAVIOR_Manager;

#define BEHAVIORS_DECL_SUBSYS(s, p) \
    BEHAVIOR_Manager s##_Behaviors = { #s, sizeof(p) / sizeof(ITS_BOOLEAN), (p) }

#if defined(__cplusplus)
extern "C"
{
#endif

ITSDLLAPI ITS_BOOLEAN   BEHAVIORS_GetBehavior(BEHAVIOR_Manager *m,
                                              ITS_UINT which);
ITSDLLAPI void          BEHAVIORS_SetBehavior(BEHAVIOR_Manager *m,
                                              ITS_UINT which,
                                              ITS_BOOLEAN setting);

ITSDLLAPI ITS_BOOLEAN *BEHAVIORS_InitSharedBehaviors(ITS_UINT key, 
                                                     ITS_UINT size);

ITSDLLAPI int BEHAVIORS_CommitSharedBehaviors(ITS_UINT key);


#if defined(__cplusplus)
}
#endif

#endif /* ITS_BEHAVIORS_H */
