
#include <its_timers.h>
#include <its_assertion.h>

int
main(int argc, char **argv)
{
    ITS_HANDLE h;
    ITS_TIME sec, usec;
    ITS_EVENT ev;
    ITS_SERIAL ser;
    int ret;

    ret = ITS_GlobalStart(0);

    TIMERS_UTime(&sec, &usec);

    printf("time now: %d:%d\n", sec, usec);

    h = ITS_Initialize(ITS_TRANSPORT_SINGLE_USER|ITS_TRANSPORT_TQUEUE,
                       1);

    ITS_C_ASSERT(h != NULL);

    ITS_EVENT_INIT(&ev, 0, 0);

    ser = TIMERS_StartUTimer(1, 200000, NULL, 0);

    ITS_C_ASSERT(ser != TIMER_BAD_SERIAL);

    while (ITS_GetNextEvent(h, &ev) == ITS_SUCCESS)
    {
        if (ev.src == ITS_TIMER_SRC)
        {
            TIMERS_UTime(&sec, &usec);

            printf("time now: %d:%d\n", sec, usec);

/*            ser = TIMERS_StartUTimer(1, 200000, NULL, 0); */
        }
        else
        {
            printf("unknown src %04x\n", ev.src);
        }
    }

    ITS_GlobalStop();

    return (0);
}

