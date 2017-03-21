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
 * ID:$Id: ISUP_ProcessCic.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
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
 * LOG:Revision 8.7  2005/03/21 13:54:16  cvsadmin
 * LOG:PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG:Revision 1.5.2.1  2003/05/09 05:30:45  ssingh
 * LOG:Changes back ported from current to 6.3
 * LOG:
 * LOG:Revision 8.5  2003/04/30 11:28:12  ssingh
 * LOG:Corrected Printf() statements in some places.
 * LOG:
 * LOG:Revision 8.4  2003/04/29 07:00:01  ssingh
 * LOG:Changed Submitted for test-application core-dump,
 * LOG:while sending IAM on not configured CIC.
 * LOG:
 * LOG:Revision 8.3  2003/04/17 11:29:39  ssingh
 * LOG:Modified printf(); more informations.
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
#include <its_ss7_trans.h>
#include "ISUP_ProcessMsg.h"

#if defined(CCITT)
#define ISS7_Stack ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack ISS7_ANSI_Stack
#endif

extern int GetOpcDpcInfo(OpcDpcInfo*);

#if defined(ANSI)
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles Group Msg ACK received from STACK.
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
ISUP_SetGroupCicBlockingState(ITS_USHORT startCic, ITS_EVENT *event,
                              ITS_ISUP_IE *ies, int  ieCount)
{
    int i, j, k, firstIndex;
    ITS_OCTET status[4];
    ITS_OCTET slen;
    ITS_OCTET range;
    ITS_BOOLEAN ret;

    for (i = 0; i < ieCount; ++i)
    {
        if(ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
           if (ies[i].param_data.rangeAndStatus.range != 0)
           {
              range = ies[i].param_data.rangeAndStatus.range;
              slen = ies[i].param_length - 1;
              memcpy(status, ies[i].param_data.rangeAndStatus.status, slen);
           }
           else
           {
              range = 23;
              slen = 3;

              if(ISUP_GetISUPMsgType(event) == ISUP_MSG_GRA)
              {
                 memset((char *)status, 0, 3);
              }
              else
              {
                 memset((char *)status, 255, 3);
              }
           }

           ret = ISUP_GetCicIndex (startCic, &firstIndex);

           for (j = 0; j < slen; j++)
           {
                for (k = 0; k < 8; k++)
                {
                    if (8*j+k <= range)
                    {
                       if(((status[j] & (1<<k)) >> k) == 1)
                       {
                          if (ISUP_GetISUPMsgType(event) == ISUP_MSG_CGBA)
                          {
                             /* Set Local Blocking */
                             ISUP_CIC_SET_LOC_MAINT(
                                        cicStatus[firstIndex+8*j+k].cic_state);
                          }
                          else if(ISUP_GetISUPMsgType(event) == ISUP_MSG_CGUA)
                          {
                              /* Remove Local Blocking */
                              ISUP_CIC_REMOVE_LOC_BLOCK(
                                         cicStatus[firstIndex+8*j+k].cic_state);
                          }
                          else if(ISUP_GetISUPMsgType(event) == ISUP_MSG_GRA)
                          {
                              /* Set Remote Blocking */
                              ISUP_CIC_SET_MAINT(
                                         cicStatus[firstIndex+8*j+k].cic_state,
                                         CKTS_RBLOCKED);

                              ISUP_CIC_SET_CALL(
                                         cicStatus[firstIndex+8*j+k].cic_state,
                                         CKTS_IDLE_CTK);

                              cicStatus[firstIndex+8*j+k].fsm_state = CPC_IDLE;
                          }

                          printf("Application: %s : line %d : Cic %d State %d\n", 
                                         __FILE__, __LINE__,
                                         cicStatus[firstIndex+8*j+k].cic_num,
                                         cicStatus[firstIndex+8*j+k].cic_state);
                       }
                       else
                       {
                          if (ISUP_GetISUPMsgType(event) == ISUP_MSG_GRA)
                          {
                              ISUP_CIC_SET_CALL(
                                          cicStatus[firstIndex+8*j+k].cic_state,
                                          CKTS_IDLE_CTK);

                              ISUP_CIC_SET_MAINT(
                                          cicStatus[firstIndex+8*j+k].cic_state,
                                          CKTS_IDLE);

                              printf("Application: %s : line %d : Cic %d State %d\n", 
                                         __FILE__, __LINE__,
                                         cicStatus[firstIndex+8*j+k].cic_num,
                                         cicStatus[firstIndex+8*j+k].cic_state);
                          }
                       }
                    }
                }
            }
            break;
         }
     }
}
#elif defined(CCITT) 

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function handles Group Msg ACK received from STACK.
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
ISUP_SetGroupCicBlockingStat(ITS_USHORT startCic, ITS_EVENT *event,
                              ITS_ISUP_IE *ies, int  ieCount)
{
    int i, j, k, firstIndex;
    ITS_OCTET status[4];
    ITS_OCTET slen;
    ITS_OCTET range;
    ITS_BOOLEAN ret;

    for (i = 0; i < ieCount; ++i)
    {
        if(ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
           if (ies[i].param_data.rangeAndStatus.range != 0)
           {
              range = ies[i].param_data.rangeAndStatus.range;
              slen = ies[i].param_length - 1;
              memcpy(status, ies[i].param_data.rangeAndStatus.status, slen);
           }
           else
           {
              range = 32;
              slen = 4;

              if(ISUP_GetISUPMsgType(event) == ISUP_MSG_GRA)
              {
                 memset((char *)status, 0, 4);
              }
              else
              {
                 memset((char *)status, 255, 4);
              }
           }

           ret = ISUP_GetCicIndex (startCic, &firstIndex);

           for (j = 0; j < slen; j++)
           {
                for (k = 0; k < 8; k++)
                {
                    if (8*j+k <= range)
                    {
                       if(((status[j] & (1<<k)) >> k) == 1)
                       {
                          if (ISUP_GetISUPMsgType(event) == ISUP_MSG_CGBA)
                          {
                             /* Set Local Blocking */
                             ISUP_CIC_SET_MAINT(cicStatus[firstIndex+8*j+k].cic_state, CKTS_LBLOCKED);
                          }
                          else if(ISUP_GetISUPMsgType(event) == ISUP_MSG_CGUA)
                          {
                              /* Remove Local Blocking */
                              ISUP_CIC_SET_MAINT(cicStatus[firstIndex+8*j+k].cic_state, CKTS_ACTIVE);
                          }
                          else if(ISUP_GetISUPMsgType(event) == ISUP_MSG_GRA)
                          {
                              /* Set Remote Blocking */
                              ISUP_CIC_SET_MAINT(
                                         cicStatus[firstIndex+8*j+k].cic_state,
                                         CKTS_RBLOCKED);
                              cicStatus[firstIndex+8*j+k].fsm_state = CPC_IDLE;
                          }

                          printf("Application: %s : line %d : Cic %d State %d\n", 
                                       __FILE__, __LINE__, 
                                       cicStatus[firstIndex+8*j+k].cic_num,
                                       cicStatus[firstIndex+8*j+k].cic_state);
                       }
                       else
                       {
                          if (ISUP_GetISUPMsgType(event) == ISUP_MSG_GRA)
                          {
                              ISUP_CIC_SET_CALL(
                                          cicStatus[firstIndex+8*j+k].cic_state,
                                          CKTS_IDLE_CTK);
                              
                              /* Set CIC Maintenace State */
                              cicStatus[firstIndex+8*j+k].cic_state &= 0xFCU;

                              printf("Application: %s : line %d : Cic %d State %d\n", 
                                        __FILE__, __LINE__, 
                                        cicStatus[firstIndex+8*j+k].cic_num,
                                        cicStatus[firstIndex+8*j+k].cic_state);
                          }
                       }
                    }
                }
            }
            break;
         }
     }
}
#endif /* CCITT */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function gives Index mapping to the Start CIC.
 *      received from STACK.
 *
 *  Input Parameters:
 *      startcic     : Message CIC
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      int
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN
ISUP_GetCicIndex (ITS_USHORT startCic, int *index)
{
     int i = 0;
     int j = numOfCICs - 1;
     int k;

     while ( i <= j)
     {
        k = (i+j)/2;

        if (startCic == cicStatus[k].cic_num)
        {
           *index = k;
           return ITS_TRUE;
        }

        if (startCic < cicStatus[k].cic_num)
        {
           j = k - 1;
        }
        else
        {
           i = k + 1;
        }
     }
     return ITS_FALSE;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function next available free CIC.
 *      received from STACK.
 *
 *  Input Parameters:
 *      cic     : Message CIC
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      freeCIC  : Available free CIC
 *
 *  Return Value:
 *      ITS_BOOLEAN
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_GetFreeCircuit (ITS_USHORT cic, ITS_USHORT *freeCIC)
{
     int        i;
     static     OpcDpcInfo info;
     ITS_OCTET  cicstate;
     ITS_CTXT   vcic;
     int ret = 0;

     GetOpcDpcInfo(&info);

     for (i=0; i < numOfCICs; i++)
     {
         printf("Application: %s : line %d : Cic %d State %d\n", 
              __FILE__, __LINE__, cicStatus[i].cic_num, cicStatus[i].cic_state);

         if (cicStatus[i].cic_num == cic)
         {
            /* Don't select;just for safety */
         }
         else
         {
#if defined(ANSI)
            if (ISUP_CIC_IS_IDLE(cicStatus[i].cic_state))
            {
                if(ISUP_CIC_IS_REM_BLOCKED(cicStatus[i].cic_state))
#elif defined(CCITT)
            if (ISUP_CIC_GET_CALL(cicStatus[i].cic_state) == CKTS_IDLE_CTK)
            {
                if(ISUP_CIC_GET_MAINT(cicStatus[i].cic_state == CKTS_RBLOCKED))
#endif
                {
                   /* do nothing */
                }
                else
                {
                   ret = ISUP_ReserveCIC(ISS7_Stack, (ITS_OCTET) info.sio,
                                       (ITS_UINT) info.opc, (ITS_UINT) info.dpc,
                                       (ITS_USHORT) cicStatus[i].cic_num,
                                       (ITS_OCTET*) &cicstate,
                                       (ITS_CTXT*) &vcic);

                   if (ret != ITS_SUCCESS)
                   {
                      printf("Application: %s : line %d : ReserveCIC return value: %d\n",
                                                       __FILE__, __LINE__, ret);

                      if (ret == ITS_ECICBLOCK)
                      {
                         printf("Application: %s : line %d : Reserve CIC State %d\n", 
                                                  __FILE__, __LINE__, cicstate);

                         if (ISUP_CIC_STATE_GET_BA(cicstate) == CKTS_LBLOCKED)
                         {
#if defined(ANSI)
                            ISUP_CIC_REMOVE_LOC_BLOCK(cicStatus[i].cic_state);
#elif defined(CCITT)
                            cicStatus[i].cic_state &= 0xFE;
#endif
                            *freeCIC = cicStatus[i].cic_num;
                            return ITS_TRUE;
                         }
                      }
                   }
                   else
                   {
                      *freeCIC = cicStatus[i].cic_num;
                      return ITS_TRUE;
                   }
                }
            }
         }
      }

      printf("Application: %s : line %d : Reattempt Call for Cic %d failed, no free Cic\n", 
                                                       __FILE__, __LINE__, cic);
      return ITS_FALSE;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function IDLE the CSC/CPC and FSM state
 *      received from STACK.
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
 *  See Also:
 ****************************************************************************/
void 
ISUP_IdleCic(ITS_USHORT cic)
{
   int i = 0;
   int j = numOfCICs - 1;
   int index = -1;
   int k;

   while ( i <= j)
   {
      k = (i+j)/2;

      if (cic == cicStatus[k].cic_num)
      {
         index = k;
         break;
      }

      if (cic < cicStatus[k].cic_num)
      {
         j = k - 1;
      }
      else
      {
         i = k + 1;
      }
   }

   if (index != -1)
   {
      /* check for response for RSC/GRA */
      if (ISUP_CIC_GET_MAINT(cicStatus[index].cic_state) == CKTS_TRANSIENT &&
          ISUP_CIC_GET_CALL(cicStatus[index].cic_state) == CKTS_OUT_OF_ORDER_CTK)
      {
#if defined(ANSI)
         ISUP_CIC_SET_MAINT(cicStatus[index].cic_state, CKTS_IDLE);
#elif defined(CCITT)
         cicStatus[index].cic_state &= 0xFCU;
#endif
      }

      ISUP_CIC_SET_CALL(cicStatus[index].cic_state, CKTS_IDLE_CTK);

      cicStatus[index].fsm_state = CPC_IDLE;

      printf("Application: %s : line %d : Cic %d State %d\n", 
              __FILE__, __LINE__, cicStatus[index].cic_num, 
                                 cicStatus[index].cic_state);
     }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets CIC as Local Block.
 *      received from STACK.
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
ISUP_SetLocalBlock (ITS_USHORT cic)
{
     int i = 0;
     int j = numOfCICs - 1;
     int index = -1;
     int k;

     while ( i <= j)
     {
        k = (i+j)/2;

        if (cic == cicStatus[k].cic_num)
        {
           index = k;
           break;
        }

        if (cic < cicStatus[k].cic_num)
        {
           j = k - 1;
        }
        else
        {
           i = k + 1;
        }
     }

     if (index != -1)
     {
        /* Set Local Blocking */
#if defined(ANSI)
        ISUP_CIC_SET_LOC_MAINT(cicStatus[index].cic_state);
#elif defined(CCITT)
        ISUP_CIC_SET_MAINT(cicStatus[index].cic_state, CKTS_LBLOCKED);
#endif
        printf("Application: %s : line %d : Cic %d State %d\n", 
               __FILE__, __LINE__, cicStatus[index].cic_num,
                                   cicStatus[index].cic_state);
     }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets CIC as Remote Block.
 *      received from STACK.
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
ISUP_SetRemoteBlock (ITS_USHORT cic)
{
     int i = 0;
     int j = numOfCICs - 1;
     int index = -1;
     int k;

     while ( i <= j)
     {
        k = (i+j)/2;

        if (cic == cicStatus[k].cic_num)
        {
           index = k;
           break;
        }

        if (cic < cicStatus[k].cic_num)
        {
           j = k - 1;
        }
        else
        {
           i = k + 1;
        }
     }

     if (index != -1)
     {
        /* Set Remote Blocking */
#if defined(ANSI)
        ISUP_CIC_SET_REM_MAINT(cicStatus[index].cic_state);
#elif defined(CCITT)
        ISUP_CIC_SET_MAINT(cicStatus[index].cic_state, CKTS_RBLOCKED);
#endif
        printf("Application: %s : line %d : Cic %d State %d\n", 
                __FILE__, __LINE__, cicStatus[index].cic_num, 
                                    cicStatus[index].cic_state);
     }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Removes Remote Blocking for CIC.
 *      received from STACK.
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
ISUP_RemoveRemoteBlock (ITS_USHORT cic)
{
     int i = 0;
     int j = numOfCICs - 1;
     int index = -1;
     int k;

     while ( i <= j)
     {
        k = (i+j)/2;

        if (cic == cicStatus[k].cic_num)
        {
           index = k;
           break;
        }

        if (cic < cicStatus[k].cic_num)
        {
           j = k - 1;
        }
        else
        {
           i = k + 1;
        }
     }

     if (index != -1)
     {
         /* Remove Remote Blocking */
#if defined(ANSI)
         ISUP_CIC_REMOVE_REM_BLOCK(cicStatus[index].cic_state);
#elif defined(CCITT)
         cicStatus[index].cic_state &= 0xFDU;
#endif
         printf("Application: %s : line %d : Cic %d State %d\n", 
                 __FILE__, __LINE__, cicStatus[index].cic_num,
                                     cicStatus[index].cic_state);
     }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function remove Local Blocking for CIC.
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
ISUP_RemoveLocalBlock (ITS_USHORT cic)
{
     int i = 0;
     int j = numOfCICs - 1;
     int index = -1;
     int k;

     while ( i <= j)
     {
        k = (i+j)/2;

        if (cic == cicStatus[k].cic_num)
        {
           index = k;
           break;
        }

        if (cic < cicStatus[k].cic_num)
        {
           j = k - 1;
        }
        else
        {
           i = k + 1;
        }
     }

     if (index != -1)
     {
        /* Remove Local Blocking */
#if defined(ANSI)
        ISUP_CIC_REMOVE_LOC_BLOCK(cicStatus[index].cic_state);
#elif defined(CCITT)
        ISUP_CIC_SET_MAINT(cicStatus[index].cic_state, CKTS_ACTIVE);
#endif
        printf("Application: %s : line %d : Cic %d State %d\n", 
                __FILE__, __LINE__, cicStatus[index].cic_num, 
                                    cicStatus[index].cic_state);
     }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sync the CIC fsm as well as csc state in case of 
 *      Stack failed to send Message down to Network
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
 *  See Also:
 ****************************************************************************/
void 
ISUP_UpdateCicStatus (ITS_USHORT cic)
{
     int         index;
     static      OpcDpcInfo info;
     ITS_OCTET   cicstate;
     ITS_CTXT    vcic;
     int         ret;
     ITS_BOOLEAN retVal;

     GetOpcDpcInfo(&info);

     retVal = ISUP_GetCicIndex (cic, &index);

     if(retVal == ITS_FALSE)
     {
        return;
     }
     
     ret = ISUP_ReserveCIC(ISS7_Stack,(ITS_OCTET) info.sio,
                   (ITS_UINT) info.opc, (ITS_UINT) info.dpc,
                   (ITS_USHORT) cic, (ITS_OCTET*) &cicstate,
                   (ITS_CTXT*) &vcic);

     ISUP_CIC_SET_MAINT(cicStatus[index].cic_state, 
                                              ISUP_CIC_STATE_GET_BA(cicstate));
     ISUP_CIC_SET_CALL(cicStatus[index].cic_state, 
                                              ISUP_CIC_STATE_GET_DC(cicstate));

     printf("Application: %s : line %d : Cic %d State %d\n", 
                        __FILE__, __LINE__, cicStatus[index].cic_num, 
                                            cicStatus[index].cic_state);
}
