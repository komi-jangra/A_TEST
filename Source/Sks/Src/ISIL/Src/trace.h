
#include <stdio.h>

#ifdef CPLUSPLUS
extern "C"
{
#endif


#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_msgdef.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif


#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

#define ITS_DEFAULT_SRC 0xEEEE

void Trace( const char *ftr, ...);

#define ISILTRACE(level,args)\
          Trace args;


#ifdef LOGGER_IMR
#define ISIL_DEBUG_TRACE(args)  LOG_PRINT_DEBUG args;
#else 
#define ISIL_DEBUG_TRACE(args)        ISILTRACE(DEBUG ,args)
#endif



#ifdef LOGGER_IMR
#define ISIL_ERROR_TRACE(args)  LOG_PRINT_CRITICAL args;
#else 
#define ISIL_ERROR_TRACE(args)        ISILTRACE(ERROR ,args)
#endif



#ifdef LOGGER_IMR
#define ISIL_WARNING_TRACE(args)   LOG_PRINT_MAJOR args;
#else 
#define ISIL_WARNING_TRACE(args)      ISILTRACE(WARNING,args)
#endif


#ifdef CPLUSPLUS
}/*end of extern C*/
#endif
