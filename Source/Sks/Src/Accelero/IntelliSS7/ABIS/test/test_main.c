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
 *
 *  ID: $Id: test_main.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:53  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.2  2006/03/28 09:18:05  yranade
 *  TRX Hello message added. (sgavalkar)
 *
 *  Revision 1.1.2.1  2005/08/16 11:41:53  mkrishna
 *  Added Initial version after unit testing.
 *
 *
 ****************************************************************************/

#include <abis_codec.h>
#include <abis_network_management.h>
#include <abis_traffic_management.h>

extern ITS_INT (*testNetworkEncodeMsg[MAX_NETWORK_FUNS_SIZE])(int);

extern ITS_INT (*testNetworkDecodeMsg[MAX_NETWORK_FUNS_SIZE])(int);

extern ITS_INT (*testTrafficDecodeMsg[MAX_TRAFFIC_FUNS_SIZE])(int);

extern ITS_INT (*testTrafficEncodeMsg[MAX_TRAFFIC_FUNS_SIZE])(int);

int
main()
{
    int choice = 0, type = 0, code, msg;
                                                                                                                                              
    printf("CHOOSE THE MESSAGE\n");
    printf("====================\n");
    printf("1. Traffic Management Message \n");
    printf("2. Network Management Message \n\n");
    scanf("%d", &msg);
    if (msg < 1 || msg > 2)
    {
        printf("Invalid Choice \n");
        return 0;
    }

    if (msg == 1)
    {
        printf("CHOOSE THE TYPE OF THE MESSAGE\n");
        printf("==============================\n");
        printf("1. Radio Link Layer Management \n");
        printf("2. Common Channel Management \n");
        printf("3. Dedicated Channel Management \n");
        printf("4. TRX Management \n");
        printf("5. Location Sevice \n\n");
        scanf("%d", &type);
        if (type < 1 || type > 5)
        {
            printf("Invalid Choice \n");
            return 0;
        }
                                                                                                                                              
        switch(type)
        {
        case 1:
            printf("-----------RLLM-----------\n");
            printf("1  : Data Request \n");
            printf("2  : Data Indication \n");
            printf("3  : Error Indication \n");
            printf("4  : Establish Request \n");
            printf("5  : Establish Confirm \n");
            printf("6  : Establish Indication \n");
            printf("7  : Release Request \n");
            printf("8  : Release Confirm \n");
            printf("9  : Release Indication \n");
            printf("10 : Unit Data Request \n");
            printf("11 : Unit Data Indication \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 11)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 2:
            printf("--------- CCM ----------\n");
            printf("17 : BCCH Information \n");
            printf("18 : CCCH Load Indication \n");
            printf("19 : Channel Required \n");
            printf("20 : Delete Indication \n");
            printf("21 : Paging Command \n");
            printf("22 : Immediate Assign Command \n");
            printf("23 : SMS Broadcast Request \n");
            printf("29 : SMS Broadcast Command \n");
            printf("30 : CBCH Load Indication \n");
            printf("31 : Notification Command \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 17 || choice > 31)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 3:
            printf("--------- DCM ----------\n");
            printf("33 : Channel Activation \n");
            printf("34 : Channel Activation Acknowledge \n");
            printf("35 : Channel Activation Negative Acknowledge \n");
            printf("36 : Connection Failure Indication \n");
            printf("37 : Deactive SACCH \n");
            printf("38 : Encryption Command \n");
            printf("39 : Handover Detection \n");
            printf("40 : Measurement Result \n");
            printf("41 : Mode Modify \n");
            printf("42 : Mode Modify Acknowledge \n");
            printf("43 : Mode Modify Negative Acknowledge \n");
            printf("44 : Physical Context Request \n");
            printf("45 : Physical Context Confirm \n");
            printf("46 : RF Channel Release \n");
            printf("47 : MS Power Control \n");
            printf("48 : BS Power Control \n");
            printf("49 : Preprocess Configure \n");
            printf("50 : Preprocess Measurement Reesult \n");
            printf("51 : RF Channel Release Acknowledge \n");
            printf("52 : SACCH Info Modify \n");
            printf("53 : Talker Detection \n");
            printf("54 : Listener Detection \n");
            printf("55 : Remote Codec Configured Report \n");
            printf("56 : Round Trip Delay Report \n");
            printf("57 : Pre-Handover Notification \n");
            printf("58 : Multirate Codec Modification Request \n");
            printf("59 : Multirate Codec Modification Acknolewdge \n");
            printf("60 : Multirate Codec Modification Negative Acknolewdge \n");
            printf("61 : Multirate Codec Modification Performed \n");
            printf("62 : TFO Report \n");
            printf("63 : TFO Modification Request \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 33 || choice > 63)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 4:
            printf("--------- TRXM ----------\n");
            printf("25 : RF Resource Indication \n");
            printf("26 : SACCH Filling \n");
            printf("27 : Overload \n");
            printf("28 : Error Report \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 25 || choice > 28)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 5:
            printf("--------- LCS ----------\n");
            printf("65 : Location Information \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice != 65)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        default:
            printf("Invalid Choice \n");
            break;
        }
                                                                                                                                              
#if 0
        printf("RLLM Size :: %d\n", sizeof(RADIO_LINK_LAYER_MSG));
        printf("DCMM Size :: %d\n", sizeof(DEDICATED_CHANNEL_MSG));
        printf("CCM Size :: %d\n", sizeof(COMMON_CHANNEL_MSG));
        printf("TRXM Size :: %d\n", sizeof(TRXM_MSG));
        printf("LCS Size :: %d\n", sizeof(LOCATION_SERVICE_MSG));
        printf("CHANNEL ACTIVA :: %d\n", sizeof(TM_DCM_CHAN_ACTIV));
#endif
        if (code)
        {
            (testTrafficEncodeMsg[choice])(choice);
        }
        else
        {
            (testTrafficDecodeMsg[choice])(choice);
        }
    }
    else
    {
        printf("CHOOSE THE TYPE OF THE MESSAGE\n");
        printf("==============================\n");
        printf("1. SW Download Management \n");
        printf("2. A-bis Interface Management \n");
        printf("3. Transmission Management \n");
        printf("4. Air Interface Management \n");
        printf("5. Test Management \n");
        printf("6. State Management And Event Report Messages \n");
        printf("7. Equipment Management \n");
        printf("8. Measurment Management \n");
        printf("9. Other Management \n\n");
        scanf("%d", &type);
        if (type < 1 || type > 9)
        {
            printf("Invalid Choice \n");
            return 0;
        }
                                                                                                                                              
        switch(type)
        {
        case 1:
            printf("----------- SWDM -----------\n");
            printf("1  : Load Data Initiative \n");
            printf("2  : Load Data Initiative Ack \n");
            printf("3  : Load Data Initiative Nack \n");
            printf("4  : Load Data Segment \n");
            printf("5  : Load Data Segment Ack\n");
            printf("6  : Load Data Abort \n");
            printf("7  : Load Data End \n");
            printf("8  : Load Data End Ack \n");
            printf("9  : Load Data End Nack \n");
            printf("10 : SW Activate Request \n");
            printf("11 : SW Activate Request Ack \n");
            printf("12 : SW Activate Request Nack \n");
            printf("13 : Activate SW \n");
            printf("14 : Activate SW Ack \n");
            printf("15 : Activate SW Nack \n");
            printf("16 : SW Activated Report \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 16)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 2:
            printf("--------- AIM ----------\n");
            printf("33 : Establish TEI \n");
            printf("34 : Establish TEI Ack\n");
            printf("35 : Establish TEI Nack\n");
            printf("36 : Connect Terrestrial Signalling \n");
            printf("37 : Connect Terrestrial Signalling Ack\n");
            printf("38 : Connect Terrestrial Signalling Nack\n");
            printf("39 : Disconnect Terrestrial Signalling \n");
            printf("40 : Disconnect Terrestrial Signalling Ack\n");
            printf("41 : Disconnect Terrestrial Signalling Nack\n");
            printf("42 : Connect Terrestrial Traffic \n");
            printf("43 : Connect Terrestrial Traffic Ack \n");
            printf("44 : Connect Terrestrial Traffic Nack \n");
            printf("45 : Disconnect Terrestrial Traffic \n");
            printf("46 : Disconnect Terrestrial Traffic Ack\n");
            printf("47 : Disconnect Terrestrial Traffic Nack\n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 33 || choice > 47)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 3:
            printf("--------- TRMM ----------\n");
            printf("49 : Connect Multi-Drop Link \n");
            printf("50 : Connect Multi-Drop Link Ack\n");
            printf("51 : Connect Multi-Drop Link Nack\n");
            printf("52 : DisconnectMulti-Drop Link \n");
            printf("53 : DisconnectMulti-Drop Link Ack \n");
            printf("54 : DisconnectMulti-Drop Link Nack \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 49 || choice > 54)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 4:
            printf("--------- AIM ----------\n");
            printf("65 : Set BTS Attributes \n");
            printf("66 : Set BTS Attributes Ack \n");
            printf("67 : Set BTS Attributes Nack \n");
            printf("68 : Set Radio Carrier Attributes \n");
            printf("69 : Set Radio Carrier Attributes Ack \n");
            printf("70 : Set Radio Carrier Attributes Nack \n");
            printf("71 : Set Channel Attributes \n");
            printf("72 : Set Channel Attributes Ack \n");
            printf("73 : Set Channel Attributes Nack \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 65 || choice > 73)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 5:
            printf("--------- TMM ----------\n");
            printf("81 : Perform Test \n");
            printf("82 : Perform Test Ack \n");
            printf("83 : Perform Test Nack \n");
            printf("84 : Test Report \n");
            printf("85 : Send Test Report \n");
            printf("86 : Send Test Report Ack \n");
            printf("87 : Send Test Report Nack \n");
            printf("88 : Stop Test \n");
            printf("89 : Stop Test Ack \n");
            printf("90 : Stop Test Nack \n");
            printf("Enter message number..\n\n");
            scanf("%d", &choice);
            if (choice < 81 || choice > 90)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 6:
            printf("--------- SMM ----------\n");
            printf("97  : State Changed Event Report \n");
            printf("98  : Failure Event Report \n");
            printf("99  : Stop Sending Event Reports \n");
            printf("100 : Stop Sending Event Reports Ack \n");
            printf("101 : Stop Sending Event Reports Nack \n");
            printf("102 : Restart Sending Event Reports \n");
            printf("103 : Restart Sending Event Reports Ack \n");
            printf("104 : Restart Sending Event Reports Nack \n");
            printf("105 : Change Administrative State \n");
            printf("106 : Change Administrative State Ack \n");
            printf("107 : Change Administrative State Nack \n");
            printf("108 : Change Administrative State Request \n");
            printf("109 : Change Administrative State Request Ack \n");
            printf("110 : Change Administrative State Request Nack \n");
            printf("147 : Report Outstanding Alarms \n");
            printf("148 : Report Outstanding Alarms Ack \n");
            printf("149 : Report Outstanding Alarms Nack \n\n");
            printf("160 : TRX Hello \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 97 || choice > 161 )
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 7:
            printf("--------- EMM ----------\n");
            printf("113 : Changeover \n");
            printf("114 : Changeover Ack \n");
            printf("115 : Changeover Nack \n");
            printf("116 : Opstart \n");
            printf("117 : Opstart Ack \n");
            printf("118 : Opstart Nack \n");
            printf("119 : Set Site Outputs \n");
            printf("120 : Set Site Outputs Ack \n");
            printf("121 : Set Site Outputs Nack \n");
            printf("135 : Reinitialise \n");
            printf("136 : Reinitialise Ack \n");
            printf("137 : Reinitialise Nack \n");
            printf("144 : Change HW Configuration \n");
            printf("145 : Change HW Configuration Ack \n");
            printf("146 : Change HW Configuration Nack \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 113 || choice > 146)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 8:
            printf("--------- MMM ----------\n");
            printf("138 : Measurement Result Request \n");
            printf("139 : Measurement Result Response \n");
            printf("140 : Stop Measurement \n");
            printf("141 : Start Measurement \n");
            printf("Enter message number..\n\n");
            scanf("%d", &choice);
            if (choice < 138 || choice > 141)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        case 9:
            printf("--------- OMM ----------\n");
            printf("129 : Get Attributes \n");
            printf("130 : Get Attributes Response \n");
            printf("131 : Get Attributes Nack \n");
            printf("132 : Set Alarm Threshold \n");
            printf("133 : Set Alarm Threshold Ack \n");
            printf("134 : Set Alarm Threshold Nack \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 129 || choice > 134)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            printf("Encoding(press 1) or  Decoding (press 0).. \n");
            scanf("%d", &code);
            break;
        default:
            printf("Invalid Choice \n");
            break;
        }
                                                                                                                                              
#if 0
        printf("SW_DOWNLOAD_MANAGEMENT_MSG :: %d\n", sizeof(NM_SW_DOWNLOAD_MANAGEMENT_MSG));
        printf("ABIS_INTERFACE_MANAGEMENT_MSG :: %d\n", sizeof(NM_ABIS_INTERFACE_MANAGEMENT_MSG));
        printf("TRASMISSION_MANAGEMENT_MSG :: %d\n", sizeof(NM_TRASMISSION_MANAGEMENT_MSG));
        printf("AIR_INTERFACE_MANAGEMENT_MSG :: %d\n", sizeof(NM_AIR_INTERFACE_MANAGEMENT_MSG));
        printf("TEST_MANAGEMENT_MSG :: %d\n", sizeof(NM_TEST_MANAGEMENT_MSG));
        printf("STATE_MANAGEMENT_MSG :: %d\n", sizeof(NM_STATE_MANAGEMENT_MSG));
        printf("EQUIPMENT_MANAGEMENT_MSG :: %d\n", sizeof(NM_EQUIPMENT_MANAGEMENT_MSG));
        printf("MEASUREMENT_MANAGEMENT_MSG :: %d\n", sizeof(NM_MEASUREMENT_MANAGEMENT_MSG));
        printf("MISCELLANEOUS_MANAGEMENT_MSG :: %d\n\n\n", sizeof(NM_MISCELLANEOUS_MANAGEMENT_MSG));


        printf("NM_SWDM_LOAD_DATA_INIT :: %d\n", sizeof(NM_SWDM_LOAD_DATA_INIT)); 
        printf("NM_SWDM_LOAD_DATA_SEG :: %d\n", sizeof(NM_SWDM_LOAD_DATA_SEG)); 
        printf("NM_SWDM_LOAD_DATA_ABORT :: %d\n", sizeof(NM_SWDM_LOAD_DATA_ABORT)); 
        printf("NM_SWDM_LOAD_DATA_END :: %d\n", sizeof(NM_SWDM_LOAD_DATA_END)); 
        printf("NM_SWDM_SW_ACTIVE_REQ :: %d\n", sizeof(NM_SWDM_SW_ACTIVE_REQ)); 
        printf("NM_SWDM_ACTIVE_SW :: %d\n", sizeof(NM_SWDM_ACTIVE_SW)); 
        printf("NM_SWDM_SW_ACT_REPORT :: %d\n", sizeof(NM_SWDM_SW_ACT_REPORT)); 
#endif

        if (code)
        {
            (testNetworkEncodeMsg[choice])(choice);
        }
        else
        {
            (testNetworkDecodeMsg[choice])(choice);
        }
    }

    return ITS_SUCCESS;
}

