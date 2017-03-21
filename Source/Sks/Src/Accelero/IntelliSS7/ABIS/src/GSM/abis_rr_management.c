/***************************************************************************
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
 ****************************************************************************/

#include <abis_rr_management.h>

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeAssignCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = msg->u.assignComplete.rrCause;

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeAssignCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_ASSIGN_CMP)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.assignComplete.rrCause =  buffer[index++];

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeAssignCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = (msg->u.assignCommand.descFCAT.chanType << 3) |
                      (msg->u.assignCommand.descFCAT.tn);
    if (msg->u.assignCommand.descFCAT.h & 0x01)
    {
        buffer[index++] = (msg->u.assignCommand.descFCAT.tsc << 5) |
                          (msg->u.assignCommand.descFCAT.h << 4) |
                          ((msg->u.assignCommand.descFCAT.maio & 0x3C)
                                                               >> 2);
        buffer[index++] = ((msg->u.assignCommand.descFCAT.maio & 0x03)
                                                                << 6) |
                          (msg->u.assignCommand.descFCAT.hsn & 0x3F);

        //Modified for Bug ID: 3710
  
        buffer[index++] = (msg->u.assignCommand.powCmd.epc << 6) |
                      (msg->u.assignCommand.powCmd.fpcEpc << 5) |
                      (msg->u.assignCommand.powCmd.powLevel);

       //------------------------------------------

       // Modified for Bug ID: 3710


        buffer[index++] = RR_IE_MOBILE_ALLOC_AFTER_TIME;
        buffer[index++] = msg->u.assignCommand.mobAllocAT.len;
        memcpy(&buffer[index], msg->u.assignCommand.mobAllocAT.val,
                           msg->u.assignCommand.mobAllocAT.len);
        index += msg->u.assignCommand.mobAllocAT.len;


       //----------------------------------------------------

    }
    else
    {
        buffer[index++] = (msg->u.assignCommand.descFCAT.tsc << 5) |
                          (msg->u.assignCommand.descFCAT.h << 4) |
                          ((msg->u.assignCommand.descFCAT.arfcn & 0x0300)
                                                                   >> 8);
        buffer[index++] = (msg->u.assignCommand.descFCAT.arfcn & 0x00FF);

        // Modified for Bug ID: 3710

        buffer[index++] = (msg->u.assignCommand.powCmd.epc << 6) |
                      (msg->u.assignCommand.powCmd.fpcEpc << 5) |
                      (msg->u.assignCommand.powCmd.powLevel);
    }

/*
    buffer[index++] = RR_IE_FREQUENCY_LIST_AFTER_TIME;
    buffer[index++] = msg->u.assignCommand.freqListAT.len;
    if ((msg->u.assignCommand.freqListAT.formatID & 0xC0) == 0)
    {
        buffer[index++] = ((msg->u.assignCommand.freqListAT.formatID & 0xC0) |
                           (msg->u.assignCommand.freqListAT.val[0] & 0x0F));
        memcpy(&buffer[index], &msg->u.assignCommand.freqListAT.val[1],
                        (msg->u.assignCommand.freqListAT.len - 1));
        index += msg->u.assignCommand.freqListAT.len - 1;
    }
*/
    if (GET_OPT_FLAG_AC_CELL_CHAN_DESC(msg))
    {
        buffer[index++] = RR_IE_CELL_CHAN_DESCRIPTION;
        memcpy(&buffer[index], msg->u.assignCommand.cellChanDesc.val, 16);
        index += 16;
    }
