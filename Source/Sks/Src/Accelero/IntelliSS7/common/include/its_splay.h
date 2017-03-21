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
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.4  2003/01/30 20:46:11  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 1.3  2003/01/24 20:10:57  mmiers
 * LOG: Fixups
 * LOG:
 * LOG: Revision 1.2  2003/01/22 22:07:22  mmiers
 * LOG: Add redblack tree.  Make hash, splay, and redblack use overrideable
 * LOG: methods for allocation and freeing.  Update tests.
 * LOG:
 * LOG: Revision 1.1  2003/01/21 22:47:57  mmiers
 * LOG: Warning removal, add splay tree class.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_SPLAY_H)
#define ITS_SPLAY_H

#include <its.h>

#ident "$Id: its_splay.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * key compare
 */
typedef int (*SPLAY_Comparator)(void *k1, ITS_UINT k1len,
                                void *k2, ITS_UINT k2len);

/*
 * Node type.
 */
typedef struct _splay_node
{
    struct _splay_node  *left;
    struct _splay_node  *right;
    struct _splay_node  *next;
    struct _splay_node  *prev;
    struct _splay_node  *parent;
    void                *key;
    void                *data;
    ITS_UINT            klen;
    ITS_UINT            dlen;
}
SPLAY_Node;

/*
 * object part
 */
typedef struct
{
    SPLAY_Node          splay;
    ITS_BOOLEAN         allowDups;
    SPLAY_Comparator    keyCompare;
}
SPLAY_ObjectPart;

/*
 * instance rec
 */
typedef struct
{
    ITS_CoreObjectPart  core;
    SPLAY_ObjectPart    splay;
}
SPLAY_TreeRec, *SPLAY_Tree;

#define SPLAY_NODE(x) \
    ((x)->splay.splay)

#define SPLAY_ALLOW_DUPS(x) \
    ((x)->splay.allowDups)

#define SPLAY_COMPARE(x) \
    ((x)->splay.keyCompare)

/*
 * class ops
 */
typedef int (*SPLAY_IterateEntryProc)(SPLAY_Node *node,
                                      void *in, void *out);

typedef SPLAY_Node *    (*SPLAY_InsertProc)(SPLAY_Tree tree,
                                            void *key, ITS_UINT klen,
                                            void *data, ITS_UINT dlen);
typedef void            (*SPLAY_DeleteProc)(SPLAY_Tree tree,
                                            SPLAY_Node *node);
typedef SPLAY_Node *    (*SPLAY_FindNearestProc)(SPLAY_Tree tree,
                                                 void * key, ITS_UINT klen,
                                                 int *cmpval); 
typedef SPLAY_Node *    (*SPLAY_FindExactProc)(SPLAY_Tree tree,
                                               void *key, ITS_UINT klen); 
typedef int             (*SPLAY_IterateProc)(SPLAY_Tree tree,
                                             void *in, void *out,
                                             SPLAY_IterateEntryProc func);
typedef void *          (*SPLAY_AllocProc)(SPLAY_Tree tree,
                                           ITS_UINT, ITS_UINT);
typedef void            (*SPLAY_FreeProc)(SPLAY_Tree tree,
                                          void *);

/*
 * class record
 */
typedef struct
{
    SPLAY_InsertProc        insert;
    SPLAY_DeleteProc        destroy;
    SPLAY_FindNearestProc   findNearest;
    SPLAY_FindExactProc     findExact;
    SPLAY_IterateProc       iterate;
    SPLAY_IterateProc       rIterate;
    SPLAY_AllocProc         alloc;
    SPLAY_FreeProc          free;
}
SPLAY_ClassPart;

typedef struct
{
    ITS_CoreClassPart       coreClass;
    SPLAY_ClassPart         splayClass;
}
SPLAY_ClassRec;

#define SPLAY_CLASS_INSERT(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.insert)

#define SPLAY_CLASS_DELETE(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.destroy)

#define SPLAY_CLASS_FIND_NEAREST(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.findNearest)

#define SPLAY_CLASS_FIND_EXACT(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.findExact)

#define SPLAY_CLASS_ITERATE(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.iterate)

#define SPLAY_CLASS_RITERATE(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.rIterate)

#define SPLAY_CLASS_ALLOC(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.alloc)

#define SPLAY_CLASS_FREE(cl) \
    (((SPLAY_ClassRec *)(cl))->splayClass.free)

#define SPLAY_CLASS_NAME    "SPLAY TREE CLASS"

extern ITSDLLAPI SPLAY_ClassRec    itsSPLAY_ClassRec;
extern ITSDLLAPI ITS_Class         itsSPLAY_Class;

/*.interface:SPLAY_
 *****************************************************************************
 *  Interface:
 *      SPLAY_*
 *
 *  Purpose:
 *      This interface implements a splay tree for the user.
 *
 *  Usage:
 *
 *****************************************************************************/
ITSDLLAPI SPLAY_Tree    SPLAY_InitSplay(SPLAY_Comparator keyCompare,
                                        ITS_BOOLEAN allowDups);
ITSDLLAPI void          SPLAY_FreeSplay(SPLAY_Tree tree);

ITSDLLAPI SPLAY_Node *  SPLAY_InsertNode(SPLAY_Tree tree,
                                         void *key, ITS_UINT klen,
                                         void *data, ITS_UINT dlen);
ITSDLLAPI void          SPLAY_DeleteNode(SPLAY_Tree tree,
                                         SPLAY_Node *node);

ITSDLLAPI SPLAY_Node *  SPLAY_FindNearest(SPLAY_Tree tree,
                                          void * key, ITS_UINT klen,
                                          int *cmpval); 
ITSDLLAPI SPLAY_Node *  SPLAY_FindExact(SPLAY_Tree tree,
                                        void *key, ITS_UINT klen); 

ITSDLLAPI SPLAY_Node *SPLAY_Root(SPLAY_Tree tree);
ITSDLLAPI SPLAY_Node *SPLAY_FindFirst(SPLAY_Tree tree);
ITSDLLAPI SPLAY_Node *SPLAY_FindLast(SPLAY_Tree tree);
ITSDLLAPI SPLAY_Node *SPLAY_Nil(SPLAY_Tree tree);
ITSDLLAPI ITS_BOOLEAN SPLAY_EmptyP(SPLAY_Tree tree);
ITSDLLAPI SPLAY_Node *SPLAY_FindNext(SPLAY_Node *node);
ITSDLLAPI SPLAY_Node *SPLAY_FindPrev(SPLAY_Node *node);

ITSDLLAPI int SPLAY_Iterate(SPLAY_Tree tree,
                            void *in, void *out, SPLAY_IterateEntryProc func);
ITSDLLAPI int SPLAY_RIterate(SPLAY_Tree tree,
                             void *in, void *out, SPLAY_IterateEntryProc func);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SPLAY_H_ */
