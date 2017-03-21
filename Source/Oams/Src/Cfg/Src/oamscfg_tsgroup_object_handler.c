/********************************File Header ***********************
  File Name        : oamscfg_tsgroup_object_handler.c
Purpose          : This file contains function defintions for tsGroup Object Handling.
Project          : BSC
Subsystem        : OAMS
Author           : VNL
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h> 

/********************************* Function  Header********************************
Function Name:       getTrunkUsageType()
Parameters:          trunkId:I_U16 
                     trunkUsageType: Pointer to I_U32 
Return type:         I_U32 
Purpose:             1. Checks validity of trunkId.
                     2. If parameters are consistent,CM_SUCCESS will be 
                        returned,else appropriate error will be returned. 
Other Note:          
**********************************************************************************/
I_U32 getTrunkUsageType(I_U16 trunkId,I_U32 *trunkUsageType)
{
   TrunkPortTableApi* trunkPortTableApiPtr = PNULL;
   TrunkPortTableIndices trunkPortTableIndices;
   I_U8 chasisFrameId,slotId;
   I_S32 dbStatus;

  LOG_PRINT(LOG_DEBUG,"Entering Function %s",__FUNCTION__);
  if((dbStatus=getChasisSlotIdTrunkTable(trunkId,&chasisFrameId, &slotId)) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_MAJOR,"Db Error %d",dbStatus);
    return CM_ERR_GET_DB_OPER_FAILED;
  }
  trunkPortTableIndices.chasisFrameId=chasisFrameId;
  trunkPortTableIndices.slotId=slotId;
  trunkPortTableIndices.trunkPortId=trunkId;
  
  dbStatus=getTrunkPortTable(&trunkPortTableIndices,&trunkPortTableApiPtr);
  if(DBLIB_SUCCESS != dbStatus)
  {
    LOG_PRINT(LOG_MAJOR,"Db Error %d",dbStatus);
    LOG_PRINT(INFO,"%s: TrunkId(%d) does not exist",__FUNCTION__,trunkId); 
    return CM_ERR_TRUNKPORT_DOES_NOT_EXIST; // TB  Changed
  }
  else
  {
    *trunkUsageType=trunkPortTableApiPtr->usageType;
    LOG_PRINT(DEBUG,"usageType (%d) for TrunkId(%d)",
        *trunkUsageType,trunkId);
    free(trunkPortTableApiPtr);
  }

  LOG_PRINT(LOG_DEBUG,"Exiting Function %s",__FUNCTION__);
  return CM_SUCCESS;
}

/********************************* Function  Header*****************************
   Function Name   : fillTSMapForTrunk()
Parameters   : busyTSMap :: I_U32
               numTs     :: I_U32
               tsMap :: Pointer to I_U32
Return type   : I_S32
Purpose      : It sends Switch Connect request for the timeslots allocated on 
               first E1 to those allocated on second E1
Other Note   : 
 *******************************************************************************/
I_U32 fillTSMapForTrunk(I_U32 busyTSMap,I_U32 numTs,I_U32 *tsMap)
{
  I_U32 retStatus=CM_SUCCESS; 
  I_U32 ctr,maxTrunkTs;
  I_U32 tsFound=0;
  I_U32 temp;


  LOG_PRINT(DEBUG,"Entering Function %s",__FUNCTION__);
  if(gBscTrunkType==BPM_TRUNK_TYPE_T1)
  {
    maxTrunkTs=MAX_T1_TS;
  }
  else
  {
    maxTrunkTs=MAX_E1_TS;
  }

    LOG_PRINT(DEBUG,"TrunkType %d Max Trunk Ts %d",gBscTrunkType,maxTrunkTs);
    for(ctr=0;ctr<maxTrunkTs && tsFound<numTs;ctr++)
    {
      LOG_PRINT(DEBUG,"Searching %d timeslot in busyTsMap",(maxTrunkTs - ctr -1));
      temp=1<<(maxTrunkTs-ctr-1); 
      /*TimeSlot is free if AND operation with busy map results in 0 */
      if((busyTSMap & temp)  == 0)
      {
        tsFound++;
        LOG_PRINT(DEBUG,"TS(%d) found free, so allocating to tsGroup",(maxTrunkTs-ctr-1));
        *tsMap|=temp;
      }
    } 
    if(tsFound < numTs)
    {
      LOG_PRINT(MAJOR,"Fewer TimeSlots available on TrunkPorts");
      retStatus=CM_ERR_FEW_FREE_TS_ON_TRUNKPORT;
    }

  LOG_PRINT(DEBUG,"Exiting Function %s",__FUNCTION__);
  return retStatus;
} 

