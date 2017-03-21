/****************************************************************************
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
 *  ID: $Id: BSSAPPrint.cpp,v 1.1.1.1 2007-10-08 11:11:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:43  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:58  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.2.3  2005/11/30 07:30:59  adutta
 * LOG: Added Authentication Failure message
 * LOG:
 * LOG: Revision 9.1.2.2  2005/11/18 05:02:38  adutta
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 9.1.2.1  2005/09/29 07:13:10  adutta
 * LOG: Implemented paging response
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:09  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:13  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/10 16:55:53  ngoel
 * LOG: DTAP merge
 * LOG:
 * LOG: Revision 1.1.2.20  2002/06/10 16:20:47  ngoel
 * LOG: after MM fixes
 * LOG:
 * LOG: Revision 1.1.2.19  2002/06/06 20:44:30  ngoel
 * LOG: after MM changes
 * LOG:
 * LOG: Revision 1.1.2.18  2002/06/05 20:56:53  ngoel
 * LOG: add ie
 * LOG:
 * LOG: Revision 1.1.2.17  2002/05/31 21:15:31  ngoel
 * LOG: amerge MM messages
 * LOG:
 * LOG: Revision 1.1.2.16  2002/05/31 21:08:54  ngoel
 * LOG: merge MM messages
 * LOG:
 * LOG: Revision 1.1.2.15  2002/05/31 17:57:07  ngoel
 * LOG: add messages
 * LOG:
 * LOG: Revision 1.1.2.14  2002/05/30 14:35:19  ngoel
 * LOG: add status message
 * LOG:
 * LOG: Revision 1.1.2.13  2002/05/29 20:46:37  ngoel
 * LOG: dd dtmf messages
 * LOG:
 * LOG: Revision 1.1.2.12  2002/05/29 20:10:30  ngoel
 * LOG: test start dtmf
 * LOG:
 * LOG: Revision 1.1.2.11  2002/05/29 16:31:23  ngoel
 * LOG: test retrieve messages
 * LOG:
 * LOG: Revision 1.1.2.10  2002/05/24 15:58:31  ngoel
 * LOG: remove duplocate
 * LOG:
 * LOG: Revision 1.1.2.9  2002/05/24 13:40:59  ngoel
 * LOG: amm specific changes
 * LOG:
 * LOG: Revision 1.1.2.8  2002/05/22 17:04:14  ngoel
 * LOG: merge print functions with mm
 * LOG:
 * LOG: Revision 1.1.2.7  2002/05/13 21:01:23  ngoel
 * LOG: add support for multiple ies
 * LOG:
 * LOG: Revision 1.1.2.6  2002/05/10 18:29:07  ngoel
 * LOG: add code
 * LOG:
 * LOG: Revision 1.1.2.5  2002/05/09 16:10:35  ngoel
 * LOG: bug fixes
 * LOG:
 * LOG: Revision 1.1.2.4  2002/05/09 14:40:51  ngoel
 * LOG: add print functions
 * LOG:
 * LOG: Revision 1.1.2.3  2002/05/09 14:12:24  ngoel
 * LOG: add print functions
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/08 22:56:36  ngoel
 * LOG: dd function
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 17:19:26  ngoel
 * LOG: start adding cc messages
 * LOG:
 * LOG: Revision 6.1.4.2  2002/04/26 20:44:36  hxing
 * LOG: Build on Solaris.
 * LOG:
 * LOG: Revision 6.1.4.1  2002/04/24 22:20:35  hxing
 * LOG: Back port to PR5.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.4  2001/11/26 15:28:10  dzhang
 * LOG: Modify PrintBSSMAPMsgHandoverRequired()
 * LOG:
 * LOG: Revision 1.3  2001/11/20 14:52:34  dzhang
 * LOG: Minor change in format
 * LOG:
 * LOG: Revision 1.2  2001/11/12 14:44:55  dzhang
 * LOG: update to latest spec version8.9.0
 * LOG:
 * LOG: Revision 1.1  2001/10/02 21:54:26  dzhang
 * LOG: Initially check in after unit test
 * LOG:
 *
 ****************************************************************************/
#ifndef HPUX
#include <iostream>
#include <iomanip>
#else
#include <iostream/iostream.h>
#include <iostream/iomanip.h>
#endif

#include <BSSAPPrint.h>
#include <its_exception.h>
//#include <its_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*
 * implementation of PrintBSSAPMessage
 */
