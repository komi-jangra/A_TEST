#include <abis_rr_management.h>

int
main()
{
    ITS_INT            choice;
    ITS_INT            size, i;
    ITS_OCTET          buffer[200];
    RR_MANAGEMENT_MSG  msg;
    ITS_OCTET buf[]  =  {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    ITS_OCTET buf1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7};
    ITS_OCTET buf11[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6};
    ITS_OCTET buf2[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                        0x09, 0x0A, 0x0B};
    ITS_OCTET buf3[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                        0x09, 0x0A, 0x0B, 0x0C};
    ITS_OCTET buf4[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

    while(1)
    {
        printf("\n\n******************************************************\n");
        printf("         Testing RR Management Messages");
        printf("\n******************************************************\n");
        printf("\t1.  Assignment Command\n");
        printf("\t2.  Assignment Complete\n");
        printf("\t3.  Assignment Failure\n");
        printf("\t4.  Ciphering Mode Command\n");
        printf("\t5.  Ciphering Mode Complete\n");
        printf("\t6.  Immediate Assignment\n");
        printf("\t7.  Immediate Assignment Reject\n");
        printf("\t8.  Channel Release\n");
        printf("\t9.  Classmark Change\n");
        printf("\t10. Classmark Enquiry\n");
        printf("\t11. Measerement Report\n");
        printf("\t12. Paging Response\n");
        printf("\t99. To quit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_ASSIGN_CMD;
                                                                                
                msg.u.assignCommand.descFCAT.chanType = 0x1F;
                msg.u.assignCommand.descFCAT.tn = 0x02;
                msg.u.assignCommand.descFCAT.tsc = 0x05;
                msg.u.assignCommand.descFCAT.h = 0x00;
                msg.u.assignCommand.descFCAT.arfcn = 0x0234;
                //msg.u.assignCommand.descFCAT.maio = 0x2A;
                //msg.u.assignCommand.descFCAT.hsn = 0x15;
                                                                                
                msg.u.assignCommand.powCmd.epc = 0x01;
                msg.u.assignCommand.powCmd.fpcEpc = 0x01;
                msg.u.assignCommand.powCmd.powLevel = 0x16;
/*
                msg.u.assignCommand.freqListAT.len = 16;
                msg.u.assignCommand.freqListAT.formatID = 0x00;
                memcpy(msg.u.assignCommand.freqListAT.val, buf4,
                             msg.u.assignCommand.freqListAT.len);
*/
                SET_OPT_FLAG_AC_CELL_CHAN_DESC((&msg));
                memcpy(msg.u.assignCommand.cellChanDesc.val, buf1,
                                                  sizeof(buf1));
/*
                msg.u.assignCommand.descMultiSlot.len = 10;
                msg.u.assignCommand.descMultiSlot.da = 0x7F;
                msg.u.assignCommand.descMultiSlot.ua = 0x66;
                memcpy(msg.u.assignCommand.descMultiSlot.chanSet, buf4,
                              (msg.u.assignCommand.descMultiSlot.len - 2));
*/
                SET_OPT_FLAG_AC_MODE_CHAN_SET1((&msg));
                msg.u.assignCommand.modeChanSet1.mode = 0x11;

                SET_OPT_FLAG_AC_MODE_CHAN_SET2((&msg));
                msg.u.assignCommand.modeChanSet2.mode = 0x22;

                SET_OPT_FLAG_AC_MODE_CHAN_SET3((&msg));
                msg.u.assignCommand.modeChanSet3.mode = 0x33;

                SET_OPT_FLAG_AC_MODE_CHAN_SET4((&msg));
                msg.u.assignCommand.modeChanSet4.mode = 0x44;

                SET_OPT_FLAG_AC_MODE_CHAN_SET5((&msg));
                msg.u.assignCommand.modeChanSet5.mode = 0x55;

                SET_OPT_FLAG_AC_MODE_CHAN_SET6((&msg));
                msg.u.assignCommand.modeChanSet6.mode = 0x66;

                SET_OPT_FLAG_AC_MODE_CHAN_SET7((&msg));
                msg.u.assignCommand.modeChanSet7.mode = 0x77;

                SET_OPT_FLAG_AC_MODE_CHAN_SET8((&msg));
                msg.u.assignCommand.modeChanSet8.mode = 0x88;

                SET_OPT_FLAG_AC_DESC_SC_AT((&msg));
                msg.u.assignCommand.descSCAT.chanType = 0x1F;
                msg.u.assignCommand.descSCAT.tn = 0x02;
                msg.u.assignCommand.descSCAT.tsc = 0x05;
                msg.u.assignCommand.descSCAT.h = 0x00;
                msg.u.assignCommand.descSCAT.arfcn = 0x03FF;
                //msg.u.assignCommand.descSCAT.maio = 0x2A;
                //msg.u.assignCommand.descSCAT.hsn = 0x15;

                SET_OPT_FLAG_AC_MODE_SEC_CHAN((&msg));
                msg.u.assignCommand.modeSecChan.mode = 0xAA;
/*
                msg.u.assignCommand.mobAllocAT.len = 0x08;
                memcpy(&msg.u.assignCommand.mobAllocAT.val, buf, sizeof(buf));
*/
                SET_OPT_FLAG_AC_START_TIME((&msg));
                msg.u.assignCommand.startTime.t1 = 0x11;
                msg.u.assignCommand.startTime.t2 = 0x16;
                msg.u.assignCommand.startTime.t3 = 0x33;
/*
                msg.u.assignCommand.freqListBT.len = 16;
                msg.u.assignCommand.freqListBT.formatID = 0x00;
                memcpy(msg.u.assignCommand.freqListBT.val, buf4,
                             msg.u.assignCommand.freqListBT.len);
*/
                SET_OPT_FLAG_AC_DESC_FC_BT((&msg));
                msg.u.assignCommand.descFCBT.chanType = 0x1F;
                msg.u.assignCommand.descFCBT.tn = 0x02;
                msg.u.assignCommand.descFCBT.tsc = 0x05;
                msg.u.assignCommand.descFCBT.h = 0x00;
                msg.u.assignCommand.descFCBT.arfcn = 0x03FF;
                //msg.u.assignCommand.descFCBT.maio = 0x2A;
                //msg.u.assignCommand.descFCBT.hsn = 0x15;

                SET_OPT_FLAG_AC_DESC_SC_BT((&msg));
                msg.u.assignCommand.descSCBT.chanType = 0x1F;
                msg.u.assignCommand.descSCBT.tn = 0x02;
                msg.u.assignCommand.descSCBT.tsc = 0x05;
                msg.u.assignCommand.descSCBT.h = 0x00;
                msg.u.assignCommand.descSCBT.arfcn = 0x03FF;
                //msg.u.assignCommand.descSCBT.maio = 0x2A;
                //msg.u.assignCommand.descSCBT.hsn = 0x15;
/*
                msg.u.assignCommand.freqChanSeqBT.lowARFCN = 0x2F;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[0] = 0x01;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[1] = 0x02;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[2] = 0x03;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[3] = 0x04;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[4] = 0x05;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[5] = 0x06;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[6] = 0x07;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[7] = 0x08;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[8] = 0x09;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[9] = 0x0A;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[10] = 0x0B;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[11] = 0x0C;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[12] = 0x0D;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[13] = 0x0E;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[14] = 0x0F;
                msg.u.assignCommand.freqChanSeqBT.isARFCN[15] = 0x01;

                msg.u.assignCommand.mobAllocBT.len = 0x08;
                memcpy(&msg.u.assignCommand.mobAllocBT.val, buf, sizeof(buf));
*/
                SET_OPT_FLAG_AC_CIPHER_MODE_SET((&msg));
                msg.u.assignCommand.cipherModeSet.sc = 0x01;
                msg.u.assignCommand.cipherModeSet.algorithmID = 0x03;

                SET_OPT_FLAG_AC_VGCS_TGT_MODE_IND((&msg));
                msg.u.assignCommand.vgcsTgtModeInd.len = 0x01;
                msg.u.assignCommand.vgcsTgtModeInd.tgtMode = 0x01;
                msg.u.assignCommand.vgcsTgtModeInd.groupCipherKey = 0x07;

                SET_OPT_FLAG_AC_MULTIRATE_CONFIG((&msg));
                msg.u.assignCommand.multirateConfig.len = 0x02;
                msg.u.assignCommand.multirateConfig.msVersion = 0x01;
                msg.u.assignCommand.multirateConfig.nscb = 0x00;
                msg.u.assignCommand.multirateConfig.icmi = 0x01;
                msg.u.assignCommand.multirateConfig.startMode = 0x01;
                msg.u.assignCommand.multirateConfig.amrCodecMode = 0x23;

                SET_OPT_FLAG_AC_VGCS_CIPHER_PARA((&msg));
                msg.u.assignCommand.vgcsCipherPara.len = 0x01;
                msg.u.assignCommand.vgcsCipherPara.randInd = 0x01;
                msg.u.assignCommand.vgcsCipherPara.lacInd = 0x01;
                msg.u.assignCommand.vgcsCipherPara.cellInd = 0x01;
                msg.u.assignCommand.vgcsCipherPara.b22Count = 0x01;
                msg.u.assignCommand.vgcsCipherPara.cgCount = 0x01;

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding AssignmentCommand\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                                                                                
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding AssignmentCommand\n");
                }

                if (PrintRRMsgAssignCmd(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing AssignmentCommand\n");
                }                                                                                 
                break;

            case 2:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_ASSIGN_CMP;

                msg.u.assignComplete.rrCause = 0x20;

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding AssignmentComplete\n");
                }       

                printf("\nEncoded Buffer :\n");

                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }

                printf("\nBuffer Length = %d", size);
                printf("\n\n");

                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding AssignmentComplete\n");
                }

                if (PrintRRMsgAssignCmp(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing AssignmentComplete\n");
                }

                break;

            case 3:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_ASSIGN_FAIL;

                msg.u.assignFailure.rrCause = 0x03;

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding Assignment Failure\n");
                }

                printf("\nEncoded Buffer :\n");
                                                                                
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }

                printf("\nBuffer Length = %d", size);
                printf("\n\n");

                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding AssignmentFailure\n");
                }
                                                                                
                if (PrintRRMsgAssignFail(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing AssignmentFailure\n");
                }

                break;
 
            case 4:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_CIPHERING_MODE_CMD;
                                                                                
                msg.u.cipherCommand.cipherModeSet = 0x04;
                msg.u.cipherCommand.cipherResp = 0x07;

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding CipheringModeCommand\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                                                                                
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding CipheringModeCommand\n");
                }

                if (PrintRRMsgCipherModeCmd(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing CipheringModeCommand\n");
                }

                break; 

            case 5:
                msg.u.cipherComplete.optIEFlags = 0x00;

                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_CIPHERING_MODE_CMP;

                SET_OPT_FLAG_MOBILE_EQUIP_ID((&msg));
                msg.u.cipherComplete.mobEquipID.len = 0x09;
                msg.u.cipherComplete.mobEquipID.typeOfID = 0x03;
                msg.u.cipherComplete.mobEquipID.oddEven = 0x00;
                memcpy(msg.u.cipherComplete.mobEquipID.idDigits, buf1,
                       sizeof(buf1));

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding CipheringModeComplete\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                                                                                
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding CipheringModeComplete\n");
                }
                                                                                
                if (PrintRRMsgCipherModeCmp(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing CipheringModeComplete\n");
                }
                break;

            case 6:
                msg.u.imAssign.optIEFlags = 0x00;

                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_IMMEDIATE_ASSIGN;

                msg.u.imAssign.pageMode = 0x03;
                msg.u.imAssign.dediMode = 0x05;

                msg.u.imAssign.chanDesc.chanType = 0x1F;
                msg.u.imAssign.chanDesc.tn = 0x02;
                msg.u.imAssign.chanDesc.tsc = 0x05;
                msg.u.imAssign.chanDesc.h = 0x00;
                msg.u.imAssign.chanDesc.arfcn = 0x0234;
                //msg.u.imAssign.chanDesc.maio = 0x2A;
                //msg.u.imAssign.chanDesc.hsn = 0x15;

                //Spare, so filled with 0x00
                memset(msg.u.imAssign.packChanDesc, 0x00, 3);

                msg.u.imAssign.reqRef.ra = 0xFF;
                msg.u.imAssign.reqRef.t[0] = 0x11;
                msg.u.imAssign.reqRef.t[1] = 0x12;

                msg.u.imAssign.timingAdv = 0x55;

                msg.u.imAssign.mobAlloc.len = 0x08;
                memcpy(&msg.u.imAssign.mobAlloc.val, buf, sizeof(buf));

                SET_OPT_FLAG_STARTING_TIME((&msg));
                msg.u.imAssign.startTime.t1 = 0x11;
                msg.u.imAssign.startTime.t2 = 0x16;
                msg.u.imAssign.startTime.t3 = 0x33;

                //Spare, so filled with 0x00
                //memset(msg.u.imAssign.iaRestOct, 0x00, 11);

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding ImmediateAssignment\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                                                                                
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding ImmediateAssignment\n");
                }

                if (PrintRRMsgImAssign(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing ImmediateAssignment\n");
                }

                break;

            case 7:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_IMMEDIATE_ASSIGN_REJ;

                msg.u.imAssignRej.pageMode = 0x03;

                msg.u.imAssignRej.reqRef1.ra = 0xFF;
                msg.u.imAssignRej.reqRef1.t[0] = 0x11;
                msg.u.imAssignRej.reqRef1.t[1] = 0x12;

                msg.u.imAssignRej.waitInd1 = 0x11;

                msg.u.imAssignRej.reqRef2.ra = 0xFF;
                msg.u.imAssignRej.reqRef2.t[0] = 0x21;
                msg.u.imAssignRej.reqRef2.t[1] = 0x22;

                msg.u.imAssignRej.waitInd2 = 0x22;

                msg.u.imAssignRej.reqRef3.ra = 0xFF;
                msg.u.imAssignRej.reqRef3.t[0] = 0x31;
                msg.u.imAssignRej.reqRef3.t[1] = 0x32;

                msg.u.imAssignRej.waitInd3 = 0x33;

                msg.u.imAssignRej.reqRef4.ra = 0xFF;
                msg.u.imAssignRej.reqRef4.t[0] = 0x41;
                msg.u.imAssignRej.reqRef4.t[1] = 0x42;
                                                                                
                msg.u.imAssignRej.waitInd4 = 0x44;

                //Spare, so filled with 0x00
                memset(msg.u.imAssignRej.iarRestOct, 0x00, 3);

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding ImmediateAssignmentReject\n");
                }

                printf("\nEncoded Buffer :\n");

                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }

                printf("\nBuffer Length = %d", size);
                printf("\n\n");

                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding ImmediateAssignmentReject\n");
                }

                if (PrintRRMsgImAssignRej(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing ImmediateAssignmentReject\n");
                }

                break;

            case 8:
                msg.u.chanRelease.optIEFlags1 = 0x00;
                msg.u.chanRelease.optIEFlags2 = 0x00;
                                                                                
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_CHANNEL_RELEASE;
                                                                                
                msg.u.chanRelease.rrCause = 0x33;
                                                                                
                SET_OPT_FLAG_BA_RANGE((&msg));
                msg.u.chanRelease.baRange.len = 0x04;
                msg.u.chanRelease.baRange.numOfRange = 0x01;
                memcpy(msg.u.chanRelease.baRange.range, buf ,
                                 (msg.u.chanRelease.baRange.len - 1));
                                                                                
                SET_OPT_FLAG_GROUP_CHAN_DESC((&msg));
                msg.u.chanRelease.groupChanDesc.len = 0x0B;
                msg.u.chanRelease.groupChanDesc.chanType = 0x1F;
                msg.u.chanRelease.groupChanDesc.tn = 0x02;
                msg.u.chanRelease.groupChanDesc.tsc = 0x05;
                msg.u.chanRelease.groupChanDesc.h = 0x00;
                msg.u.chanRelease.groupChanDesc.arfcn = 0x0234;
                //msg.u.chanRelease.groupChanDesc.maio = 0x2A;
                //msg.u.chanRelease.groupChanDesc.hsn = 0x15;
                memcpy(&msg.u.chanRelease.groupChanDesc.mac, buf, sizeof(buf));
                                                                                
                msg.u.chanRelease.groupCipherKey = 0x01;
                                                                                
                SET_OPT_FLAG_GPRS_RESUMP((&msg));
                msg.u.chanRelease.gprsResump = 0x01;

                SET_OPT_FLAG_BA_LIST_PREF((&msg));
                msg.u.chanRelease.baListPref.len = 0x08;
                memcpy(msg.u.chanRelease.baListPref.val, buf, sizeof(buf));

                SET_OPT_FLAG_UTRAN_FREQ_LIST((&msg));
                msg.u.chanRelease.utranFreqList.len = 0x08;
                memcpy(msg.u.chanRelease.utranFreqList.val, buf, sizeof(buf));

                SET_OPT_FLAG_CELL_SELECTION_IND((&msg));
                msg.u.chanRelease.cellSelIndl.len = 0x08;
                memcpy(msg.u.chanRelease.cellSelIndl.val, buf, sizeof(buf));

                SET_OPT_FLAG_CELL_CHAN_DESC((&msg));
                memcpy(msg.u.chanRelease.cellChanDesc.val, buf1, sizeof(buf1));

                SET_OPT_FLAG_RELEASE_INDICATION((&msg));
                msg.u.chanRelease.enRelInd = 0x01;

                SET_OPT_FLAG_VGCS_CIPHER_PARA((&msg));
                msg.u.chanRelease.vgcsCipherPara.len = 0x01;
                msg.u.chanRelease.vgcsCipherPara.randInd = 0x01;
                msg.u.chanRelease.vgcsCipherPara.lacInd = 0x01;
                msg.u.chanRelease.vgcsCipherPara.cellInd = 0x01;
                msg.u.chanRelease.vgcsCipherPara.b22Count = 0x01;
                msg.u.chanRelease.vgcsCipherPara.cgCount = 0x01;
/*
                msg.u.chanRelease.vgcsCiphPara.len = 0x08;
                memcpy(msg.u.chanRelease.vgcsCiphPara.val, buf, sizeof(buf)); 
*/
                SET_OPT_FLAG_GROUP_CHAN_DESC2((&msg));
                msg.u.chanRelease.groupChanDesc2.len = 0x0B;
                memcpy(msg.u.chanRelease.groupChanDesc2.val, buf2,
                                                     sizeof(buf2));

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding ChannelRelease\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding ChannelRelease\n");
                }
                                                                                
                if (PrintRRMsgChanRelease(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing ChannelRelease\n");
                }
                                                                                
                break;

            case 9:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_CLASSMARK_CHANGE;

                msg.u.cmChange.msClassmark.len = 0x03;
                msg.u.cmChange.msClassmark.revLevel = 0x01;
                msg.u.cmChange.msClassmark.esInd = 0x01;
                msg.u.cmChange.msClassmark.a51 = 0x00;
                msg.u.cmChange.msClassmark.rfPowCap = 0x04;
                msg.u.cmChange.msClassmark.psCap = 0x00;
                msg.u.cmChange.msClassmark.ssScreenInd = 0x02;
                msg.u.cmChange.msClassmark.smCap = 0x00;
                msg.u.cmChange.msClassmark.vbs = 0x01;
                msg.u.cmChange.msClassmark.vgcs = 0x01;
                msg.u.cmChange.msClassmark.fc = 0x00;
                msg.u.cmChange.msClassmark.cm3 = 0x01;
                msg.u.cmChange.msClassmark.lcsvaCap = 0x00;
                msg.u.cmChange.msClassmark.ucs2 = 0x01;
                msg.u.cmChange.msClassmark.soLSA = 0x00;
                msg.u.cmChange.msClassmark.cmsp = 0x01;
                msg.u.cmChange.msClassmark.a53 = 0x01;
                msg.u.cmChange.msClassmark.a52 = 0x00;

                msg.u.cmChange.addMsCmInfo.len = 0x0C;
                memcpy(msg.u.cmChange.addMsCmInfo.val, buf3,
                                        msg.u.cmChange.addMsCmInfo.len);

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding ClassmarkChange\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding ClassmarkChange\n");
                }
                                                                                
                if (PrintRRMsgCMChange(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing ClassmarkChange\n");
                }
                                                                                
                break;

            case 10:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_CLASSMARK_ENQUIRY;

                SET_OPT_FLAG_CM_ENQUIRY_MASK((&msg));
                msg.u.cmEnquiry.cmEnquiryMask.len = 0x01;
                msg.u.cmEnquiry.cmEnquiryMask.val = 0x1F;
                                                                                
                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding ClassmarkEnquiry\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding ClassmarkEnquiry\n");
                }
                                                                                
                if (PrintRRMsgCMEnquiry(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing ClassmarkEnquiry\n");
                }
                                                                                
                break;

            case 11:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_MEASUREMENT_REPORT;

                msg.u.measureReport.measureResult.baUsed = 0x01;
                msg.u.measureReport.measureResult.dtxUsed = 0x00;
                msg.u.measureReport.measureResult.rxLevFull = 0x18;
                msg.u.measureReport.measureResult.baUsed3G = 0x01;
                msg.u.measureReport.measureResult.measValid = 0x00;
                msg.u.measureReport.measureResult.rxLevSub = 0x18;
                msg.u.measureReport.measureResult.rxQualFull = 0x03;
                msg.u.measureReport.measureResult.rxQualSub = 0x03;
                msg.u.measureReport.measureResult.noNCellM = 0x01;
                msg.u.measureReport.measureResult.rxLevNCell1 = 0x22;
                msg.u.measureReport.measureResult.bcchFreqNCell1 = 0x11;
                msg.u.measureReport.measureResult.bsicNCell1 = 0x33;
                msg.u.measureReport.measureResult.rxLevNCell2 = 0x22;
                msg.u.measureReport.measureResult.bcchFreqNCell2 = 0x11;
                msg.u.measureReport.measureResult.bsicNCell2 = 0x33;
                msg.u.measureReport.measureResult.rxLevNCell3 = 0x22;
                msg.u.measureReport.measureResult.bcchFreqNCell3 = 0x11;
                msg.u.measureReport.measureResult.bsicNCell3 = 0x33;
                msg.u.measureReport.measureResult.rxLevNCell4 = 0x22;
                msg.u.measureReport.measureResult.bcchFreqNCell4 = 0x11;
                msg.u.measureReport.measureResult.bsicNCell4 = 0x33;
                msg.u.measureReport.measureResult.rxLevNCell5 = 0x22;
                msg.u.measureReport.measureResult.bcchFreqNCell5 = 0x11;
                msg.u.measureReport.measureResult.bsicNCell5 = 0x33;
                msg.u.measureReport.measureResult.rxLevNCell6 = 0x22;
                msg.u.measureReport.measureResult.bcchFreqNCell6 = 0x11;
                msg.u.measureReport.measureResult.bsicNCell6 = 0x33;

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding MeasurementReport\n");
                }
                                                                                
                printf("\nEncoded Buffer :\n");
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }
                                                                                
                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding MeasurementReport\n");
                }
                                                                                
                if (PrintRRMsgMeasureReport(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing MeasurementReport\n");
                }
                                                                                
                break;

            case 12:
                msg.msgSkipDisc = SKIP_INDICATOR | RR_PROTOCOL_DISC;
                msg.msgType = RR_MSG_PAGING_RESPONSE;

                msg.u.pagingResp.cipherKeySeq = 0x01;

                msg.u.pagingResp.msClassmark.len = 0x03;
                msg.u.pagingResp.msClassmark.revLevel = 0x01;
                msg.u.pagingResp.msClassmark.esInd = 0x01;
                msg.u.pagingResp.msClassmark.a51 = 0x00;
                msg.u.pagingResp.msClassmark.rfPowCap = 0x04;
                msg.u.pagingResp.msClassmark.psCap = 0x00;
                msg.u.pagingResp.msClassmark.ssScreenInd = 0x02;
                msg.u.pagingResp.msClassmark.smCap = 0x00;
                msg.u.pagingResp.msClassmark.vbs = 0x01;
                msg.u.pagingResp.msClassmark.vgcs = 0x01;
                msg.u.pagingResp.msClassmark.fc = 0x00;
                msg.u.pagingResp.msClassmark.cm3 = 0x01;
                msg.u.pagingResp.msClassmark.lcsvaCap = 0x00;
                msg.u.pagingResp.msClassmark.ucs2 = 0x01;
                msg.u.pagingResp.msClassmark.soLSA = 0x00;
                msg.u.pagingResp.msClassmark.cmsp = 0x01;
                msg.u.pagingResp.msClassmark.a53 = 0x01;
                msg.u.pagingResp.msClassmark.a52 = 0x00;

                msg.u.pagingResp.mobileID.len = 0x08;
                msg.u.pagingResp.mobileID.typeOfID = 0x03;
                msg.u.pagingResp.mobileID.oddEven = 0x00;
                memcpy(msg.u.pagingResp.mobileID.idDigits, buf11,
                       sizeof(buf11));

                if (RR_Encode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Encoding Paging Response\n");
                }

                printf("\nEncoded Buffer :\n");
                for (i = 0; i < size; i++)
                {
                    printf("%3.2x", buffer[i]);
                }

                printf("\nBuffer Length = %d", size);
                printf("\n\n");
                                                                                
                if (RR_Decode(&msg, &size, buffer) != ITS_SUCCESS)
                {
                    printf("Error while Decoding Paging Response\n");
                }
/*
                if (PrintRRMsgMeasureReport(&msg, &size) != ITS_SUCCESS)
                {
                    printf("Error while Printing MeasurementReport\n");
                }
*/                                                                                
                break;

            case 99:
                printf("\n\n***** Exiting from Test Application *****\n\n");
                exit(0);

            default:
                printf("\n\n******* Invalid Choice ********\n\n");
                break;
        }
    }
}
