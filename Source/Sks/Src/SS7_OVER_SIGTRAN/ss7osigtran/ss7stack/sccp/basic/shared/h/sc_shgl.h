/***************************************************************************
**  FILE NAME:
**      sc_shgl.h
**
****************************************************************************
**
**  FUNCTION:
**      
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  12May'98 Sriganesh. Kini   -----  Original
**  22Jul'02 Suyash Tripathi   -----  SPR # 9302
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_SHGL_H_
#define _SC_SHGL_H_

#include "sc_s7gl.h"

#include "sc_error.h"
#include "sc_api.h"

/* SPR 9302 - Fix Start */
#ifndef __FLAG_FOR_ID_FLAG__
#define __FLAG_FOR_ID_FLAG__
/* SPR 9302 - Fix End   */
extern src_id_t sccp_src_id;
extern module_id_t sccp_module_id;
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

#include "sc_debug.h"
#include "sc_smapi.h"

#include "sc_shpro.h"
#include "sc_ver.h"

#endif /* _SC_SHGL_H_ */
