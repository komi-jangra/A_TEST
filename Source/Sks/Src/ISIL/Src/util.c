#include <tcap_clientapi.h>
#include <tcap_clientimpl.h>
#include <engine.h>
#include <pthread.h>
#include <signal.h>
#include "trace.h"

extern char CpIpAddress[];
extern char PpIpAddress[];
extern int   isupClientPort;

extern int   mmClientPort;
extern int   tcapClientPort;


ITS_HANDLE CL_Handle_ISUP;
ITS_HANDLE CL_Handle_MM;

ITS_HANDLE CL_Handle_TCAP;

int InitClientIsup();

int InitClientMM();

int InitClientTcap();
extern void  add_connection(ITS_SocketInfo *connect);
extern void  ISIL_TRACE(int trace ,const char *ftstring, ...);


/* Method binds the app with server on specified ipaddress and port
 * and also registers the list of OPC,DPC,Ni supported by app
 */

#define ISIL_TRACE_DEBUG   0x01
#define ISIL_TRACE_ERROR   0x02
#define ISIL_TRACE_WARNING 0x03

#define printf
int InitClientIsup()
{
    int flag = ITS_SUCCESS;
    int ret =0,i;
    CL_REG_INFO rInfo;
    ITS_EVENT event; 
    
        /* Method binds client app with server on specified 
         *  ipaddress and port 
         */
        CL_Handle_ISUP = CL_Initialize(CpIpAddress,isupClientPort );
        ISIL_DEBUG_TRACE(("Value of ISUP handle= %x\n",CL_Handle_ISUP));
        if (CL_Handle_ISUP == NULL)
        {
            ISIL_DEBUG_TRACE(("Client Connect to ISUP Server failed\n"));
            return ITS_ENOTFOUND;
        }
        else
       {
       /* Compose routing info for list of routing keys*/
       add_connection((ITS_SocketInfo *)CL_Handle_ISUP);
       return ITS_SUCCESS;
       }
}


int InitClientTcap()
{
    int flag = ITS_SUCCESS;
    int ret =0,i;
    CL_REG_INFO rInfo;
     
        /* Method binds client app with server on specified 
         *  ipaddress and port 
         */
        CL_Handle_TCAP = CL_Initialize(PpIpAddress, tcapClientPort);
        ISIL_DEBUG_TRACE(("Value of TCAP handle = %x\n",CL_Handle_TCAP));

        if (CL_Handle_TCAP == NULL)
        {
          ISIL_DEBUG_TRACE(("Client Connect to TCAP Server failed\n"));
            return ITS_ENOTFOUND;
        }
        else 
        {
       /* Compose routing info for list of routing keys*/
       add_connection((ITS_SocketInfo *)CL_Handle_TCAP);
         return ITS_SUCCESS;
        }
}

int InitClientMM()
{
    int flag = ITS_SUCCESS;
    int ret =0,i;
    CL_REG_INFO rInfo;
   ITS_EVENT event;


        /* Method binds client app with server on specified
         *  ipaddress and port
         */
        CL_Handle_MM = CL_Initialize(CpIpAddress,mmClientPort );
        ISIL_DEBUG_TRACE(("Value of MM Handle=%x\n",CL_Handle_MM));
        if (CL_Handle_MM == NULL)
        {
            ISIL_DEBUG_TRACE(("Client Connect to MM Server failed\n"));
            return ITS_ENOTFOUND;
        }
        else
        {
        /* Compose routing info for list of routing keys*/
       add_connection((ITS_SocketInfo *)CL_Handle_MM);
        return ITS_SUCCESS;
        }
}

void Trace( const char *ftstring, ...)
{
     va_list args;
     va_start(args,ftstring);
     time_t now;
     struct tm *now_time, tbuf;
     char temptime[80];
     char outString[1024];
     char temp[20];

     time(&now);
     now_time=localtime_r(&now,&tbuf);
    strftime(temptime,80, "[%b%d %Y %H:%M:%S]: ", &tbuf);                                       /* [MMMDD YY, H H:MM:SS\0]  */
     sprintf(outString, "%s", temptime);

     strcat(outString,ftstring);
     vprintf(outString,args);
     va_end(args);
}





