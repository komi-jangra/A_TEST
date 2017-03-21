
/* Program generated by Cbasic 3.0.0.0.2032 */
#define XSCT_CBASIC

#define C_TRANSLATOR_2_6
#define XENABLE_VERSION_CHECK

#include "scttypes.h"
#include "U2ExtraOps.h"
#include "U2ctypes.h"
#include "SYSInclude.h"
#include "DBSInclude.h"
#include "CELLHInclude.h"
#include "Interfaces.h"
#include "CellHandler.h"
#ifdef XUSE_SIGNAL_NUMBERS
#include "System_CellHandler.hs"
#endif
XSYSTEMVARS
#ifdef XCTRACE
static char  xFileName[] = "System_CellHandler.c";
#endif

/*************************************************************************
**                SECTION Types and Forward references                  **
*************************************************************************/

/*****
* BLOCK INST System_CellHandler
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#U1VEEEBJiEEEXmuPlLESm2EE|pos(1,8)")
******/
extern XCONST struct xBlockIdStruct yBloR_z_System_CellHandler;
extern XCONST xIdNode yBloP_z_System_CellHandler[];

/*****
* GATE pPort
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#fFIEEEBJiEEE3L8PlLESm2EE|pos(1,14)")
******/
#ifndef XOPTCHAN
extern XCONST xIdNode yChaO_z0_pPort[];
extern XCONST xIdNode yChaOR_z0_pPort[];
extern XCONST struct xChannelIdStruct yChaR_z0_pPort;
extern XCONST struct xChannelIdStruct yChaRR_z0_pPort;
#define yChaN_z0_pPort  (&yChaR_z0_pPort)
#endif

/*****
* SIGNALROUTE route
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#ZecSEEbLAEEEqVJplLxXVh2E|pos(1,21)")
******/
#ifndef XOPTCHAN
extern XCONST xIdNode yChaO_z1_route[];
extern XCONST xIdNode yChaOR_z1_route[];
extern XCONST struct xChannelIdStruct yChaR_z1_route;
extern XCONST struct xChannelIdStruct yChaRR_z1_route;
#define yChaN_z1_route  (&yChaR_z1_route)
#endif

/*****
* SIGNALROUTE @implicit_connector_pPort_pPort_0
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#@NO@GUID|pos(1,21)")
******/
#ifndef XOPTCHAN
extern XCONST xIdNode yChaO_z2_implicit_connector_pPort_pPort_0[];
extern XCONST xIdNode yChaOR_z2_implicit_connector_pPort_pPort_0[];
extern XCONST struct xChannelIdStruct yChaR_z2_implicit_connector_pPort_pPort_0;
extern XCONST struct xChannelIdStruct yChaRR_z2_implicit_connector_pPort_pPort_0;
#define yChaN_z2_implicit_connector_pPort_pPort_0  (&yChaR_z2_implicit_connector_pPort_pPort_0)
#endif

/*****
* PROCESS INST cHandler
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#EZVEEEBJiEEETsuPlLESm2EE|pos(1,17)")
******/
extern XCONST struct xPrsIdStruct yPrsR_z3_cHandler;
#define yPrsN_z3_cHandler  (&yPrsR_z3_cHandler)
#ifndef XOPTCHAN
extern XCONST xIdNode yPrsO_z3_cHandler[];
#endif

/*****
* GATE pPort
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler/PROCESS cHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#xa-EEEKqLEEEOHDZlLESm2EE|pos(1,18)")
******/
#ifndef XOPTCHAN
extern XCONST xIdNode yChaO_z30_pPort[];
extern XCONST xIdNode yChaOR_z30_pPort[];
extern XCONST struct xChannelIdStruct yChaR_z30_pPort;
extern XCONST struct xChannelIdStruct yChaRR_z30_pPort;
#define yChaN_z30_pPort  (&yChaR_z30_pPort)
#endif

/*****
* PROCESS INST @part__@implicit_process_0
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#uTKLEEKqLEEEHjralLESm2EE|pos(1,17)")
******/
extern XCONST struct xPrsIdStruct yPrsR_z4_part__implicit_process_0;
#define yPrsN_z4_part__implicit_process_0  (&yPrsR_z4_part__implicit_process_0)
#ifndef XOPTCHAN
extern XCONST xIdNode yPrsO_z4_part__implicit_process_0[];
#endif

/*****
* GATE pPort
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler
*     /PROCESS @part__@implicit_process_0>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#fFIEEEBJiEEE3L8PlLESm2EE|pos(1,18)")
******/
#ifndef XOPTCHAN
extern XCONST xIdNode yChaO_z40_pPort[];
extern XCONST xIdNode yChaOR_z40_pPort[];
extern XCONST struct xChannelIdStruct yChaR_z40_pPort;
extern XCONST struct xChannelIdStruct yChaRR_z40_pPort;
#define yChaN_z40_pPort  (&yChaR_z40_pPort)
#endif

/*************************************************************************
**                  SECTION Variables and Functions                     **
*************************************************************************/

