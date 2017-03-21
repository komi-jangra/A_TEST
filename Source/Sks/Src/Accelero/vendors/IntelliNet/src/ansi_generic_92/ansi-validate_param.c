/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2001,2002 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: ansi-validate_param.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/08 06:21:34  ssingh
 * LOG: ISUP bug fix propagation (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.13  2005/03/21 13:53:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.16.2.5.2.1.12.2  2004/12/29 14:35:54  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.16.2.5.2.1.12.1  2004/12/06 13:34:50  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.16.2.5.2.1  2004/01/05 10:10:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.16.2.3.2.3  2003/12/03 07:11:43  ssingh
 * LOG: Bug #692 (WAIT_FOR_UBA state not cleared when RSC/GRS
 * LOG: sent out from Application) fixed.
 * LOG:
 * LOG: Revision 7.16.2.3.2.2  2003/11/24 06:36:29  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.16.2.3.2.1  2003/09/13 06:27:00  akumar
 * LOG: Msg Based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.16.2.3  2003/05/13 06:09:00  ssingh
 * LOG: CompareCGBAWithCGB and CompareCGUAWithCGU modified.
 * LOG:
 * LOG: Revision 7.16.2.2  2003/05/07 10:38:00  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.12  2003/05/06 13:55:52  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.11  2003/05/06 12:24:33  ssingh
 * LOG: Changes done for proper DEBUG_TRACE display, when Unexpected
 * LOG: CGBA/CGUA received from Network.
 * LOG:
 * LOG: Revision 8.10  2003/04/24 14:13:26  sswami
 * LOG: Bug #317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.9  2003/04/17 05:21:50  ssingh
 * LOG: __ISUP_BlockingMGBRToBLR/__ISUP_UnbockingMGBRToBLR modified; MACRO used.
 * LOG:
 * LOG: Revision 8.8  2003/04/16 06:17:28  ssingh
 * LOG: ISUP_ReleaseCicMsgBuf related changes done to prevent
 * LOG: if msg-poniter getting NULL after Releasing for MsgBuf.
 * LOG:
 * LOG: Revision 8.7  2003/04/04 12:01:20  ssingh
 * LOG: Handling of CGB/CGU is modified.
 * LOG:
 * LOG: Revision 8.4  2003/03/26 12:29:32  ssingh
 * LOG: Modified CIC_INFO changes incorporated. ISUPPending List Items done.
 * LOG:
 * LOG: Revision 8.3  2003/03/15 13:18:08  ssingh
 * LOG: Changes done in existing files to support CRM/CRA messaging.
 * LOG:
 * LOG: Revision 8.2  2003/03/14 09:37:11  ssingh
 * LOG: Changed done to prop fixes for BUG# 245,237,226 from PR6.3.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.16  2003/01/29 19:08:21  sjaddu
 * LOG: Added one more state for CRI.
 * LOG:
 * LOG: Revision 7.15  2003/01/27 15:38:01  ssingh
 * LOG: Added changes for cgb/cgu received from Network with
 * LOG: invalid Blocking type. Changes done for Comparing received CGBA
 * LOG: with CGB and received CGUA with CGU.
 * LOG:
 * LOG: Revision 7.14  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.13  2003/01/15 12:29:24  ssingh
 * LOG: Changed done for handling of CQR(rcvd)/UCIC(rcvd)/CGB(immediate Release).
 * LOG: Indications added to inform Application.
 * LOG:
 * LOG: Revision 7.12  2002/12/27 07:02:59  ssingh
 * LOG: Handling of GRS collision related changes done.
 * LOG:
 * LOG: Revision 7.11  2002/12/02 11:21:09  sjaddu
 * LOG: COT Handling in IDLE state
 * LOG:
 * LOG: Revision 7.10  2002/11/21 11:59:08  sjaddu
 * LOG: More fixes for continuity.
 * LOG:
 * LOG: Revision 7.9  2002/11/21 10:00:15  ssingh
 * LOG: Code been Added to avoid memory leak.
 * LOG:
 * LOG: Revision 7.8  2002/11/20 12:49:07  akumar
 * LOG: Worked on ALARMS indentation
 * LOG:
 * LOG: Revision 7.7  2002/11/12 06:05:00  akumar
 * LOG: Added ANSI ISUP Alarms
 * LOG:
 * LOG: Revision 7.6  2002/10/30 13:49:18  sjaddu
 * LOG: Set cot_first_time indicator to ITS_TRUE.
 * LOG:
 * LOG: Revision 7.5  2002/10/30 09:08:17  sjaddu
 * LOG: Added Continuity procedures.
 * LOG:
 * LOG: Revision 7.4  2002/10/25 13:43:57  ssingh
 * LOG: Code changes done as a part of BUG 141-to-146 fixing.
 * LOG:
 * LOG: Revision 7.3  2002/10/21 12:26:09  ssingh
 * LOG: Addec functions to support <-CQR- for ANSI.
 * LOG:
 * LOG: Revision 7.2  2002/10/11 09:24:56  sjaddu
 * LOG: Added PEGS for ANSI ISUP.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.17  2002/07/23 18:24:12  ssingh
 * LOG: Added/Changed Code to fix BUG noticed during testing.
 * LOG:
 * LOG: Revision 1.1.2.16  2002/07/19 19:12:25  ssingh
 * LOG: ANSI92 completed according to the SDLs.
 * LOG:
 * LOG: Revision 1.1.2.15  2002/07/18 22:40:28  ssingh
 * LOG: Added Code for handling BLS/BLR/RSC from remote/local.
 * LOG:
 * LOG: Revision 1.1.2.14  2002/07/18 19:16:55  ssingh
 * LOG: Handling of CGB/CGU/CGBA/CGUA/GRS/GRA from local/remote.
 * LOG:
 * LOG: Revision 1.1.2.13  2002/07/15 21:26:58  hbalimid
 * LOG: Old Implementation restored.
 * LOG:
 * LOG: Revision 1.1.2.12  2002/07/13 17:41:37  hbalimid
 * LOG: Wait for Incoming ACM procedures completed.
 * LOG:
 * LOG: Revision 1.1.2.11  2002/07/12 15:25:08  ssingh
 * LOG: Added/Changed CQM/CQR related methods.
 * LOG:
 * LOG: Revision 1.1.2.10  2002/07/10 14:08:15  ssingh
 * LOG: code chages related to CSC.
 * LOG:
 * LOG: Revision 1.1.2.9  2002/07/09 00:00:15  ssingh
 * LOG: CQR implemented. Bug Fixed.
 * LOG:
 * LOG: Revision 1.1.2.8  2002/07/08 14:17:11  ssingh
 * LOG: Code changes as per ANSI92 testing (BUG FIX)
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/07 14:06:23  hbalimid
 * LOG: Completed CRS state machine handling.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/06 19:21:28  hbalimid
 * LOG: Fixed warnings.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/06 06:09:59  hbalimid
 * LOG: Tookcare of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/05 23:29:36  ssingh
 * LOG: Bug Fix for BLO.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/05 13:57:21  ssingh
 * LOG: ansi 92 changes.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/02 23:19:34  ssingh
 * LOG: Added ANSI92 specific changes.
 * LOG: Timer handling and GRS/GRA implemented.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/01 20:17:50  hbalimid
 * LOG: Baseline for ISUP ANSI GENERIC 92.
 * LOG:
 * LOG: Revision 1.4  2002/06/28 16:18:47  ssingh
 * LOG: Changes for ANSI ISUP.
 * LOG:
 * LOG: Revision 1.3  2002/06/27 14:13:40  hbalimid
 * LOG: Fixed ITS_ISUP_BAD_RNG_STATUS to ITS_ISUP_BAD_RNG_STATUS_ERR
 * LOG:
 * LOG: Revision 1.2  2002/06/12 20:02:06  sjaddu
 * LOG: cic idle state is fixed.
 * LOG:
 * LOG: Revision 1.1  2002/06/10 14:55:36  sjaddu
 * LOG: Added first draft of file for ANSI ISUP.
 * LOG:
 *
 *****************************************************************************/

#undef CCITT
#undef ANSI
#define ANSI

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <ansi/isup_92.h>

