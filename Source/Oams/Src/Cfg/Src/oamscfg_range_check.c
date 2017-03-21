/***********************************File Header ***************************
   File Name        : oamscfg_alarm_handler.h
Purpose          : This file contains functions definitions for CFG
Alarm handler  methods.
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>


/********************************* Function  Header********************************
   Function Name:       bssTableRangeChk()
Parameters:          Pointer to BssTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for Bss table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool bssTableRangeChk(BssTableApi* rcvdMsgPtr)
{
   if ((rcvdMsgPtr->bscId < 0) || (rcvdMsgPtr->bscId > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->adminState != LOCK) && (rcvdMsgPtr->adminState != UNLOCK))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->gprsEnabled != FALSE) && (rcvdMsgPtr->gprsEnabled != TRUE))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
//   if ((rcvdMsgPtr->bssReset != TRUE) && (rcvdMsgPtr->bssReset != FALSE))
   if (rcvdMsgPtr->bssReset != NO_RESET_CMD)
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }

   if ((rcvdMsgPtr->callReestablishmentInd !=ALLOWED) && (rcvdMsgPtr->callReestablishmentInd != NOT_ALLOWED))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->attInd != ALLOWED) && (rcvdMsgPtr->attInd != NOT_ALLOWED))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->t3212 < 0) || (rcvdMsgPtr->t3212 > 255))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->mcc > 0x999)
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (( rcvdMsgPtr->mnc & 0xf) == 0xf)
   {
      /* Two digit MNC */
      if (  rcvdMsgPtr->mnc > 0x99F )
      {
         LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
         return FALSE;
      }
   }
   else /* Three digit MNC */
      if (rcvdMsgPtr->mnc > 0x999)
      {
         LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
         return(FALSE);
      }
   if ((rcvdMsgPtr->ncc < 0) || (rcvdMsgPtr->ncc > 7))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->nccPermitted < 0) || (rcvdMsgPtr->nccPermitted > 255))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->dtxDnLinkInd < 0) || (rcvdMsgPtr->dtxDnLinkInd > 1))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->dtxUpLinkInd < 0) || (rcvdMsgPtr->dtxUpLinkInd > 7) )
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->minChannelGap < 1) || (rcvdMsgPtr->minChannelGap > 123))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if((rcvdMsgPtr->txInteger < 0) || (rcvdMsgPtr->txInteger > 15))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);   
   }
   if ((rcvdMsgPtr->radioLinkTimeout < 0) || (rcvdMsgPtr->radioLinkTimeout > 15))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->maxRetrans < 0) || (rcvdMsgPtr->maxRetrans > 3))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->tWaitCellBlock < 30) || (rcvdMsgPtr->tWaitCellBlock > 1800))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->tWaitTrxBlock < 30) || (rcvdMsgPtr->tWaitTrxBlock > 1800))
   {
      LOG_PRINT(LOG_DEBUG," bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->cicMaster != 0) && (rcvdMsgPtr->cicMaster != 1))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }

   /* CS3.0 Changes : Start */
   /* if (((rcvdMsgPtr->tHandRqd < 0) || (rcvdMsgPtr->tHandRqd >10))) - commented during removal of warnings */
   if (rcvdMsgPtr->tHandRqd >10) 
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->bssapTimer8 < 15) || (rcvdMsgPtr->bssapTimer8 >60))) 
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->bssapTimer7 < 1) || (rcvdMsgPtr->bssapTimer7 >60))) 
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
/* CS3.0 Changes : End */
/* Changes For WCDMA-GSM HO Feature : Start */
   if ((rcvdMsgPtr->wcdma_FddHoAllowed != ALLOWED) && (rcvdMsgPtr->wcdma_FddHoAllowed != NOT_ALLOWED)) 
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d,value %d",__FUNCTION__,__LINE__,rcvdMsgPtr->wcdma_FddHoAllowed);
      return(FALSE);
   }
   if ((rcvdMsgPtr->t3121 < 5) || (rcvdMsgPtr->t3121 >25)) 
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d value:%d",__FUNCTION__,__LINE__,rcvdMsgPtr->t3121);
      return(FALSE);
   }
/*if ((rcvdMsgPtr->serviceIndicator != ENABLED) && (rcvdMsgPtr->serviceIndicator !=DISABLED)) 
{
   LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d value:%d",__FUNCTION__,__LINE__,rcvdMsgPtr->serviceIndicator);
   return(FALSE);
}*/
/* Changes For WCDMA-GSM HO Feature : End */
   /* Changes for AmrRltoTimeOut Feature */
   if ((rcvdMsgPtr->amrRadioLinkTimeout < 0) || (rcvdMsgPtr->amrRadioLinkTimeout > 15))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
  /* EGPRS Changes Starts*/

   if ((rcvdMsgPtr->egprsEnabled != FALSE) && (rcvdMsgPtr->egprsEnabled != TRUE))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }

  /* EGPRS Changes Ends*/

   if ((rcvdMsgPtr->localSwitchingSupport != ENABLED) && (rcvdMsgPtr->localSwitchingSupport !=DISABLED)) 
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d value:%d",__FUNCTION__,__LINE__,rcvdMsgPtr->localSwitchingSupport);
      return(FALSE);
   }
   if((rcvdMsgPtr->bssPktAggrCount < MIN_PKT_AGGR_COUNT) || (rcvdMsgPtr->bssPktAggrCount > MAX_PKT_AGGR_COUNT))
   {
      LOG_PRINT(LOG_DEBUG,"bssTable Rangecheck failed in function:%s line:%d value:%d",__FUNCTION__,__LINE__,rcvdMsgPtr->bssPktAggrCount);
      return(FALSE);
   }

   LOG_PRINT(LOG_INFO,"bssTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

}/* end of bssTableRangeChk */

I_U32 ptdcCfgTableRangeChk(PtdcConfigTableApi* rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function ptdcCfgTableRangeChk()");
   /* Bug Fixed - Mantis #5620 : Start */
   if ((rcvdMsgPtr->pdcCfgPeriodicCSAppTimer >= PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicCSAppTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicPSAppTimer >=PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicPSAppTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicCSStackTimer >=PDC_TIMER_START) &&(rcvdMsgPtr->pdcCfgPeriodicCSStackTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicPSStackTimer >=PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicPSStackTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicPlatformTimer >=PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicPlatformTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicCERTimer >=PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicCERTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicTraceTimer >=PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicTraceTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicAlarmTimer >=PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicAlarmTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgPeriodicCcuTimer >=PDC_TIMER_START) && (rcvdMsgPtr->pdcCfgPeriodicCcuTimer <= PDC_TIMER_END))
   if ((rcvdMsgPtr->pdcCfgFileMaxSize >=PDC_FILE_MAX_SIZE_START) && (rcvdMsgPtr->pdcCfgFileMaxSize <= PDC_FILE_MAX_SIZE_END))
   /* Bug Fixed - Mantis #5620 : End */
   {
      LOG_PRINT(LOG_INFO,"ptdcCfgTableRangeChk: Returns TRUE when all parameters are within range");
      return TRUE;
   }

   LOG_PRINT(LOG_DEBUG,"ptdcCfgTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
   return FALSE;
}

/********************************* Function  Header********************************
   Function Name :   csPwrCtrlTableRangeChk()
Parameters    :   Pointer to CsPwrCtrlTableApi
Return type   :   I_Bool
Purpose       : To check if all the RW Parameters are in range or not for CsPwrCtrl table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note    : Relevant to CS2.5
 ************************************************************************************/
I_Bool csPwrCtrlTableRangeChk(CONST CsPwrCtrlTableApi * rcvdMsgPtr)
{
   I_U8 *str = "ERR=RangeCheckFailed, Table=CsPwrCtrlTable, Field=";
   LOG_PRINT(LOG_INFO,"Entering %s", __FUNCTION__);

   /* lower range for cellid, enMsPctrl, enBsPctrl, lRxLevUlP, uRxLevUlP, 
       lRxQualUlP, uRxQualUlP, lRxLevDlP, uRxLevDlP, lRxQualDlP, uRxQualDlP
       is not required as these parameters are defined unsigned, and can't have
       values less than zero.
       */
   if (rcvdMsgPtr->cellId > 65535)
   {
      LOG_PRINT(LOG_DEBUG,"%s Cell ID Expected Value :{0 to 65535} Received Value : 0x%x",str,rcvdMsgPtr->cellId);
      return FALSE;
   } 

   if ((rcvdMsgPtr->lac < 1) || (rcvdMsgPtr->lac > 65535) || (rcvdMsgPtr->lac == 65534))
   {
      LOG_PRINT(LOG_DEBUG,"%s lac Expected Value :{1 to 65533, 65535} Received Value : 0x%x",str,rcvdMsgPtr->lac);
      return FALSE;
   }

   if (rcvdMsgPtr->enMsPctrl > 1)
   {
      LOG_PRINT(LOG_DEBUG,"%s enMsPctrl Expected Value :{0 to 1} Received Value :0x%x",str,rcvdMsgPtr->enMsPctrl);
      return FALSE;
   } 

   if (rcvdMsgPtr->enBsPctrl > 1)
   {
      LOG_PRINT(LOG_DEBUG,"%s enBsPctrl Expected Value :{0 to 1} Received Value :0x%x",str,rcvdMsgPtr->enBsPctrl);
      return FALSE;
   }

   if (rcvdMsgPtr->lRxLevUlP > 63)
   {
      LOG_PRINT(LOG_DEBUG,"%s lRxLevUlP Expected Value :{0 to 63} Received Value :0x%x",str,rcvdMsgPtr->lRxLevUlP);
      return FALSE;
   }

   if (rcvdMsgPtr->uRxLevUlP > 63)
   {
      LOG_PRINT(LOG_DEBUG,"%s uRxLevUlP Expected Value :{0 to 63} Received Value :0x%x",str,rcvdMsgPtr->uRxLevUlP);
      return FALSE;
   }

   if (rcvdMsgPtr->lRxQualUlP > 7)
   {
      LOG_PRINT(LOG_DEBUG,"%s lRxQualUlP Expected Value :{0 to 7} Received Value :0x%x",str,rcvdMsgPtr->lRxQualUlP);
      return FALSE;
   }
   if (rcvdMsgPtr->uRxQualUlP > 7)
   {
      LOG_PRINT(LOG_DEBUG,"%s uRxQualUlP Expected Value :{0 to 7} Received Value :0x%x",str,rcvdMsgPtr->uRxQualUlP);
      return FALSE;
   }

   if (rcvdMsgPtr->lRxLevDlP > 63)
   {
      LOG_PRINT(LOG_DEBUG,"%s lRxLevDlP Expected Value :{0 to 63} Received Value :0x%x",str,rcvdMsgPtr->lRxLevDlP);
      return FALSE;
   }

   if (rcvdMsgPtr->uRxLevDlP > 63)
   {
      LOG_PRINT(LOG_DEBUG,"%s uRxLevDlP Expected Value :{0 to 63} Received Value : 0x%x",str,rcvdMsgPtr->uRxLevDlP);
      return FALSE;
   }

   if (rcvdMsgPtr->lRxQualDlP > 7)
   {
      LOG_PRINT(LOG_DEBUG,"%s lRxQualDlP Expected Value :{0 to 7} Received Value :0x%x",str,rcvdMsgPtr->lRxQualDlP);
      return FALSE;
   }

   if (rcvdMsgPtr->uRxQualDlP > 7)
   {
      LOG_PRINT(LOG_DEBUG,"%s uRxQualDlP Expected Value :{0 to 7} Received Range :0x%x",str,rcvdMsgPtr->uRxQualDlP);
      return FALSE;
   }

   return TRUE;
}


/********************************* Function  Header********************************
   Function Name:       cellTableRangeChk()
Parameters:          Pointer to CellTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for Cell table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool cellTableRangeChk(CellPerTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO," Entering function cellTableRangeChk()");
   if ((rcvdMsgPtr->cellId < 0) || (rcvdMsgPtr->cellId > 65535))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for cellId [%u] in function:%s line:%d",
                rcvdMsgPtr->cellId, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->lac < 1) || (rcvdMsgPtr->lac > 65535) || (rcvdMsgPtr->lac == 65534))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed in for lac [%u] function:%s line:%d",
                rcvdMsgPtr->lac, __FUNCTION__, __LINE__);
      return(FALSE);
   } 
/*Changes PCU R2.5 Aricent -- START*/ 
   if ((rcvdMsgPtr->adminState != LOCK) && (rcvdMsgPtr->adminState != UNLOCK) && 
       (rcvdMsgPtr->adminState != SHUTTING_DOWN))
/*Changes PCU R2.5 Aricent -- END*/ 
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for adminState [%u] in function:%s line:%d",
                rcvdMsgPtr->adminState, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   //if (((rcvdMsgPtr->bcchArfcn < 1) || (rcvdMsgPtr->bcchArfcn > 124)) && Temporary Patch for Tanzania E-GSM support 02-Jan-2017
   if (((rcvdMsgPtr->bcchArfcn < 1) || (rcvdMsgPtr->bcchArfcn > 1023)) &&
         (rcvdMsgPtr->freqBandBcch == GSM900))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for bcchArfcn [%u] in function:%s line:%d",
                rcvdMsgPtr->bcchArfcn, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->bcchArfcn < 512) || (rcvdMsgPtr->bcchArfcn > 885)) &&
         (rcvdMsgPtr->freqBandBcch == GSM1800))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for freqBandBcch [%u] in function:%s line:%d",
                rcvdMsgPtr->freqBandBcch, __FUNCTION__, __LINE__);
      return(FALSE);
   } 
   if (((rcvdMsgPtr->bcchArfcn < 128) || (rcvdMsgPtr->bcchArfcn > 251)) &&
         (rcvdMsgPtr->freqBandBcch == GSM850))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for freqBandBcch [%u] in function:%s line:%d",
                rcvdMsgPtr->freqBandBcch, __FUNCTION__, __LINE__);
      return(FALSE);
   } 
   if (((rcvdMsgPtr->bcchArfcn < 512) || (rcvdMsgPtr->bcchArfcn > 810)) &&
         (rcvdMsgPtr->freqBandBcch == GSM1900))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for freqBandBcch [%u] in function:%s line:%d",
                rcvdMsgPtr->freqBandBcch, __FUNCTION__, __LINE__);
      return(FALSE);
   } 
