/***********************************File Header ***************************
       File Name        : oamscfg_signal_handler.h
       Purpose          : This file contains function protoypes for CFG
                          signal handlers
       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/


#ifndef OAMCFG_SIGNAL_HANDLER_H_
#define OAMCFG_SIGNAL_HANDLER_H_


typedef void (*sighandler_t)(int);
void *cfgSigalrmHandler();
void *cfgSigintHandler();
void *cfgSigquitHandler();
void *cfgSigstopHandler();
void *cfgSigsegvHandler();
void *cfgSigbusHandler();
void *cfgSigillHandler();
void *cfgSigfpeHandler();
void *cfgTimeOutHandler();

/********************************* Change History ***************************
   Release     Patch       Author         Description

************************************** End *********************************/

#endif /*OAMCFG_SIGNAL_HANDLER_H_ */ 
