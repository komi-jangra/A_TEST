/***************************************************************************
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
 * CONTRACT: INTERNAL
 *                                                                          *
 * ID: $Id: TRACE_Test.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:56  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:14  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:05  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.2  2004/08/10 13:00:31  ssingh
 * LOG: Some more changes over initial commit.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/08/10 07:52:04  ssingh
 * LOG: Initial commits for CTF Event Trace Client (base-code).
 * LOG:
 ****************************************************************************/
#include <stdio.h>

#include <its.h>
#include <engine.h>
#include <its_app.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_thread_pool.h>
#include <its_worker.h>

#define EVENT_TRACE_SERVER_SRC 0xFFE9
#define ISUP_SRC_APP_ANSI      0x04

ITS_SHORT thrInstance = 0;

static int HandleRcvdEvent(ITS_EVENT *event);
static SS7_Family Event_GetProtocol(ITS_USHORT *offset, ITS_EVENT *event);
static ITS_USHORT Event_GetDestination(ITS_USHORT *offset, ITS_EVENT *event);
static ITS_USHORT Event_GetSource(ITS_USHORT *offset, ITS_EVENT *event);
static ITS_OCTET* Event_GetData(ITS_USHORT *offset, 
                                ITS_EVENT *event, 
                                ITS_USHORT *len);

static void
WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;
    printf("Instance Number of Worker is ... %d\n",workerInstance);
    while (1)
    {
        event.data = 0;
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }

        if ( event.src == EVENT_TRACE_SERVER_SRC )
        {
            printf("Client Worker Thread, msg receive success\n");
        }
    }
}

void EventClientPreFunc(void)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread = NULL;

    if((ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        thrInstance= ITS_INVALID_SRC;
    }

    printf("EventClientPreFunc: Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));
    if (ret != ITS_SUCCESS)
    {
        thrInstance = ITS_INVALID_SRC;
        printf("---- TRACE EVENT Client application dispatch failed \n");
    }
    else
    {
        thrInstance = ( ((WORKER_Control*)thread)->worker.instance );
        printf("---- TRACE EVENT Client application dispatched\n");
    }
}

int
EventTracePostInit(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    thrInstance = ( ((WORKER_Control*)thr)->worker.instance );

    printf("Event Trace client instance is %d\n", thrInstance);

    return ITS_SUCCESS;
}
    
int
EventTracePreNext(TPOOL_THREAD *thr)
{
    WORKER_Control* worker = (WORKER_Control *)thr;

    printf("EventTracePreNext called for inst %d\n", worker->worker.instance);

    return (ITS_SUCCESS);
}

ITS_BOOLEAN
EventTraceNextEventFailed(TPOOL_THREAD *thr, int ret)
{
    WORKER_Control* worker = (WORKER_Control *)thr;

    printf("Transport Failure on %d, Return Code = %d\n",
                         worker->worker.instance, ret);

    if ( ret != ITS_SUCCESS )
    {
       if (ret == ITS_ERCVFAIL)
       {
          printf("ITS_ERCVFAIL on %d\n", worker->worker.instance);
       }
    }
    else
    {
       return ITS_FALSE;
    }
    return ITS_TRUE;
}

int
EventTracePostNext(TPOOL_THREAD *thr, ITS_EVENT *event)
{
    ITS_UINT ret = ITS_SUCCESS;

    printf("Received event source/len = 0x%x/%d\n", event->src, event->len);

#if 0
    int i=0;
    for (i=0; i<event->len; i++)
    {
        printf("0x%x ", event->data[i]);
    }

    printf("\n");
#endif

    HandleRcvdEvent(event);

    ITS_EVENT_TERM(event);
    return ret;
}
    
int
RouteApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    return  thrInstance;
}

