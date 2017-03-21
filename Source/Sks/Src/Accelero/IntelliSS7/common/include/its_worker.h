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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:58  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.5  2001/06/27 22:57:42  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.4  2001/05/04 14:30:52  mmiers
 * LOG: A few bug fixes from PR4.
 * LOG:
 * LOG: Revision 4.3  2001/05/03 15:30:48  mmiers
 * LOG: C++ fixes.
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:58:55  mmiers
 * LOG: Add thread pool shutdown logic.  People using the C API
 * LOG: need to convert to WORKER_GetExit() instead of TPOOL_THREAD_EXIT().
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.17  2001/04/12 15:55:15  labuser
 * LOG: Get the call args correct before calling C constructor.
 * LOG:
 * LOG: Revision 3.16  2001/04/05 19:19:19  mmiers
 * LOG: Workaround.
 * LOG:
 * LOG: Revision 3.15  2001/04/05 17:58:58  mmiers
 * LOG: Typo.
 * LOG:
 * LOG: Revision 3.14  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.13  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.12  2001/04/02 19:50:14  mmiers
 * LOG: Solaris build.
 * LOG:
 * LOG: Revision 3.11  2001/03/16 20:56:07  mmiers
 * LOG:
 * LOG: Ok, only resdb and parsing left.
 * LOG:
 * LOG: Revision 3.10  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.9  2001/03/06 23:54:44  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.8  2001/02/17 00:37:49  hxing
 * LOG: Typo in fastcall define
 * LOG:
 * LOG: Revision 3.7  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.6  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.5  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.4  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.3  2001/01/10 00:24:06  mmiers
 * LOG: Linux build.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/06/13 19:15:55  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:50  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.45  1999/10/25 18:28:10  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.44  1999/10/12 22:59:55  mmiers
 * LOG:
 * LOG:
 * LOG: Rework termination handling of dynamic sockets.  The transport
 * LOG: control needs to go away when the thread does.
 * LOG:
 * LOG: Revision 1.43  1999/09/01 01:00:33  mmiers
 * LOG:
 * LOG:
 * LOG: Fix build errors.
 * LOG:
 * LOG: Revision 1.42  1999/09/01 00:29:47  mmiers
 * LOG:
 * LOG:
 * LOG: Add std::string fetch for name.
 * LOG:
 * LOG: Revision 1.41  1999/08/18 16:36:48  mmiers
 * LOG:
 * LOG:
 * LOG: Finish comments.
 * LOG:
 * LOG: Revision 1.40  1999/08/18 14:49:47  mmiers
 * LOG:
 * LOG:
 * LOG: Update comments, test code.
 * LOG:
 * LOG: Revision 1.39  1999/07/29 01:58:19  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the first round of addressing Hubert's review comments.
 * LOG:
 * LOG: Revision 1.38  1999/07/01 01:15:46  mmiers
 * LOG:
 * LOG:
 * LOG: Continuing porting issue fixes.
 * LOG:
 * LOG: Revision 1.37  1999/06/28 22:16:49  mmiers
 * LOG:
 * LOG:
 * LOG: Give up on friend C functions.
 * LOG:
 * LOG: Revision 1.36  1999/06/28 22:10:18  mmiers
 * LOG:
 * LOG:
 * LOG: I give up on friend functions.
 * LOG:
 * LOG: Revision 1.35  1999/06/28 21:47:30  skarmakar
 * LOG:
 * LOG:
 * LOG: A fix for the namespace craziness.
 * LOG:
 * LOG: Revision 1.34  1999/06/28 21:08:58  skarmakar
 * LOG:
 * LOG:
 * LOG: Try this one out for friend "C" functions.
 * LOG:
 * LOG: Revision 1.33  1999/06/25 16:06:44  mmiers
 * LOG:
 * LOG:
 * LOG: Rework the berkeley sockets transport classes a little.  Required
 * LOG: modification to the Accept() method to create a transport correctly.
 * LOG:
 * LOG: Revision 1.32  1999/02/04 22:26:37  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.31  1998/11/18 18:11:25  mmiers
 * LOG: Update comments.
 * LOG:
 * LOG: Revision 1.30  1998/11/05 03:26:51  mmiers
 * LOG: Add serialization counters to transports.
 * LOG:
 * LOG: Revision 1.29  1998/10/28 17:16:33  mmiers
 * LOG: Add/complete C-based thread pools and workers.
 * LOG:
 * LOG: Revision 1.28  1998/09/30 14:46:20  mmiers
 * LOG: friend functions are not handled consistently.  Need to think about this.
 * LOG:
 * LOG: Revision 1.27  1998/09/30 14:36:27  mmiers
 * LOG: Try a modified version of "friend".
 * LOG:
 * LOG: Revision 1.26  1998/06/26 14:30:41  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.25  1998/06/24 16:12:30  mmiers
 * LOG: Straighten out the tranport vs. worker issues.
 * LOG:
 * LOG: Revision 1.24  1998/06/22 16:24:21  mmiers
 * LOG: More work with resource files.
 * LOG:
 * LOG: Revision 1.23  1998/06/20 04:15:18  mmiers
 * LOG: Fix up platform dependent stuff.
 * LOG:
 * LOG: Revision 1.22  1998/06/18 15:23:10  mmiers
 * LOG: Straighten out the NT build.
 * LOG:
 * LOG: Revision 1.21  1998/06/18 03:10:07  mmiers
 * LOG: Build on Solaris.  Right now, the NT build is not OK.
 * LOG:
 * LOG: Revision 1.20  1998/06/17 20:12:14  mmiers
 * LOG: More work on back-compat.
 * LOG:
 * LOG: Revision 1.19  1998/06/16 00:00:23  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.18  1998/06/02 19:43:16  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.17  1998/06/01 16:35:22  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.16  1998/06/01 13:44:37  mmiers
 * LOG: Fix compilation bugs.
 * LOG:
 * LOG: Revision 1.15  1998/05/31 23:05:18  mmiers
 * LOG: Finish off Worker.
 * LOG:
 * LOG: Revision 1.14  1998/05/31 20:28:31  mmiers
 * LOG: Add missing inlines.
 * LOG:
 * LOG: Revision 1.13  1998/05/31 20:22:22  mmiers
 * LOG: Bug fix.
 * LOG:
 * LOG: Revision 1.12  1998/05/31 20:14:58  mmiers
 * LOG: Finishing up the general documenation.
 * LOG:
 * LOG: Revision 1.11  1998/05/31 03:41:38  mmiers
 * LOG: Document the worker class.  Still need to provide something for the inline
 * LOG: functions.
 * LOG:
 * LOG: Revision 1.10  1998/05/31 03:14:45  mmiers
 * LOG: Fix compilation errors.
 * LOG:
 * LOG: Revision 1.9  1998/05/31 02:59:42  mmiers
 * LOG: More documenation, stabilizing the interfaces.
 * LOG:
 * LOG: Revision 1.8  1998/05/29 03:31:34  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.7  1998/05/28 17:28:43  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 * LOG: Revision 1.6  1998/05/26 02:08:07  mmiers
 * LOG: Basic comments.  I really shirked work this weekend.
 * LOG:
 * LOG: Revision 1.5  1998/05/19 17:11:51  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.4  1998/05/01 00:24:36  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.3  1998/04/22 19:00:11  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.2  1998/04/20 22:04:46  mmiers
 * LOG: Integrate in the worker code.  Trying to maintain backwards
 * LOG: compatibility with existing vendor code.
 * LOG:
 * LOG: Revision 1.1  1998/04/19 02:42:48  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_WORKER_H