/*
 * Functions for validating message parameter contents
 */

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get number of bits set in the octet array
 *
 *  Input Parameters:
 *      ptr: start of octet array
 *      len: number of octets in the array
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Number of bits set in the array.
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_NumBitsSet(ITS_OCTET *ptr, ITS_OCTET len)
{
    int count = 0;
    ITS_OCTET byte;
    int i;

    for (i = 0; i < len; i++)
    {
        byte = ptr[i];
        while(byte)
        {
            byte &= byte - 1;
            count++;
        }
    }

    return (count);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get bits set in the octet array
 *
 *  Input Parameters:
 *      ptr: start of octet array
 *      len: number of octets in the array
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      bit_offsets - array of bit offsets that are set.
 *      num_bit_offsets - number of bits set in the array      
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_GetBitsSet(ISUP_RANGE_AND_STATUS rs, ITS_OCTET len,
                  ITS_USHORT *bit_offsets, ITS_USHORT *num_bit_offsets)
{
    ITS_OCTET range=rs.range;
    ITS_OCTET *ptr=rs.status;
    ITS_OCTET byte;
    int i, j;
   
    *num_bit_offsets = 0;

    if (rs.range == 0)
    {
        range = 23;
        len = 3;
        memset ((char *)ptr, 255, 3);
    }

    for (i = 0; i < len; i++)
    {
        byte = ptr[i];

        for (j = 0; j < 8; j++)
        {
            if ((byte >> j) & 0x01)
            {
                if (8*i+j <= range)
                {
                   bit_offsets[*num_bit_offsets] = (ITS_USHORT)(8 * i + j);

                   *num_bit_offsets += 1;
                }
            }
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get bits not set in the octet array
 *
 *  Input Parameters:
 *      ptr: start of octet array
 *      len: number of octets in the array
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      bit_offsets - array of bit offsets that are not set.
 *      num_bit_offsets - number of bits not set in the array      
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_GetBitsUnset(ISUP_RANGE_AND_STATUS rs, ITS_OCTET len,
                    ITS_USHORT *bit_offsets, ITS_USHORT *num_bit_offsets)
{
    ITS_OCTET range=rs.range;
    ITS_OCTET *ptr=rs.status;
    ITS_OCTET byte;
    int i, j;

    *num_bit_offsets = 0;

    if (rs.range == 0)
    {
        range = 23;
        len = 3;
        memset ((char *)ptr, 0, 3);
    }

    for (i = 0; i < len; i++)
    {
        byte = ptr[i];

        for (j = 0; j < 8; j++)
        {
            if (!((byte >> j) & 0x01))
            {
                if (8*i+j <= range)
                {
                   bit_offsets[*num_bit_offsets] = (ITS_USHORT)(8 * i + j);

                   *num_bit_offsets += 1;
                }
            }
        }
    }

    return (ITS_SUCCESS);
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Validate contents of a RangeAndStatus param
 *
 *  Input Parameters:
 *      msg: the message containing the param
 *      cic_rec: cic record for the cic pertaining to the message
 *      config_info: config infor for the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      rs_ie: range and status IE from the message
 *      sup_msg_type: supervision message type
 *      cic: cic in the message
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_Validate_RangeStatus(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                            ISUP_OPC_DPC_INFO *config_info,
                            ITS_ISUP_IE *rs_ie, ITS_OCTET *sup_msg_type,
                            ITS_USHORT *cic)
{
    int ret = ITS_SUCCESS;
    int index = 0;
    ITS_USHORT paramlen = 0;
    ITS_ISUP_IE ies[5];
    int ieCount = 0;
    ISUP_RANGE_AND_STATUS rs; /* the param in the message */
    ITS_OCTET range; /* range value */
    ITS_OCTET rslen; /* rangestatus param len */
    ITS_OCTET slen;  /* status len */
    int i;
    ITS_OCTET cic_index;

    /* initialize local */
    memset((char *)ies, 0, sizeof(ITS_ISUP_IE) * 5);

    /* initialize output params */
    memset((char *)rs_ie, 0, sizeof(ITS_ISUP_IE));
    *sup_msg_type = 0;
    *cic = 0;

    /*
     * message contains: MTP3MessageType: MTP3Header: CIC: Message Type: Params
     */
    /* get cic from message: CIC is two bytes: LSB and MSB (4 bits) */
    cic_index = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_ANSI);
    *cic = (ITS_USHORT)((msg->data[cic_index + 1] << 8) + msg->data[cic_index]);

    /* Validate param */

    paramlen = (ITS_USHORT)(msg->len - sizeof(ITS_OCTET) - sizeof(ITS_USHORT)
                       - sizeof(MTP3_HEADER_ANSI));
    index = msg->len - paramlen;

    /* Need to do a Decode as TLV style is not being used. */
    ret = ISUP_MTP3Decode_ANSI(&msg->data[index + 1],
                                paramlen,
                                msg->data[index],
                                ies, &ieCount, config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
            rslen = ies[i].param_length;

            /* subtract 1 for range */
            slen = (ITS_OCTET)(ies[i].param_length - 1);

            if (rslen > 25)
            {
                return ITS_BADISUPMESSAGE;
            }

            rs = ies[i].param_data.rangeAndStatus;    
            *rs_ie = ies[i];
    
            range = rs.range;
            
            /* message type */
            switch (msg->data[index])
            {
                /* range and status */
                case ISUP_MSG_CGB:
                case ISUP_MSG_CGBA:
                case ISUP_MSG_CGU:
                case ISUP_MSG_CGUA:
                case ISUP_MSG_GRA:
                    /* For all these messages, Status field is must.
                     * If range is all zero; No status field.
                     * Handled in other place.
                     */
                    if(slen > 4 || (range > 23))
                    {
                        return ITS_BADISUPMESSAGE;
                    } 
                    else if (slen == 0 && range != 0)
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    break;

                case ISUP_MSG_GRS:
                case ISUP_MSG_CQM:
                case ISUP_MSG_CQR:
                    /* All these message; no Status field */

                    if (slen != 0 || (range > 23))
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    break;

                default:
                    return ITS_BADISUPMESSAGE;
            }
        }
        else if (ies[i].param_id == ISUP_PRM_CKT_GRP_SUPRVN_MT_IND)
        {
            *sup_msg_type = ies[i].param_data.supervisionMsgType.sup_mt;
        }
    }
    
    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get list of cics affected by the range/status param in a message. The
 *      list of cics is computed using the cic in the message and the offsets
 *      of the bits set in the status portion of the range/status param.
 *
 *  Input Parameters:
 *      msg: the message (to get the cic)
 *      rs_ie: pointer to range/status param to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      affected_cics: array of cics affected by the param
 *      num_affected_cics: number of cics in the array
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_GetAffectedCics(ITS_USHORT cic, ITS_ISUP_IE *rs_ie, 
                       ITS_USHORT *affected_cics, 
                       ITS_USHORT *num_affected_cics)
{
    ITS_OCTET slen;  /* status len */
    int i;
    ISUP_RANGE_AND_STATUS rs; /* the param in the message */
    ITS_USHORT bit_offsets[256];
    ITS_USHORT num_bit_offsets;
    ITS_USHORT next_cic;

    *num_affected_cics = 0;

    /* subtract 1 for range */
    slen = (ITS_OCTET)(rs_ie->param_length - 1);

    rs = rs_ie->param_data.rangeAndStatus;

    __ISUP_GetBitsSet(rs, slen, bit_offsets, &num_bit_offsets);

    for (i = 0; i < num_bit_offsets; i++)
    {
        next_cic = (ITS_USHORT)(cic + bit_offsets[i]);

        affected_cics[*num_affected_cics] = next_cic;
        
        *num_affected_cics += 1;
    }

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get list of cics affected by the range/status param in a message. The
 *      list of cics is computed using the cic in the message and the offsets
 *      of the bits set in the status portion of the range/status param.
 *
 *  Input Parameters:
 *      msg: the message (to get the cic)
 *      rs_ie: pointer to range/status param to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      set_cics: array of cics set in GRA
 *      num_set_cics: number of cics set in GRA
 *      unset_cics: array of cics not set in GRA
 *      num_unset_cics: number of cics not set in GRA
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_GetGRACics(ITS_USHORT cic, ITS_ISUP_IE *rs_ie,
                  ITS_USHORT *set_cics,
                  ITS_USHORT *num_set_cics,
                  ITS_USHORT *unset_cics,
                  ITS_USHORT *num_unset_cics)
{
    ITS_OCTET slen;  /* status len */
    int i;
    ISUP_RANGE_AND_STATUS rs; /* the param in the message */
    ITS_USHORT bit_offsets[256];
    ITS_USHORT num_bit_offsets;
    ITS_USHORT bit_offsets2[256];
    ITS_USHORT num_bit_offsets2;
    ITS_USHORT next_cic;

    *num_set_cics = 0;
    *num_unset_cics = 0;

    /* subtract 1 for range */
    slen = (ITS_OCTET)(rs_ie->param_length - 1);

    rs = rs_ie->param_data.rangeAndStatus;

    __ISUP_GetBitsSet(rs, slen, bit_offsets, &num_bit_offsets);
    __ISUP_GetBitsUnset(rs, slen, bit_offsets2, &num_bit_offsets2);

    for (i = 0; i < num_bit_offsets; i++)
    {
        next_cic = (ITS_USHORT)(cic + bit_offsets[i]);

        set_cics[*num_set_cics] = next_cic;

        *num_set_cics += 1;
    }

    for (i = 0; i < num_bit_offsets2; i++)
    {
        next_cic = (ITS_USHORT)(cic + bit_offsets2[i]);

        unset_cics[*num_unset_cics] = next_cic;
        
        *num_unset_cics += 1;
    }

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get list of cics affected by the range/status param in a GRS message.
 *
 *  Input Parameters:
 *      msg: the message (to get the cic)
 *      rs_ie: pointer to range/status param to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      grs_cics: array of cics affected by GRS
 *      num_grs_cics: number of cics affected
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_GetGRSCics(ITS_USHORT cic, ITS_ISUP_IE *rs_ie, 
                  ITS_USHORT *grs_cics, 
                  ITS_USHORT *num_grs_cics)
{
    int i;
    ISUP_RANGE_AND_STATUS rs; /* the param in the message */
    ITS_USHORT next_cic;

    *num_grs_cics = 0;

    rs = rs_ie->param_data.rangeAndStatus; 

    if( rs.range == 0)
    {
        for (i = 0; i <= 23; i++)
        {
            next_cic = (ITS_USHORT)(cic + i);

            grs_cics[*num_grs_cics] = next_cic;

            *num_grs_cics += 1;
        }

    }
    else
    {
        for (i = 0; i <= rs.range; i++)
        {
            next_cic = (ITS_USHORT)(cic + i);

            grs_cics[*num_grs_cics] = next_cic;
        
            *num_grs_cics += 1;
        }
    }

    return ITS_SUCCESS;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Call a processing routine for each cic in an array of affected cics.
 *
 *  Input Parameters:
 *      affected_cics: array of cics affected by the param
 *      num_affected_cics: number of cics in the array
 *      func: pointer to the processing routine (function) to be called for
 *            each cic
 *      config_info: pointer to config info for the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ProcessAffectedCics(ITS_USHORT *affected_cics, 
                           ITS_USHORT num_affected_cics,
                           ISUP_PROC_FUNC func,
                           ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_CIC_INFO *affected_cic_rec;
    int i;
    ISUP_PCIC pcic;
    ITS_UINT opc, dpc;
    ITS_OCTET ni;
    ITS_BOOLEAN ret = ITS_TRUE;

    for (i = 0; i < num_affected_cics; i++)
    {
        if (affected_cics[i] == ISUP_PCIC_TO_CIC(cic_rec->pcic))
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cics[i]);
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_ERROR(("Could not find PCIC\n"));
        }
        else
        {
            if (func)
            {
                ret = (*func)(affected_cic_rec, config_info);

                if (ret == ITS_FALSE)
                {
                   if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != 
                       ISUP_PCIC_TO_CIC(cic_rec->pcic))
                    {
                        ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
                    }

                    return ret;
                }
            }
            else
            {
                ISUP_ERROR(("Bad function\n"));
            }

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != 
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
        }
    }

    return ret;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Compare request and response.
 *
 *  Input Parameters:
 *      cgba_ev: CGBA event
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_CompareCGBAWithCGB(ITS_EVENT *cgba_ev,ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT   cgb_ev;
    ITS_ISUP_IE cgb_rs_ie;
    ITS_OCTET   cgb_sup_msg_type;
    ITS_USHORT  cgb_cic;
    ITS_ISUP_IE cgba_rs_ie;
    ITS_OCTET   cgba_sup_msg_type;
    ITS_USHORT  cgba_cic;
#if 0
    ITS_USHORT  cgb_affected_cics[256];
    ITS_USHORT  cgb_num_affected_cics;
    ITS_USHORT  cgba_affected_cics[256];
    ITS_USHORT  cgba_num_affected_cics;
    ITS_USHORT  cgb_index = 0;
    ITS_USHORT  cgba_index = 0;
    ITS_BOOLEAN bool_ret = ITS_TRUE;
    ITS_BOOLEAN more_cgb, more_cgba;
#endif
    ITS_BOOLEAN ret = ITS_TRUE;

    int         i, j;
    ITS_USHORT  affected_cic;
    ISUP_PCIC   pcic;
    ITS_UINT    opc, dpc;
    ITS_OCTET   ni;
    ISUP_CIC_INFO *affected_cic_rec;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

    ITS_EVENT_INIT(&cgb_ev, ITS_ISUP_ANSI_SRC, cic_msg->cgb_msg_len);

    memcpy((void *)(cgb_ev.data), cic_msg->cgb_msg, cic_msg->cgb_msg_len);
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

    __ISUP_Validate_RangeStatus(&cgb_ev, cic_rec, config_info, &cgb_rs_ie,
                                &cgb_sup_msg_type, &cgb_cic);

    __ISUP_Validate_RangeStatus(cgba_ev, cic_rec, config_info, &cgba_rs_ie,
                                &cgba_sup_msg_type, &cgba_cic);

    ITS_EVENT_TERM(&cgb_ev);
                
    /* The cics in CGB and CGBA must match */
    if (cgb_cic != cgba_cic)
    {
        ISUP_ERROR(("CGBA CIC (%d) does not match CGB CIC (%d)\n", 
                     cgba_cic, cgb_cic));

        return ITS_FALSE;
    }

    if(cgb_rs_ie.param_data.rangeAndStatus.range == 0 &&
       ((cgba_rs_ie.param_data.rangeAndStatus.range == 0) ||
        (cgba_rs_ie.param_data.rangeAndStatus.range == 23)))
    {
       return ITS_TRUE;
    }

    /* Now Check the range for non Zero */
    if (cgb_rs_ie.param_data.rangeAndStatus.range !=
            cgba_rs_ie.param_data.rangeAndStatus.range)
    {
        ISUP_ERROR(("CGBA Range (%d) does not match CGB Range (%d)\n",
                    cgba_rs_ie.param_data.rangeAndStatus.range, 
                    cgb_rs_ie.param_data.rangeAndStatus.range));

       return ITS_FALSE;
    }

#if 1
    for (i = 0; i < (cgb_rs_ie.param_length - 1); i++)
    {
        for (j=0 ; j<8 ; j++)
        {
            if ((((cgb_rs_ie.param_data.rangeAndStatus.status[i] >> j) & 0x01)
                 == 0x01) &&
               (((cgba_rs_ie.param_data.rangeAndStatus.status[i] >> j) & 0x01)
                 == 0x00))
            {
               /* Missing blocking ack for given cic */
               affected_cic = cgb_cic + 8*i +j;

               opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
               dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
               ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

               if(affected_cic == ISUP_PCIC_TO_CIC(cic_rec->pcic))
               {
                   affected_cic_rec = cic_rec;
               }
               else
               {
                  ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cic);
                  affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
               }

               if (affected_cic_rec == NULL)
               {
                  ISUP_ERROR(("Could not find PCIC\n"));
               }
               else
               {
                  /* Increament the peg */
                  PEG_IncrPeg(&affected_cic_rec->ISUP_CIC_PEGS,
                            PEG_ISUP_CIC_MISSING_ACK_IN_CGBA);

                  /* Alert maintenance */
                  ISUP_Alarm_ANSI(3259, __FILE__, __LINE__,
                           "cic: %x dpc: %d opc: %d",
                           ISUP_PCIC_TO_CIC(affected_cic_rec->pcic), dpc, opc);

                  ISUP_ERROR(("CGBA: Missing Blocking Ack for Cic %d\n",
                               ISUP_PCIC_TO_CIC(affected_cic_rec->pcic)));

                  if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                      ISUP_PCIC_TO_CIC(cic_rec->pcic))
                  {
                       ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
                  }
               }
            }
            else if ((((cgb_rs_ie.param_data.rangeAndStatus.status[i] >> j) &
               0x01) == 0x00) &&
               (((cgba_rs_ie.param_data.rangeAndStatus.status[i] >> j) & 0x01)
               == 0x01))
            {
               /* Abnormal blocking ack for given cic */
               affected_cic = cgb_cic + 8*i +j;

               opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
               dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
               ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

               if(affected_cic == ISUP_PCIC_TO_CIC(cic_rec->pcic))
               {
                   affected_cic_rec = cic_rec;
               }
               else
               {
                  ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cic);
                  affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
               }

               if (affected_cic_rec == NULL)
               {
                  ISUP_ERROR(("Could not find PCIC\n"));
               }
               else
               {
                  /* Increament the peg */
                  PEG_IncrPeg(&affected_cic_rec->ISUP_CIC_PEGS,
                              PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA);

                  /* Alert maintenance */
                  ISUP_Alarm_ANSI(3260, __FILE__, __LINE__,
                           "cic: %x dpc: %d opc: %d",
                           ISUP_PCIC_TO_CIC(affected_cic_rec->pcic), dpc, opc);

                  ISUP_ERROR(("CGBA: Abnormal Blocking Ack for Cic %d\n",
                               ISUP_PCIC_TO_CIC(affected_cic_rec->pcic)));

                  if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                      ISUP_PCIC_TO_CIC(cic_rec->pcic))
                  {
                       ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
                  }
               }
            }

            if ((cgb_cic + 8*i +j) == cgb_rs_ie.param_data.rangeAndStatus.range)
            {
               /* check for slen also */
               return ITS_TRUE;
            }
        }
    }
    ret = ITS_TRUE;

#endif 1

#if 0
    __ISUP_GetAffectedCics(cgb_cic, &cgb_rs_ie, cgb_affected_cics, 
                           &cgb_num_affected_cics);

    __ISUP_GetAffectedCics(cgba_cic, &cgba_rs_ie, cgba_affected_cics, 
                           &cgba_num_affected_cics);

    more_cgb = ITS_TRUE;
    more_cgba = ITS_TRUE;

    /* We have two sorted arrays of cics, need to compare */
    while (1)
    {
        if (cgba_index == cgba_num_affected_cics)
        {
            more_cgba = ITS_FALSE;
        }

        if (cgb_index == cgb_num_affected_cics)
        {
            more_cgb = ITS_FALSE;
        }

        if (!more_cgba && !more_cgb)
        {
            break;
        }
        else if (more_cgb && !more_cgba)
        {
            /* cgba < cgb */
            ISUP_ERROR(("CGBA has less status bits than CGB\n"));
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_MISSING_ACK_IN_CGBA);

            ret = ITS_FALSE;
            break;
        }
        else if (!more_cgb && more_cgba)
        {
            /* cgba > cgb */
            ISUP_DEBUG(("CGBA has more status bits than CGB\n"));
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA);

            bool_ret = __ISUP_ProcessAffectedCics(&cgba_affected_cics[cgba_index], 
                                                  (ITS_USHORT)(cgba_num_affected_cics - cgba_index),
                                                  __ISUP_MGBSCheckLocallyBlocked,
                                                  cic_rec, config_info);
            if (bool_ret == ITS_FALSE)
            {
                ISUP_ERROR(("At least one CIC from CGBA is not locally "
                            "blocked\n"));

                ret = ITS_FALSE;
            }

            break;
        }
        else if (more_cgb && more_cgba)
        {
            /* compare the cics in cgb and cgba */
            if (cgb_affected_cics[cgb_index] == 
                    cgba_affected_cics[cgba_index])
            {
                cgb_index++;
                cgba_index++;
            }
            else if (cgb_affected_cics[cgb_index] > 
                         cgba_affected_cics[cgba_index])
            {
                /* cgba has extra cic */
                bool_ret = __ISUP_ProcessAffectedCics(&cgba_affected_cics[cgba_index], 
                                                      1,
                                                      __ISUP_MGBSCheckLocallyBlocked,
                                                      cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    ISUP_ERROR(("At least one CIC from CGBA is not locally "
                                "blocked\n"));

                    ret = ITS_FALSE;
                    break;
                }

                cgba_index++;
            }
            else if (cgb_affected_cics[cgb_index] < 
                         cgba_affected_cics[cgba_index])
            {
                /* cgb has extra cic */
                ISUP_ERROR(("CGBA has less status bits than CGB\n"));

                ret = ITS_FALSE;
                break;
            }
        }
    }
