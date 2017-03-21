/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: clientimpl.c,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:23:46  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:13:05  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 07:26:06  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 1.1.2.7.6.1.10.1  2004/12/15 06:04:03  mmanikandan
 * Windows Build Support.
 *
 * Revision 1.1.2.7.6.1  2004/01/05 09:48:02  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.7.2.11  2003/12/19 04:45:11  akumar
 * Added flexibility to modifiy the client connection attempts with the server.
 *
 * Revision 1.1.2.7.2.10  2003/12/15 09:56:24  sjaddu
 * Refined code to exit gracefully.
 *
 * Revision 1.1.2.7.2.9  2003/11/20 06:23:07  akumar
 * More Modifications.
 *
 * Revision 1.1.2.7.2.8  2003/10/31 12:48:01  sjaddu
 * More testing with dynamic con open & close.
 *
 * Revision 1.1.2.7.2.7  2003/10/31 05:57:45  sjaddu
 * Final commit.
 *
 * Revision 1.1.2.7.2.6  2003/10/29 12:36:32  akumar
 * Modification wrt CL_CloseConnection API.
 *
 * Revision 1.1.2.7.2.5  2003/10/13 08:27:52  akumar
 * Code cleanup.
 *
 * Revision 1.1.2.7.2.4  2003/09/19 08:28:06  akumar
 * Avoid memory leak.
 *
 * Revision 1.1.2.7.2.3  2003/09/15 11:57:08  akumar
 * Connect time changed to 1 sec.
 *
 * Revision 1.1.2.7.2.2  2003/08/28 15:33:46  sjaddu
 * Functoins restructured.
 *
 * Revision 1.1.2.7.2.1  2003/08/26 12:47:48  sjaddu
 * Redundancy changes done.
 *
 * Revision 1.1.2.7  2003/08/04 11:27:03  sjaddu
 * Calling poll before going for read.
 *
 * Revision 1.1.2.6  2003/07/25 06:06:53  sjaddu
 * CL_Read CL_Write are mutex protected
 *
 * Revision 1.1.2.5  2003/06/25 14:36:50  sjaddu
 * Remove vcic from event and pass it on to decode func.
 *
 * Revision 1.1.2.4  2003/06/25 08:07:38  sjaddu
 * More tesing added decode function here.
 *
 * Revision 1.1.2.3  2003/06/20 11:21:40  sjaddu
 * more testing ...
 *
 * Revision 1.1.2.2  2003/06/18 08:49:44  tsanthosh
 * Added Request & Response functionality
 *
 * Revision 1.1.2.1  2003/06/05 05:21:45  sjaddu
 * Added first revision of files for ISUP client.
 *
 *
 ****************************************************************************/

#include <clientimpl.h>
#include <its_license_stubs.h>

#define SOC_CONNECT_INTERVAL   1