#define ITS_WORKER_H

#include <its.h>
#include <its_object.h>
#include <its_thread_pool.h>
#include <its_transports.h>

#ident "$Id: its_worker.h,v 1.1.1.1 2007-10-08 11:11:33 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:WORKER_
 *****************************************************************************
 *  Interface:
 *      WORKER_*
 *
 *  Purpose:
 *      The WORKER_Control object represents the marriage of IntelliSS7 with
 *      multithreading technology.  This object combines the features
 *      of TRANSPORT_Control with TPOOL to create an object suitable for
 *      processing ITS_EVENT(s) in a multithreaded environment.  For information
 *      on the transport and thread objects,
 *      see:
 *      <A HREF=its_thread.html>ITS_THREAD,</A>
 *      <A HREF=its_threadpool.html>TPOOL_Manager,</A> and
 *      <A HREF=its_transport.html>TRANSPORT_Control</A>.
 *
 *      The worker object allows the application programmer to create
 *      pools of threads with transports associated with them.  The
 *      threads can be persistent "border" transports (i.e., that
 *      use interprocess transports), or application transports (where
 *      the thread and transports are persistent, but the work unit is
 *      not).
 *
 *
 *  Usage:
 *      Further documenation for this class is best left to a samle program.
 *      This program shows the basic outline of an HLR; we start with the
 *      standard include section:
 *
 *      #include <assert.h>
 *      #include <stdio.h>
 *      #include <stdlib.h>
 *      #include <string.h>
 *      #include <time.h>
 *
 *      #if defined(unix)
 *      #include <unistd.h>
 *      #include <signal.h>
 *      #endif
 *
 *      #include <its.h>
 *      #include <its_app.h>
 *      #include <its_timers.h>
 *      #include <its_route.h>
 *      #include <its_transports.h>
 *      #include <its_worker.h>
 *      #include <its_service.h>
 *
 *      #include <ansi/tcap.h>
 *      #include <ansi/sccp.h>
 *
 *      static TPOOL borderPool;
 *      static TPOOL actorPool;
 *
 *      #define FIRST_BORDER    1
 *      #define NUM_BORDER      3
 *      #define FIRST_ACTOR     (FIRST_BORDER + NUM_BORDER)
 *      #define NUM_ACTOR       10
 *
 *       *
 *       * create the transaction unit-of-work threads
 *       * 
 *      static TPOOL_THREAD *
 *      CreateActorTransports(TPOOL *pool, int stackSize)
 *      {
 *          WORKER_Control* actor;
 *          int thisActor = FIRST_ACTOR;
 *
 *          actor = WORKER_InitWorker(stackSize, "An actor",
 *                                    (ITS_USHORT)thisActor,
 *                                    ITS_SCCP|ITS_TCAP|ITS_TRANSPORT_TQUEUE);
 *
 *          thisActor++;
 *
 *          return (&WORKER_THREAD(actor));
 *      }
 *
 *       *
 *       * create the IPC transports
 *       * 
 *      static TPOOL_THREAD *
 *      CreateBorderTransports(TPOOL *pool, int stackSize)
 *      {
 *          WORKER_Control* border;
 *          static int thisBorder = FIRST_ACTOR;
 *
 *          switch (thisBorder)
 *          {
 *          case 1:
 *              border = WORKER_InitWorker(stackSize,
 *                                         "First Border", (ITS_USHORT)thisBorder,
 *                                         ITS_SCCP|ITS_TCAP|ITS_TRANSPORT_DELAY_CREATE|
 *                                             ITS_TRANSPORT_CSOCKET);
 *              break;
 *
 *          case 2:
 *              border = WORKER_InitWorker(stackSize,
 *                                         "Second Border", (ITS_USHORT)thisBorder,
 *                                         ITS_SCCP|ITS_TCAP|ITS_TRANSPORT_DELAY_CREATE|
 *                                             ITS_TRANSPORT_SSOCKET);
 *          default:
 *              printf("Error: Too many border transports.\n");
 *              exit(0);
 *          }
 *
 *          thisBorder++;
 *
 *          return (&WORKER_THREAD(border));
 *      }
 *
 *       *
 *       * handle a TCAP transaction
 *       *
 *       * The application selector dispatches each new incoming TCAP
 *       * transaction to a thread that runs this function.  This function
 *       * should not exit until the transaction has been completely
 *       * finished (ended).
 *       * 
 *      void
 *      ActorDispatch(TPOOL_THREAD *thr, void *arg)
 *      {
 *          WORKER_Control* work = (WORKER_Control *)thr;
 *          ITS_HANDLE h;
 *          ITS_EVENT event;
 *
 *           * getting NULL here is a fatal error *
 *          h = ITS_Initialize(work->mask,
 *                             work->instance);
 *          assert(h != NULL);
 *   
 *           * dispatcher loop.  Take all incoming messages and send them to SCCP. * 
 *          while (!WORKER_THREAD(work).exit)
 *          {
 *               * Note: we could use ITS_GetNextEvent() here. * 
 *              if (WORKER_GetNextEvent(work, &event) != ITS_SUCCESS)
 *              {
 *                  continue;
 *              }
 *
 *              switch (event.src)
 *              {
 *              case ITS_TCAP_SRC:
 *                  break;
 *
 *              default:
 *                  break;
 *              }
 *          }
 *  
 *           * this is good practice *
 *          ITS_Terminate(h);
 *      }
 *
 *       *
 *       * transmit incoming IPC events to SCCP for processing
 *       * 
 *      void
 *      BorderDispatch(TPOOL_THREAD *thr, void *arg)
 *      {
 *          WORKER_Control* work = (WORKER_Control *)thr;
 *          ITS_HANDLE h;
 *          ITS_EVENT event;
 *
 *           * getting NULL here is a fatal error * 
 *           * Don't do this!!
 *           * assert((h = ITS_Initialize(work->mask,
 *           *                            work->instance)) != NULL);
 *           * if you disable debug builds, the init function will never
 *           * terminate.
 *           * use this instead.
 *          h = ITS_Initialize(work->mask,
 *                             work->instance)) != NULL);
 *          assert(h != NULL);
 *
 *           * dispatcher loop.  Take all incoming messages and send them to SCCP. * 
 *          while (!WORKER_THREAD(work).exit)
 *          {
 *               * Note: we could use ITS_GetNextEvent() here. *
 *              if (WORKER_GetNextEvent(work, &event) != ITS_SUCCESS)
 *              {
 *                  continue;
 *              }
 *
 *              event.src = ITS_MTP3_SRC;
 *
 *              if (TRANSPORT_PutEvent(ITS_SCCP_SRC, &event) != ITS_SUCCESS)
 *              {
 *                  printf("Couldn't send message to SCCP\n");
 *              }
 *          }
 *  
 *           * this is good practice * 
 *          ITS_Terminate(h);
 *      }
 *
 *       ****************************************************************************
 *       *  Purpose:
 *       *      Routes the TCAP message to the application based on the dialog id
 *       *      This functions as the "application selector" as documented by
 *       *      ROUTE_*
 *       *
 *       *  Input Parameters:
 *       *      hdr - the per-thread application context (dialogue_id).
 *       *
 *       *  Input/Output Parameters:
 *       *      None.
 *       *
 *       *  Output Parameters:
 *       *      None.
 *       *
 *       *  Return Value:
 *       *      returns the instance id of the first available dispatch thread
 *       *
 *       *  Notes:
 *       * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *       *
 *       *   DO NOT THROW EXCEPTIONS FROM THIS CALL.  THE CALLER IS A "C" FUNCTION
 *       *   THAT HAS A LOCKED MUTEX.  AN UNCAUGHT EXCEPTION ORIGINATING FROM THIS
 *       *   FUNCTION MEANS THE MUTEX WILL STAY LOCKED, EFFECTIVELY BLOCKING ANY NEW
 *       *   TCAP TRANSACTION OR SCCP CONNECTION FROM THE PROGRAM.  YOU HAVE BEEN
 *       *   WARNED.
 *       *
 *       * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING 
 *       *
 *       *  See Also:
 *       **************************************************************************** 
 *      ITS_USHORT
 *      SelectApplication(ITS_HDR *hdr, ITS_EVENT* event)
 *      {
 *          TPOOL_THREAD* thread;
 *          int did = hdr->context.dialogue_id;
 *          WORKER_Control* actor;
 *          int ret;
 *
 *          ret = TPOOL_GetFirstAvailThread(&actorPool, &thread);
 *          assert(ret == ITS_SUCCESS);
 *
 *          actor = (WORKER_Control *)thread;
 *
 *          ROUTE_AddApplication(actor->instance, hdr);
 *      
 *           * Invoke the Function for the thread * 
 *          ret = TPOOL_DispatchOnThread(thread,
 *                                       ActorDispatch,
 *                                       NULL);
 *          assert(ret == ITS_SUCCESS); 
 *      
 *          return (actor->instance);
 *      }
 *
 *       *
 *       * Initialization function.  Build the thread pools
 *       * 
 *      void
 *      InitFunc(int argc, const char **argv)
 *      {
 *          APPL_SetName("HLR");
 *
 *           * needed by multithreaded programs * 
 *          if (ITS_GlobalStart(ITS_SCCP|ITS_TCAP) != ITS_SUCCESS)
 *          {
 *              printf("Fatal error starting stack.\n");
 *
 *              abort();
 *          }
 *  
 *           * set the application selector for TCAP * 
 *          if (ROUTE_SetApplicationSelector(SelectApplication) != NULL)
 *          {
 *              printf("Fatal error setting app selector.\n");
 *
 *              abort();
 *          }
 *
 *           * create this first, so that any incoming transaction that
 *           * comes in quickly after startup has a handler * 
 *          if (TPOOL_InitPool(&actorPool) != ITS_SUCCESS)
 *          {
 *              printf("Fatal error creating unit-of-work transports pool.\n");
 *
 *              ITS_GlobalStop();
 *
 *              abort();
 *          }
 *
 *          if (TPOOL_CreatePool(&actorPool, NUM_ACTOR, 0,  * 0 says use OS default * 
 *                               CreateActorTransports) != ITS_SUCCESS)
 *          {
 *              printf("Fatal error creating unit-of-work transports pool.\n");
 *
 *              abort();
 *          }
 *
 *           * create this second * 
 *          if (TPOOL_InitPool(&borderPool) != ITS_SUCCESS)
 *          {
 *              printf("Fatal error creating IPC transports pool.\n");
 *
 *              TPOOL_DestroyPool(&actorPool);
 *
 *              ITS_GlobalStop();
 *
 *              abort();
 *          }
 *
 *          if (TPOOL_CreatePool(&borderPool, NUM_BORDER, 0,  * 0 says use OS default * 
 *                               CreateBorderTransports) != ITS_SUCCESS)
 *          {
 *              printf("Fatal error creating unit-of-work transports pool.\n");
 *
 *              TPOOL_DestroyPool(&actorPool);
 *              TPOOL_DestroyPool(&borderPool);
 *
 *              ITS_GlobalStop();
 *
 *              abort();
 *          }
 *      }
 *
 *       *
 *       * Main function.  Not much to do other than sleep.  The
 *       * "main" thread executes this until a stop signal is
 *       * received.
 *       * 
 *      void
 *      MainFunc(void)
 *      {
 *          TIMERS_Sleep(5);
 *      }
 *
 *       *
 *       * termination handler
 *       *
 *      void
 *      TermFunc(void)
 *      {
 *           * Kill your exterior comm points FIRST * 
 *          TPOOL_DestroyPool(&borderPool);
 *          TPOOL_DestroyPool(&actorPool);
 *      }
 *
 *      int
 *      main(int argc, char **argv)
 *      {
 *          int ret;
 *
 *          ret = SERVICE_Initialize("HLR", "HLR_Service");
 *
 *          assert(ret == ITS_SUCCESS);
 *
 *          SERVICE_SetInitFunction(InitFunc);
 *          SERVICE_SetMainFunction(MainFunc);
 *          SERVICE_SetTermFunction(TermFunc);
 *
 *          SERVICE_ProcessCommandLine(argc, argv);
 *
 *          if (SERVICE_GetType() == ST_SERVICE)
 *          {
 *              SERVICE_RunAsService();
 *          }
 *          else if (SERVICE_GetType() == ST_CONSOLE_APPLICATION)
 *          {
 *              SERVICE_RunAsConsoleApplication(argc, argv);
 *          }
 *
 *          SERVICE_Terminate();
 *
 *          return (SERVICE_GetExitCode());
 *      }
 *
 *****************************************************************************/

