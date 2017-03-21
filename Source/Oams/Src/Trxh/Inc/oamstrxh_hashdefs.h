/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamstrxh_hashdefs.h
 PURPOSE           :  Contains Trxh Hashdefs
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSTRXH_HASHDEFS_H
#define __OAMSTRXH_HASHDEFS_H


#define  RADIO_CLOCK_ID    		     0
#define  PTRX_ENABLE           		     2
#define  PTRX_DISABLE          		     1

#define  CHAN_COMBINATION_TCH_FULL           0
#define  CHAN_COMBINATION_TCH_HALF           1
#define  CHAN_COMBINATION_TCH_DUAL           0x0D

#define  CHAN_COMBINATION_BCCH_COMBINED      5
#define  CHAN_COMBINATION_SDCCH              3
#define  CHAN_COMBINATION_BCCH_MAIN          4
#define  CHAN_COMBINATION_BCH                6
//#define  CHAN_COMBINATION_PDCH             9
#define  CHAN_COMBINATION_DUAL               9

/* R2.4 Changes : Starts */
#define  CHAN_COMBINATION_BCCH_CBCH_SDCCH4   7
#define  CHAN_COMBINATION_SDCCH8_CBCH        8
/* R2.4 Changes : Ends */

#define  MAP_ALLOWED_YES        	     1
#define  MAP_ALLOWED_NO                      0

#define  MAX_CHAN_IN_PTRX                    8
#define  TRXH_HANDLER_TDM           		     1
#define  TRXH_HANDLER_IP       	      	     2
#define  MAX_TRXHM_INST    		     18

#define  NY1_TCH                             2
#define  NY1_SDCCH                           2
#define  T3105_TCH                           0xF0
#define  T3105_SDCCH                         0x64
#define  TRX_GPRS                            0x00
#define  TRX_GPRS_EDGE                       0x01
//#define  TRX_OBJ_CLASS                       0x01
//#define  OBJ_CLASS_TS                        0x03
#define  DELTA_TIME                          1000


#define  TRXH_SUCCESS                        1
#define  TRXH_FAILURE                        0

/*************Return values from configTRX **************/
#define  GOTO_STATE_UNLOCKED_DISABLED              0
#define  GOTO_STATE_WAIT_FOR_RADIO_LINK_TIME_OUT   1
#define  GOTO_STATE_LOCKED_DISABLED                2

#define  DELETE_RECVD_IND                          1
#define  LOCK_RECVD_IND                            2
#define  BIC_LOCK_RECVD_IND                        3

#define  OBJ_INSTANCE_BTS_NUM                   0x01
#define  UNKNOWN_CAUSE                          0x00


#define  INFRAME_TRX                               1
#define  BIC_TRX                                   2

//#define LAPD_LINK_DOWN                             0
//#define LAPD_LINK_UP                               1
/*Mantis #: 0007309 (If RSL Link is lost with a TRX then OML link should also be released).*/
#define SEND_DISC_REQ			1
#define UPDATE_DB			2
#define DISCARD_DISC_REQ		3
#define  GOTO_STATE_WAIT_FOR_CRE_CHAN_ACK GOTO_STATE_WAIT_FOR_RADIO_LINK_TIME_OUT  

/* R1.1 changes Start */
/* Probable Cause */
#define CP_TRACE_FAULT_PC		          2
#define DSP_TRACE_FAULT_PC              30
#define A_BIS_OML_FAULT_PC              20 
/*#define A_BIS_L3_OML_FAULT_PC           23*/
#define A_BIS_RSL_FAULT_PC              21
/*#define A_BIS_L3_RSL_FAULT_PC           22*/
#define DSP_CP_COMM_FAULT_PC            31
/*
#define RX_TEMP_HIGH_PC                 40
#define RX_TEMP_LOW_PC                  41
#define TX_TEMP_HIGH_PC                 42
#define TX_TEMP_LOW_PC                  43
#define PA_TEMP_HIGH_PC                 44
*/

