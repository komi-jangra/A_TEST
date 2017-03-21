/********************************File Header ***********************
  File Name        : oamscfg_e1_object_handler.c
Purpose          : This file contains function defintions for E1 Object Handling.
Project          : BSC
Subsystem        : OAMS
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h> 
//#include <oamscfg_globals.h>
I_U32 e1ObjectInstanceIndex;/*To store the Object Index.*/   

/********************************* Function  Header********************************
  Function Name:       getE1ObjectState()
Parameters:          void
Return type:         void
Purpose:             To get state of the received message.
Other Note:
 ************************************************************************************/

objectState getE1ObjectState(I_U32 e1Num)
{
   e1ObjectInstanceIndex = e1Num;
   LOG_PRINT(DEBUG,"getE1ObjectState ret State%d for e1%d",gE1Data[e1Num].e1State,e1Num );
   return gE1Data[e1Num].e1State;

}/*end getE1ObjectState*/


/********************************* Function  Header********************************
  Function Name:       getTrunkObjectState()
Parameters:          void
Return type:         void
Purpose:             To get state of the received message.
Other Note:
 ************************************************************************************/

TrunkPortObject  getTrunkObjectState(I_U32 e1Num)
{
   LOG_PRINT(DEBUG,"getTrunkObjectState for e1(%d) retVal(%d)",e1Num,gE1Data[e1Num].trunkState);
   return gE1Data[e1Num].trunkState;

}/*end getE1ObjectState*/

/********************************* Function  Header********************************

  Function Name:       getState()
Parameters:          void
Return type:         void
Purpose:             To typecast the received message.
Other Note:
 ************************************************************************************/
objectState getState()
{
   objectState state;
   /* Fix for SPR 169 Start....*/
   TrunkTableApi *e1ObjPtr;
   /* Fix for SPR 169 End....*/

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_TRUNKPERTABLE:
         { 
            sCmMsg* receivedCmMsgPtr = 0;
            receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;  
            e1ObjPtr = (TrunkTableApi *)((I_S8 *)receivedCmMsgPtr + sizeof(sCmMsg)); /*point to payload of received message*/
            state = getE1ObjectState(e1ObjPtr->e1Num);
         }
         break;
#if 0 /* CS4.0 HA Stack Changes */
      case BSC_API_SET_LINKADMINSTATETABLE:
         {  
            /* e1ObjectInstanceIndex is already updated in the scmMsgHandler() */
            state = getE1ObjectState(e1ObjectInstanceIndex);
         } 
         break;               
#endif
      case CSAPP_GRHM_CFG_ALARM_IND:
         {
            LOG_PRINT(LOG_INFO,"  CSAPP_GRHM_CFG_ALARM_IND: ...");
            SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
            if(recAlarmPtr->key1 == OAMS_OBJTYPE_E1)
            {
               state = getE1ObjectState(recAlarmPtr->key2);
            }
         }
         break;
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            state = getE1ObjectState((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId);
            break;
         }
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            state = getE1ObjectState((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId);
            break;
         }
      case CSAPP_GRHM_CFG_UNLOCK_FAIL:
         {
            state = getE1ObjectState((( CsappGrhmCfgUnlockFail* )gCfgMsgBuf)->objectId);
            LOG_PRINT(LOG_MAJOR,"CSAPP_GRHM_CFG_UNLOCK_FAIL not expected for E1");   
            break;
         }
   }
   return state;
}

// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       getTrunkState()
Parameters:          Pointer to e1num
Return type:         void
Purpose:             To fetch the state of TrunkPort depending on the message reecived
& find the E1 Number.
Other Note:
 ************************************************************************************/
TrunkPortObject getTrunkState( I_U32 *e1num )
{
   //objectState state;
   TrunkPortObject state                           = Invalid;
   I_U8            iLoop                           = 0;
   I_U8            result                          = 0;
   I_U8                   res                      = 0;

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_TRUNKPORTTABLE:
         { 
            state = getTrunkObjectState(gE1NumberMapToTrunk);
         }
         break;
      case OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP:
         { 
            // Based on the Transaction Id, search for E1 Number in gE1Data structure
            for( iLoop = 0; iLoop < CFG_MAX_NUM_E1 ; iLoop++ ) 
            {
               if( (( OamOilCfgE1EnableResp* )(gCfgMsgBuf))->transactionId == gE1Data[iLoop].e1Number)
               {
                  *e1num = gE1Data[iLoop].e1Number;
                  res = 1;
                  break; 
               }
               if( iLoop == CFG_MAX_NUM_E1 - 1 )
               {
                  LOG_PRINT(LOG_INFO," Invalid Transaction Id Received");   
                  res = 0;
               }

            }

            if( res == 1 ) 
               state = getTrunkObjectState(*e1num);
         }
         break;
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_ACTIVE_ALARM_RCVD )
               state = getTrunkObjectState((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId);
            break;
         }
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->reason ==  OAMS_RSN_LOS_CLEAR_ALARM_RCVD )
               state = getTrunkObjectState((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId);
            break;
         }
      case OAM_OIL_CFG_ALARM_IND:
         {

            I_U32  adminstate = 0;
            SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

            // Check in DB if Trunk Id is present
            if( ( findTrunkIdTrunkPortTable(recAlarmPtr->key3, &adminstate ) ) != I_TRUE )
            {
               LOG_PRINT(LOG_INFO," Received Trunk Port Id not present in DB :: Discarding the message");
               cfgSendNackToCm(CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB);
               return state;
            }

            I_U32 e1number = 0;

            // Based on Trunk Id, find its mapping to E1 number & search that E1 number in gE1Data structure

            result = GetE1numByTrunkId(recAlarmPtr->key3, e1num ); 

            e1number = *e1num;

            if( result == 1 )
               state = getTrunkObjectState( e1number );

            break;
         }
      default:
         LOG_PRINT(LOG_INFO," Unexpected Message Reecived :: Enable/Disable Procedure"); 
         break;

   }
   return state;
}
// CS4.0 Enable/Disable


/********************************* Function  Header********************************
  Function Name:       e1ObjectHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle the E1Lock/E1Unlock Procedures.
Other Note:
 ************************************************************************************/
void e1ObjectHandler()
{
   objectState state;
   state = getState();
   switch (state)
   {
      case unlocked:
         setTable(); 
         break;

      case lockInProgress:
         lockInProgressHandler(); 
         break;

      case locked:
         setTable(); 
         break;

      case unlockInProgress:
         unlockInProgressHandler();        
         break;
      case blockInProgress:
         LOG_PRINT(DEBUG," Val of state is shutdownInProgress");
      break; 
      case unlockOrEnableInProgress:
         LOG_PRINT(DEBUG," Val of state is unlockOrEnableInProgress");
      break; 
      case lockeOrDisableInProgress:
         LOG_PRINT(DEBUG," Val of state is lockeOrDisableInProgress");
      break; 
      case unlockedEnabled:
         LOG_PRINT(DEBUG," Val of state is unlockedEnabled");
      break; 
      case ShuttingDown:
         LOG_PRINT(DEBUG," Val of state is ShuttingDown");
      break; 
      case unlockedDisabled:
         LOG_PRINT(DEBUG," Val of state is unlockedDisabled");
      break; 
            
       default:
         LOG_PRINT(DEBUG," Val of state is default %d", state);
      break; 
            
   } /*switch ends here..*/
}

// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       TrunkPortObjectHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle Trunk Port Enable/Disable Procedure
Other Note:
 ************************************************************************************/
void TrunkPortObjectHandler()
{
   TrunkPortObject state   = Invalid;
   I_U32           e1num   = 0; 

   state = getTrunkState( &e1num );
   
   switch (state)
   {
      case Enabled:
         {
            if ( ( (SysHdr*) gCfgMsgBuf)->msgType == OAM_OIL_CFG_ALARM_IND )
            {

               SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf + sizeof(SysHdr) );

               if( recAlarmPtr->sysalarmId == ALARM_E1_LOS_ACTIVE  || recAlarmPtr->sysalarmId == ALARM_E1_LOS_CLEAR )
               {
                  PlatformAlarmHandler( recAlarmPtr->sysalarmId, &e1num );
               }

            }
            else
            { 
               setTable();
            } 
         }
         break;
      case EnableInProgress:
         if ( ( (SysHdr*) gCfgMsgBuf)->msgType == OAM_OIL_CFG_ALARM_IND )
         {
            SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf + sizeof(SysHdr));
            if( recAlarmPtr->sysalarmId == ALARM_E1_LOS_ACTIVE  || recAlarmPtr->sysalarmId == ALARM_E1_LOS_CLEAR )
            {
               PlatformAlarmHandler( recAlarmPtr->sysalarmId, &e1num );
            }
            else
            {
               EnableInProgressHandler( &e1num ); 
            }
         }
         else
         {
            EnableInProgressHandler( &e1num ); 
         }
         break;

      case Disabled:
         if ( ( (SysHdr*) gCfgMsgBuf)->msgType == OAM_OIL_CFG_ALARM_IND )
         {
            SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf + sizeof(SysHdr));
            if( recAlarmPtr->sysalarmId == ALARM_E1_LOS_ACTIVE  || recAlarmPtr->sysalarmId == ALARM_E1_LOS_CLEAR )
            {
               PlatformAlarmHandler( recAlarmPtr->sysalarmId, &e1num );
            }
         }
         else
         {
            setTable();
         } 
         break;

      case DisableInProgress:
         if ( ( (SysHdr*) gCfgMsgBuf)->msgType == OAM_OIL_CFG_ALARM_IND )
         {
            SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf + sizeof(SysHdr));
            if( recAlarmPtr->sysalarmId == ALARM_E1_LOS_ACTIVE  || recAlarmPtr->sysalarmId == ALARM_E1_LOS_CLEAR )
            {
               PlatformAlarmHandler( recAlarmPtr->sysalarmId, &e1num );
            }
            else
            {
               DisableInProgressHandler( &e1num );        
            }
         }
         else
         {
            DisableInProgressHandler( &e1num );        
         }
         break;
      default:
         LOG_PRINT(LOG_INFO," Incorrect State"); 
         break;
   } /*switch ends here..*/
}

// CS4.0 Enable/Disable

/********************************* Function  Header********************************
  Function Name:       setTable()
Parameters:          void
Return type:         void
Purpose:             To Handle the locked / unlocked state.
Other Note:
 ************************************************************************************/
void setTable()
{
   if (((SysHdr*) gCfgMsgBuf)->msgType == BSC_API_SET_TRUNKPERTABLE)
   { 
      setE1Table();  
   } 
   // CS4.0 Enable/Disable
   else if (((SysHdr*) gCfgMsgBuf)->msgType == BSC_API_SET_TRUNKPORTTABLE)
      setTrunkPortTable();  
   else if(((SysHdr*) gCfgMsgBuf)->msgType == CSAPP_GRHM_CFG_LOCK_RESP)
   {
      if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_ACTIVE_ALARM_RCVD )
      {
         //Reset LOS_Active_In_Progress flag
         gE1Data[( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId].LOS_Active_In_Progress = FALSE ;
         LOG_PRINT(LOG_INFO," LOS ACTIVE PROCEDURE ENDS");
         // Check LOS Clear Pending flag & if TRUE, proceed with LOS Clear Handling
         if( gE1Data[( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId].LOS_Clear_Pending == TRUE )
         {
            PlatformAlarmHandler( ALARM_E1_LOS_CLEAR , &(( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId ));
         }
      }
   }
   else if(((SysHdr*) gCfgMsgBuf)->msgType == CSAPP_GRHM_CFG_UNLOCK_RESP)
   {
      if((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_CLEAR_ALARM_RCVD  )
      {
         //Reset LOS_Clear_In_Progress flag
         gE1Data[( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId].LOS_Clear_In_Progress = FALSE ;
         LOG_PRINT(LOG_INFO," LOS CLEAR PROCEDURE ENDS");
         if( gE1Data[( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId].LOS_Active_Pending == TRUE )
         {
            PlatformAlarmHandler(ALARM_E1_LOS_ACTIVE , &(( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId ));
         }
      }
   }
   else if (((SysHdr*) gCfgMsgBuf)->msgType == OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP)
   {
      LOG_PRINT(LOG_INFO," OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP received in Incorrect state/Trunk Port Already Enabled/Disabled::Discarding the message");
   }
   else
   {
      LOG_PRINT(LOG_INFO," Invalid message Received::setTable");
   }
   // CS4.0 Enable/Disable
}



// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       GetE1numByTrunkId()
Parameters:          trunkid & pointer to e1number
Return type:         void
Purpose:             To find the mapping of received Trunk Id & return e1 number.
Other Note:
 ************************************************************************************/
I_U8 GetE1numByTrunkId( I_U16 trunkid, I_U32 *e1num )
{

   I_U8   ret             = 0;
   I_U16  outSize         = 0;
   I_U32  i               = 0;
   I_U32  rowsCount       = 0;
   TrunkTableApi*         TrunkTableApiPtr         = PNULL;
   TrunkTableApi*         TrunkTableAddr           = PNULL;

   // Check if received Trunk Id is mapped to Logical E1 Number  
   ret = getallTrunkTable(&TrunkTableApiPtr, &rowsCount, &outSize);
   if (ret == CLIB_SUCCESS && PNULL != TrunkTableApiPtr )
   {
      if( rowsCount > 0 )
      {
         for(i = 0; i < rowsCount; i++)
         {
            TrunkTableAddr = (TrunkTableApi *) (((char *)TrunkTableApiPtr ) + (outSize * i));

            if( TrunkTableAddr->trunkPortId == trunkid )
            {
               // Store the E1 Number
               *e1num              = TrunkTableAddr->e1Num;
               break;
            }

            if( i == rowsCount - 1 )
            {
               LOG_PRINT(LOG_INFO," Mapping Not Found for received Trunk Id ::PROCEDURE ENDS");
               free(TrunkTableApiPtr);
               return 0;
            }
         }
         free(TrunkTableApiPtr);
      }
      else
      {
         LOG_PRINT(LOG_INFO," No rows present in TrunkTable :: PROCEDURE ENDS");
         free(TrunkTableApiPtr);
         return 0 ;   
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO," No rows present in TrunkTable :: PROCEDURE ENDS");
      return 0 ;
   }   
   return 1;

}
// CS4.0 Enable/Disable

// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       FindState()
Parameters:          Admin state of E1
Return type:         unsigned char
Purpose:             To check state of BSS & E1 object when Active Alarm is received from LOS.
Other Note:
 ************************************************************************************/

I_U8 FindState( I_U32 adminstate, I_U32 e1num )
{

   // Check For Admin State of BSS
   if( (gBssState == lockInProgress) || (gBssState == locked))
   {
      LOG_PRINT(LOG_INFO," BSS is in Locked state ");
      return FALSE;
   }

   // Check For admin state of E1
   if( adminstate == LOCKED || gE1Data[e1num].e1State == lockInProgress ) 
   {
      LOG_PRINT(LOG_INFO," E1 is in Locked state :: ");
      return FALSE;
   }

   return TRUE;

}
// CS4.0 Enable/Disable


// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       IsE1ForCIC()
Parameters:          E1 number
Return type:         unsigned char
Purpose:             To check if E1 is configured for CIC.
Other Note:
 ************************************************************************************/
I_U8 IsE1ForCIC( I_U32 e1Num )
{
   

   #if 0 
   AbisTimeSlotTableApi *timeSlotblPtr;
   AbisTimeSlotTableApi *tempTimeSlotblPtr;
   I_U32  count     =0;
   I_U16  size      =0;
   I_U8   i         =0;

   if ( getTimeSlotForE1(e1Num, &timeSlotblPtr, &count, &size) == CLIB_SUCCESS )
   {
      for ( i =0 ; i < count; i++)
      {
         tempTimeSlotblPtr =(AbisTimeSlotTableApi*) ((I_U8*)timeSlotblPtr + (i *size));
         if (tempTimeSlotblPtr->usageType != SYS_TS_USAGE_CIC)
         {
            free(timeSlotblPtr);
            return FALSE;
         }
         if( i == count - 1 )
         {
            free(timeSlotblPtr);
            return TRUE;
         }
      }//for
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL,"  Timeslot Get DB Failure::LOS Procedure Ends ");   
      return 2;
   }
   return TRUE;
   #endif 
   
   // Now handling will be based on Trunk Table & Link table


   #if 0
   // Fetch tsCiCMap on the basis of E1 supplied

   if( getTsCicMapTrunkTable( e1Num, &tscicmap ) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_CRITICAL,"  gettsCicMapTrunkTable Failure::LOS Procedure Ends ");   
      return 2;
   }
   
   // Check the bits that are set in tscicmap to find the number of CICs that are configured on that E1   
   if( ( tscicmap & 0x7fffffff )  == 0x7fffffff )
   {
      LOG_PRINT(LOG_CRITICAL," All CICs are configured on this E1 ");   
      return TRUE;
   }
   else
   {}
   #endif

   if( isLinkConfiguredForE1( e1Num ) != CLIB_SUCCESS ) 
   {
      LOG_PRINT(LOG_CRITICAL," MTP2 links are not configured on this E1 ");   
      return TRUE;

      // Search in CicTable if entry for the E1 on which LOS has been received is present
      if( isTrunkPresentInCicTable( e1Num ) == CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_CRITICAL," All CICs are configured on this E1 ");   
         return TRUE;
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," E1 is not configured for both CIC and MTP2 ");   
         return FALSE;
      }
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL," MTP2 links are configured on this E1 ");   
       return FALSE;
   }
      

}

// CS4.0 Enable/Disable








/********************************* Function  Header********************************
  Function Name:       unlockInProgressFun()
Parameters:          void
Return type:         void
Purpose:             To Handle the unlockInProgress state.
Other Note:
 ************************************************************************************/
void unlockInProgressHandler()
{
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
#if 0 /* CS4.0 HA Stack Changes */ 
      case BSC_API_SET_LINKADMINSTATETABLE:
         LOG_PRINT(LOG_INFO," in BSC_API_SET_LINKADMINSTATETABLE ( RESP ): "); 
         cfgScmUnlockLinkAdmStTblResp();           
         break;
#endif
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            LOG_PRINT(LOG_INFO,"  CSAPP_GRHM_CFG_UNLOCK_RESP ...");
            if((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_E1)
            {
               csappGrhmCfgUnlockRespE1();            
            }
            else
            {
               LOG_PRINT(LOG_MAJOR,"unlockInProgressHandler: Invalid object type in Lock Response");
            }
         } 
         break;
      case BSC_API_SET_TRUNKPERTABLE:
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
         break;

      default:
         LOG_PRINT(LOG_INFO," Un expected Message recieved"); 
         break;
   }/*switch ends here..*/
}/*end unlockInProgressFun..*/


/********************************* Function  Header********************************
  Function Name:       lockInProgressFun()
Parameters:          void
Return type:         void
Purpose:             To Handle the lockInProgress state.
Other Note:
 ************************************************************************************/
void lockInProgressHandler()
{
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
#if 0 /* CS4.0 HA Stack Changes */ 
      case BSC_API_SET_LINKADMINSTATETABLE:
         cfgScmLockLinkAdmStTblResp();
         break;    
#endif 
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            LOG_PRINT(LOG_INFO,"  LOCK Response received from GRHM");
            if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_E1)
            {
               csappGrhmCfgLockRespE1();    
            }
            else
            {
               LOG_PRINT(LOG_MAJOR,"lockInProgressHandler: Invalid object type in Lock Response");
            }
         }
         break; 
      case BSC_API_SET_TRUNKPERTABLE:
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         break;

      default:
         LOG_PRINT(LOG_MAJOR," Unexpected Message"); 
         break;       
   } /*switch ends here..*/
}

// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       EnableInProgressHandler()
Parameters:          Pointer to E1 Number
Return type:         void
Purpose:             To Handle the EnableInProgress state.
Other Note:
 ************************************************************************************/
