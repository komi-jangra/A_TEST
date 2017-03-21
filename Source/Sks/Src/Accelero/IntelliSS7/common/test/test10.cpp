
#include <its.h>

extern "C" ITS_HANDLE
ITS_Initialize(ITS_UINT mask, ITS_USHORT instance)
{
    ITS_HANDLE h = NULL;

    return (h);
}

extern "C" void
ITS_Terminate(ITS_HANDLE h)
{
}

extern "C" int
ITS_GetNextEvent(ITS_HANDLE h, ITS_EVENT* ev)
{
    return (ITS_SUCCESS);
}

extern "C" int
ITS_PeekNextEvent(ITS_HANDLE h, ITS_EVENT* ev)
{
    return (ITS_SUCCESS);
}

extern "C" int
ITS_PutEvent(ITS_HANDLE h, ITS_EVENT* ev)
{
    return (ITS_SUCCESS);
}

int
main(int argc, char **argv)
{
    ITS_HANDLE h;

    h = ITS_Initialize(0, 0);

    if (!h)
    {
        return (0);
    }

    for (;;)
    {
        ITS_EVENT event;

        if (ITS_GetNextEvent(h, &event) != ITS_SUCCESS)
        {
            break;
        }

        /* act on event */
    }

    ITS_Terminate(h);

    return (0);
}
