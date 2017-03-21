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
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.7  2003/02/10 19:02:02  mmiers
 * LOG: Enhancements to implementations.
 * LOG:
 * LOG: Revision 7.6  2003/02/06 19:47:22  mmiers
 * LOG: Add a node based hash table with arbitrary keys.  This aligns the
 * LOG: hash table with the redblack and splay tree implementations.
 * LOG: Also fix a few bugs in redblack and splay.
 * LOG:
 * LOG: Revision 7.5  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.4  2003/01/24 20:10:57  mmiers
 * LOG: Fixups
 * LOG:
 * LOG: Revision 7.3  2003/01/22 22:24:05  mmiers
 * LOG: Add export modifier for windows.
 * LOG:
 * LOG: Revision 7.2  2003/01/22 22:07:22  mmiers
 * LOG: Add redblack tree.  Make hash, splay, and redblack use overrideable
 * LOG: methods for allocation and freeing.  Update tests.
 * LOG:
 * LOG: Revision 7.1  2003/01/21 22:47:57  mmiers
 * LOG: Warning removal, add splay tree class.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#include <its.h>
#include <its_assertion.h>
#include <its_splay.h>

#ident "$Id: its_splay.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*
 * shorthand (field overloading).  Only the root (sentinal) node can
 * have a NULL key.
 */
#define IS_SENTINEL(n)  ((n)->key == NULL)

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Rotate nodes about as part of balancing operations
 *
 *  Input Parameters:
 *      node - the node to rotate
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
 ****************************************************************************/
