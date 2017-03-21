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
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:50:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6  2003/02/10 19:01:34  mmiers
 * LOG: Enhance API
 * LOG:
 * LOG: Revision 7.5  2003/02/06 19:46:52  mmiers
 * LOG: Add a node based hash table with arbitrary keys.  This aligns the
 * LOG: hash table with the redblack and splay tree implementations.
 * LOG:
 * LOG: Revision 7.4  2003/01/30 20:46:11  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.3  2003/01/22 22:07:22  mmiers
 * LOG: Add redblack tree.  Make hash, splay, and redblack use overrideable
 * LOG: methods for allocation and freeing.  Update tests.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/18 19:28:12  mmiers
 * LOG: Update DBC console to be able to take more than one
 * LOG: command procedure
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/11/21 21:51:30  hdivoux
 * LOG: Change for iterate hashtable function name.
 * LOG:
 * LOG: Revision 5.3  2001/10/02 21:03:36  mmiers
 * LOG: Typo
 * LOG:
 * LOG: Revision 5.2  2001/10/02 18:29:27  mmiers
 * LOG: Add IterateEntry to the hash table.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/24 20:37:55  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.10  2001/04/02 19:50:14  mmiers
 * LOG: Solaris build.
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
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
 * LOG: Revision 3.5  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.4  2000/09/01 15:35:52  mmiers
 * LOG: Fix a bunch of Makefiles and make the C++ hash interface public.
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:06:35  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.2  2000/08/23 00:02:09  mmiers
 * LOG:
 * LOG: Get the fastcall macros working.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:16  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:31  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 03:04:08  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:38  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.10  1999/08/30 17:53:41  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitization of the support library.
 * LOG:
 * LOG: Revision 1.9  1999/02/26 04:09:50  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.8  1998/09/22 16:01:24  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.7  1998/08/27 23:28:12  hdivoux
 * LOG: Added functions to dump hashtables.
 * LOG:
 * LOG: Revision 1.6  1998/06/01 16:35:15  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.5  1998/05/27 22:08:05  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 17:11:45  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.3  1998/05/01 00:24:31  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.2  1998/04/29 21:10:20  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.1  1998/04/29 00:58:10  mmiers
 * LOG: its_hash.h its_hash.c: new files implementing sparse arrays (hash
 * LOG: tables). Efficiency is pretty good, but the C++ version is neither
 * LOG: templated nor typesafe (implementation uses the C implementation
 * LOG: directly).  Really built for speed - intended for protocol modules.
 * LOG:
 *
 ****************************************************************************/

/****************************************************************************
 * This code is derived from the generic hash in X11, and appears with the
 * following license:
 *
 * Copyright 1987, 1998  The Open Group
 * 
 * All Rights Reserved.
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Except as contained in this notice, the name of The Open Group shall not be
 * used in advertising or otherwise to promote the sale, use or other dealings
 * in this Software without prior written authorization from The Open Group.
 * 
 * 
 * Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.
 * 
 *                         All Rights Reserved
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Digital not be
 * used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 * 
 * DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * 
 *****************************************************************************/

#ifndef ITS_HASH_H
#define ITS_HASH_H

#include <its_object.h>

#ident "$Id: its_hash.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if !defined(ITS_HASH_ONESHOT)
#define ITS_HASH_ONESHOT

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * Number of entries originally in the hash table.
 */
#define INITHASHMASK 63

/*
 * Stores one entry.
 */
typedef struct _TableEntryRec
{
    ITS_UINT                rid;
    ITS_INT                 context;
    ITS_POINTER             data;
    struct _TableEntryRec*  next;
}
HASH_TableEntryRec, *HASH_TableEntry;

/*
 * when dealing with arbitrary sized keys, this structure is used
 * (the BHASH_ API)
 */
typedef struct _bhash_Node
{
    struct _bhash_Node  *prev;
    struct _bhash_Node  *next;
    void                *key;
    ITS_UINT            klen;
    void                *data;
    ITS_UINT            dlen;
}
BHASH_Node;

/* BHASH signatures */
typedef int (*BHASH_IterateEntryProc)(BHASH_Node *,
                                      void *in, void *out);

