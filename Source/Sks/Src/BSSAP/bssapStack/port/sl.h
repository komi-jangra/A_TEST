/*
 * This is the primary include file for the Service Library.  All
 * applications using the library should include _only_ this file.
 *
 * Copyright 2000, Hughes Software Systems, Ltd.
 */

#ifndef _SL_H_
#define _SL_H_

#include "cspl.h"

typedef QMODULE sl_module_t;
typedef void *sl_event_t;
typedef QTIMER sl_timer_t;
typedef QMPOOL sl_pool_t;
typedef QTIME sl_time_val;


/* Modules */
sl_module_t sl_module_register (const char *name,
				void *(*init) (void *arg),
				int (*msg_handler) (void *buf,
						     void *context),
				void (*timer_handler) (QTIMER tid, void *data, void *context),
				void *init_arg);

/* External events */
sl_event_t sl_event_register (int fd,unsigned char (*callback) (int fd));
void sl_event_deregister (sl_event_t eid);

/* Buffer Management */
sl_pool_t sl_pool_create (unsigned int bufsz, unsigned short nbuf);
void *sl_buf_alloc (sl_pool_t poolid);
void sl_buf_free (void *buf);
void *sl_alloc(unsigned int size);
void sl_free(void *p);
/* Queue Management */
void sl_mq_send (sl_module_t mid, unsigned int arg, void *buf);

/* Notes */
void sl_note_send (sl_module_t mid, unsigned int note);

/* Timer Management */
sl_timer_t sl_timer_start (sl_time_val *timeo, void *data);
sl_timer_t sl_flow_timer_start (sl_time_val *timeo, void *data);
void sl_timer_cancel (sl_timer_t tid);
void *sl_timer_get_data (sl_timer_t tid);

/* Log, print, etc. */
void sl_log (unsigned int level, const char *format, ...);
int ss7_over_sigtran_log_print (const char *format, ...);
void sl_print (const char *format, ...);
#define sl_buf_free(buf) \
  if(buf) \
  { \
  	qvMsgFree((void *)buf); \
	buf = 0; \
  }	


#define sl_panic qvPanic
void sl_log_level_set(sl_module_t mid,unsigned int level);
int sl_log_level_get(void);

#define SL_LOG_CRIT  0
#define SL_LOG_ERROR 1
#define SL_LOG_WARN  2
#define SL_LOG_INFO  3
#define SL_LOG_DEBUG 4
#define SL_LOG_OFF   5

#define SL_BUF_FREE_LESS_25 0
#define SL_BUF_FREE_LESS_50 1
#define SL_BUF_FREE_MORE_50 2
#define SL_BUF_NO_FREE_LEFT 3

/* Miscellaneous macros */
#ifdef SINGLE_THREAD
#define SL_MUTEX_DEF(name)
#define SL_MUTEX_INIT(mutex)
#define SL_MUTEX_LOCK(mutex)
#define SL_MUTEX_UNLOCK(mutex)

/* friendly alternate names (?!? :) */
#define SL_LOCK_DEF(name)
#define SL_LOCK_INIT(mutex)
#define SL_LOCK(mutex)
#define SL_UNLOCK(mutex)
#else
#include <pthread.h>
#include <semaphore.h>

#define SL_MUTEX_DEF(name) pthread_mutex_t name;
#define SL_MUTEX_INIT(mutex) pthread_mutex_init (mutex, 0)
#define SL_MUTEX_LOCK(mutex) pthread_mutex_lock (mutex)
#define SL_MUTEX_UNLOCK(mutex) pthread_mutex_unlock (mutex)
#endif

#define SL_MEMBER_OFFSET(type, member) YOFFSETOF(type, member)

#endif /* _SL_H_ */