/********************************* Function  Header*****************************
   Function Name   : convertTsBitMapToArray()
Parameters   : numTs :: I_U32
               tsMap :: I_U32
               tsAllocatedArray :: Pointer to I_U8
Return type   : I_S32
Purpose      : It stores all the timeSlots that are assigned in tsMap to tsAllocatedArray
Other Note   : 
 *******************************************************************************/
I_Void convertTsBitMapToArray(I_U32 numTs,I_U32 tsMap,I_U8* tsAllocatedArray)
{
  I_U32 maxTrunkTs;
  I_U32 ctr;
  I_U32 foundTS=0;
  I_U32 temp=0;

  LOG_PRINT(DEBUG,"Entering Function %s",__FUNCTION__);
  if(gBscTrunkType== BPM_TRUNK_TYPE_T1)
    maxTrunkTs=MAX_T1_TS;
  else
    maxTrunkTs=MAX_E1_TS;

  for(ctr=0;ctr<maxTrunkTs && foundTS<numTs;ctr++)
  {
    temp=1<<(maxTrunkTs-ctr-1);
    if((temp & tsMap) == temp)
    {
      LOG_PRINT(DEBUG,"TS Allocated %d",(maxTrunkTs-ctr-1));
      tsAllocatedArray[foundTS++]=(I_U8)(maxTrunkTs-ctr-1);
    }
  }
    
  LOG_PRINT(DEBUG,"Exiting Function %s",__FUNCTION__);
}

/********************************* Function  Header*****************************
   Function Name   : prepAndSndSwitchConForTsGroup()
Parameters   : firstTrunk :: I_U16
               tsArray1 :: Pointer to I_U8
               secondTrunk :: I_U16
               tsArray2 :: Pointer to I_U8
Return type   : I_S32
Purpose      : It sends Switch Connect request for the timeslots allocated on 
               first E1 to those allocated on second E1
Other Note   : 
 *******************************************************************************/
I_S32 prepAndSndSwitchConForTsGroup(I_U16 firstTrunk, I_U8 *tsArray1,
    I_U16 secondTrunk, I_U8 *tsArray2,I_U32 numTs)
{
   I_U32 retStatus=CM_SUCCESS;
   OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
   I_U32 ctr;

   LOG_PRINT(LOG_INFO,"Entering Function : %s",__FUNCTION__);

    for(ctr=0;ctr<numTs;ctr++)
    {
      oamsCfgGrhmSwitchConnect.firstE1Num = firstTrunk;
      oamsCfgGrhmSwitchConnect.firstTimeSlotNum = tsArray1[ctr];
      oamsCfgGrhmSwitchConnect.secondE1Num = secondTrunk;
      oamsCfgGrhmSwitchConnect.secondTimeSlotNum = tsArray2[ctr];
      LOG_PRINT(LOG_DEBUG,"%s: First E1 : %d, \
          First Ts : %d, SecE1 : %d, SecTs : %d",\
          __FUNCTION__,firstTrunk, tsArray1[ctr], secondTrunk,tsArray2[ctr]);
      cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
          ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);

    } /*for(ctr=0... */


   LOG_PRINT(LOG_INFO,"Exiting Function : %s",__FUNCTION__);
   return retStatus;
}

/********************************* Function  Header*****************************
   Function Name   : prepAndSndSwitchDisconnForTsGroup()
Parameters   : firstTrunk :: I_U16
               tsArray1 :: Pointer to I_U8
               secondTrunk :: I_U16
               tsArray2 :: Pointer to I_U8
Return type   : I_S32
Purpose      : It sends Switch Disconnect request for the timeslots allocated on 
               first E1 to those allocated on second E1
Other Note   : 
 *******************************************************************************/
I_S32 prepAndSndSwitchDisconnForTsGroup(I_U16 firstTrunk, I_U8 *tsArray1,
    I_U16 secondTrunk, I_U8 *tsArray2,I_U32 numTs)
{
   I_U32 retStatus = CM_SUCCESS;
   OamsCfgGrhmSwitchDisconnect oamsCfgGrhmSwitchDisconnect;
   I_U32 ctr;

   LOG_PRINT(LOG_INFO,"Entering Function : %s",__FUNCTION__);

    for(ctr=0;ctr<numTs;ctr++)
    {
      oamsCfgGrhmSwitchDisconnect.firstE1Num = firstTrunk;
      oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = tsArray1[ctr];
      oamsCfgGrhmSwitchDisconnect.secondE1Num = secondTrunk;
      oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = tsArray2[ctr];
      LOG_PRINT(LOG_DEBUG,"%s: First E1 : %d, \
          First Ts : %d, SecE1 : %d, SecTs : %d",\
          __FUNCTION__,firstTrunk, tsArray1[ctr], secondTrunk,tsArray2[ctr]);
      cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchDisconnect),
          ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);

    } /*for(ctr=0... */


   LOG_PRINT(LOG_INFO,"Exiting Function : %s",__FUNCTION__);
   return retStatus;
}

