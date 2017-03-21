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
 * ID:$Id: ISUP_ProcessMsg.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:24:56  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:14  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:05  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 8.8  2005/03/21 13:54:16  cvsadmin
 * LOG:PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG:Revision 1.5.2.3  2003/05/09 05:30:45  ssingh
 * LOG:Changes back ported from current to 6.3
 * LOG:
 * LOG:Revision 8.6  2003/04/29 07:00:01  ssingh
 * LOG:Changed Submitted for test-application core-dump,
 * LOG:while sending IAM on not configured CIC.
 * LOG:
 * LOG:Revision 8.5  2003/04/17 11:29:39  ssingh
 * LOG:Modified printf(); more informations.
 * LOG:
 * LOG:Revision 8.4  2003/04/04 05:22:53  ssingh
 * LOG:Conformation Handling removed from App as now No conformation.
 * LOG:
 * LOG:Revision 8.3  2003/03/28 07:35:58  ssingh
 * LOG:Removed Extra reference of accessing STACK functionality.
 * LOG:Peg things removed. Will be accessed through MML.
 * LOG:
 * LOG:Revision 8.2  2003/02/27 06:13:35  akumar
 * LOG:Added ITU Variant
 * LOG:
 * LOG:Revision 8.1  2003/02/13 17:44:31  yranade
 * LOG:Begin PR6.4
 * LOG:
 * LOG:Revision 1.5  2003/02/07 05:15:28  ssingh
 * LOG:ValidateCIC replaced by ReserverCIC.
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
#include <isup_variants.h>
#include <itu/isup.h>
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#include <ansi/mtp3.h>
#endif

#if defined(CCITT)
#define ISS7_Stack ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack ISS7_ANSI_Stack
#endif

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
    int i;
    ITS_BOOLEAN ret; 

    printf("Application: %s : line %d : Indication %d rcvd for CIC %d\n", 
                        __FILE__, __LINE__, ies.param_data.indData.indId, cic);

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

#if defined(ANSI)
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

             printf("Application: %s : line %d : Cic %d State %d\n", 
                     __FILE__, __LINE__, cicStatus[index+i].cic_num, 
                                         cicStatus[index+i].cic_state);
         }
         break;
#endif /* ANSI */

    case ITS_ISUP_CFN_ALERT_IND:
         printf("Application: CFN message rcvd from Netwrok for CIC %d\n", cic);
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
         break;

    case ITS_ISUP_SGM_WAIT_IND:

         /* Call Dropped, as Stack is still waiting for
          * SGM Message from Remote End
          */
         printf("Stack Waiting for SGM message from L3, Message Discarded \n");

         /* Idle CPC state & Set fsm_state to IDLE */
         ISUP_IdleCic(cic);
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
         printf ("Application: Message CIC BUSY Error Rcvd for CIC %d\n", cic);
         ISUP_IdleCic(cic);
         break;

    case ITS_ISUP_CIC_MNBLOCK_ERR:
         printf ("Application: Message CIC BLOCKED Error Rcvd for CIC %d\n", cic);
         ISUP_IdleCic(cic);
         ISUP_SetRemoteBlock(cic);
         break;

    case ITS_ISUP_BAD_RNG_STATUS_ERR:
         break;

    case ITS_EDESTPROHIBIT:
         printf ("Application: Message Destination Prohibit Error Rcvd for CIC %d\n", cic);

         /*
          * Application Writer should note here that he should 
          * start sending UPT here and Mark the concerned
          * User Part Unavailable
          */
         printf ("****NOTE, Need to Send UPT HERE***** \n");
         ISUP_IdleCic(cic);
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
    printf("Application: %s : line %d : Rcvd Timeout on CIC %d for Timer Id: %2d\n", 
            __FILE__, __LINE__, cic, ies.param_data.timerData.timerId);
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

    ret = ISUP_GetCicIndex (hdr->context.cic, &index);

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
                   digit1 = ies[i].param_data.calledPartyNum.dgts[j] & 0x08;
                   digit2 = ies[i].param_data.calledPartyNum.dgts[j] & 0x80;

                   if (digit1 == 0x08)
                   {
                       digit1 = ies[i].param_data.calledPartyNum.dgts[j] & 04;

                       if(digit1 == 0x04)
                       {
                          invalidDigit = ITS_TRUE;   
                          break;
                       }
                    
                       digit1 = ies[i].param_data.calledPartyNum.dgts[j] & 02;

                       if(digit1 == 0x02)
                       {
                          invalidDigit = ITS_TRUE;
                          break;
                       }
                   }

                   if (digit2 == 0x80)
                   {
                       digit2 = ies[i].param_data.calledPartyNum.dgts[j] & 40;

                       if(digit2 == 0x40)
                       {
                          invalidDigit = ITS_TRUE;
                          break;
                       }
                    
                       digit2 = ies[i].param_data.calledPartyNum.dgts[j] & 20;

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
#if defined(ANSI)
       ISUP_CIC_REMOVE_REM_BLOCK(cicStatus[index].cic_state);
#elif defined(CCITT)
       cicStatus[index].cic_state &= 0xFDU;
       cicStatus[index].cic_state &= 0xDFU;
#endif
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

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                       __FILE__, __LINE__, cicStatus[index].cic_num,
             cicStatus[index].fsm_state, cicStatus[index].cic_state);
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

    ret = ISUP_GetCicIndex (hdr->context.cic, &index);

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
            printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                              __FILE__, __LINE__, cicStatus[index].cic_num,
                        cicStatus[index].fsm_state, cicStatus[index].cic_state);
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

    ret = ISUP_GetCicIndex (hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_WAIT_IN_ANM;

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                            __FILE__, __LINE__, cicStatus[index].cic_num,
                  cicStatus[index].fsm_state, cicStatus[index].cic_state);
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

    ret = ISUP_GetCicIndex (hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_RCVD_IN_ANM;

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                              __FILE__, __LINE__, cicStatus[index].cic_num,
                   cicStatus[index].fsm_state, cicStatus[index].cic_state);
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

    ret = ISUP_GetCicIndex (hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_WAIT_IN_RES;

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                              __FILE__, __LINE__, cicStatus[index].cic_num,
                   cicStatus[index].fsm_state, cicStatus[index].cic_state);
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

    ret = ISUP_GetCicIndex (hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_RCVD_IN_ANM;

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                            __FILE__, __LINE__, cicStatus[index].cic_num,
                 cicStatus[index].fsm_state, cicStatus[index].cic_state);
}

