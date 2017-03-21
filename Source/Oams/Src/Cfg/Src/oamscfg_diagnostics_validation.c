/***********************************File Header ***************************
File Name        : oamscfg_diagnostics_validation.c
Purpose          : This file contains validation checks for CFG Diagnostics implementation 
Project          : BSC OAM
Subsystem        : Oams
Author           : Raj Kumar
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>

/*Start Remove these hashdefs */
/* Card State */
#define VALIDATE_ICC_CARD_DATA(result, dataPtr)\
{\
		IccCardInfoTableIndices indx;\
		IccCardInfoTableApi *dbData;\
    I_S32 dbResult;\
		indx.chasisFrameId = ((IccDiagTableApi *)dataPtr)->chasisFrameId;\
		indx.slotId = ((IccDiagTableApi *)dataPtr)->slotId;\
		dbResult = getIccCardInfoTable(&indx, &dbData);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		result = CM_ERR_INVALID_CARD_STATE;\
		if(dbData->physicalPresenceState == PRESENT)\
		{\
			if((dbData->cardOperationalState == BPM_CARDSTATE_ACTIVE)||\
			   (dbData->cardOperationalState == BPM_CARDSTATE_STANDBY)||\
			   (dbData->cardOperationalState == BPM_CARDSTATE_DIAGNOSTIC))\
			{\
				result = CM_SUCCESS;\
			}\
		}\
		free(dbData);\
}

#define VALIDATE_EIC_CARD_DATA(result, dataPtr)\
{\
			EicCardInfoTableIndices indx;\
			EicCardInfoTableApi *dbData;\
			indx.chasisFrameId = ((EicDiagTableApi *)dataPtr)->chasisFrameId;\
			indx.slotId = ((EicDiagTableApi *)dataPtr)->slotId;\
			dbResult = getEicCardInfoTable(&indx, &dbData);\
			if(dbResult != DB_SUCCESS)\
			{\
				result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
				return result;\
			}\
			free(dbData);\
}

#define VALIDATE_PSU_CARD_DATA(result, dataPtr)\
{\
		PowerSupplyInfoTableIndices indx;\
		PowerSupplyInfoTableApi *dbData;\
		indx.chasisFrameId = ((PwrSupDiagTableApi *)dataPtr)->chasisFrameId;\
		indx.slotId = ((PwrSupDiagTableApi *)dataPtr)->slotId;\
		dbResult = getPowerSupplyInfoTable(&indx, &dbData);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		free(dbData);\
}

#define VALIDATE_FANTRAY_CARD_DATA(result, dataPtr)\
{\
		FanTrayInfoTableIndices indx;\
		FanTrayInfoTableApi *dbData;\
		indx.chasisFrameId = ((FanTrayDiagTableApi *)dataPtr)->chasisFrameId;\
		indx.fanTrayId = ((FanTrayDiagTableApi *)dataPtr)->fanTrayId;\
		dbResult = getFanTrayInfoTable(&indx, &dbData);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		free(dbData);\
}

#define CHECK_SLOT_TRUNKPORT_STATE(diagTableName, result, objState, dataPtr)\
{\
		I_U32 outRows1 = 0;\
		I_U16 outSize1 = 0;\
		I_U16 count = 0;\
		TrunkPortTableApi *dbDataTP;\
		dbResult = getallTrunkPortTable(&dbDataTP, &outRows1, &outSize1);\
		if(dbResult == DB_SUCCESS)\
		{\
				for(count = 0; count < outRows1; count++)\
				{\
						if(  ( (dbDataTP + count)->chasisFrameId == ((diagTableName *)dataPtr)->chasisFrameId) &&\
							   ( ((diagTableName *)dataPtr)->slotId == (dbDataTP + count)->slotId) )\
						{\
								objState = (dbDataTP + count)->physicalTrunkPortState;\
    						if(objState != ACTIVATED)\
    						{\
      						result = CM_ERR_INCORRECT_OBJ_STATE;\
    						}\
								TrunkTableIndices indx1;\
								TrunkTableApi *dbData1;\
								indx1.e1Num = (dbDataTP + count)->trunkPortId;\
								dbResult = getTrunkTable(&indx1, &dbData1);\
								if(dbResult == DB_SUCCESS)\
								{\
										objState = dbData1->adminState;\
										free(dbData1);\
										if(objState != LOCKED)\
										{\
											result = CM_ERR_INCORRECT_OBJ_STATE;\
											free(dbDataTP);\
											return result;\
										}\
								}\
						}\
				}\
				free(dbDataTP);\
		}\
}
#define CHECK_SLOT_DSP_STATE(diagTableName, result, objState, dataPtr)\
{\
		DspInfoTableApi *dbDataDSP;\
		I_U32 outRows1 = 0;\
		I_U16 outSize1 = 0;\
		I_U16 count = 0;\
		dbResult = getallDspInfoTable(&dbDataDSP, &outRows1, &outSize1);\
		if(dbResult == DB_SUCCESS)\
		{\
				for(count = 0; count < outRows1; count++)\
				{\
						indx.chasisFrameId = ((diagTableName *)dataPtr)->chasisFrameId;\
						indx.slotId = ((diagTableName *)dataPtr)->slotId;\
						if(((dbDataDSP + count)->chasisFrameId == ((diagTableName *)dataPtr)->chasisFrameId) &&\
							 ((dbDataDSP + count)->slotId == ((diagTableName *)dataPtr)->slotId))\
						{\
								objState = (dbDataDSP + count)->adminState;\
								if(objState != LOCKED)\
								{\
									result = CM_ERR_DSP_UNLOCKED;\
									free(dbDataDSP);\
									return result;\
								}\
						}\
				}\
				free(dbDataDSP);\
		}\
}

#define CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr)\
{\
		IccCardInfoTableIndices indx;\
		IccCardInfoTableApi *dbData;\
		I_U32 outRows1 = 0;\
		I_U16 outSize1 = 0;\
		indx.chasisFrameId = ((IccDiagTableApi *)dataPtr)->chasisFrameId;\
		indx.slotId = ((IccDiagTableApi *)dataPtr)->slotId;\
		dbResult = getIccCardInfoTable(&indx, &dbData);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		objState = dbData->cardOperationalState;\
		free(dbData);\
		if (objState != CARDSTATE_DIAGNOSTIC)\
		{\
			result = CM_ERR_INCORRECT_OBJ_STATE;\
		}\
		else\
		{\
			CHECK_SLOT_TRUNKPORT_STATE(IccDiagTableApi, result, objState, dataPtr);\
			CHECK_SLOT_DSP_STATE(IccDiagTableApi, result, objState, dataPtr);\
		}\
}

