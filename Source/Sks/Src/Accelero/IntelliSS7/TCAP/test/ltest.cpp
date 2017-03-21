
#include <tcap++.h>

/*
 * this test is not meant to be runnable
 */
ITSDLLAPI int
TCAP_SendComponent_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                        TCAP_CPT *cpt)
{
    return (ITS_SUCCESS);
}

ITSDLLAPI int
TCAP_ReceiveComponent_PRC(ITS_HANDLE handle, ITS_EVENT *event,
                           ITS_HDR *hdr, TCAP_CPT *cpt)
{
    return (ITS_SUCCESS);
}

ITSDLLAPI int
TCAP_SendDialogue_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                       TCAP_DLG *dlg)
{
    return (ITS_SUCCESS);
}

ITSDLLAPI int
TCAP_ReceiveDialogue_PRC(ITS_HANDLE handle, ITS_EVENT *event,
                          ITS_HDR *hdr, TCAP_DLG *dlg)
{
    return (ITS_SUCCESS);
}

int
main(int argc, char **argv)
{
    its::TCAP_Begin begin;

    its::TCAP_Dialogue::Send(NULL, &begin);

    return 0;
}