/*
    buffer[index++] = RR_IE_DESC_MULTISLOT_CONFIG;
    buffer[index++] = msg->u.assignCommand.descMultiSlot.len;
    buffer[index++] = 0x80 | msg->u.assignCommand.descMultiSlot.da;
    buffer[index++] = 0x80 | msg->u.assignCommand.descMultiSlot.ua;
    memcpy(&buffer[index], msg->u.assignCommand.descMultiSlot.chanSet,
                         (msg->u.assignCommand.descMultiSlot.len - 2));
    index += msg->u.assignCommand.descMultiSlot.len - 2;
*/
    if (GET_OPT_FLAG_AC_MODE_CHAN_SET1(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET1;
        buffer[index++] = msg->u.assignCommand.modeChanSet1.mode;
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET2(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET2;
        buffer[index++] = msg->u.assignCommand.modeChanSet2.mode;
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET3(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET3;
        buffer[index++] = msg->u.assignCommand.modeChanSet3.mode;
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET4(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET4;
        buffer[index++] = msg->u.assignCommand.modeChanSet4.mode;
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET5(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET5;
        buffer[index++] = msg->u.assignCommand.modeChanSet5.mode;
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET6(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET6;
        buffer[index++] = msg->u.assignCommand.modeChanSet6.mode;
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET7(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET7;
        buffer[index++] = msg->u.assignCommand.modeChanSet7.mode;
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET8(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_CHAN_SET8;
        buffer[index++] = msg->u.assignCommand.modeChanSet8.mode;
    }

    if (GET_OPT_FLAG_AC_DESC_SC_AT(msg))
    {
        buffer[index++] = RR_IE_DESC_OF_SECOND_CHAN_AFTER_TIME;
        buffer[index++] = (msg->u.assignCommand.descSCAT.chanType << 3) |
                          (msg->u.assignCommand.descSCAT.tn);
        if (msg->u.assignCommand.descSCAT.h & 0x01)
        {
            buffer[index++] = (msg->u.assignCommand.descSCAT.tsc << 5) |
                              (msg->u.assignCommand.descSCAT.h << 4) |
                              ((msg->u.assignCommand.descSCAT.maio & 0x3C)
                                                                   >> 2);
            buffer[index++] = ((msg->u.assignCommand.descSCAT.maio & 0x03)
                                                                    << 6) |
                              (msg->u.assignCommand.descSCAT.hsn & 0x3F);
        }
        else
        {
            buffer[index++] = (msg->u.assignCommand.descSCAT.tsc << 5) |
                              (msg->u.assignCommand.descSCAT.h << 4) |
                              ((msg->u.assignCommand.descSCAT.arfcn & 0x0300)
                                                                       >> 8);
            buffer[index++] = (msg->u.assignCommand.descSCAT.arfcn & 0x00FF);
        }
    }

    if (GET_OPT_FLAG_AC_MODE_SEC_CHAN(msg))
    {
        buffer[index++] = RR_IE_MODE_OF_SECOND_CHAN;
        buffer[index++] = msg->u.assignCommand.modeSecChan.mode;
    }
/*
    buffer[index++] = RR_IE_MOBILE_ALLOC_AFTER_TIME;
    buffer[index++] = msg->u.assignCommand.mobAllocAT.len;
    memcpy(&buffer[index], msg->u.assignCommand.mobAllocAT.val,
                           msg->u.assignCommand.mobAllocAT.len);
    index += msg->u.assignCommand.mobAllocAT.len;
*/
    if (GET_OPT_FLAG_AC_START_TIME(msg))
    {
        buffer[index++] = RR_IE_STARTING_TIME;
        buffer[index++] = (msg->u.assignCommand.startTime.t1 << 3 ) |
                          ((msg->u.assignCommand.startTime.t3 & 0x38) >> 3);
        buffer[index++] = (msg->u.assignCommand.startTime.t2) |
                          ((msg->u.assignCommand.startTime.t3 & 0x07) << 5);
    }
/*
    buffer[index++] = RR_IE_FREQUENCY_LIST_BEFORE_TIME;
    buffer[index++] = msg->u.assignCommand.freqListBT.len;
    if ((msg->u.assignCommand.freqListBT.formatID & 0xC0) == 0)
    {
        buffer[index++] = ((msg->u.assignCommand.freqListBT.formatID & 0xC0) |
                           (msg->u.assignCommand.freqListBT.val[0] & 0x0F));
        memcpy(&buffer[index], &msg->u.assignCommand.freqListBT.val[1],
                           (msg->u.assignCommand.freqListBT.len - 1));
        index += msg->u.assignCommand.freqListBT.len - 1;
    }
*/
    if (GET_OPT_FLAG_AC_DESC_FC_BT(msg))
    {
        buffer[index++] = RR_IE_DESC_OF_FIRST_CHAN_BEFORE_TIME;
        buffer[index++] = (msg->u.assignCommand.descFCBT.chanType << 3) |
                          (msg->u.assignCommand.descFCBT.tn);
        if (msg->u.assignCommand.descFCBT.h & 0x01)
        {
            buffer[index++] = (msg->u.assignCommand.descFCBT.tsc << 5) |
                              (msg->u.assignCommand.descFCBT.h << 4) |
                              ((msg->u.assignCommand.descFCBT.maio & 0x3C)
                                                                   >> 2);
            buffer[index++] = ((msg->u.assignCommand.descFCBT.maio & 0x03)                                                                << 6) |
                              (msg->u.assignCommand.descFCBT.hsn & 0x3F);
        }
        else
        {
            buffer[index++] = (msg->u.assignCommand.descFCBT.tsc << 5) |
                              (msg->u.assignCommand.descFCBT.h << 4) |
                              ((msg->u.assignCommand.descFCBT.arfcn & 0x0300)
                                                                        >> 8);
            buffer[index++] = (msg->u.assignCommand.descFCBT.arfcn & 0x00FF);
        }
    }

    if (GET_OPT_FLAG_AC_DESC_SC_BT(msg))
    {
        buffer[index++] = RR_IE_DESC_OF_SECOND_CHAN_BEFORE_TIME;
        buffer[index++] = (msg->u.assignCommand.descSCBT.chanType << 3) |
                          (msg->u.assignCommand.descSCBT.tn);
        if (msg->u.assignCommand.descSCBT.h & 0x01)
        {
            buffer[index++] = (msg->u.assignCommand.descSCBT.tsc << 5) |
                              (msg->u.assignCommand.descSCBT.h << 4) |
                              ((msg->u.assignCommand.descSCBT.maio & 0x3C)
                                                                   >> 2);
            buffer[index++] = ((msg->u.assignCommand.descSCBT.maio & 0x03)                                                                     << 6) |
                              (msg->u.assignCommand.descSCBT.hsn & 0x3F);
        }
        else
        {
            buffer[index++] = (msg->u.assignCommand.descSCBT.tsc << 5) |
                              (msg->u.assignCommand.descSCBT.h << 4) |
                              ((msg->u.assignCommand.descSCBT.arfcn & 0x0300)
                                                                        >> 8);
            buffer[index++] = (msg->u.assignCommand.descSCBT.arfcn & 0x00FF);
        }
    }
/*
    buffer[index++] = RR_IE_FREQ_CHAN_SEQ_BEFORE_TIME;
    buffer[index++] = msg->u.assignCommand.freqChanSeqBT.lowARFCN & 0x7F;
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[0] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[1] & 0x0F);
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[2] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[3] & 0x0F);
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[4] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[5] & 0x0F);
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[6] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[7] & 0x0F);
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[8] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[9] & 0x0F);
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[10] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[11] & 0x0F);
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[12] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[13] & 0x0F);
    buffer[index++] = ((msg->u.assignCommand.freqChanSeqBT.isARFCN[14] & 0x0F)
                                                                      << 4) |
                       (msg->u.assignCommand.freqChanSeqBT.isARFCN[15] & 0x0F);

    buffer[index++] = RR_IE_MOBILE_ALLOC_BEFORE_TIME;
    buffer[index++] = msg->u.assignCommand.mobAllocBT.len;
    memcpy(&buffer[index], msg->u.assignCommand.mobAllocBT.val,
                           msg->u.assignCommand.mobAllocBT.len);
    index += msg->u.assignCommand.mobAllocBT.len;
*/
    if (GET_OPT_FLAG_AC_CIPHER_MODE_SET(msg))
    {
        if (msg->u.assignCommand.cipherModeSet.sc & 0x01) 
        {
            buffer[index++] = RR_IE_CIPHER_MODE_SETTING |
               ((msg->u.assignCommand.cipherModeSet.algorithmID & 0x07) << 1) |
                (msg->u.assignCommand.cipherModeSet.sc & 0x01);
        }
        else
        {
            buffer[index++] = RR_IE_CIPHER_MODE_SETTING & 0xF0;
        }
    }

    if (GET_OPT_FLAG_AC_VGCS_TGT_MODE_IND(msg))
    {
        buffer[index++] = RR_IE_VGCS_TARGET_MODE_INDICATION;
        buffer[index++] = msg->u.assignCommand.vgcsTgtModeInd.len;
        buffer[index++] = ((msg->u.assignCommand.vgcsTgtModeInd.tgtMode
                                                              & 0x03) << 6) |
                          ((msg->u.assignCommand.vgcsTgtModeInd.groupCipherKey
                                                              & 0x0F) << 2);
    }

    if (GET_OPT_FLAG_AC_MULTIRATE_CONFIG(msg))
    {
        buffer[index++] = RR_IE_MULTIRATE_CONFIG;
        buffer[index++] = msg->u.assignCommand.multirateConfig.len;
        buffer[index++] = ((msg->u.assignCommand.multirateConfig.msVersion 
                                                           & 0x07) << 5) |
                          ((msg->u.assignCommand.multirateConfig.nscb
                                                           & 0x01) << 4) |
                          ((msg->u.assignCommand.multirateConfig.icmi
                                                           & 0x01) << 3) |
                          (msg->u.assignCommand.multirateConfig.startMode
                                                           & 0x03);
        buffer[index++] = msg->u.assignCommand.multirateConfig.amrCodecMode;
    }

    if (GET_OPT_FLAG_AC_VGCS_CIPHER_PARA(msg))
    {
        buffer[index++] = RR_IE_VGCS_CIPHERING_PARA;
        buffer[index++] = msg->u.assignCommand.vgcsCipherPara.len;
        buffer[index++] = ((msg->u.assignCommand.vgcsCipherPara.randInd
                                                               & 0x01) << 5) |
                          ((msg->u.assignCommand.vgcsCipherPara.lacInd
                                                               & 0x01) << 4) |
                          ((msg->u.assignCommand.vgcsCipherPara.cellInd
                                                               & 0x01) << 3) |
                          ((msg->u.assignCommand.vgcsCipherPara.b22Count
                                                               & 0x01) << 2) |
                          (msg->u.assignCommand.vgcsCipherPara.cgCount & 0x03);
    }

   *size = index;
    return ITS_SUCCESS;
}
/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeAssignCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_ASSIGN_CMD)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.assignCommand.descFCAT.chanType = (buffer[index] & 0xF8) >> 3;
    msg->u.assignCommand.descFCAT.tn = (buffer[index++] & 0x07);
    if (buffer[index] & 0x10)
    {
        msg->u.assignCommand.descFCAT.tsc = (buffer[index] & 0xE0) >> 5;
        msg->u.assignCommand.descFCAT.h = (buffer[index] & 0x10) >> 4;
        msg->u.assignCommand.descFCAT.maio |= (buffer[index++] & 0x0F) << 2;
        msg->u.assignCommand.descFCAT.maio |= (buffer[index] & 0xC0) >> 6;
        msg->u.assignCommand.descFCAT.hsn = (buffer[index++] & 0x3F);
    }
    else
    {
        msg->u.assignCommand.descFCAT.tsc = (buffer[index] & 0xE0) >> 5;
        msg->u.assignCommand.descFCAT.h = (buffer[index] & 0x10) >> 4;
        msg->u.assignCommand.descFCAT.arfcn |= (buffer[index++] & 0x03)
                                                                  << 8;
        msg->u.assignCommand.descFCAT.arfcn |= buffer[index++];
    }

    msg->u.assignCommand.powCmd.epc = (buffer[index] & 0x40) >> 6;
    msg->u.assignCommand.powCmd.fpcEpc = (buffer[index] & 0x20) >> 5;
    msg->u.assignCommand.powCmd.powLevel = buffer[index++] & 0x1F;
/*
    if (buffer[index++] == RR_IE_FREQUENCY_LIST_AFTER_TIME)
    {
        msg->u.assignCommand.freqListAT.len = buffer[index++];
        if ((buffer[index] & 0xC0) == 0)
        {
            msg->u.assignCommand.freqListAT.formatID = buffer[index] & 0xC0;
            msg->u.assignCommand.freqListAT.val[0] = buffer[index++] & 0x0F;
            memcpy(&msg->u.assignCommand.freqListAT.val[1], &buffer[index],
                             (msg->u.assignCommand.freqListAT.len - 1));
            index += msg->u.assignCommand.freqListAT.len - 1;
        }
    }
*/
    if (buffer[index++] == RR_IE_CELL_CHAN_DESCRIPTION);
    {
        SET_OPT_FLAG_AC_CELL_CHAN_DESC(msg);
        memcpy(msg->u.assignCommand.cellChanDesc.val, &buffer[index], 16);
        index += 16;
    }
/*
    if (buffer[index++] == RR_IE_DESC_MULTISLOT_CONFIG)
    {
        msg->u.assignCommand.descMultiSlot.len = buffer[index++];
        msg->u.assignCommand.descMultiSlot.da = buffer[index++] & 0x7F;
        msg->u.assignCommand.descMultiSlot.ua = buffer[index++] & 0x7F;
        memcpy(msg->u.assignCommand.descMultiSlot.chanSet, &buffer[index],
                            (msg->u.assignCommand.descMultiSlot.len - 2));
        index += msg->u.assignCommand.descMultiSlot.len - 2;
    }
*/
    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET1)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET1(msg);
        msg->u.assignCommand.modeChanSet1.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET2)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET2(msg);
        msg->u.assignCommand.modeChanSet2.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET3)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET3(msg);
        msg->u.assignCommand.modeChanSet3.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET4)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET4(msg);
        msg->u.assignCommand.modeChanSet4.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET5)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET5(msg);
        msg->u.assignCommand.modeChanSet5.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET6)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET6(msg);
        msg->u.assignCommand.modeChanSet6.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET7)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET7(msg);
        msg->u.assignCommand.modeChanSet7.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_MODE_OF_CHAN_SET8)
    {
        SET_OPT_FLAG_AC_MODE_CHAN_SET8(msg);
        msg->u.assignCommand.modeChanSet8.mode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_DESC_OF_SECOND_CHAN_AFTER_TIME)
    {
        SET_OPT_FLAG_AC_DESC_SC_AT(msg);
        msg->u.assignCommand.descSCAT.chanType = (buffer[index] & 0xF8) >> 3;
        msg->u.assignCommand.descSCAT.tn = (buffer[index++] & 0x07);
        if (buffer[index] & 0x10)
        {
            msg->u.assignCommand.descSCAT.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.assignCommand.descSCAT.h = (buffer[index] & 0x10) >> 4;
            msg->u.assignCommand.descSCAT.maio |= (buffer[index++] & 0x0F) << 2;
            msg->u.assignCommand.descSCAT.maio |= (buffer[index] & 0xC0) >> 6;
            msg->u.assignCommand.descSCAT.hsn = (buffer[index++] & 0x3F);
        }
        else
        {
            msg->u.assignCommand.descSCAT.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.assignCommand.descSCAT.h = (buffer[index] & 0x10) >> 4;
            msg->u.assignCommand.descSCAT.arfcn |= (buffer[index++] & 0x03)
                                                                      << 8;
            msg->u.assignCommand.descSCAT.arfcn |= buffer[index++];
        }
    }

    if (buffer[index++] == RR_IE_MODE_OF_SECOND_CHAN)
    {
        SET_OPT_FLAG_AC_MODE_SEC_CHAN(msg);
        msg->u.assignCommand.modeSecChan.mode = buffer[index++];
    }
/*
    if (buffer[index++] == RR_IE_MOBILE_ALLOC_AFTER_TIME)
    {
        msg->u.assignCommand.mobAllocAT.len = buffer[index++];
        memcpy(msg->u.assignCommand.mobAllocAT.val, &buffer[index],
                              msg->u.assignCommand.mobAllocAT.len);
        index += msg->u.assignCommand.mobAllocAT.len;
    }
*/
    if (buffer[index++] == RR_IE_STARTING_TIME)
    {
        SET_OPT_FLAG_AC_START_TIME(msg);
        msg->u.assignCommand.startTime.t1 = (buffer[index] & 0xF8) >> 3;
        msg->u.assignCommand.startTime.t3 = ((buffer[index] & 0x07) << 3) |
                                       ((buffer[++index] & 0xE0) >> 5);
        msg->u.assignCommand.startTime.t2 = (buffer[index++] & 0x1F);
    }
