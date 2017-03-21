#include <stdio.h>
#include <memory.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <ansi/tcap.h>
#include <ansi/IS41.h>
#include <its_thread.h>
#include <its_ip_trans.h>
#include <its_ss7_stubs.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_trace.h>
#include <ansi/its_IS41.h>

ITS_THREAD dispatchSThread;
ITS_THREAD dispatchCThread;

SOCKTRAN_Manager *rcv_ft = NULL;
SOCKTRAN_Manager *send_ft = NULL;

THREAD_RET_TYPE Dispatch_Recv(void* );

void CreateReceiveTransport(void);
int sendTCAPBeginDlg(ITS_HANDLE handle,
			ITS_HDR *header, TCAP_DLG *dlg, int cpt_present);

int
main(int argc, char** argv)
{
    ITS_HANDLE	handle, rhandle;
    ITS_EVENT ev;

    handle = rhandle = NULL;

    /*
     * Set the name of the application.  The name of the apllication is
     * the name of the ITS .ini file read by IntelliSS7.
     */
    APPL_SetName("IS41_Test_Receive"); 

    /*
     * Initialize IntelliSS7.
     */
    handle = (ITS_HANDLE)ITS_Initialize(ITS_TCAP|ITS_SCCP|ITS_TRANSPORT_TQUEUE|
					ITS_TRANSPORT_SINGLE_USER, 1);
    if (!handle)
    {
        printf("\nUnable to create a handle.\n");

        return 1;
    }

    ITS_TRACE_WARNING(("Initialized\n"));

//    TIMERS_Sleep(1);
    CreateReceiveTransport();

    while (ITS_GetNextEvent(handle, &ev) == ITS_SUCCESS)
    {
    }

//    TIMERS_Sleep(1);
    ITS_Terminate(handle);

    return 0;
}


void CreateReceiveTransport(void)
{

    if (THREAD_CreateThread(&dispatchSThread, 0, Dispatch_Recv, NULL, ITS_TRUE) != ITS_SUCCESS) {
	printf("Could not create dispatch thread.\n");
	exit(1);
    }
    else
    {
        printf("Dispatch thread created successfully.\n");
    }
}


THREAD_RET_TYPE
Dispatch_Recv(void *arg)
{

    ITS_EVENT ev;


    rcv_ft = SOCKTRAN_CreateServerTransport("IS41_Test_Receive", 2,
                                     ITS_SCCP |ITS_TCAP | ITS_TRANSPORT_SSOCKET);

    if (!rcv_ft)
    {
	printf(" Could not create transport \n");
	exit(1);
    }

    while (TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(rcv_ft))(rcv_ft, &ev) ==
           ITS_SUCCESS)
    {
	ev.src = ITS_MTP3_SRC;
	TRANSPORT_PutEvent(ITS_SCCP_SRC, &ev);
    }

    THREAD_NORMAL_EXIT;
}