void EnableInProgressHandler( I_U32 *e1num )
{

   LOG_PRINT(LOG_INFO,"EnableInProgressHandler e1num = %d", *e1num);
   TrunkPortTableIndices primarykey = {0};

   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
      case OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP:
         {

            // Case 1: Platform has send the nack, send alarm to AFH
            if( (( OamOilCfgE1EnableResp* )(gCfgMsgBuf))->result != OPERATION_SUCCESS  || ( (OamOilCfgE1EnableResp* )( gCfgMsgBuf))->portResult[0].result != OPERATION_SUCCESS )
            {
               LOG_PRINT(LOG_MAJOR," Enable Request Discarded by BPM");
               // Send alarm to AFH:: Procedure Ends Here
               SendAlarm( ALARM_E1_ENABLE_FAILURE, TRAP_SEVERITY_MAJOR, DISABLED, *e1num );            
               gE1Data[(*(e1num))].trunkState = Disabled;
               LOG_PRINT(DEBUG,"updating TrunkState of e1Num(%d) as disabled", *e1num);
            }
            else
            {
               // CFG does nothing and wait for Event from Platform
               LOG_PRINT(LOG_MAJOR," Enable Request processed by BPM, waiting for Alarm from OIL");
               gE1Data[*e1num].trunkState = Enabled;
            }
            break;
         }
      case OAM_OIL_CFG_ALARM_IND:
         {

            LOG_PRINT(LOG_MAJOR," Alarm Received from OIL");
            // Check for the Event Received
            SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

            if( recAlarmPtr->sysalarmId == ALARM_E1_ENABLE_SUCCESS)
            {
               /*BSC R2.0 Changes Starts*/ 
               primarykey.chasisFrameId =  recAlarmPtr->key1;
               primarykey.slotId =   recAlarmPtr->key2;
							 primarykey.trunkPortId = recAlarmPtr->key3;
               LOG_PRINT(DEBUG,"ALARM_E1_ENABLE_SUCCESS Rcvd Going To update physicalTrunkortState as ACTIVATED for  frameId:%d slotId:%d portId:%d",
          primarykey.chasisFrameId,primarykey.slotId,primarykey.trunkPortId );
               updateTrunkPortOperatorControlledState(&primarykey,ACTIVATED);
               gE1Data[*e1num].trunkState = Enabled;
               
               /*BSC R2.0 Changes Starts*/ 

               #if 0
               trunkPortStsTbl.chasisFrameId =  recAlarmPtr->key1;
               trunkPortStsTbl.slotId =  recAlarmPtr->key2;
							 trunkPortStsTbl.trunkPortId =  recAlarmPtr->key3;
               if( gE1Data[*e1num].LOS_Active == TRUE)
               {
                  trunkPortStsTbl.oprStatus =  DISABLE;
                  LOG_PRINT(DEBUG,"Updating oprStt as DISABLE as LOS is Active on e1Num: %d ",*e1num);
                   SendTrunkPortDisableAlarm(trunkPortStsTbl.chasisFrameId,trunkPortStsTbl.slotId,
                                      trunkPortStsTbl.trunkPortId);
               } 
               else
               {
                   trunkPortStsTbl.oprStatus =  ENABLE;
                   LOG_PRINT(DEBUG,"Updating oprStt as ENABLE as there is LOS_Active alarm on e1Num: %d ",*e1num);
                   SendTrunkPortEnableAlarm(trunkPortStsTbl.chasisFrameId,trunkPortStsTbl.slotId,
                                      trunkPortStsTbl.trunkPortId);
               }
 
               trunkPortStsTbl.physicalPresenceState =  PRESENT;

               //Update In DB Trunk Port State to Enable 
               if( updateTrunkPortStatusTable(&trunkPortStsTbl) == CLIB_SUCCESS )
               {
                  LOG_PRINT(LOG_MAJOR, " Trunk Id = %d ENABLED/DISABLED", recAlarmPtr->key3 ); 
                  // Update the state of particular E1 instance to Enabled
                  gE1Data[*e1num].trunkState = Enabled;
                  LOG_PRINT(DEBUG,"updating TrunkState of e1Num(%d) as enabled/disabled", *e1num);
               }
               else
               {
                  LOG_PRINT(LOG_MAJOR," DB Updation failed::Enable Procedure Exits"); 
                  gE1Data[*e1num].trunkState = Disabled;
                  LOG_PRINT(DEBUG,"updating TrunkState of e1Num(%d) as diasbled", *e1num);
               }
               #endif
               SendAlarm( ALARM_E1_LOS_ACTIVE, TRAP_SEVERITY_INFORMATION, 5, *e1num );
            }

            break;

         }
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_ACTIVE_ALARM_RCVD )
            {
               //Reset LOS_Active_In_Progress flag
               gE1Data[( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId].LOS_Active_In_Progress = FALSE ;
               LOG_PRINT(LOG_INFO," LOS ACTIVE PROCEDURE ENDS");
               // Check LOS Clear Pending flag & if TRUE, proceed with LOS Clear Handling
               if( gE1Data[( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId].LOS_Clear_Pending == TRUE )
               {

                  PlatformAlarmHandler( ALARM_E1_LOS_CLEAR , &(((CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId) );
               }
            }
            break;
         }
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            if((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_CLEAR_ALARM_RCVD  )
            {
               //Reset LOS_Clear_In_Progress flag
               gE1Data[( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId].LOS_Clear_In_Progress = FALSE ;
               LOG_PRINT(LOG_INFO," LOS CLEAR PROCEDURE ENDS");
               if( gE1Data[( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId].LOS_Active_Pending == TRUE )
               {
                  PlatformAlarmHandler(ALARM_E1_LOS_ACTIVE , &(((CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId) );
               }
            }
            break;
         }
      case BSC_API_SET_TRUNKPORTTABLE: 
         {
            if( gE1Data[gE1NumberMapToTrunk].trunkState == EnableInProgress )  
            {
               LOG_PRINT(LOG_INFO,"Enable Procedure Already in Progress:: Discarding Enable Request");
               cfgSendNackToCm(CM_ERR_TRUNKPORT_ENABLE_IN_PROGRESS);
            }
            break;
         }
      default:
         LOG_PRINT(LOG_MAJOR," Unexpected Message in Enable In Progress state"); 
         break;       
   } /*switch ends here..*/
}

// CS4.0 Enable/Disable

// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       DisableInProgressHandler()
Parameters:          Pointer to E1 number
Return type:         void
Purpose:             To Handle the DisableInProgress state.
Other Note:
 ************************************************************************************/
void DisableInProgressHandler( I_U32 *e1num )
{

   LOG_PRINT(LOG_INFO,"DisableInProgressHandler e1num = %d", *e1num);
   TrunkPortTableIndices primarykey = {0};
   TrunkPortStatusTableApi *trunkPortStsTbl;
   TrunkPortStatusTableIndices trunkPortStsIndx;

   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
      case OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP:
         {

            // Case 2: Platform has send the ack, send alarm to AFH
            if((( OamOilCfgE1DisableResp* )gCfgMsgBuf)->result != OPERATION_SUCCESS || (( OamOilCfgE1DisableResp* )gCfgMsgBuf)->portResult[0].result != OPERATION_SUCCESS )
            {
               LOG_PRINT(LOG_MAJOR," Disable Request Discarded by BPM");
               SendAlarm( ALARM_E1_DISABLE_FAILURE, TRAP_SEVERITY_MAJOR, ENABLED, *e1num );            
               gE1Data[*(e1num)].trunkState = Enabled;
               LOG_PRINT(DEBUG,"updating TrunkState of e1Num(%d) as enasbled", *e1num);

            }
            else
            {
               // CFG does nothing and wait for Event from Platform
               LOG_PRINT(LOG_MAJOR," Disable Request processed by BPM, waiting for Alarm from OIL");
            }
            break;

         }
      case OAM_OIL_CFG_ALARM_IND:
         {
            // Check for the Event Received
            SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

            if( recAlarmPtr->sysalarmId == ALARM_E1_DISABLE_SUCCESS)
            {
               /*BSC R2.0 Changes Starts*/ 
               primarykey.chasisFrameId =  recAlarmPtr->key1;
               primarykey.slotId =   recAlarmPtr->key2;
							 primarykey.trunkPortId = recAlarmPtr->key3;
               LOG_PRINT(DEBUG,"ALARM_E1_DISABLE_SUCCESS Rcvd going to update physicalTrunkPort State as DEACTIVATED for port %d",primarykey.trunkPortId );
               updateTrunkPortOperatorControlledState(&primarykey,DEACTIVATED);
               /*BSC R2.0 Changes Starts*/ 

               trunkPortStsIndx.chasisFrameId =  recAlarmPtr->key1;
               trunkPortStsIndx.slotId =  recAlarmPtr->key2;
							 trunkPortStsIndx.trunkPortId =  recAlarmPtr->key3;

               if(CLIB_SUCCESS == getTrunkPortStatusTable(&trunkPortStsIndx,&trunkPortStsTbl) )
               {
                  if(trunkPortStsTbl->oprStatus == ENABLED)
                  { 
                      trunkPortStsTbl->oprStatus = DISABLED;
                     //Update In DB Trunk Port State to Disabled 
                     if(updateTrunkPortStatusTable(trunkPortStsTbl) == CLIB_SUCCESS )
                     {
                        LOG_PRINT(LOG_MAJOR, " Trunk Id = %d DISABLED", recAlarmPtr->key3 ); 
                        SendTrunkPortDisableAlarm(trunkPortStsTbl->chasisFrameId,trunkPortStsTbl->slotId,
                           trunkPortStsTbl->trunkPortId);
                     }
                     else
                     {
                        LOG_PRINT(DEBUG,"updateTrunkPortStatusTable failed for fraemId:%d,slotId:%d,TrunkId:%d",
                                trunkPortStsTbl->chasisFrameId,trunkPortStsTbl->slotId,trunkPortStsTbl->trunkPortId ); 
                     }  
                  }
                     free(trunkPortStsTbl);
               }
               else
               {
                  LOG_PRINT(LOG_MAJOR," DB get failed::Disable Procedure Exits"); 
               }
               // Updating the state of the particular E1 instance to Disabled
               gE1Data[*(e1num)].trunkState = Disabled;
               LOG_PRINT(DEBUG,"updating trunkState of e1Num(%d) as disabled", *e1num);

               // Also clear the alrams that were received while E1 was in Enabled state

               // Check for the LOS Active flag
               if( gE1Data[*(e1num)].LOS_Active == TRUE )
               {
                  //Send Clear Alarm to AFH
                  LOG_PRINT(LOG_MAJOR," Clear the active alarms that are pending corresponding to this E1"); 
                  SendAlarm( ALARM_E1_LOS_CLEAR, TRAP_SEVERITY_CLEARED, 3, *e1num );            
                  SendClearAlarms(*e1num );            
               }

            }
            break;

         }
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_ACTIVE_ALARM_RCVD )
            {
               //Reset LOS_Active_In_Progress flag
               gE1Data[( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId].LOS_Active_In_Progress = FALSE ;
               LOG_PRINT(LOG_INFO," LOS ACTIVE PROCEDURE ENDS");
               // Check LOS Clear Pending flag & if TRUE, proceed with LOS Clear Handling
               if( gE1Data[( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId].LOS_Clear_Pending == TRUE )
               {

                  PlatformAlarmHandler( ALARM_E1_LOS_CLEAR , &(( (CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId) );
               }
            }
            break;
         }
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            if((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_CLEAR_ALARM_RCVD  )
            {
               //Reset LOS_Clear_In_Progress flag
               gE1Data[( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId].LOS_Clear_In_Progress = FALSE ;
               LOG_PRINT(LOG_INFO," LOS CLEAR PROCEDURE ENDS");
               if( gE1Data[( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId].LOS_Active_Pending == TRUE )
               {
                  PlatformAlarmHandler(ALARM_E1_LOS_ACTIVE , &(( (CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId ));
               }
            }
            break;
         }
      case BSC_API_SET_TRUNKPORTTABLE: 
         {
            if( gE1Data[gE1NumberMapToTrunk].trunkState == DisableInProgress )  
            {
               LOG_PRINT(LOG_INFO,"Disable Procedure Already in Progress:: Discarding Disable Request");
               cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLE_IN_PROGRESS);
            }
            break;
         }
      default:
         LOG_PRINT(LOG_MAJOR," Unexpected Message in Disable in Progress State"); 
         break;       
   } /*switch ends here..*/
}

/********************************* Function  Header********************************
Function Name:       SendClearAlarms()
Parameters:          I_U32 e1Num
Return type:         void
Purpose:             To Handle the alarms received from platform
Other Note:
 ************************************************************************************/

I_Void SendClearAlarms(I_U32 e1Num )
{

   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
   TrunkPortTableApi  *TrunkPortDb          =  NULL;
   LOG_PRINT(LOG_MAJOR,"SendClearAlarms: Entering in Fucntion");

   OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;

   if(  getTrunkPortTableRowE1( e1Num, &TrunkPortDb )  == CLIB_SUCCESS ) 
   {
      LOG_PRINT(LOG_INFO, "SendClearAlarms: Alarm was raised on ChassisFrameId [%d],SlotId [%d],PortId [%d]",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId);
      OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  TrunkPortDb->chasisFrameId;
      OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  TrunkPortDb->slotId;
      OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  TrunkPortDb->trunkPortId;
      FillObjTypeFromSlotId(TrunkPortDb->slotId,OamsCfgAfhSysAlarmBuff.sysAlarm.info3);  
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL, "getTrunkPortTableRowE1 failed");
      return;
   }
   

   if(gE1Data[e1Num].LOS_Signal == TRUE)
   {
      LOG_PRINT(LOG_MAJOR,"SendClearAlarms: Sending INFO_MFRAMER_R_LOSS_OF_SIG_CLR_PM_OAM");
      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = INFO_MFRAMER_R_LOSS_OF_SIG_CLR_PM_OAM;
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString ,"Signal Recovered on RecvSide Framer on ChasisFrameId [%d],SlotId [%d],PortId [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1, OamsCfgAfhSysAlarmBuff.sysAlarm.key2, OamsCfgAfhSysAlarmBuff.sysAlarm.key3);
      gE1Data[e1Num].LOS_Signal = FALSE;
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   
   if(gE1Data[e1Num].LOS_Frame == TRUE)
   {
      LOG_PRINT(LOG_MAJOR,"SendClearAlarms: Sending INFO_MFRAMER_R_LOSS_OF_FRAME_CLR_PM_OAM");
      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = INFO_MFRAMER_R_LOSS_OF_FRAME_CLR_PM_OAM;
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString ,"Frame Recovered at RecvSide Framer on ChasisFrameId [%d],SlotId [%d],PortId [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1, OamsCfgAfhSysAlarmBuff.sysAlarm.key2, OamsCfgAfhSysAlarmBuff.sysAlarm.key3);
      gE1Data[e1Num].LOS_Frame = FALSE;
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }

   if(gE1Data[e1Num].LOS_Signal_detect == TRUE)
   {
      LOG_PRINT(LOG_MAJOR,"SendClearAlarms: Sending INFO_MFRAMER_LOSS_OF_SIGNAL_DETECT_CLR_PM_OAM");
      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = INFO_MFRAMER_LOSS_OF_SIGNAL_DETECT_CLR_PM_OAM;
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString ,"Signal Recovered on ChasisFrameId [%d],SlotId [%d],PortId [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1, OamsCfgAfhSysAlarmBuff.sysAlarm.key2, OamsCfgAfhSysAlarmBuff.sysAlarm.key3);
      gE1Data[e1Num].LOS_Signal_detect = FALSE;
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }

   free(TrunkPortDb);
   LOG_PRINT(LOG_MAJOR,"SendClearAlarms: Exiting from Fucntion");
}
// CS4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       PlatformAlarmHandler()
Parameters:          AlarmId & AlarmKey
Return type:         void
Purpose:             To Handle the alarms received from platform
Other Note:
 ************************************************************************************/
void PlatformAlarmHandler( I_U32 AlarmId, I_U32 *e1num )
{

   TrunkTableApi*         TrunkTableAddr           = PNULL;
   I_U32                  adminstate               = 0;
   I_U8                   res                      = 0;
   I_U32                  TimeslotAdminState       = 0;
   OamsCfgGrhmLockReq     reqMsg                   = {0};
   TrunkTableIndices      e1TableIndices           = {0};
   TrunkPortStatusTableApi *trunkPortStsTblPtr;
   ClkSourceConfigStatusTableIndices clkSrcCfg;
   ClkSourceConfigStatusTableApi *outData;
   ClkSourceConfigStatusTableApi inData;
   I_U32 oprStateAInterface = 0;
   I_U16                  trunkPortNum             = (I_U16) *e1num;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf + sizeof(SysHdr) );

   LOG_PRINT(LOG_INFO," LOS Alarm %d Received from OIL for E1 Number = %d",AlarmId, *e1num);

   /* First Set here LOS Pending flags if LOS Progress flags are set
    Code for following flags are still left
   LOS_Signal
   LOS_Frame
   LOS_Signal_detect
   Need platform support for same
   Mantis ID: 9131*/
   if( gE1Data[*e1num].LOS_Active_In_Progress == TRUE && AlarmId == ALARM_E1_LOS_CLEAR ) 
   {
      LOG_PRINT(LOG_INFO," LOS Active In Progress :: LOS Clear Received");
      gE1Data[*e1num].LOS_Clear_Pending = TRUE ;
      return;
   }
   if( gE1Data[*e1num].LOS_Clear_In_Progress == TRUE && AlarmId == ALARM_E1_LOS_ACTIVE ) 
   {
      LOG_PRINT(LOG_INFO," LOS Clear In Progress :: LOS Active Received");
      gE1Data[*e1num].LOS_Active_Pending = TRUE ;
      return;
   }

   if( AlarmId == ALARM_E1_LOS_ACTIVE && gE1Data[*e1num].LOS_Active == TRUE )
   { 
      LOG_PRINT(LOG_INFO," LOS Active Already Received :: Error Scenario LOS PROCEDURE ENDS");
      return;
   }

   e1TableIndices.e1Num = *e1num;


   if( AlarmId == ALARM_E1_LOS_ACTIVE )
   {
      // Check is LOS_Active is alreday in progress
      if(gE1Data[ *e1num ].LOS_Active_In_Progress == TRUE )
      {
         LOG_PRINT(LOG_INFO," LOS Active Already in progress :: Error Scenario LOS PROCEDURE ENDS");
         return;
      }
      else if(gE1Data[*e1num].LOS_Clear_Pending == TRUE ) // Check for LOS pending flag
      {
         LOG_PRINT(LOG_INFO," LOS Clear is pending ::LOS Active PROCEDURE ENDS");
         // Proceed with LOS Clear Procedure
      }

      if( gE1Data[*e1num].LOS_Clear_Pending != TRUE )
      {
         // Set LOS Active flag now
         gE1Data[*e1num].LOS_Active = TRUE;
         LOG_PRINT(LOG_CRITICAL, "LOS Active flag Set for E1 Number %d", *e1num );

         if(getSecTrunkPortStatusTable(trunkPortNum,&trunkPortStsTblPtr) == CLIB_SUCCESS )
         {
            trunkPortStsTblPtr->oprStatus = DISABLED;
            if(updateTrunkPortStatusTable(trunkPortStsTblPtr) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_MAJOR,"updateTrunkPortStatusTable failed for e1Num(%d)",trunkPortNum);
            } 
            LOG_PRINT(DEBUG,"updateTrunkPortStatusTable done going to send DisableAlarm");
            SendTrunkPortDisableAlarm(trunkPortStsTblPtr->chasisFrameId,
                 trunkPortStsTblPtr->slotId,trunkPortStsTblPtr->trunkPortId);
            free(trunkPortStsTblPtr); 
         }
         else
         {
            LOG_PRINT(DEBUG,"getSecTrunkPortStatusTable failed for port(%d)",
                            trunkPortNum );
         }
         /*BSC R2.3 Clock Changes Starts*/ 
         clkSrcCfg.chasisFrameId = (I_U8)recAlarmPtr->key1;
         clkSrcCfg.slotId = (I_U8)recAlarmPtr->key2;
         clkSrcCfg.trunkPortId = (I_U16)recAlarmPtr->key3;
         LOG_PRINT(DEBUG,"Going to get ClkSrcCfgSts for frame:%d,slot:%d,port:%d",
               clkSrcCfg.chasisFrameId,clkSrcCfg.slotId,clkSrcCfg.trunkPortId);
         if(CLIB_SUCCESS == getClkSourceConfigStatusTable(&clkSrcCfg,&outData))
         {
            if( outData->clkConfigStatus != PENDING) 
            {
               inData.chasisFrameId =  clkSrcCfg.chasisFrameId;
               inData.slotId = clkSrcCfg.slotId;
               inData.trunkPortId = clkSrcCfg.trunkPortId; 
               inData.clkConfigStatus =  PENDING; 
            
               updateClkSourceConfigStatusTable(&inData);
               sendClkSourcePendingAlarm(inData.chasisFrameId,inData.slotId,
                   inData.trunkPortId,ZERO);
            }
            free(outData);
         }
         /*BSC R2.3 Clock Changes Ends*/ 
      }
   }   
   else if( AlarmId == ALARM_E1_LOS_CLEAR )
   {
      // Check is LOS_Clear is alreday in progress
      if(gE1Data[*e1num].LOS_Clear_In_Progress == TRUE )
      {
         LOG_PRINT(LOG_INFO," LOS Clear Already in progress :: Error Scenario LOS PROCEDURE ENDS");
         return;
      }

      // Check if LOS Active flag is set
      if( gE1Data[*e1num].LOS_Active == FALSE )
      {
         LOG_PRINT(LOG_CRITICAL, "LOS Active flag not set::Error scenario::Disacarding LOS clear");
         return;
      }
      else
      {
         // Reset LOS Active flag & set LOS Clear In Progress Flag
         LOG_PRINT(LOG_CRITICAL, "ALARM_E1_LOS_CLEAR: LOS Active flag Reset for E1 Number %d", *e1num );
         gE1Data[*e1num].LOS_Active     = FALSE;

         if(getSecTrunkPortStatusTable(trunkPortNum,&trunkPortStsTblPtr) == CLIB_SUCCESS )
         {
            trunkPortStsTblPtr->oprStatus = ENABLED;
            if(updateTrunkPortStatusTable(trunkPortStsTblPtr) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_MAJOR,"updateTrunkPortStatusTable failed for e1Num(%d)",*e1num);
            } 
            LOG_PRINT(DEBUG,"updateTrunkPortStatusTable done going to send EnableAlarm");
            SendTrunkPortEnableAlarm(trunkPortStsTblPtr->chasisFrameId,
                 trunkPortStsTblPtr->slotId,trunkPortStsTblPtr->trunkPortId);
            free(trunkPortStsTblPtr); 
         }
         else
         {
               LOG_PRINT(DEBUG,"getSecTrunkPortStatusTable failed for port(%d)", trunkPortNum);
         }
         /*BSC R2.3 Clock Changes Starts*/ 
         clkSrcCfg.chasisFrameId = (I_U8)recAlarmPtr->key1;
         clkSrcCfg.slotId = (I_U8)recAlarmPtr->key2;
         clkSrcCfg.trunkPortId = (I_U16)recAlarmPtr->key3;
         LOG_PRINT(DEBUG,"Going to get ClkSrcCfgSts for frame:%d,slot:%d,port:%d",
               clkSrcCfg.chasisFrameId,clkSrcCfg.slotId,clkSrcCfg.trunkPortId);
         if(CLIB_SUCCESS == getClkSourceConfigStatusTable(&clkSrcCfg,&outData))
         {
            if( outData->clkConfigStatus != APPLIED) 
            {
               inData.chasisFrameId =  clkSrcCfg.chasisFrameId;
               inData.slotId = clkSrcCfg.slotId;
               inData.trunkPortId = clkSrcCfg.trunkPortId; 
               inData.clkConfigStatus =  APPLIED; 
               updateClkSourceConfigStatusTable(&inData);
               sendClkSourceAppliedAlarm(inData.chasisFrameId,inData.slotId,
                   inData.trunkPortId,ZERO);
            }
            free(outData);
         }
         #if 0
         else
         {
            inData.chasisFrameId =  clkSrcCfg.chasisFrameId;
            inData.slotId = clkSrcCfg.slotId;
            inData.trunkPortId = clkSrcCfg.trunkPortId; 
            inData.clkConfigStatus =  APPLIED; 
            updateClkSourceConfigStatusTable(&inData);
            sendClkSourceAppliedAlarm(inData.chasisFrameId,inData.slotId,
                inData.trunkPortId,ZERO);
         } 
         #endif 
         /*BSC R2.3 Clock Changes Ends*/ 
      }
   }

   if (getTrunkTable(&e1TableIndices,&TrunkTableAddr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"TrunkObjHandler: readE1Table() Failed");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }

   
   // Check for the usageType:: LOS Handling will be A-Interface E1s  
   if( TrunkTableAddr-> usageType != SYS_E1_USAGE_AIF ) 
   {
      LOG_PRINT(LOG_INFO," Usage Type is not AiF :: LOS PROCEDURE ENDS");
      SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
      free( TrunkTableAddr );
      return;

   }

   // Check for state of BSS & E1 object
   adminstate = FindState(TrunkTableAddr->adminState, *e1num );
   
   free( TrunkTableAddr);

   if( adminstate == FALSE )
   {
      LOG_PRINT(LOG_INFO," BSS/E1 is in locked state :: LOS PROCEDURE ENDS");
      SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
      return;
   }

   // Check if E1 on which LOS is received is configured for all CIC timeslots
   res = IsE1ForCIC( *e1num ); 

   if( res == TRUE ) 
      LOG_PRINT(LOG_INFO," IsE1ForCIC returns True:: E1 Configured for all CICs");


   if( res == 2 ) // Timeslot get failed in IsE1ForCIC
   {
      SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
      return;
   }

   // If result is false, check for multiple active MTP2 links
   if( res == FALSE )
   {
      // Check if MTP2 link is configured on more than one E1s
      // Two arguments are being passed::E1Number on which LOS Acive has been received
      // & integer pointer whose value will be checked after this function call to check if 
      // MTP2 Timeslot on the E1 on which LOS has been received is in LOCKED/UNLOCKED state.
      res = isMultipleMTP2LinkActive( *e1num, &TimeslotAdminState ); 

      // res = FALSE indicates Single MTP2 Timeslot is configured
      // res = TRUE indicates Multiple MTP2 Timeslots are configured but if any of MTP2 timeslot on the E1 
      // on which LOS has been received is in LOCKED state, LOS procedure will end there itself. 

      if(( res == FALSE ) || ( res == TRUE &&  TimeslotAdminState == LOCKED ) )
      {
         LOG_PRINT(LOG_INFO," Single MTP2 Timeslot is configured or MTP2 Timeslot is in locked state  :: \
               LOS PROCEDURE ENDS or CICs & MTP2 not configured on E1 on which LOS is received ");
         SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
         return;
      }

   }

    LOG_PRINT(DEBUG,"AlarmId is %d LOS_ACTIVE:%d LOS_CLEAR:%d", AlarmId,
       ALARM_E1_LOS_ACTIVE, ALARM_E1_LOS_CLEAR);
   // Handling specific to LOS Active
   if( AlarmId == ALARM_E1_LOS_ACTIVE )
   {
      // Set LOS Active flag now
      gE1Data[*e1num].LOS_Active = TRUE;
      LOG_PRINT(LOG_CRITICAL, "LOS Active flag Set for E1 Number %d", *e1num );

      if (isCicForLock(*e1num)==1)
      {
          // Preapare GRHM Lock Request
          reqMsg.objectId  = *e1num;
          reqMsg.objType   = OAMS_OBJTYPE_E1;
          reqMsg.reason    = OAMS_RSN_LOS_ACTIVE_ALARM_RCVD;
          res = cfgSendMessage(&reqMsg,sizeof(OamsCfgGrhmLockReq),ENT_CSAPP_GRHM,OAMS_CFG_GRHM_LOCK_REQ,0);
          if (res == CFG_FAILURE)
          {
             LOG_PRINT(LOG_CRITICAL, "GRHM Lock Req  send Failed");
             SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
             return;
          }
          gE1Data[*e1num].LOS_Active_In_Progress = TRUE;
      }
      SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
   }// If LOS Active

   if( AlarmId == ALARM_E1_LOS_CLEAR )
   {
      // Reset LOS Active flag & set LOS Clear In Progress Flag
      LOG_PRINT(LOG_CRITICAL, "ALARM_E1_LOS_CLEAR: LOS Active flag Reset for E1 Number %d", *e1num );
      gE1Data[*e1num].LOS_Active            = FALSE;

      getAInterfaceOprState(&oprStateAInterface); /* Check Added for Mantis 2284*/
      if(oprStateAInterface == ENABLED)
      {
         if (isCicForUnlock(*e1num) == 1)
         {
             // Prepare GRHM Unlock Request
             reqMsg.objectId        = *e1num;
             reqMsg.objType         = OAMS_OBJTYPE_E1;
             reqMsg.reason          = OAMS_RSN_LOS_CLEAR_ALARM_RCVD;
             res = cfgSendMessage(&reqMsg,sizeof(OamsCfgGrhmUnlockReq),ENT_CSAPP_GRHM,OAMS_CFG_GRHM_UNLOCK_REQ,0);
             if (res == CFG_FAILURE)
             {
                LOG_PRINT(LOG_CRITICAL, "GRHM Unlock Req  send Failed");
                SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
                return;
             }
             gE1Data[*e1num].LOS_Clear_In_Progress = TRUE;
         }
      }
      SendAlarm( AlarmId , TRAP_SEVERITY_MAJOR, 4, *e1num );            
   }// If LOS Clear
}
// CS4.0 Enable/Disable
// CS4.0 Enable/Disable

/********************************* Function  Header********************************
  Function Name:       SendAlarm()
Parameters:          AlarmId & Alarmlevel, Type of Alarm, E1 Number
Return type:         void
Purpose:             To send the alarm to AFH
Other Note:
 ************************************************************************************/
void SendAlarm( I_U32 alarmId, I_U32 alarmlevel, I_U8 info, I_U32 e1num )
{

   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};

   TrunkPortTableApi  *TrunkPortDb          =  NULL;

   I_S32              res                   = 0;  


   OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = alarmId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = alarmlevel;;


   // On the basis of E1 find Trunk Port Table row

#if 0
   if( info == ENABLED )
   {
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Trunk Port %d is Enabled",TrunkPortDb->trunkPortId);
   }
   if( info == DISABLED )
   {
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Trunk Port %d is Disabled",TrunkPortDb->trunkPortId);
   }
#endif

   if( (info == DISABLED) && (alarmId == ALARM_E1_ENABLE_FAILURE) )
   {
      if( ( res = getTrunkPortTableRowE1( e1num, &TrunkPortDb ) ) == CLIB_SUCCESS ) 
      {
         LOG_PRINT(LOG_INFO, "Port Enable On ChassisFrameId [%d],SlotId [%d],PortId [%d] Failed",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId);
         OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  TrunkPortDb->chasisFrameId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  TrunkPortDb->slotId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  TrunkPortDb->trunkPortId;
         FillObjTypeFromSlotId(TrunkPortDb->slotId,OamsCfgAfhSysAlarmBuff.sysAlarm.info3);  
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Port Enable On ChassisFrameId [%d],SlotId [%d],PortId [%d] Failed",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId );
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL, "getTrunkPortTableRowE1 failed");
      }
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   if( (info == ENABLED) && (alarmId == ALARM_E1_DISABLE_FAILURE) )
   {
      if( ( res = getTrunkPortTableRowE1( e1num, &TrunkPortDb ) ) == CLIB_SUCCESS ) 
      {
         LOG_PRINT(LOG_INFO, "Port Disable On ChassisFrameId [%d],SlotId [%d],PortId [%d] Failed",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId);
         OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  TrunkPortDb->chasisFrameId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  TrunkPortDb->slotId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  TrunkPortDb->trunkPortId;
         FillObjTypeFromSlotId(TrunkPortDb->slotId,OamsCfgAfhSysAlarmBuff.sysAlarm.info3);  
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Port Disable On ChasisFrameId [%d],SlotId [%d],PortId [%d] Failed",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId );
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL, "getTrunkPortTableRowE1 failed");
      }
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   if( info == 3 )
   {
      gE1Data[e1num].LOS_Active = FALSE;
      LOG_PRINT(LOG_CRITICAL, "LOS Active flag Reset for E1 Number %d", e1num );
      if( ( res = getTrunkPortTableRowE1( e1num, &TrunkPortDb ) ) == CLIB_SUCCESS ) 
      {
         LOG_PRINT(LOG_INFO, "Clear Active Alarms on ChassisFrameId [%d],SlotId [%d],PortId [%d] ",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId);
         OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  TrunkPortDb->chasisFrameId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  TrunkPortDb->slotId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  TrunkPortDb->trunkPortId;
         FillObjTypeFromSlotId(TrunkPortDb->slotId,OamsCfgAfhSysAlarmBuff.sysAlarm.info3);  
       /* String added for issue #9131 */
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Framer Port Up on ChasisFrameId [%d],SlotId [%d],PortId [%d]",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId );
//OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Clear Active Alarms on ChasisFrameId [%d],SlotId [%d],PortId [%d]",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId );
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL, "getTrunkPortTableRowE1 failed");
      }
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   if( info == 4  && alarmId == ALARM_E1_LOS_ACTIVE )
   {

      // Set the LOS Active flag

      if( gE1Data[e1num].LOS_Active != TRUE )
      {
         gE1Data[e1num].LOS_Active = TRUE;
         LOG_PRINT(LOG_CRITICAL, "LOS Active flag Set for E1 Number %d", e1num );
      }
      if(gE1Data[e1num].LOS_Active_Pending == TRUE )
         gE1Data[e1num].LOS_Active_Pending = FALSE;

      //OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"LOS_Active Alarm Received",TrunkPortDb->trunkPortId);
   }

   if( info == 4  && alarmId == ALARM_E1_LOS_CLEAR )
   {

      // Set the LOS Active flag
      if( gE1Data[e1num].LOS_Active == TRUE )
      {
         gE1Data[e1num].LOS_Active = FALSE;
         LOG_PRINT(LOG_CRITICAL, "LOS Active flag Reset for E1 Number %d", e1num );
      }
      if(gE1Data[e1num].LOS_Clear_Pending == TRUE )
         gE1Data[e1num].LOS_Clear_Pending = FALSE;

      //OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"LOS_Clear Alarm Received",TrunkPortDb->trunkPortId);
   }
   if(info == 5 )
   {
      gE1Data[e1num].LOS_Active = TRUE;
      LOG_PRINT(LOG_CRITICAL, "LOS Active flag Set for E1 Number %d", e1num );
      if( ( res = getTrunkPortTableRowE1( e1num, &TrunkPortDb ) ) == CLIB_SUCCESS ) 
      {
         LOG_PRINT(LOG_INFO, "Clear Active Alarms on ChassisFrameId [%d],SlotId [%d],PortId [%d] ",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId);
         OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  TrunkPortDb->chasisFrameId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  TrunkPortDb->slotId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  TrunkPortDb->trunkPortId;
         FillObjTypeFromSlotId(TrunkPortDb->slotId,OamsCfgAfhSysAlarmBuff.sysAlarm.info3);  
       /* String added for issue #9131 */
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Framer Port Down on ChasisFrameId [%d],SlotId [%d],PortId [%d]",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId );
//OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Clear Active Alarms on ChasisFrameId [%d],SlotId [%d],PortId [%d]",TrunkPortDb->chasisFrameId,TrunkPortDb->slotId, TrunkPortDb->trunkPortId );
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL, "getTrunkPortTableRowE1 failed");
      }
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }


   free(TrunkPortDb);
}


// CS 4.0 Enable/Disable
/********************************* Function  Header********************************
  Function Name:       setTrunkPortTable()
Parameters:          void
Return type:         void
Purpose:             To  handle BSC_API_SET_TRUNKPERTABLE message for Enable/Disable E1.
Other Note:
 ************************************************************************************/

void   setTrunkPortTable()
{ 
   TrunkPortTableApi *TrunkObjPtr              = NULL; 
   sCmMsg* receivedCmMsgPtr                    = NULL;
   receivedCmMsgPtr                            = ( sCmMsg* )gCfgMsgBuf;
   TrunkObjPtr                                 = (TrunkPortTableApi *)( ((I_U8 *)receivedCmMsgPtr)+sizeof(sCmMsg));
   OamsCfgOilE1EnableReq  enablereq            = {0};
   OamsCfgOilE1DisableReq disablereq           = {0};
   TrunkTableIndices e1TableIndices            = {0};

   // Pointers to Point the Database objects
   TrunkTableApi        *e1ObjFromDbPtr           = NULL;
   I_U8 res                                       = 1;

   I_U8 clkcfg                                    = FALSE;
   I_Bool status                                  = FALSE;



   // Perform range check & update TrunkPort Details in DB

   if( TrunkObjPtr->trunkFramingOption != BPM_TRUNK_FRAMING_OPT_T1_D4 && TrunkObjPtr->trunkFramingOption != \
         BPM_TRUNK_FRAMING_OPT_T1_ESF && TrunkObjPtr->trunkFramingOption != BPM_TRUNK_FRAMING_OPT_E1_CRC4 &&\
         TrunkObjPtr->trunkFramingOption != BPM_TRUNK_FRAMING_OPT_E1_NOCRC4 )
   {
      TrunkObjPtr->trunkFramingOption = BPM_TRUNK_FRAMING_OPT_INVALID; 
   }

   if( TrunkObjPtr->encodeType != BPM_TRUNK_ENCODE_OPT_T1_E1_AMI && TrunkObjPtr->encodeType != \
         BPM_TRUNK_ENCODE_OPT_T1_B8ZS && TrunkObjPtr->encodeType != BPM_TRUNK_ENCODE_OPT_E1_HDB3 )
   {
      TrunkObjPtr->encodeType = BPM_TRUNK_ENCODE_TYPE_INVALID; 
   }

   // Perform Range check for loop type
   if( TrunkObjPtr->loopType != BPM_REMOTE_LOOPBACK  && \
       TrunkObjPtr->loopType != BPM_LOCAL_LOOPBACK &&\
       TrunkObjPtr->loopType != BPM_PAYLOAD_LOOPBACK && \
       TrunkObjPtr->loopType != BPM_FRAMER_LOOPBACK &&\
       TrunkObjPtr->loopType != BPM_ANALOG_LOOPBACK )
   {
      TrunkObjPtr->loopType = BPM_LOOPBACK_INVALID; 
   }

   // Perform range check for loop back value
   if( TrunkObjPtr->loopback != BPM_TRUNK_LOOPBACK_ENABLE  && \
       TrunkObjPtr->loopback != BPM_TRUNK_LOOPBACK_DISABLE )
   {
      LOG_PRINT(LOG_INFO,"Invalid loop back value::Enable/Disable Procedure ends");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      return;
   }

#if 0
   if( TrunkObjPtr->sigStrength != BPM_TRUNK_SIG_STRENGH_0 && TrunkObjPtr->sigStrength != \
         BPM_TRUNK_SIG_STRENGH_1 && TrunkObjPtr->sigStrength != BPM_TRUNK_SIG_STRENGH_2 &&\
         TrunkObjPtr->sigStrength != BPM_TRUNK_SIG_STRENGH_3 && TrunkObjPtr->sigStrength != BPM_TRUNK_SIG_STRENGH_4 )
   {
      TrunkObjPtr->sigStrength = BPM_TRUNK_SIG_STRENGTH_INVALID; 
   }
#endif


   // Check for the correct scenario :: Enable/Disable
   switch (TrunkObjPtr->physicalTrunkPortState)
   {
      case   ACTIVATED:  // Request for Enable
         { 
            LOG_PRINT(DEBUG,"ACTIVATE TrunkPort Req is Rcvd");
            if ( gTrunkAdminStateinDB == DEACTIVATED ) 
            {

               LOG_PRINT(DEBUG,"ACTIVATE TrunkPort Req Rcvd gTrunkAdminStateinDB is DEACTIVATED"); 
               // Perform Validity Checks before sending Ack to CM


               if( g_card_in_standby_mode == TRUE || g_card_in_recovery_mode == TRUE )
               {
                  LOG_PRINT(LOG_INFO,"Card State Change In Progress:: Discarding Enable Request");
                  cfgSendNackToCm(CM_ERR_CARD_STATE_CHANGE_IN_PROGRESS);
                  res = 0;
               }

               if( !res )
               {
                  return;
               }
               else
               {
                  /* Changes For E1-T1 : Start */
                  status = trunkPortTableRangeChk(TrunkObjPtr); 
                  if(status == FALSE)
                  { 
                     LOG_PRINT(LOG_MAJOR,"Enable/Disable:: Range Check of Received TrunkPort \
                         Enable Request is Failed");
                     cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
                     return;
                  }
                  else
                  {  
                     // Send Ack to CM
                     cfgSendAckToCm(CM_SUCCESS);
                  }
                 /* Changes For E1-T1 : End */
               }

               // Update in DB Trunk Details
               res =updateTrunkDetails( TrunkObjPtr->trunkPortId, TrunkObjPtr->trunkFramingOption, TrunkObjPtr->encodeType ,TrunkObjPtr->loopType, TrunkObjPtr->loopback);

               if( res != CLIB_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"Enable/Disable:: Trunk Details not updated");
               }  

               // Prepare the Enable Request to be sent to OIL

               enablereq.numPorts                                     = 1; 
               enablereq.transactionId                                = gE1NumberMapToTrunk;
               enablereq.portDetail[0].frameId                        = g_TrunkPortDb.chasisFrameId ;
               enablereq.portDetail[0].slotId                         = g_TrunkPortDb.slotId;
               enablereq.portDetail[0].trunkPortId                    = g_TrunkPortDb.trunkPortId;
               enablereq.portDetail[0].operatorControlledTrunkState   = ENABLED; // ENABLED 
               enablereq.portDetail[0].trunkType                      = g_TrunkPortDb.trunkType;
               enablereq.portDetail[0].loopType                       = TrunkObjPtr->loopType;
               enablereq.portDetail[0].loopback                       = TrunkObjPtr->loopback;
               enablereq.portDetail[0].trunkFrameOption               = TrunkObjPtr->trunkFramingOption;
               enablereq.portDetail[0].encodeType                     = TrunkObjPtr->encodeType;
               enablereq.portDetail[0].sigStrength                    = TrunkObjPtr->sigStrength;


               res = cfgSendMessage(&enablereq,sizeof(enablereq),ENT_OAM_OIL, OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ,0);

               if( res != 0 )
               {

                  LOG_PRINT(LOG_INFO,"cfgSendCmMessage failed::Enable/Disable Procedure ends");
                  return;
               }

               LOG_PRINT(LOG_INFO,"Enable Request Sent to OIL Transaction Id = %d", gE1NumberMapToTrunk);

               LOG_PRINT(LOG_INFO,"Enable Request sent to OIl::Going to EnableinProgress state");

               // Going to state Enable in Progress
               gE1Data[gE1NumberMapToTrunk].trunkState = EnableInProgress;
               LOG_PRINT(DEBUG,"updating TrunkState of e1Num(%d) as enableInProgress", gE1NumberMapToTrunk);


            }
            else
            {
               LOG_PRINT(DEBUG,"ACTIVATE TrunkPort Req Rcvd gTrunkAdminStateinDB is not DEACTIVATED but %d ",
                           gTrunkAdminStateinDB ); 
            }  
         }
         
         break;

      case   DEACTIVATED:  /*Request for Disable*/
         { 
            LOG_PRINT(DEBUG,"DEACTIVATE TrunkPort Req is Rcvd");
            if ( gTrunkAdminStateinDB == ACTIVATED )
            {
                LOG_PRINT(DEBUG,"gTrunkAdminStateinDB is ACTIVATED in DEACTIVATE req");

               // Perform Validity Checks before sending Ack to CM

               // Check if clock source is configured on the port on which Disable request is received
               clkcfg = IsTrunkPortConfiguredAsClkSrc(gE1NumberMapToTrunk); 

               if(TRUE == clkcfg)
               {
                  LOG_PRINT(LOG_INFO,"Clock source configured on Trunk port:: Discarding Disable Request");
                  cfgSendNackToCm(CM_ERR_CLK_SRC_CONFIGURED_ON_TRUNKPORT);
                  return;
               }
							/*Mantis-8083 Start*/
							if (!AreAllLinksLockedOnGivenTrunkPortID(gE1NumberMapToTrunk))
							{
									  LOG_PRINT(LOG_DEBUG,"link is in unlocked state :: Discarding Disable Request");
									  cfgSendNackToCm(CM_ERR_LINK_NOT_LOCKED);
									  return;
							}
							/*Mantis-8083 End*/

							/*Mantis-9735 Start*/
							if (!AreAllCICsLockedOnGivenE1Num(gE1NumberMapToTrunk))
							{
									  LOG_PRINT(LOG_DEBUG,"Cic is in unlocked state :: Discarding Disable Request");
									  cfgSendNackToCm(CM_ERR_TRUNK_CICS_NOT_LOCKED);
									  return;
							}
							/*Mantis-9735 End*/

               if( g_card_in_standby_mode == TRUE || g_card_in_recovery_mode == TRUE )
               {
                  LOG_PRINT(LOG_INFO,"Card State Change In Progress:: Discarding Disable Request");
                  cfgSendNackToCm(CM_ERR_CARD_STATE_CHANGE_IN_PROGRESS);
                  res = 0;
               }

               // Check if logical E1 number is unlocked or unlock is in progress
               e1TableIndices.e1Num = gE1NumberMapToTrunk;

               if (getTrunkTable(&e1TableIndices,&e1ObjFromDbPtr) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_CRITICAL,"TrunkObjHandler: readE1Table() Failed");
                  cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
                  return;
               }
               else
               {
                  // Mantis 6745
                  if(gE1Data[gE1NumberMapToTrunk].e1State == lockInProgress )
                  {
                     res = 0;
                     LOG_PRINT(LOG_CRITICAL,"TrunkObjHandler: E1 in lock in progress state, sending NACK");
                     cfgSendNackToCm(CM_ERR_E1_LOCK_IN_PROGRESS);
                  }
                  else if(gE1Data[gE1NumberMapToTrunk].e1State == unlockInProgress )
                  {
                     res = 0;
                     LOG_PRINT(LOG_CRITICAL,"TrunkObjHandler: E1 in unlock in progress state, sending NACK");
                     cfgSendNackToCm(CM_ERR_E1_UNLOCK_IN_PROGRESS);
                  }
                  else if( e1ObjFromDbPtr->adminState == UNLOCKED )
                  {
                     res = 0;
                     LOG_PRINT(LOG_CRITICAL,"TrunkObjHandler: E1 in unlocked, sending NACK");
                     cfgSendNackToCm(CM_ERR_E1_IN_UNLOCKED_STATE);

                  }
                  else
                  {
                     ;// Do nothing
                  }

                  free(e1ObjFromDbPtr);

               }

               if( !res )
               {
                  return;
               }
               else
               {
                  // Send Ack to CM
                  cfgSendAckToCm(CM_SUCCESS);
               }
               
               #if 0
               if(TrunkObjPtr->usageType == SYS_E1_USAGE_ABISIF) 
               {
                   TrunkObjPtr->usageType = SYS_E1_USAGE_NONE;
                   updateUsageTypeAbisToFree(SYS_E1_USAGE_ABISIF); 
               }
               else if(TrunkObjPtr->usageType == SYS_E1_USAGE_AIF)
               {
                   TrunkObjPtr->usageType = SYS_E1_USAGE_NONE;
                   updateUsageTypeAifToFree();
               }    
               #endif
               // Prepare the Disable Request to be sent to OIL

               disablereq.numPorts                                     = 1; 
               disablereq.transactionId                                = gE1NumberMapToTrunk;
               disablereq.portDetail[0].frameId                        = g_TrunkPortDb.chasisFrameId ;
               disablereq.portDetail[0].slotId                         = g_TrunkPortDb.slotId;
               disablereq.portDetail[0].trunkPortId                        = g_TrunkPortDb.trunkPortId;
               disablereq.portDetail[0].operatorControlledTrunkState   = DISABLED; // DISABLED 
               disablereq.portDetail[0].trunkType                      = g_TrunkPortDb.trunkType;
               disablereq.portDetail[0].loopType                       = TrunkObjPtr->loopType;
               disablereq.portDetail[0].loopback                       = TrunkObjPtr->loopback;
               disablereq.portDetail[0].trunkFrameOption               = TrunkObjPtr->trunkFramingOption;
               disablereq.portDetail[0].encodeType                     = TrunkObjPtr->encodeType;
               disablereq.portDetail[0].sigStrength                    = TrunkObjPtr->sigStrength;


               LOG_PRINT(DEBUG,"Size of disablereq = %d", sizeof(disablereq));      
               res = cfgSendMessage(&disablereq,sizeof(disablereq),ENT_OAM_OIL, OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ,0);
               if( res != 0 )
               {
                  LOG_PRINT(LOG_INFO,"cfgSendCmMessage failed::Enable/Disable Procedure ends");
                  return;
               }
               LOG_PRINT(LOG_INFO,"Disable Request sent to OIl::Going to DisableinProgress state");

               // Going to state Disable in Progress
               LOG_PRINT(LOG_INFO,"gE1NumberMapToTrunk = %d", gE1NumberMapToTrunk);
               gE1Data[gE1NumberMapToTrunk].trunkState = DisableInProgress;
               LOG_PRINT(DEBUG,"updating TrunkState of e1Num(%d) as disableInProgress", gE1NumberMapToTrunk);


            }// if
            else
            {
               LOG_PRINT(DEBUG,"DEACTIVATE TrunkPort Req Rcvd gTrunkAdminStateinDB is not ACTIVATED but %d ",
                           gTrunkAdminStateinDB ); 
            }

         }// case
         break;
   }// switch
}

// CS 4.0 Enable/Disable


/********************************* Function  Header********************************
  Function Name:       setE1Table()
Parameters:          void
Return type:         void
Purpose:             To  handle BSC_API_SET_TRUNKPERTABLE message for Lock/Unlock E1.
Other Note:
 ************************************************************************************/

void   setE1Table()
{ 
   TrunkTableApi *e1ObjPtr; /* Pointer to point Reveved Message.*/
   sCmMsg* receivedCmMsgPtr = 0;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   e1ObjPtr = (TrunkTableApi *)( ((I_U8 *)receivedCmMsgPtr)+sizeof(sCmMsg)); /* pointing to the recieved message*/
   /*Pointers to Point the Database objects..*/
   TrunkTableApi *e1ObjFromDbPtr;/*To point the e1 Object from DB.*/
   TrunkTableIndices e1TableIndices;
   I_U32 oprStateAInterface = 0;

   /*read E1Table.. */
   e1TableIndices.e1Num = e1ObjPtr->e1Num;
   if (getTrunkTable(&e1TableIndices,&e1ObjFromDbPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"E1ObjHandler: readE1Table() Failed");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   if(e1ObjFromDbPtr->trunkPortId == INVALID_TRUNK_ID)
   {
      LOG_PRINT(LOG_CRITICAL,"setE1Table: E1 Mapping is not created");
      free(e1ObjFromDbPtr);
      cfgSendNackToCm(CM_ERR_E1_MAP_NOT_CREATED);
      return;
   }
   if(isE1RequestValid(e1ObjPtr->e1Num) != CFG_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"setE1Table: E1 validation check failed");
      free(e1ObjFromDbPtr);
      return;
   }

   switch (e1ObjPtr->adminState)
   {
      case   LOCKED:  /*Request for Lock..*/
         { 
            if ((e1ObjFromDbPtr->adminState == UNLOCKED) && (e1ObjPtr->adminState == LOCKED))  /*valid Scenario...*/
            {
               /* Change For CS2.2 : Start */
               if(e1ObjFromDbPtr->usageType == SYS_E1_USAGE_ABISIF )
               {
                  /*Changes for CS4.0 : Abis E1 Lock/Unlock Start*/
                  /*LOG_PRINT(LOG_INFO,"E1 is Configured For Abis.Lock Not Allowed");
                    LOG_PRINT(LOG_DEBUG,"Sending CM_ERR_OPERATION_NOT_ALLOWED %d", CM_ERR_OPERATION_NOT_ALLOWED);
                    cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
                    free(e1ObjFromDbPtr);
                    return;*/
                  abisE1LockUnlock(e1ObjPtr);
                  free(e1ObjFromDbPtr);
                  return;
                  /*Changes for CS4.0 :Abis E1 Lock/Unlock Ends*/
               }
               /* Change For CS2.2 : End */

               /*Code Added by Sanjeev for Mantis #1916 Start..*/
               if (gBssState == lockInProgress)
               {
                  /*As BSS LOCK in Progress...*/ 
                  LOG_PRINT(LOG_INFO,"As BSS is in Lock in progress, E1 Lock is not Possible..");
                  /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
                  cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
                  free(e1ObjFromDbPtr);   
                  return; 
               }   
               if (gBssState == unlockInProgress)
               {
                  /*As BSS UNLOCK is in Progress...*/ 
                  LOG_PRINT(LOG_INFO,"As BSS is in unlock in progress, E1 Lock is not Possible..");
                  /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
                  cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
                  free(e1ObjFromDbPtr);   
                  return; 
               }  

               /*Send CM_APPI_RESPONSE  as CM_SUCCESS*/
               cfgSendAckToCm(0);
               if(gBssState == locked)
               {
                  /*Update E1 Admin state and send Alarm*/ 
                  LOG_PRINT(LOG_INFO,"As BSS is LOCKED So Only Adminstate for E1 will be Updated");
                  e1ObjectUpdateAdminStateAndSendAlarm(LOCKED);
                  free(e1ObjFromDbPtr);   
                  return; 
               }   

               if ((e1ObjFromDbPtr->usageType == SYS_E1_USAGE_AIF)&&
                     (e1ObjPtr->usageType == SYS_E1_USAGE_AIF))
               {
                  if (isMtp2ForLock(e1ObjPtr->e1Num)==1) 
                     sendE1MessageToSCM(LOCKED);/*LOCK*/
                  if (isCicForLock(e1ObjPtr->e1Num)==1)
                     sendE1MessageToGRHM(LOCKED); /*LOCK*/
                  if (isFrTimeslot(e1ObjPtr->e1Num) == TRUE)
/*Changes PCU R2.5 Aricent -- START*/
                  {
                     /* CFG will execute Lock (Enabled) Nsvc procedure 
                        for all the Unlocked and Enabled Nsvcs for this E1*/
                     /*Mantis 13886 start*/
                     if(I_TRUE == initiateNsvcLockDisableForUnlockedNsvcsForE1(e1ObjPtr->e1Num))
                     {
                        LOG_PRINT(LOG_INFO, " setting e1State to lockInProgress for e1 = %u", e1ObjPtr->e1Num);
                        gE1Data[e1ObjPtr->e1Num].e1State=lockInProgress;
                        gE1Data[e1ObjPtr->e1Num].msgsSentForE1++;
                     }
                     /*Mantis 13886 end*/
                  }
/*Changes PCU R2.5 Aricent -- END*/
                  if (  gE1Data[e1ObjectInstanceIndex].msgsSentForE1 == 0 )
                  {
                     e1ObjectUpdateAdminStateAndSendAlarm(LOCKED);
                  }
               }
               else
                  cfgSendNackToCm(CM_ERR_E1_USAGE_TYPE_NOT_AIF);
            }
            else
            {
               /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
            }
         } 
         break;

      case  UNLOCKED:   /*Request for Unlock..*/
         {     
            if ((e1ObjFromDbPtr->adminState == LOCKED) && (e1ObjPtr->adminState == UNLOCKED))  /*valid Scenario...*/
            {
               /* Change For CS2.2 : Start */
               if(e1ObjFromDbPtr->usageType == SYS_E1_USAGE_ABISIF ) 
               {
                  /* Changes for CS4.0 :Abis E1 Lock/Unlock Start*/
                  /*LOG_PRINT(LOG_INFO,"E1 is Configured For Abis.UnLock Not Allowed");
                    LOG_PRINT(LOG_DEBUG,"Sending CM_ERR_OPERATION_NOT_ALLOWED %d", CM_ERR_OPERATION_NOT_ALLOWED);
                    cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
                    free(e1ObjFromDbPtr);
                    return;*/
                  abisE1LockUnlock(e1ObjPtr);
                  free(e1ObjFromDbPtr);
                  return;

                  /*Changes for CS4.0 :Abis E1 Lock/Unlock Ends*/
               }
               /* Change For CS2.2 : End */

               if (gBssState == lockInProgress)
               {
                  /*As BSS LOCK in Progress...*/ 
                  LOG_PRINT(LOG_INFO,"As BSS is in Lock in progress, E1 Unlock is not Possible..");
                  /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
                  cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
                  free(e1ObjFromDbPtr);   
                  return; 
               }   
               if (gBssState == unlockInProgress)
               {
                  /*As BSS UNLOCK is in Progress...*/ 
                  LOG_PRINT(LOG_INFO,"As BSS is in unlock in progress, E1 Unlock is not Possible..");
                  /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
                  cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
                  free(e1ObjFromDbPtr);   
                  return;
               }  

               /*Send CM_APPI_RESPONSE  as CM_SUCCESS*/
               cfgSendAckToCm(0);
               if(gBssState == locked)
               {
                  /*Update E1 Admin state and send Alarm*/
                  LOG_PRINT(LOG_INFO,"As BSS is LOCKED So Only Adminstate for E1 will be Updated");
                  e1ObjectUpdateAdminStateAndSendAlarm(UNLOCKED);
                  free(e1ObjFromDbPtr);   
                  return;
               }

               if (e1ObjFromDbPtr->usageType == SYS_E1_USAGE_AIF) /* removed check of usage type in received message because in this case we are interested only in adminState parameter*/
               {
                  if (isMtp2ForUnlock(e1ObjPtr->e1Num) == 1) 
                     sendE1MessageToSCM(UNLOCKED);/*UNLOCK*/

                  getAInterfaceOprState(&oprStateAInterface); /* Check Added for Mantis 2284*/
                  if(oprStateAInterface == ENABLED)
                  {
                     if (isCicForUnlock(e1ObjPtr->e1Num) == 1)
                        {
                             if(gE1Data[e1ObjPtr->e1Num].LOS_Active == FALSE)/* Fix for Mantis 8274*/
                             {
                                 LOG_PRINT(LOG_INFO,"As LOS is NOT ACTIVE on E1: so UNBLOCK the CICs")
                                 sendE1MessageToGRHM(UNLOCKED);/*UNLOCK*/
                             }
                             if(gE1Data[e1ObjPtr->e1Num].LOS_Active == TRUE)
                             {
                                 LOG_PRINT(LOG_INFO,"As LOS is ACTIVE on E1 So Only Adminstate for E1 will be Updated")
                                 
                                 /*if (insertTrunkTable(trunkTablePtr) != CLIB_SUCCESS)
                                 {
                                   LOG_PRINT(LOG_CRITICAL,"In unblockCicsRespHandler: insertTrunkTable Failed..");
                                   setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
                                 }
                                 return;*/

                                 e1ObjectUpdateAdminStateAndSendAlarm(UNLOCKED);
                                 free(e1ObjFromDbPtr);   
                                 return;
                             }
                        
                        }
                  }
                  if (isFrTimeslot(e1ObjPtr->e1Num) == TRUE)
/*Changes PCU R2.5 Aricent -- START*/
                  {
                     /* CFG will execute Unlocked (Enabled) Nsvc procedure 
                        for all the Unlocked and Disabled Nsvcs for this E1*/
                     /*Mantis 13886 start*/
                     if(I_TRUE == initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1(e1ObjPtr->e1Num))
                     {
                        LOG_PRINT(LOG_INFO, " setting e1State to unlockInProgress for e1 = %u", e1ObjPtr->e1Num);
                        gE1Data[e1ObjPtr->e1Num].e1State=unlockInProgress;
                        gE1Data[e1ObjPtr->e1Num].msgsSentForE1++;
                     }
                     /*Mantis 13886 end*/
                  }
/*Changes PCU R2.5 Aricent -- END*/

                  if (  gE1Data[e1ObjectInstanceIndex].msgsSentForE1 == 0 )
                  {
                     e1ObjectUpdateAdminStateAndSendAlarm(UNLOCKED);
                  }
               }      
               else
                  cfgSendNackToCm(CM_ERR_E1_USAGE_TYPE_NOT_AIF);
            }         
            else
            {
               /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
               LOG_PRINT(LOG_INFO," Invalid scenario :setE1Table()"); 
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
            }
         }
         break;
   }
   /*free the db pointer..*/
   free(e1ObjFromDbPtr);
}/*end setE1Table()*/

/********************************* Function  Header********************************
  Function Name:       sendE1MessageToSCM()
Parameters:          I_U16  
Return type:         void
Purpose:             To Send lock/unlock request to SCM for MTP2.
Other Note:
 ************************************************************************************/

void sendE1MessageToSCM(I_U16 reqType)
{
   I_S8 i;
   sCmMsg* receivedCmMsgPtr = 0;
   TrunkTableApi *e1ObjPtr;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   e1ObjPtr = (TrunkTableApi *)( ((I_U8 *)receivedCmMsgPtr)+sizeof(sCmMsg)); /* pointing to the recieved message*/
   /* CS4.0 HA Stack Changes : Start */
#if 0
   I_U32 count=0;
   I_U16 outSize = 0;
   AbisTimeSlotPerTableApi *timeSlotObjPtr;/*To point the timeslot Object from DB.*/
   AbisTimeSlotPerTableApi *t;
   /*read TimeSlotTable*/
   if (getallAbisTimeSlotPerTable(&timeSlotObjPtr,&count,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "E1ObjHandler: getallAbisTimeSlotPerTable() Failed");
      LOG_PRINT(LOG_INFO, " Returning from function sendE1MessageToSCM because of db get - getallAbisTimeSlotPerTable Error ");
      return;
   }
#endif
   LinkTableApi *linkTablePtr = NULL;
   LinkTableApi *tempLinkPtr = NULL;
   I_U32 noOfRows = 0;
   I_U16 rowSize = 0;
   objectState state;

   if (getallLinkTable(&linkTablePtr, &noOfRows, &rowSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "E1ObjHandler: getallLinkTable() Failed");
      LOG_PRINT(LOG_INFO, " Returning from function sendE1MessageToSCM because of db get - getallLinkTable Error ");
      return;
   }
   /* CS4.0 HA Stack Changes : End */
   state = getE1ObjectState(e1ObjPtr->e1Num);
   gE1Data[e1ObjectInstanceIndex].msgsSentForE1 =0;
   gLinkMsgSentForE1 = 0;
   gE1NumberMapToTrunk = e1ObjPtr->e1Num; 
   switch (reqType)
   {
      case LOCKED:
         {
            /*Lock*/
            /* CS4.0 HA Stack Changes : Start */
#if 0
            for (i = 0; i < count; i++)
            {
               t = (AbisTimeSlotPerTableApi*)((char*)timeSlotObjPtr + (i *outSize));  
               if (e1ObjPtr->e1Num == t->e1Num)
               {
                  if ((t->usageType == SYS_TS_USAGE_MTP2) && (t->adminState == UNLOCKED))
                  {
                     e1SendLinkAdminTableToScm(t,reqType);
                  }
               }       
            }
#endif
            for (i = 0; i <noOfRows; i++)
            {
               tempLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (i *rowSize));
               if(e1ObjPtr->e1Num == tempLinkPtr->e1Num && tempLinkPtr->adminState == UNLOCKED)
               {
                  gLinkMsgSentForE1++;
                  e1SendLinkAdminTableToScm(tempLinkPtr,reqType);
                  break;
               }
            }
            free(linkTablePtr);
            /* CS4.0 HA Stack Changes : End */
            gE1Data[e1ObjectInstanceIndex].e1State=lockInProgress;
         }

         break;

      case UNLOCKED:
         {
            /*Unlock*/
            /* CS4.0 HA Stack Changes : Start */
#if 0
            for (i = 0; i < count; i++)
            {
               t = (AbisTimeSlotPerTableApi*)((char*)timeSlotObjPtr + (i *outSize));  
               if (e1ObjPtr->e1Num == t->e1Num)
               {
                  if (t->usageType == SYS_TS_USAGE_MTP2 && t->adminState == UNLOCKED)
                  {
                     e1SendLinkAdminTableToScm(t,reqType);
                  }
               }       
            }
#endif
            for (i = 0; i <noOfRows; i++)
            {
               tempLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (i *rowSize));
               if(e1ObjPtr->e1Num == tempLinkPtr->e1Num && tempLinkPtr->adminState == UNLOCKED)
               {
                  gLinkMsgSentForE1++;
                  e1SendLinkAdminTableToScm(tempLinkPtr,reqType);
                  break;
               }
            }
            free(linkTablePtr);
            /* CS4.0 HA Stack Changes : End */
            gE1Data[e1ObjectInstanceIndex].e1State=unlockInProgress;
         }
         break;
   }
#if 0
   /*free the db pointer*/
   free(timeSlotObjPtr);
#endif
   return; 
}/*end setE1ScmLock*/

