/***********************Changes for directing its critical alarm to LOGGER***********/
#ifdef PLATFORM_IMR
#include <bpmxxx_commonDef.h>
#include <bpmxxx_OAM_commonDef.h>
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
#endif


#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
SysAddr slfAddr;
#endif



#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif


#ifdef LOGGER_IMR
#define GCS_TRACE_CRITICAL(args) \
        LOG_PRINT_CRITICAL args;
#define GCS_TRACE_DEBUG(args) \
	LOG_PRINT_DEBUG args;
#endif