void 
PrintBSSAPMessage(ITS_OCTET* buf, int len)
{
    ITS_ASSERT(buf != NULL);

    ITS_ASSERT(len >= 0 && len <= BSSAP_MAX_IE_SIZE);

    BSSAP_Message* iMsg = NULL;

    ITS_OCTET data[BSSAP_MAX_IE_SIZE];

    memset(data, 0, BSSAP_MAX_IE_SIZE);

    memcpy(&data[0], buf, len);

    ITS_OCTET msgDisc = data[0];

    int res = BSSAP_Message::Decode(&data[0], len, &iMsg);

    if (res != ITS_SUCCESS)
    {
        cout << "Error decoding BSSMAP MESSAGE." << endl << endl;
        return;
    }

    ITS_ASSERT(iMsg != NULL);

    ITS_OCTET msgType = iMsg->GetMsgType();    

    if (msgDisc == BSSAP_MD_BSSMAP)
    {
        switch (msgType)
        {             
            case BSSAP_MSG_ASSIGN_COMPLETE:
                PrintBSSMAPMsgAssignComplete(iMsg);
                break;
    
            case BSSAP_MSG_ASSIGN_FAILURE:
                PrintBSSMAPMsgAssignFailure(iMsg);
                break;

            case BSSAP_MSG_ASSIGN_REQUEST:
                PrintBSSMAPMsgAssignReq(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
                PrintBSSMAPMsgHandoverCandidateEnq(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
                PrintBSSMAPMsgHandoverCandidateRsp(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_COMMAND:
                PrintBSSMAPMsgHandoverCmd(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_COMPLETE:
                PrintBSSMAPMsgHandoverComplete(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_DETECT:
                PrintBSSMAPMsgHandoverDetect(iMsg);
                break;

            case BSSAP_MSG_HANDOVER_FAILURE:
                PrintBSSMAPMsgHandoverFailure(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_PERFORMED:
                PrintBSSMAPMsgHandoverPerformed(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_REQUEST:
                PrintBSSMAPMsgHandoverReq(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_REQUEST_ACK:
                PrintBSSMAPMsgHandoverReqAck(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_REQUIRED:
                PrintBSSMAPMsgHandoverRequired(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
                PrintBSSMAPMsgHandoverRequiredRej(iMsg);
                break;
    
            case BSSAP_MSG_HANDOVER_SUCCEEDED:
                PrintBSSMAPMsgHandoverSucceeded(iMsg);
                break;

            case BSSAP_MSG_CLEAR_COMMAND:
                PrintBSSMAPMsgClrCmd(iMsg);
                break;

            case BSSAP_MSG_CLEAR_COMPLETE:
                PrintBSSMAPMsgClrComplete(iMsg);
                break;
    
            case BSSAP_MSG_CLEAR_REQUEST:
                PrintBSSMAPMsgClrReq(iMsg);
                break;
    
            case BSSAP_MSG_SAPI_N_REJECT:
                PrintBSSMAPMsgSAPInRej(iMsg);
                break;
    
            case BSSAP_MSG_CONFUSION:
                PrintBSSMAPMsgConfusion(iMsg);
                break;
    
            case BSSAP_MSG_SUSPEND:
                PrintBSSMAPMsgSuspend(iMsg);
                break;
    
            case BSSAP_MSG_RESUME:
                PrintBSSMAPMsgResume(iMsg);
                break;
            case BSSAP_MSG_RESET:
                PrintBSSMAPMsgReset(iMsg);
                break;
    
            case BSSAP_MSG_RESET_ACK:
                PrintBSSMAPMsgResetAck(iMsg);
                break;
    
            case BSSAP_MSG_RESET_CIRCUIT:
                PrintBSSMAPMsgResetCircuit(iMsg);
                break;
    
            case BSSAP_MSG_RESET_CIRCUIT_ACK:
                PrintBSSMAPMsgResetCircuitAck(iMsg);
                break;

            case BSSAP_MSG_OVERLOAD:
                PrintBSSMAPMsgOverload(iMsg);
                break;
    
            case BSSAP_MSG_MSC_INVOKE_TRACE:
                PrintBSSMAPMsgMSCInvokeTrace(iMsg);
                break;
    
            case BSSAP_MSG_BSS_INVOKE_TRACE:
                PrintBSSMAPMsgBSSInvokeTrace(iMsg);
                break;
    
            case BSSAP_MSG_BLOCK:
                PrintBSSMAPMsgBlock(iMsg);
                break;
    
            case BSSAP_MSG_BLOCK_ACK:
                PrintBSSMAPMsgBlockAck(iMsg);
                break;

            case BSSAP_MSG_UNBLOCK:
                PrintBSSMAPMsgUnblock(iMsg);
                break;
    
            case BSSAP_MSG_UNBLOCK_ACK:
                PrintBSSMAPMsgUnblockAck(iMsg);
                break;
    
            case BSSAP_MSG_CKT_GROUP_BLOCK:
                PrintBSSMAPMsgCktGroupBlock(iMsg);
                break;
    
            case BSSAP_MSG_CKT_GRP_BLK_ACK:
                PrintBSSMAPMsgCktGroupBlockAck(iMsg);
                break;
    
            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                PrintBSSMAPMsgCktGroupUnblock(iMsg);
                break;
    
            case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
                PrintBSSMAPMsgCktGroupUnblockAck(iMsg);
                break;
    
            case BSSAP_MSG_UNEQUIPPED_CKT:
                PrintBSSMAPMsgUnequippedCkt(iMsg);
                break;
    
            case BSSAP_MSG_CHANGE_CKT:
                PrintBSSMAPMsgChangeCkt(iMsg);
                break;

            case BSSAP_MSG_CHANGE_CKT_ACK:
                PrintBSSMAPMsgChangeCktAck(iMsg);
                break;
    
            case BSSAP_MSG_RESOURCE_REQUEST:
                 PrintBSSMAPMsgResourceReq(iMsg);
                break;

            case BSSAP_MSG_RESOURCE_INDICATION:
                 PrintBSSMAPMsgResourceInd(iMsg);
                 break;
    
            case BSSAP_MSG_PAGING:
                 PrintBSSMAPMsgPaging(iMsg);
                 break;
    
            case BSSAP_MSG_PAGING_RESPONSE:
                 PrintBSSMAPMsgPagingResponse(iMsg);
                 break;
    
            case BSSAP_MSG_CIPHER_MODE_CMD:
                 PrintBSSMAPMsgCipherModeCmd(iMsg);
                 break;
    
            case BSSAP_MSG_CIPHER_MODE_COMPLETE:
                 PrintBSSMAPMsgCipherModeComplete(iMsg);
                 break;
    
            case BSSAP_MSG_CIPHER_MODE_REJECT:
                PrintBSSMAPMsgCipherModeRej(iMsg);
                break;
    
            case BSSAP_MSG_CLASSMARK_UPDATE:
                 PrintBSSMAPMsgClassmarkUpdate(iMsg);
                 break;
    
            case BSSAP_MSG_CLASSMARK_REQUEST:
                 PrintBSSMAPMsgClassmarkReq(iMsg);
                break;
    
            case BSSAP_MSG_COMPLETE_LAYER3_INFO:
                 PrintBSSMAPMsgCompleteLayer3Info(iMsg);
                 break;
    
            case BSSAP_MSG_LOAD_INDICATION:
                 PrintBSSMAPMsgLoadInd(iMsg);
                 break;
    
            case BSSAP_MSG_QUEUING_INDICATION:
                 PrintBSSMAPMsgQueuingInd(iMsg);
                 break;
    
            case BSSAP_MSG_VGCS_VBS_SETUP:
                 PrintBSSMAPMsgVGCSVBSSetup(iMsg);
                 break;
    
            case BSSAP_MSG_VGCS_VBS_SETUP_ACK:
                 PrintBSSMAPMsgVGCSVBSSetupAck(iMsg);
                 break;
    
            case BSSAP_MSG_VGCS_VBS_SETUP_REFUSE:
                 PrintBSSMAPMsgVGCSVBSSetupRefuse(iMsg);
                 break;
    
            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST:
                PrintBSSMAPMsgVGCSVBSAssignReq(iMsg);
                break;
    
            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT:
                 PrintBSSMAPMsgVGCSVBSAssignRsult(iMsg);
                 break;
    
            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE:
                PrintBSSMAPMsgVGCSVBSAssignFailure(iMsg);
                break;
    
            case BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION:
                PrintBSSMAPMsgVGCSVBSQueuingInd(iMsg);
                break;
            
            case BSSAP_MSG_UPLINK_REQUEST:
                PrintBSSMAPMsgUplinkReq(iMsg);
                break;
    
#if 0
            case BSSAP_MSG_UPLINK_REQUEST_ACK:
                PrintBSSMAPMsgUplinkReqAck(iMsg);
                break;
#endif

            case BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION:
                PrintBSSMAPMsgUplinkReqConfirm(iMsg);
                break;

            case BSSAP_MSG_UPLINK_RELEASE_INDICATION:
                PrintBSSMAPMsgUplinkReleaseInd(iMsg);
                break;

            case BSSAP_MSG_UPLINK_REJECT_COMMAND:
                PrintBSSMAPMsgUplinkRejCmd(iMsg);
                break;
            
            case BSSAP_MSG_UPLINK_RELEASE_COMMAND:
                PrintBSSMAPMsgUplinkReleaseCmd(iMsg);
                break;
    
            case BSSAP_MSG_UPLINK_SEIZED_COMMAND:
                PrintBSSMAPMsgUplinkSeizedCmd(iMsg);
                break;
    
            default:
                cout << "Unknown message type!!" << endl << endl;
                break;
        }
    }
    else
    {
        if (iMsg->GetProtDiscr() == PD_CALL_CONTROL_MSGS)
        {
            switch (msgType)
            {             
                case BSSAP_CC_MSG_ALERTING :
                    PrintBSSMAPMsgAlerting(iMsg);
                    break;

                case BSSAP_CC_MSG_CALL_PROCEEDING :
                    PrintBSSMAPMsgCallProceeding(iMsg);
                    break;

                case BSSAP_CC_MSG_CONNECT :
                    PrintBSSMAPMsgConnect(iMsg);
                    break;

                case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE :
                    PrintBSSMAPMsgConnectAck(iMsg);
                    break;

                case BSSAP_CC_MSG_SETUP :
                    PrintBSSMAPMsgSetup(iMsg);
                    break;
    
                 case BSSAP_CC_MSG_CALL_CONFIRMED :
                     PrintBSSMAPMsgCallConfirm(iMsg);
                     break;

                case BSSAP_CC_MSG_EMERGENCY_SETUP :
                    PrintBSSMAPMsgEmergencySetup(iMsg);
                    break;

                case BSSAP_CC_MSG_PROGRESS :
                    PrintBSSMAPMsgProgress(iMsg);
                    break;

                case BSSAP_CC_MSG_MODIFY :
                    PrintBSSMAPMsgModify(iMsg);
                    break;

                case BSSAP_CC_MSG_MODIFY_COMPLETE :
                    PrintBSSMAPMsgModifyComplete(iMsg);
                    break;
    
                 case BSSAP_CC_MSG_MODIFY_REJECT :
                    PrintBSSMAPMsgModifyReject(iMsg);
                    break;

                case BSSAP_CC_MSG_USER_INFORMATION :
                    PrintBSSMAPMsgUserInformation(iMsg);
                    break;

                case BSSAP_CC_MSG_HOLD :
                    PrintBSSMAPMsgHold(iMsg);
                    break;

                case BSSAP_CC_MSG_HOLD_ACKNOWLEDGE :
                    PrintBSSMAPMsgHoldAck(iMsg);
                    break;

                case BSSAP_CC_MSG_HOLD_REJECT :
                    PrintBSSMAPMsgHoldReject(iMsg);
                    break;
    
                 case BSSAP_CC_MSG_RETRIEVE :
                    PrintBSSMAPMsgRetrieve(iMsg);
                    break;

                case BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE :
                    PrintBSSMAPMsgRetrieveAck(iMsg);
                    break;

                case BSSAP_CC_MSG_RETRIEVE_REJECT :
                    PrintBSSMAPMsgRetrieveReject(iMsg);
                    break;

                case BSSAP_CC_MSG_DISCONNECT :
                    PrintBSSMAPMsgDisconnect(iMsg);
                    break;

                case BSSAP_CC_MSG_RELEASE :
                    PrintBSSMAPMsgRelease(iMsg);
                    break;
    
                 case BSSAP_CC_MSG_RELEASE_COMPLETE :
                    PrintBSSMAPMsgReleaseComplete(iMsg);
                    break;

                case BSSAP_CC_MSG_CONGESTION_CONTROL :
                    PrintBSSMAPMsgCongestionControl(iMsg);
                    break;

                case BSSAP_CC_MSG_NOTIFY :
                    PrintBSSMAPMsgNotify(iMsg);
                    break;

                case BSSAP_CC_MSG_STATUS :
                    PrintBSSMAPMsgStatus(iMsg);
                    break;

                case BSSAP_CC_MSG_STATUS_ENQUIRY :
                    PrintBSSMAPMsgStatusEnquiry(iMsg);
                    break;

                case BSSAP_CC_MSG_START_DTMF :
                    PrintBSSMAPMsgStartDTMF(iMsg);
                    break;

                case BSSAP_CC_MSG_START_DTMF_ACK :
                    PrintBSSMAPMsgStartDTMFAck(iMsg);
                    break;

                case BSSAP_CC_MSG_START_DTMF_REJECT :
                    PrintBSSMAPMsgStartDTMFReject(iMsg);
                    break;

                case BSSAP_CC_MSG_STOP_DTMF :
                    PrintBSSMAPMsgStopDTMF(iMsg);
                    break;

                case BSSAP_CC_MSG_STOP_DTMF_ACK :
                    PrintBSSMAPMsgStopDTMFAck(iMsg);
                    break;
    
                 default :
                     break;
            }
        }
        else if (iMsg->GetProtDiscr() == PD_MOBILITY_MGMT_MSGS_NON_GPRS)
        {
            switch (msgType)
            {             
                case BSSAP_MSG_IMSI_DETACH_INDICATION :
                    PrintBSSMAPMsgIMSIDetachIndication(iMsg);
                    break;

                case BSSAP_MSG_LOCATION_UPDATING_ACCEPT :
                    PrintBSSMAPMsgLocationUpdatingAccept(iMsg);
                    break;

                case BSSAP_MSG_LOCATION_UPDATING_REJECT :
                    PrintBSSMAPMsgLocationUpdatingReject(iMsg);
                    break;

                case BSSAP_MSG_LOCATION_UPDATING_REQUEST :
                    PrintBSSMAPMsgLocationUpdatingRequest(iMsg);
                    break;

                case BSSAP_MSG_AUTHENTICATION_REJECT :
                    PrintBSSMAPMsgAuthenticationReject(iMsg);
                    break;
    
                case BSSAP_MSG_AUTHENTICATION_REQUEST :
                    PrintBSSMAPMsgAuthenticationRequest(iMsg);
                    break;

                case BSSAP_MSG_AUTHENTICATION_RESPONSE :
                    PrintBSSMAPMsgAuthenticationResponse(iMsg);
                    break;

                case BSSAP_MSG_TMSI_REALLOC_COMMAND :
                    PrintBSSMAPMsgTMSIReallocCommand(iMsg);
                    break;

                case BSSAP_MSG_TMSI_REALLOC_COMPLETE :
                    PrintBSSMAPMsgTMSIReallocComplete(iMsg);
                    break;
                 
                case BSSAP_MSG_CM_SERVICE_ABORT : 
                    PrintBSSMAPMsgCMServiceAbort(iMsg);
                    break;
                
                case BSSAP_MSG_CM_SERVICE_ACCEPT :
                    PrintBSSMAPMsgCMServiceAccept(iMsg);
                    break;  

                case BSSAP_MSG_CM_SERVICE_REJECT :
                    PrintBSSMAPMsgCMServiceReject(iMsg);
                    break;  

                case BSSAP_MSG_CM_SERVICE_REQUEST :
                    PrintBSSMAPMsgCMServiceRequest(iMsg);
                    break;  
      
                case BSSAP_MSG_CM_REESTABLISHMENT_REQ:
                    PrintBSSMAPMsgCMReestablishmentReq(iMsg);
                    break;

                case BSSAP_MSG_ABORT:
                    PrintBSSMAPMsgAbort(iMsg);
                    break;

                case BSSAP_MSG_MM_INFORMATION:
                    PrintBSSMAPMsgMMInformation(iMsg);
                    break;

                case BSSAP_MSG_MM_STATUS:
                    PrintBSSMAPMsgMMStatus(iMsg);
                    break;

                case BSSAP_MSG_MM_NULL:   
                    PrintBSSMAPMsgMMNull(iMsg);
                    break;  
                   
                case BSSAP_MSG_IDENTITY_REQUEST:
                    PrintBSSMAPMsgIdentityRequest(iMsg);
                    break;

                case BSSAP_MSG_IDENTITY_RESPONSE:
                    PrintBSSMAPMsgIdentityResponse(iMsg);
                    break;

                default :
                    break;
            }
        }
    }

    delete iMsg;
}

//////////////////////////////////////////////////////////////////////
//
//     Print BSSMAP messages
//
//////////////////////////////////////////////////////////////////////

// Assignment Complete
void 
PrintBSSMAPMsgAssignComplete(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Assignment Complete **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);
    DumpIE(BSSAP_IEI_RR_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);
    DumpIE(BSSAP_IEI_CHOSEN_CHANNEL, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);
    DumpIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL, ie);              

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);
    DumpIE(BSSAP_IEI_SPEECH_VERSION, ie);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER);
    DumpIE(BSSAP_IEI_LSA_IDENTIFIER, ie);
}

// Assignment Failure
void 
PrintBSSMAPMsgAssignFailure(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Assignment Failure **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);
    DumpIE(BSSAP_IEI_RR_CAUSE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL, ie);    

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL_LIST, ie);    
}

// Assignment Request
void
PrintBSSMAPMsgAssignReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Assignment Request **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    DumpIE(BSSAP_IEI_CHANNEL_TYPE, ie); 

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION);
    DumpIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, ie);      
    
    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);
    DumpIE(BSSAP_IEI_PRIORITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_DOWNLINK_DTX_FLAG);
    DumpIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);
    DumpIE(BSSAP_IEI_GROUP_CALL_REFERENCE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_TALKER_FLAG);
    DumpIE(BSSAP_IEI_TALKER_FLAG, ie);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR);
    DumpIE(BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR, ie); 

    ie = iMsg->FindIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND);
    DumpIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, ie);

    ie = iMsg->FindIE(BSSAP_IEI_SERVICE_HANDOVER);
    DumpIE(BSSAP_IEI_SERVICE_HANDOVER, ie); 
}