#define FMPC_DSP_SW_FAULT_PC            50
#define FMPC_DSP_HW_FAULT_PC            51
#define FMPC_DSP_CLOCKOFFSET_PC         52

/* Event Type */
#define FM_COMMUNICATION_FAILURE        0
#define FM_QUALITY_OF_SERVICE_FAILURE   1
#define FM_PROCESSING_FAILURE           2
#define FM_EQUIPMENT_FAILURE            3
#define FM_ENVIORNMENT_FAILURE          4

/* Severity Type */
#define FM_ABIS_OK                      0
//#define NEW_TRAP_SEVERITY_WARNING       4

/* R1.1 changes End */

/* BSC R2.0 (High Capacity BSC) Starts*/
#define MAX_CORE_PER_DSP	0x04

#define PENDING_TRAU_MAP_STATUS_YES     0x01
#define PENDING_TRAU_MAP_STATUS_UN_MAPPABLE     0x02
#define PENDING_TRAU_MAP_STATUS_NO      0x00
#define PENDING_TRAU_MAP_STATUS_INPROGRESS      0x03
#define PENDING_TRAU_MAP_STATUS_DEFAULT			    0x04
#define MSG_SUCCESS		1
//#define PENDING                 1

/* BSC R2.0 (High Capacity BSC) Starts*/

/* STATE_CHANGE_EVENT_REPORT */
#define NOTCONFIGURED                  10
#define CONFIGURED                      9
#define FAILED                          1
#define RUNNING                         8

/*
Start:
   Changes for Probable cause for R2 BSC & BTS
   Dated:   12-OCT-2010
*/

/* these are the probable cause values which do not match wth R2-IP*/
#define  FM_DSP_PC                     0xE1
#define  FM_CP_PC                      0xE2
#define  PC_DSP_SW_ASSERT              0xE3
#define  FM_CP_WATCHDOG_PC             0xE4
#define  FM_SR_WATCHDOG_PC             0xE5
#define  RX_TEMP_HIGH_PC               0xE6
#define  TX_TEMP_HIGH_PC               0xE7
#define  RX_TEMP_LOW_PC                0xE8
#define  TX_TEMP_LOW_PC                0xE9
#define  FM_TRX_PC                     0xEA
#define  RM_HW_PC                      0xEB
#define  FM_TRX_PC                     0xEC
#define  TX_SUPERVISION_PC             0xD5
#define  TRX_TX_SYNTH_SUPERVISION_PC   0xD7
#define  TX_SWR_FAULT_PC               0x80
#define  TB_SUPERVISION_PC             0xC2
/* these are the probable cause values which do not match wth R2-IP ends here */

/*R2.9  FUS R2IP AlarmSynch  starts */
/* synched the probable cuase values with FUS */
#define CP_SW_FATAL_PC                           0x10 
#define DSP_1_SW_FATAL_PC                        0x11  
#define DSP_2_SW_FATAL_PC                        0x12 
#define DSP_3_SW_FATAL_PC                        0x13 
#define DSP_4_SW_FATAL_PC                        0x14 

//overload
#define CP_OVERLOAD_PC                          0x30     
#define DSP_1_OVERLOAD_PC                      0x31  
#define DSP_2_OVERLOAD_PC                      0x32
#define DSP_3_OVERLOAD_PC                      0x33
#define DSP_4_OVERLOAD_PC                      0x34

//internal communication
#define  TRX_BF_BF_COM_SUPERVISION            0x4A

// External Communication
#define  A_BIS_RSL_L3_FAULT_PC         0x50
#define  A_BIS_OML_L3_FAULT_PC         0x51
#define  TB_IP_LINK_DOWN_PC            0x58
#define  ABIS_ALIVE_PC                 0x5A

//BS Temerature 
#define BS_TEMP_LOW_PC                 0x60
#define BS_TEMP_HIGH_PC                0x61 

// DMB (0x70-0x77)
#define  DMB_TEMP_1_HIGH_PC            0x70
#define  DMB_TEMP_2_HIGH_PC            0x71
#define  PC_PDM_FLASH                  0x72
#define  PC_APPL_FLASH                 0x73

