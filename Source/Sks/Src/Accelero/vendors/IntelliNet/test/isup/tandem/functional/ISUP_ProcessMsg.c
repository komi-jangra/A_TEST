/****************************************************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID:$Id: ISUP_ProcessMsg.c,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:19  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:18  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 1.1  2003/02/19 15:35:50  vnitin
 * LOG:Add functional tester for Tandem
 * LOG:
 * LOG:Revision 1.4  2003/01/31 14:09:32  ssingh
 * LOG:CCR handling in App. New CRI state handling in App.
 * LOG:And one Macro added for getting Message type out of received Event.
 * LOG:
 * LOG:Revision 1.3  2003/01/30 13:11:07  ssingh
 * LOG:VCIC related changes and CIC initialization as LBLOCKED.
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:47:42  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 * LOG:
 ****************************************************************************/
#include <its.h>
#include <its_ss7_trans.h>

#if defined(CCITT)
#include <itu/isup.h>
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#include <ansi/mtp3.h>
#endif

extern ITS_HANDLE Tandem_handle;

#define ISS7_Stack Tandem_handle



#include "ISUP_SendMsg.h"
#include "ISUP_PrintMsg.h"
#include "ISUP_ProcessMsg.h"

extern int GetOpcDpcInfo(OpcDpcInfo*);

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles ISUP STATUS/REQUEST Indications
 *      received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
 ****************************************************************************/
