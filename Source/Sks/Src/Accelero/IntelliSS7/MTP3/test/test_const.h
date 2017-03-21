#ifndef TEST_CONST_H
#define TEST_CONST_H

#include <engine++.h>
#include <sccp++.h>
#include <vframe.h>

//#include "stats_record.h"

#define ASP_PC 2
#define SGP_PC 4

#if defined(CCITT)
#define ISS7_Stack    ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack    ISS7_ANSI_Stack
#endif

#define RECV_BUFFER_FORMAT "Received: %d \n"
#define SENT_BUFFER_FORMAT "Sent    : %d \n"

#define ASP_PC 2
#define SGP_PC 4

typedef enum _APP_MODE_
{
    ASP_MODE,
    SGP_MODE
}
APP_MODE;

extern APP_MODE appMode;

#define SCCP_ADDR_INDICATOR ( SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)

extern ITS_UINT LOCAL_PC;
extern ITS_UINT LOCAL_SSN;

extern ITS_UINT REMOTE_PC;
extern ITS_UINT REMOTE_SSN;

extern ITS_OCTET DATA[];

//extern StatsRecord record;

extern "C" void APP_SetStopper();

int TEST_BuildAndSendMsg(int itr, ITS_HANDLE hdl, SCCP_ADDR* dst, 
                         SCCP_ADDR* orig); 

ITS_INT TEST_AddLinkForLocalRoute(ITS_HANDLE handle);

#endif