// RTM (0x80 - )
#define  RTM_TEMP_HIGH_PC              0x80
#define  TRX_RTM_ID_FAULT_PC           0x81
#define  TRX_RTM_FREQ_BAND_FAULT_PC    0x82
#define  TRX_RTM_CAL_FAULT_PC          0x83

// DLNA (0x90-)
#define  DLNA_TEMP_HIGH_PC             0x90
#define  DLNA_MAIN_CURR_HIGH_PC        0x91
#define  DLNA_DIV_CURR_HIGH_PC         0x92
#define  TRX_DLNA_PRESENT_SUPERVISION  0x93

// PA (0xA0-)
#define  PA_TEMP_HIGH_PC               0xA0
#define  PA_CURR_HIGH_PC               0xA1
#define  PA_FAULT_STATUS_PC            0xA2
#define  TRX_PA_ID_PC                  0xA3
#define  TRX_PA_CAL_PC                 0xA4

// TX (0xB0-0xB7)
#define  TX_SWR_PC                     0xB0
#define TX_SYNTH_PC                    0xB1 

/* not implemented 
#define TX_SUPERVISION_1_PC                0xB2
#define TX_SUPERVISION_2_PC                0xB3
till here    */

// RX (0xB8 - 0xBF)
#define  RX_DIVERSITY_FAULT_PC         0xB8
#define  TRX_RX_SYNTH_SUPERVISION_PC   0xB9
#define  RX_SUPERVISION_PC             0xBA

// TRX (0xC0-0xC7)
#define  RADIO_SUPERVISION_PC          0xC1
#define  TIMING_BUS_PC                 0xC2  
#define  TRX_FRAME_SYNC_SUPERVISION_PC 0xC3
#define  TRX_SYS_CAL_SUPERVISION_PC    0xC4

// TDMoIP (0xD0 - 0xDF)
#define  TRX_TDMOIP_PORT_HOLDOVER_PC   0xD0
#define  TRX_TDMOIP_PORT_CLK_STATE_PC  0xD1
#define  TRX_TDMOIP_PORT_CLK_CONV_PC   0xD2
#define  TRX_TDMOIP_BUNDLE_OVERRUN_PC  0xD3
#define  TRX_TDMOIP_BUNDLE_UNDERRUN_PC 0xD4
#define  TRX_TDMOIP_BUNDLE_STATE_PC    0xD5


// Clock and frequency (0xE0 - 0xEF)

//GPS
#define GPS_RECIEVER_HEALTH_PC                   0xD6
#define GPS_ANTENNA_PC                           0xD7
#define GPS_STATELLITE_SIGNAL_LEVELS_PC          0xD9     

//PLL
#define MAIN_PLL_UNLOCKED_PC   0xE0
#define CLOCK_REFERENCE_PC     0xE1
#define CLOCK_FREQUENCY_PC     0xE2

/*R2.9  FUS R2IP AlarmSynch  starts */

#define  PC_WD_BASE                    0xE0


/*
End:
   Changes for Probable cause for R2 BSC & BTS
   Dated:   12-OCT-2010
*/


#define MAX_TM_HELLO_COUNT_IN_LAPD_UP                        10 /*Change for 19948*/ 
#define MAX_TM_HELLO_COUNT_IN_UE_STATE                       25 /*Change for 23304*/
#define TIMER_VAL_WAIT_FOR_DEL_CHAN_ACK                      30 /*Changes for 23304 */
#endif  /* __OAMSTRXH_HASHDEFS_H */

/* R2.9 : Power saving feature - starts */
#define TO_BE_ENABLED                                        2  
#define CAUSE_ALREADY_IN_SAME_STATE                          0x86  
#define TIMER_VAL_WAIT_FOR_BM_PWR_SAV_RESP                   10 
/* R2.9 : Power saving feature - ends */

/*#define  amrCodecRate590               amrCodecList   */      /*Added for R3 BTS temporarily*/
