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
 * LOG: Revision 8.2  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/01/29 20:56:28  mmiers
 * LOG: 64 bit issues.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.10  2001/04/06 19:44:31  mmiers
 * LOG: Pointer snafu.
 * LOG:
 * LOG: Revision 3.9  2001/04/05 18:58:05  mmiers
 * LOG: Missing align
 * LOG:
 * LOG: Revision 3.8  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.7  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.6  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.5  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.4  2000/08/24 23:06:36  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.3  2000/08/18 02:20:13  mmiers
 * LOG: First implementation of stack MEMPOOL.  Smarten realloc needs to be
 * LOG: done.
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:25:08  mmiers
 * LOG: Add user data to list remove procs.
 * LOG: Add memory pools for quick reclamation.
 * LOG: Add object creation into user supplied buffers.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.17  2000/07/27 22:03:22  mmiers
 * LOG: Last of the core changes for PR3.  Removed last stubs, stack
 * LOG: binding is now dynamic.
 * LOG:
 * LOG: Revision 2.16  2000/03/18 21:03:32  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.15  2000/02/15 21:26:30  mmiers
 * LOG:
 * LOG: Some cursory documentation.
 * LOG:
 * LOG: Revision 2.14  2000/02/15 20:34:43  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.13  2000/02/15 16:37:19  mmiers
 * LOG:
 * LOG: Good enough for a working version.  I have some ideas about cleaning
 * LOG: up the leaks (use ITS_RegisterFeature for the ClassInit).
 * LOG:
 * LOG: Revision 2.12  2000/02/14 19:17:36  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.11  2000/02/01 21:29:23  mmiers
 * LOG:
 * LOG:
 * LOG: Some updates for specific features.
 * LOG:
 * LOG: Revision 2.10  2000/01/26 18:01:22  mmiers
 * LOG:
 * LOG:
 * LOG: Start the feature processing function.
 * LOG:
 * LOG: Revision 2.9  2000/01/26 17:36:30  mmiers
 * LOG:
 * LOG:
 * LOG: Fix feature processing.
 * LOG:
 * LOG: Revision 2.8  2000/01/26 03:04:09  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.7  2000/01/07 23:49:57  fhasle
 * LOG:
 * LOG:
 * LOG: Fix at least two major brain farts.
 * LOG:
 * LOG: Revision 2.6  1999/12/22 02:08:59  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.5  1999/12/20 17:30:19  mmiers
 * LOG: Add more methods to the base object class.
 * LOG:
 * LOG: Revision 2.4  1999/12/17 16:45:14  mmiers
 * LOG:
 * LOG:
 * LOG: Add class init/destruct
 * LOG:
 * LOG: Revision 2.3  1999/12/17 00:40:05  mmiers
 * LOG: Note the trick I found.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 00:52:35  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 02:44:21  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten out the OO stuff for ITS.  This is starting to gel, but
 * LOG: I'm awaiting feedback from Hubert.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:42  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/12/03 22:38:06  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding object patterns for C.  Time to branch the tree.
 * LOG:
 * LOG: Revision 1.1  1999/12/03 22:35:38  mmiers
 * LOG:
 * LOG:
 * LOG: Add the beginnings of the class structure to the support library.
 * LOG: Time to branch the tree.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_OBJECT_H)
#define ITS_OBJECT_H

#include <its.h>
#include <its_types.h>
#include <stdarg.h>

#ident "$Id: its_object.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * basic part of any object (forward decls)
 */
typedef struct _ITS_ClassRec*       ITS_Class;
typedef struct _ITS_ClassExtRec*    ITS_ClassExt;
typedef struct _ITS_ObjectRec*      ITS_Object;

/*
 * proc signatures
 */
typedef int         (*ITS_ClassInitProc)(ITS_Class classRec);
typedef void        (*ITS_ClassDestroyProc)(ITS_Class classRec);
typedef int         (*ITS_ClassPartInitProc)(ITS_Class classRec);
typedef void        (*ITS_ClassPartDestroyProc)(ITS_Class classRec);

