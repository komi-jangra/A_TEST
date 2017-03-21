/*************************************************************** File Header ***
   File Name      : oamscfg_trx_object_handler.c
Purpose        : This file contains functions defintions for PTRX Object handling.
Project        : BSC
Subsystem    : OAMS 
Author         : Aricent Bangalore
CSCI id        :
Version        :
 ********************************************************************** End ***/

#include <oamscfg_includes.h>
/********************************* Function  Header**************************************
   Function Name:       getPtrxObjectState()
Parameters:          void
Return type:         enum
Purpose:             To  get the current state of received ptrx 
Other Note:
 ****************************************************************************************/

objectState getPtrxObjectState(I_U32 ptrxId)
{
   return gPtrxData[ptrxId].ptrxState;

}/*End of getPtrxObjectState*/

/********************************* Function  Header********************************
   Function Name:       getState()
Parameters:          void
Return type:         void
Purpose:             
Other Note:
 ************************************************************************************/
objectState getPtrxState()
{
   objectState state;
   TrxTableApi *ptrxTableApiRcvdPtr = PNULL; 
   OamsTrxhCfgLockResp *TrxhCfgLockResp = PNULL;
   OamsTrxhCfgUnlockResp *TrxhCfgUnlockResp =PNULL;
 /* Trx Block Feature : Starts */   
   OamsTrxhCfgBlockResp *TrxhCfgBlockResp = PNULL;
 /* Trx Block Feature : Ends */
   LOG_PRINT(LOG_INFO," getState... ");
   switch (((SysHdr*) gCfgMsgBuf)->msgType) /*Read the MSGTYPE from the received message*/
   {
      case BSC_API_SET_TRXTABLE:
         {
            sCmMsg* receivedCmMsgPtr = PNULL;
            receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
            ptrxTableApiRcvdPtr = (TrxTableApi *)( ((I_U8 *)receivedCmMsgPtr) + sizeof(sCmMsg));
            LOG_PRINT(LOG_DEBUG,"Received BSC_API_SET_TRXTABLE: PtrxId: %d",ptrxTableApiRcvdPtr->ptrxId);
            state = getPtrxObjectState(ptrxTableApiRcvdPtr->ptrxId);
         }
         break;
      case BSC_API_DEL_TRXTABLE:
         {
            sCmMsg* receivedCmMsgPtr = PNULL;
            receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
            ptrxTableApiRcvdPtr = (TrxTableApi *)( ((I_U8 *)receivedCmMsgPtr) + sizeof(sCmMsg));
            LOG_PRINT(LOG_DEBUG,"Received BSC_API_DEL_TRXTABLE: PtrxId: %d",ptrxTableApiRcvdPtr->ptrxId);
            state = getPtrxObjectState(ptrxTableApiRcvdPtr->ptrxId);
         }
         break;
      case OAMS_TRXH_CFG_LOCK_RESP:
         {

            TrxhCfgLockResp = (OamsTrxhCfgLockResp *)gCfgMsgBuf;
            LOG_PRINT(LOG_DEBUG,"Received OAMS_TRXH_CFG_LOCK_RESP : PtrxId: %d",TrxhCfgLockResp->objId);
            state = getPtrxObjectState(TrxhCfgLockResp->objId);

         }break;
      case OAMS_TRXH_CFG_UNLOCK_RESP:
         {

            TrxhCfgUnlockResp = (OamsTrxhCfgUnlockResp *)gCfgMsgBuf;
            LOG_PRINT(LOG_DEBUG,"nReceived OAMS_TRXH_CFG_UNLOCK_RESP: PtrxId: %d",TrxhCfgUnlockResp->objId);
            state = getPtrxObjectState(TrxhCfgUnlockResp->objId);

         }break;
 /* Trx Block Feature : Starts */		 
       case OAMS_TRXH_CFG_BLOCK_RESP:
         {
            TrxhCfgBlockResp = (OamsTrxhCfgBlockResp *)gCfgMsgBuf;
            LOG_PRINT(LOG_DEBUG,"Received OAMS_TRXH_CFG_BLOCK_RESP: PtrxId: %d",TrxhCfgBlockResp->objId);
            state = getPtrxObjectState(TrxhCfgBlockResp->objId);
         }break;
/* Trx Block Feature : Ends */
   }
   return state;

}

/********************************* Function  Header********************************
   Function Name:       trxObjectHandler()
Parameters:          void
Return type:         void
Purpose:             To  handle PTrx LOCK/UNLOCK procedures 
Other Note:
 ************************************************************************************/

void trxObjectHandler()
{
   LOG_PRINT(LOG_INFO,"Dispatched to trxObject handler");
   objectState state;
   state=getPtrxState();
   switch (state)/*Read the State of received PTRX.*/
   {
      case locked:
         LOG_PRINT(LOG_INFO,"Dispatched To LockedHAndler()");
         ptrxObjectLockedHandler();
         break;
      case lockInProgress:   
         LOG_PRINT(LOG_INFO,"Dispatched to LockInProgressHandler()");
         ptrxObjectLockInProgressHandler();
         break;
      case unlocked:
         LOG_PRINT(LOG_INFO,"Dispateched to UnlockedHAndler()");
         ptrxObjectUnlockHandler();
         break;
      case unlockInProgress:
         LOG_PRINT(LOG_INFO,"Dispatched to UnlockInProgressHandler()");   
         ptrxObjectUnlockInProgressHandler();
         break;
 /* Trx Block Feature : Starts */		 
      case blockInProgress:
         LOG_PRINT(LOG_INFO,"Dispatched to BlockInProgressHandler()");   
         ptrxObjectBlockInProgressHandler();
         break;
 /* Trx Block Feature : Ends */		 
      default:
         break;

   }/*End of switch*/

}/*End of TrxObject Handler*/

/********************************* Function  Header********************************
   Function Name:       trxResetHandler()
Parameters:          void
Return type:         void
Purpose:             To  handle PTrx LOCK/UNLOCK procedures 
Other Note:
 ************************************************************************************/

void trxResetHandler()
{
  LOG_PRINT(LOG_INFO,"Dispatched to trxReset handler");
  objectState state;
  state=getPtrxState();
  switch (state)/*Read the State of received PTRX.*/
  {
    case locked:
      LOG_PRINT(LOG_INFO,"Message Received in LOCK State");
      TrxTableApi *ptrxTableApiRcvdPtr;
      sCmMsg* receivedCmMsgPtr = PNULL;
      receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
      ptrxTableApiRcvdPtr = (TrxTableApi *)( ((I_U8 *)receivedCmMsgPtr) + sizeof(sCmMsg));
      TrxTsTeiTableIndices ptrxTsTeiTableIndices;
      TrxTsTeiTableApi *ptrxTrxTsTableApiDBPtr;
      TrxTableIndices ptrxTableIndices;
      TrxTableApi   *ptrxTableApiDBPtr;
#if 0
      BicStatusTableIndices  bicStatusIndex;
      BicStatusTableApi  *bicStatusData = NULL;  
#endif
      I_S32 errCode = 0;
      ptrxTableIndices.ptrxId = ptrxTableApiRcvdPtr->ptrxId;   
      errCode = getTrxTable(&ptrxTableIndices,&ptrxTableApiDBPtr);
      if (errCode != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"DB call : getTrxTable Failed");
        cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
        return;
      }
#if 0
      else if (ptrxTableApiDBPtr->trxLocation != TRX_LOCATION_R2_BTS)
      {
        LOG_PRINT(LOG_INFO,"RESET operation is supported on R2-BTS-TRX only");
        cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED_ON_BIC_TRX);
        free(ptrxTableApiDBPtr);
        return;
      }
#endif 
      else if (ptrxTableApiDBPtr->adminState != LOCK)
      {
        LOG_PRINT(LOG_INFO,"TRX is in not LOCK state");
        cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
        free(ptrxTableApiDBPtr);
        return;
      }
      else if (ptrxTableApiDBPtr->trxPwrAction != POWER_ON )
      {
        LOG_PRINT(LOG_INFO,"TRX Power action is not ON in DB");
        cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED_ON_TRX_POWER_OFF);
        free(ptrxTableApiDBPtr);
        return;
      }

      ptrxTsTeiTableIndices.ptrxId = ptrxTableApiRcvdPtr->ptrxId;   
      errCode = getTrxTsTeiTable(&ptrxTsTeiTableIndices,&ptrxTrxTsTableApiDBPtr);
      if (errCode != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"DB call : getTrxTsTeiTable Failed");
        cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
        free(ptrxTableApiDBPtr);
        return;
      }
      else if ((ptrxTrxTsTableApiDBPtr->lapdLinkStatus != LAPD_LINK_UP) &&
          (ptrxTableApiDBPtr->trxLocation != TRX_LOCATION_R2_BTS_IP) &&
          (ptrxTableApiDBPtr->trxLocation != TRX_LOCATION_R3_BTS))
      {
        LOG_PRINT(LOG_INFO,"LAPD_LINK_DOWN of the requested TRX");
        cfgSendNackToCm(CM_ERR_TRX_LAPD_NOT_ESTABLISHED);
        free(ptrxTableApiDBPtr);
        free(ptrxTrxTsTableApiDBPtr);
        return;
      }
#if 0
      /* Check whether Parent Bic Connected or not */
      bicStatusIndex.bicId = ptrxTableApiRcvdPtr->bicId;
      errCode = getBicStatusTable(&bicStatusIndex,&bicStatusData);
      if (errCode != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"DB call : getBicStatusTable Failed");
        cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
        free(ptrxTableApiDBPtr);
        return;
      }
      else if (bicStatusData->connectionState != BIC_CONNECTED)
      {
        LOG_PRINT(LOG_INFO,"BIC not in Connected state");
        cfgSendNackToCm(CM_ERR_BTS_NOT_CONNECTED);
        free(ptrxTableApiDBPtr);
        free(bicStatusData);
        return;
      }
#endif
      else /* check reading from DB is SUCCESS/FAILURE*/
      {
        if(ptrxTableApiRcvdPtr->trxReset == RESET )/*Request for Reset*/
        {
          /* CS3.0 Changes : Start*/
          SwMNodeTableIndices swMNodeTableIndex;
          I_U8 slotId;
          I_U8 chasisFrameId;

          I_U32 swStatus;
          if ( ( errCode = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
          {
            LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",errCode);
            free(ptrxTableApiDBPtr);
            free(ptrxTrxTsTableApiDBPtr);
            return;
          }
          LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
          if ((ptrxTableApiDBPtr->trxLocation != TRX_LOCATION_R2_BTS_IP) &&
              (ptrxTableApiDBPtr->trxLocation != TRX_LOCATION_R3_BTS)) /*Changes for R2.8  */
          {
            /*Retrieve swStatus from SwMNode Table */
            /* Changes for R2.2 : Start */
            if (ptrxTableApiDBPtr->trxLocation == TRX_LOCATION_R2_BTS )
            {
              /* In case of R2-BTS-TRX,Check the status of R2-BTS inplace of R2-BTS-TRX */
              swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R2_BTS;
              swMNodeTableIndex.nodeIdentity = ptrxTableApiDBPtr->bicId;
            }
            else
            {
              swMNodeTableIndex.nodeType = SYS_NODE_TYPE_TRX;
              swMNodeTableIndex.nodeIdentity = ptrxTableApiRcvdPtr->ptrxId;
            }
            /* Changes for R2.2 : End */
            swMNodeTableIndex.chasisFrameId = chasisFrameId;
            swMNodeTableIndex.slotId = slotId;
            if(getSwStatusFromSwMNodeTable(swMNodeTableIndex,&swStatus) != CLIB_SUCCESS)
            {
              LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable DB call is getting failed..");
              cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
              free(ptrxTableApiDBPtr);
              free(ptrxTrxTsTableApiDBPtr);
              return;
            }
            if(swStatus == SW_ACTIVATION_IN_PROGRESS || swStatus == SW_DOWNLOAD_IN_PROGRESS)
            { 
              LOG_PRINT(LOG_DEBUG,"Software activation/download is in progress for the TRX");
              cfgSendNackToCm(CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS);
              free(ptrxTableApiDBPtr);
              free(ptrxTrxTsTableApiDBPtr);
              return;
            }
            /* CS3.0 Changes : End*/
          }
          sendPtrxResetReq();
          free(ptrxTableApiDBPtr);
          free(ptrxTrxTsTableApiDBPtr);
        }/*End of if*/
        else
        {
          LOG_PRINT(LOG_INFO,"trxResetHandler:Sending NACK to CM");
          cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
          free(ptrxTableApiDBPtr);
          free(ptrxTrxTsTableApiDBPtr);               
        }
        break;
      } /*end of if */

      break;
    case lockInProgress:   
      LOG_PRINT(LOG_INFO,"Received message cannot be handled in LOCK-IN-PROGRESS State");
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
      break;
    case unlocked:
      LOG_PRINT(LOG_INFO,"Received message cannot be handled in UNLOCK State");
      cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
      break;
    case unlockInProgress:
      LOG_PRINT(LOG_INFO,"Received message cannot be handled in UNLOCK-IN-PROGRESS State");
      cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
      break;
    case blockInProgress:
      LOG_PRINT(LOG_INFO,"Received message cannot be handled in BLOCK-IN-PROGRESS State");
      cfgSendNackToCm(CM_ERR_TRX_BLOCK_IN_PROGRESS);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
      break;

  }/*End of switch*/


}/*End of TrxObject Handler*/

