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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: ansi-isup_ifc.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:30  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:05  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2  2005/04/06 10:32:06  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:53:31  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.10.2.1.6.1  2004/01/05 10:04:50  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.10.2.1.2.1  2003/09/13 06:23:33  akumar
 * LOG: Msg based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.10.2.1  2003/05/07 10:21:54  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.4  2003/04/28 15:28:08  sjaddu
 * LOG: Event TERM related changes.
 * LOG:
 * LOG: Revision 8.3  2003/04/16 06:08:10  akumar
 * LOG: Invalid optional param related changes and ITS_EVENT_TERM removal.
 * LOG:
 * LOG: Revision 8.2  2003/03/26 12:11:20  ssingh
 * LOG: Changed done as per ISUPPending List:
 * LOG: ansi-isup_alarms.c  : New Alarms added for HandleMTP3MgmtMsg.
 * LOG: ansi-isup_context.c : Function calls for DPC and Remote ISUP status.
 * LOG:                     : Indication sent; if msg received is on BAD Cic.
 * LOG:                     : Alarms for PAUSE/RESUME/STATUS.
 * LOG: ansi-isup_ifc.c     : Changes to incorporate CIC_INFO changes.
 * LOG: ansi-sprc.c         : CIC_INFO/CIC_MSG_INFO related changes.
 * LOG:                     : SendConfToApp removed, SendIsupIndToApp added.
 * LOG: isup_data.c         : Modified to include CIC_INFO/CIC_MSG_INFO changes.
 * LOG: its-ansi-isup.c     : CIC_INFO related changes.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:22  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.10  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.9  2003/01/21 15:34:18  vnitin
 * LOG: Tandem Port for ISUP, mostly type casting
 * LOG:
 * LOG: Revision 7.8  2003/01/17 15:27:18  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.7  2002/12/20 23:40:47  sjaddu
 * LOG: msg_desc has to get from Variant class.
 * LOG:
 * LOG: Revision 7.6  2002/12/19 16:57:08  sjaddu
 * LOG: FindPcic removed in SendISUPEvent.
 * LOG:
 * LOG: Revision 7.5  2002/11/20 10:40:35  ssingh
 * LOG: Added fix to Support repeated parameters occurance in message(sent).
 * LOG:
 * LOG: Revision 7.4  2002/11/07 05:25:09  ssingh
 * LOG: Changed licensable API from ITU_ISUP to ANSI_ISUP as of ANSI type.
 * LOG:
 * LOG: Revision 7.3  2002/10/26 12:02:21  ssingh
 * LOG: Updated the MTP3Encode for proper execution.
 * LOG:
 * LOG: Revision 7.2  2002/10/25 13:46:43  ssingh
 * LOG: Code changes done as a part of BUG 141-to-146 fixing.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.4  2002/07/12 14:25:11  mmiers
 * LOG: Minor cleanups
 * LOG:
 * LOG: Revision 6.3.2.4  2002/07/11 13:36:36  hbalimid
 * LOG: Modified functionality for UCIC.
 * LOG:
 * LOG: Revision 6.3.2.3  2002/07/10 19:39:46  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.3.2.2  2002/06/29 20:16:00  ssharma
 * LOG: Put CIC in event in addition to VCIC.
 * LOG:
 * LOG: Revision 6.3.2.1  2002/06/28 23:37:58  hbalimid
 * LOG: Added IntelliNet Receive Event.
 * LOG:
 * LOG: Revision 6.3  2002/05/20 21:00:33  ssharma
 * LOG: Fix NT build after merge from PR6.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:18:58  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5.2.1  2002/04/18 18:52:27  ssanyal
 * LOG: First shot at ANSI ISUP
 * LOG:
 * LOG: Revision 5.5  2002/02/13 21:19:14  mmiers
 * LOG: Finish up the ISUP integration.
 * LOG:
 * LOG: Revision 5.4  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:19:54  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:26  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:02  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:21  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/08/26 23:44:52  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.2  1999/05/27 15:52:45  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:40  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.4  1999/03/16 20:58:28  mmiers
 * LOG:
 * LOG:
 * LOG: Fix interface names, start ITU TCAP.
 * LOG:
 * LOG: Revision 1.3  1998/10/15 01:19:10  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.2  1998/06/17 21:32:28  mmiers
 * LOG: Get Vendor straightened out.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:31  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 19:57:02  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_license.h>
