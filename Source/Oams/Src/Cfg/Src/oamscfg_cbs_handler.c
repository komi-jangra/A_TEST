/************************************************************* File Header ***
File Name      : oamscfg_cbs_handler.c
Purpose        : This file contains function defintions required for handling
                 of cbs related requests.
Project        : BSC
Subsystem      : OAMS 
Author         : Aricent 
CSCI id        :
Version        :
 ******************************************************************** End ***/

#include <oamscfg_includes.h>

/******************************* Function  Header*****************************
   Function Name :    sendBreakCbsipAddressReqForAllServerToCbsIf()
Parameters    : None
Return type   : I_Void
Purpose       : Make or Breaks the TCP/IP Connection with CBS depending upon 
                the msgType passed
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendBreakCbsipAddressReqForAllServerToCbsIf()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   CbsConfigurationTableApi         *cbsConfigData = NULL;
   CbsConfigurationTableApi         *tempCbsConfigData = NULL;
   I_U32                            outCount; 
   I_U16                            outSize; 
   I_S32                            retCode;
   I_U32                            index;

   retCode = getallCbsConfigurationTable( &cbsConfigData, &outCount, &outSize); 
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"No Data exists in cbsConfigurationTable");
      LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
      return;
   }
   
   for ( index=0; index<outCount; index++ )
   {
      tempCbsConfigData = (CbsConfigurationTableApi *)((I_U8*)cbsConfigData + index*outSize);
      sendBreakCbsipAddressReqToCm (tempCbsConfigData);    
   }
   free( cbsConfigData );
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendAddCbServerForAllServersToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : Sends ADD_CB_SERVER message to CBSH 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendAddCbServerForAllServersToCbsh( )
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   CbsConfigurationTableApi         *cbsConfigData = NULL;
   CbsConfigurationTableApi         *tempCbsConfigData = NULL;
   CbsStatusTableApi                cbsStatusData;
   I_U32                            outCount; 
   I_U16                            outSize; 
   I_S32                            retCode;
   I_U32                            index=ZERO;

   retCode = getallCbsConfigurationTable( &cbsConfigData, &outCount, &outSize); 
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"No Data exists in cbsConfigurationTable");
      LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
      return;
   }

   for (index=0; index<outCount; index++)
   {
      tempCbsConfigData = (CbsConfigurationTableApi*)( ((I_U8*)cbsConfigData) + index*outSize);

      /* Add CbsStatusTable for all the external Servers After Reboot*/
      if ( tempCbsConfigData->externalCbcServer == TRUE )
      {
         cbsStatusData.cbsId =  tempCbsConfigData->cbsId;
         cbsStatusData.linkStatus =  LINK_DOWN;
         cbsStatusData.bindStatus = BIND_FAIL;
         if ( (insertCbsStatusTable(&cbsStatusData)) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_INFO,"insertCbsStatusTable failed");
            return;
         }
      }
      sendAddCbServerToCbsh(tempCbsConfigData);
      sendConfigCbsReqForAllServerToCbsIf(tempCbsConfigData);
   }
   
   free( cbsConfigData );
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendAddCbCellForAllCellsToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : Sends ADD_CB_CELL message to CBSH for all the chngrp configured 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendAddCbCellForAllCellsToCbsh( )
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   ChnGrpTableApi                   *chnGrpData;
   ChnGrpTableApi                   *tempChnGrpData;
   I_U32                            outCount; 
   I_U16                            outSize; 
   I_S32                            retCode;
   I_U32                            index = ZERO;

   /* Wrapper to find Lac & Cell with CBCH=TRUE */
   retCode = getTerChnGrpTable( TRUE, &chnGrpData, &outCount, &outSize); 
   if ( retCode != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"No Cell Exsists supporting cbsh So, not sending request OAMS_CFG_CBSH_ADD_CB_CELL");
      LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
      return;
   }
   
   for( index=0; index < outCount; index++ )
   {
      tempChnGrpData = (ChnGrpTableApi*)((I_U8*)chnGrpData + index*outSize);
      sendAddCbCellToCbsh( tempChnGrpData->cellId, tempChnGrpData->lac );
   
   } 
   free(chnGrpData);
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendCellOprStateToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : Sends Cell Operational state to CBSH 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendCellOprStateToCbsh(I_U32 cellId, I_U32 lac, I_U8 oprState)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   OamsCfgCbshCbCellStatusChange      cfgCbshCbCellState;
   ChnGrpTableSecIndices              chnGrpTableSecIndex;
   ChnGrpTableApi                     *tempChnGrpData; 
   ChnGrpTableApi                     *chnGrpData; 
   I_U32                              count;
   I_U16                              size;
   I_U32                              index;
   I_Bool                             cbchTrue = FALSE;
   I_U32                              cellBarAccess;
   I_U32                              cellOprState;
   I_U32                              oprStateAInterface;
   I_U32                              adminState;

   chnGrpTableSecIndex.cellId = cellId;
   chnGrpTableSecIndex.lac = lac;
 
   if ( CLIB_SUCCESS != (retrieveSpecifiedChnGrpRow( &chnGrpTableSecIndex, &chnGrpData, &count, &size) ) )
   {
      LOG_PRINT(LOG_MAJOR,"Entry does not exists in ChnGrpTable for Cell %d, Lac %d", 
                 chnGrpTableSecIndex.cellId, chnGrpTableSecIndex.lac);
      return;
   } 
   for ( index = 0; index< count; index++)
   {
      tempChnGrpData = (ChnGrpTableApi*)((I_U8*)chnGrpData + index*size);
      if ( tempChnGrpData->cbch == TRUE)
      {
         LOG_PRINT(LOG_MAJOR,"Cbch Configured for Cell %d, Lac %d in ChnGrp %d", 
                 chnGrpTableSecIndex.cellId, chnGrpTableSecIndex.lac, chnGrpData->chnGrpId);

         cbchTrue = TRUE;
         break;
      }
   }
   free(chnGrpData);

   if ( cbchTrue == FALSE )
   {
      LOG_PRINT(LOG_MAJOR,"Cbch Not Configured for Cell %d, Lac %d , \
                          So no need to send OAMS_CFG_CBSH_CELL_ENABLED/OAMS_CFG_CBSH_CELL_DIABLED ", 
                         chnGrpTableSecIndex.cellId, chnGrpTableSecIndex.lac);
      return;
   }
   /* Sending OAMS_CFG_CBSH_CB_CELL_STATE_CHANGE as CellOpr State Changed */
   if ( (oprState == CAUSE_CELL_ENABLED) || (oprState == CAUSE_CELL_DISABLED) )
   {
      LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CBSH_CB_CELL_STATE_CHANGE As Cell Operational State Changed CellId: [%d], Lac: [%d]", cellId, lac);
      cellOprState = oprState;
      if ( CLIB_SUCCESS != (cellHGetCellBarred(cellId , lac , &cellBarAccess)))
      {
          LOG_PRINT(LOG_MAJOR,"Entry does not exists in CellTable for Cell %d, Lac %d", cellId, lac);
          return;
      }
      if ( CLIB_SUCCESS != (getAInterfaceOprState(&oprStateAInterface)))
      {
         LOG_PRINT(LOG_MAJOR,"Entry does not exists in AInterfaceTable");
         return;
      }
      if ( oprStateAInterface == DISABLED ) 
      {
         cellBarAccess = CAUSE_CELL_BARRED;
      }
      else if ( oprStateAInterface == ENABLED && cellBarAccess == CELL_NORMAL)  
      {
        cellBarAccess =  CAUSE_CELL_UNBARRED; 
      }
      else if ( oprStateAInterface == ENABLED && cellBarAccess == CELL_BARRED)  
      {
        cellBarAccess =  CAUSE_CELL_BARRED; 
      }

   }
   /* Sending OAMS_CFG_CBSH_CB_CELL_STATE_CHANGE as AInterface Opr State Changed */
   else  if ( (oprState == CAUSE_CELL_UNBARRED) || (oprState == CAUSE_CELL_BARRED) )
   {
      LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CBSH_CB_CELL_STATE_CHANGE As AInterface Operational State \
                          Changed CellId: [%d], Lac: [%d]", cellId, lac);

      if ( CLIB_SUCCESS != (cellHGetCellBarred(cellId , lac , &cellBarAccess)))
      {
          LOG_PRINT(LOG_MAJOR,"Entry does not exists in CellTable for Cell %d, Lac %d", cellId, lac);
          return;
      }
      if ( cellBarAccess == CELL_BARRED ) 
      {
         cellBarAccess = CAUSE_CELL_BARRED;
      }
      else   
      {
         cellBarAccess = oprState;
      }
     
      if ( CLIB_SUCCESS != getCellAdminStateAndOprState(lac, cellId, &adminState, &cellOprState))
      {
          LOG_PRINT(LOG_MAJOR,"Entry does not exists in CellTable for Cell %d, Lac %d", cellId, lac);
          return;
      }
   }

   cfgCbshCbCellState.ci = cellId;
   cfgCbshCbCellState.lac = lac;
   cfgCbshCbCellState.barredState = cellBarAccess;
   cfgCbshCbCellState.oprState = cellOprState;
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CBSH_CB_CELL_STATUS_CHANGE CellId: [%d], Lac: [%d], \
                       CellBarStatus: [%d], CellOprStatus: [%d]", cfgCbshCbCellState.ci, cfgCbshCbCellState.lac, 
                       cfgCbshCbCellState.barredState, cfgCbshCbCellState.oprState);


   cfgSendMessage(&cfgCbshCbCellState, sizeof(OamsCfgCbshCbCellStatusChange), ENT_CSAPP_CBSH, OAMS_CFG_CBSH_CB_CELL_STATUS_CHANGE, 0);

   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}

