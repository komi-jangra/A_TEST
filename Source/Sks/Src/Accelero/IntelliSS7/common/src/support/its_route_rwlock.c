#include <stdio.h>
#include <its.h>
#include <its_route_rwlock.h>
#include <its_tq_trans.h>
#include <its_dsm.h>
#include <its_route.h>
#include <its_timers.h>
#include <its_trace.h>

/* for now */
/*#define ITS_TRACE_DEBUG printf*/


typedef struct
{
    ITS_UINT  readers[MAX_NODES][MAX_THREADS];
    ITS_UINT  writers[MAX_NODES][MAX_THREADS];
}
LOCK_RecursiveControl;


static  ITS_BOOLEAN  isTableLockedByLocalReader[MAX_THREADS] = {ITS_FALSE};

/* modified by FTM callbacks. */
static  volatile ITS_BOOLEAN peerActive = ITS_TRUE;  

static void ROUTE_WaitForReaders(ROUTE_RWLock *mtp3Lock);

static void MembershipChangeCb( ITS_POINTER object, ITS_POINTER userData,
                                ITS_POINTER callData);


static LOCK_RecursiveControl lockRecursiveControl;

ITSDLLAPI ROUTE_RWLock *routeRWLock = NULL;


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates a RW Lock for the IntelliNet Routing table
 *
 *  Input Parameters:
 *      
 *
 *  Input/Output Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      
 *
 *  Notes:
 *     There is only one instance of a ROUTE RW Lock. 
 *     Multiple invocation of this function return the same RW Lock instance.
 *     DSM_MGMT_REC_ROUTERWLOCK key in the DSM Management Table.
 *
 *  See Also:
 *      
 ****************************************************************************/
ITSDLLAPI ROUTE_RWLock *
ROUTE_RWLockCreate()
{

    ROUTE_RWLock *lock;
    CALLBACK_Manager* cbManager;
    ITS_INT error, i, j, ret;
    ITS_UINT key = DSM_MGMT_REC_ROUTERWLOCK;
    static ITS_BOOLEAN isFtmCbRegistered = ITS_FALSE;
    ITS_UINT nodeId   = DSM_GetNodeId();
    static ITS_UINT FalseReadingFlag = 0;
    if (DSM_LockTable(DSM_MgmtDataFtGroupId, 
                      DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
    {
        ITS_TRACE_DEBUG(("ROUTE_RWLockCreate: Unable to lock MGMT Table"));
        return (NULL);
    }

    lock = (ROUTE_RWLock *) DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                                            DSM_TABLE_MGMT_DATA,
                                            (ITS_OCTET*)&key,
                                            sizeof(key),
                                            &error);
    if (error == ITS_ENOTFOUND)
    {
        /* new entry, allocate the bucket */
        ITS_TRACE_DEBUG(("ROUTE_RWLockCreate: Creating Shared lock"));

        lock = (ROUTE_RWLock *)DSM_AllocNoLock(DSM_MgmtDataFtGroupId,
                                           DSM_TABLE_MGMT_DATA,
                                           (ITS_OCTET *)&key,
                                           sizeof(key),
                                           sizeof(ROUTE_RWLock),
                                           &error);

        if (error != ITS_SUCCESS || lock == NULL)
        {

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

            return (NULL);
        }

        lock->somethingIsWriting = ITS_FALSE;
        lock->writersWaitingForLock  =  0;
        for (i = 0; i < MAX_NODES; i++)
        {
            for(j = 0; j < MAX_THREADS; j++)
            {
                lock->thisInstanceIsReading[i][j] = ITS_FALSE;

                lockRecursiveControl.readers[i][j] = 0;
                lockRecursiveControl.writers[i][j] = 0;
            }
        }


        DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                         DSM_TABLE_MGMT_DATA,
                         (ITS_OCTET *)&key,
                         sizeof(key),
                         lock);
       FalseReadingFlag = 1;
    }
    else if ( (error != ITS_SUCCESS) || (lock == NULL))
    {

        ITS_TRACE_DEBUG(("ROUTE_RWLockCreate: Error Creating Lock;" 
                         " error: %d", error));
        DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

        return (NULL);
    }
    else
    {
        ITS_TRACE_CRITICAL(("ROUTE_RWLockCreate: ROUTE Reader/Writer Lock" 
                         " is already created...FalseReadingFlag[%d]",FalseReadingFlag));
        if(FalseReadingFlag == 0)
        {
    //    ITS_TRACE_CRITICAL(("##########################################################################\n")); 
                
                 for (i = 0; i < MAX_NODES; i++) 
                 {
                     for(j = 0; j < MAX_THREADS; j++)
                     {
                         if(i == nodeId)
                         {
      //                      ITS_TRACE_CRITICAL(("ROUTE_RWLockCreate:thisInstanceIsReading[%d][%d] = [%d]",i,j,lock->thisInstanceIsReading[i][j]));
                            lock->thisInstanceIsReading[i][j] = ITS_FALSE;
                            lockRecursiveControl.readers[i][j] = 0;
                            lockRecursiveControl.writers[i][j] = 0;
       //                     ITS_TRACE_CRITICAL(("ROUTE_RWLockCreate:Setting thisInstanceIsReading[%d][%d] = [%d] \n",i,j,lock->thisInstanceIsReading[i][j]));
                         }

                      }
                }

     //   ITS_TRACE_CRITICAL(("##########################################################################\n")); 
        DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                         DSM_TABLE_MGMT_DATA,
                         (ITS_OCTET *)&key,
                         sizeof(key),
                         lock);
        FalseReadingFlag = 1;
      }
        
    }


    DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

    /*
     * Register membership change callback (to set the peer state).
     * if not already registered
     */

    if (!isFtmCbRegistered)
    {

        cbManager = DSM_GetMembershipChangeCallbacks(DSM_MgmtDataFtGroupId);
        if (cbManager == NULL)
        {
            ITS_TRACE_DEBUG(("ERROR ROUTE_RWLockCreate: "
                            "DSM_GetMembershipChangeCallbacks failed"));

            return (NULL);
        }

        ret = CALLBACK_AddCallback(cbManager, MembershipChangeCb, NULL);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_DEBUG(("ERROR ROUTE_RWLockCreate: " 
                            "CALLBACK_AddCallback failed"));

            return (NULL);
        }

        isFtmCbRegistered = ITS_TRUE;

    }

    ITS_TRACE_DEBUG(("ROUTE_RWLockCreate: Create lock success..."));

    return lock;


}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function 
 *
 *  Input Parameters:
 *      
 *
 *  Input/Output Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      
 *
 *  Notes:
 *
 *  See Also:
 *      
 ****************************************************************************/
