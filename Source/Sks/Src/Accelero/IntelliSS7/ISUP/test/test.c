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
 *  ID: $Id: test.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:07  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:02  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1  2003/07/17 07:47:14  sjaddu
 * LOG: testnig commit
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:37  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:36  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:05  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:36  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.12  2000/05/22 21:07:39  labuser
 * LOG: Modified main menu
 * LOG:
 * LOG: Revision 2.11  2000/05/17 14:31:23  cbascon
 * LOG: New and improved MainMenu
 * LOG:
 * LOG: Revision 2.10  2000/05/17 14:08:56  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.9  2000/05/16 15:11:35  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.8  2000/02/08 14:16:54  labuser
 * LOG: OGC Selected is now sent automatically in ANSI.
 * LOG:
 * LOG: Revision 2.7  2000/01/27 14:56:47  labuser
 * LOG: cbascon: Clean up code.
 * LOG:
 * LOG: Revision 2.6  2000/01/16 15:58:51  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.5  2000/01/13 22:54:06  labuser
 * LOG: cbascon: CIC is now calculated from user entries - trunk grp and
 * LOG:          circuit no.
 * LOG:
 * LOG: Revision 2.4  2000/01/11 18:11:21  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.3  1999/12/30 15:54:12  labuser
 * LOG: Clean up...
 * LOG:
 * LOG: Revision 2.2  1999/12/10 22:50:07  cbascon
 * LOG: Tested ANSI ISUP messages ACM, ANM, CPG, IAM, BLO, UBL, UCIC, REL, RLC,
 * LOG: RSC
 * LOG:
 * LOG: Revision 2.1  1999/12/07 00:40:04  cbascon
 * LOG: Encoded and sent the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO
 * LOG:
 * LOG: Received and decoded the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO, UCIC
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:38  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1999/11/24 19:21:17  cbascon
 * LOG: Can now select CON, CPG, RSC, SAM on main menu.
 * LOG:
 * LOG: Revision 1.6  1999/11/14 23:33:44  cbascon
 * LOG: No need to call ISUP_Decode in WaitForEvent(), ISUP_Receive*** functions
 * LOG: will perform the decode into an IE array.
 * LOG:
 * LOG: Revision 1.5  1999/11/14 23:18:31  cbascon
 * LOG: *** empty log message ***
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>

#include <its.h>
#include <itu/isup.h>
#include <ansi/isup.h>
#include <isup_vendor_ext.h>
#include "printISUPMsg.h"
#include "test.h"