/*****
* ENV
******/
#ifndef XMULTIPLESYSTEMS
#ifndef XOPTCHAN
xIdNode yEnvO_env[] = {(xIdNode)&yChaR_z0_pPort, (xIdNode)0  XTRACHANNELLIST};
#endif
#endif

/*****
* BLOCK INST System_CellHandler
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#U1VEEEBJiEEEXmuPlLESm2EE|pos(1,8)")
******/
XCONST xIdNode yBloP_z_System_CellHandler[] = {xOptChanZ((xIdNode)&yChaR_z1_route),
  xOptChanZ((xIdNode)&yChaR_z2_implicit_connector_pPort_pPort_0),
  (xIdNode)&yPrsR_z3_cHandler, (xIdNode)&yPrsR_z4_part__implicit_process_0,
  xOptChanZ((xIdNode)&yChaRR_z0_pPort)};
static struct xBlockStruct yBloA_z_System_CellHandler = {
  &yBloA_z_System_CellHandler, &yBloA_z_System_CellHandler,
  (xBlockNode)&yBloR_z_System_CellHandler xNrInst(0), -1};
XCONST struct xBlockIdStruct yBloR_z_System_CellHandler = {xBlockEC ,
  (xIdNode)0, (xIdNode)0, (xIdNode)&xSymbolTableIdRec,
  "System_CellHandler" xIdNumber(0) XCOMMON_EXTRAS,
  &yBloR_z_CellHandler_Z0_System_CellHandler, yBloP_z_System_CellHandler,
  (xPrdIdNode *)0, (xViewListRec *)0, (xViewIndexRec *)0 xNrInst(1), 1,
  &yBloA_z_System_CellHandler, &yPrsR_z4_part__implicit_process_0 xTrace(-1)
  xMSCETrace(-1) xGRTrace(-1) xMSCETrace(0) XBLO_EXTRAS};

/*****
* GATE pPort
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#fFIEEEBJiEEE3L8PlLESm2EE|pos(1,14)")
******/
#ifndef XOPTCHAN
static XCONST XSIGTYPE yChaS_z0_pPort[] =
  {SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_AVAIL,
  &ySigR_z_Interfaces_S0_OAMS_TRXH_CELLH_BCCH_AVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_UNAVAIL,
  &ySigR_z_Interfaces_S1_OAMS_TRXH_CELLH_BCCH_UNAVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_SEND_SACCH_INFO,
  &ySigR_z_Interfaces_S2_OAMS_TRXH_CELLH_SEND_SACCH_INFO),
  SIGNAL_NAME(HEALTH_CHECK_REQ, &ySigR_z_Interfaces_SF_HEALTH_CHECK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_UNLOCK_REQ,
  &ySigR_z_Interfaces_SB_OAMS_CFG_CELLH_UNLOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_LOCK_REQ,
  &ySigR_z_Interfaces_SC_OAMS_CFG_CELLH_LOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_CELL_BAR_ACCESS,
  &ySigR_z_Interfaces_SD_OAMS_CFG_CELLH_CELL_BAR_ACCESS),
  SIGNAL_NAME(OAMS_CFG_CELLH_SHUTDOWN_IND,
  &ySigR_z_Interfaces_SE_OAMS_CFG_CELLH_SHUTDOWN_IND),
  SIGNAL_NAME(OAMS_MAPENT_CELLH_DEL_MAP_RESP,
  &ySigR_z_Interfaces_SK_OAMS_MAPENT_CELLH_DEL_MAP_RESP), (XSIGTYPE)0};
static XCONST XSIGTYPE yChaSR_z0_pPort[] =
  {SIGNAL_NAME(OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND,
  &ySigR_z_Interfaces_S3_OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND),
  SIGNAL_NAME(OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ,
  &ySigR_z_Interfaces_S4_OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ),
  SIGNAL_NAME(OAMS_CELLH_CFG_ALARM_IND,
  &ySigR_z_Interfaces_S8_OAMS_CELLH_CFG_ALARM_IND),
  SIGNAL_NAME(OAMS_CELLH_CFG_LOCK_RESP,
  &ySigR_z_Interfaces_S9_OAMS_CELLH_CFG_LOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_CFG_UNLOCK_RESP,
  &ySigR_z_Interfaces_SA_OAMS_CELLH_CFG_UNLOCK_RESP),
  SIGNAL_NAME(HEALTH_CHECK_RESP, &ySigR_z_Interfaces_S5_HEALTH_CHECK_RESP),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_BCCH_INFO,
  &ySigR_z_Interfaces_S6_OAMS_CELLH_ABIHM_BCCH_INFO),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_SACCH_FILL,
  &ySigR_z_Interfaces_S7_OAMS_CELLH_ABIHM_SACCH_FILL),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_CRE_MAP_REQ,
  &ySigR_z_Interfaces_SI_OAMS_CELLH_MAPENT_CRE_MAP_REQ),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_DEL_MAP_REQ,
  &ySigR_z_Interfaces_SJ_OAMS_CELLH_MAPENT_DEL_MAP_REQ),
  SIGNAL_NAME(OAMS_ADD_TAU_INST_IN_INSTMAP,
  &ySigR_z_Interfaces_SG_OAMS_ADD_TAU_INST_IN_INSTMAP),
  SIGNAL_NAME(OAMS_FREE_INST, &ySigR_z_Interfaces_SH_OAMS_FREE_INST),
  (XSIGTYPE)0};
