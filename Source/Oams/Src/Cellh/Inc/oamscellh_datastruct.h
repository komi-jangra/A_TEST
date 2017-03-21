/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamscellh_datastruct.h
 PURPOSE           :  Contains Cell Handler Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/
#ifndef __OAMSCELLH_DATASTRUCT_H
#define __OAMSCELLH_DATASTRUCT_H

typedef struct
{
   PtrxId          ptrxId;
   LtrxId          ltrxId;
   Tei             tei;
   CellId          cellId;
   I_U8            objType;
   Lac             lac;	
   OamsCellIndex   cellIndex;
   I_U32           reason;  
   I_Bool          cellBarStatus; 
   I_U32           e1[MAX_NUM_E1];
	 I_S32					 selfInst;
   I_U8            isCellExtended;
}OamsCellhContext;

typedef struct
{
   I_PU8    si1buff;
   I_PU8    si2buff;
   I_PU8    si2terbuff;
   I_PU8    si3buff;
   I_PU8    si4buff;
   I_PU8    si5buff;
   I_PU8    si5terbuff;
   I_PU8    si6buff;
   I_PU8    si13buff;
   I_PU8    si2quatbuff;
   I_U16    si1buffLen;     
   I_U16    si2buffLen;     
   I_U16    si2terbuffLen;     
   I_U16    si3buffLen;     
   I_U16    si4buffLen;     
   I_U16    si5buffLen;     
   I_U16    si5terbuffLen;     
   I_U16    si6buffLen;     
   I_U16    si13buffLen;     
   I_U16    si2quatbuffLen;     
}OamsSiContext;

/* CS4.0: HA changes Start */
I_Void activeInProgressStateHandler();
I_Void activeStateHandler();
I_Void findLclPidPtr ( I_U32 refId, I_U8 classId, I_U32 *lclPidPtr, I_U8 entId);
I_U32  getCountAllocatedInst ( I_U16 instCount );
/* CS4.0: HA changes End */

typedef struct
{
	I_U8 								siPrepFlag;			
	I_U8 								ind2ter;
	I_U8 								ind5ter;
	I_U8 								psEnable;
	I_U32 							lockingE1Cellh;
	I_U8 								isShutDownInProgress;
	I_U8 								ccchConf;
	I_U8								tsc;
	I_U16 							bcchArfcn;
	I_U8 								frToHrSwitchPerct;
	I_U8								pbcchTS;
	I_U8 								abisE1LockFlag;
	Tei             		tei;
	PtrxId							ptrxId;
	OamsCellIndex				cellIndex;
	I_U8            		maxNumTch;
}OamsCellhRepContext;


typedef struct
{
				
I_U32 cellId;
I_U16 lac;
I_U8 	data[50];			
}CellhSwitchOverContextTable;

typedef struct
{
I_PU8    measInfo;
I_U16    measInfoLen;     
}OamsMsInfoCtxt;

#endif /* __OAMSCELLH_DATASTRUCT_H */