/********************************* Function  Header********************************
  Function Name:       sendE1MessageToGRHM()
Parameters:            I_U16
Return type:            void
Purpose:                 To Send lock request to GRHM for CIC.
Other Note:
 ************************************************************************************/
void sendE1MessageToGRHM(I_U16 reqType)
{
   I_S32  rval;
   I_U32 size; 
   sCmMsg* receivedCmMsgPtr = 0;
   TrunkTableApi *e1ObjPtr;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   e1ObjPtr=(TrunkTableApi *)( ((I_U8 *)receivedCmMsgPtr)+sizeof(sCmMsg)); /* pointing to the recieved message*/

   switch (reqType)
   {
      case LOCKED:
         {
            /*Lock*/
            OamsCfgGrhmLockReq lockReqToGrhm;  
            /************* fix for mantis-1797 ***********************/
            memset(&lockReqToGrhm,0,sizeof(OamsCfgGrhmLockReq));
            /**********************************************************/
            lockReqToGrhm.objectId = e1ObjPtr->e1Num;
            lockReqToGrhm.objType = OAMS_OBJTYPE_E1;
            lockReqToGrhm.reason = OAMS_RSN_OPERATORINITIATED;
            size = sizeof(OamsCfgGrhmLockReq);
            rval = cfgSendMessage(&lockReqToGrhm,size,ENT_CSAPP_GRHM,OAMS_CFG_GRHM_LOCK_REQ,0);
            if (rval == CFG_FAILURE)
            {
               LOG_PRINT(LOG_CRITICAL, "E1ObjHandler:setE1GrhmLock,CFG_GRHM_LOCK_REQ Failed");
            }
            if (rval == CFG_SUCCESS)
            {
               gE1Data[e1ObjectInstanceIndex].msgsSentForE1++;
               LOG_PRINT(LOG_INFO, "E1ObjHandler:setE1GrhmLock,CFG_GRHM_LOCK_REQ SUCCESS");
               gE1Data[e1ObjectInstanceIndex].e1State=lockInProgress;
            }       
         }
         break;

      case UNLOCKED:
         {   
            /*Unlock*/
            OamsCfgGrhmUnlockReq unlockReqToGrhm;        
            unlockReqToGrhm.objectId = e1ObjPtr->e1Num;
            unlockReqToGrhm.objType = OAMS_OBJTYPE_E1;
            unlockReqToGrhm.reason = OAMS_RSN_OPERATORINITIATED;
            size = sizeof(OamsCfgGrhmUnlockReq);
            rval = cfgSendMessage(&unlockReqToGrhm,size,ENT_CSAPP_GRHM,OAMS_CFG_GRHM_UNLOCK_REQ,0);
            if (rval == CFG_FAILURE)
            {
               LOG_PRINT(LOG_CRITICAL, "E1ObjHandler:setE1GrhmUnlock,CFG_GRHM_UNLOCK_REQ Failed");
            }
            if (rval == CFG_SUCCESS)
            {
               gE1Data[e1ObjectInstanceIndex].msgsSentForE1++;
               LOG_PRINT(LOG_INFO, "E1ObjHandler:setE1GrhmUnlock,CFG_GRHM_UNLOCK_REQ SUCCESS");
            }
            gE1Data[e1ObjectInstanceIndex].e1State=unlockInProgress;   
         }
         break;
   }
}/*setE1GrhmLock*/

