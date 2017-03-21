/***********************************File Header ***************************
   File Name        : oamscfg_consistency_check.c
Purpose          : This file contains functions definitions for CFG
consistency check  methods.
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent 
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>

/********************************* Function  Header*****************************
Function Name   : doConsistencyChecksOnSetOnRaTable()
Parameters      : RaTableApi*  : receivedMsgPtr 
Return type     : I_U32
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
I_U32 doConsistencyChecksOnSetOnRaTable(RaTableApi  *receivedMsgPtr)
{
   LaTableApi* laTblApiPtr = PNULL;
   LaTableIndices apiLaIndex;
   I_S32  ret = CM_FAILURE;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL; 
   
   /* Checks BssPsPreConfigTable must be configured already */
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < rowsCount)
   {
      /*Do Nothing*/
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB Call getallBssPsPreConfigTable returned [%d]",ret);
      return CM_ERR_GPRS_NOT_ALLOWED;
   }
  
   /* Check if entry is present in DB or not */
   apiLaIndex.lac =  receivedMsgPtr->lac;

   ret = getLaTable(&apiLaIndex, &laTblApiPtr); 
   
   if (laTblApiPtr == PNULL)
   {
      LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnPSCellTable : lac[%u] not present in La Table for Rac[%u], Sending Nack", receivedMsgPtr->lac, receivedMsgPtr->rac);
      return CM_ERR_LAC_NOT_PRESENT;
   }
   
   free(laTblApiPtr);
   
   return CM_SUCCESS;
   
}

