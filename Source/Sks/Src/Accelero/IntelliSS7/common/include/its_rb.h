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
 * LOG: Revision 7.4  2003/01/30 22:00:50  mmiers
 * LOG: Some fixups.  More work on selectable table types.
 * LOG:
 * LOG: Revision 7.3  2003/01/30 20:46:11  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.2  2003/01/24 20:10:57  mmiers
 * LOG: Fixups
 * LOG:
 * LOG: Revision 7.1  2003/01/22 22:07:22  mmiers
 * LOG: Add redblack tree.  Make hash, splay, and redblack use overrideable
 * LOG: methods for allocation and freeing.  Update tests.
 * LOG:
 * LOG: Revision 1.1  2003/01/21 22:47:57  mmiers
 * LOG: Warning removal, add splay tree class.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_RB_H_)
#define	_ITS_RB_H_

#include <its.h>

#ident "$Id: its_rb.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * comparison function
 */
typedef int (*RB_Comparator)(void *k1, ITS_UINT k1Len,
                             void *k2, ITS_UINT k2Len);

/*
 * structure for a R/B node.  The flags are for internal use
 * only.
 */
typedef struct _redblack_node
{
    struct _redblack_node   *left;
    struct _redblack_node   *right;
    struct _redblack_node   *next;
    struct _redblack_node   *prev;
    struct _redblack_node   *parent;
    void                    *key;
    void                    *data;
    ITS_UINT                klen;
    ITS_UINT                dlen;
    ITS_OCTET   isRed       : 1,
                isInternal  : 1,
                isLeft      : 1,
                isRoot      : 1,
                isHead      : 1;
}
REDBLACK_Node;

/*
 * tree part
 */
typedef struct
{
    REDBLACK_Node       rb;
    ITS_BOOLEAN         allowDups;
    RB_Comparator       keyCompare;
}
REDBLACK_ObjectPart;

/*
 * tree instance record.
 */
typedef struct
{
    ITS_CoreObjectPart  core;
    REDBLACK_ObjectPart redBlack;
}
REDBLACK_TreeRec, *REDBLACK_Tree;

#define RB_NODE(x) \
    ((x)->redBlack.rb)

#define RB_ALLOW_DUPS(x) \
    ((x)->redBlack.allowDups)

#define RB_COMPARE(x) \
    ((x)->redBlack.keyCompare)

typedef int (*RB_IterateEntryProc)(REDBLACK_Node *,
                                   void *in, void *out);

typedef REDBLACK_Node * (*RB_FindNearestProc)(REDBLACK_Tree tree,
                                              void *key, ITS_UINT klen,
                                              int *cmpval);
typedef REDBLACK_Node * (*RB_FindExactProc)(REDBLACK_Tree tree,
                                            void *key, ITS_UINT klen);
typedef REDBLACK_Node * (*RB_InsertPosProc)(REDBLACK_Tree tree,
                                            REDBLACK_Node *n,
                                            void *key, ITS_UINT klen,
                                            void *val, ITS_UINT vlen);
typedef REDBLACK_Node * (*RB_InsertProc)(REDBLACK_Tree tree,
                                         void *key, ITS_UINT klen,
                                         void *val, ITS_UINT vlen);
typedef void            (*RB_DeleteProc)(REDBLACK_Tree tree,
                                         REDBLACK_Node *node);
typedef int             (*RB_IterateProc)(REDBLACK_Tree tree,
                                          void *in, void *out,
                                          RB_IterateEntryProc func);
typedef void *          (*RB_AllocProc)(REDBLACK_Tree tree,
                                        ITS_UINT, ITS_UINT);
typedef void            (*RB_FreeProc)(REDBLACK_Tree tree,
                                       void *);