XCONST xIdNode yChaO_z0_pPort[] = {(xIdNode)&yChaRR_z1_route,
  (xIdNode)&yChaRR_z2_implicit_connector_pPort_pPort_0, (xIdNode)0};
XCONST xIdNode yChaOR_z0_pPort[] = {(xIdNode)&yEnvR_env, (xIdNode)0};
XCONST struct xChannelIdStruct yChaR_z0_pPort = {xGateEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yBloR_z_System_CellHandler, "pPort" xIdNumber(0)
  XCOMMON_EXTRAS, yChaS_z0_pPort, yChaO_z0_pPort, &yChaRR_z0_pPort XCHA_EXTRAS};
XCONST struct xChannelIdStruct yChaRR_z0_pPort = {xGateEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yBloR_z_System_CellHandler, "pPort" xIdNumber(0)
  XCOMMON_EXTRAS, yChaSR_z0_pPort, yChaOR_z0_pPort, &yChaR_z0_pPort
  XCHA_EXTRAS};
#endif

/*****
* SIGNALROUTE route
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#ZecSEEbLAEEEqVJplLxXVh2E|pos(1,21)")
******/
#ifndef XOPTCHAN
static XCONST XSIGTYPE yChaS_z1_route[] =
  {SIGNAL_NAME(OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND,
  &ySigR_z_Interfaces_S3_OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND),
  SIGNAL_NAME(OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ,
  &ySigR_z_Interfaces_S4_OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ),
  SIGNAL_NAME(OAMS_CELLH_CFG_ALARM_IND,
  &ySigR_z_Interfaces_S8_OAMS_CELLH_CFG_ALARM_IND),
  SIGNAL_NAME(OAMS_CELLH_CFG_LOCK_RESP,
  &ySigR_z_Interfaces_S9_OAMS_CELLH_CFG_LOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_CFG_UNLOCK_RESP,
  &ySigR_z_Interfaces_SA_OAMS_CELLH_CFG_UNLOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_BCCH_INFO,
  &ySigR_z_Interfaces_S6_OAMS_CELLH_ABIHM_BCCH_INFO),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_SACCH_FILL,
  &ySigR_z_Interfaces_S7_OAMS_CELLH_ABIHM_SACCH_FILL),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_CRE_MAP_REQ,
  &ySigR_z_Interfaces_SI_OAMS_CELLH_MAPENT_CRE_MAP_REQ),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_DEL_MAP_REQ,
  &ySigR_z_Interfaces_SJ_OAMS_CELLH_MAPENT_DEL_MAP_REQ),
  SIGNAL_NAME(OAMS_ADD_TAU_INST_IN_INSTMAP,
  &ySigR_z_Interfaces_SG_OAMS_ADD_TAU_INST_IN_INSTMAP),
  SIGNAL_NAME(OAMS_FREE_INST, &ySigR_z_Interfaces_SH_OAMS_FREE_INST),
  (XSIGTYPE)0};
static XCONST XSIGTYPE yChaSR_z1_route[] =
  {SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_AVAIL,
  &ySigR_z_Interfaces_S0_OAMS_TRXH_CELLH_BCCH_AVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_UNAVAIL,
  &ySigR_z_Interfaces_S1_OAMS_TRXH_CELLH_BCCH_UNAVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_SEND_SACCH_INFO,
  &ySigR_z_Interfaces_S2_OAMS_TRXH_CELLH_SEND_SACCH_INFO),
  SIGNAL_NAME(OAMS_CFG_CELLH_UNLOCK_REQ,
  &ySigR_z_Interfaces_SB_OAMS_CFG_CELLH_UNLOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_LOCK_REQ,
  &ySigR_z_Interfaces_SC_OAMS_CFG_CELLH_LOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_CELL_BAR_ACCESS,
  &ySigR_z_Interfaces_SD_OAMS_CFG_CELLH_CELL_BAR_ACCESS),
  SIGNAL_NAME(OAMS_CFG_CELLH_SHUTDOWN_IND,
  &ySigR_z_Interfaces_SE_OAMS_CFG_CELLH_SHUTDOWN_IND),
  SIGNAL_NAME(OAMS_MAPENT_CELLH_DEL_MAP_RESP,
  &ySigR_z_Interfaces_SK_OAMS_MAPENT_CELLH_DEL_MAP_RESP), (XSIGTYPE)0};