/********************************* Function  Header********************************
Function Name:       sndSwtConnForAllTsGroupMap()
Parameters:          None 
Return type:         None 
Purpose:             Send Switch Connect to GRHM for all TsGroups in DB  
Other Note:          
**********************************************************************************/
I_Void sndSwtConnForAllTsGroupMaps()
{
  I_S32 retStatus;
  I_U32 rowsCount = 0,ctr=0;
  I_U16 outSize = 0;
  TsGroupMapTableApi *tsGroupMapTableApiPtr=PNULL,*tmpTsGroupMapPtr=PNULL;
  I_U8 tsArray1[MAX_E1_TS],tsArray2[MAX_E1_TS];

  LOG_PRINT(LOG_DEBUG,"Entering Function %s",__FUNCTION__);
  retStatus=getallTsGroupMapTable(&tsGroupMapTableApiPtr,&rowsCount,&outSize);
  if(CLIB_SUCCESS == retStatus)
  {
    for(ctr=0;ctr<rowsCount;ctr++)
    {
      memset(tsArray1,0,MAX_E1_TS);
      memset(tsArray2,0,MAX_E1_TS);
      tmpTsGroupMapPtr=(TsGroupMapTableApi*)((I_U8*)tsGroupMapTableApiPtr + ctr*outSize);
      LOG_PRINT(DEBUG,"Calling convertTsBitMapToArray for E1(%d)",tmpTsGroupMapPtr->trunkPortId1);
      convertTsBitMapToArray(tmpTsGroupMapPtr->numTS,tmpTsGroupMapPtr->timeSlotMap1,tsArray1);
      LOG_PRINT(DEBUG,"Calling convertTsBitMapToArray for E1(%d)",tmpTsGroupMapPtr->trunkPortId2);
      convertTsBitMapToArray(tmpTsGroupMapPtr->numTS,tmpTsGroupMapPtr->timeSlotMap2,tsArray2);

      retStatus=prepAndSndSwitchConForTsGroup(tmpTsGroupMapPtr->trunkPortId1,tsArray1,tmpTsGroupMapPtr->trunkPortId2,tsArray2,tmpTsGroupMapPtr->numTS);
    }
    free(tsGroupMapTableApiPtr);
  }
  LOG_PRINT(LOG_DEBUG,"Exiting Function %s",__FUNCTION__);

  return;
}

