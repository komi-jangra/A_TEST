
/********************************** Copyright Notice ************************
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
 **************************************** End *********************************/
/***********************************File Header ***************************
  File Name        : oamcfg_type.h
Purpose          : header file to declare the methods, API IDs and API data
structures used for registering the Application data tables
and acces APIs.
Project          : IMR OAM - BSC
Subsystem        : bsc
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/
#ifndef _OAMCFG_TYPE_H_
#define _OAMCFG_TYPE_H_

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

#endif

/********************************* Change History ***************************
  Release     Patch       Author         Description

 ************************************** End *********************************/