XCONST xIdNode yChaO_z1_route[] = {(xIdNode)&yChaRR_z0_pPort, (xIdNode)0};
XCONST xIdNode yChaOR_z1_route[] = {(xIdNode)&yChaR_z30_pPort, (xIdNode)0};
XCONST struct xChannelIdStruct yChaR_z1_route = {xSignalrouteEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yBloR_z_System_CellHandler, "route" xIdNumber(0)
  XCOMMON_EXTRAS, yChaS_z1_route, yChaO_z1_route, &yChaRR_z1_route XCHA_EXTRAS};
XCONST struct xChannelIdStruct yChaRR_z1_route = {xSignalrouteEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yBloR_z_System_CellHandler, "route" xIdNumber(0)
  XCOMMON_EXTRAS, yChaSR_z1_route, yChaOR_z1_route, &yChaR_z1_route
  XCHA_EXTRAS};
#endif

/*****
* SIGNALROUTE @implicit_connector_pPort_pPort_0
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#@NO@GUID|pos(1,21)")
******/
#ifndef XOPTCHAN
static XCONST XSIGTYPE yChaS_z2_implicit_connector_pPort_pPort_0[] =
  {SIGNAL_NAME(OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND,
  &ySigR_z_Interfaces_S3_OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND),
  SIGNAL_NAME(OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ,
  &ySigR_z_Interfaces_S4_OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ),
  SIGNAL_NAME(OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND,
  &ySigR_z_Interfaces_S3_OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND),
  SIGNAL_NAME(OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ,
  &ySigR_z_Interfaces_S4_OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ),
  SIGNAL_NAME(HEALTH_CHECK_RESP, &ySigR_z_Interfaces_S5_HEALTH_CHECK_RESP),
  SIGNAL_NAME(HEALTH_CHECK_RESP, &ySigR_z_Interfaces_S5_HEALTH_CHECK_RESP),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_BCCH_INFO,
  &ySigR_z_Interfaces_S6_OAMS_CELLH_ABIHM_BCCH_INFO),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_SACCH_FILL,
  &ySigR_z_Interfaces_S7_OAMS_CELLH_ABIHM_SACCH_FILL),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_BCCH_INFO,
  &ySigR_z_Interfaces_S6_OAMS_CELLH_ABIHM_BCCH_INFO),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_SACCH_FILL,
  &ySigR_z_Interfaces_S7_OAMS_CELLH_ABIHM_SACCH_FILL),
  SIGNAL_NAME(OAMS_CELLH_CFG_ALARM_IND,
  &ySigR_z_Interfaces_S8_OAMS_CELLH_CFG_ALARM_IND),
  SIGNAL_NAME(OAMS_CELLH_CFG_LOCK_RESP,
  &ySigR_z_Interfaces_S9_OAMS_CELLH_CFG_LOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_CFG_UNLOCK_RESP,
  &ySigR_z_Interfaces_SA_OAMS_CELLH_CFG_UNLOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_CFG_ALARM_IND,
  &ySigR_z_Interfaces_S8_OAMS_CELLH_CFG_ALARM_IND),
  SIGNAL_NAME(OAMS_CELLH_CFG_LOCK_RESP,
  &ySigR_z_Interfaces_S9_OAMS_CELLH_CFG_LOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_CFG_UNLOCK_RESP,
  &ySigR_z_Interfaces_SA_OAMS_CELLH_CFG_UNLOCK_RESP),
  SIGNAL_NAME(OAMS_ADD_TAU_INST_IN_INSTMAP,
  &ySigR_z_Interfaces_SG_OAMS_ADD_TAU_INST_IN_INSTMAP),
  SIGNAL_NAME(OAMS_FREE_INST, &ySigR_z_Interfaces_SH_OAMS_FREE_INST),
  SIGNAL_NAME(OAMS_ADD_TAU_INST_IN_INSTMAP,
  &ySigR_z_Interfaces_SG_OAMS_ADD_TAU_INST_IN_INSTMAP),
  SIGNAL_NAME(OAMS_FREE_INST, &ySigR_z_Interfaces_SH_OAMS_FREE_INST),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_CRE_MAP_REQ,
  &ySigR_z_Interfaces_SI_OAMS_CELLH_MAPENT_CRE_MAP_REQ),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_DEL_MAP_REQ,
  &ySigR_z_Interfaces_SJ_OAMS_CELLH_MAPENT_DEL_MAP_REQ),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_CRE_MAP_REQ,
  &ySigR_z_Interfaces_SI_OAMS_CELLH_MAPENT_CRE_MAP_REQ),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_DEL_MAP_REQ,
  &ySigR_z_Interfaces_SJ_OAMS_CELLH_MAPENT_DEL_MAP_REQ), (XSIGTYPE)0};