#define CHECK_ICC_CARD_ACTIVE_STATE(result, objState, dataPt,diagnosTcIdr)\
{\
		IccCardInfoTableIndices indx;\
		IccCardInfoTableApi *dbData;\
		indx.chasisFrameId = ((IccDiagTableApi *)dataPtr)->chasisFrameId;\
		indx.slotId = ((IccDiagTableApi *)dataPtr)->slotId;\
		dbResult = getIccCardInfoTable(&indx, &dbData);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		objState = dbData->cardOperationalState;\
		free(dbData);\
		if (objState != CARDSTATE_ACTIVE)\
		{\
			result = CM_ERR_INCORRECT_OBJ_STATE;\
		}\
		else\
		{\
			CHECK_SLOT_TRUNKPORT_STATE(IccDiagTableApi, result, objState, dataPtr);\
			if(diagnosTcId == DIAGNOS_TCID_ICC_TSI_All)\
			{\
				CHECK_SLOT_DSP_STATE(IccDiagTableApi, result, objState, dataPtr);\
			}\
		}\
}

#define CHECK_EIC_CARD_STATE(result, objState, dataPtr)\
{\
			EicCardInfoTableIndices indx;\
			EicCardInfoTableApi *dbData;\
			indx.chasisFrameId = ((EicDiagTableApi *)dataPtr)->chasisFrameId;\
			indx.slotId = ((EicDiagTableApi *)dataPtr)->slotId;\
			dbResult = getEicCardInfoTable(&indx, &dbData);\
			if(dbResult != DB_SUCCESS)\
			{\
				result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
				return result;\
			}\
			objState = dbData->cardOperationalState;\
			free(dbData);\
			if (objState != CARDSTATE_DIAGNOSTIC)\
			{\
				result = CM_ERR_INCORRECT_OBJ_STATE;\
			}\
			else\
			{\
				CHECK_SLOT_TRUNKPORT_STATE(EicDiagTableApi, result, objState, dataPtr);\
				CHECK_SLOT_DSP_STATE(EicDiagTableApi, result, objState, dataPtr);\
			}\
}

#define CHECK_TRUNKPORT_PRESENT_STATE(diagTableName, result, objState, dataPtr)\
{\
		TrunkPortTableIndices indx1;\
		TrunkPortTableApi *dbData1;\
		indx1.chasisFrameId = ((diagTableName *)dataPtr)->chasisFrameId;\
		indx1.slotId = ((diagTableName *)dataPtr)->slotId;\
		indx1.trunkPortId = ((diagTableName *)dataPtr)->trunkPortId;\
		dbResult = getTrunkPortTable(&indx1, &dbData1);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		objState = dbData1->physicalTrunkPortState;\
		free(dbData1);\
}

#define CHECK_TRUNKPORT_ADMIN_STATE(diagTableName, result, objState, dataPtr)\
{\
		TrunkTableIndices indx1;\
		TrunkTableApi *dbData1;\
    TrunkPortTableIndices indx2;\
    TrunkPortTableApi *dbData2;\
    indx2.chasisFrameId = ((diagTableName *)dataPtr)->chasisFrameId;\
    indx2.slotId = ((diagTableName *)dataPtr)->slotId;\
    indx2.trunkPortId = ((diagTableName *)dataPtr)->trunkPortId;\
    dbResult = getTrunkPortTable(&indx2, &dbData2);\
    if(dbResult != DB_SUCCESS)\
    {\
      result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
      return result;\
    }\
    objState = dbData2->physicalTrunkPortState;\
    free(dbData2);\
    if(objState != ACTIVATED)\
    {\
      result = CM_ERR_INCORRECT_OBJ_STATE;\
    }\
		indx1.e1Num = ((diagTableName *)dataPtr)->trunkPortId;\
		dbResult = getTrunkTable(&indx1, &dbData1);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		objState = dbData1->adminState;\
		free(dbData1);\
		if(objState != LOCKED)\
		{\
			result = CM_ERR_INCORRECT_OBJ_STATE;\
		}\
}

#define CHECK_DSP_ADMIN_STATE(result, objState, dataPtr, cardTypeTmp)\
{\
			DspStatusTableApi *dbData;\
			DspInfoTableApi *dbDataT;\
			DspInfoTableIndices indx;\
			I_U32 outRows = 0;\
			I_U16 outSize = 0;\
			I_U16 i = 0;\
			if(cardTypeTmp == DIAGNOS_TCT_ICC_DSP)\
			{\
					dbResult = getallDspStatusTable(&dbData, &outRows, &outSize);\
					if(dbResult != DB_SUCCESS)\
					{\
						result = CM_ERR_DSP_ID_NOT_PRESENT_IN_DB;\
						return result;\
					}\
					for(i = 0; i < outRows; i++)\
					{\
							if( (((IccDiagTableApi *)dataPtr)->chasisFrameId == dbData[i].chasisFrameId) &&\
									(((IccDiagTableApi *)dataPtr)->slotId == dbData[i].slotId) &&\
									( dbData[i].physicalPresenceState == PRESENT))\
							{\
									indx.chasisFrameId = dbData[i].chasisFrameId;\
									indx.slotId = dbData[i].slotId;\
									indx.dspId = dbData[i].dspId;\
									dbResult = getDspInfoTable(&indx, &dbDataT);\
									if(dbResult != DB_SUCCESS)\
									{\
										result = CM_ERR_DSP_ID_NOT_PRESENT_IN_DB;\
										free(dbData);\
										return result;\
									}\
									objState = dbDataT->adminState;\
									free(dbDataT);\
									if(objState != LOCKED)\
									{\
										result = CM_ERR_DSP_UNLOCKED;\
										free(dbData);\
										return result;\
									}\
							}\
					}\
					free(dbData);\
			}\
			if(cardTypeTmp == DIAGNOS_TCT_EIC_DSP)\
			{\
					indx.chasisFrameId = ((EicDiagTableApi *)dataPtr)->chasisFrameId;\
					indx.slotId = ((EicDiagTableApi *)dataPtr)->slotId;\
					indx.dspId = ((EicDiagTableApi *)dataPtr)->dspId;\
					dbResult = getDspInfoTable(&indx, &dbDataT);\
					if(dbResult != DB_SUCCESS)\
					{\
						result = CM_ERR_DSP_ID_NOT_PRESENT_IN_DB;\
						return result;\
					}\
					objState = dbDataT->adminState;\
					free(dbDataT);\
					if(objState != LOCKED)\
					{\
						result = CM_ERR_DSP_UNLOCKED;\
						return result;\
					}\
			}\
}\