/********************************* Function  Header********************************
 ********************************* Function  Header********************************
 Function Name:       cfgScmLockLinkAdmStTblResp()
Parameters:          void
return type:         void
Purpose:             To  handle BSC_API_SET_LINKADMINSTATE message.
Other Note:
 ************************************************************************************/
void  cfgScmLockLinkAdmStTblResp()
{
   e1ObjectUpdateAdminStateAndSendAlarm(LOCKED );
}/*end cfgScmLockLinkAdmStTblResp*/

/********************************* Function  Header********************************
  Function Name:       csappGrhmCfgLockRespE1()
Parameters:          void
Return type:         void
Purpose:             To  handle CSAPP_GRHM_CFG_LOCK_RESP message.
Other Note:
 ************************************************************************************/
void csappGrhmCfgLockRespE1()
{
   e1ObjectUpdateAdminStateAndSendAlarm(LOCKED );
}/*end csappGrhmCfgLockRespE1*/


/********************************* Function  Header********************************
  Function Name:       cfgScmUnlockLinkAdmStTblResp()
Parameters:          void
Return type:         void
Purpose:             To  handle BSC_API_SET_LINKADMINSTATE message.
Other Note:
 ************************************************************************************/
void cfgScmUnlockLinkAdmStTblResp()
{
   e1ObjectUpdateAdminStateAndSendAlarm(UNLOCKED );
} /*end cfgScmUnlockLinkAdmStTblResp..*/

/********************************* Function  Header********************************
  Function Name:       csappGrhmCfgUnlockRespE1()
Parameters:          void
Return type:         void
Purpose:             To  handle CSAPP_GRHM_CFG_UNLOCK_RESP message.
Other Note:
 ************************************************************************************/
void csappGrhmCfgUnlockRespE1()
{
   e1ObjectUpdateAdminStateAndSendAlarm(UNLOCKED );  
}/*end csappGrhmCfgUnlockRespE1*/

/********************************* Function  Header********************************
  Function Name:       isMtp2ForLock()
Parameters:          void
Return type:         I_S8
Purpose:             To check any timeslots allocated for mtp2 links.
Other Note:
 ************************************************************************************/
I_S8  isMtp2ForLock(I_U32 e1Num)
{ 
   /* CS4.0 HA Stack Changes : Start */ 
#if 0    
   AbisTimeSlotPerTableApi *timeSlotObjPtr;
   AbisTimeSlotPerTableApi *t;
   I_U32 count=0;
   I_U16 outSize=0;
   I_S8 mtp2Flag=0,i;  
   if (getallAbisTimeSlotPerTable(&timeSlotObjPtr,&count,&outSize) != CLIB_SUCCESS)
   { 
      LOG_PRINT(LOG_CRITICAL, "E1ObjHandler: readE1Table() Failed"); 

   }   
   for(i = 0; i < count; i++)
   {      
      t = (AbisTimeSlotPerTableApi*)((char*)timeSlotObjPtr + (i *outSize));  
      if (e1Num == t->e1Num)  
      {
         if (t->usageType == SYS_TS_USAGE_MTP2)
         {
            mtp2Flag=1; 
            break;
         }         
      }
   }
   free(timeSlotObjPtr);       
#endif
   LinkTableApi *linkTablePtr = NULL;
   LinkTableApi *tempLinkPtr = NULL;
   I_U32 noOfRows = 0;
   I_U16 rowSize = 0;
   I_S8 mtp2Flag=0,i;  
   if (getallLinkTable(&linkTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (i *rowSize));
         if(tempLinkPtr->e1Num == e1Num)
         {
            mtp2Flag=1; 
            break;
         }         
      }
      free(linkTablePtr); 
   }
   else
      LOG_PRINT(LOG_INFO,"isMtp2ForLock :  No rows in Link table ");
   /* CS4.0 HA Stack Changes : End */ 

   return mtp2Flag;  
} /*end isMtp2ForLock*/


/********************************* Function  Header********************************
  Function Name:       trxhCfgUnlockRespE1()
Parameters:          void
Return type:         I_S8
Purpose:             To check any timeslots allocated for cic links.
Other Note:
 ************************************************************************************/