// Handover Candidate Enquire
void 
PrintBSSMAPMsgHandoverCandidateEnq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Candidate Enquire **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_NUMBER_OF_MS);
    DumpIE(BSSAP_IEI_NUMBER_OF_MS, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);   
}

// Handover Candidate Response   
void 
PrintBSSMAPMsgHandoverCandidateRsp(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Candidate Response **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_NUMBER_OF_MS);
    DumpIE(BSSAP_IEI_NUMBER_OF_MS, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);     
}

// Handover Command   
void 
PrintBSSMAPMsgHandoverCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Command **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    DumpIE(BSSAP_IEI_LAYER3_INFORMATION, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);     
}

// Handover Complete   
void 
PrintBSSMAPMsgHandoverComplete(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Complete **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);
    DumpIE(BSSAP_IEI_RR_CAUSE, ie);
}

// Handover Detect   
void 
PrintBSSMAPMsgHandoverDetect(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "HandoverDetect does not have IE **** " << endl << endl;
}

// Handover Failure   
void 
PrintBSSMAPMsgHandoverFailure(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Failure **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);
    DumpIE(BSSAP_IEI_RR_CAUSE, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL_LIST, ie);   
}

// Handover Performed  
void 
PrintBSSMAPMsgHandoverPerformed(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Performed **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);
    DumpIE(BSSAP_IEI_CHOSEN_CHANNEL, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);
    DumpIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, ie);

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);
    DumpIE(BSSAP_IEI_SPEECH_VERSION, ie);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER);
    DumpIE(BSSAP_IEI_LSA_IDENTIFIER, ie);
}

