/***********************************File Header ***************************
  File Name        : oamscfg_type.h
Purpose          : This file contains  typedefs for CFG
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMCFG_TYPE_H_
#define __OAMCFG_TYPE_H_

/* history buffer */

typedef struct HIST
{
   I_S32 daoId;
   I_S16 qryId;
   I_S16 size;
   I_S8 *buf;
   struct HIST *next;
}hist;

typedef struct
{
   I_U8 dListLinkE1;
   I_U8 tListLinkTs;
}dataLinkE1Ts;

typedef struct
{
   I_U32  cbsTimerId;
   I_U16  cbsId;
}CbsRespTimer;

typedef CbsRespTimer CbsRepeatTimer;

#endif /*_OAMCFG_TYPE_H_*/

/********************************* Change History ***************************
  Release     Patch       Author         Description

 ************************************** End *********************************/