typedef int         (*ITS_InstanceConstruct)(ITS_Object, va_list args);
typedef void        (*ITS_InstanceDestruct)(ITS_Object);

typedef ITS_Object  (*ITS_InstanceCloneProc)(ITS_Object);
typedef void        (*ITS_InstancePrintProc)(ITS_Object);
typedef ITS_OCTET*  (*ITS_InstanceSerializeProc)(ITS_Object);
typedef ITS_BOOLEAN (*ITS_InstanceEqualsProc)(ITS_Object, ITS_Object);
typedef ITS_UINT    (*ITS_InstanceHashProc)(ITS_Object);

/*
 * class base.
 */
typedef struct _ITS_CoreClassPart
{
    ITS_Class                   superClass;
    size_t                      instanceSize;
    ITS_BOOLEAN                 classInitted;
    ITS_INT                     classRefCount;
    const char *                className;
    ITS_ClassInitProc           classInit;
    ITS_ClassDestroyProc        classDestroy;
    ITS_ClassPartInitProc       classPartInit;
    ITS_ClassPartDestroyProc    classPartDestroy;
    ITS_InstanceConstruct       instantiate;
    ITS_InstanceDestruct        destroy;
    ITS_InstanceCloneProc       clone;
    ITS_InstancePrintProc       print;
    ITS_InstanceSerializeProc   serialize;
    ITS_InstanceEqualsProc      equals;
    ITS_InstanceHashProc        hash;
    ITS_ClassExt                extension;
}
ITS_CoreClassPart;

/*
 * basic class record.
 */
typedef struct _ITS_ClassRec
{
    ITS_CoreClassPart   coreClass;
}
ITS_ClassRec;

#define ITS_CLASS_SUPERCLASS(x) \
    ((x)->coreClass.superClass)

#define ITS_CLASS_INSTANCE_SIZE(x) \
    ((x)->coreClass.instanceSize)

#define ITS_CLASS_INITTED(x) \
    ((x)->coreClass.classInitted)

#define ITS_CLASS_REF_COUNT(x) \
    ((x)->coreClass.classRefCount)

#define ITS_CLASS_CLASSNAME(x) \
    ((x)->coreClass.className)

#define ITS_CLASS_CONSTRUCTOR(x) \
    ((x)->coreClass.classInit)

#define ITS_CLASS_DESTRUCTOR(x) \
    ((x)->coreClass.classDestroy)

#define ITS_CLASS_PART_CONSTRUCTOR(x) \
    ((x)->coreClass.classPartInit)

#define ITS_CLASS_PART_DESTRUCTOR(x) \
    ((x)->coreClass.classPartDestroy)

#define ITS_CLASS_OBJECT_INSTANTIATE(x) \
    ((x)->coreClass.instantiate)

#define ITS_CLASS_OBJECT_DESTROY(x) \
    ((x)->coreClass.destroy)

#define ITS_CLASS_CLONE(x) \
    ((x)->coreClass.clone)

#define ITS_CLASS_PRINT(x) \
    ((x)->coreClass.print)

#define ITS_CLASS_SERIALIZE(x) \
    ((x)->coreClass.serialize)

#define ITS_CLASS_EQUALS(x) \
    ((x)->coreClass.equals)

#define ITS_CLASS_HASH(x) \
    ((x)->coreClass.hash)

#define ITS_CLASS_EXTENSION(x) \
    ((x)->coreClass.extension)

#define CORE_CLASS_NAME    "CORE"

ITSDLLAPI extern ITS_ClassRec        itsCORE_ClassRec;
ITSDLLAPI extern ITS_Class           itsCORE_Class;

/*
 * method overrides
 */
#define ITS_CLASS_NO_INIT        (ITS_ClassInitProc)NULL
#define ITS_CLASS_NO_DEST        (ITS_ClassDestroyProc)NULL
#define ITS_CLASS_PART_NO_INIT   (ITS_ClassPartInitProc)NULL
#define ITS_CLASS_PART_NO_DEST   (ITS_ClassPartDestroyProc)NULL