/* EBS headers */
#include <types.h>
#include <isupparams.h>
#include <isupcall.h>
#include <isupcircuit.h>
#include <isupcause.h>
#include <isupuser.h>
#include <isupCallCont.h>



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will prompt the user for an integer input 
 *      
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      CIC supplied by user.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_USHORT
GetCIC()
{
    int trunkGroup = 0;
    int circuitNumber = 0;
    int cic = 0;

    printf("\n");
    printf("Enter trunk group: ");
    scanf("%d", &trunkGroup);
    printf("Enter circuit no: ");
    scanf("%d", &circuitNumber);

#ifdef ANSI
    cic = trunkGroup * 24 + circuitNumber;
#endif
#ifdef CCITT
    cic = trunkGroup * 32 + circuitNumber;
#endif    

    printf("\n");
    printf("Using CIC: %d \n", cic);

    return (ITS_USHORT)cic;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will prompt the user for an integer input 
 *      
 *  Input Parameters:
 *      min - minimum valid input
 *      max - maximum valid input
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      Integer entered by the user which is between min and max.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
GetSelection(int min, int max)
{
    int selection = -999;
    
    while ((selection < min) || (selection > max))
    {
        fflush(stdin);
        scanf("%d", &selection);
    }
    return selection;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the main menu of the ISUP test program.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
DisplayMainMenu()
{
    printf("\n");
#ifdef ANSI
    printf("ANSI ISUP \n");
#elif defined(CCITT)
    printf("CCITT ISUP \n");
#endif
    printf("----------------------------------------------------- \n");
    printf("[%3d] ACM  AddressComplete     [%3d] GRS GroupReset \n",
           ISUP_MSG_ACM, ISUP_MSG_GRS);
    printf("[%3d] ANM  Answer              [%3d] IAM InitialAddress \n",
           ISUP_MSG_ANM, ISUP_MSG_IAM);
    printf("[%3d] BLO  Block               [%3d] INF InformationReq \n",
           ISUP_MSG_BLO, ISUP_MSG_INF);
    printf("[%3d] CCR  ContinuityCheck     [%3d] INR InformationRes \n",
           ISUP_MSG_CCR, ISUP_MSG_INR);
    printf("[%3d] CFN  Confusion           [%3d] PAM PassAlong \n",
           ISUP_MSG_CFN, ISUP_MSG_PAM);
    printf("[%3d] CGB  CktGroupBlock       [%3d] REL Release \n",
           ISUP_MSG_CGB, ISUP_MSG_REL);
    printf("[%3d] CGU  CktGroupUnblock     [%3d] RES Resume \n",
           ISUP_MSG_CGU, ISUP_MSG_RES);
    printf("[%3d] CGUA CktGroupUnblockAck  [%3d] RLC ReleaseComplete \n",
           ISUP_MSG_CGUA, ISUP_MSG_RLC);
    printf("[%3d] COT  Continuity          [%3d] RSC Reset \n",
           ISUP_MSG_COT, ISUP_MSG_RSC);
    printf("[%3d] CPG  CallProgress        [%3d] SUS Suspend \n",
           ISUP_MSG_CPG, ISUP_MSG_SUS);
    printf("[%3d] CQM  CktQuery            [%3d] UBL Unblock \n",
           ISUP_MSG_CQM, ISUP_MSG_UBL);
    printf("[%3d] FOT  ForwardTransfer \n", ISUP_MSG_FOT);
    printf("\n");

#ifdef ANSI
    printf("[%3d] CRM  CktReservation      [%3d] CVT CktValidationTest \n",
           ISUP_MSG_CRM, ISUP_MSG_CVT);
    printf("[%3d] CVR  CktValidationResp   [%3d] EXM Exit \n",
           ISUP_MSG_CVR, ISUP_MSG_EXM);
#endif

#ifdef CCITT
    printf("[%3d] CON  Connect             [%3d] NRM NetwResourceManagement\n",
           ISUP_MSG_CON, ISUP_MSG_NRM);
    printf("[%3d] IDR  IdentificationReq   [%3d] SAM SubsequentAddress\n",
           ISUP_MSG_IDR, ISUP_MSG_SAM);
    printf("[%3d] IRS  IdentificationResp \n", ISUP_MSG_IRS);
#endif

    printf("\n");
    printf("[%3d] Quit \n", TEST_QUIT);
    printf("\n->> ");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will wait for an ITS Event.
 *
 *  Input Parameters:
 *      handle - the transport associated with the ITS_Event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      recvHeader - storage for header of ISUP message to be received
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if an event is received successfully.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
WaitForEvent(ITS_HANDLE handle, ITS_HDR *recvHeader)
{
    int result = 0;
    int invRespType = 0;
    int begRespType = 0;
    int noResponse = 0;
    ITS_HDR header;
    ITS_EVENT event;

    /* Initializations */
    memset((char *)&header, 0, sizeof(ITS_HDR));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    /* Keep getting an Event */
    while (1)
    {
        /*
         * Get the next event if there is an event otherwise block until an
         * event is received
         */
        result = ITS_GetNextEvent(handle, &event);
        if (result == ITS_SUCCESS)
        {
            /* Check if we received a ISUP Event */
            switch ( event.src )
            {
            case ITS_ISUP_SRC:
                printf("ISUPTEST: Received an ISUP event. \n");
                result = ReceiveISUPMsg(handle, &event, &header);
                return result;
                break;
            case ITS_MTP3_SRC:
                printf("ISUPTEST: Received a MTP3 event. \n");
                break;
            case ITS_SCCP_SRC:
                printf("ISUPTEST: Received a SCCP event. \n");
                break;
            case ITS_TCAP_SRC:
                printf("ISUPTEST: Received a TCAP event. \n");
                break;
            default:
                printf("ISUPTEST: Received unknown event, src = 0x%02x \n",
                       event.src);
            }
        }
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will receive and decode an ISUP message.
 *
 *  Input Parameters:
 *      handle - the transport associated with the event
 *      event - pointer to an IntelliSS7 event
 *      hdr - header associated with the event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned on decode success.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReceiveISUPMsg(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr)
{
    int          i = 0;
    int          choice = 0;
    int          recvResult = ITS_SUCCESS;
    int          sendResult = ITS_SUCCESS;
    int          ieCount = 0;
    int          trunkGrp = 0;
    int          circuitNum = 0;
    int          circuitsPerTrunkGrp = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ITS_OCTET    timerID = 0x00;
    ITS_OCTET    nature = 0x00; 
    static int   sent_CGU = 0;

    memset((char *)&ies, 0, ITS_MAX_ISUP_IES * sizeof(ITS_ISUP_IE));

    printf("\n------------------------------------------------------\n");
    printf("ISUPTEST: Received ");

    /*
     * Determine which ISUP message is packaged inside event structure
     * and receive the message.
     */
    switch ( event->data[0] )
    {
    case ISUP_MSG_EBS_INVALID_MSG:
        printf("EBS INVALID MSG");
        EXT_getCIC(handle, event, hdr);
        break;
    case ISUP_MSG_EBS_TIMER_EVT:
        printf("Timer event. \n");
        EXT_getTimerEvent(handle, event, hdr, &timerID, &nature);
        printf("ISUPTEST: timerID = 0x%02x \n", timerID);
        printf("ISUPTEST: nature = 0x%02x", nature);
        break;
    case ISUP_MSG_ACM:
        recvResult = ISUP_ReceiveACMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("ACM");
#if 0
printf( "\n** test.c:  After ISUP_ReceiveACMIndication() - Msg Len: %d\n", event->len );
printf( "event->len: %d\n", event->len );
printf( "event->src: 0x%02x\n", event->src );
for ( i=0; i<=event->len; i++ )
{
   printf( "event->data[%d]: 0x%02x\n", i, event->data[i] );
}
printf( "*************************\n" );
#endif

        break;
    case ISUP_MSG_ANM:
        recvResult = ISUP_ReceiveANMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("ANM");
        break;
    case ISUP_MSG_BLO:
        recvResult = ISUP_ReceiveBLOIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("BLO");
        break;
    case ISUP_MSG_BLA:
        recvResult = ISUP_ReceiveBLAIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("BLA");
        break;
    case ISUP_MSG_CCR:
        recvResult = ISUP_ReceiveCCRIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CCR");
        break;
    case ISUP_MSG_CFN:
        recvResult = ISUP_ReceiveCFNIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CFN");
        break;
    case ISUP_MSG_CGB:
        recvResult = ISUP_ReceiveCGBIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CGB");
        break;
    case ISUP_MSG_CGBA:
        recvResult = ISUP_ReceiveCGBAIndication(handle, event, hdr, ies,
                                                &ieCount);
        printf("CGBA");
        break;
    case ISUP_MSG_CGU:
        recvResult = ISUP_ReceiveCGUIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CGU");
        if (recvResult == ITS_SUCCESS)
        {
            PrintISUPMsg(ies, ieCount);
            sendResult = TestSendCGUARequest( handle, hdr );
            if (sendResult == ITS_SUCCESS)
            {
                printf("ISUPTEST: CGUA send success. CIC %d \n",
                       hdr->context.CIC);
            }
            else
            {
                printf("ISUPTEST: CGUA send failed. CIC %d, result %d \n",
                       hdr->context.CIC, sendResult);
            }
        }
        break;
    case ISUP_MSG_CGUA:
        recvResult = ISUP_ReceiveCGUAIndication(handle, event, hdr, ies,
                                                &ieCount);
        printf("CGUA");
        break;
    case ISUP_MSG_COT:
        recvResult = ISUP_ReceiveCOTIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("COT");
        break;
    case ISUP_MSG_CPG:
        recvResult = ISUP_ReceiveCPGIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CPG, ieCount = %d", ieCount);
        break;
    case ISUP_MSG_CQM:
        recvResult = ISUP_ReceiveCQMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CQM");
        break;
    case ISUP_MSG_CQR:
        recvResult = ISUP_ReceiveCQRIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CQR");
        break;

#ifdef ANSI
    case ISUP_MSG_CRA:
        recvResult = ISUP_ReceiveCRAIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CRA");
        break;
    case ISUP_MSG_CRM:
        recvResult = ISUP_ReceiveCRMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CRM");
        break;
    case ISUP_MSG_CVR:
        recvResult = ISUP_ReceiveCVRIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CVR");
        break;
    case ISUP_MSG_CVT:
        recvResult = ISUP_ReceiveCVTIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CVT");
        break;
    case ISUP_MSG_EXM:
        recvResult = ISUP_ReceiveEXMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("EXM");
        break;
#endif

    case ISUP_MSG_FOT:
        recvResult = ISUP_ReceiveFOTIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("FOT");
        break;
    case ISUP_MSG_GRA:
        recvResult = ISUP_ReceiveGRAIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("GRA");
        break;
    case ISUP_MSG_GRS:
        recvResult = ISUP_ReceiveGRSIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("GRS");
        break;
    case ISUP_MSG_IAM:
        recvResult = ISUP_ReceiveIAMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("IAM");
#if 0
        if (recvResult == ITS_SUCCESS)
        {
            PrintISUPMsg(ies, ieCount);

            sendResult = TestSendACMRequest( handle, hdr );
            if (sendResult == ITS_SUCCESS)
            {
                printf("ISUPTEST: ACM send success. CIC %d \n",
                       hdr->context.CIC);

                sendResult = TestSendANMRequest( handle, hdr );
                if (sendResult == ITS_SUCCESS)
                {
                    printf("ISUPTEST: ANM send success. CIC %d \n",
                           hdr->context.CIC);
                }
                else
                {
                    printf("ISUPTEST: ANM send failed. CIC %d, result %d \n",
                           hdr->context.CIC, sendResult);
                }
            }
            else
            {
                printf("ISUPTEST: ACM send failed. CIC %d, result %d \n",
                       hdr->context.CIC, sendResult);
            }
        }
#endif
        break;
    case ISUP_MSG_INF:
        recvResult = ISUP_ReceiveINFIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("INF");
        break;
    case ISUP_MSG_INR:
        recvResult = ISUP_ReceiveINRIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("INR");
        break;
    case ISUP_MSG_LPA:
        recvResult = ISUP_ReceiveLPAIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("LPA");
        break;
    case ISUP_MSG_PAM:
        recvResult = ISUP_ReceivePAMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("PAM");
        break;
    case ISUP_MSG_REL:
        recvResult = ISUP_ReceiveRELIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("REL");
        if (recvResult == ITS_SUCCESS)
        {
            PrintISUPMsg(ies, ieCount);

            sendResult = TestSendRLCRequest( handle, hdr );
            if (sendResult == ITS_SUCCESS)
            {
                printf("ISUPTEST: RLC send success. CIC %d \n",
                       hdr->context.CIC);
            }
            else
            {
                printf("ISUPTEST: RLC send failed. CIC %d, result %d \n",
                       hdr->context.CIC, sendResult);
            }
        }
        break;
    case ISUP_MSG_RES:
        recvResult = ISUP_ReceiveRESIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("RES");
        break;
    case ISUP_MSG_RLC:
        recvResult = ISUP_ReceiveRLCIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("RLC");
        break;
    case ISUP_MSG_RSC:
        recvResult = ISUP_ReceiveRSCIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("RSC");
        if (recvResult == ITS_SUCCESS)
        {
            PrintISUPMsg(ies, ieCount);

            sendResult = TestSendResetRLCRequest( handle, hdr );
            if (sendResult == ITS_SUCCESS)
            {
                printf("ISUPTEST: Reset RLC send success. CIC %d \n",
                       hdr->context.CIC);
            }
            else
            {
                printf("ISUPTEST: Reset RLC send failed. CIC %d, result %d \n",
                       hdr->context.CIC, sendResult);
            }
        }
        break;
    case ISUP_MSG_SUS:
        recvResult = ISUP_ReceiveSUSIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("SUS");
        break;
    case ISUP_MSG_UBA:
        recvResult = ISUP_ReceiveUBAIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("UBA");
        break;
    case ISUP_MSG_UBL:
        printf("UBL");
        recvResult = ISUP_ReceiveUBLIndication(handle, event, hdr, ies,
                                               &ieCount);
        if (recvResult == ITS_SUCCESS)
        {
            PrintISUPMsg(ies, ieCount);
            sendResult = TestSendUBARequest( handle, hdr );
            if (sendResult == ITS_SUCCESS)
            {
                printf("ISUPTEST: UBA send success. CIC %d \n",
                       hdr->context.CIC);
            }
            else
            {
                printf("ISUPTEST: UBA send failed. CIC %d, result %d \n",
                       hdr->context.CIC, sendResult);
            }
        }
        break;
    case ISUP_MSG_UCIC:
        recvResult = ISUP_ReceiveUCICIndication(handle, event, hdr, ies,
                                                &ieCount);
        printf("UCIC");
        break;

#ifdef CCITT
    case ISUP_MSG_CON:
        recvResult = ISUP_ReceiveCONIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("CON");
        break;
    case ISUP_MSG_FAA:
        recvResult = ISUP_ReceiveFAAIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("FAA");
        break;

#ifdef CCITT
/* TODO: Add component as argument
    case ISUP_MSG_FAC:
        recvResult = ISUP_ReceiveFACIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("FAC");
        break;
*/
#endif
    case ISUP_MSG_FAR:
        recvResult = ISUP_ReceiveFARIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("FAR");
        break;
    case ISUP_MSG_FRJ:
        recvResult = ISUP_ReceiveFRJIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("FRJ");
        break;
    case ISUP_MSG_IDR:
        recvResult = ISUP_ReceiveIDRIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("IDR");
        break;
    case ISUP_MSG_IRS:
        recvResult = ISUP_ReceiveIRSIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("IRS");
        break;
    case ISUP_MSG_NRM:
        recvResult = ISUP_ReceiveNRMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("NRM");
        break;
    case ISUP_MSG_OLM:
        recvResult = ISUP_ReceiveOLMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("OLM");
        break;
    case ISUP_MSG_SAM:
        recvResult = ISUP_ReceiveSAMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("SAM");
        break;
    case ISUP_MSG_SGM:
        recvResult = ISUP_ReceiveSGMIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("SGM");
        break;
    case ISUP_MSG_UPA:
        recvResult = ISUP_ReceiveUPAIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("UPA");
        break;
    case ISUP_MSG_UPT:
        recvResult = ISUP_ReceiveUPTIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("UPT");
        break;
    case ISUP_MSG_USR:
        recvResult = ISUP_ReceiveUSRIndication(handle, event, hdr, ies,
                                               &ieCount);
        printf("USR");
        break;
#endif

    default:
        printf("Unrecognized msg: 0x%02x \n", event->data[0]);
    }
    printf("\n");

    if (recvResult == ITS_SUCCESS)
    {

#ifdef ANSI
        circuitsPerTrunkGrp = 24;
#endif
#ifdef CCITT
        circuitsPerTrunkGrp = 32;
#endif
        trunkGrp = hdr->context.CIC / circuitsPerTrunkGrp;
        circuitNum = hdr->context.CIC % circuitsPerTrunkGrp;

        printf(" (TrnkGrp: %d, Ckt: %d) \n", trunkGrp, circuitNum);

        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("ISUPTEST: Fail to receive ISUP message \n");
        printf("ISUPTEST: Error is %s \n", ITS_GetErrorText(recvResult));
    }

    return recvResult;

}