#endif 0

    return ret;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Compare request and response.
 *
 *  Input Parameters:
 *      cgua_ev: CGUA event
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_CompareCGUAWithCGU(ITS_EVENT *cgua_ev,ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT cgu_ev;
    ITS_ISUP_IE cgu_rs_ie;
    ITS_OCTET cgu_sup_msg_type;
    ITS_USHORT cgu_cic;
    ITS_ISUP_IE cgua_rs_ie;
    ITS_OCTET cgua_sup_msg_type;
    ITS_USHORT cgua_cic;
#if 0
    ITS_USHORT cgu_affected_cics[256];
    ITS_USHORT cgu_num_affected_cics;
    ITS_USHORT cgua_affected_cics[256];
    ITS_USHORT cgua_num_affected_cics;
    int cgu_index = 0;
    int cgua_index = 0;
    ITS_BOOLEAN bool_ret = ITS_TRUE;
    ITS_BOOLEAN more_cgu, more_cgua;
#endif
    ITS_BOOLEAN ret = ITS_TRUE;

    int         i, j;
    ITS_USHORT  affected_cic;
    ISUP_PCIC   pcic;
    ITS_UINT    opc, dpc;
    ITS_OCTET   ni;
    ISUP_CIC_INFO *affected_cic_rec;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

    ITS_EVENT_INIT(&cgu_ev, ITS_ISUP_ANSI_SRC, cic_msg->cgu_msg_len);

    memcpy((void *)(cgu_ev.data), cic_msg->cgu_msg, cic_msg->cgu_msg_len);
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

    __ISUP_Validate_RangeStatus(&cgu_ev, cic_rec, config_info, &cgu_rs_ie,
                                &cgu_sup_msg_type, &cgu_cic);

    __ISUP_Validate_RangeStatus(cgua_ev, cic_rec, config_info, &cgua_rs_ie,
                                &cgua_sup_msg_type, &cgua_cic);

    ITS_EVENT_TERM(&cgu_ev);
                
    /* The cics in CGU and CGUA must match */
    if (cgu_cic != cgua_cic)
    {
        ISUP_ERROR(("CGUA CIC (%d) does not match CGU CIC (%d)\n", 
                     cgua_cic, cgu_cic));

        return ITS_FALSE;
    }


    if(cgu_rs_ie.param_data.rangeAndStatus.range == 0 && 
       ((cgua_rs_ie.param_data.rangeAndStatus.range == 0) ||
        (cgua_rs_ie.param_data.rangeAndStatus.range == 23)))
    {
       return ITS_TRUE;
    }

    /* Now Check the range for non Zero */
    if (cgu_rs_ie.param_data.rangeAndStatus.range !=
            cgua_rs_ie.param_data.rangeAndStatus.range)
    {
        ISUP_ERROR(("CGUA Range (%d) does not match CGU Range (%d)\n",
                    cgua_rs_ie.param_data.rangeAndStatus.range,
                    cgu_rs_ie.param_data.rangeAndStatus.range));

       return ITS_FALSE;
    }

#if 1
    for (i = 0; i < (cgu_rs_ie.param_length - 1); i++)
    {
        for (j=0 ; j<8 ; j++)
        {
            if ((((cgu_rs_ie.param_data.rangeAndStatus.status[i] >> j) & 0x01)
                 == 0x01) &&
               (((cgua_rs_ie.param_data.rangeAndStatus.status[i] >> j) & 0x01)
                 == 0x00))
            {
               /* Missing unblocking ack for given cic */
               affected_cic = cgu_cic + 8*i +j;

               opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
               dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
               ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

               if(affected_cic == ISUP_PCIC_TO_CIC(cic_rec->pcic))
               {
                   affected_cic_rec = cic_rec;
               }
               else
               {
                  ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cic);
                  affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
               }

               if (affected_cic_rec == NULL)
               {
                  ISUP_ERROR(("Could not find PCIC\n"));
               }
               else
               {
                  /* Increament the peg */
                  PEG_IncrPeg(&affected_cic_rec->ISUP_CIC_PEGS,
                            PEG_ISUP_CIC_MISSING_ACK_IN_CGUA);

                  /* Alert maintenance */
                  ISUP_Alarm_ANSI(3101, __FILE__, __LINE__,
                           "cic: %x dpc: %d opc: %d",
                           ISUP_PCIC_TO_CIC(affected_cic_rec->pcic), dpc, opc);

                  ISUP_ERROR(("CGUA: Missing UnBlocking Ack for Cic %d\n",
                               ISUP_PCIC_TO_CIC(affected_cic_rec->pcic)));

                  if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                      ISUP_PCIC_TO_CIC(cic_rec->pcic))
                  {
                       ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
                  }
               }
            }
            else if ((((cgu_rs_ie.param_data.rangeAndStatus.status[i] >> j) &
               0x01) == 0x00) &&
               (((cgua_rs_ie.param_data.rangeAndStatus.status[i] >> j) & 0x01)
               == 0x01))
            {
               /* Abnormal unblocking ack for given cic */
               affected_cic = cgu_cic + 8*i +j;

               opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
               dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
               ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

               if(affected_cic == ISUP_PCIC_TO_CIC(cic_rec->pcic))
               {
                   affected_cic_rec = cic_rec;
               }
               else
               {
                  ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cic);
                  affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
               }

               if (affected_cic_rec == NULL)
               {
                  ISUP_ERROR(("Could not find PCIC\n"));
               }
               else
               {
                  /* Increament the peg */
                  PEG_IncrPeg(&affected_cic_rec->ISUP_CIC_PEGS,
                              PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA);

                  /* Alert maintenance */
                  ISUP_Alarm_ANSI(3107, __FILE__, __LINE__,
                           "cic: %x dpc: %d opc: %d",
                           ISUP_PCIC_TO_CIC(affected_cic_rec->pcic), dpc, opc);

                  ISUP_ERROR(("CGUA: Abnormal UnBlocking Ack for Cic %d\n",
                               ISUP_PCIC_TO_CIC(affected_cic_rec->pcic)));

                  if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                      ISUP_PCIC_TO_CIC(cic_rec->pcic))
                  {
                       ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
                  }
               }
            }

            if ((cgu_cic + 8*i +j) == cgu_rs_ie.param_data.rangeAndStatus.range)
            {
               /* check for slen also */
               return ITS_TRUE;
            }
        }
    }
    ret = ITS_TRUE;