/*
    if (buffer[index++] == RR_IE_FREQUENCY_LIST_BEFORE_TIME)
    {
        msg->u.assignCommand.freqListBT.len = buffer[index++];
        if ((buffer[index] & 0xC0) == 0)
        {
            msg->u.assignCommand.freqListBT.formatID = buffer[index] & 0xC0;
            msg->u.assignCommand.freqListBT.val[0] = buffer[index++] & 0x0F;
            memcpy(&msg->u.assignCommand.freqListBT.val[1], &buffer[index],
                             (msg->u.assignCommand.freqListBT.len - 1));
            index += msg->u.assignCommand.freqListBT.len - 1;
        }
    }
*/
    if (buffer[index++] == RR_IE_DESC_OF_FIRST_CHAN_BEFORE_TIME)
    {
        SET_OPT_FLAG_AC_DESC_FC_BT(msg); 
        msg->u.assignCommand.descFCBT.chanType = (buffer[index] & 0xF8) >> 3;
        msg->u.assignCommand.descFCBT.tn = (buffer[index++] & 0x07);
        if (buffer[index] & 0x10)
        {
            msg->u.assignCommand.descFCBT.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.assignCommand.descFCBT.h = (buffer[index] & 0x10) >> 4;
            msg->u.assignCommand.descFCBT.maio |= (buffer[index++] & 0x0F)
                                                                     << 2;
            msg->u.assignCommand.descFCAT.maio |= (buffer[index] & 0xC0) >> 6;
            msg->u.assignCommand.descFCBT.hsn = (buffer[index++] & 0x3F);
        }
        else
        {
            msg->u.assignCommand.descFCBT.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.assignCommand.descFCBT.h = (buffer[index] & 0x10) >> 4;
            msg->u.assignCommand.descFCBT.arfcn |= (buffer[index++] & 0x03)
                                                                      << 8;
            msg->u.assignCommand.descFCBT.arfcn |= buffer[index++];
        }
    }

    if (buffer[index++] == RR_IE_DESC_OF_SECOND_CHAN_BEFORE_TIME)
    {
        SET_OPT_FLAG_AC_DESC_SC_BT(msg);
        msg->u.assignCommand.descSCBT.chanType = (buffer[index] & 0xF8) >> 3;
        msg->u.assignCommand.descSCBT.tn = (buffer[index++] & 0x07);
        if (buffer[index] & 0x10)
        {
            msg->u.assignCommand.descSCBT.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.assignCommand.descSCBT.h = (buffer[index] & 0x10) >> 4;
            msg->u.assignCommand.descSCBT.maio |= (buffer[index++] & 0x0F) 
                                                                     << 2;
            msg->u.assignCommand.descSCAT.maio |= (buffer[index] & 0xC0) >> 6;
            msg->u.assignCommand.descSCBT.hsn = (buffer[index++] & 0x3F);
        }
        else
        {
            msg->u.assignCommand.descSCBT.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.assignCommand.descSCBT.h = (buffer[index] & 0x10) >> 4;
            msg->u.assignCommand.descSCBT.arfcn |= (buffer[index++] & 0x03)
                                                                      << 8;
            msg->u.assignCommand.descSCBT.arfcn |= buffer[index++];
        }
    }
