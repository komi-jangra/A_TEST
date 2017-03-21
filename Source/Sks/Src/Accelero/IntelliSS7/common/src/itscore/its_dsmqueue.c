/****************************************************************************
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
 * LOG: Revision 8.2  2005/03/21 13:51:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.3  2003/01/21 22:47:57  mmiers
 * LOG: Warning removal, add splay tree class.
 * LOG:
 * LOG: Revision 7.2  2003/01/16 19:08:31  mmiers
 * LOG: Warning removal, Borland update.
 * LOG:
 * LOG: Revision 7.1  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.5  2003/01/10 19:52:01  sjaddu
 * LOG: Unlock the table in FindDSMQue().
 * LOG:
 * LOG: Revision 7.4  2002/12/03 16:15:52  ngoel
 * LOG: check for null queue before deleting
 * LOG:
 * LOG: Revision 7.3  2002/11/22 18:57:53  randresol
 * LOG: Meke sure QDATA table is unlocked in DSMQUEUE_Delete
 * LOG:
 * LOG: Revision 7.2  2002/11/09 21:41:11  randresol
 * LOG: Add fix for faster processing
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.9  2002/08/20 20:08:27  mmiers
 * LOG: Missing return.
 * LOG:
 * LOG: Revision 1.8  2002/08/16 16:23:40  randresol
 * LOG: Fix DSM Error in DSMQUEUE_Dequeue
 * LOG:
 * LOG: Revision 1.6  2002/06/21 20:28:00  randresol
 * LOG: Fix bug in DSMQUEUE_Enqueue
 * LOG:
 * LOG: Revision 1.5  2002/05/15 14:59:56  randresol
 * LOG: remove ITS_EVENT_TERM bug
 * LOG:
 * LOG: Revision 1.4  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 1.3  2002/03/28 01:47:12  mmiers
 * LOG: Warning removal (dsmqueue on linux).
 * LOG: License optimizations when capability checking is not desired.
 * LOG:
 * LOG: Revision 1.2  2002/03/27 18:31:57  randresol
 * LOG: Remove Visual C++ Warnings
 * LOG:
 * LOG: Revision 1.1  2002/03/26 18:38:01  randresol
 * LOG: Add Implementation that creates and manipulates Queues in DSM
 * LOG:
 * LOG: 
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_dsm.h>
#include <its_dsmqueue.h>


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *       
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *      
 *  See Also:
 *      
 ****************************************************************************/
ITSDLLAPI DSM_Queue *  
DSMQUEUE_Create(ITS_UINT keyType, ITS_UINT keyValue)
{

    /* note: for a more flexible queue, another DSM table
       would be necessary to store these values...
    */

    DSM_Queue *queue;

    ITS_INT error;

    DSMQUEUE_EntryKey newKey;

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES) != ITS_SUCCESS)
    {
        return NULL; 
    }

    newKey.type = keyType;
    newKey.value = keyValue;    
    newKey.maxQueueSize = 0;

    queue = (DSM_Queue *) DSM_FindNoLock(DSM_Mtp3FtGroupId,
                            DSM_TABLE_QUEUES,
                            (ITS_OCTET *)&newKey,
                            DSMQUEUE_KEY_SIZE,
                            &error);
 
    if (error == ITS_ENOTFOUND)
    {
        /* new entry, allocate the bucket */
        queue = (DSM_Queue *)DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                                    DSM_TABLE_QUEUES,
                                    (ITS_OCTET *)&newKey,
                                     DSMQUEUE_KEY_SIZE,
                                     sizeof(DSM_Queue),
                                     &error);
        if (error != ITS_SUCCESS || queue == NULL)
        {
            /*ITS_TRACE_ERROR(("Create Table: Out of memory\n")); */

            DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);
            
            return NULL;
        }
    }
    else if (error != ITS_SUCCESS || queue == NULL)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

        return NULL;
    }
    else 
    {
        /* queue already exists  */
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

        return NULL;
    }
         
      
    (queue)->key = newKey;
    (queue)->numEntries = 0;
    (queue)->firstEntry = 0;
    (queue)->lastEntry = -1;
    (queue)->entries = NULL; 


    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_QUEUES,
                     (ITS_OCTET *)&newKey,
                      DSMQUEUE_KEY_SIZE,
                     queue);

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);
 
 
    return queue;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add 
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - .  Any other value indicates
 *      an error.
 *
 *  Notes:
 *      
 *  See Also:
 *      
 ****************************************************************************/
