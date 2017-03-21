#include "sl.h"
#include "sl_msg.h"
#include "bssap.h"
#include <syslog.h>

#define SL_MAX_POOLS 256
#define CSPL_EVENT_MAX 512

int ss7_over_sigtran_log_print (const char *format, ...);
void ss7_over_sigtran_err_log(unsigned long tlli, char *fmt, ...);

char *sl_log_names[] = {
    "CRITICAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG"
};
unsigned long int defaultaddress1;
typedef struct {
    int logLevel;   /*Order of logLevel and name should be the same with cmk_task_ctxt struct*/
    char name [31]; /*Done to keep sl_log and cmk_log in sync*/
} sl_module_ctxt;    

static const int yes = 1, no = 0;

int systemLogFlag = 1;
int gsn_log_id = DEFAULT_LOG_ID;
char h_buf[4096];

typedef struct{
    int fd;
    unsigned char (*callback) (int fd);
    YLNODE list_entry;
}sl_event;

typedef struct {
    int npools;
    sl_pool_t pool_id [SL_MAX_POOLS];
    unsigned int size[SL_MAX_POOLS];
    unsigned int step[SL_MAX_POOLS];
} sl_pool_list;

static sl_pool_list pool_list;

YLIST sl_event_list, sl_event_free_list;

unsigned char nm_autorefresh_flag;
static int    ss7_over_sigtran_vprintf( const char *format, va_list A );

sl_event *event_pool_global;

 sl_pool_t gtp_pool;
static	void	errorabort( const char *s )
{
	char	*e = strerror(errno);
	qvPanic("%s: %s", s, e );
}

static	void	*ss7_over_sigtran_receive( void *S, QMODULE *sender, QMODULE *receiver, signed char *priority )
{
	YLIST *event_list = (YLIST *)S;
	fd_set rfds;
	int max_fd = 0, n;	
	sl_event *event;
	YLNODE *entry;
	struct timeval
		zero;
	zero.tv_sec = zero.tv_usec = 0;


	if (ylEmpty(event_list))
	{
		qvPanic("External event list empty");
		return 0;
	}

	FD_ZERO (&rfds);
	max_fd = 0;

	for( entry = ylFirst(event_list); entry; entry = ylNext(entry) )
	{

		event = YMEMBEROF(sl_event, list_entry, entry);
		if (event->fd + 1 > max_fd)
			max_fd = event->fd + 1;
		FD_SET (event->fd, &rfds);
	}
	n = select( max_fd, &rfds, 0, 0, &zero );

	if( n < 0 ) {
		errorabort("select");
	}
	for( entry = ylFirst(event_list); entry; entry = ylNext(entry) )
	{
		event = YMEMBEROF(sl_event, list_entry,
				entry);
		if (FD_ISSET (event->fd, &rfds))
			event->callback (event->fd);
	}
	return 0;
}

static	void 	ss7_over_sigtran_timedwait( void *S, const QTIME *T )
{
	YLIST *event_list = (YLIST *)S;
	fd_set	F;
	int max_fd = 0, n;	
	sl_event *event;
	YLNODE  *entry;

	struct timeval
		timeout;

	FD_ZERO( &F );
	max_fd = 0;
	for( entry = ylFirst(event_list); entry; entry = ylNext(entry) )
	{
		event = YMEMBEROF(sl_event, list_entry,
				entry);
		if (event->fd + 1 > max_fd)
			max_fd = event->fd + 1;

		FD_SET (event->fd, &F);
	}

	if( T ) {
		timeout.tv_sec = T->s;
		timeout.tv_usec = T->us;
	}

	n = select( max_fd, &F, 0, 0, T?&timeout:0 );
	if( n < 0 ) {
		errorabort("select");
	}
}

const QSHELL    __operations = {
        ss7_over_sigtran_timedwait,
        0, 
        ss7_over_sigtran_receive,
        0,
        0
};

const QSHELL	*operations = &__operations;

static	void	*__qvc;

static	void	*s_malloc( unsigned int size )
{
	return malloc( size );
}

static	void	s_free( void *m )
{
	free(m);
}

static	void	*s_newkey( void )
{
	return 0;
}

static	void	*s_getkey( void *key )
{
	return __qvc;
}