ITSDLLAPI int 
ROUTE_RWLockDelete(ROUTE_RWLock *mtp3Lock)
{

    /* TODO */

    return ITS_SUCCESS;

}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function
 *
 *  Input Parameters:
 *
 *
 *  Input/Output Parameters:
 *
 *
 *  Output Parameters:
 *
 *
 *  Return Value:
 *
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITSDLLAPI int 
ROUTE_LockForRead(ROUTE_RWLock *mtp3Lock)
{
    ITS_INT  error;
    ITS_UINT nodeId   = DSM_GetNodeId();
    ITS_UINT threadId = THREAD_GetCurrentThreadID() % MAX_THREADS;

    ROUTE_RWLock *lock;

//    ITS_TRACE_CRITICAL(("ROUTE_LockForRead: for nodeId: %d threadId: %d", 
//                      nodeId, threadId));

    if ( (lockRecursiveControl.readers[nodeId][threadId] != 0) || 
         (lockRecursiveControl.writers[nodeId][threadId] != 0) )
    {

        /* This case handles reccursive read/read and write/read.
         * This instance is already a reader or a writer, so
         * no operation is required.
         */
        ITS_TRACE_DEBUG(("ROUTE_LockForRead#%d: Recursive read;  " 
                  " instance already a reader or writer... do nothing.",
                    threadId));

        lockRecursiveControl.readers[nodeId][threadId]++;
 
        return ITS_SUCCESS;
    }

    /*
     * if the reader is already in active reading mode and noone 
     * is writing  or waiting to get a lock then this function 
     * does nothing.
     *
     * We update the pointer in DSM only when it was necessary to 
     * change state. Since 99% of operations are reads, by default
     * an instance in reading mode.
     */

    if  ( mtp3Lock->somethingIsWriting                                || 
          (mtp3Lock->writersWaitingForLock > 0)                       || 
          !mtp3Lock->thisInstanceIsReading[nodeId][threadId] 
        )
    {

        ITS_UINT key = DSM_MGMT_REC_ROUTERWLOCK;

        ITS_TRACE_DEBUG(("ROUTE_LockForRead#%d: Something is writing or " 
                         "waiting for lock", threadId));
        ITS_TRACE_DEBUG((" ROUTE_LockForRead#%d:  \n"
                        " writersWaitingForLock: %d\n"
                        " somethingIsWriting: %s\n" 
                        " thisInstanceIsReading[%d][%d]: %s\n",
                        threadId, mtp3Lock->writersWaitingForLock,
                        mtp3Lock->somethingIsWriting ? "true" : "false", 
                        nodeId, threadId,
                        mtp3Lock->thisInstanceIsReading[nodeId][threadId] ? 
                                "true" : "false"));

        ITS_TRACE_DEBUG(("ROUTE_LockForRead#%d: Setting "
                         "thisInstanceIsReading to "
                         "ITS_FALSE... \n", threadId));

        DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

        lock = (ROUTE_RWLock *) DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                                               DSM_TABLE_MGMT_DATA,
                                               (ITS_OCTET*)&key,
                                               sizeof(key),
                                               &error);


        if ( (lock != NULL) && (error == ITS_SUCCESS) )
        {

            /*
             * make sure this is set to false to allow the writer that
             * already lock the ROUTE_Table to proceede.
             */
            lock->thisInstanceIsReading[nodeId][threadId] = ITS_FALSE;

            /* commit lock to DSM*/
            DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                             DSM_TABLE_MGMT_DATA,
                             (ITS_OCTET *)&key,
                             sizeof(key),
                             lock) ;

            ITS_TRACE_DEBUG(("ROUTE_LockForRead#%d: thisInstanceIsReading "
                             "is now set to ITS_FALSE\n", threadId));

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
        }
        else
        {
            ITS_TRACE_DEBUG(("ERROR: ROUTE_LockForRead lock == NULL; " 
                            "error %d", error));
            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
        }

 
        if ( ROUTE_LockTable() != ITS_SUCCESS )
        {
            ITS_TRACE_DEBUG(("ERROR: ROUTE_LockForRead -- "
                      "ROUTE_LockTable FAILS"));

            isTableLockedByLocalReader[threadId] = ITS_FALSE;

            return ITS_ENOMEM;
        }

        ITS_TRACE_DEBUG(("ROUTE_LockForRead#%d: ROUTE Table is locked " 
                         "for READ", threadId));

        isTableLockedByLocalReader[threadId] = ITS_TRUE;


        ITS_TRACE_DEBUG(("ROUTE_LockForRead#%d: Setting thisInstanceIsReading" 
                         " to ITS_TRUE\n", threadId));

        DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

        lock =  (ROUTE_RWLock *) DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                                                DSM_TABLE_MGMT_DATA,
                                                (ITS_OCTET*)&key,
                                                sizeof(key),
                                                &error);

        if ( (lock != NULL) && (error == ITS_SUCCESS) ) 
        {
            lock->thisInstanceIsReading[nodeId][threadId] = ITS_TRUE;
            /* commit mtp3Lock to DSM */

            DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                             DSM_TABLE_MGMT_DATA,
                             (ITS_OCTET *)&key,
                             sizeof(key),
                             lock);

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

        } 
        else
        {
            ITS_TRACE_DEBUG(("*** ERROR: ROUTE_LockForRead lock == NULL; " 
                      "error %d", error));

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
        }
    

    }

    lockRecursiveControl.readers[nodeId][threadId]++;

    return ITS_SUCCESS;

}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function 
 *
 *  Input Parameters:
 *      
 *
 *  Input/Output Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      
 *
 *  Notes:
 *
 *  See Also:
 *      
 ****************************************************************************/
