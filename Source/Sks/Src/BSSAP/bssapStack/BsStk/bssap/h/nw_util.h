/*******************************************************************************
**      FILE NAME:
**          nw_util.h
**
**      DESCRIPTION:
**              This file contains the definitions and prototypes for socket utilities required 
**							by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
#ifndef __NW_UTIL_H__
#define	__NW_UTIL_H__

#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define SOC_MGR_INVALID_SOC_FD		(-1)
#define SS7_API_HEADER_LEN      5 
#define SS7_BSSAP_APP_API_HEADER_LEN      28 
#define MAX_KEY_SIZE  128
#define MAX_BUFF_SIZE 2048
#define BSSAP_CONF_FILENAME   "bssap_ph_conf"


int  soc_mgr_send_api
( int sockfd,
	const unsigned char		*p_hdr_buf,
    const unsigned char       *p_api_buf,
    unsigned int        api_len);


int soc_mgr_setup_client
(   char    *serv_ipstr,
    unsigned short serv_tcpport);


int soc_mgr_nw_read
(   int             sockfd,
    unsigned char   *ptr,
    int             nbytes);

int soc_mgr_nw_write
(   int             sockfd,
    const unsigned char   *ptr,
    int             nbytes);


int sigtran_get_conf_file (char *filename);
int cd_get_param (char *filename, char *key_string, char *return_string);


#endif
 /* __NW_UTIL_H__ */