ITSDLLAPI int
DSMQUEUE_Enqueue(DSM_Queue *queue, ITS_EVENT ev)
{
    DSMQUEUE_Entry *qEntries;
    DSMQUEUE_Entry newEnt;
    DSMQUEUE_EntryKey oldKey = queue->key;
    int error;


    /* note: implementation mimics a circular list */


    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA) != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
        return (ITS_EBADMUTEX);
    } 
    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES) != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        ITS_EVENT_TERM(&ev);
        return (ITS_EBADMUTEX);
    }

    /* Build the new entry */
    memset(&newEnt, 0, sizeof(DSMQUEUE_Entry) );
    newEnt.len = ev.len;
    newEnt.src = ev.src;
    memcpy(newEnt.data, ev.data, ev.len);

    if ( queue->key.maxQueueSize && (queue->numEntries < queue->key.maxQueueSize ) )
    {
        /*
        ** The queue has already been created AND there is enough
        ** space to add this new entry
        */

        queue->lastEntry = (queue->lastEntry + 1) % (int)queue->key.maxQueueSize;

        queue->entries  = (DSMQUEUE_Entry *) DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                                 DSM_TABLE_QDATA,
                                                 (ITS_OCTET *)&queue->key,
                                                  sizeof(DSMQUEUE_EntryKey),
                                                  &error);

        if (error != ITS_SUCCESS || queue->entries == NULL)
        {
            /*printf("ERROR:  queue->entries=DSM_FindNoLock\n");*/
            DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
            DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

            ITS_EVENT_TERM(&ev);
            return (ITS_ENOMEM);

        }


        queue->entries[queue->lastEntry] = newEnt;
        queue->numEntries++;
     

        DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                         DSM_TABLE_QDATA,
                         (ITS_OCTET *)&queue->key,
                         sizeof(DSMQUEUE_EntryKey),
                         queue->entries);
    
        DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                         DSM_TABLE_QUEUES,
                         (ITS_OCTET *)&queue->key,
                          DSMQUEUE_KEY_SIZE,
                         queue);


        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

        ITS_EVENT_TERM(&ev);
  
        /*
        printf("\n*** DSMQUEUE_Enqueue: Data Enqueued ***\n"
               "       - queue->key.type      %d         \n" 
               "       - queue->key.value     %d         \n" 
               "       - queue->key.maxQueueSize  %d     \n" 
               "       - queue->numEntries    %d         \n" 
               "       - queue->firstEntry    %d         \n" 
               "       - queue->lastEntry     %d         \n", 
               queue->key.type, queue->key.value, queue->key.maxQueueSize,
               queue->numEntries, queue->firstEntry, queue->lastEntry);
       */


        return ITS_SUCCESS;

    }
    
    /*
    ** we're here because the queue is either empty or full 
    */

    if (queue->key.maxQueueSize == 0)
    {
        /* This queue is empty, let's set the initial queue size */
        queue->key.maxQueueSize = QUEUE_INITIAL_SIZE;    
    }
    else
    {
        /* This queue is full, it needs to grow */
        queue->key.maxQueueSize *= QUEUE_GROWTH_FACTOR;

        /* note: we may need an upper bound value */
    }
    
    /* sanity check 1: make sure the new entry doesn't already exist */

    qEntries = (DSMQUEUE_Entry *) DSM_FindNoLock(DSM_Mtp3FtGroupId, 
                                                  DSM_TABLE_QDATA,
                                                 (ITS_OCTET *)&queue->key,
                                                  sizeof(DSMQUEUE_EntryKey),
                                                  &error);
    if (error != ITS_ENOTFOUND ||
        (error == ITS_SUCCESS && qEntries != NULL))
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

        ITS_EVENT_TERM(&ev);
        return (ITS_ENOMEM);
    
    }

    /* sanity check 2: make sure the old entry matches what's in this queue */

    qEntries = (DSMQUEUE_Entry *) DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                                 DSM_TABLE_QDATA,
                                                 (ITS_OCTET *)&oldKey,
                                                  sizeof(DSMQUEUE_EntryKey),
                                                  &error);
 
    /* NOTE: qEntries is NULL when this queue has not been allocated yet */
    if (qEntries != queue->entries)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

        ITS_EVENT_TERM(&ev);
        return (ITS_ENOMEM);
    }

    /* allocate the new entries */
    qEntries = (DSMQUEUE_Entry *)DSM_AllocNoLock(DSM_Mtp3FtGroupId, 
                                     DSM_TABLE_QDATA,
                                     (ITS_OCTET *)&queue->key,
                                     sizeof(DSMQUEUE_EntryKey),
                                     sizeof(DSMQUEUE_Entry) * 
                                         queue->key.maxQueueSize,
                                     &error);

    if (error != ITS_SUCCESS || qEntries == NULL)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

        ITS_EVENT_TERM(&ev);
        return (ITS_ENOMEM);
    }

    /* copy over the old entries, if any */
    if (queue->numEntries)
    {
        ITS_UINT i;
        
        /* copy in the right order, from fristEntry to fastEntry */
        for (i = 0; i < queue->numEntries ; i++)
        {
            int idx = (int)(queue->firstEntry + i) % (int)oldKey.maxQueueSize;
     
            qEntries[i] = queue->entries[idx];
        }
        queue->firstEntry = 0;
        queue->lastEntry  = (int)queue->numEntries - 1;
            

    } 

    /* release the old range, if any */
    if (queue->entries)
    {
        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_QDATA,
                       (ITS_OCTET *)&oldKey,
                       sizeof(DSMQUEUE_EntryKey),
                       queue->entries);

    } 

    /* set new queue entries */
    queue->entries = qEntries;

    /* add the new element */
    queue->lastEntry = (queue->lastEntry + 1) % (int)queue->key.maxQueueSize;
    queue->entries[queue->lastEntry] = newEnt;
    queue->numEntries++;

    /* commit new queue */
    DSM_CommitNoLock(DSM_Mtp3FtGroupId, 
                     DSM_TABLE_QDATA,
                     (ITS_OCTET *)&queue->key,
                     sizeof(DSMQUEUE_EntryKey),
                     qEntries);

    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_QUEUES,
                     (ITS_OCTET *)&queue->key,
                     DSMQUEUE_KEY_SIZE,
                     queue);


    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

    ITS_EVENT_TERM(&ev);