/*
 * instance part
 */
typedef struct
{
    TRANSPORT_Control*  transport;
    char*               name;
    ITS_USHORT          instance;
    ITS_UINT            mask;
    void*               back;
}
WORKER_ObjectPart;

/*
 * instance record.  This needs to be rethought.  We should use
 * ITS_Object for ITS_THREAD and TPOOL_THREAD.
 */
typedef struct
{
    ITS_CoreObjectPart      core;
    ITS_ThreadPart          thread;
    TPOOL_ThreadObjectPart  tpool;
    WORKER_ObjectPart       worker;
}
WORKER_Control;

#define WORKER_THREAD(x) \
    (((WORKER_Control *)(x))->tpool)

#define WORKER_TRANSPORT(x) \
    (((WORKER_Control *)(x))->worker.transport)

#define WORKER_NAME(x) \
    (((WORKER_Control *)(x))->worker.name)

#define WORKER_INSTANCE(x) \
    (((WORKER_Control *)(x))->worker.instance)

#define WORKER_MASK(x) \
    (((WORKER_Control *)(x))->worker.mask)

#define WORKER_BACK_PTR(x) \
    (((WORKER_Control *)(x))->worker.back)
/*
 * class part
 */
typedef int (*WORKER_TransportCreateProc)(WORKER_Control *);
typedef void (*WORKER_TransportDeleteProc)(WORKER_Control *);
typedef int (*WORKER_EventProc)(WORKER_Control *, ITS_EVENT *);

typedef struct
{
    WORKER_TransportCreateProc  createTransport;
    WORKER_TransportDeleteProc  deleteTransport;
    WORKER_EventProc            getNextEvent;
    WORKER_EventProc            peekNextEvent;
    WORKER_EventProc            putEvent;
}
WORKER_ClassPart;

/*
 * class record
 */
typedef struct
{
    ITS_CoreClassPart       coreClass;
    WORKER_ClassPart        workerClass;
}
WORKER_ClassRec, *WORKER_Class;

#define WORKER_CLASS_CREATE_TRANSPORT(x) \
    (((WORKER_Class)(x))->workerClass.createTransport)