ITSDLLAPI int 
ROUTE_LockForWrite(ROUTE_RWLock *mtp3Lock)
{

    ITS_UINT lockKey = DSM_MGMT_REC_ROUTERWLOCK;
    ITS_INT  error;
    ITS_UINT nodeId   = DSM_GetNodeId();
    ITS_UINT threadId = THREAD_GetCurrentThreadID() % MAX_THREADS;

    ROUTE_RWLock *lock;

    ITS_TRACE_DEBUG(("ROUTE_LockForWrite: locking for Write "));

  //  ITS_TRACE_CRITICAL(("ROUTE_LockForWrite: for nodeId: %d threadId: %d ", nodeId, threadId));


    if ( lockRecursiveControl.writers[nodeId][threadId] != 0) 
    {
        ITS_TRACE_DEBUG(("ROUTE_LockForWrite#%d: This instance is already the "
                  "writer... do nothing\n", threadId));

        lockRecursiveControl.writers[nodeId][threadId]++; 
       
        return ITS_SUCCESS; 
    }


    DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

    lock =  (ROUTE_RWLock *)DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                             DSM_TABLE_MGMT_DATA,
                             (ITS_OCTET *)&lockKey,
                             sizeof(ITS_UINT),
                             &error);

    if ( (lock == NULL) || (error != ITS_SUCCESS) )
    {
        ITS_TRACE_DEBUG(("**** ERROR: ROUTE_LockForWrite: error %d", error)); 
        DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
        return ITS_ENOMEM;
    }

    lock->writersWaitingForLock++;

  //  ITS_TRACE_CRITICAL((" ROUTE_LockForWrite#%d : Setting writersWaitingForLock "
