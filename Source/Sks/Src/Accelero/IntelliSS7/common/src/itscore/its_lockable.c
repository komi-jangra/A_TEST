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
 * LOG: Revision 7.1  2002/08/26 22:10:00  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:55  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:36  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.7  2000/02/15 20:34:48  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.6  2000/02/14 19:17:43  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.5  1999/12/22 02:09:03  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.4  1999/12/15 18:23:16  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.3  1999/12/15 02:44:22  mmiers
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
 * LOG: Revision 2.0  1999/12/03 23:27:49  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/12/03 22:38:18  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding object patterns for C.  Time to branch the tree.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_lockable.h>

#ident "$Id: its_lockable.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method locks a class.
 *
 *  Input Parameters:
 *      None.
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
static int
LockClass(LOCKABLE_Class classRecord)
{
    return MUTEX_AcquireMutex(&LOCKABLE_CLASS_LOCK(classRecord));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method tries to lock a class.
 *
 *  Input Parameters:
 *      None.
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
static int
TryLockClass(LOCKABLE_Class classRecord)
{
    return MUTEX_TryAcquireMutex(&LOCKABLE_CLASS_LOCK(classRecord));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method unlocks a class.
 *
 *  Input Parameters:
 *      None.
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
static int
UnlockClass(LOCKABLE_Class classRecord)
{
    return MUTEX_ReleaseMutex(&LOCKABLE_CLASS_LOCK(classRecord));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method initializes the Lockable part of a class.
 *
 *  Input Parameters:
 *      None.
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
static int
ClassPartInitialize(ITS_Class classRecord)
{
    if (LOCKABLE_LOCK_METHOD(classRecord) == LOCKABLE_INHERIT)
    {
        LOCKABLE_LOCK_METHOD(classRecord) = LockClass;
    }

    if (LOCKABLE_TRY_LOCK_METHOD(classRecord) == LOCKABLE_INHERIT)
    {
        LOCKABLE_TRY_LOCK_METHOD(classRecord) = TryLockClass;
    }

    if (LOCKABLE_UNLOCK_METHOD(classRecord) == LOCKABLE_INHERIT)
    {
        LOCKABLE_UNLOCK_METHOD(classRecord) = UnlockClass;
    }

    return MUTEX_CreateMutex(&LOCKABLE_CLASS_LOCK(classRecord), 0);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys the unlockable part of a class.
 *
 *  Input Parameters:
 *      None.
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
static void
ClassPartDestroy(ITS_Class classRecord)
{
    if (!ITS_CLASS_INITTED(classRecord))
    {
        return;
    }

    MUTEX_DeleteMutex(&LOCKABLE_CLASS_LOCK(classRecord));
}

/*
 * the lockable class record
 */
ITSDLLAPI LOCKABLE_ClassRec itsLOCKABLE_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,          /* no meaningful superclass */
        0,                          /* no meaningful instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial refCount */
        LOCKABLE_CLASS_NAME,        /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ClassPartInitialize,        /* class initialize part */
        ClassPartDestroy,           /* class destroy part */
        ITS_INST_NO_CONST,          /* can't instantiate from here */
        ITS_INST_NO_DEST,           /* can't destruct anything */
        ITS_INST_CLONE_INHERIT,     /* inherit clone */
        ITS_INST_PRINT_INHERIT,     /* inherit print */
        ITS_INST_SERIAL_INHERIT,    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,    /* inherit equals */
        ITS_INST_HASH_INHERIT,      /* inherit equals */
        NULL                        /* no extension of interest */
    },
    /* lockable part */
    {
        LockClass,          /* lock method */
        TryLockClass,       /* try lock method */
        UnlockClass,        /* unlock method */
        { 0 },              /* no meaningful mutex */
        NULL                /* no meaningful object */
    }
};

ITSDLLAPI ITS_Class itsLOCKABLE_Class = (ITS_Class)&itsLOCKABLE_ClassRec;

#undef LOCKABLE_Lock
#undef LOCKABLE_TryLock
#undef LOCKABLE_Unlock
#undef LOCKABLE_GetShared

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function locks the singleton class record
 *
 *  Input Parameters:
 *      lockClass - the lock class.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, this function returns ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LOCKABLE_Lock(LOCKABLE_Class lockClass)
{
    return LOCKABLE_LOCK_METHOD(lockClass)(lockClass);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function tries to lock the singleton class record
 *
 *  Input Parameters:
 *      lockClass - the lock class.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, this function returns ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LOCKABLE_TryLock(LOCKABLE_Class lockClass)
{
    return LOCKABLE_TRY_LOCK_METHOD(lockClass)(lockClass);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function unlocks the singleton class record
 *
 *  Input Parameters:
 *      lockClass - the lock class.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, this function returns ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LOCKABLE_Unlock(LOCKABLE_Class lockClass)
{
    return LOCKABLE_UNLOCK_METHOD(lockClass)(lockClass);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the shared singleton protected by this class
 *
 *  Input Parameters:
 *      lockClass - the lock class.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, this function returns a pointer to the shared resource
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_Object
LOCKABLE_GetShared(LOCKABLE_Class lockClass)
{
    return LOCKABLE_SHARED_INSTANCE(lockClass);
}