/*
    printf("\n*** DSMQUEUE_Enqueue: Data Enqueued ***\n"
           "       - queue->key.type      %d         \n" 
           "       - queue->key.value     %d         \n" 
           "       - queue->key.maxQueueSize  %d     \n" 
           "       - queue->numEntries    %d         \n" 
           "       - queue->firstEntry    %d         \n" 
           "       - queue->lastEntry     %d         \n", 
           queue->key.type, queue->key.value, queue->key.maxQueueSize,
           queue->numEntries, queue->firstEntry, queue->lastEntry);
*/


    return (ITS_SUCCESS);

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *         
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      
 *  Notes: 
 *      
 *  See Also:
 *       
 ****************************************************************************/
ITSDLLAPI int
DSMQUEUE_Dequeue(DSM_Queue *queue, ITS_EVENT **data)
{

    ITS_EVENT *ev;
    ITS_UINT idx;


    /* note: implementation mimics a circular list */

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    } 

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES) != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        return (ITS_EBADMUTEX);
    }

    if (queue->numEntries == 0)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);
        return ITS_ENOMSG;

    }

    *data = NULL;

    if ((ev = (ITS_EVENT *) ITS_Malloc(sizeof(ITS_EVENT) )) == NULL)
    {
        /*ITS_TRACE_ERROR(("DSMQUEUE_Dequeue: memery allocation failed\n"));*/
 
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);
        return (ITS_ENOMEM);
    }

    idx = queue->firstEntry;
    ITS_EVENT_INIT(ev, queue->entries[idx].src, queue->entries[idx].len); 
    memcpy(ev->data, queue->entries[idx].data, ev->len); 

    *data = ev;;
 
    queue->firstEntry = (queue->firstEntry + 1) % (int)queue->key.maxQueueSize;
    queue->numEntries--;

    if (queue->numEntries == 0)
    {
        queue->firstEntry = 0;
        queue->lastEntry = -1;

        /* Question: Should we deallocate the queue from DSM?? */
    } 
/*
    let's commit only the queue header... for faster processing
    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_QDATA,
                     (ITS_OCTET *)&queue->key,
                     sizeof(DSMQUEUE_EntryKey),
                     queue->entries);
*/
    
    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_QUEUES,
                     (ITS_OCTET *)&queue->key,
                     DSMQUEUE_KEY_SIZE,
                     queue);

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

/*
    printf("\n*** DSMQUEUE_Dequeue: Data Dequeued ***\n"
           "       - queue->key.type      %d         \n"
           "       - queue->key.value     %d         \n"
           "       - queue->key.maxQueueSize  %d     \n"
           "       - queue->numEntries    %d         \n"
           "       - queue->firstEntry    %d         \n"
           "       - queue->lastEntry     %d         \n",
           queue->key.type, queue->key.value, queue->key.maxQueueSize,
           queue->numEntries, queue->firstEntry, queue->lastEntry);
*/


    return ITS_SUCCESS;
   
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *         
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      
 *  Notes: 
 *      
 *  See Also:
 *       
 ****************************************************************************/