//             "to %d ***", threadId, lock->writersWaitingForLock));

    /*
     * an instance is a reader by default... now unset the reader flag
     * since we are now asking for a write permission.
     */
    lock->thisInstanceIsReading[nodeId][threadId] = ITS_FALSE;

    DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                     DSM_TABLE_MGMT_DATA,
                     (ITS_OCTET *)&lockKey, sizeof(ITS_UINT),
                     lock);

    DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
 
    /* I need to do a DSM Lock in any cases!!! */
    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        ITS_TRACE_DEBUG(("ERROR: ROUTE_LockForWrite -- ROUTE_LockTable FAILS"));
        return ITS_ENOMEM;
    }

    ITS_TRACE_DEBUG(("*** ROUTE_LockForWrite#%d: ROUTE Table is locked " 
              "for WRITE ***", threadId));

    /*
     * this call blocks until all active readers are done
     */
    ROUTE_WaitForReaders(lock);

    DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

    lock =  (ROUTE_RWLock *)DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                             DSM_TABLE_MGMT_DATA,
                             (ITS_OCTET *)&lockKey,
                             sizeof(ITS_UINT),
                             &error);

    if ( (lock == NULL) || (error != ITS_SUCCESS) )
    {
        ITS_TRACE_DEBUG(("ERROR: ROUTE_LockForWrite; error = %d", error)); 
        DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
        return ITS_ENOMEM;
    }
 
    lock->somethingIsWriting = ITS_TRUE;
    lock->writersWaitingForLock--;

    ITS_TRACE_DEBUG(("ROUTE_LockForWrite#%d : Setting writersWaitingForLock" 
              " to %d ", threadId, lock->writersWaitingForLock));

    DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                     DSM_TABLE_MGMT_DATA,
                     (ITS_OCTET *)&lockKey, sizeof(ITS_UINT),
                     lock);

    DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

    lockRecursiveControl.writers[nodeId][threadId]++; 

  
    return ITS_SUCCESS;
 
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function 
 *
 *  Input Parameters:
 *      
 *
 *  Input/Output Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      
 *
 *  Notes:
 *
 *  See Also:
 *      
 ****************************************************************************/
