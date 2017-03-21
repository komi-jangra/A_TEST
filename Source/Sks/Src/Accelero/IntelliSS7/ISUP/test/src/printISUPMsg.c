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
 *  ID: $Id: printISUPMsg.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:08  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:05  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:37  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:37  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:06  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.2  2000/09/20 18:44:03  labuser
 * LOG: Had wrong printing for CircuitStateIndicator parameter
 * LOG:
 * LOG: Revision 1.1  2000/09/08 14:34:16  labuser
 * LOG: cbascon: now have correct directory structure
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:33  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.17  2000/07/06 18:34:06  labuser
 * LOG: Separating ANS/CCITT code
 * LOG:
 * LOG: Revision 2.16  2000/07/06 18:32:23  labuser
 * LOG: ANSI/CCITT should've been separated to begin with
 * LOG:
 * LOG: Revision 2.15  2000/07/06 18:28:02  labuser
 * LOG: Still separating ANSI and CCITT code
 * LOG:
 * LOG: Revision 2.14  2000/07/06 18:26:00  labuser
 * LOG: Still separating ANSI and CCITT code
 * LOG:
 * LOG: Revision 2.13  2000/07/06 18:24:33  labuser
 * LOG: Had two more case statements that needed to be in CCITT ifdef
 * LOG:
 * LOG: Revision 2.12  2000/07/06 18:22:54  labuser
 * LOG: Have if defined(CCITT) clauses to enclose each function individually
 * LOG:
 * LOG: Revision 2.11  2000/07/06 18:09:42  labuser
 * LOG: Move code valid for CCITT into correct ifdef clause
 * LOG:
 * LOG: Revision 2.10  2000/07/06 18:04:43  labuser
 * LOG: Some parameters were inside wrong protocol ifdefs
 * LOG:
 * LOG: Revision 2.9  2000/05/17 14:08:55  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.8  2000/05/16 15:11:32  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.7  2000/01/11 22:36:42  labuser
 * LOG: No major change.
 * LOG:
 * LOG: Revision 2.6  2000/01/11 18:11:19  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.5  1999/12/30 15:54:11  labuser
 * LOG: Clean up...
 * LOG:
 * LOG: Revision 2.4  1999/12/27 19:01:47  cbascon
 * LOG: Added functions for reading and printing parameters for ACM, ANM, CPG,
 * LOG: REL, RLC, CFN, CON, SAM, UCIC, RSC for CCITT only.
 * LOG:
 * LOG: Revision 2.3  1999/12/21 19:25:08  cbascon
 * LOG: Added print functions for IAM parameters(CCITT)
 * LOG:
 * LOG: Revision 2.2  1999/12/10 22:50:06  cbascon
 * LOG: Tested ANSI ISUP messages ACM, ANM, CPG, IAM, BLO, UBL, UCIC, REL, RLC,
 * LOG: RSC
 * LOG:
 * LOG: Revision 2.1  1999/12/07 00:40:03  cbascon
 * LOG: Encoded and sent the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO
 * LOG:
 * LOG: Received and decoded the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO, UCIC
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:35  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/11/24 19:25:22  cbascon
 * LOG: Added pretty print functions.
 * LOG:
 * LOG: Revision 1.1  1999/11/14 23:14:25  cbascon
 * LOG: Added print functions for parameters.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>

