#ifndef __OAMSCCUH_HASHDEFS_H
#define __OAMSCCUH_HASHDEFS_H


#define  CCUH_ACT_CLID                       1
#define  CCU_HANDLER  1
#define CCU_SUCCESS 	1
#define CCU_FAILURE	0

#define MAX_LAPD_PACKET_SIZE 235
#define VALID_INFO 	1
#define INVALID_INFO 	2
#define START   0
#define STOP    1

#define FAIL   0
#define SUCCESS    1

#define SEQUENCE_NUM			0x00
//#define OBJECT_CLASS			0x10
#define OBJECT_INST_OCTET1		0x01			
#define OBJECT_INST_OCTET2		0xFF
#define OBJECT_INST_OCTET3		0xFF


#define NO_CC_COMM  	         	0x01
#define PARAMETER_OUT_OF_RANGE          0x02
#define BIC_CCU_INTERNAL_FAULT	        0x03
#define CC_INFO_NACK_RESP_INVALID	0x04

#define CARDSTATE_INVALID               0xFF

#define CC_DATA_PRESENT 0x01
#define STOP_SUCCESSFUL 0x02

#endif
