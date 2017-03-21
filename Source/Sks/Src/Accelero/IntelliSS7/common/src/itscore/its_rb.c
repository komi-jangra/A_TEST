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
 * LOG: Revision 8.4  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6  2003/02/10 19:02:02  mmiers
 * LOG: Enhancements to implementations.
 * LOG:
 * LOG: Revision 7.5  2003/02/06 19:47:22  mmiers
 * LOG: Add a node based hash table with arbitrary keys.  This aligns the
 * LOG: hash table with the redblack and splay tree implementations.
 * LOG: Also fix a few bugs in redblack and splay.
 * LOG:
 * LOG: Revision 7.4  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.3  2003/01/24 20:10:57  mmiers
 * LOG: Fixups
 * LOG:
 * LOG: Revision 7.2  2003/01/22 22:25:09  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 7.1  2003/01/22 22:07:22  mmiers
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
#include <its_rb.h>

#ident "$Id: its_rb.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*
 * information hiding.  The user doesn't care about these.
 */
#define IsRed(n)            ((n)->isRed)
#define IsBlack(n)          (!IsRed(n))
#define IsLeft(n)           ((n)->isLeft)
#define IsRight(n)          (!IsLeft(n))
#define IsInternal(n)       ((n)->isInternal)
#define IsExternal(n)       (!IsInternal(n))
#define IsHead(n)           ((n)->isHead)
#define IsRoot(n)           ((n)->isRoot)

#define SetRed(n)           ((n)->isRed = 1)
#define SetBlack(n)         ((n)->isRed = 0)
#define SetLeft(n)          ((n)->isLeft = 1)
#define SetRight(n)         ((n)->isLeft = 0)
#define SetHead(n)          ((n)->isHead = 1)
#define SetRoot(n)          ((n)->isRoot = 1)
#define SetInternal(n)      ((n)->isInternal = 1)
#define SetExternal(n)      ((n)->isInternal = 0)
#define SetNormal(n)        ((n)->isRoot = 0, (n)->isHead = 0)

