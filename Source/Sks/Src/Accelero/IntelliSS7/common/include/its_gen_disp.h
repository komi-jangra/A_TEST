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
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.46.2  2005/02/21 07:36:55  dsatish
 * LOG: PRC/TTC related changes.
 * LOG:
 * LOG: Revision 7.5.46.1  2004/12/16 03:26:18  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.42.1  2004/10/25 20:39:57  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.5  2002/09/24 21:11:34  yranade
 * LOG: Define MTP3 callback functions
 * LOG:
 * LOG: Revision 7.4  2002/09/18 20:27:35  mmiers
 * LOG: Move prototypes so C++ can use them
 * LOG:
 * LOG: Revision 7.3  2002/09/17 15:55:42  mmiers
 * LOG: Add C++ internode callbacks.
 * LOG:
 * LOG: Revision 7.2  2002/09/16 22:34:01  mmiers
 * LOG: Add signatures for INode callbacks
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/22 14:21:38  mmiers
 * LOG: Add china dispatcher
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/02/25 21:27:31  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.3  2001/11/20 17:42:01  mmiers
 * LOG: Finish DBC conversion.
 * LOG:
 * LOG: Revision 5.2  2001/11/16 16:40:35  mmiers
 * LOG: Don't block in accept.  Make the dispatchers aware of this.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 00:28:12  mmiers
 * LOG: Add custom dispatch.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.15  2001/04/19 20:43:10  mmiers
 * LOG: More error callbacks for the dispatchers.  Give the user an
 * LOG: option if ITS_Initialize fails.
 * LOG:
 * LOG: Revision 3.14  2001/04/18 19:59:13  mmiers
 * LOG: Add a preAccept call.
 * LOG:
 * LOG: Revision 3.13  2001/04/03 23:56:22  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.12  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.11  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 3.10  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 3.9  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.8  2001/03/07 01:16:02  mmiers
 * LOG: Shared lib template.  Need to test to see what happens to
 * LOG: symbols in the .so that are defined in the app.
 * LOG:
 * LOG: Revision 3.7  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 * LOG: Revision 3.6  2001/03/01 22:10:46  mmiers
 * LOG: Added thread pool.  Need application and serious thought on how
 * LOG: to glue it together.
 * LOG:
 * LOG: Revision 3.5  2001/03/01 17:18:57  mmiers
 * LOG: Revamp for engine.  Really just adding more callbacks.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:14  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/08/10 22:46:45  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update, dispatcher rework for generic behavior.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:36  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/07/28 02:25:55  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitize the names for the generic dispatchers.
 * LOG:
 * LOG: Revision 1.2  1999/07/27 23:25:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more generic dispatchers, this time for an integrated stack
 * LOG: in the application.  Add a method to determine if this is the last
 * LOG: component in a C++ TCAP_Component.
 * LOG:
 * LOG: Revision 1.1  1999/06/28 16:59:27  mmiers
 * LOG:
 * LOG:
 * LOG: Move the dispatchers to the support library for convenience.f
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_GEN_DISP_H
#define ITS_GEN_DISP_H

#include <its_thread_pool.h>

#ident "$Id: its_gen_disp.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

/*
 * we need this stanza for windows.  What a PITA
 */
#if defined(WIN32)
#if defined(DISP_IMPLEMENTATION)
#define DISPDLLAPI __declspec(dllexport)
#else
#define DISPDLLAPI __declspec(dllimport)
#endif
#else  /* WIN32 */
#define DISPDLLAPI
#endif /* WIN32 */

/*
 * what kind of traffic
 */
typedef enum
{
    DISP_PROT_CCITT,    /* ITU SS7 */
    DISP_PROT_ANSI,     /* ANSI SS7 */
    DISP_PROT_PRC,      /* CHINA SS7 */
    DISP_PROT_TTC,      /* JAPAN SS7 */
    DISP_PROT_USER,     /* UNDEFINED */
    DISP_PROT_WORK_ITEM,/* UNDEFINED */
    DISP_PROT_ITERATIVE,/* SOCKETS */
    DISP_PROT_DBC,      /* DEBUG CONSOLE */
    DISP_PROT_CUSTOM
}
DISP_HandlerType;