/*Changes PCU R2.5 Aricent -- START*/ 
   if ((rcvdMsgPtr->freqBandBcch != GSM900) && (rcvdMsgPtr->freqBandBcch != GSM1800) && 
       (rcvdMsgPtr->freqBandBcch != GSM850) && (rcvdMsgPtr->freqBandBcch != GSM1900) ) 
/*Changes PCU R2.5 Aricent -- END*/ 
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for freqBandBcch [%u] in function:%s line:%d",
                rcvdMsgPtr->freqBandBcch, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->bcc < 0) || (rcvdMsgPtr->bcc > 7))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for bcc [%u] in function:%s line:%d",
                rcvdMsgPtr->bcc,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   /* CS3.0 Changes */
   /*Changes PCU R2.5 Aricent -- START*/ 
   if ( ((rcvdMsgPtr->freqBandBcch == GSM900) || (rcvdMsgPtr->freqBandBcch == GSM850)) &&
         ((rcvdMsgPtr->msTxPwrMax < OAMS_CFG_MS_TX_PWR_MIN_VALUE_FOR_GSM_900) || 
         (rcvdMsgPtr->msTxPwrMax > OAMS_CFG_MS_TX_PWR_MAX_VALUE_FOR_GSM_900)) )
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for msTxPwrMax [%u] in function:%s line:%d",
                rcvdMsgPtr->msTxPwrMax, __FUNCTION__, __LINE__);
      return(FALSE);  
   }
   if ( ((rcvdMsgPtr->freqBandBcch == GSM1800) || (rcvdMsgPtr->freqBandBcch == GSM1900)) &&
         ((rcvdMsgPtr->msTxPwrMax < OAMS_CFG_MS_TX_PWR_MIN_VALUE_FOR_GSM_1800) || 
         (rcvdMsgPtr->msTxPwrMax > OAMS_CFG_MS_TX_PWR_MAX_VALUE_FOR_GSM_1800)) )
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for msTxPwrMax [%u] in function:%s line:%d",
                rcvdMsgPtr->msTxPwrMax, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ( ((rcvdMsgPtr->freqBandBcch == GSM900) || (rcvdMsgPtr->freqBandBcch == GSM850)) &&
         ((rcvdMsgPtr->msTxPowerMaxCch < OAMS_CFG_MS_TX_POWER_MAX_CCH_MIN_VALUE_FOR_GSM_900) || 
         (rcvdMsgPtr->msTxPowerMaxCch > OAMS_CFG_MS_TX_POWER_MAX_CCH_MAX_VALUE_FOR_GSM_900)) )
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for rcvdMsgPtr->msTxPowerMaxCch [%u] in function:%s line:%d",
                rcvdMsgPtr->msTxPowerMaxCch, __FUNCTION__, __LINE__);
      return(FALSE);  
   }
   if ( ((rcvdMsgPtr->freqBandBcch == GSM1800) || (rcvdMsgPtr->freqBandBcch == GSM1900)) && 
         ((rcvdMsgPtr->msTxPowerMaxCch < OAMS_CFG_MS_TX_POWER_MAX_CCH_MIN_VALUE_FOR_GSM_1800) || 
         (rcvdMsgPtr->msTxPowerMaxCch > OAMS_CFG_MS_TX_POWER_MAX_CCH_MAX_VALUE_FOR_GSM_1800)) )
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for msTxPowerMaxCch [%u] in function:%s line:%d",
                rcvdMsgPtr->msTxPowerMaxCch, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   /*Changes PCU R2.5 Aricent -- END*/
   if ((rcvdMsgPtr->psAllowed != ALLOWED ) && (rcvdMsgPtr->psAllowed != NOT_ALLOWED))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for psAllowed [%u] in function:%s line:%d",
                rcvdMsgPtr->psAllowed, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->cellBarAccess != 0) && (rcvdMsgPtr->cellBarAccess != 1))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for cellBarAccess [%u] in function:%s line:%d",
                rcvdMsgPtr->cellBarAccess, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->bcchPwr < 0) || (rcvdMsgPtr->bcchPwr > 127 ))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck  for bcchPwr failed in function:%s line:%d",
                rcvdMsgPtr->bcchPwr, __FUNCTION__, __LINE__);
      return(FALSE);
   }

   if ((rcvdMsgPtr->bsAgBlksRes < 0) || (rcvdMsgPtr->bsAgBlksRes > 7))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for bsAgBlksRes [%u] in function:%s line:%d",
                rcvdMsgPtr->bsAgBlksRes, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->bsPaMfrms < 0) || (rcvdMsgPtr->bsPaMfrms > 7))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for bsPaMfrms [%u] in function:%s line:%d",
                rcvdMsgPtr->bsPaMfrms, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->cellReselectHysteresis < 0) || (rcvdMsgPtr->cellReselectHysteresis > 7))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for cellReselectHysteresis [%u] in function:%s line:%d",
                rcvdMsgPtr->cellReselectHysteresis, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->rxLevAccessMin < 0) || (rcvdMsgPtr->rxLevAccessMin > 63))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for rxLevAccessMin [%u] in function:%s line:%d",
                rcvdMsgPtr->rxLevAccessMin, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->powerOffset < 0) || (rcvdMsgPtr->powerOffset > 3))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for powerOffset [%u] in function:%s line:%d",
                rcvdMsgPtr->powerOffset, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->cbq > 1)
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for cbq [%u] in function:%s line:%d",
                rcvdMsgPtr->cbq, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->cellReselectOffset > 63)
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for cellReselectOffset [%u] in function:%s line:%d",
                rcvdMsgPtr->cellReselectOffset, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->tempOffset > 7)
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for tempOffset [%u] in function:%s line:%d",
                rcvdMsgPtr->tempOffset, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->penalityTime > 31)
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for penalityTime [%u] in function:%s line:%d",
                rcvdMsgPtr->penalityTime, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->fnOffset > 25)
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for fnOffset [%u] in function:%s line:%d",
                rcvdMsgPtr->fnOffset, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