#include <its_transports.h>
#include <its_assertion.h>

#ident "$Id: ansi-isup_ifc.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/isup.h>
#include <isup_variants.h>

#include "isup_intern.h"  

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method allocates the next available dialogue id for the user.
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
 *
 *  Notes:
 *      This method should be used for originating transactions ONLY
 *      (not that the user has visibility into received transactions).         
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_AllocateCIC_ANSI(ITS_SS7_HANDLE handle,
                            ITS_USHORT *cic)
{
    return (ITS_ENOMSGSPACE);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a generic ISUP message. Event will have
 *      the format "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg",
 *      required by MTP3.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message                
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Congestion level in outgoing REL
 *                           # 488          related changes.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_SendISUPEvent_ANSI(ITS_HANDLE handle, ITS_OCTET type,
                              ITS_HDR *hdr, ITS_ISUP_IE *ies, int ieCount,
                              ISUP_MSG_DESC *desc)                            
{
    ITS_EVENT ev;
    int ret = ITS_SUCCESS;
    int index = 0, i, j;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0;
    ISUP_OPC_DPC_INFO config_info;
    MTP3_HEADER *mtp3 = NULL;
    ITS_ISUP_IE temp_ies[ITS_MAX_ISUP_IES];
    ISUP_MSG_DESC *msg_desc;

    /*
     * a) License Verification, then
     * b) ISUP msg Check.
     */
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_ISUP))
    {
        return ITS_ENOLICENSE;                                                 
    }

    /* find the routing label, if present */
    for (i = 0, j = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_ROUTING_LABEL)
        {
            mtp3 = &ies[i].param_data.routingLabel;
        }
        else
        {
            temp_ies[j++] = ies[i];
        }
    }
    if (mtp3 == NULL)
    {
        /* FIXME:Else, we can use a default address if only one remote end
         * point. Check if there is only one DPC configured, then use it.
         * Needs Size() functions in isup_data.c */
        return ITS_ENOADDRESS;
    }                                                                          

    /* Get ISUP_DPC_OPC_INFO for variant info & outgoing mtp3_header */
    ret = ISUP_FindOpcDpc(*mtp3, &config_info, ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("INTELLINET_SendISUPEvent_ANSI():\nBad Config "
                    "for MsgType 0x%02x. cic 0x%x.\n", type, hdr->context.cic));

        return ITS_ENOTCONFIG;                                                 
    }

    /* Check the Message Type */
    if (!VAR_IsMsgSupported( config_info.isup_var_class, type ))
    {
        ISUP_ERROR(("INTELLINET_SendISUPEvent_ANSI():\nBad Message Type "
                    "0x%02x. cic 0x%x.\n", type, hdr->context.cic));

        ISUP_ReleaseOpcDpc(&config_info);
        return ITS_EINVISUPMSGTYPE;
    }

   /* Get MSG_DESC from Variant record */
    msg_desc = VAR_GetMsgDescription( config_info.isup_var_class, type );
    if (msg_desc == NULL)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ITS_ENOTCONFIG;
    }

    ret = ISUP_MessageSanityCheck_ANSI(type, temp_ies, j, msg_desc);           
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ret;
    }

    if (type == ISUP_MSG_REL)
    {
       ITS_OCTET   locCongLevel   = AUTO_CONGESTION_OFF;
       ITS_BOOLEAN congIePresent  = ITS_FALSE;

       /* Check for Local Congestion Present */
       if (ANSI_ISUP_conglevel1Found || ANSI_ISUP_conglevel2Found)
       {
          if (ANSI_ISUP_conglevel1Found)
          {
             locCongLevel = AUTO_CONGESTION_LEVEL1;
          }
          else if (ANSI_ISUP_conglevel2Found)
          {
             locCongLevel = AUTO_CONGESTION_LEVEL2;
          }

          /* find for ACL IE present */
          for (i = 0; i < ieCount; i++)
          {
              if (ies[i].param_id == ISUP_PRM_AUTO_CONGEST_LEVEL)
              {
                  congIePresent = ITS_TRUE;

                  /* Update congestion level in IE */
                  ies[i].param_data.autoCongestionLevel.level = locCongLevel;
              }
          }

          if (congIePresent == ITS_FALSE)
          {
              /* Add ACL IE with proper local congestion level */
              ies[ieCount].param_id = ISUP_PRM_AUTO_CONGEST_LEVEL;
              ies[ieCount].param_length = 1;
              ies[ieCount].param_data.autoCongestionLevel.level = locCongLevel;
              ieCount++;
          }
       }
    }


    /* ISUP_MTP3Encode_ANSI(); */
    memset( (char *)data, 0, ISUP_MAX_MSG_LEN );
    ret = ISUP_MTP3Encode_ANSI( data, &len, type, ies, ieCount,
                                 config_info.isup_var_class );
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ret;
    }

    ISUP_ReleaseOpcDpc(&config_info);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT( (&ev), (TRANSPORT_INSTANCE(handle)),
                           (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len) );
                                                                              
    /* Fill in MTP3 Message Type */
    ev.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy( (char *)&ev.data[index], (char *)mtp3, sizeof(MTP3_HEADER_ANSI) );
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    ev.data[index++] = (ITS_OCTET)(hdr->context.cic & 0xFFU);
    ev.data[index++] = (ITS_OCTET)((hdr->context.cic >> 8) & 0xFFU);

    /* Fill in the ISUP message type */
    ev.data[index++] = type;

    /* Fill in Encoded ISUP message data */
    memcpy( (char *)&ev.data[index], (char *)data, len );

    ret = TRANSPORT_PutEvent(ITS_ISUP_ANSI_SRC, &ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function decodes a generic ISUP message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the pointer to the ITS_EVENT received by the application,
 *           containing the ISUP message and related data
 *      desc - the format of the message that is to be decoded (not used with
 *             new implementation)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *                                                                             
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The format of the event received by the application is:
 *        ISUPMsgType:CIC:MTP3_HEADER:EncodedISUPMsg.
 *
 *      The input parameter 'desc' is obsolete. The ISUP_MSG_DESC is obtained
 *      from internal configuration data maintained by the stack, per variant.
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_ReceiveISUPEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                 ITS_HDR *hdr,
                                 ITS_ISUP_IE *ies, int *ieCount,
                                 ISUP_MSG_DESC *desc)
{
    int ret = 0, index = 0;
    ITS_USHORT cic = 0, paramlen = 0;
    ISUP_OPC_DPC_INFO config_info;
    MTP3_HEADER mtp3;
    MTP3_HEADER reverse_mtp3;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_ISUP))
    {
        return ITS_ENOLICENSE;
    }
    *ieCount = 0;
    paramlen = (ITS_USHORT)(ev->len - sizeof(ITS_OCTET) - sizeof(ITS_CTXT)
                       - sizeof(ITS_USHORT) - sizeof(MTP3_HEADER_ANSI));
    index = ev->len - paramlen;

    memcpy(&mtp3, &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)
                            + sizeof(ITS_USHORT)], sizeof(MTP3_HEADER));

    MTP3_RL_SET_DPC_VALUE_ANSI(reverse_mtp3.label,
                                MTP3_RL_GET_OPC_VALUE_ANSI(mtp3.label));
    MTP3_RL_SET_OPC_VALUE_ANSI(reverse_mtp3.label,
                                MTP3_RL_GET_DPC_VALUE_ANSI(mtp3.label));
    reverse_mtp3.sio = mtp3.sio;


    /* Get cic from event */
    cic |= ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)];
    cic |= (ev->data[sizeof(ITS_OCTET) + sizeof(ITS_OCTET) + sizeof(ITS_CTXT)] << 8);
                                                                              
    /* Get OPC_DPC configuration for access to Variant info. */
    ret = ISUP_FindOpcDpc(reverse_mtp3, &config_info, ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }

    hdr->type = ITS_ISUP;
    hdr->context.cic = cic;

    /* Need to do a Decode as TLV style is not being used. */
    /* ISUP_MTP3Decode_ANSI(); */
    ret = ISUP_MTP3Decode_ANSI( &ev->data[index], paramlen, ev->data[0], ies,
                                 ieCount, config_info.isup_var_class );
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ret;
    }                                                                          

    /* Finally, copying MTP3 Header. */
    ies[*ieCount].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[*ieCount].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[*ieCount].param_data.routingLabel, &mtp3, sizeof(MTP3_HEADER));

    (*ieCount)++;

    ISUP_ReleaseOpcDpc(&config_info);
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and a generic ISUP message in the SS7 wire format.
 *
 *  Input Parameters:
 *      type - the ISUP message type to encode
 *      ies - the information elements that make up the message                
 *      ieCount - the number of information elements
 *      isup_variant - the variant specific info for the relevant OPC-DPC pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - a pointer to the beginning of the encoded byte stream
 *      len - a pointer containing the number of bytes in the encoded byte
 *            stream pointed to by 'data'.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      ISUP_MTP3Decode_ANSI(ITS_OCTET *data, ITS_USHORT len,
 *                            ITS_OCTET type, ITS_ISUP_IE *ies, int *ieCount,
 *                            ISUP_OPC_DPC_INFO *config_info);                 
 *
 ****************************************************************************/