#define CHECK_DSP_PRESENT_STATE(diagTableName, result, objState, dataPtr)\
{\
			DspStatusTableApi *dbData;\
			I_U32 outRows = 0;\
			I_U16 outSize = 0;\
			I_U16 i = 0;\
			dbResult = getallDspStatusTable(&dbData, &outRows, &outSize);\
			if(dbResult != DB_SUCCESS)\
			{\
				result = CM_ERR_DSP_ID_NOT_PRESENT_IN_DB;\
				return result;\
			}\
			for(i = 0; i < outRows; i++)\
			{\
					DspStatusTableApi *dbDataT;\
          DspInfoTableIndices indx;\
					if( (((diagTableName *)dataPtr)->chasisFrameId == dbData[i].chasisFrameId) &&\
					    (((diagTableName *)dataPtr)->slotId == dbData[i].slotId) &&\
					    ( dbData[i].physicalPresenceState == PRESENT))\
					{\
							indx.chasisFrameId = dbData[i].chasisFrameId;\
							indx.slotId = dbData[i].slotId;\
							indx.dspId = dbData[i].dspId;\
							dbResult = getDspInfoTable(&indx, &dbDataT);\
							if(dbResult != DB_SUCCESS)\
							{\
								result = CM_ERR_DSP_ID_NOT_PRESENT_IN_DB;\
								free(dbData);\
								return result;\
							}\
							free(dbDataT);\
					}\
			}\
			free(dbData);\
}\

#define VALIDATE_CH_TYPE(dataPtr)\
{\
		switch(((IccDiagTableApi *)dataPtr)->chanType)\
		{\
			case CHAN_TYPE_MTP2:\
			{\
				if ((((IccDiagTableApi *)dataPtr)->channel != CT_MTP2_VAL_1)&&\
				    (((IccDiagTableApi *)dataPtr)->channel != CT_MTP2_VAL_2)&&\
				    (((IccDiagTableApi *)dataPtr)->channel != CT_MTP2_VAL_3)&&\
				    (((IccDiagTableApi *)dataPtr)->channel != CT_MTP2_VAL_4))\
				{	\
					result = CM_ERR_PARAM_OUT_OF_RANGE;\
					return result;\
				}	\
				break;\
			}\
			case CHAN_TYPE_LAPD:\
			{	\
				if ((((IccDiagTableApi *)dataPtr)->channel < CT_LAPD_VAL_MIN)||\
						(((IccDiagTableApi *)dataPtr)->channel > CT_LAPD_VAL_MAX))\
				{	\
					result = CM_ERR_PARAM_OUT_OF_RANGE;\
					return result;\
				}	\
				break;\
			}\
			case CHAN_TYPE_MLPPP:\
			{	\
				if ((((IccDiagTableApi *)dataPtr)->channel < CT_MLPPP_VAL_MIN)||\
						(((IccDiagTableApi *)dataPtr)->channel > CT_MLPPP_VAL_MAX))\
				{	\
					result = CM_ERR_PARAM_OUT_OF_RANGE;\
					return result;\
				}	\
				break;\
			}\
			case CHAN_TYPE_FR:\
			{	\
				if ((((IccDiagTableApi *)dataPtr)->channel < CT_FR_VAL_MIN)||\
						(((IccDiagTableApi *)dataPtr)->channel > CT_FR_VAL_MAX))\
				{	\
					result = CM_ERR_PARAM_OUT_OF_RANGE;\
					return result;\
				}	\
				break;\
			}\
			default:\
			{\
				break;\
			}\
		}\
}