/******************************* Function  Header*****************************
   Function Name :    sendAddCbCellToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : Sends ADD_CB_CELL message to CBSH for particular cell 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendAddCbCellToCbsh( I_U32 cellId, I_U32 lac)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   OamsCfgCbshAddCbCell             cfgCbshAddCbCell;

   cfgCbshAddCbCell.ci = cellId;
   cfgCbshAddCbCell.lac = lac;
   
   LOG_PRINT(LOG_DEBUG," Sending OAMS_CFG_CBSH_ADD_CB_CELL equest CellId: [%d], Lac: [%d]", cfgCbshAddCbCell.ci, cfgCbshAddCbCell.lac);

   cfgSendMessage(&cfgCbshAddCbCell, sizeof(OamsCfgCbshAddCbCell), ENT_CSAPP_CBSH, OAMS_CFG_CBSH_ADD_CB_CELL, 0);
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendDelCbCellToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : Sends DEL_CB_CELL message to CBSH for particular cell 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendDelCbCellToCbsh( I_U32 cellId, I_U32 lac)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   OamsCfgCbshDelCbCell        cfgCbshDelCbCell;

   cfgCbshDelCbCell.ci = cellId;
   cfgCbshDelCbCell.lac = lac;
   
   LOG_PRINT(LOG_DEBUG," Sending OAMS_CFG_CBSH_DEL_CB_CELL equest CellId: [%d], Lac: [%d]",
                         cfgCbshDelCbCell.ci, cfgCbshDelCbCell.lac);

   cfgSendMessage(&cfgCbshDelCbCell, sizeof(OamsCfgCbshDelCbCell), ENT_CSAPP_CBSH, OAMS_CFG_CBSH_DEL_CB_CELL, 0);
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    setCbsConfigurationHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles BSC_API_SET_cbsCONFIGURATIONTABLE message from CM 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void setCbsConfigurationHandler()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   CbsConfigurationTableApi                 *receiveMsgPtr = NULL;
   CbsConfigurationTableIndices              cbsConfigIndex;
   CbsConfigurationTableApi                 *cbsConfigData = NULL;
   SetOmcIpAddressTableApi                  *omcData = NULL;
   MlpppConfigTableApi                      *mlpppData = NULL;
   CbsStatusTableApi                        cbsStatusData;
   I_U32                                    retCode;
   I_Bool                                   statusChk;
   I_U8                                     charBuffer[CBS_NAME_SIZE+1];
   I_U32                                    outCount;
   I_U16                                    outSize;
   I_Bool                                   flagParamChange = FALSE;  
   CbsConfigurationTableSecIndices          cbsConfigTableSecIndex;
   CbsConfigurationTableApi                 *cbsSecConfigData = NULL;


   receiveMsgPtr = (CbsConfigurationTableApi*)( ((I_U8 *)gCfgMsgBuf) + sizeof(sCmMsg) );  

   cbsConfigIndex.cbsId = receiveMsgPtr->cbsId;

   retCode = getCbsConfigurationTable(&cbsConfigIndex, &cbsConfigData);
   if ( retCode != CLIB_SUCCESS ) /* New Request for Configuring CB Server */
   {
       retCode = getallCbsConfigurationTable( &cbsConfigData, &outCount, &outSize); 
      if ( retCode != CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_INFO,"No Data exists in cbsConfigurationTable");
      }
      else
      {
          LOG_PRINT(LOG_INFO,"MAX CbServers (Count=1) already Configured, So rejecting Request");
          free(cbsConfigData);
          cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
          return; 
      }
      statusChk = cbsConfigRangeCheck(receiveMsgPtr);
      if ( !statusChk)
      {
         LOG_PRINT(LOG_INFO, "Send Nack to CM Range Check Fail ");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      if ( receiveMsgPtr->externalCbcServer == TRUE )
      {
         statusChk = cbsConfigRangeIpPortCheck(receiveMsgPtr);
         if ( !statusChk)
         {
            LOG_PRINT(LOG_INFO, "Send Nack to CM Range Check Fail ");
            cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            return; 
         }
         memset(charBuffer, '\0', CBS_NAME_SIZE+1);
	 memcpy(charBuffer, receiveMsgPtr->name, CBS_NAME_SIZE);
	 LOG_PRINT(LOG_INFO,"Name: %s ",charBuffer);

	 memset(charBuffer,  '\0', CBS_NAME_SIZE+1);
	 memcpy(charBuffer, receiveMsgPtr->biLateralAgreement, CBS_NAME_SIZE);
	 LOG_PRINT(LOG_INFO,"biLateralAgreement: %s ",charBuffer);

	 memset(charBuffer,  '\0', CBS_NAME_SIZE+1);
	 memcpy(charBuffer, receiveMsgPtr->password, CBS_NAME_SIZE);
	 LOG_PRINT(LOG_INFO,"Password: %s ",charBuffer);

         retCode = insertCbsConfigurationTable(receiveMsgPtr);
         if ( retCode != CLIB_SUCCESS )
         {
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return; 
         }
         cbsStatusData.cbsId = receiveMsgPtr->cbsId;
         cbsStatusData.linkStatus = LINK_DOWN;
         cbsStatusData.bindStatus = BIND_FAIL;

         retCode = insertCbsStatusTable(&cbsStatusData);
         if ( retCode != CLIB_SUCCESS )
         {
            retCode = deleteCbsConfigurationTable(&cbsConfigIndex);
            if ( retCode != CLIB_SUCCESS ) 
            {
               LOG_PRINT(LOG_INFO, "deleteCbsConfigurationTable Failed.. ");
            }
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return; 
         }
         /*Send Ack of Set command */
         cfgSendAckToCm();
         sendAddCbServerToCbsh(receiveMsgPtr);
         LOG_PRINT(LOG_INFO," Sending OAMS_CFG_CBSIF_CONFIG_CBS");
         sendConfigCbsReqForAllServerToCbsIf(receiveMsgPtr );
      }
      if ( receiveMsgPtr->externalCbcServer == FALSE )
      {
         cbsConfigTableSecIndex.externalCbcServer = FALSE;
         retCode = getSecCbsConfigurationTable(&cbsConfigTableSecIndex, &cbsSecConfigData, &outCount, &outSize);
         if (retCode == CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_INFO,"Internal cbs Server already Configured Sending NACK.");
            free(cbsSecConfigData);
            cfgSendNackToCm(CM_ERR_INTERNAL_CB_SERVER_ALREADY_CONFIGURED);
            return;
         }

         retCode = getallSetOmcIpAddressTable( &omcData, &outCount, &outSize);
         if (retCode != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_CRITICAL,"Get Failed for MlpppConfigTable and SetOmcIpAddressTable..");
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return; 
         }
         retCode = getallMlpppConfigTable( &mlpppData, &outCount, &outSize);
         if (retCode != CLIB_SUCCESS )
         {
            memcpy(receiveMsgPtr->cbsIpAddr,omcData->omcIpAddr, MAX_IP_ADDR_LEN);
            receiveMsgPtr->cbsIpPort = omcData->omcIpPort;
         }
         else
         {
            memcpy(receiveMsgPtr->cbsIpAddr,mlpppData->omcIpAddr, MAX_IP_ADDR_LEN);
            receiveMsgPtr->cbsIpPort = omcData->omcIpPort;
            free( mlpppData);
         }
         free(omcData);
         memset(receiveMsgPtr->name, '\0', CBS_NAME_SIZE);
         memset(receiveMsgPtr->biLateralAgreement, '\0', CBS_NAME_SIZE);
         memset(receiveMsgPtr->password, '\0', CBS_NAME_SIZE);

         retCode = insertCbsConfigurationTable(receiveMsgPtr);
         if ( retCode != CLIB_SUCCESS )
         {
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return; 
         }

         cfgSendAckToCm();
         sendAddCbServerToCbsh(receiveMsgPtr);
         sendIntfUpToCbsh(receiveMsgPtr->cbsId);
         
      }
   }
   else /* Modification Request for already Configured CB Server */
   {
      flagParamChange = compareRcvdMsgAndDbEntry(receiveMsgPtr,cbsConfigData,sizeof(CbsConfigurationTableApi));
      if ( flagParamChange )
      {
         statusChk = checkParamModifiedCbsConfigReq(receiveMsgPtr,cbsConfigData);
         if ( !statusChk)
         {
                free (cbsConfigData);
                return;
         }
         else
         {
             retCode = updateCbsConfigurationTable(receiveMsgPtr);
             if ( retCode != CLIB_SUCCESS )
             {
               cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
               free(cbsConfigData);
               return; 
             }
            cfgSendAckToCm();
            sendBreakCbsipAddressReqToCm(receiveMsgPtr);
            breakRespAwaited=TRUE; /* Send Send CONFIG_CBS after Receiving Connection Down */
            //sendConfigCbsReqForAllServerToCbsIf(receiveMsgPtr);
         }
      }
      else
      {
         LOG_PRINT(LOG_INFO," Modification Request with same value as in DB, sending Ack");
         cfgSendAckToCm();
      }
      free (cbsConfigData);
   }
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}
/******************************* Function  Header*****************************
   Function Name :    cbsConfigRangeCheck()
Parameters    : None
Return type   : I_Void
Purpose       : Range Checks for cbs Configuration Request 
Other Note    : Added For BSC R2.4
*****************************************************************************/

