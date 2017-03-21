/***********************************File Header ***************************
       File Name        : oamscfg_ut.h
       Purpose          : This file contains include files which needed during CFG UT

       Project          : BSC OAM
       Subsystem        : Oams
       Author           : VNL
       CSCI ID          :
       Version          :
************************************* End **********************************/

#ifndef  __UT_H_
#define  __UT_H_

I_S32 UteSendMsg(I_Void *snd_ptr, I_SL32 priority, I_S32 _length) ;
#define SendMsg(snd_ptr, priority, _length) UteSendMsg(snd_ptr, priority, _length)

#endif /*__UT_H_*/

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change

************************************** End *********************************/
