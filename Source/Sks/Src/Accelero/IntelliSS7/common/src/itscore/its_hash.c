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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.9  2005/03/21 13:51:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.1  2003/02/19 16:19:22  randresol
 * LOG: Bug fixing for DSM-GCS.
 * LOG:
 * LOG: Revision 7.5  2003/02/10 19:02:02  mmiers
 * LOG: Enhancements to implementations.
 * LOG:
 * LOG: Revision 7.4  2003/02/06 19:47:22  mmiers
 * LOG: Add a node based hash table with arbitrary keys.  This aligns the
 * LOG: hash table with the redblack and splay tree implementations.
 * LOG: Also fix a few bugs in redblack and splay.
 * LOG:
 * LOG: Revision 7.3  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.2  2003/01/22 22:07:22  mmiers
 * LOG: Add redblack tree.  Make hash, splay, and redblack use overrideable
 * LOG: methods for allocation and freeing.  Update tests.
 * LOG:
 * LOG: Revision 7.1  2002/12/20 19:40:41  mmiers
 * LOG: Move files.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/18 19:28:13  mmiers
 * LOG: Update DBC console to be able to take more than one
 * LOG: command procedure
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/11/21 21:51:30  hdivoux
 * LOG: Change for iterate hashtable function name.
 * LOG:
 * LOG: Revision 5.4  2001/11/12 22:33:31  mmiers
 * LOG: Clean up on exit.
 * LOG:
 * LOG: Revision 5.3  2001/10/02 18:29:27  mmiers
 * LOG: Add IterateEntry to the hash table.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/07/24 20:37:56  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.2  2001/07/06 21:47:13  mmiers
 * LOG: Add shared timers.  The default is still non-shared.
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
 * LOG: Revision 3.4  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/02/24 23:57:15  hdivoux
 * LOG: Correction for sizeof type.
 * LOG:
 * LOG: Revision 2.4  2000/02/24 16:12:26  hdivoux
 * LOG: Added use of ITS_OBJ_CLASS for HASH_UniqueKey.
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:42  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  2000/01/26 23:42:45  mmiers
 * LOG:
 * LOG:
 * LOG: Do some rearranging.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 03:04:09  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:40  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.11  1999/02/26 04:09:52  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.10  1999/02/25 22:57:10  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.9  1998/11/19 00:36:25  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.8  1998/10/01 17:39:52  mmiers
 * LOG: Try to find the race condition with routing.
 * LOG:
 * LOG: Revision 1.7  1998/09/21 22:52:33  mmiers
 * LOG: Start adding C-trace to infrastructure.
 * LOG:
 * LOG: Revision 1.6  1998/08/27 23:28:14  hdivoux
 * LOG: Added functions to dump hashtables.
 * LOG:
 * LOG: Revision 1.5  1998/06/16 00:00:25  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.4  1998/05/27 22:08:07  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.3  1998/04/29 21:10:20  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.2  1998/04/29 01:00:26  mmiers
 * LOG: Some false positives.  This is intended to commit the workspace/project
 * LOG: file changes.
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

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_hash.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_hash.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*
 * Given an ITS_UINT and a context, returns a value between 0 and HashSize-1.
 * Currently, this requires that HashSize be a power of 2.
 */
#define Hash(db,rid,context) \
    HASH_TABLE(db)[(((rid) << 1) + context) & HASH_MASK(db)]

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Resize the given db
 *
 *  Input Parameters:
 *      db - the hash table to grow or shrink
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
ResizeTable(HASH_Table db)
{
    HASH_TableEntry *otable;
    HASH_TableEntry entry, next, *pold, *head;
    int i, j;

    ITS_TRACE_DEBUG(("ResizeTable:\n"));

    otable = HASH_TABLE(db);
    for (i = INITHASHMASK+1; (i + i) < HASH_NUM_ENTRIES(db); )
    {
        i += i;
    }
    HASH_TABLE(db) = HASH_CLASS_ALLOC(ITS_OBJ_CLASS(db))(db,
                                                         (unsigned)i,
                                                         sizeof(HASH_TableEntry));

    if (!HASH_TABLE(db))
    {
        ITS_TRACE_ERROR(("ResizeTable: out of memory\n"));

        HASH_TABLE(db) = otable;

        return;
    }

    j = HASH_MASK(db) + 1;
    HASH_MASK(db) = i - 1;

    for (pold = otable ; --j >= 0; pold++)
    {
        for (entry = *pold; entry; entry = next)
        {
            next = entry->next;
            head = &Hash(db, entry->rid, entry->context);
            entry->next = *head;
            *head = entry;
        }
    }

    HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, otable);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      get the next unique context.  Pretty simple algo, the table takes
 *      care of the compaction.
 *
 *  Input Parameters:
 *      db - the hash table to generate the unique key for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The next unique context value.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_INT