#define WORKER_CLASS_DELETE_TRANSPORT(x) \
    (((WORKER_Class)(x))->workerClass.deleteTransport)

#define WORKER_CLASS_GET_NEXT_EVENT(x) \
    (((WORKER_Class)(x))->workerClass.getNextEvent)

#define WORKER_CLASS_PEEK_NEXT_EVENT(x) \
    (((WORKER_Class)(x))->workerClass.peekNextEvent)

#define WORKER_CLASS_PUT_EVENT(x) \
    (((WORKER_Class)(x))->workerClass.putEvent)

#define WORKER_CLASS_NAME   "WORKER Class"

ITSDLLAPI extern WORKER_ClassRec  itsWORKER_ClassRec;
ITSDLLAPI extern ITS_Class        itsWORKER_Class;

/*
 * The API
 */
#if !defined(ITS_FASTCALL)

ITSDLLAPI WORKER_Control* WORKER_InitWorker(int stackSize, const char *name,
                                            ITS_USHORT instance, ITS_UINT mask);
ITSDLLAPI void            WORKER_DeleteWorker(WORKER_Control* worker);

ITSDLLAPI int  WORKER_CreateTransport(WORKER_Control *worker);
ITSDLLAPI void WORKER_DeleteTransport(WORKER_Control *worker);

ITSDLLAPI int WORKER_GetNextEvent(WORKER_Control* worker, ITS_EVENT* ev);
ITSDLLAPI int WORKER_PeekNextEvent(WORKER_Control* worker, ITS_EVENT* ev);
ITSDLLAPI int WORKER_PutEvent(WORKER_Control* worker, ITS_EVENT* ev);

#else /* ITS_FASTCALL */

#define WORKER_InitWorker(s,n,m,i)                          \
    (WORKER_Control *)ITS_ConstructObject(itsWORKER_Class,  \
                                       (s), (n), (m), (i))

#define WORKER_DeleteWorker(w)                              \
    ITS_DestructObject((ITS_Object)w)

#define WORKER_CreateTransport(w)                           \
    WORKER_CLASS_CREATE_TRANSPORT(ITS_OBJ_CLASS(w))(w)

#define WORKER_DeleteTransport(w)                           \
    WORKER_CLASS_DELETE_TRANSPORT(ITS_OBJ_CLASS(w))(w)

#define WORKER_GetNextEvent(w,e)                            \
    WORKER_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(w))(w, e)

#define WORKER_PeekNextEvent(w,e)                           \
    WORKER_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(w))(w, e)

#define WORKER_PutEvent(w,e)                                \
    WORKER_CLASS_PUT_EVENT(ITS_OBJ_CLASS(w))(w, e)

#endif /* ITS_FASTCALL */

/*
 * outside fastcall
 */
ITSDLLAPI ITS_BOOLEAN   WORKER_GetExit(WORKER_Control *work);
ITSDLLAPI void          WORKER_SetExit(WORKER_Control *work,
                                       ITS_BOOLEAN which);
/*
 * this one is special
 */
ITSDLLAPI WORKER_Control* WORKER_FindWorker(ITS_USHORT instance);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <its_thread_pool.h>
#include <its_transports.h>

