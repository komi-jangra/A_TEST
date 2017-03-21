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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:23  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:24  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.5  2001/07/05 22:48:01  mmiers
 * LOG: Update for DMA.  Need to finish timers.
 * LOG:
 * LOG: Revision 1.4  2001/07/03 21:16:22  mmiers
 * LOG: Move RM and DSM.
 * LOG:
 * LOG: Revision 1.1  2001/06/22 18:33:27  mmiers
 * LOG: Move DSM to ENGINE.
 * LOG:
 * LOG: Revision 1.2  2001/06/21 00:58:29  mmiers
 * LOG: UNIX build.
 * LOG:
 * LOG: Revision 1.1  2001/06/20 21:07:19  mmiers
 * LOG: Add DSM stub.
 * LOG:
 * LOG: Revision 1.1  2001/06/20 19:56:09  mmiers
 * LOG: Split DSM out into a separate lib.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_DSM_IMPL_H_)
#define _DSM_IMPL_H_

#include <its.h>
#include <its_hash.h>

#ident "$Id: dsm_impl.h,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"

/*
 * object part (just a hash table)
 */
typedef struct
{
    HASH_Table  table;
    ITS_USHORT  nodeId;
}
DSM_ObjectPart;

#define DSM_TABLE(x) \
    (((DSM_Area *)(x))->dsm.table)

#define DSM_GIVEN_NODE_ID(x) \
    (((DSM_Area *)(x))->dsm.nodeId)

#endif /* _DSM_IMPL_H_ */

