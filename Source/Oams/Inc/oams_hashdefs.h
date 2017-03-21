/********************************************************* File Header ***
 FILE NAME         :  oams_hashdefs.h
 PURPOSE           :  Contains common hashdefs used by Oams modules  
 PROJECT           :  BSC CS2.2
 SUBSYSTEM         :  Oams
 AUTHOR            :  Kapil Tyagi
 CSCI ID           :
 VERSION           :  
*******************************************************************************/

#ifndef _OAMS_HASHDEFS_H_
#define _OAMS_HASHDEFS_H_	1

/* Connection States of BICs */
#define BIC_CONNECTED		1 
#define BIC_NOT_CONNECTED	0

/* Location of TRXs */
#define TRX_LOCATION_IN_FRAME	  1
#define TRX_LOCATION_BIC	      2
#define TRX_LOCATION_R2_BTS     3  /* Added in R2.8 */
#define TRX_LOCATION_R3_BTS	4  /* Added in R2.8 */
#define TRX_LOCATION_R2_BTS_IP	5  /* Added in R2.8 */
/* Usage Type of E1 */
#define E1_USAGE_TYPE_SHARED		0
#define E1_USAGE_TYPE_STANDALONE	1

/* TS Usage Type */
#define TS_USAGE_BIC		 SYS_NODE_TYPE_BIC
#define TS_USAGE_BICTRX	 SYS_NODE_TYPE_TRX
#define TS_USAGE_BTS  	 SYS_NODE_TYPE_R2_BTS
#define TS_USAGE_BTS_TRX SYS_NODE_TYPE_R2_BTS_TRX

#define LAPD_LINK_DOWN          0
#define LAPD_LINK_UP            1
#define LAPD_NOT_APPLICABLE     0xFFFFFFFF
/* Changes for PCU R2.5 : Start*/

#define ABIS_IP_DOWN          0
#define ABIS_IP_UP            1

/* Changes for PCU R2.5 : End*/

/* Changes for R2.2 : Start */
#define ERR_TIMEOUT             0

/* Changes for CS4.0 CCUH */
#define NIGHT                   0x80
#define NIGHT_SHUT_DOWN_MODE    0x40
#define NO_MODULE_POWER         0x20
#define OVP                     0x10
#define HIGH_TEMP               0x08
#define BATTERY_SERVICE         0x04
#define EMERGENCY_SHUTDOWN      0x02
#define MODULE_SERVICE          0x01

/*Alarms*/
#define CCU_ALARM_BIC_CC_CONNECTED_OK                0x11
#define CCU_ALARM_BIC_CC_NOT_CONNECTED               0x10
#define CCU_ALARM_BIC_CC_NO_SOLAR_PANNEL_PWR         0x01

#define CCU_ALARM_BIC_CC_SOLAR_PANNEL_PWR_OK          0x02
#define CCU_ALARM_BIC_CC_PANNEL_CLEANING_NEED         0x03
#define CCU_ALARM_BIC_CC_PANNEL_CLEAN_OK              0x04
#define CCU_ALARM_BIC_CC_BATTERY_CC_SERVICE           0x05
#define CCU_ALARM_BIC_CC_BATTERY_CC_SERVICE_OK        0x06
#define CCU_ALARM_BIC_CC_BATTERY_AGING                0x07
#define CCU_ALARM_BIC_CC_BATTERY_AGING_OK             0x08
#define CCU_ALARM_BIC_CC_BATTERY_AGING_ASSESS_FAIL    0x09
#define CCU_ALARM_BIC_CC_BATTERY_AGING_CALIBR_FAIL    0x0B 
#define CCU_ALARM_BIC_CC_SOC_ALARM_THRES_ALARM        0x0D
#define CCU_ALARM_BIC_CC_SOC_ALARM_THRES_ALARM_OK     0x0E
#define CCU_ALARM_BIC_CC_EMERGENCY_SHUTDOWN_WARNING   0x0F
#define CCU_ALARM_BIC_CC_EMERGENCY_SHUTDOWN_WARNING_OK  0x0A
#define CCU_ALARM_BIC_CC_NIGHT_MODE_REQUEST_ALARM   0x12
#define CCU_ALARM_BIC_CC_NIGHT_MODE_REQUEST_ALARM_OK   0x13
#define CCU_ALARM_BIC_CC_NIGHT_ALARM  0x14
#define CCU_ALARM_BIC_CC_NIGHT_ALARM_OK  0x15
#define CCU_ALARM_BIC_CC_HIGH_TEMPARATURE_ALARM  0x16
#define CCU_ALARM_BIC_CC_HIGH_TEMPARATURE_ALARM_OK  0x17

