/***********************************File Header ***************************
       File Name        : oam_sysinfo_hashdefs.h
       Purpose          : header file to declare the hashdefs 
                          used for system information message encoding
       Project          : IMR OAM - BSC
       Subsystem        : bsc
       Author           : Aricent
       CSCI ID          :
       Version          :
************************************* End **********************************/
#ifndef SYSINFODEFS_HPP_
#define SYSINFODEFS_HPP_

#define RADIO_RESOURCE_MANAGEMENT_MSG 	0x06
#define SKIP_INDICATOR 			0x00
#define MSG_SYS_INFO_01 		0x19
#define MSG_SYS_INFO_02 		0x1A
#define MSG_SYS_INFO_02ter 		0x03
#define MSG_SYS_INFO_03 		0x1B
#define MSG_SYS_INFO_04 		0x1C
#define MSG_SYS_INFO_05 		0x1D
#define MSG_SYS_INFO_05ter 		0x06
#define MSG_SYS_INFO_06 		0x1E
#define MSG_SYS_INFO_13 		0x00
#define MSG_SYS_INFO_02quat 0x07
#define MSG_MEAS_INFO       0x05
#define BUF_LEN 			50
#define NW_LEN 		                28
#define ARFCN_LEN 		        18
#define BITMAP_512_INDEX                1
#define BITMAP_512_RANGE                511
#define BITMAP_ZERO_LEN                 124
#define ACCESS_CLASS_LEN		16
#define NCC_LEN                         8
#define BA_IND_ZERO			0
#define COMPLETE_BA			0
#define NORMAL_REPORTING		0
#define CCCH_CONF_0                     0
#define CCCH_CONF_1                     1
#define CCCH_CONF_2                     2
#define BCCH_CCCH_1                     1
#define BCCH_CCCH_2                     2
#define PRESENT                         1
#define NOT_PRESENT                     0
#define FORMAT_LEN                      22
#define BITSTRING_LEN                   22
#define BITSTRING_LEN_23		23
#define SI_SPARE                        43
#define BCCH_CHANGE_MARK_ZERO           0
#define SI_CHANGE_FIELD_ZERO            0
	
/* IE for Update SI msgs */		
#define SI_2TER_IND_NOT_PRESENT         0
#define SI_2TER_IND_PRESENT             1
#define CELL_BAR_ACCESS                 2              
#define TRUE                            1
#define CBCH_CHANNEL_DESCRIPTION        0x64
/* PCU Rel2.5*/
#define GPRS_PRESENT                    3
#define GPRS_NOT_PRESENT                4
#define N_CELL_CHANGE                   5
/* PCU Rel2.5*/              
 #define MP_CHANGE_MARK                 1
 #define FDD_QOFFSET                    0
 #define FDD_REPQUANT                   1
 #define FDD_MULTIRAT                   1
 #define FDD_RSCPMIN                    0
 #define QUAT_BUF_LEN 			            400


#endif /* SYSINFODEFS_HPP_ */