I_Bool cbsConfigRangeCheck(CbsConfigurationTableApi *receiveMsgPtr)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
   if ( (receiveMsgPtr->cbsId < 0) || (receiveMsgPtr->cbsId > 65535) )
   {
      LOG_PRINT(LOG_DEBUG,"cbsConfigRangeCheck : cbsId received is out of range ");
      return FALSE;
   }
   if ( (receiveMsgPtr->externalCbcServer != TRUE) && (receiveMsgPtr->externalCbcServer != FALSE) )
   {
      LOG_PRINT(LOG_DEBUG,"cbsConfigRangeCheck : externalCbcServer value received is out of range ");
      return FALSE;
   }

   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
   return TRUE;
}

/******************************* Function  Header*****************************
   Function Name :    cbsConfigRangeIpPortCheck()
Parameters    : None
Return type   : I_Void
Purpose       : Range Checks for IP and Port 
Other Note    : Added For BSC R2.4
*****************************************************************************/

I_Bool cbsConfigRangeIpPortCheck(CbsConfigurationTableApi *receiveMsgPtr)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   I_S32   *cbsIp[4];
   I_U32   index = ZERO;

   if ( (receiveMsgPtr->cbsIpPort < 0) || (receiveMsgPtr->cbsIpPort > 65535) )
   {
      LOG_PRINT(LOG_DEBUG,"cbsConfigRangeCheck : cbsIpPort received is out of range ");
      return FALSE;
   }
   
   memset(cbsIp,4,0);
   if(receiveMsgPtr->cbsIpAddr !=NULL)
   {
      convertIpToToken(receiveMsgPtr->cbsIpAddr, cbsIp); 

      if ( cbsIp[0] == ZERO )
      {
         LOG_PRINT(LOG_DEBUG,"cbsConfigRangeCheck : cbsIp received is out of range ");
         return FALSE;
      }
      for( index=0; index<4; index++)
      {
         if ( cbsIp[index] > 255 )
         {
            LOG_PRINT(LOG_DEBUG,"cbsConfigRangeCheck : cbsIp received is out of range ");
            return FALSE;
         }
      }
   }
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
   return TRUE;
}

