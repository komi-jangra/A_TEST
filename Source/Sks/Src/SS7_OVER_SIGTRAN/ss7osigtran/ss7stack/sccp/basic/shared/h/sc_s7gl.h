/***************************************************************************
**  FILE NAME:
**      sc_s7gl.h
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


/* This file contains the header files of the SS7 stack which are needed
   by SCCP */

#ifndef _SC_S7GL_H_
#define _SC_S7GL_H_

#ifndef SCCP
#define SCCP
#endif

#define DEFAULT_NW_ID  0
#define MAX_SCCP_INSTANCES 255
#define SST_RUNNING  1
#define SST_NOT_RUNNING  0
#define SS_ALLOWED 1
#define SS_PROHIBITED 0
#define SP_ALLOWED 1
#define SP_PROHIBITED 0

#include "s7_typ.h"
#include "s7_def.h"
#include "s7_error.h"
#include "s7_api.h"
#include "s7_stdbg.h"
#include "s7_sm.h"
#include "s7_sterr.h"
#include "s7_stst.h"

#include "s7_prot.h"
#include "s7_stpro.h"

#ifdef ANSI_PROTO
#define _ARGS_(x)	x
#else
#define _ARGS_(x)	()
#endif

#endif /* _SC_S7GL_H_ */
