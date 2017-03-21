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
 *  ID: $Id: file_main.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:53  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.2  2005/09/05 12:29:55  mkrishna
 *  Added network mangement simulator - akshata & sriraghavendrasm
 *
 *  Revision 1.1.2.1  2005/08/29 08:59:39  mkrishna
 *  Added codec simulator - hakshata & sriraghavendrasm
 *
 ****************************************************************************/

#include <abis_codec.h>
#include <abis_network_management.h>
#include <abis_traffic_management.h>

/* TRAFFIC MANAGEMENT */
extern ITS_INT (*testTrafficMsg_RLLM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testTrafficMsg_DCMM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testTrafficMsg_CCM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testTrafficMsg_TRXM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testTrafficMsg_LCS[MAX_TRAFFIC_FUNS_SIZE])(int);

/* NETWORK MANAGEMENT */
extern ITS_INT (*testNetworkMsg_SWDM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_AIMM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_TMM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_AIM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_TESTMM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_EMM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_SMM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_MMM[MAX_TRAFFIC_FUNS_SIZE])(int);
extern ITS_INT (*testNetworkMsg_OMM[MAX_TRAFFIC_FUNS_SIZE])(int);

extern FILE *fp;
char filename[20];

int
main(int argc,char *argv[])
{
                                                                                                                             
    int choice = 0, type = 0, code, msg;

    printf("Enter the filename to be scanned\n");
    scanf("%s",filename);
    fp=fopen(filename,"r");
    printf("CHOOSE THE MESSAGE TO BE READ FROM FILE\n");
    printf("====================\n");
    printf("1. Traffic Management Message \n");
    printf("2. Network Management Message \n");
    scanf("%d", &msg);
    if ( msg < 1 || msg > 2)
    {
        printf("Invalid Choice \n");
        return 0;
    }
                                                                                                                             
    if (msg == 1)
    {
        printf("CHOOSE THE TYPE OF THE MESSAGE\n");
        printf("==============================\n");
        printf("1. Radio Link Layer Management \n");
	printf("2. Dedicated Channel Management \n");
        printf("3. Common Channel Management \n");
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
            if (strcmp(filename,"RLLM.txt")!=0)
            {
                printf("Enter the corrrect filename for radio link layer management\n");
                exit(1);
            }
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
	    if (choice < 1 || choice > 12)

            {
                printf("Invalid Choice \n");
                return 0;
            }
	    (testTrafficMsg_RLLM[choice])(choice);
            break;
            case 2:
            if (strcmp(filename,"DCMM.txt")!=0)
            {
                printf("Enter the corrrect filename for dedicated channel management\n");
                exit(1);
            }
                           
            printf("--------- DCM ----------\n");
            printf("1 : Channel Activation \n");
            printf("2 : Channel Activation Acknowledge \n");
            printf("3 : Channel Activation Negative Acknowledge \n");
            printf("4 : Connection Failure Indication \n");
            printf("5 : Deactive SACCH \n");
            printf("6 : Encryption Command \n");
            printf("7 : Handover Detection \n");
            printf("8 : Measurement Result \n");
            printf("9 : Mode Modify \n");
            printf("10 : Mode Modify Acknowledge \n");
            printf("11 : Mode Modify Negative Acknowledge \n");
            printf("12 : Physical Context Request \n");
            printf("13 : Physical Context Confirm \n");
            printf("14 : RF Channel Release \n");
            printf("15 : MS Power Control \n");
            printf("16 : BS Power Control \n");
            printf("17 : Preprocess Configure \n");
            printf("18 : Preprocess Measurement Reesult \n");
            printf("19 : RF Channel Release Acknowledge \n");
            printf("20 : SACCH Info Modify \n");
            printf("21 : Talker Detection \n");
            printf("22 : Listener Detection \n");
            printf("23 : Remote Codec Configured Report \n");
            printf("24 : Round Trip Delay Report \n");
            printf("25 : Pre-Handover Notification \n");
            printf("26 : Multirate Codec Modification Request \n");
            printf("27 : Multirate Codec Modification Acknolewdge \n");
            printf("28 : Multirate Codec Modification Negative Acknolewdge \n");
            printf("29 : Multirate Codec Modification Performed \n");
            printf("30 : TFO Report \n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            
	    (testTrafficMsg_DCMM[choice])(choice);
	    break;
            case 3:
            if (strcmp(filename,"CCM.txt")!=0)
            {
                printf("Enter the corrrect filename for CCM management\n");
                exit(1);
            }
            printf("-------------- CCM --------------\n");
            printf("1  : BCCH Information \n");
            printf("2  : CCCH Load Indication \n");
            printf("3  : Channel Required \n");
            printf("4  : Delete Indication \n");
            printf("5  : Paging Command \n");
            printf("6  : Immediate Assign Command \n");
            printf("7  : SMS Broadcast Request \n");
            printf("8  : SMS Broadcast Command \n");
            printf("9  : CBCH Load Indication \n");
            printf("10 : Notification Command \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 10)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testTrafficMsg_CCM[choice])(choice);
            break;

            case 4:
            if (strcmp(filename,"TRXM_LCS.txt")!=0)
            {
                printf("Enter the corrrect filename for TRXM_LCS management\n");
                exit(1);
            }
            printf("------------ TRXM -------------\n");
            printf("1 : RF Resource Indication \n");
            printf("2 : SACCH Filling \n");
            printf("3 : Overload \n");
            printf("4 : Error Report \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 4)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testTrafficMsg_TRXM[choice])(choice);
            break;
            case 5:
            printf("------------ LCS ---------------\n");
            printf("1 : Location Information \n\n");
            printf("Enter message number..\n");
            scanf("%d",&choice);
            if (choice!=1)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testTrafficMsg_LCS[choice])(choice);
            break;
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
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for SWDM management\n");
                exit(1);
            }
             
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
            (testNetworkMsg_SWDM[choice])(choice);
            break;
         case 2:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for AIMM management\n");
                exit(1);
            }
            printf("--------- AIM ----------\n");
            printf("1 : Establish TEI \n");
            printf("2 : Establish TEI Ack\n");
            printf("3 : Establish TEI Nack\n");
            printf("4 : Connect Terrestrial Signalling \n");
            printf("5 : Connect Terrestrial Signalling Ack\n");
            printf("6 : Connect Terrestrial Signalling Nack\n");
            printf("7 : Disconnect Terrestrial Signalling \n");
            printf("8 : Disconnect Terrestrial Signalling Ack\n");
            printf("9 : Disconnect Terrestrial Signalling Nack\n");
            printf("10 : Connect Terrestrial Traffic \n");
            printf("11 : Connect Terrestrial Traffic Ack \n");
            printf("12 : Connect Terrestrial Traffic Nack \n");
            printf("13 : Disconnect Terrestrial Traffic \n");
            printf("14 : Disconnect Terrestrial Traffic Ack\n");
            printf("15 : Disconnect Terrestrial Traffic Nack\n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 15)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_AIMM[choice])(choice);
            break;
            case 3:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for TMM management\n");
                exit(1);
            }
            printf("--------- TRMM ----------\n");
            printf("1 : Connect Multi-Drop Link \n");
            printf("2 : Connect Multi-Drop Link Ack\n");
            printf("3 : Connect Multi-Drop Link Nack\n");
            printf("4 : DisconnectMulti-Drop Link \n");
            printf("5 : DisconnectMulti-Drop Link Ack \n");
            printf("6 : DisconnectMulti-Drop Link Nack \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 6)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_TMM[choice])(choice);
            break;
            case 4:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for AIM management\n");
                exit(1);
            }
            printf("--------- AIM ----------\n");
            printf("1 : Set BTS Attributes \n");
            printf("2 : Set BTS Attributes Ack \n");
            printf("3 : Set BTS Attributes Nack \n");
            printf("4 : Set Radio Carrier Attributes \n");
            printf("5 : Set Radio Carrier Attributes Ack \n");
            printf("6 : Set Radio Carrier Attributes Nack \n");
            printf("7 : Set Channel Attributes \n");
            printf("8 : Set Channel Attributes Ack \n");
            printf("9 : Set Channel Attributes Nack \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 9)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_AIM[choice])(choice);
            break;
        case 5:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for TESTMM management\n");
                exit(1);
            }
            printf("--------- TMM ----------\n");
            printf("1 : Perform Test \n");
            printf("2 : Perform Test Ack \n");
            printf("3 : Perform Test Nack \n");
            printf("4 : Test Report \n");
            printf("5 : Send Test Report \n");
            printf("6 : Send Test Report Ack \n");
            printf("7 : Send Test Report Nack \n");
            printf("8 : Stop Test \n");
            printf("9 : Stop Test Ack \n");
            printf("10 : Stop Test Nack \n");
            printf("Enter message number..\n\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 10)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_TESTMM[choice])(choice);
            break;
          case 6:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for SMM management\n");
                exit(1);
            }
            printf("--------- SMM ----------\n");
            printf("1   : State Changed Event Report \n");
            printf("2   : Failure Event Report \n");
            printf("3   : Stop Sending Event Reports \n");
            printf("4   : Stop Sending Event Reports Ack \n");
            printf("5   : Stop Sending Event Reports Nack \n");
            printf("6   : Restart Sending Event Reports \n");
            printf("7   : Restart Sending Event Reports Ack \n");
            printf("8   : Restart Sending Event Reports Nack \n");
            printf("9   : Change Administrative State \n");
            printf("10  : Change Administrative State Ack \n");
            printf("11  : Change Administrative State Nack \n");
            printf("12  : Change Administrative State Request \n");
            printf("13  : Change Administrative State Request Ack \n");
            printf("14  : Change Administrative State Request Nack \n");
            printf("15  : Report Outstanding Alarms \n");
            printf("16  : Report Outstanding Alarms Ack \n");
            printf("17  : Report Outstanding Alarms Nack \n\n");  
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 17)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_SMM[choice])(choice);
            break;
            case 7:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for EMM management\n");
                exit(1);
            }
            printf("--------- EMM ----------\n");
            printf("1  : Changeover \n");
            printf("2  : Changeover Ack \n");
            printf("3  : Changeover Nack \n");
            printf("4  : Opstart \n");
            printf("5  : Opstart Ack \n");
            printf("6  : Opstart Nack \n");
            printf("7  : Reinitialise \n");
            printf("8  : Reinitialise Ack \n");
            printf("9  : Reinitialise Nack \n");
            printf("10 : Set Site Outputs \n");
            printf("11 : Set Site Outputs Ack \n");
            printf("12 : Set Site Outputs Nack \n");
            printf("13 : Change HW Configuration \n");
            printf("14 : Change HW Configuration Ack \n");
            printf("15 : Change HW Configuration Nack \n\n"); 
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice > 15)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_EMM[choice])(choice);
            break;
         case 8:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for MMM management\n");
                exit(1);
            }
            printf("--------- MMM ----------\n");
            printf("1 : Measurement Result Request \n");
            printf("2 : Measurement Result Response \n");
            printf("3 : Start Measurement \n");
            printf("4 : Stop Measurement \n");
            printf("Enter message number..\n\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 4)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_MMM[choice])(choice);
             break;
          case 9:
            if (strcmp(filename,"NETWORK_MSG.txt")!=0)
            {
                printf("Enter the corrrect filename for OMM management\n");
                exit(1);
            }
            printf("--------- OMM ----------\n");
            printf("1  : Get Attributes \n");
            printf("2  : Get Attributes Nack \n");
            printf("3  : Get Attributes Response \n");
            printf("4  : Set Alarm Threshold \n");
            printf("5  : Set Alarm Threshold Ack \n");
            printf("6  : Set Alarm Threshold Nack \n\n");
            printf("Enter message number..\n");
            scanf("%d", &choice);
            if (choice < 1 || choice > 6)
            {
                printf("Invalid Choice \n");
                return 0;
            }
            (testNetworkMsg_OMM[choice])(choice);
            break;
        default:
            printf("Invalid Choice \n");
            break;
        }
                                                                                                                             
    }
        return ITS_SUCCESS;
}