int
ISUP_MTP3Encode_ANSI(ITS_OCTET *data, ITS_USHORT *len, ITS_OCTET type,
                     ITS_ISUP_IE *ies, int ieCount, ITS_Class isup_variant)
{
    int i, j, offset, evoffset, lastVarOffset;
    ITS_ISUP_IE* ieRef[ITS_MAX_ISUP_IES];
    ITS_BOOLEAN haveOpts = ITS_FALSE, sawOpts = ITS_FALSE;
    int optPtr = 0;
    int ptrTableSize = 0;
    ITS_OCTET *margs, *vargs, *oargs;
    int nmargs = 0, nvargs = 0, noargs = 0;
    ISUP_MSG_DESC *desc = NULL;
    ITS_BOOLEAN msgIsPAM = ITS_FALSE;
    ITS_OCTET msgTypeInPAM = 0x00;
    int startIndex = 0;
#if defined(LOCAL_DEBUG)
    int q;
#endif                                                                         

    /* sanity */
    if (ieCount > ITS_MAX_ISUP_IES)
    {
        return (ITS_EOVERFLOW);
    }

    /* Get MSG_DESC from Variant record */
    desc = VAR_GetMsgDescription( isup_variant, type );
    if (desc == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    margs = desc->mArgs;
    nmargs = desc->nmArgs;

    vargs = desc->vArgs;
    nvargs = desc->nvArgs;

    oargs = desc->oArgs;
    noargs = desc->noArgs;                                                     

    /* Check if msg Type is PAM */
    if (type == ISUP_MSG_PAM)
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
    for (j = startIndex; j < ieCount; j++)
    {
        for (i = 0; i < noargs; i++)
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

    /* copy them in.   */
    /* evoffset starts at 0 */
    evoffset = 0;

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
        memcpy(&data[evoffset], &ieRef[i]->param_data, ieRef[i]->param_length);
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
        data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
        lastVarOffset += ieRef[nmargs + i]->param_length + 1;                  
        evoffset++;
    }

    /* if we have *any* optionals, build pointer to that */
    if (haveOpts)
    {
        data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
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

    /* This has put in the else part of
     * next check as in case of no OPT parameters
     * EOP is not required as per specs
     * terminate variable list *
    if (noargs != 0)
    {
        data[evoffset] = ISUP_PRM_EOP;
        evoffset++;
    }
    */

    if (haveOpts && !sawOpts)
    {
        data[optPtr] = 0;
    }
    else
    {
        if(noargs != 0)
        {
           data[evoffset] = ISUP_PRM_EOP;
           evoffset++;
        }
    }

    /* set final length */
    *len = (ITS_USHORT)evoffset;

    return ITS_SUCCESS;
}                                                                              

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function converts an encoded byte stream (received from MTP3)
 *      containing the parameters into an array of IEs.
 *
 *  Input Parameters:
 *      data - a pointer to the beginning of the encoded byte stream
 *      len - indicates the number of bytes in the encoded byte stream pointed
 *            to by 'data'.
 *      type - the ISUP message type to decode
 *      isup_variant - the variant specific info for the relevant OPC-DPC pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Return Value:                                                              
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      ISUP_MTP3Encode_ANSI(ITS_OCTET *data, ITS_USHORT *len,
 *                            ITS_OCTET type, ITS_ISUP_IE *ies, int ieCount,
 *                            ISUP_OPC_DPC_INFO *config_info);
 *
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_MTP3Decode_ANSI(ITS_OCTET *data, ITS_USHORT len, ITS_OCTET mType,
                     ITS_ISUP_IE *ies, int *ieCount, ITS_Class isup_variant)
{
    int index = 0, i, j = 0;
    ITS_OCTET *ptr;
    ITS_OCTET *margs, *vargs, *oargs;
    int nmargs = 0, nvargs = 0, noargs = 0;
    ITS_BOOLEAN paramFound = ITS_FALSE;
    ITS_USHORT newlen = 0;

    ISUP_MSG_DESC *desc = NULL;                                                
    __ISUP_ComputeMSizeProc computeMSize = NULL;

#if defined(LOCAL_DEBUG)
    int q;
#endif

    /* Get MSG_DESC from Variant record */
    desc = VAR_GetMsgDescription( isup_variant, mType );
    if (desc == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    margs = desc->mArgs;
    nmargs = desc->nmArgs;
    vargs = desc->vArgs;
    nvargs = desc->nvArgs;
    oargs = desc->oArgs;
    noargs = desc->noArgs;

                                                                            
    /* Get ComputeMSize from Variant info. */
    computeMSize = VAR_ComputeMsize( isup_variant );

    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        ies[i].param_id = margs[i];
        if (computeMSize != NULL)
        {
            ies[i].param_length = (ITS_OCTET)(*computeMSize)(isup_variant, margs[i]);
        }
        else
        {
            ies[i].param_length = ISUP_ComputeMSize(margs[i]);
        }

        /* ISUP_ComputeMSize() return value should > 0,
         * otherwise there is bug */
        ITS_C_ASSERT(ies[i].param_length > 0);

        memcpy(&ies[i].param_data.pad.buf,
               &data[index], ies[i].param_length);                             

        index += ies[i].param_length;
    }

    newlen = index;

    /* get the variable mandatories */
    ptr = &data[index];

    for (i = 0; i < nvargs; i++)
    {
        ITS_OCTET *tmp;

        ies[i + nmargs].param_id = vargs[i];

        /* compute the pointer */
        tmp = ptr + *ptr;
        ies[i + nmargs].param_length = *tmp;
        newlen += (*tmp + 2);
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
        newlen++;

        /*assert((ptr - data) <= ev->len);*/

        while (*ptr != ISUP_PRM_EOP)
        {
            paramFound = ITS_FALSE;
            for (j =0; j < noargs ;++j)
            {
                if (*ptr == desc->oArgs[j])
                {
                    paramFound = ITS_TRUE;
                }
            }
            if(paramFound)
            {
                ies[i + nmargs + nvargs].param_id = *ptr;
                ptr++;
                ies[i + nmargs + nvargs].param_length = *ptr;
                newlen += (*ptr + 2);
                ptr++;

                memcpy(&ies[i + nmargs + nvargs].param_data.pad.buf,
                       ptr, ies[i + nmargs + nvargs].param_length);                
                ptr += ies[i + nmargs + nvargs].param_length;
                i++;
            }
            else
            {
                ies[i + nmargs + nvargs].param_id = ISUP_PRM_PAD_BUF;
                ies[i + nmargs + nvargs].param_length = len - newlen;
                memcpy(&ies[i + nmargs + nvargs].param_data.pad.buf,
                       ptr, len - newlen);
                *ieCount = nmargs + nvargs + i + 1;
                return ITS_EPARAMPRSNT;
            }

            /*assert((ptr - ev->data) <= ev->len);*/
        }
    }

    /* set the return ieCount. */
    *ieCount = nmargs + nvargs + i;

    return ITS_SUCCESS;
}                                                                              