I_S8  isCicForLock(I_U32 e1Num)
{
   /* CS4.0 HA Stack Changes : Start */
#if 0
   AbisTimeSlotPerTableApi *timeSlotObjPtr;
   AbisTimeSlotPerTableApi *t;
   I_U32 count = 0;
   I_U16 outSize = 0;
   I_S8 cicFlag = 0,i;
   if (getallAbisTimeSlotPerTable(&timeSlotObjPtr,&count,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "E1ObjHandler: readE1Table() Failed");
   }
   for (i = 0; i < count; i++)
   {
      t = (AbisTimeSlotPerTableApi*)((char*)timeSlotObjPtr + (i *outSize));
      if (e1Num == t->e1Num)
      {
         if (t->usageType == SYS_TS_USAGE_CIC)
         {  
            cicFlag=1;
            break;
         }
      }
   }
   free(timeSlotObjPtr);        
#endif
   CicTableApi *cicTablePtr = NULL;
   CicTableApi *tempCicPtr = NULL;
   I_U32 noOfRows = 0;
   I_U16 rowSize = 0;
   I_S8 cicFlag = 0,i;

   if (getallCicTable(&cicTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempCicPtr = (CicTableApi *)((I_U8*)cicTablePtr + (i *rowSize));
         if(tempCicPtr->e1Num == e1Num)
         {  
            cicFlag=1;
            break;
         }
      }
      free(cicTablePtr); 
   }
   else
      LOG_PRINT(LOG_INFO,"isCicForLock :  No rows in Cic table ");

   /* CS4.0 HA Stack Changes : End */
   return cicFlag;
}/* end isCicForLock*/


/********************************* Function  Header********************************
  Function Name:       isMtp2ForUnlock()
Parameters:          void
Return type:         I_S8
Purpose:             To check any timeslots allocated for mtp2 links.
Other Note:
 ************************************************************************************/
I_S8  isMtp2ForUnlock(I_U32 e1Num)
{
   /* CS4.0 HA Stack Changes : Start */ 
#if 0
   AbisTimeSlotPerTableApi *timeSlotObjPtr;
   I_U32 count = 0;
   AbisTimeSlotPerTableApi *t;
   I_U16 outSize = 0;
   I_S8 mtp2Flag = 0,i; 
   if (getallAbisTimeSlotPerTable(&timeSlotObjPtr,&count,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "E1ObjHandler: readE1Table() Failed");
   }
   for (i = 0; i < count; i++)
   {
      t = (AbisTimeSlotPerTableApi*)((char*)timeSlotObjPtr + (i *outSize));
      if (e1Num == t->e1Num)
      {
         if (t->usageType == SYS_TS_USAGE_MTP2 && t->adminState == UNLOCKED)
         {
            mtp2Flag=1; 
            break;
         }       
      }   
   }
   free(timeSlotObjPtr);
#endif 
   LinkTableApi *linkTablePtr = NULL;
   LinkTableApi *tempLinkPtr = NULL;
   I_U32 noOfRows = 0;
   I_U16 rowSize = 0;
   I_S8 mtp2Flag=0,i;  
   if (getallLinkTable(&linkTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (i *rowSize));
         if(tempLinkPtr->e1Num == e1Num && tempLinkPtr->adminState == UNLOCKED)
         {
            mtp2Flag=1; 
            break;
         }         
      }
      if (mtp2Flag != 1)
        LOG_PRINT(LOG_DEBUG,"No Links are in UNLOCKED state, Link activation will not be triggered ");
      free(linkTablePtr); 
   }
   else
      LOG_PRINT(LOG_CRITICAL,"In isMtp2ForUnlock :No rows in Link table ");
   /* CS4.0 HA Stack Changes : End */ 

   return mtp2Flag;
}/*end isMtp2ForUnlock*/

/********************************* Function  Header********************************
  Function Name:       isCicForUnlock()
Parameters:          void
Return type:         I_S8
Purpose:             To check any timeslots allocated for cic links.
Other Note:
 ************************************************************************************/
I_S8  isCicForUnlock(I_U32 e1Num)
{
   /* CS4.0 HA Stack Changes : End */
#if 0
   AbisTimeSlotPerTableApi *timeSlotObjPtr;
   I_U32 count = 0;
   AbisTimeSlotPerTableApi *t;
   I_U16 outSize = 0;
   I_S8 cicFlag = 0,i; 
   if (getallAbisTimeSlotPerTable(&timeSlotObjPtr,&count,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "E1ObjHandler: readE1Table() Failed");
   }
   for (i = 0; i < count; i++)
   {
      t = (AbisTimeSlotPerTableApi*)((char*)timeSlotObjPtr + (i *outSize));
      if (e1Num == t->e1Num)
      {
         if (t->usageType == SYS_TS_USAGE_CIC && t->adminState == UNLOCKED)
         {
            cicFlag=1;    
            break;  
         }       
      }
   }
   free(timeSlotObjPtr); 
#endif
   CicTableApi *cicTablePtr = NULL;
   CicTableApi *tempCicPtr = NULL;
   I_U32 noOfRows = 0;
   I_U16 rowSize = 0;
   I_S8 cicFlag = 0,i;

   if (getallCicTable(&cicTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempCicPtr = (CicTableApi *)((I_U8*)cicTablePtr + (i *rowSize));
         if(tempCicPtr->e1Num == e1Num && tempCicPtr->adminState == UNLOCKED)
         {  
            cicFlag=1;
            break;
         }
      }
      free(cicTablePtr); 
   }
   else
      LOG_PRINT(LOG_INFO,"isCicForLock :  No rows in Cic table ");

   /* CS4.0 HA Stack Changes : End */

   return cicFlag;
}/*end isCicForUnlock*/

/********************************* Function  Header********************************
Function Name:       isFrTimeslot()
Parameters:          void
Return type:         I_S8
Purpose:             To check any timeslots allocated for fr links.
Other Note:
 ************************************************************************************/
I_Bool  isFrTimeslot(I_U32 e1Num)
{
/*Changes PCU R2.5 Aricent -- START*/
   FrLinkTableApi *frLinkPtr = NULL;
   FrLinkTableApi *tempFrLinkPtr = NULL;
   I_U32 noOfRows = 0;
   I_S32 ret = CM_FAILURE;
   I_U16 rowSize = 0;
   I_Bool frFlag = FALSE;
   I_S8 i = 0;
   
   ret = getallFrLinkTable(&frLinkPtr, &noOfRows, &rowSize);
   if (CLIB_SUCCESS == ret)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempFrLinkPtr = (FrLinkTableApi*)((I_U8*)frLinkPtr + (i *rowSize));
         if (tempFrLinkPtr->e1Id == e1Num )
         {
            frFlag = TRUE;
            break;
         }
      }
      free(frLinkPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"isFrTimeslot:  No rows in FrLink table Error Code = [%d] ", ret);
   }
   return frFlag;
/*Changes PCU R2.5 Aricent -- END*/
}/*end isFrTimeslot*/

/* CS4.0 HA Stack Changes : Start*/ 
void e1SendLinkAdminTableToScm(LinkTableApi *linkTablePtr, I_U32 admStateReqst)
{
   if (gStackStatus == SS7_STACK_UP)
   {
      OamScmLinkAdminState linkConfig;
      linkConfig.linkId = linkTablePtr->linkId; 
      linkConfig.linkSetId = linkTablePtr->linksetID;
      linkConfig.adminState = admStateReqst;  
      if (admStateReqst == UNLOCKED)
      {
         /*Changes for R2.3.4 Starts*/  
         if(fillMtp2TimerInfo(&(linkConfig.mtp2TimerConfig),linkTablePtr->satFlag) != I_TRUE)
         {
            LOG_PRINT(DEBUG,"fillMtp2TimerInfo failed");
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return;
         }
         /*Changes for R2.3.4 Ends*/  
         setStackObject(BSC_API_SET_TRUNKPERTABLE, SCM_UNLOCK, OAM_SCM_LINK_ADMIN_CONFIG);
      } 
      else
         setStackObject(BSC_API_SET_TRUNKPERTABLE, SCM_LOCK, OAM_SCM_LINK_ADMIN_CONFIG);

      gE1Data[e1ObjectInstanceIndex].msgsSentForE1++;
      gMsgSentForE1Num = linkTablePtr->e1Num;
      gE1NumberMapToTrunk = linkTablePtr->e1Num; 
      LOG_PRINT(LOG_INFO,"Sending OAM_SCM_LINK_ADMIN_CONFIG to Oil..");
      if (cfgSendStackMessage((I_Void *)&linkConfig, sizeof(OamScmLinkAdminState)) != CFG_SUCCESS)
      {
         return;
      }
   }
   else 
   {
      LOG_PRINT(DEBUG,"Request cannot be send to SCM as Ss7 Stack status is Down");
   }
}
/* CS4.0 HA Stack Changes : End*/ 

#if 0 /* CS4.0 HA Stack Changes*/ 
void e1SendLinkAdminTableToScm(AbisTimeSlotPerTableApi *e1TimeSlotObjPtr, I_U32 admStateReqst)
{
   LinkAdminStateTableIndices linkAdminStateTableIndicesBuff={0};
   LinkAdminStateTableApi   *linkAdminStateTableApiPtr=NULL;
   linkAdminStateTableIndicesBuff.linkAdminlinksetID= 
      M_GET_LINKSET(e1TimeSlotObjPtr->usingEntity);
   linkAdminStateTableIndicesBuff.linkAdminlinkCode =
      M_GET_LINKCODE(e1TimeSlotObjPtr->usingEntity);
   if ((( getLinkAdminStateTable(&linkAdminStateTableIndicesBuff,
                  &linkAdminStateTableApiPtr) == CLIB_SUCCESS )) && 
         (linkAdminStateTableApiPtr->linkAdminadminState == UNLOCKED ))
   {

      linkAdminStateTableApiPtr->linkAdminadminState = admStateReqst;
      gE1Data[e1ObjectInstanceIndex].msgsSentForE1++;
      gMsgSentForE1Num = e1TimeSlotObjPtr->e1Num;
      sendLinkAdminStateTableReqToScm(linkAdminStateTableApiPtr);
      free(linkAdminStateTableApiPtr);  /*free the mem allocated in db call*/
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL," getLinkAdminStateTable() DB Failure... ");
   }

}
#endif 
void updateOprStatusOfTimeSlotsForE1(I_U32 e1Num, I_U32 oprStatus)
{
   AbisTimeSlotTableApi *timeSlotblPtr;
   AbisTimeSlotTableApi *tempTimeSlotblPtr;
   I_U32  count=0;
   I_U16  size=0;
   OamsCfgAfhSysAlarm alarmBuff= {0};
   I_U16 i=0;

   if ( getTimeSlotForE1(e1Num, &timeSlotblPtr, &count, &size) == CLIB_SUCCESS )
   {
      for ( i =0 ; i < count; i++)
      {
         tempTimeSlotblPtr =(AbisTimeSlotTableApi*)
            ((I_U8*)timeSlotblPtr + (i *size));
         if (tempTimeSlotblPtr->oprState != oprStatus  && tempTimeSlotblPtr->adminState == UNLOCKED)
         {
            tempTimeSlotblPtr->oprState = oprStatus ;
            if ( updateAbisTimeSlotTable(tempTimeSlotblPtr)!=CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL," updateAbisTimeSlotTable() DB Failure... ");            
            }
            /*Sending the Alarm...*/
            if (    oprStatus == DISABLED )  
            {
               alarmBuff.sysAlarm.sysalarmId = TIMESLOT_DISABLED;
               alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"Timeslot %d of E1 %d is Disabled",tempTimeSlotblPtr->tsNum,e1Num);
            }
            else
            {
               alarmBuff.sysAlarm.sysalarmId = TIMESLOT_ENABLED;               
               alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"Timeslot %d of E1 %d is Enabled",tempTimeSlotblPtr->tsNum,e1Num);
            }
            alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"Timeslot %d of E1 %d is Enabled",tempTimeSlotblPtr->tsNum,e1Num);
            alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TIMESLOT;

            alarmBuff.sysAlarm.key1 = tempTimeSlotblPtr->tsNum;
            alarmBuff.sysAlarm.key2 = e1Num;

            /* Mantis Id 2242 Start */
            alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
            /* Mantis Id 2242 End */

            cfgSendMessage(&alarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);              
         }
      }
      free(timeSlotblPtr);
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL," updateOprStatusOfTimeSlotsForE1() DB Failure... ");   
   }
}

void  e1ObjectUpdateAdminStateAndSendAlarm(I_U32 admState)
{
   OamsCfgAfhSysAlarm alarmBuff={0};
   I_Bool tsOprStateChange = FALSE;
   I_U32 tsOprState;
   I_U8 chasisId;
   I_U8 slotId;
   if ( gE1Data[e1ObjectInstanceIndex].msgsSentForE1 != 0)
   {
      gE1Data[e1ObjectInstanceIndex].msgsSentForE1 --;
   }
   else
   { 
      tsOprStateChange = TRUE;
   }

   if ( gE1Data[e1ObjectInstanceIndex].msgsSentForE1 == 0 )
   { 
			  //Mantis #8719 start
			  gMsgSentForE1Num = 0xff;
			  //end
      /*Sending the Alarm...*/
      if ( admState == LOCKED )
      {
         alarmBuff.sysAlarm.sysalarmId = ALARM_TRUNK_LOCKED;
//         alarmBuff.sysAlarm.sysalarmId = E1_LOCKED;
         alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
         gE1Data[e1ObjectInstanceIndex].e1State = locked; /*Locked..*/
         alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"TRUNK %d is LOCKED",e1ObjectInstanceIndex);
         tsOprState=DISABLED;
         alarmBuff.sysAlarm.alarmReason =(e1ObjectInstanceIndex >= CFG_MIN_NUM_INT_E1 && e1ObjectInstanceIndex <= CFG_MAX_NUM_INT_E1) ? 1 : 0; 
      }
      else
      {
         alarmBuff.sysAlarm.sysalarmId = ALARM_TRUNK_UNLOCKED;
         alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
         gE1Data[e1ObjectInstanceIndex].e1State = unlocked; /*unLocked..*/              
         alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"TRUNK %d is UNLOCKED",e1ObjectInstanceIndex);
         tsOprState=ENABLED;  
         alarmBuff.sysAlarm.alarmReason =(e1ObjectInstanceIndex >= CFG_MIN_NUM_INT_E1 && e1ObjectInstanceIndex <= CFG_MAX_NUM_INT_E1) ? 1 : 0; 
      }

      //alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TRUNKPORT;
      if(getChasisSlotIdTrunkTable( e1ObjectInstanceIndex,&chasisId, &slotId) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm: No Chasis and Slot found for Trunk [%d]" , e1ObjectInstanceIndex);
         LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm: Not Sending Alarm");
         return;      
      }
      alarmBuff.sysAlarm.key1 = chasisId;
      alarmBuff.sysAlarm.key2 = slotId;
      alarmBuff.sysAlarm.key3 = e1ObjectInstanceIndex;
      FillObjTypeFromSlotId(slotId,alarmBuff.sysAlarm.info3 );

      /*Database Updatation is Required (changing in AST of E1Table)..*/
      if(updateE1AdminState(e1ObjectInstanceIndex,admState)==CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO, "E1ObjHandler:,DB Updation is Done..");
         /*BSC R2.0 Changes*/ 
         #if 0   
         // CS40 PH-2 Changes ::PreConfig to Config
         // Update admin State in TrunkPortTable as well here
         if(updateTrunkAdminState(e1ObjectInstanceIndex,admState )==CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO, "E1ObjHandler:,DB Updation is Done..");
         }
         // CS40 PH-2 Changes ::PreConfig to Config
         #endif
      }

      cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);          
   }
   else
   {
      LOG_PRINT(MAJOR,"Err case: gE1Data[%d].msgsSentForE1 is not zero",e1ObjectInstanceIndex );
   } 
}

/********************************* Function  Header********************************
Function Name	: sendingInitAbisE1()
Parameters	: None
Return type	: I_Void
Purpose		: It create AbisE1Ts list at the time of CFG initialization.
Other Note	:
************************************************************************************/
I_Void sendingInitAbisE1() 
{
   I_U32 *e1Num = NULL;
   I_U32 e1RecCount = ZERO;
   I_U32 i = ZERO;
   OamsCfgBichInitAbisE1 oamsCfgBichInitAbisE1;

   LOG_PRINT(LOG_INFO,"sendingInitAbisE1: Entering in the function");

   /* Initializing LapdTeiConfigTable Data */	
/*   retVal = getallLapdTEIConfigTable(&LapdTEIConfigTableApiPtr, &lapdTeiRecCount, &lapdTeiRecSz); 
   if(retVal != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"sendingInitAbisE1: No Rows in LapdTEIConfigTable");
      return ;
   }
*/
   /* Populating AbisE1TsList */	
   if(getE1NumTrunkTable(SYS_E1_USAGE_ABISIF, &e1Num, &e1RecCount) == DBLIB_SUCCESS)
   {
      for(i = 0; i < e1RecCount; i++)
      {
	 oamsCfgBichInitAbisE1.e1Id = e1Num[i];
	 cfgSendMessage(&oamsCfgBichInitAbisE1, sizeof(OamsCfgBichInitAbisE1), ENT_OAMS_BICH,
							OAMS_CFG_BICH_INIT_ABIS_E1,0);
      }
      free(e1Num);
   }
   
   LOG_PRINT(LOG_INFO,"sendingInitAbisE1: Exiting from the function");
   return ;
}

/********************************* Function  Header*****************************
  Function Name   : updateTrunkTable()
Parameters   : None
Return type   : I_Void
Purpose      : It update usageType of E1 in TrunkTable
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void updateTrunkTableHandler()
{
   TrunkTableApi* receivedMsgPtr = ( TrunkTableApi* )(((I_U8 *)gCfgMsgBuf ) +
         sizeof(sCmMsg));
   BicTableApi* bicTableApiPtr = NULL;
   I_U32 rowCount = ZERO;
   I_U16 rowSz = ZERO;
   I_S32 dbStatus = -1;

   LOG_PRINT(LOG_INFO,"Entering Function : updateTrunkTable");

   /* Check whether all Bics connected with E1 are deleted from BSC */
   dbStatus = getSecBicTable(receivedMsgPtr->e1Num, &bicTableApiPtr, &rowCount, &rowSz);

   if(DBLIB_SUCCESS == dbStatus)
   {
      /* Bic are configured for E1 */
      free(bicTableApiPtr);
      LOG_PRINT(LOG_INFO,"updateTrunkTable : BICs Configured at BSC for E1 : %d",
            receivedMsgPtr->e1Num);
      cfgSendNackToCm(CM_ERR_BTS_CONFIGURED_FOR_E1);
   }
   #if 0
   else
   {
      /* Remove data corresponding to E1 from BicE1TeiMap Table */
      deleteE1DataBicTeiE1MapTable(receivedMsgPtr->e1Num);

      /* Delete E1 Data From AbisE1List */
      delE1InAbisE1TsList(receivedMsgPtr->e1Num);

      /* Update data in DB */
      dbStatus = updateTrunkTable(receivedMsgPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         /* Table Updation Failed*/
         LOG_PRINT(LOG_INFO,"updateTrunkTable : TrunkTable Updation Failed");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      else
      {
         /* Update E1 Data in AbisE1List */
         addE1InAbisE1TsList(receivedMsgPtr->e1Num, receivedMsgPtr->usageType);

         /* Add data corresponding to E1 in BicE1TeiMap Table */
         addE1DataBicTeiE1MapTable(receivedMsgPtr->e1Num);

         /* Initialize gMaxCellsNum variable according to the changes in total 
          * available LAPD_TRX type timeslots in BSC */
         //initGlobalMaxCellNumVar();

         /* Send Update AbisE1 to BICH */
         oamsCfgBichUpdateAbisE1.e1Id = receivedMsgPtr->e1Num;
         cfgSendMessage(&oamsCfgBichUpdateAbisE1, sizeof(OamsCfgBichUpdateAbisE1), ENT_OAMS_BICH,
               OAMS_CFG_BICH_UPDATE_ABIS_E1, 0);
         /* Send Ack To CM */
         cfgSendAckToCm();
         /*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/
         gE1Data[receivedMsgPtr->e1Num].usageType = receivedMsgPtr->usageType;
         /*BSC CS4.0 : Abis E1 Lock/Unlock changes starts*/
      }
   }
   #endif
   LOG_PRINT(LOG_INFO,"Entering Function : updateTrunkTable");
}

/*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/

/********************************* Function  Header********************************
  Function Name:       abisE1LockUnlock()
Parameters:          TrunkTableApi *e1ObjPtr
Return type:         void
Purpose:             To perform Lock/Unlock procedure for AbisE1.
Other Note:
 ************************************************************************************/
void abisE1LockUnlock(TrunkTableApi *e1ObjPtr)
{
   E1StatusTableApi e1StatusApi;
   LOG_PRINT(LOG_INFO,"abisE1LockUnlock: Entering in function");
   cfgSendAckToCm();
   switch(e1ObjPtr->adminState)
   {
      case LOCKED:
         {
            gE1Data[e1ObjPtr->e1Num].e1State = lockInProgress;
            e1StatusApi.e1Id = e1ObjPtr->e1Num;
            e1StatusApi.state = LOCKINPROGRESS;
            if(updateE1StatusTable(&e1StatusApi) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL,"abisE1LockUnlock : Update operation on E1Status Table failed in lockInProgress state");
               return ;
            }

            if(gBssState == locked || gBssState == lockInProgress)
            {
               LOG_PRINT(LOG_DEBUG,"abisE1LockUnlock: Abis E1= LOCKED and gBssState = locked/lockInProgress");
               updateAbisE1StateInDBAndSendAlarm(e1ObjPtr->e1Num, e1ObjPtr->adminState);
            }
            else if(gBssState == unlockInProgress)
            {
               LOG_PRINT(LOG_DEBUG,"abisE1LockUnlock: Abis E1= LOCKED and gBssState = unlockInProgress");
               e1LockForBssUnlockInProgress(e1ObjPtr->e1Num);
            }
            else if (gBssState == unlocked)
            {
               LOG_PRINT(LOG_DEBUG,"abisE1LockUnlock: Abis E1= LOCKED and gBssState = unlock");
               e1LockForBssUnlocked(e1ObjPtr->e1Num);
            }
            break;
         }
      case UNLOCKED:
         {
            gE1Data[e1ObjPtr->e1Num].e1State = unlockInProgress;
            e1StatusApi.e1Id = e1ObjPtr->e1Num;
            e1StatusApi.state = UNLOCKINPROGRESS;
            if(updateE1StatusTable(&e1StatusApi) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL,"abisE1LockUnlock : Update operation on E1Status Table failed in unlockInProgress State. ");
               return ;
            }

            if(gBssState == locked || gBssState == lockInProgress)
            {
               LOG_PRINT(LOG_DEBUG,"abisE1LockUnlock: Abis E1= UNLOCKED and gBssState = locked/lockedInProgress");
               updateAbisE1StateInDBAndSendAlarm(e1ObjPtr->e1Num, e1ObjPtr->adminState);
            }
            else if(gBssState == unlockInProgress)
            {
               LOG_PRINT(LOG_DEBUG,"abisE1LockUnlock: Abis E1= UNLOCKED and gBssState = unlockInProgress");
               e1UnlockForBssUnlockInProgress(e1ObjPtr->e1Num);
            }
            else if (gBssState == unlocked)
            {
               LOG_PRINT(LOG_DEBUG,"abisE1LockUnlock: Abis E1= UNLOCKED and gBssState = unlock");
               e1UnlockForBssUnlocked(e1ObjPtr->e1Num);
            }
            break;
         }
   }
   LOG_PRINT(LOG_INFO,"abisE1LockUnlock: Exiting from function");
   return;
}
/********************************* Function  Header********************************
  Function Name:       isE1RequestValid()
Parameters:          I_U32 e1Num , I_U32 adminState
Return type:         I_Bool
Purpose:             To perform validation checks on E1 Lock\Unlock request.
Other Note:
 ************************************************************************************/