/********************************* Function  Header********************************
   Function Name:       ptrxObjectLockedHandler()
Parameters:          void
Return type:         void
Purpose:             To handle Locked state procedures
Other Note:
 ************************************************************************************/

void ptrxObjectLockedHandler()
{
   switch (((SysHdr*) gCfgMsgBuf)->msgType) /*Read the MSGTYPE from the received message*/
   {
      case BSC_API_SET_TRXTABLE:
         LOG_PRINT(LOG_INFO,"Switching to SetHandler()");
         ptrxObjectPtrxSetTableHandler();
         break;
   }/*End of switch*/
}/* End of ptrxObjectLockedHandler*/

/********************************* Function  Header********************************
   Function Name:       ptrxObjectLockInProgressHandler()
Parameters:          void
Return type:         void
Purpose:             To handle LockInProgress state procedures
Other Note:
 **********************************************************************************/

void ptrxObjectLockInProgressHandler()
{
   switch (((SysHdr*) gCfgMsgBuf)->msgType)/*Read the MSGTYPE from the received message*/
   {
      case BSC_API_SET_TRXTABLE:
         {

            LOG_PRINT(LOG_INFO,"Received message cannot be handled in LOCK-IN-PROGRESS State");
            cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
         }
         break;   
      case OAMS_TRXH_CFG_LOCK_RESP:
         LOG_PRINT(LOG_INFO,"Received LOCK Response ");
         oamsTrxhCfhLockResp();
         break;
   }/*End of switch*/
}/* End of ptrxObjectLockInProgressHandler*/

/********************************* Function  Header********************************
   Function Name:       ptrxObjectUnlockHandler()
Parameters:          void
Return type:         void
Purpose:             To handle UnLocked state procedures
Other Note:
 ************************************************************************************/

void ptrxObjectUnlockHandler()
{
   switch (((SysHdr*) gCfgMsgBuf)->msgType)/*Read the MSGTYPE from the received message*/
   {
      case BSC_API_SET_TRXTABLE:
         ptrxObjectPtrxSetTableHandler();
       
         break;   
   }/*End of switch*/
}/* End of ptrxObjectUnockHandler*/

/********************************* Function  Header********************************
   Function Name:       ptrxObjectUnLockInProgressHandler()
Parameters:          void
Return type:         void
Purpose:             To handle UnLockInProgress state procedures
Other Note:
 ************************************************************************************/

void ptrxObjectUnlockInProgressHandler()
{
   switch (((SysHdr*) gCfgMsgBuf)->msgType)/*Read the MSGTYPE from the received message*/
   {
      case BSC_API_SET_TRXTABLE:
         {
            LOG_PRINT(LOG_INFO,"Received message cannot be handled in UNLOCK-IN-PROGRESS State");
            cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
         }
         break;   
      case OAMS_TRXH_CFG_UNLOCK_RESP:
         LOG_PRINT(LOG_INFO,"Received UNLOCK Response ");
         oamsTrxhCfgUnlockResp();
         break;

   }/*End of switch*/
}/*End of ptrxObjectUnLockInProgressHandler*/

/********************************* Function  Header********************************
   Function Name:       ptrxObjectPtrxSetTableHandler()
Parameters:          void
Return type:         void
Purpose:             To handle BSC_API_SET_PRXTABLE message for Lock/Unlock PTRX.
Other Note:
 ************************************************************************************/

void ptrxObjectPtrxSetTableHandler()
{


   TrxTableApi *ptrxTableApiRcvdPtr;
   sCmMsg* receivedCmMsgPtr = PNULL;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   ptrxTableApiRcvdPtr = (TrxTableApi *)( ((I_U8 *)receivedCmMsgPtr) + sizeof(sCmMsg));
   TrxTableIndices ptrxTableIndices;
   TrxTableApi   *ptrxTableApiDBPtr;
   I_S32 errCode = 0;
   ptrxTableIndices.ptrxId = ptrxTableApiRcvdPtr->ptrxId;   
   errCode = getTrxTable(&ptrxTableIndices,&ptrxTableApiDBPtr);
   if (errCode == CLIB_SUCCESS)/* check reading from DB is SUCCESS/FAILURE*/
   {
      LOG_PRINT(LOG_INFO,"Handling request based on ADMIN STATE");
      switch (ptrxTableApiDBPtr->adminState)
      {
         case LOCK: 
            if(ptrxTableApiRcvdPtr->adminState == UNLOCK)/*Request for Unlock*/
            {
               /* CS3.0 Changes : Start*/
             if(TRX_LOCATION_R2_BTS_IP != ptrxTableApiRcvdPtr->trxLocation && TRX_LOCATION_R3_BTS != 
              ptrxTableApiRcvdPtr->trxLocation)/*Changes for R2.8*/
             {  
               SwMNodeTableIndices swMNodeTableIndex;
               I_U8 slotId;
               I_U8 chasisFrameId;

               I_U32 swStatus;
                 if ( ( errCode = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
                 {
                    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",errCode);
      		    free(ptrxTableApiDBPtr);
                    return;
                 }
                 LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

               /*Retrieve swStatus from SwMNode Table */
	       /* Changes for R2.2 : Start */
   	           if(ptrxTableApiDBPtr->trxLocation == TRX_LOCATION_R2_BTS )
      	       {
		    /* In case of R2-BTS-TRX,Check the status of R2-BTS inplace of R2-BTS-TRX */
        	    swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R2_BTS;
         	    swMNodeTableIndex.nodeIdentity = ptrxTableApiDBPtr->bicId;
      	       }
      	       else
      	       {
         	    swMNodeTableIndex.nodeType = SYS_NODE_TYPE_TRX;
         	    swMNodeTableIndex.nodeIdentity = ptrxTableApiRcvdPtr->ptrxId;
      	       }
	       /* Changes for R2.2 : End */

               swMNodeTableIndex.chasisFrameId = chasisFrameId;
               swMNodeTableIndex.slotId = slotId;
               if(getSwStatusFromSwMNodeTable(swMNodeTableIndex,&swStatus) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable DB call is getting failed..");
                  cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      		  free(ptrxTableApiDBPtr);
                  return;
               }
               if(swStatus == SW_ACTIVATION_IN_PROGRESS || swStatus == SW_DOWNLOAD_IN_PROGRESS)
               { 
                  LOG_PRINT(LOG_DEBUG,"Software activation/download is in progress for the TRX");
                  cfgSendNackToCm(CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS);
            		  free(ptrxTableApiDBPtr);
                  return;
               }
               /* CS3.0 Changes : End*/
              }
               LOG_PRINT(LOG_INFO,"ptrxObjectPtrxSetTableHandler : Send ACK to CM before executing UNLOCK Procedure");
               cfgSendAckToCm();/*Send CM_APPI_RESPONSE with status = CM_SUCCESS to CM*/
               sendPtrxUnlockReq();
            }/*End of if*/
            else if(ptrxTableApiRcvdPtr->adminState == BLOCK)/*Request for Block*/
            {
               LOG_PRINT(LOG_INFO,"\nptrxObjectPtrxSetTableHandler :Block request is received when TRX is Locked so Sending NACK to CM");
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
            }
            else
            {
               LOG_PRINT(LOG_INFO,"ptrxObjectPtrxSetTableHandler :Sending NACK to CM");
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
            }
            break;
         case UNLOCK:

            if (ptrxTableApiRcvdPtr->adminState == LOCK)/*Request for Lock*/
            {
               LOG_PRINT(LOG_INFO,"ptrxObjectPtrxSetTableHandler : Send ACK to CM before executing LOCK Procedure");
               cfgSendAckToCm();/*Send CM_APPI_RESPONSE with status = CM_SUCCESS to CM*/
               sendPtrxLockReq();
            }/*End of if*/

   /* Trx Block Feature : Starts */
            else if (ptrxTableApiRcvdPtr->adminState == BLOCK)/*Request for Trx Block */
            {
               PtrxTableIndices        ptrxTableIndex;
               PtrxTableApi*           ptrxTablePtr = PNULL;

               LOG_PRINT(LOG_INFO,"TRX Block Request Received from CM "); 
               
               /* Check whether Trx is operationally Enabled or Not */
               ptrxTableIndex.ptrxId = ptrxTableApiRcvdPtr->ptrxId ; 
               if(getPtrxTable(&ptrxTableIndex,&ptrxTablePtr) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_INFO,"getPtrxTable db call failed.....");
                  cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      	         free(ptrxTableApiDBPtr);
                  return;
               } 
               else
               {
                 if( ptrxTablePtr->oprState == ENABLED )
                 { 
                    sendBlockReqForTrx(ptrxTableApiRcvdPtr->ptrxId);
                    free(ptrxTableApiDBPtr);
                    free(ptrxTablePtr);
                    return;
                 }
                 else
                 {
                    LOG_PRINT(LOG_INFO,"PtrxId - %d received is operationally Disabled",ptrxTableApiRcvdPtr->ptrxId);
                    LOG_PRINT(LOG_INFO,"Send Trx Lock request immediately");
                    free(ptrxTableApiDBPtr);
                    free(ptrxTablePtr);
                    cfgSendAckToCm();
                    sendPtrxLockReq();
                    return;
                 }
               }
            }/*End of else if*/
/* Trx Block Feature : Ends */
            else 
            {
               LOG_PRINT(LOG_INFO,"ptrxObjectPtrxSetTableHandler :Sending NACK to CM");
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);/*Send CM_APPI_RESPONSE with status = CM_FAILURE to CM*/
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"ptrxObjectPtrxSetTableHandler :Not Expected Admin State");   
            cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);               
      }/*End of switch*/
      free(ptrxTableApiDBPtr);
   } /*end of if */

   else
   {
      LOG_PRINT(LOG_INFO,"DB getTrxTable Failed");
      return;
   }

} /*end of ptrxObjectPtrxSetTableHandler */

/********************************* Function  Header********************************
   Function Name:       oamsTrxhCfhLockResp()
Parameters:          void
Return type:         void
Purpose:             To handle OAMS_TRXH_CFG_LOCK_RESP
Other Note:
 ************************************************************************************/

I_U32 oamsTrxhPtrxAdminState(I_U32 ptrxId, I_U32  state)
{
   TrxTableApi *PhyTrxPtr;
   TrxTableIndices phyTrxIndex;
   phyTrxIndex.ptrxId = ptrxId;
   if ( getTrxTable(&phyTrxIndex,&PhyTrxPtr)== CLIB_SUCCESS)
   {
      PhyTrxPtr->adminState = state;
      if (updateTrxTable(PhyTrxPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL," Adminstate updation failed ");
      }
      else
      {
         free(PhyTrxPtr);
         return CLIB_SUCCESS;
      }
   }
   return ~CLIB_SUCCESS;

}