#include <string>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Worker
 *****************************************************************************
 *  Interface:
 *      Worker
 *
 *  Purpose:
 *      The Worker class represents the marriage of IntelliSS7 with
 *      multithreading technology.  This class combines the features
 *      of Transport with ITS_Thread to create a class suitable for
 *      processing Event(s) (or ITS_EVENT(s)) in a multithreaded
 *      environment.  For information on the transport and thread classes,
 *      see:
 *      <A HREF=its_thread.html>ITS_Thread,</A>
 *      <A HREF=its_threadpool.html>ThreadPool,</A> and
 *      <A HREF=its_transport.html>ITS_Transports</A>.
 *
 *      The worker class allows the application programmer to create
 *      pools of threads with transports associated with them.  The
 *      threads can be persistent "border" transports (i.e., that
 *      use interprocess transports), or application transports (where
 *      the thread and transports are persistent, but the work unit is
 *      not).
 *
 *      There is not much more to the Worker class that has not been
 *      documented extensively elsewhere, with one exception: delayed
 *      creation of the tranport associated with a worker.  Certain classes
 *      of transports have constructors that will block indefinitely due
 *      to the nature of the transport medium; among these are the
 *      ITS_TCPServerSocket and the ITS_FifoTransport (on some architectures).
 *      When using transports of these classes with a worker, the user will
 *      probably want to create the Worker objects associated with these
 *      transports with the ITS_TRANSPORT_DELAY_CREATE flag set in the
 *      mask.  That flag is an indication to the Worker constructor that
 *      the transport should NOT be created by the constructor, but instead
 *      delayed until such time as the user calls ITS_Initialize() within
 *      the worker's work function.  This has the effect of distributing
 *      the blocking over several threads, which allows the process to connect
 *      to all of its peers in parallel rather than in serial.  This also
 *      has the effect of allowing processing to start before all interprocess
 *      transports have been created; this is an essential feature when
 *      degraded processing is desirable even when all communication paths
 *      to external entities have not been established.
 *
 *  Usage:
 *      Further documenation for this class is best left to a samle program.
 *      This program shows the basic outline of an HLR; we start with the
 *      standard include section:
 *      ---------------------------------------------------------------------
 *      #include <stdio.h>
 *      #include <stdlib.h>
 *      #include <string.h>
 *      #include <time.h>
 *
 *      #if defined(unix)
 *      #include <unistd.h>
 *      #include <signal.h>
 *      #endif
 *
 *      #include <exception>
 *      #include <iostream.h>
 *
 *      #include <its++.h>
 *      #include <its_timers.h>
 *      #include <its_route.h>
 *      #include <its_transports.h>
 *      #include <its_worker.h>
 *      #include <its_exception.h>
 *      #include <its_timers.h>
 *
 *      #include <sccp++.h>
 *      #include <tcap++.h>
 *      #include <ansi/IS41.h>
 *
 *      -------------------------------------------------------------------
 *
 *      This next little sniglet is necessary when using C++.
 *
 *      -------------------------------------------------------------------
 *      #if defined(ITS_NAMESPACE)
 *      using namespace its;
 *      #endif
 *
 *      -------------------------------------------------------------------
 *
 *      Now we start thinking about transports.  We allocate the first
 *      three valid transports to persistent "border" transports/workers,
 *      and the next 100 to transaction handlers.
 *
 *      -------------------------------------------------------------------
 *      //
 *      // these values represent the instance ids of the border transports
 *      //
 *      #define GATE_DISPATCHER     1
 *      #define VLR_DISPATCHER      2
 *      #define MSC_DISPATCHER      3
 *      #define MAX_DISPATCHERS     3
 *
 *      #define FIRST_INVOKE_THREAD 4
 *
 *      -------------------------------------------------------------------
 *
 *      Ok, now we need to subclass from ThreadPool to create the
 *      "dispatcher" threads.  These represent threads whose transports
 *      are inter-process.
 *
 *      -------------------------------------------------------------------
 *      //.interface:
 *      //////////////////////////////////////////////////////////////////////////////
 *      //  Name:
 *      //      HLR_Invoke pool
 *      //
 *      //  Purpose:
 *      //      A class to create dispatcher threads
 *      //
 *      //  Usage:
 *      //      INLINE
 *      //////////////////////////////////////////////////////////////////////////////
 *      class HLR_DispatcherPool : public ThreadPool
 *      {
 *      public:
 *          HLR_DispatcherPool()
 *              : ThreadPool(), count(GATE_DISPATCHER)
 *          {
 *          }
 *
 *      -------------------------------------------------------------------
 *
 *      Note the override of the default thread pool creation method.
 *
 *      -------------------------------------------------------------------
 *          virtual ITS_ThreadPoolThread* CreatePoolThread(int stackSize)
 *          {
 *              Worker* work;
 *
 *      -------------------------------------------------------------------
 *
 *      Note also that we can mix transport types within a thread pool.
 *
 *      -------------------------------------------------------------------
 *              //
 *              // recall that "instance" is the third constructor arg.
 *              // When used, this identifies the "transport id" for each
 *              // thread.
 *              // 
 *              switch (count)
 *              {
 *              case GATE_DISPATCHER:
 *                  // creating the Gateway dispatcher?   
 *                  work = new Worker(stackSize, "Gateway Dispatch",
 *                                        count,
 *                                        ITS_SCCP|ITS_TRANSPORT_CSOCKET|
 *                                          ITS_TRANSPORT_DELAY_CREATE);
 *                  break;
 *
 *              case VLR_DISPATCHER:
 *                  // creating the VLR dispatcher?   
 *                  work = new Worker(stackSize, "VLR Dispatch",
 *                                        count,
 *                                        ITS_SCCP|ITS_TRANSPORT_FIFO|
 *                                          ITS_TRANSPORT_DELAY_CREATE);
 *                  break;
 *
 *              case MSC_DISPATCHER:
 *                  // creating the MSC dispatcher?   
 *                  work = new Worker(stackSize, "MSC Dispatch",
 *                                        count,
 *                                        ITS_SCCP|ITS_TRANSPORT_FIFO|
 *                                          ITS_TRANSPORT_DELAY_CREATE);
 *                  break;
 *
 *              default:
 *                  exception ex;
 *
 *                  throw ex;
 *              }
 *      
 *              count++;
 *      
 *              return (ITS_ThreadPoolThread *)work;
 *          }
 *
 *          // the work function for this pool
 *          static void Dispatcher(ITS_ThreadPoolThread *thr, void *arg);
 *
 *      private:
 *          ITS_USHORT count;
 *      };
 *
 *      -------------------------------------------------------------------
 *
 *      This method handles all external event sources.  For an HLR, all
 *      events are SCCP events, so we can just send them to SCCP, if they
 *      are formatted correctly.
 *
 *      -------------------------------------------------------------------
 *
 *      //.implementation:extern
 *      //////////////////////////////////////////////////////////////////////////////
 *      //  Purpose:
 *      //      Dispatch all indications to SCCP (our border transports function
 *      //      as MTP3).
 *      //
 *      //  Input Parameters:
 *      //      thr - a pointer to an Worker thread
 *      //      arg - the argument to this function execution session
 *      //
 *      //  Input/Output Parameters:
 *      //      None.
 *      //
 *      //  Output Parameters:
 *      //      None.
 *      //
 *      //  Return Value:
 *      //      None.
 *      //
 *      //  Notes:
 *      //
 *      //  See Also:
 *      //////////////////////////////////////////////////////////////////////////////
 *      void
 *      HLR_DispatcherPool::Dispatcher(ITS_ThreadPoolThread *thr, void *arg)
 *      {
 *          Worker* work = (Worker *)thr;
 *          ITS_HANDLE h;
 *          Event event;
 *
 *          // getting NULL here is a fatal error
 *          h = ITS_Initialize(work->GetMask(),
 *                             work->GetInstance());
 *
 *          ITS_THROW_ASSERT(h != NULL);
 *  
 *          // dispatcher loop.  Take all incoming messages and send them to TCAP.
 *          while (!work->GetExit())
 *          {
 *              // Note: we could use ITS_GetNextEvent() here.
 *              if (work->GetNextEvent(event) != ITS_SUCCESS)
 *              {
 *                  continue;
 *              }
 *
 *              event.SetSource(ITS_MTP3_SRC);
 *
 *              if (Transport::PutEvent(ITS_SCCP_SRC, event) != ITS_SUCCESS)
 *              {
 *                  printf("Couldn't send message to SCCP\n");
 *              }
 *          }
 *
 *          // this is good practice
 *          ITS_Terminate(h);
 *      }
 *
 *      -------------------------------------------------------------------
 *
 *      Next, we need to create a thread pool for the transaction handlers.
 *      Note that each transaction handler gets a task queue for a transport;
 *      this means they will never *directly* receive events from extraprocess
 *      sources.
 *
 *      -------------------------------------------------------------------
 *      //.interface:
 *      //////////////////////////////////////////////////////////////////////////////
 *      //  Name:
 *      //      HLR_Invoke pool
 *      //
 *      //  Purpose:
 *      //      A class to handle "invokee" threads
 *      //
 *      //  Usage:
 *      //      INLINE
 *      //////////////////////////////////////////////////////////////////////////////
 *      class HLR_InvokePool : public ThreadPool
 *      {
 *      public:
 *          HLR_InvokePool()
 *              : ThreadPool(), count(FIRST_INVOKE_THREAD)
 *          {
 *          }
 *
 *          //
 *          // recall that we used 3 instances above.  So we must start at
 *          // 4 here.
 *          // 
 *          virtual ITS_ThreadPoolThread* CreatePoolThread(int stackSize)
 *          {
 *              char iThreadName[16];
 *
 *              sprintf(iThreadName,"InvokeThread%d",count);
 *
 *              Worker* work =
 *                  new Worker(stackSize, iThreadName,
 *                                 count, ITS_TRANSPORT_TQUEUE);
 *              count++;
 *
 *              return (ITS_ThreadPoolThread *)work;
 *          }
 *
 *          // this function handles all external invokes.
 *          static void Invoke(ITS_ThreadPoolThread *s, void *arg);
 *  
 *      private:
 *          ITS_USHORT count;
 *      };
 *
 *      -------------------------------------------------------------------
 *
 *      This method represents the heart the transaction handling.  Here
 *      transaction handlers receive events from TCAP and process them.
 *      Threads start executing this method when the application selector
 *      decides which thread should handle a transaction.
 *
 *      -------------------------------------------------------------------
 *      //.implementation:extern
 *      //////////////////////////////////////////////////////////////////////////////
 *      //  Purpose:
 *      //      This function represents a TCAP "unit-of-work", or transaction handler
 *      //
 *      //  Input Parameters:
 *      //      thr - a pointer to an Worker thread
 *      //      arg - the argument to this function execution session
 *      //
 *      //  Input/Output Parameters:
 *      //      None.
 *      //
 *      //  Output Parameters:
 *      //      None.
 *      //
 *      //  Return Value:
 *      //      None.
 *      //
 *      //  Notes:
 *      //
 *      //  See Also:
 *      //////////////////////////////////////////////////////////////////////////////
 *      void
 *      HLR_InvokePool::Invoke(ITS_ThreadPoolThread *s, void *arg)
 *      {
 *          Worker* self = (Worker*)s;
 *          ITS_HANDLE hd;
 *          Event ev;
 *          TCAP_Dialogue *dlg;
 *          TCAP_Component *cpt;
 *
 *          // getting NULL here is a fatal error
 *          hd = ITS_Initialize(self->GetMask(),
 *                              self->GetInstance());
 *
 *          ITS_THROW_ASSERT(hd != NULL);
 *
 *          // Get the Dialog portion of the TCAP message
 *          self->GetNextEvent(ev);
 *
 *          // this will throw an exception if the event is not a dialogue
 *          ITS_THROW_ASSERT(TCAP_MSG_TYPE((&ev.GetEvent())) == ITS_TCAP_DLG);
 *          TCAP_Dialogue::Receive(hd, ev, &dlg);
 *
 *          // Get the component portion of the TCAP message
 *          self->GetNextEvent(ev);
 *
 *          // make sure we got a component
 *          ITS_THROW_ASSERT(TCAP_MSG_TYPE((&ev.GetEvent())) == ITS_TCAP_CPT);
 *          TCAP_Component::Receive(hd, ev, dlg, &cpt);
 *
 *          // handle invokes
 *          if (cpt->GetComponentType() == TCPPT_TC_INVOKE)
 *          {
 *              ITS_BOOLEAN isNat;
 *              ITS_OCTET family, op;
 *              TCAP_Invoke* inv = (TCAP_Invoke *)cpt;
 *
 *              inv->GetOperation(isNat, family, op);
 *
 *              // what to do for each operation
 *              switch(op)
 *              {
 *              case IS41_OP_LOC_REQ:
 *                  // yadada
 *                  break;
 *
 *              case IS41_OP_FEATURE_REQ:
 *                  // yadada
 *                  break;
 *
 *              case IS41_OP_REG_NOTIF:
 *                  // yadada
 *                  break;
 *
 *              default:
 *                  break;
 *              }
 *           }
 *           else 
 *           {
 *               // if it's not an invoke, it's an application error
 *               ITS_THROW_ASSERT(ITS_FALSE);
 *           }
 *      }
 *
 *      -------------------------------------------------------------------
 *
 *      Now we need to build our application class.  We base this on the
 *      ITS_Service class, which simplifies what we have to do to make
 *      this a service on NT, or a daemon process on UNIX.
 *
 *      -------------------------------------------------------------------
 *      //
 *      // a class for the service
 *      //
 *      class HLR_Service : public ITS_Service
 *      {
 *      public:
 *          HLR_Service(const std::string displayedName,
 *                      const std::string internalName,
 *                      ITS_ExceptionLog& exceptionLog,
 *                      EventLog& eventLog)
 *              : ITS_Service(displayedName, internalName,
 *                            exceptionLog, eventLog),
 *                dispatcherPool(NULL),
 *                invokePool(NULL)
 *          {
 *              static int instanceCounter = 0;
 *              //
 *              // Note: Instance counter mechanism is not thread safe.
 *              //
 *
 *              instanceCounter++;
 *
 *              if (instanceCounter > 1)
 *              {
 *                  bool only_one_instance_must_be_created = false;
 *
 *                  ITS_THROW_ASSERT(only_one_instance_must_be_created);
 *              }
 *          }
 *
 *          virtual ~HLR_Service()
 *          {
 *              // Nothing to do
 *          }
 *
 *          virtual void BeforeApplicationLoop(int argc, const char **argv);
 *          virtual void ApplicationLoop();
 *          virtual void AfterApplicationLoop();
 *
 *          static ITS_USHORT ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event);
 *
 *          HLR_DispatcherPool *
 *          GetDispatcherPool()
 *          {
 *              ITS_THROW_ASSERT(dispatcherPool != NULL);
 *
 *              return dispatcherPool;
 *          }
 *
 *          HLR_InvokePool *
 *          GetInvokePool()
 *          {
 *              ITS_THROW_ASSERT(invokePool != NULL);
 *
 *              return invokePool;
 *          }
 *
 *      protected:
 *          HLR_DispatcherPool * dispatcherPool;
 *          HLR_InvokePool *     invokePool;
 *      };
 *
 *      -------------------------------------------------------------------
 *
 *      This function is the application selector callback for this
 *      application.  The linkage is "C" because some systems will warn
 *      about using a static C++ method as a C function.  We just call
 *      the static C++ method in the service class.
 *
 *      -------------------------------------------------------------------
 *      //.implementation:extern
 *      //////////////////////////////////////////////////////////////////////////////
 *      //  Purpose:
 *      //      Routes the TCAP message to the application based on the dialog id
 *      //      This functions as the "application selector" as documented by
 *      //      ITS_RoutingMap
 *      //
 *      //  Input Parameters:
 *      //      hdr - the per-thread application context (dialogue_id).
 *      //
 *      //  Input/Output Parameters:
 *      //      None.
 *      //
 *      //  Output Parameters:
 *      //      None.
 *      //
 *      //  Return Value:
 *      //      returns the instance id of the first available dispatch thread
 *      //
 *      //  Notes:
 *      // WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *      //
 *      //   DO NOT THROW EXCEPTIONS FROM THIS CALL.  THE CALLER IS A "C" FUNCTION
 *      //   THAT HAS A LOCKED MUTEX.  AN UNCAUGHT EXCEPTION ORIGINATING FROM THIS
 *      //   FUNCTION MEANS THE MUTEX WILL STAY LOCKED, EFFECTIVELY BLOCKING ANY NEW
 *      //   TCAP TRANSACTION OR SCCP CONNECTION FROM THE PROGRAM.  YOU HAVE BEEN
 *      //   WARNED.
 *      //
 *      // WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *      //
 *      //  On some systems, the linkage type of this function must be "C".
 *      //
 *      //  See Also:
 *      //////////////////////////////////////////////////////////////////////////////
 *      extern "C" ITS_USHORT
 *      SelectApplication(ITS_HDR *hdr, ITS_EVENT* event)
 *      {
 *          try
 *          {
 *              return HLR_Service::ApplicationSelector(hdr, event);
 *          }
 *          catch (...)
 *          {
 *              return (ITS_INVALID_SRC);
 *          }
 *      }
 *
 *      -------------------------------------------------------------------
 *
 *      This is the real selector.  Note the translation from transaction
 *      id to thread (based on the context in the ITS_HDR structure).  TCAP
 *      is smart enough to only call this function for *new* transactions.
 *
 *      -------------------------------------------------------------------
 *
 *      //.implementation:extern
 *      //////////////////////////////////////////////////////////////////////////////
 *      //  Purpose:
 *      //      Routes the TCAP message to the application based on the dialog id
 *      //      This functions as the "application selector" as documented by
 *      //      ITS_RoutingMap
 *      //
 *      //  Input Parameters:
 *      //      hdr - the per-thread application context (dialogue_id).
 *      //      event - the event that begins this unit of work.
 *      //
 *      //  Input/Output Parameters:
 *      //      None.
 *      //
 *      //  Output Parameters:
 *      //      None.
 *      //
 *      //  Return Value:
 *      //      returns the instance id of the first available dispatch thread
 *      //
 *      //  Notes:
 *      //
 *      //  See Also:
 *      //////////////////////////////////////////////////////////////////////////////
 *      ITS_USHORT
 *      HLR_Service::ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event)
 *      {
 *          ITS_ThreadPoolEntry iThread;
 *          HLR_Service& service =
 *              reinterpret_cast<HLR_Service&>(ITS_Service::GetCurrentService());
 *  
 *          int did = hdr->context.dialogue_id;
 *
 *          int ret = service.GetInvokePool()->GetFirstAvailThread(iThread);
 *          ITS_THROW_ASSERT(ret == ITS_SUCCESS);
 *
 *          Worker* wThread = (Worker*)iThread.GetThread();
 *
 *          ITS_USHORT qid = wThread->GetInstance();
 *      
 *          ITS_RoutingMap::AddApplication(qid, hdr);
 *      
 *          // Invoke the Function for the thread
 *          ret = service.GetInvokePool()->DispatchOnThread(iThread,
 *                                                          HLR_InvokePool::Invoke,
 *                                                          NULL)
 *
 *          ITS_THROW_ASSERT(ret == ITS_SUCCESS); 
 *      
 *          return (qid);
 *      }
 *
 *      //
 *      // Before the main loop
 *      //
 *      void
 *      HLR_Service::BeforeApplicationLoop(int argc,
 *                                         const char **argv)
 *      {
 *          // First things first
 *          int ret = ITS_GlobalStart(ITS_TCAP|ITS_SCCP);
 *          ITS_THROW_ASSERT(ret == ITS_SUCCESS);
 *  
 *          // set the application selector for TCAP
 *          ROUTE_Selector last =
 *              ITS_RoutingMap::SetApplicationSelector(SelectApplication);
 *
 *          ITS_THROW_ASSERT(last != NULL);
 *
 *          // create your internal threads FIRST
 *          try
 *          {
 *              invokePool = new HLR_InvokePool();
 *
 *              invokePool->CreatePool(100, 0);
 *          }
 *          catch (ITS_GenericException& ex)
 *          {
 *              ex.Log();
 *          }
 *          catch (exception& exc)
 *          {
 *              ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);
 *
 *              standardExc.Log();
 *          }
 *      #if defined(NDEBUG)
 *          catch (...)
 *          {
 *              ITS_UnknownException unknownExc(__FILE__, __LINE__);
 *
 *              unknownExc.Log();
 *          }
 *      #endif // defined(NDEBUG)
 *
 *          // then create your external interfaces.
 *          try
 *          {
 *              dispatcherPool = new HLR_DispatcherPool();
 *
 *              dispatcherPool->CreatePool(MAX_DISPATCHERS, 0);
 *
 *              //
 *              // the order that threads are allocated is the same as the order
 *              // they were created in.  Not relevant here, but good to know.
 *              //
 *              int ret = dispatcherPool->Dispatch(HLR_DispatcherPool::Dispatcher,
 *                                                 NULL);
 *
 *              ITS_THROW_ASSERT(ret == ITS_SUCCESS);
 *
 *              ret = dispatcherPool->Dispatch(HLR_DispatcherPool::Dispatcher,
 *                                             NULL);
 *
 *              ITS_THROW_ASSERT(ret == ITS_SUCCESS);
 *
 *              ret = dispatcherPool->Dispatch(HLR_DispatcherPool::Dispatcher,
 *                                             NULL);
 *
 *              ITS_THROW_ASSERT(ret == ITS_SUCCESS);
 *          }
 *          catch (ITS_GenericException& ex)
 *          {
 *              ex.Log();
 *          }
 *          catch (exception& exc)
 *          {
 *              ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);
 *
 *              standardExc.Log();
 *          }
 *      #if defined(NDEBUG)
 *          catch (...)
 *          {
 *              ITS_UnknownException unknownExc(__FILE__, __LINE__);
 *
 *              unknownExc.Log();
 *          }
 *      #endif // defined(NDEBUG)
 *      }
 *
 *      //
 *      // main loop
 *      //
 *      void
 *      HLR_Service::ApplicationLoop()
 *      {
 *          TIMERS_Sleep(5);
 *      }
 *
 *      //
 *      // after main loop
 *      //
 *      void
 *      HLR_Service::AfterApplicationLoop()
 *      {
 *          // Kill your exterior comm points FIRST
 *          if (dispatcherPool)
 *          {
 *              delete dispatcherPool;
 *          }
 *          if (invokePool)
 *          {
 *              delete invokePool;
 *          }
 *      }
 *
 *
 *
 *      -------------------------------------------------------------------
 *
 *      main().
 *
 *      -------------------------------------------------------------------
 *      //
 *      // and the entry point.
 *      //
 *      int
 *      main(int argc, char **argv)
 *      {
 *          //
 *          // The exception log and event log objects MUST always be created as static
 *          // objects.  Also, no point in doing this in a try catch as if these
 *          // constructors throw an exception we can't report it.
 *          //
 *
 *      #if defined(WIN32)
 *
 *          static ITS_NtExceptionLog exceptionLog("TCAP Server");
 *          static ITS_NtEventLog eventLog("TCAP Server");
 *
 *          //
 *          // Ideally the following should be done by the installation procedure.
 *          //
 *
 *          ITS_NtEventLog::RegistryCreateSource("TCAP Server", "ItsMsgFile.dll");
 *
 *      #else // !defined(WIN32)
 *
 *          static ITS_UnixExceptionLog exceptionLog("TCAP Server");
 *          static ITS_UnixEventLog eventLog("TCAP Server");
 *
 *      #endif // defined(WIN32)
 *
 *          try
 *          {
 *              HLR_Service service("HLR Service", "HLR_Service",
 *                                  exceptionLog, eventLog);
 *
 *
 *              // Process command line.
 *              service.ProcessCommandLine(argc, (const char **)argv);
 *
 *              //
 *              // Set the application name.  This can be done in ProcessCommandLine().
 *              //
 *              // ITS_Application::SetName("TCAP_Server");
 *
 *              // set path for configuration directory.  Or let ProcessCommandLine()
 *              // do this.
 *              // ITS_Application::SetConfigDir("./");
 *
 *              // Override default behavior - force to foreground
 *              service.SetApplicationType(ITS_Service::AT_CONSOLE_APPLICATION);
 *
 *              if (service.GetApplicationType() ==
 *                  ITS_Service::AT_SERVICE)
 *              {
 *                  service.RunAsService();
 *              }
 *              else if (service.GetApplicationType() ==
 *                       ITS_Service::AT_CONSOLE_APPLICATION)
 *              {
 *                  service.RunAsConsoleApplication(argc, (const char **)argv);
 *              }
 *
 *              //
 *              // at this point, the main application thread has done it's work.  It
 *              // is no longer necessary for this thread to continue.  More, we won't
 *              // even get here under most common circumstances
 *              //
 *              exit(service.GetExitCode());
 *          }
 *          catch (ITS_GenericException& exc)
 *          {
 *              exc.Log();
 *          }
 *          catch (exception& exc)
 *          {
 *              ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);
 *
 *              standardExc.Log();
 *          }
 *
 *      #if defined(NDEBUG)
 *
 *          catch (...)
 *          {
 *              ITS_UnknownException unknownExc(__FILE__, __LINE__);
 *
 *              unknownExc.Log();
 *          }
 *
 *      #endif // defined(NDEBUG)
 *
 *          // Reached only if an exception has occurred.
 *
 *          return (EXIT_FAILURE);
 *      }
 *      --------------------------------------------------------------------
 *
 *****************************************************************************/