I_Bool isE1RequestValid(I_U32 e1Num)
{
   LOG_PRINT(LOG_INFO,"isE1RequestValid: Entering in function");
   if(gE1Data[e1Num].trunkState == EnableInProgress)
   {
      LOG_PRINT(LOG_INFO,"isE1RequestValid: Validation check failed. Enable procedure this E1 is in progress");
      cfgSendNackToCm(CM_ERR_TRUNKPORT_ENABLE_IN_PROGRESS);
      return CFG_FAILURE;
   }
   else if(gE1Data[e1Num].trunkState == DisableInProgress)
   {
      LOG_PRINT(LOG_INFO,"isE1RequestValid: Validation check failed. Disable Procedure for this E1 is in progress");
      cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLE_IN_PROGRESS);
      return CFG_FAILURE;
   }
   else if(gE1Data[e1Num].trunkState == Disabled)
   {
      LOG_PRINT(LOG_INFO,"isE1RequestValid: Validation check failed. E1 is disabled");
      cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLED);
      return CFG_FAILURE;
   }

   LOG_PRINT(LOG_INFO,"isE1RequestValid: Exiting from function");
   return CFG_SUCCESS;
}

/********************************* Function  Header********************************
  Function Name:       updateAbisE1StateInDbAndSendAlarm()
Parameters:          I_U32 e1Num , I_U32 adminState
Return type:         I_Bool
Purpose:             To perform validation checks on Abis E1 Lock\Unlock request.
Other Note:
 ************************************************************************************/
void updateAbisE1StateInDBAndSendAlarm(I_U32 e1Num, I_U32 adminState)
{
   OamsCfgAfhSysAlarm alarmBuff={0};
   E1StatusTableApi e1StatusApi;
   I_U8 chasisId;
   I_U8 slotId;
   TrunkPortTableApi  *trunkPortDb          =  NULL;
   I_S32 res = -1;
   LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm:Entering in function");
   if ( adminState == LOCKED )
   {
      alarmBuff.sysAlarm.sysalarmId = ALARM_TRUNK_LOCKED;
//      alarmBuff.sysAlarm.sysalarmId = ALARM_E1_LOCKED;
      alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      gE1Data[e1Num].e1State = locked; /*Locked..*/
      alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"TRUNK %d is LOCKED",e1ObjectInstanceIndex);
      e1StatusApi.e1Id = e1Num;
      e1StatusApi.state = LOCKED;
      alarmBuff.sysAlarm.alarmReason =(e1Num >= CFG_MIN_NUM_INT_E1 && e1Num <= CFG_MAX_NUM_INT_E1) ? 1 : 0; 

   }
   else
   {
      alarmBuff.sysAlarm.sysalarmId = ALARM_TRUNK_UNLOCKED;
//      alarmBuff.sysAlarm.sysalarmId = ALARM_E1_UNLOCKED;
      alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
      gE1Data[e1Num].e1State = unlocked; /*unLocked..*/              
      alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"TRUNK %d is UNLOCKED",e1ObjectInstanceIndex);
      e1StatusApi.e1Id = e1Num;
      e1StatusApi.state = UNLOCKED;
      alarmBuff.sysAlarm.alarmReason =(e1Num >= CFG_MIN_NUM_INT_E1 && e1Num <= CFG_MAX_NUM_INT_E1) ? 1 : 0; 
   }

   if( ( res = getTrunkPortTableRowE1( e1Num, &trunkPortDb ) ) == CLIB_SUCCESS ) 
   {
      LOG_PRINT(DEBUG,"getTrunkPortTableRowE1 succ for e1(%d)",e1Num); 
      alarmBuff.sysAlarm.key1 = trunkPortDb->chasisFrameId;  
      alarmBuff.sysAlarm.key2 = trunkPortDb->slotId;  
      free(trunkPortDb);
   }
   else 
   {
       getActiveIccSlotId(&chasisId, &slotId);
       alarmBuff.sysAlarm.key1 = chasisId; 
       alarmBuff.sysAlarm.key2 = slotId;  
   }
   alarmBuff.sysAlarm.key3 = e1Num;

   FillObjTypeFromSlotId(alarmBuff.sysAlarm.key2,alarmBuff.sysAlarm.info3 );
    
   /*BSC R2.0 Chages Starts*/
   #if 0   
   if(getChasisSlotIdTrunkTable( e1Num,&chasisId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm: No Chasis and Slot found for Trunk [%d]" , e1Num);
      LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm: Not Sending Alarm");
      return;      
   }
   alarmBuff.sysAlarm.key1 = chasisId;
   alarmBuff.sysAlarm.key2 = slotId;
   alarmBuff.sysAlarm.key3 = e1Num;
   #endif
   /*BSC R2.0 Chages Starts*/
   

   /*Database Updatation is Required */
   if(updateE1AdminState(e1Num,adminState)==CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm:DB Updation is Done..");
      /*BSC R2.0 Changes*/ 
      #if 0   
      // CS40 PH-2 Changes ::PreConfig to Config
			// Update admin State in TrunkPortTable as well here
      if(updateTrunkAdminState(e1ObjectInstanceIndex,adminState )==CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm:,DB Updation is Done..");
      }
      // CS40 PH-2 Changes ::PreConfig to Config
      #endif
   }
   if(updateE1StatusTable(&e1StatusApi) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateAbisE1StateInDBAndSendAlarm : Update operation on E1Status Table failed ");
      return ;
   }
   cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); 
   LOG_PRINT(LOG_INFO, "updateAbisE1StateInDBAndSendAlarm:Exiting from function");
}

/********************************* Function  Header********************************
  Function Name:       e1UnlockForBssUnlocked()
Parameters:          I_U32 e1Num 
Return type:         I_Void
Purpose:             To Unlock AbisE1 when BSS is Unlocked.
Other Note:
 ************************************************************************************/

I_Void e1UnlockForBssUnlocked(I_U32 e1Num)
{
   CellPerTableIndices *impactedCells = NULL;
   I_U32 lenListOfCell = 0;
   I_U32 cellCount = 0;
   I_U32 impactedCellCount = 0;
   I_Bool isUnlockedCell = FALSE;
   I_S32 retVal;
   LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlocked: Entering in function");

   retVal = getCellListByE1(e1Num, &impactedCells, &lenListOfCell);
   if(retVal != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG, "e1UnlockForBssUnlocked: No Cell for this E1 found. Update state in DB only");
      updateAbisE1StateInDBAndSendAlarm(e1Num, UNLOCKED);
      return;
   }
   LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlocked: Enter from Loop");
   for(impactedCellCount = 0; impactedCellCount < lenListOfCell ; impactedCellCount++)
   {
      for(cellCount = 0 ; cellCount < CFG_MAX_NUM_CELLS ; cellCount++)
      {
         if(gCellData[cellCount].CellID == impactedCells[impactedCellCount].cellId && 
               gCellData[cellCount].lac == impactedCells[impactedCellCount].lac)
         {
            if(gCellData[cellCount].CellState == locked || gCellData[cellCount].CellState == lockeOrDisableInProgress || gCellData[cellCount].CellState == unlockedDisabled)
            {

               LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlocked: Cell Id = %d, Lac = %d, CellState = Locked/unlockDisabled/lockedOrDisableInProgress" , gCellData[cellCount].CellID, gCellData[cellCount].lac);
               //Do Nothing
            }
            else if(gCellData[cellCount].CellState == unlockedEnabled) 
            {
               LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlocked: Cell Id = %d, Lac = %d, CellState = UnlockedEnabled" , gCellData[cellCount].CellID, gCellData[cellCount].lac);
               isUnlockedCell = TRUE;
               sendAbisE1UnlockReq(e1Num, gCellData[cellCount].CellID, gCellData[cellCount].lac, cellCount);
               gE1Data[e1ObjectInstanceIndex].e1CellUnlockReqSent++;

            }
            else if(gCellData[cellCount].CellState == unlockOrEnableInProgress)
            {
               LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlocked: Cell Id = %d, Lac = %d, CellState = unlockOrEnableInProgress" , gCellData[cellCount].CellID, gCellData[cellCount].lac);
               isUnlockedCell = TRUE;
               gE1Data[e1ObjectInstanceIndex].waitingForCellUnlockRespCounter++; 
            }
            break;
         }
      }
   }
   LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlocked: Exit from Loop");
   if(isUnlockedCell == FALSE)
   {
      updateAbisE1StateInDBAndSendAlarm(e1Num, UNLOCK);
   }
   free(impactedCells);
   LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlocked: Exiting from function");
}

/********************************* Function  Header********************************
  Function Name:       e1UnlockForBssUnlockInProgress()
Parameters:          I_U32 e1Num 
Return type:         I_Void
Purpose:             To Unlock AbisE1 when BSS is Unlock in progress.
Other Note:
 ************************************************************************************/
I_Void e1UnlockForBssUnlockInProgress(I_U32 e1Num)
{
   AInterfaceTableApi *aInterfaceTable = NULL;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlockInProgress: Entering in function");
   if(getallAInterfaceTable(&aInterfaceTable, &outRows, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "e1UnlockForBssUnlockInProgress: Db Query for A Interface Table failed");
      return;
   }
   if(aInterfaceTable->oprState == ENABLED)
   {
      LOG_PRINT(LOG_DEBUG, "e1UnlockForBssUnlockInProgress: A Interface is Enabled");
      e1UnlockForBssUnlocked(e1Num);
   }
   else
   {
      LOG_PRINT(LOG_DEBUG, "e1UnlockForBssUnlockInProgress: A Interface is Disabled");
      updateAbisE1StateInDBAndSendAlarm(e1Num, UNLOCKED);

   }
   free(aInterfaceTable);
   LOG_PRINT(LOG_INFO, "e1UnlockForBssUnlockInProgress: Exiting from function");

}

/********************************* Function  Header********************************
  Function Name:       sendAbisE1UnlockReq()
Parameters:          I_U32 e1Num ,I_UL32 cellId, I_U32 lac, I_U16 cellIndex
Return type:         I_Void
Purpose:             Send Abis E1 Unlock request to Cellh
Other Note:
 ************************************************************************************/

I_Void sendAbisE1UnlockReq(I_U32 e1Num, I_UL32 cellId, I_U32 lac, I_U16 cellIndex)
{
   OamsCfgCellhAbisE1UnlockReq oamsCfgCellhAbisE1UnlockReq;
   LOG_PRINT(LOG_INFO, "sendAbisE1UnlockReq: Entering in the function");
   oamsCfgCellhAbisE1UnlockReq.e1Id = e1Num;
   oamsCfgCellhAbisE1UnlockReq.objId = cellId;
   oamsCfgCellhAbisE1UnlockReq.lac = lac;
   oamsCfgCellhAbisE1UnlockReq.cellIndex = cellIndex;
   cfgSendMessage(&oamsCfgCellhAbisE1UnlockReq, sizeof(OamsCfgCellhAbisE1UnlockReq), ENT_OAMS_CELLH, OAMS_CFG_CELLH_E1_UNLOCK_REQ, 0);
   LOG_PRINT(LOG_INFO, "sendAbisE1UnlockReq: Exiting from function");

}

/********************************* Function  Header********************************
  Function Name:       e1LockForBssUnlocked()
Parameters:          I_U32 e1Num 
Return type:         I_Void
Purpose:             Send Abis E1 Lock request to Cellh
Other Note:
 ************************************************************************************/
I_Void e1LockForBssUnlocked(I_U32 e1Num)
{
   CellPerTableIndices *impactedCells = NULL;
   I_U32 lenListOfCell = 0;
   I_U32 cellCount = 0;
   I_U32 impactedCellCount = 0;
   I_Bool isUnlockedCell = FALSE;
   LOG_PRINT(LOG_INFO, "e1LockForBssUnlocked: Entering in function");
   if(getCellListByE1(e1Num, &impactedCells, &lenListOfCell)!= CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG, "e1LockForBssUnlocked: No Cell for this E1 found. Update state in DB only");
      updateAbisE1StateInDBAndSendAlarm(e1Num, LOCKED);
      return;
   }
   for(impactedCellCount = 0; impactedCellCount < lenListOfCell ; impactedCellCount ++)
   {
      for(cellCount = 0 ; cellCount < CFG_MAX_NUM_CELLS ; cellCount++)
      {
         if(gCellData[cellCount].CellID == impactedCells[impactedCellCount].cellId && 
               gCellData[cellCount].lac == impactedCells[impactedCellCount].lac)
         {
            if(gCellData[cellCount].CellState == locked || gCellData[cellCount].CellState == lockeOrDisableInProgress|| gCellData[cellCount].CellState == unlockedDisabled)
            {
               LOG_PRINT(LOG_INFO, "e1LockForBssUnlocked: Cell Id = %d, Lac = %d, CellState = Locked/unlockDisabled/lockedOrDisableInProgress" , gCellData[cellCount].CellID, gCellData[cellCount].lac);
               //Do nothing
            }
            else if(gCellData[cellCount].CellState == unlockedEnabled)
            {
               LOG_PRINT(LOG_INFO, "e1LockForBssUnlocked: Cell Id = %d, Lac = %d, CellState = UnlockedEnabled" , gCellData[cellCount].CellID, gCellData[cellCount].lac);
               isUnlockedCell = TRUE;
               sendAbisE1LockReq(e1Num, gCellData[cellCount].CellID, gCellData[cellCount].lac, cellCount);
               gE1Data[e1ObjectInstanceIndex].e1CellLockReqSent++;

            }
            else if(gCellData[cellCount].CellState == unlockOrEnableInProgress)
            {
               LOG_PRINT(LOG_INFO, "e1LockForBssUnlocked: Cell Id = %d, Lac = %d, CellState = unlockOrEnableInProgress" , gCellData[cellCount].CellID, gCellData[cellCount].lac);
               isUnlockedCell = TRUE;
               gE1Data[e1ObjectInstanceIndex].waitingForCellUnlockRespCounter++; 
            }
            break;
         }
      }
   }

   if(isUnlockedCell == FALSE)
   {
      updateAbisE1StateInDBAndSendAlarm(e1Num, LOCK);
   }
   free(impactedCells);
   LOG_PRINT(LOG_INFO, "e1LockForBssUnlocked: Exiting from function");

}

/********************************* Function  Header********************************
  Function Name:       e1LockForBssUnlockInProgress()
Parameters:          I_U32 e1Num 
Return type:         I_Void
Purpose:             To Lock AbisE1 when BSS is Unlock in progress.
Other Note:
 ************************************************************************************/
I_Void e1LockForBssUnlockInProgress(I_U32 e1Num)
{
   AInterfaceTableApi *aInterfaceTable = NULL;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   LOG_PRINT(LOG_INFO, "e1LockForBssUnlockInProgress: Entering in function");
   if(getallAInterfaceTable(&aInterfaceTable, &outRows, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "e1LockForBssUnlockInProgress: Db Query for A Interface Table failed");
      return;
   }
   if(aInterfaceTable->oprState == ENABLED)
   {
      LOG_PRINT(LOG_DEBUG, "e1LockForBssUnlockInProgress: A Interface is Enabled");
      e1LockForBssUnlocked(e1Num);
   }
   else
   {
      LOG_PRINT(LOG_DEBUG, "e1LockForBssUnlockInProgress: A Interface is Disabled");
      updateAbisE1StateInDBAndSendAlarm(e1Num, LOCKED);

   }
   free(aInterfaceTable);
   LOG_PRINT(LOG_INFO, "e1LockForBssUnlockInProgress: Exiting from function");

}

/********************************* Function  Header********************************
  Function Name:       sendAbisE1LockReq()
Parameters:          I_U32 e1Num ,I_UL32 cellId, I_U32 lac, I_U16 cellIndex
Return type:         I_Void
Purpose:             Send Abis E1 Lock request to Cellh
Other Note:
 ************************************************************************************/

I_Void sendAbisE1LockReq(I_U32 e1Num, I_UL32 cellId, I_U32 lac, I_U16 cellIndex)
{
   OamsCfgCellhAbisE1LockReq oamsCfgCellhAbisE1LockReq;
   LOG_PRINT(LOG_INFO, "sendAbisE1LockReq: Entering in the function");
   oamsCfgCellhAbisE1LockReq.e1Id = e1Num;
   oamsCfgCellhAbisE1LockReq.objId = cellId;
   oamsCfgCellhAbisE1LockReq.lac = lac;
   oamsCfgCellhAbisE1LockReq.cellIndex = cellIndex;
   cfgSendMessage(&oamsCfgCellhAbisE1LockReq, sizeof(OamsCfgCellhAbisE1LockReq), ENT_OAMS_CELLH, OAMS_CFG_CELLH_E1_LOCK_REQ, 0);
   LOG_PRINT(LOG_INFO, "sendAbisE1LockReq: Exiting from function");
}

/********************************* Function  Header********************************
  Function Name:       abisE1LockUnlockAfterCellUnlock()
Parameters:          I_U32 e1Num ,I_UL32 cellId, I_U32 lac
Return type:         I_Void
Purpose:             This function will perform Abis Lock Unlock after Cell Unlock.
Other Note:
 ************************************************************************************/

I_Void abisE1LockUnlockAfterCellUnlock(I_U32 cellId, I_U32 lacId)
{
   I_U32 *e1Id = NULL;
   I_U32 outSize = 0;
   I_U32 count = 0;
   LOG_PRINT(LOG_INFO,"abisE1LockUnlockAfterCellUnlock: Entering from Function ");

   if(getE1ForCell(lacId, cellId, &e1Id, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"abisE1LockUnlockAfterCellUnlock: E1's for this Cell Not found. getE1sForCell() failed ");
      return ;   
   }
   for (count = 0; count < outSize ; count++)
   {
      if(gE1Data[e1Id[count]].e1State == lockInProgress)
      {
         abisE1LockAfterCellUnlock(e1Id[count], cellId, lacId);
      }
      else if(gE1Data[e1Id[count]].e1State == unlockInProgress)
      {
         abisE1UnlockAfterCellUnlock(e1Id[count], cellId, lacId);   
      }
   }
   free(e1Id);
   LOG_PRINT(LOG_INFO,"abisE1LockUnlockAfterCellUnlock: Exiting from Function ");
}

/********************************* Function  Header********************************
  Function Name:       abisE1LockAfterCellUnlock()
Parameters:          I_U32 e1Num ,I_UL32 cellId, I_U32 lac
Return type:         I_Void
Purpose:             This function will perform Abis Lock after Cell Unlock.
Other Note:
 ************************************************************************************/
I_Void abisE1LockAfterCellUnlock(I_U32 e1Num, I_U32 cellId, I_U32 lac)
{
   I_U16 cellIndex = 0;
   LOG_PRINT(LOG_INFO,"abisE1LockAfterCellUnlock: Entering in Function ");
   getCellIndex(lac, cellId, &cellIndex);
   gE1Data[e1Num].waitingForCellUnlockRespCounter--;
   sendAbisE1LockReq(e1Num, cellId, lac, cellIndex);
   gE1Data[e1Num].e1CellLockReqSent++;
   LOG_PRINT(LOG_INFO,"abisE1LockAfterCellUnlock: Exiting from Function ");

}

/********************************* Function  Header********************************
  Function Name:       abisE1UnlockAfterCellUnlock()
Parameters:          I_U32 e1Num ,I_UL32 cellId, I_U32 lac
Return type:         I_Void
Purpose:             This function will perform Abis Unlock after Cell Unlock.
Other Note:
 ************************************************************************************/
I_Void abisE1UnlockAfterCellUnlock(I_U32 e1Num, I_U32 cellId, I_U32 lac)
{
   I_U16 cellIndex = 0;
   LOG_PRINT(LOG_INFO,"abisE1UnlockAfterCellUnlock: Entering in Function ");
   gE1Data[e1Num].waitingForCellUnlockRespCounter--;
   getCellIndex(lac, cellId, &cellIndex);
   sendAbisE1UnlockReq(e1Num, cellId, lac, cellIndex);
   gE1Data[e1Num].e1CellUnlockReqSent++;
   LOG_PRINT(LOG_INFO,"abisE1LockAfterCellUnlock: Exiting from Function ");

}

/*BSC CS4.0 : Abis E1 Lock/Unlock changes Ends*/

/* Trunk UsageType Changes : Start - Vijinder */

/********************************* Function  Header*****************************
  Function Name   : updateUsageTypeAbisToFree()
Parameters      : None
Return type     : I_Void
Purpose         : It update usageType of Trunk in TrunkPortTable
Other Note      : Added For 
 *******************************************************************************/
I_S32 updateUsageTypeAbisToFree(I_U32 usageTypeInDB)
{
   TrunkPortTableApi* receivedMsgPtr = ( TrunkPortTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   I_S32 dbStatus              = -1;
   I_U32 status                = 0;
   OamsCfgBichDeleteAbisE1     oamsCfgBichDeleteAbisE1;

   LOG_PRINT(LOG_INFO,"Entering Function : updateUsageTypeAbisToFree");

   /*BSC R2.0 Changes Starts*/ 
   /* Remove data corresponding to E1 from BicE1TeiMap Table */
   //deleteE1DataBicTeiE1MapTable(receivedMsgPtr->trunkPortId);
   /*BSC R2.0 Changes Starts*/ 

   /* Delete E1 Data From AbisE1List */
   /*delE1InAbisE1TsList(receivedMsgPtr->trunkPortId);*/

   status = delAbisTimeSlotTable(usageTypeInDB);
   if( status == CFG_FAILURE )
   {
      LOG_PRINT(LOG_MAJOR,"updateUsageTypeAbisToFree: Deletion Failed in AbisTimeSlotTable");
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);         
      return CFG_FAILURE; 
   }

   /* Initialize gMaxCellsNum variable according to the changes in total 
    * available LAPD_TRX type timeslots in BSC */
   //initGlobalMaxCellNumVar();

   /* Update data in DB */
   //dbStatus = updateTrunkPortTable(receivedMsgPtr);
   dbStatus = updateUsageTypeInTrunkPortTable(receivedMsgPtr->trunkPortId,receivedMsgPtr->usageType);

   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_INFO,"updateUsageTypeAbisToFree : TrunkPortTable Updation Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE; 
   }
   else
   { 
      dbStatus = updateUsageTypeInTrunkTable(receivedMsgPtr->trunkPortId,receivedMsgPtr->usageType);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_INFO,"updateUsageTypeAbisToFree : TrunkPortTable Updation Failed");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return CFG_FAILURE; 
      } 
      else
      {
         /* Send Delete AbisE1 to BICH */
         oamsCfgBichDeleteAbisE1.e1Id = receivedMsgPtr->trunkPortId;   
         cfgSendMessage(&oamsCfgBichDeleteAbisE1, sizeof(OamsCfgBichDeleteAbisE1), ENT_OAMS_BICH,
               OAMS_CFG_BICH_DELETE_ABIS_E1, 0);

         /* Update Internal Data Structure of E1 */
         LOG_PRINT(LOG_INFO,"updateUsageTypeAbisToFree : Update Internal E1 Data Structure ");    
         gE1Data[receivedMsgPtr->trunkPortId].usageType = receivedMsgPtr->usageType;
      }
   }
   LOG_PRINT(LOG_INFO,"Exiting Function : updateUsageTypeAbisToFree");
   return CFG_SUCCESS;   
}