#if defined(ANSI)
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
              printf("Application: %s : line %d : CVR(Failure) rcvd from Stack for CIC %d\n", 
                                      __FILE__, __LINE__, hdr->context.cic);
            }
          }
       }
    }
}
#endif /* ANSI */

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

    ret = ISUP_GetCicIndex (hdr->context.cic, &index);

    sendResult = TestSendRLCRequest(ISS7_Stack, hdr);
    printf("\n(Application to ISUP Stack) Send RLC return result = %d\n",
                                               sendResult);

    ISUP_CIC_SET_CALL(cicStatus[index].cic_state, CKTS_IDLE_CTK);
    
    cicStatus[index].fsm_state = CPC_IDLE;

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                             __FILE__, __LINE__, cicStatus[index].cic_num,
                  cicStatus[index].fsm_state, cicStatus[index].cic_state);
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

#if defined(ANSI)
    sendResult = TestSendLPARequest(ISS7_Stack, hdr);
#elif defined(CCITT)
    /**** Wait for REL from the Remote end *****/
#endif 
    printf("\n(Application to ISUP Stack) Send LPA return result = %d\n",
                                               sendResult);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles CON message received from STACK.
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
ISUP_HandleIncomingCONMsg (ITS_HDR *hdr, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int  index = 0;
    ISUP_GetCicIndex (hdr->context.cic, &index);

    cicStatus[index].fsm_state = CPC_RCVD_IN_ANM;

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                              __FILE__, __LINE__, cicStatus[index].cic_num,
                    cicStatus[index].fsm_state, cicStatus[index].cic_state);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles BLO message received from STACK.
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
ISUP_HandleIncomingBLOMsg (ITS_HDR *hdr, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int  index = 0;
    ISUP_GetCicIndex (hdr->context.cic, &index);

    /* Handle BLO message received from STACK */
    ISUP_SetRemoteBlock(index);

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                               __FILE__, __LINE__, cicStatus[index].cic_num,
                     cicStatus[index].fsm_state, cicStatus[index].cic_state);

    /* Send BLA Message in response to
     * BLO
     */
    TestSendBLARequest(ISS7_Stack, hdr);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles UBL message received from STACK.
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
ISUP_HandleIncomingUBLMsg (ITS_HDR *hdr, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int  index = 0;
    ISUP_GetCicIndex (hdr->context.cic, &index);

    /* Handle UBL message received from STACK */
    ISUP_RemoveRemoteBlock(index);

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                              __FILE__, __LINE__, cicStatus[index].cic_num,
                    cicStatus[index].fsm_state, cicStatus[index].cic_state);

    /* Send UBA Message in response to
     * UBL
     */
    TestSendUBARequest(ISS7_Stack, hdr);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles RSC message received from STACK.
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
ISUP_HandleIncomingRSCMsg (ITS_HDR *hdr, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int  index = 0;
    ISUP_GetCicIndex (hdr->context.cic, &index);

    /* Handle RSC message received from STACK */

    /* Unblock cic remotely */
    ISUP_RemoveRemoteBlock (index);

    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                              __FILE__, __LINE__, cicStatus[index].cic_num,
                   cicStatus[index].fsm_state, cicStatus[index].cic_state);

    /* Send RLC Message in response to
     * RSC
     */
    TestSendRLCRequest(ISS7_Stack, hdr);
}