/*
    if (buffer[index++] == RR_IE_FREQ_CHAN_SEQ_BEFORE_TIME)
    {
        msg->u.assignCommand.freqChanSeqBT.lowARFCN = buffer[index++] & 0x7F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[0] = (buffer[index] & 0xF0)
                                                                         >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[1] = buffer[index++] & 0x0F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[2] = (buffer[index] & 0xF0)                                                                          >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[3] = buffer[index++] & 0x0F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[4] = (buffer[index] & 0xF0)                                                                          >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[5] = buffer[index++] & 0x0F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[6] = (buffer[index] & 0xF0)                                                                          >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[7] = buffer[index++] & 0x0F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[8] = (buffer[index] & 0xF0)                                                                          >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[9] = buffer[index++] & 0x0F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[10] = (buffer[index] & 0xF0)                                                                          >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[11] = buffer[index++] & 0x0F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[12] = (buffer[index] & 0xF0)                                                                          >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[13] = buffer[index++] & 0x0F;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[14] = (buffer[index] & 0xF0)                                                                          >> 4;
        msg->u.assignCommand.freqChanSeqBT.isARFCN[15] = buffer[index++] & 0x0F;
    }

    if (buffer[index++] == RR_IE_MOBILE_ALLOC_BEFORE_TIME)
    {
        msg->u.assignCommand.mobAllocBT.len = buffer[index++];
        memcpy(msg->u.assignCommand.mobAllocBT.val, &buffer[index],
                              msg->u.assignCommand.mobAllocBT.len);
        index += msg->u.assignCommand.mobAllocBT.len;
    }
*/
    if ((buffer[index] & 0xF0) == RR_IE_CIPHER_MODE_SETTING)
    {
        SET_OPT_FLAG_AC_CIPHER_MODE_SET(msg);
        if (buffer[index] & 0x01)
        {
            msg->u.assignCommand.cipherModeSet.sc = buffer[index] & 0x01;
            msg->u.assignCommand.cipherModeSet.algorithmID = 
                               (buffer[index++] & 0x0E) >> 1;
        }
        else
        {
            msg->u.assignCommand.cipherModeSet.algorithmID = 0x00;
        }
    }

    if (buffer[index++] == RR_IE_VGCS_TARGET_MODE_INDICATION)
    {
        SET_OPT_FLAG_AC_VGCS_TGT_MODE_IND(msg);
        msg->u.assignCommand.vgcsTgtModeInd.len = buffer[index++];
        msg->u.assignCommand.vgcsTgtModeInd.tgtMode = (buffer[index] & 0xC0)
                                                                       >> 6;
        msg->u.assignCommand.vgcsTgtModeInd.groupCipherKey = (buffer[index++]
                                                               & 0x3C) >> 2;
    }

    if (buffer[index++] == RR_IE_MULTIRATE_CONFIG)
    {
        SET_OPT_FLAG_AC_MULTIRATE_CONFIG(msg);
        msg->u.assignCommand.multirateConfig.len = buffer[index++];
        msg->u.assignCommand.multirateConfig.msVersion = ((buffer[index] 
                                                          & 0xE0) >> 5);
        msg->u.assignCommand.multirateConfig.nscb = ((buffer[index]                                                                       & 0x10) >> 4);
        msg->u.assignCommand.multirateConfig.icmi = ((buffer[index]
                                                          & 0x08) >> 3);
        msg->u.assignCommand.multirateConfig.startMode = (buffer[index++]
                                                                & 0x03);
        msg->u.assignCommand.multirateConfig.amrCodecMode = buffer[index++];
    }

    if (buffer[index++] == RR_IE_VGCS_CIPHERING_PARA)
    {
        SET_OPT_FLAG_AC_VGCS_CIPHER_PARA(msg);
        msg->u.assignCommand.vgcsCipherPara.len = buffer[index++];
        msg->u.assignCommand.vgcsCipherPara.randInd = ((buffer[index]
                                                        & 0x20) >> 5);
        msg->u.assignCommand.vgcsCipherPara.lacInd = ((buffer[index]
                                                        & 0x10) >> 4);
        msg->u.assignCommand.vgcsCipherPara.cellInd = ((buffer[index]
                                                        & 0x08) >> 3);
        msg->u.assignCommand.vgcsCipherPara.b22Count = ((buffer[index]
                                                        & 0x04) >> 2);
        msg->u.assignCommand.vgcsCipherPara.cgCount = buffer[index++] & 0x03;
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeAssignFail(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = msg->u.assignFailure.rrCause;

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeAssignFail(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_ASSIGN_FAIL)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.assignFailure.rrCause =  buffer[index++];

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeCipherModeCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
	ITS_OCTET   cmsAlgoid = 0;
    ITS_OCTET   cmsSC     = 0;
	ITS_OCTET   CR        = 0;
	ITS_OCTET   _3rdByte  = 0;

    ITS_INT index = 0;

    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

	CR        = msg->u.cipherCommand.CR;
	cmsSC     = msg->u.cipherCommand.cmsSC;
	cmsAlgoid = msg->u.cipherCommand.cmsAlgoid;

	_3rdByte  |= CR;
	_3rdByte  |= _3rdByte << 4;
	cmsAlgoid |= cmsAlgoid << 1;
	_3rdByte  |= cmsAlgoid;
	_3rdByte  |= cmsSC;

    buffer[index++] = _3rdByte;

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeCipherModeCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT   index     = 0;
	ITS_OCTET _3rdByte  = 0;
	ITS_OCTET cmsSC     = 0;
	ITS_OCTET cmsAlgoid = 0;
	ITS_OCTET CR        = 0;

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_CIPHERING_MODE_CMD)
    {
        return (!ITS_SUCCESS);
    }
	
	_3rdByte  = buffer[index];
	cmsSC     = _3rdByte & 0x01;
	_3rdByte |= _3rdByte >> 1;
	cmsAlgoid = _3rdByte & 0x07;
    _3rdByte |= _3rdByte >> 3;
	CR        = _3rdByte & 0x0F;


    msg->u.cipherCommand.cmsAlgoid= cmsAlgoid;
    msg->u.cipherCommand.cmsSC= cmsSC; 
	msg->u.cipherCommand.CR = CR;

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeCipherModeCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    if (GET_OPT_FLAG_MOBILE_EQUIP_ID(msg))
    {
        buffer[index++] = RR_IE_MOBILE_EQUIP_ID;
        buffer[index++] = msg->u.cipherComplete.mobEquipID.len;
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[0] & 
                                                                 0x0F) << 4) | 
                    ((msg->u.cipherComplete.mobEquipID.oddEven & 0x01) << 3) |
                    (msg->u.cipherComplete.mobEquipID.typeOfID & 0x07);
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[2] &
                                                                 0x0F) << 4) |
                    (msg->u.cipherComplete.mobEquipID.idDigits[1] & 0x0F);
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[4] &                                                                  0x0F) << 4) |
                    (msg->u.cipherComplete.mobEquipID.idDigits[3] & 0x0F);
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[6] &                                                                  0x0F) << 4) |
                    (msg->u.cipherComplete.mobEquipID.idDigits[5] & 0x0F);
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[8] &                                                                  0x0F) << 4) |
                    (msg->u.cipherComplete.mobEquipID.idDigits[7] & 0x0F);
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[10] &                                                                  0x0F) << 4) |
                    (msg->u.cipherComplete.mobEquipID.idDigits[9] & 0x0F);
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[12] &                                                                  0x0F) << 4) |
                    (msg->u.cipherComplete.mobEquipID.idDigits[11] & 0x0F);
        buffer[index++] = ((msg->u.cipherComplete.mobEquipID.idDigits[14] &                                                                  0x0F) << 4) |
                    (msg->u.cipherComplete.mobEquipID.idDigits[13] & 0x0F);
        buffer[index++] = (msg->u.cipherComplete.mobEquipID.idDigits[15] & 
                                                                0x0F) | 0xF0;
    }

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeCipherModeCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_CIPHERING_MODE_CMP)
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] == RR_IE_MOBILE_EQUIP_ID)
    {
        SET_OPT_FLAG_MOBILE_EQUIP_ID(msg);    
        msg->u.cipherComplete.mobEquipID.len = buffer[index++];
        msg->u.cipherComplete.mobEquipID.oddEven = (buffer[index] & 0x08) >> 3;
        msg->u.cipherComplete.mobEquipID.typeOfID = buffer[index] & 0x07;
        msg->u.cipherComplete.mobEquipID.idDigits[0] = (buffer[index++] & 0xF0)
                                                                        >> 4;
        msg->u.cipherComplete.mobEquipID.idDigits[1] = buffer[index] & 0x0F;
        msg->u.cipherComplete.mobEquipID.idDigits[2] = (buffer[index++] & 0xF0)
                                                                          >> 4;
        msg->u.cipherComplete.mobEquipID.idDigits[3] = buffer[index] & 0x0F;
        msg->u.cipherComplete.mobEquipID.idDigits[4] = (buffer[index++] & 0xF0)
                                                                          >> 4;
        msg->u.cipherComplete.mobEquipID.idDigits[5] = buffer[index] & 0x0F;
        msg->u.cipherComplete.mobEquipID.idDigits[6] = (buffer[index++] & 0xF0)
                                                                          >> 4;
        msg->u.cipherComplete.mobEquipID.idDigits[7] = buffer[index] & 0x0F;
        msg->u.cipherComplete.mobEquipID.idDigits[8] = (buffer[index++] & 0xF0)
                                                                          >> 4;
        msg->u.cipherComplete.mobEquipID.idDigits[9] = buffer[index] & 0x0F;
        msg->u.cipherComplete.mobEquipID.idDigits[10] = (buffer[index++] & 0xF0)
                                                                          >> 4;
        msg->u.cipherComplete.mobEquipID.idDigits[11] = buffer[index] & 0x0F;
        msg->u.cipherComplete.mobEquipID.idDigits[12] = (buffer[index++] & 0xF0)
                                                                          >> 4;
        msg->u.cipherComplete.mobEquipID.idDigits[13] = buffer[index] & 0x0F;
        msg->u.cipherComplete.mobEquipID.idDigits[14] = (buffer[index++] & 0xF0)
                                                                          >> 4;
       msg->u.cipherComplete.mobEquipID.idDigits[15] = buffer[index] & 0x0F;

    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeChanRelease(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;
                                                                                
    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = msg->u.chanRelease.rrCause;

    if (GET_OPT_FLAG_BA_RANGE(msg))
    {
        buffer[index++] = RR_IE_BA_RANGE;
        buffer[index++] = msg->u.chanRelease.baRange.len;
        buffer[index++] = msg->u.chanRelease.baRange.numOfRange;
        memcpy(&buffer[index], msg->u.chanRelease.baRange.range,
                               (msg->u.chanRelease.baRange.len - 1));
        index += msg->u.chanRelease.baRange.len - 1;
    }

    if (GET_OPT_FLAG_GROUP_CHAN_DESC(msg))
    {
        buffer[index++] = RR_IE_GROUP_CHAN_DESC;
        buffer[index++] = msg->u.chanRelease.groupChanDesc.len;
        buffer[index++] = (msg->u.chanRelease.groupChanDesc.chanType << 3) |
                          (msg->u.chanRelease.groupChanDesc.tn);
        if (msg->u.chanRelease.groupChanDesc.h & 0x01)
        {
            buffer[index++] = (msg->u.chanRelease.groupChanDesc.tsc << 5) |
                              (msg->u.chanRelease.groupChanDesc.h << 4) |
                              ((msg->u.chanRelease.groupChanDesc.maio & 0x3C)
                                                                       >> 2);
            buffer[index++] = ((msg->u.chanRelease.groupChanDesc.maio & 0x03)
                                                                       << 6) |
                              (msg->u.chanRelease.groupChanDesc.hsn & 0x3F);
        }
        else
        {
            buffer[index++] = (msg->u.chanRelease.groupChanDesc.tsc << 5) |
                              (msg->u.chanRelease.groupChanDesc.h << 4) |
                              ((msg->u.chanRelease.groupChanDesc.arfcn &
                                                          0x0300) >> 8);
            buffer[index++] = (msg->u.chanRelease.groupChanDesc.arfcn & 0x00FF);
        }

        memcpy(&buffer[index], msg->u.chanRelease.groupChanDesc.mac, 
                               (msg->u.chanRelease.groupChanDesc.len - 3));
        index += (msg->u.chanRelease.groupChanDesc.len - 3);

        buffer[index++] = RR_IE_GROUP_CIPHER_KEY_NUM |
                      (msg->u.chanRelease.groupCipherKey & 0x0F);
    }    
/*
    buffer[index++] = RR_IE_GROUP_CIPHER_KEY_NUM |
                      (msg->u.chanRelease.groupCipherKey & 0x0F);
*/
    if (GET_OPT_FLAG_GPRS_RESUMP(msg))
    {
        buffer[index++] = RR_IE_GPRS_RESUMPTION |
                      (msg->u.chanRelease.gprsResump & 0x01);
    }

    if (GET_OPT_FLAG_BA_LIST_PREF(msg))
    {
        buffer[index++] = RR_IE_BA_LIST_PREF;
        buffer[index++] = msg->u.chanRelease.baListPref.len;
        memcpy(&buffer[index], msg->u.chanRelease.baListPref.val, 
                               msg->u.chanRelease.baListPref.len);
        index += msg->u.chanRelease.baListPref.len;
    }

    if (GET_OPT_FLAG_UTRAN_FREQ_LIST(msg))
    {
        buffer[index++] = RR_IE_UTRAN_FREQ_LIST;
        buffer[index++] = msg->u.chanRelease.utranFreqList.len;
        memcpy(&buffer[index], msg->u.chanRelease.baListPref.val,
                               msg->u.chanRelease.utranFreqList.len);
        index += msg->u.chanRelease.utranFreqList.len;
    }

    if (GET_OPT_FLAG_CELL_SELECTION_IND(msg))
    {
        buffer[index++] = RR_IE_CELL_SELECTION_INDICATOR;
        buffer[index++] = msg->u.chanRelease.cellSelIndl.len;
        memcpy(&buffer[index], msg->u.chanRelease.cellSelIndl.val,
                               msg->u.chanRelease.cellSelIndl.len);
        index += msg->u.chanRelease.cellSelIndl.len;
    }

    if (GET_OPT_FLAG_CELL_CHAN_DESC(msg))
    {
        buffer[index++] = RR_IE_CELL_CHAN_DESCRIPTION;
        memcpy(&buffer[index], msg->u.chanRelease.cellChanDesc.val, 16);
        index += 16;
    }

    if (GET_OPT_FLAG_RELEASE_INDICATION(msg))
    {
        buffer[index++] = RR_IE_EN_DTM_CS_RELEASE_INDICATION |
                                            msg->u.chanRelease.enRelInd;
    }

    if (GET_OPT_FLAG_VGCS_CIPHER_PARA(msg))
    {
        buffer[index++] = RR_IE_VGCS_CIPHERING_PARA;
        buffer[index++] = msg->u.chanRelease.vgcsCipherPara.len;
        buffer[index++] = ((msg->u.chanRelease.vgcsCipherPara.randInd
                                                               & 0x01) << 5) |
                          ((msg->u.chanRelease.vgcsCipherPara.lacInd
                                                               & 0x01) << 4) |
                          ((msg->u.chanRelease.vgcsCipherPara.cellInd
                                                               & 0x01) << 3) |
                          ((msg->u.chanRelease.vgcsCipherPara.b22Count
                                                               & 0x01) << 2) |
                          (msg->u.chanRelease.vgcsCipherPara.cgCount & 0x03);
/*
        buffer[index++] = RR_IE_VGCS_CIPHERING_PARA;
        buffer[index++] = msg->u.chanRelease.vgcsCiphPara.len;
        memcpy(&buffer[index], msg->u.chanRelease.vgcsCiphPara.val, 
                               msg->u.chanRelease.vgcsCiphPara.len);
        index += msg->u.chanRelease.vgcsCiphPara.len;
*/
    }

    if (GET_OPT_FLAG_GROUP_CHAN_DESC2(msg))
    {
        buffer[index++] = RR_IE_GROUP_CHAN_DESCRIPTION2;
        buffer[index++] = msg->u.chanRelease.groupChanDesc2.len;
        memcpy(&buffer[index], msg->u.chanRelease.groupChanDesc2.val,
                               msg->u.chanRelease.groupChanDesc2.len);
        index += msg->u.chanRelease.groupChanDesc2.len;
    }

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeChanRelease(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;
                                                                                
    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }
                                                                                
    if (buffer[index++] != RR_MSG_CHANNEL_RELEASE)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.chanRelease.rrCause = buffer[index++];

    if (buffer[index++] == RR_IE_BA_RANGE)
    {
        SET_OPT_FLAG_BA_RANGE(msg);
        msg->u.chanRelease.baRange.len = buffer[index++];
        msg->u.chanRelease.baRange.numOfRange = buffer[index++];
        memcpy(msg->u.chanRelease.baRange.range, &buffer[index],
                          (msg->u.chanRelease.baRange.len - 1));
        index += msg->u.chanRelease.baRange.len - 1;
    }

    if (buffer[index++] == RR_IE_GROUP_CHAN_DESC)
    {
        SET_OPT_FLAG_GROUP_CHAN_DESC(msg);
        msg->u.chanRelease.groupChanDesc.len = buffer[index++];
        msg->u.chanRelease.groupChanDesc.chanType = (buffer[index] & 0xF8) >> 3;
        msg->u.chanRelease.groupChanDesc.tn = (buffer[index++] & 0x07);
        if (buffer[index] & 0x10)
        {
            msg->u.chanRelease.groupChanDesc.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.chanRelease.groupChanDesc.h = (buffer[index] & 0x10) >> 4;
            msg->u.chanRelease.groupChanDesc.maio |= (buffer[index++] & 0x0F)
                                                                        << 2;
            msg->u.chanRelease.groupChanDesc.maio |= (buffer[index] & 0xC0)
                                                                        >> 6;
            msg->u.chanRelease.groupChanDesc.hsn = (buffer[index++] & 0x3F);
        }
        else
        {
            msg->u.chanRelease.groupChanDesc.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.chanRelease.groupChanDesc.h = (buffer[index] & 0x10) >> 4;
            msg->u.chanRelease.groupChanDesc.arfcn |= (buffer[index++] & 
                                                                  0x03) << 8;
            msg->u.chanRelease.groupChanDesc.arfcn |= buffer[index++];
        }

        memcpy(msg->u.chanRelease.groupChanDesc.mac, &buffer[index], 
                               (msg->u.chanRelease.groupChanDesc.len - 3));
        index += (msg->u.chanRelease.groupChanDesc.len - 3);

        msg->u.chanRelease.groupCipherKey = (buffer[index++] & 0x0F);
    }
/*
    msg->u.chanRelease.groupCipherKey = (buffer[index++] & 0x0F);
*/
    if ((buffer[index] & 0xF0) == RR_IE_GPRS_RESUMPTION)
    {
        SET_OPT_FLAG_GPRS_RESUMP(msg);
        msg->u.chanRelease.gprsResump = (buffer[index++] & 0x0F);
    }

    if (buffer[index++] == RR_IE_BA_LIST_PREF)
    {
        SET_OPT_FLAG_BA_LIST_PREF(msg);
	msg->u.chanRelease.baListPref.len = buffer[index++];
        memcpy(msg->u.chanRelease.baListPref.val, &buffer[index], 
                               msg->u.chanRelease.baListPref.len);
        index += msg->u.chanRelease.baListPref.len;
    }

    if (buffer[index++] == RR_IE_UTRAN_FREQ_LIST)
    {
        SET_OPT_FLAG_UTRAN_FREQ_LIST(msg);
        msg->u.chanRelease.utranFreqList.len = buffer[index++];
        memcpy(msg->u.chanRelease.utranFreqList.val, &buffer[index],
                               msg->u.chanRelease.utranFreqList.len);
        index += msg->u.chanRelease.utranFreqList.len;
    }

    if (buffer[index++] == RR_IE_CELL_SELECTION_INDICATOR)
    {
        SET_OPT_FLAG_CELL_SELECTION_IND(msg);
        msg->u.chanRelease.cellSelIndl.len = buffer[index++];
        memcpy(msg->u.chanRelease.cellSelIndl.val, &buffer[index],
                              msg->u.chanRelease.cellSelIndl.len);
        index += msg->u.chanRelease.cellSelIndl.len;
    }

    if (buffer[index++] == RR_IE_CELL_CHAN_DESCRIPTION);
    {
        SET_OPT_FLAG_CELL_CHAN_DESC(msg);
        memcpy(msg->u.chanRelease.cellChanDesc.val, &buffer[index], 16);
        index += 16;
    }

    if ((buffer[index] & 0xF0) == RR_IE_EN_DTM_CS_RELEASE_INDICATION)
    {
        SET_OPT_FLAG_RELEASE_INDICATION(msg);
        msg->u.chanRelease.enRelInd = (buffer[index++] & 0x0F);
    }

    if (buffer[index++] == RR_IE_VGCS_CIPHERING_PARA)
    {
        SET_OPT_FLAG_VGCS_CIPHER_PARA(msg);
        msg->u.chanRelease.vgcsCipherPara.len = buffer[index++];
        msg->u.chanRelease.vgcsCipherPara.randInd = ((buffer[index]
                                                        & 0x20) >> 5);
        msg->u.chanRelease.vgcsCipherPara.lacInd = ((buffer[index]
                                                        & 0x10) >> 4);
        msg->u.chanRelease.vgcsCipherPara.cellInd = ((buffer[index]
                                                        & 0x08) >> 3);
        msg->u.chanRelease.vgcsCipherPara.b22Count = ((buffer[index]
                                                        & 0x04) >> 2);
        msg->u.chanRelease.vgcsCipherPara.cgCount = buffer[index++] & 0x03;
/*
        msg->u.chanRelease.vgcsCiphPara.len = buffer[index++];
        memcpy(msg->u.chanRelease.vgcsCiphPara.val, &buffer[index],
                              msg->u.chanRelease.vgcsCiphPara.len);
        index += msg->u.chanRelease.vgcsCiphPara.len;
*/
    }

    if (buffer[index++] == RR_IE_GROUP_CHAN_DESCRIPTION2);
    {
        SET_OPT_FLAG_GROUP_CHAN_DESC2(msg);
        msg->u.chanRelease.groupChanDesc2.len = buffer[index++];
        memcpy(msg->u.chanRelease.groupChanDesc2.val, &buffer[index],
                              msg->u.chanRelease.groupChanDesc2.len);
        index += msg->u.chanRelease.groupChanDesc2.len;
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeImAssign(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    buffer[index++] = 0x00; ;
    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = (msg->u.imAssign.dediMode << 4) |
                       msg->u.imAssign.pageMode;

    if (!(msg->u.imAssign.dediMode))
    {
        buffer[index++] = (msg->u.imAssign.chanDesc.chanType << 3) |
                          (msg->u.imAssign.chanDesc.tn);
        if (msg->u.imAssign.chanDesc.h & 0x01)
        {
            buffer[index++] = (msg->u.imAssign.chanDesc.tsc << 5) |
                              (msg->u.imAssign.chanDesc.h << 4) |
                              ((msg->u.imAssign.chanDesc.maio & 0x3C) >> 2);
            buffer[index++] = ((msg->u.imAssign.chanDesc.maio & 0x03) << 6) |
                              (msg->u.imAssign.chanDesc.hsn & 0x3F);
        }
        else
        {
            buffer[index++] = (msg->u.imAssign.chanDesc.tsc << 5) |
                              (msg->u.imAssign.chanDesc.h << 4) |
                              ((msg->u.imAssign.chanDesc.arfcn & 0x0300) >> 8);
            buffer[index++] = (msg->u.imAssign.chanDesc.arfcn & 0x00FF);
        }
    }
    else
    {
        memcpy(&buffer[index], msg->u.imAssign.packChanDesc, 3);
        index += 3;
    }

    buffer[index++] = msg->u.imAssign.reqRef.ra;
    memcpy(&buffer[index], msg->u.imAssign.reqRef.t, 2);
    index += 2;

    buffer[index++] = msg->u.imAssign.timingAdv;

    if (msg->u.imAssign.chanDesc.h == 0)
    {
        buffer[index++] = 0;    //length is zero
    }
    else
    {
        buffer[index++] = msg->u.imAssign.mobAlloc.len;
        memcpy(&buffer[index], msg->u.imAssign.mobAlloc.val,
                              msg->u.imAssign.mobAlloc.len);
        index += msg->u.imAssign.mobAlloc.len;
    }

    if (GET_OPT_FLAG_STARTING_TIME(msg))
    {
        buffer[index++] = RR_IE_STARTING_TIME;
        buffer[index++] = (msg->u.imAssign.startTime.t1 << 3 ) |
                          ((msg->u.imAssign.startTime.t3 & 0x38) >> 3);
        buffer[index++] = (msg->u.imAssign.startTime.t2) |
                          ((msg->u.imAssign.startTime.t3 & 0x07) << 5);
    }

    //L2 Pseudo Length excluding IA Rest Octets
    //Bug fix -- Issue ID : 3238
    buffer[0] = (((index - 1) << 2) | 0x01);

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeImAssign(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    //msg->l2PseudoLen = buffer[index++];

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_IMMEDIATE_ASSIGN)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.imAssign.pageMode = buffer[index] & 0x03;
    msg->u.imAssign.dediMode = (buffer[index++] & 0x70) >> 4;

    if (!(msg->u.imAssign.dediMode))
    {
        msg->u.imAssign.chanDesc.chanType = (buffer[index] & 0xF8) >> 3;
        msg->u.imAssign.chanDesc.tn = (buffer[index++] & 0x07);
    
        if (buffer[index] & 0x10)
        {
            msg->u.imAssign.chanDesc.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.imAssign.chanDesc.h = (buffer[index] & 0x10) >> 4;
            msg->u.imAssign.chanDesc.maio |= (buffer[index++] & 0x0F) << 2;
            msg->u.imAssign.chanDesc.maio |= (buffer[index] & 0xC0) >> 6;
            msg->u.imAssign.chanDesc.hsn = (buffer[index++] & 0x3F);
        }
        else
        {
            msg->u.imAssign.chanDesc.tsc = (buffer[index] & 0xE0) >> 5;
            msg->u.imAssign.chanDesc.h = (buffer[index] & 0x10) >> 4;
            msg->u.imAssign.chanDesc.arfcn |= (buffer[index++] & 0x03) << 8;
            msg->u.imAssign.chanDesc.arfcn |= buffer[index++];
        }
    }
    else
    {
        memcpy(msg->u.imAssign.packChanDesc, &buffer[index], 3);
        index += 3;
    }

    msg->u.imAssign.reqRef.ra = buffer[index++];
    memcpy(msg->u.imAssign.reqRef.t, &buffer[index], 2);
    index += 2;

    msg->u.imAssign.timingAdv = buffer[index++];

    if (msg->u.imAssign.chanDesc.h == 0)
    {
        msg->u.imAssign.mobAlloc.len = buffer[index++];
    }
    else
    {
        msg->u.imAssign.mobAlloc.len = buffer[index++];
        memcpy(msg->u.imAssign.mobAlloc.val, &buffer[index],
                              msg->u.imAssign.mobAlloc.len);
        index += msg->u.imAssign.mobAlloc.len;
    }

    if (buffer[index++] == RR_IE_STARTING_TIME)
    {
        SET_OPT_FLAG_STARTING_TIME(msg);
        msg->u.imAssign.startTime.t1 = (buffer[index] & 0xF8) >> 3;
        msg->u.imAssign.startTime.t3 = ((buffer[index] & 0x07) << 3) | 
                                       ((buffer[++index] & 0xE0) >> 5);
        msg->u.imAssign.startTime.t2 = (buffer[index++] & 0x1F);
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeImAssignRej(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    //L2 Pseudo Length
    buffer[index++] = 22;

    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = (msg->u.imAssignRej.pageMode & 0x03);
/*
    buffer[index++] = msg->u.imAssignRej.reqRef1.ra;
    buffer[index++] = (msg->u.imAssignRej.reqRef1.t1 << 3 ) | 
                      ((msg->u.imAssignRej.reqRef1.t3 & 0x38) >> 3);
    buffer[index++] = (msg->u.imAssignRej.reqRef1.t2) &
                      ((msg->u.imAssignRej.reqRef1.t3 & 0x07) << 5);
*/
    buffer[index++] = msg->u.imAssignRej.reqRef1.ra;
    memcpy(&buffer[index], msg->u.imAssignRej.reqRef1.t, 2);
    index += 2;

    buffer[index++] = msg->u.imAssignRej.waitInd1;
/*
    buffer[index++] = msg->u.imAssignRej.reqRef2.ra;
    buffer[index++] = (msg->u.imAssignRej.reqRef2.t1 << 3 ) |
                      ((msg->u.imAssignRej.reqRef2.t3 & 0x38) >> 3);
    buffer[index++] = (msg->u.imAssignRej.reqRef2.t2) |
                      ((msg->u.imAssignRej.reqRef2.t3 & 0x07) << 5);
*/
    buffer[index++] = msg->u.imAssignRej.reqRef2.ra;
    memcpy(&buffer[index], msg->u.imAssignRej.reqRef2.t, 2);
    index += 2;

    buffer[index++] = msg->u.imAssignRej.waitInd2;
/*
    buffer[index++] = msg->u.imAssignRej.reqRef3.ra;
    buffer[index++] = (msg->u.imAssignRej.reqRef3.t1 << 3 ) |
                      ((msg->u.imAssignRej.reqRef3.t3 & 0x38) >> 3);
    buffer[index++] = (msg->u.imAssignRej.reqRef3.t2) |
                      ((msg->u.imAssignRej.reqRef3.t3 & 0x07) << 5);
*/
    buffer[index++] = msg->u.imAssignRej.reqRef3.ra;
    memcpy(&buffer[index], msg->u.imAssignRej.reqRef3.t, 2);
    index += 2;

    buffer[index++] = msg->u.imAssignRej.waitInd3;
/*
    buffer[index++] = msg->u.imAssignRej.reqRef4.ra;
    buffer[index++] = (msg->u.imAssignRej.reqRef4.t1 << 3 ) |
                      ((msg->u.imAssignRej.reqRef4.t3 & 0x38) >> 3);
    buffer[index++] = (msg->u.imAssignRej.reqRef4.t2) |
                      ((msg->u.imAssignRej.reqRef4.t3 & 0x07) << 5);
*/
    buffer[index++] = msg->u.imAssignRej.reqRef4.ra;
    memcpy(&buffer[index], msg->u.imAssignRej.reqRef4.t, 2);
    index += 2;

    buffer[index++] = msg->u.imAssignRej.waitInd4;

    //L2 Pseudo Length - excluding IAR Rest Octets
    //Bug fix -- Issue ID : 3238
    buffer[0] = (((index - 1) << 2) | 0x01);

//    memcpy(&buffer[index], msg->u.imAssignRej.iarRestOct, 3);
//    index += 3;

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeImAssignRej(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    //msg->l2PseudoLen = buffer[index++];

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_IMMEDIATE_ASSIGN_REJ)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.imAssignRej.pageMode = (buffer[index++] & 0x03);
/*
    msg->u.imAssignRej.reqRef1.ra = buffer[index++];
    msg->u.imAssignRej.reqRef1.t1 = (buffer[index] & 0xF8) >> 3;
    msg->u.imAssignRej.reqRef1.t3 = ((buffer[index] & 0x07) << 3) |
                                    ((buffer[++index] & 0xE0) >> 5);
    msg->u.imAssignRej.reqRef1.t2 = (buffer[index++] & 0x1F);
*/
    msg->u.imAssignRej.reqRef1.ra = buffer[index++];
    memcpy(msg->u.imAssignRej.reqRef1.t, &buffer[index], 2);
    index += 2;
                                                                                
    msg->u.imAssignRej.waitInd1 = buffer[index++];
/*
    msg->u.imAssignRej.reqRef2.ra = buffer[index++];
    msg->u.imAssignRej.reqRef2.t1 = (buffer[index] & 0xF8) >> 3;
    msg->u.imAssignRej.reqRef2.t3 = ((buffer[index] & 0x07) << 3) |
                                    ((buffer[++index] & 0xE0) >> 5);
    msg->u.imAssignRej.reqRef2.t2 = (buffer[index++] & 0x1F);
*/
    msg->u.imAssignRej.reqRef2.ra = buffer[index++];
    memcpy(msg->u.imAssignRej.reqRef2.t, &buffer[index], 2);
    index += 2;

    msg->u.imAssignRej.waitInd2 = buffer[index++];
/*
    msg->u.imAssignRej.reqRef3.ra = buffer[index++];
    msg->u.imAssignRej.reqRef3.t1 = (buffer[index] & 0xF8) >> 3;
    msg->u.imAssignRej.reqRef3.t3 = ((buffer[index] & 0x07) << 3) |
                                    ((buffer[++index] & 0xE0) >> 5);
    msg->u.imAssignRej.reqRef3.t2 = (buffer[index++] & 0x1F);
*/
    msg->u.imAssignRej.reqRef3.ra = buffer[index++];
    memcpy(msg->u.imAssignRej.reqRef3.t, &buffer[index], 2);
    index += 2;

    msg->u.imAssignRej.waitInd3 = buffer[index++];
/*
    msg->u.imAssignRej.reqRef4.ra = buffer[index++];
    msg->u.imAssignRej.reqRef4.t1 = (buffer[index] & 0xF8) >> 3;
    msg->u.imAssignRej.reqRef4.t3 = ((buffer[index] & 0x07) << 3) |
                                    ((buffer[++index] & 0xE0) >> 5);
    msg->u.imAssignRej.reqRef4.t2 = (buffer[index++] & 0x1F);
*/
    msg->u.imAssignRej.reqRef4.ra = buffer[index++];
    memcpy(msg->u.imAssignRej.reqRef4.t, &buffer[index], 2);
    index += 2;

    msg->u.imAssignRej.waitInd4 = buffer[index++];

    memcpy(msg->u.imAssignRej.iarRestOct, &buffer[index], 3);
    index += 3;

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeCMChange(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;
                                                                                
    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = msg->u.cmChange.msClassmark.len;
    buffer[index++] = ((msg->u.cmChange.msClassmark.revLevel & 0x03) << 5) |
                      ((msg->u.cmChange.msClassmark.esInd & 0x01) << 4) |
                      ((msg->u.cmChange.msClassmark.a51 & 0x01) << 3) |
                      ((msg->u.cmChange.msClassmark.rfPowCap & 0x07));
    buffer[index++] = ((msg->u.cmChange.msClassmark.psCap & 0x01) << 6) |
                      ((msg->u.cmChange.msClassmark.ssScreenInd & 0x03) << 4) |
                      ((msg->u.cmChange.msClassmark.smCap & 0x01) << 3) |
                      ((msg->u.cmChange.msClassmark.vbs & 0x01) << 2) |
                      ((msg->u.cmChange.msClassmark.vgcs & 0x01) << 1) |
                      ((msg->u.cmChange.msClassmark.fc & 0x01));
    buffer[index++] = ((msg->u.cmChange.msClassmark.cm3 & 0x01) << 7) |
                      ((msg->u.cmChange.msClassmark.lcsvaCap & 0x01) << 5) |
                      ((msg->u.cmChange.msClassmark.ucs2 & 0x01) << 4) |
                      ((msg->u.cmChange.msClassmark.soLSA & 0x01) << 3) |
                      ((msg->u.cmChange.msClassmark.cmsp & 0x01) << 2) |
                      ((msg->u.cmChange.msClassmark.a53 & 0x01) << 1) |
                      ((msg->u.cmChange.msClassmark.a52& 0x01));

    if (msg->u.cmChange.msClassmark.cm3 > 0)
    {
        buffer[index++] = RR_IE_ADDITIONAL_MS_CM_INFO;
        buffer[index++] = msg->u.cmChange.addMsCmInfo.len;
        memcpy(&buffer[index], msg->u.cmChange.addMsCmInfo.val,
                              msg->u.cmChange.addMsCmInfo.len);
        index += msg->u.cmChange.addMsCmInfo.len;
    }

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeCMChange(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_CLASSMARK_CHANGE)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.cmChange.msClassmark.len = buffer[index++];
    msg->u.cmChange.msClassmark.revLevel = (buffer[index] & 0x60) >> 5;
    msg->u.cmChange.msClassmark.esInd = (buffer[index] & 0x10) >> 4;
    msg->u.cmChange.msClassmark.a51 = (buffer[index] & 0x08) >> 3;
    msg->u.cmChange.msClassmark.rfPowCap = buffer[index++] & 0x07;
    msg->u.cmChange.msClassmark.psCap = (buffer[index] & 0x40) >> 6;
    msg->u.cmChange.msClassmark.ssScreenInd = (buffer[index] & 0x30) >> 4;
    msg->u.cmChange.msClassmark.smCap = (buffer[index] & 0x10) >> 3;
    msg->u.cmChange.msClassmark.vbs = (buffer[index] & 0x04) >> 2;
    msg->u.cmChange.msClassmark.vgcs = (buffer[index] & 0x02) >> 1;
    msg->u.cmChange.msClassmark.fc = buffer[index++] & 0x01;
    msg->u.cmChange.msClassmark.cm3 = (buffer[index] & 0x80) >> 7;
    msg->u.cmChange.msClassmark.lcsvaCap = (buffer[index] & 0x20) >> 5;
    msg->u.cmChange.msClassmark.ucs2  = (buffer[index] & 0x10) >> 4;
    msg->u.cmChange.msClassmark.soLSA = (buffer[index] & 0x08) >> 3;
    msg->u.cmChange.msClassmark.cmsp = (buffer[index] & 0x04) >> 2;
    msg->u.cmChange.msClassmark.a53 = (buffer[index] & 0x02) >> 1;
    msg->u.cmChange.msClassmark.a52 = buffer[index++] & 0x01;

    if (msg->u.cmChange.msClassmark.cm3 > 0)
    {
        if (buffer[index++] == RR_IE_ADDITIONAL_MS_CM_INFO)
        {
            msg->u.cmChange.addMsCmInfo.len = buffer[index++];
            memcpy(msg->u.cmChange.addMsCmInfo.val, &buffer[index],
                                  msg->u.cmChange.addMsCmInfo.len);
            index += msg->u.cmChange.addMsCmInfo.len;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeCMEnquiry(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;
                                                                                
    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    if(GET_OPT_FLAG_CM_ENQUIRY_MASK(msg))
	{
		buffer[index++] = RR_IE_CLASSMARK_ENQUIRY_MASK;
		buffer[index++] = msg->u.cmEnquiry.cmEnquiryMask.len;
		buffer[index++] = msg->u.cmEnquiry.cmEnquiryMask.val;
	}

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeCMEnquiry(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;
                                                                                
    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }
                                                                                
    if (buffer[index++] != RR_MSG_CLASSMARK_ENQUIRY)
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] == RR_IE_CLASSMARK_ENQUIRY_MASK)
    {
        SET_OPT_FLAG_CM_ENQUIRY_MASK(msg);
        msg->u.cmEnquiry.cmEnquiryMask.len = buffer[index++];
        msg->u.cmEnquiry.cmEnquiryMask.val = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodeMeasureReport(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer){
    ITS_INT index = 0;

    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = ((msg->u.measureReport.measureResult.baUsed & 0x01)
                                                                     << 7) |
                      ((msg->u.measureReport.measureResult.dtxUsed & 0x01)
                                                                     << 6) |
                       (msg->u.measureReport.measureResult.rxLevFull & 0x3F);

    buffer[index++] = ((msg->u.measureReport.measureResult.baUsed3G & 0x01)
                                                                     << 7) |
                      ((msg->u.measureReport.measureResult.measValid & 0x01)
                                                                     << 6) |
                       (msg->u.measureReport.measureResult.rxLevSub & 0x3F);

    buffer[index++] = ((msg->u.measureReport.measureResult.rxQualFull & 0x07)
                                                                     << 4) |
                      ((msg->u.measureReport.measureResult.rxQualSub & 0x07)
                                                                     << 1) |
                      ((msg->u.measureReport.measureResult.noNCellM & 0x40)
                                                                     >> 2);
    buffer[index++] = ((msg->u.measureReport.measureResult.noNCellM & 0x03)
                                                                     << 6) |
                       (msg->u.measureReport.measureResult.rxLevNCell1 & 0x3F);

    buffer[index++] = ((msg->u.measureReport.measureResult.bcchFreqNCell1
                                                             & 0x1F) << 3) |
                      ((msg->u.measureReport.measureResult.bsicNCell1 & 0x38)
                                                                     >> 3);

    buffer[index++] = ((msg->u.measureReport.measureResult.bsicNCell1 & 0x07) 
                                                                     << 5) |
                      ((msg->u.measureReport.measureResult.rxLevNCell2 & 0x3E)
                                                                     >> 1);

    buffer[index++] = ((msg->u.measureReport.measureResult.rxLevNCell2 & 0x01)
                                                                     << 7) |
                      ((msg->u.measureReport.measureResult.bcchFreqNCell2
                                                             & 0x1F) << 2) |
                      ((msg->u.measureReport.measureResult.bsicNCell2 & 0x30)
                                                                     >> 4);

    buffer[index++] = ((msg->u.measureReport.measureResult.bsicNCell2 & 0x0F) 
                                                                     << 4) |
                      ((msg->u.measureReport.measureResult.rxLevNCell3 & 0x3C)
                                                                     >> 2);

    buffer[index++] = ((msg->u.measureReport.measureResult.rxLevNCell3 & 0x03)
                                                                     << 6) |
                      ((msg->u.measureReport.measureResult.bcchFreqNCell3 
                                                             & 0x1F) << 1) |
                      ((msg->u.measureReport.measureResult.bsicNCell3 & 0x20)
                                                                     >> 5); 

    buffer[index++] = ((msg->u.measureReport.measureResult.bsicNCell3 & 0x1F)
                                                                     << 3) |
                      ((msg->u.measureReport.measureResult.rxLevNCell4 & 0x38)
                                                                     >> 3);

    buffer[index++] = ((msg->u.measureReport.measureResult.rxLevNCell4 & 0x07)
                                                                     << 5) |
                       (msg->u.measureReport.measureResult.bcchFreqNCell4 
                                                                    & 0x1F);

    buffer[index++] = ((msg->u.measureReport.measureResult.bsicNCell4 & 0x3F)
                                                                     << 2) |
                      ((msg->u.measureReport.measureResult.rxLevNCell5 & 0x30)
                                                                     >> 4);

    buffer[index++] = ((msg->u.measureReport.measureResult.rxLevNCell5 & 0x0F)
                                                                     << 4) |
                      ((msg->u.measureReport.measureResult.bcchFreqNCell5
                                                             & 0x1E) >> 1);

    buffer[index++] = ((msg->u.measureReport.measureResult.bcchFreqNCell5
                                                             & 0x01) << 7) |
                      ((msg->u.measureReport.measureResult.bsicNCell5 & 0x3F)
                                                                     << 1) |
                      ((msg->u.measureReport.measureResult.rxLevNCell6 & 0x20)
                                                                     >> 5);

    buffer[index++] = ((msg->u.measureReport.measureResult.rxLevNCell6 & 0x1F)
                                                                     << 3) |
                      ((msg->u.measureReport.measureResult.bcchFreqNCell6
                                                             & 0x1C) >> 2);

    buffer[index++] = ((msg->u.measureReport.measureResult.bcchFreqNCell6
                                                             & 0x03) << 6) |
                       (msg->u.measureReport.measureResult.bsicNCell6 & 0x3F);

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodeMeasureReport(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    if (buffer[index++] != (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        return (!ITS_SUCCESS);
    }

    if (buffer[index++] != RR_MSG_MEASUREMENT_REPORT)
    {
        return (!ITS_SUCCESS);
    }

    msg->u.measureReport.measureResult.baUsed = (buffer[index] & 0x80) >> 7;
    msg->u.measureReport.measureResult.dtxUsed = (buffer[index] & 0x40) >> 6;
    msg->u.measureReport.measureResult.rxLevFull = buffer[index++] & 0x3F;
    msg->u.measureReport.measureResult.baUsed3G = (buffer[index] & 0x80) >> 7;
    msg->u.measureReport.measureResult.measValid = (buffer[index] & 0x40) >> 6;
    msg->u.measureReport.measureResult.rxLevSub = buffer[index++] & 0x3F;
    msg->u.measureReport.measureResult.rxQualFull = (buffer[index] & 0x70)
                                                                      >> 4; 
    msg->u.measureReport.measureResult.rxQualSub = (buffer[index] & 0x0E) >> 1; 
    msg->u.measureReport.measureResult.noNCellM = (buffer[index++] & 0x01) 
                                                                      << 2; 
    msg->u.measureReport.measureResult.noNCellM |= (buffer[index] & 0xC0) >> 6;
    msg->u.measureReport.measureResult.rxLevNCell1 = buffer[index++] & 0x3F;
    msg->u.measureReport.measureResult.bcchFreqNCell1 = (buffer[index] & 0xF8)
                                                                          >> 3;
    msg->u.measureReport.measureResult.bsicNCell1 = (buffer[index++] & 0x07) 
                                                                       << 3;
    msg->u.measureReport.measureResult.bsicNCell1 |= (buffer[index] & 0xE0)
                                                                      >> 5;
    msg->u.measureReport.measureResult.rxLevNCell2 = (buffer[index++] & 0x1F)
                                                                        << 1;
    msg->u.measureReport.measureResult.rxLevNCell2 |= (buffer[index] & 0x80)
                                                                       >> 7;
    msg->u.measureReport.measureResult.bcchFreqNCell2 = (buffer[index] & 0x7C)
                                                                         >> 2;
    msg->u.measureReport.measureResult.bsicNCell2 = (buffer[index++] & 0x03)
                                                                       << 4; 
    msg->u.measureReport.measureResult.bsicNCell2 |= (buffer[index] & 0xF0)
                                                                      >> 4;
    msg->u.measureReport.measureResult.rxLevNCell3 = (buffer[index++] & 0x0F)
                                                                        << 2; 
    msg->u.measureReport.measureResult.rxLevNCell3 |= (buffer[index] & 0xC0)
                                                                       >> 6;
    msg->u.measureReport.measureResult.bcchFreqNCell3 = (buffer[index] & 0x3E)
                                                                        >> 1;
    msg->u.measureReport.measureResult.bsicNCell3 = (buffer[index++] & 0x01)
                                                                       << 5;
    msg->u.measureReport.measureResult.bsicNCell3 |= (buffer[index] & 0xF8)
                                                                      >> 3;
    msg->u.measureReport.measureResult.rxLevNCell4 = (buffer[index++] & 0x07)
                                                                        << 3;
    msg->u.measureReport.measureResult.rxLevNCell4 |= (buffer[index] & 0xE0)
                                                                       >> 5;
    msg->u.measureReport.measureResult.bcchFreqNCell4 = buffer[index++] & 0x1F;
    msg->u.measureReport.measureResult.bsicNCell4 = (buffer[index] & 0xFC) >> 2;
    msg->u.measureReport.measureResult.rxLevNCell5 = (buffer[index++] & 0x03)
                                                                        << 4;
    msg->u.measureReport.measureResult.rxLevNCell5 |= (buffer[index] & 0xF0)
                                                                       >> 4;
    msg->u.measureReport.measureResult.bcchFreqNCell5 = (buffer[index++] 
                                                           & 0x0F) << 1;
    msg->u.measureReport.measureResult.bcchFreqNCell5 |= (buffer[index] & 0x80)
                                                                       >> 7;
    msg->u.measureReport.measureResult.bsicNCell5 = (buffer[index] & 0x7E)
                                                                      >> 1;
    msg->u.measureReport.measureResult.rxLevNCell6 = (buffer[index++] & 0x01)
                                                                        << 5;
    msg->u.measureReport.measureResult.rxLevNCell6 |= (buffer[index] & 0xF8)
                                                                       >> 3;
    msg->u.measureReport.measureResult.bcchFreqNCell6 = (buffer[index++] & 
                                                                0x07) << 2;
    msg->u.measureReport.measureResult.bcchFreqNCell6 |= (buffer[index] & 0xC0)
                                                                       >> 6;
    msg->u.measureReport.measureResult.bsicNCell6 = buffer[index++] & 0x3F;

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_EncodePagingResp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;
                                                                                
    buffer[index++] = msg->msgSkipDisc;
    buffer[index++] = msg->msgType;

    buffer[index++] = (msg->u.pagingResp.cipherKeySeq & 0x0F);

    buffer[index++] = msg->u.cmChange.msClassmark.len;
    buffer[index++] = ((msg->u.pagingResp.msClassmark.revLevel & 0x03) << 5) |
                      ((msg->u.pagingResp.msClassmark.esInd & 0x01) << 4) |
                      ((msg->u.pagingResp.msClassmark.a51 & 0x01) << 3) |
                      ((msg->u.pagingResp.msClassmark.rfPowCap & 0x07));
    buffer[index++] = ((msg->u.pagingResp.msClassmark.psCap & 0x01) << 6) |
                      ((msg->u.pagingResp.msClassmark.ssScreenInd & 0x03)
                                                                    << 4) |
                      ((msg->u.pagingResp.msClassmark.smCap & 0x01) << 3) |
                      ((msg->u.pagingResp.msClassmark.vbs & 0x01) << 2) |
                      ((msg->u.pagingResp.msClassmark.vgcs & 0x01) << 1) |
                      ((msg->u.pagingResp.msClassmark.fc & 0x01));
    buffer[index++] = ((msg->u.pagingResp.msClassmark.cm3 & 0x01) << 7) |
                      ((msg->u.pagingResp.msClassmark.lcsvaCap & 0x01) << 5) |
                      ((msg->u.pagingResp.msClassmark.ucs2 & 0x01) << 4) |
                      ((msg->u.pagingResp.msClassmark.soLSA & 0x01) << 3) |
                      ((msg->u.pagingResp.msClassmark.cmsp & 0x01) << 2) |
                      ((msg->u.pagingResp.msClassmark.a53 & 0x01) << 1) |
                      ((msg->u.pagingResp.msClassmark.a52& 0x01));

    buffer[index++] = msg->u.pagingResp.mobileID.len;
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[0] &
                                                   0x0F) << 4) |
                ((msg->u.pagingResp.mobileID.oddEven & 0x01) << 3) |
                (msg->u.pagingResp.mobileID.typeOfID & 0x07);
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[2] &
                                                   0x0F) << 4) |
                (msg->u.pagingResp.mobileID.idDigits[1] & 0x0F);
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[4] &                                                             0x0F) << 4) |
                (msg->u.pagingResp.mobileID.idDigits[3] & 0x0F);
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[6] &                                                             0x0F) << 4) |
                (msg->u.pagingResp.mobileID.idDigits[5] & 0x0F);
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[8] &                                                             0x0F) << 4) |
                (msg->u.pagingResp.mobileID.idDigits[7] & 0x0F);
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[10] &                                                              0x0F) << 4) |
                (msg->u.pagingResp.mobileID.idDigits[9] & 0x0F);
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[12] &                                                              0x0F) << 4) |
                (msg->u.pagingResp.mobileID.idDigits[11] & 0x0F);
    buffer[index++] = ((msg->u.pagingResp.mobileID.idDigits[14] &                                                              0x0F) << 4) |
                (msg->u.pagingResp.mobileID.idDigits[13] & 0x0F);