/******************************* Function  Header*****************************
   Function Name :    sendAddCbServerToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : Sends ADD_CB_SERVER message to CBSH 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendAddCbServerToCbsh( CbsConfigurationTableApi *cbsConfigData)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   OamsCfgCbshAddCbServer           cfgCbshAddCbServer;

   memcpy( cfgCbshAddCbServer.cbsIP, cbsConfigData->cbsIpAddr, MAX_IP_ADDR_LEN);
   cfgCbshAddCbServer.cbsPortNum = cbsConfigData->cbsIpPort;
   cfgCbshAddCbServer.cbsId = cbsConfigData->cbsId;

   LOG_PRINT(LOG_DEBUG," Sending OAMS_CFG_CBSH_ADD_CB_SERVER Request cbsIp: [%s], CbcPort: [%d], cbsId: [%d]", 
                         cfgCbshAddCbServer.cbsIP,cfgCbshAddCbServer.cbsPortNum,cfgCbshAddCbServer.cbsId);

   LOG_PRINT(LOG_INFO," Sending OAMS_CFG_CBSH_ADD_CB_SERVER to CBSH");
   cfgSendMessage(&cfgCbshAddCbServer, sizeof(OamsCfgCbshAddCbServer), ENT_CSAPP_CBSH, OAMS_CFG_CBSH_ADD_CB_SERVER, 0);
   
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    findLocalIpPort()
Parameters    : None
Return type   : I_Void
Purpose       : find Local Ip and Port
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void findLocalIpPort(I_S8 *config_ne_ip, I_U16 *nePort)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   I_S8            *tmp_config_ne_ip;

   tmp_config_ne_ip = getenv("config_CP_IP");
   if ( tmp_config_ne_ip == NULL )
   {
      LOG_PRINT(LOG_CRITICAL,"config_PP_IP not Set: Exiting....");
      exit(0); 
   }
   LOG_PRINT(LOG_INFO,"config_CP_IP: [%s]",tmp_config_ne_ip);
   strcpy(config_ne_ip,tmp_config_ne_ip);
   //memcpy(config_ne_ip,tmp_config_ne_ip,strlen(tmp_config_ne_ip));

   *nePort = CONFIG_CP_CBS_PORT;
   LOG_PRINT(LOG_INFO,"NeIp: [%s], NePort: [%d]", config_ne_ip, *nePort);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendBreakCbsipAddressReqToCm()
Parameters    : None
Return type   : I_Void
Purpose       : Make or Breaks the TCP/IP Connection with CBS depending upon 
                the msgType passed
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendBreakCbsipAddressReqToCm( CbsConfigurationTableApi *cbsConfigData )
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   OamsCfgCbsifBreakIpAddress       cfgCbsifBreakIpAddress;

   if ( cbsConfigData->externalCbcServer != TRUE )
   {
      LOG_PRINT(LOG_INFO,"%d is Not a external server So Not Sending Request to CBSIF", cbsConfigData->cbsId);
      return;
   }
   cfgCbsifBreakIpAddress.cbsId = cbsConfigData->cbsId;

   LOG_PRINT(LOG_DEBUG," Sending Ip Request to CbsId: [%d]",
                        cfgCbsifBreakIpAddress.cbsId);

   cfgSendMessage(&cfgCbsifBreakIpAddress, sizeof(OamsCfgCbsifBreakIpAddress), ENT_CSAPP_CBSIF, OAMS_CFG_CBSIF_BREAK_IP, 0);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendConfigCbsReqForAllServerToCbsIf()
Parameters    : None
Return type   : I_Void
Purpose       : Make TCP/IP Connection with CBS 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendConfigCbsReqForAllServerToCbsIf(CbsConfigurationTableApi *cbsConfigData )
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   OamsCfgCbsifConfigCbs            cfgCbsifConfigCbs;

   if ( cbsConfigData->externalCbcServer != TRUE )
   {
      LOG_PRINT(LOG_INFO,"%d is Not a external server So Not Sending Request to CBSIF", cbsConfigData->cbsId);
      return;
   }
   cfgCbsifConfigCbs.cbsId = cbsConfigData->cbsId;
   memcpy(cfgCbsifConfigCbs.cbsIpAddr, cbsConfigData->cbsIpAddr, MAX_IP_ADDR_LEN);
   cfgCbsifConfigCbs.cbsIpPort = cbsConfigData->cbsIpPort;
   findLocalIpPort(cfgCbsifConfigCbs.localIpAddr, &(cfgCbsifConfigCbs.localIpPort));

   LOG_PRINT(LOG_DEBUG," Sending Ip Request to CbsId: [%d] CbsIp: [%s] CbsPort: [%d] \
                         LocalIp: [%s] LocalPort: [%d]", cfgCbsifConfigCbs.cbsId,
                         cfgCbsifConfigCbs.cbsIpAddr, cfgCbsifConfigCbs.cbsIpPort, 
                         cfgCbsifConfigCbs.localIpAddr, cfgCbsifConfigCbs.localIpPort);

   cfgSendMessage(&cfgCbsifConfigCbs, sizeof(OamsCfgCbsifConfigCbs), ENT_CSAPP_CBSIF, OAMS_CFG_CBSIF_CONFIG_CBS, 0);
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}
/******************************* Function  Header*****************************
   Function Name :    cbsifConnectionDownHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles connection Down message from CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsifConnectionDownHandler()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   CsappCbsifCfgConnectionDown        *receiveMsgPtr = NULL;
   OamsCfgAfhSysAlarm                 sysAlarmBuff = {0};
   I_S32                              retCode;
   CbsConfigurationTableApi           *cbsData = NULL;
   CbsConfigurationTableIndices        cbsIndex;
   I_U16                               index;

   receiveMsgPtr = (CsappCbsifCfgConnectionDown *)(gCfgMsgBuf);

   /* Stopping Bind Resp and Bind Repeat Timer if running */
   if ( getIndexOfCbsResp(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Resp Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_RESPONSE as Object being deleted CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRespTimer[index].cbsTimerId);

      StopTimerFrmwrk(cbsRespTimer[index].cbsTimerId);
      cbsRespTimer[index].cbsId = INVALID_CBS;
   }
   if ( getIndexOfCbsRepeat(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Repeat Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_REPEAT as Object being deleted CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRepeatTimer[index].cbsTimerId);

      StopTimerFrmwrk(cbsRepeatTimer[index].cbsTimerId);
      cbsRepeatTimer[index].cbsId = INVALID_CBS;
   }

   retCode = updateLinkStatusCbsStatusTable(receiveMsgPtr->cbsId, LINK_DOWN);
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_MAJOR,"updateLinkStatuscbsConfigurationTable failed for cbsId: [%d]", receiveMsgPtr->cbsId);
   }

   retCode = updateBindStatusCbsStatusTable(receiveMsgPtr->cbsId, BIND_FAIL);
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_MAJOR,"updateBindStatusCbsStatusTable failed for cbsId: [%d]", receiveMsgPtr->cbsId);
      return;
   }

   LOG_PRINT(LOG_MAJOR,"LinkStatus Updated as TCP_DOWN and BindStatus updated as BIND_FAIL for cbsId: [%d]", receiveMsgPtr->cbsId);
   LOG_PRINT(LOG_INFO,"Sending ALARM: EVENT_CBS_TCP_DOWN");
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_CBS_TCP_DOWN;

   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CBS; 
   sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->cbsId; 
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR; 
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "TCP Link Down for cbsId [%d]",receiveMsgPtr->cbsId); 

   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   
   sendIntfDownToCbsh(receiveMsgPtr->cbsId);
   if ( breakRespAwaited == TRUE)
   {
      breakRespAwaited=FALSE;
      cbsIndex.cbsId = receiveMsgPtr->cbsId;
      retCode = getCbsConfigurationTable(&cbsIndex, &cbsData);
      if ( retCode != CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_MAJOR," CbsId does not exists in CbsConfigurationTable, So Could not send CONFIG_CBS");
      }
      else
      {
         sendConfigCbsReqForAllServerToCbsIf(cbsData);
         free(cbsData);
      }
      
   }
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendIntfDownToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : send INTF_DOWN message to CBSH
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendIntfDownToCbsh(I_U16 cbsId)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   OamsCfgCbshIntfDown                cfgCbshIntfDown;

   cfgCbshIntfDown.cbsId = cbsId;
  
   LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSH_INTF_DOWN for cbsId: [%d]",cfgCbshIntfDown.cbsId);

   cfgSendMessage((I_Void *)&cfgCbshIntfDown,sizeof(OamsCfgCbshIntfDown),
                ENT_CSAPP_CBSH, OAMS_CFG_CBSH_INTF_DOWN, 0);
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}

