
#include <its_alarm.h>
#include <sys/file.h>


#ifndef  _ALARM_ENTRY_
#define  _ALARM_ENTRY_

#define CCITT_BSSAP_ALARM_START  5101
#define CCITT_BSSAP_ALARM_END    5141

//ITS_UINT BSSAP_AlarmLevel_CCITT = ALARM_LVL_OFF;

#endif

void
BSSAP_Alarm_CCITT(int which, const char *file, const int line,
                char *format, ...);