static XCONST XSIGTYPE yChaSR_z2_implicit_connector_pPort_pPort_0[] =
  {SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_AVAIL,
  &ySigR_z_Interfaces_S0_OAMS_TRXH_CELLH_BCCH_AVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_UNAVAIL,
  &ySigR_z_Interfaces_S1_OAMS_TRXH_CELLH_BCCH_UNAVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_SEND_SACCH_INFO,
  &ySigR_z_Interfaces_S2_OAMS_TRXH_CELLH_SEND_SACCH_INFO),
  SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_AVAIL,
  &ySigR_z_Interfaces_S0_OAMS_TRXH_CELLH_BCCH_AVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_UNAVAIL,
  &ySigR_z_Interfaces_S1_OAMS_TRXH_CELLH_BCCH_UNAVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_SEND_SACCH_INFO,
  &ySigR_z_Interfaces_S2_OAMS_TRXH_CELLH_SEND_SACCH_INFO),
  SIGNAL_NAME(OAMS_CFG_CELLH_UNLOCK_REQ,
  &ySigR_z_Interfaces_SB_OAMS_CFG_CELLH_UNLOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_LOCK_REQ,
  &ySigR_z_Interfaces_SC_OAMS_CFG_CELLH_LOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_CELL_BAR_ACCESS,
  &ySigR_z_Interfaces_SD_OAMS_CFG_CELLH_CELL_BAR_ACCESS),
  SIGNAL_NAME(OAMS_CFG_CELLH_SHUTDOWN_IND,
  &ySigR_z_Interfaces_SE_OAMS_CFG_CELLH_SHUTDOWN_IND),
  SIGNAL_NAME(OAMS_CFG_CELLH_UNLOCK_REQ,
  &ySigR_z_Interfaces_SB_OAMS_CFG_CELLH_UNLOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_LOCK_REQ,
  &ySigR_z_Interfaces_SC_OAMS_CFG_CELLH_LOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_CELL_BAR_ACCESS,
  &ySigR_z_Interfaces_SD_OAMS_CFG_CELLH_CELL_BAR_ACCESS),
  SIGNAL_NAME(OAMS_CFG_CELLH_SHUTDOWN_IND,
  &ySigR_z_Interfaces_SE_OAMS_CFG_CELLH_SHUTDOWN_IND),
  SIGNAL_NAME(HEALTH_CHECK_REQ, &ySigR_z_Interfaces_SF_HEALTH_CHECK_REQ),
  SIGNAL_NAME(HEALTH_CHECK_REQ, &ySigR_z_Interfaces_SF_HEALTH_CHECK_REQ),
  SIGNAL_NAME(OAMS_MAPENT_CELLH_DEL_MAP_RESP,
  &ySigR_z_Interfaces_SK_OAMS_MAPENT_CELLH_DEL_MAP_RESP),
  SIGNAL_NAME(OAMS_MAPENT_CELLH_DEL_MAP_RESP,
  &ySigR_z_Interfaces_SK_OAMS_MAPENT_CELLH_DEL_MAP_RESP), (XSIGTYPE)0};
XCONST xIdNode yChaO_z2_implicit_connector_pPort_pPort_0[] =
  {(xIdNode)&yChaRR_z0_pPort, (xIdNode)0};
XCONST xIdNode yChaOR_z2_implicit_connector_pPort_pPort_0[] =
  {(xIdNode)&yChaR_z40_pPort, (xIdNode)0};
XCONST struct xChannelIdStruct yChaR_z2_implicit_connector_pPort_pPort_0 =
  {xSignalrouteEC , (xIdNode)0, (xIdNode)0,
  (xIdNode)&yBloR_z_System_CellHandler,
  "@implicit_connector_pPort_pPort_0" xIdNumber(0) XCOMMON_EXTRAS,
  yChaS_z2_implicit_connector_pPort_pPort_0,
  yChaO_z2_implicit_connector_pPort_pPort_0,
  &yChaRR_z2_implicit_connector_pPort_pPort_0 XCHA_EXTRAS};
XCONST struct xChannelIdStruct yChaRR_z2_implicit_connector_pPort_pPort_0 =
  {xSignalrouteEC , (xIdNode)0, (xIdNode)0,
  (xIdNode)&yBloR_z_System_CellHandler,
  "@implicit_connector_pPort_pPort_0" xIdNumber(0) XCOMMON_EXTRAS,
  yChaSR_z2_implicit_connector_pPort_pPort_0,
  yChaOR_z2_implicit_connector_pPort_pPort_0,
  &yChaR_z2_implicit_connector_pPort_pPort_0 XCHA_EXTRAS};
#endif

