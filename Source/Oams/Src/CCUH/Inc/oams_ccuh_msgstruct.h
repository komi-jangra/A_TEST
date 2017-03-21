/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oams_ccuh_msgstruct.h
 PURPOSE           :  Contains CCUHandler Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  VNL
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMS_CCUH_MSGSTRUCT_H
#define __OAMS_CCUH_MSGSTRUCT_H


//#include "stdio.h"
typedef struct
{
   OptFlag                         isCcuIdPresent;
   OptFlag                         isCcuBackupSwVersionPresent;
   OptFlag                         isCcuNackPresent;
	BicTei                          bicTei;
   BicIdentifier                   bicId;
	CcuIdentifier  					  ccuId;
	Result                          infoAvailStatus;
	BicCcProtoVersion                 ccProtoVersion;
	BicCcSerialNumber               ccSerialNumber;
	CcActiveSwVersion               ccActiveSwVersion;
	CcBackupSwVersion               ccBackupSwVersion;
	CcNackCause                     nackCause;
	CcPowerInfo                       ccPwrInfo;
}OamsCcuhContext;

#endif   /* __OAMS_BICH_MSGSTRUCT_H */