/*
 * blocking or non-blocking dispatchers
 */
typedef enum
{
    DISP_BLOCKING,
    DISP_NON_BLOCKING
}
DISP_Type;

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 *  These need to appear somewhere, might as well be here.
 */
ITSSS7DLLAPI int MTP3_INodeEvent_ANSI(TPOOL_THREAD *, ITS_EVENT *);
ITSSS7DLLAPI int MTP3_TransportPostInit_ANSI(TPOOL_THREAD *, ITS_HANDLE);
ITSSS7DLLAPI int MTP3_INodeEvent_CCITT(TPOOL_THREAD *, ITS_EVENT *);
ITSSS7DLLAPI int MTP3_TransportPostInit_CCITT(TPOOL_THREAD *, ITS_HANDLE);
ITSSS7DLLAPI int MTP3_INodeEvent_PRC(TPOOL_THREAD *, ITS_EVENT *);
ITSSS7DLLAPI int MTP3_TransportPostInit_PRC(TPOOL_THREAD *, ITS_HANDLE);
ITSSS7DLLAPI int MTP3_INodeEvent_TTC(TPOOL_THREAD *, ITS_EVENT *);
ITSSS7DLLAPI int MTP3_TransportPostInit_TTC(TPOOL_THREAD *, ITS_HANDLE);

#if defined(__cplusplus)
}
#endif

#if defined (USE_CPLUSPLUS)

/*
 * generic C++ dispatchers
 */
typedef void (*DISP_CPPDispatcher)(its::ThreadPoolThread *, void *);

/*
 * what to pass as the argument
 */
typedef struct
{
    DISP_Type           type;
    int                 (*PreInitialize)(its::ThreadPoolThread *);
    int                 (*PostInitialize)(its::ThreadPoolThread *, ITS_HANDLE);
    int                 (*PreNextEvent)(its::ThreadPoolThread *);
    bool                (*NextEventFailed)(its::ThreadPoolThread *, int);
    int                 (*PostNextEvent)(its::ThreadPoolThread *, its::Event &);
    int                 (*DispatchUserEvent)(its::ThreadPoolThread *,
                                             its::Event &);
    int                 (*DispatchISUPEvent)(its::ThreadPoolThread *,
                                             its::Event &);
    int                 (*DispatchSCCPEvent)(its::ThreadPoolThread *,
                                             its::Event &);
    int                 (*PreAccept)(its::ThreadPoolThread *,
                                     its::ThreadPoolThread *);
    int                 (*OnAccept)(its::ThreadPoolThread *,
                                    its::ThreadPoolThread *);
    void                (*PreTerminate)(its::ThreadPoolThread *);
    void                (*PostTerminate)(its::ThreadPoolThread *);
    its::ThreadPool     *pool;
    DISP_CPPDispatcher  dispAccept;
}
DISP_FuncsCPP;

