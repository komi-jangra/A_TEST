/*****************************************************************************

 @(#) $RCSfile: xti_tcp.h,v $ $Name: not supported by cvs2svn $($Revision: 1.1.1.1 $) $Date: 2007-10-08 11:11:34 $

 -----------------------------------------------------------------------------

 Copyright (c) 2001-2004  OpenSS7 Corporation <http://www.openss7.com>
 Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This library is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free
 Software Foundation; either version 2.1 of the License, or (at your option)
 any later version.

 This library is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Lesser Public License for more
 details.

 You should have received a copy of the GNU Lesser General Public License
 along with this library; if not, write to the Free Software Foundation, Inc.,
 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any success regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 -----------------------------------------------------------------------------

 Last Modified $Date: 2007-10-08 11:11:34 $ by $Author: bsccs2 $

 $Log: not supported by cvs2svn $
 Revision 1.1.1.1  2007/10/04 13:24:04  bsccs2
 init tree

 Revision 1.1  2007/09/24 05:48:18  ankur.sharda
 *** empty log message ***

 Revision 1.1.2.1  2004/04/13 12:12:52  brian
 - Rearranged header files.

 *****************************************************************************/

#ifndef _SYS_XTI_TCP_H
#define _SYS_XTI_TCP_H

#ident "@(#) $RCSfile: xti_tcp.h,v $ $Name: not supported by cvs2svn $($Revision: 1.1.1.1 $) Copyright (c) 1997-2004 OpenSS7 Corporation."

/*
 * TCP level
 */
#define T_INET_TCP		6	/* TCP level (same as protocol number) */

/*
 * TCP level Options
 */
#define T_TCP_NODELAY		1	/* don't coalese packets */
#define T_TCP_MAXSEG		2	/* get maximum segment size */
#define T_TCP_KEEPALIVE		3	/* keep connections alive */
#define T_TCP_CORK		4	/* control sending of partial frames */
#define T_TCP_KEEPIDLE		5	/* start keepalives after this period */
#define T_TCP_KEEPINTVL		6	/* invterval between keepalives */
#define T_TCP_KEEPCNT		7	/* number of keepalives before death */
#define T_TCP_SYNCNT		8	/* number of SYN retranmits */
#define T_TCP_LINGER2		9	/* life time of orphaned FIN-WAIT-2 state */
#define T_TCP_DEFER_ACCEPT	10	/* wake up listener only when data arrives */
#define T_TCP_WINDOW_CLAMP	11	/* bound advertised window */
#define T_TCP_INFO		12	/* information about this connection */
#define T_TCP_QUICKACK		13	/* block/reneable quick acks */

#define T_TCP_MSS		536
#define T_TCP_MAXWIN		65525
#define T_TCP_MAX_WINSHIFT	14

/*
 * Structure used with TCP_KEEPALIVE option.
 */
struct t_kpalive {
	t_scalar_t kp_onoff;		/* option on/off */
	t_scalar_t kp_timeout;		/* timeout in minutes */
};

#define T_TCP_CA_Open		0
#define T_TCP_CA_Disorder	1
#define T_TCP_CA_CWR		2
#define T_TCP_CA_Recovery	3
#define T_TCP_CA_Loss		4

#define T_TCPI_OPT_TIMESTAMPS	1
#define T_TCPI_OPT_SACK		2
#define T_TCPI_OPT_WSCALE	4
#define T_TCPI_OPT_ECN		8

struct t_tcp_info {
	unsigned char tcpi_state;
	unsigned char tcpi_ca_state;
	unsigned char tcpi_retransmits;
	unsigned char tcpi_probes;
	unsigned char tcpi_backoff;
	unsigned char tcpi_options;
	unsigned char tcpi_snd_wscale:4, tcpi_rcv_wscale:4;
	t_uscalar_t tcpi_rto;
	t_uscalar_t tcpi_ato;
	t_uscalar_t tcpi_snd_mss;
	t_uscalar_t tcpi_rcv_mss;
	t_uscalar_t tcpi_unacked;
	t_uscalar_t tcpi_sacked;
	t_uscalar_t tcpi_lost;
	t_uscalar_t tcpi_retrans;
	t_uscalar_t tcpi_fackets;
	/*
	   Times. 
	 */
	t_uscalar_t tcpi_last_data_sent;
	t_uscalar_t tcpi_last_ack_sent;	/* Not remembered, sorry. */
	t_uscalar_t tcpi_last_data_recv;
	t_uscalar_t tcpi_last_ack_recv;
	/*
	   Metrics. 
	 */
	t_uscalar_t tcpi_pmtu;
	t_uscalar_t tcpi_rcv_ssthresh;
	t_uscalar_t tcpi_rtt;
	t_uscalar_t tcpi_rttvar;
	t_uscalar_t tcpi_snd_ssthresh;
	t_uscalar_t tcpi_snd_cwnd;
	t_uscalar_t tcpi_advmss;
	t_uscalar_t tcpi_reordering;
};

#endif				/* _SYS_XTI_TCP_H */