#endif 1

#if 0
    __ISUP_GetAffectedCics(cgu_cic, &cgu_rs_ie, cgu_affected_cics, 
                           &cgu_num_affected_cics);

    __ISUP_GetAffectedCics(cgua_cic, &cgua_rs_ie, cgua_affected_cics, 
                           &cgua_num_affected_cics);

    more_cgu = ITS_TRUE;
    more_cgua = ITS_TRUE;

    /* We have two sorted arrays of cics, need to compare */
    while (1)
    {
        if (cgua_index == cgua_num_affected_cics)
        {
            more_cgua = ITS_FALSE;
        }

        if (cgu_index == cgu_num_affected_cics)
        {
            more_cgu = ITS_FALSE;
        }

        if (!more_cgua && !more_cgu)
        {
            break;
        }
        else if (more_cgu && !more_cgua)
        {
            /* cgua < cgu */
            ISUP_ERROR(("CGUA has less status bits than CGU\n"));
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_MISSING_ACK_IN_CGUA);

            ret = ITS_FALSE;
            break;
        }
        else if (!more_cgu && more_cgua)
        {
            /* cgua > cgu */
            ISUP_DEBUG(("CGUA has more status bits than CGU\n"));
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK);

            bool_ret = __ISUP_ProcessAffectedCics(&cgua_affected_cics[cgua_index], 
                                                  (ITS_USHORT)(cgua_num_affected_cics - cgua_index),
                                                  __ISUP_MGBSCheckNotLocallyBlocked,
                                                  cic_rec, config_info);
            if (bool_ret == ITS_FALSE)
            {
                ISUP_ERROR(("At least one CIC from CGUA is locally "
                            "blocked\n"));

                ret = ITS_FALSE;
            }

            break;
        }
        else if (more_cgu && more_cgua)
        {
            /* compare the cics in cgu and cgua */
            if (cgu_affected_cics[cgu_index] == 
                    cgua_affected_cics[cgua_index])
            {
                cgu_index++;
                cgua_index++;
            }
            else if (cgu_affected_cics[cgu_index] > 
                         cgua_affected_cics[cgua_index])
            {
                /* cgua has extra cic */
                bool_ret = __ISUP_ProcessAffectedCics(&cgua_affected_cics[cgua_index], 
                                                      1,
                                                      __ISUP_MGBSCheckNotLocallyBlocked,
                                                      cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    ISUP_ERROR(("At least one CIC from CGUA is locally "
                                "blocked\n"));

                    ret = ITS_FALSE;
                    break;
                }

                cgua_index++;
            }
            else if (cgu_affected_cics[cgu_index] < 
                         cgua_affected_cics[cgua_index])
            {
                /* cgu has extra cic */
                ISUP_ERROR(("CGUA has less status bits than CGU\n"));

                ret = ITS_FALSE;
                break;
            }
        }
    }