/* R2.4 Changes : Starts */ 
   if ((rcvdMsgPtr->amrSupport != AMR_SUPPORTED) && (rcvdMsgPtr->amrSupport != AMR_NOT_SUPPORTED))
   {
      LOG_PRINT(LOG_DEBUG," cellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   /*Changes for R2.8 */
   if ((rcvdMsgPtr->amrSupport == AMR_SUPPORTED) && ((rcvdMsgPtr->frToHrSwitchPerct < 0) || (rcvdMsgPtr->frToHrSwitchPerct > 100)))
   {
      LOG_PRINT(LOG_DEBUG," Incorrect value of initialAmrCodecRate and frToHrSwitchPerct in function:%s line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_AMR_CODECRATE_AND_FRTOHRPERCT_INCORRECT);
      return(FALSE);
   }
   /* commented fro R2.8 
   if ((rcvdMsgPtr->amrSupport == AMR_SUPPORTED) && (rcvdMsgPtr->initialAmrCodecRate != AMR_590))
   {
      LOG_PRINT(LOG_DEBUG," Incorrect value of initialAmrCodecRate in function:%s line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_INCORRECT_AMR_CODEC_RATE);
      return(FALSE);
   }
   
   if ((rcvdMsgPtr->amrSupport == AMR_SUPPORTED) && (rcvdMsgPtr->initialAmrCodecRate == AMR_590) &&
       ((rcvdMsgPtr->frToHrSwitchPerct < 0) || (rcvdMsgPtr->frToHrSwitchPerct > 100)) )
   {
      LOG_PRINT(LOG_DEBUG," Incorrect value of frToHrSwitchPerct in function:%s line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_INCORRECT_FR_TO_HR_PERCT);
      return(FALSE);
   }
   */
   if ((rcvdMsgPtr->amrSupport == AMR_NOT_SUPPORTED) && ((rcvdMsgPtr->initialAmrCodecRate != INVALID) && (rcvdMsgPtr->frToHrSwitchPerct != INVALID)) )
   {
      LOG_PRINT(LOG_DEBUG," cellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_CODECRATE_AND_FRTOHRPERCT_NOT_INVALID);
      return(FALSE);
   }
   if ((rcvdMsgPtr->amrSupport == AMR_NOT_SUPPORTED) && (rcvdMsgPtr->initialAmrCodecRate != INVALID))
   {
      LOG_PRINT(LOG_DEBUG," initialAmrCodecRate not Invalid in function:%s line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_AMR_CODEC_RATE_NOT_INVALID);
      return(FALSE);
   }
   if ((rcvdMsgPtr->amrSupport == AMR_NOT_SUPPORTED) && (rcvdMsgPtr->frToHrSwitchPerct != INVALID))
   {
      LOG_PRINT(LOG_DEBUG," frToHrSwitchPerct not Invalid in function:%s line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_FR_TO_HR_PERCT_NOT_INVALID);
      return(FALSE);
   }

/* R2.4 Changes : Ends */ 
/* Changes For MaxAllowedTA : Start */  
   if ((rcvdMsgPtr->maxAllowedTA < 0) || (rcvdMsgPtr->maxAllowedTA > 63))
   {
      LOG_PRINT(LOG_DEBUG," cellTable Rangecheck failed for maxAllowedTA [%u] function:%s line:%d",rcvdMsgPtr->maxAllowedTA,__FUNCTION__,__LINE__);
      return(FALSE);
   }
/* Changes For MaxAllowedTA : End */  

   if ((rcvdMsgPtr->maxNumFreeHr < OAMS_CFG_MAX_NUM_FREE_HR_MIN_VALUE) || (rcvdMsgPtr->maxNumFreeHr > OAMS_CFG_MAX_NUM_FREE_HR_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for maxNumFreeHr [%u] in function:%s line:%d",
      rcvdMsgPtr->maxNumFreeHr, __FUNCTION__, __LINE__);
      return(FALSE);
   }

   /* EGPRS Changes Starts */
   if ((rcvdMsgPtr->egprsAllowed != ALLOWED ) && (rcvdMsgPtr->egprsAllowed != NOT_ALLOWED))
   {
     LOG_PRINT(LOG_MAJOR,"cellTable Rangecheck failed for egprsAllowed [%u] in function:%s line:%d",
         rcvdMsgPtr->egprsAllowed, __FUNCTION__, __LINE__);
     return(FALSE);
   }

   /* EGPRS Changes Ends */

   if ((rcvdMsgPtr->localSwitchingSupport != ENABLED) && (rcvdMsgPtr->localSwitchingSupport !=DISABLED)) 
   {
      LOG_PRINT(LOG_DEBUG,"cellTable Rangecheck failed in function:%s line:%d value:%d",__FUNCTION__,__LINE__,rcvdMsgPtr->localSwitchingSupport);
      return(FALSE);
   }
/*ICM Merge Gaurav Sinha 16 Dec 2016*/
   if ((rcvdMsgPtr->icmSupport != ENABLED) && (rcvdMsgPtr->icmSupport !=DISABLED)) 
   {
      LOG_PRINT(LOG_DEBUG,"cellTable Rangecheck failed in function:%s line:%d value:%d",__FUNCTION__,__LINE__,rcvdMsgPtr->icmSupport);
      return(FALSE);
   }
/*ICM Merge Gaurav Sinha 16 Dec 2016*/
   
   LOG_PRINT(LOG_INFO,"cellTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

}/* end of cellTableRangeChk */



/********************************* Function  Header********************************
   Function Name:       psCellTableRangeChk()
Parameters:          Pointer to PsCellTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for psCellTable table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
 /*Changes PCU R2.5 Aricent -- START*/
I_Bool psCellTableRangeChk(PsCellTableApi * rcvdMsgPtr)
{
   
   BssPsPreConfigTableIndices   bssPsPreConfigTableIndicesBuff; 
   bssPsPreConfigTableIndicesBuff.bssPsPreConfigIndex = 0;
   
   LOG_PRINT(LOG_INFO," Entering function psCellTableRangeChk()");
   
   if (rcvdMsgPtr->raColour > OAMS_CFG_RA_COLOR_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for raColor [%u] in function:%s line:%d",
                rcvdMsgPtr->raColour, __FUNCTION__, __LINE__);
      return(FALSE);
   }

   if (rcvdMsgPtr->bvciId < OAMS_CFG_BVC_ID_MIN_VALUE || rcvdMsgPtr->bvciId > OAMS_CFG_BVC_ID_MAX_VALUE) 
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for bvcId [%u] in function:%s line:%d",
                rcvdMsgPtr->bvciId, __FUNCTION__, __LINE__);
      return(FALSE);
   }

   if(rcvdMsgPtr->priorityAccessThr > OAMS_CFG_PRIORITY_ACC_THR_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for priorityAccessThr [%u] in function:%s line:%d",
                rcvdMsgPtr->priorityAccessThr, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->minNumPdchCell > OAMS_CFG_MIN_NUM_PDCH_CELL_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for minNumPdchCell [%u] in function:%s line:%d",
                rcvdMsgPtr->minNumPdchCell, __FUNCTION__, __LINE__);
      return(FALSE);

   }
   if ((rcvdMsgPtr->maxNumTbfPdch < OAMS_CFG_MAX_NUM_TBF_CELL_MIN_VALUE) || 
       (rcvdMsgPtr->maxNumTbfPdch > OAMS_CFG_MAX_NUM_TBF_CELL_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for maxNumTbfPdch [%u] in function:%s line:%d",
                rcvdMsgPtr->maxNumTbfPdch, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   
   if (rcvdMsgPtr->ssb > OAMS_CFG_SSB_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for ssb [%u] in function:%s line:%d",
                rcvdMsgPtr->ssb, __FUNCTION__, __LINE__);
      return(FALSE);

   }
   
   if ((rcvdMsgPtr->gprsDlaEnabled != TRUE) && (rcvdMsgPtr->gprsDlaEnabled != FALSE))
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->gprsCsMax < OAMS_CFG_GPRS_CS_MAX_MIN_VALUE) || 
       (rcvdMsgPtr->gprsCsMax > OAMS_CFG_GPRS_CS_MAX_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for gprsCsMax [%u] in function:%s line:%d",
                rcvdMsgPtr->gprsCsMax, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->gprsCsInitial < OAMS_CFG_GPRS_CS_INITIAL_MIN_VALUE) || 
       (rcvdMsgPtr->gprsCsInitial > OAMS_CFG_GPRS_CS_INITIAL_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for gprsCsInitial [%u] in function:%s line:%d",
                rcvdMsgPtr->gprsCsInitial, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   /* Fix for Mantis 15107 --Start*/
   if (rcvdMsgPtr->percFreeCsChannelsHyst > 100)
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for percFreeCsChannelsHyst [%u] in function:%s line:%d",
                rcvdMsgPtr->percFreeCsChannelsHyst, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->percFreeCsChannels > 100)
   {
      LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for percFreeCsChannels [%u] in function:%s line:%d",
                rcvdMsgPtr->percFreeCsChannels, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   /* Fix for Mantis 15107 --End*/
   /* EGPRS Changes Starts */

   if ((rcvdMsgPtr->egprsDlaMcsMax < OAMS_CFG_EGPRS_MCS_MAX_MIN_VALUE) ||
       (rcvdMsgPtr->egprsDlaMcsMax > OAMS_CFG_EGPRS_MCS_MAX_MAX_VALUE))

   {
     LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for egprsDlaMcsMax [%u] in function:%s line:%d",  rcvdMsgPtr->egprsDlaMcsMax, __FUNCTION__, __LINE__);       return(FALSE);
   }


   if ((rcvdMsgPtr->egprsDla8PskMcsInitial < OAMS_CFG_EGPRS_8PSK_MCS_INITIAL_MIN_VALUE) ||
       (rcvdMsgPtr->egprsDla8PskMcsInitial > OAMS_CFG_EGPRS_8PSK_MCS_INITIAL_MAX_VALUE))
   {
     LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for egprsDla8PskMcsInitial [%u] in function:%s line:%d",                 rcvdMsgPtr->egprsDla8PskMcsInitial, __FUNCTION__, __LINE__);
     return(FALSE);
   }

   if ((rcvdMsgPtr->egprsDlaGmskMcsInitial < OAMS_CFG_EGPRS_GMSK_MCS_INITIAL_MIN_VALUE) ||
       (rcvdMsgPtr->egprsDlaGmskMcsInitial > OAMS_CFG_EGPRS_GMSK_MCS_INITIAL_MAX_VALUE))
   {
     LOG_PRINT(LOG_MAJOR,"psCellTable Rangecheck failed for egprsDlaGmskMcsInitial [%u] in function:%s line:%d",                 rcvdMsgPtr->egprsDlaGmskMcsInitial, __FUNCTION__, __LINE__);
     return(FALSE);
   }
   /* EGPRS Changes Ends */


   
   LOG_PRINT(LOG_INFO,"psCellTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */
} /* end of psCellTableRangeChk */
/*Changes PCU R2.5 Aricent -- END*/

/********************************* Function  Header********************************
   Function Name:       csExternalCellTableRangeChk()
Parameters:          Pointer to CsExternalCellTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for csExternalCell table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool csExternalCellTableRangeChk(CsExternalCellTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO," Entering function csExternalCellTableRangeChk()");

   if (((rcvdMsgPtr->csExtCellId < 0) || (rcvdMsgPtr->csExtCellId > 65535)) && 
       (rcvdMsgPtr->radioAccessType == GSM))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   /* Changes For WCDMA-GSM HO Feature */
   if (((rcvdMsgPtr->csExtCellId < 0) || (rcvdMsgPtr->csExtCellId > 4095)) && 
       (rcvdMsgPtr->radioAccessType == WCDMA_FDD))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }

   if ((rcvdMsgPtr->lac < 1) || (rcvdMsgPtr->lac > 65535) || (rcvdMsgPtr->lac == 65534))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->mcc > 0x999)
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (( rcvdMsgPtr->mnc & 0xf) == 0xf)
   {
      /* Two digit MNC */
      if (  rcvdMsgPtr->mnc > 0x99F )
      {
         LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
         return FALSE;
      }
   }
   else /* Three digit MNC */
      if (rcvdMsgPtr->mnc > 0x999)
      {
         LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
         return(FALSE);
      }
   if ((rcvdMsgPtr->bcc < 0) || (rcvdMsgPtr->bcc > 7))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->ncc < 0) || (rcvdMsgPtr->ncc > 7))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   LOG_PRINT(DEBUG,"Value of freqBandBcch:%d, bcchArfcn :%d",rcvdMsgPtr->freqBandBcch,rcvdMsgPtr->bcchArfcn);
    
