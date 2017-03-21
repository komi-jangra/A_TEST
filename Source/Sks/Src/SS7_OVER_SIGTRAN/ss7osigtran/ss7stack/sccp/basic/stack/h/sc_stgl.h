/***************************************************************************
**  FILE NAME:
**      sc_stgl.h
**
****************************************************************************
**
**  FUNCTION:
**      all c files in the stack directory include this file
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  12May'98 Sriganesh. Kini   -----  Original
**  22Jul'02 Suyash Tripathi   -----  SPR # 9302
**  21oct'03 Ganesh Kumar	      SPR # 12551
**  17May'04 Ganesh Kumar	      SPR # 13444
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/


#ifndef _SC_STGL_H_
#define _SC_STGL_H_

#include "sc_s7gl.h"
#include "sc_cdef.h"

#include "sc_error.h"
#include "sc_api.h"
#include "sc_dbf.h"

#define MAX_GT_LEN 30

#define MAX_GTT_LIST 256

/* SPR 12551 FIX Start */
#define MIN_DATA_LEN 1
/* SPR 12551 FIX End */

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

typedef struct
{
  pc_t    opc;
  U8bit   nw_id;
} sccp_nsdu_org_t;


#ifdef DISTRIBUTED_SCCP
typedef U8bit dsccp_instance_id_t;
#define DSCCP_DATA_OFFSET_IN_MATE_API 7
#define DSCCP_COMMAND_OFFSET_IN_MATE_API 6
#endif

/* SPR 9302 - Fix Start */
#ifndef __FLAG_FOR_ID_FLAG__
#define __FLAG_FOR_ID_FLAG__
/* SPR 9302 - Fix End   */
extern  src_id_t sccp_src_id;
extern module_id_t sccp_module_id;
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

extern return_t sccp_ret_val;

void sccp_sendto_rm
  _ARGS_ ((U8bit * p_api));/* Added by Amaresh */

Boolean sls_assigned; /* SPR #13444 FIX */

#ifdef SCCP_INCLUDE_CO_SERVICE
#include "sc_ccb.h"
#endif

#include "sc_debug.h"
#include "sc_stats.h"
#include "sc_errh.h"

#include "sc_dbf.h"
#include "sc_dbfm.h"
#include "sc_prov.h"
#include "sc_timer.h"
#include "sc_mgst.h"
#include "sc_msgst.h"
#include "sc_redn.h"
#include "sc_portf.h"

#include "sc_shpro.h"
#include "sc_stpro.h"

#ifdef SCCP_INCLUDE_CO_SERVICE
#include "sc_copro.h"
#endif

#ifdef DISTRIBUTED_SCCP
dsccp_class1_buff_node * list_head;
dsccp_class1_buff_node * list_tail;
#endif

typedef struct t_gt_list
{
  U8bit gt_len;
  U8bit input[MAX_GT_LEN];
  U8bit output[MAX_GT_LEN];
  U32bit pc;
  U8bit ssn;
  U8bit rout_ind;
}t_gt_list;




#endif /* _SC_STGL_H_ */