// Handover Request   
void 
PrintBSSMAPMsgHandoverReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Request **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    DumpIE(BSSAP_IEI_CHANNEL_TYPE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_ENCRYPTION_INFORMATION);
    DumpIE(BSSAP_IEI_ENCRYPTION_INFORMATION, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, ie);   

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);      

    //ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    //DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);   

    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);
    DumpIE(BSSAP_IEI_PRIORITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);   

    ie = iMsg->FindIE(BSSAP_IEI_DOWNLINK_DTX_FLAG);
    DumpIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED);
    DumpIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED, ie); 
       
    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, ie);   
    
    ie = iMsg->FindIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1);
    DumpIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);
    DumpIE(BSSAP_IEI_SPEECH_VERSION, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);
    DumpIE(BSSAP_IEI_GROUP_CALL_REFERENCE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_TALKER_FLAG);
    DumpIE(BSSAP_IEI_TALKER_FLAG, ie);   
    
    ie = iMsg->FindIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND);
    DumpIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);
    DumpIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, ie); 

    ie = iMsg->FindIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS);
    DumpIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS, ie);

    ie = iMsg->FindIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA);
    DumpIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA, ie);
}

// Handover Request Acknowledge  
void 
PrintBSSMAPMsgHandoverReqAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Request Acknowledge **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    DumpIE(BSSAP_IEI_LAYER3_INFORMATION, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);
    DumpIE(BSSAP_IEI_CHOSEN_CHANNEL, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);
    DumpIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL, ie);    

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);
    DumpIE(BSSAP_IEI_SPEECH_VERSION, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER);
    DumpIE(BSSAP_IEI_LSA_IDENTIFIER, ie);
}

// Handover Required  
void 
PrintBSSMAPMsgHandoverRequired(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;
    const BSSAP_Element* ieBSS;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Required **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_RESPONSE_REQUEST);
    DumpIE(BSSAP_IEI_RESPONSE_REQUEST, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL_LIST, ie);  

    ie = iMsg->FindIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1);
    DumpIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);
    DumpIE(BSSAP_IEI_SPEECH_VERSION, ie);  

    ie = iMsg->FindIE(BSSAP_IEI_QUEUING_INDICATOR);
    DumpIE(BSSAP_IEI_QUEUING_INDICATOR, ie); 
    
#if 0
    // Print Field IE in Old BSS To New BSS Informaiton
    ieBSS = iMsg->FindIE(BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_EXTRA_INFORMATION);   
    DumpIEBSS(BSSAP_IEI_EXTRA_INFORMATION, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_2);   
    DumpIEBSS(BSSAP_IEI_CURRENT_CHANNEL_TYPE_2, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_TARGET_CELL_RADIO_INFO);   
    DumpIEBSS(BSSAP_IEI_TARGET_CELL_RADIO_INFO, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_GPRS_SUSPEND_INFO);   
    DumpIEBSS(BSSAP_IEI_GPRS_SUSPEND_INFO, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_MULTIRATE_CONFIG_INFO);   
    DumpIEBSS(BSSAP_IEI_MULTIRATE_CONFIG_INFO, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_DUAL_TRANSFER_MODE_INFO);   
    DumpIEBSS(BSSAP_IEI_DUAL_TRANSFER_MODE_INFO, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_UE_CAP_INFO);   
    DumpIEBSS(BSSAP_IEI_UE_CAP_INFO, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_CDMA_2000_CAP_INFO);   
    DumpIEBSS(BSSAP_IEI_CDMA_2000_CAP_INFO, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_UTRAN_PRECONFIG_IND_SET_INFO);   
    DumpIEBSS(BSSAP_IEI_UTRAN_PRECONFIG_IND_SET_INFO, ie);

    ie = ((BSSAP_OldBSStoNewBSSInfo*) ieBSS)->
                  FindIE(BSSAP_IEI_UE_SECURITY_INFO);   
    DumpIEBSS(BSSAP_IEI_UE_SECURITY_INFO, ie);
    // End Print Field IE in Old BSS To New BSS Informaiton

    ie = iMsg->FindIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS);
    DumpIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS, ie);

    ie = iMsg->FindIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA);
    DumpIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA, ie);
#endif
}

// Handover Required Reject   
void 
PrintBSSMAPMsgHandoverRequiredRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Handover Required Reject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);
}

// Handover Succeeded   
void 
PrintBSSMAPMsgHandoverSucceeded(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "HandoverSucceeded does not have any IE **** " << endl << endl;
}

// Clear Command 
void 
PrintBSSMAPMsgClrCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Clear Command **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION);
    DumpIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, ie);
}

