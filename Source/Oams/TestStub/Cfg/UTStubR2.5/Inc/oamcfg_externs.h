
/********************************************************** Copyright Notice ***
  INDIA MOBILITY RESEARCH PVT. LTD.

  Copyright 2004 - 2007, All rights reserved.

  This file contains unpublished source code owned by India Mobility Research.

  No part may be reproduced except as authorized by written permission. The
  copyright and the foregoing restriction extend to reproduction in all media.

  The information contained in this file is the proprietary and exclusive
  property of India Mobility Research Pvt. Ltd.  except as otherwise indicated.
  No part of this file, in whole or in part, may be reproduced, stored,
  transmitted, or used for design/implementation purposes without the prior
  written permission of India Mobility Research Pvt. Ltd.

  This file can not be used purpose other than stated in the separate software
  license agreement.

  This file may contain information of a sensitive nature. This information
  should not be given/transferred to any third party.

  The information contained in this document is subject to change without notice.
  India Mobility Research Pvt. Ltd.  specifically disclaims all warranties,
  express or limited, including, but not limited, to the implied warranties of
  merchantability and fitness for a particular purpose, except as provided for
  in a separate software license agreement.

  India Mobility Research Pvt. Ltd.
  246, Phase IV, Udyog Vihar
  Gurgaon
  Haryana
  INDIA PIN 122015
Phone: +91-124-4311600
Fax  : +91-124-4104766
 ********************************************************************** End ***/
/*************************************************************** File Header ***
  File Name      : oamcfg_externs.h
Purpose        :
Project        : IMR-BSC-CFG
Subsystem   :
Author         : Aricent, B'lore.
CSCI id        :
Version        : 1.1
 ********************************************************************** End ***/


/* Extern global variables */
#ifndef __OAMCFG_EXTERNS_H_
#define __OAMCFG_EXTERNS_H_
extern I_S32 gSrcId;      /* SrcId for the CFG */
extern void *gCfgMsgBuf;   /* Message Pointer for the received message */
extern I_U32 gRecvMsgSize;  /* received message size */

extern I_Bool gCellLockDisProcForBssLock;
extern I_Bool  gCellUnLockEnableProcForBssUnLock;
extern BssTableApi gDbBssTableApiStorage;
extern I_Bool  gAinterfaceUPDownFlag ;


extern hist *gHistBufPtr;
extern hist *gHistRunPtr;
extern I_S32 gLogFlag;
extern FILE *gErrFname;

extern I_U32 gCellEnableSent ;
extern I_U32 gCellDisableSent;
extern  void* gStoredMsgBufPtr;

/*********************/
typedef enum 
{
   CFG_INIT,
   CFG_READY
}cfgStateEnum;

extern cfgStateEnum gCfgState;  /* cfg State varable */
/*********************/
extern I_Bool gFirstBSSTableStorageUpdation;
extern I_Bool gFirstBSSTableStorageUpdation;
extern I_Bool gPsUnlockCellsProgressFlgForBSS;

/************************************************************ Change History ***
  Release     Patch       Author         Description

 ********************************************************************** End ***/

#endif