#define ITS_INST_NO_CONST        (ITS_InstanceConstruct)NULL
#define ITS_INST_NO_DEST         (ITS_InstanceDestruct)NULL
#define ITS_INST_CLONE_INHERIT   (ITS_InstanceCloneProc)NULL
#define ITS_INST_PRINT_INHERIT   (ITS_InstancePrintProc)NULL
#define ITS_INST_SERIAL_INHERIT  (ITS_InstanceSerializeProc)NULL
#define ITS_INST_EQUALS_INHERIT  (ITS_InstanceEqualsProc)NULL
#define ITS_INST_HASH_INHERIT    (ITS_InstanceHashProc)NULL

/*
 * class extension record.  The presence of this record is
 * not mandatory, but is recommended.
 */
typedef struct _ITS_CoreClassExtPart
{
    ITS_UINT                version;
}
ITS_CoreClassExtPart;

typedef struct _ITS_ClassExtRec
{
    ITS_CoreClassExtPart    coreClassExt;
}
ITS_ClassExtRec;

#define ITS_EXT_VERSION     1U

/*************************************************************/

/*
 * the basic object instance.  The root of all objects.
 */
typedef struct _ITS_CoreObjectPart
{
    ITS_Class       objClass;
    ITS_BOOLEAN     beingDestroyed;
    ITS_BOOLEAN     isDynamic;
}
ITS_CoreObjectPart;

/*
 * assumption: sizeof all pointer types is consistent.  These macros
 * are used to ensure that all objects are aligned at least to the
 * alignment of the first element in an object (the class pointer).
 * 
 * Even if sizeof(ITS_POINTER) > sizeof(ITS_UINT), these macros should
 * work, barring wrapround if (ptr) is too close to MAX_POINTER.
 * Update: nope, not true.  The cast to ITS_UINT blows off the upper
 * bits.
 */
#define ITS_OBJ_ALIGN(ptr)                                                \
    ((ITS_POINTER)(((ITS_ULONG)(ptr) + sizeof(ITS_POINTER) - 1) &          \
     (~(sizeof(ITS_POINTER) - 1))))

#define ITS_OBJ_OFFSET(ptr)                                               \
    (ITS_UINT)(ITS_OBJ_ALIGN(ptr) - (ITS_POINTER)(ptr))

typedef struct _ITS_ObjectRec
{
    ITS_CoreObjectPart  core;
}
ITS_ObjectRec;

#define ITS_OBJ_CLASS(x) \
    (((ITS_Object)(x))->core.objClass)

#define ITS_OBJ_BEING_DESTROYED(x) \
    (((ITS_Object)(x))->core.beingDestroyed)

#define ITS_OBJ_IS_DYNAMIC(x) \
    (((ITS_Object)(x))->core.isDynamic)

#define ITS_OBJ_CLONE(x) \
    (ITS_CLASS_CLONE(x)(x))

#define ITS_OBJ_PRINT(x) \
    (ITS_CLASS_PRINT(x)(x))

#define ITS_OBJ_SERIALIZE(x, b) \
    (ITS_CLASS_SERIALIZE(x)(x, b))

#define ITS_OBJ_EQUALS(x, y) \
    (ITS_CLASS_EQUALS(x)(x, y))

#define ITS_OBJ_HASH(x) \
    (ITS_CLASS_HASH(x)(x))

/*************************************************************/

/*
 * global ctors/dtors.  ITS_GlobalStart() calls the class
 * initialize methods
 *
 * What, you didn't think you could do global ctors in C?
 * Well, there is a way.  Here's how you do it:
 *
 * <file t.h>
 * typedef struct
 * {
 *      int (*foo)();
 * }
 * Init;
 *
 * <file t.c>
 * #include "t.h"
 * Init bar;
 *
 * int main() { if (bar.foo) (*bar.foo)(); return 0; }
 *
 * <file t2.c>
 * #include "t.h"
 *
 * int bum() { printf("Hello, world\n"); return 0; }
 *
 * extern Init bar = { bum };
 *
 * Try it.  Compile only t.c - it will successfully compile,
 * but when run produces no output.  Now compile and link both;
 * you should see "Hello, world" as output.
 *
 * This works on NT, Solaris, OSF.1, Linux, and HPUX.
 *
 * Go figure.
 *
 * So, what we do is realize that this doesn't always work,
 * and use something else.  Sigh.
 */
