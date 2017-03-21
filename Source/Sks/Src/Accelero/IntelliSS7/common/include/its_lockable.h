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
 * LOG: Revision 9.1  2005/03/23 12:52:49  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  1999/12/15 18:22:13  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.3  1999/12/15 02:44:21  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten out the OO stuff for ITS.  This is starting to gel, but
 * LOG: I'm awaiting feedback from Hubert.
 * LOG:
 * LOG: Revision 2.2  1999/12/10 23:44:46  mmiers
 * LOG:
 * LOG:
 * LOG: Convert to the new object format.  Only callback is done so far.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 16:36:38  mmiers
 * LOG:
 * LOG:
 * LOG: Correct a few build issues, some typos.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:40  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/12/03 22:35:38  mmiers
 * LOG:
 * LOG:
 * LOG: Add the beginnings of the class structure to the support library.
 * LOG: Time to branch the tree.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_LOCKABLE_H)
#define ITS_LOCKABLE_H

#include <its_object.h>
#include <its_mutex.h>

#ident "$Id: its_lockable.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * forward
 */
typedef struct _LOCKABLE_ClassRec*   LOCKABLE_Class;

/*
 * class methods
 */
typedef int (*LOCKABLE_LockClass)(LOCKABLE_Class);
typedef int (*LOCKABLE_TryLockClass)(LOCKABLE_Class);
typedef int (*LOCKABLE_UnlockClass)(LOCKABLE_Class);

#define LOCKABLE_INHERIT    (int (*)(LOCKABLE_Class))NULL
/*
 * the lockable class implements the design pattern of the
 * singleton object.  This is meant to be an abstract class.
 */
typedef struct
{
    LOCKABLE_LockClass      lockMethod;
    LOCKABLE_TryLockClass   tryLockMethod;
    LOCKABLE_UnlockClass    unlockMethod;

    ITS_MUTEX               classLock;
    ITS_Object              sharedInstance;
}
LOCKABLE_ClassPart;

/*
 * basic inheritance technique for the Lockable class
 */
typedef struct _LOCKABLE_ClassRec
{
    ITS_CoreClassPart   coreClass;
    LOCKABLE_ClassPart  lockClass;
}
LOCKABLE_ClassRec;

/*
 * access
 */
#define LOCKABLE_LOCK_METHOD(x) \
    (((LOCKABLE_Class)(x))->lockClass.lockMethod)

#define LOCKABLE_TRY_LOCK_METHOD(x) \
    (((LOCKABLE_Class)(x))->lockClass.tryLockMethod)

#define LOCKABLE_UNLOCK_METHOD(x) \
    (((LOCKABLE_Class)(x))->lockClass.unlockMethod)

#define LOCKABLE_CLASS_LOCK(x) \
    (((LOCKABLE_Class)(x))->lockClass.classLock)

#define LOCKABLE_SHARED_INSTANCE(x) \
    (((LOCKABLE_Class)(x))->lockClass.sharedInstance)

#define LOCKABLE_CLASS_NAME "LOCKABLE"

ITSDLLAPI extern LOCKABLE_ClassRec    itsLOCKABLE_ClassRec;
ITSDLLAPI extern ITS_Class            itsLOCKABLE_Class;

#if !defined(ITS_FASTCALL)

ITSDLLAPI int         LOCKABLE_Lock(LOCKABLE_Class lockClass);
ITSDLLAPI int         LOCKABLE_TryLock(LOCKABLE_Class lockClass);
ITSDLLAPI int         LOCKABLE_Unlock(LOCKABLE_Class lockClass);
ITSDLLAPI ITS_Object  LOCKABLE_GetShared(LOCKABLE_Class lockClass);

#else /* ITS_FASTCALL */

#define LOCKABLE_Lock(lc)                           \
    LOCKABLE_LOCK_METHOD(lc)(lc)

#define LOCKABLE_TryLock(lc)                        \
    LOCKABLE_TRY_LOCK_METHOD(lc)(lc)

#define LOCKABLE_Unlock(lc)                         \
    LOCKABLE_UNLOCK_METHOD(lc)(lc)

#define LOCKABLE_GetShared(lc)                      \
    LOCKABLE_SHARED_INSTANCE(lc)

#endif /* ITS_FASTCALL */

#if defined(__cplusplus)
}
#endif

#endif /* ITS_LOCKABLE_H */
