/***********************************File Header ***************************
   File Name        : oamscfg_alarm_handler.c
Purpose          : This file contains CFG Alarm Handler implementation 
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>
#define mkstr(a) #a
#define NAND_ALARM_HANDLE(){\
               gCfgAlarmIdRcvd = recAlarmPtr->sysalarmId;\
               makeCopyOfAlarm();\
               sendAlarmToPDC(gCfgAlarmIdRcvd);\
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),\
                   ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);\
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);\
               gCfgAlarmBuf = NULL;\
}
/*Added for IP_BSC_STACK Gaurav Sinha 08-09-2016*/
I_Void updateOrInsertAspStatusTable(I_U16 localAspId,I_U16 status)
{
   LOG_PRINT(DEBUG,"IP_BSC_STACK: Entering updateOrInsertAspStatusTable()");
   SigtranM3uaLAspConfigTableIndices key;
   SigtranM3uaLAspConfigTableApi* sigtranM3uaLAspConfigTableApi = NULL;
   key.localAspId = localAspId;
   if(CLIB_SUCCESS!=getSigtranM3uaLAspConfigTable(&key,&sigtranM3uaLAspConfigTableApi))
   {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: getSigtranM3uaLAspConfigTable() failed for localAspId %d:  Exiting updateOrInsertAspStatusTable()",localAspId);
     return;
   }
   I_S32 dbSts=-1;

   //sigtranM3uaLAspConfigTableApi->localAspId = localAspId;
   LOG_PRINT(DEBUG,"IP_BSC_STACK: Going to update Operational Status New %d Curr %d",status,sigtranM3uaLAspConfigTableApi->operationalStatus);
   sigtranM3uaLAspConfigTableApi->operationalStatus = status;

   /*if(CLIB_SUCCESS == (dbSts = insertSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi)))
   {
     LOG_PRINT(DEBUG,"IP_BSC_STACK:  insertSigtranM3uaLAspConfigTable SUCCESS (dbSts=%d), for localAspId = %d", dbSts,localAspId);
   }
   else
   {*/
     dbSts = updateSigtranM3uaLAspConfigTable(sigtranM3uaLAspConfigTableApi);
     LOG_PRINT(DEBUG,"IP_BSC_STACK:  updateSigtranM3uaLAspConfigTable (dbSts=%d), for localAspId = %d status = %d", dbSts,localAspId,status);
   //}
   LOG_PRINT(DEBUG,"IP_BSC_STACK: Exiting updateOrInsertAspStatusTable()");
}
/*Added for IP_BSC_STACK Gaurav Sinha 08-09-2016*/
void cfgAlarmHandler()
{
   OamsCfgGrhmLockReq OamsCfgGrhmLockReqBuff={0};
   OamsCfgGrhmUnlockReq OamsCfgGrhmUnlockReqBuff={0};
   I_U32 outRows;
   I_U16 outSize;
   I_U8 count =0;
   I_U32 i;
   I_U32 oprStateAInterface = 0;
   I_U8  trunkAlarms        = 0; 
   I_U8  res              = TRUE;
   I_U32 swStatus[TWO]={ZERO};
   I_U32 clkRef = 0; 
   I_U8 timeSlot = INVALID_TS;
	 
	 I_U32 cardState;
   I_S32 ret;
   I_U32 ipBtsId = 0 ;
	 IccCardInfoTableIndices iccCardInfoTableIndices;
	 IccCardInfoTableApi *iccCardInfoTableApiPtr=NULL;
	 IccCardInfoTableApi *tmpIccCardPtr = NULL;
   IccCardInfoTableApi *outDataIcc;

   AiftrunkTableSecIndices aiftrunkSecIndex;
   AiftrunkTableApi *outData; 
   CicTableApi *cicTblPtr;

/*Changes PCU R2.5 Aricent --START*/   
   OamsCfgPschBvcOpFailed oamsCfgPschBvcOpFailedBuff;
   OamsCfgGbhSigBvcResetFailed oamsCfgGbhSigBvcResetFailed;
   OamsCfgGbhFirstNsvcEnabled oamsCfgGbhFirstNsvcEnabledBuff;
   OamsCfgGbhLastNsvcDisabled oamsCfgGbhLastNsvcDisabledBuff;
/*Changes PCU R2.5 Aricent --END*/   
   CellNonPerTableApi *cellNonPerOutData=NULL;
   CardStateChangeTableApi cardStateChangeTbl;
   memset(&OamsCfgGrhmLockReqBuff,0,sizeof(OamsCfgGrhmLockReq));

   SysHdr* recHdrPtr = ( SysHdr* )gCfgMsgBuf;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   LOG_PRINT(DEBUG,"ALARMID:: Rcvd: %d", recAlarmPtr->sysalarmId); 

   switch (recHdrPtr->msgType)
   {
      case OAMS_CELLH_CFG_ALARM_IND:
      case CSAPP_CBSH_CFG_ALARM_IND:
      case OAMS_TRXH_CFG_ALARM_IND:
      case OAM_OIL_CFG_ALARM_IND: 
         LOG_PRINT(DEBUG,"ALARM Id Rcvd:%d",recAlarmPtr->sysalarmId);
         switch ( recAlarmPtr->sysalarmId ) 
         {
            case INFO_BPM_MLPPP_CONNECTED:
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_BPM_MLPPP_CONNECTED");
               mlpppConnectHandler();
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            case INFO_BPM_MLPPP_DISCONNECTED:
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_BPM_MLPPP_DISCONNECTED");
               mlpppDisconnectHandler();
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            case INFO_BPM_MLPPP_CHAN_STATUS:
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_BPM_MLPPP_CHAN_STATUS");
               LOG_PRINT(DEBUG,"MLPPP Channel Status on ChasisFrameId [%d],SlotId [%d],DataChannel [%d],DataChannelStatus [%d]",recAlarmPtr->key1,recAlarmPtr->key2,recAlarmPtr->key3,recAlarmPtr->key4);
               mlpppChanStatusHandler(&timeSlot);
               recAlarmPtr->key3 = timeSlot;
               recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString ,"MLPPP Channel Status on ChasisFrameId [%d],SlotId [%d],DataChannel [%d],DataChannelStatus [%d]",recAlarmPtr->key1,recAlarmPtr->key2,recAlarmPtr->key3,recAlarmPtr->key4);
               //mlpppChanStatusHandler(&timeSlot);
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            case INFO_BPM_MLPPP_CONFIG_REQ_EXHAUST:
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_BPM_MLPPP_CONFIG_REQ_EXHAUST");
               mlpppExhaustHandler();
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            
            case ALARM_E1_ENABLE_SUCCESS:
            case ALARM_E1_DISABLE_SUCCESS:
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
               makeCopyOfAlarm();

               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               if( TRUE == res )
               {  
                 cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                 if(gCfgState != CFG_BPM_INIT)
                 {
                   //trunkAlarms = 1;
                   TrunkPortObjectHandler();
                 }
               } 
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               break;
             
            // Transparently pass these alarms to OMC.
            case INFO_MFRAMER_R_LOSS_OF_SIG_PM_OAM:
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_MFRAMER_R_LOSS_OF_SIG_PM_OAM");               
               gE1Data[recAlarmPtr->key3].LOS_Signal = TRUE;
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               if ( TRUE == res )
               {  
                 cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               }   
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;
               break;

            case INFO_MFRAMER_R_LOSS_OF_FRAME_PM_OAM:
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_MFRAMER_R_LOSS_OF_FRAME_PM_OAM");               
               gE1Data[recAlarmPtr->key3].LOS_Frame = TRUE;
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               if ( TRUE == res )
               {  
                 cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               } 
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;
               break;

            case INFO_MFRAMER_R_LOSS_OF_SIG_CLR_PM_OAM:
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_MFRAMER_R_LOSS_OF_SIG_CLR_PM_OAM");               
               if(gE1Data[recAlarmPtr->key3].LOS_Signal == FALSE)
               {
                  trunkAlarms = 1;res = FALSE;
               }
               else
                  gE1Data[recAlarmPtr->key3].LOS_Signal = FALSE;
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               if ( TRUE == res )
               {  
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               }
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;
               break;

            case INFO_MFRAMER_R_LOSS_OF_FRAME_CLR_PM_OAM:
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_MFRAMER_R_LOSS_OF_FRAME_CLR_PM_OAM");
               if( gE1Data[recAlarmPtr->key3].LOS_Frame == FALSE)
               {
                  trunkAlarms = 1;res = FALSE;
               }
               else
                  gE1Data[recAlarmPtr->key3].LOS_Frame = FALSE;

               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               if ( TRUE == res )
               {  
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               } 
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;

               break;

            case INFO_MFRAMER_LOSS_OF_SIGNAL_DETECT_PM_OAM:
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_MFRAMER_LOSS_OF_SIGNAL_DETECT_PM_OAM");               
               gE1Data[recAlarmPtr->key3].LOS_Signal_detect = TRUE;
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               if ( TRUE == res )
               {  
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               } 
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;
               break;

            case INFO_MFRAMER_LOSS_OF_SIGNAL_DETECT_CLR_PM_OAM:
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_MFRAMER_LOSS_OF_SIGNAL_DETECT_CLR_PM_OAM");               
               if(gE1Data[recAlarmPtr->key3].LOS_Signal_detect == FALSE)
               {
                  trunkAlarms = 1;res = FALSE;
               }
               else
                  gE1Data[recAlarmPtr->key3].LOS_Signal_detect = FALSE;
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               if ( TRUE == res )
               {  
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               } 
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;
               break;

            case ALARM_E1_LOS_ACTIVE:
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_FRAMER_PORT_DOWN_PM_OAM");               
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               if( TRUE == res )
               {
                  FillObjTypeFromSlotId(recAlarmPtr->key2, 
                          recAlarmPtr->info3);
                  makeCopyOfAlarm();
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                  TrunkPortObjectHandler();
                  DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							    gCfgAlarmBuf = NULL;
               }
               break;

            case ALARM_E1_LOS_CLEAR:
               LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_FRAMER_PORT_UP_PM_OAM");               
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);  // Check here if alarm received is for Active card only
               if( TRUE == res )
               {
                  FillObjTypeFromSlotId(recAlarmPtr->key2, 
                           recAlarmPtr->info3);
                  makeCopyOfAlarm();
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                  TrunkPortObjectHandler();
							    DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							    gCfgAlarmBuf = NULL;
               } 
               break;

             case INFO_PEER_CARDSTATE_CHANGE_PM_OAM:
               LOG_PRINT(LOG_DEBUG,"Alarm Received::  INFO_PEER_CARDSTATE_CHANGE_PM_OAM");
               LOG_PRINT(LOG_DEBUG,"Previous State [%d], Next State [%d]" , recAlarmPtr->key3, recAlarmPtr->key4);
               LOG_PRINT(LOG_INFO,"Card State Change for ChasisFrameId [%d] and SlotId [%d]", recAlarmPtr->key1, recAlarmPtr->key2);
							 
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key2);
              
               if(res == TRUE)
               {
                  makeCopyOfAlarm();
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                  DalocOrdBuf((I_Void *)gCfgAlarmBuf);
                  gCfgAlarmBuf = NULL;

                  LOG_PRINT(DEBUG,"State of Peer Card of %d slotid is %d",recAlarmPtr->key2, recAlarmPtr->key4);
								  cardState = recAlarmPtr->key4;
								  iccCardInfoTableIndices.chasisFrameId = recAlarmPtr->key1;
								  if(recAlarmPtr->key2 == ICCSELFCARD)
    						 		 iccCardInfoTableIndices.slotId = ICCMATECARD;
		   					  else
			    			 		 iccCardInfoTableIndices.slotId = ICCSELFCARD;				 
								
								  if(updateIccCardState(&iccCardInfoTableIndices, cardState) == CLIB_SUCCESS)
								 	{
								 		LOG_PRINT(LOG_INFO,"Peer Card State Updation Succ");	
								 	}			 
								 	else
								 	{
								 		LOG_PRINT(LOG_INFO,"Peer Card State Updation failed");	
								 	}				
                  if(recAlarmPtr->key4 == CARDSTATE_STANDBY) 
                  {
                     LOG_PRINT(DEBUG,"State of Peer Card of %d slotid is STANDBY",recAlarmPtr->key2);
                     trunkAlarms = 1; res = FALSE;
                     gCfgAlarmIdRcvd = INFO_PEER_CARDSTATE_CHANGE_PM_OAM;

                     if(gCfgState != CFG_BPM_INIT)
                     {
                        sendPresentCardInfoReq();
			             /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
                    //Mantis #0031749
                     if(gCardPlatformType == 1)
		                 {
								 		    LOG_PRINT(LOG_INFO,"1U: Sending send1UCardInfoReqToOil() as gCardPlatformType [%d] IMX",gCardPlatformType);	
                        send1UCardInfoReqToOil();	
                     }
                     else
                     {
								 		   LOG_PRINT(LOG_INFO,"1U: send1UCardInfoReqToOil() NOT SENT as gCardPlatformType [%d] HOST",gCardPlatformType);	
                     }
                    //Mantis #0031749
		              /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	  
                        ret = sendRequestForBscAvailableReleases(iccCardInfoTableIndices.chasisFrameId,
                                   iccCardInfoTableIndices.slotId); 
                     }
                     gCfgStandbySlotId = iccCardInfoTableIndices.slotId; 
                     sendPeerTrunkStateChangeReq();
                     sendSwitchConForMate(iccCardInfoTableIndices.slotId);
                     sendLapdSwitchingInfoToPeerCfg();
                      
                     cardStateChangeTbl.chasisFrameId = recAlarmPtr->key1;
                    //Mantis #0031749
                   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
                     //cardStateChangeTbl.slotId = iccCardInfoTableIndices.slotId;
                     cardStateChangeTbl.slotId = iccCardInfoTableIndices.slotId-2;
										if(gCardPlatformType == 1)
										{
											cardStateChangeTbl.cardType = CARD_TYPE_OBM;
										}
                    else
                    {
										  cardStateChangeTbl.cardType = CARD_TYPE_HOST;
                    }
										LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: Insert/Update CardStateChangeTable slotId [%d] cardType [%d] ",cardStateChangeTbl.slotId,cardStateChangeTbl.cardType);
                     //cardStateChangeTbl.cardType = CARD_TYPE_ICC;
                   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
                    //Mantis #0031749
                     cardStateChangeTbl.cardOperationalState = recAlarmPtr->key4;
                     if(insertCardStateChangeTable(&cardStateChangeTbl) != CLIB_SUCCESS)
                     {
                        if(updateCardStateChangeTable(&cardStateChangeTbl) != CLIB_SUCCESS)
                        {
                                LOG_PRINT(MAJOR,"insertCardStateChangeTable failed for\
                                           frameId:%d slotId%d cardOprState:%d",
                                    cardStateChangeTbl.chasisFrameId,cardStateChangeTbl.slotId,
                                    cardStateChangeTbl.cardOperationalState); 
                        }
                     }  
                  }
                  else if(recAlarmPtr->key4 == CARDSTATE_ABSENT)  
                  {
                     LOG_PRINT(DEBUG,"State of Peer Card of %d slotid is ABSENT",recAlarmPtr->key2);
                     trunkAlarms = 1; res = FALSE;
                     gCfgAlarmIdRcvd = INFO_PEER_CARDSTATE_CHANGE_PM_OAM;

                     if(gCfgState != CFG_BPM_INIT)
                     {
                        sendPresentCardInfoReq();
		                 /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
                     //Mantis #0031749
                     if(gCardPlatformType == 1)
		                 {
								 		    LOG_PRINT(LOG_INFO,"1U: Sending send1UCardInfoReqToOil() as gCardPlatformType [%d] IMX",gCardPlatformType);	
                        send1UCardInfoReqToOil();	
                     }
                     else
                     {
								 		   LOG_PRINT(LOG_INFO,"1U: send1UCardInfoReqToOil() NOT SENT as gCardPlatformType [%d] HOST",gCardPlatformType);	
                     }
                     //Mantis #0031749
		                /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	  
                        ret = sendRequestForBscAvailableReleases(iccCardInfoTableIndices.chasisFrameId,
                                   iccCardInfoTableIndices.slotId); 
                     }
                     gCfgStandbySlotId = 0; 
                  }
                  else if(recAlarmPtr->key4 == CARDSTATE_FAIL )
                  {
                     I_S32 res;
                     LOG_PRINT(DEBUG,"State of Peer Card of %d slotid is FAIL",recAlarmPtr->key2);
                     updateCardDetails();
                     gCfgAlarmIdRcvd = INFO_PEER_CARDSTATE_CHANGE_PM_OAM;
                     //sendPresentCardInfoReq();
                     res = markDspDisabled(iccCardInfoTableIndices.chasisFrameId, iccCardInfoTableIndices.slotId);
/*                   makeCopyOfAlarm();
                     deleteIccCardDetails();
                     DalocOrdBuf((I_Void *)gCfgAlarmBuf);
                     gCfgAlarmBuf = NULL;
*/                
                     gCfgStandbySlotId = 0; 
                  }
                  else if(recAlarmPtr->key4 == CARDSTATE_OUT_OF_SERVICE)
                  {
                     LOG_PRINT(DEBUG,"State of Peer Card of %d slotid is OUT_OF_SERVICE",recAlarmPtr->key2);
                     gCfgAlarmIdRcvd = INFO_PEER_CARDSTATE_CHANGE_PM_OAM;
                     sendPresentCardInfoReq();
		                /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
                     //Mantis #0031749
                     if(gCardPlatformType == 1)
		                 {
								 		    LOG_PRINT(LOG_INFO,"1U: Sending send1UCardInfoReqToOil() as gCardPlatformType [%d] IMX",gCardPlatformType);	
                        send1UCardInfoReqToOil();	
                     }
                     else
                     {
								 		   LOG_PRINT(LOG_INFO,"1U: send1UCardInfoReqToOil() NOT SENT as gCardPlatformType [%d] HOST",gCardPlatformType);	
                     }
                     //Mantis #0031749
	                 /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	  
                     #if 0 
                     IccCardInfoTableApi *iccCardDetails = NULL;
                     IccCardInfoTableApi *tmpIccCardPtr = NULL;
                     I_U32 outRows,i=0;
                     I_U16 outSize;
                  
                     if( getallIccCardInfoTable(&iccCardDetails, &outRows, &outSize)  == CLIB_SUCCESS )
                     {
                         for(i=0;i<outRows;i++)
                         {
                            tmpIccCardPtr = (IccCardInfoTableApi *)((I_U8 *)iccCardDetails + (i * outSize));
                            LOG_PRINT(DEBUG,"Card Oper State is: %d of slotId:%d ",
                                tmpIccCardPtr->cardOperationalState ,tmpIccCardPtr->slotId);
                            if( tmpIccCardPtr->slotId == recAlarmPtr->key2 &&
                              tmpIccCardPtr->cardOperationalState == CARDSTATE_ACTIVE )
                            {
                               cardSetOperConStateRespHandler(iccCardInfoTableIndices.slotId,
                                       CARDSTATE_OUT_OF_SERVICE,OPERATION_SUCCESS);
                            }
                         }         
                         free(iccCardDetails);
                     }  
                     #endif 
                     gCfgStandbySlotId = 0; 
                  }
                  else if(recAlarmPtr->key4 == CARDSTATE_DIAGNOSTIC)
                  {
                     LOG_PRINT(DEBUG,"State of Peer Card of %d slotid is DIAGNOSTICS",recAlarmPtr->key2);
								     if(recAlarmPtr->key2 == ICCSELFCARD)
    						 	 		 	 iccCardInfoTableIndices.slotId = ICCMATECARD;
		   					     else
			    			 		 iccCardInfoTableIndices.slotId = ICCSELFCARD;				 
                     cardStateChangeTbl.chasisFrameId = recAlarmPtr->key1;
                     //Mantis #0031749
                    /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
                     //cardStateChangeTbl.slotId = iccCardInfoTableIndices.slotId;
                     //cardStateChangeTbl.cardType = CARD_TYPE_ICC;
										if(gCardPlatformType == 1)
										{
											cardStateChangeTbl.cardType = CARD_TYPE_OBM;
										}
                    else
                    {
										  cardStateChangeTbl.cardType = CARD_TYPE_HOST;
                    }
										LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: Insert/Update CardStateChangeTable slotId [%d] cardType [%d] ",cardStateChangeTbl.slotId,cardStateChangeTbl.cardType);
                     //cardStateChangeTbl.cardType = CARD_TYPE_ICC;
                   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
                    //Mantis #0031749
                     cardStateChangeTbl.cardOperationalState = recAlarmPtr->key4;
                     if(updateCardStateChangeTable(&cardStateChangeTbl) != CLIB_SUCCESS)
                     {
                       LOG_PRINT(MAJOR,"updateCardStateChangeTable failed for\
                         frameId:%d slotId%d cardOprState:%d",
                         cardStateChangeTbl.chasisFrameId,cardStateChangeTbl.slotId,
                               cardStateChangeTbl.cardOperationalState); 
                     }  
                  }
                  else if(recAlarmPtr->key4 == CARDSTATE_RECOVERY)
                  {
                   LOG_PRINT(LOG_INFO,"1U: case added for CARDSTATE_RECOVERY");
                   cardStateChangeTbl.chasisFrameId = recAlarmPtr->key1;
                   cardStateChangeTbl.slotId = iccCardInfoTableIndices.slotId-2;
                   if(gCardPlatformType == 1)
                   {
                      LOG_PRINT(LOG_INFO,"1U: Sending send1UCardInfoReqToOil() as gCardPlatformType [%d] IMX",gCardPlatformType);
											cardStateChangeTbl.cardType = CARD_TYPE_OBM;
                      send1UCardInfoReqToOil();
                   }
                   else
                   {
										 cardStateChangeTbl.cardType = CARD_TYPE_HOST;
                     LOG_PRINT(LOG_INFO,"1U: send1UCardInfoReqToOil() NOT SENT as gCardPlatformType [%d] HOST",gCardPlatformType);
                   }
									 LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: Insert/Update CardStateChangeTable slotId [%d] cardType [%d] ",cardStateChangeTbl.slotId,cardStateChangeTbl.cardType);
                   cardStateChangeTbl.cardOperationalState = recAlarmPtr->key4;
                   if(insertCardStateChangeTable(&cardStateChangeTbl) != CLIB_SUCCESS)
                   {
                      if(updateCardStateChangeTable(&cardStateChangeTbl) != CLIB_SUCCESS)
                      {
                              LOG_PRINT(MAJOR,"insertCardStateChangeTable failed for\
                                         frameId:%d slotId%d cardOprState:%d",
                                  cardStateChangeTbl.chasisFrameId,cardStateChangeTbl.slotId,
                                  cardStateChangeTbl.cardOperationalState); 
                      }
                   }  
                  }
               }
               break;

             case INFO_CARD_STATE_CHANGE_PM_OAM:
               LOG_PRINT(LOG_DEBUG,"Alarm Received::  INFO_CARD_STATE_CHANGE_PM_OAM");               
               LOG_PRINT(LOG_DEBUG,"Previous State [%d], Next State [%d]" , recAlarmPtr->key3, recAlarmPtr->key4);

               if(recAlarmPtr->key4 == CARDSTATE_ACTIVE)
               {
                  /*Changes for BSC R2.0 SwActivation*/
                  gCurrentCardState = CARDSTATE_ACTIVE;
                  /*Changes for BSC R2.0 SwActivation*/
#if 0  
//Not required now for Redundancy 05-09-2016 Gaurav Sinha
							 		/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
								 if( gSwicthoverCloudTrigger == 1)
									{
               			 LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::gSwicthoverCloudTrigger(%d) Matched Going for HaConf After Switchover",gSwicthoverCloudTrigger);
										 initiateSwitchoverProcForCloudBscStack();	
										 gSwicthoverCloudTrigger=0;//resetting it to zero again	
									}	
							 		/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
//Not required now for Redundancy 05-09-2016 Gaurav Sinha
#endif                  
                  updateCardDetails();

									/* Mantis 12264 start */
                  if((gSetNeIpRcvd == I_TRUE) && (gSetOmcIpReqSent == I_FALSE))
                  {
                    if(sendSetOmcIpUsingMlpppConfig() == CFG_FAILURE)
                    {
                      sendSetOmcipAddressReqToCmInActive();
                    }
                    gSetOmcIpReqSent = I_TRUE;
                  }
									/* Mantis 12264 END*/
                  
                  LOG_PRINT(LOG_DEBUG,"HandlingAlarm: Updating DSP Object Details");
                  updateDspObjDetails(gDspInfo,MAX_DSP);
                  

                  if(gCfgStandbyToActive == I_TRUE)
                  {
					 sendAddCbServerForAllServersToCbsh();//Added AmitG. 8-July-2016 for CBSH 
                     sendBpmIccEicTrunkPortStsReq(ICCSELFCARD);
                  }

                  sendBpmIccEicTrunkPortStsReq(EIC0_CARD);
                  sendBpmIccEicTrunkPortStsReq(EIC1_CARD);
                  initializingCfg();
                  if(recAlarmPtr->key4 == CARDSTATE_ACTIVE)
                  {
                     populateCardStateChangeTable(recAlarmPtr);
                     /*External Alarm Changes Start*/
                     sendAllValidExtInputAssignmentToBPM();
                     sendAllValidExtOutputAssignmentToBPM();
                     //sendAllExtInputPortStatusReq();
                     /*External Alarm Changes End*/
                  }
                  makeCopyOfAlarm();
                  cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                  DalocOrdBuf((I_Void *)gCfgAlarmBuf);
                  gCfgAlarmBuf = NULL;
									/*Change done for mantis #32181 Gaurav Sinha 20 Oct 2016*/
									if(gAipSSPRcvd == TRUE)
									{
									  LOG_PRINT(DEBUG,"IP_BSC_STACK: gAipSSPRcvd found TRUE: Proceeding for SSP procedure");
									 	getAInterfaceOprState(&oprStateAInterface);
									 	if(oprStateAInterface == ENABLED) /* Check added for Mantis 2284 */
									 	{
									 		 /* Send OAMS_CFG_GRHM_LOCK_REQ */
									 		 setAinterfaceTableOperationalState(DISABLED);
									 		 /*gAinterfaceUPDownFlag = TRUE; commented during fix for 2284 - no use of this updown flag */
									 		 OamsCfgGrhmLockReqBuff.objectId=0;
									 		 OamsCfgGrhmLockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
									 		 OamsCfgGrhmLockReqBuff.reason = OAMS_RSN_AINTERFACEDOWN;
									 		 cfgSendMessage(&OamsCfgGrhmLockReqBuff, sizeof(OamsCfgGrhmLockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_LOCK_REQ, 0);                  
									 		 /* send CellBar Acess to CELLH and PSCH for all unlocked cells */
									 		 //sendCellBarAccessToCells(LockProcedure,OAMS_RSN_AINTERFACEDOWN);
									 		 /*Cell Bar Access is sent After receiving GRHM_LOCK_RESP from
									 		 GRHM */
									 		 gAifMsgSentToGrhm = OAMS_CFG_GRHM_LOCK_REQ;
									 	}
									 	else
									 	{
									 		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: A interface is already Disabled");               
									 	}
									 }
									/*Change done for mantis #32181 Gaurav Sinha 20 Oct 2016*/
               }
							 else if(recAlarmPtr->key4 == CARDSTATE_OUT_OF_SERVICE)
							 {
									LOG_PRINT(DEBUG,"State of SelfCard of %d slotid is OUT_OF_SERVICE",recAlarmPtr->key2);
									IccCardInfoTableApi *iccCardDetails = NULL;
									IccCardInfoTableApi *tmpIccCardPtr = NULL;
									I_U32 outRows,i=0;
									I_U16 outSize;
							 
									cardSetOperConStateRespHandler(recAlarmPtr->key2,
												CARDSTATE_OUT_OF_SERVICE,OPERATION_SUCCESS);
							 }
              break;

             case INFO_CARD_EJECTED_PM_OAM:
               LOG_PRINT(LOG_DEBUG,"Alarm Received::  INFO_CARD_EJECTED_PM_OAM");               
               gCfgAlarmIdRcvd = INFO_CARD_EJECTED_PM_OAM;
               trunkAlarms = 1;res = FALSE;
               LOG_PRINT(LOG_DEBUG,"CFG will delete EIC Card entry.");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;

               deleteEicCardDetails();
               //sendPresentCardInfoReq();
               break;

             case INFO_CARD_INSERTED_PM_OAM:
               LOG_PRINT(LOG_DEBUG,"Alarm Received::  INFO_CARD_INSERTED_PM_OAM");               
               trunkAlarms = 1;res = FALSE;
               makeCopyOfAlarm();
               sendPresentCardInfoReq();
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;

             case INFO_PEER_INSERTED_PM_OAM:
               LOG_PRINT(LOG_DEBUG,"Alarm Received::  INFO_PEER_INSERTED_PM_OAM");               
							 LOG_PRINT(LOG_INFO,"FrameId = %d Slot Id = %d",recAlarmPtr->key1,recAlarmPtr->key2);
               trunkAlarms = 1;res = FALSE;
               makeCopyOfAlarm();
/* 9313 STARTS*/
	 if(getallIccCardInfoTable(&iccCardInfoTableApiPtr, &outRows, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteIccCardDetails: No Row in Icc Card Info Table");
      return;
   }
   if(outRows == 1)
   {
      LOG_PRINT(LOG_INFO,"deleteIccCardDetails: Exiting from function");
      free(iccCardInfoTableApiPtr);
      return;
   }
   if(iccCardInfoTableApiPtr->slotId != recAlarmPtr->key2)
   {
      LOG_PRINT(LOG_DEBUG,"deleteIccCardDetails: Slot Id:: %d in firstRow",iccCardInfoTableApiPtr->slotId);
      iccCardInfoTableIndices.slotId = iccCardInfoTableApiPtr->slotId;
   }
   else
   {
      tmpIccCardPtr = (IccCardInfoTableApi *)((I_U8 *)iccCardInfoTableApiPtr + outSize);
      LOG_PRINT(LOG_DEBUG,"deleteIccCardDetails: Slot Id:: %d in secondRow",tmpIccCardPtr->slotId);
      iccCardInfoTableIndices.slotId = tmpIccCardPtr->slotId;
      
   }
   iccCardInfoTableIndices.chasisFrameId = recAlarmPtr->key1;
   LOG_PRINT(LOG_INFO,"deleteIccCardDetails:To be deleted Frame Id:: %d and Slot Id:: %d ",iccCardInfoTableIndices.chasisFrameId , iccCardInfoTableIndices.slotId);

		
   if( getIccCardInfoTable(&iccCardInfoTableIndices,&outDataIcc) != CLIB_SUCCESS) 
   {
      LOG_PRINT(DEBUG,"getEicCardInfoTable failed for frameid(%d) slotid(%d)",
           iccCardInfoTableIndices.chasisFrameId, iccCardInfoTableIndices.slotId );
      return ;
   } 
   
   outDataIcc->physicalPresenceState = PRESENT;
   outDataIcc->cardOperationalState = CARDSTATE_DEFAULT;
   
   if(updateIccCardInfoTable(outDataIcc) != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"updateIccCardInfoTable failed for frameid(%d) slotid(%d)",
           iccCardInfoTableIndices.chasisFrameId, iccCardInfoTableIndices.slotId );
      free(outDataIcc);
      return ;
   }

							 /* Mantis 9313 ENDS*/




               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               sendPresentCardInfoReq();
               break;
             case INFO_PEER_EJECTED_PM_OAM:
               LOG_PRINT(LOG_DEBUG,"Alarm Received::  INFO_PEER_EJECTED_PM_OAM");               
               trunkAlarms = 1;res = FALSE;
               LOG_PRINT(LOG_DEBUG,"CFG will delete ICC Card entry.");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               deleteIccCardDetails();
               //sendPresentCardInfoReq();
               break;
             case INFO_CLOCK_CHANGE_PM_OAM:
             case INFO_CLOCK_FAIL_PM_OAM:
             case INFO_CLOCK_RECOVERED_PM_OAM:
               updateSystemClockDetails();
               clkRef = recAlarmPtr->key3;
               recAlarmPtr->key3 = recAlarmPtr->key4;
               recAlarmPtr->key4 = clkRef;
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;
               /*Mantis Id 28077 start */
               if(recAlarmPtr->sysalarmId == INFO_CLOCK_CHANGE_PM_OAM)
               {
                  setClkSrcProcState(clkSrcCfgNone);
               }
               /*Mantis Id 28077 end */
               break;              
              case INFO_CLOCK_MULTIPLE_SRCS_IN_CONFIG_DATA_PM_OAM:
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
 
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
							 gCfgAlarmBuf = NULL;
              break;  
             case INFO_BPM_EIC_DISCONNECTED :
               res = ChkActiveCardAlarm(recAlarmPtr->key1,recAlarmPtr->key3);
              
               if(res == TRUE)
               {
                  LOG_PRINT(LOG_DEBUG,"Alarm Received:: INFO_BPM_EIC_DISCONNECTED chasisFrameId [%d] SlotId [%d]",recAlarmPtr->key1,recAlarmPtr->key2);  
                  LOG_PRINT(LOG_DEBUG,"CFG will delete EIC Card entry.");
                  if( getEicSwStatusFromSwMNodeTable(SYS_NODE_TYPE_EIC, swStatus, &count) != CLIB_SUCCESS)
                  {
                     LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable call is getting failed.."); 
                     return;
                  }
                  if ( swStatus[0] ==  SW_ACTIVATION_IN_PROGRESS || swStatus[1] ==  SW_ACTIVATION_IN_PROGRESS)
                  {
                      LOG_PRINT(LOG_DEBUG,"Not deleteing Entry as ACTIVATION_IN_PROGRESS for EIC.");
                  }
                  else
                  {
                     makeCopyOfAlarm();
                     cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                     DalocOrdBuf((I_Void *)gCfgAlarmBuf);
                     gCfgAlarmBuf = NULL;
                     deleteEicCardDetails();
                   
                  }
               } 
               break;
             /* CS4.0: EIC related alarms End*/

             /*BSC R2.0 Changes Starts*/  
						 case INFO_BPM_DSP_DOWN :
 						   LOG_PRINT(LOG_DEBUG,"DSP Down message received");		
               dspDownAlarmHandler(); 
						 break;		

						 case INFO_BPM_DSP_RESET_FAILURE:
 						   LOG_PRINT(LOG_DEBUG,"INFO_BPM_DSP_RESET_FAILURE alarm received");		
               dspResetFailAlarmHandler(); 
						 break;		
             
             case INFO_TDM_FAIL_B_CARD_0_STREAM_PM_OAM     :
             case INFO_TDM_FAIL_B_CARD_1_STREAM_PM_OAM     :
             case INFO_TDM_FAIL_B_CARD_2_STREAM_PM_OAM     :
             case INFO_TDM_FAIL_B_CARD_3_STREAM_PM_OAM     :
             case INFO_TDM_FAIL_B_CARD_4_STREAM_PM_OAM     :
             case INFO_TDM_FAIL_B_CARD_5_STREAM_PM_OAM     :
             case INFO_TDM_FAIL_E1C0_STREAM_0_PM_OAM       :
             case INFO_TDM_FAIL_E1C0_STREAM_1_PM_OAM       :
             case INFO_TDM_FAIL_E1C1_STREAM_0_PM_OAM       :
             case INFO_TDM_FAIL_E1C1_STREAM_1_PM_OAM       :
             case INFO_TDM_FAIL_DSP_STREAM_0_PM_OAM        :
             case INFO_TDM_FAIL_DSP_STREAM_1_PM_OAM        :
             case INFO_TDM_FAIL_PP_STREAM_PM_OAM           :
             case INFO_TDM_FAIL_PP_COPY_STREAM_PM_OAM      :
             case INFO_TDM_FAIL_TEST_0_STREAM_PM_OAM       :
             case INFO_TDM_FAIL_TEST_1_STREAM_PM_OAM       :
             case INFO_TDM_FAIL_TEST_2_STREAM_PM_OAM       :
             case INFO_TDM_FAIL_TEST_3_STREAM_PM_OAM       :
             case INFO_TDM_FAIL_CPLD_RSV_STREAM_PM_OAM     :
             case INFO_TDM_FAIL_ICC_SF1_STREAM_PM_OAM      :
             case INFO_TDM_FAIL_ICC_SF2_STREAM_PM_OAM      :
             case INFO_TDM_FAIL_E_CARD_STREAM_PM_OAM       :
             case INFO_TDM_FAIL_TTC1_STREAM_PM_OAM         :
             case INFO_TDM_FAIL_TTC2_STREAM_PM_OAM         :
             case INFO_TDM_FAIL_TTC3_0_STREAM_PM_OAM       :
             case INFO_TDM_CHANGE_B_CARD_0_STREAM_PM_OAM   :
             case INFO_TDM_CHANGE_B_CARD_1_STREAM_PM_OAM   :
             case INFO_TDM_CHANGE_B_CARD_2_STREAM_PM_OAM   :
             case INFO_TDM_CHANGE_B_CARD_3_STREAM_PM_OAM   :
             case INFO_TDM_CHANGE_B_CARD_4_STREAM_PM_OAM   :
             case INFO_TDM_CHANGE_B_CARD_5_STREAM_PM_OAM   :
             case INFO_TDM_CHANGE_E1C0_STREAM_0_PM_OAM     :
             case INFO_TDM_CHANGE_E1C0_STREAM_1_PM_OAM     :
             case INFO_TDM_CHANGE_E1C1_STREAM_0_PM_OAM     :
             case INFO_TDM_CHANGE_E1C1_STREAM_1_PM_OAM     :
             case INFO_TDM_CHANGE_DSP_STREAM_0_PM_OAM      :
             case INFO_TDM_CHANGE_DSP_STREAM_1_PM_OAM      :
             case INFO_TDM_CHANGE_PP_STREAM_PM_OAM         :
             case INFO_TDM_CHANGE_PP_COPY_STREAM_PM_OAM    :
             case INFO_TDM_CHANGE_TEST_0_STREAM_PM_OAM     :
             case INFO_TDM_CHANGE_TEST_1_STREAM_PM_OAM     :
             case INFO_TDM_CHANGE_TEST_2_STREAM_PM_OAM     :
             case INFO_TDM_CHANGE_TEST_3_STREAM_PM_OAM     :
             case INFO_TDM_CHANGE_CPLD_RSV_STREAM_PM_OAM   :
             case INFO_TDM_CHANGE_ICC_SF1_STREAM_PM_OAM    :
             case INFO_TDM_CHANGE_ICC_SF2_STREAM_PM_OAM    :
             case INFO_TDM_CHANGE_E_CARD_STREAM_PM_OAM     :
             case INFO_TDM_CHANGE_TTC1_STREAM_PM_OAM       :
             case INFO_TDM_CHANGE_TTC2_STREAM_PM_OAM       :
             case INFO_TDM_CHANGE_TTC3_0_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_B_CARD_0_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_B_CARD_1_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_B_CARD_2_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_B_CARD_3_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_B_CARD_4_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_B_CARD_5_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_E1C0_STREAM_0_PM_OAM       :
             case INFO_TDM_RECOVERED_E1C0_STREAM_1_PM_OAM       :
             case INFO_TDM_RECOVERED_E1C1_STREAM_0_PM_OAM       :
             case INFO_TDM_RECOVERED_E1C1_STREAM_1_PM_OAM       :
             case INFO_TDM_RECOVERED_DSP_STREAM_0_PM_OAM        :
             case INFO_TDM_RECOVERED_DSP_STREAM_1_PM_OAM        :
             case INFO_TDM_RECOVERED_PP_STREAM_PM_OAM           :
             case INFO_TDM_RECOVERED_PP_COPY_STREAM_PM_OAM      :
             case INFO_TDM_RECOVERED_TEST_0_STREAM_PM_OAM       :
             case INFO_TDM_RECOVERED_TEST_1_STREAM_PM_OAM       :
             case INFO_TDM_RECOVERED_TEST_2_STREAM_PM_OAM       :
             case INFO_TDM_RECOVERED_TEST_3_STREAM_PM_OAM       :
             case INFO_TDM_RECOVERED_CPLD_RSV_STREAM_PM_OAM     :
             case INFO_TDM_RECOVERED_ICC_SF1_STREAM_PM_OAM      :
             case INFO_TDM_RECOVERED_ICC_SF2_STREAM_PM_OAM      :
             case INFO_TDM_RECOVERED_E_CARD_STREAM_PM_OAM       :
             case INFO_TDM_RECOVERED_TTC1_STREAM_PM_OAM         :
             case INFO_TDM_RECOVERED_TTC2_STREAM_PM_OAM         :
             case INFO_TDM_RECOVERED_TTC3_0_STREAM_PM_OAM       :
             case INFO_BPM_DSP_CAPACITY_PROB                    :
             case INFO_BPM_DSP_TDM_SYNC_LOSS                    :
             case INFO_BPM_DSP_TDM_ERR_CALLBACK                 :
             case INFO_BPM_DSP_TRAU_CAP_MAX_DL                  :
             case INFO_BPM_DSP_TRAU_CAP_MAX_UL                  :
             case INFO_BPM_DSP_ERR_TX_FULL                      :
             case INFO_BPM_DSP_ERR_HEARTBEAT                    :
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
               LOG_PRINT(DEBUG,"AlarmIdRcvd:%d, ObjType Filled:%d",
                   recAlarmPtr->sysalarmId, recAlarmPtr->info3);
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
             break;
   
             case INFO_SF_E1_LOSSI_PM_OAM     :
             case INFO_SF_E1_RAII_PM_OAM      :
             case INFO_SF_E1_YI_PM_OAM        :
             case INFO_SF_E1_PECI_PM_OAM      :
             case INFO_SF_E1_PECOI_PM_OAM     :
             case INFO_SF_E1_CECI_PM_OAM      :
             case INFO_SF_E1_CECOI_PM_OAM     :
             case INFO_SF_E1_SLCI_PM_OAM      :
             case INFO_SF_E1_EECI_PM_OAM      :
             case INFO_SF_E1_EECOI_PM_OAM     :
             case INFO_SF_E1_VECI_PM_OAM      :
             case INFO_SF_E1_VECOI_PM_OAM     :
             case INFO_SF_E1_BECI_PM_OAM      :
             case INFO_SF_E1_BECOI_PM_OAM     :
             case INFO_SF_T1_TFSYNCI_PM_OAM   :
             case INFO_SF_T1_PRBSI_PM_OAM     :
             case INFO_SF_T1_PRBSOI_PM_OAM    :
             case INFO_SF_T1_MFOOFI_PM_OAM    :
             case INFO_SF_T1_MFOOFOI_PM_OAM   :
             case INFO_SF_T1_BPVI_PM_OAM      :
             case INFO_SF_T1_BPVOI_PM_OAM     :
             case INFO_SF_T1_FBEI_PM_OAM      :
             case INFO_SF_T1_FBEOI_PM_OAM     :
             case INFO_SF_T1_COFAI_PM_OAM     :
             case INFO_SF_T1_COFAOI_PM_OAM    :
             case INFO_SF_T1_CRCI_PM_OAM      :
             case INFO_SF_T1_CRCOI_PM_OAM     :
             case INFO_SF_T1_OOFOI_PM_OAM     :
             case INFO_SF_T1_EXZI_PM_OAM      :
             case INFO_SF_T1_EXZOI_PM_OAM     :
             case INFO_NIC_FRAMER_TFSYN_PM_OAM        :
             case INFO_NIC_FRAMER_D4YALM_PM_OAM		    :
             case INFO_NIC_FRAMER_D4Y48_PM_OAM    	  :
             case INFO_NIC_FRAMER_ESFYEL_PM_OAM 		  :
             case INFO_NIC_FRAMER_T1DMY_PM_OAM    	  :
             case INFO_NIC_FRAMER_PRBS_PM_OAM		      :
             case INFO_NIC_FRAMER_PRBSMF_PM_OAM		    :
             case INFO_NIC_FRAMER_MFOOF_PM_OAM		    :
             case INFO_NIC_FRAMER_FBE_PM_OAM 		      :
             case INFO_NIC_FRAMER_BPV_PM_OAM		      :
             case INFO_NIC_FRAMER_CRC_PM_OAM   		    :
             case INFO_NIC_FRAMER_OOF_PM_OAM		      :
             case INFO_NIC_FRAMER_COFA_PM_OAM		      :
             case INFO_NIC_FRAMER_EXZ_PM_OAM 		      :
             case INFO_NIC_FRAMER_PRBSO_PM_OAM        :
             case INFO_NIC_FRAMER_PRBSMFO_PM_OAM 		  :
             case INFO_NIC_FRAMER_MFOOFO_PM_OAM    	  :
             case INFO_NIC_FRAMER_FBEO_PM_OAM		      :
             case INFO_NIC_FRAMER_BPVO_PM_OAM		      :
             case INFO_NIC_FRAMER_CRCO_PM_OAM		      :
             case INFO_NIC_FRAMER_OOFO_PM_OAM		      :
             case INFO_NIC_FRAMER_COFAO_PM_OAM        :
             case INFO_NIC_FRAMER_EXZO_PM_OAM         :
             case INFO_NIC_FRAMER_LOSSI_PM_OAM 		    :
             case INFO_NIC_FRAMER_RAII_PM_OAM		      :
             case INFO_NIC_FRAMER_Y_PM_OAM		        :
             case INFO_NIC_FRAMER_PEC_PM_OAM          :
             case INFO_NIC_FRAMER_SLC_PM_OAM		      :
             case INFO_NIC_FRAMER_EEC_PM_OAM		      :
             case INFO_NIC_FRAMER_VEC_PM_OAM		      :
             case INFO_NIC_FRAMER_CEC_PM_OAM 		      :
             case INFO_NIC_FRAMER_BEC_PM_OAM		      :
             case INFO_NIC_FRAMER_FEC_PM_OAM 		      :
             case INFO_NIC_FRAMER_PEO_PM_OAM 		      :
             case INFO_NIC_FRAMER_PCO_PM_OAM    		  :
             case INFO_NIC_FRAMER_SLO_PM_OAM		      :
             case INFO_NIC_FRAMER_EEO_PM_OAM		      :
             case INFO_NIC_FRAMER_VEO_PM_OAM		      :
             case INFO_NIC_FRAMER_CEO_PM_OAM 		      :
             case INFO_NIC_FRAMER_BEO_PM_OAM    		  :
             case INFO_NIC_FRAMER_FEO_PM_OAM		      :
             case INFO_MFRAMER_R_ELASTIC_STORE_FULL_PM_OAM      :
             case INFO_MFRAMER_R_ELASTIC_STORE_SLIP_PM_OAM         :
             case INFO_MFRAMER_R_ELASTIC_STORE_EMPTY_PM_OAM        :
             case INFO_MFRAMER_T_ELASTIC_STORE_FULL_PM_OAM         :
             case INFO_MFRAMER_T_ELASTIC_STORE_SLIP_PM_OAM         :
             case INFO_MFRAMER_T_ELASTIC_STORE_EMPTY_PM_OAM        :
             case INFO_MFRAMER_R_SIG_ALL_ZEROS_PM_OAM              :
             case INFO_MFRAMER_R_SIG_ALL_ONES_PM_OAM               :
             case INFO_MFRAMER_R_CRC4_MULTIFRAME_PM_OAM            :
             case INFO_MFRAMER_R_ALIGN_FRAME_PM_OAM                :
             case INFO_MFRAMER_R_SIGNALLING_STATE_CHANGE_PM_OAM    :
             case INFO_MFRAMER_TIMER_PM_OAM                        :
             case INFO_MFRAMER_ONE_SECOND_TIMER_PM_OAM             :
             case INFO_MFRAMER_R_MULTIFRAME_PM_OAM                 :
             case INFO_MFRAMER_R_FIFO_OVERRUN_PM_OAM               :
             case INFO_MFRAMER_R_HDLC_OPENING_BYTE_PM_OAM          :
             case INFO_MFRAMER_R_PACKET_END_PM_OAM                 :
             case INFO_MFRAMER_R_PACKET_START_PM_OAM               :
             case INFO_MFRAMER_R_PACKET_HIGH_WATERMARK_PM_OAM      :
             case INFO_MFRAMER_R_FIFO_NOT_EMPTY_PM_OAM             :
             case INFO_MFRAMER_R_RAI_CI_PM_OAM                     :
             case INFO_MFRAMER_R_AIS_CI_PM_OAM                     :
             case INFO_MFRAMER_R_SLC96_ALIGNMENT_PM_OAM            :
             case INFO_MFRAMER_R_FDL_RGR_FULL_PM_OAM               :
             case INFO_MFRAMER_T_SLC96_ALIGNMENT_PM_OAM            :
             case INFO_MFRAMER_T_ALIGN_FRAME_PM_OAM                :
             case INFO_MFRAMER_T_MULTIFRAME_PM_OAM                 :
             case INFO_MFRAMER_T_FDL_RGR_EMPTY_PM_OAM              :
             case INFO_MFRAMER_T_FIFO_UNDERRUN_PM_OAM              :
             case INFO_MFRAMER_T_MSG_END_PM_OAM                    :
             case INFO_MFRAMER_T_FIFO_BELOW_LOW_WATERMARK_PM_OAM   :
             case INFO_MFRAMER_T_FIFO_NOT_FULL_SET_PM_OAM          :
             case INFO_MFRAMER_BERT_R_ALL_ZEROS_PM_OAM             :
             case INFO_MFRAMER_BERT_R_ALL_ONES_PM_OAM              :
             case INFO_MFRAMER_BERT_BIT_ERR_DETECTED_PM_OAM        :
             case INFO_MFRAMER_BERT_BIT_COUNTER_OVRFLOW_PM_OAM     :
             case INFO_MFRAMER_BERT_ERR_COUNTER_OVRFLOW_PM_OAM     :
             case INFO_MFRAMER_LOSS_OF_FRAME_SYNC_PM_OAM           :
             case INFO_MFRAMER_R_RAI_PM_OAM                        :
             case INFO_MFRAMER_R_AC_PM_OAM                         :
             case INFO_MFRAMER_R_CLOCK_LOSS_PM_OAM                 :
             case INFO_MFRAMER_SCDC_PM_OAM                         :
             case INFO_MFRAMER_LOOP_DOWN_DETECT_PM_OAM             :
             case INFO_MFRAMER_V52_LINK_DETECT_PM_OAM              :
             case INFO_MFRAMER_LOOP_UP_DETECT_PM_OAM               :
             case INFO_MFRAMER_R_DISTANT_MF_ALARM_DETECT_PM_OAM    :
             case INFO_MFRAMER_JALT_PM_OAM                         :
             case INFO_MFRAMER_OPEN_CIRCUIT_DETECT_PM_OAM          :
             case INFO_MFRAMER_SHORT_CIRCUIT_DETECT_PM_OAM         :
             case INFO_MFRAMER_R_BOC_PM_OAM                        :
             case INFO_MFRAMER_T_CLOCK_LOSS_PM_OAM                 :
             case INFO_MFRAMER_BERT_LOSS_SYNC_PM_OAM               :
             case INFO_MFRAMER_R_RAI_CLR_PM_OAM                    :
             case INFO_MFRAMER_R_AC_CLR_PM_OAM                     :
             case INFO_MFRAMER_R_CLOCK_LOSS_CLR_PM_OAM             :
             case INFO_MFRAMER_SCDC_CLR_PM_OAM                     :
             case INFO_MFRAMER_LOOP_DOWN_DETECT_CLR_PM_OAM         :
             case INFO_MFRAMER_V52_LINK_DETECT_CLR_PM_OAM          :
             case INFO_MFRAMER_LOOP_UP_DETECT_CLR_PM_OAM           :
             case INFO_MFRAMER_R_DISTANT_MF_ALARM_DETECT_CLR_PM_OAM:
             case INFO_MFRAMER_JALT_CLR_PM_OAM                     :
             case INFO_MFRAMER_OPEN_CIRCUIT_DETECT_CLR_PM_OAM      :
             case INFO_MFRAMER_SHORT_CIRCUIT_DETECT_CLR_PM_OAM     :
             case INFO_MFRAMER_R_BOC_CLR_PM_OAM                    :
             case INFO_MFRAMER_T_CLOCK_LOSS_CLR_PM_OAM             :
             case INFO_MFRAMER_BERT_IN_SYNC_PM_OAM                 :
               FillObjTypeFromSlotId(recAlarmPtr->key2, 
                              recAlarmPtr->info3);
               LOG_PRINT(DEBUG,"AlarmIdRcvd:%d, ObjType Filled:%d",
                   recAlarmPtr->sysalarmId, recAlarmPtr->info3);
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
             break;  
             /*Changes R2.3.4 Starts*/
             case INFO_PSU_CARD_EJECTED :
               LOG_PRINT(DEBUG,"INFO_PSU_CARD_EJECTED Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               deletePsuCardDetails();
             break; 

             case INFO_PSU_CARD_INSERTED :
               LOG_PRINT(DEBUG,"INFO_PSU_CARD_INSERTED Alarm received");
               gCfgAlarmIdRcvd = INFO_PSU_CARD_INSERTED;
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               sendPresentCardInfoReq();
             break; 

             case INFO_PSU_CARD_FAILED :
               LOG_PRINT(DEBUG,"INFO_PSU_CARD_FAILED Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               if (markPsuCardFailed() == 0)
               {
                  LOG_PRINT(DEBUG,"markPsuCardFailed success");
               } 
               else
               { 
                  LOG_PRINT(DEBUG,"markPsuCardFailed failed");
               } 
             break; 
             
             case INFO_PSU_CARD_COMM_FAILED :
               LOG_PRINT(DEBUG,"INFO_PSU_CARD_COMM_FAILED Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break; 
             
             case INFO_PSU_CARD_COMM_RESTORED :
               LOG_PRINT(DEBUG,"INFO_PSU_CARD_COMM_RESTORED Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break; 
             
             case INFO_FAN_TRAY_EJECTED :
               LOG_PRINT(DEBUG,"INFO_FAN_TRAY_EJECTED Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               deleteFanTrayDetails();
             break; 
             
             case INFO_FAN_TRAY_INSERTED :
               LOG_PRINT(DEBUG,"INFO_FAN_TRAY_INSERTED Alarm received");
               gCfgAlarmIdRcvd = INFO_FAN_TRAY_INSERTED;
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               sendPresentCardInfoReq();
             break; 
             
             case INFO_FAN_FAILED :
               LOG_PRINT(DEBUG,"INFO_FAN_FAILED Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               if(markFanFailed() == 0)
               { 
                 LOG_PRINT(DEBUG,"markFanFailed success");
               }
               else
               { 
                 LOG_PRINT(DEBUG,"markFanFailed failed");
               } 
             break; 

             case INFO_FAN_RESTORED :
               LOG_PRINT(DEBUG,"INFO_FAN_RESTORED Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
               if(markFanRunning() == 0)
               { 
                 LOG_PRINT(DEBUG,"markFanRuning success");
               }
               else
               { 
                 LOG_PRINT(DEBUG,"markFanRuning failed");
               } 
             break; 
            /*Changes For R2.3.4 Ends*/

            /*Changes For Mantis 16678 Starts*/
             case ALARM_PTRX_ENABLED :
               if(gCfgStandbyToActiveforCbsh==I_TRUE)
               {
               LOG_PRINT(DEBUG,"PTRX_ENABLED Alarm received for SO Case with TrxId %d",recAlarmPtr->key2);    
               if(checkBcchTrx(recAlarmPtr->key2,&cellNonPerOutData)==CLIB_SUCCESS)
                 {  
                 sendCellOprStateToCbsh(cellNonPerOutData->cellId,cellNonPerOutData->lac,CAUSE_CELL_ENABLED);  
                 free(cellNonPerOutData); 
                 }
               }
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm),
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
             break;   
            
             case INFO_RMON_NAND_USAGE_EXCEED_SHUTDOWN:
               LOG_PRINT(DEBUG," Alarm %s received",mkstr(INFO_RMON_NAND_USAGE_EXCEED_SHUTDOWN));
               NAND_ALARM_HANDLE();
               break;
             case INFO_RMON_NAND_USAGE_EXCEED_CRITICAL:
               LOG_PRINT(DEBUG," Alarm %s received",mkstr(INFO_RMON_NAND_USAGE_EXCEED_CRITICAL));
               NAND_ALARM_HANDLE();
               break;
             case INFO_RMON_NAND_USAGE_EXCEED_MAJOR:
               LOG_PRINT(DEBUG," Alarm %s received",mkstr(INFO_RMON_NAND_USAGE_EXCEED_MAJOR));
               NAND_ALARM_HANDLE();
               break;
             case INFO_RMON_NAND_USAGE_CLEAR_SHUTDOWN:
               LOG_PRINT(DEBUG," Alarm %s received",mkstr(INFO_RMON_NAND_USAGE_CLEAR_SHUTDOWN));
               NAND_ALARM_HANDLE();
               break;
             case INFO_RMON_NAND_USAGE_CLEAR_CRITICAL:
               LOG_PRINT(DEBUG," Alarm %s received",mkstr(INFO_RMON_NAND_USAGE_CLEAR_CRITICAL));
               NAND_ALARM_HANDLE();
               break;
             case INFO_RMON_NAND_USAGE_CLEAR_MAJOR : 
               LOG_PRINT(DEBUG," Alarm %s received",mkstr(INFO_RMON_NAND_USAGE_CLEAR_MAJOR));
               NAND_ALARM_HANDLE();
               break;
            /*Changes For Mantis 16678 Ends*/
             case INFO_MC_EXT_INPUT_PORT_STATUS_PM_OAM:
               LOG_PRINT(DEBUG," Alarm %s received",mkstr(INFO_MC_EXT_INPUT_PORT_STATUS_PM_OAM));
               LOG_PRINT(DEBUG,"External Input on ChasisFrameId [%d],SlotId [%d],PortId [%d],PortStatus [%d]",recAlarmPtr->key1,recAlarmPtr->key2,recAlarmPtr->key3,recAlarmPtr->key4);
               ExternalInputPortConfigTableApi *extInputPortConfigTableApiPtr=NULL;
               ExternalInputPortStatusTableApi extInputPortStatusTableApi;
               I_U32 retStatus;
               I_S32 dbStatus;
               ExternalInputPortConfigTableIndices extInputPortConfigIndex;

               extInputPortConfigIndex.extInputPortId=recAlarmPtr->key3;
               dbStatus = getExternalInputPortConfigTable(&extInputPortConfigIndex, &extInputPortConfigTableApiPtr);
               if(dbStatus ==DBLIB_SUCCESS)
               {
                 /*Mantis 24748 Start*/
                 if(extInputPortConfigTableApiPtr->assignedState != EXT_PORT_FREE)
                 {
                   extInputPortStatusTableApi.extInputPortId=extInputPortConfigTableApiPtr->extInputPortId;
                   extInputPortStatusTableApi.extInputPortState=recAlarmPtr->key4;
                   dbStatus=updateExternalInputPortStatusTable(&extInputPortStatusTableApi);
                   if(DBLIB_SUCCESS != dbStatus)
                   {
                     LOG_PRINT(DEBUG,"updateExternalInputPortStatusTable Failed,\
                         Trying to insert a row in ExternalInputPortStatusTable");
                   }
                   else
                   {
                     LOG_PRINT(DEBUG,"updateExternalInputPortStatusTable Success");
                   }
                   retStatus=sendExtInputAlarmToOMC(extInputPortConfigTableApiPtr->extInputPortId,
                       recAlarmPtr->key4,
                       extInputPortConfigTableApiPtr->extInputPortAlarmCondition,
                       (const I_CHAR*)extInputPortConfigTableApiPtr->extAlarmText,
                       extInputPortConfigTableApiPtr->extAlarmSeverity);
                 }
                 else
                 {
                   LOG_PRINT(DEBUG,"Port is FREE, will not raise Alarm or update Port status");
                 }
                 /*Mantis 24748 End*/
                 free(extInputPortConfigTableApiPtr);
               }
               break;
             /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
              /*ALARMS ON OBJECT_TYPE_OBM STARTS*/
             case INFO_SELF_CARD_HARD_RESET_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_SELF_CARD_HARD_RESET_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break;
 
             case INFO_HOT_SWAP_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_HOT_SWAP_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break; 
             
							case INFO_FAN_FAULTED_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_FAN_FAULTED_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               updateFanStatusInObmCardInfoTableApi(recAlarmPtr,FAULTED);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break;
 
							case INFO_FAN_RECOVERED_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_FAN_RECOVERED_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               updateFanStatusInObmCardInfoTableApi(recAlarmPtr,WORKING);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break;
 
							case INFO_VCC_3P3_FAIL_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_VCC_3P3_FAIL_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break;
				 
							case INFO_VCC_3P3_GOOD_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_VCC_3P3_GOOD_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
             break;
 
							case INFO_MATE_CARD_JACK_IN_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_MATE_CARD_JACK_IN_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               //updatePhysicalPresenceStateInObmCardInfoTableApi(recAlarmPtr);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 send1UCardInfoReqToOil();
             break;
 
							case INFO_MATE_CARD_JACK_OUT_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_MATE_CARD_JACK_OUT_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               //deleteEntryFromObmCardInfoTableApi(recAlarmPtr);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 send1UCardInfoReqToOil();
							 break;
						
							case INFO_MATE_POWER_GOOD_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_MATE_POWER_GOOD_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	      		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
							UpdatePowerStatusObmMateCard(recAlarmPtr,GOOD);
	      		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
	             break;

							case INFO_MATE_POWER_FAIL_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_MATE_POWER_FAIL_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
	       			UpdatePowerStatusObmMateCard(recAlarmPtr,FAIL);
	       		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
	             break;

							case INFO_TEMP_INLET_WARINING_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_INLET_WARINING_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,INLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
	             break;

							case INFO_TEMP_INLET_MAJOR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_INLET_MAJOR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,INLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_INLET_CRITICAL_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_INLET_CRITICAL_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,INLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_OUTLET_WARNING_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_OUTLET_WARNING_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,OUTLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_OUTLET_MAJOR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_OUTLET_MAJOR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,OUTLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_OUTLET_CRITICAL_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_OUTLET_CRITICAL_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,OUTLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_INLET_WARINING_CLEAR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_INLET_WARINING_CLEAR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,INLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_INLET_MAJOR_CLEAR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_INLET_MAJOR_CLEAR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,INLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_OUTLET_WARNING_CLEAR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_OUTLET_WARNING_CLEAR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,OUTLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_OUTLET_MAJOR_CLEAR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_OUTLET_MAJOR_CLEAR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               UpdateTemperatureObmCard(recAlarmPtr,OUTLET_MODULE);
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;
              /*ALARMS ON OBJECT_TYPE_OBM ENDS*/
              /*ALARMS ON OBJECT_TYPE_OBF STARTS*/
							case INFO_OBF_PRESENT_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_OBF_PRESENT_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               //updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi(recAlarmPtr,ONE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 send1UCardInfoReqToOil();
							 break;

							case INFO_OBF_ABSENT_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_OBF_ABSENT_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi(recAlarmPtr,THREE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_POWER_FEED_PRESNT_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_POWER_FEED_PRESNT_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi(recAlarmPtr,ONE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_POWER_FEED_ABSENT_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_POWER_FEED_ABSENT_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi(recAlarmPtr,ONE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;
              /*ALARMS ON OBJECT_TYPE_OBF STARTS*/
              /*ALARMS ON OBJECT_TYPE_FANFILTER STARTS*/
							case INFO_FAN_FILTER_PRESENT_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_FAN_FILTER_PRESENT_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               UpdateFanFilterIdTableApi(recAlarmPtr);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_FAN_FILTER_ABSENT_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_FAN_FILTER_ABSENT_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               UpdateFanFilterIdTableApi(recAlarmPtr);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;
              /*ALARMS ON OBJECT_TYPE_FANFILTER STARTS*/
            /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
							case INFO_TEMP_IMX_WARNING_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_IMX_WARNING_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               UpdateTemperatureObmCard(recAlarmPtr,IMX_MODULE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_IMX_MAJOR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_IMX_MAJOR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               UpdateTemperatureObmCard(recAlarmPtr,IMX_MODULE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_IMX_CRITICAL_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_IMX_CRITICAL_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               UpdateTemperatureObmCard(recAlarmPtr,IMX_MODULE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_IMX_WARNING_CLEAR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_IMX_WARNING_CLEAR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               UpdateTemperatureObmCard(recAlarmPtr,IMX_MODULE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;

							case INFO_TEMP_IMX_MAJOR_CLEAR_PM_OAM:
               LOG_PRINT(DEBUG,"INFO_TEMP_IMX_MAJOR_CLEAR_PM_OAM Alarm received");
               makeCopyOfAlarm();
               cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               UpdateTemperatureObmCard(recAlarmPtr,IMX_MODULE);
               DalocOrdBuf((I_Void *)gCfgAlarmBuf);
               gCfgAlarmBuf = NULL;
							 break;
	       		  /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
             default :
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND.."); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
             break; 
             /*BSC R2.0 Changes Ends*/  
         } 
      break;
      case CSAPP_GRHM_CFG_ALARM_IND:
      case OAMS_SCM_CFG_ALARM_IND:
         /* CS4.0 HA Stack Changes : Start */ 
         switch ( recAlarmPtr->sysalarmId ) 
         {
            case ALARM_ID_BSC_SS7_DOWN: 
            case ALARM_ID_BSC_SS7_UP: 
            case ALARM_ID_MSC_LINKSET_OOS:   
            case ALARM_ID_MSC_LINKSET_INS:   
            case ALARM_ID_MSC_LINK_OOS:   
            case ALARM_ID_MSC_LINK_INS:   
            case ALARM_ID_DEST_UNAVAILABLE_MTP3_PAUSE:   
            case ALARM_ID_DEST_AVAILABLE_MTP3_RESUME:  
               updateStackTableStatus(); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
          
            /*Changes for MantisId: 12466 Starts*/ 
            case EVENT_BSSAP_BLOCK_IND :
            case EVENT_BSSAP_UNBLOCK_IND :
            case EVENT_BSSAP_RESET_CKT_IND :
	          case EVENT_BSSAP_CKT_RESET_ACK :
            case EVENT_BSSAP_BLOCK_ACK :
            case EVENT_BSSAP_UNBLOCK_ACK :
            case EVENT_BSSAP_BLOCK_CNF :
            case EVENT_BSSAP_UNBLOCK_CNF :
               aiftrunkSecIndex.e1Num = recAlarmPtr->key1;
               if(getSecAiftrunkTable(&aiftrunkSecIndex,&outData) != CLIB_SUCCESS)
               {
                  LOG_PRINT(DEBUG,"getSecAiftrunkTable failed for trunkId:%d", recAlarmPtr->key1);
                  return; 
               } 
                
               if(getCicTableUsingE1Ts(recAlarmPtr->key1,recAlarmPtr->key2,&cicTblPtr) != CLIB_SUCCESS)
               {
                  LOG_PRINT(DEBUG,"getCicTableUsingE1Ts failed for trunkId:%d ts:%d", 
                     recAlarmPtr->key1,recAlarmPtr->key2);
                   free(outData);
                  return; 
               } 
               
               recAlarmPtr->key1 =  outData->interfaceId;
               recAlarmPtr->key2 =  outData->tgpId;
               recAlarmPtr->key3 =  outData->e1Num;
               recAlarmPtr->key4 =  cicTblPtr->timeSlot;
               switch ( recAlarmPtr->sysalarmId ) 
               {
                 case EVENT_BSSAP_BLOCK_IND :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString ,
                    "Block Indication received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case EVENT_BSSAP_UNBLOCK_IND :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString ,
                    "Unblock Indication received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case EVENT_BSSAP_RESET_CKT_IND :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString ,
                    "ResetCkt Indication received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
	               case EVENT_BSSAP_CKT_RESET_ACK :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "ResetCkt Ack received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case EVENT_BSSAP_BLOCK_ACK :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "Block Ack received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case EVENT_BSSAP_UNBLOCK_ACK :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "Unblock Ack received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case EVENT_BSSAP_BLOCK_CNF :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "Block Cnf received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case EVENT_BSSAP_UNBLOCK_CNF :
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "Unblock Cnf received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 
               } 
               free(outData);
               free(cicTblPtr);
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            break; 
            /*Changes start for Mantis 16764 */
            case SKS_BSSAP_TIME_OUT_NO_BLOCK_ACK_RECV : 
            case SKS_BSSAP_TIME_OUT_NO_UNBLOCK_ACK_RECV : 
            case SKS_BSSAP_TIME_OUT_NO_RESET_CKT_ACK_RECV : 
            case SKS_BSSAP_CIC_BLOCK_STATE:
               if(getCicTableUsingCicId(recAlarmPtr->key2,&cicTblPtr) != CLIB_SUCCESS)
               {
                  LOG_PRINT(DEBUG,"getCicTableUsingCicId failed for trunkId:%d", recAlarmPtr->key1);
                  return; 

               }
               aiftrunkSecIndex.e1Num = cicTblPtr->e1Num;
               if(getSecAiftrunkTable(&aiftrunkSecIndex,&outData) != CLIB_SUCCESS)
               {
                  LOG_PRINT(DEBUG,"getSecAiftrunkTable failed for trunkId:%d", recAlarmPtr->key1);
                  free(cicTblPtr);
                  return; 
               } 
               recAlarmPtr->key1 =  outData->interfaceId;
               recAlarmPtr->key2 =  outData->tgpId;
               recAlarmPtr->key3 =  cicTblPtr->e1Num;
               recAlarmPtr->key4 =  cicTblPtr->timeSlot;
               switch ( recAlarmPtr->sysalarmId ) 
               {
                 case SKS_BSSAP_TIME_OUT_NO_BLOCK_ACK_RECV: 
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "TimeOut No Block Ack received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case SKS_BSSAP_TIME_OUT_NO_UNBLOCK_ACK_RECV : 
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "TimeOut No Unblock Ack received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case SKS_BSSAP_TIME_OUT_NO_RESET_CKT_ACK_RECV : 
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "TimeOut No ResetCkt Ack received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 case SKS_BSSAP_CIC_BLOCK_STATE:
                    recAlarmPtr->infoStrLen = sprintf(recAlarmPtr->infoString,
                    "Cic in Block State received on Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d]",
                    cicTblPtr->cicId, outData->interfaceId, outData->tgpId, outData->e1Num, cicTblPtr->timeSlot);
                    break;
                 default:
                     break;
               } 
               free(outData);
               free(cicTblPtr);
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            /*Changes end for Mantis 16764 */
            /*Changes for MantisId: 12466 done*/ 
            default:
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                                 ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break; 
         }
      break;
         /* CS4.0 HA Stack Changes : End */ 
/*Changes PCU R2.5 Aricent -- START*/
      case OAMS_PSSCM_CFG_ALARM_IND:
         switch (recAlarmPtr->sysalarmId)
         { 
            I_U16 cellIndex = 0;
            I_U16 bvciId = 0;
            I_S32 ret = CLIB_SUCCESS;

            /* to send OAMS_CFG_PSCH_BVC_OP_FAILED in all these cases*/
            case EVENT_PSSKS_BSSGP_MAX_BVC_BLOCK_TIMEOUT:
            case EVENT_PSSKS_BSSGP_MAX_BVC_UNBLOCK_TIMEOUT:
            case EVENT_PSSKS_BSSGP_MAX_BVC_RESET_TIMEOUT:
               LOG_PRINT(LOG_INFO, " Recived OAMS_PSSCM_CFG_ALARM_IND from PSSCM (BVC_BLOCK_TIMEOUT/BVC_UNBLOCK_TIMEOUT/BVC_RESET_TIMEOUT with key1 = %u, key2 = %u", recAlarmPtr->key1, recAlarmPtr->key2);
               ret = getCellIndex(recAlarmPtr->key1, recAlarmPtr->key2, &cellIndex);
               if (CLIB_SUCCESS == ret)
               {
                  ret = getBvciIdFromPsCellTable(recAlarmPtr->key1, recAlarmPtr->key2, &bvciId);
                  if (CLIB_SUCCESS == ret)   
                  {
                     oamsCfgPschBvcOpFailedBuff.cellIndex = cellIndex;
                     oamsCfgPschBvcOpFailedBuff.bvci = bvciId;
                     LOG_PRINT(LOG_INFO,"sending OAMS_CFG_PSCH_BVC_OP_FAILED to PSCH");
                     cfgSendMessage(&oamsCfgPschBvcOpFailedBuff, sizeof(OamsCfgPschBvcOpFailed), ENT_OAMS_PSCH, OAMS_CFG_PSCH_BVC_OP_FAILED, 0);
                  }
                  else
                  {
                     LOG_PRINT(LOG_MAJOR, "getBvciIdFromPsCellTable() failed, unable to send OAMS_CFG_PSCH_BVC_OP_FAILED to PSCH, Error Code [%d]", ret);
                  }
               }
               else
               {
                  LOG_PRINT(LOG_MAJOR, " DB Call getCellIndex() failed, unable to send OAMS_CFG_PSCH_BVC_OP_FAILED to PSCH, Error Code [%d]", ret);
               }
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND"); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            case EVENT_PSSKS_BSSGP_MAX_SIG_BVC_RESET_TIMEOUT:
               LOG_PRINT(LOG_INFO,"sending OAMS_CFG_GBH_SIG_BVC_RESET_FAILED to GBH"); 
               cfgSendMessage(&oamsCfgGbhSigBvcResetFailed, sizeof(OamsCfgGbhSigBvcResetFailed), ENT_OAMS_GBH, OAMS_CFG_GBH_SIG_BVC_RESET_FAILED, 0);
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND"); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            case ALARM_FIRST_NSVC_ENABLED:
               LOG_PRINT(LOG_INFO,"Received alarm ALARM_FIRST_NSVC_ENABLED, sending OAMS_CFG_GBH_FIRST_NSVC_ENABLED to GBH");
               cfgSendMessage(&oamsCfgGbhFirstNsvcEnabledBuff, sizeof(OamsCfgGbhFirstNsvcEnabled), ENT_OAMS_GBH, OAMS_CFG_GBH_FIRST_NSVC_ENABLED,0);
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND"); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            case ALARM_LAST_NSVC_DISABLED:
               cfgSendMessage(&oamsCfgGbhLastNsvcDisabledBuff, sizeof(OamsCfgGbhLastNsvcDisabled), ENT_OAMS_GBH, OAMS_CFG_GBH_LAST_NSVC_DISABLED,0);
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND"); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            case EVENT_PSSKS_NS_BVCI_UNKNOWN:
               LOG_PRINT(LOG_INFO,"Received alarm EVENT_PSSKS_NS_BVCI_UNKNOWN");
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND"); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               break;
            default:
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND"); 
               cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            
         }
         break; /* end case OAMS_PSSCM_CFG_ALARM_IND */
      /* Added in PCU R2.5 alarms received from GBH, 
         NSVCH or PSCH  are to be simply forwarded to AFH */
      case OAMS_GBH_CFG_ALARM_IND:
      case OAMS_NSVCH_CFG_ALARM_IND:
         LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND.."); 
         cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         break;
      case OAMS_PSCH_CFG_ALARM_IND:/* changes done for KPI*/
         LOG_PRINT(LOG_INFO,"handle  OAMS_PSCH_CFG_ALARM_IND for KPI alrmId = %d ",recAlarmPtr->sysalarmId);
         LOG_PRINT(LOG_INFO,"handle  OAMS_PSCH_CFG_ALARM_IND for KPI alrmId for PSCELLENABLE= %d ",ALARM_PSCELL_ENABLED);
         LOG_PRINT(LOG_INFO,"handle  OAMS_PSCH_CFG_ALARM_IND for KPI alrmId for PSCELLDISABLE= %d ",ALARM_PSCELL_DISABLED);
         switch (recAlarmPtr->sysalarmId)
         {
            case ALARM_PSCELL_ENABLED:
            LOG_PRINT(LOG_INFO,"EVENT_PS_CELL_UNBARRED / ALARM_PSCELL_ENABLED:Alarm is received %d",recAlarmPtr->sysalarmId);
            getAInterfaceOprState(&oprStateAInterface);
            if(oprStateAInterface == ENABLED)
            {
                updateDataAvlbltyTblAtPsCellEnableUnbarred(recAlarmPtr->key2, recAlarmPtr->key1);
            }
            break;
            case ALARM_PSCELL_DISABLED:
            LOG_PRINT(LOG_INFO,"EVENT_PS_CELL_BARRED / ALARM_PSCELL_DISABLED:Alarm is received %d", recAlarmPtr->sysalarmId);
            getAInterfaceOprState(&oprStateAInterface);
            if(oprStateAInterface == ENABLED)
            {
            updateDataAvlbltyTblAtPsCellDisable(recAlarmPtr->key2, recAlarmPtr->key1);
            }
            break;
         }/* changes done for  Data Availability KPI Ends */
         LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND.."); 
         cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         break;
         
      case PSSKS_FR_CFG_ALARM_IND:
         LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND.."); 
         cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         break;
/*Changes PCU R2.5 Aricent -- END*/
      case OAMS_SWMH_CFG_ALARM_IND: /*CS3.0 change */
           LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND.."); 
           cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
          if( EVENT_SW_INSTALLATION_TIMED_OUT == recAlarmPtr->sysalarmId ) 
          {
            ipBtsId = recAlarmPtr->key1;
            swInstallTimeOutHandler(ipBtsId);
          }
           break;
      case OAMS_BPM_CFG_ALARM_IND:
      case CSAPP_MRHM_CFG_ALARM_IND:
      case OAMS_BICH_CFG_ALARM_IND:  /* Change For CS2.2 */
     // case OAMS_SWMH_CFG_ALARM_IND: /*CS3.0 change */
      case OAMS_CCUH_CFG_ALARM_IND: /* Change For CS4.0 CCU */
         /* Send Alarm to AFH */
         if (! trunkAlarms && TRUE == res ) {
            LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND.."); 
           cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         }
         break;
      default:
         cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), 
                           ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         break;
   }

   switch (recAlarmPtr->sysalarmId)
   {
      /*case SCCP_SCMG_SS_PROHIBITED:
         {
            LOG_PRINT(LOG_INFO,"SCCP_SCMG_SS_PROHIBITED Alarm is received "); */
      case SSP_MSG_RECV_REM_SUBSYSTEM:
         {
            LOG_PRINT(LOG_INFO,"SSP_MSG_RECV_REM_SUBSYSTEM Alarm is received ");               
#if 0
          /*IP_BSC_STACK: Not required now 18 July 2016*/ 
						/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
            LOG_PRINT(DEBUG,"GOING to update LinkSetStatusTable as DISABLED in DATABASE");
            updateOrInsertLinkSetStatusTable(((I_U16)1),DISABLED);							
            LOG_PRINT(DEBUG,"GOING to update LinkStatusTable as DISABLED in DATABASE");
						updateOrInsertLinkStatusTable(((I_U16)1),((I_U16)1),DISABLED);	
						/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
          /*IP_BSC_STACK: Not required now 18 July 2016*/ 
#endif
            if( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) ||
                (gCurrentCardState == CARDSTATE_STANDBY) ||
                (gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS)  ) 
            {
               LOG_PRINT(DEBUG,"Storing SSP_Message as Card is in AIP");
               gAipSSPRcvd = TRUE;  
               gAipSSARcvd = FALSE;
            } 
            else
            {  
               gSSAReceived = FALSE; /*Mantis 2284*/
               
						   /*Mantis 12021 start */
						   #if 0
						   if ((gBssState == lockInProgress) || (gBssState == LOCKED))
               {
                  /*Consume It*/
               }
               else
               {
						   #endif
						   /*Mantis 12021 END */
                  getAInterfaceOprState(&oprStateAInterface);
                  if(oprStateAInterface == ENABLED) /* Check added for Mantis 2284 */
                  {
                     /* Send OAMS_CFG_GRHM_LOCK_REQ */
                     setAinterfaceTableOperationalState(DISABLED);
                     /*gAinterfaceUPDownFlag = TRUE; commented during fix for 2284 - no use of this updown flag */
                     OamsCfgGrhmLockReqBuff.objectId=0;
                     OamsCfgGrhmLockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
                     OamsCfgGrhmLockReqBuff.reason = OAMS_RSN_AINTERFACEDOWN;
                     cfgSendMessage(&OamsCfgGrhmLockReqBuff, sizeof(OamsCfgGrhmLockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_LOCK_REQ, 0);                  
                     /* send CellBar Acess to CELLH and PSCH for all unlocked cells */
                     //sendCellBarAccessToCells(LockProcedure,OAMS_RSN_AINTERFACEDOWN);
                     /*Cell Bar Access is sent After receiving GRHM_LOCK_RESP from
                     GRHM */
                     gAifMsgSentToGrhm = OAMS_CFG_GRHM_LOCK_REQ;
                  }
                  else
                  {
                     LOG_PRINT(LOG_INFO,"A interface is already Disabled");               
                  }
               //}  //12021
            }  
         }
         break;

      /* case SCCP_SCMG_SS_ALLOWED:
         LOG_PRINT(LOG_INFO,"SCCP_SCMG_SS_ALLOWED Alarm is received "); */
      case SSA_MSG_RECV_REM_SUBSYSTEM:
         LOG_PRINT(LOG_INFO,"SSA_MSG_RECV_REM_SUBSYSTEM Alarm is received ");              
#if 0
          /*IP_BSC_STACK: Not required now 18 July 2016*/ 
					/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
          LOG_PRINT(DEBUG,"GOING to update LinkSetStatusTable as ENABLED in DATABASE");
          updateOrInsertLinkSetStatusTable((I_U16)1,ENABLED);						
          LOG_PRINT(DEBUG,"GOING to update LinkStatusTable as ENABLED in DATABASE");
					updateOrInsertLinkStatusTable(((I_U16)1),((I_U16)1),ENABLED);	
					/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
          /*IP_BSC_STACK: Not required now 18 July 2016*/ 
#endif
         if( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) ||
             (gCurrentCardState == CARDSTATE_STANDBY) ||
             (gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS)  ) 
         {
            LOG_PRINT(DEBUG,"Storing SSA_Message as Card is in AIP");
            gAipSSARcvd = TRUE;
            gAipSSPRcvd = FALSE;  
         } 
         else
         {  
            gSSAReceived = TRUE; /*Mantis 2284*/
            if (gBssState == unlockInProgress )
            {
               bssObjectHandlerForSSAllowed();
            }
            else if ((gBssState == lockInProgress) || (gBssState == locked) )  
            {
               LOG_PRINT(LOG_INFO,"Ignoring SS_ALLOWED ,as BSS is in lockInProgress state..");               
               /* Consume It.. */
            }
            else
            {
               OamsCfgGrhmUnlockReqBuff.objectId=0;
               OamsCfgGrhmUnlockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
               OamsCfgGrhmUnlockReqBuff.reason = OAMS_RSN_AINTERFACEUP;
               cfgSendMessage(&OamsCfgGrhmUnlockReqBuff, sizeof(OamsCfgGrhmUnlockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_UNLOCK_REQ, 0);
               gAifMsgSentToGrhm = OAMS_CFG_GRHM_UNLOCK_REQ;
            
            }
         }
         break;
/*Changes PCU R2.5 Aricent -- START*/
      /* simply forwarding the alarm to AFH for al these cases*/
      case CELL_ENABLED:
         LOG_PRINT(LOG_INFO,"CELL_ENABLED Alarm is received ");
         /* KPI PHASE-II Changes Start */
         getAInterfaceOprState(&oprStateAInterface);
         if(oprStateAInterface == ENABLED)
         {
         updateRadioNwAvlbltyTblAtCellEnableUnbarred(recAlarmPtr->key2, recAlarmPtr->key1);
         }
         /* KPI PHASE-II Changes Ends */    
         /* R2.4 Change */
         sendCellOprStateToCbsh(recAlarmPtr->key2, recAlarmPtr->key1, CAUSE_CELL_ENABLED);
         cellObjectHandler();
         break;
      case CELL_DISABLED:
         LOG_PRINT(LOG_INFO,"CELL_DISABLED Alarm is received ");
         /* KPI PHASE-II Changes Start */
         getAInterfaceOprState(&oprStateAInterface);
         if(oprStateAInterface == ENABLED)
         {
         updateRadioNwAvlbltyTblAtCellDisable(recAlarmPtr->key2, recAlarmPtr->key1);
         }
         /* KPI PHASE-II Changes Ends */    
         /* R2.4 Change */
         sendCellOprStateToCbsh(recAlarmPtr->key2, recAlarmPtr->key1, CAUSE_CELL_DISABLED);
         cellObjectHandler();
         break;
 
        
      case ALARM_BTS_IP_LINK_UP:
      case ALARM_BTS_IP_LINK_DOWN:
         LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AFH_ALARM_IND"); 
         cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         /*Fixed for mantis #32153 Gaurav Sinha*/
         break;
         /*Fixed for mantis #32153 Gaurav Sinha*/
/*Changes PCU R2.5 Aricent -- END*/

/*Added for IP_BSC_STACK Gaurav Sinha 08-09-2016 mantis #32112 #32021*/
      case M3UA_ASP_STATE_ACTIVE:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: M3UA_ASP_STATE_ACTIVE :ALARM Recvd from SIGTRAN Stack for ASPID %d SlotId %d",recAlarmPtr->key2, recAlarmPtr->key1); 
          updateOrInsertAspStatusTable(recAlarmPtr->key2,ENABLED); 
          break;
      
      case M3UA_ASP_STATE_DOWN:
      case M3UA_ASP_STATE_INACTIVE:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: M3UA_ASP_STATE_DOWN/M3UA_ASP_STATE_INACTIVE :ALARM Recvd from SIGTRAN Stack for ASPID %d SlotId %d",recAlarmPtr->key2, recAlarmPtr->key1);
          updateOrInsertAspStatusTable(recAlarmPtr->key2,DISABLED); 
          break; 
      case M3UA_CONN_DOWN:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: M3UA_CONN_DOWN :ALARM Recvd from SIGTRAN Stack for ASPID %d SlotId %d",recAlarmPtr->key2, recAlarmPtr->key1);
         checkAndSendAspUnlock(recAlarmPtr->key2);
         break; 
      
       case SIGTRAN_DATA_PULL_DONE:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: SIGTRAN_DATA_PULL_DONE :ALARM Recvd from SIGTRAN Stack for SlotId %d", recAlarmPtr->key1);
         I_U32 aspId = ZERO; 
         aspId = getAspIdFromSlotId(recAlarmPtr->key1);
         if(aspId)
         {
          checkAndSendAspUnlock(aspId);
         }
         break; 
/*Added for mantis #32112 #32021 Gaurav Sinha 04-10-2016 */

      default:
         break;
   }
}

/********************************* Function  Header********************************
Function Name:       ChkActiveCardAlarm()
Parameters:          Alarm Structure
Return type:         TRUE if ICC card is in active state, else FALSE
Purpose:             To PopulateCardStateChange Table.
Other Note:          Added for CS4.0 HA. 
************************************************************************************/
I_U8 ChkActiveCardAlarm( I_U32 frameId, I_U32 slotId)
{
   // Send Alarm to active card only
   LOG_PRINT(LOG_INFO,"ChkActiveCardAlarm :: Check Active state of Card");
   IccCardInfoTableIndices    iccCardInfoTable;
   IccCardInfoTableApi        *iccCardInfoTableApiPtr    =NULL;

   EicCardInfoTableIndices    eicCardInfoTable;
   EicCardInfoTableApi        *eicCardInfoTableApiPtr    =NULL;

   memset(&iccCardInfoTable,0,sizeof(IccCardInfoTableIndices));
   memset(&eicCardInfoTable,0,sizeof(EicCardInfoTableIndices));
   // Construct key for IccCardInfo table
   iccCardInfoTable.chasisFrameId                        = (I_U8)frameId;
   iccCardInfoTable.slotId                               = (I_U8)slotId;
   
	 /*BSC R2.0 Changes Starts*/
   // Construct key for EicCardInfo table
   eicCardInfoTable.chasisFrameId                        = (I_U8)frameId;
   eicCardInfoTable.slotId                               = (I_U8)slotId;

   LOG_PRINT(DEBUG,"ChkActiveCardAlarm :: FrameId(%d) SlotId(%d)",
          iccCardInfoTable.chasisFrameId,iccCardInfoTable.slotId);
	 /*BSC R2.0 Changes Ends*/

   if(getIccCardInfoTable(&iccCardInfoTable, &iccCardInfoTableApiPtr) == CLIB_SUCCESS)
   {

      if( iccCardInfoTableApiPtr->cardOperationalState == CARDSTATE_ACTIVE ) 
      {
         free(iccCardInfoTableApiPtr);
         LOG_PRINT(LOG_INFO,"ChkActiveCardAlarm :: ICC Card is in active state::Forward the alarm");
         return TRUE;
      }
      else
      {
         LOG_PRINT(LOG_INFO,"ChkActiveCardAlarm :: ICC Card is not in active state:%d::Discard alarm",
                iccCardInfoTableApiPtr->cardOperationalState);
         free(iccCardInfoTableApiPtr);
         return FALSE;
      }
   }
	 /*BSC R2.0 Changes Starts*/
   else if(getEicCardInfoTable(&eicCardInfoTable, &eicCardInfoTableApiPtr) == CLIB_SUCCESS)
   {
      if( eicCardInfoTableApiPtr->cardOperationalState == BPM_EIC_ENABLE) 
      {
         free(eicCardInfoTableApiPtr);
         LOG_PRINT(LOG_INFO,"ChkActiveCardAlarm :: EIC Card is in active state::Forward the alarm");
         return TRUE;
      }
      else
      {
         LOG_PRINT(LOG_INFO,"ChkActiveCardAlarm :: EIC Card is not in active state::Discard alarm");
         free(eicCardInfoTableApiPtr);
         return FALSE;
      }
   }
	 /*BSC R2.0 Changes Ends*/
   else
   {
      LOG_PRINT(LOG_INFO,"ChkActiveCardAlarm, getIccCardInfoTable failed::Discard Alarm");
      return FALSE;
   }
  
}
/********************************* Change History ***************************
   Release     Patch       Author            Description
   CS2                     Pratibha          Enum Removal Change
   CS4.0                   Harsh Kharbanda   Alarm related changes

 ************************************** End *********************************/