ITSDLLAPI int
DSMQUEUE_Delete(DSM_Queue *queue)
{

    int error;
    DSMQUEUE_EntryKey oldKey;

    if (queue == NULL)
    {
        return (ITS_SUCCESS);
    }

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES) != ITS_SUCCESS)
    {
        return (ITS_ENOMEM);
    }      

    oldKey = queue->key; 

  
    queue = (DSM_Queue *) DSM_FindNoLock(DSM_Mtp3FtGroupId, 
                            DSM_TABLE_QUEUES,
                            (ITS_OCTET *) &oldKey, 
                            DSMQUEUE_KEY_SIZE,
                            &error);

    if (error != ITS_SUCCESS || queue == NULL)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);
        return ITS_ENOMEM;    
    }


    /* let's free the queue entries first */

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA) != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);
        return (ITS_ENOMEM); 
    }

    queue->entries = (DSMQUEUE_Entry *) DSM_FindNoLock(DSM_Mtp3FtGroupId, 
                                             DSM_TABLE_QDATA,
                                             (ITS_OCTET *) &oldKey,
                                             sizeof(DSMQUEUE_EntryKey),
                                             &error);

    if (error == ITS_ENOTFOUND)
    {
       /*ITS_TRACE_DEBUG(("No entries found for table: keyType = %d "
                        "keyValue = %d  keyIndex %d", queue->key.type, 
                        queue->key.value, queue->key.maxQueueSize)) ;*/
    }
    else if (error != ITS_SUCCESS || queue->entries == NULL)
    {
       /*ITS_TRACE_ERROR(("Cannot locate the entries for table: keyType = %d "
                        "keyValue = %d  keyIndex %d", queue->key.type, 
                        queue->key.value, queue->key.maxQueueSize)) ;*/ 
    }
    else
    {
       /* now let's deallocate the entries */
       
       DSM_FreeNoLock(DSM_Mtp3FtGroupId, 
                       DSM_TABLE_QDATA,
                       (ITS_OCTET *) &oldKey,
                       sizeof(DSMQUEUE_EntryKey),
                       queue->entries); 


    }
 
    /* Deallocate the queue header */

    DSM_FreeNoLock(DSM_Mtp3FtGroupId, 
                   DSM_TABLE_QUEUES, 
                   (ITS_OCTET *) &oldKey,
                   DSMQUEUE_KEY_SIZE,
                   queue);
      
    
              
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

    return ITS_SUCCESS;
    
   
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *         
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      
 *  Notes: 
 *      
 *  See Also:
 *       
 ****************************************************************************/