#if defined(__cplusplus)
extern "C"
{
#endif

DISPDLLAPI void DISP_Dispatch_ANSI_CPP(its::ThreadPoolThread*, void *);
DISPDLLAPI void DISP_Dispatch_CCITT_CPP(its::ThreadPoolThread*, void *);
DISPDLLAPI void DISP_Dispatch_PRC_CPP(its::ThreadPoolThread*, void *);
DISPDLLAPI void DISP_Dispatch_TTC_CPP(its::ThreadPoolThread*, void *);

DISPDLLAPI void DISP_Dispatch_SS7_ANSI_CPP(its::ThreadPoolThread*, void *);
DISPDLLAPI void DISP_Dispatch_SS7_CCITT_CPP(its::ThreadPoolThread*, void *);
DISPDLLAPI void DISP_Dispatch_SS7_PRC_CPP(its::ThreadPoolThread*, void *);
DISPDLLAPI void DISP_Dispatch_SS7_TTC_CPP(its::ThreadPoolThread*, void *);

DISPDLLAPI void DISP_Dispatch_USER_CPP(its::ThreadPoolThread*, void *);

DISPDLLAPI void DISP_Dispatch_ITERATIVE_CPP(its::ThreadPoolThread *thr,
                                            void *arg);

DISPDLLAPI void DISP_Dispatch_DBC_CPP(its::ThreadPoolThread *thr, void *arg);

DISPDLLAPI bool DISP_DeliverMTP3_ANSI_CPP(its::ThreadPoolThread *thr, void *arg,
                                          its::Event &event);
DISPDLLAPI bool DISP_DeliverMTP3_CCITT_CPP(its::ThreadPoolThread *thr, void *arg,
                                           its::Event &);
DISPDLLAPI bool DISP_DeliverMTP3_PRC_CPP(its::ThreadPoolThread *thr, void *arg,
                                         its::Event &);
DISPDLLAPI bool DISP_DeliverMTP3_TTC_CPP(its::ThreadPoolThread *thr, void *arg,
                                         its::Event &);

/*
 * These need to be provided, might as well put them here.
 * The weird appearance is to avoid linkage problems where we
 * don't want to include all of them.  Note that we don't need
 * to worry about imports on WIN32 - nobody but the application
 * will ever need them.
 */
#if defined(WIN32)
#define APPDLLAPI __declspec(dllexport)
#else
#define APPDLLAPI
#endif

#define DEFINE_MTP3_INTERNODE_ANSI_CPP                                        \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_INodeEvent_ANSI_CPP(its::ThreadPoolThread *thr,                  \
                                 its::Event& event)                           \
        {                                                                     \
            return MTP3_INodeEvent_ANSI((TPOOL_THREAD *)thr->GetPtr(),        \
                                        &event.GetEvent());                   \
        }                                                                     \
    }
#define DEFINE_MTP3_POST_INIT_ANSI_CPP                                        \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_TransportPostInit_ANSI_CPP(its::ThreadPoolThread *thr,           \
                                        ITS_HANDLE handle)                    \
        {                                                                     \
            return MTP3_TransportPostInit_ANSI((TPOOL_THREAD *)thr->GetPtr(), \
                                               handle);                       \
        }                                                                     \
    }


#define DEFINE_MTP3_INTERNODE_CCITT_CPP                                       \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_INodeEvent_CCITT_CPP(its::ThreadPoolThread *thr,                 \
                                  its::Event& event)                          \
        {                                                                     \
            return MTP3_INodeEvent_CCITT((TPOOL_THREAD *)thr->GetPtr(),       \
                                         &event.GetEvent());                  \
        }                                                                     \
    }
#define DEFINE_MTP3_POST_INIT_CCITT_CPP                                       \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_TransportPostInit_CCITT_CPP(its::ThreadPoolThread *thr,          \
                                         ITS_HANDLE handle)                   \
        {                                                                     \
            return MTP3_TransportPostInit_CCITT((TPOOL_THREAD *)thr->GetPtr(),\
                                                handle);                      \
        }                                                                     \
    }


#define DEFINE_MTP3_INTERNODE_PRC_CPP                                         \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_INodeEvent_PRC_CPP(its::ThreadPoolThread *thr,                   \
                                its::Event& event)                            \
        {                                                                     \
            return MTP3_INodeEvent_CCITT((TPOOL_THREAD *)thr->GetPtr(),         \
                                       &event.GetEvent());                    \
        }                                                                     \
    }
#define DEFINE_MTP3_POST_INIT_PRC_CPP                                         \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_TransportPostInit_PRC_CPP(its::ThreadPoolThread *thr,            \
                                       ITS_HANDLE handle)                     \
        {                                                                     \
            return MTP3_TransportPostInit_PRC((TPOOL_THREAD *)thr->GetPtr(),  \
                                              handle);                        \
        }                                                                     \
    }

#define DEFINE_MTP3_INTERNODE_TTC_CPP                                         \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_INodeEvent_TTC_CPP(its::ThreadPoolThread *thr,                   \
                                its::Event& event)                            \
        {                                                                     \
            return MTP3_INodeEvent_CCITT((TPOOL_THREAD *)thr->GetPtr(),         \
                                       &event.GetEvent());                    \
        }                                                                     \
    }