void 
ISUP_HandleIndicationRcvd (ITS_USHORT cic, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int i;

    printf("------------------------------------------------------\n");

    for (i = 0; i < ieCount; ++i)
    {
        switch ( (int)ies[i].param_id )
        {
        case ISUP_PRM_TIMEOUT_DATA:
            ISUP_ProcessTimeoutIndication(cic, event, ies[i]);
            break;

        case ISUP_PRM_ERROR_DATA:
            ISUP_ProcessErrorIndication(cic, event, ies[i]);
            break;

        case ISUP_PRM_INDICATION_DATA:
            ISUP_ProcessIndication(cic, event, ies[i]);
            break;

        case ISUP_PRM_CONFORMATION_DATA:
            ISUP_ProcessConformation(cic, event, ies[i]);
            break;

        default:
            break;
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function process indivisual STATUS/REQUEST Indications
 *      received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
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
 ****************************************************************************/
void 
ISUP_ProcessIndication (ITS_USHORT cic, ITS_EVENT *event, ITS_ISUP_IE ies)
{
    ITS_HDR    hdr;
    ITS_USHORT freeCIC;
    int        sendResult = 0;
    int        index = 0;
    int        i;
    ITS_BOOLEAN ret; 

    printf("Application: Indication %d rcvd for CIC %d\n", 
                                     ies.param_data.indData.indId, cic);
    switch ((int)ies.param_data.indData.indId)
    {
    case ITS_ISUP_CALL_FAILURE_IND:
    case ITS_ISUP_UCIC_CPCIDLE_STIND:
         /* IDLE FSM state and CPC state */
         ISUP_IdleCic(cic);
         break;

    case ITS_ISUP_CGB_REATTEMPT_RQIND:
         /* put remote block */
         /* change the FSM state */
         ret = ISUP_GetCicIndex (cic, &index);
         if (ret)
         {
             cicStatus[index].fsm_state = CPC_WAIT_IN_RLC;
         }

         /* get next free circuit */
         if( ISUP_GetFreeCircuit(cic, &freeCIC))
         {
             /* send the IAM on that circuit */
             hdr.context.cic = freeCIC;
             sendResult = TestSendIAMRequest(ISS7_Stack, &hdr);
             printf("\n(Application to ISUP Stack) Send IAM return result = %d\n", 
                                                        sendResult);
         }

         break;

    case ITS_ISUP_CGB_RBLK_STIND:
         /* put remote block */
         ISUP_SetRemoteBlock(cic);
         break;

    case ITS_ISUP_CGU_RUNBLK_STIND:
    case ITS_ISUP_RSC_RUNBLK_STIND:
    case ITS_ISUP_GRS_RUNBLK_STIND:
         /* Unblock cic remotely */
         ISUP_RemoveRemoteBlock (cic);
         break;

    case ITS_ISUP_GRS_CPCIDLE_STIND:
    case ITS_ISUP_RSC_CPCIDLE_STIND:
         /* FSM state IDLE
          * Remove Remote Block, if there
          */
         ISUP_IdleCic(cic);
         ISUP_RemoveRemoteBlock(cic);
         break;

    case ITS_ISUP_REL_REATTEMPT_IND:
         /* change the FSM state */
         ret = ISUP_GetCicIndex (cic, &index);
         cicStatus[index].fsm_state = CPC_WAIT_IN_RLC;

         /* get next free circuit */
         if( ISUP_GetFreeCircuit(cic, &freeCIC))
         {
             /* send the IAM on that circuit */
             hdr.context.cic = freeCIC;
             sendResult = TestSendIAMRequest(ISS7_Stack, &hdr);
             printf("\n(Application to ISUP Stack) Send IAM return result = %d\n", 
                                                        sendResult);
         }
         break;

    case ITS_ISUP_RSC_REATTEMPT_IND:
    case ITS_ISUP_RSC_REATTEMPT_RQIND:
    case ITS_ISUP_GRS_REATTEMPT_RQIND:
    case ITS_ISUP_UCIC_REATTEMPT_RQIND:
         /* get next free circuit */
         if( ISUP_GetFreeCircuit(cic, &freeCIC))
         {
             /* send the IAM on that circuit */
             hdr.context.cic = freeCIC;
             sendResult = TestSendIAMRequest(ISS7_Stack, &hdr);
             printf("\n(Application to ISUP Stack) Send IAM return result = %d\n",
                                                        sendResult);
         }

         /* Idle CPC state & Set fsm_state to IDLE */
         ISUP_IdleCic(cic);
         break;

    case ITS_ISUP_UCIC_LBLOCK_STIND:
         ISUP_RemoveRemoteBlock (cic);
         ISUP_SetLocalBlock (cic);
         ISUP_IdleCic(cic);
         break;

    case ITS_ISUP_IAM_REATTEMPT_IND:
         /* get next free circuit */
         if( ISUP_GetFreeCircuit(cic, &freeCIC))
         {
             /* send the IAM on that circuit */
             hdr.context.cic = freeCIC;
             sendResult = TestSendIAMRequest(ISS7_Stack, &hdr );
             printf("\n(Application to ISUP Stack) Send IAM return result = %d\n",
                                                        sendResult);
         }

         /* FSM state will be changed after receiving IAM from Stack */
         break;

    case ITS_ISUP_CGB_CPCIDLE_STIND:
         /* IDLE FSM state and CPC state */
         ISUP_IdleCic(cic);
         break;

    case ITS_ISUP_CGB_RESETRETRY_RQIND:
         /* Put remote Block; if not */
         ISUP_SetRemoteBlock (cic);

         /* Idle CPC state & Set fsm_state to IDLE */
         ISUP_IdleCic(cic);

         /* get next free circuit */
         if( ISUP_GetFreeCircuit(cic, &freeCIC))
         {
             /* send the IAM on that circuit */
             hdr.context.cic = freeCIC;
             sendResult = TestSendIAMRequest(ISS7_Stack, &hdr);
             printf("\n(Application to ISUP Stack) Send IAM return result = %d\n",
                                                        sendResult);
         }
         break;

    case ITS_ISUP_UBL_RUNBLOCK_IND:
    case ITS_ISUP_CQR_RUNBLOCKED_STIND:
         ISUP_RemoveRemoteBlock (cic);
         break;

    case ITS_ISUP_BLO_RBLOCK_IND:
    case ITS_ISUP_CQR_RBLOCKED_STIND:
         ISUP_SetRemoteBlock (cic);
         break;

    case ITS_ISUP_UBA_IND:
         ISUP_RemoveLocalBlock(cic);
         break;

    case ITS_ISUP_BLA_IND:
    case ITS_ISUP_CQR_LBLOCKED_STIND:
         ISUP_SetLocalBlock(cic);
         break;

    case ITS_ISUP_CQR_RELEASED_STIND:
    case ITS_ISUP_RLC_RELEASE_IND:
         /* Call dropped.
          * the cic_state will be changed after
          * receiving RLC in response to REL sent.
          * Change FSM state to Wait_in_RLC
          */
         ret = ISUP_GetCicIndex (cic, &index);
         cicStatus[index].fsm_state = CPC_WAIT_IN_RLC; 
         break;

    case ITS_ISUP_RLC_RESET_IND:
         /* Call dropped; RSC sent.
          * Change FSM state to Wait_in_RLC.
          */
         ret = ISUP_GetCicIndex (cic, &index);

         ISUP_CIC_SET_TRANSIENT(cicStatus[index].cic_state);
         cicStatus[index].fsm_state = CPC_WAIT_IN_RLC;
         break;

    case ITS_ISUP_UCIC_MAINT_RQIND:
         /* GRS/RSC send dorpped coz of
          * UCIC received for CICs in range;
          * Clear the Circuits
          */
         ret = ISUP_GetCicIndex (cic, &index);

         for(i=0; i< 24; i++)
         {
             if (cicStatus[index+i].cic_state != CKTS_TRANSIENT)
             {
                 break;
             }

             cicStatus[index + i].cic_state = CKTS_IDLE;

             printf("+++++++++++++++ %d  %d\n", 
                                              cicStatus[index+i].cic_num,
                                              cicStatus[index+i].cic_state);
         }
         break;

    case ITS_ISUP_CFN_ALERT_IND:
         printf("Indication : CFN message rcvd from Stack for CIC %d\n", cic);
         break;

    case ITS_ISUP_RMT_CONGLEVEL1_IND:
         printf("Application: ISUP Remote Congestion Level 1 Detected\n");
         printf("====  Cut down Traffic by 1/3 ====\n");
         break;

    case ITS_ISUP_RMT_CONGLEVEL2_IND:
         printf("Application: ISUP Remote Congestion Level 2 Detected\n");
         printf("====  Cut down Traffic by 2/3 ====\n");
         break;

    case ITS_ISUP_RMT_CONGLEVEL3_IND:
         printf("Application: ISUP Remote Congestion Level 3 Detected\n");
         printf("====  Cut down Conplete Traffic  ====\n");
         break;

    case ITS_ISUP_RMT_NOCONG_IND:
         printf("Application: ISUP Local Congestion ceased\n");
         printf("====  Resume Traffic Procedures ====\n");
         break;

    case ITS_ISUP_UCIC_GRSDROPPED_IND:
    case ITS_ISUP_RNS_MNSYS_IND:
    default:
         break;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function process indivisual conformation Indications
 *      received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
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
 ****************************************************************************/
void
ISUP_ProcessConformation (ITS_USHORT cic, ITS_EVENT *event, ITS_ISUP_IE ies)
{
    switch ((int)ies.param_data.cfmData.confId)
    {
    case ITS_ISUP_CIC_REL_CFM:
         /* Nothing to do...hehehehe */
         break;

    default:
         break;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function process error Indications received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
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
 ****************************************************************************/
void
ISUP_ProcessErrorIndication (ITS_USHORT cic, ITS_EVENT *event, ITS_ISUP_IE ies)
{
    switch ((int)ies.param_data.errorData.errorId)
    {
    case ITS_ISUP_CIC_BUSY_ERR:
         printf ("Message CIC BUSY Error Rcvd for CIC %d\n", cic);
         ISUP_IdleCic(cic);
         break;

    case ITS_ISUP_CIC_MNBLOCK_ERR:
         printf ("Message CIC BLOCKED Error Rcvd for CIC %d\n", cic);
         ISUP_IdleCic(cic);
         ISUP_SetRemoteBlock(cic);
         break;

    case ITS_ISUP_BAD_RNG_STATUS_ERR:
         break;

    default:
         break;
    }
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function process Timeout Indications received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
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
 ****************************************************************************/
void
ISUP_ProcessTimeoutIndication (ITS_USHORT cic, ITS_EVENT *event, ITS_ISUP_IE ies)
{
    printf("Application: Rcvd Timeout on CIC %d for Timer Id: %2d\n", 
            cic, ies.param_data.timerData.timerId);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles IAM message received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingIAMMsg( ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int i, j, index;
    int sendResult;
    ITS_BOOLEAN ret;
    ITS_BOOLEAN cotCheckReqFlag     = ITS_FALSE;
    ITS_BOOLEAN testCallFlag        = ITS_FALSE;
    ITS_BOOLEAN invalidDigit        = ITS_FALSE;
    ITS_OCTET   digit1 = 0x00;
    ITS_OCTET   digit2 = 0x00;

    ret = ISUP_GetCicIndex ((ITS_USHORT)hdr->context.cic, &index);

    if (ieCount != 0)
    {
       for (i = 0; i < ieCount; ++i)
       {

          switch ((int)ies[i].param_id)
          {
          case ISUP_PRM_CALLED_PARTY_NUM:
               /*Check for valid digits in Address Information field */
               for (j = 0; j < (ies[i].param_length - 2); ++j)
               {
                   digit1 = (ITS_OCTET)(ies[i].param_data.calledPartyNum.dgts[j]
                                        & 0x08);
                   digit2 = (ITS_OCTET)(ies[i].param_data.calledPartyNum.dgts[j]
                                        & 0x80);

                   if (digit1 == 0x08)
                   {
                       digit1 = (ITS_OCTET)
                                (ies[i].param_data.calledPartyNum.dgts[j] & 04);

                       if(digit1 == 0x04)
                       {
                          invalidDigit = ITS_TRUE;   
                          break;
                       }
                    
                       digit1 = (ITS_OCTET)
                                (ies[i].param_data.calledPartyNum.dgts[j] & 02);

                       if(digit1 == 0x02)
                       {
                          invalidDigit = ITS_TRUE;
                          break;
                       }
                   }

                   if (digit2 == 0x80)
                   {
                       digit2 = (ITS_OCTET)
                                (ies[i].param_data.calledPartyNum.dgts[j] & 40);

                       if(digit2 == 0x40)
                       {
                          invalidDigit = ITS_TRUE;
                          break;
                       }
                    
                       digit2 = (ITS_OCTET)
                                (ies[i].param_data.calledPartyNum.dgts[j] & 20);

                       if(digit2 == 0x20)
                       {
                          invalidDigit = ITS_TRUE;
                          break;
                       }
                    }
               }

               if(invalidDigit == ITS_TRUE)
               {
                  /*Send Release */
                  printf("------------------------------------------------------------\n");
                  printf("Application: Invalid Digit (Called Party Number) in rcvd IAM\n");
                  printf("------------------------------------------------------------\n");
                  sendResult = TestSendRELRequest(ISS7_Stack, hdr);
                  printf("\n(Application to ISUP Stack) Send REL return result = %d\n",
                                                                    sendResult);
                  cicStatus[index].fsm_state = CPC_WAIT_IN_RLC;
                  return;
               }
               break;

          case ISUP_PRM_USER_SERVICE_INFO:
               break;           

          case ISUP_PRM_CALLING_PARTY_CATEGORY:
               if (ies[i].param_data.callingPartyCategory.cat ==
                                                    CGP_CAT_TEST_CALL)
               {
                  testCallFlag = ITS_TRUE;
               }
               break;
          
          case ISUP_PRM_NATURE_CONN_INDICATORS:
               switch (ies[i].param_data.connectionIndicator.subfields4 >> 2
                       & 0x03U)
               {
               case NCI_CHECK_CKT_REQUIRED:
               case NCI_CHECKED_PREV_CKT:
                    cotCheckReqFlag = ITS_TRUE;
                    break;

               case NCI_CHECK_NOT_REQUIRED:
               default:
                    cotCheckReqFlag = ITS_FALSE; 
                    break;
               }
               break;

          default:
               break;
          }

       }
    }

    if(testCallFlag != ITS_TRUE)
    {
       /* remove remote block, if any */
       ISUP_CIC_REMOVE_REM_BLOCK(cicStatus[index].cic_state);
    }
    else
    {
       printf("-----------------------------------------------------\n");
       printf("Application : Test Call rcvd from Network for CIC: %d\n", 
                                               cicStatus[index].cic_num);
       printf("-----------------------------------------------------\n");
    }

    if(cotCheckReqFlag == ITS_TRUE)
    {
       printf("-----------------------------------------------------\n");
       printf("Application : IAM-COT ( CHECK LOOP CONNECT )\n");
       printf("-----------------------------------------------------\n");

       /* change FSM state to WAIT_IN_COT */
       cicStatus[index].fsm_state = CPC_WAIT_IN_COT;
    }
    else
    {
       /* No COT test required */
       sendResult = TestSendACMRequest(ISS7_Stack, hdr);
       printf("\n(Application to ISUP Stack) Send ACM return result = %d\n", 
                                                  sendResult);

       cicStatus[index].fsm_state = CPC_SENT_OUT_ACM;

       sendResult = TestSendANMRequest(ISS7_Stack, hdr);
       printf("\n(Application to ISUP Stack) Send ANM return result = %d\n", 
                                                      sendResult);

       cicStatus[index].fsm_state = CPC_SENT_OUT_ANM;
    }

    ISUP_CIC_SET_CALL(cicStatus[index].cic_state, CKTS_IN_CTK_BUSY);

    printf("Application: FSM state %d CIC State %d\n", 
                                   cicStatus[index].fsm_state,
                                   cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles COT message received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingCOTMsg( ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int i, index;
    int sendResult;
    ITS_BOOLEAN ret;

    ret = ISUP_GetCicIndex ((ITS_USHORT)hdr->context.cic, &index);

    if (ieCount != 0)
    {
       for (i = 0; i < ieCount; ++i)
       {
          if ((int)ies[i].param_id == ISUP_PRM_CONTINUITY_INDICATORS)
          {
            if ((ies[i].param_data.continuityIndicators.indicators & 0x01)
                 != 0)
            {
               sendResult = TestSendACMRequest(ISS7_Stack, hdr );
               printf("\n(Application to ISUP Stack) Send ACM return result = %d\n",
                                                          sendResult);

               cicStatus[index].fsm_state = CPC_SENT_OUT_ACM;

               sendResult = TestSendANMRequest(ISS7_Stack, hdr );
               printf("\n(Application to ISUP Stack) Send ANM return result = %d\n",
                                                          sendResult);

               cicStatus[index].fsm_state = CPC_SENT_OUT_ANM;
            }
            else
            {
               printf("Application: COT(Failure) rcvd from Stack for CIC: %d\n",
                                                 cicStatus[index].cic_num);
            }
            printf("Application: FSM state %d CIC State %d\n", 
                                                    cicStatus[index].fsm_state,
                                                    cicStatus[index].cic_state);
            break;
          }
       }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles ACM message received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingACMMsg( ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int index;
    ITS_BOOLEAN ret;

    ret = ISUP_GetCicIndex ((ITS_USHORT)hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_WAIT_IN_ANM;

    printf("Application: FSM state %d CIC State %d\n", 
                                             cicStatus[index].fsm_state,
                                             cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles ANM message received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingANMMsg( ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int index;
    ITS_BOOLEAN ret;

    ret = ISUP_GetCicIndex ((ITS_USHORT)hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_RCVD_IN_ANM;

    printf("Application: FSM state %d CIC State %d\n", 
                                             cicStatus[index].fsm_state,
                                             cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles SUS message received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingSUSMsg( ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int index;
    ITS_BOOLEAN ret;

    ret = ISUP_GetCicIndex ((ITS_USHORT)hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_WAIT_IN_RES;

    printf("Application: FSM state %d CIC State %d\n", 
                                             cicStatus[index].fsm_state,
                                             cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles RES message received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingRESMsg( ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int index;
    ITS_BOOLEAN ret;

    ret = ISUP_GetCicIndex ((ITS_USHORT)hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_RCVD_IN_ANM;

    printf("Application: FSM state %d CIC State %d\n", 
                                             cicStatus[index].fsm_state,
                                             cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles CVT message received from STACK.
 *
 *  Input Parameters:
 *      hdr    : ITS header for CIC reference
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingCVTMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int  sendResult = 0;

    sendResult = TestSendCVRRequest(ISS7_Stack, hdr);
    printf("\n(Application to ISUP Stack) Send CVR return result = %d\n",
                                               sendResult);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles CVR message received from STACK.
 *
 *  Input Parameters:
 *      hdr    : ITS header for CIC reference
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingCVRMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int i;

    if (ieCount != 0)
    {
       for (i = 0; i < ieCount; ++i)
       {
          if ((int)ies[i].param_id == ISUP_PRM_CKT_VALIDATION_RESP)
          {
            if (ies[i].param_data.circuitValidationResponse.indicator != 0)
            {
              printf("Application: CVR(Failure) rcvd from Stack for CIC %d\n", 
                                                             hdr->context.cic);
            }
          }
       }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles REL message received from STACK.
 *
 *  Input Parameters:
 *      hdr    : ITS header for CIC reference
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingRELMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int         index;
    ITS_BOOLEAN ret;
    int         sendResult = 0;

    ret = ISUP_GetCicIndex ((ITS_USHORT)hdr->context.cic, &index);

    sendResult = TestSendRLCRequest(ISS7_Stack, hdr);
    printf("\n(Application to ISUP Stack) Send RLC return result = %d\n",
                                               sendResult);

    ISUP_CIC_SET_CALL(cicStatus[index].cic_state, CKTS_IDLE_CTK);
    
    cicStatus[index].fsm_state = CPC_IDLE;

    printf("Application: FSM state %d CIC State %d\n", 
                                             cicStatus[index].fsm_state,
                                             cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles CCR message received from STACK.
 *
 *  Input Parameters:
 *      hdr     : ITS header for CIC reference
 *      event   : ISUP event
 *      ies     : Array of IEs in the event
 *      ieCount : IE count
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
ISUP_HandleIncomingCCRMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                           ITS_ISUP_IE *ies, int ieCount)
{
    int  sendResult = 0;

    printf("-----------------------------------------------------\n");
    printf("Application : CHECK LOOP CONNECT\n");
    printf("-----------------------------------------------------\n");

    sendResult = TestSendLPARequest(ISS7_Stack, hdr);
    printf("\n(Application to ISUP Stack) Send LPA return result = %d\n",
                                               sendResult);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function process Callp Messages before Sending it to Stack.
 *
 *  Input Parameters:
 *      isupMsgType  : Message Type
 *      startCic     : Message CIC
 *      ies          : Array of IEs
 *      ieCount      : Number of IEs
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
 ****************************************************************************/
void
ISUP_HandleOutgoingCPCMsg (ITS_OCTET isupMsgType, ITS_USHORT cic,
                 ITS_ISUP_IE *ies, int ieCount)
{
    int i, index, result = 0;
    ITS_BOOLEAN ret = 0;

    ITS_BOOLEAN testCallFlag = ITS_FALSE;
    ITS_BOOLEAN cotCheckReqFlag = ITS_FALSE;
    static      OpcDpcInfo info;
    ITS_OCTET   cicstate;
    ITS_USHORT  vcic;

    GetOpcDpcInfo(&info);

    ret = ISUP_GetCicIndex (cic, &index);

    switch (isupMsgType)
    {
    case ISUP_MSG_IAM:
       if (ieCount != 0)
       {
          for (i = 0; i < ieCount; ++i)
          {
             switch ((int)ies[i].param_id)
             {
             case ISUP_PRM_CALLING_PARTY_CATEGORY:
                if (ies[i].param_data.callingPartyCategory.cat ==
                                                       CGP_CAT_TEST_CALL)
                {
                    testCallFlag = ITS_TRUE;
                }
                break;

             case ISUP_PRM_NATURE_CONN_INDICATORS:
                switch (ies[i].param_data.connectionIndicator.subfields4 >> 2
                    & 0x03U)
                {
                case NCI_CHECK_CKT_REQUIRED:
                case NCI_CHECKED_PREV_CKT:
                     cotCheckReqFlag = ITS_TRUE;
                     break;

                case NCI_CHECK_NOT_REQUIRED:
                default:
                     cotCheckReqFlag = ITS_FALSE;
                     break;
                }
                break;

             default:
                break;
             }
          }

          result = ISUP_ReserveCIC(ISS7_Stack,(ITS_OCTET) info.sio,
                           (ITS_UINT) info.opc, (ITS_UINT) info.dpc,
                           (ITS_USHORT) cic, (ITS_OCTET*) &cicstate,
                           (ITS_CTXT*) &vcic);

          if (result != ITS_SUCCESS)
          {
              printf("\nApplication: ValidateCIC return value = %d\n", result);

              if (result == ITS_ECICBLOCK)
              {
                 if (testCallFlag == ITS_TRUE)
                 {
                    printf("-----------------------------------------------\n");
                    printf("Application: Test Call Attempted on CIC: %d\n",cic);
                    printf("-----------------------------------------------\n");
                  }
                  else
                  {
                    if (ISUP_CIC_STATE_GET_BA(cicstate) == CKTS_LBLOCKED) 
                    {
                       /* remove Local Block */
                       ISUP_CIC_REMOVE_LOC_BLOCK (cicStatus[index].cic_state);
                    }
                  }
              }
          }

          if (cotCheckReqFlag == ITS_TRUE)
          {
             /* change state to wait_in_acm */
             cicStatus[index].fsm_state = CPC_WAIT_IN_ACM;
          }
          else
          {
              /* change state to wait_cot_reports */
              cicStatus[index].fsm_state = CPC_WAIT_COT_REPORT;
          }

          ISUP_CIC_SET_CALL(cicStatus[index].cic_state, CKTS_OUT_CTK_BUSY);
       }

       break;

    case ISUP_MSG_COT:
       if (ieCount != 0)
       {
          for (i = 0; i < ieCount; ++i)
          {
              if ((int)ies[i].param_id == ISUP_PRM_CONTINUITY_INDICATORS)
              {
                if ((ies[i].param_data.continuityIndicators.indicators & 0x01)
                     != 0)
                {
                   /* change state to wait_in_acm */
                   cicStatus[index].fsm_state = CPC_WAIT_IN_ACM;
                }
                break;
            }
          }
       }

       break;

    case ISUP_MSG_ACM:
       /* change state to sent_out_acm */
       cicStatus[index].fsm_state = CPC_WAIT_COT_REPORT;

       break;

    case ISUP_MSG_ANM:
       /* change state to sent_out_anm */
       cicStatus[index].fsm_state = CPC_SENT_OUT_ANM;

       break;

    case ISUP_MSG_SUS:
       /* change state to wait_out_res */
       cicStatus[index].fsm_state = CPC_WAIT_OUT_RES;

       break;

    case ISUP_MSG_RES:
       /* change state to sent_out_anm */
       cicStatus[index].fsm_state = CPC_SENT_OUT_ANM;

       break;

    case ISUP_MSG_REL:
       /* change state to wait_in_rlc */
       cicStatus[index].fsm_state = CPC_WAIT_IN_RLC;

       break;

    default:
       break;
    }
    printf("Application: FSM state %d CIC State %d\n", 
                                             cicStatus[index].fsm_state,
                                             cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets Circuits transient before sending GRS.
 *
 *  Input Parameters:
 *      startCic     : Message CIC
 *      ies          : Array of IEs
 *      ieCount      : Number of IEs
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
 ****************************************************************************/
void
ISUP_HandleOutgoingGRSMsg(ITS_USHORT startCic, ITS_ISUP_IE *ies, int ieCount)
{
    int i, j;
    int index; 
    ITS_OCTET range;
    ITS_BOOLEAN ret = ITS_FALSE;

    ret = ISUP_GetCicIndex (startCic, &index);

    if( ret == ITS_TRUE)
    {
        for (i = 1; i < ieCount; i++)
        {
            if(ies[i].param_id == ISUP_PRM_RANGE_STATUS)
            {
               if (ies[i].param_data.rangeAndStatus.range != 0)
               {
                  range = ies[i].param_data.rangeAndStatus.range;
               }
               else
               {
                  range = 23;
               }

               for(j = index; j <= index+range; j++)
               {
                   ISUP_CIC_SET_TRANSIENT(cicStatus[j].cic_state);
                   cicStatus[j].fsm_state = CPC_WAIT_IN_RLC;
 
                   printf("CIC State : [%d]=%d | CIC FSM : %d\n", 
                                j, cicStatus[j].cic_state, cicStatus[j].fsm_state);
               }
            }
            break;
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function remove set Circuit transient before sending RSC.
 *
 *  Input Parameters:
 *      cic     : Message CIC
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
 ****************************************************************************/
void
ISUP_HandleOutgoingRSCMsg(ITS_USHORT cic)
{
     int index;
     ITS_BOOLEAN ret = 0;

     ret = ISUP_GetCicIndex (cic, &index);

     if (ret == ITS_TRUE)
     {
         ISUP_CIC_SET_TRANSIENT(cicStatus[index].cic_state);
         cicStatus[index].fsm_state = CPC_WAIT_IN_RLC;

         printf("Appication: FSM State %d CIC State [%d]=%d\n", 
                                       cicStatus[index].fsm_state, index, 
                                              cicStatus[index].cic_state);
     }
}