/* Changes For WCDMA-GSM HO Feature : Start */
   if ((((rcvdMsgPtr->freqBandBcch != GSM900) && (rcvdMsgPtr->freqBandBcch != GSM1800) &&
       (rcvdMsgPtr->freqBandBcch != GSM850) && (rcvdMsgPtr->freqBandBcch != GSM1900)) &&
       (rcvdMsgPtr->radioAccessType == GSM)) || 
       (((rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_1) && (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_2) &&
       (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_3) && (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_4) &&
       (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_5) && (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_6) &&
       (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_7) && (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_8) &&
       (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_9) && (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_10) &&
       (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_11) && (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_12) &&
       (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_13) && (rcvdMsgPtr->freqBandBcch != WCDMA_FDD_BAND_14)) &&
       (rcvdMsgPtr->radioAccessType == WCDMA_FDD)))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   //if (((rcvdMsgPtr->bcchArfcn < 1) || (rcvdMsgPtr->bcchArfcn > 124)) && Temporary Patch for Tanzania E-GSM support 02-Jan-2017 
   if (((rcvdMsgPtr->bcchArfcn < 1) || (rcvdMsgPtr->bcchArfcn > 1023)) &&
         (rcvdMsgPtr->freqBandBcch == GSM900))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->bcchArfcn < 512) || (rcvdMsgPtr->bcchArfcn > 885)) &&
         (rcvdMsgPtr->freqBandBcch == GSM1800))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->bcchArfcn < 128) || (rcvdMsgPtr->bcchArfcn > 251)) &&
         (rcvdMsgPtr->freqBandBcch == GSM850))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if (((rcvdMsgPtr->bcchArfcn < 512) || (rcvdMsgPtr->bcchArfcn > 810)) &&
         (rcvdMsgPtr->freqBandBcch == GSM1900))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->bcchArfcn < 10562) || (rcvdMsgPtr->bcchArfcn > 10838)) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_1))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 9662) || (rcvdMsgPtr->bcchArfcn > 9938)) &&
        ((rcvdMsgPtr->bcchArfcn != 412) && (rcvdMsgPtr->bcchArfcn != 437) &&
        (rcvdMsgPtr->bcchArfcn != 462) && (rcvdMsgPtr->bcchArfcn != 487) &&
        (rcvdMsgPtr->bcchArfcn != 512) && (rcvdMsgPtr->bcchArfcn != 537) &&
        (rcvdMsgPtr->bcchArfcn != 562) && (rcvdMsgPtr->bcchArfcn != 587) &&
        (rcvdMsgPtr->bcchArfcn != 612) && (rcvdMsgPtr->bcchArfcn != 637) &&
        (rcvdMsgPtr->bcchArfcn != 662) && (rcvdMsgPtr->bcchArfcn != 687))
       ) &&
       (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_2))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if (((rcvdMsgPtr->bcchArfcn < 1162) || (rcvdMsgPtr->bcchArfcn > 1513)) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_3))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 1537) || (rcvdMsgPtr->bcchArfcn > 1738)) &&
        ((rcvdMsgPtr->bcchArfcn != 1887) && (rcvdMsgPtr->bcchArfcn != 1912) &&
        (rcvdMsgPtr->bcchArfcn != 1937) &&
        (rcvdMsgPtr->bcchArfcn != 1962) && (rcvdMsgPtr->bcchArfcn != 1987) &&
        (rcvdMsgPtr->bcchArfcn != 2012) && (rcvdMsgPtr->bcchArfcn != 2037) &&
        (rcvdMsgPtr->bcchArfcn != 2062) && (rcvdMsgPtr->bcchArfcn != 2087))
       ) &&
       (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_4))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 4357) || (rcvdMsgPtr->bcchArfcn > 4458)) &&
        (rcvdMsgPtr->bcchArfcn != 1007) &&
        ((rcvdMsgPtr->bcchArfcn != 1012) && (rcvdMsgPtr->bcchArfcn != 1032) &&
        (rcvdMsgPtr->bcchArfcn != 1037) && (rcvdMsgPtr->bcchArfcn != 1062) &&
        (rcvdMsgPtr->bcchArfcn != 1087)) 
       ) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_5))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 4387) || (rcvdMsgPtr->bcchArfcn > 4413)) &&
        ((rcvdMsgPtr->bcchArfcn != 1062) && (rcvdMsgPtr->bcchArfcn != 1037)) 
       ) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_6))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 2237) || (rcvdMsgPtr->bcchArfcn > 2563)) &&
        ((rcvdMsgPtr->bcchArfcn != 2912) && (rcvdMsgPtr->bcchArfcn != 2587) &&
        (rcvdMsgPtr->bcchArfcn != 2612) && (rcvdMsgPtr->bcchArfcn != 2637) &&
        (rcvdMsgPtr->bcchArfcn != 2662) && (rcvdMsgPtr->bcchArfcn != 2687) &&
        (rcvdMsgPtr->bcchArfcn != 2812) && (rcvdMsgPtr->bcchArfcn != 2837) &&
        (rcvdMsgPtr->bcchArfcn != 2862) && (rcvdMsgPtr->bcchArfcn != 2887) &&
        (rcvdMsgPtr->bcchArfcn != 2712) && (rcvdMsgPtr->bcchArfcn != 2737) &&
        (rcvdMsgPtr->bcchArfcn != 2762) && (rcvdMsgPtr->bcchArfcn != 2787))
       ) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_7))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if (((rcvdMsgPtr->bcchArfcn < 2937) || (rcvdMsgPtr->bcchArfcn > 3088)) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_8))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if (((rcvdMsgPtr->bcchArfcn < 9237) || (rcvdMsgPtr->bcchArfcn > 9387)) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_9))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 3112) || (rcvdMsgPtr->bcchArfcn > 3388)) &&
        ((rcvdMsgPtr->bcchArfcn != 3687) && (rcvdMsgPtr->bcchArfcn != 3662) &&
        (rcvdMsgPtr->bcchArfcn != 3412) && (rcvdMsgPtr->bcchArfcn != 3437) &&
        (rcvdMsgPtr->bcchArfcn != 3462) && (rcvdMsgPtr->bcchArfcn != 3487) &&
        (rcvdMsgPtr->bcchArfcn != 3512) && (rcvdMsgPtr->bcchArfcn != 3537) &&
        (rcvdMsgPtr->bcchArfcn != 3562) && (rcvdMsgPtr->bcchArfcn != 3587) &&
        (rcvdMsgPtr->bcchArfcn != 3612) && (rcvdMsgPtr->bcchArfcn != 3637))          
       ) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_10))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        (rcvdMsgPtr->bcchArfcn < 3712) || (rcvdMsgPtr->bcchArfcn > 3787)) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_11))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 3837) || (rcvdMsgPtr->bcchArfcn > 3903)) &&
        ((rcvdMsgPtr->bcchArfcn != 3927) && (rcvdMsgPtr->bcchArfcn != 3932) &&
        (rcvdMsgPtr->bcchArfcn != 3957) && (rcvdMsgPtr->bcchArfcn != 3962) &&
        (rcvdMsgPtr->bcchArfcn != 3987) && (rcvdMsgPtr->bcchArfcn != 3992)) 
       ) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_12))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 4017) || (rcvdMsgPtr->bcchArfcn > 4043)) &&
        ((rcvdMsgPtr->bcchArfcn != 4067) && (rcvdMsgPtr->bcchArfcn != 4092)) 
       ) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_13))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if ((
        ((rcvdMsgPtr->bcchArfcn < 4117) || (rcvdMsgPtr->bcchArfcn > 4143))&&
        ((rcvdMsgPtr->bcchArfcn != 4167) && (rcvdMsgPtr->bcchArfcn != 4192)) 
       ) &&
         (rcvdMsgPtr->freqBandBcch == WCDMA_FDD_BAND_14))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }

   if ((rcvdMsgPtr->freqBandBcch == GSM900) &&
       ((rcvdMsgPtr->msTxPwrMax < 5) || 
        (rcvdMsgPtr->msTxPwrMax > 19)
      ))
   {
      LOG_PRINT(LOG_DEBUG,"Range Check Failed for attribute msTxPwrMax");
      return(FALSE);  
   }
   if ((rcvdMsgPtr->freqBandBcch == GSM1800) &&
       ((rcvdMsgPtr->msTxPwrMax < 0) || (rcvdMsgPtr->msTxPwrMax > 15)
      ))
   {
      LOG_PRINT(LOG_DEBUG,"Range Check Failed for Attribute msTxPwrMax");
      return(FALSE);
   }
   if((rcvdMsgPtr->radioAccessType == WCDMA_FDD) && (rcvdMsgPtr->scrambling_Code > 511))
   {
      LOG_PRINT(LOG_DEBUG,"Range Check Failed for Attribute scrambling_Code");
      return(FALSE);
   }
   /* Fixed Mantis #4633 : End */
   LOG_PRINT(DEBUG,"Value of Radio Access Type:%u, Scrambling Code :%d, diversity:%d",rcvdMsgPtr->radioAccessType,rcvdMsgPtr->scrambling_Code,rcvdMsgPtr->diversity);
   if ((rcvdMsgPtr->radioAccessType != GSM) && (rcvdMsgPtr->radioAccessType != WCDMA_FDD))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->scrambling_Code < 0) || (rcvdMsgPtr->scrambling_Code > 511)) && (rcvdMsgPtr->scrambling_Code != 0xffff))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->diversity< 0) || (rcvdMsgPtr->diversity > 1)) && (rcvdMsgPtr->diversity != 0xff))
   {
      LOG_PRINT(LOG_DEBUG," csExternalCellTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   /* Changes For WCDMA-GSM HO Feature : End */

   LOG_PRINT(LOG_INFO," csExternalCellTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of csExternalCellTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       laTableRangeChk()
Parameters:          Pointer to LaTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for La table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool laTableRangeChk(LaTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function laTableRangeChk()");
   if ((rcvdMsgPtr->lac < 1) || (rcvdMsgPtr->lac > 65535) || (rcvdMsgPtr->lac == 65534))
   {
      LOG_PRINT(LOG_MAJOR,"laTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }

   LOG_PRINT(LOG_INFO,"laTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of laTableRangeChk */



/********************************* Function  Header********************************
   Function Name:       raTableRangeChk()
Parameters:          Pointer to RaTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for Ra table
Retuens TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool raTableRangeChk(RaTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function raTableRangeChk()");
   if ((rcvdMsgPtr->rac < 0) || (rcvdMsgPtr->rac > 255))
   {
      LOG_PRINT(LOG_MAJOR,"raTable Rangecheck failed for rac [%u] in function:%s line:%d",rcvdMsgPtr->rac,__FUNCTION__,__LINE__);
      return(FALSE);
   }

   LOG_PRINT(LOG_INFO,"raTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of raTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       chnGrpTableRangeChk()
Parameters:          Pointer to chnGrpTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for chnGrp table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool chnGrpTableRangeChk(ChnGrpTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function chnGrpTableRangeChk()");
   I_S32 i = 0;
   I_U16 *tArfcnPtr = &(rcvdMsgPtr->arfcn1);
   I_U32 sumOfChan = 0;

   if ((rcvdMsgPtr->chnGrpId < 0) || (rcvdMsgPtr->chnGrpId > 65535))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for chnGrpId [%u] in function:%s line:%d",
                rcvdMsgPtr->chnGrpId, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->lac < 1) || (rcvdMsgPtr->lac > 65535) || (rcvdMsgPtr->lac == 65534))
   {
      LOG_PRINT(LOG_DEBUG," chnGrpTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->cellId < 0) || (rcvdMsgPtr->cellId > 65535))
   {
      LOG_PRINT(LOG_DEBUG," chnGrpTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->bcchCcchSdcch4 != 0) && (rcvdMsgPtr->bcchCcchSdcch4 != 1))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for bcchCcchSdcch4 [%u] in function:%s line:%d",
                rcvdMsgPtr->bcchCcchSdcch4, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->bcchCcch < 0) || (rcvdMsgPtr->bcchCcch > 1)) /* Mantis 1705 - CCB #22 - TRX does not support this feature. So send NACK for set/modify channel grp table command*/
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for bcchCcch [%u] in function:%s line:%d",
                rcvdMsgPtr->bcchCcch, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->sdcch8 < 0) || (rcvdMsgPtr->sdcch8 > 2))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for sdcch8 [%u] in function:%s line:%d",
                rcvdMsgPtr->sdcch8, __FUNCTION__, __LINE__);
      return(FALSE);
   }
/*Changes PCU R2.5 Aricent -- START*/
   if ( (rcvdMsgPtr->dualTraffic < OAMS_CFG_DUAL_TRAFFIC_MIN_VALUE) || 
        (rcvdMsgPtr->dualTraffic > OAMS_CFG_DUAL_TRAFFIC_MAX_VALUE) )
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for dualTraffic [%u] in function:%s line:%d",
                rcvdMsgPtr->dualTraffic, __FUNCTION__, __LINE__);
      return(FALSE);
   }
/*Changes PCU R2.5 Aricent -- END*/
   if ((rcvdMsgPtr->hsn < 0) || (rcvdMsgPtr->hsn > 63))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for hsn [%u] in function:%s line:%d",
                rcvdMsgPtr->hsn, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->maxTxPwr < 0) || (rcvdMsgPtr->maxTxPwr > 127))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for maxTxPwr [%u] in function:%s line:%d",
                rcvdMsgPtr->maxTxPwr, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->tsc < 0) || (rcvdMsgPtr->tsc > 7))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed  for tsc [%u] in function:%s line:%d",
                rcvdMsgPtr->tsc, __FUNCTION__, __LINE__);
      return(FALSE);
   }
