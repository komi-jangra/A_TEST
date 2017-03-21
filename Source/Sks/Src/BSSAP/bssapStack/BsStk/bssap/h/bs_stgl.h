/*******************************************************************************
**      FILE NAME:
**          bs_stgl.h
**
**      DESCRIPTION:
**              This files defines the structure of Called & Calling Party used by
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

#ifndef _BS_STGL_H_
#define _BS_STGL_H_

#include "bs_s7gl.h"
#include "bs_api.h"
#include "bs_dbf.h"

#define MAX_GT_LEN 30

#define MAX_GTT_LIST 256

#define MIN_DATA_LEN 1

#define SCCP_TIMER_ID_LEN     1

typedef struct
{
  Boolean pc_ind;
  Boolean ssn_ind;
  U8bit   gti;
  U8bit   rout_ind;
  U32bit  pc;
  U8bit   ssn;
  U8bit   gt_len;
  U8bit   gt[MAX_GT_LEN];
  U8bit   nat_ind;
} sccp_addr_t;

#ifndef __FLAG_FOR_ID_FLAG__
#define __FLAG_FOR_ID_FLAG__
extern  src_id_t sccp_src_id;
extern module_id_t sccp_module_id;
#endif

extern return_t sccp_ret_val;

Boolean sls_assigned; 

#endif /* _BS_STGL_H_ */

