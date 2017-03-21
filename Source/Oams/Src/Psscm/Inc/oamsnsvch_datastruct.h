/********************************************************** File Header **
 FILE NAME         :  oamsnsvch_datasruct.h
 PURPOSE           :  Contains nsvch Data struct
 PROJECT           :  BSC
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSNSVCH_DATASTRUCT_H
#define __OAMSNSVCH_DATASTRUCT_H

typedef struct
{
   I_U16			nsvci;
   I_U16			nsei;
   I_U16			frChannel;
   I_U16			dlci;
   I_U16			mccStartStrmTs;
   I_U8				numStrmTs;
   I_U16			connId;
}OamsNsvchContext;


typedef struct
{
   I_U16			gbIfIndex;
   I_U16			nsei;
   I_U16      finalState; 
   I_U16			transportType;
   I_U16			maxNsvcOverIp;
   I_U16			numOfNsvcEnabled;
   I_U32      refId;
   I_U8				ongoingAction;
}PsscmRedCtxt;


typedef struct
{
   I_U16			nsvci;
   I_U16			frChannel;
   I_U16			nsei;
   I_U16			dlci;
   I_U16			mccStartStrmTs;
   I_U8				numStrmTs;
   I_U16			connId;
   I_U16      finalState; 
   I_U8       nStopCompleted;
   I_U8       onGoingAction;   
   I_U8       nsvcDisableCause; 
   I_U8       frStatus; 
}NsvcRedCtxt;
#endif   /* __OAMSNSVCH_DATASTRUCT_H  */ 