/*
 * Stores hash table.
 */
typedef struct
{
    HASH_TableEntry     *table;         /* Pointer to array of hash entries.        */
    int                 mask;           /* Current size of hash table minus 1.      */
    int                 numentries;     /* Number of entries currently in table.    */
    ITS_INT             nextUnique;     /* key manipulation                         */
    ITS_BOOLEAN         allowDups;      /* BHASH only.  Determines if dups are ok   */
}
HASH_TableObjectPart;

typedef struct
{
   ITS_CoreObjectPart        core;
   HASH_TableObjectPart      hash;
}
HASH_TableRec, *HASH_Table;

#define HASH_TABLE(x) \
    (((HASH_Table)(x))->hash.table)

#define HASH_MASK(x) \
    (((HASH_Table)(x))->hash.mask)

#define HASH_NUM_ENTRIES(x) \
    (((HASH_Table)(x))->hash.numentries)

#define HASH_NEXT_UNIQUE(x) \
    (((HASH_Table)(x))->hash.nextUnique)

#define HASH_ALLOW_DUPS(x) \
    (((HASH_Table)(x))->hash.allowDups)

/*
 * dump an entry (printing)
 */
typedef int (*HASH_DumpEntryData)(ITS_POINTER data, char** pStrDump);
typedef int (*HASH_IterateEntryProc)(ITS_INT context, ITS_POINTER data,
                                     void *in, void *out);

/*
 * class methods
 */
typedef ITS_INT (*HASH_UniqueKeyProc)(HASH_Table);
typedef int (*HASH_AddEntryProc)(HASH_Table, ITS_UINT, ITS_INT,
                                 ITS_POINTER);
typedef int (*HASH_FindEntryProc)(HASH_Table, ITS_UINT, ITS_INT,
                                  ITS_POINTER *);
typedef int (*HASH_DeleteEntryProc)(HASH_Table, ITS_UINT, ITS_INT);
typedef int (*HASH_VTableDumpProc)(HASH_Table, ITS_UINT,
                                   char **, HASH_DumpEntryData);
typedef int (*HASH_VTableIterateProc)(HASH_Table, ITS_UINT,
                                      void *, void *,
                                      HASH_IterateEntryProc);
typedef void *(*HASH_AllocProc)(HASH_Table, ITS_UINT, ITS_UINT);
typedef void (*HASH_FreeProc)(HASH_Table, void *);

typedef struct
{
    HASH_UniqueKeyProc       uniqueKey;
    HASH_AddEntryProc        addEntry;
    HASH_FindEntryProc       findEntry;
    HASH_DeleteEntryProc     deleteEntry;
    HASH_VTableDumpProc      dumpVTable;
    HASH_VTableIterateProc   iterateVTable;
    HASH_AllocProc           alloc;
    HASH_FreeProc            free;
}
HASH_ClassPart;

typedef struct
{
    ITS_CoreClassPart        coreClass;
    HASH_ClassPart           hashClass;
}
HASH_ClassRec, *HASH_Class;

#define HASH_CLASS_NAME    "HASH_CLASS"

ITSDLLAPI extern HASH_ClassRec   itsHASH_ClassRec;
ITSDLLAPI extern ITS_Class       itsHASH_Class;

#define HASH_CLASS_UNIQUE_KEY(x) \
    (((HASH_Class)(x))->hashClass.uniqueKey)

#define HASH_CLASS_ADD_ENTRY(x) \
    (((HASH_Class)(x))->hashClass.addEntry)

#define HASH_CLASS_FIND_ENTRY(x) \
    (((HASH_Class)(x))->hashClass.findEntry)

#define HASH_CLASS_DELETE_ENTRY(x) \
    (((HASH_Class)(x))->hashClass.deleteEntry)

#define HASH_CLASS_DUMP_VTABLE(x) \
    (((HASH_Class)(x))->hashClass.dumpVTable)

#define HASH_CLASS_ITERATE_VTABLE(x) \
    (((HASH_Class)(x))->hashClass.iterateVTable)

#define HASH_CLASS_ALLOC(x) \
    (((HASH_Class)(x))->hashClass.alloc)

