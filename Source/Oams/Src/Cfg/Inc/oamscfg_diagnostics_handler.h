/***********************************File Header ***************************
File Name        : oamscfg_diagnostics_handler.h
Purpose          : This file contains functions definitions for CFG
                   Diagnostics methods.  
Project          : BSC OAM
Subsystem        : Oams
Author           : Grvjn
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMSCFG_DIAGNOSTICS_HANDLER_H
#define __OAMSCFG_DIAGNOSTICS_HANDLER_H

#define DIAGNOS_TCID_All 		1

/* Added to check ChannelType Value for Icc Mcc*/
#define CHAN_TYPE_MTP2			1
#define CHAN_TYPE_LAPD			2
#define CHAN_TYPE_MLPPP			3
#define CHAN_TYPE_FR				4

/* Added to check Channel number Value for Icc Mcc*/
#define CT_MTP2_VAL_1				2
#define CT_MTP2_VAL_2		 		4
#define CT_MTP2_VAL_3		 	 	6
#define CT_MTP2_VAL_4		 	 	8

#define CT_LAPD_VAL_MIN			10
#define CT_LAPD_VAL_MAX			89

#define CT_MLPPP_VAL_MIN		90
#define CT_MLPPP_VAL_MAX		97

#define CT_FR_VAL_MIN		 		98
#define CT_FR_VAL_MAX		 		123

/* Added to check PP Ethernet Port Value for Icc Ethernet Pp*/
#define ETH_PORT_VAL_CP_CP		 	1
#define ETH_PORT_VAL_ALL  		 	6

/* Added to check ICC TSI Stream Id Value for Icc Tsi*/
#define STREAM_ID_ICC_DSP		 		1
#define STREAM_ID_ICC_PP		 		2
#define STREAM_ID_ICC_FRAMER		3
#define STREAM_ID_MATE_TSI		 	4

/* Added to update DSP Id Value for Eic*/
#define EIC_DSP_ID_1		 	1
#define EIC_DSP_ID_2		 	1
#define DSP_ID_0		 	0
#define DSP_ID_1		 	1
#define DSP_ID_2		 	2
#define DSP_ID_3		 	3
#define DSP_ID_4		 	4
#define DSP_ID_5		 	5

#define FILLOBJTYPE(objType,apiId)\
{\
  switch(apiId)\
  {\
     case BSC_API_SET_ICCDIAGTABLE:\
       objType = OAMS_OBJTYPE_ICC;\
     break;\
     case BSC_API_SET_EICDIAGTABLE:\
       objType = OAMS_OBJTYPE_EIC;\
     break;\
     case BSC_API_SET_PWRSUPDIAGTABLE:\
       objType = OAMS_OBJTYPE_PSU;\
     break;\
     case BSC_API_SET_FANTRAYDIAGTABLE:\
       objType = OAMS_OBJTYPE_FANTRAY;\
     break;\
     case BSC_API_SET_OBMDIAGTABLE:\
       objType = OAMS_OBJTYPE_OBM;\
     break;\
     case BSC_API_SET_OBFDIAGTABLE:\
       objType = OAMS_OBJTYPE_OBF;\
     break;\
     default:\
         LOG_PRINT(MAJOR,"Wrong ApiId:%d",apiId) ;\
     break;\
  }\
}
typedef enum DiagCmdState
{
  runInProgress,
  cancelInProgress,
  abortInProgress,
  completed,
  aborted,
  cancelled,
}DiagCmdState;

typedef union RcvdDiagApi
{
  IccDiagTableApi     iccDiagApi;
  EicDiagTableApi     eicDiagApi;
  PwrSupDiagTableApi  pwrSupDiagApi;
  FanTrayDiagTableApi fantrayDiagApi;
  /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
  ObmDiagTableApi     obmDiagApi;
  ObfDiagTableApi     obfDiagApi;
  /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
}RcvdDiagApi;

typedef struct DiagDataStruct
{
   I_U32        apiId;
   I_U32        bpmRespTimer;
   I_U16        repetition;
   DiagCmdState diagCmdState; 
   RcvdDiagApi  rcvdDiagApi;
}DiagDataStruct; 

void setDiagnosticsHandler();
I_S32 sendDiagnosticsReqToBpm(I_U16 action);
I_S32 sendFtpReqToPdd(sDiagnosticTestResult * respPtr);
void bpmDiagnosticsRespHandler();
I_Void sendDiagAlarmToOmcAndDeleteDiagStsTbl();
I_Void pddMsgHandler();
void startDiagBpmRespTimer();
void startDiagIntervalTimer();
I_Void abortDiagnostics(I_U32 testResult);
I_Void cfgCleanupDiagnosticStsTable();
I_U32 * gCfgRepCnt;

#endif /*__OAMSCFG_DIAGNOSTICS_HANDLER_H */