UniqueKey(HASH_Table db)
{
    ITS_TRACE_DEBUG(("UniqueKey:\n"));

    ITS_C_REQUIRE(db != NULL);

    return HASH_NEXT_UNIQUE(db)--;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free the hash table.
 *
 *  Input Parameters:
 *      db - the hash table to destroy.
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
 *      HASH_CreateTable()
 ****************************************************************************/
static void
DeleteTable(ITS_Object obj)
{
    HASH_Table db = (HASH_Table)obj;
    int i;
    HASH_TableEntry *pentry, entry, next;

    ITS_TRACE_DEBUG(("DeleteTable:\n"));

    if (db)
    {
        for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
        {
            for (entry = *pentry; entry; entry = next)
            {
                next = entry->next;

                HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, entry);
            }
        }

        HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, HASH_TABLE(db));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create the hash table.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      pdb = the address of the hash table to create.
 *
 *  Return Value:
 *      If the table is created successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      HASH_DeleteTable()
 ****************************************************************************/
static int
CreateTable(ITS_Object obj, va_list args)
{
    HASH_Table db = (HASH_Table)obj;

    ITS_TRACE_DEBUG(("CreateTable:\n"));

    HASH_NEXT_UNIQUE(db) = -1;

    HASH_MASK(db) = INITHASHMASK;
    HASH_TABLE(db) = HASH_CLASS_ALLOC(ITS_OBJ_CLASS(db))(db,
                                                         HASH_MASK(db) + 1,
                                                         sizeof(HASH_TableEntry));
    if (!HASH_TABLE(db))
    {
        ITS_TRACE_ERROR(("CreateTable: out of memory\n"));

        return (ITS_ENOMEM);
    }
    HASH_NUM_ENTRIES(db) = 0;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Save the given value of data to correspond with the keys ITS_UINT
 *      and context.  Returns nonzero error code if an error has occured,
 *      0 otherwise.  Possible errors are Out-of-memory.
 *
 *  Input Parameters:
 *      db - the hash table to add the entry to
 *      rid = the resource id to use for this entry
 *      context - the key for this entry in this rid
 *      data - the data to save for this entry
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the entry is added successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      If the entry already exists for this rid/context pair, the current
 *      entry will be replaced with the data provided in this call.
 *
 *  See Also:
 ****************************************************************************/
static int
AddEntry(HASH_Table db, ITS_UINT rid,
         ITS_INT context, ITS_POINTER data)
{
    HASH_TableEntry *head;
    HASH_TableEntry entry;

    ITS_TRACE_DEBUG(("AddEntry:\n"));

    ITS_C_REQUIRE(db != NULL);

    head = &Hash(db, rid, context);

    for (entry = *head; entry; entry = entry->next)
    {
        if (entry->rid == rid && entry->context == context)
        {
            entry->data = (ITS_POINTER)data;

            return (ITS_SUCCESS);
        }
    }

    entry = HASH_CLASS_ALLOC(ITS_OBJ_CLASS(db))(db,
                                                1, sizeof(HASH_TableEntryRec));

    if (!entry)
    {
        ITS_TRACE_ERROR(("AddEntry: out of memory\n"));

        return (ITS_ENOMEM);
    }

    entry->rid = rid;
    entry->context = context;
    entry->data = (ITS_POINTER)data;
    entry->next = *head;
    *head = entry;

    HASH_NUM_ENTRIES(db)++;

    if (HASH_NUM_ENTRIES(db) > (HASH_MASK(db) << 2))
    {
        ResizeTable(db);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Given an ITS_UINT and context, returns the associated data.  Note
 *      that data here is a pointer since it is a return value.  Returns
 *      nonzero error code if an error has occured, 0 otherwise.  Possible
 *      errors are Entry-not-found.
 *
 *  Input Parameters:
 *      db - the table to search in
 *      rid - the resource id to search in
 *      context - the key to search for in this rid
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - returns a pointer to the saved data, if the entry is found
 *
 *  Return Value:
 *      If the entry is located, ITS_SUCCESS is returned.
 *      Any other return value indicates that the entry was not found, or
 *          an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
FindEntry(HASH_Table db, ITS_UINT rid,
          ITS_INT context, ITS_POINTER* data)
{
    HASH_TableEntry entry;

    ITS_TRACE_DEBUG(("FindEntry:\n"));

    ITS_C_REQUIRE(db != NULL);

    if (data)
    {
        *data = NULL;
    }
    else
    {
        return (ITS_ENOMSG);
    }

    for (entry = Hash(db, rid, context); entry; entry = entry->next)
    {
        if (entry->rid == rid && entry->context == context)
        {
            *data = (ITS_POINTER)entry->data;

            return (ITS_SUCCESS);
        }
    }

    return (ITS_ENOMSG);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Deletes the entry for the given ITS_UINT and context from the
 *      datastructure.  This returns the same thing that FindContext
 *      would have returned if called with the same arguments.
 *
 *  Input Parameters:
 *      db - the table to delete from
 *      rid - the resource id to delete from
 *      context - the key in the rid to delete
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the item is successfully deleted, ITS_SUCCESS is returned.
 *      Any other return value indicates that the key was not found,
 *          or that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
DeleteEntry(HASH_Table db, ITS_UINT rid, ITS_INT context)
{
    HASH_TableEntry entry, *prev;

    ITS_TRACE_DEBUG(("DeleteEntry:\n"));

    ITS_C_REQUIRE(db != NULL);

    for (prev = &Hash(db, rid, context);
         (entry = *prev) != NULL;
         prev = &entry->next)
    {
        if (entry->rid == rid && entry->context == context)
        {
            *prev = entry->next;

            HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, entry);
            HASH_NUM_ENTRIES(db)--;

            if (HASH_NUM_ENTRIES(db) < HASH_MASK(db) &&
                HASH_MASK(db) > INITHASHMASK)
            {
                ResizeTable(db);
            }

            return (ITS_SUCCESS);
        }
    }

    return (ITS_ENOMSG);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Iterate a virtual hashtable (identified by its resource id or rid). 
 *      The input parameter iterateEntryDataFn is a pointer to a function with
 *      the signature [int Function(ITS_POINTER data, void* in, void* out)]. 
 *      This iterate function must be user provided and depends of the purpose
 *      of the iteration.
 *
 *  Input Parameters:
 *      db - hashtable.
 *      rid - resource id (identifies a virtual hashtable).
 *      in - pointer to input data passed to iterate entry function.
 *      iterateEntryDataFn - pointer to iterate entry function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      out - pointer to output data passed to iterate entry function.
 *
 *  Return Value:
 *      ITS_SUCCESS or an ITS error code.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static int 
VTableIterate(HASH_Table db, ITS_UINT rid,
              void* in, void* out, 
              HASH_IterateEntryProc iterateEntryDataFn)
{
    HASH_TableEntry *pentry, entry, next;
    int i;
    int res;

    ITS_TRACE_DEBUG(("VTableIterate:\n"));

    if (db == NULL || iterateEntryDataFn == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            if (entry->rid == rid)
            {
                ITS_POINTER ptr = entry->data;

                res = iterateEntryDataFn(entry->context, ptr, in, out);

                if (res != ITS_SUCCESS)
                {
                    return res;
                }
            }
        
            next = entry->next;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dump a virtual hashtable (identified by its resource id or rid). The
 *      input parameter dumpEntryDataFn is a pointer to a function with the
 *      signature [int Function(ITS_POINTER data, char** pStrDump)]. This 
 *      dump function must be user provided and depends of the type of the
 *      data stored in the hashtable. It must allocate a character string
 *      (using *pStrDump = malloc...) and return ITS_SUCCESS or an ITS error
 *      code. The character string will be deallocated by HASH_VTableDump
 *      after use. Nothing specific is done to separate the dumps of each
 *      entries, therefore this must be done inside the dump function (e.g.
 *      adding '\n' and/or "----------").
 *
 *  Input Parameters:
 *      db - hashtable.
 *      rid - resource id (identifies a virtual hashtable).
 *      dumpEntryDataFn - pointer to function that allows to dump the data of
 *          an entry.
 *
 *  Input/Output Parameters:
 *      pStrDump - pointer to a character string. The character string is 
 *          allocated by HASH_VTableDump and therefore must be deallocated
 *          by the user (after usage).
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS or an ITS error code.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
VTableDump(HASH_Table db, ITS_UINT rid,
           char** pStrDump, HASH_DumpEntryData dumpEntryDataFn)
{
    HASH_TableEntry *pentry, entry, next;
    int i;
    int res;
    char* strEntryDump;

    ITS_TRACE_DEBUG(("VTableDump:\n"));

    if (db == NULL || dumpEntryDataFn == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* Initialization. */
    if (pStrDump)
    {
        *pStrDump = (char *)malloc(1 * sizeof(char));

        if (*pStrDump == NULL)
        {
            ITS_TRACE_ERROR(("VTableDump: out of memory\n"));

            return ITS_ENOMEM;
        }

        **pStrDump = '\0'; 
    }

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            if (entry->rid == rid)
            {
                strEntryDump = NULL;

                res = dumpEntryDataFn(entry->data, &strEntryDump);

                if (res != ITS_SUCCESS)
                {
                    if (strEntryDump != NULL)
                    {
                        free(strEntryDump);
                    }

                    return res;
                }

                /* + 1 = security. */

                if (strEntryDump)
                {
                    if (pStrDump)
                    {
                        *pStrDump = (char *)realloc(*pStrDump,
                                                    strlen(*pStrDump) * sizeof(char) +
                                                        strlen(strEntryDump) *
                                                        sizeof(char) + 1);

                        if (*pStrDump == NULL)
                        {
                            free(strEntryDump);

                            return ITS_ENOMEM;
                        }

                        strcat(*pStrDump, strEntryDump);

                        free(strEntryDump);
                    }
                }
            }
        
            next = entry->next;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Allocate for the hash
 *
 *  Input Parameters:
 *      db - hash table
 *      n - number
 *      size - size of each number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void * - allocated area
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void *
Alloc(HASH_Table db, ITS_UINT n, ITS_UINT size)
{
    return calloc(n, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free for the hash table
 *
 *  Input Parameters:
 *      db - the table to delete from
 *      data - memory to release.
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
Free(HASH_Table db, void *data)
{
    free(data);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class record.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassPartInit(ITS_Class classRec)
{
    ITS_Class superClass = ITS_CLASS_SUPERCLASS(classRec);

    if (HASH_CLASS_UNIQUE_KEY(classRec) == NULL)
    {
        HASH_CLASS_UNIQUE_KEY(classRec) = HASH_CLASS_UNIQUE_KEY(superClass);
    }

    if (HASH_CLASS_ADD_ENTRY(classRec) == NULL)
    {
        HASH_CLASS_ADD_ENTRY(classRec) = HASH_CLASS_ADD_ENTRY(superClass);
    }

    if (HASH_CLASS_FIND_ENTRY(classRec) == NULL)
    {
        HASH_CLASS_FIND_ENTRY(classRec) = HASH_CLASS_FIND_ENTRY(superClass);
    }

    if (HASH_CLASS_DELETE_ENTRY(classRec) == NULL)
    {
        HASH_CLASS_DELETE_ENTRY(classRec) = HASH_CLASS_DELETE_ENTRY(superClass);
    }

    if (HASH_CLASS_DUMP_VTABLE(classRec) == NULL)
    {
        HASH_CLASS_DUMP_VTABLE(classRec) = HASH_CLASS_DUMP_VTABLE(superClass);
    }

    if (HASH_CLASS_ITERATE_VTABLE(classRec) == NULL)
    {
        HASH_CLASS_ITERATE_VTABLE(classRec) = HASH_CLASS_ITERATE_VTABLE(superClass);
    }

    if (HASH_CLASS_ALLOC(classRec) == NULL)
    {
        HASH_CLASS_ALLOC(classRec) = HASH_CLASS_ALLOC(superClass);
    }

    if (HASH_CLASS_FREE(classRec) == NULL)
    {
        HASH_CLASS_FREE(classRec) = HASH_CLASS_FREE(superClass);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record.
 *
 *  Input Parameters:
 *      classRec - the class to destroy
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
ClassPartDest(ITS_Class classRec)
{
}

/*
 * the class record
 */
ITSDLLAPI HASH_ClassRec itsHASH_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        sizeof(HASH_TableRec),          /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        HASH_CLASS_NAME,                /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ClassPartInit,                  /* class part init */
        ClassPartDest,                  /* class part destroy */
        CreateTable,                    /* instance create */
        DeleteTable,                    /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* hash part */
    {
        UniqueKey,                      /* unique key generator */
        AddEntry,                       /* add entry method */
        FindEntry,                      /* find entry method */
        DeleteEntry,                    /* delete entry method */
        VTableDump,                     /* VTable dump method */
        VTableIterate,                  /* Iterate entry method */
        Alloc,                          /* allocate method */
        Free                            /* free method */
    }
};

ITSDLLAPI ITS_Class itsHASH_Class = (ITS_Class)&itsHASH_ClassRec;

#undef HASH_CreateTable
#undef HASH_DeleteTable
#undef HASH_UniqueKey
#undef HASH_AddEntry
#undef HASH_FindEntry
#undef HASH_DeleteEntry
#undef HASH_VTableDump
#undef HASH_VTableIterate

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      get the next unique context.  Pretty simple algo, the table takes
 *      care of the compaction.
 *
 *  Input Parameters:
 *      db - the hash table to generate the unique key for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The next unique context value.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_INT
HASH_UniqueKey(HASH_Table db)
{
    ITS_TRACE_DEBUG(("HASH_UniqueKey:\n"));

    return HASH_CLASS_UNIQUE_KEY(ITS_OBJ_CLASS(db))(db);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Free the hash table.
 *
 *  Input Parameters:
 *      db - the hash table to destroy.
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
 *      HASH_CreateTable()
 ****************************************************************************/
ITSDLLAPI void
HASH_DeleteTable(HASH_Table db)
{
    ITS_TRACE_DEBUG(("HASH_DeleteTable:\n"));

    ITS_DestructObject((ITS_Object)db);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create the hash table.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      pdb = the address of the hash table to create.
 *
 *  Return Value:
 *      If the table is created successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      HASH_DeleteTable()
 ****************************************************************************/
ITSDLLAPI HASH_Table
HASH_CreateTable()
{
    ITS_TRACE_DEBUG(("HASH_CreateTable:\n"));

    return (HASH_Table)(ITS_ConstructObject)(itsHASH_Class, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Save the given value of data to correspond with the keys ITS_UINT
 *      and context.  Returns nonzero error code if an error has occured,
 *      0 otherwise.  Possible errors are Out-of-memory.
 *
 *  Input Parameters:
 *      db - the hash table to add the entry to
 *      rid = the resource id to use for this entry
 *      context - the key for this entry in this rid
 *      data - the data to save for this entry
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the entry is added successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      If the entry already exists for this rid/context pair, the current
 *      entry will be replaced with the data provided in this call.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
HASH_AddEntry(HASH_Table db, ITS_UINT rid,
              ITS_INT context, ITS_POINTER data)
{
    return HASH_CLASS_ADD_ENTRY(ITS_OBJ_CLASS(db))(db, rid, context, data);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Given an ITS_UINT and context, returns the associated data.  Note
 *      that data here is a pointer since it is a return value.  Returns
 *      nonzero error code if an error has occured, 0 otherwise.  Possible
 *      errors are Entry-not-found.
 *
 *  Input Parameters:
 *      db - the table to search in
 *      rid - the resource id to search in
 *      context - the key to search for in this rid
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - returns a pointer to the saved data, if the entry is found
 *
 *  Return Value:
 *      If the entry is located, ITS_SUCCESS is returned.
 *      Any other return value indicates that the entry was not found, or
 *          an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
HASH_FindEntry(HASH_Table db, ITS_UINT rid,
               ITS_INT context, ITS_POINTER* data)
{
    return HASH_CLASS_FIND_ENTRY(ITS_OBJ_CLASS(db))(db, rid, context, data);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Deletes the entry for the given ITS_UINT and context from the
 *      datastructure.  This returns the same thing that FindContext
 *      would have returned if called with the same arguments.
 *
 *  Input Parameters:
 *      db - the table to delete from
 *      rid - the resource id to delete from
 *      context - the key in the rid to delete
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the item is successfully deleted, ITS_SUCCESS is returned.
 *      Any other return value indicates that the key was not found,
 *          or that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
HASH_DeleteEntry(HASH_Table db, ITS_UINT rid, ITS_INT context)
{
    return HASH_CLASS_DELETE_ENTRY(ITS_OBJ_CLASS(db))(db, rid, context);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return hashtable size (total number of entries).
 *
 *  Input Parameters:
 *      db - hashtable.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      size_t - total number of entries in hashtable.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI size_t 
HASH_Size(HASH_Table db)
{
    ITS_TRACE_DEBUG(("HASH_Size:\n"));

    if (db)
    {
        return (size_t)HASH_NUM_ENTRIES(db);
    }
    else
    {
        return (size_t)0;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return virtual hashtable size (total number of entries). A virtual
 *      hashtable is contained in the hashtable and is identified by its 
 *      resource id (rid).
 *
 *  Input Parameters:
 *      db - hashtable.
 *      rid - resource id (identifies a virtual hashtable).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      size_t - total number of entries in the virtual hashtable.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI size_t 
HASH_VTableSize(HASH_Table db, ITS_UINT rid)
{
    size_t result = (size_t)0;

    int i;
    HASH_TableEntry *pentry, entry, next;

    ITS_TRACE_DEBUG(("HASH_VTableSize:\n"));

    if (db)
    {
        for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
        {
            for (entry = *pentry; entry; entry = next)
            {
                if (entry->rid == rid)
                {
                    result++;
                }
                
                next = entry->next;
            }
        }

    }

    return result;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Iterate a table.
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
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int
HASH_VTableIterate(HASH_Table db, ITS_UINT tableId,
                   void* in, void* out,
                   HASH_IterateEntryProc iterateEntryDataFn)
{
    return HASH_CLASS_ITERATE_VTABLE(ITS_OBJ_CLASS(db))(db, tableId, 
                                                        in, out,
                                                        iterateEntryDataFn);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Dump a virtual hashtable (identified by its resource id or rid). The
 *      input parameter dumpEntryDataFn is a pointer to a function with the
 *      signature [int Function(ITS_POINTER data, char** pStrDump)]. This 
 *      dump function must be user provided and depends of the type of the
 *      data stored in the hashtable. It must fate a character string
 *      (using *pStrDump = malloc...) and return ITS_SUCCESS or an ITS error
 *      code. The character string will be deallocated by HASH_VTableDump
 *      after use. Nothing specific is done to separate the dumps of each
 *      entries, therefore this must be done inside the dump function (e.g.
 *      adding '\n' and/or "----------").
 *
 *  Input Parameters:
 *      db - hashtable.
 *      rid - resource id (identifies a virtual hashtable).
 *      dumpEntryDataFn - pointer to function that allows to dump the data of
 *          an entry.
 *
 *  Input/Output Parameters:
 *      pStrDump - pointer to a character string. The character string is 
 *          allocated by HASH_VTableDump and therefore must be deallocated
 *          by the user (after usage).
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS or an ITS error code.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int 
HASH_VTableDump(HASH_Table db,
                ITS_UINT rid,
                char** pStrDump,
                HASH_DumpEntryData dumpEntryDataFn)
{
    return HASH_CLASS_DUMP_VTABLE(ITS_OBJ_CLASS(db))(db, rid,
                                                     pStrDump, dumpEntryDataFn);
}

#define HASH_SMALL_PRIME        (7)
#define HASH_MEDIAN_PRIME       (131)
#define HASH_16_BITS_MAX_PRIME  (65531)
#define HASH_16_BITS_MASK       (0x0000FFFF)
/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Determine a hash key for a string/byte array
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
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_INT
HASH_MakeKey(const char *key, ITS_UINT klen)
{
    ITS_INT ret = HASH_MEDIAN_PRIME;
    ITS_UINT i;

    for (i = 0; i < klen; i++)
    {
        /* Protect against an input of all 1's with a small prime. */
        if (key[i] == 1)
        {
            ret *= HASH_SMALL_PRIME;
        }
        /* Protect againt zero killing the hash. */
        else if (key[i])
        {
            ret *= key[i];
        }
        /* If zero then square. */
        else
        {
            ret *= ret;
        }

        /* 
         * Multiplications may have resulted in a zeroed lower half word. If
         * lower word is clear then permute things a bit.
         */
        if (!(ret & HASH_16_BITS_MASK))
        {
            ret += HASH_16_BITS_MAX_PRIME;
        }
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create the hash table.
 *
 *  Input Parameters:
 *      allowDups - should the table allow duplicate keys.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      pdb = the address of the hash table to create.
 *
 *  Return Value:
 *      If the table is created successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      HASH_DeleteTable()
 ****************************************************************************/
ITSDLLAPI HASH_Table
BHASH_CreateTable(ITS_BOOLEAN allowDups)
{
    HASH_Table db = HASH_CreateTable();

    if (db)
    {
        HASH_ALLOW_DUPS(db) = allowDups;
    }

    return (db);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete the hash table.
 *
 *  Input Parameters:
 *      db - the table to delete
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
 *      BHASH_CreateTable()
 ****************************************************************************/
ITSDLLAPI void
BHASH_DeleteTable(HASH_Table db)
{
    HASH_TableEntry *pentry, entry, next;
    BHASH_Node *list, *lnext;
    int i;

    /* delete all rows. O(n^3).  Yuck. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            for (list = (BHASH_Node *)entry->data; list; list = lnext)
            {
                lnext = list->next;

                if (list->dlen)
                {
                    HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, list->data);
                }

                HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, list->key);
                HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, list);
            }

            next = entry->next;
        }
    }

    HASH_DeleteTable(db);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Save the given value of data to correspond with the key and
 *      rid.  Returns nonzero error code if an error has occured,
 *      0 otherwise.  Possible errors are Out-of-memory.
 *
 *  Input Parameters:
 *      db - the hash table to add the entry to
 *      rid = the resource id to use for this entry
 *      key - key data
 *      klen - length of key data
 *      data - pointer to data
 *      dlen - row data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the entry is added successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      If the entry already exists for this rid/context pair, the current
 *      entry will be replaced with the data provided in this call.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI BHASH_Node *
BHASH_AddEntry(HASH_Table db, ITS_UINT rid,
               void *key, ITS_UINT klen,
               void *data, ITS_UINT dlen)
{
    ITS_INT kval;
    ITS_POINTER lkup;
    BHASH_Node *ptr, *list;
    int ret;

    /* protect against bad keys */
    ITS_C_ASSERT(key != NULL && klen != 0);

    kval = HASH_MakeKey((const char *)key, klen);

    ret = HASH_FindEntry(db, rid, kval, &lkup);

    /* non-empty bucket?  Check for dups */
    if (ret == ITS_SUCCESS)
    {
        for (list = (BHASH_Node *)lkup; list != NULL; list = list->next)
        {
            if (klen == list->klen &&
                memcmp(key, list->key, klen) == 0)
            {
                if (!HASH_ALLOW_DUPS(db))
                {
                    return (NULL);
                }

                /* pop out of the loop regardless */
                break;
            }
        }
    }

    /* we're good.  Allocate a new node */
    ptr = HASH_CLASS_ALLOC(ITS_OBJ_CLASS(db))(db,
                                              1, sizeof(BHASH_Node));
    if (ptr == NULL)
    {
        return (NULL);
    }

    ptr->key = HASH_CLASS_ALLOC(ITS_OBJ_CLASS(db))(db, 1, klen);
    if (ptr->key == NULL)
    {
        HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, ptr);

        return (NULL);
    }

    if (dlen)
    {
        ptr->data = HASH_CLASS_ALLOC(ITS_OBJ_CLASS(db))(db, 1, dlen);
        if (ptr->data == NULL)
        {
            HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, ptr->key);
            HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, ptr);

            return (NULL);
        }
    }

    memcpy(ptr->key, key, klen);
    if (dlen && data)
    {
        memcpy(ptr->data, data, dlen);
    }
    ptr->klen = klen;
    ptr->dlen = dlen;

    /* put it into the list */
    if (lkup != NULL)
    {
        /*
         * look for a matching key. We've already done the lookup
         */
        if (list == NULL) /* no match exists? */
        {
            list = (BHASH_Node *)lkup; /* put it after the first node */
        }

        /* add node after this location */
        ptr->next = list->next;
        if (list->next)
        {
            list->next->prev = ptr;
        }
        ptr->prev = list;
        list->next = ptr;

        /*
         * We don't need to do an AddEntry(), we've ensured in the code above
         * that we aren't the first node in the list.
         */
    }
    else /* list is empty */
    {
        ret = HASH_AddEntry(db, rid, kval, (ITS_POINTER)ptr);

        if (ret != ITS_SUCCESS)
        {
            if (ptr->dlen)
            {
                HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, ptr->data);
            }
            HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, ptr->key);
            HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, ptr);

            return (NULL);
        }
    }

    return (ptr);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Given an key and rid, returns the associated row data.  Returns
 *      nonzero error code if an error has occured, 0 otherwise.  Possible
 *      errors are Entry-not-found.
 *
 *  Input Parameters:
 *      db - the table to search in
 *      rid - the resource id to search in
 *      key - key to look up
 *      klen - length of key
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - returns a pointer to the saved data, if the entry is found
 *
 *  Return Value:
 *      If the entry is located, ITS_SUCCESS is returned.
 *      Any other return value indicates that the entry was not found, or
 *          an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI BHASH_Node *
BHASH_FindEntry(HASH_Table db, ITS_UINT rid,
                void *key, ITS_UINT klen)
{
    ITS_INT kval;
    ITS_POINTER lkup;
    BHASH_Node *list;

    ITS_C_ASSERT(key != NULL && klen != 0);

    /* hash it */
    kval = HASH_MakeKey((const char *)key, klen);

    /* find the bucket */
    if (HASH_FindEntry(db, rid, kval, &lkup) != ITS_SUCCESS)
    {
        return (NULL);
    }

    /* find the match */
    for (list = (BHASH_Node *)lkup; list != NULL; list = list->next)
    {
        if (list->klen == klen &&
            memcmp(key, list->key, klen) == 0)
        {
            return (list);
        }
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Given a node, find the previous entry with the same key.
 *
 *  Input Parameters:
 *      db - the table to search in
 *      rid - the resource id to search in
 *      entry - the node to find previous for
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - returns a pointer to the saved data, if the entry is found
 *
 *  Return Value:
 *      If the entry is located, ITS_SUCCESS is returned.
 *      Any other return value indicates that the entry was not found, or
 *          an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI BHASH_Node *
BHASH_FindPrev(BHASH_Node *entry)
{
    BHASH_Node *prev;

    ITS_C_ASSERT(entry != NULL);

    prev = entry->prev;

    if (prev == NULL)
    {
        return (NULL);
    }

    if (prev->klen == entry->klen &&
        memcmp(entry->key, prev->key, prev->klen) == 0)
    {
        return (prev);
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Given a node, find the next entry with the same key.
 *
 *  Input Parameters:
 *      db - the table to search in
 *      rid - the resource id to search in
 *      entry - the node to find previous for
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - returns a pointer to the saved data, if the entry is found
 *
 *  Return Value:
 *      If the entry is located, ITS_SUCCESS is returned.
 *      Any other return value indicates that the entry was not found, or
 *          an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI BHASH_Node *
BHASH_FindNext(BHASH_Node *entry)
{
    BHASH_Node *next;

    ITS_C_ASSERT(entry != NULL);

    next = entry->next;

    if (next == NULL)
    {
        return (NULL);
    }

    if (next->klen == entry->klen &&
        memcmp(entry->key, next->key, next->klen) == 0)
    {
        return (next);
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Deletes the entry for the given ITS_UINT and context from the
 *      datastructure.  This returns the same thing that FindContext
 *      would have returned if called with the same arguments.
 *
 *  Input Parameters:
 *      db - the table to delete from
 *      rid - the resource id to delete from
 *      context - the key in the rid to delete
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the item is successfully deleted, ITS_SUCCESS is returned.
 *      Any other return value indicates that the key was not found,
 *          or that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
BHASH_DeleteEntry(HASH_Table db, ITS_UINT rid,
                  BHASH_Node *node)
{
    ITS_INT kval;
    ITS_POINTER lkup;
    int ret;

    kval = HASH_MakeKey((const char *)node->key, node->klen);

    ret = HASH_FindEntry(db, rid, kval, &lkup);

    /* if this bucket is empty we've got bad things happening */
    if (ret != ITS_SUCCESS || lkup == NULL)
    {
        return (ret);
    }

    /* delete the entry */
    /* only node in list? */
    if (node->prev == NULL && node->next == NULL)
    {
        ret = HASH_DeleteEntry(db, rid, kval);
    }
    /* head of list? */
    else if (node->prev == NULL)
    {
        ret = HASH_AddEntry(db, rid, kval, (ITS_POINTER)node->next);

        node->next->prev = NULL;
    }
    else /* somewhere else in the list */
    {
        ret = ITS_SUCCESS;

        node->prev->next = node->next;
        if (node->next)
        {
            node->next->prev = node->prev;
        }
    }

    /* free the memory */
    if (node->data)
    {
        HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, node->data);
    }

    HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, node->key);
    HASH_CLASS_FREE(ITS_OBJ_CLASS(db))(db, node);

    return (ret);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Iterate a virtual hashtable (identified by its resource id or rid). 
 *      The input parameter iterateEntryDataFn is a pointer to a function with
 *      the signature [int Function(ITS_POINTER data, void* in, void* out)]. 
 *      This iterate function must be user provided and depends of the purpose
 *      of the iteration.
 *
 *  Input Parameters:
 *      db - hashtable.
 *      rid - resource id (identifies a virtual hashtable).
 *      in - pointer to input data passed to iterate entry function.
 *      iterateEntryDataFn - pointer to iterate entry function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      out - pointer to output data passed to iterate entry function.
 *
 *  Return Value:
 *      ITS_SUCCESS or an ITS error code.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int
BHASH_Iterate(HASH_Table db, ITS_UINT rid,
              void *in, void *out,
              BHASH_IterateEntryProc iterateEntryDataFn)
{
    HASH_TableEntry *pentry, entry;
    int i;
    int res;

    ITS_TRACE_DEBUG(("BHASH_Iterate:\n"));

    if (db == NULL || iterateEntryDataFn == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = entry->next)
        {
            if (entry->rid == rid)
            {
                BHASH_Node *ptr;
                    
                for (ptr = (BHASH_Node *)entry->data; ptr != NULL; ptr = ptr->next)
                {
                    res = iterateEntryDataFn(ptr, in, out);

                    if (res != ITS_SUCCESS)
                    {
                        return (res);
                    }
                }
            }
        }
    }

    return (ITS_SUCCESS);
}

