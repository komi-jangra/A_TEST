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
 * $Id: clientapi.c,v 1.1.1.1 2007-10-08 11:11:19 bsccs2 Exp $
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
 * Revision 9.1  2005/03/23 12:52:00  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 07:26:06  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 1.1.2.5.6.2.10.1  2004/12/15 06:00:58  mmanikandan
 * Windows Build Support.
 *
 * Revision 1.1.2.5.6.2  2004/01/27 14:12:26  sjaddu
 * Changes made for active-back config.
 *
 * Revision 1.1.2.5.6.1  2004/01/05 09:48:02  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.5.2.14  2003/12/19 04:45:11  akumar
 * Added flexibility to modifiy the client connection attempts with the server.
 *
 * Revision 1.1.2.5.2.13  2003/12/15 09:56:24  sjaddu
 * Refined code to exit gracefully.
 *
 * Revision 1.1.2.5.2.12  2003/11/20 06:23:07  akumar
 * More Modifications.
 *
 * Revision 1.1.2.5.2.11  2003/10/31 12:48:01  sjaddu
 * More testing with dynamic con open & close.
 *
 * Revision 1.1.2.5.2.10  2003/10/31 05:57:45  sjaddu
 * Final commit.
 *
 * Revision 1.1.2.5.2.9  2003/10/29 12:33:35  akumar
 * Modification for CL_CloseConnection API.
 *
 * Revision 1.1.2.5.2.8  2003/10/21 06:30:14  akumar
 * Minor printf mod.
 *
 * Revision 1.1.2.5.2.7  2003/10/13 08:27:52  akumar
 * Code cleanup.
 *
 * Revision 1.1.2.5.2.6  2003/09/19 08:29:52  akumar
 * Multiple deregistrations can be done.
 *
 * Revision 1.1.2.5.2.5  2003/09/15 11:14:40  akumar
 * Misc Changes.
 *
 * Revision 1.1.2.5.2.4  2003/09/13 06:50:23  akumar
 * Dereg will remove entry kept for re-reg.
 *
 * Revision 1.1.2.5.2.3  2003/08/29 09:54:21  akumar
 * Modifications for Deregistration APi.
 *
 * Revision 1.1.2.5.2.2  2003/08/28 15:33:21  sjaddu
 * Functions restructured .
 *
 * Revision 1.1.2.5.2.1  2003/08/26 12:47:48  sjaddu
 * Redundancy changes done.
 *
 * Revision 1.1.2.5  2003/07/25 06:05:46  sjaddu
 * CL_Read CL_Write are mutex protected now.
 *
 * Revision 1.1.2.4  2003/07/04 09:37:35  tsanthosh
 * Added SS7DDLAPI to all function signatures.
 *
 * Revision 1.1.2.3  2003/06/20 11:20:59  sjaddu
 * more testing ...
 *
 * Revision 1.1.2.2  2003/06/18 08:46:02  tsanthosh
 * Added Request & Response functionality
 *
 * Revision 1.1.2.1  2003/06/05 05:21:45  sjaddu
 * Added first revision of files for ISUP client.
 *
 *
 ****************************************************************************/

#include <clientapi.h>
#include <clientimpl.h>
#include <its_redundancy.h>

CLDLLAPI CL_CONNECTION CL_ISUP_Connection;
int con_serv_attempts = 20;

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is thread function for primary connection.
 *
 *  Input Parameters:
 *      void  *  -   not used 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
