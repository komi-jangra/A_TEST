
#include <its.h>
#include <its_route.h>

int
main(int argc, char **argv)
{
    int i;
    ITS_HANDLE h;

    ITS_GlobalStart(0);

/*
    for (i = 4; i < 10; i++)
    {
        ROUTE_AddRoute(ITS_SCCP_ANSI_SRC, 1, i, LOCAL_ROUTE);
    }
*/
    h = ITS_Initialize(ITS_TRANSPORT_TQUEUE|ITS_MTP3_ANSI_SRC, 1);

    ITS_Terminate(h);

    ITS_GlobalStop();

    return (0);
}