class Worker : public ThreadPoolThread
{
public:
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Create a worker
    *
    *  Input Parameters:
    *       stackSize - size of thread stack
    *       name - worker name
    *       instance - worker instance
    *       mask - flags
    *
    ************************************************************************/
    Worker(int stackSizeParam, const char *name,
           ITS_USHORT instance, ITS_UINT mask)
        : ThreadPoolThread(stackSizeParam, sizeof(WORKER_Control))
    {
        int ret, dummy = 0;

        ret = Initialize(dummy, stackSizeParam, name, instance, mask);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }

    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Create a worker
    *
    *  Input Parameters:
    *       stackSize - size of thread stack
    *       name - worker name
    *       instance - worker instance
    *       mask - flags
    *
    ************************************************************************/
    Worker(int stackSizeParam, const std::string& name,
               ITS_USHORT instance, ITS_UINT mask)
        : ThreadPoolThread(stackSizeParam, sizeof(WORKER_Control))
    {
        int ret, dummy = 0;

        ret = Initialize(dummy, stackSizeParam, name.c_str(), instance, mask);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }

    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Destroy a worker
    *
    ************************************************************************/
    virtual
    ~Worker()
    {
        // not necessary now
    }

    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Create a worker's transport
    *
    *  Return Value:
    *       ITS_SUCCESS - the worker's transport was created
    *
    ************************************************************************/
    int
    CreateTransport()
    {
        return WORKER_CreateTransport((WORKER_Control *)thread);
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Destroy a worker's transport
    *
    ************************************************************************/
    void
    DeleteTransport()
    {
        WORKER_DeleteTransport((WORKER_Control *)thread);
    }
    
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Get the next event on a worker's source
    *
    *  Output Parameters:
    *       ev - the event retrieved
    *
    *  Return Value:
    *       ITS_SUCCESS - the event was retrieved ok.  Any other return
    *       code indicates an error
    *
    ************************************************************************/
    int
    GetNextEvent(Event& ev)
    {
        return WORKER_GetNextEvent((WORKER_Control *)thread, &ev.GetEvent());
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Peek for the next event on a worker's source
    *
    *  Output Parameters:
    *       ev - the event retrieved, if possible
    *
    *  Return Value:
    *       ITS_SUCCESS - the event was retrieved ok.  ITS_ENOMSG indicates
    *       that nothing was pending.  Any other return code indicates
    *       an error.
    *
    ************************************************************************/
    int
    PeekNextEvent(Event& ev)
    {
        return WORKER_PeekNextEvent((WORKER_Control *)thread, &ev.GetEvent());
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       Put an event on a worker's source
    *
    *  Input Parameters:
    *       ev - the event to put
    *
    *  Return Value:
    *       ITS_SUCCESS - the event was sent ok.  Any other return
    *       code indicates an error
    *
    ************************************************************************/
    int
    PutEvent(Event& ev)
    {
        return WORKER_PutEvent((WORKER_Control *)thread, &ev.GetEvent());
    }

    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method provides access to the instance member variable.
    *       The instance is read-only
    *
    *  Return Value:
    *       The instance id of this transport.
    *
    *  See Also:
    *       GetMask()
    ************************************************************************/
    ITS_USHORT
    GetInstance() const
    {
        return WORKER_INSTANCE(thread);
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method provides access to the mask member variable.
    *       The mask is read-only
    *
    *  Return Value:
    *       The mask of this transport.
    *
    *  See Also:
    *       GetInstance()
    ************************************************************************/
    ITS_UINT
    GetMask() const
    {
        return WORKER_MASK(thread);
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method provides access to the name of this transport.
    *
    *  Return Value:
    *       A pointer to a character string.
    *
    ************************************************************************/
    const char *
    GetName() const
    {
        return WORKER_NAME(thread);
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method provides access to the name of this transport.
    *
    *  Return Value:
    *       A pointer to a character string.
    *
    ************************************************************************/
    void
    GetName(std::string& nameParam) const
    {
        nameParam = WORKER_NAME(thread);
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method provides access to the resource file associated
    *       with this worker.
    *
    *  Return Value:
    *       A pointer to the associated resource file.
    *
    *  See Also:
    *       GetInstance()
    ************************************************************************/
    const RESFILE_Manager*
    GetResourceFile() const
    {
        return TRANSPORT_RES(WORKER_TRANSPORT(thread));
    }
    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method allows the user to close the resource file
    *       associated with this worker.
    *
    ************************************************************************/
    void
    CloseResourceFile()
    {
    }

    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method allows the caller to retrieve the transport
    *       associated with this worker.
    *
    *  Return Value:
    *       A pointer to the worker's transport.
    *
    ************************************************************************/
    const TRANSPORT_Control*
    GetTransport() const
    {
        return WORKER_TRANSPORT(thread);
    }

    /*.implementation:public,inline,Worker
    ************************************************************************
    *  Purpose:
    *       This method should NEVER be called by user code.
    *
    *  Input Parameters:
    *       The new mask value.  This method is only used because
    *       friend handling for extern "C" functions is wierd on
    *       different compilers.
    *
    ************************************************************************/
    void
    SetMask(ITS_UINT newMask)
    {
        WORKER_MASK(thread) = newMask;
    }

    /*.implementation:public,inline,Worker
     **************************************************************************
     *  Purpose:
     *      This method can be invoked by consumers of this class to determine
     *      if the pool object containing this thread has been destroyed.
     *      When this method returns ITS_TRUE, the user should return from
     *      the function they are executing.
     *
     *  Return Value:
     *      ITS_TRUE - the thread should exit, as the containing pool has been
     *          destroyed.
     *      ITS_FALSE - the thread may continue executing.
     *
     **************************************************************************/
    virtual ITS_BOOLEAN
    GetExit()
    {
        return WORKER_GetExit((WORKER_Control *)thread);
    }

    /*.implementation:public,inline,ThreadPoolThread
     **************************************************************************
     *  Purpose:
     *      This method can be invoked by consumers of the thread pool class
     *      to signal this thread that the pool object containing this thread
     *      has been destroyed.
     *
     **************************************************************************/
    virtual void
    SetExit(ITS_BOOLEAN exitState)
    {
        WORKER_SetExit((WORKER_Control *)thread, exitState);
    }

    /*.implementation:static,inline,Worker
     ************************************************************************
     *  Purpose:
     *      This method finds an Worker in the process global map of
     *      Worker objects by transport id.
     *
     *  Input Parameters:
     *      instance - the worker to find by transport instance
     *
     *  Return Value:
     *      If the worker was found, a pointer to the worker object is returned.
     *      If the worker has not registered, NULL is returned.
     *
     ************************************************************************/
    static Worker*
    FindWorker(ITS_USHORT instance)
    {
        WORKER_Control *tmp;

        tmp = WORKER_FindWorker(instance);

        return ((Worker *)WORKER_BACK_PTR(tmp));
    }

private:
    /*.implementation:private,inline,Worker
     ************************************************************************
     *  Purpose:
     *      Shared initializer.
     *
     *  Input Parameters:
     *      stackSize - thread stack size
     *      name - thread name
     *      instance - the worker to find by transport instance
     *      mask - thread mask
     *
     *  Return Value:
     *
     ************************************************************************/
    int
    Initialize(int dummy, ...)
    {
        va_list args;
        int ret;

        va_start(args, dummy);

        if (!ITS_CLASS_INITTED(itsWORKER_Class))
        {
            ret = ITS_InitializeClass(itsWORKER_Class);

            ITS_ASSERT(ret == ITS_SUCCESS);
        }

        ret = ITS_CLASS_OBJECT_INSTANTIATE(itsWORKER_Class)(
                                                    (ITS_Object)thread, args);

        va_end(args);

        /* a kludge to avoid the wrong class record. FIXME */
        /* see its_thread_pool.c:TPOOL_CreatePool:THREAD_CreateThread */
        ITS_OBJ_CLASS(thread) = itsWORKER_Class;

        WORKER_BACK_PTR(thread) = this;

        return (ret);
    }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif  /* USE_CPLUSPLUS */

#endif  /* ITS_WORKER_H */