/* Changes for CS4.0 CCUH end */

/*R2 BSC 2.0 changes Starts*/
#define DSP_IS_ALREADY_LOCKED                     0x01
#define DSP_IS_ALREADY_UNLOCKED                   0x02
#define DSP_DB_QUERY_FAILED                       0x03
#define DSP_INVALID_REASON_IN_LOCK                0x04
#define DSP_INVALID_REASON_IN_UNLOCK              0x05
#define DSP_IS_IN_UNLOCKED_STATE                  0x06
#define DSP_IS_IN_LOCKED_STATE                    0x07
#define DSP_RESET_IN_PROGRESS                     CM_ERR_DSP_RESET_IN_PROGRESS
#define DSP_INIT_IN_PROGRESS                      0x09
/*R2 BSC 2.0 changes Ends*/

/*Changes for PCU R2.5 Start*/
#define NOT_APPLICABLE		                      0

#define DB_READ_FAILURE                               0xFF

#define CBL_ENABLED                                   1
#define CBL_DISABLED                                  0

//#define CELL_BARRED                                   1         /* It's already defined in sysxxx_hashdefs.h */
#define CELL_UNBARRED                                 CELL_NORMAL /* Mapping with existing Macro */

#define MAX_NUM_NSVC_PER_BSS                          32 /* this is used at CFG for taking the size of array for NSVCs,  
                                                          * The maxNumNsvcsOverFr is defined in GbInterface Table
                                                          */
/*Changes for PCU R2.5 End*/
#define  AMR_NOT_SUPPORTED      0
#define  AMR_SUPPORTED          1
//#define  AMR_HR_ONLY            1

/* AMR Codec List */
#define  AMR_590                1       //Obsolete for R2.8
#define AMR_FR_1220             0x0001
#define AMR_FR_1020             0x0002
#define AMR_FR_795              0x0004
#define AMR_FR_740              0x0008
#define AMR_FR_670              0x0010
#define AMR_FR_590              0x0020
#define AMR_FR_515              0x0040
#define AMR_FR_475              0x0080
#define AMR_FR_180              0x0100
#define AMR_HR_795              0x0200
#define AMR_HR_740              0x0400
#define AMR_HR_670              0x0800
#define AMR_HR_590              0x1000
#define AMR_HR_515              0x2000
#define AMR_HR_475              0x4000
#define AMR_HR_180              0x8000
#define  INVALID                0xFF
/* START - Changes for R2.3.3 - CBCH */
#define ERR_LAPD_DOWN           1
#define ERR_DB_OPER_FAIL        2
#define ERR_MEM_FAILURE         3

#define PWR_ACTION_PWR_RESET        0x08
#define PWR_ACTION_SOFT_RESET       0x04
#define PWR_ENTITY_BIC_ALL_TRX      0x28
/* END - Changes for R2.3.3 - CBCH */

/*** New defines for R2.8 ***/
#define FACCH_REPEAT_DISABLED   0
#define FACCH_REPEAT_ENABLED    1

/* RTP Configuration */
#define JITTBUF_TYPE_STATIC     0
#define JITTBUF_TYPE_ADAPTIVE   1

#endif /* _OAMS_HASHDEFS_H_ */

/********************************* Change History ******************************
Release     Patch        Author         	Description
CS2.2                  Kapil Tyagi		Initial Draft       		

*************************************** End ***********************************/