void oamsTrxhCfhLockResp()
{
   OamsTrxhCfgLockResp *TrxhCfgLockResp = NULL;
   TrxhCfgLockResp = (OamsTrxhCfgLockResp *)gCfgMsgBuf;
   OamsTrxhCfgAlarmInd alarmBuff={0};
   TrxTableIndices trxTableIndices;
   TrxTableApi *trxTableApi; 
   I_U32 ptrxId;
   I_S32 rVal;
   LOG_PRINT(LOG_INFO,"Received LOCK Response");
   ptrxId = TrxhCfgLockResp->objId;
   if ((oamsTrxhPtrxAdminState(ptrxId,LOCKED)) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"DB Update Unsuccessfull");
      return;
   }/*End of if*/
   trxTableIndices.ptrxId = ptrxId; 
   if( CLIB_SUCCESS != getTrxTable(&trxTableIndices,&trxTableApi) )	
   {
       LOG_PRINT(DEBUG,"getTrxTable failed for Trx:%d",ptrxId);
       return;
   }

   gPtrxData[ptrxId].ptrxState = locked; 

   alarmBuff.sysAlarm.sysalarmId = PTRX_LOCKED;
   alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_PTRX;
   alarmBuff.sysAlarm.key1 = trxTableApi->bicId;
   alarmBuff.sysAlarm.key2 = trxTableApi->ptrxId;
   free(trxTableApi);
   /* Mantis Id 2242 Start */
   alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   /* Mantis Id 2242 End */
   alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"BtsId %d PTRX %d is LOCKED",
                alarmBuff.sysAlarm.key1, alarmBuff.sysAlarm.key2);

   LOG_PRINT(LOG_INFO,"oamsTrxhCfhLockResp() : Sending Alarm : ");
   rVal = cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   if (rVal == CFG_FAILURE)
   {
      LOG_PRINT(LOG_CRITICAL,"oamsTrxhCfhLockResp() :OAMS_CFG_AFH_ALARM_IND send Failed");/*TBD send log */
   }/*End of if*/
   if (rVal == CFG_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"oamsTrxhCfhLockResp() :OAMS_CFG_AFH_ALARM_IND  send Success");/*TBD send log */
   } /*End of if*/
}/*End of oamsTrxhCfhLockResp*/

/********************************* Function  Header********************************
   Function Name:       oamsTrxhCfhUnlockResp()
Parameters:          void
Return type:         void
Purpose:             To handle OAMS_TRXH_CFG_UNLOCK_RESP
Other Note:
 ************************************************************************************/

void oamsTrxhCfgUnlockResp()
{

   OamsTrxhCfgUnlockResp *TrxhCfgUnlockResp = PNULL;
   TrxhCfgUnlockResp = (OamsTrxhCfgUnlockResp *)gCfgMsgBuf;
   OamsTrxhCfgAlarmInd alarmBuff={0};
   TrxTableIndices trxTableIndices;
   TrxTableApi *trxTableApi; 
   I_U32 ptrxId;
   I_S32 rVal;
   LOG_PRINT(LOG_INFO,"Received UNLOCK Response ");
   ptrxId = TrxhCfgUnlockResp->objId;
   if ((oamsTrxhPtrxAdminState(ptrxId,UNLOCKED)) != CLIB_SUCCESS)
   {   
      LOG_PRINT(LOG_INFO,"Update is UNSUCCESSFUL");/*TBD We should log error*/
      return;
   }/*End of if*/
   trxTableIndices.ptrxId = ptrxId; 
   if( CLIB_SUCCESS != getTrxTable(&trxTableIndices,&trxTableApi) )	
   {
       LOG_PRINT(DEBUG,"getTrxTable failed for Trx:%d",ptrxId);
       return;
   }

   gPtrxData[ptrxId].ptrxState = unlocked; 
   alarmBuff.sysAlarm.sysalarmId = PTRX_UNLOCKED;
   alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_PTRX;
   alarmBuff.sysAlarm.key1 = trxTableApi->bicId;
   alarmBuff.sysAlarm.key2 = trxTableApi->ptrxId;
   free(trxTableApi);
   alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
   alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"BtsId %d PTRX %d is UNLOCKED",
                         alarmBuff.sysAlarm.key1, alarmBuff.sysAlarm.key2);
   LOG_PRINT(LOG_INFO," oamsTrxhCfgUnlockResp() :Sending Alarm :");
   rVal = cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   if (rVal == CFG_FAILURE)
   {
      LOG_PRINT(LOG_CRITICAL,"oamsTrxhCfgUnlockResp() :OAMS_CFG_AFH_ALARM_IND send Failed");/*TBD send log */
   }/*End of if*/
   if (rVal == CFG_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"oamsTrxhCfgUnlockResp() :OAMS_CFG_AFH_ALARM_IND  send SUCCESS");/*TBD send log */
   } /*End of if*/

}/*End of oamsTrxhCfgUnlockResp*/

/********************************* Function  Header********************************
   Function Name:       sendPtrxLockReq()
Parameters:          void
Return type:         void
Purpose:             To handle PTRX Lock Request procedure
Other Note:
 ************************************************************************************/

void sendPtrxLockReq()

{

   TrxTableApi *ptrxTableApiRcvdPtr = PNULL;
   sCmMsg* receivedCmMsgPtr = PNULL;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   ptrxTableApiRcvdPtr = (TrxTableApi *)( ((I_U8 *)receivedCmMsgPtr) + sizeof(sCmMsg));
   I_S32 rVal;
   OamsCfgTrxhLockReq lockBuff;
   lockBuff.sysHdr.msgType = OAMS_CFG_TRXH_LOCK_REQ;
   lockBuff.objId = ptrxTableApiRcvdPtr->ptrxId;
   lockBuff.objType = OAMS_OBJTYPE_PTRX;
   lockBuff.reason = OAMS_RSN_OPERATORINITIATED;
   LOG_PRINT(LOG_INFO,"sendPtrxLockReq() :Sending Lock Request");
   rVal = cfgSendMessage(&lockBuff,sizeof(OamsCfgTrxhLockReq), ENT_OAMS_TRXH, OAMS_CFG_TRXH_LOCK_REQ,0);
   if (rVal == CFG_FAILURE)
   {
      LOG_PRINT(LOG_CRITICAL, "sendPtrxLockReq():OAMS_CFG_TRXH_LOCK_REQ send Failed");/*TBD send log */
   }/*End of if*/
   if (rVal == CFG_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"sendPtrxLockReq() :OAMS_CFG_TRXH_LOCK_REQ  send SUCCESS");/*TBD send log */
      gPtrxData[ptrxTableApiRcvdPtr->ptrxId].ptrxState = lockInProgress; 
   } /*End of if*/


}/*End of sendPtrxLockReq*/

/********************************* Function  Header********************************
   Function Name:       sendPtrxUnLockReq()
Parameters:          void
Return type:         void
Purpose:             To handle PTRX UnLock Request procedure
Other Note:
 ************************************************************************************/

void sendPtrxUnlockReq()
{

   TrxTableApi *ptrxTableApiRcvdPtr = PNULL;
   sCmMsg* receivedCmMsgPtr = PNULL;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   ptrxTableApiRcvdPtr = (TrxTableApi *)( ((I_U8 *)receivedCmMsgPtr) + sizeof(sCmMsg));
   I_S32 rVal;

   OamsCfgTrxhUnlockReq unlockBuff;
   unlockBuff.sysHdr.msgType = OAMS_CFG_TRXH_UNLOCK_REQ;
   unlockBuff.objId = ptrxTableApiRcvdPtr->ptrxId;
   unlockBuff.objType = OAMS_OBJTYPE_PTRX;
   unlockBuff.reason = OAMS_RSN_OPERATORINITIATED;

   LOG_PRINT(LOG_INFO,"sendPtrxUnlockReq() :Sending Unlock Request");
   rVal = cfgSendMessage(&unlockBuff,sizeof(OamsCfgTrxhUnlockReq), ENT_OAMS_TRXH, OAMS_CFG_TRXH_UNLOCK_REQ,0);
   if (rVal == CFG_FAILURE)
   {
      LOG_PRINT(LOG_CRITICAL,"sendPtrxUnlockReq() :OAMS_CFG_TRXH_UNLOCK_REQ send Failed");/*TBD send log */
   }/*End of if*/
   if (rVal == CFG_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"sendPtrxUnlockReq() :OAMS_CFG_TRXH_UNLOCK_REQ  send SUCCESS");/*TBD send log */
      LOG_PRINT(LOG_INFO," State Changed To UNLOCK-IN-Progress");
      gPtrxData[ptrxTableApiRcvdPtr->ptrxId].ptrxState=unlockInProgress;  
   } /*End of if*/

}/*End of sendPtrxUnLockReq*/

/********************************* Function  Header********************************
   Function Name:       sendPtrxResetReq()
Parameters:          void
Return type:         void
Purpose:             To handle PTRX Reset Request procedure
Other Note:
 ************************************************************************************/

void sendPtrxResetReq()

{
   TrxTableApi *ptrxTableApiRcvdPtr = PNULL;
   sCmMsg* receivedCmMsgPtr = PNULL;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   ptrxTableApiRcvdPtr = (TrxTableApi *)( ((I_U8 *)receivedCmMsgPtr) + sizeof(sCmMsg));
   I_S32 rVal;

   OamsCfgTrxhTrxReset resetBuff;
   resetBuff.sysHdr.msgType = OAMS_CFG_TRXH_TRX_RESET;
   resetBuff.objId = ptrxTableApiRcvdPtr->ptrxId;

   LOG_PRINT(LOG_INFO,"sendPtrxResetReq() :Sending Trx Reset Request");
   rVal = cfgSendMessage(&resetBuff,sizeof(OamsCfgTrxhTrxReset), ENT_OAMS_TRXH, OAMS_CFG_TRXH_TRX_RESET,0);
   if (rVal == CFG_FAILURE)
   {
      LOG_PRINT(LOG_CRITICAL,"sendPtrxResetReq() :OAMS_CFG_TRXH_TRX_RESET send Failed");/*TBD send log */
   }/*End of if*/
   else 
   {
      LOG_PRINT(LOG_INFO,"sendPtrxResetReq() :OAMS_CFG_TRXH_TRX_RESET  send SUCCESS");/*TBD send log */
   } /*End of if*/


}/*End of sendPtrxUnLockReq*/

/********************************* Function  Header*****************************
   Function Name   : addTrxTableHandler()
Parameters   : None
Return type   : I_Void
Purpose      : It handle add trx request received from OMC/CLI
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void addTrxTableHandler()
{
   I_S32 dbStatus = -1;
   I_U8 numConfiguredTrxForBic = ZERO;
   I_U8 numAllowedTrxForBic = ZERO;
   I_U32 trxE1Id = ZERO;
   I_S32 status = CFG_FAILURE;
/* Trunk UsageType Changes : Starts */
   MccLinkResourceTableApi*  mccLinkTablePtr     = NULL;
   I_U32                     trxLapdTs;
   I_U32                     outRows             = 0;
   I_U16                     outSize             = 0;
   I_U16                     counter             = 0;
   I_U32 tmpE1 = 0;
   I_U32 tmpts = 0;
   I_U32 tsSts = 0;
   I_U8 cardNum = 0;
   I_U8 applTei=0;/*R2.8 changes, Mantis 24271*/
   TrxTsTeiTableApi trxTsTeiTableApi;
/* Trunk UsageType Changes : Ends */

   TrxTableApi* receivedMsgPtr = ( TrxTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   BicTableIndices bicTableIndexPtr;
   BicTableApi* bicTableApiPtr = PNULL;
   InFrameTrxE1TsTableApi* inFrameTrxTableApiPtr = PNULL;
   InFrameTrxE1TsTableIndices inFrameTrxTableIndices;
   BicTrxTsTableApi* bicTrxTsTableApiPtr = PNULL;
   BicTrxTsTableIndices bicTrxTsTableIndices;
   TrxTableIndices trxTableIndices;
   BicTrxTimeslotUsageTableIndices bicTrxTsUsage;

/* Changes for R2.2 : Start */
   I_U32  *allocatedTs = NULL;
   I_U32  *tmpTs = NULL;
   I_U32   outCount = 0;
/* Changes for R2.2 : End */

   LOG_PRINT(LOG_INFO,"Entering Function : addTrxTableHandler");

/* Trunk UsageType Changes : Starts */
    tmpE1 = INVALID_E1;
    tmpts = INVALID_TS;
    tsSts = SYS_TS_FREE;
    cardNum = ICCSELFCARD ;

/* Changes for R2.2 : Start */
	 if(TRX_LOCATION_BIC == receivedMsgPtr->trxLocation || TRX_LOCATION_IN_FRAME ==  receivedMsgPtr->trxLocation) /* Check Trx Location */
	 {   

      /* Check and Reserve Free LAPD Slot in MccLinkResource Table */
      dbStatus =  getFreeMccTrunkNumTsFromMccLinkTable(cardNum,SYS_TS_USAGE_ABIS_FREE,tmpE1,
                     tmpts,tsSts, &mccLinkTablePtr, &outRows,&outSize);
      if( (dbStatus != DBLIB_SUCCESS) || (outRows == ZERO) )
      {
         LOG_PRINT(LOG_MAJOR,"addTrxTableHandler: No Free entries found in MccLinkResource Table. ");
         cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS);  
         return ; 
      }
      LOG_PRINT(DEBUG,"Allocated MccE1:%d MccTs:%d",
          mccLinkTablePtr->mccTrunkNum,mccLinkTablePtr->mccTrunkTs);
   }
