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
 * LOG: Revision 7.2.2.1  2003/02/19 16:19:22  randresol
 * LOG: Bug fixing for DSM-GCS.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.12  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.11  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.10  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.9  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.8  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.7  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.6  2001/01/19 22:47:46  mmiers
 * LOG: cleanup
 * LOG:
 * LOG: Revision 3.5  2001/01/19 19:33:08  mmiers
 * LOG: Mysteries
 * LOG:
 * LOG: Revision 3.4  2000/08/24 23:06:39  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.3  2000/08/18 02:20:13  mmiers
 * LOG: First implementation of stack MEMPOOL.  Smarten realloc needs to be
 * LOG: done.
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:27:22  mmiers
 * LOG: Add user data to list remove procs
 * LOG: Add memory pool for quick reclamation
 * LOG: Add object creation into user supplied buffer
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:05  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.6  2000/03/18 21:03:50  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 1.5  2000/02/15 20:34:44  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 1.4  2000/02/15 16:37:20  mmiers
 * LOG:
 * LOG: Good enough for a working version.  I have some ideas about cleaning
 * LOG: up the leaks (use ITS_RegisterFeature for the ClassInit).
 * LOG:
 * LOG: Revision 1.3  2000/02/14 19:20:34  mmiers
 * LOG:
 * LOG:
 * LOG: Set classInitted to FALSE after class destruction.
 * LOG:
 * LOG: Revision 1.2  2000/02/14 19:17:39  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 1.1  2000/01/26 23:42:45  mmiers
 * LOG:
 * LOG:
 * LOG: Do some rearranging.
 * LOG:
 * LOG: Revision 2.2  1999/12/22 18:47:48  mmiers
 * LOG:
 * LOG:
 * LOG: Object based support working.
 * LOG:
 * LOG: Revision 2.1  1999/12/22 02:09:03  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:54  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/12/03 22:38:19  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding object patterns for C.  Time to branch the tree.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_object.h>
#include <its_assertion.h>

#ident "$Id: its_object.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*
 * forward
 */
static int InitializeObject(ITS_Class objClass, ITS_Object object,
                            va_list args);
static void DestructObject(ITS_Class objClass, ITS_Object object);