// Clear Complete
void 
PrintBSSMAPMsgClrComplete(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "ClearComplete does not have any IE **** " << endl << endl;  
}

// Clear Request
void 
PrintBSSMAPMsgClrReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Clear Request **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);
} 

// SAPI n Reject
void
PrintBSSMAPMsgSAPInRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "SAPI n Reject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_DLCI);
    DumpIE(BSSAP_IEI_DLCI, ie);
}

// Confusion   
void 
PrintBSSMAPMsgConfusion(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Confusion **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_DIAGNOSTICS);
    DumpIE(BSSAP_IEI_DIAGNOSTICS, ie);     
}

// Suspend   
void 
PrintBSSMAPMsgSuspend(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Suspend does not have any IE **** " << endl << endl; 
    
    ie = iMsg->FindIE(BSSAP_IEI_DLCI);
    DumpIE(BSSAP_IEI_DLCI, ie);  
}

// Resume   
void 
PrintBSSMAPMsgResume(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Resume does not have any IE **** " << endl << endl; 
    
    ie = iMsg->FindIE(BSSAP_IEI_DLCI);
    DumpIE(BSSAP_IEI_DLCI, ie);  
}

// Reset
void 
PrintBSSMAPMsgReset(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Reset **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie); 
}

// Reset Ack
void 
PrintBSSMAPMsgResetAck(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "ResetAck does not have any IE **** " << endl << endl;
}

// Reset Circuit
void 
PrintBSSMAPMsgResetCircuit(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Reset Circuit **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);   
    
    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);                       
}

// Reset Circuit Ack
void 
PrintBSSMAPMsgResetCircuitAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Reset Circuit Ack **** " << endl << endl;    

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);     
}

// Overload
void 
PrintBSSMAPMsgOverload(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Overload **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);                       

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);     
}

// MSC Invoke Trace   
void 
PrintBSSMAPMsgMSCInvokeTrace(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "MSC Invoke Trace **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_TYPE);
    DumpIE(BSSAP_IEI_TRACE_TYPE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_REFERENCE);
    DumpIE(BSSAP_IEI_TRACE_REFERENCE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_TRIGGER_ID);
    DumpIE(BSSAP_IEI_TRIGGER_ID, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_TRANSACTION_ID);
    DumpIE(BSSAP_IEI_TRANSACTION_ID, ie);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIE(BSSAP_IEI_MOBILE_IDENTITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_OMC_ID);
    DumpIE(BSSAP_IEI_OMC_ID, ie);
}

// BSS Invoke Trace   
void 
PrintBSSMAPMsgBSSInvokeTrace(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "BSS Invoke Trace **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_TYPE);
    DumpIE(BSSAP_IEI_TRACE_TYPE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_REFERENCE);
    DumpIE(BSSAP_IEI_TRACE_REFERENCE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_FORWARD_INDICATOR);
    DumpIE(BSSAP_IEI_FORWARD_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_TRIGGER_ID);
    DumpIE(BSSAP_IEI_TRIGGER_ID, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_TRANSACTION_ID);
    DumpIE(BSSAP_IEI_TRANSACTION_ID, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIE(BSSAP_IEI_MOBILE_IDENTITY, ie);

    ie = iMsg->FindIE(BSSAP_IEI_OMC_ID);
    DumpIE(BSSAP_IEI_OMC_ID, ie); 
}

// Block
void
PrintBSSMAPMsgBlock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Block **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_CONNECTION_RELEASE_REQUESTED);
    DumpIE(BSSAP_IEI_CONNECTION_RELEASE_REQUESTED, ie); 
}

// Block Acknowledge
void 
PrintBSSMAPMsgBlockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Block Acknowledge **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);     
}

// Unblock
void 
PrintBSSMAPMsgUnblock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Unblock **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);     
}

// Unblock Acknowledge
void 
PrintBSSMAPMsgUnblockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Unblock Ack **** " << endl << endl; 

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);     
}

// Circuit Group Block   
void 
PrintBSSMAPMsgCktGroupBlock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Circuit Group Block **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, ie);
}

// Circuit Group Block Ack  
void 
PrintBSSMAPMsgCktGroupBlockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Circuit Group Block Ack **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, ie);     
}

// Circuit Group Unblock 
void 
PrintBSSMAPMsgCktGroupUnblock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Circuit Group Unblock **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie); 

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, ie);     
}

// Circuit Group Unblock Ack  
void 
PrintBSSMAPMsgCktGroupUnblockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Circuit Group Unblock Ack **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, ie);     
}

// Unequipped Circuit   
void 
PrintBSSMAPMsgUnequippedCkt(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Unequipped Circuit **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie); 
    
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, ie);     
}

// Change Circuit   
void 
PrintBSSMAPMsgChangeCkt(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Change Circuit **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);  
}

// Change Circuit Ack  
void 
PrintBSSMAPMsgChangeCktAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Change Circuit Ack **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);  
}

// Resource Request
void 
PrintBSSMAPMsgResourceReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Resource Request **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_PERIODICITY);
    DumpIE(BSSAP_IEI_PERIODICITY, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD);
    DumpIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);

    ie = iMsg->FindIE(BSSAP_IEI_EXTENDED_RESOURCE_INDICATOR);
    DumpIE(BSSAP_IEI_EXTENDED_RESOURCE_INDICATOR, ie);
} 

// Resource Indication
void 
PrintBSSMAPMsgResourceInd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Resource Indication **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD);
    DumpIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_AVAILABLE);
    DumpIE(BSSAP_IEI_RESOURCE_AVAILABLE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_TOTAL_RESOURCE_ACCESSIBLE);
    DumpIE(BSSAP_IEI_TOTAL_RESOURCE_ACCESSIBLE, ie);
} 

// Paging
void 
PrintBSSMAPMsgPaging(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Paging **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_IMSI);
    DumpIE(BSSAP_IEI_IMSI, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_TMSI);
    DumpIE(BSSAP_IEI_TMSI, ie);

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_NEEDED);
    DumpIE(BSSAP_IEI_CHANNEL_NEEDED, ie);

    ie = iMsg->FindIE(BSSAP_IEI_eMLPP_PRIORITY);
    DumpIE(BSSAP_IEI_eMLPP_PRIORITY, ie);
} 

// Paging Response
void
PrintBSSMAPMsgPagingResponse(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Paging Response **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE);
    DumpIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, ie);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIE(BSSAP_IEI_MOBILE_IDENTITY, ie);
}

// Cipher Mode Command
void 
PrintBSSMAPMsgCipherModeCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Cipher Mode Command **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_ENCRYPTION_INFORMATION);
    DumpIE(BSSAP_IEI_ENCRYPTION_INFORMATION, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION);
    DumpIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CIPHER_RESPONSE_MODE);
    DumpIE(BSSAP_IEI_CIPHER_RESPONSE_MODE, ie);
} 

// Cipher Mode Complete
void 
PrintBSSMAPMsgCipherModeComplete(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Cipher Mode Complete **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_MESSAGE_CONTENT);
    DumpIE(BSSAP_IEI_LAYER3_MESSAGE_CONTENT, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);
    DumpIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, ie);
} 

// Cipher Mode Reject
void 
PrintBSSMAPMsgCipherModeRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Cipher Mode Reject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);
} 

// Classmark Update
void 
PrintBSSMAPMsgClassmarkUpdate(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Classmark Update **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, ie); 
} 