static	void	s_setkey( void *key, void *value )
{
	__qvc = value;
}

static	void	*s_newlock( void )
{
	return	0;
}

static	void	s_lock( void *lock )
{
}

static	void	s_unlock( void *lock )
{
}

static	void	s_destroylock( void *lock )
{
}

static int    ss7_over_sigtran_vprintf( const char *format, va_list A )
{
#ifdef SYSLOG_SUPPORT
	return vfprintf( stdout, format, A );
#else
    char buf[2048];
	char *p1;
	char temp_hbuf[4096];
   
	memset(buf, 0, sizeof(buf));
	memset(temp_hbuf, 0, sizeof(temp_hbuf));
    vsprintf (buf, format, A);
	p1=strchr(format,'\n');
	if(p1== NULL)
	{
			if ( ( strlen(h_buf) + strlen(buf) )  >= 4096 )
				{
						syslog (2, "%s", h_buf);
						memset(h_buf,0,4096);
				}
/*	   strncat(h_buf,buf, sizeof(buf));
	   snprintf(h_buf, sizeof(h_buf), "%s%s", h_buf, buf);*/
	   snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, buf);
	   snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
	   h_buf[sizeof(h_buf) - 1]=0;

	}
	else
	{
		if(p1 == format)
		{
			syslog (2, "%s", h_buf);
			memset(h_buf,0,4096);
/*			strcat(h_buf,buf+1);	*/
	   		snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, buf+1);
	   		snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
			h_buf[sizeof(h_buf) - 1]=0;
		}
		else if (p1 == (format+strlen(format)-1))
		{
				if ( ( strlen(h_buf) + strlen(buf) )  >= 4096 )
				{
						syslog (2, "%s", h_buf);
						memset(h_buf,0,4096);
				}
/*			strcat(h_buf,buf);
			snprintf(h_buf, sizeof(h_buf), "%s%s", h_buf, buf);*/
			snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, buf);
	   		snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
	   		h_buf[sizeof(h_buf) - 1]=0;
			syslog (2, "%s", h_buf);
			memset(h_buf,0,4096);
		}
		else 
		{
				if ( ( strlen(h_buf) + strlen(buf) )  >= 4096 )
				{
						syslog (2, "%s", h_buf);
						memset(h_buf,0,4096);
				}
/*			strcat(h_buf,buf);*/
			snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, buf);
	   		snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
	 		h_buf[sizeof(h_buf) - 1]=0;

		}

	}
    return 0;
#endif
}

static	int	s_vprintf( const char *format, va_list A )
{
	return vfprintf( stderr, format, A );
}

static	void	s_abort(void)
{
	abort();
}

const QSYSOP	__os = {
	s_malloc,
	s_free,
	s_newkey,
	s_getkey,
	s_setkey,
	s_newlock,
	s_destroylock,
	s_lock,
	s_unlock,
	ss7_over_sigtran_vprintf,
	s_vprintf,
	s_abort
};

const QSYSOP *os = &__os;

static	void	s_walltime( QTIME *now )
{
	struct timeval	T;

	gettimeofday( &T, 0 );
	now->s = T.tv_sec;
	now->us = T.tv_usec;
}

const QWAIT __waitstruct = {
	0,
	0,
	0,
	s_walltime
};


const QWAIT *waitstruct = &__waitstruct;


void sl_event_init (void)
{
    int i;

    ylInit(&sl_event_free_list);
    ylInit(&sl_event_list);

    event_pool_global = malloc (sizeof (sl_event) * CSPL_EVENT_MAX);
    if (!event_pool_global)
	{
	printf ("Memory allocation for event pool failed\n");
	ss7_over_sigtran_err_log (0,"Memory allocation for event pool failed\n");
	exit(21);
	}

    for (i = 0; i < CSPL_EVENT_MAX; i++)
	ylPushTail (&sl_event_free_list, &event_pool_global[i].list_entry);
}

void sl_event_destroy(void)
{
    free(event_pool_global);
}