#define GetSibling(n) \
    ((IsLeft(n)) ? ((n)->parent->prev) : ((n)->parent->next))

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Link a node into a list
 *
 *  Input Parameters:
 *      node - the node to insert
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
InsertItem(REDBLACK_Node *item, REDBLACK_Node *list)
{
    REDBLACK_Node *last_node;
    
    last_node = list->prev;
    
    list->prev = item;
    last_node->next = item;
    item->prev = last_node;
    item->next = list;
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete a node from the list
 *
 *  Input Parameters:
 *      node - the node to insert
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
DeleteItem(REDBLACK_Node *item)
{
    item->next->prev = item->prev;
    item->prev->next = item->next;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Perform a single rotation on a node.
 *
 *  Input Parameters:
 *      node - the node to insert
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
SingleRotate(REDBLACK_Node *n, int toLeft)
{
    int nIsLeft, nIsRoot;
    REDBLACK_Node *other, *np;

    nIsRoot = IsRoot(n);
    np = n->parent;

    if (!nIsRoot)
    {
        nIsLeft = IsLeft(n);
    }
    
    if (toLeft)
    {
        other = n->next;
        n->next = other->prev;

        SetLeft(n->next);

        n->next->parent = n;
        other->prev = n;

        SetRight(n);  
    }
    else
    {
        other = n->prev;
        n->prev = other->next;

        SetRight(n->prev);

        n->prev->parent = n;
        other->next = n;

        SetLeft(n);  
    }
    
    other->parent = np;
    n->parent = other;

    if (nIsRoot)
    {
        np->parent = other;

        SetNormal(n);
        SetRoot(other);
    }
    else
    {
        if (nIsLeft)
        {
            np->next = other;

            SetLeft(other);
        }
        else
        {
            np->prev = other;

            SetRight(other);
        }
    }
}
    
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Recolor a redblack tree
 *
 *  Input Parameters:
 *      node - the node to insert
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
Recolor(REDBLACK_Node *n)
{  
    REDBLACK_Node *p, *gp, *s;
    
    for (;;)
    {
        if (IsRoot(n))
        {
            SetBlack(n);

            return;
        }
        
        p = n->parent;
        
        if (IsBlack(p))
        {
            return;
        }
        
        if (IsRoot(p))
        {
            SetBlack(p);

            return;
        }
        
        gp = p->parent;
        s = GetSibling(p);

        if (IsRed(s))
        {
            SetBlack(p);
            SetRed(gp);
            SetBlack(s);

            n = gp;
        }
        else
        {
            break;
        }
    }

    /*
     * at this point, p's sibling is black, p is red, and gp is black
     */
    if (!IsLeft(n) && !IsLeft(p))
    {
        SingleRotate(gp, IsLeft(n));

        SetBlack(p);
        SetRed(gp);
    }
    else
    {
        SingleRotate(p, IsLeft(n));
        SingleRotate(gp, IsLeft(n));

        SetBlack(n);
        SetRed(gp);
    }
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Make a new internal node
 *
 *  Input Parameters:
 *      node - the node to insert
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
static REDBLACK_Node *
NewExternalNode(REDBLACK_Tree tree,
                void *key, ITS_UINT klen,
                void *val, ITS_UINT vlen)
{
    REDBLACK_Node *newnode;

    /* protect against bad keys */
    ITS_C_ASSERT(key != NULL && klen != 0);

    newnode = (REDBLACK_Node *)
        RB_CLASS_ALLOC(ITS_OBJ_CLASS(tree))(tree, 1, sizeof(REDBLACK_Node));
    if (newnode == NULL)
    {
        return (NULL);
    }

    newnode->key = RB_CLASS_ALLOC(ITS_OBJ_CLASS(tree))(tree, 1, klen);
    if (newnode->key == NULL)
    {
        RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, newnode);

        return (NULL);
    }
    if (vlen)
    {
        newnode->data = RB_CLASS_ALLOC(ITS_OBJ_CLASS(tree))(tree, 1, klen);
        if (newnode->data == NULL)
        {
            RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, newnode->key);
            RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, newnode);

            return (NULL);
        }
    }

    memcpy(newnode->key, key, klen);
    if (vlen && val)
    {
        memcpy(newnode->data, val, vlen);
    }

    newnode->klen = klen;
    newnode->dlen = vlen;

    SetExternal(newnode);
    SetBlack(newnode);
    SetNormal(newnode);

    return (newnode);
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Make a new internal node
 *
 *  Input Parameters:
 *      node - the node to insert
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
static REDBLACK_Node *
NewInternalNode(REDBLACK_Tree tree,
                REDBLACK_Node *left, REDBLACK_Node *right,
                REDBLACK_Node *parent, int isLeft)
{
    REDBLACK_Node *newnode;
    
    newnode = (REDBLACK_Node *)
        RB_CLASS_ALLOC(ITS_OBJ_CLASS(tree))(tree, 1, sizeof(REDBLACK_Node));
    if (newnode == NULL)
    {
        return (NULL);
    }

    SetInternal(newnode);
    SetRed(newnode);
    SetNormal(newnode);

    newnode->next = left;
    newnode->prev = right;
    newnode->parent = parent;

    newnode->left = left;
    newnode->right = right;

    left->parent = newnode;
    right->parent = newnode;

    SetLeft(left);
    SetRight(right);

    if (IsHead(parent))
    {
        parent->parent = newnode;

        SetRoot(newnode);
    }
    else if (isLeft)
    {
        SetLeft(newnode);

        parent->next = newnode;
    }
    else
    {
        SetRight(newnode);

        parent->prev = newnode;
    }
    
    Recolor(newnode);

    return (newnode);
}  
  
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the closest left node above
 *
 *  Input Parameters:
 *      node - the node to insert
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
REDBLACK_Node *
FindPrevLeft(REDBLACK_Node *n)
{
    if (IsHead(n))
    {
        return (n);
    }

    while (!IsRoot(n))
    {
        if (IsRight(n))
        {
            return (n->parent);
        }
        
        n = n->parent;
    }
    
    return (n->parent);
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the closest right node above.
 *
 *  Input Parameters:
 *      node - the node to insert
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
REDBLACK_Node *
FindPrevRight(REDBLACK_Node *n)
{
    if (IsHead(n))
    {
        return (n);
    }

    while (!IsRoot(n))
    {
        if (IsLeft(n))
        {
            return (n->parent);
        }

        n = n->parent;
    }

    return (n->parent);
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize a redblack class rec
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
static int
ClassInit(ITS_Class objClass)
{
    ITS_Class superClass = ITS_CLASS_SUPERCLASS(objClass);

    if (RB_CLASS_ALLOC(objClass) == NULL)
    {
        RB_CLASS_ALLOC(objClass) = RB_CLASS_ALLOC(superClass);
    }
    if (RB_CLASS_FREE(objClass) == NULL)
    {
        RB_CLASS_FREE(objClass) = RB_CLASS_FREE(superClass);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a redblack class rec
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
static void
ClassDest(ITS_Class objClass)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize a new redblack tree.
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
static int
Initialize(ITS_Object obj, va_list alist)
{
    REDBLACK_Tree tree = (REDBLACK_Tree)obj;
    RB_Comparator keyCompare;
    ITS_BOOLEAN allowDups;

    keyCompare = va_arg(alist, RB_Comparator);
    allowDups = va_arg(alist, ITS_BOOLEAN);

    RB_NODE(tree).left = NULL;
    RB_NODE(tree).right = NULL;
    RB_NODE(tree).next = &RB_NODE(tree);
    RB_NODE(tree).prev = &RB_NODE(tree);
    RB_NODE(tree).parent = &RB_NODE(tree);

    RB_NODE(tree).key = NULL;
    RB_NODE(tree).data = NULL;
    RB_NODE(tree).klen = 0;
    RB_NODE(tree).dlen = 0;

    RB_COMPARE(tree) = keyCompare;
    RB_ALLOW_DUPS(tree) = allowDups;

    SetHead(&RB_NODE(tree));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a redblack tree
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
static void
Terminate(ITS_Object obj)
{
    REDBLACK_Tree tree = (REDBLACK_Tree)obj;

    ITS_C_ASSERT(IsHead(&RB_NODE(tree)));
    
    while (RB_FindFirst(tree) != RB_Nil(tree))
    {
        RB_CLASS_DELETE(ITS_OBJ_CLASS(tree))(tree, RB_FindFirst(tree));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the closest item in a redblack tree
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
static REDBLACK_Node *
FindNearest(REDBLACK_Tree tree, void *key, ITS_UINT klen, int *cmpval)
{
    int cmp;
    REDBLACK_Node *n = &RB_NODE(tree);
    
    *cmpval = 1;

    ITS_C_ASSERT(IsHead(n));

    if (n->parent == n)
    {
        return (n);
    }

    cmp = (*RB_COMPARE(tree))(key, klen, n->prev->key, n->prev->klen);
    if (cmp == 0)
    {
        *cmpval = 0;

        return (n->prev); 
    }

    if (cmp > 0)
    {
        return (n); 
    }

    n = n->parent;

    for (;;)
    {
        if (IsExternal(n))
        {
            return (n);
        }

        cmp = (*RB_COMPARE(tree))(key, klen, n->left->key, n->left->klen);
        if (cmp == 0)
        {
            *cmpval = 0;

            return (n->left);
        }

        if (cmp < 0)
        {
            *cmpval = -1;

            n = n->next;
        }
        else
        {
            *cmpval = 1;

            n = n->prev;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the exact item in a redblack tree
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
static REDBLACK_Node *
FindExact(REDBLACK_Tree tree, void *key, ITS_UINT klen)
{
    int cmpval;
    REDBLACK_Node *n;
    
    n = RB_CLASS_FIND_NEAREST(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                   &cmpval);
    if (cmpval)
    {
        return (n);
    }
    
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Insert a node before this node
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
static REDBLACK_Node *
InsertBefore(REDBLACK_Tree tree, REDBLACK_Node *n,
             void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    REDBLACK_Node *newleft, *newright, *newnode, *p, *i;
    
    if (IsHead(n))
    {
        /* Tree is empty? */
        if (n->parent == n)
        {
            newnode = NewExternalNode(tree, key, klen, val, vlen);
            if (newnode == NULL)
            {
                return (NULL);
            }
            
            InsertItem(newnode, n);
            
            n->parent = newnode;
            newnode->parent = n;
            
            SetRoot(newnode);
            
            return (newnode);
        }
        
        /* not empty */
        newright = NewExternalNode(tree, key, klen, val, vlen);
        if (newright == NULL)
        {
            return (NULL);
        }

        InsertItem(newright, n);

        newleft = newright->prev;

        SetNormal(newleft);

        i = NewInternalNode(tree, newleft, newright,
                            newleft->parent, IsLeft(newleft));
        if (i == NULL)
        {
            DeleteItem(newright);

            return (NULL);
        }

        p = FindPrevRight(newright);

        if (!IsHead(p))
        {
            p->left = newright;
        }

        return (newright);
    }

    /* not head */
    newleft = NewExternalNode(tree, key, klen, val, vlen);
    if (newleft == NULL)
    {
        return (NULL);
    }

    InsertItem(newleft, n);

    SetNormal(n);

    i = NewInternalNode(tree, newleft, n,
                        n->parent, IsLeft(n));
    if (i == NULL)
    {
        DeleteItem(newleft);

        return (NULL);
    }

    p = FindPrevLeft(newleft);

    if (!IsHead(p))
    {
        p->right = newleft;
    }

    return (newleft);    
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Insert a node after this node
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
static REDBLACK_Node *
InsertAfter(REDBLACK_Tree tree, REDBLACK_Node *n,
            void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    return RB_CLASS_INSERT_BEFORE(ITS_OBJ_CLASS(tree))(tree, n->next,
                                                       key, klen, val, vlen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Insert this value into the tree
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
static REDBLACK_Node *
InsertNode(REDBLACK_Tree tree,
           void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    REDBLACK_Node *n;
    int cmpval;

    n = RB_CLASS_FIND_NEAREST(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                   &cmpval);

    if (!RB_ALLOW_DUPS(tree) && cmpval == 0)
    {
        return (NULL);
    }

    return RB_CLASS_INSERT_BEFORE(ITS_OBJ_CLASS(tree))(tree, n, key, klen,
                                                       val, vlen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete a leaf node from the tree
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
static void
DeleteNode(REDBLACK_Tree tree, REDBLACK_Node *n)
{
    REDBLACK_Node *s, *p, *gp, *x, *z;
    int isRed, isLeft;
    
    ITS_C_ASSERT(!IsInternal(n));
    ITS_C_ASSERT(!IsHead(n));

    DeleteItem(n);

    p = n->parent;
    /* The only node */
    if (IsRoot(n))
    {
        p->parent = p;

        RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, n);

        return;
    }

    /* The only node after deletion? */
    s = GetSibling(n);
    if (IsRoot(p))
    {
        s->parent = p->parent;
        s->parent->parent = s;

        SetRoot(s);

        RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, p);
        RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, n);

        return;
    }

    /* Set parent to sibling */
    gp = p->parent;
    s->parent = gp;

    if (IsLeft(p))
    {
        gp->next = s;

        SetLeft(s);
    }
    else
    {
        gp->prev = s;

        SetRight(s);
    }

    isRed = IsRed(p);

    RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, p);
    RB_CLASS_FREE(ITS_OBJ_CLASS(tree))(tree, n);
    
    /* Update proper rext and lext values */
    if (IsExternal(s))
    {
        p = FindPrevLeft(s); 
        if (!IsHead(p))
        {
            p->right = s;
        }

        p = FindPrevRight(s);
        if (!IsHead(p))
        {
            p->left = s;
        }
    }
    else if (!IsBlack(s))
    {
        p = FindPrevLeft(s);
        if (!IsHead(p))
        {
            p->right = s->next;
        }

        p = FindPrevRight(s);
        if (!IsHead(p))
        {
            p->left = s->prev;
        }

        SetBlack(s);

        return;
    }
    else
    {
        /* "Deletion Problem: Sibling is black, but an internal node */
        ITS_C_ASSERT(ITS_FALSE);
    }
    
    if (isRed)
    {
        return;
    }
    
    /*
     * Recoloring is needed
     */
    n = s;
    p = n->parent;
    s = GetSibling(n);

    while (IsBlack(p) && IsBlack(s) && IsInternal(s) && 
           IsBlack(s->next) && IsBlack(s->prev))
    {
        SetRed(s);

        n = p;

        if (IsRoot(n))
        {
            return;
        }

        p = n->parent;
        s = GetSibling(n);
    }
    
    /* Rotation 2.3b */
    if (IsBlack(p) && IsRed(s))
    {
        SingleRotate(p, IsRight(n));

        SetRed(p);
        SetBlack(s);

        s = GetSibling(n);
    }
    
    /* Sibling is not internal? */
    ITS_C_ASSERT(!IsExternal(s));
    
    isLeft = IsLeft(n);
    x = isLeft ? s->next : s->prev;
    z = GetSibling(x);
    
    /* Rotation 2.3f */
    if (IsRed(z))
    {
        SingleRotate(p, !isLeft);

        SetBlack(z);

        if (IsRed(p))
        {
            SetRed(s);
        }
        else
        {
            SetBlack(s);
        }

        SetBlack(p);
    }
    /* Recoloring only (2.3c) */
    else if (IsBlack(x))
    {
        ITS_C_ASSERT(!IsRed(s) && !IsBlack(p));

        SetBlack(p);
        SetRed(s);

        return;
    }
    /* 2.3d */
    else if (IsRed(p))
    {
        SingleRotate(s, isLeft);
        SingleRotate(p, !isLeft);

        SetBlack(x);
        SetRed(s);

        return;
    }
    /* 2.3e */
    else
    {
        SingleRotate(s, isLeft);
        SingleRotate(p, !isLeft);

        SetBlack(x);

        return;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Forward iterate over the tree
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
static int
Iterate(REDBLACK_Tree tree, void *in, void *out, RB_IterateEntryProc func)
{
    REDBLACK_Node *ptr;
    int ret = ITS_SUCCESS;

    for (ptr = RB_FindFirst(tree);
         ptr != RB_Nil(tree);
         ptr = RB_FindNext(ptr))
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
 *      Reverse iterate over the tree
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
static int
RIterate(REDBLACK_Tree tree, void *in, void *out, RB_IterateEntryProc func)
{
    REDBLACK_Node *ptr;
    int ret = ITS_SUCCESS;

    for (ptr = RB_FindLast(tree);
         ptr != RB_Nil(tree);
         ptr = RB_FindPrev(ptr))
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
 *      Allocate for the tree
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
static void *
Alloc(REDBLACK_Tree tree, ITS_UINT count, ITS_UINT size)
{
    return calloc(count, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free for the tree
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
static void
Free(REDBLACK_Tree tree, void *data)
{
    free(data);
}

/*
 * the class record
 */
ITSDLLAPI REDBLACK_ClassRec itsREDBLACK_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        sizeof(REDBLACK_Tree),          /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        REDBLACK_CLASS_NAME,            /* class name */
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
    /* redblack part */
    {
        FindNearest,                    /* find nearest match */
        FindExact,                      /* find exact match */
        InsertBefore,                   /* insert before node */
        InsertAfter,                    /* insert after node */
        InsertNode,                     /* insert in order */
        DeleteNode,                     /* remove node from tree */
        Iterate,                        /* forward iterate */
        RIterate,                       /* reverse iterate */
        Alloc,                          /* alloc */
        Free                            /* free */
    }
};

ITSDLLAPI ITS_Class itsREDBLACK_Class = (ITS_Class)&itsREDBLACK_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Make a new redblack tree
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
ITSDLLAPI REDBLACK_Tree 
RB_InitTree(RB_Comparator keyCompare, ITS_BOOLEAN allowDups)
{
    return (REDBLACK_Tree)ITS_ConstructObject(itsREDBLACK_Class,
                                              keyCompare,
                                              allowDups);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Destroy a redblack tree
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
ITSDLLAPI void
RB_FreeTree(REDBLACK_Tree tree)
{
    ITS_DestructObject((ITS_Object)tree);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the first value in a redblack tree.
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
ITSDLLAPI REDBLACK_Node *
RB_FindFirst(REDBLACK_Tree tree)
{
    return (RB_NODE(tree).next);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the last value in a redblack tree
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
ITSDLLAPI REDBLACK_Node *
RB_FindLast(REDBLACK_Tree tree)
{
    return (RB_NODE(tree).prev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the next value after this node
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
ITSDLLAPI REDBLACK_Node *
RB_FindNext(REDBLACK_Node *n)
{
    return (n->next);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the previous value before this node
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
ITSDLLAPI REDBLACK_Node *
RB_FindPrev(REDBLACK_Node *n)
{
    return (n->prev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test if a redblack tree is empty
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
ITSDLLAPI ITS_BOOLEAN
RB_EmptyP(REDBLACK_Tree tree)
{
    if (RB_NODE(tree).next == &RB_NODE(tree))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      No operation
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
ITSDLLAPI REDBLACK_Node *
RB_Nil(REDBLACK_Tree tree)
{
    return (&RB_NODE(tree));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the number of black nodes in the path to this one.
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
ITSDLLAPI int
RB_NumBlack(REDBLACK_Node *n)
{
    int nb = 0;

    ITS_C_ASSERT(!IsHead(n) && !IsInternal(n));

    while (!IsHead(n))
    {
        if (IsBlack(n))
        {
            nb++;
        }

        n = n->parent;
    }

    return (nb);
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return the length of the path to this node
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
ITSDLLAPI int
RB_PathLength(REDBLACK_Node *n)
{
    int pl = 0;

    ITS_C_ASSERT(!IsHead(n) && !IsInternal(n));

    while (!IsHead(n))
    {
        pl++;

        n = n->parent;
    }

    return (pl);
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the closest item in a redblack tree
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
ITSDLLAPI REDBLACK_Node *
RB_FindNearest(REDBLACK_Tree tree, void *key, ITS_UINT klen,
               int *cmpval)
{
    return RB_CLASS_FIND_NEAREST(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                      cmpval);
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find the exact item in a redblack tree
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
ITSDLLAPI REDBLACK_Node *
RB_FindExact(REDBLACK_Tree tree, void *key, ITS_UINT klen)
{
    return RB_CLASS_FIND_EXACT(ITS_OBJ_CLASS(tree))(tree, key, klen);
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Insert a node before this node
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
ITSDLLAPI REDBLACK_Node *
RB_InsertBefore(REDBLACK_Tree tree, REDBLACK_Node *n,
                void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    return RB_CLASS_INSERT_BEFORE(ITS_OBJ_CLASS(tree))(tree, n,
                                                       key, klen,
                                                       val, vlen);
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Insert a node after this node
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
ITSDLLAPI REDBLACK_Node *
RB_InsertAfter(REDBLACK_Tree tree, REDBLACK_Node *n,
               void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    return RB_CLASS_INSERT_AFTER(ITS_OBJ_CLASS(tree))(tree, n,
                                                      key, klen,
                                                      val, vlen);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Insert this value into the tree
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
ITSDLLAPI REDBLACK_Node *
RB_InsertNode(REDBLACK_Tree tree,
              void *key, ITS_UINT klen, void *val, ITS_UINT vlen)
{
    return RB_CLASS_INSERT(ITS_OBJ_CLASS(tree))(tree, key, klen,
                                                val, vlen);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete a leaf node from the tree
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
ITSDLLAPI void
RB_DeleteNode(REDBLACK_Tree tree, REDBLACK_Node *n)
{
    RB_CLASS_DELETE(ITS_OBJ_CLASS(tree))(tree, n);
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Forward iterate over the tree
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
ITSDLLAPI int
RB_Iterate(REDBLACK_Tree tree,
           void *in, void *out, RB_IterateEntryProc func)
{
    return RB_CLASS_ITERATE(ITS_OBJ_CLASS(tree))(tree, in, out, func);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Reverse iterate over the tree
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
ITSDLLAPI int
RB_RIterate(REDBLACK_Tree tree,
            void *in, void *out, RB_IterateEntryProc func)
{
    return RB_CLASS_RITERATE(ITS_OBJ_CLASS(tree))(tree, in, out, func);
}

#if defined(RB_TEST)

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print out a redblack tree
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
ITSDLLAPI void
RB_PrintTree(REDBLACK_Node *t, int level)
{
    int i;
    ITS_UINT idx;

    if (IsHead(t) && t->parent == t)
    {
        printf("tree %p is empty\n", t);
    }
    else if (IsHead(t))
    {
        printf("Head: %p.  Root = %p\n", t, t->parent);

        RB_PrintTree(t->parent, 0);
    }
    else
    {
        if (IsExternal(t))
        {
            for (i = 0; i < level; i++)
            {
                putchar(' ');
            }

            printf("Ext node %p: %c,%c: p=%p, k=", 
                   t, IsRed(t) ? 'R' : 'B', IsLeft(t) ? 'l' : 'r', t->parent);

            for (idx = 0; idx < t->klen; idx++)
            {
                printf("%02x ", ((unsigned char *)t->key)[idx]);
            }
            printf("\n");
        }
        else
        {
            RB_PrintTree(t->next, level + 2);
            RB_PrintTree(t->prev, level + 2);

            for (i = 0; i < level; i++)
            {
                putchar(' ');
            }

            printf("Int node %p: %c,%c: l=%p, r=%p, p=%p, lr=(", 
                   t, IsRed(t) ? 'R' : 'B', IsLeft(t) ? 'l' : 'r',
                   t->next, t->prev, t->parent);
            
            for (idx = 0; idx < t->left->klen; idx++)
            {
                printf("%02x ", ((unsigned char *)t->left->key)[idx]);
            }
            printf(", ");
            
            for (idx = 0; idx < t->right->klen; idx++)
            {
                printf("%02x ", ((unsigned char *)t->right->key)[idx]);
            }
            printf(")\n");
        }
    }
}

#endif /* RB_TEST */
