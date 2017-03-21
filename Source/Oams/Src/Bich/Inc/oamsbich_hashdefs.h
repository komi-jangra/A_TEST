#ifndef __OAMSBICH_HASHDEFS_H
#define __OAMSBICH_HASHDEFS_H
#include<time.h>


#define  BIC_HANDLER                          1
#define  BICHM_ACT_CLID                       1
#define  CONNECTED                            1
#define  NOT_CONNECTED                        0
#define  BTS_LAPD_LINK_UP                     LAPD_LINK_UP
#define  BTS_LAPD_LINK_DOWN                   LAPD_LINK_DOWN
#define  BTS_LAPD_NOT_APPLICABLE              LAPD_NOT_APPLICABLE
#define  BICHM_IPC_MEM_FREE                   1
#define  BICHM_ORD_MEM_FREE                   0
#define  LINK_ESTAB                           1
#define  LINK_ESTAB_FAILED                    2
#define  FREE_INST                            3
#define  NO_LINK_EST                          2
#define  INVALID                              0
#define  SUCCESS                              1
#define  FAILURE                              0
#define  BIC_E1_MISMATCH                      0
#define  BIC_E1_MATCHES                       1
#define  BIC_PARENT_NOT_CONF                  2
#define  BIC_PARENT_E1_MISMATCH               3
#define  BIC_PARENT_NOT_CONNECTED             4
#define  BIC_PARENT_INCORRECT                 5
#define  BIC_LAPD_TS_MISMATCH                 6
#define  BIC_PARENT_LAPD_TS_MISMATCH          7
#define ABIS_E1_STATUS_NO_BIC  			0
#define ABIS_E1_STATUS_BIC_CON_IN_PROGRESS	1
#define ABIS_E1_STATUS_BIC_CONNECTED		2
#define MAX_RETRY_COUNT                         5
#define CONFIG_TIMER_VAL                        1
#define MALLOC	malloc 	/*later it will be changed to AlocOrdBuf */
#define FREE	free 	/*later it will be changed to DealocOrdBuf */

#define BICH_SUCCESS 	1
#define BICH_FAILURE	0


#define SEQUENCE_NUM			0x00
//#define OBJECT_CLASS			0x10
#define OBJECT_INST_OCTET1		0x01			
#define OBJECT_INST_OCTET2		0xFF
#define OBJECT_INST_OCTET3		0xFF

#define BIC                             1
#define BICTRX                          2
#define CARDSTATE_INVALID               0xFF

# define BSC_BIC_NACK_PARAMETER_OUT_OF_RANGE    0x05

/* R1.1 Changes start */
#define CLK_SYN_IN_PROGRESS             0x80
#define CLK_SYN_SUCCESSFUL              0x81
#define CLK_SYN_HOLD_OVER_MODE          0x82
#define BIC_TRX_POWER_ON_STATE          0x83
#define BIC_TRX_POWER_OFF_STATE         0x84

/* R1.1 Changes End */

/* R2.5.5 Changes start */
#define   TB_IP_LINK_DOWN_PC                  0x52
#define   DLNA_TEMP_HIGH_PC                   0x63
#define   DMB_TEMP_1_HIGH_PC                  0x64
#define   DMB_TEMP_2_HIGH_PC                  0x65
#define   TX_SWR_FAULT_PC                     0x80
#define   RX_DIVERSITY_FAULT_PC               0x90
#define   FM_TRX_PC                           0xd0
#define   RADIO_SUPERVISION_PC                0xd2
#define   TRX_FRAME_SYNC_SUPERVISION_PC       0xd6
#define   TRX_TX_SYNTH_SUPERVISION_PC         0xd7
#define   TRX_RX_SYNTH_SUPERVISION_PC         0xd8
#define   TRX_BF_BF_COM_SUPERVISION_PC        0xd9
#define   RM_HW_PC                            0xc0
#define   DLNA_MAIN_CURR_HIGH_PC              0xe0
#define   DLNA_DIV_CURR_HIGH_PC               0xe1
#define   PA_CURR_HIGH_PC                     0xe2
/*R2.9  FUS R2IP AlarmSynch  starts */
/* synched the probable cuase values with FUS */
#define CP_SW_FATAL_PC                           0x10 
#define DSP_1_SW_FATAL_PC                        0x11  
#define DSP_2_SW_FATAL_PC                        0x12 
#define DSP_3_SW_FATAL_PC                        0x13 
#define DSP_4_SW_FATAL_PC                        0x14 

//overload
#define CP_OVERLOAD_PC                          0x31     
#define DSP_1_OVERLOAD_PC                      0x32  
#define DSP_2_OVERLOAD_PC                      0x33
#define DSP_3_OVERLOAD_PC                      0x34
#define DSP_4_OVERLOAD_PC                      0x35

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

/* R2.5.5 Changes End */

#define  MAX_BM_HELLO_CNT_CNCTD_OR_CIP_STATE  50 /*Changes for mantis 23210*/

#endif