#if defined(CCITT)
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles GRS message received from STACK.
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
ISUP_HandleIncomingGRSMsg (ITS_HDR *hdr, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int  index = 0, i = 0, j = 0, indx = 0, offset = 0;
    ITS_OCTET range = 0, sio = 0;
    ISUP_RANGE_AND_STATUS rs_ie;
    ITS_OCTET gra_status[4];
    MTP3_HEADER header;
    ITS_UINT dpc = 0, opc = 0;
    int r_ieCount = 0;
    ITS_ISUP_IE r_ies[2];

    ISUP_GetCicIndex (hdr->context.cic, &index);

    /* Handle GRS message received from STACK */

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
            range = ies[i].param_data.rangeAndStatus.range;
        }
    }

    for (i = index; i <= range; i++)
    {
        /* Unblock cic remotely */
#if defined(ANSI)
        ISUP_CIC_REMOVE_REM_BLOCK (cicStatus[i].cic_state);
#elif defined(CCITT)
        cicStatus[i].cic_state &= 0xFDU;
#endif
        cicStatus[i].fsm_state = CPC_IDLE;

        printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                                       __FILE__, __LINE__, cicStatus[i].cic_num,
                                cicStatus[i].fsm_state, cicStatus[i].cic_state);
    }

    /* Send GRA Message in response to
     * GRS
     */

    memset ((char *)gra_status, 0, 4);

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (8*i+j <= range)
            {
                if (ISUP_CIC_STATE_GET_BA(cicStatus[index++].cic_state))
                {
                    gra_status[i] |= 1 << j;
                }
            }
        }
    }
    
    memcpy(rs_ie.status, gra_status, 4);

    /* Encode the params for GRA msg to be sent. */
    memset((char *)&r_ies, 0, sizeof(ITS_ISUP_IE) * 2);

    /* Fill in range and status parameter. */
    r_ies[indx].param_id = ISUP_PRM_RANGE_STATUS;
    r_ies[indx].param_data.rangeAndStatus.range = range;

    memcpy(r_ies[indx].param_data.rangeAndStatus.status, rs_ie.status, 4);
    r_ies[indx].param_length = 5;
    indx++;

    /* Format MTP3_HEADER type parameter */

    offset = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* Getting the Header From Event */
    memset((char*)&header, 0, sizeof(MTP3_HEADER));
    memcpy(&header, &event->data[offset], sizeof(MTP3_HEADER));

    r_ies[indx].param_id = ISUP_PRM_ROUTING_LABEL;

    sio = MTP3_HDR_GET_SIO(header);
    opc = MTP3_RL_GET_DPC_VALUE(header.label);
    dpc = MTP3_RL_GET_OPC_VALUE(header.label);

    r_ies[indx].param_data.routingLabel.sio = sio;
    MTP3_RL_SET_DPC_VALUE(r_ies[indx].param_data.routingLabel.label,
                                dpc);
    MTP3_RL_SET_OPC_VALUE(r_ies[indx].param_data.routingLabel.label,
                                opc);

    r_ies[indx].param_length = sizeof(MTP3_HEADER);

    r_ieCount = indx + 1;  /* array index is one less than the count */

    PrintISUPMsg(r_ies, r_ieCount);
    ISUP_SendGRARequest(ISS7_Stack, hdr, r_ies, r_ieCount);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles CGB message received from STACK.
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
ISUP_HandleIncomingCGBMsg (ITS_HDR *hdr, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int i = 0, j = 0, range, index = 0, indx = 0, offset = 0;
    ITS_OCTET slen = 0, sio = 0;  /* status len */
    ITS_OCTET sup_mtype, l_status[32];
    MTP3_HEADER header;
    ITS_UINT dpc = 0, opc = 0;
    int r_ieCount = 0;
    ITS_ISUP_IE r_ies[3];
    

    memset((char *)l_status, 0, 32);

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
            range = ies[i].param_data.rangeAndStatus.range;
            slen = ies[i].param_length - 1;
            memcpy(l_status, ies[i].param_data.rangeAndStatus.status, slen);
        }
        else if (ies[i].param_id == ISUP_PRM_CKT_GRP_SUPRVN_MT_IND)
        {
            sup_mtype = ies[i].param_data.supervisionMsgType.sup_mt;
        }
        else
        {
            /* Don't do anything */
        }
    }

    for (i = 0; i < slen; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (8*i+j <= range)
            {
                if(l_status[i]>>j & 0x01)
                {
                   // l_status[i] |= 1 << j;
                    ISUP_GetCicIndex(i, &index);
                    ISUP_CIC_SET_MAINT(cicStatus[index].cic_state,
                                                   CKTS_RBLOCKED);

                    /* If Supervision Msg Type is Hwr */
                    if (sup_mtype == 0x01)
                    {
                        cicStatus[index].fsm_state = CPC_IDLE;
                        ISUP_CIC_SET_CALL(cicStatus[index].cic_state,
                                                       CKTS_IDLE_CTK);
                    }
                }
            }
        }
    }

    /* 
     * Construct the CGBA Message to be sent
     * to ISUP Layer, We are not reading from
     * Text File
     */

    /* Encode the params for CGBA msg to be sent. */
    memset((char *)&r_ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    r_ies[indx].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    r_ies[indx].param_data.supervisionMsgType.sup_mt = sup_mtype;
    r_ies[indx].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    indx++;


    /* Now, Fill the Range and Status Param */

    r_ies[indx].param_id = ISUP_PRM_RANGE_STATUS;
    r_ies[indx].param_data.rangeAndStatus.range = range;

    memcpy(r_ies[indx].param_data.rangeAndStatus.status, l_status, 4);

    r_ies[indx].param_length = 5;
    indx++;

    /* MTP3 Header Follows */

    offset = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* Getting the Header From Event */
    memset((char*)&header, 0, sizeof(MTP3_HEADER));
    memcpy(&header, &event->data[offset], sizeof(MTP3_HEADER));

    r_ies[indx].param_id = ISUP_PRM_ROUTING_LABEL;

    sio = MTP3_HDR_GET_SIO(header);
    opc = MTP3_RL_GET_DPC_VALUE(header.label);
    dpc = MTP3_RL_GET_OPC_VALUE(header.label);

    r_ies[indx].param_data.routingLabel.sio = sio;

    MTP3_RL_SET_DPC_VALUE(r_ies[indx].param_data.routingLabel.label,
                                dpc);
    MTP3_RL_SET_OPC_VALUE(r_ies[indx].param_data.routingLabel.label,
                                opc);

    r_ies[indx].param_length = sizeof(MTP3_HEADER);

    r_ieCount = indx + 1;  /* array index is one less than the count */

    PrintISUPMsg(r_ies, r_ieCount);
    ISUP_SendCGBARequest(ISS7_Stack, hdr, r_ies, r_ieCount);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles CGU message received from STACK.
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
ISUP_HandleIncomingCGUMsg (ITS_HDR *hdr, ITS_EVENT *event,
                           ITS_ISUP_IE *ies, int ieCount)
{
    int i = 0, j = 0, range, index = 0, indx = 0, offset = 0;
    ITS_OCTET slen = 0, sio = 0;  /* status len */
    ITS_OCTET sup_mtype, l_status[32];
    MTP3_HEADER header;
    ITS_UINT dpc = 0, opc = 0;
    int r_ieCount = 0;
    ITS_ISUP_IE r_ies[3];


    memset((char *)l_status, 0, 32);

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
            range = ies[i].param_data.rangeAndStatus.range;
            slen = ies[i].param_length - 1;
            memcpy(l_status, ies[i].param_data.rangeAndStatus.status, slen);
        }
        else if (ies[i].param_id == ISUP_PRM_CKT_GRP_SUPRVN_MT_IND)
        {
            sup_mtype = ies[i].param_data.supervisionMsgType.sup_mt;
        }
        else
        {
            /* Don't do anything */
        }
    }

    for (i = 0; i < slen; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (8*i+j <= range)
            {
                if(l_status[i]>>j & 0x01)
                {
                    ISUP_GetCicIndex(i, &index);
                    ISUP_CIC_SET_MAINT(cicStatus[index].cic_state,
                                                     CKTS_ACTIVE);

                    /* If Supervision Msg Type is Hwr */
                    if (sup_mtype == 0x01)
                    {
                        cicStatus[index].fsm_state = CPC_IDLE;
                    }
                }
            }
        }
    }

    /*
     * Construct the CGUA Message to be sent
     * to ISUP Layer, We are not reading from
     * Text File
     */

    /* Encode the params for CGUA msg to be sent. */
    memset((char *)&r_ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    r_ies[indx].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    r_ies[indx].param_data.supervisionMsgType.sup_mt = sup_mtype;
    r_ies[indx].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    indx++;


    /* Now, Fill the Range and Status Param */

    r_ies[indx].param_id = ISUP_PRM_RANGE_STATUS;
    r_ies[indx].param_data.rangeAndStatus.range = range;

    memcpy(r_ies[indx].param_data.rangeAndStatus.status, l_status, 4);

    r_ies[indx].param_length = 5;
    indx++;

    /* MTP3 Header Follows */

    offset = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* Getting the Header From Event */
    memset((char*)&header, 0, sizeof(MTP3_HEADER));
    memcpy(&header, &event->data[offset], sizeof(MTP3_HEADER));

    r_ies[indx].param_id = ISUP_PRM_ROUTING_LABEL;


    sio = MTP3_HDR_GET_SIO(header);
    opc = MTP3_RL_GET_DPC_VALUE(header.label);
    dpc = MTP3_RL_GET_OPC_VALUE(header.label);

    r_ies[indx].param_data.routingLabel.sio = sio;

    MTP3_RL_SET_DPC_VALUE(r_ies[indx].param_data.routingLabel.label,
                                dpc);
    MTP3_RL_SET_OPC_VALUE(r_ies[indx].param_data.routingLabel.label,
                                opc);

    r_ies[indx].param_length = sizeof(MTP3_HEADER);

    r_ieCount = indx + 1;  /* array index is one less than the count */

    PrintISUPMsg(r_ies, r_ieCount);
    ISUP_SendCGUARequest(ISS7_Stack, hdr, r_ies, r_ieCount);
}

