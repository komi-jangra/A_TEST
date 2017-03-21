
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

int
main(int argc, char **argv)
{
    RUDP_Manager *endPoint;
    ITS_EVENT event;

    APPL_SetName("Test17");

    ITS_AddFeature(itsRUDP_Class);

    ITS_GlobalStart(0);

    endPoint = RUDP_Listen("Default-Transport1", 1,
                           ITS_TRANSPORT_DATAGRAM|ITS_TRANSPORT_RUDP_SOCKET|
                           ITS_TRANSPORT_SINGLE_USER,
                           NULL, callback);

    if (endPoint)
    {
        printf("\n\n****** Enter event loop *******\n\n");

        while (ITS_GetNextEvent(endPoint, &event) == ITS_SUCCESS)
        {
            printf("echo packet: %s\n", event.data);

            if (event.data[0] == 'q')
            {
                break;
            }

            TRANSPORT_PutEvent(2, &event);
        }

        RUDP_Close(endPoint);
    }

    ITS_GlobalStop();

    ITS_RemFeature(itsRUDP_Class);

    return (0);
}