#endif 0

    return ret;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Compare request and response.
 *
 *  Input Parameters:
 *      gra_ev: GRA event
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_CompareGRAWithGRS(ITS_EVENT *gra_ev,ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT grs_ev;
    ITS_ISUP_IE grs_rs_ie;
    ITS_USHORT grs_cic;
    ITS_OCTET grs_sup_msg_type;
    ITS_ISUP_IE gra_rs_ie;
    ITS_USHORT gra_cic;
    ITS_OCTET gra_sup_msg_type;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

    ITS_EVENT_INIT(&grs_ev, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);

    memcpy((void *)(grs_ev.data), cic_msg->grs_msg, cic_msg->grs_msg_len);
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

    __ISUP_Validate_RangeStatus(&grs_ev, cic_rec, config_info, &grs_rs_ie,
                                &grs_sup_msg_type, &grs_cic);

    __ISUP_Validate_RangeStatus(gra_ev, cic_rec, config_info, &gra_rs_ie,
                                &gra_sup_msg_type, &gra_cic);

    ITS_EVENT_TERM(&grs_ev);
                
    /* The cics in GRS and GRA must match */
    if (grs_cic != gra_cic)
    {
        ISUP_ERROR(("GRA CIC (%d) does not match GRS CIC (%d)\n", 
                     gra_cic, grs_cic));

        return ITS_FALSE;
    }
    
    if (grs_rs_ie.param_data.rangeAndStatus.range == 0 &&
        ((gra_rs_ie.param_data.rangeAndStatus.range == 0 ) ||
         (gra_rs_ie.param_data.rangeAndStatus.range == 23)) )
    {
       return ITS_TRUE;
    }

    /* The range in GRS and GRA must match */
    if (grs_rs_ie.param_data.rangeAndStatus.range != 
            gra_rs_ie.param_data.rangeAndStatus.range)
    {
        ISUP_ERROR(("GRA Range (%d) does not match GRS Range (%d)\n", 
                     gra_rs_ie.param_data.rangeAndStatus.range, 
                     grs_rs_ie.param_data.rangeAndStatus.range));

        return ITS_FALSE;
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingMGBSToBLS(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_IDLE)
    {
        /* Mark CIC state accordingly: Locally Blocked */
        cic_rec->cic_state &= 0xFEU;
        cic_rec->cic_state |= CKTS_LBLOCKED;         

        cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        __ISUP_StopBLOTimers(cic_rec, config_info);

        cic_rec->bls_state = BLS_IDLE;        
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
    {
        __ISUP_StopUBLTimers(cic_rec, config_info);

        cic_rec->bls_state = BLS_IDLE;        
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingMGBRToCPCO(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    switch(cic_rec->fsm_state)
    {
    case IDLE:
        return ITS_TRUE;

    case WAIT_COT_REPORTS_AND_CRA:
    case WAIT_INCOMING_CRA:
        /*Stop TCRM timer */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        /*Send a Re-attempt indication to the application */
        SPRC_SendIndToApp_ANSI(ITS_ISUP_AUTOREL_CRMRETRY_RQIND, cic_rec);

        __ISUP_StopCPCToCCO(cic_rec,config_info);

        __ISUP_StartRELTimers(cic_rec, config_info);

        SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                            cic_rec,config_info);
        cic_rec->fsm_state = WAIT_INCOMING_RLC;

        break;

    case WAIT_COT_REPORTS_HAVE_CRA:
    case WAIT_INCOMING_IAM:
    case WAIT_INCOMING_COT_AND_IAM:
    case WAIT_OUTGOING_IAM:
        /* Ignore and no change of fsm_state */
        break;

    case WAIT_CONTINUITY_REPORT:
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /* Send REATTEMPT indic to app */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_CGB_REATTEMPT_RQIND, cic_rec);

            SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                     cic_rec,
                                     config_info);

            /* Start T5 and T1 */
            __ISUP_StartRELTimers(cic_rec, config_info);

            /* Change state to WAIT_INCOMING_RLC */
            cic_rec->fsm_state = WAIT_INCOMING_RLC;
        }
        break;

    case WAIT_INCOMING_COT:
        break;

    case WAIT_INCOMING_ACM:
        /* Stop timer T7 */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

        /* Send REATTEMPT indic to app */
        SPRC_SendIndToApp_ANSI(ITS_ISUP_CGB_REATTEMPT_RQIND, cic_rec);

        SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                 cic_rec,
                                 config_info);

        /* Start T5 and T1 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
        break;

    default:
        break;
    }
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      MGBS helper function
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_MGBSCheckLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info)
{

    if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      MGBS helper function
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_MGBSCheckNotLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info)
{
    if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
    {
        return ITS_FALSE;
    }
    else
    {
        return ITS_TRUE;
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingMGBRToBLR(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (!ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
    {
        /* Mark CIC state accordingly: Remotely blocked */
        /* Preserve local block if any */
        ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state); 

        /* Maintenance System ind */
        SPRC_SendIndToApp_ANSI(ITS_ISUP_CGB_RBLK_STIND, cic_rec);

        cic_rec->blr_state = BLR_IDLE;
    }
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBRToCRO(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_TIMER_EXPIRY :
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_COT :
        if (cic_rec->dco_state == DCO_IDLE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        }
        else
        {
            __ISUP_StopCROToDCO(cic_rec,config_info);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_IDLE :
        break;

    default :
        /* TODO : Add Alarm or Trace */;
    }
    cic_rec->cro_state = CRO_IDLE;
    return ITS_TRUE;

}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBSToCRO(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_TIMER_EXPIRY :
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        break;

    case CRO_WAIT_FOR_COT :
        if (cic_rec->dco_state == DCO_IDLE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        }
        else
        {
            __ISUP_StopCROToDCO(cic_rec,config_info);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cot_first_ind = ITS_TRUE;
        break;

    case CRO_IDLE :
    case CRO_WAIT_FOR_OUTGOING_CCR :
        break;

    default :

        break;
    }
    cic_rec->cro_state = CRO_IDLE;
    return ITS_TRUE;

}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBRToCRI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        if(cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCRR);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        /* Idle the Ckt*/
        cic_rec->cri_state = CRI_IDLE;
    }
    else if(cic_rec->cri_state == CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
    {
        if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
       /* remove loop
       - Enable echo suppressor, if any */
        /* Idle the Ckt*/
        cic_rec->cri_state = CRI_IDLE;
    }
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBSToCRI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        if(cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCRR);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->fsm_state = IDLE;
    }
    else if(cic_rec->cri_state == CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
    {

        if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
        }
       /* remove loop
       - Enable echo suppressor, if any */
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
    }
    return ITS_TRUE;
}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingMGBSToBLS(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_IDLE)
    {
        /* Mark CIC state accordingly: Locally Un-Blocked */
        ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);

        cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        __ISUP_StopBLOTimers(cic_rec, config_info);

        /* Mark CIC state accordingly: Locally Un-Blocked */
        ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);

        cic_rec->bls_state = BLS_IDLE;        
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
    {
        __ISUP_StopUBLTimers(cic_rec, config_info);

        /* Mark CIC state accordingly: Locally Un-Blocked */
        ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);

        cic_rec->bls_state = BLS_IDLE;       
    }

    return ITS_TRUE;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingMGBRToBLR(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
    {
        /* Mark CIC state accordingly: Remotely Un-blocked */
        ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

        /* Send Indication to Application */
        SPRC_SendIndToApp_ANSI(ITS_ISUP_CGU_RUNBLK_STIND, cic_rec);

        cic_rec->blr_state = BLR_IDLE;
    }
    return ITS_TRUE;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingBLSToCPC(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingCPCIToBLS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

        /* This is not in SDL */
        __ISUP_StopBLOTimers(cic_rec, config_info);

        __ISUP_StartBLOTimers(cic_rec, config_info);
    }
    else if (cic_rec->bls_state == BLS_IDLE)
    {
        SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

        __ISUP_StartBLOTimers(cic_rec, config_info);

        cic_rec->bls_state = BLS_WAIT_FOR_BLA;
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingCRSToBLS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
        {
           /* Maintenance system ind */
           ISUP_CRITICAL(("Unblocking CRS to BLS, pcic 0x%08x, vcic %d.\n",
                           cic_rec->pcic, cic_rec->vcic));

           /* Mark CIC state accordingly: Locally Un-Blocked */
           ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);
        }

        __ISUP_StopBLOTimers(cic_rec, config_info);

        cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_IDLE)
    {
        if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
        {
           /* Maintenance system ind */
           ISUP_CRITICAL(("CIC unblocked, pcic 0x%08x, vcic %d.\n",
                           cic_rec->pcic, cic_rec->vcic));

           /* Mark CIC state accordingly: Locally Un-Blocked */
           ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);
        }

        cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
    {
        __ISUP_StopUBLTimers(cic_rec, config_info);

        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

        cic_rec->bls_state = BLS_IDLE;
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingCGRSToBLS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
        {
            /* Maintenance system ind */
            ISUP_CRITICAL(("Unblocking CGRS to BLS, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));

            /* Mark CIC state accordingly: Locally Un-Blocked */
            ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);
         }

         __ISUP_StopBLOTimers(cic_rec, config_info);

         cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_IDLE)
    {
        if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
        {
            /* Maintenance system ind */
            ISUP_CRITICAL(("CIC unblocked, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));

            /* Mark CIC state accordingly: Locally Un-Blocked */
            ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);
        }

         cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
    {
        __ISUP_StopUBLTimers(cic_rec, config_info);

        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

        cic_rec->cgrr_m_status = 0;
        cic_rec->bls_state = BLS_IDLE;
    }

    return ITS_TRUE;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingCGRSToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        ISUP_Alarm_ANSI(3016, __FILE__, __LINE__, "cic : %x dpc:%d opc: %d",
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));

        /* Maintenance system ind */
        ISUP_CRITICAL(("Blocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: Remotely blocked */
        cic_rec->cic_state &= 0xFDU;
        cic_rec->cic_state |= CKTS_RBLOCKED;

        cic_rec->blr_state = BLR_IDLE; 
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingCRRToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        ISUP_Alarm_ANSI(3017, __FILE__, __LINE__, "cic : %x dpc:%d opc: %d",
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));

        ISUP_CRITICAL(("Unblocking CRR to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }

    /* Maintenance system ind */
    SPRC_SendIndToApp_ANSI(ITS_ISUP_RSC_RUNBLK_STIND, cic_rec);

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingCRSToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingCGRRToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CGRR to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        ISUP_Alarm_ANSI(3018, __FILE__, __LINE__, "cic : %x dpc:%d opc: %d",
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

        cic_rec->blr_state = BLR_IDLE;
    }

    /* Maintenance system ind */
    SPRC_SendIndToApp_ANSI(ITS_ISUP_GRS_RUNBLK_STIND, cic_rec);

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingCPCIToBLR(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CPCI to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

        cic_rec->blr_state = BLR_IDLE;
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRSToMGBS(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
    {
        /* FIXED: changed see page 87 of Q.764 Annex H */
        ret = __ISUP_CompareCGBWithGRS(cic_rec, config_info);

        if (ret == ITS_TRUE)
        {
            cic_rec->mgbs_state = MGBS_IDLE;
        }
    }
    else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
    {
        /* FIXED: see page 89 of Q.764 Annex H */
        ret = __ISUP_CompareCGUWithGRS(cic_rec, config_info);

        if (ret == ITS_TRUE)
        {
            cic_rec->mgbs_state = MGBS_IDLE;
        }
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRRToMGBR(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
#if 0
    if (cic_rec->mgbr_state == MGBR_WAIT_FOR_UBL_RESP)
    {
        cic_rec->mgbr_state = MGBR_IDLE;
    }
    else if (cic_rec->mgbr_state == MGBR_WAIT_FOR_BLO_RESP)
    {
        cic_rec->mgbr_state = MGBR_IDLE;
    }
#endif

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRSToMGBR(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
#if 0
    if (cic_rec->mgbr_state == MGBR_WAIT_FOR_BLO_RESP)
    {
        cic_rec->mgbr_state = MGBR_IDLE;
    }
#endif

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetMGBSToCPC(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_UINT indId = ITS_ISUP_CGB_CPCIDLE_STIND;

    /* FIXEME: */
    /* Wait for Continuity states handling is not implmented   */
    /* See Figure 25/T1.113.4 Sheet 4A, 4C, 8 and 10           */
    /* See Figure 25/T1.113.4 Sheet 29, 29D, 29F and 29G       */
    /* Wait for Digits state; see Figure 25/T1.113.4 Sheet 29J */

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         return (ITS_TRUE);
         break;

    case WAIT_COT_REPORTS_AND_CRA:
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

         __ISUP_StopCPCToCCO(cic_rec,config_info);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_CRMRETRY_RQIND;

         break;

    case WAIT_COT_REPORTS_HAVE_CRA:
         __ISUP_StopCPCToCCO(cic_rec,config_info);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_CRMRETRY_RQIND;

         break;

    case WAIT_INCOMING_CRA:
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_CRMRETRY_RQIND;

         break;

    case WAIT_INCOMING_IAM:
        /* FIXME: No maintioning in specs */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

         break;

    case WAIT_INCOMING_COT_AND_IAM:
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
           __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }

        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        break;

    case WAIT_CONTINUITY_REPORT :
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
            indId = ITS_ISUP_CGB_RESETRETRY_RQIND;
        }
        break;
    case WAIT_INCOMING_COT :
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }
        break;
    case WAIT_INCOMING_ACM :
         /* Stop T7 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_RESETRETRY_RQIND;

         break;

    case WAIT_INCOMING_ANM :
         /* FIXME: */
         /* Outgoing Release Request */

         /* stop T9 timer, if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T9);

         break;

    case WAIT_OUTGOING_IAM :
    case RCVD_INCOMING_ANM :
         /* Outgoing Release Request */

         break;

    case WAIT_INCOMING_RLC :
         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         break;

    case WAIT_OUTGOING_ACM :
    case WAIT_OUTGOING_ANM :
         /* FIXME:                   */
         /* Incoming Release Request */

         break;

    case SENT_OUTGOING_ANM :
         /* Charging Office; Stop charging */
         /* Release Network Path */

         /* FIXME:                   */
         /* Incoming Release Request */

         break;

    case WAIT_OUTGOING_RLC :
         break;

    case WAIT_INCOMING_RES :
         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* FIXME: */
         /* Outgoing Release Request */

         break;

    case WAIT_OUTGOING_RES :
         /* Controlling Exchage; Charging Office; Stop charging */
         /* Release Network Path */

         /* FIXME:                   */
         /* Incoming Release Request */

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
        break;
    default:
         ret  = ITS_FALSE;
         return ret;
    }

    /* release indication to Application */
    SPRC_SendIndToApp_ANSI(indId , cic_rec);

    /* Idle  CPC */
    ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

    /* change state to Idle */
    cic_rec->fsm_state = IDLE;

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetMGBRToCPC(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_UINT indId = ITS_ISUP_CGB_CPCIDLE_STIND;

    /* FIXEME: */
    /* Wait for Continuity states handling is not implmented   */
    /* See Figure 25/T1.113.4 Sheet 4A, 4C, 8 and 10           */
    /* See Figure 25/T1.113.4 Sheet 29, 29D, 29F and 29G       */
    /* Wait for Digits state; see Figure 25/T1.113.4 Sheet 29J */

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         return (ITS_TRUE);
         break;

    case WAIT_COT_REPORTS_AND_CRA:
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

         __ISUP_StopCPCToCCO(cic_rec,config_info);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_CRMRETRY_RQIND;

         break;

    case WAIT_COT_REPORTS_HAVE_CRA:
         __ISUP_StopCPCToCCO(cic_rec,config_info);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_CRMRETRY_RQIND;

         break;

    case WAIT_INCOMING_CRA:
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_CRMRETRY_RQIND;

         break;

    case WAIT_INCOMING_IAM:
        /* FIXME: No maintioning in specs */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

         break;

    case WAIT_INCOMING_COT_AND_IAM:
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
           __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }

        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        break;

    case WAIT_CONTINUITY_REPORT :
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /* Call retry indication     */
            indId = ITS_ISUP_CGB_RESETRETRY_RQIND;
        }
        break;

    case WAIT_INCOMING_COT :
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
            ISUP_ClearCic(cic_rec);
        }
        break;

    case WAIT_INCOMING_ACM :
         /* Stop T7 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Call retry indication     */
         indId = ITS_ISUP_CGB_RESETRETRY_RQIND;

         break;

    case WAIT_INCOMING_ANM :
         /* FIXME: */
         /* Outgoing Release Request */

         /* stop T9 timer, if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T9);

         break;

    case WAIT_OUTGOING_IAM:
    case RCVD_INCOMING_ANM :
         /* FIXME: */
         /* Outgoing Release Request */

         break;

    case WAIT_INCOMING_RES :
         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* FIXME: */
         /* Outgoing Release Request */

         break;

    case WAIT_INCOMING_RLC :
         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         break;

    case WAIT_OUTGOING_ACM :
         /* FIXME:
          * Pre-ACM connect (y/n)
          * Release Network Path
          */
          
         /* Incoming Release Request */

         break;
    
    case WAIT_OUTGOING_ANM :
         /* Release Network Path */

         /* Incoming Release Request */

         break;

    case SENT_OUTGOING_ANM :
         /* Charging Office; Stop charging */
         /* Release Network Path */

         /* FIXME:                   */
         /* Incoming Release Request */

         break;

    case WAIT_OUTGOING_RLC :
         break;

    case WAIT_OUTGOING_RES :
         /* Controlling Exchage; Charging Office; Stop charging */
         /* Release Network Path */

         /* FIXME:                   */
         /* Incoming Release Request */

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
        break;
    default:
         ret  = ITS_FALSE;
         return ret;
    }

    /* release indication to Application */
    SPRC_SendIndToApp_ANSI(indId , cic_rec);

    /* Idle  CPC */
    ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

    /* change state to Idle */
    cic_rec->fsm_state = IDLE;

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      CRS helper function
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCRSCommon1(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_UnblockingCRSToBLS(cic_rec, config_info);

    if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
    {
        __ISUP_UnblockingCRSToBLR(cic_rec, config_info);
    }
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      CRS helper function
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCRSCommon2(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_ResetCRSCommon1(cic_rec, config_info);

    __ISUP_StopCRRToCRO(cic_rec, config_info);
    __ISUP_StopCRRToCRI(cic_rec, config_info);
    
    ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);

    SPRC_SendRSCToMTP3_ANSI(cic_rec, config_info);

    __ISUP_StartRSCTimers(cic_rec, config_info);

    cic_rec->crs_state = CRS_WAIT_FOR_RELEASE;

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCPCToCRS(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->crs_state == CRS_IDLE)
    {
        /* FIXME: Start Reset Indic to CC */
        
        cic_rec->reset_flag = RESET_FROM_CPC;

        __ISUP_ResetCRSCommon2(cic_rec, config_info);
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCRCRToCRS(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->crs_state == CRS_IDLE)
    {
        /* FIXME: Start Reset Indic to CC */
        
        cic_rec->reset_flag = RESET_FROM_CPC;

        __ISUP_ResetCRSCommon2(cic_rec, config_info);
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetAfterT5CPCToCRS(ISUP_CIC_INFO *cic_rec, 
                            ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->crs_state == CRS_IDLE)
    {
        cic_rec->reset_flag = RESET_AFTER_T5;

        __ISUP_ResetCRSCommon2(cic_rec, config_info);
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetAfterT5CRCSToCRS(ISUP_CIC_INFO *cic_rec, 
                             ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->crs_state == CRS_IDLE)
    {
        cic_rec->reset_flag = RESET_AFTER_T5;

        __ISUP_ResetCRSCommon2(cic_rec, config_info);
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCRSToCPC(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXME */
    ITS_BOOLEAN ret = ITS_TRUE;

    switch (cic_rec->fsm_state)
    {
    case IDLE :

         break;

    case WAIT_COT_REPORTS_AND_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        __ISUP_StopCPCToCCO(cic_rec,config_info);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_COT_REPORTS_HAVE_CRA:
        __ISUP_StopCPCToCCO(cic_rec,config_info);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_IAM:
        /* FIXME: No maintioning in specs */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_COT_AND_IAM:
        __ISUP_StopCPCToCCI(cic_rec,config_info);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_CONTINUITY_REPORT :
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
        }
        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_COT :
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }
        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_ACM :
         /* stop T7 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_ANM :
         /* stop T9 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T9);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case RCVD_INCOMING_ANM :
         /* stop charging */

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_RLC :
         /* release conformation */
         SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* T5 and T1 stop */
        __ISUP_StopRELTimers(cic_rec, config_info);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_IAM :
    case WAIT_OUTGOING_ACM :
    case WAIT_OUTGOING_ANM :
    case SENT_OUTGOING_ANM :
    case WAIT_OUTGOING_RLC :
         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_RES :
         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
  
         break;

    case WAIT_OUTGOING_RES :
         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
        break;
    default:
         ret  = ITS_FALSE;
         break;
    }
    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCRRToCRCS(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXME */
    /* Continuity recheck stuff (SENT) */
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCRRToCRCR(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXME */
    /* Continuity recheck stuff (RECEIVED) */
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCompleteCPCIToCRR(ISUP_CIC_INFO *cic_rec, 
                             ISUP_OPC_DPC_INFO *config_info)
{
    SPRC_SendRLCToMTP3_ANSI(cic_rec, config_info);

    cic_rec->crr_state = CRR_IDLE;

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      CGRS helper function
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRSCommon1(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_UnblockingCGRSToBLS(cic_rec, config_info);

    if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
    {
        __ISUP_UnblockingCGRSToBLR(cic_rec, config_info);
    }
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      CGRS helper function
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRSCommon2(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_ResetCGRSToCPC(cic_rec, config_info);

    __ISUP_ResetCGRSCommon1(cic_rec, config_info);

    if (cic_rec->crs_state == CRS_WAIT_FOR_RELEASE)
    {
        __ISUP_StopRSCTimers(cic_rec, config_info);

        /* Stop Repeat RSC timer also */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T98);

        cic_rec->crs_state = CRS_IDLE;
    }

    /* FIXME: CONTINUITY checks */
    __ISUP_StopCGRSToCRO(cic_rec, config_info);
    __ISUP_StopCGRSToCRI(cic_rec, config_info);

    ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingCGRSToBLR(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        ISUP_Alarm_ANSI(3019, __FILE__, __LINE__, "cic : %x dpc:%d opc: %d",
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRSToCPC(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXED */
    ITS_BOOLEAN ret = ITS_TRUE;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
    break;

    case WAIT_COT_REPORTS_AND_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        __ISUP_StopCPCToCCO(cic_rec,config_info);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_COT_REPORTS_HAVE_CRA:
        __ISUP_StopCPCToCCO(cic_rec,config_info);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_IAM:
        /* FIXME: No maintioning in specs */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_COT_AND_IAM:
        __ISUP_StopCPCToCCI(cic_rec,config_info);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);

        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_CONTINUITY_REPORT :
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
        }
        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_COT :
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }
        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_ACM :
         /* stop T7 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
         break;

    case WAIT_INCOMING_ANM :
         /* stop T9 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T9);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
         break;

    case RCVD_INCOMING_ANM :
         /* stop charging */

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
         break;

    case WAIT_INCOMING_RLC :
         /* release conformation */
         SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_REL_IND,cic_rec);

         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
         break;

    case WAIT_OUTGOING_IAM :
    case WAIT_OUTGOING_ACM :
    case WAIT_OUTGOING_ANM :
    case SENT_OUTGOING_ANM :
    case WAIT_OUTGOING_RLC :
         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
         break;

    case WAIT_INCOMING_RES :
         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_RES :
         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
        break;
    default:
         ret  = ITS_FALSE;
         break;
    }
    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      CGRR helper function.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRRCommon1(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->fsm_state != IDLE)
    {
       __ISUP_ResetCGRRToCPC(cic_rec, config_info);

    }
    __ISUP_StopCGRRToCRO(cic_rec, config_info);
    __ISUP_StopCGRRToCRI(cic_rec, config_info);

    if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
    {
       /* M-blocked status bit is set to "1" for GRA */
       cic_rec->cgrr_m_status = 1;
    }
    if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
    {
        __ISUP_UnblockingCGRRToBLR(cic_rec, config_info);
    }
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRRToCRCS(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXME :: continuity recheck control (SENDING)*/
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRRToCRCR(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXME :: continuity recheck control (RECEIVING) */
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRRToCPC(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_UINT indId = ITS_ISUP_GRS_CPCIDLE_STIND;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         return ret;
         break;

    case WAIT_COT_REPORTS_AND_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        __ISUP_StopCPCToCCO(cic_rec,config_info);

        /* Call retry indication     */
        indId = ITS_ISUP_GRS_CRMRETRY_RQIND;
        break;

    case WAIT_COT_REPORTS_HAVE_CRA:
        __ISUP_StopCPCToCCO(cic_rec,config_info);

        /* Call retry indication     */
        indId = ITS_ISUP_GRS_CRMRETRY_RQIND;

        break;

    case WAIT_INCOMING_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        /* Call retry indication     */
        indId = ITS_ISUP_GRS_CRMRETRY_RQIND;

        break;

    case WAIT_INCOMING_IAM:
        /* FIXME: not there in Specs */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        break;

    case WAIT_INCOMING_COT_AND_IAM:
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
           __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }

        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        break;

    case WAIT_CONTINUITY_REPORT :
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /* Send Reset Re-attempt indication */
            indId = ITS_ISUP_GRS_REATTEMPT_RQIND;
        }
        break;
    case WAIT_INCOMING_COT :
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }
        break;
    case WAIT_INCOMING_ACM :
         /* T7 stop */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Send Reset Re-attempt indication */
         indId = ITS_ISUP_GRS_REATTEMPT_RQIND;

         break;

    case WAIT_OUTGOING_IAM :
    case WAIT_INCOMING_ANM :
         /* Outgoing Release Req.*/

         break;

    case RCVD_INCOMING_ANM :
         break;

    case WAIT_INCOMING_RLC :
         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         break;

    case WAIT_OUTGOING_ACM :
         /* FIXME:
          * if (pre-ACM Connect) ? Y/N
          * Release Network Path 
          */

         /* Incoming Release Req.*/

         break;

    case WAIT_OUTGOING_ANM :
         /* Release Network Path */

         /* Incoming Release Req.*/

         break;

    case SENT_OUTGOING_ANM :
         /* Charging office; Stop Charging, if (Y) */

         /* Release Network Path */

         /* Incoming Release Req.*/

         break;

    case WAIT_OUTGOING_RLC :
         break;

    case WAIT_INCOMING_RES :
         /* FIXME: 
          * if (Controlling exchange == Y) 
          * Stop T6 timer
          */

         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* Outgoing Release Req.*/

         break;

    case WAIT_OUTGOING_RES :
         /* FIXME:
          * if (Controlling exchange == Y)
          * Stop charging, if (Y)
          */

         /* Release Network Path */

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
        break;
    default:
         ret  = ITS_FALSE;
         break;
    }

    /* Send Indication to Application */
    SPRC_SendIndToApp_ANSI(indId, cic_rec);

    /* Idle CPC state & Set fsm_state to IDLE */
    ISUP_ClearCic(cic_rec);

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_GetGRARangeNStatus(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info,
                           ITS_USHORT  *affected_cics,
                           ITS_USHORT  num_affected_cics,
                           ISUP_RANGE_AND_STATUS *rs)
{
    int                    i, count=0;
    ISUP_PCIC              pcic;
    ITS_UINT               opc, dpc;
    ITS_OCTET              ni;
    ITS_OCTET              gra_status[3];
    ISUP_CIC_INFO         *affected_cic_rec;

    memset ((char *)gra_status, 0, 3);

    for (i= 0; i < num_affected_cics; i++)
    {
        if (affected_cics[i] == ISUP_PCIC_TO_CIC(cic_rec->pcic))
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cics[i]);
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_ERROR(("Could not find PCIC\n"));
        }
        else
        {
            /* edit status field concerned M_BLOCKED */
            gra_status[count] |= affected_cic_rec->cgrr_m_status << i%8;

            if (affected_cic_rec->cgrr_m_status == 1)
            {
                ISUP_CIC_SET_MAINT(affected_cic_rec->cic_state, CKTS_LBLOCKED);

                /* Idle CPC state & set fsm_state to IDLE */
                ISUP_ClearCic(affected_cic_rec);
            }
            else
            {
                if(affected_cic_rec->cic_state != SPRC_CKTS_TRANSIENT)
                {
                   ISUP_CIC_SET_MAINT(affected_cic_rec->cic_state, CKTS_ACTIVE);

                   /* Idle CPC state & set fsm_state to IDLE */
                   ISUP_ClearCic(affected_cic_rec);
                }
            }

            if ((i + 1) % 8 == 0)
            {
                count++;
            }

            affected_cic_rec->cgrr_m_status=0;

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != 
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
        }
    }

    /* Fill GRA Range and Status field */
    rs->range = (ITS_OCTET)(num_affected_cics - 1);
    memcpy( rs->status, gra_status, 3);

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_IdleCircuit(ISUP_CIC_INFO *cic_rec,
                   ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_CompareCGUWithGRS(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT             cgu_ev;
    ITS_EVENT             grs_ev;
    ITS_ISUP_IE           cgu_rs_ie;
    ITS_ISUP_IE           grs_rs_ie;
    ITS_OCTET             cgu_sup_msg_type;
    ITS_OCTET             grs_sup_msg_type;
    ITS_USHORT            cgu_cic;
    ITS_USHORT            grs_cic;
    ISUP_RANGE_AND_STATUS grs_rs;
    ISUP_RANGE_AND_STATUS cgu_rs;
    ITS_OCTET             cgu_slen;
    ITS_OCTET             cgu_status[32];
    ITS_OCTET             cgu_range;
    ITS_OCTET             grs_range;
    ITS_OCTET             byte;
    ITS_OCTET             i,j;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, ITS_TRUE);

    ITS_EVENT_INIT(&grs_ev, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);
    memcpy((void *)(grs_ev.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

    __ISUP_Validate_RangeStatus(&grs_ev, cic_rec, config_info, &grs_rs_ie,
                                &grs_sup_msg_type, &grs_cic);

    ITS_EVENT_TERM(&grs_ev);

    ITS_EVENT_INIT(&cgu_ev, ITS_ISUP_ANSI_SRC, cic_msg->cgu_msg_len);
    memcpy((void *)(cgu_ev.data), cic_msg->cgu_msg, cic_msg->cgu_msg_len);

    __ISUP_Validate_RangeStatus(&cgu_ev, cic_rec, config_info, &cgu_rs_ie,
                                &cgu_sup_msg_type, &cgu_cic);

    grs_rs = grs_rs_ie.param_data.rangeAndStatus;

    if(grs_rs.range != 0)
    {
       grs_range = (ITS_OCTET)(grs_rs.range + 1);
    }
    else
    {
       grs_range = 24;
    }

    cgu_slen = (ITS_OCTET)(cgu_rs_ie.param_length - 1);
    cgu_rs = cgu_rs_ie.param_data.rangeAndStatus;

    if(cgu_rs.range != 0)
    {
      cgu_range = (ITS_OCTET)(cgu_rs.range + 1);
    }
    else
    {
      cgu_range = 24;
    }

    memcpy(cgu_status, cgu_rs.status, cgu_slen);

    if (grs_cic == cgu_cic)
    {
       if ( cgu_range <= grs_range )
       {
            SPRC_SendIndToApp_ANSI(ITS_ISUP_RNS_MNSYS_IND, cic_rec);

            __ISUP_StopCGUTimers(cic_rec, config_info);

            return ITS_TRUE;
       }
       else
       {
           for (i = 0; i < cgu_slen; i++)
           {
                byte = cgu_status[i];

                for (j = 0; j < 8; j++)
                {
                    if ((8*i+j) < grs_range)
                    {
                       byte &= ~(1<<j);
                    }

                    cgu_status[i] = byte;
                }
            }
       }
    }

    memcpy(cgu_rs.status, cgu_status, cgu_slen);

    __ISUP_Change_RangeStatus(&cgu_ev, config_info, cgu_rs, ISUP_MSG_CGU);

    /* store the message in cic rec */
    memcpy(cic_msg->cgu_msg, cgu_ev.data, cgu_ev.len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_TRUE);

    ITS_EVENT_TERM(&cgu_ev);

    return ITS_FALSE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_CompareCGBWithGRS(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT             cgb_ev;
    ITS_EVENT             grs_ev;
    ITS_ISUP_IE           cgb_rs_ie;
    ITS_ISUP_IE           grs_rs_ie;
    ITS_OCTET             cgb_sup_msg_type;
    ITS_OCTET             grs_sup_msg_type;
    ITS_USHORT            cgb_cic;
    ITS_USHORT            grs_cic;
    ISUP_RANGE_AND_STATUS grs_rs;
    ISUP_RANGE_AND_STATUS cgb_rs;
    ITS_OCTET             cgb_slen;
    ITS_OCTET             cgb_status[32];
    ITS_OCTET             cgb_range;
    ITS_OCTET             grs_range;
    ITS_OCTET             byte;
    ITS_OCTET             i,j;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, ITS_TRUE);

    ITS_EVENT_INIT(&grs_ev, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);
    memcpy((void *)(grs_ev.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

    __ISUP_Validate_RangeStatus(&grs_ev, cic_rec, config_info, &grs_rs_ie,
                                &grs_sup_msg_type, &grs_cic);

    ITS_EVENT_TERM(&grs_ev);

    ITS_EVENT_INIT(&cgb_ev, ITS_ISUP_ANSI_SRC, cic_msg->cgb_msg_len);
    memcpy((void *)(cgb_ev.data), cic_msg->cgb_msg, cic_msg->cgb_msg_len);

    __ISUP_Validate_RangeStatus(&cgb_ev, cic_rec, config_info, &cgb_rs_ie,
                                &cgb_sup_msg_type, &cgb_cic);

    grs_rs = grs_rs_ie.param_data.rangeAndStatus;

    if(grs_rs.range != 0)
    {
       grs_range = (ITS_OCTET)(grs_rs.range + 1);
    }
    else
    {
       grs_range = 24;
    }

    cgb_slen = (ITS_OCTET)(cgb_rs_ie.param_length - 1);
    cgb_rs = cgb_rs_ie.param_data.rangeAndStatus;

    if(cgb_rs.range != 0)
    {
       cgb_range = (ITS_OCTET)(cgb_rs.range + 1);
    }
    else
    {
       cgb_range = 24;
    }

    memcpy(cgb_status, cgb_rs.status, cgb_slen);

    if (grs_cic == cgb_cic)
    {
       if ( cgb_range <= grs_range )
       {
            SPRC_SendIndToApp_ANSI(ITS_ISUP_RNS_MNSYS_IND, cic_rec);

            __ISUP_StopCGBTimers(cic_rec, config_info);

            return ITS_TRUE;
       }
       else
       {
           for (i = 0; i < cgb_slen; i++)
           {
                byte = cgb_status[i];

                for (j = 0; j < 8; j++)
                {
                    if (8*i+j < grs_range)
                    {
                       byte &= ~(1<<j);
                    }

                    cgb_status[i] = byte;
                }
            }
       }
    }

    memcpy(cgb_rs.status, cgb_status, cgb_slen);

    __ISUP_Change_RangeStatus(&cgb_ev, config_info, cgb_rs, ISUP_MSG_CGB);

    /* store the message in cic rec */
    memcpy(cic_msg->cgb_msg, cgb_ev.data, cgb_ev.len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_TRUE);

    ITS_EVENT_TERM(&cgb_ev);

    return ITS_FALSE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Update contents of a RangeAndStatus param
 *
 *  Input Parameters:
 *      msg: the message containing the param
 *      cic_rec: cic record for the cic pertaining to the message
 *      config_info: config infor for the opc dpc pair
 *      rs_ie: range and status IE from the message
 *      msgType: message type
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_Change_RangeStatus(ITS_EVENT *msg,
                          ISUP_OPC_DPC_INFO *config_info,
                          ISUP_RANGE_AND_STATUS rs_ie,
                          ITS_OCTET msgType)
{
    int         ret = ITS_SUCCESS;
    int         index = 0;
    int         ieCount = 0;
    int         i;
    ITS_USHORT  paramlen = 0;
    ITS_USHORT  len = 0;
    ITS_ISUP_IE ies[5];
    ITS_OCTET   data[ISUP_MAX_MSG_LEN];

    /* initialize local */
    memset((char *)ies, 0, sizeof(ITS_ISUP_IE) * 5);

    /* Get index to param */
    paramlen = (ITS_USHORT)(msg->len - sizeof(ITS_OCTET) - sizeof(ITS_USHORT)
               - sizeof(MTP3_HEADER_ANSI));
    index = msg->len - paramlen;

    /* Need to do Decode */
    ret = ISUP_MTP3Decode_ANSI(&msg->data[index + 1],
                                paramlen,
                                msg->data[index],
                                ies,
                                &ieCount,
                                config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        return ITS_FALSE;
    }

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
          ies[i].param_data.rangeAndStatus = rs_ie;
        }
    }

    /* Need to do Encode */
    ret = ISUP_MTP3Encode_ANSI(data,
                                &len,
                                msgType,
                                ies,
                                ieCount,
                                config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        return ITS_FALSE;
    }

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&msg->data[index +1], (char *)data, len);
    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      CRR helper function
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCompleteCPCOToCRR(ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info)
{
    SPRC_SendRLCToMTP3_ANSI(cic_rec, config_info);

    cic_rec->crr_state = CRR_IDLE;

    return ITS_TRUE;
}

 /****************************************************************************
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCGRRCommon0(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info)
{

    if (cic_rec->fsm_state != IDLE)
    {
       __ISUP_ResetCGRRToCPC(cic_rec, config_info);

    }

    if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state) )
    {
       /* Send Blocking CGRR->BLS */
       __ISUP_BlockingCRRToBLS(cic_rec, config_info);
    }

    if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state) )
    {
        __ISUP_UnblockingCGRRToBLR(cic_rec, config_info);
    }
   __ISUP_StopCGRRToCRO(cic_rec, config_info);
   __ISUP_StopCGRRToCRI(cic_rec, config_info);

    return ITS_TRUE;
}

 /****************************************************************************
 *  Purpose:
 *      Compare request and response.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *      sup_msg_type: Unblocking type
 *      affected_cics: No. of CICs
 *      rs_ie: Range and Status field
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_HandleUnexpectedCGBA(ISUP_CIC_INFO *cic_rec, 
                            ISUP_OPC_DPC_INFO *config_info,
                            ITS_OCTET sup_msg_type,
                            ITS_ISUP_IE rs_ie,
                            ITS_USHORT *affected_cics,
                            ITS_USHORT num_affected_cics)
{

    ITS_EVENT   cgb_ev;
    ITS_ISUP_IE cgb_rs_ie;
    ITS_OCTET   cgb_sup_msg_type;
    ITS_USHORT  cgb_cic;

    int         i, offset=0;
    ITS_OCTET   cgu_slen;
    ITS_OCTET   cgu_range;
    ITS_OCTET   cgu_status[32];
    ITS_BOOLEAN bit_set = ITS_FALSE;
    ITS_BOOLEAN ret = ITS_TRUE;
    ISUP_RANGE_AND_STATUS cgu_rs_ie;
    ITS_USHORT  msg_cic;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
    {
       cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

       ITS_EVENT_INIT(&cgb_ev, ITS_ISUP_ANSI_SRC, cic_msg->cgb_msg_len);

       memcpy((void *)(cgb_ev.data), cic_msg->cgb_msg, cic_msg->cgb_msg_len);
       ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

       __ISUP_Validate_RangeStatus(&cgb_ev, cic_rec, config_info, &cgb_rs_ie,
                                   &cgb_sup_msg_type, &cgb_cic);

       ITS_EVENT_TERM(&cgb_ev);

       if (sup_msg_type == cgb_sup_msg_type)
       {
          return ITS_TRUE;
       }
    }

    /* Sending CGU as got Unexpected CGBA */
    if(rs_ie.param_data.rangeAndStatus.range != 0)
    {
       cgu_slen  = (ITS_OCTET)(rs_ie.param_length - 1);
       cgu_range = (ITS_OCTET)(rs_ie.param_data.rangeAndStatus.range + 1);
    }
    else
    {
       cgu_slen  = 3;
       cgu_range = 24;
    }
    memset ((char *)cgu_status, 0, cgu_slen);

    for(i=0; i < num_affected_cics; i++)
    {
             ret = __ISUP_ProcessAffectedCics(&affected_cics[i],
                                              1,
                                              __ISUP_MGBSCheckLocallyBlocked,
                                              cic_rec,
                                              config_info);
             if (ret == ITS_FALSE)
             {
                msg_cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);
                offset = ((affected_cics[i] - msg_cic) / 8);
                cgu_status[offset] |= 1 << ((affected_cics[i] - msg_cic) % 8);
                bit_set = ITS_TRUE;
             }
    }

    if (bit_set)
    {
       cgu_rs_ie.range = (ITS_OCTET)(cgu_range - 1);
       memcpy(cgu_rs_ie.status, cgu_status, cgu_slen);

       /* Send CGU to L3 */
       SPRC_SendCGUToMTP3_ANSI (cic_rec,
                                config_info,
                                cgu_rs_ie,
                                sup_msg_type);

       __ISUP_StartCGUTimers(cic_rec, config_info);

       cic_rec->mgbs_state = MGBS_WAIT_FOR_CGUA;
       return ITS_FALSE;
    }
    else
    {
       cic_rec->mgbs_state = MGBS_IDLE;
       return ITS_TRUE;
    }
}

 /****************************************************************************
 *  Purpose:
 *      Compare request and response.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *      sup_msg_type: Unblocking type
 *      affected_cics: No. of CICs
 *      rs_ie: Range and Status field
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_HandleUnexpectedCGUA(ISUP_CIC_INFO *cic_rec,
                            ISUP_OPC_DPC_INFO *config_info,
                            ITS_OCTET sup_msg_type,
                            ITS_ISUP_IE rs_ie,
                            ITS_USHORT *affected_cics,
                            ITS_USHORT num_affected_cics)
{
    ITS_EVENT    cgu_ev;
    ITS_ISUP_IE  cgu_rs_ie;
    ITS_OCTET    cgu_sup_msg_type;
    ITS_USHORT   cgu_cic;

    int          i, offset=0;
    ITS_OCTET    cgb_slen;
    ITS_OCTET    cgb_range;
    ITS_OCTET    cgb_status[32];
    ITS_BOOLEAN  ret = ITS_TRUE;
    ITS_BOOLEAN  bit_set = ITS_FALSE;
    ISUP_RANGE_AND_STATUS cgb_rs_ie;
    ITS_USHORT   msg_cic;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
    {
       cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

       ITS_EVENT_INIT(&cgu_ev, ITS_ISUP_ANSI_SRC, cic_msg->cgu_msg_len);

       memcpy((void *)(cgu_ev.data), cic_msg->cgu_msg, cic_msg->cgu_msg_len);
       ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

       __ISUP_Validate_RangeStatus(&cgu_ev, cic_rec, config_info, &cgu_rs_ie,
                                &cgu_sup_msg_type, &cgu_cic);

       ITS_EVENT_TERM(&cgu_ev);

       if (sup_msg_type == cgu_sup_msg_type)
       {
           if ((cgu_rs_ie.param_data.rangeAndStatus.range == 0) &&
               (rs_ie.param_data.rangeAndStatus.range == 0      ||
                rs_ie.param_data.rangeAndStatus.range == 23))
           {
              if (affected_cics[0] == cgu_cic)
              {
                 return ITS_TRUE;
              }
              else
              {
                 return ITS_FALSE;
              }
           }

           if ( (affected_cics[0] != cgu_cic) &&
                (rs_ie.param_data.rangeAndStatus.range !=
                 cgu_rs_ie.param_data.rangeAndStatus.range))
           {
              return ITS_FALSE;
           }

          return ITS_TRUE;
       }
    }

    /* Sending CGB as got Unexpected CGUA */
    if(rs_ie.param_data.rangeAndStatus.range != 0)
    {
       cgb_slen  = (ITS_OCTET)(rs_ie.param_length - 1);
       cgb_range = (ITS_OCTET)(rs_ie.param_data.rangeAndStatus.range + 1);
    }
    else
    {
       cgb_slen  = 3;
       cgb_range = 24;
    }

    memset ((char *)cgb_status, 0, cgb_slen);

    for(i=0; i < num_affected_cics; i++)
    {
             ret = __ISUP_ProcessAffectedCics(&affected_cics[i],
                                              1,
                                              __ISUP_MGBSCheckLocallyBlocked,
                                              cic_rec,
                                              config_info);
             if (ret == ITS_TRUE)
             {
                msg_cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);
                offset = ((affected_cics[i] - msg_cic) / 8);
                cgb_status[offset] |= 1 << ((affected_cics[i] - msg_cic) % 8);
                bit_set = ITS_TRUE;
             }
    }

    if (bit_set)
    {
       cgb_rs_ie.range = (ITS_OCTET)(cgb_range - 1);
       memcpy(cgb_rs_ie.status, cgb_status, cgb_slen);

       /* Send CGB to L3 */
       SPRC_SendCGBToMTP3_ANSI (cic_rec,
                                config_info,
                                cgb_rs_ie,
                                sup_msg_type);

       __ISUP_StartCGBTimers(cic_rec, config_info);

       cic_rec->mgbs_state = MGBS_WAIT_FOR_CGBA;
       return ITS_FALSE;
    }
    else
    {
       cic_rec->mgbs_state = MGBS_IDLE;
       return ITS_TRUE;
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_GetCGBARangeNStatus(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info,
                           ITS_USHORT  *affected_cics,
                           ITS_USHORT  num_affected_cics,
                           ISUP_RANGE_AND_STATUS *rs)
{
    int                    i, offset=0;
    ISUP_PCIC              pcic;
    ITS_UINT               opc, dpc;
    ITS_OCTET              ni;
    ITS_OCTET              cgba_status[3];
    ISUP_CIC_INFO         *affected_cic_rec;
    ITS_BOOLEAN            status_bit = 0;
    ITS_USHORT             msg_cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);


    memset ((char *)cgba_status, 0, 3);

    for (i= 0; i < num_affected_cics; i++)
    {
        if (affected_cics[i] == ISUP_PCIC_TO_CIC(cic_rec->pcic))
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cics[i]);
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
           status_bit = 0;
        }
        else
        {
            if (ISUP_CIC_IS_REM_BLOCKED(affected_cic_rec->cic_state))
            {
               status_bit = 1;
            }

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != 
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
        }

        /* edit status field concerned M_BLOCKED */
        offset = ((affected_cics[i] - msg_cic) / 8);
        cgba_status[offset] |= status_bit << ((affected_cics[i] - msg_cic) % 8);
    }

    /* Fill CGBA Status field */
    memcpy( rs->status, cgba_status, 3);

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_GetCGUARangeNStatus(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info,
                           ITS_USHORT  *affected_cics,
                           ITS_USHORT  num_affected_cics,
                           ISUP_RANGE_AND_STATUS *rs)
{
    int                    i, offset=0;
    ISUP_PCIC              pcic;
    ITS_UINT               opc, dpc;
    ITS_OCTET              ni;
    ITS_OCTET              cgua_status[3];
    ISUP_CIC_INFO         *affected_cic_rec;
    ITS_BOOLEAN            status_bit = 0;
    ITS_USHORT             msg_cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    memset ((char *)cgua_status, 0, 3);

    for (i= 0; i < num_affected_cics; i++)
    {
        if (affected_cics[i] == ISUP_PCIC_TO_CIC(cic_rec->pcic))
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cics[i]);
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            status_bit = 0;
        }
        else
        {
            if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
            {
               status_bit = 0;
            }
            else
            {
               status_bit = 1;
            }

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != 
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
        }

        /* edit status field concerned M_BLOCKED */
        offset = ((affected_cics[i] - msg_cic) / 8);
        cgua_status[offset] |= status_bit << ((affected_cics[i] - msg_cic) %8 );
    }

    /* Fill CGUA Status field */
    memcpy( rs->status, cgua_status, 3);

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Check circuit blocking Status
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_CheckRemotellyBlocked(ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info)
{

    if(ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      MGBR helper function.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *      affected_cics:
 *      num_affected_cics:
 *      sup_msg_type:
 *      rs_ie:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingMGBRCommon1(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info,
                           ITS_USHORT *affected_cics,
                           ITS_USHORT num_affected_cics,
                           ITS_OCTET sup_msg_type,
                           ITS_ISUP_IE rs_ie)
{
    ISUP_CIC_INFO *affected_cic_rec;
    int i;
    ISUP_PCIC pcic;
    ITS_UINT opc, dpc;
    ITS_OCTET ni;
    ITS_BOOLEAN bool_ret = ITS_FALSE;

    for (i = 0; i < num_affected_cics; i++)
    {
        if (affected_cics[i] == ISUP_PCIC_TO_CIC(cic_rec->pcic))
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cics[i]);
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_DEBUG(("Could not find PCIC for CIC %d\n", affected_cics[i]));
        }
        else
        {
            __ISUP_StopMGBRToCRO(affected_cic_rec, config_info);
            __ISUP_StopMGBRToCRI(affected_cic_rec, config_info);

            if (cic_rec->mgbr_state == MGBR_IDLE)
            {
                if (sup_msg_type == BLOCK_WO_RELEASE)
                {
                    __ISUP_BlockingMGBRToBLR(affected_cic_rec, config_info);
                    __ISUP_BlockingMGBRToCPCO(affected_cic_rec, config_info);
                }
                else if (sup_msg_type == BLOCK_W_IMDIAT_RELEASE)
                {
                    __ISUP_BlockingMGBRToBLR(affected_cic_rec, config_info);
                    __ISUP_ResetMGBRToCPC(affected_cic_rec, config_info);
                }
            }

            if (rs_ie.param_data.rangeAndStatus.range == 0)
            {
                bool_ret = __ISUP_CheckRemotellyBlocked(affected_cic_rec, 
                                                        config_info);
            }

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
         }
    }
    return bool_ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      MGBS helper function.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *      affected_cics:
 *      num_affected_cics:
 *      sup_msg_type:
 *      rs_ie:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingMGBSCommon1(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info,
                           ITS_USHORT *affected_cics,
                           ITS_USHORT num_affected_cics,
                           ITS_OCTET sup_msg_type,
                           ITS_ISUP_IE rs_ie)
{
    ISUP_CIC_INFO *affected_cic_rec;
    int i;
    ISUP_PCIC pcic;
    ITS_UINT opc, dpc;
    ITS_OCTET ni;
    ITS_BOOLEAN bool_ret = ITS_TRUE;

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
    {
        /* Stop CGUA Timers */
        __ISUP_StopCGUTimers(cic_rec, config_info);
    }

    for (i = 0; i < num_affected_cics; i++)
    {
        if (affected_cics[i] == ISUP_PCIC_TO_CIC(cic_rec->pcic))
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cics[i]);
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_DEBUG(("Could not find pcic for CIC %d\n", affected_cics[i]));
        }
        else
        {
            __ISUP_StopMGBSToCRO(affected_cic_rec, config_info);
            __ISUP_StopMGBSToCRI(affected_cic_rec, config_info);

            if (sup_msg_type == BLOCK_WO_RELEASE)
            {
                __ISUP_BlockingMGBSToBLS(affected_cic_rec, config_info);

            }
            else if (sup_msg_type == BLOCK_W_IMDIAT_RELEASE)
            {
                __ISUP_BlockingMGBSToBLS(affected_cic_rec, config_info);
                __ISUP_ResetMGBSToCPC(affected_cic_rec, config_info);
            }

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
         }
    }
    return bool_ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      MGBR helper function.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *      affected_cics:
 *      num_affected_cics:
 *      sup_msg_type:
 *      rs_ie:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UnblockingMGBRCommon1(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info,
                           ITS_USHORT *affected_cics,
                           ITS_USHORT num_affected_cics,
                           ITS_ISUP_IE rs_ie)
{
    ISUP_CIC_INFO *affected_cic_rec;
    int i;
    ISUP_PCIC pcic;
    ITS_UINT opc, dpc;
    ITS_OCTET ni;
    ITS_BOOLEAN bool_ret = ITS_TRUE;

    for (i = 0; i < num_affected_cics; i++)
    {
        if (affected_cics[i] == ISUP_PCIC_TO_CIC(cic_rec->pcic))
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, affected_cics[i]);
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_DEBUG(("Could not find PCIC for CIC %d\n", affected_cics[i]));
        }
        else
        {
            __ISUP_UnblockingMGBRToBLR(affected_cic_rec, config_info);

            if (rs_ie.param_data.rangeAndStatus.range == 0)
            {
                bool_ret = __ISUP_CheckRemotellyBlocked(affected_cic_rec, 
                                                             config_info);
            }

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
         }
    }
    return bool_ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_IdleRemoteBlockCircut(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        ISUP_Alarm_ANSI(3016, __FILE__, __LINE__, "cic : %x dpc:%d opc: %d",
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));

        /* Maintenance system indication */
        ISUP_CRITICAL(("Blocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));

        /* Mark CIC state accordingly: Remotely blocked */
        cic_rec->cic_state &= 0xFDU;
        cic_rec->cic_state |= CKTS_RBLOCKED;

        cic_rec->blr_state = BLR_IDLE;
    }

    ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

    return ITS_TRUE;
}
