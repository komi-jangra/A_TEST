/****************************************************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * $Id: tcap_clientapi.c
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/08 11:12:27  bsccs2
 * Init Code
 *
 * Revision 1.1.1.1  2007/10/04 13:25:04  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 * BscCs2
 *
 * Revision 1.3  2007/05/31 10:13:58  ashutosh.singh
 * *** empty log message ***
 *
 * Revision 1.2  2007/04/17 08:35:43  ashutosh.singh
 * Logger Lib related changes
 *
 * Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * Initialising sources in CVS
 *
 * Revision 1.1  2003/10/07 12:48:58  sswami
 * TCAP multiple App binding API's
 *
 *
 ****************************************************************************/
#include <tcap_clientapi.h>
#include <tcap_clientimpl.h>
#include "trace.h"
ITS_MUTEX CL_WriteMutexLock;
ITS_MUTEX CL_ReadMutexLock;
ITS_MUTEX SCMCL_WriteMutexLock;

ITS_SocketInfo * CL_SockInfo = NULL;




/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method creates a client stream socket and connects to the server
 *      socket
 *
 *  Input Parameters:
 *      host  - host machine IP address.
 *      port  - port number of the server
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_HANDLE if sucess else returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

SS7DLLAPI ITS_HANDLE
CL_Initialize(const char *host, int port)
{
    int ret =0;
    if (host == NULL)
    {
        return NULL;
    }

    ret = SOCK_ClientOpen(&CL_SockInfo, INET_DOMAIN, host, port); 
    if (ret != ITS_SUCCESS)
    {
        ISIL_DEBUG_TRACE(("Client socket open  failed!\n"));
        return NULL;
    }
    
    if (CL_SockInfo == NULL)
    {
        ISIL_ERROR_TRACE(("CL_SockInfo is NULL!\n"));
        return NULL;
    }

    ret = SOCK_ClientConnect(CL_SockInfo);
    if (ret != ITS_SUCCESS)
    {
   //     ISIL_DEBUG_TRACE(("Client conenct failed!\n"));
        SOCK_Close(CL_SockInfo);   // Code add to close the opened socket
        return NULL;
    }

    if (MUTEX_CreateMutex(&CL_WriteMutexLock, 0) != ITS_SUCCESS)
    {
       ISIL_ERROR_TRACE(("Failed to create mutex!\n"));
   /*     exit (1);*/
    }

    if (MUTEX_CreateMutex(&CL_ReadMutexLock, 0) != ITS_SUCCESS)
    {
        ISIL_ERROR_TRACE(("Failed to create mutex!\n"));
       /* exit (1);*/
    }
    return (ITS_HANDLE)CL_SockInfo;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method closes the socket connection with server
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
SS7DLLAPI int
CL_CloseConnection(ITS_HANDLE handle)
{
    if (handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    SOCK_Close((ITS_SocketInfo*)handle);

    MUTEX_DeleteMutex(&CL_WriteMutexLock);
    MUTEX_DeleteMutex(&CL_ReadMutexLock);

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method registers the routing info with server.
 *      socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      hdr    - array of CL_REG_INFO
 *      count  - number of elements in the array
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
SS7DLLAPI int
CL_Register(ITS_HANDLE handle, CL_REG_INFO *reg_info, int count)
{
    ITS_EVENT evt;
    int i =0, j = 1;

    /* form a register event and send to server*/
    ITS_EVENT_INIT(&evt, CL_SRC_SERVER, (sizeof(CL_REG_INFO) * count + 1));

    evt.data[0] = CL_TCAP_REGISTER_EVENT;
    
    for(i = 0; i < count; ++i)
    {
        memcpy(&evt.data[j], &reg_info[i], sizeof(CL_REG_INFO));
        j += sizeof(CL_REG_INFO);
    }

    return CL_WriteEvent(handle, &evt);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method deregerters the routing info with the server
 *      socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      hdr    - array of CL_REG_INFO
 *      count  - number of elements in the array
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
SS7DLLAPI int
CL_Deregister(ITS_HANDLE handle, CL_REG_INFO *reg_info, int count)
{
    ITS_EVENT evt;
    int i =0, j = 1;

    /* form a Deregister event and send to server*/
    ITS_EVENT_INIT(&evt, CL_SRC_SERVER, (sizeof(CL_REG_INFO) * count + 1));

    evt.data[0] = CL_TCAP_DEREGISTER_EVENT;
    
    for(i = 0; i < count; ++i)
    {
        memcpy(&evt.data[j], &reg_info[i], sizeof(CL_REG_INFO));
        j += sizeof(CL_REG_INFO);
    }

    return CL_WriteEvent(handle, &evt);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrives new event comming from server
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      evet    - ITS_EVENT * 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS if succeeds else returns ITS_ERCVFAIL
 *
 *  Notes:
 *      It retrun ITS_ERCVFAIL if it lost connection with server
 *      in that case user supposed to re Initialize the connection
 *  See Also:
 *
 ****************************************************************************/
SS7DLLAPI int
CL_GetNextEvent_FromMtp3(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int ret =0;

    if (evt == NULL || handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }


      /*  printf("Waiting for data \n");*/
        ret = CL_ReadEventMtp3(handle, evt);
/*        printf("read data successfully %d\n", ret);*/
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ERCVFAIL)
            {
               ISIL_ERROR_TRACE(("Client Lost the connection %d\n", ret));
                CL_CloseConnection(handle);
            }
            return ret;
        }

    return ITS_SUCCESS;
}

SS7DLLAPI int
CL_GetNextEvent_FromIsup(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int ret =0;

    if (evt == NULL || handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }


/*       printf("Waiting for data \n");*/
        ret = CL_ReadEventIsup(handle, evt);
/*        printf("read data successfully %d\n", ret);*/
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ERCVFAIL)
            {
                ISIL_ERROR_TRACE(("Client Lost the connection %d\n", ret));
                CL_CloseConnection(handle);
            }
            return ret;
        }


    return ITS_SUCCESS;
}





SS7DLLAPI int
CL_GetNextEvent_FromSccp(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int ret =0;

    if (evt == NULL || handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }


      /*  printf("Waiting for data \n");*/
        ret = CL_ReadEventSccp(handle, evt);
/*        printf("read data successfully %d\n", ret);*/
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ERCVFAIL)
            {
                ISIL_ERROR_TRACE(("Client Lost the connection %d\n", ret));
                CL_CloseConnection(handle);
            }
            return ret;
        }

    return ITS_SUCCESS;
}

