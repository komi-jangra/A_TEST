
#include <sccp++.h>

/*
 * note: this test is not meant to be runnable.
 */
ITSDLLAPI int
SCCP_SendEvent_PRC(ITS_HANDLE handle, ITS_OCTET type,
                    ITS_HDR *hdr, ITS_SCCP_IE *ies,
                    int ieCount, SCCP_MSG_DESC* desc)
{
    return (ITS_SUCCESS);
}

ITSDLLAPI int
SCCP_ReceiveEvent_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                       ITS_HDR *hdr, ITS_SCCP_IE *ies,
                       int *ieCount, SCCP_MSG_DESC* desc)
{
    return (ITS_SUCCESS);
}

int
main(int argc, char **argv)
{
    its::SCCP_UnitData msg;
    its::Event event;
    ITS_HDR hdr;

    its::SCCP_MessageClass::Send(NULL, &hdr, &msg);

    return (0);
}
