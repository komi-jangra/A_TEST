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
 * Revision 1.1.1.1  2007/10/04 13:23:55  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:52  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:13:29  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:52:36  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.1  2003/10/07 12:48:58  sswami
 * TCAP multiple App binding API's
 *
 *
 ****************************************************************************/
#include <tcap_clientapi.h>
#include <tcap_clientimpl.h>

ITS_MUTEX CL_WriteMutexLock;
ITS_MUTEX CL_ReadMutexLock;

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
        return NULL;
    }
    
    if (CL_SockInfo == NULL)
    {
        return NULL;
    }

    ret = SOCK_ClientConnect(CL_SockInfo);
    if (ret != ITS_SUCCESS)
    {
        return NULL;
    }

    if (MUTEX_CreateMutex(&CL_WriteMutexLock, 0) != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (MUTEX_CreateMutex(&CL_ReadMutexLock, 0) != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
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
CL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int ret =0;

    if (evt == NULL || handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    while(1)
    {

        ret = CL_ReadEvent(handle, evt);
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ERCVFAIL)
            {
                printf("Client Lost the connection %d\n", ret);
                CL_CloseConnection(handle);
            }
            return ret;
        }

        /* I want check if this event is for client or for App
         * if it is for client handle it and go again to ReadEvent()
         */
        if (evt->src == ITS_TCAP_SRC)
        {
            break;
        }
        else
        {
            CL_HandleClientEvent(evt);
        }
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