// Classmark Request
void 
PrintBSSMAPMsgClassmarkReq(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Classmark Request does not have any IE **** " << endl << endl;
}

// Complete Layer 3 Information
void 
PrintBSSMAPMsgCompleteLayer3Info(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Complete Layer 3 Information **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    DumpIE(BSSAP_IEI_LAYER3_INFORMATION, ie);  

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER_LIST);
    DumpIE(BSSAP_IEI_LSA_IDENTIFIER_LIST, ie);
}   

// Load Indication
void 
PrintBSSMAPMsgLoadInd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Load Indication **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_TIME_INDICATION);
    DumpIE(BSSAP_IEI_TIME_INDICATION, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, ie);

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_SITUATION);
    DumpIE(BSSAP_IEI_RESOURCE_SITUATION, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);
} 

// Queuing Indication
void 
PrintBSSMAPMsgQueuingInd(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "QueuingIndication does not have any IE **** " << endl << endl;
}

// VGCSVBS Setup
void 
PrintBSSMAPMsgVGCSVBSSetup(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "VGCSVBS Setup **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);
    DumpIE(BSSAP_IEI_GROUP_CALL_REFERENCE, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);
    DumpIE(BSSAP_IEI_PRIORITY, ie);
} 

// VGCSVBS Setup Ack
void 
PrintBSSMAPMsgVGCSVBSSetupAck(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "VGCSVBSSetupAck does not have any IE **** " << endl << endl;
} 

// VGCSVBS Setup Refuse
void 
PrintBSSMAPMsgVGCSVBSSetupRefuse(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "VGCSVBS Setup Refuse **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);          
}

// VGCSVBS Assign Req
void 
PrintBSSMAPMsgVGCSVBSAssignReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "VGCSVBS Assign Req **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    DumpIE(BSSAP_IEI_CHANNEL_TYPE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_ASSIGNMENT_REQUIREMENT);
    DumpIE(BSSAP_IEI_ASSIGNMENT_REQUIREMENT, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);                       

    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);
    DumpIE(BSSAP_IEI_GROUP_CALL_REFERENCE, ie);        

    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);
    DumpIE(BSSAP_IEI_PRIORITY, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_DOWNLINK_DTX_FLAG);
    DumpIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_ENCRYPTION_INFORMATION);
    DumpIE(BSSAP_IEI_ENCRYPTION_INFORMATION, ie);
}

// VGCSVBSAssignRsult
void 
PrintBSSMAPMsgVGCSVBSAssignRsult(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "VGCSVBS Assign Rsult **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    DumpIE(BSSAP_IEI_CHANNEL_TYPE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);
    DumpIE(BSSAP_IEI_CHOSEN_CHANNEL, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    DumpIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, ie);                       

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL, ie);
}

// VGCSVBSAssignFailure        
void 
PrintBSSMAPMsgVGCSVBSAssignFailure(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "VGCSVBSAssignFailure **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);     

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL, ie);      
   
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);
    DumpIE(BSSAP_IEI_CIRCUIT_POOL_LIST, ie);
}        

// VGCSVBS Queuing Indication
void 
PrintBSSMAPMsgVGCSVBSQueuingInd(BSSAP_Message* iMsg)
{
     cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
     cout << "VGCSVBSQueuingInd does not have any IE **** " << endl << endl;
}

// HandOff Required Reject        
void 
PrintBSSMAPMsgHORequiredRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "HandOff Required Reject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);                       
}

// Uplink Request
void 
PrintBSSMAPMsgUplinkReq(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout <<"UplinkRequest does not have any IE **** " << endl << endl;
}        

// Uplink Req Ack
void 
PrintBSSMAPMsgUplinkReqAck(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "UplinkReqAck does not have any IE **** " << endl << endl;
}

// UplinkReqConfirm
void 
PrintBSSMAPMsgUplinkReqConfirm(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "UplinkReqConfirm **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    DumpIE(BSSAP_IEI_LAYER3_INFORMATION, ie);
}

// UplinkReleaseInd
void 
PrintBSSMAPMsgUplinkReleaseInd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Uplink Release Ind **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie); 
}        

// Uplink Rej Cmd
void 
PrintBSSMAPMsgUplinkRejCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Uplink Rej Cmd **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);
}       

// Uplink Release Cmd
void 
PrintBSSMAPMsgUplinkReleaseCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Uplink Release Cmd **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);
}

// Uplink Seized Cmd       
void 
PrintBSSMAPMsgUplinkSeizedCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Uplink Seized Cmd **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    DumpIE(BSSAP_IEI_CAUSE, ie);     
}

// CommonID
void 
PrintBSSMAPMsgCommonID(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Common ID **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_IMSI);
    DumpIE(BSSAP_IEI_IMSI, ie);     
}

// LSA Information
void 
PrintBSSMAPMsgLSAInfo(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "LSA Information **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LSA_INFORMATION);
    DumpIE(BSSAP_IEI_LSA_INFORMATION, ie);     
}

// Connection Oriented Information
void 
PrintBSSMAPMsgConnOrientInfo(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Connection Oriented Information **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_APDU);
    DumpIE(BSSAP_IEI_APDU, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_SEGMENTATION);
    DumpIE(BSSAP_IEI_SEGMENTATION, ie);  
}

// Perform Location Request
void 
PrintBSSMAPMsgPerformLocReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Perform Location Request **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_TYPE);
    DumpIE(BSSAP_IEI_LOCATION_TYPE, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    DumpIE(BSSAP_IEI_CELL_IDENTIFIER, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, ie);  

    ie = iMsg->FindIE(BSSAP_IEI_LCS_CLIENT_TYPE);
    DumpIE(BSSAP_IEI_LCS_CLIENT_TYPE, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);
    DumpIE(BSSAP_IEI_CHOSEN_CHANNEL, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_LCS_QOS);
    DumpIE(BSSAP_IEI_LCS_QOS, ie);  

    ie = iMsg->FindIE(BSSAP_IEI_GPS_ASSISTANCE_DATA);
    DumpIE(BSSAP_IEI_GPS_ASSISTANCE_DATA, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_APDU);
    DumpIE(BSSAP_IEI_APDU, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_LCS_PRIORITY);
    DumpIE(BSSAP_IEI_LCS_PRIORITY, ie); 
}

// Perform Location Response
void 
PrintBSSMAPMsgPerformLocRsp(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Perform Location Response **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_ESTIMATE);
    DumpIE(BSSAP_IEI_LOCATION_ESTIMATE, ie);   
    
    ie = iMsg->FindIE(BSSAP_IEI_DECIPHERING_KEYS);
    DumpIE(BSSAP_IEI_DECIPHERING_KEYS, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_LCS_CAUSE);
    DumpIE(BSSAP_IEI_LCS_CAUSE, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_POSITIONING_DATA);
    DumpIE(BSSAP_IEI_POSITIONING_DATA, ie); 
}

// Perform Location Abort
void 
PrintBSSMAPMsgPerformLocAbort(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Perform Location Abort **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LCS_CAUSE);
    DumpIE(BSSAP_IEI_LCS_CAUSE, ie);     
}