/********************************* Function  Header*****************************
  Function Name   : usageTypeDefaultToAbis()
Parameters      : None
Return type     : I_Void
Purpose         : It update usageType of Trunk in TrunkPortTable
Other Note      : Added For 
 *******************************************************************************/
I_S32 updateUsageTypeFreeToAbis()
{
   TrunkPortTableApi*        receivedMsgPtr      = ( TrunkPortTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   OamsCfgBichInitAbisE1   oamsCfgBichInitAbisE1;
   I_U32                     status              = ZERO;
   I_S32                     dbStatus            = -1;

   LOG_PRINT(LOG_INFO,"Entering Function : updateUsageTypeFreeToAbis");

#if 0
   /*BSC R2.0 Changes Starts*/
   //status = updateFreeLAPDEntriesAsBusy(mccLinkTablePtrSelf,mccLinkTablePtrMate,sizeSelf,sizeMate,reqEntries);
   //if(status == CFG_FAILURE)
   //{
   //   LOG_PRINT(LOG_MAJOR,"updateUsageTypeFreeToAbis: DB Call updateMccLinkresource Table fails");
   //   cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED); 
   //   free(mccLinkTablePtrSelf);
   //   free(mccLinkTablePtrMate);
   //   return CFG_FAILURE;
   //}     
   /*BSC R2.0 Changes Ends*/

   /* Free the Memory */            
   free(mccLinkTablePtrSelf);         
   free(mccLinkTablePtrMate);

   //LOG_PRINT(LOG_INFO,"Required No of Free Entries are marked as Busy in MccLinkResource Table");      
#endif 

   status = populateAbisTimeSlotTable();
   if( status == CFG_FAILURE )
   {
      LOG_PRINT(LOG_MAJOR,"updateUsageTypeFreeToAbis: Insertion Failed in AbisTimeSlotTable");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return CFG_FAILURE; 
   }  

   /* Update E1 Data in AbisE1List */
   //addE1InAbisE1TsList(receivedMsgPtr->trunkPortId, receivedMsgPtr->usageType);

   /*BSC R2.0 Changes Starts*/
   /* Add data corresponding to E1 in BicE1TeiMap Table */
   //addE1DataBicTeiE1MapTable(receivedMsgPtr->trunkPortId);
   /*BSC R2.0 Changes Ends*/

   /* Initialize gMaxCellsNum variable according to the changes in total 
    * available LAPD_TRX type timeslots in BSC */
   //initGlobalMaxCellNumVar();

   /* Update data in DB */
   dbStatus = updateUsageTypeInTrunkPortTable(receivedMsgPtr->trunkPortId,receivedMsgPtr->usageType);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_INFO,"updateUsageTypeFreeToAbis : TrunkPortTable Updation Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE; 
   }
   else
   { 
      dbStatus = updateUsageTypeInTrunkTable(receivedMsgPtr->trunkPortId,receivedMsgPtr->usageType);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_INFO,"updateUsageTypeFreeToAbis : TrunkPortTable Updation Failed");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return CFG_FAILURE; 
      } 
      else
      {
         /* Send Update AbisE1 to BICH */
         oamsCfgBichInitAbisE1.e1Id = receivedMsgPtr->trunkPortId;
         cfgSendMessage(&oamsCfgBichInitAbisE1, sizeof(OamsCfgBichInitAbisE1), ENT_OAMS_BICH,
            OAMS_CFG_BICH_INIT_ABIS_E1, 0);

         /* Update Internal Data Structure of E1 */
         LOG_PRINT(LOG_INFO,"updateUsageTypeFreeToAbis : Update Internal E1 Data Structure ");    
         gE1Data[receivedMsgPtr->trunkPortId].usageType = receivedMsgPtr->usageType;
      }
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : updateUsageTypeFreeToAbis");
   return CFG_SUCCESS;
}


/********************************* Function  Header*****************************
Function Name   : performValidityCheck()
Parameters      : None
Return type     : I_Void
Purpose         : It will perform validity checks
Other Note      : Added For 
 *******************************************************************************/
I_S32 performValidityCheck(TrunkPortTableApi* TrunkPortTableApiPtr)
{

   LOG_PRINT(LOG_INFO,"Entering Function : performValidityCheck");

   {
      /* Check if logical E1 number is unlocked or lock is in progress */
      if(gE1Data[gE1NumberMapToTrunk].e1State == lockInProgress ) 
      {
         LOG_PRINT(LOG_CRITICAL,"performValidityCheck: E1/Trunk in lock in progress state, sending NACK");
         cfgSendNackToCm(CM_ERR_TRUNK_LOCK_IN_PROGRESS);
         return CFG_FAILURE;          
      }
      if(gE1Data[gE1NumberMapToTrunk].e1State == unlockInProgress ) 
      {
         LOG_PRINT(LOG_CRITICAL,"performValidityCheck: E1/Trunk in unlock in progress state, sending NACK");
         cfgSendNackToCm(CM_ERR_TRUNK_UNLOCK_IN_PROGRESS);
         return CFG_FAILURE;
      }
      //if( TrunkPortTableApiPtr->physicalTrunkPortState == ACTIVATED ) 
      if(gE1Data[gE1NumberMapToTrunk].e1State == unlocked ) 
      {
         LOG_PRINT(LOG_CRITICAL,"performValidityCheck: E1/Trunk is in unlocked state, sending NACK");
         cfgSendNackToCm(CM_ERR_TRUNK_IN_UNLOCKED_STATE);
         return CFG_FAILURE;
      }
      if( gE1Data[gE1NumberMapToTrunk].trunkState == DisableInProgress )
      {
         LOG_PRINT(LOG_INFO,"Disable Procedure in Progress:: Discarding Enable Request");
         cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLE_IN_PROGRESS);
         return CFG_FAILURE;
      }
      if( gE1Data[gE1NumberMapToTrunk].trunkState == EnableInProgress )
      {
         LOG_PRINT(LOG_INFO,"Enable Procedure in Progress:: Discarding Disable Request");
         cfgSendNackToCm(CM_ERR_TRUNKPORT_ENABLE_IN_PROGRESS);
         return CFG_FAILURE;
      }
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : performValidityCheck");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : updateFreeLAPDEntriesAsBusy()
Parameters      : 
Return type     : I_Void
Purpose         : It will checks whether the require number of free entries are
                : present or not. If Present then update these rows with the FirstE1
                : FirstTs and mark them as BUSY.
Other Note      : Added For 
 *******************************************************************************/
I_U32 updateFreeLAPDEntriesAsBusy(MccLinkResourceTableApi *mccLinkTablePtrSelf,MccLinkResourceTableApi
      *mccLinkTablePtrMate,I_U16 sizeSelf,I_U16 sizeMate, I_U32 reqEntries)
{
   //TrunkPortTableApi*           receivedMsgPtr   = ( TrunkPortTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   MccLinkResourceTableApi*     tempMccLinkResTableApiPtr    = NULL;
   MccLinkResourceTableApi      updateDbMccLinkResTableApiPtr;
   I_S32                        dbStatus         = -1;
   I_U32                        extTs            =  1;
   I_U32                        count            =  0;

   LOG_PRINT(LOG_INFO,"Entering Function : updateFreeLAPDEntriesAsBusy");
   LOG_PRINT(LOG_INFO,"Value of ReqEntries = %d",reqEntries);
   {
      LOG_PRINT(LOG_INFO,"updateFreeLAPDEntriesAsBusy: Reserve Entries in MccLinkResource Table for Self Card");
      for(count=0; count<reqEntries; count++)
      {
         tempMccLinkResTableApiPtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkTablePtrSelf + (count * sizeSelf));

         memcpy(&updateDbMccLinkResTableApiPtr,tempMccLinkResTableApiPtr, sizeof(MccLinkResourceTableApi)); 

         updateDbMccLinkResTableApiPtr.extTrunkNum   = gE1NumberMapToTrunk;
         updateDbMccLinkResTableApiPtr.extTrunkTs    = extTs++;
         updateDbMccLinkResTableApiPtr.mccLinkStatus = SYS_TS_ALLOCATED;

         dbStatus = updateMccLinkResourceTable(&updateDbMccLinkResTableApiPtr);
         if(DBLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_MAJOR,"updateFreeLAPDEntriesAsBusy : Updation fails in MccLinkResourceTable");
            return CFG_FAILURE;
         }  
      }              
   }

   {
      LOG_PRINT(LOG_INFO,"updateFreeLAPDEntriesAsBusy: Reserve Entries in MccLinkResource Table for Mate Card");
      tempMccLinkResTableApiPtr = NULL;
      extTs =  1;

      for(count=0; count<reqEntries; count++)
      {
         tempMccLinkResTableApiPtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkTablePtrMate + (count * sizeMate));

         memcpy(&updateDbMccLinkResTableApiPtr,tempMccLinkResTableApiPtr, sizeof(MccLinkResourceTableApi)); 

         updateDbMccLinkResTableApiPtr.extTrunkNum   = gE1NumberMapToTrunk;
         updateDbMccLinkResTableApiPtr.extTrunkTs    = extTs++;
         updateDbMccLinkResTableApiPtr.mccLinkStatus = SYS_TS_ALLOCATED;

         dbStatus = updateMccLinkResourceTable(&updateDbMccLinkResTableApiPtr);
         if(DBLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_MAJOR,"updateFreeLAPDEntriesAsBusy : Updation fails in MccLinkResourceTable");
            return CFG_FAILURE;
         }  
      }              
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : updateFreeLAPDEntriesAsBusy");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
  Function Name   : populateAbisTimeslotPerTable()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_U32 populateAbisTimeSlotTable()
{
   TrunkPortTableApi*            receivedMsgPtr   = ( TrunkPortTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   AbisTimeSlotPerTableApi       timeSlotTableApiPtr;
   AbisTimeSlotNonPerTableApi    AbisTimeSlotNonPerTableApiBuf = {0};
  
   I_U32                         count = 0;
   //I_U32                         bicLapdTs = 0;
   I_S32                         dbStatus = 0;

   LOG_PRINT(LOG_INFO,"Entering function : populateAbisTimeslotPerTable()");

/*   if(receivedMsgPtr->usageType==SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10  ||
         receivedMsgPtr->usageType==SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10)
   {
      bicLapdTs = 1; 
   }
   else if(receivedMsgPtr->usageType==SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4)
   {
      bicLapdTs = 4;
   }
   else
   {
      bicLapdTs = 7;
   }

   for(count=1; count<=bicLapdTs; count++)
   {
      timeSlotTableApiPtr.e1Num           = receivedMsgPtr->trunkPortId;
      timeSlotTableApiPtr.tsNum           = count;
      timeSlotTableApiPtr.adminState      = LOCK;
      timeSlotTableApiPtr.usageType       = SYS_TS_USAGE_LAPD_BIC;
      
      AbisTimeSlotNonPerTableApiBuf.e1Num      = receivedMsgPtr->trunkPortId;
      AbisTimeSlotNonPerTableApiBuf.tsNum      = count;
      AbisTimeSlotNonPerTableApiBuf.usageType  = SYS_TS_USAGE_LAPD_BIC;
      AbisTimeSlotNonPerTableApiBuf.adminState = LOCK;

      
      dbStatus=insertAbisTimeSlotPerTable(&timeSlotTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"populateAbisTimeslotPerTable : Insertion fails in AbisTimeSlotPerTable");
         return CFG_FAILURE;
      }
      
      dbStatus=insertAbisTimeSlotNonPerTable(&timeSlotTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"populateAbisTimeslotPerTable : Insertion fails in insertAbisTimeSlotNonPerTable");
         return CFG_FAILURE;
      }*/
      
      /* Update Internal Data Structure of Timeslot */
      /*gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1Number = receivedMsgPtr->trunkPortId;
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1TimeslotID = count;
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1TimeslotState = locked;
   }*/

   for( count=1; count<32; count++ )
   {
      timeSlotTableApiPtr.e1Num           = receivedMsgPtr->trunkPortId;
      timeSlotTableApiPtr.tsNum           = count;
      timeSlotTableApiPtr.adminState      = UNLOCK;

      AbisTimeSlotNonPerTableApiBuf.e1Num      = receivedMsgPtr->trunkPortId;
      AbisTimeSlotNonPerTableApiBuf.tsNum      = count;
      AbisTimeSlotNonPerTableApiBuf.adminState = UNLOCK;
      
      timeSlotTableApiPtr.usageType            = SYS_TS_USAGE_ABIS_FREE;
      AbisTimeSlotNonPerTableApiBuf.usageType  = SYS_TS_USAGE_ABIS_FREE;
      
      dbStatus=insertAbisTimeSlotPerTable(&timeSlotTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"populateAbisTimeslotPerTable : Insertion fails in AbisTimeSlotPerTable");
         return CFG_FAILURE;
      }

      dbStatus=insertAbisTimeSlotNonPerTable(&AbisTimeSlotNonPerTableApiBuf);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"populateAbisTimeslotPerTable : Insertion fails in insertAbisTimeSlotNonPerTable");
         return CFG_FAILURE;
      }
      
      /* Update Internal Data Structure of Timeslot */
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1Number = receivedMsgPtr->trunkPortId;
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1TimeslotID = count;
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1TimeslotState = unlocked;
   }
   LOG_PRINT(LOG_INFO,"populateAbisTimeslotPerTable : Internal Timeslot Data Structure Updated");    

   LOG_PRINT(LOG_INFO,"Exiting  function : populateAbisTimeslotPerTable()");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : delAbisTimeSlotTable()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_U32 delAbisTimeSlotTable(I_U32 usageTypeInDB)
{
   TrunkPortTableApi*               receivedMsgPtr= ( TrunkPortTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg)); 
   AbisTimeSlotPerTableIndices      abisTimeSlotIndices; 
   AbisTimeSlotNonPerTableIndices   AbisTimeSlotNonTableIndicesBuf; 
   I_U32                            count = 0;
   I_U32                            dbStatus  = 0;

   LOG_PRINT(LOG_INFO,"Entering function : deleteAbisTimeslotPerTable()");

   for(count=1; count<32; count++)
   {
      abisTimeSlotIndices.e1Num           = receivedMsgPtr->trunkPortId;
      abisTimeSlotIndices.tsNum           = count;

      dbStatus=deleteAbisTimeSlotPerTable(&abisTimeSlotIndices);

      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"deleteAbisTimeslotPerTable : Deletion fails in AbisTimeSlotPerTable");
         return CFG_FAILURE;
      }
      
      AbisTimeSlotNonTableIndicesBuf.e1Num    = receivedMsgPtr->trunkPortId;
      AbisTimeSlotNonTableIndicesBuf.tsNum    = count;
      
      dbStatus=deleteAbisTimeSlotNonPerTable(&AbisTimeSlotNonTableIndicesBuf);

      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"deleteAbisTimeSlotNonPerTable : Deletion fails in AbisTimeSlotPerTable");
         return CFG_FAILURE;
      }
      /* Update Internal Data Structure of Timeslot */
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1Number = receivedMsgPtr->trunkPortId;
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1TimeslotID = count;
      gE1TimeslotData[receivedMsgPtr->trunkPortId][count].e1TimeslotState = none;
   }
   LOG_PRINT(LOG_INFO,"deleteAbisTimeslotPerTable : Internal Timeslot Data Structure Updated ");    

   /*BSC R2.0 Changes Starts*/
   #if 0
   if(usageTypeInDB==SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10  ||
        usageTypeInDB==SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10)
   {
      bicLapdTs = 1; 
   }
   else if(usageTypeInDB==SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4)
   {
      bicLapdTs = 4;
   }
   else
   {
      bicLapdTs = 7;
   }

   LOG_PRINT(LOG_INFO,"deleteAbisTimeslotPerTable : value of BicLapdTs = %d",bicLapdTs);

   LOG_PRINT(LOG_INFO,"deleteAbisTimeslotPerTable : Mark the entries Reserved in MccLinkResource as FREE");
   for(count=1;count<=bicLapdTs;count++)
   {
      dbStatus=freeMccLinkResourceTablebyExternalE1Ts(receivedMsgPtr->trunkPortId,count,INVALID_E1,INVALID_TS,SYS_TS_FREE);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"deleteAbisTimeslotPerTable : Db wrapper freeMccLinkResourceTablebyExternalE1Ts Fails");
         return CFG_FAILURE;
      } 
   } 

   #endif 
   /*BSC R2.0 Changes Ends*/
   LOG_PRINT(LOG_INFO,"Exiting function : deleteAbisTimeslotPerTable()");
}

/********************************* Function  Header*****************************
  Function Name   : updateUsageTypeFreeToAif()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_S32 updateUsageTypeFreeToAif()
{
   LOG_PRINT(LOG_INFO,"Entering function : updateUsageTypeFreeToAif()");
   TrunkPortTableApi *receivedMsgPtr = (TrunkPortTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg)); 
   if (updateUsageTypeInTrunkPortTable(receivedMsgPtr->trunkPortId,SYS_E1_USAGE_AIF) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateTrunkPortTable Failed..");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE;  
    }
   LOG_PRINT(DEBUG,"Going to update trunkportId(%d) to usageType(%d)", 
           receivedMsgPtr->trunkPortId,SYS_E1_USAGE_AIF);
   if (updateUsageTypeInTrunkTable(receivedMsgPtr->trunkPortId,SYS_E1_USAGE_AIF) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateUsageTypeInTrunkTable Failed..");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE;  
   }
   LOG_PRINT(LOG_INFO,"updateUsageTypeFreeToAif : UsageType updated in DB ");    
   LOG_PRINT(LOG_INFO,"updateUsageTypeFreeToAif : Update Internal E1 Data Structure ");    
   gE1Data[receivedMsgPtr->trunkPortId].usageType = SYS_E1_USAGE_AIF;
   LOG_PRINT(LOG_INFO,"Exiting function : updateUsageTypeFreeToAif()");
   return CFG_SUCCESS;
}


/********************************* Function  Header*****************************
  Function Name   : updateUsageTypeAifToFree()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_S32 updateUsageTypeAifToFree()
{
   LOG_PRINT(LOG_INFO,"Entering updateUsageTypeAifToFree()");
   TrunkPortTableApi *receivedMsgPtr = (TrunkPortTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg)); 

   if (updateUsageTypeInTrunkPortTable(receivedMsgPtr->trunkPortId,SYS_E1_USAGE_NONE) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateTrunkPortTable Failed..");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE;  
   }

   if (updateUsageTypeInTrunkTable(receivedMsgPtr->trunkPortId,SYS_E1_USAGE_NONE) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateUsageTypeInTrunkTable Failed..");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE;  
   }
   LOG_PRINT(LOG_INFO,"updateUsageTypeAifToFree : UsageType updated in DB ");    
   LOG_PRINT(LOG_INFO,"updateUsageTypeAifToFree : Update Internal E1 Data Structure ");    
   gE1Data[receivedMsgPtr->trunkPortId].usageType = SYS_E1_USAGE_NONE;
   LOG_PRINT(LOG_INFO,"Exiting updateUsageTypeAifToFree()");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
  Function Name   : validityChecksAifToFree()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_S32 validityChecksAifToFree()
{
   LOG_PRINT(LOG_INFO,"Entering validityChecksAifToFree()");
   TrunkPortTableApi *receivedMsgPtr = (TrunkPortTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg)); 

   if (isAnyLinkExistOnGivenE1(receivedMsgPtr->trunkPortId) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"Link Exists on the received E1");
      cfgSendNackToCm(CM_ERR_LINK_EXISTS_ON_RCVD_E1);
      return CFG_FAILURE;  
   }

   if (isAnyTrunkExistOnGivenE1(receivedMsgPtr->trunkPortId) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"Trunk Exists on the received E1");
      cfgSendNackToCm(CM_ERR_TRUNK_EXISTS_ON_RCVD_E1);
      return CFG_FAILURE;  
   }

   /* PCU R2.5 Aricent --START*/
   if (isFrTimeslot(receivedMsgPtr->trunkPortId) == TRUE)
   {
      LOG_PRINT(LOG_INFO,"FR Link is configured on this port. Change the configuration First");
        cfgSendNackToCm(CM_ERR_FR_LINK_EXISTS_ON_RCVD_E1);
      return CFG_FAILURE;
   }
   /* PCU R2.5 Aricent --END*/

   if(checkForMlpppConfig(receivedMsgPtr->trunkPortId)==CFG_FAILURE)
   {
      LOG_PRINT(LOG_INFO,"Mlppp is configured on this port. Change the configuration First");
   	 cfgSendNackToCm(CM_ERR_MLPPP_IS_CONFIGURED);
     return CFG_FAILURE;
   }

   LOG_PRINT(LOG_INFO,"Exiting validityChecksAifToFree()");
   return CFG_SUCCESS;  
}

/********************************* Function  Header*****************************
Function Name   : E1UsageTypeChangeHandler()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_S32 E1UsageTypeChangeHandler(TrunkPortTableApi* TrunkPortTableApiPtr)
{
   LOG_PRINT(LOG_INFO,"Entering function : E1UsageTypeChangeHandler()");

   TrunkPortTableApi        *receivedMsgPtr      = (TrunkPortTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   MccLinkResourceTableApi  *mccLinkTablePtrSelf = NULL;
   MccLinkResourceTableApi  *mccLinkTablePtrMate = NULL;
   I_U16                     sizeSelf            = 0;
   I_U16                     sizeMate            = 0;
   I_U32                     reqEntries          = 0;
   I_U32                     dbStatus            = 0;
   I_U8                      clkcfg              = FALSE;

   dbStatus = performValidityCheck(TrunkPortTableApiPtr);
   if (dbStatus != CFG_SUCCESS)
   { 
      LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");         
      return CFG_FAILURE;
   }

/* Changes for R2.2 : Start */
   if((receivedMsgPtr->usageType == SYS_E1_USAGE_NONE) &&
         (TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_ABISIF )  
      )
   {
      LOG_PRINT(LOG_INFO,"Request came for change of UsageType of E1 from ABISIF* to FREE");
      if(validityCheckAbisToFree() == CFG_SUCCESS)
      { 
         if( updateUsageTypeAbisToFree(TrunkPortTableApiPtr->usageType) == CFG_SUCCESS)
         {
            /* Send Ack to CM */
            //cfgSendAckToCm();
            return CFG_SUCCESS; 
         }
      } 
   }

   else if((TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_NONE) &&
            (receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF)   
         )
   {
      LOG_PRINT(LOG_INFO,"Request came for change of UsageType of E1 from FREE to ABISIF*");
/* Changes for R2.2 : Start */
      //if(validityCheckFreeToAbis(&mccLinkTablePtrSelf,&mccLinkTablePtrMate,&sizeSelf,&sizeMate,
        // &reqEntries) == CFG_SUCCESS)
      //{
      
      /* Changes For E1-T1:Start */
         if(gBscTrunkType == BPM_TRUNK_TYPE_T1)
         {
            LOG_PRINT(LOG_INFO,"BscTrunkType is ANSI :: Discarding Change in usage type request");
            cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
            return;
         }  
      /* Changes For E1-T1:End */
         if( updateUsageTypeFreeToAbis() == CFG_SUCCESS)
            /* Send Ack to CM */
            //cfgSendAckToCm();
            return CFG_SUCCESS; 
      //}    
   }