/* Trunk UsageType Changes : Ends */

   /* Performed Range Check on received request of add TrxTable */
   if(FALSE == trxTableRangeChk(receivedMsgPtr))
   {
      /* Range Check on Table TrxTable for Add TRX request is failed. 
       * Sending NACK to OMC/CLI */
      LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Range Check of Received Add \
            TrxTable Request is Failed");
      if(mccLinkTablePtr!=NULL)
        free(mccLinkTablePtr);
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;
   }
   else if(TRX_LOCATION_BIC == receivedMsgPtr->trxLocation || TRX_LOCATION_R2_BTS ==  receivedMsgPtr->trxLocation || TRX_LOCATION_R2_BTS_IP == receivedMsgPtr->trxLocation ||TRX_LOCATION_R3_BTS == receivedMsgPtr->trxLocation) /* Check Trx Location */
   {
      bicTableIndexPtr.bicId = receivedMsgPtr->bicId;
      dbStatus = getBicTable(&bicTableIndexPtr, &bicTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         /* bicId received in Add TrxTable Request is not Added at BSC.
          * Sending NACK to OMC/CLI  */
         LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : bicId : %d Received in Add \
               Trx Request is not Added at BSC",receivedMsgPtr->bicId);
         if(mccLinkTablePtr!=NULL)
         free(mccLinkTablePtr);
         cfgSendNackToCm(CM_ERR_REFERENCED_OBJECT_NOT_FOUND);
         return;
      }
      else
      {
         /* Check Bic is in Locked State*/
         if (bicTableApiPtr->adminState != LOCKED)
         { 
            LOG_PRINT(LOG_DEBUG,"addTrxTableHandler:Trx Addition is not allowed while parent Bts is in Unlock State");
            cfgSendNackToCm(CM_ERR_BTS_NOT_LOCKED_IN_DB);
            if(mccLinkTablePtr!=NULL)
         	    	free(mccLinkTablePtr);
            if(bicTableApiPtr!=NULL)
            		free(bicTableApiPtr);
            return;
         }
	 if (!((bicTableApiPtr->btsType == BIC && receivedMsgPtr->trxLocation == TRX_LOCATION_BIC) ||
		(bicTableApiPtr->btsType == R2_BTS && receivedMsgPtr->trxLocation == TRX_LOCATION_R2_BTS )||
    (bicTableApiPtr->btsType == R2_BTS_IP && receivedMsgPtr->trxLocation == TRX_LOCATION_R2_BTS_IP)||
    (bicTableApiPtr->btsType == R3_BTS && receivedMsgPtr->trxLocation == TRX_LOCATION_R3_BTS) ))
	 {/*Changes for R2.8*/
            LOG_PRINT(LOG_DEBUG,"addTrxTableHandler:Trx Location %d and Bts Type %d mismatch",
                receivedMsgPtr->trxLocation,bicTableApiPtr->btsType);
            cfgSendNackToCm(CM_ERR_BTS_TRX_TYPE_NOT_SAME);
            if(mccLinkTablePtr!=NULL)
 	            	free(mccLinkTablePtr);
            if(bicTableApiPtr!=NULL)
            		free(bicTableApiPtr);
            return;

	 }
         /* bicId received in Add TrxTable Request is Configured at BSC. 
          * Checking BIC is connected or not */
      if(TRX_LOCATION_R2_BTS_IP != receivedMsgPtr->trxLocation && TRX_LOCATION_R3_BTS != 
          receivedMsgPtr->trxLocation)/*Changes for R2.8*/
       {
         trxE1Id = bicTableApiPtr->e1Id;
         dbStatus = getTsNumTimeSlotPerTable(trxE1Id, SYS_TS_USAGE_ABIS_FREE, &allocatedTs, &outCount);
          if( (dbStatus != DBLIB_SUCCESS) || 
		(receivedMsgPtr->trxLocation == TRX_LOCATION_BIC && outCount< THREE )|| 
		(receivedMsgPtr->trxLocation == TRX_LOCATION_R2_BTS && outCount< TWO ) )
          {
             LOG_PRINT(LOG_MAJOR,"validityCheckFreeToAbis: Required Free Entries are not found in AbisTimeSlotTable. ");
             cfgSendNackToCm(CM_ERR_NO_FREE_TS_IN_TRUNKPORT);
            if(mccLinkTablePtr!=NULL)
       	    	free(mccLinkTablePtr);
            if(bicTableApiPtr!=NULL)
               free(bicTableApiPtr);
	          if (allocatedTs != NULL)
               free(allocatedTs);
             return;
          }

       }
         #if 0
         bicStatusIndexPtr.bicId = receivedMsgPtr->bicId;
         dbStatus = getBicStatusTable(&bicStatusIndexPtr, &bicStatusApiPtr);
         if(DBLIB_SUCCESS != dbStatus)
         {
            /* BIC is not Configured at BSC. Sending NACK to OMC/CLI */
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : bicId : %d Received in \
                  Add Trx Request is not Configured in BicStatus Table at BSC",
                  receivedMsgPtr->bicId);
            if(mccLinkTablePtr!=NULL)
        	    	free(mccLinkTablePtr);
            if(bicTableApiPtr!=NULL)
            		free(bicTableApiPtr);
	          if (allocatedTs != NULL)
               free(allocatedTs);
            cfgSendNackToCm(CM_ERR_REFERENCED_OBJECT_NOT_FOUND);
            return;
         }
         else
         {
            /* BIC is Configured at BSC.
             * Checking that BIC is Connected or Not */
            if(BIC_CONNECTED == bicStatusApiPtr->connectionState)
            {
               /* BIC is Connected */
               LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : bicId : %d Received in\
                     Add Trx Request is in Connected State",receivedMsgPtr->bicId);
               cfgSendNackToCm(CM_ERR_BTS_CONNECTED);
               if(mccLinkTablePtr!=NULL)
        	       	free(mccLinkTablePtr);
               if(bicTableApiPtr!=NULL)
               		free(bicTableApiPtr);
               if(bicStatusApiPtr !=NULL)
                  free(bicStatusApiPtr);
	             if (allocatedTs != NULL)
                  free(allocatedTs);
               return;
            }
            else
            {
               /* BIC is Not Connected */
               if(bicStatusApiPtr !=NULL)
                  free(bicStatusApiPtr);
            }
         }
         #endif 
         /* Check that number of already Configured TRXs for that BIC is less 
          * than allowed by BIC */
         numConfiguredTrxForBic = getNumConfiguredTrxForBic(receivedMsgPtr->bicId);
         numAllowedTrxForBic = bicTableApiPtr->numTrx;
         if(bicTableApiPtr!=NULL)
         free(bicTableApiPtr);

         if(numConfiguredTrxForBic >= numAllowedTrxForBic)
         {
            /* Number of TRXs Allowed in BIC are already Configured.
             * Sending NACK to OMC/CLI  */
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Max Possible TRXs  %d for \
                  bicId : %d Already configured", bicTableApiPtr->numTrx,receivedMsgPtr->bicId);
            cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
               if(mccLinkTablePtr!=NULL)
        	       	free(mccLinkTablePtr);
               if(bicTableApiPtr!=NULL)
               		free(bicTableApiPtr);
	             if (allocatedTs != NULL)
                  free(allocatedTs);
            return;
         }
  
         /* Check that no TRX is already Configured for trxPos received in 
          * Request for corresponding bicId */
         if(TRUE == isTrxPosAlreadyConfigured(receivedMsgPtr->trxLocation, 
                  receivedMsgPtr->trxPos,   receivedMsgPtr->bicId)
            )
         {
            /* Received trx position is already configured for BIC */
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Trx Position %d is already \
                  configured at BSC",receivedMsgPtr->trxPos);
            cfgSendNackToCm(CM_ERR_TRX_POSITION_ALREADY_USED);   
            if(mccLinkTablePtr!=NULL)
        	    	free(mccLinkTablePtr);
	          if (allocatedTs != NULL)
               free(allocatedTs);
            return;
         }

        if(TRX_LOCATION_R2_BTS_IP != receivedMsgPtr->trxLocation && TRX_LOCATION_R3_BTS != 
        receivedMsgPtr->trxLocation)/*Changes for R2.8*/
        {   
         /* Check that trxPos is also configured in BicTrxTs Table */
         bicTrxTsTableIndices.trxPos = receivedMsgPtr->trxPos;
         dbStatus = getBicTrxTsTable(&bicTrxTsTableIndices, &bicTrxTsTableApiPtr);
         if(DBLIB_SUCCESS != dbStatus)
         {
            /* For Bic Trx, trx position is not configured */
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : For Bic Add Trx Request,\
                  trxPosition is not Configured in BicTrxTsTable at BSC");
            cfgSendNackToCm(CM_ERR_TRX_POSITION_INVALID);
            if(mccLinkTablePtr!=NULL)
        	    	free(mccLinkTablePtr);
	          if (allocatedTs != NULL)
               free(allocatedTs);
            return;
         }
         else
         {
            free(bicTrxTsTableApiPtr);
         }
        } 
      }
   }
   else
   {
     //A6 inframe changes start
     I_U32 outRow = ZERO;
     I_U16 outSz = ZERO;
     InFrameTrxE1TsTableApi* InFrameTrxE1TsTableApiPtr = NULL;
     
     dbStatus = getallInFrameTrxE1TsTable(&InFrameTrxE1TsTableApiPtr, &outRow, &outSz);
     if(DBLIB_SUCCESS != dbStatus)
     {
       /* No TRX configured in DB */
       LOG_PRINT(LOG_INFO,"addTrxTableHandler : getallInFrameTrxE1TsTable failed");
     }
     else
     {
       if(outRow > MAX_INFRAME_TRX)
       {
         LOG_PRINT(LOG_INFO,"Maximum allowed inframe TRX's are :  %d ",MAX_INFRAME_TRX);
         cfgSendNackToCm(CM_ERR_MAX_INFRAME_TRX_ALREADY_CONFIGURED);   
         free(InFrameTrxE1TsTableApiPtr);
         
       }
     }
  //A6 inframe changes end
     
      /* TRX is In-Frame */
      /* Check that no TRX is already Configured for trxPos received in 
       * Request for In Frame TRX */
      if(TRUE == isTrxPosAlreadyConfigured(TRX_LOCATION_IN_FRAME, 
               receivedMsgPtr->trxPos,   receivedMsgPtr->bicId)
         )
      {
         /* Received trx position is already configured for In Frame TRX */
         LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Trx Position is already \
               configured at BSC");
         cfgSendNackToCm(CM_ERR_TRX_POSITION_ALREADY_USED);   
         free(mccLinkTablePtr);
         return;
      }

      /* Check that trxPos is also configured in InFrameTrxE1TsTable */
      inFrameTrxTableIndices.trxPos = receivedMsgPtr->trxPos;
      dbStatus = getInFrameTrxE1TsTable(&inFrameTrxTableIndices, 
            &inFrameTrxTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         /* For In-Frame Trx, trx position is not configured */
         LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : For In-Frame Add Trx Request,\
               trxPosition is not Configured in InFrameTrxE1TsTable at BSC");
         cfgSendNackToCm(CM_ERR_TRX_POSITION_INVALID);
         free(mccLinkTablePtr);
         return;
      }
      //A6 inframe changes start
      else
      {
         trxE1Id=inFrameTrxTableApiPtr->e1Id;
         LOG_PRINT(INFO,"Inframe E1Id : %d",trxE1Id);
         tmpTs=allocatedTs=malloc(sizeof(I_U32)*3);
         *allocatedTs=inFrameTrxTableApiPtr->startTs;
         LOG_PRINT(INFO,"Inframe tmpTs1 :%d",*allocatedTs);
         tmpTs++;
         *tmpTs = inFrameTrxTableApiPtr->startTs +1;
         LOG_PRINT(INFO,"Inframe tmpTs2 :%d",*tmpTs);
         tmpTs++;
         *tmpTs = inFrameTrxTableApiPtr->startTs +2;
         LOG_PRINT(INFO,"Inframe tmpTs3 :%d",*tmpTs);
         free(inFrameTrxTableApiPtr);
      }
      //A6 inframe changes end
   }

    if(TRX_LOCATION_R2_BTS_IP != receivedMsgPtr->trxLocation && TRX_LOCATION_R3_BTS != 
      receivedMsgPtr->trxLocation)/*Changes for R2.8*/
    { 
   /* Add TrxTable in DB */
   dbStatus = insertTrxTable(receivedMsgPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* DB Insert Failed. Sending NACK to OMC/CLI */
      LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : TrxTable Insert Failed");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);   
      if(mccLinkTablePtr!=NULL)
        	free(mccLinkTablePtr);
	    if (allocatedTs != NULL)
         free(allocatedTs);
   }
   else
   {
      /* TrxTable Inserted in DB Successfully. Sending Add Trx req to TRXH */
      /* Fixed Mantis : #4818 : Start */
/* Trunk UsageType Changes : Starts */
/* Mantis Fixed Starts- 7271 */
/* Changes for R2.2 : Start */
     
      tmpTs=allocatedTs;
      if(TRX_LOCATION_BIC == receivedMsgPtr->trxLocation || TRX_LOCATION_IN_FRAME ==  receivedMsgPtr->trxLocation) /* Check Trx Location */
      {      
         LOG_PRINT(LOG_INFO,"addTrxTableHandler : LAPD TS for TRX = %d",trxLapdTs);

         mccLinkTablePtr->extTrunkNum   = trxE1Id;
         mccLinkTablePtr->extTrunkTs    = *tmpTs;
         mccLinkTablePtr->mccLinkStatus = SYS_TS_ALLOCATED;
         mccLinkTablePtr->cardNum       = ICCSELFCARD;
         
         dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
         if(DBLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler :ICCSELFCARD Updation fails in MccLinkResourceTable");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);  
            if(mccLinkTablePtr!=NULL)
               free(mccLinkTablePtr);
	          if (allocatedTs != NULL)
               free(allocatedTs);
            return;
         } 

         mccLinkTablePtr->cardNum       = ICCMATECARD;

         dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
         if(DBLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCMATECARD Updation fails in MccLinkResourceTable");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);  
            if(mccLinkTablePtr!=NULL)
               free(mccLinkTablePtr);
	          if (allocatedTs != NULL)
               free(allocatedTs);
            return ;
         } 
	       dbStatus = updateRowAbisTimeSlotPerTable(trxE1Id,*tmpTs,SYS_TS_USAGE_LAPD_TRX);
       	 if(DBLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Abis TimeSlot Table Updation failed");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            /*ADD TRX Issue Fixed Starts Matntis 6686*/
            LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : Deleting Entry of TRX");
            trxTableIndices.ptrxId = receivedMsgPtr->ptrxId;
            if(deleteTrxTable(&trxTableIndices) != CLIB_SUCCESS)
            {
              LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : TRX Deletion Failed in Trx");
            }	      
            LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Free the reserved entry in MccLinkResourceTable");
            mccLinkTablePtr->extTrunkNum   = INVALID_E1;
            mccLinkTablePtr->extTrunkTs    = INVALID_TS;
            mccLinkTablePtr->mccLinkStatus = SYS_TS_FREE;
            mccLinkTablePtr->cardNum       = ICCSELFCARD;
            
            dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
            if(DBLIB_SUCCESS != dbStatus)
            {
              LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCSELFCARD Updation fails in MccLinkResourceTable");
              if(mccLinkTablePtr!=NULL)
                free(mccLinkTablePtr);
              if (allocatedTs != NULL)
                free(allocatedTs);
              return ;
            }        
            mccLinkTablePtr->cardNum       = ICCMATECARD;
            
            dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
            if(DBLIB_SUCCESS != dbStatus)
            {
              LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCMATECARD Updation fails in MccLinkResourceTable");
              if(mccLinkTablePtr!=NULL)
                free(mccLinkTablePtr);
              if (allocatedTs != NULL)
                free(allocatedTs);
              return ;
            } 
            if(mccLinkTablePtr!=NULL)
      	    	free(mccLinkTablePtr);
	          if (allocatedTs != NULL)
         	   	free(allocatedTs);
            return ;
        }
        tmpTs++;
        LOG_PRINT(LOG_INFO,"tmpTs after updating AbisTimeslotPerTAble is %d",*tmpTs); 
      }
      for (counter=0;counter<TWO;counter++)
      {
        LOG_PRINT(LOG_INFO,"addTrxTableHandler : updateRowAbisTimeSlotPerTable E1Id :%d,Ts=%d",trxE1Id,*tmpTs);
      	dbStatus = updateRowAbisTimeSlotPerTable(trxE1Id,*tmpTs,SYS_TS_USAGE_TRAFFIC);
      	if(DBLIB_SUCCESS != dbStatus)
       	{
           LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Abis TimeSlot Table Updation failed");
           cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
           /*ADD TRX Issue Fixed Starts Matntis 6686*/
           LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : Deleting Entry of TRX");
           trxTableIndices.ptrxId = receivedMsgPtr->ptrxId;
           if(deleteTrxTable(&trxTableIndices) != CLIB_SUCCESS)
           {
              LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : TRX Deletion Failed in Trx");
           }	
           LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Free the reserved entry in MccLinkResourceTable");
           mccLinkTablePtr->extTrunkNum   = INVALID_E1;
           mccLinkTablePtr->extTrunkTs    = INVALID_TS;
           mccLinkTablePtr->mccLinkStatus = SYS_TS_FREE;
           mccLinkTablePtr->cardNum       = ICCSELFCARD;
         
      	   dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
           if(DBLIB_SUCCESS != dbStatus)
       	   {
       	    	LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCSELFCARD Updation fails in MccLinkResourceTable");
              if(mccLinkTablePtr!=NULL)
 	    	        free(mccLinkTablePtr);
	            if (allocatedTs != NULL)
         		    free(allocatedTs);
            	return ;
       	   }        
       	   mccLinkTablePtr->cardNum       = ICCMATECARD;

       	   dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
       	   if(DBLIB_SUCCESS != dbStatus)
       	   {
       	    	LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCMATECARD Updation fails in MccLinkResourceTable");
              if(mccLinkTablePtr!=NULL)
 	    	        free(mccLinkTablePtr);
     	        if (allocatedTs != NULL)
		            free(allocatedTs);
             return ;
      	   } 
           if(mccLinkTablePtr!=NULL)
      	   	free(mccLinkTablePtr);
	         if (allocatedTs != NULL)
           	free(allocatedTs);
           return ;
       	}
       	tmpTs++;
      }
/* Changes for R2.2 : End */
/* Mantis Fixed Ends- 7271 */
/* Trunk UsageType Changes : Ends */

      status = populateTrxTsTeiTable(receivedMsgPtr,trxE1Id,allocatedTs);

      if(CFG_FAILURE == status)
      {
         LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : Error in Populating TrxTsTeiTable");
	       cfgSendNackToCm(CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA);

      	 if(TRX_LOCATION_BIC == receivedMsgPtr->trxLocation || TRX_LOCATION_IN_FRAME ==  receivedMsgPtr->trxLocation) /* Check Trx Location */
         {
             LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Free the reserved entry in MccLinkResourceTable");
             mccLinkTablePtr->extTrunkNum   = INVALID_E1;
             mccLinkTablePtr->extTrunkTs    = INVALID_TS;
             mccLinkTablePtr->mccLinkStatus = SYS_TS_FREE;
             mccLinkTablePtr->cardNum       = ICCSELFCARD;
             
             dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
             if(DBLIB_SUCCESS != dbStatus)
             {
                LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCSELFCARD Updation fails in MccLinkResourceTable");
                cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);  
                if(mccLinkTablePtr!=NULL)
                   free(mccLinkTablePtr);
	              if (allocatedTs != NULL)
	                 free(allocatedTs);
                return ;
             }        
             mccLinkTablePtr->cardNum       = ICCMATECARD;
             
             dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
             if(DBLIB_SUCCESS != dbStatus)
             {
                LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCMATECARD Updation fails in MccLinkResourceTable");
                cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);  
                if(mccLinkTablePtr!=NULL)
                   free(mccLinkTablePtr);
	              if (allocatedTs != NULL)
	                 free(allocatedTs);
                return ;
             } 
         }
         //A6 inframe changes start
         dbStatus=updateRowAbisTimeSlotPerTable(trxE1Id,*allocatedTs,SYS_TS_USAGE_ABIS_FREE);
         if(DBLIB_SUCCESS != dbStatus)
         {
           LOG_PRINT(LOG_MAJOR,"addTrxTableHandler :updateRowAbisTimeSlotPerTable Fails for e1Id : %d,Ts :%d",trxE1Id,*allocatedTs);
         }
         //A6 Inframe changes end

         /*ADD TRX Issue Fixed Starts Matntis 6686*/
         LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : Deleting Entry of TRX");
         trxTableIndices.ptrxId = receivedMsgPtr->ptrxId;
         if(deleteTrxTable(&trxTableIndices) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : TRX Deletion Failed in Trx");
	          cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
            if(mccLinkTablePtr!=NULL)
        	     free(mccLinkTablePtr);
	          if (allocatedTs != NULL)
	             free(allocatedTs);
            return;
         }
         if(receivedMsgPtr->trxLocation != TRX_LOCATION_IN_FRAME) //A6 inframe change
         {
           bicTrxTsUsage.tsUser = TS_USAGE_BICTRX ;
           bicTrxTsUsage.bicOrTrxId = receivedMsgPtr->ptrxId;
           if(deleteBicTrxTimeslotUsageTable(&bicTrxTsUsage) != CLIB_SUCCESS)
           {
             LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : TRX Deletion Failed in BicTrxTimeSlotUsageTable");
	           cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
             if(mccLinkTablePtr!=NULL)
        	      free(mccLinkTablePtr);
	           if (allocatedTs != NULL)
	              free(allocatedTs);
             return;
           }
         }
         /*ADD TRX Issue Fixed End*/
            if(mccLinkTablePtr!=NULL)
        	     free(mccLinkTablePtr);
	          if (allocatedTs != NULL)
	             free(allocatedTs);
	    return;
      }
      /* Fixed Mantis : #4818 : End */

      if ( receivedMsgPtr->trxLocation != TRX_LOCATION_R2_BTS)
      {     
         dbStatus = cfgInsertSwMNodeTableForTrx(receivedMsgPtr->ptrxId, receivedMsgPtr->trxLocation); /*CS3.0 Changes */
         if(DBLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : SwMNodeTable Insert Failed");
         
      	    if(TRX_LOCATION_BIC == receivedMsgPtr->trxLocation || TRX_LOCATION_IN_FRAME ==  receivedMsgPtr->trxLocation) /* Check Trx Location */
            { 
                LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : Free the reserved entry in MccLinkResourceTable");
                mccLinkTablePtr->extTrunkNum   = INVALID_E1;
                mccLinkTablePtr->extTrunkTs    = INVALID_TS;
                mccLinkTablePtr->mccLinkStatus = SYS_TS_FREE;
                mccLinkTablePtr->cardNum       = ICCSELFCARD;
                
                dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
                if(DBLIB_SUCCESS != dbStatus)
                {
                   LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCSELFCARD Updation fails in MccLinkResourceTable");
                   cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);  
                   if(mccLinkTablePtr!=NULL)
        	            free(mccLinkTablePtr);
	                 if (allocatedTs != NULL)
	                    free(allocatedTs);
                   return ;
                }
         
                mccLinkTablePtr->cardNum       = ICCMATECARD;
                
                dbStatus = updateMccLinkResourceTable(mccLinkTablePtr);
                if(DBLIB_SUCCESS != dbStatus)
                {
                   LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : ICCMATECARD Updation fails in MccLinkResourceTable");
                   cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);  
                   if(mccLinkTablePtr!=NULL)
        	            free(mccLinkTablePtr);
	                 if (allocatedTs != NULL)
	                    free(allocatedTs);
                   return ;
                } 
             }      
             cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);  
             /*ADD TRX Issue Fixed Starts Matntis 6686*/
             LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : Deleting Entry of TRX");
             trxTableIndices.ptrxId = receivedMsgPtr->ptrxId;
             if(deleteTrxTable(&trxTableIndices) != CLIB_SUCCESS)
             {
                LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : TRX Deletion Failed in Trx");
	              cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
                if(mccLinkTablePtr!=NULL)
        	         free(mccLinkTablePtr);
	              if (allocatedTs != NULL)
	                 free(allocatedTs);
                return ;
             }
           if(receivedMsgPtr->trxLocation != TRX_LOCATION_IN_FRAME) //A6 inframe changes 
           {
             bicTrxTsUsage.tsUser = TS_USAGE_BICTRX ;
             bicTrxTsUsage.bicOrTrxId = receivedMsgPtr->ptrxId;
             if(deleteBicTrxTimeslotUsageTable(&bicTrxTsUsage) != CLIB_SUCCESS)
             {
                LOG_PRINT(LOG_DEBUG,"addTrxTableHandler : TRX Deletion Failed in BicTrxTimeSlotUsageTable");
	              cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
                if(mccLinkTablePtr!=NULL)
        	         free(mccLinkTablePtr);
	              if (allocatedTs != NULL)
	                 free(allocatedTs);
                return;
             }
           }
             /*ADD TRX Issue Fixed End*/
	           cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
             if(mccLinkTablePtr!=NULL)
 	            	free(mccLinkTablePtr);
             if (allocatedTs != NULL)
	            	free(allocatedTs);
	           return; 
         }
      }  
      if(mccLinkTablePtr!=NULL)
         free(mccLinkTablePtr);
	    if (allocatedTs != NULL)
	       free(allocatedTs);

      status = sendAddTrxReq(receivedMsgPtr->ptrxId, receivedMsgPtr->trxLocation,receivedMsgPtr->bicId);      
      cfgSendAckToCm();
      setPtrxInitState(receivedMsgPtr->ptrxId);
   }
  }
  else
  {/*trxLocation=R3_BTS/R2_BTS_IP */
  if(allocateApplTei(TEI_USR_TRX,receivedMsgPtr->ptrxId, &applTei) != CLIB_SUCCESS)
      {
      LOG_PRINT(DEBUG,"applTei allocation Failed");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      if(mccLinkTablePtr!=NULL)
        	free(mccLinkTablePtr);
	    if (allocatedTs != NULL)
         free(allocatedTs);
      return;
      }
   /* Add TrxTable in DB */
   dbStatus = insertTrxTable(receivedMsgPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* DB Insert Failed. Sending NACK to OMC/CLI */
      LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : TrxTable Insert Failed for TRX %d",receivedMsgPtr->
          ptrxId);
      dbStatus=deAllocateApplTei((I_U16) applTei);
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);   
      if(mccLinkTablePtr!=NULL)
        	free(mccLinkTablePtr);
	    if (allocatedTs != NULL)
         free(allocatedTs);
      return;
   }
      trxTsTeiTableApi.ptrxId=receivedMsgPtr->ptrxId;
      trxTsTeiTableApi.trxTei= (I_U8)applTei;/* Mantsi 24271*/
      trxTsTeiTableApi.e1Id = 0xFFFFFFFF;
      trxTsTeiTableApi.lapdTs = INVALID_TS;
      trxTsTeiTableApi.lapdLinkStatus = 0xFFFFFFFF; 
      trxTsTeiTableApi.firstTsTraffic = INVALID_TS;
      trxTsTeiTableApi.secondTsTraffic= INVALID_TS;
      LOG_PRINT(LOG_DEBUG,"addTrxTableHandler: going to insert AppTei %d in TrxTsTeiTable",trxTsTeiTableApi.trxTei);
      dbStatus = insertTrxTsTeiTable(&trxTsTeiTableApi);
   if(dbStatus != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertTrxTsTeiTable : Insert in DB failed for trxid %d with error %s",
          receivedMsgPtr->ptrxId,dbStatus );
      trxTableIndices.ptrxId = receivedMsgPtr->ptrxId;
      if(deleteTrxTable(&trxTableIndices) != CLIB_SUCCESS)
      LOG_PRINT(LOG_MAJOR,"addTrxTableHandler : TRX Deletion Failed in DB");
      dbStatus=deAllocateApplTei((I_U16) applTei);
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);   
      if(mccLinkTablePtr!=NULL)
        	free(mccLinkTablePtr);
	    if (allocatedTs != NULL)
         free(allocatedTs);
      return;
   }
                     
      if(mccLinkTablePtr!=NULL)
         free(mccLinkTablePtr);
	    if (allocatedTs != NULL)
	       free(allocatedTs);

      status = sendAddTrxReq(receivedMsgPtr->ptrxId, receivedMsgPtr->trxLocation,receivedMsgPtr->bicId);      
      cfgSendAckToCm();
      setPtrxInitState(receivedMsgPtr->ptrxId);
  }  
   
   LOG_PRINT(LOG_INFO,"addTrxTableHAndler: After adding TRX");
   //getListValue();
   LOG_PRINT(LOG_INFO,"Exiting Function : addTrxTableHandler");
}