/******************************* Function  Header*****************************
   Function Name :    sendDelcbsConfigToCbsif()
Parameters    : None
Return type   : I_Void
Purpose       : send DELETE_CONFIG_CBS message to CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendDelcbsConfigToCbsif(CbsConfigurationTableApi *receiveMsgPtr)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   OamsCfgCbsifDelConfigCbs         cfgCbsifDelConfigCbs;

   cfgCbsifDelConfigCbs.cbsId = receiveMsgPtr->cbsId;
    
   LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSIF_DELETE_CONFIG_CBS for cbsId: [%d]",   
                        cfgCbsifDelConfigCbs.cbsId);

   cfgSendMessage((I_Void *)&cfgCbsifDelConfigCbs,sizeof(OamsCfgCbsifDelConfigCbs),
                ENT_CSAPP_CBSIF, OAMS_CFG_CBSIF_DELETE_CONFIG_CBS, 0);

   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}

/******************************* Function  Header*****************************
   Function Name :    delCbsConfigurationHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Delete Request for cbsConfigurationTable
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void delCbsConfigurationHandler()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   CbsConfigurationTableApi         *receiveMsgPtr = NULL;
   CbsConfigurationTableApi         *cbsConfigData = NULL;
   CbsConfigurationTableIndices      cbsConfigIndex;
   I_S32                             retCode;
   receiveMsgPtr = (CbsConfigurationTableApi *)( ((I_U8 *)gCfgMsgBuf) + sizeof(sCmMsg));

   cbsConfigIndex.cbsId = receiveMsgPtr->cbsId;
   retCode = getCbsConfigurationTable(&cbsConfigIndex, &cbsConfigData);
   if ( retCode != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested cbsId: [%d] does not Exists in CbcConfigutaionTable, sending Nack",receiveMsgPtr->cbsId);   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   if ( cbsConfigData->externalCbcServer == TRUE )
   {
      sendDelcbsConfigToCbsif(receiveMsgPtr);
   }
   else
   {
      /* Deletion is for Internal cbs Server So Not Sending Message to CBSIF So Sending
         Message to CBSH and Deleting cbsConfigurationTable */
      /* Before Sending Delete Request Sending Intf Down to CBSH */
      sendIntfDownToCbsh(receiveMsgPtr->cbsId);
      sendDelCbsServerToCbsh(receiveMsgPtr->cbsId, cbsConfigData->externalCbcServer); 
   }
   free(cbsConfigData);
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}
/******************************* Function  Header*****************************
   Function Name :    sendDelCbsServerToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : send DELETE_CONFIG_CBS message to CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendDelCbsServerToCbsh(I_U16 cbsId, I_U32 externalCbcServer)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   OamsCfgCbshDelCbServer           cfgCbshDelCbServer;
   CbsConfigurationTableIndices     cbsConfigIndex;
   CbsStatusTableIndices            cbsStatusIndex;
   I_S32                            retCode;
   

   cfgCbshDelCbServer.cbsId = cbsId;
    
   LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSH_DEL_CB_SERVER for cbsId: [%d]",cfgCbshDelCbServer.cbsId);

   cfgSendMessage((I_Void *)&cfgCbshDelCbServer,sizeof(OamsCfgCbshDelCbServer),
                ENT_CSAPP_CBSH, OAMS_CFG_CBSH_DEL_CB_SERVER, 0);

   cbsConfigIndex.cbsId = cbsId;
   retCode = deleteCbsConfigurationTable(&cbsConfigIndex);
   if ( retCode != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteCbsConfigurationTable failed sending NACK"); 
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
      return;   
   }
   if ( externalCbcServer == TRUE )
   {
      cbsStatusIndex.cbsId = cbsId;
      retCode = deleteCbsStatusTable(&cbsStatusIndex);
      if ( retCode != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"deleteCbsStatusTable failed sending NACK"); 
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
         return;   
      }
   }
   cfgSendAckToCm();

   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}

/******************************* Function  Header*****************************
   Function Name :    cbsifDeleteConfigCbsResp()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Delete Request for cbsConfigurationTable
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsifDeleteConfigCbsResp()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   CsappCbsifCfgDelConfigResp       *receiveMsgPtr = NULL;
   I_U16                            index;

   receiveMsgPtr = (CsappCbsifCfgDelConfigResp *)(gCfgMsgBuf);
   if ( receiveMsgPtr->result != CFG_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Delete CB server failed from CBSIF sending NACK"); 
      cfgSendNackToCm(CM_ERR_DEL_CB_SERVER_FAILED);
      return;   

   }
   /* Stopping Bind Resp and Bind Repeat Timer if running */
   if ( getIndexOfCbsResp(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Resp Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_RESPONSE as Object being deleted CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRespTimer[index].cbsTimerId);

      StopTimerFrmwrk(cbsRespTimer[index].cbsTimerId);
      cbsRespTimer[index].cbsId = INVALID_CBS;
   }
   if ( getIndexOfCbsRepeat(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Repeat Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_REPEAT as Object being deleted CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRepeatTimer[index].cbsTimerId);

      StopTimerFrmwrk(cbsRepeatTimer[index].cbsTimerId);
      cbsRepeatTimer[index].cbsId = INVALID_CBS;
   }

   /* Deletion is for External cbs Server So Need to To remove CbcStatusTable */  
   sendDelCbsServerToCbsh(receiveMsgPtr->cbsId, TRUE); 
  
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}
/******************************* Function  Header*****************************
   Function Name :    startCbsTimer()
Parameters    : None
Return type   : I_Void
Purpose       : Start Timer for BIND RESP. 
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void startCbsTimer(I_U16 cbsId, I_U8 timerId, I_U32 timerVal)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   SysAddr        sAddr;
   TmrPayLoad     tmrPayload;
   I_U16          index;
   sAddr.entity = ENT_OAMS_CFG;
   tmrPayload.payLoad[0] = timerId;
   memcpy(&(tmrPayload.payLoad[1]),&(cbsId),sizeof(I_U16));

   StartTimerFrmwrk(&sAddr,timerVal,&tmrPayload,&gCbsTimerId);

   if ( CBS_BIND_RESP == timerId )
   {
      if(getIndexOfCbsResp(INVALID_CBS,&index) == CFG_FAILURE)
      {  
         LOG_PRINT(LOG_INFO,"Max No of Cbs Server already configured");
         return;
      }
      cbsRespTimer[index].cbsTimerId = gCbsTimerId;
      cbsRespTimer[index].cbsId = cbsId;
   }
   if ( CBS_BIND_REPEAT == timerId )
   {
      if(getIndexOfCbsRepeat(INVALID_CBS,&index) == CFG_FAILURE)
      {  
         LOG_PRINT(LOG_INFO,"Max No of Cbs Server already configured");
         return;
      }
      cbsRepeatTimer[index].cbsTimerId = gCbsTimerId;
      cbsRepeatTimer[index].cbsId = cbsId;
   }
   LOG_PRINT(LOG_INFO," CbsId: %d, TimerId: %d Index: %d", cbsId, gCbsTimerId, index);
   
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendBindReqToCbsif()
Parameters    : None
Return type   : I_Void
Purpose       : send Bind Requestto CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendBindReqToCbsif(I_U16 cbsId)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   OamsCfgCbsifBindReq            cfgCbsifBindReq;
   CbsConfigurationTableApi       *cbsConfigData = NULL;
   CbsConfigurationTableIndices   cbsConfigIndex;
   I_S32                          retCode;
   I_Void                         *outPutMsg = NULL;
   I_U32                          outPutMsgLen; 
   OamsCfgCbsifDataReq            *cfgCbsifDataReq;

   cbsConfigIndex.cbsId = cbsId;
   retCode = getCbsConfigurationTable( &cbsConfigIndex, &cbsConfigData);
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_MAJOR,"getCbsConfigurationTable failed for cbsId: [%d]",cbsConfigIndex.cbsId);
      return;
   }

   cfgCbsifBindReq.cbsId = cbsConfigData->cbsId;
   memcpy( cfgCbsifBindReq.name, cbsConfigData->name,CBS_NAME_SIZE);
   memcpy(cfgCbsifBindReq.biLateralAgreement, cbsConfigData->biLateralAgreement, CBS_NAME_SIZE);
   memcpy(cfgCbsifBindReq.password, cbsConfigData->password, CBS_NAME_SIZE);
   cfgCbsifBindReq.sHdr.msgType = SMSCB_BIND;
   cfgCbsifBindReq.isPasswordPresent = I_TRUE;
   cfgCbsifBindReq.version = SMSCB_VERION;
    
   LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSIF_BIND_REQ for cbsId: [%d], Name: [%s],\
                       biLateralAgreement: [%s], Passwod: [%s]",cfgCbsifBindReq.cbsId, 
                        cfgCbsifBindReq.name, cfgCbsifBindReq.biLateralAgreement,cfgCbsifBindReq.password);

   retCode = EncodeCbshMsgAsn(&cfgCbsifBindReq, sizeof(OamsCfgCbsifBindReq) ,&outPutMsg, &outPutMsgLen);
   if ( outPutMsg == NULL)
   {
      LOG_PRINT(LOG_CRITICAL," EncodeCbshMsgAsn failed in sendBindReqToCbsif"); 
      return ;  
   }
   cfgCbsifDataReq = AlocMsgBuf(sizeof(OamsCfgCbsifDataReq)+outPutMsgLen); 

   if (!cfgCbsifDataReq)
   { 
      LOG_PRINT(LOG_CRITICAL,"AllocMsgBuf failed in sendBindReqToCbsif"); 
      return ;  
   } 
   memset(cfgCbsifDataReq,0,sizeof(OamsCfgCbsifDataReq)+outPutMsgLen) ; 

   cfgCbsifDataReq->sysHdr.msgType     = OAMS_CFG_CBSIF_DATA_REQ; 
   cfgCbsifDataReq->sysHdr.src.entity  = ENT_OAMS_CFG; 
   cfgCbsifDataReq->sysHdr.dest.entity = ENT_CSAPP_CBSIF; 

   cfgCbsifDataReq->cbsId = cfgCbsifBindReq.cbsId;
   cfgCbsifDataReq->size = outPutMsgLen;
   memcpy((cfgCbsifDataReq->payLoad), outPutMsg, outPutMsgLen);
    
   PRINT_HEX_DUMP(LOG_DEBUG, (I_PVoid)cfgCbsifDataReq, sizeof(OamsCfgCbsifDataReq)+outPutMsgLen);

   if (SendMsg(cfgCbsifDataReq, 1, sizeof(OamsCfgCbsifDataReq)+outPutMsgLen) < 0) 
   { 
      LOG_PRINT(LOG_CRITICAL,"CFG: In sendBindReqToCbsif - msg sending failed"); 
      return; 
   } 

   freeEncodeBuffer(outPutMsg);

   startCbsTimer(cbsId, CBS_BIND_RESP, CBS_BIND_RESP_TIMER);
   free(cbsConfigData);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}


/******************************* Function  Header*****************************
   Function Name :    cbsifConnectionUpHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles connection UP message from CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsifConnectionUpHandler()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   CsappCbsifCfgConnectionUp           *receiveMsgPtr = NULL;
   OamsCfgAfhSysAlarm                 sysAlarmBuff = {0};
   I_S32                              retCode;
   receiveMsgPtr = (CsappCbsifCfgConnectionUp *)(gCfgMsgBuf);
 
   retCode = updateLinkStatusCbsStatusTable(receiveMsgPtr->cbsId, LINK_UP );
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_MAJOR,"updateLinkStatuscbsConfigurationTable failed for cbsId: [%d]", receiveMsgPtr->cbsId);
      return;
   }
   LOG_PRINT(LOG_MAJOR,"LinkStatus Updated as TCP_UP for cbsId: [%d]", receiveMsgPtr->cbsId);
   LOG_PRINT(LOG_INFO,"Sending ALARM: EVENT_CBS_TCP_UP");
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_CBS_TCP_UP;

   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CBS; 
   sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->cbsId; 
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION; 
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "TCP Link Up for cbsId [%d]",receiveMsgPtr->cbsId); 

   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   
   sendBindReqToCbsif(receiveMsgPtr->cbsId);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    cbsBindRespTimeOutHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Timer expiry for CBS_BIND_RESP
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsBindRespTimeOutHandler(I_U16 cbsId)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   I_U16    index;
   LOG_PRINT(LOG_DEBUG,"CBS_BIND_RESP timer expired...");
   if ( getIndexOfCbsResp(cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Timer not Present for CbsId: %d",cbsId);
      return;
   }

   cbsRespTimer[index].cbsId = INVALID_CBS;

   startCbsTimer(cbsId, CBS_BIND_REPEAT, CBS_BIND_REPEAT_TIMER);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    cbsBindRepeatTimeOutHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Timer expiry for CBS_BIND_REPEAT
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsBindRepeatTimeOutHandler(I_U16 cbsId)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   I_U16     index;
   LOG_PRINT(LOG_DEBUG,"CBS_BIND_REPEAT timer expired...");
   if ( getIndexOfCbsRepeat(cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Timer not Present for CbsId: %d",cbsId);
      return;
   }
   cbsRepeatTimer[index].cbsId = INVALID_CBS;

   sendBindReqToCbsif(cbsId);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    cbsifBindConfirmHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Bind Confirm message from CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsifBindConfirmHandler(I_PVoid outputMsg)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   CsappCbsifCfgBindConfirm            *receiveMsgPtr = NULL;
   OamsCfgAfhSysAlarm                 sysAlarmBuff = {0};
   I_S32                              retCode;
   I_U16                              index;
   receiveMsgPtr = (CsappCbsifCfgBindConfirm *)(outputMsg);
   if ( getIndexOfCbsResp(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
      return;
   }
     LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_RESPONSE as BIND_CONFIRM received CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRespTimer[index].cbsTimerId);

   StopTimerFrmwrk(cbsRespTimer[index].cbsTimerId);
   cbsRespTimer[index].cbsId = INVALID_CBS;
   
   retCode = updateBindStatusCbsStatusTable( receiveMsgPtr->cbsId, BIND_SUCCESS );
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_MAJOR,"updateBindStatuscbsConfigurationTable failed for cbsId: [%d]",  receiveMsgPtr->cbsId);
      return;
   }

   LOG_PRINT(LOG_MAJOR,"LinkStatus Updated as BIND_UP for cbsId: [%d]",  receiveMsgPtr->cbsId);
   LOG_PRINT(LOG_INFO,"Sending ALARM: EVENT_CBS_BIND_SUCCESS");
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_CBS_BIND_SUCCESS;

   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CBS; 
   sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->cbsId; 
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION; 
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "cbsId [%d] Binded Successfuly",receiveMsgPtr->cbsId); 

   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   
   sendIntfUpToCbsh(receiveMsgPtr->cbsId);
   FREEDECODEBUFFER(outputMsg);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendIntfUpToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : send INTF message to CBSH
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendIntfUpToCbsh(I_U16 cbsId)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   OamsCfgCbshIntfUp               cfgCbshIntUp;
   
   cfgCbshIntUp.cbsId = cbsId;
    
   LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSH_INTF_UP for cbsId: [%d]",cfgCbshIntUp.cbsId);

   cfgSendMessage((I_Void *)&cfgCbshIntUp,sizeof(OamsCfgCbshIntfUp),
                ENT_CSAPP_CBSH, OAMS_CFG_CBSH_INTF_UP, 0);
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    cbsifBindFailHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Bind Fail message from CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsifBindFailHandler(I_PVoid outputMsg)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   OamsCbsifCfgBindFail              *receiveMsgPtr = NULL;
   OamsCfgAfhSysAlarm                 sysAlarmBuff = {0};
   I_S32                              retCode;
   I_U8                               string[MAX_STRING_LENGTH];
   I_U16                              index;
   receiveMsgPtr = (OamsCbsifCfgBindFail *)(outputMsg);
   if ( getIndexOfCbsResp(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
      return;
   }
   LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_RESPONSE as BIND_FAIL received CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRespTimer[index].cbsTimerId);


   StopTimerFrmwrk(cbsRespTimer[index].cbsTimerId);
   cbsRespTimer[index].cbsId = INVALID_CBS;


   retCode = updateBindStatusCbsStatusTable(receiveMsgPtr->cbsId, BIND_FAIL );
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_MAJOR,"updateBindStatuscbsConfigurationTable failed for cbsId: [%d]", receiveMsgPtr->cbsId);
      return;
   }

   LOG_PRINT(LOG_MAJOR,"LinkStatus Updated as BIND_FAIL for cbsId: [%d]", receiveMsgPtr->cbsId);
   LOG_PRINT(LOG_INFO,"Sending ALARM: EVENT_CBS_BIND_FAIL");
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_CBS_BIND_FAIL;

   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CBS; 
   sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->cbsId; 
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR; 
   sysAlarmBuff.sysAlarm.alarmReason = receiveMsgPtr->reason;
   getStringForBindFailErrorCause(receiveMsgPtr->cbsId,receiveMsgPtr->reason, string);
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,string); 

   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   
   if ( (receiveMsgPtr->reason == CBS_TEMPORARY_OVERLOAD) || (receiveMsgPtr->reason == CBS_TEMPORARY_FAILURE) )
   {
      LOG_PRINT(LOG_INFO,"Starting Timer CBS_BIND_REPEAT.. ");
      startCbsTimer(receiveMsgPtr->cbsId, CBS_BIND_REPEAT, CBS_BIND_REPEAT_TIMER);
   }
   FREEDECODEBUFFER(outputMsg);

   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}


/******************************* Function  Header*****************************
   Function Name : getStringForBindFailErrorCause()
Return type   : I_Void
Purpose       : Return a string corresponding to the failure cause for 
                Binf Failure from CBSIF
Other Note    : Added For BSC R2.4
 *****************************************************************************/
