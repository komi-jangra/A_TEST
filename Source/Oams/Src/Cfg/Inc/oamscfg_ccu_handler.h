/***********************************File Header ***************************
 *   File Name        : oamscfg_ccu_handler.h
 *   Purpose          : This file contains functions definitions for ccu related Handler  methods.
 *   Project          : BSC OAM
 *   Subsystem        : Oams
 *   Author           : Aricent 
 *   CSCI ID          :
 *   Version          :
 *    ************************************* End **********************************/

#ifndef __OAMSCFG_CCU_HANDLER_H_
#define __OAMSCFG_CCU_HANDLER_H_


I_Void setCcConfigTable();
I_Void setCcDataReqTable();
I_Bool ccConfigRangeChk(CcConfigTableApi *);
I_Bool ccDataReqRangeChk(CcDataReqTableApi *);
I_Void setBicPowerOrderTable();
//I_Bool bicPowerOrderRangeChk(BicPowerOrderTableApi *);
I_Void setCcPowerOrderTable();
I_Bool ccPowerOrderRangeChk(CcPowerOrderTableApi *);


/********************************* Change History ***************************
 *   Release     Patch       Author         Description
 *
 *      ************************************** End *********************************/

#endif /*__OAMSCFG_CCU_HANDLER_H_ */