/********************************* Function  Header*****************************
   Function Name   : updateTrxTableHandler()
Parameters   : trxTableApiPtr :: TrxTableApi*
Return type   : I_Void
Purpose      : It handle update TrxTable request received from OMC/CLI
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void updateTrxTableHandler(TrxTableApi* trxTableApiPtr)
{
   TrxTableApi* receivedMsgPtr = ( TrxTableApi* )(((I_U8 *)gCfgMsgBuf ) + 
         sizeof(sCmMsg));
   I_S32  dbStatus = -1;
   I_Bool changeInRoParam = TRUE;

   LOG_PRINT(LOG_INFO,"Entering Function : updateTrxTableHandler");
   LOG_PRINT(LOG_DEBUG,"updateTrxTableHandler : Update Request is received \
         for ptrxId = %d",receivedMsgPtr->ptrxId);

   if(receivedMsgPtr->trxLocation == trxTableApiPtr->trxLocation)
      if(receivedMsgPtr->bicId == trxTableApiPtr->bicId)
         if(receivedMsgPtr->trxPos == trxTableApiPtr->trxPos)
         {
            changeInRoParam = FALSE;
         }

   if(TRUE == changeInRoParam)
   {
      /* Received Request has some Read Only parameters changed.
       * Update TrxTable is rejected. Sending NACK to OMC/CLI  */
      LOG_PRINT(LOG_INFO,"updateTrxTableHandler : Received TrxTable Update \
            Request has changed RO Parameters");
      cfgSendNackToCm(CM_ERR_CHANGE_IN_ROSC_PARAM);
   }
   else
   {
      /* Received Request has all Read Only parameters unchanged.
       * Checking Is there any change in RW parameters */
      if((receivedMsgPtr->antennaID == trxTableApiPtr->antennaID) && 
            (receivedMsgPtr->rfPathGain == trxTableApiPtr->rfPathGain)
         )
      {
         /* No change in RW parameters. Rejecting TrxTable Update Request. */
         LOG_PRINT(LOG_INFO,"updateTrxTableHandler : Received Request has \
               no change in Parameters");
         //cfgSendNackToCm(CM_ERR_UNKNOWN);
          cfgSendAckToCm(); // Mantis:7217
      }
      else
      {
         /* The PowerSavingMode parameter in DB should not get updated */
         receivedMsgPtr->pwrSavingMode = trxTableApiPtr->pwrSavingMode;

         /* Received Request has RW parameters changed. Going to Update TrxTable */
         dbStatus = updateTrxTable(receivedMsgPtr);
         if(DBLIB_SUCCESS == dbStatus) 
         {
            /* TrxTable Updation is Successfull */
            LOG_PRINT(LOG_INFO,"updateTrxTableHandler : TrxTable Updation is Successfull");
            cfgSendAckToCm();
         }
         else
         {
            /* TrxTable Updation is Failed*/
            LOG_PRINT(LOG_INFO,"updateTrxTableHandler : TrxTable Updation is Failed");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         }
      } 
   }
   LOG_PRINT(LOG_INFO,"Exiting Function : updateTrxTableHandler");
}


