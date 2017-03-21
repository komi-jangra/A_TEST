/*******************************************************************************
**      FILE NAME:
**          bs_s7gl.h
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


/* This file contains the header files of the SS7 stack which are needed
   by SCCP */

#ifndef _BS_S7GL_H_
#define _BS_S7GL_H_

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

#endif /* _BS_S7GL_H_ */
