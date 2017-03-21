/***********************************File Header ***************************
File Name        : oamscfg_externalport_handler.c
Purpose          : This file contains Cluster Table Implementation
Project          : BSC OAM
Subsystem        : Oams
Author           : Rishabh Garg
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>


/********************************* Function  Header********************************
Function Name:       setClusterTableHandler()
Parameters:          void
Return type:         void
Purpose:             To handle ClusterTable configuration 
                     from OMC.
Other Note:
 ************************************************************************************/
I_Void setClusterTableHandler()
{
  ClusterTableIndices clusterTabInd = {0};
  I_S32               dbStatus = 0; 
  ClusterTableApi     *pClusterTable = NULL;
  BicTableApi         *pBtsTable = NULL, *pTmpBtsTable = NULL;
  I_U32               rowCount = 0;
  I_U16               rowSize = 0;
  I_U16               btsCount = 0;
  I_U16               isUpdateAllowed = I_TRUE;
  I_U32               retVal = 0; 
  ClusterTableApi     *receivedMsgPtr = (ClusterTableApi *)((I_U8 *)gCfgMsgBuf + sizeof(sCmMsg));

  LOG_PRINT(INFO,"Entering setClusterTableHandler");
  LOG_PRINT(LOG_INFO,"setClusterTableHandler: clusterId %d, clusterNameString %s clusterNameSite %s,"
      " pktAggrCount: %u",receivedMsgPtr->clusterId,receivedMsgPtr->clusterNameString,
      receivedMsgPtr->clusterNameSite,receivedMsgPtr->pktAggrCount);

  clusterTabInd.clusterId = receivedMsgPtr->clusterId;
  dbStatus = getClusterTable(&clusterTabInd, &pClusterTable);
  
  if (dbStatus != DBLIB_SUCCESS)
  {
    LOG_PRINT(MAJOR,"setClusterTableHandler: Addition of New CluterId");
    retVal = clusterTableRangeCheck(receivedMsgPtr);
    if (retVal != CM_SUCCESS)
    {
      LOG_PRINT(DEBUG,"setClusterTableHandler: range Check Failed");
      cfgSendNackToCm(retVal);
      return;
    }
  
    dbStatus = insertClusterTable(receivedMsgPtr);
    if (dbStatus != DBLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"setClusterTableHandler: insertion of new entry failed");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return;
    }
  }
  else
  {
    if(receivedMsgPtr->pktAggrCount != pClusterTable->pktAggrCount)
    {
      /* Check if all the concerned BTSs are Locked or not */
      dbStatus = getallBicTable(&pBtsTable, &rowCount, &rowSize);
      if (dbStatus == DBLIB_SUCCESS)
      {
        for (btsCount = 0; btsCount < rowCount; btsCount++)
        {
          pTmpBtsTable = (BicTableApi *) ((I_U8 *)pBtsTable + (btsCount * rowSize));
          if ((pTmpBtsTable->clusterId == pClusterTable->clusterId) &&
              (LOCKED != pTmpBtsTable->adminState))
          {
            LOG_PRINT(DEBUG,"setClusterTableHandler: BTS: %u is not in LOCKED state, Update is not allowed",
                pTmpBtsTable->bicId);
            isUpdateAllowed = I_FALSE;
            break;
          }
        }

        free(pBtsTable);
      }
      else
      {
        LOG_PRINT(DEBUG,"setClusterTableHandler: No BTS is configured in BSC, Update is allowed");
      }

      if (isUpdateAllowed)
      {
        /* Cluster Table update is Allowed */
        pClusterTable->pktAggrCount = receivedMsgPtr->pktAggrCount;

        dbStatus = updateClusterTable(pClusterTable);
        if (dbStatus != DBLIB_SUCCESS)
        {
          LOG_PRINT(DEBUG,"setClusterTableHandler: update failed for clusterId: %u, PktAggrCnt: %u",
              pClusterTable->clusterId,pClusterTable->pktAggrCount);
          cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
          free(pClusterTable);
          return;
        }
      }
      else
      {
        /* Cluster Table update is Not Allowed */
        cfgSendNackToCm(CM_ERR_BTS_NOT_LOCKED_IN_DB);
        free(pClusterTable);
        return;
      }
    }
    if(receivedMsgPtr->clusterCSCallLimit != pClusterTable->clusterCSCallLimit)
    {
      isUpdateAllowed = I_TRUE;
      /* Check if all the concerned BTSs are Locked or not */
      dbStatus = getallBicTable(&pBtsTable, &rowCount, &rowSize);
      if (dbStatus == DBLIB_SUCCESS)
      {
        for (btsCount = 0; btsCount < rowCount; btsCount++)
        {
          pTmpBtsTable = (BicTableApi *) ((I_U8 *)pBtsTable + (btsCount * rowSize));
          if ((pTmpBtsTable->clusterId == pClusterTable->clusterId) &&
              (LOCKED != pTmpBtsTable->adminState))
          {
            LOG_PRINT(DEBUG,"setClusterTableHandler: BTS: %u is not in LOCKED state, Update is not allowed",
                pTmpBtsTable->bicId);
            isUpdateAllowed = I_FALSE;
            break;
          }
        }

        free(pBtsTable);
      }
      else
      {
        LOG_PRINT(DEBUG,"setClusterTableHandler: No BTS is configured in BSC, Update is allowed");
      }

      if (isUpdateAllowed)
      {
        /* Cluster Table update is Allowed */
        pClusterTable->pktAggrCount = receivedMsgPtr->pktAggrCount;
        pClusterTable->clusterCSCallLimit = receivedMsgPtr->clusterCSCallLimit;

        dbStatus = updateClusterTable(pClusterTable);
        if (dbStatus != DBLIB_SUCCESS)
        {
          LOG_PRINT(DEBUG,"setClusterTableHandler: update failed for clusterId: %u, PktAggrCnt: %u",
              pClusterTable->clusterId,pClusterTable->pktAggrCount);
          cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
          free(pClusterTable);
          return;
        }
      }
      else
      {
        /* Cluster Table update is Not Allowed */
        cfgSendNackToCm(CM_ERR_BTS_NOT_LOCKED_IN_DB);
        free(pClusterTable);
        return;
      }
    }
    else
    {
      LOG_PRINT(LOG_INFO,"setClusterTableHandler: Modify Opertion on Cluster Table : No change in parameters");
    }

    free(pClusterTable);
  }

  cfgSendAckToCm();
}

