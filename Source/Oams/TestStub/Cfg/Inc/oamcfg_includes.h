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

/***********************************File Header ***************************
       File Name        : oamcfg_includes.h
       Purpose          : header file for CFG includes
       Project          : IMR OAM - BSC
       Subsystem        : bsc
       Author           :  Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/

#ifndef  __OAMCFG_INCLUDES_H_
#define  __OAMCFG_INCLUDES_H_

/*************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sysxxx_typedef.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_msgopcode.h>
#include <sysxxx_proc.h>
#include <sysxxx_macro.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_datastruct.h>
#include <syscmn_hashdefs.h>
#include <syscmn_datastruct.h>
#include <oamxxx_tableapidefs.h>
#include <oamomc_errorcodes.h>
#include <oamxxx_hashdefs.h>
#include <oamxxx_datastruct.h>
#include <oamxxx_msgstruct.h>
#include <dbsxxx_commondefs.h>
#include <dbsxxx_commonwrappers.h>
#include <dbsxxx_cfg_dbwrapper.h>
#include <dbsxxx_cellh_dbwrapper.h>
#include <oamsks_alarmtypedefs.h>

#ifdef PLATFORM_IMR
#include <bpmxxx_commonDef.h>
#include <bpmxxx_OAM_commonDef.h>
#endif

#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <DBLIBError.h>
#include <mgs_common_hashdef.h>
#include <mgs_trau_hashdef.h>
#include <mgs_common_hashdef.h>
#include <mgs_trau_msgstruct.h>
#include <mgs_tsi_msgstruct.h>
#include <oamsxxx_alarmid.h>
#include <oamsxxx_typedef.h>
#include <oamsxxx_hashdef.h>
#include <oamscfg_hashdefs.h>
#include <oamscfg_type.h>
#include <csappxxx_common_datastruct.h>
#include <oamsxxx_msgstruct.h>
#include <oamcfg_externs.h>
#include <oams_msgstruct.h>
#include <cfg_stub_bss_object_handler.h>
#include <cfg_stub_cell_object_handler.h>
#include<cfg_stub_dbhndlr.h>
#include<cfg_stub_db_del_operations.h>
#include<cfg_stub_trxh.h>
#include<cfg_stub_e1_object_handler.h>
#include<cfg_stub_alarm_handler.h>
#include <cfg_stub_trau_init_handler.h>

#endif

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change

************************************** End *********************************/

