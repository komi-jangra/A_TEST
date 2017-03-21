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
 ****************************************************************************
 *  $Id: abis_rr_management_printIE.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
 *
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:52  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.2  2006/06/14 12:05:19  gdevanand
 *  Fix for BUG ID: 3894 and 3898
 *
 *  Revision 1.1.2.1  2006/02/06 05:27:29  yranade
 *  After unit test for 2nd validation release (badri).
 *
 *****************************************************************************/


#include <its.h>
#include <abis_rr_management.h>

ITS_INT
PrintRRMsgAssignCmp(RR_MANAGEMENT_MSG *msg)
{
    printf("\n***** RR Message : Assignment Complete *****\n");

    printf("\nRR Cause: %3.2x\n", msg->u.assignComplete.rrCause);

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgAssignCmd(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;

    printf("\n***** RR Message : Assignment Command *****\n");

    printf("\nDescription of the First Channel, After Time:\n");
    printf("\tChannel Type: %3.2x\n", msg->u.assignCommand.descFCAT.chanType);
    printf("\tTN: %3.2x\n", msg->u.assignCommand.descFCAT.tn);
    printf("\tTSC: %3.2x\n", msg->u.assignCommand.descFCAT.tsc);
    if (msg->u.assignCommand.descFCAT.h)
    {
        printf("\tH: %3.2x\n", msg->u.assignCommand.descFCAT.h);
        printf("\tMAIO: %3.2x\n", msg->u.assignCommand.descFCAT.maio);
        printf("\tHSN: %3.2x\n", msg->u.assignCommand.descFCAT.hsn);
    }
    else
    {
        printf("\tH: %3.2x\n", msg->u.assignCommand.descFCAT.h);
        printf("\tARFCN: %3.2x\n", msg->u.assignCommand.descFCAT.arfcn);
    }

    printf("\nPower Command:\n");
    printf("\tEPC: %3.2x\n", msg->u.assignCommand.powCmd.epc);
    printf("\tFPC EPC: %3.2x\n", msg->u.assignCommand.powCmd.fpcEpc);
    printf("\tPower Level: %3.2x\n", msg->u.assignCommand.powCmd.powLevel);
/*
    printf("\nFrequency List After Time:\n");
    printf("\tFormat ID: %3.2x\n", msg->u.assignCommand.freqListAT.formatID);
    printf("\tARFCN :");
    for (i = 0; i < msg->u.assignCommand.freqListAT.len - 1; i++)
    {
        printf(" %3.2x", msg->u.assignCommand.freqListAT.val[i]);
    }        
*/
    if (GET_OPT_FLAG_AC_CELL_CHAN_DESC(msg))
    {
        printf("\n\nCell Channel Description:\n\t");
        for (i = 0; i < 16; i++)
        {
            printf(" %3.2x", msg->u.assignCommand.cellChanDesc.val[i]);
        }
    }
/*
    printf("\n\nDescription of Multislot Configuration:");
    printf("\n\tDA: %3.2x", msg->u.assignCommand.descMultiSlot.da);
    printf("\n\tUA: %3.2x", msg->u.assignCommand.descMultiSlot.ua);
    printf("\n\tChannel Set:");
    for (i = 0; i < msg->u.assignCommand.descMultiSlot.len - 2; i++)
    {
        printf(" %3.2x", msg->u.assignCommand.descMultiSlot.chanSet[i]);
    } 
*/
    if (GET_OPT_FLAG_AC_MODE_CHAN_SET1(msg))
    {
        printf("\n\nMode of 1st Channel: %3.2x",
                          msg->u.assignCommand.modeChanSet1.mode);
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET2(msg))
    {
        printf("\n\nMode of 2nd Channel: %3.2x",
                           msg->u.assignCommand.modeChanSet2.mode);
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET3(msg))
    {
        printf("\n\nMode of 3rd Channel: %3.2x",
                           msg->u.assignCommand.modeChanSet3.mode);
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET4(msg))
    {
        printf("\n\nMode of 4th Channel: %3.2x",
                           msg->u.assignCommand.modeChanSet4.mode);
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET5(msg))
    {
        printf("\n\nMode of 5th Channel: %3.2x",
                           msg->u.assignCommand.modeChanSet5.mode);
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET6(msg))
    {
        printf("\n\nMode of 6th Channel: %3.2x",  
                           msg->u.assignCommand.modeChanSet6.mode);
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET7(msg))
    {
        printf("\n\nMode of 7th Channel: %3.2x",
                           msg->u.assignCommand.modeChanSet7.mode);
    }

    if (GET_OPT_FLAG_AC_MODE_CHAN_SET8(msg))
    {
        printf("\n\nMode of 8th Channel: %3.2x",
                           msg->u.assignCommand.modeChanSet8.mode);
    }

    if (GET_OPT_FLAG_AC_DESC_SC_AT(msg))
    {
        printf("\n\nDescription of Second Channel After Time:\n");
        printf("\tChannel Type: %3.2x\n",
                                msg->u.assignCommand.descSCAT.chanType);
        printf("\tTN: %3.2x\n", msg->u.assignCommand.descSCAT.tn);
        printf("\tTSC: %3.2x\n", msg->u.assignCommand.descSCAT.tsc);
        if (msg->u.assignCommand.descSCAT.h)
        {
            printf("\tH: %3.2x\n", msg->u.assignCommand.descSCAT.h);
            printf("\tMAIO: %3.2x\n", msg->u.assignCommand.descSCAT.maio);
            printf("\tHSN: %3.2x\n", msg->u.assignCommand.descSCAT.hsn);
        }
        else
        {
            printf("\tH: %3.2x\n", msg->u.assignCommand.descSCAT.h);
            printf("\tARFCN: %3.2x\n", msg->u.assignCommand.descSCAT.arfcn);
        }
    }

    if (GET_OPT_FLAG_AC_MODE_SEC_CHAN(msg))
    {
        printf("\n\nMode of Second Channel: %3.2x\n",
                                msg->u.assignCommand.modeSecChan.mode);
    }
/*
    printf("\n\nMobile Allocation After Time:\n\t");
    for (i = 0; i < msg->u.assignCommand.mobAllocAT.len; i++)
    {
        printf(" %3.2x", msg->u.assignCommand.mobAllocAT.val[i]);
    }
*/
    if (GET_OPT_FLAG_AC_START_TIME(msg))
    {
        printf("\n\nStarting Time:\n");
        printf("\tT1: %3.2x\n",msg->u.assignCommand.startTime.t1);
        printf("\tT2: %3.2x\n",msg->u.assignCommand.startTime.t2);
        printf("\tT3: %3.2x\n",msg->u.assignCommand.startTime.t3);
    }
/*
    printf("\n\nFrequency List Before Time:\n");
    printf("\tFormat ID: %3.2x\n", msg->u.assignCommand.freqListBT.formatID);
    printf("\tARFCN :");
    for (i = 0; i < msg->u.assignCommand.freqListBT.len - 1; i++)
    {
        printf(" %3.2x", msg->u.assignCommand.freqListBT.val[i]);
    }
*/
    if (GET_OPT_FLAG_AC_DESC_FC_BT(msg))
    {
        printf("\n\nDescription of First Channel Before Time:\n");   
        printf("\tChannel Type: %3.2x\n",
                                msg->u.assignCommand.descFCBT.chanType);
        printf("\tTN: %3.2x\n", msg->u.assignCommand.descFCBT.tn);
        printf("\tTSC: %3.2x\n", msg->u.assignCommand.descFCBT.tsc);
        if (msg->u.assignCommand.descFCBT.h)
        {
            printf("\tH: %3.2x\n", msg->u.assignCommand.descFCBT.h);
            printf("\tMAIO: %3.2x\n", msg->u.assignCommand.descFCBT.maio);
            printf("\tHSN: %3.2x\n", msg->u.assignCommand.descFCBT.hsn);
        }
        else
        {
            printf("\tH: %3.2x\n", msg->u.assignCommand.descFCBT.h);
            printf("\tARFCN: %3.2x\n", msg->u.assignCommand.descFCBT.arfcn);
        }
    }

    if (GET_OPT_FLAG_AC_DESC_SC_BT(msg))
    {
        printf("\n\nDescription of Second Channel Before Time:\n");
        printf("\tChannel Type: %3.2x\n",
                                msg->u.assignCommand.descSCBT.chanType);
        printf("\tTN: %3.2x\n", msg->u.assignCommand.descSCBT.tn);
        printf("\tTSC: %3.2x\n", msg->u.assignCommand.descSCBT.tsc);
        if (msg->u.assignCommand.descSCBT.h)
        {
            printf("\tH: %3.2x\n", msg->u.assignCommand.descSCBT.h);
            printf("\tMAIO: %3.2x\n", msg->u.assignCommand.descSCBT.maio);
            printf("\tHSN: %3.2x\n", msg->u.assignCommand.descSCBT.hsn);
        }
        else
        {
            printf("\tH: %3.2x\n", msg->u.assignCommand.descSCBT.h);
            printf("\tARFCN: %3.2x\n", msg->u.assignCommand.descSCBT.arfcn);
        }
     }
/*
    printf("\n\nFrequency Channel Sequence Before Time:\n");
    printf("\n\tLowest ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.lowARFCN);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[0]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[1]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[2]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[3]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[4]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[5]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[6]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[7]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[8]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[9]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[10]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[11]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[12]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[13]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[14]);
    printf("\n\tinc skip of ARFCN: %3.2x",
                            msg->u.assignCommand.freqChanSeqBT.isARFCN[15]);

    printf("\n\nMobile Allocation Before Time:\n\t");
    for (i = 0; i < msg->u.assignCommand.mobAllocBT.len; i++)
    {
        printf(" %3.2x", msg->u.assignCommand.mobAllocBT.val[i]);
    }
*/
    if (GET_OPT_FLAG_AC_CIPHER_MODE_SET(msg))
    {
        printf("\n\nCipher Mode Setting:");
        printf("\n\tAlgorithm Identifier: %3.2x",
                       msg->u.assignCommand.cipherModeSet.algorithmID);
        printf("\n\tSC: %3.2x", msg->u.assignCommand.cipherModeSet.sc);
    }

    if (GET_OPT_FLAG_AC_VGCS_TGT_MODE_IND(msg))
    {
        printf("\n\nVGCS Target Mode Indicator:");
        printf("\n\tTarget Mode: %3.2x",
                           msg->u.assignCommand.vgcsTgtModeInd.tgtMode);
        printf("\n\tGroup Cipher Key Number: %3.2x",
                           msg->u.assignCommand.vgcsTgtModeInd.groupCipherKey);
    }

    if (GET_OPT_FLAG_AC_MULTIRATE_CONFIG(msg))
    {
        printf("\n\nMultirate Configuration:");
        printf("\n\tMultirate Speech Version: %3.2x",
                            msg->u.assignCommand.multirateConfig.msVersion);
        printf("\n\tNSCB: %3.2x",
                            msg->u.assignCommand.multirateConfig.nscb);
        printf("\n\tICMI: %3.2x", 
                            msg->u.assignCommand.multirateConfig.icmi);
        printf("\n\tStart Mode: %3.2x", 
                            msg->u.assignCommand.multirateConfig.startMode);
        printf("\n\tAMR Codec Mode: %3.2x", 
                            msg->u.assignCommand.multirateConfig.amrCodecMode);
    }

    if (GET_OPT_FLAG_AC_VGCS_CIPHER_PARA(msg))
    {
        printf("\n\nVGCS Ciphering Parameter:");
        printf("\n\tRAND IND: %3.2x",
                            msg->u.assignCommand.vgcsCipherPara.randInd);
        printf("\n\tLAC IND: %3.2x",
                            msg->u.assignCommand.vgcsCipherPara.lacInd);
        printf("\n\tCELL IND: %3.2x",
                            msg->u.assignCommand.vgcsCipherPara.cellInd);
        printf("\n\tB22 Count: %3.2x",
                            msg->u.assignCommand.vgcsCipherPara.b22Count);
        printf("\n\tCell Global Count: %3.2x",
                            msg->u.assignCommand.vgcsCipherPara.cgCount);
    }

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgAssignFail(RR_MANAGEMENT_MSG *msg)
{
    printf("\n***** RR Message : Assignment Failure *****\n");
                                                                                
    printf("\nRR Cause: %3.2x\n", msg->u.assignFailure.rrCause);
                                                                                
    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgCipherModeCmd(RR_MANAGEMENT_MSG *msg)
{
    printf("\n***** RR Message : Ciphering Mode Command *****\n");

    printf("\nCiphering Mode Setting cmsSC: %3.2x\n",
                                       msg->u.cipherCommand.cmsSC );
	printf("\nCiphering Mode Setting cmsAlgoid: %3.2x\n",
                                       msg->u.cipherCommand.cmsAlgoid );
    printf("Ciphering Response CR: %3.2x\n", msg->u.cipherCommand.CR);

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgCipherModeCmp(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;

    printf("\n***** RR Message : Ciphering Mode Complete *****\n");

    if (GET_OPT_FLAG_MOBILE_EQUIP_ID(msg))
    {
        printf("\nMobile Equipment Identity:\n");
        printf("\tType of Identity: %3.2x\n",
                         msg->u.cipherComplete.mobEquipID.typeOfID);
        printf("\tOdd/Even Indicator: %3.2x\n",
                         msg->u.cipherComplete.mobEquipID.oddEven);
        printf("\tIdentity Digits:");
    
        for (i = 0; i < 16; i++)
        {
            printf(" %3.2x", msg->u.cipherComplete.mobEquipID.idDigits[i]);
        }
    }

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgChanRelease(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;

    printf("\n***** RR Message : Channel Release *****\n");

    printf("\nRR Cause: %3.2x\n", msg->u.chanRelease.rrCause);

    if (GET_OPT_FLAG_BA_RANGE(msg))
    {
        printf("\nBA Range:\n");
        printf("\tNo. of Range: %3.2x\n",
                             msg->u.chanRelease.baRange.numOfRange);
        printf("\tRange: %3.2x %3.2x %3.2x\n",
                             msg->u.chanRelease.baRange.range[0],
                             msg->u.chanRelease.baRange.range[1],
                             msg->u.chanRelease.baRange.range[2]);
    }

    if (GET_OPT_FLAG_GROUP_CHAN_DESC(msg))
    {
        printf("\nGroup Channel Desciption:\n");
        printf("\tChannel Type: %3.2x\n", 
                                msg->u.chanRelease.groupChanDesc.chanType);
        printf("\tTN: %3.2x\n", msg->u.chanRelease.groupChanDesc.tn);
        printf("\tTSC: %3.2x\n", msg->u.chanRelease.groupChanDesc.tsc);

        if (msg->u.chanRelease.groupChanDesc.h & 0x01)
        {
            printf("\tH: %3.2x\n", msg->u.chanRelease.groupChanDesc.h);
            printf("\tMAIO: %3.2x\n", msg->u.chanRelease.groupChanDesc.maio);
            printf("\tHSN: %3.2x\n", msg->u.chanRelease.groupChanDesc.hsn);
        }
        else
        {
            printf("\tH: %3.2x\n", msg->u.chanRelease.groupChanDesc.h);
            printf("\tARFCN: %3.2x\n", msg->u.chanRelease.groupChanDesc.arfcn);
        }

        printf("\tMAC:");
        for (i = 0; i < 8; i++)
        {
            printf("%3.2x", msg->u.chanRelease.groupChanDesc.mac[i]);
        }
    }

    printf("\n\nGroup Cipher Key: %3.2x\n", msg->u.chanRelease.groupCipherKey);

    if (GET_OPT_FLAG_GPRS_RESUMP(msg))
    {
        printf("\nGPRS Resumption: %3.2x\n", msg->u.chanRelease.gprsResump);
    }

    printf("\nBA List Pref:");

    if (GET_OPT_FLAG_BA_LIST_PREF(msg))
    {
        for (i = 0; i < msg->u.chanRelease.baListPref.len; i++)
        {
            printf("%3.2x", msg->u.chanRelease.baListPref.val[i]);
        }
    }

    printf("\n\nUTRAN Freq List:");

    if (GET_OPT_FLAG_UTRAN_FREQ_LIST(msg))
    {
        for (i = 0; i < msg->u.chanRelease.utranFreqList.len; i++)
        {
            printf("%3.2x", msg->u.chanRelease.utranFreqList.val[i]);
        }
    }

    printf("\n\nCell Selection Indicator:");

    if (GET_OPT_FLAG_CELL_SELECTION_IND(msg))
    {
        for (i = 0; i < msg->u.chanRelease.cellSelIndl.len; i++)
        {
            printf("%3.2x", msg->u.chanRelease.cellSelIndl.val[i]);
        }
    }

    printf("\n\nCell Channel Description:");

    if (GET_OPT_FLAG_CELL_CHAN_DESC(msg))
    {
        for (i = 0; i < 16; i++)
        {
            printf("%3.2x", msg->u.chanRelease.cellChanDesc.val[i]);
        }
    }

    if (GET_OPT_FLAG_RELEASE_INDICATION(msg))
    {
        printf("\n\nEnhanced DTM CS Release Indication: %3.2x\n",
                                          msg->u.chanRelease.enRelInd);
    }

    printf("\nVGCS Ciphering Parameter:\n");

    if (GET_OPT_FLAG_VGCS_CIPHER_PARA(msg))
    {
        printf("\tRAND IND:%3.2x\n", msg->u.chanRelease.vgcsCipherPara.randInd);
        printf("\tLAC IND:%3.2x\n", msg->u.chanRelease.vgcsCipherPara.lacInd);
        printf("\tCELL IND:%3.2x\n", msg->u.chanRelease.vgcsCipherPara.cellInd);
        printf("\tB22 Count:%3.2x\n",
                            msg->u.chanRelease.vgcsCipherPara.b22Count);
        printf("\tCell Global Count:%3.2x\n",
                             msg->u.chanRelease.vgcsCipherPara.cgCount);
    }

    printf("\n\nGroup Channel Description:");

    if (GET_OPT_FLAG_GROUP_CHAN_DESC2(msg))
    {
        for (i = 0; i < msg->u.chanRelease.groupChanDesc2.len; i++)
        {
            printf("%3.2x", msg->u.chanRelease.groupChanDesc2.val[i]);
        }
    }

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgImAssign(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;

    printf("\n***** RR Message : Immediate Assignment *****\n");

    printf("\nPage Mode: %3.2x\n", msg->u.imAssign.pageMode);
    printf("Dedicated Mode: %3.2x\n", msg->u.imAssign.dediMode);

    printf("\nChannel Description:\n");
    printf("\tChannel Type: %3.2x\n", msg->u.imAssign.chanDesc.chanType);
    printf("\tTN: %3.2x\n", msg->u.imAssign.chanDesc.tn);
    printf("\tTSC: %3.2x\n", msg->u.imAssign.chanDesc.tsc);
    if (msg->u.imAssign.chanDesc.h)
    {
        printf("\tH: %3.2x\n", msg->u.imAssign.chanDesc.h);
        printf("\tMAIO: %3.2x\n", msg->u.imAssign.chanDesc.maio);
        printf("\tHSN: %3.2x\n", msg->u.imAssign.chanDesc.hsn);
    }
    else
    {
        printf("\tH: %3.2x\n", msg->u.imAssign.chanDesc.h);
        printf("\tARFCN: %3.2x\n", msg->u.imAssign.chanDesc.arfcn);
    }

    printf("\nRequest Reference:\n");
    printf("\tRA: %3.2x\n", msg->u.imAssign.reqRef.ra);
    printf("\tT: %3.2x %3.2x\n", msg->u.imAssign.reqRef.t[0],
                                 msg->u.imAssign.reqRef.t[1]);

    printf("\nTiming Advance: %3.2x\n", msg->u.imAssign.timingAdv);

    printf("\nMobile Allocation:\n\t");
    if (msg->u.imAssign.chanDesc.h == 0)
    {
        printf("This IE has no data, length = 0\n");
    }
    else
    {
        for (i = 0; i < msg->u.imAssign.mobAlloc.len; i++)
        {
            printf("%3.2x", msg->u.imAssign.mobAlloc.val[i]);
        }
    }

    if (GET_OPT_FLAG_STARTING_TIME(msg))
    {
        printf("\n\nStarting Time:\n");
        printf("\tT1: %3.2x\n", msg->u.imAssign.startTime.t1);
        printf("\tT2: %3.2x\n", msg->u.imAssign.startTime.t2);
        printf("\tT3: %3.2x\n", msg->u.imAssign.startTime.t3);
    }

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgImAssignRej(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;
                                                                                
    printf("\n***** RR Message : Immediate Assignment Reject *****\n");
                                                                                
    printf("\nPage Mode: %3.2x\n", msg->u.imAssignRej.pageMode);

    printf("\nRequest Reference 1:\n");
    printf("\tRA: %3.2x\n", msg->u.imAssignRej.reqRef1.ra);
    printf("\tT: %3.2x %3.2x\n", msg->u.imAssignRej.reqRef1.t[0],                                                msg->u.imAssignRej.reqRef1.t[1]);

    printf("\nWait Indication 1: %3.2x\n", msg->u.imAssignRej.waitInd1);

    printf("\nRequest Reference 2:\n");
    printf("\tRA: %3.2x\n", msg->u.imAssignRej.reqRef2.ra);
    printf("\tT: %3.2x %3.2x\n", msg->u.imAssignRej.reqRef2.t[0],                                                msg->u.imAssignRej.reqRef2.t[1]);

    printf("\nWait Indication 2: %3.2x\n", msg->u.imAssignRej.waitInd2);

    printf("\nRequest Reference 3:\n");
    printf("\tRA: %3.2x\n", msg->u.imAssignRej.reqRef3.ra);
    printf("\tT: %3.2x %3.2x\n", msg->u.imAssignRej.reqRef3.t[0],                                                msg->u.imAssignRej.reqRef3.t[1]);

    printf("\nWait Indication 3: %3.2x\n", msg->u.imAssignRej.waitInd3);

    printf("\nRequest Reference 4:\n");
    printf("\tRA: %3.2x\n", msg->u.imAssignRej.reqRef4.ra);
    printf("\tT: %3.2x %3.2x\n", msg->u.imAssignRej.reqRef4.t[0],                                                msg->u.imAssignRej.reqRef4.t[1]);

    printf("\nWait Indication 4: %3.2x\n", msg->u.imAssignRej.waitInd4);

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgCMChange(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;
                                                                                
    printf("\n***** RR Message : Classmark Change *****\n");

    printf("\nMobile Station Classmark:\n");
    printf("\trevLevel: %3.2x\n", msg->u.cmChange.msClassmark.revLevel);
    printf("\tesInd: %3.2x\n", msg->u.cmChange.msClassmark.esInd );
    printf("\ta51: %3.2x\n", msg->u.cmChange.msClassmark.a51);
    printf("\trfPowCap: %3.2x\n", msg->u.cmChange.msClassmark.rfPowCap);
    printf("\tpsCap: %3.2x\n", msg->u.cmChange.msClassmark.psCap);
    printf("\tssScreenInd: %3.2x\n", msg->u.cmChange.msClassmark.ssScreenInd);
    printf("\tsmCap: %3.2x\n", msg->u.cmChange.msClassmark.smCap);
    printf("\tvbs: %3.2x\n", msg->u.cmChange.msClassmark.vbs);
    printf("\tvgcs: %3.2x\n", msg->u.cmChange.msClassmark.vgcs);
    printf("\tfc: %3.2x\n", msg->u.cmChange.msClassmark.fc);
    printf("\tcm3: %3.2x\n", msg->u.cmChange.msClassmark.cm3);
    printf("\tlcsvaCap: %3.2x\n", msg->u.cmChange.msClassmark.lcsvaCap);
    printf("\tucs2: %3.2x\n", msg->u.cmChange.msClassmark.ucs2);
    printf("\tsoLSA: %3.2x\n", msg->u.cmChange.msClassmark.soLSA);
    printf("\tcmsp: %3.2x\n", msg->u.cmChange.msClassmark.cmsp);
    printf("\ta53: %3.2x\n", msg->u.cmChange.msClassmark.a53);
    printf("\ta52: %3.2x\n", msg->u.cmChange.msClassmark.a52);

    if (msg->u.cmChange.msClassmark.cm3 > 0)
    {
        printf("\nAdditional Mobile Station Classmark Information:\n\t");
        for (i = 0; i < msg->u.cmChange.addMsCmInfo.len; i++)
        {
            printf("%3.2x", msg->u.cmChange.addMsCmInfo.val[i]);
        }
    }

    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgCMEnquiry(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;
                                                                                
    printf("\n***** RR Message : Classmark Enquiry *****\n");
                      
    printf("\nClassmark Enquiry Mask: %3.2x\n",
                                        msg->u.cmEnquiry.cmEnquiryMask.val);
                                                          
    return ITS_SUCCESS;
}

ITS_INT
PrintRRMsgMeasureReport(RR_MANAGEMENT_MSG *msg)
{
    ITS_INT i;
                                                                                
    printf("\n***** RR Message : Measurement Report *****\n");

    printf("\nMeasurement Results:\n");
    printf("\tBA Used: %3.2x\n", msg->u.measureReport.measureResult.baUsed);
    printf("\tDTX Used: %3.2x\n", msg->u.measureReport.measureResult.dtxUsed);
    printf("\tRXLev Full Servicing Cell: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevFull);
    printf("\t3G BA Used: %3.2x\n",
                           msg->u.measureReport.measureResult.baUsed3G);
    printf("\tMeas Value: %3.2x\n",
                           msg->u.measureReport.measureResult.measValid);
    printf("\tRXLev Sub Servicing Cell: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevSub);
    printf("\tRX Qual Full Servicing Cell: %3.2x\n",
                           msg->u.measureReport.measureResult.rxQualFull);
    printf("\tRX  Sub Servicing Cell: %3.2x\n",
                           msg->u.measureReport.measureResult.rxQualSub);
    printf("\tNo N Cell M: %3.2x\n",
                           msg->u.measureReport.measureResult.noNCellM);
    printf("\tRXLev N Cell 1: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevNCell1);
    printf("\tBCCH Freq N Cell M 1: %3.2x\n",
                           msg->u.measureReport.measureResult.bcchFreqNCell1);
    printf("\tBSIC N Cell 1: %3.2x\n",
                           msg->u.measureReport.measureResult.bsicNCell1);
    printf("\tRXLev N Cell 2: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevNCell2);
    printf("\tBCCH Freq N Cell M 2: %3.2x\n",
                           msg->u.measureReport.measureResult.bcchFreqNCell2);
    printf("\tBSIC N Cell 2: %3.2x\n",
                           msg->u.measureReport.measureResult.bsicNCell2);
    printf("\tRXLev N Cell 3: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevNCell3);
    printf("\tBCCH Freq N Cell M 3: %3.2x\n",
                           msg->u.measureReport.measureResult.bcchFreqNCell3);
    printf("\tBSIC N Cell 3: %3.2x\n",
                           msg->u.measureReport.measureResult.bsicNCell3);
    printf("\tRXLev N Cell 4: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevNCell4);
    printf("\tBCCH Freq N Cell M 4: %3.2x\n",
                           msg->u.measureReport.measureResult.bcchFreqNCell4);
    printf("\tBSIC N Cell 4: %3.2x\n",
                           msg->u.measureReport.measureResult.bsicNCell4);
    printf("\tRXLev N Cell 5: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevNCell5);
    printf("\tBCCH Freq N Cell M 5: %3.2x\n",
                           msg->u.measureReport.measureResult.bcchFreqNCell5);
    printf("\tBSIC N Cell 5: %3.2x\n",
                           msg->u.measureReport.measureResult.bsicNCell5);
    printf("\tRXLev N Cell 6: %3.2x\n",
                           msg->u.measureReport.measureResult.rxLevNCell6);
    printf("\tBCCH Freq N Cell M 6: %3.2x\n",
                           msg->u.measureReport.measureResult.bcchFreqNCell6);
    printf("\tBSIC N Cell 6: %3.2x\n",
                           msg->u.measureReport.measureResult.bsicNCell6);

    return ITS_SUCCESS;
}

void
Print_Abis_RR_Management_Msg(RR_MANAGEMENT_MSG *msg)
{
    switch (msg->msgType)
    {
        case RR_MSG_ASSIGN_CMP:
            if (PrintRRMsgAssignCmp(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Assignment Complete\n");
            }
            break; 

        case RR_MSG_CIPHERING_MODE_CMD:
            if (PrintRRMsgCipherModeCmd(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Cipher Mode Command\n");
            }
            break;

        case RR_MSG_CIPHERING_MODE_CMP:
            if (PrintRRMsgCipherModeCmp(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Cipher Mode Complete\n");
            }
            break;

        case RR_MSG_CHANNEL_RELEASE:
            if (PrintRRMsgChanRelease(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Channel Release\n");
            }
            break;

        case RR_MSG_ASSIGN_CMD:
            if (PrintRRMsgAssignCmd(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Assignment Command\n");
            }
            break;

        case RR_MSG_ASSIGN_FAIL:
            if (PrintRRMsgAssignFail(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Assignment Failure\n");
            }
            break;

        case RR_MSG_IMMEDIATE_ASSIGN:
            if (PrintRRMsgImAssign(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Immediate Assignment\n");
            }
            break;

        case RR_MSG_IMMEDIATE_ASSIGN_REJ:
            if (PrintRRMsgImAssignRej(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Immediate Assignment Reject\n");
            }
            break;

        case RR_MSG_CLASSMARK_CHANGE:
            if (PrintRRMsgCMChange(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Classmark Change\n");
            }
            break;

        case RR_MSG_CLASSMARK_ENQUIRY:
            if (PrintRRMsgCMEnquiry(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Classmark Enquiry\n");
            }
            break;

        case RR_MSG_MEASUREMENT_REPORT:
            if (PrintRRMsgMeasureReport(msg) != ITS_SUCCESS)
            {
                printf("Error in printing Measurement Report\n");
            }
            break;

        default:
            printf("Unknown Message\n");
            break;
    }
}
