/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *
 *  ID: $Id: remote_isup_ifc.cpp,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:06  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:05  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.1  2001/03/21 20:19:00  hxing
 * LOG: Commit remote isup lib files
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <iostream>

#include <its.h>
#include <its_transports.h>
#include <its_assertion.h>

#include <remote_isup.h>

#ifdef __cplusplus
extern "C"
{
#endif


using namespace std;

CALLBACK_Manager *ISUP_ManagementCallbacks = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
ISUP_SendEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
               ITS_ISUP_IE *ies, int ieCount,
               ISUP_MSG_DESC *desc)
{
    ITS_EVENT           event;
    
    ITS_EVENT_INIT(&event, ITS_ISUP_SRC, MTP2_MAX_MSG_SIZE);

    if(ISUP_EncodeMTP3(ies, ieCount, type, &event, hdr, desc) != ITS_SUCCESS)
    {        
        return !ITS_SUCCESS;        
    }

    if (TRANSPORT_PutEvent(2, &event) != ITS_SUCCESS)
    {
        printf("Transport_PutEvent failed\n");

        return !ITS_SUCCESS;
    }

    //ITS_EVENT_TERM(&event);

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
ISUP_ReceiveEvent(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                  ITS_ISUP_IE *ies, int *ieCount,
                  ISUP_MSG_DESC *desc)
{
    int ret;


    if ((ret = ISUP_DecodeMTP3(ies, ieCount, ev, desc)) != ITS_SUCCESS)
    {
        return (ret);
    }

    hdr->type = ITS_ISUP;
    hdr->context.conref = (ev->data[1] << 8) | ev->data[2];

    return (ITS_SUCCESS);
}



/*
 * convert an array of IEs to a ITS_OCTET buf for MTP3.
 */
int 
ISUP_EncodeMTP3(ITS_ISUP_IE *ies, int ieCount, ITS_OCTET msgType,
                ITS_EVENT *event, ITS_HDR *hdr, ISUP_MSG_DESC* desc)
{
    int i, j, offset, evoffset, lastVarOffset;

    ITS_ISUP_IE* ieRef[ITS_MAX_ISUP_IES];

    ITS_BOOLEAN haveOpts = ITS_FALSE, sawOpts = ITS_FALSE;
    int optPtr = 0;

    int ptrTableSize = 0;

    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;

    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;

    ITS_OCTET *oargs = desc->oArgs;
    int noargs = desc->noArgs;

    ITS_BOOLEAN msgIsPAM = ITS_FALSE;
    ITS_OCTET msgTypeInPAM = 0x00;
    int startIndex = 0;
    ITS_USHORT len = 0;
    ITS_OCTET data[MAX_ISUP_DATA_LEN];
    MTP3_HEADER mtp3Hdr;
    ITS_UINT dpc, opc;
    ITS_USHORT CIC = hdr->context.CIC;

    printf("ISUP_EncodeMTP3: hdr->context.CIC = %d\n", CIC);

    memset(&mtp3Hdr, 0, sizeof(MTP3_HEADER));

    /* sanity */
    if (ieCount > ITS_MAX_ISUP_IES)
    {
        return (ITS_EOVERFLOW);
    }

    /* Check if msg Type is PAM */
    if (msgType == ISUP_MSG_PAM)
    {
        if (ies[0].param_id == ISUP_PRM_MSG_IN_PAM)
        {
            msgTypeInPAM = ies[0].param_data.msgTypeInPAM;
            msgIsPAM = ITS_TRUE;
            startIndex++;
        }
        else
        {
            return (ITS_EMISSMAND);
        }
    }

    /* start at zero */
    offset = 0;

    /* find the fixed mandatory */
    for (i = 0; i < nmargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the variable mandatory */
    for (i = 0; i < nvargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == vargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extras */
    while (offset < ieCount)
    {
        ieRef[offset] = NULL;
        offset++;
    }
        
    /* set the message type */
    data[0] = msgType;
    
    evoffset = sizeof(ITS_OCTET);    

    /*
     * Before putting in the params, if the Msg is the PAM, before the params
     * we must have the msg type in the PAM
     */
    if (msgIsPAM)
    {
        data[evoffset] = msgTypeInPAM;
        evoffset++;
    }

    /* copy in the mandatories */
    for (i = 0; i < nmargs; i++)
    {
        memcpy(&data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* do we have any optionals? */
    if (noargs > 0)
    {
        haveOpts = ITS_TRUE;
    }

    /* compute the size of the ptr table */
    ptrTableSize = nvargs + (haveOpts ? 1 : 0);
    lastVarOffset = 0;

    /* build the ptr table for mandatory variable args */
    for (i = 0; i < nvargs; i++)
    {
        data[evoffset] = ptrTableSize + lastVarOffset - i;
        lastVarOffset += ieRef[nmargs + i]->param_length + 1;
        evoffset++;
    }

    /* if we have *any* optionals, build pointer to that */
    if (haveOpts)
    {
        data[evoffset] = ptrTableSize + lastVarOffset - i;
        optPtr = evoffset;
        evoffset++;
    }

    /* copy in the variable mandatories */
    for (i = 0; i < nvargs; i++)
    {
        data[evoffset] = ieRef[nmargs + i]->param_length;
        evoffset++;

        memcpy(&data[evoffset], &ieRef[nmargs + i]->param_data,
               ieRef[nmargs + i]->param_length);

        evoffset += ieRef[nmargs + i]->param_length;
    }

    /* copy in the optionals */
    for (i = nmargs + nvargs; i < ieCount; i++)
    {
        if (ieRef[i] == NULL)
        {
            continue;
        }

        sawOpts = ITS_TRUE;

        data[evoffset] = ieRef[i]->param_id;
        evoffset++;

        data[evoffset] = ieRef[i]->param_length;
        evoffset++;

        memcpy(&data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* terminate variable list */
    if (noargs != 0)
    {
        data[evoffset] = ISUP_PRM_EOP;
        evoffset++;
    }

    if (haveOpts && !sawOpts)
    {
        data[optPtr] = 0;
    }

    /* set final length */
    len = evoffset;

    /* get mtp3Hdr */
    mtp3Hdr.sio = MTP3_SIO_ISUP;
    
    /* get the dpc */    
    dpc = 257;  // TODO: not hardcode
    printf("DestPointCode: %d.%d.%d,  0x%04x,    %d\n", 
            (int) ((dpc >> 16) & 0xff), 
            (int) ((dpc >> 8) & 0xff), 
            (int) (dpc & 0xff),
            (int) dpc, (int) dpc);

    /* get the opc */    
    opc= 3;  // TODO: not hardcode
    printf("OrigPointCode: %d.%d.%d,   0x%04x,    %d\n", 
            (int) ((opc >> 16) & 0xff), 
            (int) ((opc >> 8) & 0xff), 
            (int) (opc & 0xff),
            (int) opc, (int) opc);

    /* set the dpc, opc (U32) */
    MTP3_RL_SET_DPC_VALUE(mtp3Hdr.label, dpc);   
    MTP3_RL_SET_OPC_VALUE(mtp3Hdr.label, opc);

    /* set the sls = the four least significant bits of the CIC */
    MTP3_RL_SET_SLS(mtp3Hdr.label, CIC & 0x000F);

    event->data[0] = MTP3_MSG_USER_DATA;
    
    memcpy(&event->data[1], &mtp3Hdr, sizeof(MTP3_HEADER));

    /* copy in the (rest of)CIC */
    event->data[1 + sizeof(MTP3_HEADER)] = (CIC >> 4) & 0xFF;
    event->data[1 + sizeof(MTP3_HEADER) + 1] = (CIC >> 12) & 0x0F; 
    
    memcpy(&event->data[1 + sizeof(MTP3_HEADER) + 2], data, len);

    event->len = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + 
                 sizeof(ITS_USHORT) + len;
    event->src = ITS_ISUP_SRC;

    /*   -------------------------------------------------
     *   | 1 | MTP3_HEADER | CIC | ISUP message          |
     *   -------------------------------------------------
     *     1   sizeof(^)      2        len
     */

    return (ITS_SUCCESS);
}


int 
ISUP_DecodeMTP3(ITS_ISUP_IE *ies, int *ieCount, ITS_EVENT *ev,
                ISUP_MSG_DESC* desc)
{
    int evoffset = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) +
                   sizeof(MTP3_HEADER) + sizeof(ITS_OCTET);
    ITS_OCTET *ptr;
    int i;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
#if 0 /* this is a placeholder */
    ITS_OCTET *oargs = desc->oArgs;
#endif
    int noargs = desc->noArgs;
    
    if (ev->len<(sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)))
    {
        return (ITS_ENOMSG);
    }

    if (ev->data[0] != MTP3_MSG_USER_DATA)
    {
        return (ITS_ENOMSG);
    }    

    /* copy the MTP3 header over */
    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &ev->data[sizeof(ITS_OCTET)],
           sizeof(MTP3_HEADER));

    /* avoid adding +1 everywhere */
    ies++;
    
    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        ies[i].param_id = margs[i];
        ies[i].param_length = ISUP_ComputeMSize(margs[i]);

        /* ComputeMSize() return value should > 0, otherwise there is bug */
        ITS_C_REQUIRE(ies[i].param_length > 0);

        memcpy(&ies[i].param_data.pad.buf,
               &ev->data[evoffset], ies[i].param_length);

        evoffset += ies[i].param_length;
    }

    /* get the variable mandatories */
    ptr = &ev->data[evoffset];

    for (i = 0; i < nvargs; i++)
    {
        ITS_OCTET *tmp;

        ies[i + nmargs].param_id = vargs[i];

        /* compute the pointer */
        tmp = ptr + *ptr;
        ies[i + nmargs].param_length = *tmp;
        tmp++;

        memcpy(&ies[i + nmargs].param_data.pad.buf,
               tmp, ies[i + nmargs].param_length);

        ptr++;
    }

    /* get the optionals, if any */
    i = 0;
    if (noargs && *ptr)
    {
        ptr += *ptr;

        ITS_C_REQUIRE((ptr - ev->data) <= ev->len);

        while (*ptr != ISUP_PRM_EOP)
        {
            ies[i + nmargs + nvargs].param_id = *ptr;
            ptr++;
            ies[i + nmargs + nvargs].param_length = *ptr;
            ptr++;

            memcpy(&ies[i + nmargs + nvargs].param_data.pad.buf,
                   ptr, ies[i + nmargs + nvargs].param_length);

            ptr += ies[i + nmargs + nvargs].param_length;
            i++;

            ITS_C_REQUIRE((ptr - ev->data) <= ev->len);
        }
    }

    /* set the return ieCount.  The '1' is for the MTP3 header */
    *ieCount = nmargs + nvargs + i + 1;

    return (ITS_SUCCESS);
}



ITS_OCTET 
GetISUPMsgType(ITS_EVENT& ev)
{
    /*   -------------------------------------------------
     *   | 1 | MTP3_HEADER | CIC | ISUP message          |
     *   -------------------------------------------------
     *     1   sizeof(^)      2        len
     */
    
    int offset = 1 + sizeof(MTP3_HEADER) + 2;

    return ev.data[offset];
}

//
//  Dump ITS_EVENT
//
void DumpITSEvent(ITS_EVENT* ev)
{
    int i;

    cout << "\nEvent came from: " << ev->src << endl;
    cout << "The length was:  " << ev->len << endl;

    for (i = 0; i < ev->len; i++)
    {
        printf("%02x ", ev->data[i]);
        if (!((i+1) % 20))
        {
            printf("\n");
        }
    }
    if ((i+1) % 20)
    {
        printf("\n");
    }
}

#ifdef __cplusplus
}
#endif