I_Void getStringForBindFailErrorCause(I_U16 cbsId, I_U8 reason, I_U8 *string)
{
   switch(reason)
   {
      case  CBS_TEMPORARY_OVERLOAD:
         sprintf(string,"cbsId [%d] Bind Failed as Temorary Overload",cbsId); 
         break;
      case CBS_TEMPORARY_FAILURE:
         sprintf(string,"cbsId [%d] Bind Failed as Temorary Failure",cbsId); 
         break;
      case CBS_NOT_ENTITLED:
         sprintf(string,"cbsId [%d] Bind Failed as Not Entitled",cbsId); 
         break;
      case CBS_INCORRECT_ID_OR_PASSWORD:
         sprintf(string,"cbsId [%d] Bind Failed as Incorrect Id or Password",cbsId); 
         break;
      case CBS_VERSION_UNSUPPORTED:
         sprintf(string,"cbsId [%d] Bind Failed as Version Supported",cbsId); 
         break;
      default:
         sprintf(string,"cbsId [%d] Bind Failed with Invalid Cause Value",cbsId); 
         break;
   }
}

/******************************* Function  Header*****************************
   Function Name :    cbsifUnBindHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles UnBind Request from CBSIF
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void cbsifUnBindHandler(I_PVoid outputMsg)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   CsappCbsifCfgUnbind                *receiveMsgPtr = NULL;
   OamsCfgAfhSysAlarm                 sysAlarmBuff = {0};
   I_S32                              retCode;
   I_U16                              index;
   receiveMsgPtr = (CsappCbsifCfgUnbind *)(outputMsg);

   /* Stopping Bind Resp and Bind Repeat Timer if running */
   if ( getIndexOfCbsResp(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Resp Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_RESPONSE as Object being deleted CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRespTimer[index].cbsTimerId);

      StopTimerFrmwrk(cbsRespTimer[index].cbsTimerId);
      cbsRespTimer[index].cbsId = INVALID_CBS;
   }
   if ( getIndexOfCbsRepeat(receiveMsgPtr->cbsId, &index) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Repeat Timer not Present for CbsId: %d",receiveMsgPtr->cbsId);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Stopping Timer CBS_BIND_REPEAT as Object being deleted CbsId: %d, TimerId: %d",
                       receiveMsgPtr->cbsId,cbsRepeatTimer[index].cbsTimerId);

      StopTimerFrmwrk(cbsRepeatTimer[index].cbsTimerId);
      cbsRepeatTimer[index].cbsId = INVALID_CBS;
   }

   retCode = updateBindStatusCbsStatusTable(receiveMsgPtr->cbsId, BIND_FAIL );
   if ( retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_MAJOR,"updateLinkStatuscbsConfigurationTable failed for cbsId: [%d]", receiveMsgPtr->cbsId);
      return;
   }

   sendIntfDownToCbsh(receiveMsgPtr->cbsId);

   LOG_PRINT(LOG_MAJOR,"BindStatus Updated as BIND_FAIL for cbsId: [%d]", receiveMsgPtr->cbsId);
   LOG_PRINT(LOG_INFO,"Sending ALARM: EVENT_CBS_UNBIND");
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_CBS_UNBIND;

   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CBS; 
   sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->cbsId; 
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION; 
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "cbsId [%d] UnBinded",receiveMsgPtr->cbsId); 

   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   
   LOG_PRINT(LOG_INFO,"Starting Timer CBS_BIND_REPEAT.. ");
   startCbsTimer(receiveMsgPtr->cbsId, CBS_BIND_REPEAT, CBS_BIND_REPEAT_TIMER);
   FREEDECODEBUFFER(outputMsg);

   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}