ITSDLLAPI int 
ROUTE_UnlockRead(ROUTE_RWLock *mtp3Lock, const TQUEUETRAN_Manager *tq)
{
    ITS_INT error;

    ROUTE_RWLock *lock;
    static ITS_UINT maxQueueSize=0;
    ITS_UINT qSize=0;
    ITS_UINT nodeId   = DSM_GetNodeId();
    ITS_UINT threadId = THREAD_GetCurrentThreadID() % MAX_THREADS;


    ITS_TRACE_DEBUG(("ROUTE_UnlockRead#%d Unlocking Read...", threadId));
   // ITS_TRACE_CRITICAL(("*** ROUTE_UnlockRead: for nodeId: %d threadId: %d ",
   //            nodeId, threadId));

    lockRecursiveControl.readers[nodeId][threadId]--;

    if ( (lockRecursiveControl.readers[nodeId][threadId] != 0) || 
         (lockRecursiveControl.writers[nodeId][threadId] != 0) )
    {
        /* 
         *  handle recursive case read/read and write/read 
         *  when the second read is being unloked.
         */ 

        ITS_TRACE_DEBUG(("ROUTE_UnlockRead#%d: Recursive read unlock;  " 
                  " instance already a reader or writer... do nothing.",
                    threadId));

        return ITS_SUCCESS;    
    }

    ITS_TRACE_DEBUG(("ROUTE_UnlockRead#%d: no readers or writers ", threadId));

    qSize = (tq == NULL) ? 0 : TQUEUETRAN_EMLIST(tq)->list.count;

    maxQueueSize = ((qSize > 0) && (qSize > maxQueueSize)) ? 
                   qSize : maxQueueSize;


    /* 
     * To minimize DSM access, we update the reader flag to false
     * when something is waiting for lock or when the queue is empty.
     * Otherwise, this instance remains in reader mode
     */

    ITS_TRACE_DEBUG(("ROUTE_UnlockRead#%d : mtp3Lock->thisInstanceIsReading %s",
                      threadId, 
                      mtp3Lock->thisInstanceIsReading[nodeId][threadId] ? 
                      "true" : "false"));

    if ( (qSize == 0)  || (mtp3Lock->writersWaitingForLock > 0)  )
    {

        ITS_UINT key = DSM_MGMT_REC_ROUTERWLOCK;
 
        ITS_TRACE_DEBUG(("ROUTE_UnlockRead: qSize %d writersWaitingForLock %d "
                         "somethingIsWriting %s\n", 
                          qSize, 
                          mtp3Lock->writersWaitingForLock, 
                          mtp3Lock->somethingIsWriting ? "true" : "false"));

        /*
         * In this particular case, where the queue is empty, we set 
         * flag to FALSE. This will avoid blocking other writers. 
         */

        ITS_TRACE_DEBUG(("ROUTE_UnlockRead: Set thisInstanceIsReading " 
                         "to ITS_FALSE"));

        DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

        lock =  (ROUTE_RWLock *)DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                        DSM_TABLE_MGMT_DATA,
                        (ITS_OCTET*)&key,
                        sizeof(key),
                        &error);

        if ( (lock != NULL) && (error == ITS_SUCCESS) )
        {
            lock->thisInstanceIsReading[nodeId][threadId] = ITS_FALSE;

            DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                   DSM_TABLE_MGMT_DATA,
                   (ITS_OCTET *)&key,
                   sizeof(key),
                   lock) ;

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);


        }
        else
        {

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
            ITS_TRACE_DEBUG(("ERROR: ROUTE_LockForRead; error %d", error));
        }

    }


    if (isTableLockedByLocalReader[threadId])
    {
        ITS_TRACE_DEBUG(("ROUTE_UnlockRead#%d: table was lock... unlocking "
                         "table ***", threadId));
        isTableLockedByLocalReader[threadId] = ITS_FALSE;
        ROUTE_UnlockTable(); /* to signal readers on the mate node */
    }

    
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function 
 *
 *  Input Parameters:
 *      
 *
 *  Input/Output Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      
 *
 *  Notes:
 *
 *  See Also:
 *      
 ****************************************************************************/
ITSDLLAPI int 
ROUTE_UnlockWrite(ROUTE_RWLock *mtp3Lock)
{
    ITS_UINT key = DSM_MGMT_REC_ROUTERWLOCK;
    ITS_INT error;
    ROUTE_RWLock *lock;
    ITS_UINT nodeId   = DSM_GetNodeId();
    ITS_UINT threadId = THREAD_GetCurrentThreadID() % MAX_THREADS;


   // ITS_TRACE_CRITICAL(("ROUTE_UnlockWrite: for nodeId: %d threadId: %d", nodeId, threadId));

    lockRecursiveControl.writers[nodeId][threadId]--;

    if (lockRecursiveControl.writers[nodeId][threadId] != 0)
    {
        /* 
         *  handle recursive case write/write 
         *  when the second write is being unloked.
         */ 

        ITS_TRACE_DEBUG(("*** ROUTE_UnlockWrite#%d: Recursive write unlock; " 
                  "instance already a writer... do nothing.",
                    threadId));

        return ITS_SUCCESS;    
    }

    ITS_TRACE_DEBUG(("*** ROUTE_UnlockWrite: Set somethingIsWriting " 
                     "to ITS_FALSE ***"));

    DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

    lock =  (ROUTE_RWLock *)DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                        DSM_TABLE_MGMT_DATA,
                        (ITS_OCTET*)&key,
                        sizeof(key),
                        &error);
    if ( (lock != NULL) && (error == ITS_SUCCESS) )
    {
        lock->somethingIsWriting = ITS_FALSE;

        if  (lockRecursiveControl.readers[nodeId][threadId] != 0) 
        {
            /* 
             *  handle recursive case read/write 
             *  when the write is being unloked.
             *  Reset the reader flag to true.
             */
            ITS_TRACE_DEBUG(("ROUTE_UnlockWrite#%d: Recursive write unlock;  " 
                      " instance was a reader... reset to reader mode",
                        threadId));

            lock->thisInstanceIsReading[nodeId][threadId] = ITS_TRUE;

        }


        DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                   DSM_TABLE_MGMT_DATA,
                   (ITS_OCTET *)&key,
                   sizeof(key),
                   lock) ;
        DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
    }
    else
    {

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
            ITS_TRACE_DEBUG(("ERROR: ROUTE_LockForRead; error %d", error));
    }

 
    ROUTE_UnlockTable();


    return ITS_SUCCESS;

} 

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function 
 *
 *  Input Parameters:
 *      
 *
 *  Input/Output Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      
 *
 *  Notes:
 *
 *  See Also:
 *      
 ****************************************************************************/
