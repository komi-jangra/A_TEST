
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <its_emlist.h>
#include <its_thread.h>
#include <its_statics.cpp>
#include <its_timers.h>

EMLIST_Manager *list;
ITS_EVENT event;

THREAD_RET_TYPE
runThread(void *arg)
{
    int ret;

    for (;;)
    {
	printf("send event\n");
        if ((ret = EMLIST_PutEvent(list, &event, sizeof(ITS_EVENT))) != ITS_SUCCESS)
        {
            abort();
        }

        TIMERS_USleep(rand() % 100);
    }

    THREAD_NORMAL_EXIT;
}

int
main(int argc, char **argv)
{
    int ret;
    void* data;
    int len;
    ITS_THREAD thr;

    if (ITS_GlobalStart(0) != ITS_SUCCESS)
    {
        exit(0);
    }

    if ((list = EMLIST_Create()) == NULL)
    {
        exit(0);
    }

    if (THREAD_CreateThread(&thr, 0, runThread, NULL, ITS_TRUE) != ITS_SUCCESS)
    {
        exit(0);
    }

    TIMERS_Sleep(1);

    for (;;)
    {

        if ((ret = EMLIST_GetNextEvent(list, &data, &len)) != ITS_SUCCESS)
        {
            abort();
        }

        EMLIST_Free(list, data);

        printf("Got event\n");
    }

    return 0;
}