/********************************* Function  Header*****************************
   Function Name   : prepAndSndSwitchConForTrx()
Parameters   : ptrxId :: I_U32
Return type   : I_Void
Purpose      : It calculate first E1 & TS and then get corresponding MCC E1 
& TS and send Switch Connect message to GRHM.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void prepAndSndSwitchConForTrx(I_U32 ptrxId)
{
   I_S32 dbStatus = -1;
   I_U8 status = CFG_FAILURE;
   I_U32 firstE1 = ZERO;
   I_U32 firstTs = ZERO;
   I_U32 secE1 = ZERO;
   I_U32 secTs = ZERO;
   TrxTsTeiTableApi* trxTsTeiTableApiPtr = NULL;
   TrxTsTeiTableIndices trxTsTeiTableIndices;
   OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;

   LOG_PRINT(LOG_INFO,"Entering Function : prepAndSndSwitchConForTrx");
   LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchConForTrx : Received ptrxId : %d",ptrxId);

   /* Get first E1 & Ts corresponding to the received ptrxId */
   trxTsTeiTableIndices.ptrxId = ptrxId;
   dbStatus = getTrxTsTeiTable(&trxTsTeiTableIndices, &trxTsTeiTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus) 
   {
      /* TrxTsTeiTable is not populated for ptrxId received */
      LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchConForTrx : TrsTsTeiTable not \
            populated for ptrxId : %d",ptrxId);
   }
   else
   {
      firstE1 = trxTsTeiTableApiPtr->e1Id;
      firstTs = trxTsTeiTableApiPtr->lapdTs;
      /* Get second E1 & Ts */ 
      status = getMccE1Ts(firstE1, firstTs, &secE1, &secTs);
      if(CFG_FAILURE == status)
      {
         /* Mcc E1 or Ts not configured */
         LOG_PRINT(LOG_INFO,"prepAndSndSwitchConForTrx : Mcc E1 & Ts not Configured");
      }
      else
      {
         /* Prepare & Send Switch Connect Msg */
         oamsCfgGrhmSwitchConnect.firstE1Num = firstE1;
         oamsCfgGrhmSwitchConnect.firstTimeSlotNum = firstTs;
         oamsCfgGrhmSwitchConnect.secondE1Num = secE1;
         oamsCfgGrhmSwitchConnect.secondTimeSlotNum = secTs;
         LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchConForTrx : First E1 : %d, \
               First Ts : %d, SecE1 : %d, SecTs : %d",\
               firstE1, firstTs, secE1, secTs);

         cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
               ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);
      }
      /*Changes for HA-R2.5.5*/ 
      if(CFG_READY == gCfgState || gCfgState == CFG_BPM_SW_QUERY)
      {
         if(gCfgStandbySlotId != 0)
         { 
             sendLapdSwitchReqToPeerCfg(firstE1, firstTs,CFG_MAKE_SWITCH,CFG_SWITCH_TRX_ADD_DEL);
         }
      }
      /*Changes for HA-R2.5.5*/ 
      free(trxTsTeiTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : prepAndSndSwitchConForTrx");
}


