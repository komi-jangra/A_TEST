/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
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
 *  ID: $Id: itu-validate_param.c,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:11  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.3  2005/05/05 09:32:51  ssingh
 * LOG: fix for bug #1746 (Ramesh K V)
 * LOG:
 * LOG: Revision 9.2  2005/04/08 07:12:27  ssingh
 * LOG: ISUP bug fix propagation (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:58  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.12  2005/03/21 13:54:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.9.2.1.12.1  2004/12/29 14:56:05  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.9.2.1  2004/01/05 10:10:45  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.5.2.5.2.5  2003/12/04 05:48:03  ssingh
 * LOG: Code Correction, GRS/RSC received from App on or included Circuit
 * LOG: having BLS state WAIT_FOR_UBA.
 * LOG:
 * LOG: Revision 7.5.2.5.2.4  2003/11/24 06:40:44  akumar
 * LOG: bug fix cycle.
 * LOG:
 * LOG: Revision 7.5.2.5.2.3  2003/11/14 10:36:29  akumar
 * LOG: Bug Fix #658.
 * LOG:
 * LOG: Revision 7.5.2.5.2.2  2003/11/13 13:17:49  akumar
 * LOG: Bug fixing cycle for TCS-ISUP.
 * LOG:
 * LOG: Revision 7.5.2.5.2.1  2003/09/05 09:44:02  akumar
 * LOG: Modifications for Msg Based redundancy scheme.
 * LOG:
 * LOG: Revision 7.5.2.5  2003/07/25 05:15:11  akumar
 * LOG: ITU National Matter is implemented.
 * LOG:
 * LOG: Revision 7.5.2.4  2003/06/13 03:41:44  akumar
 * LOG: Fixed BUG #354.
 * LOG:
 * LOG: Revision 7.5.2.3  2003/05/07 11:03:13  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.6  2003/05/02 14:36:17  ssingh
 * LOG: ANSI changes propped to ITU (common and related).
 * LOG:
 * LOG: Revision 8.5  2003/05/02 13:54:16  akumar
 * LOG: Bug Fix #226, 237.
 * LOG:
 * LOG: Revision 8.4  2003/04/30 11:16:59  akumar
 * LOG: Removed warnings.
 * LOG:
 * LOG: Revision 8.3  2003/04/30 05:31:15  akumar
 * LOG: Bug Fix #253, 260.
 * LOG:
 * LOG: Revision 8.2  2003/04/04 05:07:20  ssingh
 * LOG: SPRC_SendConfToApp calling is replaced by SPRC_SendIndToApp.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:30  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.5  2003/02/07 13:18:41  akumar
 * LOG: Removed Warnings for CC compiler
 * LOG:
 * LOG: Revision 7.4  2003/01/29 05:02:51  akumar
 * LOG: __ISUP_Change_RangeStatus() argument type made compatible with its sig
 * LOG:
 * LOG: Revision 7.3  2003/01/22 08:40:46  akumar
 * LOG: Added ITU COT procedure
 * LOG:
 * LOG: Revision 7.2  2002/10/10 10:40:12  sjaddu
 * LOG: Added Alarms for ITU93/97.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:37  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.6  2002/08/05 20:57:18  ssharma
 * LOG: Move pegs identifiers from vendors to IntelliSS7.
 * LOG:
 * LOG: Revision 1.5  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.4  2002/07/05 21:12:34  ssharma
 * LOG: Remove warnings on Linux.
 * LOG:
 * LOG: Revision 1.3.2.2  2002/07/10 19:34:16  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.3.2.1  2002/07/06 20:06:42  hbalimid
 * LOG: Fixed all warnings.
 * LOG:
 * LOG: Revision 1.3  2002/06/24 17:00:44  ssingh
 * LOG: Phase 3 missing functionality and auto timer handling.
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:46:49  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.1.2.15  2002/05/09 18:38:10  labuser
 * LOG: Merge from ISUP_APR_19_2002 branch to PR6.
 * LOG:
 * LOG: Revision 1.1.2.14.2.1  2002/04/29 20:40:14  labuser
 * LOG: Fix bug in handling of GRS/GRA.
 * LOG:
 * LOG: Revision 1.1.2.14  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 1.1.2.13  2002/04/01 21:08:02  ssharma
 * LOG: Fix memory leaks in ISUP_FindXX() functions.
 * LOG:
 * LOG: Revision 1.1.2.12  2002/03/28 20:21:07  ssharma
 * LOG: Add CSC file, Reorganize code to separate CSC code to a file.
 * LOG:
 * LOG: Revision 1.1.2.11  2002/03/26 22:30:01  ssharma
 * LOG: Bug fix.
 * LOG:
 * LOG: Revision 1.1.2.10  2002/03/26 22:10:37  ssharma
 * LOG: More changes for CGRS, CGRR.
 * LOG:
 * LOG: Revision 1.1.2.9  2002/03/26 21:41:16  ssharma
 * LOG: Remove duplicate definitions.
 * LOG:
 * LOG: Revision 1.1.2.8  2002/03/22 16:29:00  ssharma
 * LOG: Warning removal, CGRS related changes.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/03/22 16:24:12  ssharma
 * LOG: Warning removal, CGRS related changes.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/03/19 18:08:28  ssharma
 * LOG: Bug fix (FindPcic resulting in 5 second timeout).
 * LOG:
 * LOG: Revision 1.1.2.5  2002/03/19 17:29:11  ssharma
 * LOG: Implement functions for Circuit reset state machines.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/03/14 22:59:06  ssharma
 * LOG: Implement HGBS, HGBR, HLB and HRB
 * LOG:
 * LOG: Revision 1.1.2.3  2002/03/14 15:31:06  ssharma
 * LOG: Change signature of Validate_RangeStatus, add CSC state machines.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/03/05 21:26:58  ssharma
 * LOG: Validate range and status parameter.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/03/05 14:55:37  ssharma
 * LOG: Add new file that contains parameter validation functions.
 * LOG:
 *
 *****************************************************************************/

#undef ANSI
#undef CCITT
#define CCITT

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <itu/isup.h>
#include <isup_intern.h>
#include <itu/isup_93.h>

/* Forward Declaration */
static void __ISUP_StopWaitingCGRS(ISUP_CIC_INFO *cic_rec,
                                   ISUP_OPC_DPC_INFO *config_info);

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
int
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
int
__ISUP_GetBitsSet(ISUP_RANGE_AND_STATUS rs, ITS_OCTET len, 
                  ITS_USHORT *bit_offsets, ITS_USHORT *num_bit_offsets)
{
    ITS_OCTET range=rs.range;
    ITS_OCTET *ptr=rs.status;
    ITS_OCTET byte;
    int i, j;
    
    *num_bit_offsets = 0;


    for (i = 0; i < len; i++)
    {
        byte = ptr[i];

        for (j = 0; j < 8; j++)
        {
            if ((byte >> j) & 0x01)
            {
                if (8*i+j <= range)
                {
                   bit_offsets[*num_bit_offsets] = 8 * i + j;

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
int
__ISUP_GetBitsUnset(ISUP_RANGE_AND_STATUS rs, ITS_OCTET len, 
                    ITS_USHORT *bit_offsets, ITS_USHORT *num_bit_offsets)
{
    ITS_OCTET range=rs.range;
    ITS_OCTET *ptr=rs.status;
    ITS_OCTET byte;
    int i, j;
    
    *num_bit_offsets = 0;


    for (i = 0; i < len; i++)
    {
        byte = ptr[i];

        for (j = 0; j < 8; j++)
        {
            if (!((byte >> j) & 0x01)) 
            {
                if (8*i+j <= range)
                {
                   bit_offsets[*num_bit_offsets] = 8 * i + j;

                   *num_bit_offsets += 1;
                }
            }
        }
    }

    return (ITS_SUCCESS);
}


#if 0
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
int
__ISUP_Change_RangeStatus(ITS_EVENT *msg,
                          ISUP_OPC_DPC_INFO *config_info,
                          ISUP_RANGE_AND_STATUS rs_ie,
                          ITS_UINT msgType)
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
    paramlen = msg->len - sizeof(ITS_OCTET) - sizeof(ITS_USHORT)
               - sizeof(MTP3_HEADER_CCITT);
    index = msg->len - paramlen;

    /* Need to do Decode */
    ret = ISUP_MTP3Decode_CCITT(&msg->data[index + 1],
                                paramlen,
                                msg->data[index],
                                ies,
                                &ieCount,
                                config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
          ies[i].param_data.rangeAndStatus = rs_ie;
        }
    }

    /* Need to do Encode */
    ret = ISUP_MTP3Encode_CCITT(data, 
                                &len,
                                msgType,
                                ies,
                                ieCount,
                                config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&msg->data[index +1], (char *)data, len);
    return ITS_SUCCESS;
}
#endif


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
int
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
    ITS_OCTET bits;
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
    cic_index = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_CCITT);
    *cic = (msg->data[cic_index + 1] << 8) + msg->data[cic_index];
    
    /* Validate param */

    paramlen = msg->len - sizeof(ITS_OCTET) - sizeof(ITS_USHORT)
                       - sizeof(MTP3_HEADER_CCITT);
    index = msg->len - paramlen;

    /* Need to do a Decode as TLV style is not being used. */
    ret = ISUP_MTP3Decode_CCITT(&msg->data[index + 1], 
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
            slen = ies[i].param_length - 1; 

            if (rslen > 33)
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
                    if (range == 0 || range > 255)
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    bits = __ISUP_NumBitsSet(rs.status, slen);
                    if (bits > 32)
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    if (slen == 0 && range != 0)
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    break;

                case ISUP_MSG_GRA:
                    if ((range == 0) || (range > 31))
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    if (slen > 4)
                    {
                        return ITS_BADISUPMESSAGE;
                    } 
                    break;

                /* only range */
                case ISUP_MSG_GRS:
                    if ((range == 0) || (range > 31))
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    if (slen != 0)
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    break;
         
                case ISUP_MSG_CQM:
                    if (range > 31)
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    if (slen != 0)
                    {
                        return ITS_BADISUPMESSAGE;
                    }
                    break;

                case ISUP_MSG_CQR:
                    if (slen != 0)
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
int
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
    slen = rs_ie->param_length - 1; 

    rs = rs_ie->param_data.rangeAndStatus; 

    /* __ISUP_GetBitsSet(rs.status, slen, bit_offsets, &num_bit_offsets); */
    __ISUP_GetBitsSet(rs, slen, bit_offsets, &num_bit_offsets);

    for (i = 0; i < num_bit_offsets; i++)
    {
        next_cic = cic + bit_offsets[i];

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
int
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
    slen = rs_ie->param_length - 1; 

    rs = rs_ie->param_data.rangeAndStatus; 

    /*__ISUP_GetBitsSet(rs.status, slen, bit_offsets, &num_bit_offsets);*/
    __ISUP_GetBitsSet(rs, slen, bit_offsets, &num_bit_offsets);
    /*__ISUP_GetBitsUnset(rs.status, slen, bit_offsets2, &num_bit_offsets2);*/
    __ISUP_GetBitsUnset(rs, slen, bit_offsets2, &num_bit_offsets2);

    for (i = 0; i < num_bit_offsets; i++)
    {
        next_cic = cic + bit_offsets[i];

        set_cics[*num_set_cics] = next_cic;
        
        *num_set_cics += 1;
    }

    for (i = 0; i < num_bit_offsets2; i++)
    {
        next_cic = cic + bit_offsets2[i];

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
int
__ISUP_GetGRSCics(ITS_USHORT cic, ITS_ISUP_IE *rs_ie, 
                  ITS_USHORT *grs_cics, 
                  ITS_USHORT *num_grs_cics)
{
    int i;
    ISUP_RANGE_AND_STATUS rs; /* the param in the message */
    ITS_USHORT next_cic;

    *num_grs_cics = 0;

    rs = rs_ie->param_data.rangeAndStatus; 

    for (i = 0; i <= rs.range; i++)
    {
        next_cic = cic + i;

        grs_cics[*num_grs_cics] = next_cic;
        
        *num_grs_cics += 1;
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
ITS_BOOLEAN
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
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

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
            affected_cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
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
                        ISUP_ReleaseCic(affected_cic_rec, isdsmlocal);
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
                ISUP_ReleaseCic(affected_cic_rec, isdsmlocal);
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
ITS_BOOLEAN
__ISUP_CompareCGBAWithCGB(ITS_EVENT *cgba_ev,ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT cgb_ev;
    ITS_ISUP_IE cgb_rs_ie;
    ITS_OCTET cgb_sup_msg_type;
    ITS_USHORT cgb_cic;
    ITS_ISUP_IE cgba_rs_ie;
    ITS_OCTET cgba_sup_msg_type;
    ITS_USHORT cgba_cic;
    ITS_USHORT cgb_affected_cics[256];
    ITS_USHORT cgb_num_affected_cics;
    ITS_USHORT cgba_affected_cics[256];
    ITS_USHORT cgba_num_affected_cics;
    ITS_USHORT cgb_index = 0;
    ITS_USHORT cgba_index = 0;
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_BOOLEAN bool_ret = ITS_TRUE;
    ITS_BOOLEAN more_cgb, more_cgba;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, isdsmlocal);

    ITS_EVENT_INIT(&cgb_ev, ITS_ISUP_CCITT_SRC, cic_msg->cgb_msg_len);

    memcpy((void *)(cgb_ev.data), cic_msg->cgb_msg, cic_msg->cgb_msg_len);
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

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
ITS_BOOLEAN
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
    ITS_USHORT cgu_affected_cics[256];
    ITS_USHORT cgu_num_affected_cics;
    ITS_USHORT cgua_affected_cics[256];
    ITS_USHORT cgua_num_affected_cics;
    int cgu_index = 0;
    int cgua_index = 0;
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_BOOLEAN bool_ret = ITS_TRUE;
    ITS_BOOLEAN more_cgu, more_cgua;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, isdsmlocal);

    ITS_EVENT_INIT(&cgu_ev, ITS_ISUP_CCITT_SRC, cic_msg->cgu_msg_len);

    memcpy((void *)(cgu_ev.data), cic_msg->cgu_msg, cic_msg->cgu_msg_len);
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

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
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA);

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
ITS_BOOLEAN
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

    ITS_EVENT_INIT(&grs_ev, ITS_ISUP_CCITT_SRC, cic_msg->grs_msg_len);

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
ITS_BOOLEAN
__ISUP_BlockingMGBSToBLS(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_IDLE)
    {
        /* Mark CIC state accordingly: Locally Blocked */
        cic_rec->cic_state &= 0xFEU;
        cic_rec->cic_state |= CKTS_LBLOCKED;         

        cic_rec->bls_state = BLS_LBLOCKED;
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        __ISUP_StopBLOTimers(cic_rec, config_info);

        cic_rec->bls_state = BLS_LBLOCKED;        
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
    {
        __ISUP_StopUBLTimers(cic_rec, config_info);

        cic_rec->bls_state = BLS_LBLOCKED;        
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
ITS_BOOLEAN
__ISUP_BlockingMGBRToCPCO(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->fsm_state == WAIT_INCOMING_ACM ||
        cic_rec->fsm_state == WAIT_CONTINUITY_REPORT)
    {
        /* Stop timer T7 */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

        /* Send REATTEMPT indic to app */
        SPRC_SendIndToApp_CCITT(ITS_ISUP_REL_REATTEMPT_IND, cic_rec);

        /* Send REL to L3 */
        SPRC_SendRELToMTP3_CCITT(CI_CAUSE_NORMAL_UNSPECIFIED,
                                 cic_rec,
                                 config_info);
 
        /* Start T5 and T1 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
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
ITS_BOOLEAN
__ISUP_MGBSCheckLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_LBLOCKED)
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
ITS_BOOLEAN
__ISUP_MGBSCheckNotLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_LBLOCKED)
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
ITS_BOOLEAN
__ISUP_BlockingMGBRToBLR(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_IDLE)
    {
        /* Mark CIC state accordingly: Remotely blocked */
        cic_rec->cic_state &= 0xFDU;
        cic_rec->cic_state |= CKTS_RBLOCKED;

        cic_rec->blr_state = BLR_RBLOCKED;
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
    {
        /* Mark CIC state accordingly: Remotely blocked */
        cic_rec->cic_state &= 0xFDU;
        cic_rec->cic_state |= CKTS_RBLOCKED;

        cic_rec->blr_state = BLR_RBLOCKED;       
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
    {
        cic_rec->blr_state = BLR_RBLOCKED;        
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
ITS_BOOLEAN
__ISUP_UnblockingMGBSToBLS(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_LBLOCKED)
    {
        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

        cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        __ISUP_StopBLOTimers(cic_rec, config_info);

        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

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
ITS_BOOLEAN
__ISUP_UnblockingMGBRToBLR(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_RBLOCKED)
    {
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
    {
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;      
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
    {
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
ITS_BOOLEAN
__ISUP_BlockingBLSToCPC(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXED: To be done */
    /* nothing to do ??? */

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
ITS_BOOLEAN
__ISUP_BlockingCRRToBLS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        SPRC_SendBLOToMTP3_CCITT(cic_rec, config_info);

        /* This is not in SDL */
        __ISUP_StopBLOTimers(cic_rec, config_info);
        
        __ISUP_StartBLOTimers(cic_rec, config_info);
    }
    else if (cic_rec->bls_state == BLS_LBLOCKED)
    {
        SPRC_SendBLOToMTP3_CCITT(cic_rec, config_info);

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
ITS_BOOLEAN
__ISUP_BlockingCPCIToBLS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        SPRC_SendBLOToMTP3_CCITT(cic_rec, config_info);

        /* This is not in SDL */
        __ISUP_StopBLOTimers(cic_rec, config_info);

        __ISUP_StartBLOTimers(cic_rec, config_info);
    }
    else if (cic_rec->bls_state == BLS_LBLOCKED)
    {
        SPRC_SendBLOToMTP3_CCITT(cic_rec, config_info);

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
ITS_BOOLEAN
__ISUP_UnblockingCRSToBLS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CRS to BLS, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        __ISUP_StopBLOTimers(cic_rec, config_info);

        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

        cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_LBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("CIC unblocked, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

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
ITS_BOOLEAN
__ISUP_UnblockingCGRSToBLS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CGRS to BLS, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        __ISUP_StopBLOTimers(cic_rec, config_info);

        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

        cic_rec->cgrr_m_status = 0;
        cic_rec->bls_state = BLS_IDLE;
    }
    else if (cic_rec->bls_state == BLS_LBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("CIC unblocked, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: Locally Un-Blocked */
        cic_rec->cic_state &= 0xFEU;

        cic_rec->cgrr_m_status = 0;
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
ITS_BOOLEAN
__ISUP_BlockingBLRToCPCO(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->fsm_state == WAIT_INCOMING_ACM ||
        cic_rec->fsm_state == WAIT_CONTINUITY_REPORT)
    {
        /* Stop timer T7 */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

        /* Send REATTEMPT indic to app */
        SPRC_SendIndToApp_CCITT(ITS_ISUP_REL_REATTEMPT_IND, cic_rec);

        /* Send REL to L3 */
        SPRC_SendRELToMTP3_CCITT(CI_CAUSE_NORMAL_UNSPECIFIED,
                                 cic_rec,
                                 config_info);

        /* Start T5 and T1 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
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
ITS_BOOLEAN
__ISUP_BlockingCGRSToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->fsm_state == WAIT_OUTGOING_GRA)
    {
        return ITS_TRUE;
    }
    if (cic_rec->blr_state == BLR_IDLE)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3417, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Blocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: Remotely blocked */
        cic_rec->cic_state &= 0xFDU;
        cic_rec->cic_state |= CKTS_RBLOCKED;

        cic_rec->blr_state = BLR_RBLOCKED; 
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3417, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Blocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: Remotely blocked */
        cic_rec->cic_state &= 0xFDU;
        cic_rec->cic_state |= CKTS_RBLOCKED;

        cic_rec->blr_state = BLR_RBLOCKED;
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3417, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Blocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        cic_rec->blr_state = BLR_RBLOCKED;
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
ITS_BOOLEAN
__ISUP_UnblockingCRRToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3418, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CRR to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3418, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CRR to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
    {
        ISUP_Alarm_CCITT(3418, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

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
ITS_BOOLEAN
__ISUP_UnblockingCRSToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
    {
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
ITS_BOOLEAN
__ISUP_UnblockingCGRRToBLR(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3420, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CGRR to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3420, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CGRR to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
    {
        ISUP_Alarm_CCITT(3420, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

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
ITS_BOOLEAN
__ISUP_UnblockingCPCIToBLR(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3421, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CPCI to BLR, pcic 0x%08x, vcic %d.\n",
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
ITS_BOOLEAN
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
ITS_BOOLEAN
__ISUP_ResetCGRRToMGBR(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->mgbr_state == MGBR_WAIT_FOR_UBL_RESP)
    {
        cic_rec->mgbr_state = MGBR_IDLE;
    }
    else if (cic_rec->mgbr_state == MGBR_WAIT_FOR_BLO_RESP)
    {
        cic_rec->mgbr_state = MGBR_IDLE;
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
ITS_BOOLEAN
__ISUP_ResetCGRSToMGBR(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->mgbr_state == MGBR_WAIT_FOR_BLO_RESP)
    {
        cic_rec->mgbr_state = MGBR_IDLE;
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
ITS_BOOLEAN
__ISUP_BlockingHGBSToHLB(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hlb_state == HLB_IDLE)
    {
        /* Mark CIC state accordingly: HW Locally Blocked */
        cic_rec->cic_state &= 0xEFU;
        cic_rec->cic_state |= (CKTS_LBLOCKED << 4);

        cic_rec->hlb_state = HLB_LBLOCKED;
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
ITS_BOOLEAN
__ISUP_ReleaseHGBSToCPC(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXED */
    ITS_BOOLEAN ret = ITS_TRUE; 

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         break;

    case WAIT_INCOMING_ACM :
         /* call failure indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CALL_FAILURE_IND,cic_rec);

         /* stop T7 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_CONTINUITY_REPORT :
        if(cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            __ISUP_StopCPCToCCO(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
        }
        cic_rec->fsm_state = IDLE;
        break;
    case WAIT_INCOMING_COT :
        if(cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            __ISUP_StopCPCToCCI(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }
        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_ANM :
         /* call failure indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CALL_FAILURE_IND, cic_rec);

         /* stop T9 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T9);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* Change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case RCVD_INCOMING_ANM :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND,cic_rec);

         /* stop charging */

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_RLC :
         /* release conf */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND,cic_rec);

         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         /* idle cpc */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_ACM :
    case WAIT_OUTGOING_ANM :
         /* call failure indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CALL_FAILURE_IND, cic_rec);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case SENT_OUTGOING_ANM :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_RLC :
         /* idle cpc */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_RES :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);
  
         /* Stop timers T6 and T38; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T38);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* Change state to Idle */
         cic_rec->fsm_state = IDLE;
   
         break;

    case WAIT_OUTGOING_RES :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
    default:
         ret  = ITS_FALSE;
         return ret;
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
ITS_BOOLEAN
__ISUP_UnblockingCRSToHLB(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hlb_state == HLB_LBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CRS to HLB, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: HW Locally Unblocked */
        cic_rec->cic_state &= 0xEFU;

        cic_rec->hlb_state = HLB_IDLE;
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
ITS_BOOLEAN
__ISUP_UnblockingCGRSToHLB(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hlb_state == HLB_LBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CGRS to HLB, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: HW Locally Unblocked */
        cic_rec->cic_state &= 0xEFU;

        cic_rec->hlb_state = HLB_IDLE;
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
ITS_BOOLEAN
__ISUP_UnblockingHGBSToHLB(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hlb_state == HLB_LBLOCKED)
    {
        /* Mark CIC state accordingly: HW Locally Unblocked */
        cic_rec->cic_state &= 0xEFU;

        cic_rec->hlb_state = HLB_IDLE;
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
ITS_BOOLEAN
__ISUP_BlockingHGBRToHRB(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hrb_state == HRB_IDLE)
    {
        /* Mark CIC state accordingly: HW Remotely Blocked */
        cic_rec->cic_state &= 0xDFU;
        cic_rec->cic_state |= (CKTS_RBLOCKED << 4);

        cic_rec->hrb_state = HRB_RBLOCKED;
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
ITS_BOOLEAN
__ISUP_UnblockingCRSToHRB(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hrb_state == HRB_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CRS to HRB, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: HW Remotely Unblocked */
        cic_rec->cic_state &= 0xDFU;

        cic_rec->hrb_state = HRB_IDLE;
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
ITS_BOOLEAN
__ISUP_UnblockingCRRToHRB(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hrb_state == HRB_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3425, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CRR to HRB, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: HW Remotely Unblocked */
        cic_rec->cic_state &= 0xDFU;

        cic_rec->hrb_state = HRB_IDLE;
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
ITS_BOOLEAN
__ISUP_UnblockingCGRSToHRB(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hrb_state == HRB_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CGRS to HRB, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: HW Remotely Unblocked */
        cic_rec->cic_state &= 0xDFU;

        cic_rec->hrb_state = HRB_IDLE;
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
ITS_BOOLEAN
__ISUP_UnblockingCGRRToHRB(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hrb_state == HRB_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3427, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CGRR to HRB, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: HW Remotely Unblocked */
        cic_rec->cic_state &= 0xDFU;

        cic_rec->hrb_state = HRB_IDLE;
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
ITS_BOOLEAN
__ISUP_UnblockingCPCIToHRB(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hrb_state == HRB_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_Alarm_CCITT(3428, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

        ISUP_CRITICAL(("Unblocking CPCI to HRB, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 

        /* Mark CIC state accordingly: HW Remotely Unblocked */
        cic_rec->cic_state &= 0xDFU;

        cic_rec->hrb_state = HRB_IDLE;
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
ITS_BOOLEAN
__ISUP_UnblockingHGBRToHRB(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hrb_state == HRB_RBLOCKED)
    {
        /* Mark CIC state accordingly: HW Remotely Unblocked */
        cic_rec->cic_state &= 0xDFU;

        cic_rec->hrb_state = HRB_IDLE;
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
ITS_BOOLEAN
__ISUP_BlockingCRRToHGBS(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hgbs_state == HGBS_IDLE)
    {
        /* FIXED */
        SPRC_SendHWBToMTP3_CCITT(cic_rec, config_info);

        __ISUP_StartCGBTimers(cic_rec, config_info);

        cic_rec->hgbs_state = HGBS_WAIT_FOR_CGBA;
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
ITS_BOOLEAN
__ISUP_BlockingCGRRToHGBS(ITS_USHORT *affected_cics,
                          ITS_USHORT num_affected_cics,
                          ISUP_CIC_INFO *cic_rec,
                          ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_CIC_INFO         *affected_cic_rec;
    int                    i, count, number_h_bits = 0;
    ISUP_PCIC              pcic;
    ITS_UINT               opc, dpc;
    ITS_OCTET              ni;
    ITS_OCTET              cgb_status[32];
    ITS_USHORT             start_cic;
    ISUP_RANGE_AND_STATUS  rs;
    ITS_BOOLEAN            isdsmlocal = ITS_TRUE;

    if (cic_rec->hgbs_state == HGBS_IDLE)
    {
        memset ((char *)cgb_status, 0, 32);

        count = 0;

        start_cic = affected_cics[0];

        for (i= 0; i < num_affected_cics; i++)
        {
            /* FIXED */
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
                affected_cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
            }
    
            if (affected_cic_rec == NULL)
            {
                ISUP_ERROR(("Could not find PCIC\n"));
            }
            else
            {
                cgb_status[count] |= affected_cic_rec->cgrr_h_status << i%8;
    
                if (affected_cic_rec->cgrr_h_status == 1) 
                {
                    number_h_bits++;
                    affected_cic_rec->cgrr_h_status=0;
                }

                if ((i + 1) % 8 == 0) 
                    count++;

                if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                                 ISUP_PCIC_TO_CIC(cic_rec->pcic))
                {
                    ISUP_ReleaseCic(affected_cic_rec, isdsmlocal);
                }
            }
        }
    
        if (number_h_bits != 0)
        {
            rs.range = num_affected_cics - 1;
            memcpy(rs.status, cgb_status, 32);
    
            cic_rec->hgbs_state = HGBS_WAIT_FOR_CGBA;
    
            SPRC_SendHWGBToMTP3_CCITT(cic_rec, config_info, rs);
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
ITS_BOOLEAN
__ISUP_BlockingCPCIToHGBS(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hgbs_state == HGBS_IDLE)
    {
        /* FIXED */

        /* Send CGB (hw block) for the cic */
        SPRC_SendHWBToMTP3_CCITT(cic_rec, config_info);

        __ISUP_StartCGBTimers(cic_rec, config_info);

        cic_rec->hgbs_state = HGBS_WAIT_FOR_CGBA;
    }

    return ITS_TRUE;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      HGBS helper function
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
ITS_BOOLEAN
__ISUP_HGBSCheckLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hlb_state == HLB_LBLOCKED)
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
 *      HGBS helper function
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
ITS_BOOLEAN
__ISUP_HGBSCheckNotLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hlb_state == HLB_LBLOCKED)
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
ITS_BOOLEAN
__ISUP_ResetCGRSToHGBS(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{

    ITS_BOOLEAN ret;

    if (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGBA)
    {
        /* FIXED: see page 97 of Q.764 Annex H */
        ret = __ISUP_CompareCGBWithGRS(cic_rec, config_info);

        if (ret == ITS_TRUE)
        {
            cic_rec->hgbs_state = HGBS_IDLE;
        }
    }
    else if (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGUA)
    {
        /* FIXED: see page 99 of Q.764 Annex H */
        ret = __ISUP_CompareCGUWithGRS(cic_rec, config_info);

        if (ret == ITS_TRUE)
        {
            cic_rec->hgbs_state = HGBS_IDLE;
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
ITS_BOOLEAN
__ISUP_ReleaseHGBRToCPC(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    /*FIXED: */
    ITS_BOOLEAN ret = ITS_TRUE;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         break;

    case WAIT_CONTINUITY_REPORT :
        if(cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            __ISUP_StopCPCToCCO(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
        }
        cic_rec->fsm_state = IDLE;
        break;
    case WAIT_INCOMING_COT :
        if(cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            __ISUP_StopCPCToCCI(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }
        cic_rec->fsm_state = IDLE;
        break;

    case WAIT_INCOMING_ACM :
         /* call failure indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CALL_FAILURE_IND, cic_rec);

         /* stop T7 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_ANM :
         /* call failure indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CALL_FAILURE_IND, cic_rec);

         /* stop T9 timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T9);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case RCVD_INCOMING_ANM :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* stop charging */

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_RLC :
         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         /* idle cpc */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_ACM :
    case WAIT_OUTGOING_ANM :
         /* call failure indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CALL_FAILURE_IND, cic_rec);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case SENT_OUTGOING_ANM :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* idle cpc */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_OUTGOING_RLC :
         /* idle cpc */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

    case WAIT_INCOMING_RES :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);
  
         /* Stop timers T6 and T38; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T38);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
   
         break;

    case WAIT_OUTGOING_RES :
         /* release indication */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

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
ITS_BOOLEAN
__ISUP_ResetCGRRToHGBR(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hgbr_state == HGBR_WAIT_FOR_UBL_RESP)
    {
        cic_rec->hgbr_state = HGBR_IDLE;
    }
    else if (cic_rec->hgbr_state == HGBR_WAIT_FOR_BLO_RESP)
    {
        cic_rec->hgbr_state = HGBR_IDLE;
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
ITS_BOOLEAN
__ISUP_ResetCGRSToHGBR(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->hgbr_state == HGBR_WAIT_FOR_BLO_RESP)
    {
        cic_rec->hgbr_state = HGBR_IDLE;
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
ITS_BOOLEAN
__ISUP_ResetCRSCommon1(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED) ||
            (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCRSToBLS(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_RBLOCKED) ||
            (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCRSToBLR(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LBLOCKED) ||
            (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCRSToHLB(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_RBLOCKED) ||
            (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCRSToHRB(cic_rec, config_info);
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
ITS_BOOLEAN
__ISUP_ResetCRSCommon2(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_ResetCRSCommon1(cic_rec, config_info);

    /* CONTINUITY checks */
    __ISUP_StopCRRToCRO(cic_rec, config_info);
    __ISUP_StopCRRToCRI(cic_rec, config_info);
    
    ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);

    SPRC_SendRSCToMTP3_CCITT(cic_rec, config_info);

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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Added Error Indication to 
 *                           #389           Application with Message type.
 *
 *  kramesh     05-05-2005   Bug fix #1746  Added the Reattempt Indication.
 ****************************************************************************/
ITS_BOOLEAN
__ISUP_ResetCPCToCRS(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->crs_state == CRS_IDLE)
    {
        /* Start Reset Indic to CC */
        if ( cic_rec->fsm_state == WAIT_INCOMING_ACM)
        {
            SPRC_SendIndToApp_CCITT(ITS_ISUP_RSC_REATTEMPT_IND, cic_rec);
        }
        else
        {
            SPRC_SendIndToApp_CCITT(ITS_ISUP_START_RESET_IND, cic_rec);
        }

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
ITS_BOOLEAN
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
ITS_BOOLEAN
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
ITS_BOOLEAN
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
ITS_BOOLEAN
__ISUP_ResetCRSToCPC(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXED */
    ITS_BOOLEAN ret = ITS_TRUE;

    switch (cic_rec->fsm_state)
    {
    case IDLE :

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
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* T5 and T1 stop */
        __ISUP_StopRELTimers(cic_rec, config_info);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;

         break;

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

         /* Stop timers T1 and T38; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T38);

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
ITS_BOOLEAN
__ISUP_ResetCRRToCPC(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;

    /* FIXED: for other states */
    switch (cic_rec->fsm_state)
    {
    case IDLE :
         __ISUP_ResetCompleteCPCIToCRR(cic_rec, config_info);

         /* return ITS_FALSE so that CRR state is not changed */
         ret = ITS_FALSE;

         break;

    case WAIT_CONTINUITY_REPORT :
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
            SPRC_SendIndToApp_CCITT(ITS_ISUP_RSC_REATTEMPT_RQIND, cic_rec);

            /* Idle CPC & Change State to IDLE */
            ISUP_ClearCic(cic_rec);
        }
        break;

    case WAIT_INCOMING_COT :
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);

            /* Incoming release request */
            /* Idle CPC & Change State to IDLE */
            ISUP_ClearCic(cic_rec);
        }
        break;

    case WAIT_INCOMING_ACM :
         /* T7 stop */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Reset indication (reattampt) cpco->ssco */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_RSC_REATTEMPT_IND, cic_rec);

         /* change state to "wait for OGC reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_RLC;
         break;

    case RCVD_INCOMING_ANM :
         /* stop charging */

         /* Reset indication cpco->ssco */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state to "wait for OGC reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_RLC;
         break;

    case WAIT_INCOMING_RLC :
         /*reset complete (cpco->crr) */
         __ISUP_ResetCompleteCPCOToCRR(cic_rec, config_info);

         /* Release Conformation */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         /* Idle CPC & set state to IDLE */
         ISUP_ClearCic(cic_rec);

         break;

    case WAIT_OUTGOING_ACM :
    case WAIT_OUTGOING_ANM :
    case SENT_OUTGOING_ANM :
         /* Send Reset IND  cpci->ssci */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state "wait for icc reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_RLC;

         break;

    case WAIT_OUTGOING_RLC :
         /* Reset complete (cpci->crr) */
         __ISUP_ResetCompleteCPCIToCRR(cic_rec, config_info);

         /* return ITS_FALSE so that CRR state is not changed */
         ret = ITS_FALSE;

         /* Idle CPC & Change State to IDLE */
         ISUP_ClearCic(cic_rec);

         break;

    case WAIT_INCOMING_RES :
         /* stop charging */

         /* Stop timers T6 and T38; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T38);

         /* Send Reset Indication (cpco -> ssco) */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state "wait_for_OGC_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_RLC;

         break;

    case WAIT_OUTGOING_RES :
         /* Send Reset Indication (cpco -> ssco) */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state "wait_for_ICC_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_RLC;

         break;

    case WAIT_INCOMING_ANM :
    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
    default:
         ret = ITS_FALSE;
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
ITS_BOOLEAN
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
ITS_BOOLEAN
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
ITS_BOOLEAN
__ISUP_ResetCompleteCPCIToCRR(ISUP_CIC_INFO *cic_rec, 
                             ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXED: set release code */
    SPRC_SendRLCToMTP3_CCITT(CI_CAUSE_NORMAL, cic_rec, config_info);

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
ITS_BOOLEAN
__ISUP_ResetCGRSCommon1(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{
    if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED) ||
            (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCGRSToBLS(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_RBLOCKED) ||
            (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCGRSToBLR(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LBLOCKED) ||
            (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCGRSToHLB(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_RBLOCKED) ||
            (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCGRSToHRB(cic_rec, config_info);
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
ITS_BOOLEAN
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

    /* Continuity Checks */
    __ISUP_StopCGRSToCRO(cic_rec, config_info);
    __ISUP_StopCGRSToCRI(cic_rec, config_info);

    cic_rec->cgrr_m_status = 0;

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
ITS_BOOLEAN
__ISUP_UnblockingCGRSToBLR(ISUP_CIC_INFO *cic_rec, 
                           ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_RBLOCKED)
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("Unblocking CGRS to BLR, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
        
        /* Mark CIC state accordingly: Remotely Un-blocked */
        cic_rec->cic_state &= 0xFDU;

        cic_rec->blr_state = BLR_IDLE;
    }
    else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
    {
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
ITS_BOOLEAN
__ISUP_ResetCGRSToCPC(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXED */
    ITS_BOOLEAN ret = ITS_TRUE;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
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
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND,cic_rec);

         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         /* Idle  CPC */
         ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

         /* change state to Idle */
         cic_rec->fsm_state = IDLE;
    break;

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
         /* Stop timers T6 and T38; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T38);

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
ITS_BOOLEAN
__ISUP_ResetCGRRCommon1(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info)
{

    /* FIXED: code according to H.38/Q.764 page 109 */
    /*
     * M-blocked circuits status bit is set to "1" for GRA
     * H-blocked circuits status bit is set to "1" for CGB
     */

    __ISUP_ResetCGRRToCPC(cic_rec, config_info);
    
    /* CONTINUITY checks */
    __ISUP_StopCGRRToCRO(cic_rec, config_info);
    __ISUP_StopCGRRToCRI(cic_rec, config_info);

    if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_RBLOCKED) ||
            (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCGRRToBLR(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_RBLOCKED) ||
            (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
    {
        __ISUP_UnblockingCGRRToHRB(cic_rec, config_info);
    }
    if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED))
    {
        if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
        {
            cic_rec->cgrr_m_status = 0;
        }
        else
        {
            cic_rec->cgrr_m_status = 1;
        }
    }
    else
    {
        cic_rec->cgrr_m_status = 0;
    }

    if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LBLOCKED))
    {
        /* FIXME: Check for HGBS_state, but currently that only applies */
        /* to the first CIC in the group. At some point it can be fixed */

         cic_rec->cgrr_h_status= 1;
    }
    else
    {
         cic_rec->cgrr_h_status= 0;
    }

    /* Change the CIC state to transient before sending GRS to App */
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
ITS_BOOLEAN
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
ITS_BOOLEAN
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
ITS_BOOLEAN
__ISUP_ResetCGRRToCPC(ISUP_CIC_INFO *cic_rec, 
                      ISUP_OPC_DPC_INFO *config_info)
{
    /* FIXED for other states */
    ITS_BOOLEAN ret = ITS_TRUE;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         /* Removed because of change in the way of handling */ 
         /* __ISUP_ResetCompleteCPCToCGRR(cic_rec, config_info); */

         /* change state to "wait_for_OGC_group_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_GRA;

         break;

    case WAIT_INCOMING_ACM :
         /* T7 stop */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Send Reset indication (cpco->ssco)  */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state to "wait_for_OGC_group_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_GRA;

         break;

    case WAIT_INCOMING_ANM :
         /* Send Reset indication (cpco->ssco)  */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state to "wait_for_OGC_group_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_GRA;

         break;

    case RCVD_INCOMING_ANM :
         /* stop charging */

         /* send Reset Indication (cpco->ssco) */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state to "wait_for_OGC_group_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_GRA;

         break;

    case WAIT_INCOMING_RLC :
         /*reset complete (cpco->crr) */
         /* Removed because of change in the way of handling */ 
         /* __ISUP_ResetCompleteCPCToCGRR(cic_rec, config_info); */

         /* Send Release Confirmation (cpco->ssco)  */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_REL_IND, cic_rec);

         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         /* Instead of Idling CPC,  */
         /* FSM state is changed to "wait_for_OGC_group_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_GRA;

         break;

    case WAIT_OUTGOING_ACM :
    case WAIT_OUTGOING_ANM :
    case SENT_OUTGOING_ANM :
         /* Send Reset Indication (cpci->ssci)  */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         /* change state to "wait_for_OGC_group_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_GRA;

         break;

    case WAIT_OUTGOING_RLC :
         /*Reset complete (cpci->cgrr) */
         /* Removed because of change in the way of handling */ 
         /*__ISUP_ResetCompleteCPCToCGRR(cic_rec, config_info); */

         /* Instead of Idling CPC,  */
         /* FSM state is changed to "wait_for_OGC_group_reset" */
         cic_rec->fsm_state = WAIT_OUTGOING_GRA;

         break;

    case WAIT_INCOMING_RES :
         /* stop charging */

         /* Stop timers T1 and T38; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T38);

         /*Send Reset Indication (cpco -> ssco) */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         break;

    case WAIT_OUTGOING_RES :
         /*Send Reset Indication (cpco -> ssco) */
         SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_RSC_IND, cic_rec);

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
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
ITS_BOOLEAN
__ISUP_ResetCompleteCPCToCGRR(ITS_EVENT *msg,
                              ISUP_CIC_INFO *cic_rec, 
                              ISUP_OPC_DPC_INFO *config_info)
{
    ITS_ISUP_IE            rs_ie;
    ITS_OCTET              sup_msg_type;
    ITS_USHORT             cic;
    ITS_USHORT             affected_cics[256];
    ITS_USHORT             num_affected_cics;
    int                    i, count=0;
    ISUP_PCIC              pcic;
    ITS_UINT               opc, dpc;
    ITS_OCTET              ni;
    ITS_OCTET              gra_status[32];
    ITS_USHORT             start_cic;
    ISUP_RANGE_AND_STATUS  rs;
    ISUP_CIC_INFO         *affected_cic_rec;
    int                    ret;
    ITS_BOOLEAN            isdsmlocal = ITS_TRUE;

    /* FIXED: code according to Annex H page 110 */
    __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                &rs_ie, &sup_msg_type, &cic);

    __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

    memset ((char *)gra_status, 0, 32);

    start_cic = affected_cics[0];

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
            affected_cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_ERROR(("Could not find PCIC\n"));
        }
        else
        {
            if ((ISUP_CIC_STATE_GET_BA(affected_cic_rec->cic_state)
               == CKTS_TRANSIENT)
               && (ISUP_CIC_STATE_GET_DC(affected_cic_rec->cic_state)
               == CKTS_OUT_OF_ORDER_CTK))
            {
                ISUP_CIC_SET_CALL(affected_cic_rec->cic_state, CKTS_IDLE_CTK);
                affected_cic_rec->fsm_state = IDLE;
            }
            else
            {
                /* Idle CPC state & set fsm_state to IDLE */
                ISUP_ClearCic(affected_cic_rec);
            }

            /* edit status field concerned M_BLOCKED */
            gra_status[count] |= affected_cic_rec->cgrr_m_status << i%8;

            if (affected_cic_rec->cgrr_m_status == 1)
            {
                ISUP_CIC_SET_MAINT(affected_cic_rec->cic_state, 
                                   CKTS_LBLOCKED);
                affected_cic_rec->bls_state = BLS_LBLOCKED;
            }
            else 
            {
                ISUP_CIC_SET_MAINT(affected_cic_rec->cic_state, 
                                   CKTS_ACTIVE);
                affected_cic_rec->bls_state = BLS_IDLE;
            }

            if ((i + 1) % 8 == 0)
            {
                count++;
            }

            affected_cic_rec->cgrr_m_status=0;

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
                            ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, isdsmlocal);
            }
        }
    }

    /* modify GRA status fiend before sending to Network */
    rs.range = num_affected_cics - 1;

    memcpy(rs.status, gra_status, 32);

    ret = __ISUP_Change_RangeStatus(msg, config_info, rs, ISUP_MSG_GRA);

    return (ret);
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
ITS_BOOLEAN
__ISUP_IdleCircuit(ISUP_CIC_INFO *cic_rec,
                   ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->fsm_state != WAIT_OUTGOING_GRA)
    {
        ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);
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
ITS_BOOLEAN 
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

    ITS_EVENT_INIT(&grs_ev, ITS_ISUP_CCITT_SRC, cic_msg->grs_msg_len);
    memcpy((void *)(grs_ev.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

    __ISUP_Validate_RangeStatus(&grs_ev, cic_rec, config_info, &grs_rs_ie,
                                &grs_sup_msg_type, &grs_cic);

    ITS_EVENT_TERM(&grs_ev);

    ITS_EVENT_INIT(&cgu_ev, ITS_ISUP_CCITT_SRC, cic_msg->cgu_msg_len);
    memcpy((void *)(cgu_ev.data), cic_msg->cgu_msg, cic_msg->cgu_msg_len);

    __ISUP_Validate_RangeStatus(&cgu_ev, cic_rec, config_info, &cgu_rs_ie,
                                &cgu_sup_msg_type, &cgu_cic);

    grs_rs = grs_rs_ie.param_data.rangeAndStatus;
    grs_range = grs_rs.range + 1;

    cgu_slen = cgu_rs_ie.param_length - 1;
    cgu_rs = cgu_rs_ie.param_data.rangeAndStatus;
    cgu_range = cgu_rs.range + 1;

    memcpy(cgu_status, cgu_rs.status, cgu_slen);

    if (grs_cic == cgu_cic)
    {
       if ( cgu_range <= grs_range )
       {
            SPRC_SendIndToApp_CCITT(ITS_ISUP_RNS_MNSYS_IND, cic_rec);

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
ITS_BOOLEAN 
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
    ITS_BOOLEAN           isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, isdsmlocal);

    ITS_EVENT_INIT(&grs_ev, ITS_ISUP_CCITT_SRC, cic_msg->grs_msg_len);
    memcpy((void *)(grs_ev.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

    __ISUP_Validate_RangeStatus(&grs_ev, cic_rec, config_info, &grs_rs_ie,
                                &grs_sup_msg_type, &grs_cic);

    ITS_EVENT_TERM(&grs_ev);

    ITS_EVENT_INIT(&cgb_ev, ITS_ISUP_CCITT_SRC, cic_msg->cgb_msg_len);
    memcpy((void *)(cgb_ev.data), cic_msg->cgb_msg, cic_msg->cgb_msg_len);

    __ISUP_Validate_RangeStatus(&cgb_ev, cic_rec, config_info, &cgb_rs_ie,
                                &cgb_sup_msg_type, &cgb_cic);

    grs_rs = grs_rs_ie.param_data.rangeAndStatus;
    grs_range = grs_rs.range + 1;

    cgb_slen = cgb_rs_ie.param_length - 1;
    cgb_rs = cgb_rs_ie.param_data.rangeAndStatus;
    cgb_range = cgb_rs.range + 1;

    memcpy(cgb_status, cgb_rs.status, cgb_slen);

    if (grs_cic == cgb_cic)
    {
       if ( cgb_range <= grs_range )
       {
            SPRC_SendIndToApp_CCITT(ITS_ISUP_RNS_MNSYS_IND, cic_rec);

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

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, isdsmlocal);

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
ITS_BOOLEAN
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
    paramlen = msg->len - sizeof(ITS_OCTET) - sizeof(ITS_USHORT)
               - sizeof(MTP3_HEADER_CCITT);
    index = msg->len - paramlen;

    /* Need to do Decode */
    ret = ISUP_MTP3Decode_CCITT(&msg->data[index + 1],
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
    ret = ISUP_MTP3Encode_CCITT(data, 
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
ITS_BOOLEAN
__ISUP_ResetCompleteCPCOToCRR(ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->crr_state == CRR_WAIT_FOR_RESPONSE)
    {
        SPRC_SendRLCToMTP3_CCITT(CI_CAUSE_NORMAL, cic_rec, config_info);

        cic_rec->crr_state = CRR_IDLE;
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
void
__ISUP_StopCRRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_IDLE :
        break;
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

    case CRO_WAIT_FOR_COT :

        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);

        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    default :
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
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
void
__ISUP_StopCRRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

        cic_rec->cot_first_ind = ITS_TRUE;

       /* remove loop
        * - Enable echo suppressor, if any
        */
        ISUP_ClearCic(cic_rec);
    }
    else if (cic_rec->cri_state == CRI_IDLE)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
    }
    cic_rec->cri_state = CRI_IDLE;
    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRSToCRO is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopCGRSToCRO(ISUP_CIC_INFO *cic_rec,
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
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_COT :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_IDLE :
        break;

    default :
        break;
    }
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRRToCRI is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopCGRRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

        cic_rec->cot_first_ind = ITS_TRUE;
       /* remove loop
       - Enable echo suppressor, if any */
        ISUP_ClearCic(cic_rec);
    }
    else if (cic_rec->cri_state == CRI_IDLE)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
    }
    cic_rec->cri_state = CRI_IDLE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRRToCRO is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopCGRRToCRO(ISUP_CIC_INFO *cic_rec,
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

    case CRO_WAIT_FOR_COT :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
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
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRSToCRI is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopCGRSToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

       /* remove loop
       - Enable echo suppressor, if any */
        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCPCToCCO is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
ITS_BOOLEAN
__ISUP_StopCPCToCCO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;
    switch (cic_rec->cco_state)
    {
    case CCO_WAIT_COT_REPORT:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        cic_rec->cco_state = CCO_IDLE;
         ret  = ITS_TRUE;
         break;
    case CCO_IDLE :
    default :
         ret  = ITS_FALSE;
         break;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCPCToCCI is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 ****************************************************************************/
ITS_BOOLEAN
__ISUP_StopCPCToCCI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;

    switch (cic_rec->cci_state)
    {
    case CCI_WAIT_FOR_COT:
         /*Change CCI state to Wait for COT*/
         cic_rec->cci_state = CCI_IDLE;
         ret = ITS_TRUE;
         break;

    case CCI_IDLE :
    default:
         ret = ITS_FALSE;
         break;
     }
     return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLRToCRI is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopBLRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);

       /* remove loop
       - Enable echo suppressor, if any */
    }
    /* Idle the Ckt*/
    cic_rec->cri_state = CRI_IDLE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLSToCRI is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopBLSToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

       /* remove loop
       - Enable echo suppressor, if any */

        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLRToCRO is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopBLRToCRO(ISUP_CIC_INFO *cic_rec,
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

    case CRO_WAIT_FOR_COT :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
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
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLSToCRO is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopBLSToCRO(ISUP_CIC_INFO *cic_rec,
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
        }
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_COT :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_IDLE :
        break;
    default :
        break;
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
ITS_BOOLEAN
__ISUP_StopMGBSToCRI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->fsm_state = IDLE;
    }
    else if(cic_rec->cri_state == CRI_WAIT_FOR_REL)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

       /* remove loop
        - Enable echo suppressor, if any */
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
    }
    else if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        cic_rec->cci_state = CCI_IDLE;
        cic_rec->fsm_state = IDLE;
    }
        
    return ITS_TRUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for a REL request from App in any state is done here.
 *
 *  Input Parameters:
 *      msg - the message event
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *      src - source of event (L3 or application)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StartRELProcedure(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* store the REL message in cic rec */
    memcpy(cic_rec->cpc_msg, msg->data, msg->len);
    cic_rec->cpc_msg_len = msg->len;

    /* Send REL to SPRC */
    SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

    /* Start T5 and T1 */
    __ISUP_StartRELTimers(cic_rec, config_info);

    /* Change fsm state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;

    return;
}

/*
 * UCIC Related Stuff, NATIONAL MATTER only
 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToCRS is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopUCICToCRS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->crs_state)
    {
        case CRS_IDLE:
            break;

        case CRS_WAIT_FOR_RELEASE:
            /* Stop RSC Timers T16 and T17 */
            __ISUP_StopRSCTimers(cic_rec, config_info);

            /* Stop Repeat RSC timer also */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T98);

            /* FIXME:
             * check if Alert Indicator is On/Off
             * If on, alert maintenance else do not alert
             */
            SPRC_SendIndToApp_CCITT(ITS_ISUP_UCIC_MAINT_RQIND, cic_rec);

            /* FIXME - Raise an Alarm */

            /* Idle the circuit */
            ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

            /* cic crs state to Idle */
            cic_rec->crs_state = CRS_IDLE;

            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToCRS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->crs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToCGRS is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopUCICToCGRS(ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cgrs_state)
    {
        case CGRS_IDLE:
        case CGRS_WAIT_FOR_GRA:
            __ISUP_StopWaitingCGRS(cic_rec, config_info);

            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToCGRS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->cgrs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToCRO is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopUCICToCRO(ISUP_CIC_INFO *cic_rec,
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
        }
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_COT :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_IDLE :
        break;

    default :
        /* TODO add Trace or Alarm */
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToBLS is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopUCICToBLS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{

    switch (cic_rec->bls_state)
    {
        case BLS_IDLE:
            break;

        case BLS_WAIT_FOR_BLA:
            /* stop T12 and T13 Timers */
            __ISUP_StopBLOTimers(cic_rec, config_info);

            /* change state to Idle */
            cic_rec->bls_state = BLS_IDLE;
            break;

        case BLS_WAIT_FOR_UBA:
            /* stop T14 and T15 Timers */
            __ISUP_StopUBLTimers(cic_rec, config_info);

            /* change state to Idle */
            cic_rec->bls_state = BLS_IDLE;
            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToBLS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->cgrs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToGBUS is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_StopUCICToGBUS(ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{

    /* FIXME:
     * No implementation found in SDLs
     * Need to study more and implement
     */
    switch (cic_rec->mgbs_state)
    {
        case MGBS_IDLE:
            break;

        case MGBS_WAIT_FOR_CGBA:
            /* stop T18/T19 timers */
            __ISUP_StopCGBTimers(cic_rec, config_info);

            cic_rec->mgbs_state = MGBS_IDLE;
            break;

        case MGBS_WAIT_FOR_CGUA:
            /* stop T20/T21 timers */
            __ISUP_StopCGUTimers(cic_rec, config_info);

            cic_rec->mgbs_state = MGBS_IDLE;
            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToCGRS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->cgrs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for ResetUCICToCPC is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
void
__ISUP_ResetUCICToCPC(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_DEBUG(("__ISUP_Received_UCIC "));
    switch (cic_rec->fsm_state)
    {
        case IDLE:
            break;

        case WAIT_OUTGOING_IAM:
            /* Won't come here; UCIC is unexpected in this state */
            break;

       case WAIT_CONTINUITY_REPORT :
            if (__ISUP_StopCPCToCCO(cic_rec,config_info))
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

                SPRC_SendIndToApp_CCITT(ITS_ISUP_UCIC_REATTEMPT_RQIND, cic_rec);
                ISUP_ClearCic(cic_rec);
            }
            break;

       case WAIT_INCOMING_COT :
            break;

       case WAIT_INCOMING_ACM:
            /* Stop ACM Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /* Retry to app */
            SPRC_SendIndToApp_CCITT(ITS_ISUP_UCIC_REATTEMPT_RQIND, cic_rec);

            /* Idle Ckt and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);

            break;

        case WAIT_INCOMING_ANM:
            break;

        case RCVD_INCOMING_ANM:
            break;

        case WAIT_INCOMING_RLC:
            /* Stop Timer T5 and T1 */
            __ISUP_StopRELTimers(cic_rec, config_info);

            /* Indication to app */
            SPRC_SendIndToApp_CCITT(ITS_ISUP_UCIC_CPCIDLE_STIND, cic_rec);

            /* Idle the circuit and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);

            break;

        case WAIT_INCOMING_RES:
        case WAIT_OUTGOING_ACM:
        case WAIT_OUTGOING_ANM:
        case SENT_OUTGOING_ANM:
        case WAIT_OUTGOING_RLC:
        case WAIT_OUTGOING_RES:
        case WAIT_OUTGOING_REL:
        case WAIT_OUTGOING_RSC:
        case WAIT_OUTGOING_GRA:
            break;
        default:
            ISUP_ERROR(("__ISUP_ResetUCICToCPC(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->fsm_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }
}

 /***************************************************************************
 *  Purpose:
 *      The processing for StopWaitingCGRS is done here
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
static void
__ISUP_StopWaitingCGRS(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_USHORT    i = 0;
    ITS_USHORT    affected_cics[256];
    ITS_USHORT    num_affected_cics;
    ITS_USHORT    cic;
    ITS_USHORT    index_cic;
    ITS_UINT      opc, dpc;
    ITS_OCTET     ni;
    ISUP_CIC_INFO *affected_cic_rec;
    ITS_EVENT     grs_ev;
    ITS_ISUP_IE   grs_rs_ie;
    ITS_USHORT    grs_cic;
    ITS_OCTET     grs_sup_msg_type;
    ISUP_PCIC     pcic;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    /* check for this being a part of GRS previously sent
     * if yes, Assume GRS been discarded and stop GRA waiting
     */
    index_cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    if (cic_rec->cgrs_state == CGRS_WAIT_FOR_GRA)
    {
        cic = index_cic;
    }
    else
    {
        cic = (ITS_USHORT)(index_cic - 1);
    }

    opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
    dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
    ni  = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

    do
    {
      if(cic == index_cic)
      {
         affected_cic_rec = cic_rec;
      }
      else
      {
         ISUP_PCICFromParts(&pcic, opc, dpc, ni, cic);
         affected_cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
      }

      if (affected_cic_rec == NULL)
      {
          ISUP_ERROR(("Could not find PCIC\n"));
      }
      else if (affected_cic_rec->cgrs_state == CGRS_WAIT_FOR_GRA)
      {
          /* Get the range and make all idle */
          cic_msg = ISUP_FindPcicMsgBuf(affected_cic_rec->pcic, ITS_FALSE,
                                                              isdsmlocal);

          ITS_EVENT_INIT(&grs_ev, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);
          memcpy((void *)(grs_ev.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

          ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

          __ISUP_Validate_RangeStatus(&grs_ev, affected_cic_rec, config_info,
                                      &grs_rs_ie, &grs_sup_msg_type,
                                      &grs_cic);

          ITS_EVENT_TERM(&grs_ev);

          if (index_cic <= grs_cic + grs_rs_ie.param_data.rangeAndStatus.range)
          {
              __ISUP_GetGRSCics(grs_cic, &grs_rs_ie,
                                affected_cics, &num_affected_cics);

              __ISUP_ProcessAffectedCics(affected_cics,
                                         num_affected_cics,
                                         __ISUP_IdleCircuit,
                                         affected_cic_rec, config_info);

              /* Stop timers T22, T23 */
              __ISUP_StopGRSTimers(affected_cic_rec, config_info);

              SPRC_SendIndToApp_CCITT(ITS_ISUP_UCIC_MAINT_RQIND,
                                      affected_cic_rec);

              /* Alert Maintenance Personnel */
              /* FIXME - Send an Alarm */

              affected_cic_rec->cgrs_state = CGRS_IDLE;
           }

           if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
               ISUP_PCIC_TO_CIC(cic_rec->pcic))
           {
               ISUP_ReleaseCic(affected_cic_rec, ITS_FALSE);
           }

           break;
       }
       else
       {
          cic -=1;

          if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
              ISUP_PCIC_TO_CIC(cic_rec->pcic))
          {
              ISUP_ReleaseCic(affected_cic_rec, ITS_FALSE);
          }
       }
    }while ( i++ < ( index_cic > 32 ? 32 : index_cic));
}

