/*******************************************************************************
**      FILE NAME:
**          bssap.h
**
**      DESCRIPTION:
**              Defines required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef	____BSSAP_H___
#define	____BSSAP_H___

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>

#include	<netinet/in.h>
#define LOG_PRINT(a,b,args...) printf(b,args);
#ifdef SYSLOG_SUPPORT
#include <syslog.h>
#endif

#define DEFAULT_LOG_ID LOG_LOCAL0
#define DEFAULT_SYSLOG_FACILITY  gsn_log_id
#define DEFAULT_SYSLOG_LEVEL     LOG_INFO
#define DEFAULT_SYSLOG_PRIO      (DEFAULT_SYSLOG_FACILITY | DEFAULT_SYSLOG_LEVEL)


#define	EXTRACT(outcast, incast, rshift, mask, x) (outcast(( (incast(x)) >> rshift)&mask))
#define	GETBYTE(x,n)	EXTRACT( (unsigned char), (unsigned long), (8*(n)), 0x000000FF, (x) )
#define	GETWORD(x,n)	EXTRACT( (unsigned short), (unsigned long), (16*(n)), 0x0000FFFF, (x) )

#define	GETNIBBLE(x,n)	EXTRACT( (unsigned char), (unsigned long), (4*(n)), 0x0000000F, (x) )

#define	SETNIBBLE_HI(x,y)	((x)=(((x)&0x0F) | (((y) & 0x0F) << 4)))
#define	SETNIBBLE_LO(x,y)	((x)=(((x)&0xF0) | (((y) & 0x0F))))

#define	GETNIBBLE_HI(x)	(((x) & 0xF0) >> 4)
#define	GETNIBBLE_LO(x)	(((x) & 0x0F))

#define	CLRBIT(x,n)	((x)=( (x) & (~(1 << (n) ) )))
#define	SETBIT(x,n)	((x)=( (x) | ((1 << (n) ) )))
#define	GETBIT(x,n)	(( (x) & ((1 << (n) ) ))?1:0)

#define	panic(d)	(___panic(__LINE__,__FILE__,__FUNCTION__,__PRETTY_FUNCTION__,errno,d), abort())
#define	xperror(d)	___xperror(__LINE__,__FILE__,__FUNCTION__,__PRETTY_FUNCTION__,errno,d)
#define ___panic(__l,__fl,__fn, __pfn,__e,__m)	fprintf(stderr,"PANIC\t%s line %d (%s) %s: %s\n\t[%s]\n", __fl, __l, __fn, __m, strerror(__e), __pfn )
#define ___xperror(__l,__fl,__fn, __pfn,__e,__m)	fprintf(stderr,"ERROR\t%s line %d (%s) %s: %s\n\t[%s]\n", __fl, __l, __fn, __m, strerror(__e), __pfn )

#define ___trace()	fprintf(stderr,"TRACE\t%s line %d (%s)\n\t[%s]\n", __FILE__, __LINE__, __FUNCTION__,__PRETTY_FUNCTION__ )

#define	OFFSETOF(s,f)	((int)( &(((s *)0)->f)))

#define SCCP_OVER_MTP3 (las_bitmap &0x02)

struct poolshow_t {
    char        *name;
    sl_pool_t   *pool;
};

struct lclpoolshow_t {
    char        *name;
    sl_pool_t   *pool;
    
};

typedef struct
{
    unsigned char		global_title_ind;
    unsigned char		translation_type;
    unsigned char		numbering_plan;
    unsigned char		encoding_scheme;
    unsigned char		nature_of_addr_ind;
    unsigned char		num_gt_addr_info_octets;
    unsigned char		gt_addr_info [20];
} gt_info;


#endif /* #ifndef	____BSSAP_H___ */