static void
Rotate(SPLAY_Node *node)
{
    SPLAY_Node *parent, *grandparent;

    /* ignore root */
    if (IS_SENTINEL(node->parent))
    {
        return;
    }
    
    parent = node->parent;
    grandparent = parent->parent;

    /* rotate parent around me */
    if (parent->left == node)
    {
        parent->left = node->right;
        if (parent->left != NULL)
        {
            parent->left->parent = parent;
        }
        node->right = parent;
    }
    else if (parent->right == node)
    {
        parent->right = node->left;
        if (parent->right != NULL)
        {
            parent->right->parent = parent;
        }
        node->left = parent;
    }
    else
    {
        /* rotate error: parent's children are not right */
        ITS_C_ASSERT(ITS_FALSE);
    }
    
    parent->parent = node;
    node->parent = grandparent;

    /* rotate me around grandparent */
    if (IS_SENTINEL(grandparent))
    {
        grandparent->parent = node;
    }
    else if (grandparent->left == parent)
    {
        grandparent->left = node;
    }
    else if (grandparent->right == parent)
    {
        grandparent->right = node;
    }
    else
    {
        /* rotate error: grandparent's children are not right */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Resplay this node
 *
 *  Input Parameters:
 *      node - the node to rotate
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
 ****************************************************************************/
static void
Splay(SPLAY_Node *node)
{
    SPLAY_Node *parent, *grandparent;

    /* ignore root */
    if (IS_SENTINEL(node))
    {
        return;
    }
    
    for (;;)
    {
        /* bail at root */
        if (IS_SENTINEL(node->parent))
        {
            return;
        }
        
        parent = node->parent;
        grandparent = parent->parent;
        
        /*
         * If the node's parent is the root of the tree, do one rotation
         */
        if (IS_SENTINEL(grandparent))
        {
            Rotate(node);
        }
        /*
         * If we have a zig-zig, then rotate my parent, then rotate me
         */
        else if ((parent->left  == node && grandparent->left  == parent) ||
                 (parent->right == node && grandparent->right == parent))
        {
            Rotate(parent);
            Rotate(node);
        }
        /*
         * If we have a zig-zag, then rotate me twice
         */
        else
        {
            Rotate(node);
            Rotate(node);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize a splay tree class
 *
 *  Input Parameters:
 *      objClass - the class to initialize
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
 ****************************************************************************/
static int
ClassInit(ITS_Class objClass)
{
    ITS_Class superClass = ITS_CLASS_SUPERCLASS(objClass);

    if (SPLAY_CLASS_INSERT(objClass) == NULL)
    {
        SPLAY_CLASS_INSERT(objClass) = SPLAY_CLASS_INSERT(superClass);
    }
    if (SPLAY_CLASS_DELETE(objClass) == NULL)
    {
        SPLAY_CLASS_DELETE(objClass) = SPLAY_CLASS_DELETE(superClass);
    }
    if (SPLAY_CLASS_FIND_NEAREST(objClass) == NULL)
    {
        SPLAY_CLASS_FIND_NEAREST(objClass) = SPLAY_CLASS_FIND_NEAREST(superClass);
    }
    if (SPLAY_CLASS_FIND_EXACT(objClass) == NULL)
    {
        SPLAY_CLASS_FIND_EXACT(objClass) = SPLAY_CLASS_FIND_EXACT(superClass);
    }
    if (SPLAY_CLASS_ITERATE(objClass) == NULL)
    {
        SPLAY_CLASS_ITERATE(objClass) = SPLAY_CLASS_ITERATE(superClass);
    }
    if (SPLAY_CLASS_RITERATE(objClass) == NULL)
    {
        SPLAY_CLASS_RITERATE(objClass) = SPLAY_CLASS_RITERATE(superClass);
    }
    if (SPLAY_CLASS_ALLOC(objClass) == NULL)
    {
        SPLAY_CLASS_ALLOC(objClass) = SPLAY_CLASS_ALLOC(superClass);
    }
    if (SPLAY_CLASS_FREE(objClass) == NULL)
    {
        SPLAY_CLASS_FREE(objClass) = SPLAY_CLASS_FREE(superClass);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a splay tree class
 *
 *  Input Parameters:
 *      objClass - the class to initialize
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
 ****************************************************************************/
static void
ClassDest(ITS_Class objClass)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to insert into
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
 ****************************************************************************/
static int
Initialize(ITS_Object obj, va_list alist)
{
    SPLAY_Tree tree = (SPLAY_Tree)obj;
    SPLAY_Comparator keyCompare;
    ITS_BOOLEAN allowDups;

    keyCompare = va_arg(alist, SPLAY_Comparator);
    allowDups = va_arg(alist, ITS_BOOLEAN);

    SPLAY_NODE(tree).key = NULL;
    SPLAY_NODE(tree).data = NULL;

    SPLAY_NODE(tree).next = &SPLAY_NODE(tree);
    SPLAY_NODE(tree).prev = &SPLAY_NODE(tree);

    SPLAY_NODE(tree).left = NULL;
    SPLAY_NODE(tree).right = NULL;
    SPLAY_NODE(tree).parent = NULL;

    SPLAY_COMPARE(tree) = keyCompare;
    SPLAY_ALLOW_DUPS(tree) = allowDups;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to insert into
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
 ****************************************************************************/
static void
Terminate(ITS_Object obj)
{
    SPLAY_Tree tree = (SPLAY_Tree)obj;
    SPLAY_Node *ptr;
    
    for (;;)
    {
        ptr = SPLAY_FindFirst(tree);

        if (!IS_SENTINEL(ptr))
        {
            SPLAY_DeleteNode(tree, ptr);
        }
        else
        {
            return;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Insert a node into a known location in a splay tree.
 *
 *  Input Parameters:
 *      tree - the tree to insert into
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
 ****************************************************************************/
static SPLAY_Node *
SplayInsert(SPLAY_Tree tree,
            void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    SPLAY_Node *s;
    SPLAY_Node *parent;
    int cmpval;

    /* protect against bad keys */
    ITS_C_ASSERT(key != NULL && klen != 0);

    /* protect against bad trees */
    parent = SPLAY_CLASS_FIND_NEAREST(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                           &cmpval);
    if (parent == NULL)
    {
        return (NULL);
    }

    /* dups? */
    if (!SPLAY_ALLOW_DUPS(tree) && cmpval == 0)
    {
        return (NULL);
    }

    /* allocate stuff */
    s = (SPLAY_Node *)SPLAY_CLASS_ALLOC(ITS_OBJ_CLASS(tree))(tree,
                                                             1, sizeof(SPLAY_Node));
    if (s == NULL)
    {
        return (NULL);
    }
    s->key = SPLAY_CLASS_ALLOC(ITS_OBJ_CLASS(tree))(tree, 1, klen);
    if (s->key == NULL)
    {
        SPLAY_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, s);

        return (NULL);
    }

    if (vlen)
    {
        s->data = SPLAY_CLASS_ALLOC(ITS_OBJ_CLASS(tree))(tree, 1, vlen);
        if (s->data == NULL)
        {
            SPLAY_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, s->key);
            SPLAY_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, s);

            return (NULL);
        }
    }

    memcpy(s->key, key, klen);
    if (vlen && val)
    {
        memcpy(s->data, val, vlen);
    }
    s->klen = klen;
    s->dlen = vlen;

    s->parent = parent;
    s->left = NULL;
    s->right = NULL;

    /*
     * Set the parent's correct child pointer.  The only subtle case here
     * is when the key is already in the tree -- then we need to find a
     * leaf node to use as a parent
     */
    
    /*
     * When we're done here, parent should point to the new node's
     * successor in the linked list
     */
    if (IS_SENTINEL(parent))
    {
        parent->parent = s;
    }
    else
    {
        if (cmpval == 0)
        {
            /*
             * If the key is already in the tree, try to insert a new one
             * as the node's right child.  If the node already has a right
             * child, then try to insert the new one as a left child.  If
             * there is already a left child, then go to parent-next and
             * insert the node as its left child.
             */
            if (parent->right == NULL)
            {
                cmpval = 1;
            }
            else if (parent->left == NULL)
            {
                cmpval = -1;
            }
            else
            {
                parent = parent->next;
                s->parent = parent;
                cmpval = -1;
            }
        }

        /* Insert as right child */
        if (cmpval > 0)
        {
            if (parent->right != NULL)
            {
                /* SPLAY_Insert error: parent->right != NULL */
                ITS_C_ASSERT(ITS_FALSE);
            }

            parent->right = s;
            parent = parent->next;
        }
        else
        {
            if (parent->left != NULL)
            {
                /* SPLAY_Insert error: parent->left != NULL */
                ITS_C_ASSERT(ITS_FALSE);
            }

            parent->left = s;
        }
    }
    
    s->next = parent;
    s->prev = parent->prev;
    s->next->prev = s;
    s->prev->next = s;

    Splay(s);

    return (s);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete a known node from the splay tree.
 *
 *  Input Parameters:
 *      tree - the tree to insert into
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
 ****************************************************************************/
static void
SplayDelete(SPLAY_Tree tree, SPLAY_Node *node)
{
    SPLAY_Node *left, *right, *newroot;
    
    Splay(node);

    ITS_C_ASSERT(&SPLAY_NODE(tree) == node->parent);

    left = node->left;
    right = node->right;
    newroot = node->next;
    
    node->next->prev = node->prev;
    node->prev->next = node->next;

    SPLAY_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, node->data);
    SPLAY_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, node->key);
    SPLAY_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, node);
    
    if (right == NULL && left == NULL)
    {
        SPLAY_NODE(tree).parent = NULL;
    }
    else if (right == NULL)
    {
        SPLAY_NODE(tree).parent = left;
        left->parent = &SPLAY_NODE(tree);
    }
    else if (left == NULL)
    {
        SPLAY_NODE(tree).parent = right;
        right->parent = &SPLAY_NODE(tree);
    }
    else
    {
        SPLAY_NODE(tree).parent = right;
        right->parent = &SPLAY_NODE(tree);

        Splay(newroot);

        newroot->left = left;
        left->parent = newroot;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the nearest node to a key value
 *
 *  Input Parameters:
 *      tree - the tree to insert into
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
 ****************************************************************************/
static SPLAY_Node *
SplayFindNearest(SPLAY_Tree tree, void *key, ITS_UINT klen, int *cmpval)
{
    SPLAY_Node *s, *last;
    int cmp;
    
    last = &SPLAY_NODE(tree);
    s = SPLAY_Root(tree);
    cmp = 1;
    
    while (s != NULL)
    {
        last = s;

        cmp = (*SPLAY_COMPARE(tree))(key, klen, s->key, s->klen);

        if (cmp == 0)
        {
            *cmpval = 0;

            return s;
        }
        else if (cmp < 0)
        {
            s = s->left;
        }
        else
        {
            s = s->right;
        }
    }
    
    *cmpval = cmp;

    return last;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the exact key match to that passed in
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
static SPLAY_Node *
SplayFindExact(SPLAY_Tree tree, void *key, ITS_UINT klen)
{
    int cmpval;
    SPLAY_Node *s;
    
    s = SPLAY_CLASS_FIND_NEAREST(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                      &cmpval);

    Splay(s);

    if (cmpval == 0)
    {
        return (s);
    }

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Forward iterate a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
static int
SplayIterate(SPLAY_Tree tree,
             void *in, void *out, SPLAY_IterateEntryProc func)
{
    SPLAY_Node *ptr;
    int ret = ITS_SUCCESS;

    for (ptr = SPLAY_FindFirst(tree);
         ptr != SPLAY_Nil(tree);
         ptr = SPLAY_FindNext(ptr))
    {
        ret = (func)(ptr, in, out);

        if (ret != ITS_SUCCESS)
        {
            break;
        }
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Forward iterate a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
static int
SplayRIterate(SPLAY_Tree tree,
              void *in, void *out, SPLAY_IterateEntryProc func)
{
    SPLAY_Node *ptr;
    int ret = ITS_SUCCESS;

    for (ptr = SPLAY_FindLast(tree);
         ptr != SPLAY_Nil(tree);
         ptr = SPLAY_FindPrev(ptr))
    {
        ret = (func)(ptr, in, out);

        if (ret != ITS_SUCCESS)
        {
            break;
        }
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Allocate for a tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
static void *
Alloc(SPLAY_Tree tree, ITS_UINT n, ITS_UINT size)
{
    return calloc(n, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free for a tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
static void
Free(SPLAY_Tree tree, void *data)
{
    free(data);
}

/*
 * the class record
 */
ITSDLLAPI SPLAY_ClassRec itsSPLAY_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        sizeof(SPLAY_Tree),             /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        SPLAY_CLASS_NAME,               /* class name */
        ClassInit,                      /* class init */
        ClassDest,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        Initialize,                     /* instance create */
        Terminate,                      /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* splay part */
    {
        SplayInsert,                    /* insert new node */
        SplayDelete,                    /* delete known node */
        SplayFindNearest,               /* find nearest node */
        SplayFindExact,                 /* find exact node */
        SplayIterate,                   /* forward iterate */
        SplayRIterate,                  /* reverse iterate */
        Alloc,                          /* alloc */
        Free                            /* free */
    }
};

ITSDLLAPI ITS_Class itsSPLAY_Class = (ITS_Class)&itsSPLAY_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create a new splay tree
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Tree 
SPLAY_InitSplay(SPLAY_Comparator keyCompare, ITS_BOOLEAN allowDups)
{
    return (SPLAY_Tree)ITS_ConstructObject(itsSPLAY_Class,
                                           keyCompare,
                                           allowDups);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to delete
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
 ****************************************************************************/
ITSDLLAPI void
SPLAY_FreeSplay(SPLAY_Tree tree)
{
    ITS_DestructObject((ITS_Object)tree);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return a pointer to the root node of a splay
 *
 *  Input Parameters:
 *      tree - the tree to return the root for.
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_Root(SPLAY_Tree tree)
{
    return (SPLAY_NODE(tree).parent);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return a pointer to the first entry in a splay
 *
 *  Input Parameters:
 *      tree - the tree to return the first node for
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_FindFirst(SPLAY_Tree tree)
{
    return (SPLAY_NODE(tree).next);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return a pointer to the last entry in a splay
 *
 *  Input Parameters:
 *      tree - the tree to return the last entry for
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_FindLast(SPLAY_Tree tree)
{
    return (SPLAY_NODE(tree).prev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Given a node, return a pointer to the next key's node
 *
 *  Input Parameters:
 *      node - the node to return next for
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_FindNext(SPLAY_Node *node)
{
    return (node->next);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Given a node, return a pointer to the prev key's node
 *
 *  Input Parameters:
 *      node - the node to return prev for
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_FindPrev(SPLAY_Node *node)
{
    return (node->prev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      No operation.
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_Nil(SPLAY_Tree tree)
{
    return (&SPLAY_NODE(tree));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      No operation.
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SPLAY_EmptyP(SPLAY_Tree tree)
{
    return (SPLAY_NODE(tree).parent == NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Insert a node into a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_InsertNode(SPLAY_Tree tree,
                 void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    return SPLAY_CLASS_INSERT(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                   val, vlen);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Insert a node into a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI void
SPLAY_DeleteNode(SPLAY_Tree tree, SPLAY_Node *node)
{
    SPLAY_CLASS_DELETE(ITS_OBJ_CLASS(tree))(tree, node);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the nearest key to that passed in
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_FindNearest(SPLAY_Tree tree, void *key, ITS_UINT klen,
                  int *cmpval)
{
    return SPLAY_CLASS_FIND_NEAREST(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                         cmpval);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the exact key match to that passed in
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI SPLAY_Node *
SPLAY_FindExact(SPLAY_Tree tree, void *key, ITS_UINT klen)
{
    return SPLAY_CLASS_FIND_EXACT(ITS_OBJ_CLASS(tree))(tree, key, klen);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Forward iterate a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI int
SPLAY_Iterate(SPLAY_Tree tree,
              void *in, void *out, SPLAY_IterateEntryProc func)
{
    return SPLAY_CLASS_ITERATE(ITS_OBJ_CLASS(tree))(tree, in, out, func);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Reverse iterate a splay tree
 *
 *  Input Parameters:
 *      tree - the tree to return
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
 ****************************************************************************/
ITSDLLAPI int
SPLAY_RIterate(SPLAY_Tree tree,
               void *in, void *out, SPLAY_IterateEntryProc func)
{
    return SPLAY_CLASS_RITERATE(ITS_OBJ_CLASS(tree))(tree, in, out, func);
}