SS7DLLAPI int
CL_GetNextEvent_FromTcap(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int ret =0;

    if (evt == NULL || handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }


/*       printf("Waiting for data \n");*/
        ret = CL_ReadEventTcap(handle, evt);
/*        printf("read data successfully %d\n", ret);*/
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ERCVFAIL)
            {
               ISIL_ERROR_TRACE(("Client Lost the connection %d\n", ret));
                CL_CloseConnection(handle);
            }
            return ret;
        }


    return ITS_SUCCESS;
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles register response
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      evt    - ITS_EVENT * 
 *      regInfo - register entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS if registered successfully else returns failure
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev,
                                  CL_TCAP_REG_ENTRY *regInfo)
{
    int counter =1;

    memcpy(&regInfo->reg_info, &ev->data[1], sizeof(CL_REG_INFO));
    counter += sizeof(CL_REG_INFO);

    regInfo->ret = 0;
    regInfo->ret |= ev->data[counter++];
    regInfo->ret |= ev->data[counter++] << 8;
    regInfo->ret |= ev->data[counter++] << 16;
    regInfo->ret |= ev->data[counter++] << 24;

    return(regInfo->ret);
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles responses to deregister request
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      evet    - ITS_EVENT * 
 *      regInfo - registration entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS deregistration succeeds else failure
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveDeRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                 CL_TCAP_REG_ENTRY *regInfo)
{
    int counter =1;

    memcpy(&regInfo->reg_info, &ev->data[1], sizeof(CL_REG_INFO));
    counter += sizeof(CL_REG_INFO);

    regInfo->ret = 0;
    regInfo->ret |= ev->data[counter++];
    regInfo->ret |= ev->data[counter++] << 8;
    regInfo->ret |= ev->data[counter++] << 16;
    regInfo->ret |= ev->data[counter++] << 24;

    return(regInfo->ret);
}




SS7DLLAPI int
CL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int ret =0;

    if (evt == NULL || handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }


/*       printf("Waiting for data \n");*/
        ret = CL_ReadEvent(handle, evt);
/*        printf("read data successfully %d\n", ret);*/
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ERCVFAIL)
            {
                ISIL_ERROR_TRACE(("Client Lost the connection %d\n", ret));
                CL_CloseConnection(handle);
            }
            return ret;
        }


    return ITS_SUCCESS;
}
