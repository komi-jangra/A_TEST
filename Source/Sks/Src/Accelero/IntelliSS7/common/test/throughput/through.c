
#include <its.h>
#include <engine.h>
#include <sys/timeb.h>

#define MAX_LOOPS 100000
#define LOOP_INCR 10000

struct timeb start, finish;

int
writeFunc(TPOOL_THREAD *tp)
{
    int i;
    ITS_EVENT ev;

    ftime(&start);

    for (i = 0; i < MAX_LOOPS; i++)
    {
        ITS_EVENT_INIT(&ev, 0, 120);

        TRANSPORT_PutEvent(1, &ev);
    }

    ftime(&finish);

    printf("Start: %d %d, finish %d %d\n", start.time, start.millitm,
           finish.time, finish.millitm);
    fflush(stdout);

    return (ITS_ENOMSG);
}

int
initFunc(TPOOL_THREAD *tp)
{
    static int firstTime = 1;

    if (firstTime)
    {
        TPOOL_THREAD *thr;
        int ret = TPOOL_GetFirstAvailThread(workerPool, &thr);

        if (ret != ITS_SUCCESS)
        {
            abort();
        }

        ret = TPOOL_DispatchOnThread(thr, DISP_Dispatch_USER,
                                     WORKER_BACK_PTR(thr));

        if (ret != ITS_SUCCESS)
        {
            abort();
        }

        firstTime = 0;
    }

    return (ITS_SUCCESS);
}

int
readFunc(TPOOL_THREAD *tp, ITS_EVENT *ev)
{
    int ret;

    ret = TRANSPORT_PutEvent(1, ev);

    return ret;
}

int
copyMain(TPOOL_THREAD *tp, ITS_EVENT *ev)
{
    static int numTimes = 0;

    if (numTimes == 0)
    {
        ftime(&start);
    }

    numTimes++;

    if (numTimes == MAX_LOOPS)
    {
        ftime(&finish);

        printf("Start: %d %d, finish %d %d\n", start.time, start.millitm,
               finish.time, finish.millitm);
        fflush(stdout);
    }

    if ((numTimes % LOOP_INCR) == 0)
    {
        printf("copied %d\n", LOOP_INCR);
        fflush(stdout);
    }

    return TRANSPORT_PutEvent(3, ev);
}

int
discardFunc(TPOOL_THREAD *tp, ITS_EVENT *ev)
{
    static int numTimes = 0;

    if (numTimes == 0)
    {
        ftime(&start);
    }

    numTimes++;

    if (numTimes == MAX_LOOPS)
    {
        ftime(&finish);

        printf("Start: %d %d, finish %d %d\n", start.time, start.millitm,
               finish.time, finish.millitm);
        fflush(stdout);
    }

    if ((numTimes % LOOP_INCR) == 0)
    {
        printf("discarded %d\n", LOOP_INCR);
        fflush(stdout);
    }

    return (ITS_SUCCESS);
}

ITS_BOOLEAN
nextFail(TPOOL_THREAD *tp, int why)
{
    printf("Next fail\n");

    return (why);
}