typedef struct _ITS_FeatureRec
{
    struct _ITS_FeatureRec *next;
    struct _ITS_FeatureRec *prev;
    ITS_Class              objClass;
}
ITS_FeatureRec, *ITS_Feature;

/*.interface:ITS_
 *****************************************************************************
 *  Interface:
 *      ITS_*
 *
 *  Purpose:
 *      This API is used to control the objects subsystem.  It controls
 *      registration, creation and deletion of classes used by the
 *      CORE and support libraries.
 *
 *  Usage:
 *      Subclasses of SUPPORT components should use ITS_AddFeature
 *      as the class initializer (or call it during class initialization).
 *      This keeps the reference counting mechanism in order, ensuring
 *      the classes will be destroyed in the correct order.  In a like
 *      manner, ITS_RemFeature should be used as the class destructor
 *      (or called from the class destructor).
 *
 *      Static features (those added before ITS_GlobalStart is called),
 *      should not be handled this way, as the classes are added manually
 *      and therefore are "preregistered" with the feature system.  It
 *      is good practice to remove the feature (ITS_RemFeature) after
 *      ITS_GlobalStop() has executed.
 *
 *      Classes have three different construct/destruct routines.  The
 *      first is the class constructor.  This method is called exactly
 *      once for each class.  Classes "preregistered" (using ITS_AddFeature)
 *      have their class constructors called during ITS_GlobalStart().
 *      Class destructors are likewise called exactly once, during the
 *      execution of ITS_GlobalStop().
 *
 *      ClassPart constructors and destructors are called for every
 *      subclass of a superclass to initialize the inherited class part
 *      in the subclass.  This allows subclasses to either inherit
 *      class methods from their parent class, or to override the
 *      behavior themselves.
 *
 *      Finally, instance constructors and destructors are called to
 *      create or destroy instances of objects in a single class.
 *
 *      No provision is made for multiple inheritance; this would confuse
 *      the class record offsets too much.
 *
 *****************************************************************************/
ITSDLLAPI extern int ITS_AddFeature(ITS_Class newFeature);
ITSDLLAPI extern void ITS_RemFeature(ITS_Class newClass);
ITSDLLAPI extern ITS_Class ITS_FindFeature(const char *name);

/*
 * these are internal functions that must never be
 * called by the user.
 */
extern int ITS_InitFeatures();
extern void ITS_DestroyFeatures();
extern int ITS_FeatureStart();
extern void ITS_FeatureStop();

/*************************************************************/

/*
 * public API
 */
ITSDLLAPI int         ITS_InitializeClass(ITS_Class objClass);
ITSDLLAPI void        ITS_DestroyClass(ITS_Class objClass);

ITSDLLAPI ITS_Object  ITS_ConstructObject(ITS_Class objClass, ...);
ITSDLLAPI ITS_Object  ITS_ConstructObjectIn(void *region,
                                            ITS_Class objClass,
                                            ...);

ITSDLLAPI void        ITS_DestructObject(ITS_Object object);

ITSDLLAPI ITS_Object  ITS_Clone(ITS_Object);

ITSDLLAPI ITS_UINT    ITS_Hash(ITS_Object object);

ITSDLLAPI void        ITS_Print(ITS_Object object);

ITSDLLAPI ITS_OCTET*  ITS_Serialize(ITS_Object object);

ITSDLLAPI ITS_UINT    ITS_InstanceSize(ITS_Class objClass);

/*
 * ITS_TRUE if o2 shares a class with o1, and classPart(o2) == classPart(o1)
 */
ITSDLLAPI ITS_BOOLEAN ITS_Equals(ITS_Object o1, ITS_Object o2);

/*
 * simple.  Walk the inheritance chain to see if any superclass of
 * "o" equals "c".
 */
ITSDLLAPI ITS_BOOLEAN ITS_IsInstanceOf(ITS_Class c, ITS_Object o);

#if defined(__cplusplus)
}
#endif

#endif /* ITS_OBJECT_H */