#ifdef WIN32
static unsigned __stdcall 
#else
static void *
#endif
PrimaryThreadFunction(void *v)
{
    ITS_EVENT evt;
    int ret =0;

    memset(&evt, 0, sizeof(ITS_EVENT));
    while(CL_ISUP_Connection.primaryInfo.thrInfo.isRunning)
    {
        ret = CL_ReadEvent(&CL_ISUP_Connection.primaryInfo, &evt);
        if (ret == ITS_SUCCESS)
        {
            ret = CL_PutEventOnTaskQue(&CL_ISUP_Connection.taskTrans, &evt);
            if (ret != ITS_SUCCESS)
            {
                printf("Some problem in puting the event on to list\n");
            }
        }
        else if (ret == ITS_ENOSOCKET)
        {
            continue;
        }
        else if (ret == ITS_ERCVFAIL)
        {
            CL_CloseCon(&CL_ISUP_Connection.primaryInfo);

            /* Try to reconnect */
            ret = CL_Connect(&CL_ISUP_Connection.primaryInfo);
            if (ret != ITS_SUCCESS)
            {
                if (ret == ITS_ENOSOCKET)
                {
                    printf("Attempt to reconnect failed check server\n");
                    printf("Server IP Addr %s and Port# %d\n",
                            CL_ISUP_Connection.primaryInfo.ipAddr,
                            CL_ISUP_Connection.primaryInfo.port);
                    CL_CloseConnection(CL_PRIMARY_CONNECTION);
                    THREAD_DeleteThread(&CL_ISUP_Connection.primaryInfo.thrInfo.info);
#ifdef WIN32
					return 0;
#else
                    return NULL;
#endif
                }
                else
                {
                    printf("We have major problem here ---\n");
#ifdef WIN32
					return 0;
#else
                    return NULL;
#endif
                }
            }
            else
            {
                /* We have to reregister again*/
                ret = CL_ReRegister(&CL_ISUP_Connection.primaryInfo,
                                    CL_PRIMARY_CONNECTION, 
                                    CL_ISUP_Connection.regInfo.mtp3, 
                                    CL_ISUP_Connection.regInfo.count);
                if (ret != ITS_SUCCESS)
                {   
                    printf("Re Registration failed -------------\n");
                }
                printf(" Primary connection reconnected \n");
                continue;
            }
        } 
    }

    SOCK_Close(CL_ISUP_Connection.primaryInfo.sockInfo);
    CL_ISUP_Connection.primaryInfo.sockInfo = NULL;
    THREAD_DeleteThread(&CL_ISUP_Connection.primaryInfo.thrInfo.info);
    printf("Thread exiting for primary connection\n");
#ifdef WIN32
					return 0;
#else
                    return NULL;
#endif
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is thread function for backup connection.
 *
 *  Input Parameters:
 *      void  *  -   not used 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

 
#ifdef WIN32
unsigned __stdcall 
#else
static void *
#endif
BackupThreadFunction(void *v)
{
    ITS_EVENT evt;
    int ret =0;
    
    memset(&evt, 0, sizeof(ITS_EVENT));
    while(CL_ISUP_Connection.backupInfo.thrInfo.isRunning)
    {
        ret = CL_ReadEvent(&CL_ISUP_Connection.backupInfo, &evt);
        if (ret == ITS_SUCCESS)
        {
            ret = CL_PutEventOnTaskQue(&CL_ISUP_Connection.taskTrans, &evt);
            if (ret != ITS_SUCCESS)
            {
                printf("Some problem in puting the event on to list\n");
            }
        }
        else if (ret == ITS_ENOSOCKET)
        {
            continue;
        }
        else if (ret == ITS_ERCVFAIL)
        {
            printf("BackUp Connection lost with the ISUP server\n");
            CL_CloseCon(&CL_ISUP_Connection.backupInfo);
            ret = CL_Connect(&CL_ISUP_Connection.backupInfo);
            if (ret != ITS_SUCCESS)
            {
                if (ret == ITS_ENOSOCKET)
                {
                    printf("Attempt to reconnect failed check server\n");
                    printf("Server IP Addr %s and Port# %d\n",
                            CL_ISUP_Connection.backupInfo.ipAddr,
                            CL_ISUP_Connection.backupInfo.port);
                    CL_CloseConnection(CL_BACKUP_CONNECTION);
                    THREAD_DeleteThread(&CL_ISUP_Connection.backupInfo.thrInfo.info);
#ifdef WIN32
					return 0;
#else
                    return NULL;
#endif
                }
                else
                {
                    printf("We have major problem here ---\n");
#ifdef WIN32
					return 0;
#else
                    return NULL;
#endif
                }
            }
            else
            {
                /* We have to reregister again*/
                ret = CL_ReRegister(&CL_ISUP_Connection.backupInfo, 
                                    CL_BACKUP_CONNECTION,
                                    CL_ISUP_Connection.regInfo.mtp3, 
                                    CL_ISUP_Connection.regInfo.count);
                if (ret != ITS_SUCCESS)
                {   
                    printf("Re Registration failed -------------\n");
                }
                printf(" Backup connection reconnected \n");
                continue;
            }
        } 
    }
    SOCK_Close(CL_ISUP_Connection.backupInfo.sockInfo);
    CL_ISUP_Connection.backupInfo.sockInfo = NULL;
    THREAD_DeleteThread(&CL_ISUP_Connection.backupInfo.thrInfo.info);
    printf("Thread exiting for backup connection\n");
#ifdef WIN32
					return 0;
#else
                    return NULL;
#endif
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method pre intializes 
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs int if ITS_SUCCESS 
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int
CL_PreInitialize()
{
    int ret =0;

    /*primary initialization*/
    CL_ISUP_Connection.primaryInfo.thrInfo.func = PrimaryThreadFunction;
    CL_ISUP_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    CL_ISUP_Connection.primaryInfo.isUp = ITS_FALSE;
    CL_ISUP_Connection.primaryInfo.isInitialized = ITS_FALSE;
    CL_ISUP_Connection.primaryInfo.sockInfo = NULL;

    if (MUTEX_CreateMutex(&CL_ISUP_Connection.primaryInfo.readLock, 0)                  != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (MUTEX_CreateMutex(&CL_ISUP_Connection.primaryInfo.writeLock, 0)                 != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    /*Back up initialization*/
    CL_ISUP_Connection.backupInfo.thrInfo.func = BackupThreadFunction;
    CL_ISUP_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
    CL_ISUP_Connection.backupInfo.isUp = ITS_FALSE;
    CL_ISUP_Connection.backupInfo.isInitialized = ITS_FALSE;
    CL_ISUP_Connection.backupInfo.sockInfo = NULL;

    if (MUTEX_CreateMutex(&CL_ISUP_Connection.backupInfo.readLock, 0) 
        != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (MUTEX_CreateMutex(&CL_ISUP_Connection.backupInfo.writeLock, 0) 
        != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    /* Initialize registration info */
    CL_ISUP_Connection.regInfo.count = 0;
    memset(CL_ISUP_Connection.regInfo.mtp3, 0,  
           sizeof(CL_ISUP_Connection.regInfo.mtp3));

    /* Create Task Que for client */
    CL_ISUP_Connection.taskTrans.taskQue = EMLIST_Create();

    return ret;
}
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
 *      Returns int. 
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int
CL_Initialize(const char *host, int port, CL_CONNECTION_TYPE type,
                                              int conServattempts)
{
    int ret =0;
    if (host == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* update the global variable for server connection attempts */
    con_serv_attempts = conServattempts;
    
    if (type == CL_PRIMARY_CONNECTION)
    {
        if (CL_ISUP_Connection.primaryInfo.isInitialized == ITS_TRUE)
        {
            printf("Client already connected on this connection\n");
            return ITS_EINUSE;
        }

        memcpy(&CL_ISUP_Connection.primaryInfo.ipAddr, host, strlen(host));
        CL_ISUP_Connection.primaryInfo.port = port;

        ret = CL_Connect(&CL_ISUP_Connection.primaryInfo);
        if (ret == ITS_SUCCESS)
        {
            printf("Client successfully connected\n");
        }
        else if (ret == ITS_ENOSOCKET)
        {
            printf("Attempt to Connect to server failed check\n");
            printf("Server IP Addr %s and Port# %d\n",
                    CL_ISUP_Connection.primaryInfo.ipAddr,
                    CL_ISUP_Connection.primaryInfo.port);

            CL_CloseConnection(CL_PRIMARY_CONNECTION);
            return ret;
        }
        else
        {
            printf("We have major problem here ---\n");
            return ret;
        }

        CL_ISUP_Connection.primaryInfo.thrInfo.isRunning = ITS_TRUE;
        THREAD_CreateThread(&CL_ISUP_Connection.primaryInfo.thrInfo.info,
                            0,
                            CL_ISUP_Connection.primaryInfo.thrInfo.func,
                            NULL,
                            ITS_TRUE);
        CL_ISUP_Connection.primaryInfo.isInitialized = ITS_TRUE;
    }
    else if (type == CL_BACKUP_CONNECTION)
    {
        if (CL_ISUP_Connection.backupInfo.isInitialized == ITS_TRUE)
        {
            printf("Client already connected on this connection\n");
            return ITS_EINUSE;
        }

        memcpy(&CL_ISUP_Connection.backupInfo.ipAddr, host, strlen(host));
        CL_ISUP_Connection.backupInfo.port = port;

        ret = CL_Connect(&CL_ISUP_Connection.backupInfo);
        if (ret == ITS_SUCCESS)
        {
            printf("Client successfully connected\n");
        }
        else if (ret == ITS_ENOSOCKET)
        {
            printf("Attempt to Connect to server failed check\n");
            printf("Server IP Addr %s and Port# %d\n",
                    CL_ISUP_Connection.backupInfo.ipAddr,
                    CL_ISUP_Connection.backupInfo.port);

            CL_CloseConnection(CL_BACKUP_CONNECTION);
            return ret;
        }
        else
        {
            printf("We have major problem here ---\n");
            return ret;
        }

        if (CL_ISUP_Connection.backupInfo.sockInfo == NULL)
        {
            return ITS_ENOSOCKET;
        }

        CL_ISUP_Connection.backupInfo.thrInfo.isRunning = ITS_TRUE;
        THREAD_CreateThread(&CL_ISUP_Connection.backupInfo.thrInfo.info,
                            0,
                            CL_ISUP_Connection.backupInfo.thrInfo.func,
                            NULL,
                            ITS_TRUE);
        CL_ISUP_Connection.backupInfo.isInitialized = ITS_TRUE;
    }

    if (CL_ISUP_Connection.regInfo.count)
    {
        if (type == CL_BACKUP_CONNECTION)
        {
            CL_ReRegister(&CL_ISUP_Connection.backupInfo,
                          type,
                          CL_ISUP_Connection.regInfo.mtp3,
                          CL_ISUP_Connection.regInfo.count);
        }
        else
        {
            CL_ReRegister(&CL_ISUP_Connection.primaryInfo,
                          type,
                          CL_ISUP_Connection.regInfo.mtp3,
                          CL_ISUP_Connection.regInfo.count);
        }
    }

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method do the clean up job
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI void
CL_Terminate()
{
    CL_ISUP_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    CL_ISUP_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;

    MUTEX_DeleteMutex(&CL_ISUP_Connection.primaryInfo.readLock); 
    MUTEX_DeleteMutex(&CL_ISUP_Connection.primaryInfo.writeLock); 
    
    MUTEX_DeleteMutex(&CL_ISUP_Connection.backupInfo.readLock); 
    MUTEX_DeleteMutex(&CL_ISUP_Connection.backupInfo.writeLock); 

    EMLIST_Delete(CL_ISUP_Connection.taskTrans.taskQue);

    if (CL_ISUP_Connection.primaryInfo.sockInfo)
    {
        printf("Closing primary connection \n");
        CL_CloseConnection(CL_PRIMARY_CONNECTION);
    }

    if (CL_ISUP_Connection.backupInfo.sockInfo)
    {
        printf("Closing back up connection \n");
        CL_CloseConnection(CL_BACKUP_CONNECTION);
    }

    printf("------ Terminating client application -----\n");
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method registers the routing info with server.
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
CL_Register(ITS_HANDLE handle, MTP3_HEADER *hdr, int count)
{
    ITS_EVENT evt;
    int i =0, j = 1, ret =0;

    if (CL_ISUP_Connection.primaryInfo.isUp)
    {
        /* form a register event and send to server*/
        ITS_EVENT_INIT(&evt, CL_SRC_SERVER, (sizeof(MTP3_HEADER) * count + 1));

        evt.data[0] = CL_ISUP_REGISTER_EVENT;
        for(i = 0; i < count; ++i)
        {
            memcpy(&evt.data[j], &hdr[i], sizeof(MTP3_HEADER));
            j += sizeof(MTP3_HEADER);
        }

        ret = CL_WriteEvent((ITS_HANDLE*)&CL_ISUP_Connection.primaryInfo,  
                             &evt);
        if (ret != ITS_SUCCESS)
        {
            printf("CL_Register: Primary Connection Reg Failed Ret  %d\n", ret);
        }
    }
    else
    {
        printf("Registration failed, check the portno and IP addr for Prim Connection \n");
        ret = !ITS_SUCCESS;
    }

    if (CL_ISUP_Connection.backupInfo.isUp)
    {
        /* form a register event and send to server*/
        ITS_EVENT_INIT(&evt, CL_SRC_SERVER, (sizeof(MTP3_HEADER) * count + 1));

        evt.data[0] = CL_ISUP_REGISTER_BACKUP_EVENT;
        for(i = 0; i < count; ++i)
        {
            memcpy(&evt.data[j], &hdr[i], sizeof(MTP3_HEADER));
            j += sizeof(MTP3_HEADER);
        }

        ret = CL_WriteEvent((ITS_HANDLE*)&CL_ISUP_Connection.backupInfo,  
                             &evt);
    }
    else
    {
        printf("Registration failed, check the portno and IP addr for backup Connection \n");
        ret = !ITS_SUCCESS;
    }

    /* store the registration information so that we can re reregister
     * auotomatically when server comes up
     */
    if (CL_ISUP_Connection.primaryInfo.isUp 
       || CL_ISUP_Connection.backupInfo.isUp)
    {
        for(i = 0, j = CL_ISUP_Connection.regInfo.count; i < count; ++i)
        {
            memcpy(&CL_ISUP_Connection.regInfo.mtp3[j], &hdr[i], sizeof(MTP3_HEADER));
            ++j;
        }
        CL_ISUP_Connection.regInfo.count += i;
    }

    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method deregerters the routing info with the server
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
CL_Deregister(ITS_HANDLE handle, MTP3_HEADER *hdr, int count)
{
    ITS_EVENT evt;
    int i =0, j = 1;

    /* form a Deregister event and send to server for primary conn */
    ITS_EVENT_INIT(&evt, CL_SRC_SERVER, (sizeof(MTP3_HEADER) * count + 1));

    evt.data[0] = CL_ISUP_DEREGISTER_EVENT;
    
    for(i = 0; i < count; ++i)
    {
        memcpy(&evt.data[j], &hdr[i], sizeof(MTP3_HEADER));
        j += sizeof(MTP3_HEADER);
    }

    CL_WriteEvent((ITS_HANDLE*)&CL_ISUP_Connection.primaryInfo, &evt);

    /* form a Deregister event and send to server for backup conn */

    /* form a deregister event and send to server*/
    ITS_EVENT_INIT(&evt, CL_SRC_SERVER, (sizeof(MTP3_HEADER) * count + 1));

    evt.data[0] = CL_ISUP_DEREGISTER_BACKUP_EVENT;
    for(i = 0; i < count; ++i)
    {
        memcpy(&evt.data[j], &hdr[i], sizeof(MTP3_HEADER));
        j += sizeof(MTP3_HEADER);
    }

    CL_WriteEvent((ITS_HANDLE*)&CL_ISUP_Connection.backupInfo,
                         &evt);

    for (i = 0; i < count; i++)
    {
        for(j = 0; j < CL_ISUP_Connection.regInfo.count; ++j)
        {
            if (memcmp(&CL_ISUP_Connection.regInfo.mtp3[j], &hdr[i],
                                    sizeof(MTP3_HEADER)) == 0)
            {
                memmove(&CL_ISUP_Connection.regInfo.mtp3[j], 
                        &CL_ISUP_Connection.regInfo.mtp3[++j],
                        sizeof(MTP3_HEADER));    
                CL_ISUP_Connection.regInfo.count--;
                break;
            }
        }
    }
    return ITS_SUCCESS;
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
CLDLLAPI int
CL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int ret =0;
    CL_CONNECTION *conn = (CL_CONNECTION*)handle;

    if (evt == NULL || conn == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    ret = CL_GetEventFromTaskQue(&conn->taskTrans, evt);
    if (ret != ITS_SUCCESS)
    {
        printf("Failed to receive event from QUE ret %d\n",ret);
        return ret;
    }

    /* I want check if this event is for client or for App
     * if it is for client handle it and go again to ReadEvent()
     */
    if (evt->src == ITS_ISUP_SRC || evt->src == ITS_SCCP_SRC)
    {
    }
    else
    {
        CL_HandleClientEvent(evt);
    }

    return ITS_SUCCESS;
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles reserve cic response
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      ev    - ITS_EVENT * 
 *      reserveCic - ReserveCIC entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the return value ReserveCIC Api
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int
ISUP_ReceiveReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                 CL_ISUP_RESERVE_CIC_ENTRY *reserveCic)
{
    int counter =1;

    memcpy(&reserveCic->mtp3, &ev->data[1], sizeof(MTP3_HEADER));

    counter += sizeof(MTP3_HEADER);
    
    reserveCic->cic = 0;
    reserveCic->cic |= ev->data[counter++];
    reserveCic->cic |= ev->data[counter++] << 8;

    reserveCic->cic_state = ev->data[counter++];

    reserveCic->vcic =  ITS_GET_CTXT(&ev->data[counter]);
    counter += sizeof(ITS_CTXT);

    reserveCic->ret = 0;
    reserveCic->ret |= ev->data[counter++];
    reserveCic->ret |= ev->data[counter++] << 8;
    reserveCic->ret |= ev->data[counter++] << 16;
    reserveCic->ret |= ev->data[counter++] << 24;

    return (reserveCic->ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles unreserveCic response
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      ev    - ITS_EVENT * 
 *      unreserveCic - UnreserveCic Entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the return value UnReserveCIC Api
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
CLDLLAPI int
ISUP_ReceiveUnReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                   CL_ISUP_UNRESERVE_CIC_ENTRY *unreserveCic)
{
    int counter =1;

    memset(unreserveCic, 0, sizeof(CL_ISUP_UNRESERVE_CIC_ENTRY));

    memcpy(&unreserveCic->mtp3, &ev->data[1], sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);


    unreserveCic->cic |= ev->data[counter++];
    unreserveCic->cic |= ev->data[counter++] << 8;

    unreserveCic->ret = 0;
    unreserveCic->ret |= ev->data[counter++];
    unreserveCic->ret |= ev->data[counter++] << 8;
    unreserveCic->ret |= ev->data[counter++] << 16;
    unreserveCic->ret |= ev->data[counter++] << 24;

    return (unreserveCic->ret);
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
CLDLLAPI int
ISUP_ReceiveRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                               CL_ISUP_REG_ENTRY *regInfo)
{
    int counter =1;

    memcpy(&regInfo->mtp3, &ev->data[1], sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

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
CLDLLAPI int
ISUP_ReceiveDeRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                 CL_ISUP_REG_ENTRY *regInfo)
{
    int counter =1;

    memcpy(&regInfo->mtp3, &ev->data[1], sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

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
 *      This method closes the socket connection with server, this is for the
 *      user to close connection with one server and establish conn with new,
 *      or may be swap the connection ie primary to backup or vice-versa.
 *
 *  Input Parameters:
 *
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
CL_CloseConnection(CL_CONNECTION_TYPE type)
{
    if (type == CL_PRIMARY_CONNECTION)
    {
        CL_ISUP_Connection.primaryInfo.isUp = ITS_FALSE;
        CL_ISUP_Connection.primaryInfo.isInitialized = ITS_FALSE;
        CL_ISUP_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    }
    else if (type == CL_BACKUP_CONNECTION)
    {
        CL_ISUP_Connection.backupInfo.isUp = ITS_FALSE;
        CL_ISUP_Connection.backupInfo.isInitialized = ITS_FALSE;
        CL_ISUP_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
    }
    else
    {
        printf("\n Error::Unrecognised connection type %d\n", type);
        return !ITS_SUCCESS;
    }

    if (CL_ISUP_Connection.primaryInfo.isInitialized == ITS_FALSE &&
        CL_ISUP_Connection.backupInfo.isInitialized  == ITS_FALSE)
    {
        /* Reset registration info */
        CL_ISUP_Connection.regInfo.count = 0;
        memset(CL_ISUP_Connection.regInfo.mtp3, 0,  
               sizeof(CL_ISUP_Connection.regInfo.mtp3));
    }
    return ITS_SUCCESS;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *        Sends the state chanage event to stack
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *      This is the  idea this function works if app & stack are  same
 *      exe. When they are defferent this function defintion we will provide
 *      as part of client library.
 *  See Also:
 *****************************************************************************/
CLDLLAPI int
ITS_SendStateChangeEventToStack(ITS_NODE_STATE type)
{
    ITS_EVENT evt;

    ITS_EVENT_INIT(&evt, CL_SRC_SERVER, 3);
    evt.data[0] = ITS_STATE_CHANGE_EVENT;
    evt.data[1] = type;

    return CL_SendEvent(&CL_ISUP_Connection, &evt);
}

CLDLLAPI ITS_HANDLE __ISUP_Handle = (ITS_HANDLE)&CL_ISUP_Connection;