// Connectionless Information
void 
PrintBSSMAPMsgConnlessInfo(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Connectionless Information **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY);
    DumpIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, ie);  

    ie = iMsg->FindIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY);
    DumpIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, ie);
    
    ie = iMsg->FindIE(BSSAP_IEI_APDU);
    DumpIE(BSSAP_IEI_APDU, ie);
    
    ie = iMsg->FindIE(BSSAP_IEI_SEGMENTATION);
    DumpIE(BSSAP_IEI_SEGMENTATION, ie);  
    
    ie = iMsg->FindIE(BSSAP_IEI_RETURN_ERROR_REQUEST);
    DumpIE(BSSAP_IEI_RETURN_ERROR_REQUEST, ie);

    ie = iMsg->FindIE(BSSAP_IEI_RETURN_ERROR_CAUSE);
    DumpIE(BSSAP_IEI_RETURN_ERROR_CAUSE, ie);
}

void 
PrintBSSMAPMsgAlerting(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Alerting **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_FACILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      
}

void 
PrintBSSMAPMsgCallConfirm(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Call Confirm **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAPABILITIES);
    DumpCCIE(BSSAP_IEI_CC_CAPABILITIES, ie);      
}

void 
PrintBSSMAPMsgCallProceeding(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Call Proceeding **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_FACILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      
}

void 
PrintBSSMAPMsgConnect(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Connect **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_FACILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CONNECTED_NUMBER);
    DumpCCIE(BSSAP_IEI_CC_CONNECTED_NUMBER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CONNECTED_SUB_ADDRESS);
    DumpCCIE(BSSAP_IEI_CC_CONNECTED_SUB_ADDRESS, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_SS_VERSION_IND);
    DumpCCIE(BSSAP_IEI_CC_SS_VERSION_IND, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_STREAM_IDENTIFIER);
    DumpCCIE(BSSAP_IEI_CC_STREAM_IDENTIFIER, ie);
}

void 
PrintBSSMAPMsgConnectAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Connect Ack**** " << endl << endl;
}

void 
PrintBSSMAPMsgEmergencySetup(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "EmergencySetup **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_STREAM_IDENTIFIER);
    DumpCCIE(BSSAP_IEI_CC_STREAM_IDENTIFIER, ie);

    ie = iMsg->FindIE(BSSAP_IEI_CC_SUPPORTED_CODECS);
    DumpCCIE(BSSAP_IEI_CC_SUPPORTED_CODECS, ie);

    ie = iMsg->FindIE(BSSAP_IEI_CC_EMERGENCY_CATEGORY);
    DumpCCIE(BSSAP_IEI_CC_EMERGENCY_CATEGORY, ie);
}

void 
PrintBSSMAPMsgProgress(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Progress **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      
}

void 
PrintBSSMAPMsgCCEstablishment(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "CCEstablishment **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_SETUP_CONTAINER_INTERNAL);
    DumpCCIE(BSSAP_IEI_CC_SETUP_CONTAINER_INTERNAL, ie);      
}

void 
PrintBSSMAPMsgCCEstablishmentConfirm(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Connect **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_REPEAT_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_REPEAT_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      
}

void 
PrintBSSMAPMsgSetup(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Setup **** " << endl << endl;
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_REPEAT_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_REPEAT_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    ie = iMsg->FindNextIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      
    
    ie = iMsg->FindIE(BSSAP_IEI_CC_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_FACILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_SIGNAL);
    DumpCCIE(BSSAP_IEI_CC_SIGNAL, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CALLING_PARTY_BCD_NUMBER);
    DumpCCIE(BSSAP_IEI_CC_CALLING_PARTY_BCD_NUMBER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CALLING_PARTY_SUB_ADDRESS);
    DumpCCIE(BSSAP_IEI_CC_CALLING_PARTY_SUB_ADDRESS, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CALLED_PARTY_BCD_NUMBER);
    DumpCCIE(BSSAP_IEI_CC_CALLED_PARTY_BCD_NUMBER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CALLED_PARTY_SUB_ADDRESS);
    DumpCCIE(BSSAP_IEI_CC_CALLED_PARTY_SUB_ADDRESS, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_REDIRECTING_PARTY_BCD_NUMBER);
    DumpCCIE(BSSAP_IEI_CC_REDIRECTING_PARTY_BCD_NUMBER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_REDIRECTING_PARTY_SUB_ADDRESS);
    DumpCCIE(BSSAP_IEI_CC_REDIRECTING_PARTY_SUB_ADDRESS, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PRIORITY_LEVEL);
    DumpCCIE(BSSAP_IEI_CC_PRIORITY_LEVEL, ie);

    ie = iMsg->FindIE(BSSAP_IEI_CC_ALERTING_PATTERN);
    DumpCCIE(BSSAP_IEI_CC_ALERTING_PATTERN, ie);
}

void 
PrintBSSMAPMsgModify(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Modify **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_REVERSE_CALL_SETUP_DIRECTION);
    DumpCCIE(BSSAP_IEI_CC_REVERSE_CALL_SETUP_DIRECTION, ie);      
}

void 
PrintBSSMAPMsgModifyComplete(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "ModifyComplete **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_REVERSE_CALL_SETUP_DIRECTION);
    DumpCCIE(BSSAP_IEI_CC_REVERSE_CALL_SETUP_DIRECTION, ie);      
}

void 
PrintBSSMAPMsgModifyReject(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "ModifyReject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_BEARER_CAPABILITY);
    DumpCCIE(BSSAP_IEI_CC_BEARER_CAPABILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY);
    DumpCCIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, ie);      
}

void 
PrintBSSMAPMsgUserInformation(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "UserInformation **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_MORE_DATA);
    DumpCCIE(BSSAP_IEI_CC_MORE_DATA, ie);      
}

void 
PrintBSSMAPMsgHold(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSAP MESSAGE **** ";
    cout << "Hold **** " << endl << endl;
}

void 
PrintBSSMAPMsgHoldAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSAP MESSAGE **** ";
    cout << "Hold Ack**** " << endl << endl;
}

void 
PrintBSSMAPMsgHoldReject(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSAP MESSAGE **** ";
    cout << "Hold Reject**** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      
}

void 
PrintBSSMAPMsgRetrieve(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Retrieve **** " << endl << endl;
}

void 
PrintBSSMAPMsgRetrieveAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "RetrieveAck **** " << endl << endl;
}

void 
PrintBSSMAPMsgRetrieveReject(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "RetrieveReject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      
}

void 
PrintBSSMAPMsgDisconnect(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Disconnect **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_FACILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      

    //ie = iMsg->FindIE(BSSAP_IEI_CC_SS_VERSION_IND);
    //DumpCCIE(BSSAP_IEI_CC_SS_VERSION_IND, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_ALLOWED_ACTIONS);
    DumpCCIE(BSSAP_IEI_CC_ALLOWED_ACTIONS, ie);
}

void 
PrintBSSMAPMsgRelease(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Release **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_FACILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_SS_VERSION_IND);
    DumpCCIE(BSSAP_IEI_CC_SS_VERSION_IND, ie);      
}

void 
PrintBSSMAPMsgReleaseComplete(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "ReleaseComplete **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_FACILITY, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_PROGRESS_INDICATOR);
    DumpCCIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_USER_USER);
    DumpCCIE(BSSAP_IEI_CC_USER_USER, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_SS_VERSION_IND);
    DumpCCIE(BSSAP_IEI_CC_SS_VERSION_IND, ie);      
}