/********************************* Function  Header*****************************
Function Name   : doConsistencyChecksOnSetOnLepInfoTable()
Parameters      : LepInfoTableApi*  : receivedMsgPtr 
                : I_Bool : isAdd (TRUE if request is for row addition)
Return type     : I_U32
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
I_U32 doConsistencyChecksOnSetOnLepInfoTable(LepInfoTableApi  *receivedMsgPtr, I_Bool isAdd)
{
   BssPsPreConfigTableApi *psPreConfigTablePtr = PNULL;
   GbInterfaceTableApi *gbInterfaceTablePtr = PNULL;
   LepInfoTableApi *lepInfoTableApiPtr = PNULL;
   SetNeIpAddressTableApi *setNeIpAddressTableApiPtr = PNULL;

   I_U32 rowsCount= 0;
   I_U16 outSize = 0;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;
   I_U32 outCountNeIp = 0;
   I_U16 outSizeNeIp = 0;
   I_U16 *neIp[4];// = {0};
   I_U16 *lepIp[4];// = {0};

   I_S32  ret = CM_FAILURE;
   I_S32 i = 0, j = 0;
   I_U32 dotCount = 0; 
   I_U16 lepLen = 0; 
   LOG_PRINT(LOG_DEBUG,"Entering doConsistencyChecksOnSetOnLepInfoTable");
   LOG_PRINT(LOG_DEBUG,"receivedMsgPtr->lep = %s",receivedMsgPtr->lep);

   while (i < OAMS_CFG_LEP_LENGTH && dotCount < 3)
   {
      if ('.' == receivedMsgPtr->lep[i])
         dotCount++;
         i++;
   }

   if (dotCount != 3)
   {
       LOG_PRINT(LOG_MAJOR, "LEP IP is not valid (dotCount != 3) :: Sending Nack ") ;
       return CM_ERR_LEP_IP_INVALID;
   }
 
   for (j = 0; j < 3; j++)
   {
      if ((receivedMsgPtr->lep[i + j] < '0') || (receivedMsgPtr->lep[i + j] > '9'))
         break;
   }
   if (0 == j)
   {
       LOG_PRINT(LOG_MAJOR, "LEP IP is not valid (Non Digit) :: Sending Nack ") ;
       return CM_ERR_LEP_IP_INVALID;
   }
   receivedMsgPtr->lep[i + j] = 0;
   lepLen = i + j;
   for (j = 0; j < lepLen; j++)
   {
     if ('.' == receivedMsgPtr->lep[j])
       continue;
     if ((receivedMsgPtr->lep[j] < '0') || (receivedMsgPtr->lep[j] > '9'))
       break;
   }
   if ( j < lepLen )
   {
      LOG_PRINT(LOG_MAJOR, "LEP IP is not valid :: Sending Nack ") ;
      return CM_ERR_LEP_IP_INVALID;
   }
   ret = getallSetNeIpAddressTable(&setNeIpAddressTableApiPtr,&outCountNeIp, &outSizeNeIp);
   if(ret != CLIB_SUCCESS)
   {
       LOG_PRINT(LOG_CRITICAL,"getallSetNeIpAddressTable DB call failed..");
       return CM_ERR_GET_ALL_OPERATION_FAILED;
   }
   LOG_PRINT(LOG_DEBUG,"receivedMsgPtr->lep = %s",receivedMsgPtr->lep);
   LOG_PRINT(LOG_DEBUG,"setNeIpAddressTableApiPtr->nodeIpAddr = %s",setNeIpAddressTableApiPtr->nodeIpAddr);
   /*
   if(ret != TRUE)
   {
      convertIpToToken(receivedMsgPtr->lep, lepIp);
      convertIpToToken(setNeIpAddressTableApiPtr->nodeIpAddr, neIp);
      for ( i = 0; i < 4; i++)
      {
         LOG_PRINT(LOG_DEBUG," lep[%u] = %u", i, lepIp[i]);
         LOG_PRINT(LOG_DEBUG," Neip [%u] = %u", i, neIp[i]);
         if (lepIp[i] != neIp[i])
         {
            LOG_PRINT(LOG_CRITICAL, "Lep-Ip Address is not equal to Ne-Ip address..");
            free(setNeIpAddressTableApiPtr);
            LOG_PRINT(LOG_DEBUG,"after free");
            return CM_ERR_LEP_AND_NE_IP_NOT_EQUAL;
         }
      }
   }
   LOG_PRINT(LOG_DEBUG,"before free");*/
   free(setNeIpAddressTableApiPtr);

   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < rowsCount)
   {
      free(psPreConfigTablePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB call getallBssPsPreConfigTable returned [%u]",ret);
      return CM_ERR_GPRS_NOT_ALLOWED;
   }
   ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outCountGb, &outSizeGb);
   if ( CLIB_SUCCESS == ret)
   {
      if (FR != gbInterfaceTablePtr->transportType)
      {
         if(LOCKED != bssLock())
         {
            LOG_PRINT(LOG_MAJOR,"Transport type is IP and BSS is not LOCKED so operation on Lep table not allowed");
            free(gbInterfaceTablePtr);
            return CM_ERR_BSS_UNLOCKED;
         }
      } 
      free(gbInterfaceTablePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"DB call getallBssPsPreConfigTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      return CM_ERR_GET_DB_OPER_FAILED;
   }
   if( isAdd )
   {
      ret = getallLepInfoTable( &lepInfoTableApiPtr, &rowsCount, &outSize);  
      if ( CLIB_SUCCESS == ret )
      {
         if ( ZERO < rowsCount)
         {
            LOG_PRINT(LOG_MAJOR," Maximum Leps Rows already present in LepInfo Table :%s line:%d",__FUNCTION__,__LINE__);
            free(lepInfoTableApiPtr); 
            return CM_ERR_MAX_ENTRY_PRES;
         }
         free(lepInfoTableApiPtr); 
      }
      else if(DBLIBERR_PTOPAGE_HAS_NO_ROWS != ret)
      {
         LOG_PRINT(LOG_MAJOR,"DB call getallLepInfoTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
         return CM_ERR_GET_ALL_OPERATION_FAILED;
      }
   }
  
   return CM_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : doConsistencyChecksOnSetOnRepInfoTable()
Parameters      : RepInfoTableApi*  : receivedMsgPtr 
                : I_Bool : isAdd (TRUE if request is for row addition)
Return type     : I_U32
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
I_U32 doConsistencyChecksOnSetOnRepInfoTable(RepInfoTableApi  *receivedMsgPtr, I_Bool isAdd)
{
   BssPsPreConfigTableApi *psPreConfigTablePtr = PNULL;
   RepInfoTableApi *repInfoTableApiPtr = PNULL;
   LepInfoTableApi *lepInfoTableApiPtr = PNULL;
   GbInterfaceTableApi *gbInterfaceTablePtr = PNULL;

   I_U32 rowsCount= 0;
   I_U32 lepCount= 0;
   I_U32 repCount= 0;
   I_U16 outSize = 0;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;
   I_S32  ret = CM_FAILURE;
   
   I_S32 i = 0, j = 0;
   I_U32 dotCount = 0; 
   I_U16 repLen = 0; 
   LOG_PRINT(LOG_DEBUG,"Entering doConsistencyChecksOnSetOnRepInfoTable");
   LOG_PRINT(LOG_DEBUG,"receivedMsgPtr->rep = %s",receivedMsgPtr->rep);

   while (i < OAMS_CFG_REP_LENGTH && dotCount < 3)
   {
      if ('.' == receivedMsgPtr->rep[i])
         dotCount++;
         i++;
   }

   if (dotCount != 3)
   {
       LOG_PRINT(LOG_MAJOR, "REP IP is not valid (dotCount != 3) :: Sending Nack ") ;
       return CM_ERR_REP_IP_INVALID;
   }
 
   for (j = 0; j < 3; j++)
   {
      if ((receivedMsgPtr->rep[i + j] < '0') || (receivedMsgPtr->rep[i + j] > '9'))
         break;
   }
   if (0 == j)
   {
       LOG_PRINT(LOG_MAJOR, "REP IP is not valid (Non Digit) :: Sending Nack ") ;
       return CM_ERR_LEP_IP_INVALID;
   }
   receivedMsgPtr->rep[i + j] = 0;
   repLen = i + j;
   for (j = 0; j < repLen; j++)
   {
     if ('.' == receivedMsgPtr->rep[j])
       continue;
     if ((receivedMsgPtr->rep[j] < '0') || (receivedMsgPtr->rep[j] > '9'))
       break;
   }
   if ( j < repLen )
   {
      LOG_PRINT(LOG_MAJOR, "REP IP is not valid :: Sending Nack ") ;
      return CM_ERR_REP_IP_INVALID;
   }
  
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < rowsCount)
   {
      free(psPreConfigTablePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB call getallBssPsPreConfigTable returned [%u]",ret);
      return CM_ERR_GPRS_NOT_ALLOWED;
   }
   
   ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outCountGb, &outSizeGb);
   if ( CLIB_SUCCESS == ret )
   {
      if (FR != gbInterfaceTablePtr->transportType)
      {
         if(LOCKED != bssLock())
         {
            LOG_PRINT(LOG_MAJOR,"Transport type is IP and BSS is not LOCKED so operation on Rep table not allowed");
            free(gbInterfaceTablePtr);
            return CM_ERR_BSS_UNLOCKED;
         }
      } 
      if( isAdd )
      {
         ret =  getallRepInfoTable( &repInfoTableApiPtr, &rowsCount, &outSize); 
         repCount = rowsCount;
         if ( CLIB_SUCCESS == ret )
         {
            if ( repCount == gbInterfaceTablePtr->maxNumReps )
            {
               LOG_PRINT(LOG_MAJOR,"Maximum Reps Rows[%u] already present in RepInfo Table",rowsCount);
               free(gbInterfaceTablePtr);
               free(repInfoTableApiPtr);
               return CM_ERR_MAX_ENTRY_PRES;
            }

            ret =  getallLepInfoTable( &lepInfoTableApiPtr, &rowsCount, &outSize); 
            if ( CLIB_SUCCESS == ret )
            {
               lepCount = rowsCount;
               if ( (lepCount * repCount) > gbInterfaceTablePtr->maxNumNsvcsOverIp)
               {
                  
                  LOG_PRINT(LOG_MAJOR,"Consistency Check failed (No. of Leps) [%u] * (No. of Reps [%u]) >  Maximum Number of maxNumNsvcsOverIp in GbInterface Table ",
                            lepCount, repCount, gbInterfaceTablePtr->maxNumNsvcsOverIp);
                  free(gbInterfaceTablePtr);
                  free(lepInfoTableApiPtr); 
                  free(repInfoTableApiPtr); 
                  return CM_ERR_MAX_ENTRY_PRES;
               }
               free(lepInfoTableApiPtr);
            }
            else
            { 
               LOG_PRINT(LOG_INFO,"DB call getallLepInfoTable returned [%d] :%s line:%d", ret, __FUNCTION__,__LINE__);
            }
            free(gbInterfaceTablePtr);
            free(repInfoTableApiPtr);
             
         }
         else if(DBLIBERR_PTOPAGE_HAS_NO_ROWS != ret)
         {
            LOG_PRINT(LOG_MAJOR,"DB call getallRepInfoTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
            free(gbInterfaceTablePtr);
            return CM_ERR_GET_ALL_OPERATION_FAILED;
         }
      }/* End case isAdd */
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"DB call getGbInterfaceTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      return CM_ERR_GET_DB_OPER_FAILED;
   } 
   
   return CM_SUCCESS;
   
}

/********************************* Function  Header*****************************
Function Name   : doConsistencyChecksOnSetOnNsvcTable()
Parameters      : NsvcTableApi*  : receivedMsgPtr 
Return type     : I_U32
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
I_U32 doConsistencyChecksOnSetOnNsvcTable(NsvcTableApi  *receivedMsgPtr, I_Bool isAdd)
{

   NsvcTableApi *tmpNsvcTableApiPtr = PNULL;
   FrLinkTableApi *frLinkTblApiPtr = PNULL;
   GbInterfaceTableApi *gbInterfaceTablePtr = PNULL;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL;
   NsvcTableApi* nsvcTableApiPtr = PNULL;
   FrLinkTableIndices apiFrLinkIndex;
   
   I_U32 outCount = 0;
   I_U16 outSize  = 0;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;
   I_S32 ret = CM_FAILURE;
   I_U32 i = 0;

   
   LOG_PRINT(LOG_INFO,"In doConsistencyChecksOnSetOnNsvcTable");
   
   apiFrLinkIndex.frChnId = receivedMsgPtr->frChnId;
   if (CLIB_SUCCESS !=  getFrLinkTable(&apiFrLinkIndex, &frLinkTblApiPtr))
   {
      LOG_PRINT(LOG_MAJOR, "FrChnId[%u] does not exist in FrLinkTable",receivedMsgPtr->frChnId);
      return CM_ERR_FR_LINK_DOES_NOT_EXIST;
   }
   free(frLinkTblApiPtr);
   
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &outCount, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < outCount)
   {
      free(psPreConfigTablePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB call getallBssPsPreConfigTable returned [%u]",ret);
      return CM_ERR_GPRS_NOT_ALLOWED;
   }
   ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outCountGb, &outSizeGb);
   if ( CLIB_SUCCESS == ret )
   {
      ret = getallNsvcTable( &nsvcTableApiPtr, &outCount, &outSize);
      if ( CLIB_SUCCESS == ret )
      {
         if(isAdd)
         {
            if ( outCount == gbInterfaceTablePtr->maxNumNsvcsOverFr)
            {
               LOG_PRINT(LOG_MAJOR,"Maximum Nsvc Rows[%d] already present in Nsvc Table",outCount);
               free(nsvcTableApiPtr); 
               free(gbInterfaceTablePtr);
               return CM_ERR_MAX_ENTRY_PRES; 
            }
         } /* end if(isAdd) */
         
         for (i = 0; i < outCount; i++)
         {
            tmpNsvcTableApiPtr = (NsvcTableApi*)(((I_U8 *)(nsvcTableApiPtr)) + (i * outSize));
            if ((tmpNsvcTableApiPtr->frChnId == receivedMsgPtr->frChnId) && (tmpNsvcTableApiPtr->nsvcId != receivedMsgPtr->nsvcId))
            {
               LOG_PRINT(LOG_MAJOR, "FrChnId[%u] is already associated with some other NSVC[%u]: Sending Nack",receivedMsgPtr->frChnId, tmpNsvcTableApiPtr->nsvcId);
               free(gbInterfaceTablePtr);
               free(nsvcTableApiPtr);
               return CM_ERR_FR_CHANNEL_ALREADY_ASSOCIATED;
            }
         } 
         free(nsvcTableApiPtr); 
         free(gbInterfaceTablePtr);
      }
      else if(DBLIBERR_PTOPAGE_HAS_NO_ROWS != ret)
      {
         LOG_PRINT(LOG_MAJOR,"DB call getallNsvcTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
         return CM_ERR_GET_ALL_OPERATION_FAILED;
      }
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"DB call getallGbInterfaceTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      return CM_ERR_GET_DB_OPER_FAILED;
   }   
   return CM_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : doConsistencyChecksOnSetOnFrLinkTable()
Parameters      : FrLinkTableApi*  : receivedMsgPtr 
Return type     : I_U32
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
I_U32 doConsistencyChecksOnSetOnFrLinkTable(FrLinkTableApi  *receivedMsgPtr, I_Bool isAdd)
{
   FrLinkTableApi *frLinkTblApiPtrAll = PNULL;
   FrLinkTableApi *frLinkTblApiPtr = PNULL;
   NsvcTableApi *nsvcTableApiPtr = PNULL;
   TrunkTableApi* trunkTableApiPtr = PNULL;
   TrunkTableIndices trunkTableIndices;
   
   CicTableApi *cicTablePtr = PNULL;
   LinkTableApi *linkTablePtr = PNULL;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL;
   
   GbInterfaceTableApi *gbInterfaceTablePtr = PNULL;

   I_U32 rowsCount = 0;
   I_U16 outSize = 0;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;
   I_U32 timeSlot = 0;
   
   I_U32 outCountFr = 0;
   I_S32 ret = CM_FAILURE;
   I_U16 outSizeFr = 0;
   
   I_S32 totalFrTimeslots = 0;
   I_U32 i = 0;
   I_U32 tsBitMap = 0x00000000;
   I_U32 trunkUsageType=0;
   I_U32 retStatus;
   I_U32 temp;
   
   LOG_PRINT(LOG_INFO,"In doConsistencyChecksOnSetOnFrLinkTable");
   
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < rowsCount)
   {
      free(psPreConfigTablePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB call getallBssPsPreConfigTable returned [%u]",ret);
      return CM_ERR_GPRS_NOT_ALLOWED;
   }
   /* In case of modification on FrLink Table Nsvc should be Locked */
   if (FALSE == isAdd)
   {
      ret =  getNsvcForFrChannel(receivedMsgPtr->frChnId, &nsvcTableApiPtr, &rowsCount, &outSize);
      if (CLIB_SUCCESS == ret)
      {
         if ( UNLOCKED == nsvcTableApiPtr->adminState )
         {
            LOG_PRINT(LOG_MAJOR, "NSVC is Unlocked");
            free(nsvcTableApiPtr);
            return CM_ERR_OBJECT_NOT_LOCKED;
         }
         free(nsvcTableApiPtr);
      }
      else 
      {
         LOG_PRINT(LOG_INFO," No Nsvc Associated with this Fr Link, DB call getNsvcForFrChannel returned [%u] :%s line:%d", ret, __FUNCTION__, __LINE__);
      }
   }

   outCountFr= 0;
   outSizeFr = 0;
   ret = getallFrLinkTable(&frLinkTblApiPtrAll, &outCountFr, &outSizeFr);
   if (CLIB_SUCCESS == ret)
   { 
      if(TRUE == isAdd) 
      {  
         ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outCountGb, &outSizeGb);
         if ( CLIB_SUCCESS == ret )
         {
            LOG_PRINT(LOG_INFO,"Entries in frLink Table :: [%u] and Value of maxNumNsvcsOverFr :: [%u]",outCountFr,gbInterfaceTablePtr->maxNumNsvcsOverFr);
            if (outCountFr == gbInterfaceTablePtr->maxNumNsvcsOverFr)
            {
               LOG_PRINT(LOG_MAJOR, "Maximum number of FrLinks already present i.e. [%u]", outCountFr);
               free(frLinkTblApiPtrAll);
               free(gbInterfaceTablePtr);
               return CM_ERR_MAX_ENTRY_PRES;
            }
         }
         else
         {
            LOG_PRINT(LOG_MAJOR,"DB call getallGbInterfaceTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
            free(frLinkTblApiPtrAll);
            return CM_ERR_GET_ALL_OPERATION_FAILED;
         }
         free(gbInterfaceTablePtr);
      }
   }
   else if(DBLIBERR_PTOPAGE_HAS_NO_ROWS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"DB call getallFrLinkTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      return CM_ERR_GET_ALL_OPERATION_FAILED;
   }
   rowsCount= 0;
   outSize = 0;
   
   trunkTableIndices.e1Num = receivedMsgPtr->e1Id;
   ret = getTrunkTable(&trunkTableIndices, &trunkTableApiPtr);
   if ( CLIB_SUCCESS != ret )
   {
      LOG_PRINT(LOG_MAJOR, "E1Id <%d> does not exists in Trunk Table:%s line:%d",receivedMsgPtr->e1Id, __FUNCTION__,__LINE__);
      free(frLinkTblApiPtrAll);
      return CM_ERR_REFERENCED_OBJECT_DOES_NOT_EXIST;
   }
   
   if ( SYS_E1_USAGE_AIF != trunkTableApiPtr->usageType )
   {
      LOG_PRINT(LOG_MAJOR, "The usage type of E1 with E1 Id <%d> is not SYS_E1_USAGE_AIF :%s line:%d",receivedMsgPtr->e1Id, __FUNCTION__,__LINE__);
      free(trunkTableApiPtr);
      free(frLinkTblApiPtrAll);
      return CM_ERR_E1_USAGE_TYPE_NOT_AIF;
   }
   else
   {
      free(trunkTableApiPtr);
   }
  
   for ( i = 0; i < outCountFr; i++)
   {
      frLinkTblApiPtr = (FrLinkTableApi*)(((I_U8 *)(frLinkTblApiPtrAll)) + (i * outSizeFr));
      /*
       In case of modify on FrLink Table subtract the already 
       * existing numTs for that Fr and later the numTs 
       * received in the request will be added in totalFrTimeslots */
       
      if (FALSE == isAdd && frLinkTblApiPtr->frChnId == receivedMsgPtr->frChnId)
      {
          totalFrTimeslots -= frLinkTblApiPtr->numTs;
      }
      totalFrTimeslots += frLinkTblApiPtr->numTs; 
   }
    
   totalFrTimeslots += receivedMsgPtr->numTs;

   if (totalFrTimeslots > getNumElemMccFrResource())
   {
      LOG_PRINT(LOG_MAJOR,"requested timeslots are not available in MccLinkResourceTable :%s line:%d",__FUNCTION__,__LINE__);
      free(frLinkTblApiPtrAll);
      return CM_ERR_MCC_RESOURCE_NOT_AVAILABLE;
   }
   /* Changes for  TsGroup Start*/
   tsBitMap = getBusyTsMapForTsGroup(receivedMsgPtr->e1Id);
   /* Changes for  TsGroup End*/
   for ( timeSlot = receivedMsgPtr->startTs; timeSlot < (receivedMsgPtr->startTs + receivedMsgPtr->numTs); timeSlot++ )
   {
      /* Check if timeslot is associated for some other Fr Link; if yes then send Nack */
      for ( i = 0; i < outCountFr; i++)
      {
         frLinkTblApiPtr = (FrLinkTableApi*)(((I_U8 *)(frLinkTblApiPtrAll)) + (i * outSizeFr));
         if ( (timeSlot >= frLinkTblApiPtr->startTs) && timeSlot < (frLinkTblApiPtr->startTs + frLinkTblApiPtr->numTs) &&
              (receivedMsgPtr->e1Id == frLinkTblApiPtr->e1Id) && (frLinkTblApiPtr->frChnId != receivedMsgPtr->frChnId) )
         {
            LOG_PRINT(LOG_INFO," TimeSlot <%d> is configured for FR for frChnId [%u] ", timeSlot, frLinkTblApiPtr->frChnId);
            free(frLinkTblApiPtrAll);
            return CM_ERR_TS_CONFIGURED_FOR_FR;
         }
      }
      
      /* Check if timeslot is configured for CIC; if yes send Nack */
      ret = getCicTableUsingE1Ts(receivedMsgPtr->e1Id, timeSlot, &cicTablePtr );
      if(CLIB_SUCCESS == ret )
      {
         LOG_PRINT(LOG_INFO," TimeSlot <%d> is configured for CIC ", timeSlot);
         free(cicTablePtr);
         free(frLinkTblApiPtrAll);
         return CM_ERR_TS_CONFIGURED_FOR_CIC;
      }
   
      /* Check if timeslot is configured for MTP2; if yes siend Nack */
      ret = getLinkTableUsingE1Ts( receivedMsgPtr->e1Id, timeSlot, &linkTablePtr );
      if(CLIB_SUCCESS == ret )
      {
         LOG_PRINT(LOG_INFO," TimeSlot <%d> is configured for MTP2 Link ", timeSlot);
         free(linkTablePtr);
         free(frLinkTblApiPtrAll);
         return CM_ERR_TS_CONFIGURED_FOR_LINK;
      }
   
      /* Check if timeslot is configured for MLPP; if yes send Nack */
      if( I_TRUE == isMlpppConfigExistsForE1Ts(receivedMsgPtr->e1Id, timeSlot) )
      {
         LOG_PRINT(LOG_INFO," TimeSlot <%d> is configured for Mlpp", timeSlot);
         free(frLinkTblApiPtrAll);
         return CM_ERR_TS_CONFIGURED_FOR_MLPP;
      }

      /*Changes for TsGroup Start */
      temp=1<<timeSlot;
      if ((tsBitMap & temp) == temp)
      {
         LOG_PRINT(LOG_INFO," TimeSlot <%d> is configured busy in E1 [%u] ", timeSlot, receivedMsgPtr->e1Id);
         free(frLinkTblApiPtrAll);
         return CM_ERR_TS_CONFIGURED_FOR_TSGROUP;
      }
      /*Changes for TsGroup End */
   }

   
   free(frLinkTblApiPtrAll);
   return CM_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : doConsistencyChecksOnSetOnGbInterfaceTable()
Parameters      : GbInterfaceTableApi  : receivedMsgPtr received in Set Request
Return type     : I_U32 : Error Code | CM_SUCCESS
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
I_U32 doConsistencyChecksOnSetOnGbInterfaceTable(GbInterfaceTableApi *rcvdMsgPtr)
{
   if ((rcvdMsgPtr->tFcTh < rcvdMsgPtr->tFcC))
   {
      LOG_PRINT(LOG_DEBUG,"gbInterfaceTable consistency check failed tFcTh [%u] < tFcC [%u] in function:%s line:%d",
                rcvdMsgPtr->tFcTh, rcvdMsgPtr->tFcC, __FUNCTION__, __LINE__);
      return (CM_ERR_CONSISTENCY_CHECK_FAILED);
   }
   if (((rcvdMsgPtr->tFcSup * 100 ) * (rcvdMsgPtr->nMaxFcRep + 1 )) >= (rcvdMsgPtr->tFcC * 1000))
   {
      LOG_PRINT(LOG_DEBUG,"gbInterfaceTable consistency check [ (tFcSup * 100) * (nMaxFcRep + 1) < tFcC] failed. tFcSup = [%u], nMaxFcRep = [%u], tFcC = [%u] in function:%s line:%d",
                rcvdMsgPtr->tFcSup, rcvdMsgPtr->nMaxFcRep, rcvdMsgPtr->tFcC, __FUNCTION__, __LINE__);
      return (CM_ERR_CONSISTENCY_CHECK_FAILED);
   }
   return CM_SUCCESS;
}

I_Bool isMlpppConfigExistsForE1Ts(I_U16 e1Id, I_U8 timeSlot)
{
   I_Bool retVal;
   I_S32 errCode;
   I_U32 outCount = 0 , cond = 0 , counter = 0;
   I_U16 outSize  = 0;
   I_U32 rowCount = 0;
   MlpppConfigTableApi *outData = NULL, *tempData = NULL;

   errCode = getallMlpppConfigTable(&outData, &outCount, &outSize);

   if( errCode != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"DB call isMlpppConfigExistsForE1Ts failed: errCode: %d", errCode);
      retVal = I_FALSE;
      return retVal;
    }

    for ( rowCount = 0; rowCount < outCount; rowCount++ )
    {
      tempData = (MlpppConfigTableApi*)((I_U8*)outData + (rowCount * outSize));

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId1 == e1Id) && (tempData->timeslot1 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId2 == e1Id) && (tempData->timeslot2 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;
      if((tempData->trunkportId3 == e1Id) && (tempData->timeslot3 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId4 == e1Id) && (tempData->timeslot4 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId5 == e1Id) && (tempData->timeslot5 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId6 == e1Id) && (tempData->timeslot6 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId7 == e1Id) && (tempData->timeslot7 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId8 == e1Id) && (tempData->timeslot8 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;
      
      if((tempData->trunkportId9 == e1Id) && (tempData->timeslot9 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId10 == e1Id) && (tempData->timeslot10 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId11 == e1Id) && (tempData->timeslot11 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId12 == e1Id) && (tempData->timeslot12 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId13 == e1Id) && (tempData->timeslot13 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId14 == e1Id) && (tempData->timeslot14 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId15 == e1Id) && (tempData->timeslot15 == timeSlot))
      {
          cond = 1;
          break;
      }

      if(tempData->numChannel == counter)    break;
      counter++;

      if((tempData->trunkportId16 == e1Id) && (tempData->timeslot16 == timeSlot))
      {
          cond = 1;
          break;
      }
   } /* end of for */

   if( cond == 1)
   {
       LOG_PRINT(LOG_INFO,"Db call isMlpppConfigExistsForE1Ts successful: outSize: %d  outCount: %d", outSize, outCount);
       retVal = I_TRUE;
    }
   else
   {
       LOG_PRINT(DEBUG,"DB call isMlpppConfigExistsForE1Ts failed: errCode: %d", errCode);
       retVal = I_FALSE;
   }

   free(outData);
   return retVal;
}


/******************************* END ******************************************/
/******************   Change History *******************************************
   Release     Patch       Author              Description
   R2.5                    Aricent GGN         consistency Check Methods for Tables
   
 ******************************************************************************/