static void DestructClass(ITS_Class baseClass, ITS_Class subClass);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method initializes a class record.
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
InitializeClass(ITS_Class baseClass, ITS_Class subClass)
{
    int ret;

    if (ITS_CLASS_SUPERCLASS(baseClass))
    {
        ret = InitializeClass(ITS_CLASS_SUPERCLASS(baseClass), subClass);

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }

    if (ITS_CLASS_PART_CONSTRUCTOR(baseClass) != ITS_CLASS_PART_NO_INIT)
    {
        ret = ITS_CLASS_PART_CONSTRUCTOR(baseClass)(subClass);

        if (ret != ITS_SUCCESS)
        {
            if (ITS_CLASS_SUPERCLASS(baseClass))
            {
                DestructClass(ITS_CLASS_SUPERCLASS(baseClass), subClass);
            }

            return (ret);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys a class.  This is where the recursive
 *      destruction is performed.
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
 *      The destructors are called in subclass to superclass order.
 *
 *  See Also:
 ****************************************************************************/
static void
DestructClass(ITS_Class baseClass, ITS_Class subClass)
{
    ITS_CLASS_REF_COUNT(baseClass)--;

    if (ITS_CLASS_PART_DESTRUCTOR(baseClass))
    {
        ITS_CLASS_PART_DESTRUCTOR(baseClass)(subClass);
    }

    if (ITS_CLASS_SUPERCLASS(baseClass))
    {
        DestructClass(ITS_CLASS_SUPERCLASS(baseClass), subClass);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method initializes a class record.  Any class specific
 *      initialization should happen here.
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
 *      ALL CLASS INITIALIZATION MUST TAKE PLACE SINGLE THREADED!
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ITS_InitializeClass(ITS_Class objClass)
{
    int ret;

    ITS_C_REQUIRE(objClass != NULL);

    if (ITS_CLASS_INITTED(objClass))
    {
        ITS_CLASS_REF_COUNT(objClass)++;

        return (ITS_SUCCESS);
    }

    if (ITS_CLASS_SUPERCLASS(objClass))
    {
        ret = ITS_InitializeClass(ITS_CLASS_SUPERCLASS(objClass));

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }

    ITS_CLASS_INITTED(objClass) = ITS_TRUE;
    ITS_CLASS_REF_COUNT(objClass)++;

    if (ITS_CLASS_CONSTRUCTOR(objClass) != ITS_CLASS_NO_INIT)
    {
        ret = ITS_CLASS_CONSTRUCTOR(objClass)(objClass);

        if (ret != ITS_SUCCESS)
        {
            ITS_CLASS_INITTED(objClass) = ITS_FALSE;
            ITS_CLASS_REF_COUNT(objClass)--;

            return (ret);
        }
    }

    ret = InitializeClass(objClass, objClass);

    if (ret != ITS_SUCCESS)
    {
        if (ITS_CLASS_SUPERCLASS(objClass))
        {
            ITS_DestroyClass(ITS_CLASS_SUPERCLASS(objClass));
        }

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method destroys a class record.  Any class specific
 *      destruction should happen here.
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
 *      The astute reader of this and the feature code will notice that
 *      we construct classes nested; that is, we build (any) superclasses,
 *      then build a given subclass.  However, when we destroy classes, we
 *      destroy them flatly; that is, one class at a time.  The reason for
 *      this is that the class nesting is implicit in the feature list, and
 *      we destroy the feature list in reverse order.  So, the superclass
 *      is added to the feature list, then the subclass.  So, they are
 *      destroyed in subclass/superclass order.  We could be clever and
 *      destroy them nested, but that requires some fancy dancing to
 *      ensure the feature list pointer travel isn't pooched.  It's
 *      easier just to let the list itself control the destruction, so
 *      we can process the feature list one node at a time.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ITS_DestroyClass(ITS_Class objClass)
{
    ITS_C_REQUIRE(objClass != NULL);

    if (ITS_CLASS_REF_COUNT(objClass) < 0)
    {
        ITS_CLASS_REF_COUNT(objClass) = 0;
    }
    else
    {
        DestructClass(objClass, objClass);
    }

    if (!ITS_CLASS_INITTED(objClass))
    {
        return;
    }

    if (ITS_CLASS_REF_COUNT(objClass) < 0)
    {
        ITS_CLASS_REF_COUNT(objClass) = 0;
    }

    if (ITS_CLASS_REF_COUNT(objClass) == 0)
    {
        if (ITS_CLASS_DESTRUCTOR(objClass) != ITS_CLASS_NO_DEST)
        {
            ITS_CLASS_DESTRUCTOR(objClass)(objClass);
        }

        ITS_CLASS_INITTED(objClass) = ITS_FALSE;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method instantiates an object.  This is where the recursive
 *      instantiation is performed.
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
 *      The constructors are called in superclass to subclass order.
 *
 *  See Also:
 ****************************************************************************/
static int
InitializeObject(ITS_Class objClass, ITS_Object object, va_list args)
{
    int ret;

    if (ITS_CLASS_SUPERCLASS(objClass))
    {
        ret = InitializeObject(ITS_CLASS_SUPERCLASS(objClass),
                               object, args);

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }

    if (ITS_CLASS_OBJECT_INSTANTIATE(objClass) != ITS_INST_NO_CONST)
    {
        ret = ITS_CLASS_OBJECT_INSTANTIATE(objClass)(object, args);

        if (ret != ITS_SUCCESS)
        {
            if (ITS_CLASS_SUPERCLASS(objClass))
            {
                DestructObject(ITS_CLASS_SUPERCLASS(objClass),
                               object);
            }

            return (ret);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys an object.  This is where the recursive
 *      destruction is performed.
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
 *      The destructors are called in subclass to superclass order.
 *
 *  See Also:
 ****************************************************************************/
static void
DestructObject(ITS_Class objClass, ITS_Object object)
{
    if (ITS_CLASS_OBJECT_DESTROY(objClass))
    {
        ITS_CLASS_OBJECT_DESTROY(objClass)(object);
    }

    if (ITS_CLASS_SUPERCLASS(objClass))
    {
        DestructObject(ITS_CLASS_SUPERCLASS(objClass),
                       object);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method instantiates an object.  If the class is not initialized,
 *      this routine will attempt to initialize it.  If the initialization is
 *      not thread safe, and you instantiate an object of an uninitialized
 *      class after going multithreaded, the results of the initialization
 *      and instantiation are undefined (read: likely core dump).
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
 *      The constructors are called in superclass to subclass order.
 *      Space for the object is allocated on the heap.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_Object
ITS_ConstructObject(ITS_Class objClass, ...)
{
    int ret;
    ITS_Object obj = NULL;
    va_list alist;

    ITS_C_REQUIRE(objClass != NULL);

    if (!ITS_CLASS_INITTED(objClass))
    {
        ret = ITS_InitializeClass(objClass);

        if (ret != ITS_SUCCESS)
        {
            return (NULL);
        }
    }

    obj = (ITS_Object)calloc(1, ITS_CLASS_INSTANCE_SIZE(objClass));
    if (obj == NULL)
    {
        return (NULL);
    }

    ITS_OBJ_CLASS(obj) = objClass;
    ITS_OBJ_IS_DYNAMIC(obj) = ITS_TRUE;

    va_start(alist, objClass);

    ret = InitializeObject(objClass, obj, alist);

    va_end(alist);

    if (ret != ITS_SUCCESS)
    {
        free(obj);

        return (NULL);
    }

    return (obj);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method instantiates an object.  If the class is not initialized,
 *      this routine will attempt to initialize it.  If the initialization is
 *      not thread safe, and you instantiate an object of an uninitialized
 *      class after going multithreaded, the results of the initialization
 *      and instantiation are undefined (read: likely core dump).
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
 *      The constructors are called in superclass to subclass order.
 *      Space for the object is created by the user.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_Object
ITS_ConstructObjectIn(void *region, ITS_Class objClass, ...)
{
    int ret;
    ITS_Object obj = NULL;
    va_list alist;

    ITS_C_REQUIRE(region != NULL);
    ITS_C_REQUIRE(objClass != NULL);

    if (!ITS_CLASS_INITTED(objClass))
    {
        ret = ITS_InitializeClass(objClass);

        if (ret != ITS_SUCCESS)
        {
            return (NULL);
        }
    }

    obj = (ITS_Object)ITS_OBJ_ALIGN(region);
    if (obj == NULL)
    {
        return (NULL);
    }

    /*
     * NOTE: We used to do this here:
     *
     * memset(region, 0, ITS_InstanceSize(objClass));
     *
     * Turns out that's not such a hot idea, if the user
     * wants to preinitialize some fields.  This is all a pain,
     * but the hash table constructor wants to call a class method,
     * and if a derived class overrides that method the oject record
     * isn't properly set up yet.  This means that the user must hand
     * initialize such fields, which get blown away by the memset.  See
     * HashAlloc in dsm_gcs_impl.c for a real-world case (look at
     * CreateTable in its_hash.c for why).
     */

    ITS_OBJ_CLASS(obj) = objClass;
    ITS_OBJ_IS_DYNAMIC(obj) = ITS_FALSE;

    va_start(alist, objClass);

    ret = InitializeObject(objClass, obj, alist);

    va_end(alist);

    if (ret != ITS_SUCCESS)
    {
        return (NULL);
    }

    return (obj);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method destructs an object.
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
 *      The destructors are called in subclass to superclass order.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ITS_DestructObject(ITS_Object object)
{
    ITS_BOOLEAN isDyn;

    if (!object)
    {
        return;
    }

    ITS_OBJ_BEING_DESTROYED(object) = ITS_TRUE;
    isDyn = ITS_OBJ_IS_DYNAMIC(object);

    DestructObject(ITS_OBJ_CLASS(object), object);

    if (isDyn)
    {
        free(object);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This determines if an instance is a subclass of a class
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
 *      This method is subject to structure packing constraints.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
ITS_InstanceSize(ITS_Class cl)
{
    ITS_C_REQUIRE(cl != NULL);

    return ITS_CLASS_INSTANCE_SIZE(cl);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This determines if an instance is a subclass of a class
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
 *      This method is subject to structure packing constraints.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
ITS_IsInstanceOf(ITS_Class cl, ITS_Object obj)
{
    ITS_Class objClass;

    ITS_C_REQUIRE(cl != NULL);
    ITS_C_REQUIRE(obj != NULL);

    objClass = ITS_OBJ_CLASS(obj);
    while (objClass)
    {
        if (objClass == cl)
        {
            return (ITS_TRUE);
        }

        objClass = ITS_CLASS_SUPERCLASS(objClass);
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method prints an object.
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
 *      This needs work to be machine portable.  Right now, such a
 *      beast needs an override for this method in all subclasses.
 *      This method is subject to structure packing constraints.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_Object
ITS_Clone(ITS_Object obj)
{
    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    if (ITS_CLASS_CLONE(ITS_OBJ_CLASS(obj)))
    {
        return ITS_CLASS_CLONE(ITS_OBJ_CLASS(obj))(obj);
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method prints an object.
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
 *      This method is subject to structure packing constraints.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ITS_Print(ITS_Object obj)
{
    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    if (ITS_CLASS_PRINT(ITS_OBJ_CLASS(obj)))
    {
        ITS_CLASS_PRINT(ITS_OBJ_CLASS(obj))(obj);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method prints an object.
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
 *      This needs work to be machine portable.  Right now, such a
 *      beast needs an override for this method in all subclasses.
 *      This method is subject to structure packing constraints.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_OCTET *
ITS_Serialize(ITS_Object obj)
{
    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    if (ITS_CLASS_SERIALIZE(ITS_OBJ_CLASS(obj)))
    {
        return ITS_CLASS_SERIALIZE(ITS_OBJ_CLASS(obj))(obj);
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This determines if an instance is equal to another instance.
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
 *      This method is subject to structure packing constraints.
 *      We only climb the hierarchy for the second object.
 *      NOTE: Should we do this for both objects, looking for a common
 *      ancestor?
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
ITS_Equals(ITS_Object o1, ITS_Object o2)
{
    ITS_C_REQUIRE(o1 != NULL && o2 != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(o1) != NULL && ITS_OBJ_CLASS(o2) != NULL);

    if (ITS_CLASS_EQUALS(ITS_OBJ_CLASS(o1)))
    {
        return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(o1))(o1, o2);
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This determines if an instance is equal to another instance.
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
 *      This method is subject to structure packing constraints.
 *      We only climb the hierarchy for the second object.
 *      NOTE: Should we do this for both objects, looking for a common
 *      ancestor?
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
ITS_Hash(ITS_Object obj)
{
    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    if (ITS_CLASS_HASH(ITS_OBJ_CLASS(obj)))
    {
        return ITS_CLASS_HASH(ITS_OBJ_CLASS(obj))(obj);
    }

    return (0);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method initializes the CORE part of a class.
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
ClassPartInit(ITS_Class objClass)
{
    ITS_Class cl = ITS_CLASS_SUPERCLASS(objClass);

    if (!cl)
    {
        return (ITS_SUCCESS);
    }

    if (ITS_CLASS_CLONE(objClass) == ITS_INST_CLONE_INHERIT)
    {
        ITS_CLASS_CLONE(objClass) = ITS_CLASS_CLONE(cl);
    }
    if (ITS_CLASS_PRINT(objClass) == ITS_INST_PRINT_INHERIT)
    {
        ITS_CLASS_PRINT(objClass) = ITS_CLASS_PRINT(cl);
    }
    if (ITS_CLASS_SERIALIZE(objClass) == ITS_INST_SERIAL_INHERIT)
    {
        ITS_CLASS_SERIALIZE(objClass) = ITS_CLASS_SERIALIZE(cl);
    }
    if (ITS_CLASS_EQUALS(objClass) == ITS_INST_EQUALS_INHERIT)
    {
        ITS_CLASS_EQUALS(objClass) = ITS_CLASS_EQUALS(cl);
    }
    if (ITS_CLASS_HASH(objClass) == ITS_INST_HASH_INHERIT)
    {
        ITS_CLASS_HASH(objClass) = ITS_CLASS_HASH(cl);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys the CORE part of a class.
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
ClassPartDestroy(ITS_Class objClass)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method clones an object.
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
 *      This method is not chained.
 *
 *  See Also:
 ****************************************************************************/
static ITS_Object
Clone(ITS_Object obj)
{
    size_t size;
    ITS_Object ret;

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    size = ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(obj));

    ret = (ITS_Object)calloc(1, size);
    if (ret == NULL)
    {
        return (ret);
    }

    memcpy(ret, obj, size);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method prints an object.
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
 *      This method is subject to structure packing constraints.
 *      This method is not chained.
 *
 *  See Also:
 ****************************************************************************/
static void
Print(ITS_Object obj)
{
    size_t size, i;

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    size = ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(obj));

    for (i = 0; i < size; i++)
    {
        printf("%02x ", ((ITS_OCTET *)obj)[i]);

        if (!((i+1) % 25))
        {
            printf("\n");
        }
    }

    if (!((i+1) % 25))
    {
        printf("\n");
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method serializes an object.
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
 *      This needs work to be machine portable.  Right now, such a
 *      beast needs an override for this method in all subclasses.
 *      This method is subject to structure packing constraints.
 *      This method is not chained.
 *
 *  See Also:
 ****************************************************************************/
static ITS_OCTET *
Serialize(ITS_Object obj)
{
    size_t size;
    ITS_OCTET *ret;

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    size = ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(obj));

    ret = (ITS_OCTET *)calloc(1, size);
    if (ret == NULL)
    {
        return (ret);
    }

    memcpy(ret, obj, size);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This determines if an instance is equal to another instance.
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
 *      This method is subject to structure packing constraints.
 *      We only climb the hierarchy for the second object.
 *      NOTE: Should we do this for both objects, looking for a common
 *      ancestor?
 *      This method is not chained.
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
Equals(ITS_Object o1, ITS_Object o2)
{
    ITS_Class objClass;
    
    ITS_C_REQUIRE(o1 != NULL);
    ITS_C_REQUIRE(o2 != NULL);

    objClass = ITS_OBJ_CLASS(o2);

    while (objClass)
    {
        if (objClass == ITS_OBJ_CLASS(o1))
        {
            break;
        }

        objClass = ITS_CLASS_SUPERCLASS(objClass);
    }

    if (!objClass)
    {
        return (ITS_FALSE);
    }

    if (memcmp(o1, o2, ITS_CLASS_INSTANCE_SIZE(objClass)) == 0)
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This determines if an instance is equal to another instance.
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
 *      This method is subject to structure packing constraints.
 *      We only climb the hierarchy for the second object.
 *      NOTE: Should we do this for both objects, looking for a common
 *      ancestor?
 *
 *  See Also:
 ****************************************************************************/
static ITS_UINT
Hash(ITS_Object obj)
{
    size_t size, i;
    ITS_UINT ret = 0;

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(obj) != NULL);

    size = ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(obj));

    for (i = 0; i < size; i++)
    {
        ret += ((ITS_OCTET *)obj)[i];
        ret *= 43;
    }

    return (ret);
}

ITSDLLAPI ITS_ClassRec itsCORE_ClassRec =
{
    /* core */
    {
        NULL,                   /* no superclass */
        sizeof(ITS_ObjectRec),  /* instance size */
        ITS_FALSE,              /* class not initted */
        0,                      /* initial ref count */
        CORE_CLASS_NAME,        /* class name */
        ITS_CLASS_NO_INIT,      /* class init proc */
        ITS_CLASS_NO_DEST,      /* class destroy proc */
        ClassPartInit,          /* class init proc */
        ClassPartDestroy,       /* class destroy proc */
        ITS_INST_NO_CONST,      /* no constructor */
        ITS_INST_NO_DEST,       /* no destructor */
        Clone,                  /* default clone */
        Print,                  /* default print */
        Serialize,              /* default serialize */
        Equals,                 /* default equals */
        Hash,                   /* default hash */
        NULL                    /* no extension */
    }
};

ITSDLLAPI ITS_Class itsCORE_Class = &itsCORE_ClassRec;