void *sl_event_register (int fd, unsigned char (*callback) (int fd))
{
    sl_event *event;
    YLNODE *pNode;

    if (ylEmpty (&sl_event_free_list)) {
	qvLog (QVLOG_MAJOR, "Event free list empty\n");
	return 0;
    }

    pNode = ylPopHead(&sl_event_free_list);
    event = YMEMBEROF(sl_event, list_entry, pNode);
	if(!event)
	  return 0;

    event->fd = fd;
    event->callback = callback;
    ylPushTail (&sl_event_list, &event->list_entry);
    return event;
}

void sl_event_deregister (void *eid)
{
    sl_event *event = eid;
    ylDelete (&sl_event_list, &event->list_entry);
    ylPushTail(&sl_event_free_list, &event->list_entry);
}

int sl_log_level_get()
{
	sl_module_ctxt *pCtxt;
	pCtxt = (sl_module_ctxt *)qvThisContext();
	if(pCtxt)
		return pCtxt->logLevel;
	else 
		return SL_LOG_INFO;
}

void sl_log (unsigned int level, const char *format, ...)
{
	va_list A;
	unsigned int logLevel=SL_LOG_OFF; /*UMR fix*/
    const char* name = "unknown";
    char *data=NULL; /*UMR fix*/
#ifdef SYSLOG_SUPPORT
    unsigned char buf[2048];
#endif

    if (systemLogFlag==0)
        return;


	logLevel = sl_log_level_get();

	if ((logLevel == SL_LOG_OFF) || (level > logLevel)) {
		return;
	}

    if ((data = qvThisContext ()))
        name = data + sizeof (unsigned int);

	va_start( A, format );
#ifndef SYSLOG_SUPPORT
    fprintf (stdout, "%s[%s]: ", name, 
                  sl_log_names [(level>SL_LOG_OFF)?logLevel:level]);
	vfprintf ( (FILE *stdout, format, A ));
#else
    vsprintf ((char *)buf, format, A);
    syslog (DEFAULT_SYSLOG_PRIO, "%s[%s]: %s", name, 
                  sl_log_names [(level>SL_LOG_OFF)?logLevel:level], buf);
#endif
	va_end( A );
}

void sl_log_level_set(QMODULE mid, unsigned int level)
{
	if( !mid )
	{
		if(level == SL_LOG_OFF)
			qvLogLevel(QVLOG_NONE);
		else
			qvLogLevel(level + 1);
	}
	else 
	{
		sl_module_ctxt *pCtxt = (sl_module_ctxt *)qvModuleContext(mid);
		pCtxt->logLevel = level;
	}
}

int ss7_over_sigtran_log_print(const char *format, ...)
{
	va_list ap;
	char temp_hbuf[4096];
#ifdef SYSLOG_SUPPORT
	char buf[2048];
	char *p = buf;
	char *p1;
#endif
    	if (systemLogFlag==0)
        return 1;

	va_start (ap, format);
#ifdef SYSLOG_SUPPORT
    vfprintf (stdout, format, ap);
#else
	memset(temp_hbuf, 0, sizeof(temp_hbuf));
	vsprintf (p, format, ap);
	p1=strchr(format,'\n');
	if(p1== NULL)
	{
			if ( ( strlen(h_buf) + strlen(buf) )  >= 4096 )
				{
						syslog (2, "%s", h_buf);
						memset(h_buf,0,4096);
				}
/*	   strcat(h_buf,p);*/
	   snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, p);
	   snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
	   h_buf[sizeof(h_buf)-1]=0;

	}
	else
	{
		if(p1 == format)
		{
			syslog (DEFAULT_SYSLOG_PRIO, "%s", h_buf);
			memset(h_buf,0,4096);
/*			strcat(h_buf,p+1);	*/
			snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, p+1);
	   		snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
	   		h_buf[sizeof(h_buf)-1]=0;
		}
		else if (p1 == (format+strlen(format)-1))
		{
				if ( ( strlen(h_buf) + strlen(buf) )  >= 4096 )
				{
						syslog (2, "%s", h_buf);
						memset(h_buf,0,4096);
				}
/*			strcat(h_buf,p);*/
			snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, p);
	   		snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
	  		h_buf[sizeof(h_buf)-1]=0;

			syslog (DEFAULT_SYSLOG_PRIO, "%s", h_buf);
			memset(h_buf,0,4096);
		}
		else 
		{
				if ( ( strlen(h_buf) + strlen(buf) )  >= 4096 )
				{
						syslog (2, "%s", h_buf);
						memset(h_buf,0,4096);
				}
/*			strcat(h_buf,p);*/
			snprintf(temp_hbuf, sizeof(temp_hbuf), "%s%s", h_buf, p);
	   		snprintf(h_buf, sizeof(h_buf), "%s", temp_hbuf);
	  		h_buf[sizeof(h_buf)-1]=0;

		}

	}