static char* sync_data = "ISS7SSI";
static int   sd_len = 7;
extern int con_serv_attempts;

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method sends the event to server 
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt - event to be send
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *  This method decides on which connection it should put the event,
 *  it always try to send on the primary connection in case of failure
 *  of primary connection only it sends on backup connection alternatively.  
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
CL_SendEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    CL_CONNECTION *conn = NULL; 
    int ret =0;

    if (handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    conn = (CL_CONNECTION*)handle;

    if (conn->primaryInfo.isUp)
    {
        ret = CL_WriteEvent(&conn->primaryInfo, evt);
        if (ret != ITS_SUCCESS)
        {
            printf("CL_SendEvent:: Write Event on prim connection failed\n");
        }
    }
    else if (conn->backupInfo.isUp) 
    {
        ret = CL_WriteEvent(&conn->backupInfo, evt);
        if (ret != ITS_SUCCESS)
        {
            printf("CL_SendEvent:: Write Event on backup connection failed\n");
        }
    }
    else
    {
        printf("CL_SendEvent:: Could not send Event to server conn is down\n");
    }

    return ret;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method write the data to socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt - event to be send
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *   
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int
CL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite;
    ITS_USHORT tmp =0;
    CL_CONNECTION_INFO *conInfo = NULL; 

    if (handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    conInfo = (CL_CONNECTION_INFO*)handle;

    if (!conInfo->isUp)
    {
        return ITS_ESENDFAIL;
    }

    MUTEX_AcquireMutex(&conInfo->writeLock);

    nrite = SOCK_Write(conInfo->sockInfo, sync_data, sd_len); 
    if (nrite != sd_len)
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return ITS_ESENDFAIL;
    }

    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(conInfo->sockInfo, (char *)evt->data, evt->len);

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&conInfo->writeLock);
            return (ITS_ESENDFAIL);
        }
    }
   
    /* Free the event*/
    if (evt->data)
    {
        free(evt->data);
        evt->data =0;
    }
    MUTEX_ReleaseMutex(&conInfo->writeLock);
    return ITS_SUCCESS;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method Reads the data from server
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt    -  event 
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *      evt - type ITS_EVENT *.
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 * 
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
CL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0;
    char buf;
    ITS_USHORT tmp =0;
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;
    CL_CONNECTION_INFO *conInfo = NULL; 

    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    conInfo = (CL_CONNECTION_INFO*)handle;
    if (conInfo == NULL)
    {
        return ITS_ERCVFAIL;
    }

    MUTEX_AcquireMutex(&conInfo->readLock);

    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */
        if (firstTime)
        {
            ITS_SockPollInfo info;

repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = conInfo->sockInfo;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&conInfo->readLock);
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                if (conInfo->isUp == ITS_FALSE)
                {
                    MUTEX_ReleaseMutex(&conInfo->readLock);
                    return ITS_ENOSOCKET;
                }
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

        ret = SOCK_Read(conInfo->sockInfo, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
            MUTEX_ReleaseMutex(&conInfo->readLock);
            return (ITS_ERCVFAIL);
        }

        if (buf != sync_data[i])
        {
            i = ~0U;
            continue;
        }
    }

    /* Here we are so successfully received ISS7SSI*/ 

    /* read the source */
    nread = SOCK_Read(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (ITS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
    nread = SOCK_Read(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (ITS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);

    evt->data = (ITS_OCTET *)malloc(evt->len);
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (evt->len)
    {
        nread = SOCK_Read(conInfo->sockInfo, (char *)evt->data, evt->len);

        if (nread != evt->len)
        {
            free(evt->data);
            evt->data = NULL;

            MUTEX_ReleaseMutex(&conInfo->readLock);
            return (ITS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&conInfo->readLock);
    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles the cleint specific events
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
CL_HandleClientEvent(ITS_EVENT *evt)
{
    printf("---Unexpected Client Msg received from server---\n");
    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method re registers the routing info with server.
 *      socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      hdr    - array of MTP3_HEADERS
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
CLDLLAPI int 
CL_ReRegister(CL_CONNECTION_INFO *info, CL_CONNECTION_TYPE type, 
              MTP3_HEADER *hdr, int count)
{
    ITS_EVENT evt;
    int i =0, j = 1, ret =0;

    if (info->isUp)
    {
        
        /* form a register event and send to server*/
        ITS_EVENT_INIT(&evt, CL_SRC_SERVER, (sizeof(MTP3_HEADER) * count + 1));

        if (type == CL_PRIMARY_CONNECTION)
        {
            evt.data[0] = CL_ISUP_REGISTER_EVENT;
        }
        else if (type == CL_BACKUP_CONNECTION)
        {
            evt.data[0] = CL_ISUP_REGISTER_BACKUP_EVENT;
        }

        for(i = 0; i < count; ++i)
        {
            memcpy(&evt.data[j], &hdr[i], sizeof(MTP3_HEADER));
            j += sizeof(MTP3_HEADER);
        }

        ret = CL_WriteEvent((ITS_HANDLE)info, &evt);
    }
    else
    {
        printf("Registration failed, check the connection \n");
    }

    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method connects to the server.
 *      socket
 *
 *  Input Parameters:
 *      info  -   of type CL_CONNECTION_INFO
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *      This function doesn't return until it connects to the server.
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
CL_Connect(CL_CONNECTION_INFO *info)
{
    int ret =0;
    int repeat_count = 1;

    while(1)
    {
        if (repeat_count > con_serv_attempts)
        {
            return  ITS_ENOSOCKET;
        }
        ret = SOCK_ClientOpen(&info->sockInfo,
                              INET_DOMAIN,
                              info->ipAddr,
                              info->port);
        if (ret != ITS_SUCCESS)
        {
            printf("Create client Failed fatal error: %d \n", ret);
            exit(1);
        }

        ret = SOCK_ClientConnect(info->sockInfo);
        if (ret != ITS_SUCCESS)
        {
            printf("Client connect failed Server IP Addr %s and Port# %d\n",
                                        info->ipAddr, info->port);
            SOCK_Close(info->sockInfo);
            info->sockInfo = NULL;
#ifdef WIN32
			Sleep(SOC_CONNECT_INTERVAL);
#else
            sleep(SOC_CONNECT_INTERVAL);
#endif
            repeat_count++;
        }
        else
        {   
            info->isUp = ITS_TRUE;
            printf("CL_Connect:: Client connected to Server\n");
            break;
        }
    }
    return ret;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method puts the event on to the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type CL_CONNECTION
 *      evt   -   of type ITS_EVENT
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
CLDLLAPI int 
CL_PutEventOnTaskQue(CL_TRANS_QUE *taskTran, ITS_EVENT *evt)
{
    int ret =0;
    
    ret = EMLIST_PutEvent(taskTran->taskQue,  (char *)evt, sizeof(ITS_EVENT));
    ++taskTran->noCurrEnts;

    return ret;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrieves the event from the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type CL_CONNECTION
 *      
 *  Output Parameters:
 *      evt   -   of type ITS_EVENT
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
CL_GetEventFromTaskQue(CL_TRANS_QUE *taskTran, ITS_EVENT *evt)
{
    int len = 0, ret;
    void *data = 0;

//    ITS_EVENT_TERM(evt);

repeat:
    if ((ret = EMLIST_GetNextEventWithTimeOut(taskTran->taskQue,
                                              &data, &len,
                                              HMI_GetTimeOutInterval()))
        != ITS_SUCCESS)
    {
        if (ret == ITS_ETIMEOUT)
        {
            goto repeat;
        }

        return (ret);
    }

    memcpy(evt, data, len);

    if (EMLIST_Lock(taskTran->taskQue) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ITS_Free(data);

    --taskTran->noCurrEnts;

    EMLIST_Unlock(taskTran->taskQue);

    return ret;
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
CLDLLAPI int
CL_CloseCon(ITS_HANDLE handle)
{
    CL_CONNECTION_INFO *conInfo = NULL;
    if (handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }
    conInfo = (CL_CONNECTION_INFO*)handle;
    
    conInfo->isUp = ITS_FALSE;
    SOCK_Close(conInfo->sockInfo);

    conInfo->sockInfo = NULL;

    return ITS_SUCCESS;
}

#if defined (ANSI)

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method encodes and sends the isup message to server
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_SendEvent_ANSI(ITS_HANDLE handle, ITS_OCTET type,
                                  ITS_HDR *hdr, ITS_ISUP_IE_ANSI *ies,
                                  int ieCount, ISUP_MSG_DESC *desc)
{

    int ret = ITS_SUCCESS;
    int  i = 0, j = 0;
    ITS_ISUP_IE temp_ies[ITS_MAX_ISUP_IES];
    ITS_EVENT evt;

    ITS_EVENT_INIT(&evt, 1, MTP2_MAX_MSG_SIZE);

    /* find the routing label, if present */
    for (i = 0, j = 0; i < ieCount; i++)
    {
        if (ies[i].param_id != ISUP_PRM_ROUTING_LABEL)
        {
            temp_ies[j++] = ies[i];
        }
    }

    ret = ISUP_MessageSanityCheck_ANSI(type, temp_ies, j, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    ret = ISUP_EncodeMTP3(ies, ieCount, type, &evt, hdr, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Fill the event src as from application*/
    evt.src = CL_APP_ISUP_SRC;

    ret = CL_SendEvent(handle, &evt);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&evt);
    }
    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method decodes the evet and returns ISUP IEs.
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_ReceiveEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                     ITS_HDR *hdr, ITS_ISUP_IE_ANSI *ies,
                                     int *ieCount, ISUP_MSG_DESC *desc)

{
    int ret = 0;
    hdr->type = ITS_ISUP;

    /* Get cic from event */
    hdr->context.cic |= ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)];
    hdr->context.cic |= (ev->data[sizeof(ITS_OCTET) + sizeof(ITS_OCTET) +
                         sizeof(ITS_CTXT)] << 8);

    /* let remove the vcic and pass it on to the Decode func*/
    memmove( &ev->data[sizeof(ITS_OCTET)], 
             &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
             ev->len - sizeof(ITS_CTXT));

    ev->len -=  sizeof(ITS_CTXT);

    ret = ISUP_DecodeMTP3(ies, ieCount, ev, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    /* These ies already includes the mtp3 header*/

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method reserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_ReserveCIC_ANSI(ITS_HANDLE h,
                                    ITS_OCTET sio,
                                    ITS_UINT  opc,
                                    ITS_UINT  dpc,
                                    ITS_USHORT cic,
                                    ITS_OCTET* cic_state,
                                    ITS_CTXT *vcic)
{
    /* Need to form an event out of these data */
    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter=0;

    ITS_EVENT_INIT(&event, CL_SRC_SERVER, sizeof(MTP3_HEADER) + 
                   sizeof(ITS_USHORT) + 1);

    event.data[0] = CL_ISUP_RESERVE_CIC_REQ;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return CL_SendEvent(h, &event);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method unreserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_UnReserveCIC_ANSI(ITS_HANDLE h,
                                     ITS_OCTET sio,
                                     ITS_UINT opc,
                                     ITS_UINT dpc,
                                     ITS_USHORT cic)

{

    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter=0;

    /* Need to form an event out of these data */
    ITS_EVENT_INIT(&event, CL_SRC_SERVER, sizeof(MTP3_HEADER) + 
                   sizeof(ITS_USHORT) + 1);

    event.data[0] = CL_ISUP_UNRESERVE_CIC_REQ;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return CL_SendEvent(h, &event);
}
#endif

#if defined (CCITT)

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method encodes and sends the isup message to server
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_SendEvent_CCITT(ITS_HANDLE handle, ITS_OCTET type,
                                  ITS_HDR *hdr, ITS_ISUP_IE_CCITT *ies,
                                  int ieCount, ISUP_MSG_DESC *desc)
{

    int ret = ITS_SUCCESS;
    int  i = 0, j = 0;
    ITS_ISUP_IE temp_ies[ITS_MAX_ISUP_IES];
    ITS_EVENT evt;

    ITS_EVENT_INIT(&evt, 1, MTP2_MAX_MSG_SIZE);

    /* find the routing label, if present */
    for (i = 0, j = 0; i < ieCount; i++)
    {
        if (ies[i].param_id != ISUP_PRM_ROUTING_LABEL)
        {
            temp_ies[j++] = ies[i];
        }
    }

    ret = ISUP_MessageSanityCheck_CCITT(type, temp_ies, j, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    ret = ISUP_EncodeMTP3(ies, ieCount, type, &evt, hdr, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Fill the event src as from application*/
    evt.src = CL_APP_ISUP_SRC;

    ret = CL_SendEvent(handle, &evt);

    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&evt);
    }
    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method decodes the evet and returns ISUP IEs.
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_ReceiveEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                     ITS_HDR *hdr, ITS_ISUP_IE_CCITT *ies,
                                     int *ieCount, ISUP_MSG_DESC *desc)

{
    int ret = 0;
    hdr->type = ITS_ISUP;

    /* Get cic from event */
    hdr->context.cic |= ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)];
    hdr->context.cic |= (ev->data[sizeof(ITS_OCTET) + sizeof(ITS_OCTET) +
                         sizeof(ITS_CTXT)] << 8);

    /* let remove the vcic and pass it on to the Decode func*/
    memmove( &ev->data[sizeof(ITS_OCTET)], 
             &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
             ev->len - sizeof(ITS_CTXT));

    ev->len -=  sizeof(ITS_CTXT);

    ret = ISUP_DecodeMTP3(ies, ieCount, ev, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    /* These ies already includes the mtp3 header*/

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method reserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_ReserveCIC_CCITT(ITS_HANDLE h,
                                    ITS_OCTET sio,
                                    ITS_UINT  opc,
                                    ITS_UINT  dpc,
                                    ITS_USHORT cic,
                                    ITS_OCTET* cic_state,
                                    ITS_CTXT *vcic)
{
    /* Need to form an event out of these data */
    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter=0;

    ITS_EVENT_INIT(&event, CL_SRC_SERVER, sizeof(MTP3_HEADER) + 
                   sizeof(ITS_USHORT) + 1);

    event.data[0] = CL_ISUP_RESERVE_CIC_REQ;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return CL_SendEvent(h, &event);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method unreserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int 
ISUP_UnReserveCIC_CCITT(ITS_HANDLE h,
                                     ITS_OCTET sio,
                                     ITS_UINT opc,
                                     ITS_UINT dpc,
                                     ITS_USHORT cic)

{

    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter=0;

    /* Need to form an event out of these data */
    ITS_EVENT_INIT(&event, CL_SRC_SERVER, sizeof(MTP3_HEADER) + 
                   sizeof(ITS_USHORT) + 1);

    event.data[0] = CL_ISUP_UNRESERVE_CIC_REQ;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return CL_SendEvent(h, &event);
}
#endif

