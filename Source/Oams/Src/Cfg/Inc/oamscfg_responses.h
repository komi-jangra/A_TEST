/***********************************File Header ***************************
       File Name        : oamscfg_alarm_handler.h
       Purpose          : This file contains function prototype for CFG
                          CM responses
                          Alarm handler  methods.
       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/

#ifndef __OAMCFG_RESPONSES_H_
#define __OAMCFG_RESPONSES_H_

void cfgSendNackToCm(I_U32 errNum);
void cfgSendAckToCm();

#endif /*__OAMCFG_RESPONSES_H_*/

/********************************* Change History ***************************
   Release     Patch       Author         Description
************************************** End *********************************/