/******************************* Function  Header*****************************
   Function Name :    sendIntfDownForInternalCbsToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : send INTF_DOWN message to CBSH for internal cbs server
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendIntfDownForInternalCbsToCbsh()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   CbsConfigurationTableSecIndices          cbsConfigTableSecIndex;
   CbsConfigurationTableApi                *cbsConfigData = NULL;
   OamsCfgCbshIntfDown                     cfgCbshIntfDown;
   I_U32                                   retCode;
   I_U32                                   outCount;
   I_U16                                   outSize;
   
   cbsConfigTableSecIndex.externalCbcServer = FALSE;
   retCode = getSecCbsConfigurationTable(&cbsConfigTableSecIndex, &cbsConfigData, &outCount, &outSize);
   if (retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Internal cbs Server not Configured, So no need to send INTF_DOWN message to CBSH");
      return;
   }
   if ( outCount > 1)
   {
      LOG_PRINT(LOG_MAJOR,"Two Internal cbs Server Configured, Which is not allowed ");
   }
   
   cfgCbshIntfDown.cbsId = cbsConfigData->cbsId;
  
   LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSH_INTF_DOWN for cbsId: [%d]", cfgCbshIntfDown.cbsId);

   cfgSendMessage((I_Void *)&cfgCbshIntfDown, sizeof(OamsCfgCbshIntfDown),
                ENT_CSAPP_CBSH, OAMS_CFG_CBSH_INTF_DOWN, 0);
   free (cbsConfigData); 
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}
/******************************* Function  Header*****************************
   Function Name :    sendModifyCbsToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : send INTF_UP message to CBSH for internal cbs server
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendModifyCbsToCbsh(CbsConfigurationTableApi *cbsConfigData)
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   MlpppConfigTableApi        *mlpppConfigRow = NULL;
   OamsCfgCbshModifyCbsIp     cfgCbshModifyIp;
   SetOmcIpAddressTableApi    *setOmcIpAddressTableApiPtr = NULL;
   I_U32                      outCount;
   I_U16                      outSize;
   I_S32                      retCode;

   if ( gCurrentConnectivityMode == MLPPP_MODE )
   {
      if(getallMlpppConfigTable(&mlpppConfigRow, &outCount, &outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL," gCurrentConnectivityMode set to \"MLPPP_MODE\" whereas No Row in MlpppConfig Table");
         return;
      }
      retCode = memcmp(cbsConfigData->cbsIpAddr,mlpppConfigRow->omcIpAddr, MAX_IP_ADDR_LEN);  
      if ( retCode == ZERO )
      {
          LOG_PRINT(LOG_INFO,"No Change in IP So no need to send MODIFY_CBS_IP message to CBSH");
          free(mlpppConfigRow);
          return;
      }
      memcpy(cfgCbshModifyIp.oldcbsIP,cbsConfigData->cbsIpAddr,MAX_IP_ADDR_LEN);
      memcpy(cfgCbshModifyIp.newcbsIP,mlpppConfigRow->omcIpAddr,MAX_IP_ADDR_LEN);
      cfgCbshModifyIp.oldcbsPortNum = cbsConfigData->cbsIpPort;
      cfgCbshModifyIp.newcbsPortNum = cbsConfigData->cbsIpPort;
      cfgCbshModifyIp.cbsId = cbsConfigData->cbsId;

      LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSH_MODIFY_CBS_IP for cbsId: [%d] OldcbsIp: [%s] OldCbcPort: [%d] \
                           NewcbsIp: [%s] NewCbcPort: [%d]", cfgCbshModifyIp.cbsId, cfgCbshModifyIp.oldcbsIP, 
                           cfgCbshModifyIp.oldcbsPortNum,cfgCbshModifyIp.newcbsIP,cfgCbshModifyIp.newcbsPortNum);

      cfgSendMessage((I_Void *)&cfgCbshModifyIp,sizeof(OamsCfgCbshModifyCbsIp),
                ENT_CSAPP_CBSH, OAMS_CFG_CBSH_MODIFY_CBS_IP, 0);
    /* Update cbsIp and Port in CbcConfigurationTable */
     retCode = updateCbsIpPortCbsConfigurationTable( cbsConfigData->cbsId, mlpppConfigRow->omcIpAddr, cbsConfigData->cbsIpPort  );
     if ( retCode != CLIB_SUCCESS )
     {
        LOG_PRINT(LOG_INFO,"updatecbsIpPortCbcConfigurationTable failed ");
     }
     else 
        LOG_PRINT(LOG_INFO,"updatecbsIpPortCbcConfigurationTable successful for cbsId: [%d], cbsId: [%s], CbcPort: [%d]",
                        cbsConfigData->cbsId, mlpppConfigRow->omcIpAddr, cbsConfigData->cbsIpPort);
     free(mlpppConfigRow);

   }
   else if ( gCurrentConnectivityMode == NO_MODE  || gCurrentConnectivityMode ==  ETHERNET_MODE)
   {
      if(getallSetOmcIpAddressTable(&setOmcIpAddressTableApiPtr, &outCount,&outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"Get All failed on SetOmcIpAddressTable");
         return;
      }
      retCode = memcmp(cbsConfigData->cbsIpAddr,setOmcIpAddressTableApiPtr->omcIpAddr, MAX_IP_ADDR_LEN);  
      if ( retCode == ZERO )
      {
          LOG_PRINT(LOG_INFO,"No Change in IP So no need to send MODIFY_CBS_IP message to CBSH");
          free(setOmcIpAddressTableApiPtr);
          return;
      }
      memcpy(cfgCbshModifyIp.oldcbsIP,cbsConfigData->cbsIpAddr,MAX_IP_ADDR_LEN);
      memcpy(cfgCbshModifyIp.newcbsIP,setOmcIpAddressTableApiPtr->omcIpAddr,MAX_IP_ADDR_LEN);
      cfgCbshModifyIp.oldcbsPortNum = cbsConfigData->cbsIpPort;
      cfgCbshModifyIp.newcbsPortNum = setOmcIpAddressTableApiPtr->omcIpPort;
      cfgCbshModifyIp.cbsId = cbsConfigData->cbsId;

      LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSH_MODIFY_CBS_IP for cbsId: [%d] OldcbsIp: [%s] OldCbcPort: [%d] \
                           NewcbsIp: [%s] NewCbcPort: [%d]", cfgCbshModifyIp.cbsId, cfgCbshModifyIp.oldcbsIP, 
                           cfgCbshModifyIp.oldcbsPortNum,cfgCbshModifyIp.newcbsIP,cfgCbshModifyIp.newcbsPortNum);

      cfgSendMessage((I_Void *)&cfgCbshModifyIp,sizeof(OamsCfgCbshModifyCbsIp),
                ENT_CSAPP_CBSH, OAMS_CFG_CBSH_MODIFY_CBS_IP, 0);
    /* Update cbsIp and Port in CbcConfigurationTable */
     retCode = updateCbsIpPortCbsConfigurationTable( cbsConfigData->cbsId, setOmcIpAddressTableApiPtr->omcIpAddr, setOmcIpAddressTableApiPtr->omcIpPort  );
     if ( retCode != CLIB_SUCCESS )
     {
        LOG_PRINT(LOG_INFO,"updatecbsIpPortCbcConfigurationTable failed ");
     }
     LOG_PRINT(LOG_INFO,"updatecbsIpPortCbcConfigurationTable successful for cbsId: [%d], cbsId: [%s], CbcPort: [%d]",
                        cbsConfigData->cbsId, cbsConfigData->cbsIpAddr, cbsConfigData->cbsIpPort);
   free(setOmcIpAddressTableApiPtr);
  }

}


