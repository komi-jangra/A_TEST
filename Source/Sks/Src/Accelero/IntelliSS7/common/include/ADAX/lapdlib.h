/*
 * Copyright (c) 1984-1997 ADAX, Inc.
 *   Use of this code subject to your agreement with ADAX, Inc.
 *
 *  "@(#)lapdlib.h	1.7 delta 03/09/25\n";
 *
 * lapdlib.h
 * 
 * lapdlib is the application programmer's interface library between the 
 * Adax LAPD module and the user application.
 */
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
#include "include/sys/dlpi.h"
#else
#include "include/sys/lihdr.h"
#endif

#ifndef ROUTINE
#define ROUTINE
#endif

/* lapdlib address struct */
typedef struct lapdaddr_t_s {
	unsigned int cmdaddr;	/*addr of connection.  Address 
	                     	 *is the line form of the command address */
	unsigned int resaddr;	/*addr of connection.  Address 
	                      	 *is the line form of the responce address */
	unsigned int EFaddr;    /* LAPV5-EF address */
} lapdaddr_t;

/* FRMR fields for con_frmr */
struct frmr_info {
	unsigned short control;	/* control field of FRMR'd frame */
	unsigned short cmd_res;	/* command/response field of FRMR'd frame */
	unsigned short cause;	/* bit cause code. see CCITT Rec. X.25 */
};

/* struct to hold lapd parameters for con_config() 
 * all timers are measured in milliseconds */
struct lapd_param {
unsigned short t1;	/* t200 in lapd: re-xmit timer. default = 3000 msec. */
unsigned short t3;	/* t203 in lapd: idle line timer. default=30000 msec.*/
unsigned short n2;	/* n200 in lapd: Max num. retransmitions. default = 3 */
unsigned short n1_bytes;/* n201 in lapd: Max octets in I frame. default = 260 */
unsigned short k;	/* window size. default = 7 */
unsigned short n202;	/* Max. transmissions of TEI ident req. default = 3 */
unsigned short t201;	/* TEI ident check re-xmit timer. default = t200 */
unsigned short t202;	/* TEI ident req. re-xmit timer. default = 2000 msec. */
};

/* frame statistics and counts */
struct fr_stats {
	int niframes;		/* number of Iframes received */
	int oiframes;		/* number of Iframes sent */
	int ntimeouts;		/* number of T1/T200 timeouts */
	int nrejs;		/* number of REJs received */
	int orejs;		/* number of REJs sent */
	int nfrmrs;		/* number of FRMRs received */
	int ofrmrs;		/* number of FRMRs sent */
	int ncrcs;		/* number of CRC errors ZZZ needed? */
	int naborts;		/* number of aborted frames */
	int nlinkup;		/* number of LINKUPs for this connection */
	int nlinkdown;		/* number of LINKDOWNs for this connection */
};

/* structs used by functions which have to send or recieve DLPI messages */
typedef struct lapd_unitdata_req {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_unitdata_req_t dl_udata;
#else
struct DL_unitdata_req dl_udata;
#endif
lapdaddr_t addr;
} lapd_unitdata_req_t;

typedef struct lapd_unitdata_ind {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_unitdata_ind_t dl_udata;
#else
struct DL_unitdata_ind dl_udata;
#endif
lapdaddr_t addr;
} lapd_unitdata_ind_t;

typedef struct lapd_bind_req {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_bind_req_t dl_bind;
#else
struct DL_bind_req dl_bind;
#endif
lapdaddr_t addr;
unsigned short addr_size;	/* size of address field 1,2,3,4 */
unsigned short modulo;		/* modulo of the connection (8 or 128) */
} lapd_bind_req_t;

typedef struct lapd_bind_ack {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_bind_ack_t dl_bndack;
#else
struct DL_bind_ack dl_bndack;
#endif
lapdaddr_t addr;
} lapd_bind_ack_t;

typedef struct lapd_unbind_req {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_unbind_req_t dl_unbind;
#else
struct DL_unbind_req dl_unbind;
#endif
lapdaddr_t addr;
} lapd_unbind_req_t;

typedef struct lapd_info_req {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_info_req_t dl_info;
#else
struct DL_info_req dl_info;
#endif
lapdaddr_t addr;
} lapd_info_req_t;

typedef struct lapd_info_ack {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_info_ack_t dl_infoack;
#else
struct DL_info_ack dl_infoack;
#endif
lapdaddr_t addr;
} lapd_info_ack_t;