typedef struct
{
    RB_FindNearestProc  findNearest;
    RB_FindExactProc    findExact;
    RB_InsertPosProc    insertBefore;
    RB_InsertPosProc    insertAfter;
    RB_InsertProc       insert;
    RB_DeleteProc       destroy;
    RB_IterateProc      iterate;
    RB_IterateProc      rIterate;
    RB_AllocProc        alloc;
    RB_FreeProc         free;
}
REDBLACK_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    REDBLACK_ClassPart  rbClass;
}
REDBLACK_ClassRec;

#define REDBLACK_CLASS_NAME   "RED/BLACK TREE CLASS"

#define RB_CLASS_FIND_NEAREST(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.findNearest)

#define RB_CLASS_FIND_EXACT(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.findExact)

#define RB_CLASS_INSERT_BEFORE(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.insertBefore)

#define RB_CLASS_INSERT_AFTER(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.insertAfter)

#define RB_CLASS_INSERT(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.insert)

#define RB_CLASS_DELETE(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.destroy)

#define RB_CLASS_ITERATE(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.iterate)

#define RB_CLASS_RITERATE(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.rIterate)

#define RB_CLASS_ALLOC(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.alloc)

#define RB_CLASS_FREE(x) \
    (((REDBLACK_ClassRec *)(x))->rbClass.free)

ITSDLLAPI extern REDBLACK_ClassRec  itsREDBLACK_ClassRec;
ITSDLLAPI extern ITS_Class          itsREDBLACK_Class;

/*.interface:RB_
 *****************************************************************************
 *  Interface:
 *      RB_*
 *
 *  Purpose:
 *      This interface implements a red/black tree for the user.
 *
 *  Usage:
 *
 *****************************************************************************/

ITSDLLAPI REDBLACK_Tree RB_InitTree(RB_Comparator keyCompare,
                                    ITS_BOOLEAN allowDups);
ITSDLLAPI void          RB_FreeTree(REDBLACK_Tree tree);

ITSDLLAPI REDBLACK_Node *RB_FindNearest(REDBLACK_Tree tree,
                                        void *key, ITS_UINT klen,
                                        int *cmpval);
ITSDLLAPI REDBLACK_Node *RB_FindExact(REDBLACK_Tree tree,
                                      void *key, ITS_UINT klen);
ITSDLLAPI REDBLACK_Node *RB_InsertNodeBefore(REDBLACK_Tree tree,
                                             void *key, ITS_UINT klen,
                                             void *val, ITS_UINT vlen);
ITSDLLAPI REDBLACK_Node *RB_InsertNodeBefore(REDBLACK_Tree tree,
                                             void *key, ITS_UINT klen,
                                             void *val, ITS_UINT vlen);
ITSDLLAPI REDBLACK_Node *RB_InsertNode(REDBLACK_Tree tree,
                                       void *key, ITS_UINT klen,
                                       void *val, ITS_UINT vlen);
ITSDLLAPI void          RB_DeleteNode(REDBLACK_Tree tree,
                                      REDBLACK_Node *node);

ITSDLLAPI int           RB_NumBlack(REDBLACK_Node *node);
ITSDLLAPI int           RB_PathLength(REDBLACK_Node *node);

ITSDLLAPI REDBLACK_Node *RB_FindFirst(REDBLACK_Tree tree);
ITSDLLAPI REDBLACK_Node *RB_FindLast(REDBLACK_Tree tree);
ITSDLLAPI ITS_BOOLEAN   RB_Empty(REDBLACK_Tree tree);
ITSDLLAPI REDBLACK_Node *RB_Nil(REDBLACK_Tree tree);
ITSDLLAPI REDBLACK_Node *RB_FindPrev(REDBLACK_Node *node);
ITSDLLAPI REDBLACK_Node *RB_FindNext(REDBLACK_Node *node);

ITSDLLAPI int   RB_Iterate(REDBLACK_Tree tree,
                           void *in, void *out, RB_IterateEntryProc func);
ITSDLLAPI int   RB_RIterate(REDBLACK_Tree tree,
                            void *in, void *out, RB_IterateEntryProc func);
 
#if defined(__cplusplus)
}
#endif

#endif /* _ITS_RB_H_ */
