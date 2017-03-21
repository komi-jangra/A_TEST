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
 ****************************************************************************/

#if !defined(ITS_BC_H)
#define ITS_BC_H

#ident "$Id: its_bc.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

class Event;
class Application;
class CallbackManager;
class CondVar;
class EventLog;
class NtEventLog;
class UnixEventLog;
class ExceptionLog;
class GenericException;
class StandardException;
class UnknownException;
class NtExceptionLog;
class UnixExceptionLog;
class Fifo;
class FifoTransport;
class BasicEvent;
class GatedFifo;
class GatedFifoTransport;
class Socket;
class GatedSocket;
class Mutex;
class GatedClientSocket;
class GatedServerSocket;
class HashTable;
class ClientTransport;
class ServerTransport;
class Transport;
class EndPointTransport;
class MemPool;
template <class _MutexGuard_> class SynchGuard;
class RoutingMap;
class ResourceManager;
class RWLock;
class Semaphore;
class IPCSemaphore;
class Socket;
class ClientSocket;
class ServerSocket;
class EndPointSocket;
class RawSocket;
class Thread;
class ThreadPoolThread;
class SS7Transport;
class Service;
class ThreadPoolEntry;
class ThreadPool;
class TaskQueueTransport;
class TraceOutputMethod;
class TraceFile;
class TraceStdout;
class TraceLevel;
class TraceNtEventLog;
class TraceUnixSyslog;
class TraceSubSystem;
class TransportFactory;
class Worker;
class WorkerFactory;
/* generated */
class Assert;
class Precondition;
class Postcondition;
class Invariant;
class Error;
class ServiceError;
class Win32Error;

typedef Event               ITS_Event;
typedef Application         ITS_Application;
typedef CallbackManager     ITS_CallbackManager;
typedef CondVar             ITS_CondVar;
typedef EventLog            ITS_EventLog;
typedef NtEventLog          ITS_NtEventLog;
typedef UnixEventLog        ITS_UnixEventLog;
typedef ExceptionLog        ITS_ExceptionLog;
typedef GenericException    ITS_GenericException;
typedef StandardException   ITS_StandardException;
typedef UnknownException    ITS_UnknownException;
typedef NtExceptionLog      ITS_NtExceptionLog;
typedef UnixExceptionLog    ITS_UnixExceptionLog;
typedef Fifo                ITS_Fifo;
typedef FifoTransport       ITS_FifoTransport;
typedef BasicEvent          ITS_BasicEvent;
typedef GatedFifo           ITS_GatedFifo;
typedef GatedFifoTransport  ITS_GatedFifoTransport;
typedef Socket              ITS_Socket;
typedef GatedSocket         ITS_GatedSocket;
typedef Mutex               ITS_Mutex;
typedef GatedClientSocket   ITS_GatedClientSocket;
typedef GatedServerSocket   ITS_GatedServerSocket;
typedef HashTable           ITS_HashTable;
typedef ClientTransport     ITS_ClientTransport;
typedef Transport           ITS_Transport;
typedef ServerTransport     ITS_ServerTransport;
typedef EndPointTransport   ITS_EndPointTransport;
typedef MemPool             ITS_MemPool;
typedef SynchGuard<Mutex>   ITS_MutexGuard;
typedef RoutingMap          ITS_RoutingMap;
typedef ResourceManager     ITS_ResourceManager;
typedef RWLock              ITS_RWLock;
typedef Semaphore           ITS_Semaphore;
typedef IPCSemaphore        ITS_IPC_Semaphore;
typedef Socket              ITS_Socket;
typedef ClientSocket        ITS_ClientSocket;
typedef ServerSocket        ITS_ServerSocket;
typedef EndPointSocket      ITS_EndPointSocket;
typedef RawSocket           ITS_RawSocket;
typedef Thread              ITS_Thread;
typedef ThreadPoolThread    ITS_ThreadPoolThread;
typedef SS7Transport        ITS_SS7Transport;
typedef Service             ITS_Service;
typedef ThreadPoolEntry     ITS_ThreadPoolEntry;
typedef ThreadPool          ITS_ThreadPool;
typedef TaskQueueTransport  ITS_TaskQueueTransport;
typedef TraceOutputMethod   ITS_TraceOutputMethod;
typedef TraceFile           ITS_TraceFile;
typedef TraceStdout         ITS_TraceStdout;
typedef TraceUnixSyslog     ITS_TraceSyslog;
typedef TraceNtEventLog     ITS_TraceNTEventLog;
typedef TraceLevel          ITS_TraceLevel;
typedef TraceSubSystem      ITS_TraceSubSystem;
typedef TransportFactory    ITS_TransportFactory;
typedef Worker              ITS_Worker;
typedef WorkerFactory       ITS_WorkerFactory;
/* generated */
typedef Assert              ITS_Assert;
typedef Precondition        ITS_Precondition;
typedef Postcondition       ITS_Postcondition;
typedef Invariant           ITS_Invariant;
typedef Error               ITS_Error;
typedef ServiceError        ITS_ServiceError;
typedef Win32Error          ITS_Win32Error;

/*
 * some we can't do with typedefs
 */
#define ITS_ByteArray                   ByteArray
#define ITS_STL_EMList                  EMList
#define ITS_MList                       MList
#define ITS_Factory                     Factory
#define ITS_ThreadSafeFactory           ThreadSafeFactory
#define ITS_Singleton                   Singleton
#define ITS_SingletonMultithreaded      SingletonMultithreaded
#define ITS_State                       State
#define ITS_Transition                  Transition
#define ITS_BasicState                  BasicState
#define ITS_FiniteStateMachine          FiniteStateMachine
#define ITS_SubFiniteStateMachine       SubFiniteStateMachine
#define ITS_BasicSubFiniteStateMachine  BasicSubFiniteStateMachine
#define ITS_BinaryTransition            BinaryTransition
#define ITS_BasicTransition             BasicTransition
#define ITS_TernaryTransition           TernaryTransition
#define ITS_QuaternaryTransition        QuaternaryTransition

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* ITS_BC_H */
