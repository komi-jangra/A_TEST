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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:30  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:10  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:13  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:58  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  2000/06/02 02:05:19  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some nasty hangaround bugs, convert transports and route to
 * LOG: RWLOCK.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:10  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/09/30 20:42:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add some stuff for primitive RTOSs.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_spinlock.h>
#include <assert.h>

#ident "$Id: its_spinlock.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

extern int test_and_set(ITS_SPINLOCK *s);
extern void disable_irqs();
extern void enable_irqs();

/*
 * Lock a spinlock.
 */
void
SPINLOCK_lock(ITS_SPINLOCK *s)
{
    assert(s != NULL);

    /*
     * Note that this is a busy wait, so the lock should NOT be
     * held for a long time.  Note that the loop will never be
     * performed more than once on a uniprocessor machine
     * unless a lock holder context switches while the
     * lock is held.  Ideally, this call should be made with
     * interrupts disabled so that context switching cannot
     * happen on this CPU (no scheduler run via timer interrupt).
     * In other words, a context switch MUST NOT BE POSSIBLE
     * WHILE THIS FUNCTION RUNS.
     */
    disable_irqs();

    while (test_and_set(s) != 0)
    {
        /*
         * avoid monopolizing the bus by locking it in the
         * function above.
         *
        while (*s != 0)
        {
        }
    }

    enable_irqs();
}

/*
 * unlock a spinlock.  We really don't care if this operation
 * is atomic, as the store will release the lock from any
 * other perspective.
 */
void
SPINLOCK_unlock(spinlock_t *s)
{
    *s = 0;
}
