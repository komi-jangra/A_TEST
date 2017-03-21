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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:02  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 23:32:46  mmiers
 * LOG: Add to alarm API.  Add peg API.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_assertion.h>
#include <its_pegs.h>

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Add to a peg
 *
 *  Input Parameters:
 *      m - peg manager
 *      p - peg index
 *      hm - how much to add
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
PEG_AddToPeg(PEG_Manager *m, ITS_UINT p, ITS_UINT hm)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(p < m->numPegs);

    m->pegs[p] += hm;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete from a peg.
 *
 *  Input Parameters:
 *      m - peg manager
 *      p - peg index
 *      hm - how much to sub
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
PEG_RemFromPeg(PEG_Manager *m, ITS_UINT p, ITS_UINT hm)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(p < m->numPegs);

    m->pegs[p] -= hm;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Clear a peg.
 *
 *  Input Parameters:
 *      m - peg manager
 *      p - peg index
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
PEG_ClearPeg(PEG_Manager *m, ITS_UINT p)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(p < m->numPegs);

    m->pegs[p] = 0;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Clear all pegs.
 *
 *  Input Parameters:
 *      m - peg manager
 *      p - peg index
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
PEG_ClearBlock(PEG_Manager *m)
{
    ITS_C_ASSERT(m != NULL);

    if (m->numPegs > 0)
    {
        memset(m->pegs, 0, m->numPegs * sizeof(ITS_UINT));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the value of a specific peg.
 *
 *  Input Parameters:
 *      m - peg manager
 *      p - peg index
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
PEG_GetPeg(PEG_Manager *m, ITS_UINT p)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(p < m->numPegs);

    return (m->pegs[p]);
}