/********************************* Function  Header*****************************
   Function Name   : addConfiguredTrxs()
Parameters   : None
Return type   : I_Void
Purpose      : It add all TRXs in BSC those configured in TrxTable at the 
time OAM Startup.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void addConfiguredTrxs()
{
   I_S32 dbStatus = -1, status = CFG_FAILURE;
   I_U32 outRow = ZERO,outRow1 = ZERO;
   I_U16 outSz = ZERO,outSz1 = ZERO;
   I_U32 index = ZERO;
   TrxTableApi* trxTableApiPtr = NULL;
   I_PVoid origPtr = NULL;
   I_S32 retVal = CFG_FAILURE;
   gSentAddTrxReqAtInitNum = 0;
   OamsCfgTrxhAddTrxReq oamsCfgTrxhAddTrxReq;
   TrxTsTeiTableApi trxTsTeiTableApi;
   /*Changes for R2.8*/
   ApplTeiPoolTableSecIndices          applTeiPoolTableSecIndices;/*Changes for R2.8*/
   ApplTeiPoolTableApi*                applTeiPoolTableOutData =PNULL;
   ApplTeiPoolTableApi*                applTeiPoolTable1 =PNULL;
   LOG_PRINT(LOG_INFO,"Entering Function : addConfiguredTrxs");

   dbStatus = getallTrxTable(&trxTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* No TRX configured in DB */
      LOG_PRINT(LOG_INFO,"addConfiguredTrxs : No TRX Configured");
   }
   else
   {
      /* Send Add Trx Request for all ptrxIds */
      origPtr = (I_PVoid)trxTableApiPtr;
      for(index = 0; index < outRow; index++)
      {
         trxTableApiPtr = (TrxTableApi *)(((I_U8 *)(origPtr)) + (index * outSz));
         /* Initialize Trx Data Structure */
         gPtrxData[trxTableApiPtr->ptrxId].PTRXID = trxTableApiPtr->ptrxId;
         if(trxTableApiPtr->adminState == ZERO)
	       {
            gPtrxData[trxTableApiPtr->ptrxId].ptrxState = locked;   
	       }
         else
	       {
            gPtrxData[trxTableApiPtr->ptrxId].ptrxState = unlocked;
	       }

         //status = populateTrxTsTeiTable(trxTableApiPtr->ptrxId, 
         //      trxTableApiPtr->trxLocation, trxTableApiPtr->bicId);
         if((trxTableApiPtr->trxLocation!=TRX_LOCATION_R2_BTS_IP) && (trxTableApiPtr->trxLocation!=TRX_LOCATION_R3_BTS))/*Changes for R2.8 */
         {   
          status = populateTrxTsTeiTableOnReboot(trxTableApiPtr);
          if(CFG_SUCCESS == status)
          {
            oamsCfgTrxhAddTrxReq.ptrxId = trxTableApiPtr->ptrxId;
            retVal = cfgSendMessage(&oamsCfgTrxhAddTrxReq, sizeof(OamsCfgTrxhAddTrxReq), 
                  ENT_OAMS_TRXH, OAMS_CFG_TRXH_ADD_TRX_REQ, 0);
            if(retVal == CFG_SUCCESS)
            {
               gSentAddTrxReqAtInitNum++;
            }
          }
         }
         else/*Changes for R2.8 */
         {
          applTeiPoolTableSecIndices.applTeiUser=(I_U8)TEI_USR_TRX;
          applTeiPoolTableSecIndices.userId=trxTableApiPtr->ptrxId;  
          dbStatus = getSecApplTeiPoolTable(&applTeiPoolTableSecIndices, &applTeiPoolTableOutData,
          &outRow1, &outSz1);
          if(dbStatus == DBLIB_SUCCESS)
          {
          applTeiPoolTable1=(ApplTeiPoolTableApi*)((I_U8 *)applTeiPoolTableOutData);  
          trxTsTeiTableApi.ptrxId=trxTableApiPtr->ptrxId;
          trxTsTeiTableApi.trxTei=applTeiPoolTable1->applTei;
          trxTsTeiTableApi.e1Id = 0xFFFFFFFF;
          trxTsTeiTableApi.lapdTs = INVALID_TS;
          trxTsTeiTableApi.lapdLinkStatus = 0xFFFFFFFF; 
          trxTsTeiTableApi.firstTsTraffic = INVALID_TS;
          trxTsTeiTableApi.secondTsTraffic= INVALID_TS;
          dbStatus = insertTrxTsTeiTable(&trxTsTeiTableApi);
             if(dbStatus == DBLIB_SUCCESS)
             {
             oamsCfgTrxhAddTrxReq.ptrxId = trxTableApiPtr->ptrxId;
             retVal = cfgSendMessage(&oamsCfgTrxhAddTrxReq, sizeof(OamsCfgTrxhAddTrxReq), 
                  ENT_OAMS_TRXH, OAMS_CFG_TRXH_ADD_TRX_REQ, 0);
             if(retVal == CFG_SUCCESS)
             gSentAddTrxReqAtInitNum++;
             }
             else
             {
             LOG_PRINT(LOG_INFO,"insertTrxTsTeiTable : Insert in DB failed for trxid %d with error %s",
             trxTableApiPtr->ptrxId,dbStatus );
             //dbStatus=deAllocateApplTei((I_U16) applTeiPoolTable1->applTei); Mantis #0031537 Gaurav Sinha 20 July 2016
             }  
          if(applTeiPoolTableOutData!=NULL)
            free(applTeiPoolTableOutData);   
          }
          else
          {  
          LOG_PRINT(MAJOR,"getSecApplTeiPoolTable Failed for trxId %d",trxTableApiPtr->ptrxId);
          }
         
         }  
      }
      free(origPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : addConfiguredTrxs");
}


/********************************* Function  Header*****************************
   Function Name   : sendAddTrxReq()
Parameters   : ptrxId  :: I_U32
trxType :: I_U8
bicId     :: I_U32
Return type   : I_S32
Purpose      : It populate TrxTsTeiTable and send Add Trx request to TRXH.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_S32 sendAddTrxReq(I_U32 ptrxId, I_U8 trxType, I_U32 bicId)
{
   OamsCfgTrxhAddTrxReq oamsCfgTrxhAddTrxReq;

   LOG_PRINT(LOG_INFO,"Entering Function : sendAddTrxReq");
   LOG_PRINT(LOG_DEBUG,"sendAddTrxReq : Received ptrxId : %d, trxType : %d",\
         ptrxId, trxType);

   oamsCfgTrxhAddTrxReq.ptrxId = ptrxId;
   cfgSendMessage(&oamsCfgTrxhAddTrxReq, sizeof(OamsCfgTrxhAddTrxReq), 
         ENT_OAMS_TRXH, OAMS_CFG_TRXH_ADD_TRX_REQ, 0);

   LOG_PRINT(LOG_INFO,"Exiting Function : sendAddTrxReq");
   return CFG_SUCCESS;
}


/********************************* Function  Header*****************************
   Function Name   : sendDelTrxReq()
Parameters   : ptrxId  :: I_U32
Return type   : I_Void
Purpose      : It delete entry from TrxTsTeiTable corresponding to the 
received ptrxId and send Add Trx request to TRXH.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void sendDelTrxReq(I_U32 ptrxId)
{
   OamsCfgTrxhDelTrxReq oamsCfgTrxhDelTrxReq;

   LOG_PRINT(LOG_INFO,"Entering Function : sendDelTrxReq");
   LOG_PRINT(LOG_DEBUG,"sendDelTrxReq : Received ptrxId : %d", ptrxId);

   /* Prepare & Send Del Trx request to TRXH */
   oamsCfgTrxhDelTrxReq.ptrxId = ptrxId;
   cfgSendMessage(&oamsCfgTrxhDelTrxReq, sizeof(oamsCfgTrxhDelTrxReq),
         ENT_OAMS_TRXH, OAMS_CFG_TRXH_DEL_TRX_REQ, 0);

   LOG_PRINT(LOG_INFO,"Exiting Function : sendDelTrxReq");
}


/********************************* Function  Header*****************************
   Function Name   : prepAndSndSwitchDisConForTrx()
Parameters   : ptrxId :: I_U32
Return type   : I_Void
Purpose      : It calculate first E1 & TS and then get corresponding MCC E1 
& TS and send Switch Disconnect message to GRHM.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void prepAndSndSwitchDisConForTrx(I_U32 ptrxId)
{
   I_S32 dbStatus = -1;
   I_U8 status = CFG_FAILURE;
   I_U32 firstE1 = ZERO;
   I_U32 firstTs = ZERO;
   I_U32 secE1 = ZERO;
   I_U32 secTs = ZERO;
   TrxTsTeiTableApi* trxTsTeiTableApiPtr = NULL;
   TrxTsTeiTableIndices trxTsTeiTableIndices;
   OamsCfgGrhmSwitchDisconnect oamsCfgGrhmSwitchDisconnect;

   LOG_PRINT(LOG_INFO,"Entering Function : prepAndSndSwitchDisConForTrx");
   LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchDisConForTrx : Received ptrxId : %d",ptrxId);

   /* Get first E1 & Ts corresponding to the received ptrxId */
   trxTsTeiTableIndices.ptrxId = ptrxId;
   dbStatus = getTrxTsTeiTable(&trxTsTeiTableIndices, &trxTsTeiTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus) 
   {
      /* TrxTsTeiTable is not populated for ptrxId received */
      LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchDisConForTrx : TrsTsTeiTable not \
            populated for ptrxId : %d",ptrxId);
   }
   else
   {
      firstE1 = trxTsTeiTableApiPtr->e1Id;
      firstTs = trxTsTeiTableApiPtr->lapdTs;
      /* Get second E1 & Ts */ 
      status = getMccE1Ts(firstE1, firstTs, &secE1, &secTs);
      if(CFG_FAILURE == status)
      {
         /* Mcc E1 or Ts not configured */
         LOG_PRINT(LOG_INFO,"prepAndSndSwitchDisConForTrx : Mcc E1 & Ts not Configured");
      }
      else
      {
         oamsCfgGrhmSwitchDisconnect.firstE1Num = firstE1;
         oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = firstTs;
         oamsCfgGrhmSwitchDisconnect.secondE1Num = secE1;
         oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = secTs;
         LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchDisConForTrx : First E1 : %d, \
               First Ts : %d, SecE1 : %d, SecTs : %d",
               firstE1, firstTs, secE1, secTs);

         cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchConnect),
               ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);
      }

      /*Changes for HA-R2.5.5*/ 
      if(CFG_READY == gCfgState || gCfgState == CFG_BPM_SW_QUERY)
      {
         if(gCfgStandbySlotId != 0)
         { 
             sendLapdSwitchReqToPeerCfg(firstE1, firstTs,CFG_BREAK_SWITCH,CFG_SWITCH_TRX_ADD_DEL);
         }
      }
      /*Changes for HA-R2.5.5*/ 

      /* Free the Entry Reserved in MccLinkResource Table */
      dbStatus=freeMccLinkResourceTablebyExternalE1Ts(firstE1,firstTs,INVALID_E1,INVALID_TS,SYS_TS_FREE);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"prepAndSndSwitchDisConForTrx : Db wrapper freeMccLinkResourceTablebyExternalE1Ts Fails");
      }
 
      free(trxTsTeiTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : prepAndSndSwitchDisConForTrx");
}