#define DEFINE_MTP3_POST_INIT_TTC_CPP                                         \
    extern "C"                                                                \
    {                                                                         \
        APPDLLAPI int                                                         \
        MTP3_TransportPostInit_TTC_CPP(its::ThreadPoolThread *thr,            \
                                       ITS_HANDLE handle)                     \
        {                                                                     \
            return MTP3_TransportPostInit_TTC((TPOOL_THREAD *)thr->GetPtr(),  \
                                              handle);                        \
        }                                                                     \
    }



#if defined(__cplusplus)
}
#endif

#else /* !USE_CPLUSPLUS */

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * generic C dispatchers
 */
typedef void (*DISP_Dispatcher)(TPOOL_THREAD *, void *);

/*
 * what to pass as the argument
 */
typedef struct
{
    DISP_Type           type;
    int                 (*PreInitialize)(TPOOL_THREAD *);
    int                 (*PostInitialize)(TPOOL_THREAD *, ITS_HANDLE);
    int                 (*PreNextEvent)(TPOOL_THREAD *);
    ITS_BOOLEAN         (*NextEventFailed)(TPOOL_THREAD *, int);
    int                 (*PostNextEvent)(TPOOL_THREAD *, ITS_EVENT *);
    int                 (*DispatchUserEvent)(TPOOL_THREAD *, ITS_EVENT *);
    int                 (*DispatchISUPEvent)(TPOOL_THREAD *, ITS_EVENT *);
    int                 (*DispatchSCCPEvent)(TPOOL_THREAD *, ITS_EVENT *);
    int                 (*PreAccept)(TPOOL_THREAD *, TPOOL_THREAD *);
    int                 (*OnAccept)(TPOOL_THREAD *, TPOOL_THREAD *);
    void                (*PreTerminate)(TPOOL_THREAD *);
    void                (*PostTerminate)(TPOOL_THREAD *);
    TPOOL               *pool;
    DISP_Dispatcher     dispAccept;
}
DISP_Funcs;

DISPDLLAPI void DISP_Dispatch_ANSI(TPOOL_THREAD *thr, void *arg);
DISPDLLAPI void DISP_Dispatch_CCITT(TPOOL_THREAD *thr, void *arg);
DISPDLLAPI void DISP_Dispatch_PRC(TPOOL_THREAD *thr, void *arg);
DISPDLLAPI void DISP_Dispatch_TTC(TPOOL_THREAD *thr, void *arg);

DISPDLLAPI void DISP_Dispatch_SS7_ANSI(TPOOL_THREAD *thr, void *arg);
DISPDLLAPI void DISP_Dispatch_SS7_CCITT(TPOOL_THREAD *thr, void *arg);
DISPDLLAPI void DISP_Dispatch_SS7_PRC(TPOOL_THREAD *thr, void *arg);
DISPDLLAPI void DISP_Dispatch_SS7_TTC(TPOOL_THREAD *thr, void *arg);

DISPDLLAPI void DISP_Dispatch_USER(TPOOL_THREAD *thr, void *arg);

DISPDLLAPI void DISP_Dispatch_ITERATIVE(TPOOL_THREAD *thr, void *arg);

DISPDLLAPI void DISP_Dispatch_DBC(TPOOL_THREAD *thr, void *arg);

DISPDLLAPI ITS_BOOLEAN DISP_DeliverMTP3_ANSI(TPOOL_THREAD *work, void *arg,
                                             ITS_EVENT *event);
DISPDLLAPI ITS_BOOLEAN DISP_DeliverMTP3_CCITT(TPOOL_THREAD *work, void *arg,
                                              ITS_EVENT *event);
DISPDLLAPI ITS_BOOLEAN DISP_DeliverMTP3_PRC(TPOOL_THREAD *work, void *arg,
                                            ITS_EVENT *event);
DISPDLLAPI ITS_BOOLEAN DISP_DeliverMTP3_TTC(TPOOL_THREAD *work, void *arg,
                                            ITS_EVENT *event);

#if defined(__cplusplus)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_GEN_DISP_H */
