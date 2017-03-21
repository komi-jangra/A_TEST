/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamscellh_hashdefs.h
 PURPOSE           :  Contains Cell Handler HashDefs
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSCELLH_HASHDEFS_H
#define __OAMSCELLH_HASHDEFS_H

/* CELLH Error Codes */
#define OAMS_SUCCESS                    1
#define OAMS_FAILURE                    0

/*For LTRX Specifications */
#define   MAX_LTRXS_IN_CELL        MAX_NUM_TRX_PER_CELL
#define   MAX_CHAN_TYPE            6
#define   BCCHCCCHPRIORITY        100000
#define   BCCHCCCHSDCCH4PRIORITY  100000
/* Commented for PCU Rel2.5*/
/* #define   PBCCHPRIORITY           10000
#define   PDCHPRIORITY            100 */
#define   SDCCH8PRIORITY          10000      
/*Changes starts for PCU Rel2.5*/
/*#define   TCHPRIORITY             100 */
#define   DUALTRAFFICPRIORITY     100
#define   REL_INVALID             0xFF
/*Changes ends for PCU Rel2.5*/
#define   CELLHM_HANDLER          1
/*Changes starts for PCU Rel2.5*/
/*#define   MAX_CELLHM_INST         18 */
/*Changes ends for PCU Rel2.5*/

#define SYS_INFO_TYPE_01        1
#define SYS_INFO_TYPE_02        2
#define SYS_INFO_TYPE_02TER     11
#define SYS_INFO_TYPE_03        3
#define SYS_INFO_TYPE_04        4
#define SYS_INFO_TYPE_05        5
#define SYS_INFO_TYPE_05ter     14
#define SYS_INFO_TYPE_06        6
#define SYS_INFO_TYPE_13        40
#define SYS_INFO_TYPE_02QUAT    41
#define MEAS_INFO               72

/* LTRX Status */
#define GEN_FAILED		1
#define GEN_SUCCESS		0

/* CS4.0: Abis E1 Lock/Unlock changes : Starts */
#define INVALID_E1		0xFF
#define MAX_NUM_E1              8
/* CS4.0: Abis E1 Lock/Unlock changes : Ends */

#define CARDSTATE_INVALID               0xFF
#define BCCH_CCCH_SDCCH4_SI4_CBCH       0x6 /*Used in SI4_SDCCH4 for CBCH */
#define SDCCH8_SI4_CBCH                 0xA /*Used in SI4_SDCCH8 for CBCH */
#define TRUE_SI_CBCH                    0
#define INVALID_PTRXID 0
#endif /* __OAMSCELLH_HASHDEFS_H */