static int
HandleRcvdEvent(ITS_EVENT *event)
{
    int i=0;
    int ret = 0;
    ITS_USHORT sourceStack, destStack;
    SS7_Family protocol;
    ITS_OCTET *data;
    ITS_USHORT offset=0;
    ITS_USHORT len=0;
    FILE *output;

    output = fopen("/tmp/event_data", "a");
    if (output == NULL) 
    {
        printf("Unable to open file to write in it\n");
        return ret;
    }     

    switch (event->src)
    {
    case EVENT_TRACE_SERVER_SRC:
         printf("Event Received from Event Trace Server\n\n");

         sourceStack = Event_GetSource(&offset, event);
         destStack   = Event_GetDestination(&offset, event);
         protocol    = Event_GetProtocol(&offset, event);
         data        = Event_GetData(&offset, event, &len);

         switch (sourceStack)
         {
         case ITS_ISUP_ANSI_SRC:
         case ITS_ISUP_CCITT_SRC:

              if (protocol == FAMILY_ANSI)
              {
                 fprintf(output, "source : ANSI ISUP\n");
              }
              else
              {
                 fprintf(output, "source : ANSI ISUP\n");
              }
              break;

         case ITS_MTP3_CCITT_SRC:
         case ITS_MTP3_ANSI_SRC:
              if (protocol == FAMILY_ANSI)
              {
                 fprintf(output, "source : ANSI MTP3\n");
              }
              else
              {
                 fprintf(output, "source : ANSI MTP3\n");
              }
              break;

         case ISUP_SRC_APP_ANSI:
         default:
              if (protocol == FAMILY_ANSI)
              {
                 fprintf(output, "source : ANSI APP\n");
              }
              else
              {
                 fprintf(output, "source : ANSI APP\n");
              }
              break;
         }

         switch (destStack)
         {
         case ITS_ISUP_ANSI_SRC:
         case ITS_ISUP_CCITT_SRC:

              if (protocol == FAMILY_ANSI)
              {
                 fprintf(output, "dest : ANSI ISUP\n");
              }
              else
              {
                 fprintf(output, "dest : ANSI ISUP\n");
              }
              break;

         case ITS_MTP3_CCITT_SRC:
         case ITS_MTP3_ANSI_SRC:
              if (protocol == FAMILY_ANSI)
              {
                 fprintf(output, "dest : ANSI MTP3\n");
              }
              else
              {
                 fprintf(output, "dest : ANSI MTP3\n");
              }
              break;

         case ISUP_SRC_APP_ANSI:
         default:
              if (protocol == FAMILY_ANSI)
              {
                 fprintf(output, "dest : ANSI APP\n");
              }
              else
              {
                 fprintf(output, "dest : ANSI APP\n");
              }
              break;
         }

         fprintf(output, "Event Dump :");
         for (i=0; i<len; i++)
         {
             if(i%15 == 0) fprintf(output,"\n");
             fprintf(output, "0x%x ", data[i]);
         }
     
         fprintf(output, "\n\n");

         break;

    default:
         break;

    }
    fclose(output);
    return ret;
}

static ITS_USHORT 
Event_GetSource(ITS_USHORT *offset, ITS_EVENT *event)
{
    ITS_USHORT src=0;

    memcpy(&src, &event->data[*offset], sizeof(ITS_USHORT));

    *offset +=sizeof(ITS_USHORT);

    return src;
}

static ITS_USHORT
Event_GetDestination(ITS_USHORT *offset, ITS_EVENT *event)
{
    ITS_USHORT dest=0;

    memcpy(&dest, &event->data[*offset], sizeof(ITS_USHORT));

    *offset +=sizeof(ITS_USHORT);

    return dest;
}

static SS7_Family
Event_GetProtocol(ITS_USHORT *offset, ITS_EVENT *event)
{
    SS7_Family prot;

    memcpy(&prot, &event->data[*offset], sizeof(ITS_INT));

    *offset +=sizeof(ITS_INT);

    return prot;
}

static ITS_OCTET*
Event_GetData(ITS_USHORT *offset, ITS_EVENT *event, ITS_USHORT *len)
{
    ITS_EVENT evt;

    *len = event->len - 2*sizeof(ITS_USHORT) - sizeof(ITS_INT);

    ITS_EVENT_INIT(&evt, 0, *len);

    memcpy(evt.data, &event->data[*offset], *len);

    return evt.data;
}