/*****
* PROCESS INST cHandler
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#EZVEEEBJiEEETsuPlLESm2EE|pos(1,17)")
******/
static XPRSNODE yPrsB_z3_cHandler = (XPRSNODE)0;
XCONST struct xPrsIdStruct yPrsR_z3_cHandler = {xProcessEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yBloR_z_System_CellHandler, "cHandler" xIdNumber(0)
  XCOMMON_EXTRAS, yPrsT_z_CellHandler_Z0T0_CellHandler,
  yPrsS_z_CellHandler_Z0T0_CellHandler xOptChan(yPrsO_z3_cHandler), 0, -1
  xNrInst(1), 0, &yPrsB_z3_cHandler,
  (xptrint)sizeof(yVDef_z_CellHandler_Z0T0_CellHandler)
  xPrsPrioPar(xDefaultPrioProcess), (XPRSNODE *)0 xTrace(-1) xGRTrace(-1)
  xBreakB(yRef_z_CellHandler_Z0T0_CellHandler)
  xBreakB(ySym_z_CellHandler_Z0T0_CellHandler) xBreakB(8) xMSCETrace(-1)
  xCoverage(yPrsC_z_CellHandler_Z0T0_CellHandler) xCoverage(0) xCoverage(0), 0,
  0, 0, &yPrsR_z_CellHandler_Z0T0_CellHandler, (xPrdIdNode *)0
  xBreakB("#SDTREF(U2,\"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#EZVEEEBJiEEETsuPlLESm2EE|pos(1,17)\")")
  xThreadName(0) xThreadName(0) XPRS_EXTRAS(z_CellHandler_Z0T0_CellHandler)};
#ifndef XOPTCHAN
XCONST xIdNode yPrsO_z3_cHandler[] = {(xIdNode)&yChaRR_z30_pPort, (xIdNode)0};
#endif

/*****
* GATE pPort
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler/PROCESS cHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#xa-EEEKqLEEEOHDZlLESm2EE|pos(1,18)")
******/
#ifndef XOPTCHAN
static XCONST XSIGTYPE yChaS_z30_pPort[] =
  {SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_AVAIL,
  &ySigR_z_Interfaces_S0_OAMS_TRXH_CELLH_BCCH_AVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_UNAVAIL,
  &ySigR_z_Interfaces_S1_OAMS_TRXH_CELLH_BCCH_UNAVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_SEND_SACCH_INFO,
  &ySigR_z_Interfaces_S2_OAMS_TRXH_CELLH_SEND_SACCH_INFO),
  SIGNAL_NAME(OAMS_CFG_CELLH_UNLOCK_REQ,
  &ySigR_z_Interfaces_SB_OAMS_CFG_CELLH_UNLOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_LOCK_REQ,
  &ySigR_z_Interfaces_SC_OAMS_CFG_CELLH_LOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_CELL_BAR_ACCESS,
  &ySigR_z_Interfaces_SD_OAMS_CFG_CELLH_CELL_BAR_ACCESS),
  SIGNAL_NAME(OAMS_CFG_CELLH_SHUTDOWN_IND,
  &ySigR_z_Interfaces_SE_OAMS_CFG_CELLH_SHUTDOWN_IND),
  SIGNAL_NAME(OAMS_MAPENT_CELLH_DEL_MAP_RESP,
  &ySigR_z_Interfaces_SK_OAMS_MAPENT_CELLH_DEL_MAP_RESP), (XSIGTYPE)0};
static XCONST XSIGTYPE yChaSR_z30_pPort[] =
  {SIGNAL_NAME(OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND,
  &ySigR_z_Interfaces_S3_OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND),
  SIGNAL_NAME(OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ,
  &ySigR_z_Interfaces_S4_OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ),
  SIGNAL_NAME(OAMS_CELLH_CFG_ALARM_IND,
  &ySigR_z_Interfaces_S8_OAMS_CELLH_CFG_ALARM_IND),
  SIGNAL_NAME(OAMS_CELLH_CFG_LOCK_RESP,
  &ySigR_z_Interfaces_S9_OAMS_CELLH_CFG_LOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_CFG_UNLOCK_RESP,
  &ySigR_z_Interfaces_SA_OAMS_CELLH_CFG_UNLOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_BCCH_INFO,
  &ySigR_z_Interfaces_S6_OAMS_CELLH_ABIHM_BCCH_INFO),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_SACCH_FILL,
  &ySigR_z_Interfaces_S7_OAMS_CELLH_ABIHM_SACCH_FILL),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_CRE_MAP_REQ,
  &ySigR_z_Interfaces_SI_OAMS_CELLH_MAPENT_CRE_MAP_REQ),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_DEL_MAP_REQ,
  &ySigR_z_Interfaces_SJ_OAMS_CELLH_MAPENT_DEL_MAP_REQ),
  SIGNAL_NAME(OAMS_ADD_TAU_INST_IN_INSTMAP,
  &ySigR_z_Interfaces_SG_OAMS_ADD_TAU_INST_IN_INSTMAP),
  SIGNAL_NAME(OAMS_FREE_INST, &ySigR_z_Interfaces_SH_OAMS_FREE_INST),
  (XSIGTYPE)0};
XCONST xIdNode yChaO_z30_pPort[] = {(xIdNode)&yPrsR_z3_cHandler, (xIdNode)0};
XCONST xIdNode yChaOR_z30_pPort[] = {(xIdNode)&yChaR_z1_route, (xIdNode)0};
XCONST struct xChannelIdStruct yChaR_z30_pPort = {xGateEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yPrsR_z3_cHandler, "pPort" xIdNumber(0) XCOMMON_EXTRAS,
  yChaS_z30_pPort, yChaO_z30_pPort, &yChaRR_z30_pPort XCHA_EXTRAS};