#define GET_DSP_ID_FROM_SLOT_ID_EIC(dataPtr)\
{\
	if(((EicDiagTableApi *)dataPtr)->slotId == EIC0_SLOTID)\
	{\
			((((EicDiagTableApi *)dataPtr)->dspId== EIC_DSP_ID_1) ? \
			 (((EicDiagTableApi *)dataPtr)->dspId = DSP_ID_2) : \
			 (((EicDiagTableApi *)dataPtr)->dspId = DSP_ID_3));	\
	}\
	if(((EicDiagTableApi *)dataPtr)->slotId == EIC1_SLOTID)\
	{\
			((((EicDiagTableApi *)dataPtr)->dspId== EIC_DSP_ID_2) ? \
			 (((EicDiagTableApi *)dataPtr)->dspId = DSP_ID_4) : \
			 (((EicDiagTableApi *)dataPtr)->dspId = DSP_ID_5));	\
	}\
}
/*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
#define VALIDATE_OBM_CARD_DATA(result, dataPtr)\
{\
		ObmCardInfoTableIndices indx;\
		ObmCardInfoTableApi *dbData;\
		indx.chasisFrameId = ((ObmDiagTableApi *)dataPtr)->chassisFrameID;\
		indx.slotID = ((ObmDiagTableApi *)dataPtr)->slotID;\
		dbResult = getObmCardInfoTable(&indx, &dbData);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		free(dbData);\
}
#define VALIDATE_OBF_CARD_DATA(result, dataPtr)\
{\
		PowerSupplyTableIndices indx;\
		PowerSupplyTableApi *dbData;\
		indx.chasisFrameId = ((ObfDiagTableApi *)dataPtr)->chassisFrameID;\
		indx.slotID = ((ObfDiagTableApi *)dataPtr)->slotID;\
		dbResult = getPowerSupplyTable(&indx, &dbData);\
		if(dbResult != DB_SUCCESS)\
		{\
			result = CM_ERR_DIAGNOS_OBJ_NOT_PRESESNT;\
			return result;\
		}\
		free(dbData);\
}
/*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
/* ICC Diagnos */
I_U32 validateIccGenTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICCGen_All:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		case DIAGNOS_TCID_ICCGen_1:
		{
      //CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /* Removed from Validation Checks.*/
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		case DIAGNOS_TCID_ICCGen_2:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccGenTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccRamCpTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_RamCP_All:
		case DIAGNOS_TCID_ICC_RamCP_1:
		case DIAGNOS_TCID_ICC_RamCP_2:
		case DIAGNOS_TCID_ICC_RamCP_3:
		case DIAGNOS_TCID_ICC_RamCP_4:
		case DIAGNOS_TCID_ICC_RamCP_5:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccRamCpTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccEthernetCpTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_EthCP_1:
		{
			if(((IccDiagTableApi *)dataPtr)->ethPortId != ETH_PORT_VAL_ALL)
			{
					result = CM_ERR_PARAM_OUT_OF_RANGE;\
      }	
      else
      {
      	VALIDATE_ICC_CARD_DATA(result, dataPtr);
      }	
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccEthernetCpTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccFlashDiskCpTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_FlashDiskCP_All:
		case DIAGNOS_TCID_ICC_FlashDiskCP_1:
		case DIAGNOS_TCID_ICC_FlashDiskCP_2:
		case DIAGNOS_TCID_ICC_FlashDiskCP_3:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccFlashDiskCpTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccCpldTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_CPLDICC_All:
		case DIAGNOS_TCID_ICC_CPLDICC_1:
		case DIAGNOS_TCID_ICC_CPLDICC_2:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccCpldTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}
I_U32 validateIccFramerTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_FramerICC_All:
		{
			LOG_PRINT(DEBUG, "validateIccFramerTc : Received TC ID  %d, Not Supported Reject It", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
      
      //CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		case DIAGNOS_TCID_ICC_FramerICC_1: /* Raj: Why Trunk present/lock status not needed */
		case DIAGNOS_TCID_ICC_FramerICC_2: /* Raj: Why Trunk present/lock status not needed */
		{
      CHECK_TRUNKPORT_PRESENT_STATE(IccDiagTableApi, result, objState, dataPtr) /*Raj : Can add this macro. */
			return result;
		}
		case DIAGNOS_TCID_ICC_FramerICC_3:
		case DIAGNOS_TCID_ICC_FramerICC_4:
		case DIAGNOS_TCID_ICC_FramerICC_5:
		{
					if((((IccDiagTableApi *)dataPtr)->rep > ONE))
					{
						LOG_PRINT(DEBUG, "validateIccFramerTc : Rep should not be >1 for TC _3 _4 _5");
						result = CM_ERR_PARAM_OUT_OF_RANGE;
						return result;
					}
					else
					{
						CHECK_TRUNKPORT_ADMIN_STATE(IccDiagTableApi, result, objState, dataPtr);
					}

					return result;	
		}
		case DIAGNOS_TCID_ICC_FramerICC_6:
		{
			LOG_PRINT(DEBUG, "validateIccFramerTc : Received TC ID  %d, Not Supported Reject It", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;

      //CHECK_TRUNKPORT_ADMIN_STATE(IccDiagTableApi, result, objState, dataPtr);

      return;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccFramerTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccEthernetPpTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_EthPP_All:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);

			return result;	
		}
		case DIAGNOS_TCID_ICC_EthPP_1:
		{

			if(((IccDiagTableApi *)dataPtr)->ethPortId != ETH_PORT_VAL_ALL)
			{
					result = CM_ERR_PARAM_OUT_OF_RANGE;\
			}	
			else
			{
				VALIDATE_ICC_CARD_DATA(result, dataPtr);
			}	

			return result;	
		}
		case DIAGNOS_TCID_ICC_EthPP_2:
		{
				if(((IccDiagTableApi *)dataPtr)->ethPortId == ETH_PORT_VAL_CP_CP)
				{
					LOG_PRINT(DEBUG, "validateIccEthernetPpTc : Invalid Eth Port CP_CP for TC ID  %d", diagnosTcId);
					result = CM_ERR_PARAM_OUT_OF_RANGE;
					return result;
				}
      	VALIDATE_ICC_CARD_DATA(result, dataPtr);

			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccEthernetPpTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccRamPpTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_RamPP_All:
		case DIAGNOS_TCID_ICC_RamPP_1:
		case DIAGNOS_TCID_ICC_RamPP_2:
		case DIAGNOS_TCID_ICC_RamPP_3:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		case DIAGNOS_TCID_ICC_RamPP_4:
		{
			if((((IccDiagTableApi *)dataPtr)->dataVal) <= 0xFFFF)
			{
      	VALIDATE_ICC_CARD_DATA(result, dataPtr);
      }
      else
      {
				LOG_PRINT(DEBUG, "validateIccRamPpTc : Received dataValue > 16 bits");
      	result = CM_ERR_PARAM_OUT_OF_RANGE;
      }
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccRamPpTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccFlashDiskPpTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_FlashDiskPP_All:
		case DIAGNOS_TCID_ICC_FlashDiskPP_1:
		case DIAGNOS_TCID_ICC_FlashDiskPP_2:
		case DIAGNOS_TCID_ICC_FlashDiskPP_3:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccFlashDiskPpTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccI2cBusTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	if(diagnosTcId == DIAGNOS_TCID_ICC_I2CBusICC_3)
	{
		if((((IccDiagTableApi *)dataPtr)->i2cReg < 0) || (((IccDiagTableApi *)dataPtr)->i2cReg > 34))
		{
				result = CM_ERR_PARAM_OUT_OF_RANGE;
				return result;
		}
	}
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_I2CBusICC_1:
		case DIAGNOS_TCID_ICC_I2CBusICC_2:
		case DIAGNOS_TCID_ICC_I2CBusICC_3:
		case DIAGNOS_TCID_ICC_I2CBusICC_4:
		case DIAGNOS_TCID_ICC_I2CBusICC_7:
		case DIAGNOS_TCID_ICC_I2CBusICC_8:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;
		}
		case DIAGNOS_TCID_ICC_I2CBusICC_All:
		case DIAGNOS_TCID_ICC_I2CBusICC_5:
		case DIAGNOS_TCID_ICC_I2CBusICC_6:
		{
      CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccI2cBusTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccDspTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_DSP_1:
		case DIAGNOS_TCID_ICC_DSP_2:
		case DIAGNOS_TCID_ICC_DSP_3:
		{
			CHECK_DSP_PRESENT_STATE(IccDiagTableApi, result, objState, dataPtr);
			return result;
		}
		case DIAGNOS_TCID_ICC_DSP_All:
		case DIAGNOS_TCID_ICC_DSP_4:
		{
					if((((IccDiagTableApi *)dataPtr)->rep > ONE))
					{
						LOG_PRINT(DEBUG, "validateIccDspTc : Rep should not be >1 for TC _all _4");
						result = CM_ERR_PARAM_OUT_OF_RANGE;
						return result;
					}
					else
					{
      			CHECK_DSP_ADMIN_STATE(result, objState, dataPtr, DIAGNOS_TCT_ICC_DSP);
					}

			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccDspTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccMccTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	if(diagnosTcId != DIAGNOS_TCID_ICC_MCC_2)
	{
		VALIDATE_CH_TYPE(dataPtr);
	}	

	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_MCC_All:
		case DIAGNOS_TCID_ICC_MCC_1:
		{
			LOG_PRINT(DEBUG, "validateIccFramerTc : Received TC ID  %d, Not Supported Reject It", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;

      //VALIDATE_ICC_CARD_DATA(result, dataPtr);
      
			return;
		}
		case DIAGNOS_TCID_ICC_MCC_2:
		case DIAGNOS_TCID_ICC_MCC_3:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccMccTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateIccTsiTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((IccDiagTableApi *)dataPtr)->iccTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_ICC_TSI_1:
		{
      VALIDATE_ICC_CARD_DATA(result, dataPtr);
			return result;
		}
		case DIAGNOS_TCID_ICC_TSI_All:
		{
      CHECK_ICC_CARD_ACTIVE_STATE(result, objState, dataPtr,diagnosTcId);
      //CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		case DIAGNOS_TCID_ICC_TSI_2:
		{
			if((((IccDiagTableApi *)dataPtr)->streamId != STREAM_ID_ICC_DSP) ||
				 (((IccDiagTableApi *)dataPtr)->rep > ONE))
			{
					LOG_PRINT(DEBUG, "validateIccTsiTc : Invalid StreamId for TC ID  %d or REP", diagnosTcId);
			  	result = CM_ERR_PARAM_OUT_OF_RANGE;
					return result;
			}
      CHECK_DSP_ADMIN_STATE(result, objState, dataPtr, DIAGNOS_TCT_ICC_DSP);
      //CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		case DIAGNOS_TCID_ICC_TSI_3:
		{
			if((((IccDiagTableApi *)dataPtr)->streamId != STREAM_ID_ICC_PP) ||
			   (((IccDiagTableApi *)dataPtr)->rep > ONE))
			{
					LOG_PRINT(DEBUG, "validateIccTsiTc : Invalid StreamId for TC ID  %d or REP", diagnosTcId);
			  	result = CM_ERR_PARAM_OUT_OF_RANGE;
					return result;
			}
      //CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		case DIAGNOS_TCID_ICC_TSI_4:
		{
			if((((IccDiagTableApi *)dataPtr)->streamId != STREAM_ID_ICC_FRAMER) ||
			   (((IccDiagTableApi *)dataPtr)->rep > ONE))
			{
					LOG_PRINT(DEBUG, "validateIccTsiTc : Invalid StreamId for TC ID  %d or REP", diagnosTcId);
			  	result = CM_ERR_PARAM_OUT_OF_RANGE;
					return result;
			}
      CHECK_ICC_CARD_ACTIVE_STATE(result, objState, dataPt,diagnosTcIdr);
      //CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		case DIAGNOS_TCID_ICC_TSI_5:
		{
			if((((IccDiagTableApi *)dataPtr)->streamId != STREAM_ID_MATE_TSI) ||
			   (((IccDiagTableApi *)dataPtr)->rep > ONE))
			{
					LOG_PRINT(DEBUG, "validateIccTsiTc : Invalid StreamId for TC ID  %d or REP", diagnosTcId);
			  	result = CM_ERR_PARAM_OUT_OF_RANGE;
					return result;
			}
      //CHECK_ICC_CARD_DIAGNOSTIC_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateIccTsiTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

/* EIC Diagnos */
I_U32 validateEicFramerTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((EicDiagTableApi *)dataPtr)->eicTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_EIC_FRAMER_All:
		{
			LOG_PRINT(DEBUG, "validateIccFramerTc : Received TC ID  %d, Not Supported Reject It", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;
      
      //CHECK_EIC_CARD_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		case DIAGNOS_TCID_EIC_FRAMER_1:
		case DIAGNOS_TCID_EIC_FRAMER_2:
		{
			CHECK_TRUNKPORT_PRESENT_STATE(EicDiagTableApi, result, objState, dataPtr);
			return result;
		}
		case DIAGNOS_TCID_EIC_FRAMER_3:
		case DIAGNOS_TCID_EIC_FRAMER_4:
		case DIAGNOS_TCID_EIC_FRAMER_5:
		{
			if((((EicDiagTableApi *)dataPtr)->rep > ONE))
			{
				LOG_PRINT(DEBUG, "validateEicFramerTc : Rep should not be >1 for TC _3 _4 _5");
				result = CM_ERR_PARAM_OUT_OF_RANGE;
				return result;
			}
			else
			{
      	CHECK_TRUNKPORT_ADMIN_STATE(EicDiagTableApi, result, objState, dataPtr);
			}
      
			return result;	
		}
		case DIAGNOS_TCID_EIC_FRAMER_6:
		{
			LOG_PRINT(DEBUG, "validateEicFramerTc : Received TC ID  %d, Not Supported Reject It", diagnosTcId);
      result = CM_ERR_INVALID_ICC_DIAGNOS_TC_ID;

      //CHECK_TRUNKPORT_ADMIN_STATE(EicDiagTableApi, result, objState, dataPtr);
      
			return;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateEicFramerTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_EIC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateEicEthernetCpTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((EicDiagTableApi *)dataPtr)->eicTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_EIC_ETHCP_1:
		{
      VALIDATE_EIC_CARD_DATA(result, dataPtr);

			return result;	
		}
		case DIAGNOS_TCID_EIC_ETHCP_All:
		case DIAGNOS_TCID_EIC_ETHCP_2:
		case DIAGNOS_TCID_EIC_ETHCP_3:
		{
      CHECK_EIC_CARD_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateEicEthernetCpTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_EIC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateEicEthernetSwitch(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((EicDiagTableApi *)dataPtr)->eicTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_EIC_ETHSW_All:
		case DIAGNOS_TCID_EIC_ETHSW_1:
		case DIAGNOS_TCID_EIC_ETHSW_2:
		{
      CHECK_EIC_CARD_STATE(result, objState, dataPtr) /*Raj : Can add this macro. */

			return result;	
		}
		case DIAGNOS_TCID_EIC_ETHSW_3:
		{
      VALIDATE_EIC_CARD_DATA(result, dataPtr);
			return result;	
		}
		
		default:
		{
			LOG_PRINT(DEBUG, "validateEicEthernetSwitch : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_EIC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateEicDspTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((EicDiagTableApi *)dataPtr)->eicTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_EIC_DSP_1:
		case DIAGNOS_TCID_EIC_DSP_2:
		case DIAGNOS_TCID_EIC_DSP_3:
		{
			CHECK_DSP_PRESENT_STATE(EicDiagTableApi, result, objState, dataPtr);
			return result;
		}
		case DIAGNOS_TCID_EIC_DSP_All:
		case DIAGNOS_TCID_EIC_DSP_4:
		{
			if((((EicDiagTableApi *)dataPtr)->rep > ONE))
			{
				LOG_PRINT(DEBUG, "validateEicDspTc : Rep should not be >1 for TC _all _4");
				result = CM_ERR_PARAM_OUT_OF_RANGE;
				return result;
			}
			else
			{
      	CHECK_DSP_ADMIN_STATE(result, objState, dataPtr, DIAGNOS_TCT_EIC_DSP);
			}

			return result;	
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateEicDspTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_EIC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

I_U32 validateEicCpldTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((EicDiagTableApi *)dataPtr)->eicTestId;

	I_S32 dbResult = DB_SUCCESS;

	I_U32 objState = 0;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_EIC_CPLD_All:
		case DIAGNOS_TCID_EIC_CPLD_1:
		case DIAGNOS_TCID_EIC_CPLD_2:
		case DIAGNOS_TCID_EIC_CPLD_3:
		{
      VALIDATE_EIC_CARD_DATA(result, dataPtr);
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateEicCpldTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_EIC_DIAGNOS_TC_ID;
			return result;
		}
  }
}

/* PSU Diagnos */
I_U32 validatePsuTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((PwrSupDiagTableApi *)dataPtr)->psuTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_PSU_All:
		case DIAGNOS_TCID_PSU_1:
		case DIAGNOS_TCID_PSU_2:
		{
      VALIDATE_PSU_CARD_DATA(result, dataPtr);
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validatePsuTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_PSU_DIAGNOS_TC_ID;
			return result;
		}
  }
}

/* FAN TRAY Diagnos */
I_U32 validateFanTrayTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((FanTrayDiagTableApi *)dataPtr)->fanTrayTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_FANTRAY_All:
		case DIAGNOS_TCID_FANTRAY_1:
		case DIAGNOS_TCID_FANTRAY_2:
		{
      VALIDATE_FANTRAY_CARD_DATA(result, dataPtr);
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateFanTrayTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_FANTRAY_DIAGNOS_TC_ID;
			return result;
		}
  }
}
/*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
I_U32 validateObmGenTc(I_PVoid dataPtr)
{
  LOG_PRINT(DEBUG,"Entering validateObmGenTc");  
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((ObmDiagTableApi *)dataPtr)->obmTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_OBMGen_All:
		case DIAGNOS_TCID_OBMGen_1:
		case DIAGNOS_TCID_OBMGen_2:
		{
      VALIDATE_OBM_CARD_DATA(result, dataPtr); 
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateObmGenTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_OBM_DIAGNOS_TC_ID; 
			return result;
		}
  }
}
I_U32 validateObmRamTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((ObmDiagTableApi *)dataPtr)->obmTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_OBM_Ram_All:
		case DIAGNOS_TCID_OBM_Ram_1:
		case DIAGNOS_TCID_OBM_Ram_2:
		case DIAGNOS_TCID_OBM_Ram_3:
		case DIAGNOS_TCID_OBM_Ram_4:
		{
      VALIDATE_OBM_CARD_DATA(result, dataPtr); 
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateObmRamTc: Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_OBM_DIAGNOS_TC_ID; 
			return result;
		}
  }
}
I_U32 validateObmEthTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((ObmDiagTableApi *)dataPtr)->obmTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_OBM_Eth_1:
		{
      VALIDATE_OBM_CARD_DATA(result, dataPtr); 
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateObmEthTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_OBM_DIAGNOS_TC_ID; 
			return result;
		}
  }
}
I_U32 validateObmFlashDiskTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((ObmDiagTableApi *)dataPtr)->obmTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_OBM_FlashDisk_All:
		case DIAGNOS_TCID_OBM_FlashDisk_1:
		case DIAGNOS_TCID_OBM_FlashDisk_2:
		case DIAGNOS_TCID_OBM_FlashDisk_3:
		{
      VALIDATE_OBM_CARD_DATA(result, dataPtr); 
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateObmFlashDiskTc : Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_OBM_DIAGNOS_TC_ID; 
			return result;
		}
  }
}
I_U32 validateObmFanTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((ObmDiagTableApi *)dataPtr)->obmTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_OBM_Fan_All:
		case DIAGNOS_TCID_OBM_Fan_1:
		case DIAGNOS_TCID_OBM_Fan_2:
		{
      LOG_PRINT(DEBUG,"Entering Validation for DIAGNOS_TCT_OBM_FAN");
      VALIDATE_OBM_CARD_DATA(result, dataPtr); 
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateObmFanTc: Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_OBM_DIAGNOS_TC_ID; 
			return result;
		}
  }
}
I_U32 validateObfTc(I_PVoid dataPtr)
{
	I_U32 result = CM_SUCCESS;

	I_U16 diagnosTcId = ((ObfDiagTableApi *)dataPtr)->obfTestId;

	I_S32 dbResult = DB_SUCCESS;
	
	switch (diagnosTcId)
	{
		case DIAGNOS_TCID_OBF_All:
		case DIAGNOS_TCID_OBF_1:
		case DIAGNOS_TCID_OBF_2:
		{
      VALIDATE_OBF_CARD_DATA(result, dataPtr); 
			return result;
		}
		default:
		{
			LOG_PRINT(DEBUG, "validateObfTc: Received Invalid TC ID  %d", diagnosTcId);
      result = CM_ERR_INVALID_OBF_DIAGNOS_TC_ID; 
			return result;
		}
  }
}
/*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
/* Start: Diagnostics Validation Functions. */
I_U32 validateDiagnosTcData(I_PVoid dataPtr, I_U32 diagApi)
{
	I_U32 result = CM_SUCCESS;
	I_U16 diagnosTcType = 0;
	I_U16 action = 0;
	I_U16 testReference = 0;

	switch(diagApi)
	{
		case BSC_API_SET_ICCDIAGTABLE:
		{
			diagnosTcType = ((IccDiagTableApi *)dataPtr)->iccTestType;
			action = ((IccDiagTableApi *)dataPtr)->action;
			testReference = ((IccDiagTableApi *)dataPtr)->testReference;
			switch(diagnosTcType)
			{
					case DIAGNOS_TCT_ICC_GEN:
					case DIAGNOS_TCT_ICC_RAM_CP:
					case DIAGNOS_TCT_ICC_ETHERNET_CP:
					case DIAGNOS_TCT_ICC_FLASHDISK_CP:
					case DIAGNOS_TCT_ICC_CPLD:
					case DIAGNOS_TCT_ICC_FRAMER:
					case DIAGNOS_TCT_ICC_ETHERNET_PP:
					case DIAGNOS_TCT_ICC_RAM_PP:
					case DIAGNOS_TCT_ICC_FLASHDISK_PP:
					case DIAGNOS_TCT_ICC_I2C_BUS:
					case DIAGNOS_TCT_ICC_DSP:
					case DIAGNOS_TCT_ICC_MCC:
					case DIAGNOS_TCT_ICC_TSI:
					{
						if((((IccDiagTableApi *)dataPtr)->iccTestId == DIAGNOS_TCID_All) && 
							 (((IccDiagTableApi *)dataPtr)->rep > ONE))
						{
							result = CM_ERR_PARAM_OUT_OF_RANGE;
							return result;
						}
						break;
					}
					default:
					{
     				result = CM_ERR_INVALID_DIAGNOS_TCT;
     				return result;
					}
			}	
			break;
		}
		case BSC_API_SET_EICDIAGTABLE:
		{
			diagnosTcType = ((EicDiagTableApi *)dataPtr)->eicTestType;
			action = ((EicDiagTableApi *)dataPtr)->action;
			testReference = ((EicDiagTableApi *)dataPtr)->testReference;
			switch(diagnosTcType)
			{
					case DIAGNOS_TCT_EIC_FRAMER:
					case DIAGNOS_TCT_EIC_ETHERNET_CP:
					case DIAGNOS_TCT_EIC_ETHERNET_SWITCH:
					case DIAGNOS_TCT_EIC_DSP:
					case DIAGNOS_TCT_EIC_CPLD:
					{
						if((((EicDiagTableApi *)dataPtr)->eicTestId == DIAGNOS_TCID_All) && 
							 (((EicDiagTableApi *)dataPtr)->rep > ONE))
						{
							result = CM_ERR_PARAM_OUT_OF_RANGE;
							return result;
						}
						break;
					}
					default:
					{
     				result = CM_ERR_INVALID_DIAGNOS_TCT;
     				return result;
					}
			}	
			break;
		}
		case BSC_API_SET_PWRSUPDIAGTABLE:
		{
			diagnosTcType = ((PwrSupDiagTableApi *)dataPtr)->psuTestType;
			action = ((PwrSupDiagTableApi *)dataPtr)->action;
			testReference = ((PwrSupDiagTableApi *)dataPtr)->testReference;
			switch(diagnosTcType)
			{
					case DIAGNOS_TCT_PSU:
					{
						if((((PwrSupDiagTableApi *)dataPtr)->psuTestId == DIAGNOS_TCID_All) && 
							 (((PwrSupDiagTableApi *)dataPtr)->rep > ONE))
						{
							result = CM_ERR_PARAM_OUT_OF_RANGE;
							return result;
						}
						break;
					}
					default:
					{
     				result = CM_ERR_INVALID_DIAGNOS_TCT;
     				return result;
					}
			}	
			break;
		}
		case BSC_API_SET_FANTRAYDIAGTABLE:
		{
			diagnosTcType = ((FanTrayDiagTableApi *)dataPtr)->fanTrayTestType;
			action = ((FanTrayDiagTableApi *)dataPtr)->action;
			testReference = ((FanTrayDiagTableApi *)dataPtr)->testReference;
			switch(diagnosTcType)
			{
					case DIAGNOS_TCT_FAN_TRAY:
					{
						if((((FanTrayDiagTableApi *)dataPtr)->fanTrayTestId == DIAGNOS_TCID_All) && 
							 (((FanTrayDiagTableApi *)dataPtr)->rep > ONE))
						{
							result = CM_ERR_PARAM_OUT_OF_RANGE;
							return result;
						}
						break;
					}
					default:
					{
     				result = CM_ERR_INVALID_DIAGNOS_TCT;
     				return result;
					}
			}	
			break;
		}
    /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
    case BSC_API_SET_OBMDIAGTABLE:
    {
			diagnosTcType = ((ObmDiagTableApi *)dataPtr)->obmTestType;
			action = ((ObmDiagTableApi *)dataPtr)->action;
			testReference = ((ObmDiagTableApi *)dataPtr)->testReference;
			switch(diagnosTcType)
			{
				case DIAGNOS_TCT_OBM_GEN:
				case DIAGNOS_TCT_OBM_RAM:
				case DIAGNOS_TCT_OBM_ETHERNET:
				case DIAGNOS_TCT_OBM_FLASHDISK:
				case DIAGNOS_TCT_OBM_FAN:
				{
					if((((ObmDiagTableApi *)dataPtr)->obmTestId == DIAGNOS_TCID_All) && 
					 (((ObmDiagTableApi *)dataPtr)->rep > ONE))
					{
						result = CM_ERR_PARAM_OUT_OF_RANGE;
            LOG_PRINT(DEBUG,"validateDiagnosTcData failed... BSC_API_SET_OBMDIAGTABLE: result:%d", result);  
						return result;
					}
					break;
				}
			  default:
			  {
    		 result = CM_ERR_INVALID_DIAGNOS_TCT;
         LOG_PRINT(DEBUG,"validateDiagnosTcData failed... BSC_API_SET_OBMDIAGTABLE:default case  result:%d", result);  
    		 return result;
			  }
      }
     break;
    }
    case BSC_API_SET_OBFDIAGTABLE:
    {
			diagnosTcType = ((ObfDiagTableApi *)dataPtr)->obfTestType;
			diagnosTcType = ((ObfDiagTableApi *)dataPtr)->obfTestType;
			action = ((ObfDiagTableApi *)dataPtr)->action;
			testReference = ((ObfDiagTableApi *)dataPtr)->testReference;
			switch(diagnosTcType)
      {
				case DIAGNOS_TCT_OBF:
				{
					if((((ObfDiagTableApi *)dataPtr)->obfTestId == DIAGNOS_TCID_All) && 
					 (((ObfDiagTableApi *)dataPtr)->rep > ONE))
					{
						result = CM_ERR_PARAM_OUT_OF_RANGE;
						return result;
					}
					break;
				}
			  default:
			  {
    		 result = CM_ERR_INVALID_DIAGNOS_TCT;
    		 return result;
			  }
      }
    break;
    }
    /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
		default:
    {  	
     	result = CM_ERR_INVALID_DIAGNOS_TCT;
      LOG_PRINT(DEBUG,"validateDiagnosTcData failed... Default case : result:%d", result);  
			return result;
		}	
	}

	/*Checking If any diagnos Test Case is pending*/
	I_PVoid dbDataPtr = NULL;
	I_S32 dbResult = 0;
	I_U32 outRows = 0;
	I_U16 outSize = 0;
	dbResult = getallDiagStatusTable(&dbDataPtr, &outRows, &outSize);
	if((dbResult == DB_SUCCESS) && (outRows > ZERO))
	{
		LOG_PRINT(DEBUG, "validateDiagnosticsDataFromOmc : action: %d, testRef rcvd %d, testRef db %d",\
		action, testReference,((DiagStatusTableApi *)(dbDataPtr))->testReference);
		if((action == DIAG_CMD_CANCEL) && (((DiagStatusTableApi *)(dbDataPtr))->testReference == testReference))
		{
			LOG_PRINT(DEBUG, "validateDiagnosticsDataFromOmc : Received DIAG_CMD_CANCEL for ref %d",testReference);
			return result;
		}
		result = CM_ERR_DIAGNOS_OPR_IN_PROGRESS;
		return result;
	}
  LOG_PRINT(DEBUG,"No entry found in DiagStatusTable continuing with diagnosTcType : %d",diagnosTcType);  

	switch (diagnosTcType)
	{
		/* ICC Diagnos */
		case DIAGNOS_TCT_ICC_GEN:
		{
		 	result = validateIccGenTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_RAM_CP:
		{
		 	result = validateIccRamCpTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_ETHERNET_CP:
		{
		 	result = validateIccEthernetCpTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_FLASHDISK_CP:
		{
		 	result = validateIccFlashDiskCpTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_CPLD:
		{
		 	result = validateIccCpldTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_FRAMER:
		{
		 	result = validateIccFramerTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_ETHERNET_PP:
		{
		 	result = validateIccEthernetPpTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_RAM_PP:
		{
		 	result = validateIccRamPpTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_FLASHDISK_PP:
		{
		 	result = validateIccFlashDiskPpTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_I2C_BUS:
		{
		 	result = validateIccI2cBusTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_DSP:
		{
		 	result = validateIccDspTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_MCC:
		{
		 	result = validateIccMccTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_ICC_TSI:
		{
		 	result = validateIccTsiTc(dataPtr);
			return result;	
		}
		/* EIC DIAG */
		case DIAGNOS_TCT_EIC_FRAMER:
		{
		 	result = validateEicFramerTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_EIC_ETHERNET_CP:
		{
		 	result = validateEicEthernetCpTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_EIC_ETHERNET_SWITCH:
		{
		 	result = validateEicEthernetSwitch(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_EIC_DSP:
		{
		 	//GET_DSP_ID_FROM_SLOT_ID_EIC(dataPtr);
		 	result = validateEicDspTc(dataPtr);
			return result;	
		}
		case DIAGNOS_TCT_EIC_CPLD:
		{
		 	result = validateEicCpldTc(dataPtr);
			return result;	
		}

		/* Power Supply */
		case DIAGNOS_TCT_PSU:
		{
		 	result = validatePsuTc(dataPtr);
			return result;	
		}

		/* Fan Tray */
		case DIAGNOS_TCT_FAN_TRAY:
		{
		 	result = validateFanTrayTc(dataPtr);
			return result;	
		}
    /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
		case DIAGNOS_TCT_OBM_GEN:
		{
		 	result = validateObmGenTc(dataPtr);
			return result;	
		}
    
		case DIAGNOS_TCT_OBM_RAM:
		{
		 	result = validateObmRamTc(dataPtr);
			return result;	
		}

		case DIAGNOS_TCT_OBM_ETHERNET:
		{
		 	result = validateObmEthTc(dataPtr);
			return result;	
		}

		case DIAGNOS_TCT_OBM_FLASHDISK:
		{
		 	result = validateObmFlashDiskTc(dataPtr);
			return result;	
		}

		case DIAGNOS_TCT_OBM_FAN:
		{
		 	result = validateObmFanTc(dataPtr);
			return result;	
		}

		case DIAGNOS_TCT_OBF:
		{
		 	result = validateObfTc(dataPtr);
			return result;	
		}
    /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/

		default:
		{
			LOG_PRINT(DEBUG, "validateDiagnosticsDataFromOmc : Received Invalid TC Type  %d", diagnosTcType);
      result = CM_ERR_INVALID_DIAGNOS_TCT;
			return result;
		}
	}	
}