#endif
	va_end (ap);
	return 0;
}

sl_pool_t sl_pool_create (unsigned int bufsz, unsigned short nbuf)
{
    static int first_request=0;
    sl_pool_t pool = qvMsgPoolCreate (bufsz, nbuf);
    if (!pool)
        return 0;
    if(!first_request)
    {
	 first_request=1;
	 pool_list.npools = 0;
    }
    if (pool_list.npools == SL_MAX_POOLS)
        qvPanic ("Error: Number of pools more than %d. Pool extension would fail\n", SL_MAX_POOLS);
    pool_list.pool_id[pool_list.npools] = pool;
    pool_list.size[pool_list.npools] = bufsz;
    pool_list.step[pool_list.npools++] = nbuf;
    return pool;
}

extern struct poolshow_t poolshow[];
int last_exception;

void sl_get_buf_status(void *poolid, unsigned short *nf, unsigned short *no)
{
	unsigned int total = qvMsgPoolSize((QMPOOL)poolid, (unsigned int *)no);
	*nf = total - (*no);
}

static void sl_buf_chk_exception(void)
{
    double buf_percent;
    int i;
    int exception = 2;
    unsigned short nf = 0;
    unsigned short no = 0;
    unsigned int num_free_buf = 0;
    unsigned int num_occp_buf = 0;
    
    for( i=0; poolshow[i].name; i++ ) {
            if( *(poolshow[i].pool) == 0 ) {
                continue;
            }
                                sl_get_buf_status(*poolshow[i].pool, &nf, &no);
                num_free_buf += nf;
                num_occp_buf += no;
                                nf=no=0;
      }

	  if (nm_autorefresh_flag)

    buf_percent = (num_occp_buf * 100)/(num_occp_buf + num_free_buf);
	
	if (buf_percent <= 50 )
	{
		exception = SL_BUF_FREE_MORE_50;
	}
	else if (buf_percent == 100 )
	{
		exception = SL_BUF_NO_FREE_LEFT;
	}
	else if (buf_percent >= 75 )
	{
		exception = SL_BUF_FREE_LESS_25;
	}
	else if (buf_percent >= 50 )
	{
		exception = SL_BUF_FREE_LESS_50;
	}
	
	if(last_exception!=exception)
	{
	}

	last_exception=exception;
    return;
}

void *sl_buf_alloc (sl_pool_t poolid)
{
    int i, nbuf = 0;
    void *p = qvMsgAllocFromPool(poolid);
    /* static int count; */
	if (p)
	{
#if 0
		if(count==100)	
		{
		sl_buf_chk_exception ();
		count=0;
		}
		count++;
#endif
	return p;
	}
    for (i=0; i < pool_list.npools; i++)
        if (poolid == pool_list.pool_id[i])
        {
            nbuf = pool_list.step[i];
            break;
        }
    if (!nbuf)
    {
        qvLog (QVLOG_MAJOR, "Pool [%x] not found in pool list. Could not be extended.\n", poolid);
        return 0;
    }
    if (qvMsgPoolExtend (poolid, nbuf))
    {
        qvLog (QVLOG_INFO, "Pool [%x] extended with [%d] buffers\n", poolid, nbuf);
		sl_buf_chk_exception ();	
        return qvMsgAllocFromPool (poolid);
    }
    
    qvLog (QVLOG_MAJOR, "Pool [%x] extension failed\n", poolid, nbuf);
    return 0;
}
#if 0
void sl_buf_free (void *buf)
{
	qvMsgFree(buf);
}
#endif

void sl_mq_send (sl_module_t mid, unsigned int arg, void *buf)
{
	qvSend(mid, arg, buf);
}