ITS_EVENT QueueEntryToItsEvent(DSMQUEUE_Entry entry)
{
    ITS_EVENT ev;

    ITS_EVENT_INIT(&ev, entry.src, entry.len);
    memcpy(ev.data, entry.data, entry.len);

    return ev;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *         
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      
 *  Notes: 
 *      
 *  See Also:
 *       
 ****************************************************************************/
ITSDLLAPI int
DSMQUEUE_Insert(DSM_Queue *queue, DSMQUEUE_InsertFunc func, ITS_EVENT ev)
{

    ITS_UINT numEntries, count;
    int idx;
    ITS_EVENT qEntryEv;
 
    QUEUE_Entry b, a, n;

    QUEUE_Entry *bef = &b , *aft = &a, *ni= &n;

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA) != ITS_SUCCESS)
    {
        /*ITS_EVENT_TERM(&ev); */
        return (ITS_EBADMUTEX);
    }
 
    memcpy(&ni->data, &ev, sizeof(ITS_EVENT)); 

    ni->data = ev;

    if (queue->numEntries == 0)
    {
        /* Queue is empty */
        if ((*func)(NULL, NULL, ni))
        {
           DSMQUEUE_Enqueue(queue, ev); 
        }

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA);     

        /* FIXME: Core here */
        /*ITS_EVENT_TERM(&ev);*/

        return ITS_SUCCESS;
    }


    numEntries = queue->numEntries;

    idx = queue->firstEntry; 

    for (count = 0 ; count < numEntries+1; count++)
    {

        bef = &b ; aft = &a;


        if (count == numEntries)
        {
            aft = NULL;
            qEntryEv = QueueEntryToItsEvent(queue->entries[queue->lastEntry]);
            memcpy(&bef->data, &qEntryEv, sizeof(ITS_EVENT));  

        }

        else if (idx == queue->firstEntry)
        {
            bef = NULL;
            qEntryEv = QueueEntryToItsEvent(queue->entries[idx]);
            memcpy(&aft->data, &qEntryEv, sizeof(ITS_EVENT)); 
        }

        else
        {
           ITS_UINT prevIdx;

           /* Entry in the middle */
           prevIdx = (idx != 0 ? idx - 1 : queue->key.maxQueueSize - 1);
           qEntryEv = QueueEntryToItsEvent(queue->entries[prevIdx]);
           memcpy(&bef->data, &qEntryEv, sizeof(ITS_EVENT)); 

           qEntryEv = QueueEntryToItsEvent(queue->entries[idx]);
           memcpy(&aft->data, &qEntryEv, sizeof(ITS_EVENT) ); 

        }
        
        if ((*func)(bef, aft, ni))
        {
            ITS_EVENT toAdd, tmp;    
            
            
	    if (count ==  queue->key.maxQueueSize)
            {
                /* The end of the queue has been reached; 
                ** just enqueue the new event
                */
                DSMQUEUE_Enqueue(queue, ev); 
                break;
            }


            toAdd = ev; 
            tmp = QueueEntryToItsEvent(queue->entries[idx]);

            queue->lastEntry = idx  - 1 ;

            queue->numEntries = ( (idx - queue->firstEntry) < 0 ?
                                  (idx - queue->firstEntry) +
                                   queue->key.maxQueueSize      : 
                                  (idx - queue->firstEntry)  );

            do   
            {
                DSMQUEUE_Enqueue(queue, toAdd);
                idx = (idx + 1) % (int)queue->key.maxQueueSize;
                toAdd = tmp;
                tmp   = QueueEntryToItsEvent(queue->entries[idx]);
                count++;

            }
            while(count < numEntries + 1);

            break;      
        }

        idx = (idx + 1) % (int)queue->key.maxQueueSize;

    }


    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QDATA); 

    /* FIXME ?? cores there */
 
   /* ITS_EVENT_TERM(&ev); */

    return ITS_SUCCESS;

}     


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *         
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      
 *  Notes: 
 *      
 *  See Also:
 *       
 ****************************************************************************/
ITSDLLAPI int
DSMQUEUE_Unlink(DSM_Queue *queue, DSMQUEUE_Entry *ent)
{
    int count, numEntries;
    DSMQUEUE_Entry *iterator;

    numEntries = (int)queue->numEntries;
    iterator = &queue->entries[queue->firstEntry];

    for (count = 0; count < numEntries; count++)
    {
        if (iterator == ent)
        {
            /* entry found, let's remove it */
                  
            queue->numEntries--;

            do
            {

                iterator = DSMQUEUE_NEXT(queue, iterator);
           
                memcpy(ent, iterator, sizeof(DSMQUEUE_Entry) );
 
                ent = iterator;

                count++;
                
            }
            while (count < numEntries );

            queue->lastEntry = (!queue->lastEntry && queue->numEntries) ?
                               (int)queue->key.maxQueueSize - 1               :
                               queue->lastEntry - 1;
            
        }

        iterator = DSMQUEUE_NEXT(queue, iterator);

    } 
    
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *         
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      
 *  Notes: 
 *      
 *  See Also:
 *       
 ****************************************************************************/
ITSDLLAPI DSM_Queue *
DSMQUEUE_FindQueue(ITS_UINT keyType, ITS_UINT keyValue)
{

    /* note: for a more flexible queue, another DSM table
       would be necessary to store these values...
    */

    DSM_Queue *queue;

    ITS_INT error;

    DSMQUEUE_EntryKey key;

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES) != ITS_SUCCESS)
    {
        return NULL;
    }

    key.type = keyType;
    key.value = keyValue;
    key.maxQueueSize = 16;

    queue = (DSM_Queue *) DSM_FindNoLock(DSM_Mtp3FtGroupId, 
                            DSM_TABLE_QUEUES,
                            (ITS_OCTET *)&key,
                            DSMQUEUE_KEY_SIZE,
                            &error);

    if (error != ITS_SUCCESS || queue == NULL)
    {
        /* queue cannot be found */

       DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);
       
       return NULL; 
    }

    queue->entries  = (DSMQUEUE_Entry *) DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                             DSM_TABLE_QDATA,
                                             (ITS_OCTET *)&queue->key,
                                              sizeof(DSMQUEUE_EntryKey),
                                              &error);

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_QUEUES);

    return (queue);
}
