
#include <its_app.h>
#include <its_ss7_stubs.h>
#include <its_ip_trans.h>
#include <its_timers.h>

int
main(int argc, char **argv)
{
    SOCKTRAN_Manager *endPoint;
    ITS_EVENT event;

    APPL_SetName("Test15");

    ITS_GlobalStart(0);

    endPoint = ITS_Initialize(ITS_TRANSPORT_DATAGRAM|
                                ITS_TRANSPORT_SINGLE_USER,
                              1);

    if (endPoint)
    {
        while (ITS_GetNextEvent(endPoint, &event) == ITS_SUCCESS)
        {
            if (event.data[0] == 'q')
            {
                break;
            }

            printf("Read string: %s\n", event.data);

            TRANSPORT_PutEvent(2, &event);
        }

        ITS_Terminate(endPoint);
    }

    ITS_GlobalStop();

    return (0);
}
