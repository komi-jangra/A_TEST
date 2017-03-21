#ifndef __SKSDB_EXTERN_H
#define __SKSDB_EXTERN_H 
/*se ts=2************************************File Header*****
File Name		:		skdb_include.h 
Purpose			:		hash defines used by Application and 
                     DBUTIL Library
Project			:		GSM
Subsystem		:	  SKS / DBUTIL	
Author			:		
CSCI id			:
Version			:		V0.1
*************************************************************/

/*******************************************Change History***
S.No.   Release        Patch        Author        Description
1.      Rel0.0         None         xxxxx         Creation
*************************************************************/

extern I_U32 *logLevelPtrG;
extern I_U8  consolePrintFlagG;
void  SksDbInit();
#ifdef MSC
I_S32  GetMapInitConfigData(mapInitConfig**, I_U8*);
I_S32  GetMapSecurityConfigData(OamScmMapSecurityConfig**, I_U8*);
I_S32  GetMapTimerConfigData(OamScmMapTimerConfig**, I_U8*);
I_S32  GetCssfTimerConfigData(OamScmCssfTimerConfig**, I_U8*);
I_S32  GetIsupInitConfigData(sIsupInitConfigTableApi**, I_U8*);
I_S32  GetIsupTimerConfigData(OamScmIsupTimerConfig**, I_U8*);
I_S32  GetInitConfigData(OamScmMscConfig*);
I_S32  GetSS7GttConfigData(OamScmSs7GttConfig**, I_U8*);
#endif

#ifdef BSC
I_S32  GetInitConfigData(OamScmSs7StackConfig*);
I_S32  GetLapdTsConfigData(OamScmLapdTSConfig**, I_U8*);
I_S32  GetLapdTeiConfigData(OamScmLapdTEIConfig**, I_U8*);
I_S32  GetLapdSapiConfigData(OamScmLapdSAPIConfig**, I_U8*);
I_S32  GetLapdTimerConfigData(OamScmLapdTimerConfig**, I_U8*);
#endif
I_S32  GetLinkConfigData(OamScmLinkConfig**, I_U8*);
I_S32  GetLinksetConfigData(OamScmLinkSetConfig**, I_U8*);
I_S32  GetMtp3TimerConfigData(OamScmMtp3TimerConfig**, I_U8*);
I_S32  GetSS7RouteConfigData(OamScmSs7RouteConfig**, I_U8*);
I_S32  GetSccpBehaviorConfigData(sSccpBehaviorConfigTableApi**, I_U8*);
I_S32  GetSccpTimerConfigData(OamScmSccpTimerConfig**, I_U8*);
I_S32  GetSksGenConfigData(sksGenConfig**, I_U8*);
I_S32  GetTrunkCicConfigData(OamScmTrunkCicConfig**, I_U8*);
I_S32 GetDstStreamTsConfigDataWithTrunkAndTimeslot( I_U8*, I_U8 , I_U8);
I_S32  GetBssapTimerConfigData(OamScmBssapTimerConfig **, I_U8*);
I_S32  GetInterfaceConfigData(OamScmInterfaceConfig**, I_U8*);
//I_S32  GetMtp2TimerConfigData(OamScmMtp2TimerConfig**, I_U8*);



#endif // __SKSDB_EXTERN_H 