#endif /* CCITT */
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

    if(ret == ITS_FALSE)
    {
       return; 
    }

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
                           (ITS_USHORT*) &vcic);

          if (result != ITS_SUCCESS)
          {
              printf("\nApplication: %s : line %d : ReserveCIC return value = %d\n", 
                                                    __FILE__, __LINE__, result);

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
#if defined(ANSI)
                       ISUP_CIC_REMOVE_LOC_BLOCK (cicStatus[index].cic_state);
#elif defined(CCITT)
                       cicStatus[index].cic_state &= 0xFE; 
#endif
                    }
                  }
              }
          }

          if (cotCheckReqFlag == ITS_TRUE)
          {
             /* change state to wait_cot_reports */
             cicStatus[index].fsm_state = CPC_WAIT_COT_REPORT;
          }
          else
          {
              /* change state to wait_in_acm */
              cicStatus[index].fsm_state = CPC_WAIT_IN_ACM;
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
       cicStatus[index].fsm_state = CPC_SENT_OUT_ACM;

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
    printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                             __FILE__, __LINE__, cicStatus[index].cic_num,
                   cicStatus[index].fsm_state, cicStatus[index].cic_state);
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
#ifdef ANSI
                  range = 23;
#elif  CCITT
                  range = 32;
#endif
               }

               for(j = index; j <= index+range; j++)
               {
                   ISUP_CIC_SET_TRANSIENT(cicStatus[j].cic_state);
                   cicStatus[j].fsm_state = CPC_WAIT_IN_RLC;
 
                   printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                                   __FILE__, __LINE__, cicStatus[j].cic_num,
                             cicStatus[j].fsm_state, cicStatus[j].cic_state);
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

         printf("Application: %s : line %d : Cic %d FSM state %d CIC State %d\n", 
                                   __FILE__, __LINE__, cicStatus[index].cic_num,
                        cicStatus[index].fsm_state, cicStatus[index].cic_state);
     }
}