/********************************* Function  Header*****************************
   Function Name   : setPtrxInitState()
Parameters   : ptrxId :: I_U32
Return type   : I_Void
Purpose      : It set the initial state of gPtrxData corresponding to the 
received ptrxId.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void setPtrxInitState(I_U32 ptrxId)
{
   gPtrxData[ptrxId].PTRXID = ptrxId;
   gPtrxData[ptrxId].ptrxState = locked;
}


/********************************* Function  Header*****************************
   Function Name   : isTrxPosAlreadyConfigured()
Parameters   : trxType :: I_U8
trxPos  :: I_U8
bicId     :: I_U32
Return type   : I_Bool
Purpose      : It checks whether TRX Position is already configured for other 
TRX. It returns TRUE if position is already configured for any
other TRX, otherwise it returns FALSE.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Bool isTrxPosAlreadyConfigured(I_U8 trxType, I_U8 trxPos, I_U32 bicId)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_Bool retVal = TRUE;
   TrxTableApi* trxTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"Entering Function : isTrxPosAlreadyConfigured");
   LOG_PRINT(LOG_DEBUG,"isTrxPosAlreadyConfigured : Received TrxType : %d, \
         TrxPosition : %d, BtsId : %d",trxType, trxPos, bicId);

   if(TRX_LOCATION_BIC == trxType || TRX_LOCATION_R2_BTS == trxType ||TRX_LOCATION_R2_BTS_IP == trxType
       ||TRX_LOCATION_R3_BTS == trxType)/*Changes for R2.8*/
   {
      dbStatus = getTerTrxTable(bicId, trxPos, &trxTableApiPtr, &outRow,
            &outSz);
      if(DBLIB_SUCCESS != dbStatus)
      {
         retVal = FALSE;
         LOG_PRINT(LOG_INFO,"isTrxPosAlreadyConfigured : No TRX is configured \
               for received Trx Position");
      }
      else
      {
         LOG_PRINT(LOG_DEBUG,"isTrxPosAlreadyConfigured : ptrxId : %d is \
               configured at TrxPos : %d",trxTableApiPtr->ptrxId, trxPos);
         free(trxTableApiPtr);
      }
   }
   else if(TRX_LOCATION_IN_FRAME == trxType)
   {
      dbStatus = getQuatTrxTable(trxType, trxPos, &trxTableApiPtr, &outRow,
            &outSz);
      if(DBLIB_SUCCESS != dbStatus)
      {
         retVal = FALSE;
         LOG_PRINT(LOG_INFO,"isTrxPosAlreadyConfigured : No TRX is configured \
               for received Trx Position");
      }
      else
      {
         LOG_PRINT(LOG_DEBUG,"isTrxPosAlreadyConfigured : ptrxId : %d is \
               configured at TrxPos : %d",trxTableApiPtr->ptrxId, trxPos);
         free(trxTableApiPtr);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"isTrxPosAlreadyConfigured : Invalid Trx Location \
            Value Received");
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isTrxPosAlreadyConfigured");
   return retVal;
}

/*Changes For R2.2 : Start */
void sendIndicationToBic(TrxTableApi* trxTableApiPtr)
{
	 I_U32 rVal; 
	 LOG_PRINT(DEBUG,"Entering into sendIndicationToBic function");
	 switch (((SysHdr*) gCfgMsgBuf)->msgType)
	 {
			case OAMS_TRXH_CFG_ADD_TRX_RESP:
				 {
			OamsCfgBichAddTrxInd  addTrxIndBuff;
						addTrxIndBuff.sysHdr.msgType=OAMS_CFG_BICH_ADD_TRX_INDICATION;
						addTrxIndBuff.bicId=trxTableApiPtr->bicId;
						addTrxIndBuff.pTrxId=trxTableApiPtr->ptrxId;
			LOG_PRINT(LOG_INFO,"sendIndicationToBic() :Sending Trx Add Indication");
			rVal = cfgSendMessage(&addTrxIndBuff,sizeof(OamsCfgBichAddTrxInd), ENT_OAMS_BICH, OAMS_CFG_BICH_ADD_TRX_INDICATION,0);
			if (rVal == CFG_FAILURE)
			{
				 LOG_PRINT(LOG_CRITICAL,"sendPtrxUnlockReq() :OAMS_CFG_BICH_ADD_TRX_INDICATION send Failed");/*TBD send log */
			}/*End of if*/
			if (rVal == CFG_SUCCESS)
			{
				 LOG_PRINT(LOG_INFO,"sendPtrxUnlockReq() :OAMS_CFG_BICH_ADD_TRX_INDICATION send SUCCESS");/*TBD send log */
			} /*End of if*/
	 }
	 break;
			case OAMS_TRXH_CFG_DEL_TRX_RESP:
				 {
			OamsCfgBichDelTrxInd  delTrxIndBuff;
						delTrxIndBuff.sysHdr.msgType=OAMS_CFG_BICH_DEL_TRX_INDICATION;
						delTrxIndBuff.bicId=trxTableApiPtr->bicId;
						delTrxIndBuff.pTrxId=trxTableApiPtr->ptrxId;
			LOG_PRINT(LOG_INFO,"sendIndicationToBic() :Sending Trx Del Indication");
			rVal = cfgSendMessage(&delTrxIndBuff,sizeof(OamsCfgBichDelTrxInd), ENT_OAMS_BICH, OAMS_CFG_BICH_DEL_TRX_INDICATION,0);
			if (rVal == CFG_FAILURE)
			{
				 LOG_PRINT(LOG_CRITICAL,"sendPtrxUnlockReq() :OAMS_CFG_BICH_DEL_TRX_INDICATION send Failed");/*TBD send log */
			}/*End of if*/
			if (rVal == CFG_SUCCESS)
			{
				 LOG_PRINT(LOG_INFO,"sendPtrxUnlockReq() :OAMS_CFG_BICH_DEL_TRX_INDICATION send SUCCESS");/*TBD send log */
			} /*End of if*/
            
            /*Changes PCU R2.5 Aricent -- START*/ 
            /* Delete row from RlcMac PS performance counter table */
            deleteRowFromPsPerfCounterTableForTrx(trxTableApiPtr->ptrxId);
            /*Changes PCU R2.5 Aricent -- END*/ 
	 }

	 }
}
/*Changes For R2.2 : End */

 /* Trx Block Feature : Starts */
/********************************* Function  Header*****************************
Function Name   : sendBlockReqForTrx()
Parameters   : ptrxId :: I_U32
Return type   : I_Void
Purpose      : It sends the Block Request to TRXH. 
Other Note   : Added in R2.5.1 for TRX BLOCK feature
 *******************************************************************************/
I_Void sendBlockReqForTrx(I_U32 ptrxId)
{
   OamsCfgTrxhBlockReq blockBuff;
   I_U32 rVal = CFG_FAILURE;
   LOG_PRINT(LOG_INFO,"Entering sendBlockReqForTrx()");

   blockBuff.sysHdr.msgType = OAMS_CFG_TRXH_BLOCK_REQ;
   blockBuff.objId = ptrxId;
   blockBuff.objType = OAMS_OBJTYPE_PTRX;
   blockBuff.reason = OAMS_RSN_OPERATORINITIATED;

   LOG_PRINT(LOG_INFO,"Sending TRX Block Request");
   rVal = cfgSendMessage(&blockBuff,sizeof(OamsCfgTrxhBlockReq), ENT_OAMS_TRXH, OAMS_CFG_TRXH_BLOCK_REQ,0);
   if (rVal == CFG_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"OAMS_CFG_TRXH_BLOCK_REQ  send SUCCESS");
      gPtrxData[ptrxId].ptrxState = blockInProgress;
      LOG_PRINT(LOG_INFO,"State Changed To Block-In-Progress");
   } /*End of if*/
   else
   {
       LOG_PRINT(LOG_CRITICAL, "OAMS_CFG_TRXH_BLOCK_REQ send Failed");
   }/*End of if*/

   cfgSendAckToCm();
   LOG_PRINT(LOG_INFO,"Exiting sendBlockReqForTrx()");
}
/********************************* Function  Header*****************************
Function Name   : ptrxObjectBlockInProgressHandler()
Parameters   : 
Return type   : I_Void
Purpose      : It handles the messages which are received when Trx is in 
               BlockInProgress state. 
Other Note   : Added in R2.5.1 for TRX BLOCK feature
 *******************************************************************************/
I_Void ptrxObjectBlockInProgressHandler()
{
   TrxTableApi *trxTableRcvPtr=NULL;
   OamsTrxhCfgBlockResp *oamsTrxhCfgBlockRespPtr=NULL;
   sCmMsg* receivedCmMsgPtr=NULL;
   TrxTableIndices trxTableIndex;
   TrxTableApi* trxTableDbPtr = PNULL;
   OamsCfgTrxhLockReq lockBuff;
   I_U8  index = 0;
   I_U32 ptrxId;
   I_S32 rVal; 

   LOG_PRINT(LOG_INFO,"Entering ptrxObjectBlockInProgressHandler()");


   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_TRXTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         trxTableRcvPtr = (TrxTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         LOG_PRINT(LOG_INFO,"BSC_API_SET_TRXTABLE message is received during Block In Progress for ptrxId=%u, sending Nack",trxTableRcvPtr->ptrxId);
         cfgSendNackToCm(CM_ERR_TRX_BLOCK_IN_PROGRESS);
         break; 
      case OAMS_TRXH_CFG_BLOCK_RESP:
         oamsTrxhCfgBlockRespPtr = (OamsTrxhCfgBlockResp *)gCfgMsgBuf;
         LOG_PRINT(LOG_INFO,"OAMS_TRXH_CFG_BLOCK_RESP for ptrxId = %u", oamsTrxhCfgBlockRespPtr->objId);
         {
            lockBuff.sysHdr.msgType = OAMS_CFG_TRXH_LOCK_REQ;
            lockBuff.objId = oamsTrxhCfgBlockRespPtr->objId;
            lockBuff.objType = OAMS_OBJTYPE_PTRX;
            lockBuff.reason = OAMS_RSN_OPERATORINITIATED;

            LOG_PRINT(LOG_INFO,"Sending TRX Lock Request");
            rVal = cfgSendMessage(&lockBuff,sizeof(OamsCfgTrxhLockReq), ENT_OAMS_TRXH, OAMS_CFG_TRXH_LOCK_REQ,0);
            if (rVal == CFG_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"OAMS_CFG_TRXH_LOCK_REQ  send SUCCESS");
               gPtrxData[oamsTrxhCfgBlockRespPtr->objId].ptrxState = lockInProgress; 
            } /*End of if*/
            else
            {
                LOG_PRINT(LOG_CRITICAL, "OAMS_CFG_TRXH_LOCK_REQ send Failed");
            }/*End of if*/
         } 
         break;   
      default:
         LOG_PRINT(LOG_CRITICAL,"Unexpected Message is received ");

   }/*end of switch (((SysHdr*) gCfgMsgBuf)->msgType)*/
   LOG_PRINT(LOG_INFO,"Exiting ptrxObjectBlockInProgressHandler()");
}
/* Trx Block Feature : Ends */

/********************************* Function  Header*****************************
Function Name   : sndSwitchConForTrxsAtSwitchOver()
Parameters   : None
Return type   : I_Void
Purpose      : It calculate first E1 & TS and then call function 
prepAndSndSwitchConForTrx that prepare & send Switch Connect 
to GRHM.
Other Note   : Added For BSC HA-R2.5.5 
 *******************************************************************************/
I_Void sndSwitchConForTrxsAtSwitchOver()
{
    I_S32 dbStatus = -1;
    I_U32 outRow = ZERO, index = ZERO;
    I_U16 outSz;
    I_U32 tsUser = ZERO;
    I_U32 e1Id = ZERO, e1Ts = ZERO, i = ZERO;
    I_S32 status = ZERO;
    TrxTableApi *trxTableApiPtr = NULL;
    I_PVoid origPtr = NULL;
     /*Changes For R2.2 :Start */

    LOG_PRINT(LOG_INFO,"Entering Function : sndSwitchConForTrxsAtSwitchOver");
    dbStatus = getallTrxTable(&trxTableApiPtr,&outRow,&outSz);
    if(DBLIB_SUCCESS != dbStatus)
    {
        LOG_PRINT(LOG_MAJOR,"sndSwitchConForTrxsAtSwitchOver : Get Form BicTable Failed");
    }
    else
    {
        origPtr =  trxTableApiPtr;
        for(index = 0; index < outRow; index++)
        {
            trxTableApiPtr = (TrxTableApi *)(((I_U8 *)(origPtr)) + (index * outSz));

	          if(  (trxTableApiPtr->trxLocation == TRX_LOCATION_BIC) || 
            		 (trxTableApiPtr->trxLocation == TRX_LOCATION_IN_FRAME)  )
            {
                prepAndSndSwitchConForTrx(trxTableApiPtr->ptrxId); 
            }
        }
        free(origPtr);
    }
    LOG_PRINT(LOG_INFO,"Exiting Function : sndSwitchConForTrxsAtSwitchOver");
}

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change
   BSC CS2.2      Kapil Tyagi     Added Functions:
   - addTrxTableHandler
   - updateTrxTableHandler
   - prepAndSndSwitchConForTrx
   - addConfiguredTrxs
   - sendAddTrxReq
   - prepAndSndSwitchDisConForTrx
   - setPtrxInitState
   - isTrxPosAlreadyConfigured
Modifications:
- PhysicalTrxPreconfigTable is removed 
in CS2.2 & it is replaced by TrxTable.
Removed Functions:
- setPtrxTableHandler
 ************************************** End *********************************/