XCONST struct xChannelIdStruct yChaRR_z30_pPort = {xGateEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yPrsR_z3_cHandler, "pPort" xIdNumber(0) XCOMMON_EXTRAS,
  yChaSR_z30_pPort, yChaOR_z30_pPort, &yChaR_z30_pPort XCHA_EXTRAS};
#endif

/*****
* PROCESS INST @part__@implicit_process_0
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#uTKLEEKqLEEEHjralLESm2EE|pos(1,17)")
******/
static XPRSNODE yPrsB_z4_part__implicit_process_0 = (XPRSNODE)0;
XCONST struct xPrsIdStruct yPrsR_z4_part__implicit_process_0 = {xProcessEC ,
  (xIdNode)0, (xIdNode)0, (xIdNode)&yBloR_z_System_CellHandler,
  "System_CellHandler" xIdNumber(0) XCOMMON_EXTRAS,
  yPrsT_z_CellHandler_Z0T1_implicit_process_0,
  yPrsS_z_CellHandler_Z0T1_implicit_process_0 xOptChan(
  yPrsO_z4_part__implicit_process_0), 0, -1 xNrInst(1), 1,
  &yPrsB_z4_part__implicit_process_0,
  (xptrint)sizeof(yVDef_z_CellHandler_Z0T1_implicit_process_0)
  xPrsPrioPar(xDefaultPrioProcess), (XPRSNODE *)0 xTrace(-1) xGRTrace(-1)
  xBreakB(yRef_z_CellHandler_Z0T1_implicit_process_0)
  xBreakB(ySym_z_CellHandler_Z0T1_implicit_process_0) xBreakB(9) xMSCETrace(-1)
  xCoverage(yPrsC_z_CellHandler_Z0T1_implicit_process_0) xCoverage(0)
  xCoverage(0), 0, 0, 0, &yPrsR_z_CellHandler_Z0T1_implicit_process_0,
  (xPrdIdNode *)0
  xBreakB("#SDTREF(U2,\"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#U1VEEEBJiEEEXmuPlLESm2EE|pos(1,8)\")")
  xThreadName(0) xThreadName(0)
  XPRS_EXTRAS(z_CellHandler_Z0T1_implicit_process_0)};
#ifndef XOPTCHAN
XCONST xIdNode yPrsO_z4_part__implicit_process_0[] =
  {(xIdNode)&yChaRR_z40_pPort, (xIdNode)0};
#endif

/*****
* GATE pPort
* <<PACKAGE CellHandler/BLOCK TYPE System_CellHandler
*     /PROCESS @part__@implicit_process_0>>
* #SDTREF(U2,"u2:/home/gur12171/Release_1.0/VNLBSC/Source/Oams/Src/Cellh/CellhModel/Model/CellHandler.u2#fFIEEEBJiEEE3L8PlLESm2EE|pos(1,18)")
******/
#ifndef XOPTCHAN
static XCONST XSIGTYPE yChaS_z40_pPort[] =
  {SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_AVAIL,
  &ySigR_z_Interfaces_S0_OAMS_TRXH_CELLH_BCCH_AVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_BCCH_UNAVAIL,
  &ySigR_z_Interfaces_S1_OAMS_TRXH_CELLH_BCCH_UNAVAIL),
  SIGNAL_NAME(OAMS_TRXH_CELLH_SEND_SACCH_INFO,
  &ySigR_z_Interfaces_S2_OAMS_TRXH_CELLH_SEND_SACCH_INFO),
  SIGNAL_NAME(OAMS_CFG_CELLH_UNLOCK_REQ,
  &ySigR_z_Interfaces_SB_OAMS_CFG_CELLH_UNLOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_LOCK_REQ,
  &ySigR_z_Interfaces_SC_OAMS_CFG_CELLH_LOCK_REQ),
  SIGNAL_NAME(OAMS_CFG_CELLH_CELL_BAR_ACCESS,
  &ySigR_z_Interfaces_SD_OAMS_CFG_CELLH_CELL_BAR_ACCESS),
  SIGNAL_NAME(OAMS_CFG_CELLH_SHUTDOWN_IND,
  &ySigR_z_Interfaces_SE_OAMS_CFG_CELLH_SHUTDOWN_IND),
  SIGNAL_NAME(HEALTH_CHECK_REQ, &ySigR_z_Interfaces_SF_HEALTH_CHECK_REQ),
  SIGNAL_NAME(OAMS_MAPENT_CELLH_DEL_MAP_RESP,
  &ySigR_z_Interfaces_SK_OAMS_MAPENT_CELLH_DEL_MAP_RESP), (XSIGTYPE)0};