void 
PrintBSSMAPMsgCongestionControl(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "CongestionControl **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CONGESTION_LEVEL_INTERNAL);
    DumpCCIE(BSSAP_IEI_CC_CONGESTION_LEVEL_INTERNAL, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      
}

void 
PrintBSSMAPMsgNotify(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Notify **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_NOTIFICATION_INDICATOR_INTERNAL);
    DumpCCIE(BSSAP_IEI_CC_NOTIFICATION_INDICATOR_INTERNAL, ie);      
}

void 
PrintBSSMAPMsgStartDTMF(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Start DTMF **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_KEYPAD_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_KEYPAD_FACILITY, ie);      
}

void 
PrintBSSMAPMsgStartDTMFAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Start DTMF Ack **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_KEYPAD_FACILITY);
    DumpCCIE(BSSAP_IEI_CC_KEYPAD_FACILITY, ie);      
}

void 
PrintBSSMAPMsgStartDTMFReject(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Start DTMF Reject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      
}

void 
PrintBSSMAPMsgStopDTMF(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Stop DTMF **** " << endl << endl;
}

void 
PrintBSSMAPMsgStopDTMFAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Stop DTMF Ack **** " << endl << endl;
}

void 
PrintBSSMAPMsgStatus(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Status **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CC_CAUSE);
    DumpCCIE(BSSAP_IEI_CC_CAUSE, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_CALL_STATE_INTERNAL);
    DumpCCIE(BSSAP_IEI_CC_CALL_STATE_INTERNAL, ie);      

    ie = iMsg->FindIE(BSSAP_IEI_CC_AUXILLARY_STATES);
    DumpCCIE(BSSAP_IEI_CC_AUXILLARY_STATES, ie);      
}

void 
PrintBSSMAPMsgStatusEnquiry(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Status Enquiry **** " << endl << endl;
}

void 
PrintBSSMAPMsgIMSIDetachIndication(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "IMSIDetachIndication **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1, ie); 
	
    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIEMM(BSSAP_IEI_MOBILE_IDENTITY, ie);
}

void 
PrintBSSMAPMsgLocationUpdatingAccept(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "LocationUpdatingAccept **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER);
    DumpIEMM(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, ie);  

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIEMM(BSSAP_IEI_MOBILE_IDENTITY, ie); 
	
    ie = iMsg->FindIE(BSSAP_IEI_FOLLOW_ON_PROCEED);
    DumpIEMM(BSSAP_IEI_FOLLOW_ON_PROCEED, ie);
}

void 
PrintBSSMAPMsgLocationUpdatingReject(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "LocationUpdatingReject **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);
    DumpIE(BSSAP_IEI_RR_CAUSE, ie); 
}

void 
PrintBSSMAPMsgLocationUpdatingRequest(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "LocationUpdatingRequest **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_UPDATING_TYPE);
    DumpIEMM(BSSAP_IEI_LOCATION_UPDATING_TYPE, ie); 
	
    ie = iMsg->FindIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE);
    DumpIEMM(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER);
    DumpIEMM(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, ie);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1, ie);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIEMM(BSSAP_IEI_MOBILE_IDENTITY, ie);
}

void 
PrintBSSMAPMsgAuthenticationReject(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "AuthenticationReject does not have any IE **** " << endl << endl;
}

void 
PrintBSSMAPMsgAuthenticationRequest(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "AuthenticationRequest **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE);
    DumpIEMM(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, ie); 
	
    ie = iMsg->FindIE(BSSAP_IEI_PARAMETER_RAND);
    DumpIEMM(BSSAP_IEI_PARAMETER_RAND, ie);
}

void 
PrintBSSMAPMsgAuthenticationResponse(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "AuthenticationResponse **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_PARAMETER_SRES);
    DumpIEMM(BSSAP_IEI_PARAMETER_SRES, ie); 
}

void
PrintBSSMAPMsgAuthenticationFailure(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;
                                                                                
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "AuthenticationFailure **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_REJECT_CAUSE);
    DumpIEMM(BSSAP_IEI_REJECT_CAUSE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_AUTH_FAILURE_PARAMETER);
    DumpIEMM(BSSAP_IEI_AUTH_FAILURE_PARAMETER, ie);
}

void 
PrintBSSMAPMsgIdentityRequest(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "IdentityRequest **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_IDENTITY_TYPE);
    DumpIEMM(BSSAP_IEI_IDENTITY_TYPE, ie); 
}

void 
PrintBSSMAPMsgIdentityResponse(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "IdentityResponse **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIEMM(BSSAP_IEI_MOBILE_IDENTITY, ie); 
}

void 
PrintBSSMAPMsgTMSIReallocCommand(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "TMSIReallocCommand **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER);
    DumpIEMM(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, ie);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIEMM(BSSAP_IEI_MOBILE_IDENTITY, ie);
}

void 
PrintBSSMAPMsgTMSIReallocComplete(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "TMSIReallocComplete does not have any IE **** " << endl << endl;
}

void 
PrintBSSMAPMsgCMReestablishmentReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "CMReestablishmentReq **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE);
    DumpIEMM(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, ie); 
	
    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, ie);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIEMM(BSSAP_IEI_MOBILE_IDENTITY, ie);

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER);
    DumpIEMM(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, ie);
}

void 
PrintBSSMAPMsgCMServiceAbort(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "CMServiceAbort does not have any IE **** " << endl << endl;
}

void 
PrintBSSMAPMsgCMServiceAccept(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "CMServiceAccept does not have any IE **** " << endl << endl;
}

void 
PrintBSSMAPMsgCMServiceReject(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "CMServiceReject **** " << endl << endl;

    ie = iMsg->FindIE( BSSAP_IEI_RR_CAUSE);
    DumpIE( BSSAP_IEI_RR_CAUSE, ie); 
}

void 
PrintBSSMAPMsgCMServiceRequest(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "CMServiceRequest **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_CM_SERVICE_TYPE);
    DumpIEMM(BSSAP_IEI_CM_SERVICE_TYPE, ie); 
	
    ie = iMsg->FindIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE);
    DumpIEMM(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    DumpIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, ie);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);
    DumpIEMM(BSSAP_IEI_MOBILE_IDENTITY, ie);
}

void 
PrintBSSMAPMsgAbort(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "Abort does not have any IE **** " << endl << endl;
}

void 
PrintBSSMAPMsgMMInformation(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "MMInformation **** " << endl << endl;

    ie = iMsg->FindIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY);
    DumpIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, ie); 
	
    ie = iMsg->FindIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY);
    DumpIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, ie);

    ie = iMsg->FindIE(BSSAP_IEI_TIME_ZONE);
    DumpIEMM(BSSAP_IEI_TIME_ZONE, ie);

    ie = iMsg->FindIE(BSSAP_IEI_TIME_ZONE_TIME);
    DumpIEMM(BSSAP_IEI_TIME_ZONE_TIME, ie);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER);
    DumpIE(BSSAP_IEI_LSA_IDENTIFIER, ie);
}

void 
PrintBSSMAPMsgMMNull(BSSAP_Message* iMsg)
{
    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "MMNull does not have any IE **** " << endl << endl;
}

void 
PrintBSSMAPMsgMMStatus(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    cout << endl << setw(15) << " " << "BSSMAP MESSAGE **** ";
    cout << "MMStatus **** " << endl << endl;

    ie = iMsg->FindIE( BSSAP_IEI_RR_CAUSE);
    DumpIE( BSSAP_IEI_RR_CAUSE, ie); 
}

#if defined(ITS_NAMESPACE)
}
#endif
