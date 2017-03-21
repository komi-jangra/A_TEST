
#include <its_app.h>
#include <its_rudp.h>
#include <its_ip_trans.h>
#include <its_ss7_stubs.h>
#include <its_timers.h>

void
callback(ITS_POINTER object, ITS_POINTER ud, ITS_POINTER cbs)
{
    ITS_RUDP_CALLBACK_DATA *msg = (ITS_RUDP_CALLBACK_DATA *)cbs;

    printf("callback called: type %d connID: %04x\n",
           msg->type, msg->connID);
}

RUDP_Manager *endPoint;

THREAD_RET_TYPE
Rcv(void *arg)
{
    ITS_EVENT event;

    endPoint = RUDP_Open("Default-Transport1", 1,
                         ITS_TRANSPORT_DATAGRAM|ITS_TRANSPORT_RUDP_SOCKET|
                         ITS_TRANSPORT_SINGLE_USER,
                         NULL, callback);

    printf("\n\n****** Enter event loop *******\n\n");

    while (ITS_GetNextEvent(endPoint, &event) == ITS_SUCCESS)
    {
        printf("event data: %s\n", event.data);
    }

    printf("\n\n****** Exit event loop *******\n\n");

    THREAD_NORMAL_EXIT;
}

int
main(int argc, char **argv)
{
    char buf[80];
    ITS_EVENT event;
    ITS_THREAD thr;
    void *status;

    APPL_SetName("Test18");

    ITS_AddFeature(itsRUDP_Class);

    ITS_GlobalStart(0);

    THREAD_CreateThread(&thr, 0, Rcv, NULL, ITS_TRUE);

    while (gets(buf))
    {
        strcpy(event.data, buf);

        event.len = strlen(buf) + 1;

        TRANSPORT_PutEvent(2, &event);

        if (buf[0] == 'q')
        {
            RUDP_Close(endPoint);

            break;
        }
    }

    printf("Wait for thread\n");

    THREAD_WaitForThread(&thr, &status);

    ITS_GlobalStop();

    return (0);
}