#if 0
   else if(((receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10) || 
            (receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1) || 
            (receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4) || 
            (receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7)) &&
         ((TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10) || 
          (TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1) || 
          (TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4) || 
          (TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7)))
   {
      /* Add Code for Abis-If* to Abis-If*  */
      LOG_PRINT(LOG_INFO,"Request came for change of UsageType of E1 from ABISIF* to ABISIF* ");

      if((validityCheckAbisToFree() == CFG_SUCCESS) 
          && 
          (validityCheckAbisToAbis(TrunkPortTableApiPtr->usageType,receivedMsgPtr->usageType) == CFG_SUCCESS))
      {
         if( updateUsageTypeAbisToFree(TrunkPortTableApiPtr->usageType) == CFG_SUCCESS)      
         {
            if(validityCheckFreeToAbis(&mccLinkTablePtrSelf,&mccLinkTablePtrMate,&sizeSelf,&sizeMate,
            &reqEntries) == CFG_SUCCESS)
            {
               if(updateUsageTypeFreeToAbis(mccLinkTablePtrSelf,mccLinkTablePtrMate,sizeSelf,
                  sizeMate,reqEntries) == CFG_SUCCESS)
                    /* Send Ack to CM */
                    //cfgSendAckToCm();
                    return CFG_SUCCESS; 
            }
         }  
      }
    }
#endif
/* Changes for R2.2 : End */

    else if((receivedMsgPtr->usageType == SYS_E1_USAGE_NONE) &&
            ((TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_AIF)))
    {
         LOG_PRINT(LOG_INFO,"Request came for change of UsageType of E1 from AIF to Free ");
          
         /* Mantis Id : 7818 */
         // Check if Trunk port is configured for Clock Source
         clkcfg = IsTrunkPortConfiguredAsClkSrc(TrunkPortTableApiPtr->trunkPortId); 

         if(TRUE == clkcfg)
         {
            LOG_PRINT(LOG_INFO,"Clock source configured on Trunk port:: Discarding Change in usage type request");
            cfgSendNackToCm(CM_ERR_CLK_SRC_CONFIGURED_ON_TRUNKPORT);
            return;
         }
         /* Mantis Id : 7818 */
        
         if( validityChecksAifToFree() == CFG_SUCCESS)
         {
            if( updateUsageTypeAifToFree() == CFG_SUCCESS)
               /* Send Ack to CM */
               //cfgSendAckToCm();
               return CFG_SUCCESS; 
         }
    }

      else if((receivedMsgPtr->usageType == SYS_E1_USAGE_AIF ) &&
            ((TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_NONE)))
     {
         LOG_PRINT(LOG_INFO,"Request came for change of UsageType of E1 from Free to AIF ");
         if( updateUsageTypeFreeToAif() == CFG_SUCCESS)
         {
            /* Send Ack to CM */
            //cfgSendAckToCm();
            return CFG_SUCCESS; 
         }
     }

/* Changes for R2.2 : Start */
      else if((TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_AIF) &&
            (receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF))
      {
/* Changes for R2.2 : End */
         LOG_PRINT(LOG_INFO,"Request came for change of UsageType of E1 from AIF to ABISIF ");

         /* Mantis Id : 7818 */
         // Check if Trunk port is configured for Clock Source
         clkcfg = IsTrunkPortConfiguredAsClkSrc(TrunkPortTableApiPtr->trunkPortId); 

         if(TRUE == clkcfg)
         {
            LOG_PRINT(LOG_INFO,"Clock source configured on Trunk port:: Discarding Change in usage type request");
            cfgSendNackToCm(CM_ERR_CLK_SRC_CONFIGURED_ON_TRUNKPORT);
            return;
         }
         /* Mantis Id : 7818 */
         /* Changes For E1-T1:Start */
         if(gBscTrunkType == BPM_TRUNK_TYPE_T1)
         {
            LOG_PRINT(LOG_INFO,"BscTrunkType is T1 :: Discarding Change in usage type request");
            cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
            return;
         }  
      /* Changes For E1-T1:End */

         if( validityChecksAifToFree() == CFG_SUCCESS)
         {
            /*if(validityCheckFreeToAbis(&mccLinkTablePtrSelf,&mccLinkTablePtrMate,&sizeSelf,&sizeMate,
               &reqEntries) == CFG_SUCCESS)
            {*/
               if(updateUsageTypeFreeToAbis() == CFG_SUCCESS)
                     /* Send Ack to CM */
                     //cfgSendAckToCm();
                     return CFG_SUCCESS; 
            //}
         }
      }

/* Changes for R2.2 : Start */
      else if((receivedMsgPtr->usageType == SYS_E1_USAGE_AIF) &&
             (TrunkPortTableApiPtr->usageType == SYS_E1_USAGE_ABISIF))
      {
/* Changes for R2.2 : End */
         LOG_PRINT(LOG_INFO,"Request came for change of UsageType of E1 from ABISIF to AIF ");
         if( validityCheckAbisToFree() == CFG_SUCCESS)
         {
            if( updateUsageTypeAbisToFree(TrunkPortTableApiPtr->usageType) == CFG_SUCCESS)
            {
               if( updateUsageTypeFreeToAif() == CFG_SUCCESS)
                  /* Send Ack to CM */
                  //cfgSendAckToCm();
                  return CFG_SUCCESS; 
            } 
         }
      }
      else
      {
         LOG_PRINT(LOG_INFO,"Requested change of the usageTypr from:%d to:%d not Supported", 
                           TrunkPortTableApiPtr->usageType,receivedMsgPtr->usageType);
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      }
   LOG_PRINT(LOG_INFO,"Exiting E1UsageTypeChangeHandler()");
   return CFG_FAILURE;  
}

/********************************* Function  Header*****************************
Function Name   : validityCheckAbisToFree()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_U32 validityCheckAbisToFree()
{
   LOG_PRINT(LOG_INFO,"Entering validityCheckAbisToFree()");
   TrunkPortTableApi *receivedMsgPtr = (TrunkPortTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   BicTableApi       *bicTableApiPtr = NULL;
   I_S32              dbStatus       = -1;
   I_U32              rowCount = ZERO;
   I_U16              rowSz = ZERO;

   dbStatus = getSecBicTable(receivedMsgPtr->trunkPortId, &bicTableApiPtr, &rowCount, &rowSz);
   if(DBLIB_SUCCESS == dbStatus)
   {
      /* Bic are configured for E1 */
      free(bicTableApiPtr);
      LOG_PRINT(LOG_INFO,"validityCheckAbisToFree : BICs Configured at BSC for E1 : %d",receivedMsgPtr->trunkPortId);
      cfgSendNackToCm(CM_ERR_BTS_CONFIGURED_FOR_E1);
      return CFG_FAILURE;
   }
   LOG_PRINT(LOG_INFO,"Exiting validityCheckAbisToFree()");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
  Function Name   : validityCheckFreeToAbis()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
I_U32 validityCheckFreeToAbis(MccLinkResourceTableApi **mccLinkTablePtrSelf, MccLinkResourceTableApi
      **mccLinkTablePtrMate,I_U16 *sizeSelf, I_U16 *sizeMate,I_U32 *reqEntries)
{
   #if 0
   LOG_PRINT(LOG_INFO,"Entering function : validityCheckFreeToAbis()");

   TrunkPortTableApi*        receivedMsgPtr      = ( TrunkPortTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   IccCardInfoTableApi      *outData             = NULL;
   IccCardInfoTableApi      *tempIccCardPtr      = NULL;
   I_U32                     outRows             = 0;
   I_U16                     outSize             = 0;
   I_S32                     dbStatus            = -1;
   I_U32                     rowsSelf            = 0;
   I_U32                     rowsMate            = 0;

   if((receivedMsgPtr->usageType ==  SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10) || 
         (receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1))  
   {
      *reqEntries = 1;
   } 
   else if (receivedMsgPtr->usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4)
   {
      *reqEntries = 4;
   } 
   else
   {
      *reqEntries = 7;
   }
   
   /* Check for Free entries in MccLinkResource Table For SELF CARD */
   dbStatus = getFreeMccTrunkNumTsFromMccLinkTable(ICCSELFCARD,SYS_TS_USAGE_ABIS_GENERIC,INVALID_E1,INVALID_TS,SYS_TS_FREE, mccLinkTablePtrSelf, &rowsSelf, sizeSelf);
   if( (dbStatus != DBLIB_SUCCESS) || (rowsSelf == ZERO) )
   {
      LOG_PRINT(LOG_MAJOR,"validityCheckFreeToAbis: No Free entries found in MccLinkResource Table. ");
      cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS);  
      return CFG_FAILURE; 
   }

   if ( *reqEntries > rowsSelf ) 
   {
      LOG_PRINT(LOG_MAJOR,"validityCheckFreeToAbis: Required no of entries for LAPD TS are not Free in MccLinkResource Table");
      free(*mccLinkTablePtrSelf);
      cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS); 
      return CFG_FAILURE;
   }
   else
   {
     /* Check for Free entries in MccLinkResource Table For MATE CARD */
     dbStatus = getFreeMccTrunkNumTsFromMccLinkTable(ICCMATECARD,SYS_TS_USAGE_ABIS_GENERIC,INVALID_E1,INVALID_TS, SYS_TS_FREE,mccLinkTablePtrMate, &rowsMate,sizeMate);
     if( (dbStatus != DBLIB_SUCCESS) || (rowsMate == ZERO) )
     {
        LOG_PRINT(LOG_MAJOR,"validityCheckFreeToAbis: No Free entries found in MccLinkResource Table. ");
        cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS);
        free(*mccLinkTablePtrSelf);
        return CFG_FAILURE; 
     } 
     if ( *reqEntries > rowsMate ) 
     {
        LOG_PRINT(LOG_MAJOR,"validityCheckFreeToAbis: Required no of entries for LAPD TS are not Free in MccLinkResource Table");
        free(*mccLinkTablePtrSelf);
        free(*mccLinkTablePtrMate);
        cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS);
        return CFG_FAILURE;
     }
   }
   /*Now update the mate card information to match with seld card with only cardnum changed*/
   {
      MccLinkResourceTableApi *tempMccLinkResTableApiSelfPtr = NULL;
      MccLinkResourceTableApi *tempMccLinkResTableApiMatePtr = NULL;
      I_U32 count; 
      for(count=0; count< *reqEntries; count++)
      {
        tempMccLinkResTableApiSelfPtr=
          (MccLinkResourceTableApi *)((I_U8 *)(*mccLinkTablePtrSelf) + (count * (*sizeMate)));
        tempMccLinkResTableApiMatePtr = 
          (MccLinkResourceTableApi *)((I_U8 *)(*mccLinkTablePtrMate) + (count * (*sizeMate)));

       *tempMccLinkResTableApiMatePtr  = *tempMccLinkResTableApiSelfPtr;
       tempMccLinkResTableApiMatePtr->cardNum    = ICCMATECARD;
      }              
   }
   
   LOG_PRINT(LOG_INFO,"Exiting function : validityCheckFreeToAbis()");
   #endif
   return CFG_SUCCESS; 
}

/********************************* Function  Header*****************************
  Function Name   : validityCheckAbisToAbis()
Parameters      : 
Return type     : I_Void
Purpose         : 
Other Note      : Added For 
 *******************************************************************************/
#if 0
I_U32 validityCheckAbisToAbis(I_U32 DbUsageType, I_U32 RcvdUsageType)
{
  I_U32 reqEntries          = 0;
  I_U32 neededEntries       = 0;
  I_U32 dbEntries           = 0;
  I_U32 rowsSelf            = 0;
  I_U16 sizeSelf            = 0;
  I_S32 dbStatus            = -1;
  MccLinkResourceTableApi   *mccLinkTablePtrSelf = PNULL;

  switch (DbUsageType) {
    case SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10:
    case SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1:
      dbEntries = 1;
      break;
    case SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4:  
      dbEntries = 4;
      break;
    case SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7:  
      dbEntries = 7;
      break;
  }

  switch (RcvdUsageType) {
    case SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10:
    case SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1:
      reqEntries = 1;
      break;
    case SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4:  
      reqEntries = 4;
      break;
    case SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7:  
      reqEntries = 7;
      break;
  }  

  if (dbEntries >= reqEntries ) {
    return CFG_SUCCESS;
  }
  neededEntries = reqEntries - dbEntries;
   /* Check for Free entries in MccLinkResource Table For SELF CARD */
   dbStatus = getFreeMccTrunkNumTsFromMccLinkTable(ICCSELFCARD,
                                                   SYS_TS_USAGE_ABIS_GENERIC,
                                                   INVALID_E1,
                                                   INVALID_TS,
                                                   SYS_TS_FREE, 
                                                   &mccLinkTablePtrSelf, 
                                                   &rowsSelf, 
                                                   &sizeSelf);

   if( (dbStatus != DBLIB_SUCCESS) || (rowsSelf == ZERO) )
   {
      LOG_PRINT(LOG_MAJOR,"validityCheckFreeToAbis: No Free entries found in MccLinkResource Table. ");
      cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS);  
      return CFG_FAILURE; 
   }

   if ( neededEntries > rowsSelf ) 
   {
      LOG_PRINT(LOG_MAJOR,"[%s]: Req no of entries for LAPD TS not Free in MccLinkResource Table",__func__);
      free(mccLinkTablePtrSelf);
      cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS); 
      return CFG_FAILURE;
   }
   free(mccLinkTablePtrSelf);
   return CFG_SUCCESS;
}

#endif


I_S32 checkAndSendLinkActivationRequestForE1(I_U16 reqType)
{
   LinkTableApi *linkTablePtr = NULL;
   LinkTableApi *tmpLinkPtr = NULL;
   I_U32 outRows = 0;
   I_U16 rowSize = 0;
   I_S32 retVal = FALSE;
   I_U32 cardOprState = 0;


   if (getallLinkTable(&linkTablePtr, &outRows, &rowSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "checkAndSendLinkActivationRequestForE1: getallLinkTable() Failed");
      return retVal;
   }
   switch (reqType)
   {
      case LOCKED:
         {
            while (gLinkMsgSentForE1 < outRows) {
               tmpLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (gLinkMsgSentForE1 *rowSize));
               gLinkMsgSentForE1++;
               /*Mantis - 8686 start*/
               //If the card is not present then try for the next entry
               /* if (getStateForSlotIdIccTable(tmpLinkPtr->cardNum,&cardOprState) != CLIB_SUCCESS) {
                  LOG_PRINT(LOG_DEBUG, "checkAndSendLinkActivationRequestForE1: Received cardNum [%d] does not exists in iccCardInfo Table", tmpLinkPtr->cardNum);
                  continue;
               }*/
             /*  if (cardOprState == CARDSTATE_ACTIVE ||cardOprState == CARDSTATE_STANDBY ) {*/
				      LOG_PRINT(LOG_INFO,"checkAndSendLinkActivationRequestForE1 in case of lock:Trunk recieved from operator is %d",gE1NumberMapToTrunk);
				      LOG_PRINT(LOG_INFO,"checkAndSendLinkActivationRequestForE1 in case of lock:Trunk mapped to E1[%d]",tmpLinkPtr->e1Num);
                  if ((tmpLinkPtr->e1Num == gE1NumberMapToTrunk) && ((tmpLinkPtr->adminState == UNLOCKED) && (gE1Data[tmpLinkPtr->e1Num].e1State == lockInProgress))) {
                     tmpLinkPtr->adminState = LOCKED;
                     LOG_PRINT(LOG_INFO, "checkAndSendLinkActivationRequestForE1: Trunkport[%u] locked  and link[%u] locked ",tmpLinkPtr->e1Num,tmpLinkPtr->linkId);
                     LOG_PRINT(LOG_INFO, "checkAndSendLinkActivationRequestForE1: Sending Link Act ");
                     e1SendLinkAdminTableToScm(tmpLinkPtr,reqType);
                     retVal = TRUE;
                     break;
                  }
               //}
               /*else
                   LOG_PRINT(LOG_DEBUG,"checkAndSendLinkActivationRequestForE1: Not sending Link Activation Request as Link[%u] not for active card", tmpLinkPtr->linkId);*/
               /*Mantis #8686 End*/
               
            }
            free(linkTablePtr);
            return retVal;
         }

      case UNLOCKED:
         {
            while (gLinkMsgSentForE1 < outRows) {
               tmpLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (gLinkMsgSentForE1 *rowSize));
               gLinkMsgSentForE1++;
               /*Mantis - 8686 start*/
               //If the card is not present then try for the next entry
               /*if (getStateForSlotIdIccTable(tmpLinkPtr->cardNum,&cardOprState) != CLIB_SUCCESS) {
                  LOG_PRINT(LOG_DEBUG, "checkAndSendLinkActivationRequestForE1: Received cardNum [%d] does not exists in iccCardInfo Table", tmpLinkPtr->cardNum);
                  continue;
               }
               if (cardOprState == CARDSTATE_ACTIVE || cardOprState == CARDSTATE_STANDBY) {*/

				      LOG_PRINT(LOG_INFO,"checkAndSendLinkActivationRequestForE1 in case of unlock:Trunk recieved from operator is %d",gE1NumberMapToTrunk);
				      LOG_PRINT(LOG_INFO,"checkAndSendLinkActivationRequestForE1 in case of unlock:Trunk mapped to E1[%d]",tmpLinkPtr->e1Num);
                  if ((tmpLinkPtr->adminState == UNLOCKED) && (gE1Data[tmpLinkPtr->e1Num].e1State == unlockInProgress)) {
                     LOG_PRINT(LOG_INFO, "checkAndSendLinkActivationRequestForE1: Trunkport[%u] unlocked  and link[%u] unlocked ",tmpLinkPtr->e1Num,tmpLinkPtr->linkId);
                     LOG_PRINT(LOG_INFO, "checkAndSendLinkActivationRequestForE1: Sending Link Ack --> for activating link[%u]",tmpLinkPtr->linkId);
                     e1SendLinkAdminTableToScm(tmpLinkPtr,reqType);
                     retVal = TRUE;
                     break;
                  }
               //}
               /*else
                   LOG_PRINT(LOG_DEBUG,"checkAndSendLinkActivationRequestForE1: Not sending Link Activation Request as Link[%u] not for active card",tmpLinkPtr->linkId);*/
               
               /*Mantis #8686 End*/
            }
            free(linkTablePtr);
            return retVal;
         }

   }
   return retVal; 
}

/*BSC R2.0 Changes Starts*/
/********************************* Function  Header********************************
Function Name:       SendTrunkPortEnableAlarm()
Parameters:          Pointer to E1 Number
Return type:         void
Purpose:             To Handle the EnableInProgress state.
Other Note:
 ************************************************************************************/
void SendTrunkPortEnableAlarm( I_U8 frameId, I_U8 slotId, I_U16 portId )
{
   OamsCfgAfhSysAlarm oamsCfgAfhSysAlarmBuff = {0};

   oamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = ALARM_TRUNKPORT_ENABLED;
   oamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   oamsCfgAfhSysAlarmBuff.sysAlarm.key1 =frameId;  
   oamsCfgAfhSysAlarmBuff.sysAlarm.key2 = slotId; 
   oamsCfgAfhSysAlarmBuff.sysAlarm.key3 = portId; 
   FillObjTypeFromSlotId(slotId,oamsCfgAfhSysAlarmBuff.sysAlarm.info3); 

   sprintf(oamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
              "TrunkPort Enabled for ChasisId[%d],SlotId[%d],portId[%d]",frameId,slotId, portId);

   cfgSendMessage(&oamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
}

/********************************* Function  Header********************************
Function Name:       SendTrunkPortDisableAlarm()
Parameters:          Pointer to E1 Number
Return type:         void
Purpose:             To Handle the EnableInProgress state.
Other Note:
 ************************************************************************************/
void SendTrunkPortDisableAlarm( I_U8 frameId, I_U8 slotId, I_U16 portId )
{
   OamsCfgAfhSysAlarm oamsCfgAfhSysAlarmBuff = {0};

   oamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = ALARM_TRUNKPORT_DISABLED;
   oamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   oamsCfgAfhSysAlarmBuff.sysAlarm.key1 =frameId;  
   oamsCfgAfhSysAlarmBuff.sysAlarm.key2 = slotId; 
   oamsCfgAfhSysAlarmBuff.sysAlarm.key3 = portId; 
   FillObjTypeFromSlotId(slotId,oamsCfgAfhSysAlarmBuff.sysAlarm.info3); 

   sprintf(oamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
              "TrunkPort Disabled for ChasisId[%d],SlotId[%d],portId[%d]",frameId,slotId, portId);

   LOG_PRINT(DEBUG,"Sending ALARM_TRUNKPORT_DISABLED");
   cfgSendMessage(&oamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
}
/*BSC R2.0 Changes Ends*/
/*Changes PCU R2.5 Aricent -- START*/

/********************************* Function  Header********************************
Function Name:       informNsvcUnlockDisableForUnlockedNsvcsToE1()
Parameters:          void
Return type:         void
Purpose:             to inform E1Object Handler that all the Nsvcs for this
                     E1 are Disabled.
Other Note:
 ************************************************************************************/
I_Void informNsvcUnlockDisableForUnlockedNsvcsToE1()
{
   e1ObjectUpdateAdminStateAndSendAlarm(LOCKED);
}

/********************************* Function  Header********************************
Function Name:       informNsvcUnlockEnableForUnlockDisabledNsvcsToE1()
Parameters:          void
Return type:         void
Purpose:             to inform E1Object Handler that all the Nsvcs for this
                     E1 are Enabled.
Other Note:
 ************************************************************************************/
I_Void informNsvcUnlockEnableForUnlockDisabledNsvcsToE1()
{
   e1ObjectUpdateAdminStateAndSendAlarm(UNLOCKED);
}
/*Changes PCU R2.5 Aricent -- END*/

/********************************* Change History ***************************
  Release     Patch       Author         Description
  CS2                     Pratibha       Enum Removal Change
  BSC CS2.2      Kapil Tyagi             Added Function updateTrunkTable()
  BSC CS4.0      Gaurav Bhatnagar        Added new function for Abis Lock/Unlock
  BSC CS4.0      Harsh Kharbanda         Trunk Port procedures
  BSC R2.0       Gaurav Jain               
 ************************************** End *********************************/