/********************************* Function  Header********************************
Function Name:       allocateTSforTsGroup()
Parameters:          firstTrunk:I_U16 
                     secondTrunk:I_U16
                     numTs:I_U32
                     tsMap1: Pointer to I_U32
                     tsMap2: Pointer to I_U32
Return type:         CM_SUCCESS or CM_ERR_NO_FREE_TS_IN_TRUNKPORT
Purpose:             1. Do a DB wrapper call to find free Ts on first Trunk. Wrapper returns
                        bitMap of TS that are already allocated on Trunk.
                     2. Take numTs bits from MSB which are 0 and set the tsMap1 with
                        the bits 
                     3. Repeat steps 1 and 2 for second Ts and tsMap2
Other Note:         TBD 
**********************************************************************************/
I_U32 allocateTSforTsGroup(I_U16 firstTrunk,I_U16 secondTrunk,I_U32 numTs,
    I_U32 *tsMap1,I_U32 *tsMap2,I_U32 usageType1,I_U32 usageType2)
{
  I_U32 retStatus=CM_SUCCESS;
  I_U32 busyTsMap=0;
  I_U32 maxTSMask=0;

  LOG_PRINT(DEBUG,"Entering Function %s",__FUNCTION__);
  /* 0th TimeSlot is never allocated */
  if(gBscTrunkType ==BPM_TRUNK_TYPE_T1)
  {
    maxTSMask=0xFFFFFF;
  }
  else
  {
    maxTSMask=0xFFFFFFFF;
  }
  
  busyTsMap=getBusyTsMapOnTrunkPort(firstTrunk,usageType1);
  LOG_PRINT(DEBUG,"For trunk(%d) busyTsMap(0x%x)",firstTrunk,busyTsMap);
  if(busyTsMap == maxTSMask)
  {
    LOG_PRINT(MAJOR,"All TimeSlots busy on TrunkPort(%d)",firstTrunk);
    retStatus=CM_ERR_NO_FREE_TS_IN_TRUNKPORT;
  }
  else
  {
    retStatus=fillTSMapForTrunk(busyTsMap,numTs,tsMap1);
    LOG_PRINT(DEBUG,"For Trunk(%d) allocated TsMap(0x%x)",firstTrunk,*tsMap1);
    if(retStatus != CM_SUCCESS)
    {
      return retStatus;
    }
    else
    {
      busyTsMap=getBusyTsMapOnTrunkPort(secondTrunk,usageType2);
      LOG_PRINT(DEBUG,"For trunk(%d) busyTsMap(0x%x)",secondTrunk,busyTsMap);
      if(busyTsMap == maxTSMask)
      {
        LOG_PRINT(MAJOR,"All TimeSlots busy on TrunkPort(%d)",firstTrunk);
        retStatus=CM_ERR_NO_FREE_TS_IN_TRUNKPORT;
      }
      else
      {
        retStatus=fillTSMapForTrunk(busyTsMap,numTs,tsMap2);
        LOG_PRINT(DEBUG,"For Trunk(%d) allocated TsMap(0x%x)",secondTrunk,*tsMap2);
        if(retStatus!=CM_SUCCESS)
        {
          return retStatus;
        }
      }
    }
  } /* if(busyTsMap ... */

  LOG_PRINT(DEBUG,"Exiting Function %s",__FUNCTION__);
  return retStatus;
}

I_U32 updateAbisTimeSlotforTsGroup(I_U16 trunkId,I_U32 numTs,I_U8 *tsArray,I_U32 usageType)
{
  I_U32 ctr;
  I_S32 updStatus;
  I_U32 retStatus=CM_SUCCESS;


  LOG_PRINT(LOG_DEBUG,"Entering Function %s",__FUNCTION__);
  LOG_PRINT(DEBUG,"Updating usageType for E1(%d)",trunkId);
  for(ctr=0;ctr<numTs;ctr++)
  {
    LOG_PRINT(DEBUG,"Marking TS(%d) with usageType(%d) in AbisTimeSlotPerTable",tsArray[ctr],usageType);
    updStatus=updateRowAbisTimeSlotPerTable(trunkId,(I_U32)tsArray[ctr],usageType);
    if(updStatus!=CFG_SUCCESS)
    {
      retStatus=CM_ERR_UPDATE_DB_OPER_FAILED;
      break;
    }
  } 
  LOG_PRINT(LOG_DEBUG,"Exiting Function %s",__FUNCTION__);

  return retStatus;
}

/******************************* Function  Header*****************************
  Function Name : AreTimeSlotsNotUsedForTsGroup()
Parameters    : I_U16 e1Id,I_U32 tsMap 
Return type   : I_S32
Purpose       : To check the timeSlots are busy for TsGroup or not 
                CFG_FAILURE - means busy
                CFG_SUCCESS - means free
Other Note    : 
 *****************************************************************************/
I_U32 AreTimeSlotsNotUsedForTsGroup(I_U16 e1Id,I_U32 tsMap)
{
  I_U32 tsBitMap;

  LOG_PRINT(LOG_DEBUG,"Entering Function %s",__FUNCTION__);
  LOG_PRINT(LOG_DEBUG,"E1(%d) tsMap(0x%x)",e1Id,tsMap);
  tsBitMap = getBusyTsMapForTsGroup(e1Id);
  LOG_PRINT(LOG_DEBUG,"busyTsMap(0x%x)",tsBitMap);
  if(gBscTrunkType == BPM_TRUNK_TYPE_T1)
    tsBitMap|=0xFF000000; 

  if((tsBitMap & tsMap) != 0)
  {
    LOG_PRINT(LOG_INFO," One of the TimeSlots is already allocated in E1 [%u] ", e1Id);
    LOG_PRINT(LOG_DEBUG,"Exiting Function %s",__FUNCTION__);
    return CFG_FAILURE;
  }
    
  LOG_PRINT(LOG_DEBUG,"Exiting Function %s",__FUNCTION__);
  return CFG_SUCCESS;
}

/********************************* Change History ***************************
  Release     Patch       Author         Description
  BSC R2.5.5              Gaurav Jain               
 ************************************** End *********************************/

