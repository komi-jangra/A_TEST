
#include <its_app.h>
#include <its_ss7_stubs.h>
#include <its_ip_trans.h>
#include <its_timers.h>

int
main(int argc, char **argv)
{
    SOCKTRAN_Manager *endPoint;
    char buf[80];
    ITS_EVENT event;

    APPL_SetName("Test16");

    ITS_GlobalStart(0);

    endPoint = ITS_Initialize(ITS_TRANSPORT_DATAGRAM|
                                ITS_TRANSPORT_SINGLE_USER,
                              1);

    if (endPoint)
    {
        while (gets(buf))
        {
            strcpy(event.data, buf);

            event.len = strlen(buf);

            TRANSPORT_PutEvent(2, &event);

            if (buf[0] == 'q')
            {
                break;
            }

            if (ITS_GetNextEvent(endPoint, &event) != ITS_SUCCESS)
            {
                break;
            }

            printf("echo packet: %s\n", event.data);
        }

        ITS_Terminate(endPoint);
    }

    ITS_GlobalStop();

    return (0);
}