/*Changes PCU R2.5 Aricent -- START*/
   if ((rcvdMsgPtr->band != GSM900) && (rcvdMsgPtr->band != GSM1800)  && (rcvdMsgPtr->band != GSM850)  && (rcvdMsgPtr->band != GSM1900))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for band [%u] in function:%s line:%d",
                rcvdMsgPtr->band, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->validArfcns < OAMS_CFG_VALID_ARFCN_MIN_VALUE) || (rcvdMsgPtr->validArfcns > OAMS_CFG_VALID_ARFCN_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for validArfcns [%u] in function:%s line:%d",rcvdMsgPtr->validArfcns, __FUNCTION__, __LINE__);
      return(FALSE);
   }
/*Changes PCU R2.5 Aricent -- END*/
   /* R2.4 Changes Start */
   if ((rcvdMsgPtr->cbch != 0) && (rcvdMsgPtr->cbch != 1))
   {
      LOG_PRINT(LOG_DEBUG," chnGrpTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   /* R2.4 Changes end */

   /* To check validity of Valid Arfcn Values */
   for (i = 1; i <= rcvdMsgPtr->validArfcns; i++)
   {          
      //if (((*tArfcnPtr < 1) || (*tArfcnPtr > 124)) && Temporary Patch for Tanzania E-GSM support 02-Jan-2017
      if (((*tArfcnPtr < 1) || (*tArfcnPtr > 1023)) &&
            (rcvdMsgPtr->band == GSM900))
      {
         LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for arfcn[%d]= %u in function:%s line:%d",
                   i, *tArfcnPtr, __FUNCTION__, __LINE__);
         return(FALSE);
      }
      if (((*tArfcnPtr < 512) || (*tArfcnPtr > 885)) &&
            (rcvdMsgPtr->band == GSM1800))
      {
         LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for arfcn[%d] = %u in function:%s line:%d",
                   i, *tArfcnPtr, __FUNCTION__, __LINE__);
         return(FALSE);
      }
      if (((*tArfcnPtr < 128) || (*tArfcnPtr > 251)) &&
            (rcvdMsgPtr->band == GSM850))
      {
         LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for arfcn[%d] = %u in function:%s line:%d",
                   i, *tArfcnPtr, __FUNCTION__, __LINE__);
         return(FALSE);
      } 
      #if 0
      if (((*tArfcnPtr < 512) || (*tArfcnPtr > 810)) &&
            (rcvdMsgPtr->band == GSM1900))
      {
         LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for arfcn[%d] = %u in function:%s line:%d",
                   i, *tArfcnPtr, __FUNCTION__, __LINE__);
         return(FALSE);
      } 
      #endif
/*Changes PCU R2.5 Aricent -- START*/
      if (((*tArfcnPtr < OAMS_CFG_ARFCN_MIN_VALUE_FOR_GSM_1900) || (*tArfcnPtr > OAMS_CFG_ARFCN_MAX_VALUE_FOR_GSM_1900)) &&
            (rcvdMsgPtr->band == GSM1900))
      {
         LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for arfcn [%u] in function:%s line:%d",
                   *tArfcnPtr, __FUNCTION__, __LINE__);
         return(FALSE);
      }
      if (((*tArfcnPtr < OAMS_CFG_ARFCN_MIN_VALUE_FOR_GSM_850) || (*tArfcnPtr > OAMS_CFG_ARFCN_MAX_VALUE_FOR_GSM_850)) &&
            (rcvdMsgPtr->band == GSM850))
      {
         LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for arfcn [%u] in function:%s line:%d",
                   *tArfcnPtr, __FUNCTION__, __LINE__);
         return(FALSE);
      }
