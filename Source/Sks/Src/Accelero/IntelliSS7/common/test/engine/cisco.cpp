
#include <its++.h>

#include <engine.h>

#if defined(WIN32)
#define EXPORTFUNC  __declspec(dllexport)
#else
#define EXPORTFUNC
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

static void *
SS7_Initialize(ITS_UINT mask, ITS_USHORT instance)
{
    return calloc(1, sizeof(ITS_UINT));
}

static void
SS7_Terminate(void *)
{
}

static int
SS7_GetNextEvent(void *, ITS_EVENT *)
{
    return (ITS_SUCCESS);
}

static int
SS7_PeekNextEvent(void *, ITS_EVENT *)
{
    return (ITS_SUCCESS);
}

static int
SS7_PutEvent(void *, ITS_EVENT *)
{
    return (ITS_SUCCESS);
}

EXPORTFUNC SS7STACK_ClassRec itsNMS_ClassRec =
{
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        NMS_CLASS_NAME,
        ITS_CLASS_NO_INIT,
        ITS_CLASS_NO_DEST,
        ITS_CLASS_PART_NO_INIT,
        ITS_CLASS_PART_NO_DEST,
        ITS_INST_NO_CONST,
        ITS_INST_NO_DEST,
        NULL
    },
    {
        SS7_Initialize,
        SS7_Terminate,
        SS7_GetNextEvent,
        SS7_PeekNextEvent,
        SS7_PutEvent
    }
};
extern "C" EXPORTFUNC ITS_Class itsNMS_Class = (ITS_Class)&itsNMS_ClassRec;

static void
DoStateChange(SS7_VendorState newState)
{
}

EXPORTFUNC SS7RM_ClassRec itsNMSRM_ClassRec =
{
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        SS7RM_CLASS_NAME,
        ITS_CLASS_NO_INIT,
        ITS_CLASS_NO_DEST,
        ITS_CLASS_PART_NO_INIT,
        ITS_CLASS_PART_NO_DEST,
        ITS_INST_NO_CONST,
        ITS_INST_NO_DEST,
        NULL
    },
    {
        NULL,
        DoStateChange,
        NULL
    }
};

extern "C" EXPORTFUNC ITS_Class itsNMSRM_Class = (ITS_Class)&itsNMSRM_ClassRec;

extern "C" EXPORTFUNC ITS_USHORT
RouteSS7(ITS_HDR *h, ITS_EVENT *ev)
{
    return (ITS_DEFAULT_USER_SRC);
}

extern "C" EXPORTFUNC ITS_USHORT
RouteAPP(ITS_HDR *h, ITS_EVENT *ev)
{
    return (ITS_DEFAULT_USER_SRC);
}

extern "C" EXPORTFUNC int
CISCOMain(ThreadPoolThread *thr, Event& ev)
{
    return (ITS_SUCCESS);
}

extern "C" EXPORTFUNC int
GenericMain(ThreadPool *thr, Event &ev)
{
    return (ITS_SUCCESS);
}

extern "C" EXPORTFUNC int
FilterCacheMsgs(ThreadPoolThread *thr, Event &ev)
{
    return (ITS_SUCCESS);
}

extern "C" EXPORTFUNC int
GetConfigDir(ThreadPoolThread *thr)
{
    return (ITS_SUCCESS);
}

extern "C" EXPORTFUNC int
FilterUserMsgs(ThreadPoolThread *thr, Event &ev)
{
    return (ITS_SUCCESS);
}

extern "C" EXPORTFUNC int
AcceptOne(ThreadPoolThread *acceptor, ThreadPoolThread *accepted)
{
    return (ITS_SUCCESS);
}

extern "C" EXPORTFUNC void
HandleMTP3Management(ITS_POINTER object, ITS_POINTER userData,
                     ITS_POINTER callData)
{
}

extern "C" EXPORTFUNC void
HandleSCCPManagement(ITS_POINTER object, ITS_POINTER userData,
                     ITS_POINTER callData)
{
}

extern "C" EXPORTFUNC void
HandleGlobalTitle(ITS_POINTER object, ITS_POINTER userData,
                  ITS_POINTER callData)
{
}