sl_module_t sl_module_register (const char *name,
				void *(*init) (void *arg),
				int (*msg_handler) (void *buf,
						     void *context),
				void (*timer_handler) (QTIMER tid, void *data, void *context),
				void *init_arg)
{
	QMANIFEST *manifest;
	manifest= (QMANIFEST *)qvSysMalloc( sizeof(QMANIFEST) );
	bzero(manifest, sizeof(QMANIFEST));
	manifest->handler.message = msg_handler;
	manifest->handler.timer = timer_handler;
	manifest->init.late = init;

	if(!init_arg)
	{
        sl_module_ctxt *pCtxt;
        int length = (strlen (name)>30)?30:strlen(name);
		init_arg = qvSysMalloc (sizeof (sl_module_ctxt));
        pCtxt = (sl_module_ctxt*)init_arg;
/*        strncpy (pCtxt->name, name, length);*/
	   snprintf(pCtxt->name, sizeof(pCtxt->name), "%.*s", length, name);
	   h_buf[sizeof(h_buf)-1]=0;

        pCtxt->name[length] = 0;
	}
	return qvRegister( 0, name, 0, manifest, init_arg);
}

sl_timer_t sl_timer_start (sl_time_val *timeo, void *data)
{
	return qvTimerStart(timeo, data, 0);
}

sl_timer_t sl_flow_timer_start (sl_time_val *timeo, void *data)
{
	return qvTimerStart(timeo, data, 1);
}

void sl_timer_cancel (sl_timer_t tid)
{
    if(qvTimerRunning(tid)) {
        qvTimerStop(tid, 0);
    }
}

void *sl_timer_get_data (sl_timer_t tid)
{
	return qvTimerData(tid);
}


sl_msg_t *sl_msg_alloc (unsigned int size __attribute__((unused)))
{
    sl_msg_t *msg = sl_buf_alloc (gtp_pool);

	if(!msg) {
	  qvLog (QVLOG_CRITICAL, "sl_buf_alloc failed for function sl_msg_alloc.\n");
	  return 0;
	}
    memset (msg, 0, 2048);
    msg->data = msg->edata = msg->base;
    msg->size = 2048 - sizeof (sl_msg_t);

    return msg;
}

void sl_msg_free (sl_msg_t *msg)
{
    sl_msg_t *p;

    while ((p = msg)) {
	msg = msg->next;
	sl_buf_free (p);
    }
}


void sl_pool_show (void *poolid, char *format, char *name)
{
    int index;
    unsigned int alloc, nbuf;
    QMPOOL pool = (QMPOOL)poolid;
    if (pool)
    {
        for (index=0; index < pool_list.npools ; index++)
            if (pool_list.pool_id [index] == poolid)
                break;
        if (index == pool_list.npools)
        {
            qvLog (QVLOG_MAJOR, "Pool [%s] not created while bufshow is called.\n", name);
            return;
        }
        nbuf = qvMsgPoolSize (pool, &alloc);
        /*errprintf (format, pool_list.size[index], nbuf, alloc, nbuf-alloc, name);*/
    }
    return;
}

void sl_pool_trace( void *poolid )
{
}

void sl_note_send (sl_module_t mid, unsigned int note)
{
	extern sl_pool_t note_pool;
	void *buf = sl_buf_alloc(note_pool);
	if(buf)
	{
		qvSend(mid, note, buf);
	}
}

void *sl_alloc(unsigned int size)
{	
    return qvAlloc(size,NULL);
}

void sl_free(void *p)
{
    qvFree(p);
}


void print_pool_in_file(void *poolid, char *format, char *name, FILE *fd)
{
    int index;
    unsigned int alloc, nbuf;
    QMPOOL pool = (QMPOOL)poolid;
    if (pool)
    {
        for (index=0; index < pool_list.npools ; index++)
            if (pool_list.pool_id [index] == poolid)
                break;

        if (index == pool_list.npools)
        {
            return;
        }

        nbuf = qvMsgPoolSize (pool, &alloc);
        fprintf (fd,format, pool_list.size[index], nbuf, alloc, nbuf-alloc, name)
;
    }
    return;
}
void ss7_over_sigtran_err_log(unsigned long tlli, char *fmt, ...)
{
    va_list A;

    va_start (A, fmt);
    fprintf (stdout, "%08x %08x ", time (0), tlli);
    vfprintf (stdout, fmt, A);
    /*vfprintf (stdout, "%s", "\n");*/
    va_end (A);
    return ;
}