#define HASH_CLASS_FREE(x) \
    (((HASH_Class)(x))->hashClass.free)

#if defined(__cplusplus)
}
#endif

#endif /* ITS_HASH_ONESHOT */

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:HASH
 *****************************************************************************
 *  Interface:
 *      HASH_*
 *
 *  Purpose:
 *      The HASH_Table is designed to provide a low-cost, high-speed
 *      implementation for hash storage.  The decision on the basic hash
 *      algorhithm is left to the user (i.e., the user has the freedom to
 *      choose their own method of generating hash keys from data).
 *
 *      The algorithms and implementation of the hashing functions have
 *      been *heavily* influenced by the hash functions provided by X11
 *      (read, plagiarized).
 *
 *      One extremely useful feature of this implementation is the ability
 *      for one physical hash table to implement many virtual hash tables
 *      (up to 4B); user code can be written to automatically handle
 *      duplicate keys within one virtual table.
 *
 *      Each RID (or resource id) can specify a virtual table.  The
 *      algorithms combine the RID and the CONTEXT to locate and store
 *      entries.  The important thing to note is that the same key will
 *      not find the same entry if the RID(s) are different when you look
 *      up an entry.  That is,
 *
 *      HASH_FindEntry(0, 27, &data);
 *
 *      and
 *
 *      HASH_FindEntry(1, 27, &data);
 *
 *      will return two different values in data (assuming data has been
 *      stored in both "virtual" tables.
 *
 *  Usage:
 *      Creating and manipulating hash tables using these functions is
 *      fairly straight-forward:
 *      -----------------------------------------------------------------
 *      * create a table *
 *      HASH_Table table;
 *
 *      if ((table = HASH_CreateTable()) != ITS_SUCCESS)
 *      {
 *          * an error has occurred *
 *      }
 *
 *      ...
 *
 *      * find an entry *
 *      ITS_INT key = 32;
 *      ITS_POINTER data;
 *
 *      if (HASH_FindEntry(table, 0, key, &data) != ITS_SUCCESS)
 *      {
 *          * no entry was found or an error occurred *
 *      }
 *
 *      ...
 *
 *      * save an entry *
 *      char* b = malloc(20);
 *
 *      if (HASH_AddEntry(table, 0, key, b) != ITS_SUCCESS)
 *      {
 *          * an error occurred *.
 *      }
 *
 *      ...
 *
 *      * remove an entry *
 *      if (HASH_DeleteEntry(table, 0, key) != ITS_SUCCESS)
 *      {
 *          * the entry was not found or an error occurred *
 *      }
 *
 *      ...
 *
 *      * when finished with a table, it should be destroyed *
 *      HASH_DeleteTable(table);
 *      ----------------------------------------------------------
 *
 *      Note that the has table is not thread-safe, even though the
 *      manipulation routines are reentrant.  If a hash table is to
 *      be accessed by multiple threads, the table must be mutex protected.
 *
 *****************************************************************************/

ITSDLLAPI size_t HASH_Size(HASH_Table db);
ITSDLLAPI size_t HASH_VTableSize(HASH_Table db, ITS_UINT rid);
ITSDLLAPI ITS_INT HASH_MakeKey(const char *key, ITS_UINT klen);

/*
 * BHASH_ API (arbitrary sized keys)
 */
ITSDLLAPI HASH_Table    BHASH_CreateTable(ITS_BOOLEAN allowDups);
ITSDLLAPI void          BHASH_DeleteTable(HASH_Table db);
ITSDLLAPI BHASH_Node *  BHASH_AddEntry(HASH_Table db, ITS_UINT rid,
                                       void *key, ITS_UINT klen,
                                       void *data, ITS_UINT dlen);
ITSDLLAPI BHASH_Node *  BHASH_FindEntry(HASH_Table db, ITS_UINT rid,
                                        void *key, ITS_UINT klen);
ITSDLLAPI BHASH_Node *  BHASH_FindPrev(BHASH_Node *entry);
ITSDLLAPI BHASH_Node *  BHASH_FindNext(BHASH_Node *entry);

ITSDLLAPI int           BHASH_DeleteEntry(HASH_Table db, ITS_UINT rid,
                                          BHASH_Node *node);
ITSDLLAPI int           BHASH_Iterate(HASH_Table db, ITS_UINT rid,
                                      void *in, void *out,
                                      BHASH_IterateEntryProc func);

#if !defined(ITS_FASTCALL)

ITSDLLAPI ITS_INT HASH_UniqueKey(HASH_Table db);

ITSDLLAPI HASH_Table HASH_CreateTable();
ITSDLLAPI void HASH_DeleteTable(HASH_Table db);

ITSDLLAPI int HASH_AddEntry(HASH_Table db, ITS_UINT rid,
                            ITS_INT context, ITS_POINTER data);
ITSDLLAPI int HASH_FindEntry(HASH_Table db, ITS_UINT rid,
                             ITS_INT context, ITS_POINTER* data);
ITSDLLAPI int HASH_DeleteEntry(HASH_Table db, ITS_UINT rid, ITS_INT context);

ITSDLLAPI int HASH_VTableDump(HASH_Table db,
                              ITS_UINT rid,
                              char** pStrDump,
                              HASH_DumpEntryData dumpEntryDataFn);
ITSDLLAPI int HASH_VTableIterate(HASH_Table db,
                                 ITS_UINT rid,
                                 void *in, void *out,
                                 HASH_IterateEntryProc iterateEntryFn);

#else /************ defined(ITS_FASTCALL) ***************/

#define HASH_CreateTable() \
    (HASH_Table)ITS_ConstructObject(itsHASH_Class, NULL)

#define HASH_DeleteTable(x) \
    ITS_DestructObject((ITS_Object)(x))

#define HASH_UniqueKey(x) \
    HASH_CLASS_UNIQUE_KEY(ITS_OBJ_CLASS(x))(x)

#define HASH_AddEntry(x, r, c, d) \
    HASH_CLASS_ADD_ENTRY(ITS_OBJ_CLASS(x))((x), (r), (c), (d))

#define HASH_FindEntry(x, r, c, d) \
    HASH_CLASS_FIND_ENTRY(ITS_OBJ_CLASS(x))((x), (r), (c), (d))

#define HASH_DeleteEntry(x, r, c) \
    HASH_CLASS_DELETE_ENTRY(ITS_OBJ_CLASS(x))((x), (r), (c))

#define HASH_VTableDump(x, r, p, f) \
    HASH_CLASS_DUMP_VTABLE(ITS_OBJ_CLASS(x))((x), (r), (p), (f))

#define HASH_VTableIterate(x, r, i, o, f) \
    HASH_CLASS_ITERATE_VTABLE(ITS_OBJ_CLASS(x))((x), (r), (i), (o), (f))

#endif /* defined(ITS_FASTCALL) */

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <exception>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:HashTable
 *****************************************************************************
 *  Interface:
 *      HashTable
 *
 *  Purpose:
 *      The HashTable provides a C++ interface to a light-weight,
 *      high-speed implementation of a hash table.  The hash table
 *      itself is implemented in C.
 *
 *      Hash tables cannot be copied via construction or assignment.
 *
 *  Usage:
 *      The C++ interface is defined as inline functions calling their
 *      C counterparts.  The "RID" parameter is used as a key for
 *      combining separate hashable data items into the same table.
 *      That is, one hash table can be thought of as two virtual
 *      hash tables, if two different RID(s) are used to hash entries.
 *
 *      The usage is quite simple:
 *      ------------------------------------------------------------------
 *      // create the table
 *      HashTable* h = new HashTable();
 *
 *      ...
 *
 *      // add an entry
 *      char *data = "foo";
 *      ITS_INT key = h->UniqueKey();
 *      if (h->AddEntry(0, key, data) != ITS_SUCCESS)
 *      {
 *          // an error has occurred.
 *      }
 *
 *      ...
 *
 *      // you can look up entries as well
 *      ITS_POINTER hData;
 *      if (h->FindEntry(0, key, &hData) != ITS_SUCCESS)
 *      {
 *          // an error has occurred, or the entry is not present
 *      }
 *
 *      ...
 *
 *      // and you can delete entries
 *      if (h->DeleteEntry(0, key) != ITS_SUCCESS)
 *      {
 *          // an error has occurred, or the entry is not present
 *      }
 *
 *      ...
 *
 *      // finally, the table should be destroyed if no longer in
 *      // use
 *      delete h;
 *      ----------------------------------------------------------
 *
 *      The routines are NOT thread safe.  A mutex should be added to serialize
 *      access to a hash table if the hash table is to be shared among threads.
 *
 *****************************************************************************/
class HashTable
{
public:
    /*.implementation:public,inline,HashTable
    ************************************************************************
    *  Purpose:
    *	    This method creates the HashTable object.
    *
    *  Notes:
    *       An exception may be thrown if the hash table cannot be created.
    *
    *  See Also:
    *       ~HashTable()
    ************************************************************************/
    HashTable()
        : table(NULL)
    {
        if ((table = HASH_CreateTable()) == NULL)
        {
            std::exception ex;

            throw ex;
        }
    }
    /*.implementation:public,inline,HashTable
    ************************************************************************
    *  Purpose:
    *	    This method destroys a hash table object.
    *
    ************************************************************************/
    virtual ~HashTable()
    {
        HASH_DeleteTable(table);
    }

    /*.implementation:public,inline,HashTable
    ************************************************************************
    *  Purpose:
    *       This method returns the next available unique key for a hash
    *       table.  Note that once the key space is exhausted, the key
    *       value returned will repeat.  For this reason, users of the
    *       hash table must either a) create their own unique keys,
    *       or b) provide some further distinguishing characteristic
    *       (key extension) in the data.  In either case, if duplicate
    *       keys are allowed, the data stored for each key should
    *       most likely represent a linked list of values.  The list will
    *       contain the different records associated with the duplicate key.
    *
    *  Return Value:
    *       An integer value from the key space.  The key will not repeat
    *       until the total number of calls to this function exceeds the
    *       maximum range of an integer.
    *
    ************************************************************************/
    ITS_INT
    UniqueKey()
    {
        return HASH_UniqueKey(table);
    }
    /*.implementation:public,inline,HashTable
    ************************************************************************
    *  Purpose:
    *       This method will add an entry to the hash table.
    *
    *  Input Parameters:
    *       rid - the resource identifier for this hash
    *       context - the unique key within this RID
    *       data - a pointer value to store for this rid/context pair.
    *
    *  Return Value:
    *       If the addition is successful, ITS_SUCCESS is returned.
    *       Any other return value indicates an IntelliSS7 error.
    *
    *  Notes:
    *       Note that if the entry already exists, this function will replace
    *       the current data value with the new data value.
    *
    ************************************************************************/
    int
    AddEntry(ITS_UINT rid, ITS_INT context, ITS_POINTER data)
    {
        return HASH_AddEntry(table, rid, context, data);
    }
    /*.implementation:public,inline,HashTable
    ************************************************************************
    *  Purpose:
    *       This method attempts to find an entry by rid/context in the has
    *       table.
    *
    *  Input Parameters:
    *       rid - the resource id to select for
    *       context - the context for this entry
    *
    *  Output Parameters:
    *       data - the address of a pointer to put the saved data pointer
    *           into if the entry is in the table.
    *
    *  Return Value:
    *       If the entry is found in the table, ITS_SUCCESS is returned.
    *       Any other return value indicates an IntelliSS7 error.
    *
    ************************************************************************/
    int
    FindEntry(ITS_UINT rid, ITS_INT context, ITS_POINTER* data)
    {
        return HASH_FindEntry(table, rid, context, data);
    }
    /*.implementation:public,inline,HashTable
    ************************************************************************
    *  Purpose:
    *       This method deletes an entry from the hash table.
    *
    *  Input Parameters:
    *       rid - the resource id of the entry to delete
    *       context - the context of the entry to delete
    *
    *  Return Value:
    *       If the entry is deleted, ITS_SUCCESS is returned.
    *       Any other return value indicates the entry was not found, or
    *       an IntelliSS7 error was returned.
    *
    ************************************************************************/
    int
    DeleteEntry(ITS_UINT rid, ITS_INT context)
    {
        return HASH_DeleteEntry(table, rid, context);
    }

    /*.implementation:public,inline,HashTable
    *************************************************************************
    *  Purpose:
    *        Return hashtable size (total number of entries).
    *       
    *  Return Value:
    *        size_t - total number of entries in hashtable.
    *
    ************************************************************************/
    size_t 
    Size()
    {
        return HASH_Size(table);
    }

    /*.implementation:public,inline,HashTable
    *************************************************************************
    *  Purpose:
    *       Return virtual hashtable size (total number of entries). A
    *       virtual hashtable is contained in the hashtable and is identified
    *       by its resource id (rid).
    *
    *  Input Parameters:
    *       rid - resource id (identifies a virtual hashtable).
    *
    *  Return Value:
    *       size_t - total number of entries in the virtual hashtable.
    *
    ************************************************************************/
    size_t 
    VTableSize(ITS_UINT rid)
    {
        return HASH_VTableSize(table, rid);
    }

    /*.implementation:public,inline,HashTable
    *************************************************************************
    *  Purpose:
    *       Dump a virtual hashtable (identified by its resource id or rid).
    *       The input parameter dumpEntryDataFn is a pointer to a function
    *       with the signature [int Function(ITS_POINTER data, char** 
    *       pStrDump)]. This dump function must be user provided and depends
    *       of the type of the data stored in the hashtable. It must allocate
    *       a character string (using *pStrDump = malloc...) and return
    *       ITS_SUCCESS or an ITS error code. The character string will be
    *       deallocated by HASH_VTableDump after use. Nothing specific is
    *       done to separate the dumps of each entries, therefore this must
    *       be done inside the dump function (e.g. adding '\n' and/or
    *       "----------").
    *
    *  Input Parameters:
    *       rid - resource id (identifies a virtual hashtable).
    *       dumpEntryDataFn - pointer to function that allows to dump the
    *       data of an entry.
    *
    *  Input/Output Parameters:
    *      pStrDump - pointer to a character string. The character string is
    *          allocated by HASH_VTableDump and therefore must be deallocated
    *          by the user (after usage).
    *
    *  Return Value:
    *      ITS_SUCCESS or an ITS error code.
    *
    ************************************************************************/
    int 
    VTableDump(ITS_UINT rid,
               char** pStrDump,
               HASH_DumpEntryData dumpEntryDataFn)
    {
        return HASH_VTableDump(table, rid, pStrDump, dumpEntryDataFn);
    }
    /*.implementation:public,inline,HashTable
    *************************************************************************
    *  Purpose:
    *       Dump a virtual hashtable (identified by its resource id or rid).
    *       The input parameter dumpEntryDataFn is a pointer to a function
    *       with the signature [int Function(ITS_POINTER data, char** 
    *       pStrDump)]. This dump function must be user provided and depends
    *       of the type of the data stored in the hashtable. It must allocate
    *       a character string (using *pStrDump = malloc...) and return
    *       ITS_SUCCESS or an ITS error code. The character string will be
    *       deallocated by HASH_VTableDump after use. Nothing specific is
    *       done to separate the dumps of each entries, therefore this must
    *       be done inside the dump function (e.g. adding '\n' and/or
    *       "----------").
    *
    *  Input Parameters:
    *       rid - resource id (identifies a virtual hashtable).
    *       dumpEntryDataFn - pointer to function that allows to dump the
    *       data of an entry.
    *
    *  Input/Output Parameters:
    *      pStrDump - pointer to a character string. The character string is
    *          allocated by HASH_VTableDump and therefore must be deallocated
    *          by the user (after usage).
    *
    *  Return Value:
    *      ITS_SUCCESS or an ITS error code.
    *
    ************************************************************************/
    int 
    VTableIterate(ITS_UINT rid,
               void *in, void *out,
               HASH_IterateEntryProc iterateEntryFn)
    {
        return HASH_VTableIterate(table, rid, in, out, iterateEntryFn);
    }


private:
    HashTable(HashTable&) {}
    HashTable& operator=(HashTable&) { return *this; }

    HASH_Table table;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_HASH_H */
