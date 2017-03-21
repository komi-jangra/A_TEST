/***************************************************************************
**  FILE NAME:
**      sc_smapi.h
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
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_SMAPI_H_
#define _SC_SMAPI_H_

#include<string.h>
#include "sc_s7gl.h"
#include "sc_api.h"

#define SS7_SM_API_MIN_LEN   8

/* Category PROV */

/* commands */
/* Category CTRL */
#define SCCP_CONF_TIMER          1
#define SCCP_LOCAL_CONG_IND      2
#define SCCP_SET_SEG_LEN         3

/* Category STATS */

/* commands as defined in s7_sm.h */

/* Category ERROR */

/* event levels */

#define SCCP_NO_EVENT_RPT	SS7_NO_EVENT_RPT
#define SCCP_EVENT_RPT		SS7_EVENT_RPT
/* common defines for event-alarms */



/* objects for event alarms */
#define SCCP_SM_OBJECT_SP       0x00
#define SCCP_SM_OBJECT_SS       0x01
#define SCCP_SM_OBJECT_CONN     0x02
#define SCCP_SM_ALL_OBJECTS     0x03


/* Category DISPLAY */

/* commands */

#define SCCP_SM_DISPLAY_SP      1
#define SCCP_SM_DISPLAY_SS      2


#define SCCP_SM_DISPLAY_SP_LEN    (SS7_SM_API_MIN_LEN + \
                                   SCCP_SM_SP_ID_LEN)

#define SCCP_SM_DISPLAY_SS_LEN    (SS7_SM_API_MIN_LEN + \
                                   SCCP_SM_SS_ID_LEN)

#define SCCP_SM_PROV_REPL_BUF_LEN      (SS7_SM_API_MIN_LEN + \
                                        1)

#define SCCP_SM_PROV_REPL_NUM_ELEM (SS7_SM_API_MIN_LEN + \
                                    1)

#define DEL_SS_OF_SP_MASK  0x01
#define DEL_SP_AS_CSP_MASK 0x01

#define DEL_SS_AS_CSS_MASK  0x01

#define GET_BYTE_CODED_SS_ID(p_byte)    (GET_4_BYTE_LE(p_byte))
#define GET_BYTE_CODED_SP_ID(p_byte)    (GET_4_BYTE_LE(p_byte))
#define GET_BYTE_CODED_SM_PC(p_byte)    (GET_4_BYTE_LE(p_byte))


#define SCCP_SM_STAT_REPL_BUF_LEN      (SS7_SM_API_MIN_NO_ELEM + \
                                        1)

#define SCCP_SM_STAT_REPL_NUM_ELEM     (SS7_SM_API_MIN_NO_ELEM + \
                                        1)

#define SM_COMMAND_STAT_TYPE_OFFSET    (SS7_SM_API_MIN_LEN)

#endif /* _SC_SMAPI_H_ */