/*Changes PCU R2.5 Aricent -- END*/

      tArfcnPtr++; /* Increment Ptr to access next valid arfcn */

   }/* end of for loop */       
   /* Added For Mantis 17658 : Start */ 
   if ((rcvdMsgPtr->maio < 0) || (rcvdMsgPtr->maio > 16))
   {
      LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for maio [%u] in function:%s line:%d",
                rcvdMsgPtr->maio, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->validArfcns-1) < rcvdMsgPtr->maio)
   {
     LOG_PRINT(LOG_MAJOR,"chnGrpTable Rangecheck failed for maio [%u] is greaterthan to validArfcn [%u] in function:%s line:%d",
                rcvdMsgPtr->maio, rcvdMsgPtr->validArfcns, __FUNCTION__, __LINE__);
      return(FALSE);
   }  
   /* Added For Mantis 17658 : End */ 

   LOG_PRINT(LOG_INFO,"chnGrpTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of chnGrpTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       csNeighCellsTableRangeChk()
Parameters:          Pointer to CsNeighCellsTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for csNeighCells table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool csNeighCellsTableRangeChk(CsNeighCellsTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO," Entering function csNeighCellsTableRangeChk()");
   if ((rcvdMsgPtr->cellId < 0) || (rcvdMsgPtr->cellId > 65535))
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->lac < 1) || (rcvdMsgPtr->lac > 65535) || (rcvdMsgPtr->lac == 65534))
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->cellType != INTERNAL) && (rcvdMsgPtr->cellType != EXTERNAL))
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->neighborCellId < 0) || (rcvdMsgPtr->neighborCellId > 65535))
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->neighborLac < 0) || (rcvdMsgPtr->neighborLac > 65535))
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->neighborMcc > 0x999)
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (( rcvdMsgPtr->neighborMnc & 0xf) == 0xf)
   {
      /* Two digit MNC */
      if (  rcvdMsgPtr->neighborMnc > 0x99F )
      {
         LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
         return FALSE;
      }
   }
   else /* Three digit MNC */
      if (rcvdMsgPtr->neighborMnc > 0x999)
      {
         LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
         return(FALSE);
      }
   if ((rcvdMsgPtr->relationType != ACTIVE_IDLE))
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }   
   /* On The Fly Changes : Start */
   if (rcvdMsgPtr->rxLevMinN > 63)
   {
      LOG_PRINT(LOG_DEBUG,"csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   /* On The Fly Changes : End */
/* Changes For WCDMA-GSM HO Feature : Start */
   if ((rcvdMsgPtr->radioAccessType != GSM) && (rcvdMsgPtr->radioAccessType != WCDMA_FDD))
   {
      LOG_PRINT(LOG_DEBUG," csNeighCellsTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
/* Changes For WCDMA-GSM HO Feature : End */

   LOG_PRINT(LOG_INFO," csNeighCellsTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of csNeighCellsTableRangeChk */

/********************************* Function  Header********************************
   Function Name:       arfcnListTableRangeChk()
Parameters:          Pointer to ArfcnListTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for ArfcnList table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool arfcnListTableRangeChk(ArfcnListTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO," Entering function arfcnListTableRangeChk()");
   /* CS3.0 Changes */
   if ((rcvdMsgPtr->band != GSM850) && (rcvdMsgPtr->band != GSM900) &&
       (rcvdMsgPtr->band != GSM1800) && (rcvdMsgPtr->band != GSM1900))
   {
      LOG_PRINT(LOG_DEBUG," arfcnListTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   //if (((rcvdMsgPtr->arfcn < 1) || (rcvdMsgPtr->arfcn > 124)) && Temporary Patch for Tanzania E-GSM support 02-Jan-2017 
   if (((rcvdMsgPtr->arfcn < 1) || (rcvdMsgPtr->arfcn > 1023)) &&
         (rcvdMsgPtr->band == GSM900))
   {
      LOG_PRINT(LOG_DEBUG," arfcnListTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->arfcn < 512) || (rcvdMsgPtr->arfcn > 885)) &&
         (rcvdMsgPtr->band == GSM1800))
   {
      LOG_PRINT(LOG_DEBUG," arfcnListTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (((rcvdMsgPtr->arfcn < 128) || (rcvdMsgPtr->arfcn > 251)) &&
         (rcvdMsgPtr->band == GSM850))
   {
      LOG_PRINT(LOG_DEBUG," arfcnListTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 
   if (((rcvdMsgPtr->arfcn < 512) || (rcvdMsgPtr->arfcn > 810)) &&
         (rcvdMsgPtr->band == GSM1900))
   {
      LOG_PRINT(LOG_DEBUG," arfcnListTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   } 

   LOG_PRINT(LOG_INFO," arfcnListTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of arfcnListTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       gbInterfaceTableRangeChk()
Parameters:          Pointer to GbInterfaceTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for GbInterface table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool gbInterfaceTableRangeChk(GbInterfaceTableApi* rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function gbInterfaceTableRangeChk()");
   if ((rcvdMsgPtr->transportType != FR) &&
         (rcvdMsgPtr->transportType != IP_STATIC) &&
         (rcvdMsgPtr->transportType != IP_DYNAMIC))      
   {
      LOG_PRINT(LOG_MAJOR,"gbInterfaceTable Rangecheck failed for transportType [%u] in function:%s line:%d",
                rcvdMsgPtr->transportType, __FUNCTION__, __LINE__);
      return(FALSE);
   }
/*Changes PCU R2.5 Aricent -- START*/
   if ((rcvdMsgPtr->tFcC < OAMS_CFG_T_FC_C_MIN_VALUE) || 
       (rcvdMsgPtr->tFcC > OAMS_CFG_T_FC_C_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"gbInterfaceTable Rangecheck failed for tFcC [%u] in function:%s line:%d",
                rcvdMsgPtr->tFcC, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->tFcTh < OAMS_CFG_T_FC_TH_MIN_VALUE) || 
       (rcvdMsgPtr->tFcTh > OAMS_CFG_T_FC_TH_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"gbInterfaceTable Rangecheck failed for tFcTh [%u]  in function:%s line:%d", rcvdMsgPtr->tFcTh, __FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->tFcSup < OAMS_CFG_T_FC_SUP_MIN_VALUE) || 
       (rcvdMsgPtr->tFcSup > OAMS_CFG_T_FC_SUP_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"gbInterfaceTable Rangecheck failed for tFcSup [%u] in function:%s line:%d",
                rcvdMsgPtr->tFcSup, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->nMaxFcRep < OAMS_CFG_N_MAX_FC_REP_MIN_VALUE) || 
       (rcvdMsgPtr->nMaxFcRep > OAMS_CFG_N_MAX_FC_REP_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"gbInterfaceTable Rangecheck failed for nMaxFcRep [%u] in function:%s line:%d",
                rcvdMsgPtr->nMaxFcRep, __FUNCTION__, __LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->tWaitConfig < OAMS_CFG_T_WAIT_CONFIG_MIN_VALUE) || 
       (rcvdMsgPtr->tWaitConfig > OAMS_CFG_T_WAIT_CONFIG_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"gbInterfaceTable Rangecheck failed for tWaitConfig [%u] in function:%s line:%d",
                rcvdMsgPtr->tWaitConfig, __FUNCTION__, __LINE__);
      return(FALSE);
   }
/*Changes PCU R2.5 Aricent -- END*/
   LOG_PRINT(LOG_INFO,"gbInterfaceTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of gbInterfaceTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       nsvcTableRangeChk()
Parameters:          Pointer to NsvcTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for NSVC table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool nsvcTableRangeChk(NsvcTableApi* rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function nsvcTableRangeChk()");
/*Change PCU R2.5 Aricent -- START*/
   if ((rcvdMsgPtr->dlci < OAMS_CFG_DLCI_MIN_VALUE) || 
       (rcvdMsgPtr->dlci > OAMS_CFG_DLCI_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"nsvcTable Rangecheck failed for dlci [%u] in function:%s line:%d",rcvdMsgPtr->dlci,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->adminState != LOCKED) && (rcvdMsgPtr->adminState !=  UNLOCKED))
   {
      LOG_PRINT(LOG_MAJOR,"nsvcTable Rangecheck failed for adminState [%u] in function:%s line:%d",rcvdMsgPtr->adminState,__FUNCTION__,__LINE__);
      return(FALSE);
   }
/*Change PCU R2.5 Aricent -- END*/

   LOG_PRINT(LOG_INFO,"nsvcTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of nsvcTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       frLinkTableRangeChk()
Parameters:          Pointer to FrLinkTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for FrLink table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool frLinkTableRangeChk(FrLinkTableApi* rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function frLinkTableRangeChk()");
/*Changes PCU R2.5 Aricent -- START*/
   if ((rcvdMsgPtr->frChnId < OAMS_CFG_FR_CHN_ID_MIN_VALUE)  ||  (rcvdMsgPtr->frChnId > OAMS_CFG_FR_CHN_ID_MAX_VALUE))
   {
      LOG_PRINT(LOG_MAJOR,"frLinkTable Rangecheck failed for FrChnId [%u] in function:%s line:%d",rcvdMsgPtr->frChnId,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ( ZERO == rcvdMsgPtr->startTs || 32 <= rcvdMsgPtr->startTs)
   {
      LOG_PRINT(LOG_MAJOR,"frLinkTable Rangecheck failed for StartTS [%u] in function:%s line:%d",rcvdMsgPtr->startTs,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ( (rcvdMsgPtr->startTs + rcvdMsgPtr->numTs - 1) > 31)
   {
      LOG_PRINT(LOG_MAJOR,"frLinkTable Rangecheck failed for (startTs[%u] + numTs[%u]) > 32 in function:%s line:%d",rcvdMsgPtr->startTs,rcvdMsgPtr->numTs,__FUNCTION__,__LINE__);
      return(FALSE);
   }
/*Changes PCU R2.5 Aricent -- END*/
   LOG_PRINT(LOG_INFO,"frLinkTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of frLinkTableRangeChk */   

/*Changes PCU R2.5 Aricent -- START*/
/********************************* Function  Header********************************
   Function Name:    bssPsTableRangeChk()
Parameters:          Pointer to BssPsTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for BssPs table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool bssPsTableRangeChk(BssPsTableApi* rcvdMsgPtr)
{
   PsCellTableApi* tempPsCellTablePtr = PNULL; /* Changes for mantis id # 19881 */
   PsCellTableApi* tempPsCellTablePtr1 = PNULL;
   I_S32  ret = CM_FAILURE;
   I_U32  rowsCount = 0;
   I_U32  i = 0;
   I_U16  outSize;
   I_U16  minNumPDCHSum=ZERO;
   
   LOG_PRINT(LOG_INFO,"Entering function bssPsTableRangeChk()");
   if (rcvdMsgPtr->nmo > OAMS_CFG_NMO_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"bssPsTable Rangecheck failed for nmo [%u] in function:%s line:%d",rcvdMsgPtr->nmo,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->sgsnr > OAMS_CFG_SGSNR_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"bssPsTable Rangecheck failed for sgsnr [%u] in function:%s line:%d",rcvdMsgPtr->sgsnr,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->tAvgW > OAMS_CFG_T_AVG_W_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"bssPsTable Rangecheck failed for tAvgW [%u] in function:%s line:%d",rcvdMsgPtr->tAvgW,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->tAvgT > OAMS_CFG_T_AVG_T_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"bssPsTable Rangecheck failed for tAvgT [%u] in function:%s line:%d",rcvdMsgPtr->tAvgT,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->nAvgI > OAMS_CFG_N_AVG_I_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"bssPsTable Rangecheck failed for nAvgI [%u] in function:%s line:%d",rcvdMsgPtr->nAvgI,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if (rcvdMsgPtr->maxNumPdchBss > MAX_NUM_PDCH_PER_BSS)
   {
      LOG_PRINT(LOG_MAJOR,"bssPsTable Rangecheck failed for maxNumPdchBss [%u] in function:%s line:%d",rcvdMsgPtr->maxNumPdchBss,__FUNCTION__,__LINE__);
      return(FALSE);
   }
   /* Changes for mantis id # 19881 */
   ret = getallPsCellTable(&tempPsCellTablePtr, &rowsCount, &outSize);
   
   if ( CLIB_SUCCESS == ret)
   {       
      for(i = 0; i < rowsCount; i++)
      {
         tempPsCellTablePtr1 = (PsCellTableApi *) (((I_U8 *) tempPsCellTablePtr ) + (outSize * i));
         minNumPDCHSum+=tempPsCellTablePtr1->minNumPdchCell;
      }
      free(tempPsCellTablePtr);
   }
   else if(DBLIBERR_PTOPAGE_HAS_NO_ROWS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"DB call getallPsCellTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      return FALSE;
   }
   if(minNumPDCHSum >rcvdMsgPtr->maxNumPdchBss)
     {
      LOG_PRINT(LOG_MAJOR,"bssPsTable consistency Check  failed , Total of minPDCH in all Cells %u \
          is greater than maxNumPdchBss [%u] in function:%s line:%d",minNumPDCHSum,
          rcvdMsgPtr->maxNumPdchBss,__FUNCTION__,__LINE__);
      return(FALSE);
     } 
   
   LOG_PRINT(LOG_INFO,"bssPsTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */
}
/*Changes PCU R2.5 Aricent -- END*/

/********************************* Function  Header********************************
   Function Name:       lepInfoTableRangeChk()
Parameters:          Pointer to LepInfoTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for LepInfo table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool lepInfoTableRangeChk(LepInfoTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function lepInfoTableRangeChk()");
   if (rcvdMsgPtr->lepPort < OAMS_CFG_LEP_PORT_MIN_VALUE || rcvdMsgPtr->lepPort > OAMS_CFG_LEP_PORT_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"lepInfoTable Rangecheck failed for lepPort [%u] in function:%s line:%d",rcvdMsgPtr->lepPort,__FUNCTION__,__LINE__);
      return(FALSE);
   }

   LOG_PRINT(LOG_INFO,"lepInfoTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

} /* end of lepInfoTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       repInfoTableRangeChk()
Parameters:          Pointer to RepInfoTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for RepInfo table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool repInfoTableRangeChk(RepInfoTableApi * rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function repInfoTableRangeChk()");

   if (rcvdMsgPtr->repPort < OAMS_CFG_LEP_PORT_MIN_VALUE || rcvdMsgPtr->repPort > OAMS_CFG_LEP_PORT_MAX_VALUE)
   {
      LOG_PRINT(LOG_MAJOR,"repInfoTable Rangecheck failed for repPort [%u] in function:%s line:%d",rcvdMsgPtr->repPort,__FUNCTION__,__LINE__);
      return(FALSE);
   }

   LOG_PRINT(LOG_INFO,"repInfoTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

}   /* end of repInfoTableRangeChk */

/********************************* Function  Header********************************
   Function Name:       hoCtrlTableRangeChk()
Parameters:          Pointer to HoCtrlTableApi
Return type:         I_Bool
Purpose:             To check if all the RW Parameters are in range or not for HoCtrl table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool hoCtrlTableRangeChk(HoCtrlTableApi* rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO," Entering function hoCtrlTableRangeChk()");
   if ((rcvdMsgPtr->cellId < 0) || (rcvdMsgPtr->cellId > 65535))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->lac < 1) || (rcvdMsgPtr->lac > 65535) || (rcvdMsgPtr->lac == 65534))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->enHoLev != TRUE) && (rcvdMsgPtr->enHoLev != FALSE))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->enHoQual != TRUE) && (rcvdMsgPtr->enHoQual != FALSE))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->enHoPbgt != TRUE) && (rcvdMsgPtr->enHoPbgt != FALSE))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->windowSizeRxLevH < 1) || (rcvdMsgPtr->windowSizeRxLevH > 10))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->windowSizeRxQualH < 1) || (rcvdMsgPtr->windowSizeRxQualH > 10))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if ((rcvdMsgPtr->windowSizeNcell < 1) || (rcvdMsgPtr->windowSizeNcell > 10))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->lRxLevDlH > 63)
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->lRxLevUlH > 63)
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->lRxQualDlH > 7)
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->lRxQualUlH > 7)
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->hystH > 63)
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
   if (rcvdMsgPtr->multibandReporting > 3)
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  
/* Changes For WCDMA-GSM HO Feature : Start */
   if ((rcvdMsgPtr->enableIncHo != TRUE) && (rcvdMsgPtr->enableIncHo != FALSE))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }  

   if ((rcvdMsgPtr->enableIncWcdmaFddHo != TRUE) && (rcvdMsgPtr->enableIncWcdmaFddHo != FALSE))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
     if ((rcvdMsgPtr->qSearch_I < 0) || (rcvdMsgPtr->qSearch_I > 15))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->qSearch_C_Initial < 0) || (rcvdMsgPtr->qSearch_C_Initial > 1))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->fddQmin < 0) || (rcvdMsgPtr->fddQmin > 7))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
   if ((rcvdMsgPtr->fddQminOffset < 0) || (rcvdMsgPtr->fddQminOffset > 7))
   {
      LOG_PRINT(LOG_DEBUG," HoCtrlTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return(FALSE);
   }
/* Changes For WCDMA-GSM HO Feature : End */

   LOG_PRINT(LOG_INFO," hoCtrlTableRangeChk: Returns TRUE when all parameters are within range");
   return(TRUE);  /* Returns TRUE when all parameters are within range */

}/* end of hoCtrlTableRangeChk */


/********************************* Function  Header********************************
   Function Name:       compareRcvdMsgAndDbEntry()
Parameters:          Void  Pointer- Pointer to the received messsage Ptr
Void  Pointer- Pointer to corresponding DB Entry
I_U32- Size of Message
Return type:         I_Bool
Purpose:             To check if there is any change in received message Parameters and
corresponding DB entry
Returns TRUE, if there is a change in the parameters
Returns FALSE, if received meesage has same parameter values as in DB
Other Note:
 ************************************************************************************/
I_Bool compareRcvdMsgAndDbEntry(void* rcvdMsgPtr, void * dbEntryPtr,I_U32 size)
{
   LOG_PRINT(LOG_INFO," Entering function compareRcvdMsgAndDbEntry()");

   if (  0 == memcmp(rcvdMsgPtr, dbEntryPtr, size))
   {
      LOG_PRINT(LOG_DEBUG," compareRcvdMsgAndDbEntry failed in function:%s line:%d",__FUNCTION__,__LINE__);
      return FALSE;
   }
   else
   {
      /* There is a changes in the parameter. */
      LOG_PRINT(LOG_INFO," compareRcvdMsgAndDbEntry returns true");
      return TRUE;
   }
} /* end of compareRcvdMsgAndDbEntry */


/********************************* Function  Header*****************************
   Function Name   : bicTableRangeChk()
Parameters   : rcvdMsgPtr :: BicTableApi*
Return type   : I_Bool
Purpose      : It perform range check on the parameters of BicTable. It 
return TRUE if range check on all parameters passes, otherwise
returns FALSE. 
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Bool bicTableRangeChk(BicTableApi* rcvdMsgPtr)
{
   BicTrxTsTableApi* bicTrxTsTableApiPtr = NULL;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_S32 dbStatus = -1;

   LOG_PRINT(LOG_INFO,"Entering Function : bicTableRangeChk");
   
   /* Mantis - 8229 : Starts */
   if((rcvdMsgPtr->bicId < 1) || (rcvdMsgPtr->bicId > 4294967294))
   {
      LOG_PRINT(LOG_DEBUG,"bicTableRangeChk : Range Check Failed - bicId : %d",\
            rcvdMsgPtr->bicId);
        cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return (FALSE);
   }
   /* Mantis - 8229 : Ends   */
   if(rcvdMsgPtr->btsType != R3_BTS) /*R2.8 */
   {     
     dbStatus = getallBicTrxTsTable(&bicTrxTsTableApiPtr, &outRow, &outSz);
     if(DBLIB_SUCCESS != dbStatus)   
     {
       LOG_PRINT(LOG_MAJOR,"bicTableRangeChk : BicTrxTsTable is Not Populated in\
           DB.So Unable to Calculate possible value of numTrx \
           in received request");
       cfgSendNackToCm(CM_ERR_GET_FAIL);
       return (FALSE);
     }
     else if(rcvdMsgPtr->numTrx > outRow)
     {
       LOG_PRINT(LOG_INFO,"bicTableRangeChk : Range Check Failed - numTrx : %d",\
           rcvdMsgPtr->numTrx);
       free(bicTrxTsTableApiPtr);
       cfgSendNackToCm(CM_ERR_NUM_TRX_RANGE_FAIL);
       return (FALSE);
     }
     else
     {
       free(bicTrxTsTableApiPtr);
     }

     if(rcvdMsgPtr->btsType != R2_BTS_IP)/*Changes for R2.8 */
     {  
       if( (rcvdMsgPtr->e1Id < 0) || (rcvdMsgPtr->e1Id > CFG_MAX_NUM_INT_E1 ) ) 
       {
         LOG_PRINT(LOG_INFO,"bicTableRangeChk : Range Check Failed - e1Id : %u",\
             rcvdMsgPtr->e1Id);
         cfgSendNackToCm(CM_ERR_E1_NOT_PRESENT_IN_DB);
         return (FALSE);
       }
     } 
     /*Changes For R2.2 : End */
   }

   if((rcvdMsgPtr->btsType != BIC) && (rcvdMsgPtr->btsType != R2_BTS)&& (rcvdMsgPtr->btsType != R3_BTS)&&
       (rcvdMsgPtr->btsType != R2_BTS_IP)) 
   {
      LOG_PRINT(LOG_INFO,"bicTableRangeChk : Range Check Failed - btsType : %d",\
            rcvdMsgPtr->btsType);
        cfgSendNackToCm(CM_ERR_INVALID_BTS_TYPE);
      return (FALSE);
   }

   if(rcvdMsgPtr->btsReset != NO_RESET)  
   {
      LOG_PRINT(LOG_INFO,"bicTableRangeChk : Range Check Failed - btsReset : %d",\
            rcvdMsgPtr->btsReset);
        cfgSendNackToCm(CM_ERR_INVALID_BTS_RESET);
      return (FALSE);
   }

   if((rcvdMsgPtr->btsConnectivityState != BTS_CONNECT) && (rcvdMsgPtr->btsConnectivityState != BTS_DISCONNECT)) 
   {
      LOG_PRINT(LOG_INFO,"bicTableRangeChk : Range Check Failed - btsConnectivityState : %d",\
            rcvdMsgPtr->btsConnectivityState);
        cfgSendNackToCm(CM_ERR_INVALID_BTS_CONSTATE);
      return (FALSE);
   }

   if (((rcvdMsgPtr->btsType == BIC) || (rcvdMsgPtr->btsType == R2_BTS))
        && (rcvdMsgPtr->clusterId != ZERO))
   {
      LOG_PRINT(LOG_DEBUG,"bicTableRangeChk : Valid ClusterId value Valid only for IP Bts");
      cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_ID_BTS_TYPE);
      return (FALSE);
   }

   if(rcvdMsgPtr->clusterId > CLUSTER_ID_RANGE)
   {
      LOG_PRINT(LOG_INFO,"bicTableRangeChk : Range Check Failed - clusterId : %d",\
            rcvdMsgPtr->clusterId);
        cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_ID_VALUE);
      return (FALSE);
   }

   if ((rcvdMsgPtr->maxRfPwrConf < 0) || (rcvdMsgPtr->maxRfPwrConf > 127))
   {
      LOG_PRINT(LOG_INFO,"bicTableRangeChk : Range Check Failed - maxRfPwrConf : %u",\
            rcvdMsgPtr->maxRfPwrConf);
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return (FALSE);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : bicTableRangeChk");
   return (TRUE);
}


/********************************* Function  Header*****************************
   Function Name   : trxTableRangeChk()
Parameters   : rcvdMsgPtr :: TrxTableApi*
Return type   : I_Bool
Purpose      : It perform range check on the parameters of TrxTable. It 
return TRUE if range check on required parameters passes, 
otherwise returns FALSE.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Bool trxTableRangeChk(TrxTableApi* rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering Function : trxTableRangeChk");

   if((rcvdMsgPtr->ptrxId < 1) || (rcvdMsgPtr->ptrxId > CFG_MAX_NUM_TRX))
   {
      LOG_PRINT(LOG_DEBUG,"trxTableRangeChk : Range Check Failed - ptrxId : %d",
            rcvdMsgPtr->ptrxId);
      return (FALSE);
   }
   if((rcvdMsgPtr->adminState != LOCK) && (rcvdMsgPtr->adminState != UNLOCK))
   {
      LOG_PRINT(LOG_DEBUG,"trxTableRangeChk : Range Check Failed - adminState :\
            %d", rcvdMsgPtr->adminState);
      return (FALSE);
   }
/*Changes for  R2.2 : Start */
   if((TRX_LOCATION_BIC != rcvdMsgPtr->trxLocation) &&
         (TRX_LOCATION_IN_FRAME != rcvdMsgPtr->trxLocation) &&
         (TRX_LOCATION_R2_BTS != rcvdMsgPtr->trxLocation)&&
         (TRX_LOCATION_R2_BTS_IP != rcvdMsgPtr->trxLocation)&&
         (TRX_LOCATION_R3_BTS != rcvdMsgPtr->trxLocation)/*Changes for R2.8 */
         
      )
/*Changes for  R2.2 : End */
   {
      LOG_PRINT(LOG_INFO,"trxTableRangeChk : Range Check Failed - trxLocation : %d",\
            rcvdMsgPtr->trxLocation);
      return (FALSE);
   }
   if((TRX_LOCATION_IN_FRAME == rcvdMsgPtr->trxLocation) &&
         (ZERO != rcvdMsgPtr->bicId)
      )
   {
      LOG_PRINT(LOG_INFO,"trxTableRangeChk : Range Check Failed - bicId Receivd in \
            Request is not 0 for In-Frame Trx");
      return (FALSE);
   }
/* Changes for R2.2 : Start */
   if(NO_RESET != rcvdMsgPtr->trxReset)
   {
      LOG_PRINT(LOG_INFO,"trxTableRangeChk : Trx Not allowed with RESET option");
      return (FALSE);
   }
   if(POWER_ON != rcvdMsgPtr->trxPwrAction)
   {
      LOG_PRINT(LOG_INFO,"trxTableRangeChk : Trx Not allowed with POWER_OFF option");
      return (FALSE);
   }
/* Changes for R2.2 : End */


   LOG_PRINT(LOG_INFO,"Exiting Function : trxTableRangeChk");
   return (TRUE);
}

/* Changes For E1-T1 : Start */
/********************************* Function  Header*****************************
   Function Name   : trunkPortTableRangeChk()
Parameters   : rcvdMsgPtr :: TrunkPortTableApi*
Return type   : I_Bool
Purpose      : It perform range check on the parameters of TrunkPortTable. It 
return TRUE if range check on required parameters passes, 
otherwise returns FALSE.
Other Note   : Added For BSC R2.5.5(E1-T1)
 *******************************************************************************/
I_Bool trunkPortTableRangeChk(TrunkPortTableApi* rcvdMsgPtr)
{
   LOG_PRINT(LOG_INFO,"Entering Function : trunkPortTableRangeChk");
   
   if(    (g_TrunkPortDb.trunkType == BPM_TRUNK_TYPE_E1) &&
            !( (rcvdMsgPtr->trunkFramingOption == BPM_TRUNK_FRAMING_OPT_E1_CRC4) ||
              (rcvdMsgPtr->trunkFramingOption == BPM_TRUNK_FRAMING_OPT_E1_NOCRC4) )  )   
   {
      LOG_PRINT(LOG_DEBUG,"trunkPortTableRangeChk : Range Check Failed - trunkFramingOption(trunkType=E1) :\
            %d", rcvdMsgPtr->trunkFramingOption);
      return (FALSE);
   }  
   if(    (g_TrunkPortDb.trunkType == BPM_TRUNK_TYPE_T1) &&
              !( (rcvdMsgPtr->trunkFramingOption ==BPM_TRUNK_FRAMING_OPT_T1_D4) ||
                (rcvdMsgPtr->trunkFramingOption ==BPM_TRUNK_FRAMING_OPT_T1_ESF) )  )   
   {
      LOG_PRINT(LOG_DEBUG,"trunkPortTableRangeChk : Range Check Failed - trunkFramingOption(trunkType=T1) :\
            %d", rcvdMsgPtr->trunkFramingOption);
      return (FALSE);
   }
  /* Fixed Issue :14124(Remove T1_E1_AMI From EncodeType for E1) */ 
   if(    (g_TrunkPortDb.trunkType == BPM_TRUNK_TYPE_E1) &&
          (rcvdMsgPtr->encodeType !=BPM_TRUNK_ENCODE_OPT_E1_HDB3) )   
   {
      LOG_PRINT(LOG_DEBUG,"trunkPortTableRangeChk : Range Check Failed - encodeType(trunkType=E1) :\
            %d", rcvdMsgPtr->encodeType);
      return (FALSE);
   }  
   if(    (g_TrunkPortDb.trunkType == BPM_TRUNK_TYPE_T1) &&
          !( (rcvdMsgPtr->encodeType ==BPM_TRUNK_ENCODE_OPT_T1_E1_AMI) ||
              (rcvdMsgPtr->encodeType ==BPM_TRUNK_ENCODE_OPT_T1_B8ZS) )  )   
   {
      LOG_PRINT(LOG_DEBUG,"trunkPortTableRangeChk : Range Check Failed - encodeType(trunkType=T1) :\
            %d", rcvdMsgPtr->encodeType);
      return (FALSE);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : trunkPortTableRangeChk");
   return (TRUE);

}
/* Changes For E1-T1 : End */

/* Changes for TsGroup Start */
/********************************* Function  Header********************************
Function Name:       tsGroupConfigTableRangeCheck()
Parameters:          Pointer to TsGroupConfigTableApi 
Return type:         CM_SUCCESS if pass, other CM_ERR_<ERR_ID> 
Purpose:             1. Checks validity of TsGroupConfig Table parameters.
                     2. Called when set() is called on TsGroup Table.
                     3. If parameters are consistent,CM_SUCCESS will be 
                         returned otherwise error is returned.
Other Note:           
**********************************************************************************/
I_U32 tsGroupConfigTableRangeCheck(TsGroupConfigTableApi *receivedMsgPtr)
{
  I_U32 retStatus;
  I_U32 trunkUsageType1,trunkUsageType2;
  I_U32 maxTrunkTs;
  I_S32 dbStatus;
  TrunkTableIndices trunkTableIndex;
  TrunkTableApi *trunkTableApiPtr=PNULL;

   LOG_PRINT(LOG_DEBUG,"Entering Function : %s",__FUNCTION__);
   LOG_PRINT(LOG_DEBUG,"NUMTS(%d),TrunkPortId1(%d),TrunkPortId2(%d)",receivedMsgPtr->numTS,receivedMsgPtr->trunkPortId1,receivedMsgPtr->trunkPortId2);
  trunkTableIndex.e1Num=receivedMsgPtr->trunkPortId1;
  dbStatus=getTrunkTable(&trunkTableIndex,&trunkTableApiPtr);
  if(dbStatus != DBLIB_SUCCESS)
  {
    LOG_PRINT(INFO,"Get on Trunk Table failed for e1Num(%d)",receivedMsgPtr->trunkPortId1);
    return CM_ERR_TRUNKPORT_DOES_NOT_EXIST; 
  }
  else
  {
    if(trunkTableApiPtr->e1Category == INTERNAL_E1) 
    {
      LOG_PRINT(INFO,"%s: TrunkPort(%d) should be EXTERNAL",__func__,receivedMsgPtr->trunkPortId1);
      free(trunkTableApiPtr);
      return CM_ERR_E1_TYPE_NOT_EXTERNAL;
    }
    trunkUsageType1=trunkTableApiPtr->usageType;
    free(trunkTableApiPtr);
  }

  trunkTableIndex.e1Num=receivedMsgPtr->trunkPortId2;
  dbStatus=getTrunkTable(&trunkTableIndex,&trunkTableApiPtr);
  if(dbStatus != DBLIB_SUCCESS)
  {
    LOG_PRINT(INFO,"Get on Trunk Table failed for e1Num(%d)",receivedMsgPtr->trunkPortId2);
    return CM_ERR_TRUNKPORT_DOES_NOT_EXIST;
  }
  else
  {
    if(trunkTableApiPtr->e1Category == INTERNAL_E1) 
    {
      LOG_PRINT(INFO,"%s: TrunkPort(%d) should be EXTERNAL",__func__,receivedMsgPtr->trunkPortId2);
      free(trunkTableApiPtr);
      return CM_ERR_E1_TYPE_NOT_EXTERNAL;
    }
    trunkUsageType2=trunkTableApiPtr->usageType;
    free(trunkTableApiPtr);
  }

  if((SYS_E1_USAGE_AIF != trunkUsageType1  && SYS_E1_USAGE_ABISIF != trunkUsageType1) && 
  (SYS_E1_USAGE_AIF != trunkUsageType2  && SYS_E1_USAGE_ABISIF != trunkUsageType2))
  {  
  LOG_PRINT(INFO,"%s: Both TrunkPort should be either AIF or ABISIF",__func__);
    return CM_ERR_TRUNK_USAGE_TYPE_NOT_ABIS_OR_AIF;
  }

  if(receivedMsgPtr->trunkPortId1 == receivedMsgPtr->trunkPortId2)
  {
    LOG_PRINT(INFO,"TrunkPortId1(%d) is same as TrunkPortId2(%d)",receivedMsgPtr->trunkPortId1,receivedMsgPtr->trunkPortId2);
    return CM_ERR_BOTH_TRUNKPORT_SAME;
  }


  if(gBscTrunkType==BPM_TRUNK_TYPE_T1)
  {
    maxTrunkTs=MAX_T1_TS;
  }
  else
  {
    maxTrunkTs=MAX_E1_TS;
  }

  if(receivedMsgPtr->numTS<1 || receivedMsgPtr->numTS>maxTrunkTs-1)
  {
    LOG_PRINT(INFO,"Number of TimeSlots should be between 1 and %d",maxTrunkTs-1);
    return CM_ERR_PARAM_OUT_OF_RANGE;
  }

   LOG_PRINT(LOG_INFO,"Exiting Function : %s",__FUNCTION__);
  return CM_SUCCESS;
}
/* Changes for TsGroup End*/

/* Changes for callEndTableTimerRangeCheck Start*/
/********************************* Function  Header********************************
Function Name:       callEndTableTimerRangeCheck()
Parameters:          Pointer to CallEndTimerConfigTableApi
Return type:         I_Bool
Purpose:             To check if all the Parameters are in range or not for CallEndTimerConfig table
Returns TRUE, if in all Parameters are in Range
Returns FALSE, if any Parameter is out of range
Other Note:
 ************************************************************************************/
I_Bool callEndTableTimerRangeCheck(CallEndTimerConfigTableApi* rcvdMsgPtr)
{

  if( rcvdMsgPtr->callEndTimer >= 60  || rcvdMsgPtr->callEndTimer <= 900 ||  rcvdMsgPtr->callEndTimer == 4294967295 )
  {
      return (TRUE); 
  }
  else
    return (FALSE);

}
/* Changes for callEndTableTimerRangeCheck End*/

/******************   Change History *******************************************
   Release     Patch       Author              Description
   1.0                    Pooja Mittal      Range Check Methods for Tables
   BSC CS2.2       Kapil Tyagi      Added Function bicTableRangeChk &
   trxTableRangeChk   
 ******************************************************************************/