/******************************* Function  Header*****************************
   Function Name :    sendIntfUpForInternalCbsToCbsh()
Parameters    : None
Return type   : I_Void
Purpose       : send INTF_UP message to CBSH for internal cbs server
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Void sendIntfUpForInternalCbsToCbsh()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);

   CbsConfigurationTableSecIndices          cbsConfigTableSecIndex;
   CbsConfigurationTableApi                *cbsConfigData = NULL;
   OamsCfgCbshIntfUp                       cfgCbshIntfUp;
   I_U32                                   retCode;
   I_U32                                   outCount;
   I_U16                                   outSize;
   
   cbsConfigTableSecIndex.externalCbcServer = FALSE;
   retCode = getSecCbsConfigurationTable(&cbsConfigTableSecIndex, &cbsConfigData, &outCount, &outSize);
   if (retCode != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"Internal cbs Server not Configured, So no need to send INTF_UP message to CBSH");
      return;
   }
   if ( outCount > 1)
   {
      LOG_PRINT(LOG_MAJOR,"Two Internal cbs Server Configured, Which is not allowed ");
   }
   
   sendModifyCbsToCbsh(cbsConfigData);

   cfgCbshIntfUp.cbsId = cbsConfigData->cbsId;
  
   LOG_PRINT(LOG_INFO," Sending Message OAMS_CFG_CBSH_INTF_UP for cbsId: [%d]",cfgCbshIntfUp.cbsId);

   cfgSendMessage((I_Void *)&cfgCbshIntfUp,sizeof(OamsCfgCbshIntfUp),
                ENT_CSAPP_CBSH, OAMS_CFG_CBSH_INTF_UP, 0);
  
   free (cbsConfigData); 
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}
/******************************* Function  Header*****************************
   Function Name :    checkParamModifiedcbsConfigReq()
Parameters    : None
Return type   : I_Bool
Purpose       : Check Which param modified in Modification Request of cbsConfigurationTable
Other Note    : Added For BSC R2.4
*****************************************************************************/
I_Bool checkParamModifiedCbsConfigReq(CbsConfigurationTableApi *receiveMsgPtr,CbsConfigurationTableApi *cbsConfigData)
{
    LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
    I_S32 retCode;
    retCode = memcmp(receiveMsgPtr->cbsIpAddr, cbsConfigData->cbsIpAddr,MAX_IP_ADDR_LEN);

    /* Modification of cbsIpAddress or CbcPort Not allowed */
    if ( (retCode != ZERO) || (receiveMsgPtr->cbsIpPort != cbsConfigData->cbsIpPort)
      || (receiveMsgPtr->externalCbcServer != cbsConfigData->externalCbcServer) )
    {
       LOG_PRINT(LOG_INFO,"cbsIPAddr/cbsIpPort/externalCbcCbcServer Modification not allowed, sending NACK.. ");
       cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
       return FALSE;
    }
    if ( receiveMsgPtr->externalCbcServer == FALSE )
    {
       LOG_PRINT(LOG_INFO,"No ParamaterModification allowed for internalcbsServer,sending NACK.. ");
       cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
       return FALSE;
    }
    LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
    return TRUE;

}

I_U32 getIndexOfCbsResp(I_U16 value,I_U16 *index)
{
   I_U32 counter;
   LOG_PRINT(LOG_INFO,"getIndexOfCbsResp : Entering Function");
   for ( counter = 0; counter < MAX_CBS_SERVER;counter++ )
   {
      if (cbsRespTimer[counter].cbsId == value)
      {
         LOG_PRINT(LOG_DEBUG,"getIndexOfCbsResp : Value of Index : %d",counter);
         *index=counter;
         return CFG_SUCCESS;
      }
   }
   LOG_PRINT(LOG_INFO,"getIndexOfCbsResp : Exiting Function");
   return CFG_FAILURE;
}

I_U32 getIndexOfCbsRepeat(I_U16 value,I_U16 *index)
{
   I_U32 counter;
   LOG_PRINT(LOG_INFO,"getIndexOfCbsRepeat : Entering Function");
   for ( counter = 0; counter < MAX_CBS_SERVER;counter++ )
   {
      if (cbsRepeatTimer[counter].cbsId == value)
      {
         LOG_PRINT(LOG_DEBUG,"getIndexOfCbsRepeat : Value of Index : %d",counter);
         *index=counter;
         return CFG_SUCCESS;
      }
   }
   LOG_PRINT(LOG_INFO,"getIndexOfCbsRepeat : Exiting Function");
   return CFG_FAILURE;
}

