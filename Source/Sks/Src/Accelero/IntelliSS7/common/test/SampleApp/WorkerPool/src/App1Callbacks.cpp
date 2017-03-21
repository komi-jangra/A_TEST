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
 *  ID: $Id: App1Callbacks.cpp,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:34  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:27  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:53  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.1  2005/01/31 11:15:28  kannanp
 * LOG: Sample App - Initial.
 * LOG:
****************************************************************************/
#ident "$Id: App1Callbacks.cpp,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $"

#include <its++.h>
#include <engine++.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#include <stdio.h>
#include <app_trace.h>

#include <its_worker.h>
#include <its_transports.h>

ITS_INT TransportInstance;

/***********************************************************************
 *  Implementation for worker pool call backs.
 *  
 ***********************************************************************/

extern "C"
{

void App_Dispatch(ThreadPoolThread* thr, void* arg);

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This RouteApp function is responsible for routing
 *      incoming messages.
 *
 *  Input Parameters:
 *      ITS_HDR h, ITS_EVENT evt.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      transportinstance.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

ITS_USHORT
RouteApp(ITS_HDR *hdr,ITS_EVENT *evt)
{
    ITS_INT ret = 0;
    ITS_ThreadPoolEntry ent;

    APP_TRACE_DEBUG((" RouteApp"));

  /* Get the First Available Thread from WorkerPool*/
  if(workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
   {
      engine::Worker* worker = (engine::Worker *)ent.GetThread();

      if (worker == NULL)
      {
          workerPool->ReturnToAvailThreads(ent);
      }

      if(worker != NULL)
      {
         APP_TRACE_DEBUG(("********** DISPATCHED WORKER INSTANCE = %d**********", worker->GetInstance()));

         /* Dispatch the received Event to the worker*/

         ret = workerPool->its::ThreadPool::DispatchOnThread(ent, App_Dispatch, NULL);
          
         if (ret != ITS_SUCCESS)
         {
             workerPool->ReturnToAvailThreads(ent);

             ITS_THROW_ERROR(ret);
         }
      }
      ret = worker->GetInstance();
   }

   return ret;
}

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This dispatch function handles the messages received from border 
 *      transport. When a event is received on a woker thread, the event
 *      length and data are printed on the standard output. 
 *
 *  Input Parameters:
 *      thr - The thread that will be running as the Border transport
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
App_Dispatch(ThreadPoolThread* thr, void *arg)
{
   ITS_INT ret = ITS_SUCCESS;
   Event event;
   
   ITS_Worker* worker = (ITS_Worker*) thr;

   APP_TRACE_DEBUG(("App_Dispatch "));
 
   while(1)
   {
     /* Get the Event Dispatched on the worker*/

      ret = worker->GetNextEvent(event);
  
     if (ret != ITS_SUCCESS)
     { 
         printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
     }
     else
     {
         /* Print the Received Event Length and Data on the stdout */

         printf ("\nBorder : Event length %d\n", event.GetLength());
         printf ("\nBorder : Event Data\n");
         printf("\n Instance : %d",worker->GetInstance());

         for(int i = 0; i <= event.GetLength(); i++)
         {
             printf("%c ", event.GetData()[i]);
         }
         printf("\n");
      }

     fflush(stdout);
   }
}

/*.implementation:extern
****************************************************************************
 *  Purpose:
 *      This Callback initializes the Sample Application.
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
 *      In case of any error returned from the above procedures, the errorCode
 *      is set to indicate the same. The application can then take suitable
 *      action.
 *
 ****************************************************************************/

void ENGINE_PreFunc(void)
{
   APP_TRACE_DEBUG((" ENGINE_PreFunc"));

   /* Set the application selector */
   ROUTE_SetApplicationSelector(RouteApp);
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

   ITS_Worker* worker = (ITS_Worker*) thr;

   APP_TRACE_DEBUG(("App_PostInit called\n"));

   APP_TRACE_DEBUG(("App_PostInit::Transport Instance %d\n", worker->GetInstance()));

   APP_TRACE_DEBUG(("Worker name = %s, Instance = %d ",worker->GetName(),
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
 *
 *  Input Parameters:
 *      Pointer to ThreadPpoolThread.
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
App_PostNextEvent(ThreadPoolThread* thr, Event* event)
{
   int ret;
   ITS_HDR* hdr;

   APP_TRACE_DEBUG(("\n App_PostNextEvent called"));

   /* Call RouteApp to route the received Event */
   ITS_USHORT trInst = RouteApp( hdr, &event->GetEvent());

   /* Transport put event on the Transport Instance returned by RouteApp */
    ret = its::Transport::PutEvent(trInst, &event->GetEvent());

   if (ret != ITS_SUCCESS)
   {
      printf("Transport PutEvent Failed in App_PostNextEven\n");
   }

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
ENGINE_PostFunc()
{
    APP_TRACE_DEBUG(("In Post Func"));

    return ITS_SUCCESS;
}

/* End of extern C */
}