//    buffer[index++] = (msg->u.pagingResp.mobileID.idDigits[15] &
//                                                0x0F) | 0xF0;

    *size = index;
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_DecodePagingResp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    ITS_INT index = 0;

    index += 2;

    msg->u.pagingResp.cipherKeySeq = (buffer[index++] & 0x0F);

    msg->u.pagingResp.msClassmark.len = buffer[index++];
    msg->u.pagingResp.msClassmark.revLevel = (buffer[index] & 0x60) >> 5;
    msg->u.pagingResp.msClassmark.esInd = (buffer[index] & 0x10) >> 4;
    msg->u.pagingResp.msClassmark.a51 = (buffer[index] & 0x08) >> 3;
    msg->u.pagingResp.msClassmark.rfPowCap = buffer[index++] & 0x07;
    msg->u.pagingResp.msClassmark.psCap = (buffer[index] & 0x40) >> 6;
    msg->u.pagingResp.msClassmark.ssScreenInd = (buffer[index] & 0x30) >> 4;
    msg->u.pagingResp.msClassmark.smCap = (buffer[index] & 0x10) >> 3;
    msg->u.pagingResp.msClassmark.vbs = (buffer[index] & 0x04) >> 2;
    msg->u.pagingResp.msClassmark.vgcs = (buffer[index] & 0x02) >> 1;
    msg->u.pagingResp.msClassmark.fc = buffer[index++] & 0x01;
    msg->u.pagingResp.msClassmark.cm3 = (buffer[index] & 0x80) >> 7;
    msg->u.pagingResp.msClassmark.lcsvaCap = (buffer[index] & 0x20) >> 5;
    msg->u.pagingResp.msClassmark.ucs2  = (buffer[index] & 0x10) >> 4;
    msg->u.pagingResp.msClassmark.soLSA = (buffer[index] & 0x08) >> 3;
    msg->u.pagingResp.msClassmark.cmsp = (buffer[index] & 0x04) >> 2;
    msg->u.pagingResp.msClassmark.a53 = (buffer[index] & 0x02) >> 1;
    msg->u.pagingResp.msClassmark.a52 = buffer[index++] & 0x01;

    msg->u.pagingResp.mobileID.len = buffer[index++];
    msg->u.pagingResp.mobileID.oddEven = (buffer[index] & 0x08) >> 3;
    msg->u.pagingResp.mobileID.typeOfID = buffer[index] & 0x07;
    msg->u.pagingResp.mobileID.idDigits[0] = (buffer[index++] & 0xF0)
                                                                    >> 4;
    msg->u.pagingResp.mobileID.idDigits[1] = buffer[index] & 0x0F;
    msg->u.pagingResp.mobileID.idDigits[2] = (buffer[index++] & 0xF0)
                                                    >> 4;
    msg->u.pagingResp.mobileID.idDigits[3] = buffer[index] & 0x0F;
    msg->u.pagingResp.mobileID.idDigits[4] = (buffer[index++] & 0xF0)
                                                                     >> 4;
    msg->u.pagingResp.mobileID.idDigits[5] = buffer[index] & 0x0F;
    msg->u.pagingResp.mobileID.idDigits[6] = (buffer[index++] & 0xF0)
                                                                     >> 4;
    msg->u.pagingResp.mobileID.idDigits[7] = buffer[index] & 0x0F;
    msg->u.pagingResp.mobileID.idDigits[8] = (buffer[index++] & 0xF0)
                                                                      >> 4;
    msg->u.pagingResp.mobileID.idDigits[9] = buffer[index] & 0x0F;
    msg->u.pagingResp.mobileID.idDigits[10] = (buffer[index++] & 0xF0)                                                                          >> 4;
    msg->u.pagingResp.mobileID.idDigits[11] = buffer[index] & 0x0F;
    msg->u.pagingResp.mobileID.idDigits[12] = (buffer[index++] & 0xF0)                                                                          >> 4;
    msg->u.pagingResp.mobileID.idDigits[13] = buffer[index] & 0x0F;
    msg->u.pagingResp.mobileID.idDigits[14] = (buffer[index++] & 0xF0)                                                                          >> 4;