static void 
ROUTE_WaitForReaders(ROUTE_RWLock *mtp3Lock)
{
    ITS_UINT i, j;
    ITS_BOOLEAN readersActive = ITS_FALSE;
    ITS_UINT myNodeId = DSM_GetNodeId();

    ITS_TRACE_DEBUG(("ROUTE_WaitForReaders..."));
  //  ITS_TRACE_CRITICAL(("ROUTE_WaitForReaders... mynodeId %u peerActive %d ",myNodeId,peerActive));
    do
    {
        readersActive = ITS_FALSE;

        for (i = 0; i < MAX_NODES; i++)
        {
            for(j = 0; j < MAX_THREADS; j++)
            {
                ITS_TRACE_DEBUG(("ROUTE_WaitForReaders: " 
                          "thisInstanceIsReading[%d][%d]: %s ",
                          i, j, mtp3Lock->thisInstanceIsReading[i][j] ? 
                          "true" : "false"));

                if (mtp3Lock->thisInstanceIsReading[i][j])  
                {

                    if (!peerActive && (i != myNodeId))
                    {

                        ITS_TRACE_DEBUG(("ROUTE_WaitForReaders: setting "
                               "thisInstanceIsReading[%d][%d] to ITS_FALSE",
                                i, j));

                        mtp3Lock->thisInstanceIsReading[i][j] = ITS_FALSE;
                               

                    }
                    else
                    {
                        /* at least one node is reading */
                        readersActive = ITS_TRUE;     
    //                    ITS_TRACE_CRITICAL(("ROUTE_WaitForReaders... readersActive = ITS_TRUE mtp3Lock->thisInstanceIsReading[%d][%d]",i,j));
                        break;
                    }
                }
            } 
            if (readersActive)
            {
                break;
            }
        }

        if (readersActive)
        {
      //      ITS_TRACE_CRITICAL(("Going For Sleep 200 mtp3Lock->thisInstanceIsReading[%d][%d]",i,j));
            TIMERS_USleep(200);
        }

    }
    while( readersActive );

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      object      - see DSM API.
 *      userData    - see DSM API.
 *      callData    - see DSM API.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
MembershipChangeCb(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{
    DSM_MembershipChangeCbData*
        membershipChangeCbData =
            (DSM_MembershipChangeCbData*)callData;

    /* Two nodes system only. */
    /*if (membershipChangeCbData->memberNodeId != DSM_GetNodeId())*/
    {
        if (membershipChangeCbData->
                membershipChangeType ==
                    DSM_FT_GROUP_MEMBER_LEAVE)
        {
            ITS_TRACE_DEBUG(("DSM_FT_GROUP_MEMBER_LEAVE: Setting peerActive to "
                   "ITS_FALSE"));

            peerActive = ITS_FALSE;
        }
        else if (membershipChangeCbData->
                     membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_JOIN)
        {

            ITS_TRACE_DEBUG(("DSM_FT_GROUP_MEMBER_JOIN: Setting peerActive "
                   "to ITS_TRUE"));

            peerActive = ITS_TRUE;

        }
        else if (membershipChangeCbData->
                     membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_ALIVE)
        {

            ITS_TRACE_DEBUG(("DSM_FT_GROUP_MEMBER_ALIVE: Setting peerActive " 
                   "to ITS_TRUE"));

            peerActive = ITS_TRUE;

        }

        else
        {
            /* Ignore. */
        }
    }
}