/********************************* Function  Header********************************
Function Name:       clusterTableRangeCheck
Parameters:          Pointer to ClusterTable
Return type:         error or CM_SUCCESS
Purpose:             Validation of ClusterTable configuratiion rxd
                     from OMC.
Other Note:
 ************************************************************************************/
I_U32 clusterTableRangeCheck(ClusterTableApi *pClusterTable)
{
  I_U8 length = 0;
  LOG_PRINT(LOG_DEBUG,"ENtering Funcion clusterTableRangeCheck");
  if ((pClusterTable->clusterId < 1) || (pClusterTable->clusterId > CLUSTER_ID_RANGE))
  {
    LOG_PRINT(LOG_INFO,"clusterTableRangeCheck : Range Check Failed - clusterId : %d",\
            pClusterTable->clusterId);
    cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_ID_VALUE);
    return (FALSE);
  }
  length = strlen(pClusterTable->clusterNameString);
  if((length == 0) || (length >20))
  {
    LOG_PRINT(LOG_INFO,"clusterTableRangeCheck : Range Check Failed - "
                       "clusterNameString Len: %d",length);
    cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_STRING_LEN);
    return (FALSE);
  }
  length = strlen(pClusterTable->clusterNameSite);
  if((length == 0) || (length >20))
  {
    LOG_PRINT(LOG_INFO,"clusterTableRangeCheck : Range Check Failed - "
                       "clusterNameSite Len : %d",length);
    cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_SITE_LEN);
    return (FALSE);
  }
  if((pClusterTable->pktAggrCount < MIN_PKT_AGGR_COUNT) || 
     (pClusterTable->pktAggrCount > MAX_PKT_AGGR_COUNT))
  {
    LOG_PRINT(LOG_INFO,"clusterTableRangeCheck : Range Check Failed - "
                       "pktAggrCount : %d",pClusterTable->pktAggrCount);
    cfgSendNackToCm(CM_ERR_PKT_AGGR_COUNT);
    return (FALSE);
  }

  return(CM_SUCCESS);
}

/********************************* Function  Header********************************
Function Name:       deleteClusterTableHandler()
Parameters:          void
Return type:         void
Purpose:             To handle ClusterTable configuration 
                     from OMC.
Other Note:
 ************************************************************************************/
I_Void delClusterTableHandler()
{
  I_S32                retVal = 0;
  ClusterTableIndices  clusterTabInd = {0};
  ClusterTableApi      *receivedMsgPtr = (ClusterTableApi *)((I_U8 *)gCfgMsgBuf + sizeof(sCmMsg));
  ClusterTableApi      *pClusterTable = NULL;
  BicTableApi          *pBtsTable = NULL;
  BicTableApi          *pTempBtsTable = NULL;
  I_U32                outRows = 0;
  I_U16                outSize = 0;
  I_S32                dbStatus = DBLIB_SUCCESS;
  I_U32                count = 0;
  
  clusterTabInd.clusterId = receivedMsgPtr->clusterId;
  dbStatus = getClusterTable(&clusterTabInd, &pClusterTable);
  
  if (dbStatus != DBLIB_SUCCESS)
  {
    LOG_PRINT(DEBUG,"delClusterTableHandler: No table with cluster Id %d exits",clusterTabInd.clusterId);
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  dbStatus = getallBicTable(&pBtsTable, &outRows, &outSize);
  if(dbStatus != DBLIB_SUCCESS)
  {
    LOG_PRINT(LOG_INFO,"delClusterTableHandler: no Row present in Bic Table Thus deleting cluster Table");
    retVal = deleteClusterTable( &clusterTabInd);
    if (retVal !=  DBLIB_SUCCESS)
    {
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
      free(pClusterTable);
      return;
    }

    free(pClusterTable);
  }
  else
  {
    for (count = 0; count < outRows; count ++)
    {
      pTempBtsTable = (BicTableApi *)((I_U8 *)pBtsTable + count*outSize);
      if(pTempBtsTable->clusterId == clusterTabInd.clusterId)
      {
        LOG_PRINT(LOG_INFO,"delClusterTableHandler: Cluster Id %d linked with Bts id %d",
                  clusterTabInd.clusterId, pTempBtsTable->bicId);
        LOG_PRINT(DEBUG,"delClusterTableHandler: Del failed for clusterId %d", clusterTabInd.clusterId);
        cfgSendNackToCm(CM_ERR_CLUSTER_ID_USED_IN_BTS_TABLE);
        free(pClusterTable);
        free(pBtsTable);
        return;
      }
    }
    retVal = deleteClusterTable( &clusterTabInd);
    if (retVal !=  DBLIB_SUCCESS)
    {
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
      free(pClusterTable);
      free(pBtsTable);
      return;
    }

    free(pClusterTable);
    free(pBtsTable);
  }
  cfgSendAckToCm();
}