//    msg->u.pagingResp.mobileID.idDigits[15] = buffer[index] & 0x0F;
  
    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_Encode(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    switch (msg->msgType)
    {
        case RR_MSG_ASSIGN_CMP:
            if (RR_EncodeAssignCmp(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CIPHERING_MODE_CMD:
            if (RR_EncodeCipherModeCmd(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CIPHERING_MODE_CMP:
            if (RR_EncodeCipherModeCmp(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CHANNEL_RELEASE:
            if (RR_EncodeChanRelease(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_ASSIGN_CMD:
            if (RR_EncodeAssignCmd(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_ASSIGN_FAIL:
            if (RR_EncodeAssignFail(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_IMMEDIATE_ASSIGN:
            if (RR_EncodeImAssign(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;
                                                                                
        case RR_MSG_IMMEDIATE_ASSIGN_REJ:
            if (RR_EncodeImAssignRej(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CLASSMARK_CHANGE:
            if (RR_EncodeCMChange(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CLASSMARK_ENQUIRY:
            if (RR_EncodeCMEnquiry(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_MEASUREMENT_REPORT:
            if (RR_EncodeMeasureReport(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_PAGING_RESPONSE:
            if (RR_EncodePagingResp(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        default:
            return (!ITS_SUCCESS);
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ************************************************************************
 *  Purpose:
 *        None.
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
 *        None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITS_INT
RR_Decode(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer)
{
    if (buffer[0] == (SKIP_INDICATOR | RR_PROTOCOL_DISC))
    {
        msg->msgSkipDisc = buffer[0];
        msg->msgType = buffer[1];
    }
    else
    {
       return (!ITS_SUCCESS);
    }
 
    switch (msg->msgType)
    {
        case RR_MSG_ASSIGN_CMP:
            if (RR_DecodeAssignCmp(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;
                                                                                
        case RR_MSG_CIPHERING_MODE_CMD:
            if (RR_DecodeCipherModeCmd(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;
                                                                                
        case RR_MSG_CIPHERING_MODE_CMP:
            if (RR_DecodeCipherModeCmp(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CHANNEL_RELEASE:
            if (RR_DecodeChanRelease(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_ASSIGN_CMD:
            if (RR_DecodeAssignCmd(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_ASSIGN_FAIL:
            if (RR_DecodeAssignFail(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_IMMEDIATE_ASSIGN:
            if (RR_DecodeImAssign(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;
                                                                                
        case RR_MSG_IMMEDIATE_ASSIGN_REJ:
            if (RR_DecodeImAssignRej(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CLASSMARK_CHANGE:
            if (RR_DecodeCMChange(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_CLASSMARK_ENQUIRY:
            if (RR_DecodeCMEnquiry(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_MEASUREMENT_REPORT:
            if (RR_DecodeMeasureReport(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        case RR_MSG_PAGING_RESPONSE:
            if (RR_DecodePagingResp(msg, size, buffer) != ITS_SUCCESS)
            {
               return (ITS_EOVERFLOW);
            }
            break;

        default:
            return (!ITS_SUCCESS);
    }

    return ITS_SUCCESS;
}
