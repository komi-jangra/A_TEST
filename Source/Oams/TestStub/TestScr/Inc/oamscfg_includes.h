/***********************************File Header ***************************
       File Name        : oamscfg_alarm_handler.h
       Purpose          : This file contains include files for CFG

       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/

#ifndef  __OAMCFG_INCLUDES_H_
#define  __OAMCFG_INCLUDES_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <memory.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <errno.h>
#include <time.h>
#include <sysxxx_typedef.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_datastruct.h>
#include <sysxxx_msgopcode.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <sysxxx_msgstruct.h>
#include <syscmn_hashdefs.h>
#include <syscmn_datastruct.h>
#include <sysxxx_alarm.h>
#include <oamxxx_tableapidefs.h>
#include <oamomc_errorcodes.h>
#include <oamsnmp_hashdefs.h>
#include <oamxxx_hashdefs.h>
#include <dbsxxx_commondefs.h>
#include <dbsxxx_commonwrappers.h>
#include <dbsxxx_cfg_dbwrapper.h>
#include <dbsxxx_cellh_dbwrapper.h>
#include <dbsxxx_grhm_dbwrapper.h>

#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <ipcfrm_msgdef.h>
#include <DBLIBError.h>

#endif /*__OAMCFG_INCLUDES_H_*/

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change

************************************** End *********************************/