static XCONST XSIGTYPE yChaSR_z40_pPort[] =
  {SIGNAL_NAME(OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND,
  &ySigR_z_Interfaces_S3_OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_IND),
  SIGNAL_NAME(OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ,
  &ySigR_z_Interfaces_S4_OAMS_CELLH_TRXH_DEL_PTRX_LTRX_MAPPING_REQ),
  SIGNAL_NAME(HEALTH_CHECK_RESP, &ySigR_z_Interfaces_S5_HEALTH_CHECK_RESP),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_BCCH_INFO,
  &ySigR_z_Interfaces_S6_OAMS_CELLH_ABIHM_BCCH_INFO),
  SIGNAL_NAME(OAMS_CELLH_ABIHM_SACCH_FILL,
  &ySigR_z_Interfaces_S7_OAMS_CELLH_ABIHM_SACCH_FILL),
  SIGNAL_NAME(OAMS_CELLH_CFG_ALARM_IND,
  &ySigR_z_Interfaces_S8_OAMS_CELLH_CFG_ALARM_IND),
  SIGNAL_NAME(OAMS_CELLH_CFG_LOCK_RESP,
  &ySigR_z_Interfaces_S9_OAMS_CELLH_CFG_LOCK_RESP),
  SIGNAL_NAME(OAMS_CELLH_CFG_UNLOCK_RESP,
  &ySigR_z_Interfaces_SA_OAMS_CELLH_CFG_UNLOCK_RESP),
  SIGNAL_NAME(OAMS_ADD_TAU_INST_IN_INSTMAP,
  &ySigR_z_Interfaces_SG_OAMS_ADD_TAU_INST_IN_INSTMAP),
  SIGNAL_NAME(OAMS_FREE_INST, &ySigR_z_Interfaces_SH_OAMS_FREE_INST),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_CRE_MAP_REQ,
  &ySigR_z_Interfaces_SI_OAMS_CELLH_MAPENT_CRE_MAP_REQ),
  SIGNAL_NAME(OAMS_CELLH_MAPENT_DEL_MAP_REQ,
  &ySigR_z_Interfaces_SJ_OAMS_CELLH_MAPENT_DEL_MAP_REQ), (XSIGTYPE)0};
XCONST xIdNode yChaO_z40_pPort[] =
  {(xIdNode)&yPrsR_z4_part__implicit_process_0, (xIdNode)0};
XCONST xIdNode yChaOR_z40_pPort[] =
  {(xIdNode)&yChaR_z2_implicit_connector_pPort_pPort_0, (xIdNode)0};
XCONST struct xChannelIdStruct yChaR_z40_pPort = {xGateEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yPrsR_z4_part__implicit_process_0, "pPort" xIdNumber(0)
  XCOMMON_EXTRAS, yChaS_z40_pPort, yChaO_z40_pPort, &yChaRR_z40_pPort
  XCHA_EXTRAS};
XCONST struct xChannelIdStruct yChaRR_z40_pPort = {xGateEC , (xIdNode)0,
  (xIdNode)0, (xIdNode)&yPrsR_z4_part__implicit_process_0, "pPort" xIdNumber(0)
  XCOMMON_EXTRAS, yChaSR_z40_pPort, yChaOR_z40_pPort, &yChaR_z40_pPort
  XCHA_EXTRAS};
#endif

/*************************************************************************
**                       SECTION Initialization                         **
*************************************************************************/
#ifndef XMULTIPLESYSTEMS
void yInit (void)
{
#else
void yInit_System_CellHandler (void)
{
#endif
  int  Temp;
  YINIT_TEMP_VARS
  BEGIN_YINIT

#ifdef XMONITOR
  xTranslatorVersion =
    "Program generated by Cbasic 3.0.0.0.2032";
#endif
  yInit_U2ExtraOps();
  yInit_U2ctypes();
  yInit_CELLHInclude();
  yInit_DBSInclude();
  yInit_SYSInclude();
  yInit_Interfaces();
  yInit_CellHandler();
  xInsertIdNode((xIdNode)&yBloR_z_System_CellHandler);
#ifndef XOPTCHAN
  xInsertIdNode((xIdNode)&yChaR_z0_pPort);
  xInsertIdNode((xIdNode)&yChaRR_z0_pPort);
#endif
#ifndef XOPTCHAN
  xInsertIdNode((xIdNode)&yChaR_z1_route);
  xInsertIdNode((xIdNode)&yChaRR_z1_route);
#endif
#ifndef XOPTCHAN
  xInsertIdNode((xIdNode)&yChaR_z2_implicit_connector_pPort_pPort_0);
  xInsertIdNode((xIdNode)&yChaRR_z2_implicit_connector_pPort_pPort_0);
#endif
  xInsertIdNode((xIdNode)&yPrsR_z3_cHandler);
#ifndef XOPTCHAN
  xInsertIdNode((xIdNode)&yChaR_z30_pPort);
  xInsertIdNode((xIdNode)&yChaRR_z30_pPort);
#endif
  xInsertIdNode((xIdNode)&yPrsR_z4_part__implicit_process_0);
#ifndef XOPTCHAN
  xInsertIdNode((xIdNode)&yChaR_z40_pPort);
  xInsertIdNode((xIdNode)&yChaRR_z40_pPort);
#endif
}