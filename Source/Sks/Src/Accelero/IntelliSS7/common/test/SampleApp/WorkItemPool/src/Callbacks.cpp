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
 *
 *  ID: $Id: Callbacks.cpp,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:33  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:26  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/08 11:38:52  kannanp
 * LOG: WorkItem Initial - Hari Priya.
 * LOG:
 * LOG:
****************************************************************************/
#ident "$Id: Callbacks.cpp,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $"

#include <its++.h>
#include <engine++.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#include <stdio.h>
#include <WorkItem.h>
#include <its_worker.h>
#include <its_transports.h>

#define WORK_ITEM_QUEUE  50001
#define NUM_OF_THREADS   4
#define SIZE_OF_WORKITEM 12 

WORKITEMPOOL *AppWorkItemPool; 
WORKITEM_Instance *item;

/***********************************************************************
 *  Implementation for worker pool call backs.
 *  
 ***********************************************************************/

extern "C"
{

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This function handles the messages received from Workitem queue. 
 *      When a event is received on a thread, the thread id, the event
 *      length and data are printed on the standard output. 
 *
 *  Input Parameters:
 *      arg -
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
****************************************************************************/

void 
App_func(void *args)
{
   ITS_UINT thrid;
   ITS_EVENT *evt = (ITS_EVENT*) args;

   APP_TRACE_DEBUG(("App_func "));

   /* Print the Thread ID of the thread on which the event 
      is dispatched by the WorkItemPool */ 

   thrid = THREAD_GetCurrentThreadID();
   APP_TRACE_DEBUG((" \nTHREAD ID : %d",thrid));
 
   /* Print the Received Event Length and Data on the stdout */

   //APP_TRACE_DEBUG(("\n Event length %d\n", evt->len));
   APP_TRACE_DEBUG(("\n Event length %d\n", evt->len));
   APP_TRACE_DEBUG(("\n Event Data\n"));
   //APP_TRACE_DEBUG(("\n Event Data\n"));

   for(int i = 0; i < evt->len; i++)
   {
       printf("%c ", evt->data[i]);
   }
   printf("\n");


   fflush(stdout);
}

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This Callback initializes the Sample Application. It creates the 
 *      WorkItemPool.
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
 *      The following sequence is performed:
 *      1. Trace is initialized.
 *      2. SystemConfiguration Database is initialized.
 *
 ****************************************************************************/

void App_PreFunc(void)
{
   void *data;

   APP_TRACE_DEBUG((" App_PreFunc"));

   /* Create a WorkItemPool that internally creates a Queue 
      and returns a reference to the Instance of the Queue */
   AppWorkItemPool = WORKITEMPOOL_InitPool(data, WORK_ITEM_QUEUE, NUM_OF_THREADS, 0, WORKITEMPOOL_Dispatch);

}

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This Callback handles the TCAP border Transport after initialization.
 *
 *  Input Parameters:
 *      Pointer to the ThreadPoolThread.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if transport has been initialized and 
        the event is put on the transport, failure otherwise.
 *
 *  Notes:
        The event is created and put on the border Transport 
 *
 *  See Also:
 *
 ****************************************************************************/

int
App_PostInit(ThreadPoolThread* thr)
{
   ITS_OCTET str[30] = "****OK! HELLO WORLD****";
   ITS_OCTET *byte;
   byte = str;
   ITS_Event evt;
   ITS_ThreadPoolEntry ent;
   int ret;
   int numThreads = 10;
   ITS_USHORT TransportInstance;

   ITS_Worker* worker = (ITS_Worker*) thr;

   APP_TRACE_DEBUG(("App_PostInit:: Worker name = %s, Instance = %d ",worker->GetName(),
                                                       worker->GetInstance()));
   /* Get the Border Transport Instance */
   TransportInstance = worker->GetInstance();
   
   for(int i = 0; i < numThreads; i++)
   {
      /* Set the Event to be put to the Border Transport */
      evt.SetLength(30);
      evt.SetData(byte, 30);

      /* Put Event on the Border Transport */
      ret = its::Transport::PutEvent(TransportInstance, evt);
   }

   if (ret != ITS_SUCCESS)
   {
        printf("\nError in App_PostInit");
   }

   return(ITS_SUCCESS);
}

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This Callback handles the border Transport before it gets the event.
 *
 *  Input Parameters:
 *      Pointer to ThreadPoolThread.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 *
 ****************************************************************************/

int
App_PreNext(ThreadPoolThread* thr)
{
    ITS_Worker* worker = (ITS_Worker*) thr;

    APP_TRACE_DEBUG(("\nApp_PreNext called for inst %d\n", worker->GetInstance()));

    return(ITS_SUCCESS);
}


/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This Callback handles the border Transport if it fails to get
 *      the event.
 *
 *  Input Parameters:
 *      thr - Pointer to ThreadPoolThread
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Boolean - true.
 *
 ****************************************************************************/

ITS_BOOLEAN
App_NextEventFailed(ThreadPoolThread* thr, int ret)
{

    ITS_Worker* worker = (ITS_Worker*) thr;

    APP_TRACE_DEBUG(( "App_NextEventFailed  "));
                     

    APP_TRACE_DEBUG(("Transport Failure on %d, Return Code = %d\n",
                         worker->GetInstance(), ret));

    if ( ret != ITS_SUCCESS )
    {
       /* Terminate the loop */
 
       if (ret == ITS_ERCVFAIL)
       {
         APP_TRACE_DEBUG(("ITS_ERCVFAIL on %d\n", worker->GetInstance()));
       }
    }
    else
    {
       return ITS_FALSE;
    }
    return ITS_TRUE;
}

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This Callback handles the border Transport after it gets the event.
 *      After the Event is received from the Border Transport, it places the 
 *      event on the WorkItem queue.
 *
 *  Input Parameters:
 *      Reference to the received event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      In case of success, ITS_SUCCESS. Any other return value indicates
 *      failure.
 *
 ****************************************************************************/

int
App_PostNextEvent(ThreadPoolThread* thr,Event *event)
{
   int ret;
   ITS_EVENT& evt = event->GetEvent();
   ITS_EVENT * evstr = new ITS_EVENT;
   memcpy( evstr, &evt, sizeof(ITS_EVENT));
   
   APP_TRACE_DEBUG(("\n App_PostNextEvent called"));
      
   /* Create a WorkItem and return a pointer to the  WorkItem created */   
   item = WORKITEM_Create( SIZE_OF_WORKITEM, false, App_func);
   
   /* Pass the Event to the object pointed to by the WorkItem */
   item->object = evstr;

   /* Place the WorkItem on the WorkItemPool Queue */
   WORKITEM_PutWorkItem( TRANSPORT_INSTANCE(WORKITEMPOOL_QUEUE(AppWorkItemPool)), item);

   return ret;
}

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This Callback does the cleanup before the Sample Application stops.
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
 ****************************************************************************/

int
App_PostFunc()
{
    APP_TRACE_DEBUG(("In Post Func"));

    return ITS_SUCCESS;
}

/* End of extern C */
}

