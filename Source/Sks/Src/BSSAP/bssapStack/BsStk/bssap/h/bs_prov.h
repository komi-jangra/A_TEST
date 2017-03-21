/*******************************************************************************
**      FILE NAME:
**          bs_prov.h
**
**      DESCRIPTION:
**              This files defines the macros common definitions to be used by
**              by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef _BS_PROV_H_
#define _BS_PROV_H_

#include "bs_s7gl.h"

typedef struct
{
	U8bit standard;
	U16bit seg_size;       /* Segmentation parameter */ 
	U8bit nw_type;         /* Broadband or Narrowband */
} sc_opt_t;

extern sc_opt_t sc_opt;

#ifdef SCCP_BROADBAND
#define SCCP_DEFAULT_SEG_SIZE 2560
#else
#define SCCP_DEFAULT_SEG_SIZE 160 
#endif

#define SCCP_MAX_XUDT_SEG_SIZE 254
#define SCCP_MAX_CO_SEG_SIZE 255  
 
#endif /* _BS_PROV_H_ */