typedef struct lapd_error_ack {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_error_ack_t dl_errack;
#else
struct DL_error_ack dl_errack;
#endif
lapdaddr_t addr;
} lapd_error_ack_t;

typedef struct lapd_ok_ack {
#if defined (SUN_SOL) || defined (HPUX) || defined (LINUX_LIS) || defined (AIX) || defined (VXWORKS)
dl_ok_ack_t dl_okack;
#else
struct DL_ok_ack dl_okack;
#endif
lapdaddr_t addr;
} lapd_ok_ack_t;

typedef struct lapd_linkup_ind {
unsigned int dlp_linkup;	/* always DLP_LINKUP */
lapdaddr_t addr;
} lapd_linkup_ind_t;

typedef struct lapd_linkdown_ind {
unsigned int dlp_linkdown;	/* always DLP_LINKDOWN */
unsigned int cause;		/* linkdown cause code */
lapdaddr_t addr;
} lapd_linkdown_ind_t;

typedef struct lapd_frmr_ind {
unsigned int dlp_frmrind;	/* always DLP_FRMRIND */
lapdaddr_t addr;
} lapd_frmr_ind_t;

/* ioctls */
#define LIO_CONFIG 256
#define LIO_QUEUE 257
#define LIO_PARAM 258
#define LIO_START 259
#define LIO_STOP 260
#define LIO_CONREQ 261
#define LIO_INIT 262
#define LIO_TRANS 263
#define LIO_FRMR 264
#define LIO_DISC 265
#define LIO_RSTREQ 266
#define LIO_XIDREQ 267
#define LIO_STAT 270
#define LIO_ZERO 271
#define LIO_GPARAM 272		/* get lapd params */
#define LIO_DEBUG 273		/* turn on debugging */
#define LIO_FRMCHECK 274	/* toggle flag for tx frame length checking */
#define LIO_STROPTS 275
#define LIO_LNKSTATE 276	/* return current frm_state 
				 * (FRM_IDLE, FRM_DOWN, FRM_INFOTR) */
#define LIO_NOSABMS 277		/* turns on/off SABM suppression */

/* --------------------- now DLP messages */

#define DLP_LINKUP 0		/* link is up after SABM==UA */
#define DLP_LINKDOWN 1		/* link is down: DISC or T3 timeout */
#define DLP_FRMRIND 2		/* FRMR has been received */
#define DLP_SHTDOWN 0xf0000001	/* channel has been shut down due to overrun 
				 * interrupt queue or high error rate */
#define DLP_UIDATA_REQ  0xf0000007  /* unnumbered information UI user request */
#define DLP_UIDATA_IND  0xf0000008  /* unnumbered information UI net inbound */
#define DLP_XIDATA_REQ  0xf0000029  /* unnumbered information UI user request */
#define DLP_XIDATA_IND  0xf000002A  /* unnumbered information UI net inbound */
#define DLP_XIDATA_RES  0xf000002B  /* unnumbered information UI user response*/
#define DLP_XIDATA_CON  0xf000002C  /* unnumbered information UI net response */


/* con_supermux() mode definitions */
#define LAPB_MODE 0
#define LAPD_MODE 1
#define LAPD_V5EF_MODE 2
#define LAPV5_V5EF_MODE 3

/* linkdown cause codes */
#define LINKDOWN_TIMEOUT 0
#define LINKDOWN_DM 1
#define LINKDOWN_DISC 2
#define LINKDOWN_FRMR 3
#define LINKDOWN_SABM_TIMEOUT 4

/* frame states: primary (frm_state) */
#define FRM_IDLE 0	/* we are down and not trying */
#define FRM_DOWN 1	/* we are down and sending SABM/Es */
#define FRM_INFOTR 2	/* we are up. */

/* lapdlib functions */
ROUTINE int con_bind();
ROUTINE int con_unbind();
ROUTINE int con_start();
ROUTINE int con_stop();
ROUTINE int con_config();
ROUTINE int con_getmsg();
ROUTINE int con_putmsg();
ROUTINE int con_uidata();
ROUTINE int con_query();
ROUTINE int con_frmr();
ROUTINE int con_supermux();
ROUTINE int con_disc();
ROUTINE int con_stat();
ROUTINE int con_zero();
ROUTINE int ln2addr();
ROUTINE void addr2ln();
ROUTINE int ln2v5addr();
ROUTINE void v5addr2ln();
