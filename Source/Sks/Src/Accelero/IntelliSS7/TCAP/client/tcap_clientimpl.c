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
 * $Id: tcap_clientimpl.c
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
 * Revision 1.1  2003/10/07 12:46:08  sswami
 * TCAP multiple App binding Client Implementation
 *
 *
 ****************************************************************************/
#include <tcap_clientimpl.h>
#include <its_license_stubs.h>
#include <its_hash.h>
#include <its_mutex.h>
#include <stdlib.h>
#include <its_transports.h>
#include <its_ss7_trans.h>

extern ITS_MUTEX CL_WriteMutexLock;
extern ITS_MUTEX CL_ReadMutexLock;

static char* sync_data = "ISS7SSI";
static int   sd_len = 7;

ITS_USHORT did = 0;

SS7TRAN_Manager* ISS7_ANSI_Stack;
#define ISS7_Stack         ISS7_ANSI_Stack

int CL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite;
    ITS_USHORT tmp =0;

    if (CL_SockInfo == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* today I don't have to use handle, may be in future 
     * we might have to use
     */

    MUTEX_AcquireMutex(&CL_WriteMutexLock);

    nrite = SOCK_Write(CL_SockInfo, sync_data, sd_len); 
    if (nrite != sd_len)
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_SockInfo, (char *)evt->data, evt->len);

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&CL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }
   
    /* Free the event*/
    if (evt->data)
    {
        free(evt->data);
        evt->data =0;
    }
    MUTEX_ReleaseMutex(&CL_WriteMutexLock);
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
int CL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0;
    char buf;
    ITS_USHORT tmp =0;
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;

    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&CL_ReadMutexLock);

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
            info.sinfo = CL_SockInfo;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&CL_ReadMutexLock);
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

        ret = SOCK_Read(CL_SockInfo, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
            MUTEX_ReleaseMutex(&CL_ReadMutexLock);
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
    nread = SOCK_Read(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
    nread = SOCK_Read(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);

    evt->data = (ITS_OCTET *)malloc(evt->len);
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (evt->len)
    {
        nread = SOCK_Read(CL_SockInfo, (char *)evt->data, evt->len);

        if (nread != evt->len)
        {
            free(evt->data);
            evt->data = NULL;

            MUTEX_ReleaseMutex(&CL_ReadMutexLock);
            return (ITS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&CL_ReadMutexLock);
    return ITS_SUCCESS;
}

#if defined (ANSI)

SS7DLLAPI int TCAP_SendComponent_ANSI(ITS_HANDLE handle,
                                      ITS_HDR* hdr,
                                      TCAP_CPT* cpt)
{
    ITS_EVENT ev;
    int ret;

    ITS_EVENT_INIT(&ev, CL_APP_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
    ev.data[0] = ITS_TCAP_CPT;
    ITS_SET_CTXT(&ev.data[1], hdr->context.dialogue_id);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], cpt, sizeof(TCAP_CPT));

    /* Fill the event src as from application*/
    ev.src = CL_APP_TCAP_SRC;

    ret = CL_WriteEvent(handle, &ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }
    return ret;
}

SS7DLLAPI int
TCAP_SendDialogue_ANSI(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    ITS_EVENT ev;
    int ret; 

    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));
    ev.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&ev.data[1], hdr->context.dialogue_id);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], dlg, sizeof(TCAP_DLG));

    /* Fill the event src as from application*/
    ev.src = CL_APP_TCAP_SRC;

    ret = CL_WriteEvent(handle, &ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }
    return ret;
}

#if 0
/* Commented this has to be implemented */

SS7DLLAPI int
TCAP_AllocateDialogueId_ANSI_New(ITS_HANDLE h, ITS_CTXT* pdid, 
                                 MTP3_HEADER* mtp3)
{
    ITS_EVENT event;
    ITS_INT counter=0;

    ITS_EVENT_INIT(&event, CL_SRC_SERVER,  
                   10);

    printf("\n entered allocdid\n");
    event.data[counter++] = CL_TCAP_ALLOC_DID_REQ;
    memcpy(&event.data[1], mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.len = counter;

    /* Call Write Event */
    CL_WriteEvent(h, &event);
  
    while (!did) 
    {
    }
    *pdid = did;
    did = 0;
    return (ITS_SUCCESS);
}

#endif /* commented */

#endif /* ANSI */

#if defined (CCITT)
/* WRITE FOR ITU ALSO */
#endif

int CL_HandleClientEvent(ITS_EVENT *evt)
{
    if (evt->src == CL_SRC_SERVER)
    {
        if (evt->data[0] == CL_TCAP_ALLOC_DID_RESP)
        {
            did = 0;
            did |= evt->data[1];
            did |= evt->data[2] & (did << 8);
            printf("\n Got ALLOC DID %d\n", did);
        } 
    }
    else
    {
        printf("---Unexpected Client Msg received from server---\n");
    }
    return ITS_SUCCESS;
}