#include <its.h>
#include <itu/isup.h>
#include <ansi/isup.h>
#include "printISUPMsg.h"


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
int
PrintISUPMsg(const ITS_ISUP_IE *ie, int ieCount)
{
    int i;
    int result = ITS_SUCCESS;

    /* Make sure ieCount > 0 */
    if ( ieCount > 0)
    {
        /* Check if ie is not NULL */
        if ( ie )
        {
            for (i = 0; i < ieCount; ++i)
            {
                switch ( (int)ie[i].param_id )
                {
                case ISUP_PRM_ACCESS_TRANSPORT:
                    PrintAccessTransportPar(&ie[i]);
                    break;
                case ISUP_PRM_AUTO_CONGEST_LEVEL:
                    PrintAutoCongestionLvlPar(&ie[i]);
                    break;
                case ISUP_PRM_BKWD_CALL_INDICATORS:
                    PrintBackwardCallIndPar(&ie[i]);
                    break;
                case ISUP_PRM_CALL_REF:
                    PrintCallRefPar(&ie[i]);
                    break;
                case ISUP_PRM_CALLED_PARTY_NUM:
                    PrintCalledPartyNumPar(&ie[i]);
                    break;
                case ISUP_PRM_CALLING_PARTY_CATEGORY:
                    PrintCallingPartyCategoryPar(&ie[i]);
                    break;
                case ISUP_PRM_CALLING_PARTY_NUM:
                    PrintCallingPartyNumPar(&ie[i]);
                    break;
                case ISUP_PRM_CAUSE_INDICATORS:
                    PrintCauseIndPar(&ie[i]);
                    break;
                case ISUP_PRM_CONNECTION_REQ:
                    PrintConnectRequestPar(&ie[i]);
                    break;
                case ISUP_PRM_CONTINUITY_INDICATORS:
                    PrintContinuityIndPar(&ie[i]);
                    break;
                case ISUP_PRM_CKT_GRP_SUPRVN_MT_IND:
                    PrintCircuitGrpSupervisionMsgTypIndPar(&ie[i]);
                    break;
                case ISUP_PRM_CKT_STATE_INDICATOR:
                    PrintCircuitStateIndPar(&ie[i]);
                    break;
                case ISUP_PRM_EOP:
                    PrintEOPPar(&ie[i]);
                    break;
                case ISUP_PRM_EVENT_INFO:
                    PrintEventInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_FWD_CALL_INDICATORS:
                    PrintForwCallIndPar(&ie[i]);
                    break;
                case ISUP_PRM_GENERIC_DIGITS:
                    PrintGenericDigitsPar(&ie[i]);
                    break;
                case ISUP_PRM_INFO_INDICATORS:
                    PrintInfoIndPar(&ie[i]);
                    break;
                case ISUP_PRM_INFO_REQ_INDICATORS:
                    PrintInfoReqIndPar(&ie[i]);
                    break;
                case ISUP_PRM_NATURE_CONN_INDICATORS:
                    PrintNatureOfConnectionIndPar(&ie[i]);
                    break;
                case ISUP_PRM_OPT_BKWD_CALL_INDICATORS:
                    PrintOptBackwardCallIndPar(&ie[i]);
                    break;
                case ISUP_PRM_ORIG_CALLED_NUM:
                    PrintOrigCalledNumPar(&ie[i]);
                    break;
                case ISUP_PRM_RANGE_STATUS:
                    PrintRangeAndStatusPar(&ie[i]);
                    break;
                case ISUP_PRM_REDIRECTING_NUM:
                    PrintRedirectingNumPar(&ie[i]);
                    break;
                case ISUP_PRM_REDIRECTION_INFO:
                    PrintRedirectionInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_SERVICE_ACTIVATION:
                    PrintServiceActivationPar(&ie[i]);
                    break;
                case ISUP_PRM_SUSP_RESUM_INDICATORS:
                    PrintSuspendResumeIndPar(&ie[i]);
                    break;
                case ISUP_PRM_TRANSIT_NTWK_SELECT:
                    PrintTransitNetworkSelectionPar(&ie[i]);
                    break;
                case ISUP_PRM_USER_SERVICE_INFO:
                    PrintUserServiceInfoPar(&ie[i]);
                    break;

                /* TODO: Add printing for routing label 
                case ISUP_PRM_ROUTING_LABEL:
                    Print(&ie[i]);
                    break;
                */

                case ISUP_PRM_MSG_IN_PAM:
                    PrintMessageInPAMPar(&ie[i]);
                    break;

/* ANSI Specific Parameters */
#if defined(ANSI)
                case ISUP_PRM_BUSINESS_GROUP:
                    PrintBusinessGrpPar(&ie[i]);
                    break;
                case ISUP_PRM_CARRIER_ID:
                    PrintCarrierIdPar(&ie[i]);
                    break;
                case ISUP_PRM_CARRIER_SELECTION_INFO:
                    PrintCarrierSelectionInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_CHARGE_NUMBER:
                    PrintChargeNumPar(&ie[i]);
                    break;
                case ISUP_PRM_CKT_VALIDATION_RESP:
                    PrintCircuitValRespIndPar(&ie[i]);
                    break;
                case ISUP_PRM_CKT_GRP_CHARACTERISTIC:
                    PrintCircuitGrpCharIndPar(&ie[i]);
                    break;
                case ISUP_PRM_CKT_IDENTIFICATION_NAME:
                    PrintCircuitIdNamePar(&ie[i]);
                    break;
                case ISUP_PRM_CLLI_CODE:
                    PrintCLLICodePar(&ie[i]);
                    break;
                case ISUP_PRM_EGRESS_SERVICE:
                    PrintEgressServicePar(&ie[i]);
                    break;
                case ISUP_PRM_GENERIC_ADDR:
                    PrintGenericAddrPar(&ie[i]);
                    break;
                case ISUP_PRM_JURISDICTION:
                    PrintJurisdictionPar(&ie[i]);
                    break;
                case ISUP_PRM_NTWK_TRANSPORT:
                    PrintNetworkTransportPar(&ie[i]);
                    break;
                case ISUP_PRM_NOTIFICATION:
                    PrintNotificationIndPar(&ie[i]);
                    break;
                case ISUP_PRM_ORIG_LINE_INFO:
                    PrintOrigLineInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_OUTGOING_TRUNK_GRP_NUM:
                    PrintOutgoingTrunkGrpNumPar(&ie[i]);
                    break;
                case ISUP_PRM_SERVICE_CODE:
                    PrintServiceCodePar(&ie[i]);
                    break;
                case ISUP_PRM_SPECIAL_PROCESS_REQUEST:
                    PrintSpecialProcessReqPar(&ie[i]);
                    break;
                case ISUP_PRM_TRANSACTION_REQUEST:
                    PrintTransactionReqPar(&ie[i]);
                    break;
#endif /* ANSI specific parameter Names */


/* ITU Specific Parameters */
#if defined(CCITT)
                case ISUP_PRM_ACCESS_DELIVERY_INFO:
                    PrintAccessDeliveryInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_CALL_DIVERSION_INFO:
                    PrintCallDiversionInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_CALL_HISTORY_INFO:
                    PrintCallHistoryInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_CONNECTED_NUM:
                    PrintConnectedNumPar(&ie[i]);
                    break;
                case ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE:
                    PrintClosedUserGrpIntrlckCodePar(&ie[i]);
                    break;
                case ISUP_PRM_ECHO_CTRL_INFO:
                    PrintEchoControlInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_NTWK_SPECIFIC_FACILITIES:
                    PrintNetworkSpecificFacilityPar(&ie[i]);
                    break;
                case ISUP_PRM_FACILITY_INDICATOR:
                    PrintFacilityIndPar(&ie[i]);
                    break;
                case ISUP_PRM_FREEPHONE_INDICATORS:
                    PrintAccessTransportPar(&ie[i]);
                    break;
                case ISUP_PRM_GENERIC_NOTIFICATION:
                    PrintGenericNotificationIndPar(&ie[i]);
                    break;
                case ISUP_PRM_GENERIC_NUM:
                    PrintGenericNumberPar(&ie[i]);
                    break;
                case ISUP_PRM_GENERIC_REF:
                    PrintGenericReferencPar(&ie[i]);
                    break;

#if 0
                /* The Hop Counter parameter format is not provided at the */
                /* current time.                                           */
                case ISUP_PRM_HOP_COUNTER:
                    PrintHopCounterPar(&ie[i]);
                    break;
#endif

                case ISUP_PRM_LOCATION_NUM:
                    PrintLocationNumberPar(&ie[i]);
                    break;

                case ISUP_PRM_MCID_REQ_INDICATOR:
                    PrintMCIDRequestIndPar(&ie[i]);
                    break;
                case ISUP_PRM_MCID_RESP_INDICATOR:
                    PrintMCIDResponseIndPar(&ie[i]);
                    break;

                case ISUP_PRM_MLPP_PRECEDENCE:
                    PrintMLPPPrecedencePar(&ie[i]);
                    break;

                case ISUP_PRM_MSG_COMPAT_INFO:
                    PrintMsgCompatibiltyInfoPar(&ie[i]);
                    break;

                case ISUP_PRM_OPT_FWD_CALL_INDICATORS:
                    PrintOptForwardCallIndPar(&ie[i]);
                    break;
                case ISUP_PRM_ORIG_ISC_PC:
                    PrintOrigISCPointCodePar(&ie[i]);
                    break;
                case ISUP_PRM_PARAM_COMPAT_INFO:
                    PrintParamCompInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_PROP_DELAY_COUNTER:
                    PrintPropDelayCounterPar(&ie[i]);
                    break;
                case ISUP_PRM_REDIRECTION_NUM:
                    PrintRedirectionNumPar(&ie[i]);
                    break;
                case ISUP_PRM_REDIRECTION_NUM_RESTRICT:
                    PrintRedirectionNumRestrictPar(&ie[i]);
                    break;
                case ISUP_PRM_REMOTE_OPS:
                    PrintRemoteOperationsPar(&ie[i]);
                    break;
                case ISUP_PRM_SIGNALLING_POINT_CODE:
                    PrintSignallingPointCodePar(&ie[i]);
                    break;
                case ISUP_PRM_SUBSEQUENT_NUM:
                    PrintSubsequentNumPar(&ie[i]);
                    break;
                case ISUP_PRM_TX_MEDIUM_REQMNT:
                    PrintTXMediumRequirementPar(&ie[i]);
                    break;
                case ISUP_PRM_TX_MEDIUM_REQMNT_PRIME:
                    PrintTXMediumRequirementPrimePar(&ie[i]);
                    break;
                case ISUP_PRM_TX_MEDIUM_USED:
                    PrintTXMediumUsedPar(&ie[i]);
                    break;
                case ISUP_PRM_USER_SERVICE_INFO_PRIME:
                    PrintUserServiceInfoPrimePar(&ie[i]);
                    break;
                case ISUP_PRM_USER_TELESERVICE_INFO:
                    PrintUserTeleserviceInfoPar(&ie[i]);
                    break;
                case ISUP_PRM_USER_TO_USER_INDICATORS:
                    PrintUserToUserIndPar(&ie[i]);
                    break;
                case ISUP_PRM_USER_TO_USER_INFO:
                    PrintUserToUserInfoPar(&ie[i]);
                    break;
#endif /* ITU specific parameter Names */

                default:
                    printf("ISUPTEST: Unrecognized Parameter Tag: 0x%02x \n",
                           ie[i].param_id);
                    result = !ITS_SUCCESS;
                }
            }
            printf("\n");
        }
        else
        {
            printf("ISUPTEST: Error, IE Array = NULL \n");
            result = !ITS_SUCCESS;
        }
    }
    else
    {
        printf("ISUPTEST: No IEs for this message \n");
    }
    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintMessageInPAMPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: MessageInPam \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("msgTypeInPAM: 0x%02x \n", ie->param_data.msgTypeInPAM);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintAccessDeliveryInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: AccessDeliveryInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("info: 0x%02x \n", ie->param_data.accessDeliveryInfo.info);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintAccessTransportPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int maxplen = 128;

    printf("\n");
    printf("Parameter: AccessTransport \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    if ((int)ie->param_length > maxplen)
    {
        printf("ISUPTEST: AccessTransport no. of info elements > %d \n",
               maxplen);
    }

    printf("acc_transport[%d] =", ie->param_length);
    for ( i = 0; i < ie->param_length; ++i )
    {
        printf(" 0x%02x", ie->param_data.accessTransport.acc_transport[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintAutoCongestionLvlPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: AutomaticCongestionLevel \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("level: 0x%02x \n", ie->param_data.autoCongestionLevel.level);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintBackwardCallIndPar(const ITS_ISUP_IE *ie)
{
    int i;
    int plen = 2;

    printf("\n");
    printf("Parameter: BackwardCallIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
   
    printf("bkwd_ci[%d]:", ie->param_length);
    for (i = 0; i < plen; ++i)
    {
        printf(" 0x%02x", ie->param_data.backwardCallIndicators.bkwd_ci[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintCallDiversionInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CallDiversionInfo \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("div_info: 0x%02x \n", ie->param_data.callDiversionInfo.div_info);
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintCallingPartyCategoryPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CallingPartyCategory \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("cat: 0x%02x \n", ie->param_data.callingPartyCategory.cat);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintCalledPartyNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: CalledPartyNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.calledPartyNum.addr_ind);
    printf("num_plan: 0x%02x \n", ie->param_data.calledPartyNum.num_plan);

    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i)
    {
        printf("0x%02x ", ie->param_data.calledPartyNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintCallHistoryInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: CallHistoryInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("delay[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.callHistoryInfo.prop_delay[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintCallingPartyNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: CallingPartyNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.callingPartyNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.callingPartyNum.subfields4);

    printf("dgts[%d]:", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i )
    {
        printf("0x%02x ", ie->param_data.callingPartyNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintCallRefPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nCIOctets;
    int nPCOctets = 3;

    printf("\n");
    printf("Parameter: CallReference \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

#ifdef ANSI
    nCIOctets = 3;
#endif
#ifdef CCITT
    nCIOctets = 2;
#endif

    printf("call_ident: ");
    for (i = 0; i < nCIOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.callRef.call_ident[i]);
    }
  
    printf("\n");
    printf("point_code: ");
    for (i = 0; i < nPCOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.callRef.point_code[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintCauseIndPar(const ITS_ISUP_IE *ie)
{
    int        i = 0;
    ITS_OCTET  nDiagnostics = 0x00;

    printf("\n");
    printf("Parameter: CauseIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("subfields4: 0x%02x \n", ie->param_data.causeIndicator.subfields4);
    printf("cause_val: 0x%02x \n", ie->param_data.causeIndicator.cause_val);

    nDiagnostics = ie->param_length - 2;
    printf("diagnostics[%d]: ", nDiagnostics);
    for (i = 0; i < nDiagnostics; ++i)
    {
        printf("0x%02x ", ie->param_data.causeIndicator.diagnostics[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef ANSI
void
PrintChargeNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: ChargeNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.chargeNumber.addr_ind);
    printf("num_plan: 0x%02x \n", ie->param_data.chargeNumber.num_plan);
  
    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i)
    {
        printf("0x%02x ", ie->param_data.chargeNumber.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintCircuitStateIndPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nStates = 0;

    printf("\n");
    printf("Parameter: CircuitStateIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("states[%d]: ", nStates);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitStateIndicators.states[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintClosedUserGrpIntrlckCodePar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nDigitsOctets = 2;
    int nCodeOctets = 2;

    printf("\n");
    printf("Parameter: ClosedUserGroupInterlockCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    if ((int)ie->param_length != nDigitsOctets + nCodeOctets)
    {
        printf("ISUPTEST: ClosedUserGroupInterlockCode plen != %d \n",
               nDigitsOctets + nCodeOctets);
    }

    printf("digits[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x2%x ", ie->param_data.interlockCode.digits[i]);
    }
    printf("\n");

    printf("code[%d]: ", nCodeOctets);
    for (i = 0; i < nCodeOctets; ++i)
    {
        printf("0x2%x ", ie->param_data.interlockCode.code[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintConnectedNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: ConnectedNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("addr_ind: 0x%02x \n", ie->param_data.connectedNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.connectedNum.subfields4);

    printf("dgts[%d]:", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i )
    {
        printf("0x%02x ", ie->param_data.connectedNum.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintConnectRequestPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nCIOctets = 3;
    int nPCOctets = 0;

    printf("\n");
    printf("Parameter: ConnectionRequest \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("call_ident[%d]: ", nCIOctets);
    for (i = 0; i < nCIOctets; ++ i)
    {
        printf("0x%02x ", ie->param_data.connectionRequest.call_ident[i]);
    }
    printf("\n");

#ifdef ANSI
    nPCOctets = 3;
#endif
#ifdef CCITT
    nPCOctets = 2;
#endif

    printf("point_code[%d]: ", nPCOctets);
    for (i = 0; i < nCIOctets; ++ i)
    {
        printf("0x%02x ", ie->param_data.connectionRequest.point_code[i]);
    }
    printf("\n");

    printf("protocol_class: 0x%02x \n",
           ie->param_data.connectionRequest.protocol_class);
    printf("credit: 0x%02x \n", ie->param_data.connectionRequest.credit);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintContinuityIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: ContinuityIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicators: 0x%02x \n",
           ie->param_data.continuityIndicators.indicators);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintEchoControlInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: EchoControlInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("info: 0x%02x \n", ie->param_data.echoControlInfo.info);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintEOPPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: EOP \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintEventInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: EventInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("evt_info: 0x%02x \n", ie->param_data.eventInfo.evt_info);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintFacilityIndPar( const ITS_ISUP_IE *ie )
{
    printf( "\n" );
    printf( "Parameter: FacilityIndicator \n" );
    printf( "Parameter Id: 0x%02x \n", ie->param_id );
    printf( "Length: %d octets \n", ie->param_length );
    printf( "fac_ind: 0x%02x\n", ie->param_data.facilityIndicator.fac_ind);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintForwCallIndPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int plen = 2;

    printf("\n");
    printf("Parameter: ForwardCallIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("fwd_ci[%d]: ", plen);
    for (i = 0; i < plen; ++i)
    {
        printf("0x%02x ", ie->param_data.forwardCallIndicators.fwd_ci[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef ANSI
void
PrintGenericAddrPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    
    printf("\n");
    printf("Parameter: GenericAddress \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.genericAddress.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.genericAddress.subfields4);
    printf("type_of_addr: 0x%02x \n",
           ie->param_data.genericAddress.type_of_addr);

    printf("dgts[%d]: ", ie->param_length - 3);
    for (i = 0; i < ie->param_length - 3; ++i )
    {
        printf("0x%02x ", ie->param_data.genericAddress.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintGenericDigitsPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: GenericDigits \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("type_scheme: 0x%02x \n", ie->param_data.genericDigits.type_scheme);
    
    printf("digits[%d]: ", ie->param_length - 1);
    for (i = 0; i < (ie->param_length - 1); ++i)
    {
        printf("0x%02x ", ie->param_data.genericDigits.digits[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintGenericNotificationIndPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: GenericNotificationIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("indicators[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ",
               ie->param_data.genericNotificationIndicator.indicators[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef CCITT
void
PrintGenericNumberPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nQOctets = 1;       /* qualifier octet len */
    int nNOctets = 1;       /* nature octet len */
    int nSOctets = 1;       /* subfields4 octet len */
    int nDigitsOctets = 0;  /* digits octet len */

    printf("\n");
    printf("Parameter: GenericNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("qualifier: 0x%02x \n", ie->param_data.genericNumber.qualifier);
    printf("nature: 0x%02x \n", ie->param_data.genericNumber.nature);
    printf("subfields4: 0x%02x \n", ie->param_data.genericNumber.subfields4);
    
    nDigitsOctets = (int)ie->param_length - nQOctets - nNOctets - nSOctets;

    printf("digits[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.genericDigits.digits[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
 *      In Q.763 this GenericReference is a reserved parameter.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintGenericReferencPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nQOctets = 1;       /* qualifier octet len */
    int nNOctets = 1;       /* nature octet len */
    int nSOctets = 1;       /* subfields4 octet len */
    int nDigitsOctets = 0;  /* digits octet len */
    int nQualOctets = 1;
    int nOctetsToPrint = 0;
    int entryIndex = 0;
    int nRefOctets = 0;
    int nLROctets = 

    printf("\n");
    printf("Parameter: GenericReference \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    nOctetsToPrint = ie->param_length;

    while (nOctetsToPrint > 0);
    {
        nRefOctets = 0;

        /* qualifier */
        printf("qualifier: 0x%02x \n",
               ie->param_data.genericReference.entries[entryIndex].qualifier);

        /* length of reference [1, 4] inclusive */
        printf("refCount: 0x%02x \n",
               ie->param_data.genericReference.entries[entryIndex].refCount);
        
        nRefOctets = 
            (int)ie->param_data.genericReference.entries[entryIndex].refCount;

        /* references */
        printf("refs[%d]: " , nRefOctets);
        for (i = 0; i < nRefOctets; ++i)
        {
            printf("0x%02x ",
                ie->param_data.genericReference.entries[entryIndex]. \
                refs[i]);
        }

        /* Read N octets from file */
        nOctetsToPrint -= nQualOctets - nLROctets - (int)nRefOctets;

        ++entryIndex;
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintInfoIndPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: InformationIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    
    printf("indics[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.informationIndicators.indics[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
PrintInfoReqIndPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: InformationRequestIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("indics[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ",
               ie->param_data.informationRequestIndicators.indics[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
#ifdef ANSI
void
PrintJurisdictionPar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: Jurisdiction \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("digits[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.jurisdiction.digits[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
 *      Same format for ANSI & CCITT.
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT)
void
PrintLocationNumberPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: LocationNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("addr_ind: 0x%02x \n", ie->param_data.locationNumber.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.locationNumber.subfields4);

    printf("dgts[%d]:", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i )
    {
        printf("0x%02x ", ie->param_data.locationNumber.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#if defined(CCITT)
void
PrintMCIDRequestIndPar( const ITS_ISUP_IE *ie )
{
    printf("\n");
    printf("Parameter: MCIDRequestIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("mcid_rqst_ind: %d octets \n",
           ie->param_data.mcidRequestIndicators.indics);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#if defined(CCITT)
void
PrintMCIDResponseIndPar( const ITS_ISUP_IE *ie )
{
    printf("\n");
    printf("Parameter: MCIDResponseIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("mcid_rspnse_ind: %d octets \n",
           ie->param_data.mcidResponseIndicators.indics);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
 *      Same format for ANSI & CCITT.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
PrintMLPPPrecedencePar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nNILen = 2;
    int nDomainLen = 3;

    printf("\n");
    printf("Parameter: MLPPPrecedence \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    
    printf("lfbLevel: 0x%02x \n", ie->param_data.mlppPrecedence.lfbLevel);

    printf("ni[%d]: ", nNILen);
    for (i = 0; i < nNILen; ++i)
    {
        printf("0x%02x ", ie->param_data.mlppPrecedence.ni[i]);
    }
    printf("\n");
    
    printf("ni[%d]: ", nDomainLen);
    for (i = 0; i < nDomainLen; ++i)
    {
        printf("0x%02x ", ie->param_data.mlppPrecedence.domain[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints
 *
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#if defined(CCITT)
void
PrintMsgCompatibiltyInfoPar( const ITS_ISUP_IE *ie )
{
    int i;

    printf( "\n" );
    printf( "Parameter: MessageCompatibilityInformation \n" );
    printf( "Parameter Id: 0x%02x \n", ie->param_id );
    printf( "Length: %d octets \n", ie->param_length );

    printf( "msg_compatibility_info:\n   " );
    for (i=0; i<128; i++)
    {
        printf( "0x%02x ",
                ie->param_data.msgCompatibilityInfo.data[i] );
        if ( i % 10 == 0 )
        {
            printf( "\n   " );
        }
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
 *      Same format for ANSI & CCITT.
 *
 *  See Also:
 ****************************************************************************/
void
PrintNatureOfConnectionIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: NatureOfConnectionIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("subfields4: 0x%02x \n",
           ie->param_data.connectionIndicator.subfields4);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#if defined(CCITT)
void
PrintNetworkSpecificFacilityPar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: NetworkSpecificFalicities \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("networkID_len: 0x%02x \n",
           ie->param_data.networkSpecificFacility.length_ofNtwrkId);
    printf("ntwrk_type_plan: 0x%02x \n",
           ie->param_data.networkSpecificFacility.ntwrk_type_plan);

    printf("networkID:\n");
    for (i=0; i < ie->param_data.networkSpecificFacility.length_ofNtwrkId; i++)
    {
        printf("0x%02x ", ie->param_data.networkSpecificFacility.ntwrk_id[i]);
        if (i % 10 == 0)
        {
            printf("\n   ");
        }
    }
    printf("\n");

    printf("ntwrk_facility:\n   ");
    for ( i=0; i<=128; i++ )
    {
        printf("0x%02x ",
               ie->param_data.networkSpecificFacility.ntwrk_facility[i]);
        if (i % 10 == 0)
        {
            printf("\n   ");
        }
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintNotificationIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: NotificationIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicator: 0x%02x \n", ie->param_data.notification.indicator);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintOptBackwardCallIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: OptionalBackwardCallIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("obkwd_ind: 0x%02x \n",
           ie->param_data.optBkwdCallIndicators.obkwd_ind);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintOptForwardCallIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: OptionalForwardCallIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indics: 0x%02x \n", ie->param_data.optFwdCallIndicators.indics);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintOrigCalledNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: OriginalCalledNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.origCalledNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.origCalledNum.subfields4);

    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < ie->param_length - 2; ++i)
    {
        printf("0x%02x ", ie->param_data.origCalledNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintOutgoingTrunkGrpNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nOctets = 0;

    printf("\n");
    printf("Parameter: OutgoingTrunkGroupNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    nOctets = (int)ie->param_length;

    printf("digits[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.outgoingTrunkNum.digits[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintPropDelayCounterPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: PropagationDelayCounter \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("delay[%d]: ", nOctets);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.propDelayCounter.delay[i]);
    }
    printf("\n");
}
#endif


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintRangeAndStatusPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nStatusOctets = 0;

    printf("\n");
    printf("Parameter: RangeAndStatus \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("range: 0x%02x \n", ie->param_data.rangeAndStatus.range);

#ifdef ANSI
    nStatusOctets = 4;
#endif
#ifdef CCITT
    nStatusOctets = 32;
#endif

    if (ie->param_length > 1)
    {
        printf("status[%d]: ", nStatusOctets);
        for (i = 0; i < ie->param_length - 1; ++i)
        {
            printf("0x%02x ", ie->param_data.rangeAndStatus.status[i]);
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintRedirectingNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: RedirectingNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.redirectingNum.addr_ind);
    printf("subfields4: 0x%02x \n", ie->param_data.redirectingNum.subfields4);

    printf("dgts[%d]: ", ie->param_length - 2);
    for (i = 0; i < (ie->param_length - 2); ++i)
    {
        printf("0x%02x ", ie->param_data.redirectingNum.dgts[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintRedirectionInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nOctets = 2;

    printf("\n");
    printf("Parameter: RedirectionInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    if ((int)ie->param_length != nOctets)
    {
        printf("ISUPTEST: RedirectionInformation plen != %d \n", nOctets);
    }

    printf("red_info[%d]: ", ie->param_length);
    for (i = 0; i < nOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.redirectionInfo.red_info[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintServiceActivationPar(const ITS_ISUP_IE *ie)
{
    int i;
    int maxNOctets = 0;

    printf("\n");
    printf("Parameter: ServiceActivation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

#ifdef ANSI
    maxNOctets  = 64;
#endif
#ifdef CCITT
    maxNOctets = 128;
#endif

    if (ie->param_length <= maxNOctets)
    {
        printf("data[%d]: ", ie->param_length);
        for (i = 0; i < ie->param_length; ++i)
        {
            printf("0x%02x ", ie->param_data.servactivation.data[i]);
        }
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintSignallingPointCodePar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: SignallingPointCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("data[%d]: ", (int)ie->param_length);
    for (i = 0; i < (int)ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.signallingPointCode.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintSuspendResumeIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: SuspendResumeIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("sus_res: 0x%02x \n", ie->param_data.suspendResumeInd.sus_res);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintTransactionReqPar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: TransactionRequest \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("transaction_id: %d, sizeof() = %d \n",
           ie->param_data.transactionRequest.transaction_id,
           sizeof(ie->param_data.transactionRequest.transaction_id));

    printf("SCCP_addr len: %d \n",
           ie->param_data.transactionRequest.SCCP_addr.len);

    printf("SCCP_addr data[%d]: ",
           ie->param_data.transactionRequest.SCCP_addr.len);
    for (i = 0; i < ie->param_data.transactionRequest.SCCP_addr.len; ++i)
    {
        printf("0x%02x ", ie->param_data.transactionRequest.SCCP_addr.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintTransitNetworkSelectionPar(const ITS_ISUP_IE *ie)
{
    int i = 0;

    printf("\n");
    printf("Parameter: TransitNetworkSelection \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("network: 0x%02x \n",
           ie->param_data.transitNetworkSelection.network);

#ifdef CCITT
    printf("network_id[%d]: ", ie->param_length - 1);
    for (i = 0; i < ie->param_length - 1; ++i)
    {
        printf("0x%02x ",
               ie->param_data.transitNetworkSelection.network_id[i]);
    }
    printf("\n");
#endif
#ifdef ANSI
    printf("digit2and1: 0x%02x \n",
           ie->param_data.transitNetworkSelection.digit2and1);
    printf("digit4and3: 0x%02x \n",
           ie->param_data.transitNetworkSelection.digit4and3);
    printf("code: 0x%02x \n", ie->param_data.transitNetworkSelection.code);
#endif
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintBusinessGrpPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nbgidOctets = 3;
    int nsgidOctets = 2;

    printf("\n");
    printf("Parameter: BusinessGroup\n");
    printf("Parameter Id: 0x%02x\n", ie->param_id);
    printf("Length: %d octets\n", ie->param_length);

    printf("party_selector: 0x%02x\n",
           ie->param_data.businessGroup.party_selector);
    
    printf("line_privileges: 0x%02x\n",
           ie->param_data.businessGroup.line_privileges);

    printf("business_group_ident[%d]: ", nbgidOctets);
    for (i = 0; i < nbgidOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.businessGroup.business_group_ident[i]);
    }
    printf("\n");

    printf("sub_group_ident[%d]: ", nsgidOctets);
    for (i = 0; i < nsgidOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.businessGroup.sub_group_ident[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintCarrierIdPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CarrierIdentification \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets\n", ie->param_length);

    printf("network: 0x%02x \n", ie->param_data.carrierIdentification.network);
    
    printf("digit2and1: 0x%02x \n",
           ie->param_data.carrierIdentification.digit2and1);
    
    printf("digit4and3: 0x%02x \n",
           ie->param_data.carrierIdentification.digit4and3);
}
#endif /* ANSI */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintCarrierSelectionInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CarrierSelectionInfo \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("information: 0x%02x \n",
           ie->param_data.carrierSelectionInfo.information);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintCircuitGrpCharIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CircuitGroupCharacteristicsIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicator: 0x%02x \n",
           ie->param_data.circuitGrpCharacteristic.indicator);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintCircuitGrpSupervisionMsgTypIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CircuitGroupSupervisionMessageTypeIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("sup_mt: 0x%02x \n", ie->param_data.supervisionMsgType.sup_mt);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintCircuitIdNamePar(const ITS_ISUP_IE *ie)
{
    int i;
    int nTrunkNumOctets = 4;
    int nOfficeAOctets = 11;
    int nOfficeZOctets = 11;

    printf("\n");
    printf("Parameter: CircuitIdentificationName \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("trunkNum[%d]: ", nTrunkNumOctets);
    for (i = 0; i < nTrunkNumOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitIdName.trunkNum[i]);
    }
    printf("\n");

    printf("clliCode_officeA[%d]:", nOfficeAOctets);
    for (i = 0; i < nOfficeAOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitIdName.clliCode_officeA[i]);
    }
    printf("\n");

    printf("clliCode_officeZ[%d]:", nOfficeZOctets);
    for (i = 0; i < nOfficeZOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.circuitIdName.clliCode_officeZ[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintCircuitValRespIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: CircuitValidationResponseIndicator \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("indicator: 0x%02x \n",
           ie->param_data.circuitValidationResponse.indicator);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintCLLICodePar(const ITS_ISUP_IE *ie)
{
    int i;
    int nTownOctets = 4;
    int nStateOctets = 2;
    int nBuildingOctets = 2;
    int nBuildingSubdivOctets = 3;

    printf("\n");
    printf("Parameter: CLLICode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("town[%d]: ", nTownOctets);
    for (i = 0; i < nTownOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.town[i]);
    }
    printf("\n");

    printf("state[%d]: ", nStateOctets);
    for (i = 0; i < nStateOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.state[i]);
    }
    printf("\n");

    printf("building[%d]: ", nBuildingOctets);
    for (i = 0; i < nBuildingOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.building[i]);
    }
    printf("\n");

    printf("buildingSubdiv[%d]: ", nBuildingSubdivOctets);
    for (i = 0; i < nBuildingSubdivOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.clliCode.buildingSubdiv[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintEgressServicePar(const ITS_ISUP_IE *ie)
{
    int i;

    printf("\n");
    printf("Parameter: EgressService \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("data[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.egressService.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintNetworkTransportPar(const ITS_ISUP_IE *ie)
{
    int i;
    int nOctets = 128;

    printf("\n");
    printf("Parameter: NetworkTransport \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    
    printf("data[%d]: ", ie->param_length);
    for (i = 0; i < ie->param_length; ++i)
    {
        printf("0x%02x ", ie->param_data.networkTransport.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintOrigISCPointCodePar(const ITS_ISUP_IE *ie)
{
    int i;
    int nPCOctets = 2;

    printf("\n");
    printf("Parameter: OriginatingISCPointCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);

    printf("data[%d]: ", nPCOctets);
    for (i = 0; i < nPCOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.origIscPointCode.data[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintOrigLineInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: OriginatingLineInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("data: 0x%02x \n", ie->param_data.origLineInfo.data);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintParamCompInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0, j = 0;
    int nInstOctets = 2;
    int moduloN = 3;      /* used to check maxplen divisible by 3 */

    /* Set IE information */
    printf("\n");
    printf("\n Parameter: ParameterCompatibilityInformation");
    printf("\n Parameter Id: 0x%02x", ie->param_id);
    printf("\n Length: %d octets", ie->param_length);

    for (i = 0; i < ((int)ie->param_length / moduloN); ++i)
    {
        /* upgraded parameter */
        printf("paramName: 0x%02x \n",
               ie->param_data.paramCompatInfo.param_info[i].paramName);

        /* instruction indicators */
        printf("instructions[%d]: ", nInstOctets);
        for (j = 0; j < nInstOctets; ++j)
        {
            printf("0x%02x ", ie->param_data.paramCompatInfo.param_info[i]. \
                   instructions[0]);
        }
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintRedirectionNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nDigitsOctets = 0;
    int aiLen = 1;
    int npLen = 1;

    printf("\n");
    printf("Parameter: RedirectionNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.redirectionNum.addr_ind);
    printf("num_plan: 0x%02x \n", ie->param_data.redirectionNum.num_plan);

    /* digits */
    nDigitsOctets = (int)ie->param_length - aiLen - npLen;

    printf("dgts[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.redirectionNum.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintRedirectionNumRestrictPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: RedirectionNumberRestriction \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("data: 0x%02x \n", ie->param_data.redirectionRestriction.bits);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintRemoteOperationsPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int maxNCptOctets = 128;
    int nProtProfileOctets = 1;
    int nCptOctets = 0;

    printf("\n");
    printf("Parameter: RemoteOperations \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("protocol_profile: 0x%02x \n",
           ie->param_data.remoteOperation.protocol_profile);

    nCptOctets = (int)ie->param_length - nProtProfileOctets;

    printf("components[%d]: ", nCptOctets);
    for (i = 0; i < nCptOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.remoteOperation.protocol_profile);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void
PrintServiceCodePar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: ServiceCode \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("code: 0x%02x \n", ie->param_data.serviceCode.code);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef ANSI
void PrintSpecialProcessReqPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: SpecialProcessingRequest \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("data: 0x%02x \n", ie->param_data.specialProcessing.data);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintSubsequentNumPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int aiLen = 1;
    int nDigitsOctets = 0;

    printf("\n");
    printf("Parameter: SubsequentNumber \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("addr_ind: 0x%02x \n", ie->param_data.subsequentNum.addr_ind);

    nDigitsOctets = (int)ie->param_length - aiLen;
    printf("dgts[%d]: ", nDigitsOctets);
    for (i = 0; i < nDigitsOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.subsequentNum.dgts[i]);
    }
    printf("\n");
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintTXMediumRequirementPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: TransmissionMediumRequirement \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("tmr: 0x%02x \n", ie->param_data.txMediumRequirement.tmr);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintTXMediumRequirementPrimePar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: TransmissionMediumRequirementPrime \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("tmr: 0x%02x \n", ie->param_data.txMediumRequirementPrime.tmr);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintTXMediumUsedPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: TransmissionMediumUsed \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("tmr: 0x%02x \n", ie->param_data.txMediumUsed.tmr);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
PrintUserServiceInfoPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: UserServiceInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("coding: 0x%02x \n", ie->param_data.userServiceInfo.coding);
    printf("trans_mode: 0x%02x \n", ie->param_data.userServiceInfo.trans_mode);
    printf("config: 0x%02x \n", ie->param_data.userServiceInfo.config);
    printf("symmetry: 0x%02x \n", ie->param_data.userServiceInfo.symmetry);

#ifdef ANSI
    printf("rate_multiplier: 0x%02x \n",
        ie->param_data.userServiceInfo.rate_multiplier);
#endif

    printf("layer1: 0x%02x \n", ie->param_data.userServiceInfo.layer1);

#ifdef ANSI
    printf("layer1_ext_user_rate: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_user_rate);
    
    printf("layer1_ext_rate_adaption_3b: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_rate_adaption_3b);

    printf("layer1_ext_parity: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_parity);

    printf("layer1_ext_modem_type: 0x%02x \n",
           ie->param_data.userServiceInfo.layer1_ext_modem_type);
#endif

    printf("layer2: 0x%02x \n", ie->param_data.userServiceInfo.layer2);
    printf("layer3: 0x%02x \n", ie->param_data.userServiceInfo.layer3);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintUserServiceInfoPrimePar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: UserServiceInformationPrime \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("coding: 0x%02x \n", ie->param_data.userServiceInfoPrime.coding);
    printf("trans_mode: 0x%02x \n",
           ie->param_data.userServiceInfoPrime.trans_mode);
    printf("config: 0x%02x \n", ie->param_data.userServiceInfoPrime.config);
    printf("symmetry: 0x%02x \n",
           ie->param_data.userServiceInfoPrime.symmetry);
    printf("layer1: 0x%02x \n", ie->param_data.userServiceInfoPrime.layer1);
    printf("layer2: 0x%02x \n", ie->param_data.userServiceInfoPrime.layer2);
    printf("layer3: 0x%02x \n", ie->param_data.userServiceInfoPrime.layer3);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#if defined(CCITT)
void
PrintUserTeleserviceInfoPar(const ITS_ISUP_IE *ie)
{
    printf( "\n" );
    printf( "Parameter: UserTeleserviceInfo \n" );
    printf( "Parameter Id: 0x%02x \n", ie->param_id );
    printf( "Length: %d octets \n", ie->param_length );

/* TBD: Fix me */
#if 0
    printf( "subfields3: 0x%02x\n",
             ie->param_data.userTeleServiceInfo.subfields3 );
    printf( "hlayer_char_id: 0x%02x\n",
             ie->param_data.userTeleServiceInfo.hlayer_char_id );
    printf( "ext_hlayer_char_id: 0x%02x\n",
             ie->param_data.userTeleServiceInfo.ext_hlayer_char_id );
#endif
}
#endif   /* CCITT */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintUserToUserIndPar(const ITS_ISUP_IE *ie)
{
    printf("\n");
    printf("Parameter: UserToUserIndicators \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("utu_ind: 0x%02x \n", ie->param_data.userToUserIndicators.utu_ind);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Prints 
 *      
 *  Input Parameters:
 *      ie - Pointer to an ISUP information element
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
#ifdef CCITT
void
PrintUserToUserInfoPar(const ITS_ISUP_IE *ie)
{
    int i = 0;
    int nProtDiscOctets = 1;

    printf("\n");
    printf("Parameter: UserToUserInformation \n");
    printf("Parameter Id: 0x%02x \n", ie->param_id);
    printf("Length: %d octets \n", ie->param_length);
    printf("prot_disc: 0x%02x \n", ie->param_data.userToUserInfo.prot_disc);

    printf("utu_info[%d]: ", ((int)ie->param_length - nProtDiscOctets));
    for (i = 0; i < (int)ie->param_length - nProtDiscOctets; ++i)
    {
        printf("0x%02x ", ie->param_data.userToUserInfo.utu_info[i]);
    }
    printf("\n");
}
#endif
