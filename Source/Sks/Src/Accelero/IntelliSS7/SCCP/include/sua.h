/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                  
 * CONTRACT: INTERNAL
 *      
 * ID: $Id: sua.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:52  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:50  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:20  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.2  2004/12/16 02:22:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/14 13:44:52  snagesh
 * LOG: Modifications for Chinese variant
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/07/03 19:54:44  mmiers
 * LOG: China fixes
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:25:07  lbana
 * LOG: commit sua.h from PR5
 * LOG:
 * LOG: Revision 4.3.2.10  2002/04/15 16:47:31  ngoel
 * LOG: change reg res length to 24
 * LOG:
 * LOG: Revision 4.3.2.9  2002/04/15 13:58:11  ngoel
 * LOG: define common parameter local rkid
 * LOG:
 * LOG: Revision 4.3.2.8  2002/04/03 14:28:53  ngoel
 * LOG: make sua desc common for ANSI and CCITT
 * LOG:
 * LOG: Revision 4.3.2.7  2002/03/14 20:37:26  ngoel
 * LOG: add transport manager in function definition
 * LOG:
 * LOG: Revision 4.3.2.6  2002/03/11 21:54:05  ngoel
 * LOG: add transport manager to codec definition
 * LOG:
 * LOG: Revision 4.3.2.5  2002/02/25 15:30:57  ngoel
 * LOG: move to sua draft 12
 * LOG:
 * LOG: Revision 4.3.2.4  2002/02/22 19:05:45  ngoel
 * LOG: add asp label parameter
 * LOG:
 * LOG: Revision 4.3.2.3  2002/02/21 16:20:38  ngoel
 * LOG: get interworking mode in class initialize
 * LOG:
 * LOG: Revision 4.3.2.2  2002/02/21 15:17:43  ngoel
 * LOG: some additions
 * LOG:
 * LOG: Revision 4.3.2.1  2002/02/11 22:20:37  ngoel
 * LOG: move to sua v11
 * LOG:
 * LOG: Revision 4.3  2001/07/26 14:49:58  labuser
 * LOG: commit SUA v5 to current.
 * LOG:
 * LOG: Revision 1.13.2.1  2001/06/22 20:24:48  labuser
 * LOG: SUA Draft V5 Codec.
 * LOG:

 *                 
 ****************************************************************************/

#ifndef SUA_H
#define SUA_H

#include <its.h>
#include <its_object.h>
#include <its_sctp_trans.h>

#if defined(ANSI)

#if defined(USE_ITU_SCCP)

#undef ANSI
#define CCITT 1

#include <itu/sccp.h>

#undef CCITT
#define ANSI 1

#else /* USE_ITU_SCCP */

#include <ansi/sccp.h>

#endif /* USE_ITU_SCCP */

#elif defined(CCITT)

#if defined(USE_ANSI_SCCP)

#undef CCITT
#define ANSI 1

#include <ansi/sccp.h>

#undef ANSI
#define CCITT 1

#else /* USE_ANSI_SCCP */

#include <itu/sccp.h>

#endif /* USE_ANSI_SCCP */

#elif defined(PRC)

#include <china/sccp.h>

#elif defined(TTC)

#include <japan/sccp.h>

#else
#error "Protocol family not defined."
#endif

#if defined(WIN32)

#if defined(SUA_IMPLEMENTATION)
#define SUADLLAPI __declspec(dllexport)
#else
#define SUADLLAPI __declspec(dllimport)
#endif

#else  /* WIN32 */

#define SUADLLAPI

#endif /* WIN32 */

#if defined(__cplusplus)
extern "C"
{
#endif

#define SUA_EBADMSG                   -73
#define SUA_EWRG_SUA_PARAM            -74
#define SUA_INTERWORK_MODE_STRING      "interworkingMode"
#define SUA_SG_MODE_STRING             "sgMode"
#define SUA_ITW_SG                     0x01U
#define SUA_ITW_ASP                    0x02U




/* SUA protocol version */
#define SUA_PROT_VER1                 0x01

/* message class */
#define SUA_CL_MGMT_MSG               0x00
#define SUA_CL_SSNM_MSG               0x02
#define SUA_CL_ASP_STATE_MAINT_MSG    0x03
#define SUA_CL_ASP_TRAF_MAINT_MSG     0x04
#define SUA_CL_CL_MSG                 0x07
#define SUA_CL_CO_MSG                 0x08
#define SUA_RKEY_MGMT_MSG             0x09

/* management message */
#define SUA_MSG_ERR                   0x00
#define SUA_MSG_NOTIFY                0x01


/* Application Server Process Maintenance messages (ASPM) */
#define SUA_MSG_ASPUP                 0x01
#define SUA_MSG_ASPDN                 0x02
#define SUA_MSG_BEAT                  0x03
#define SUA_MSG_ASPUP_ACK             0x04
#define SUA_MSG_ASPDN_ACK             0x05
#define SUA_MSG_BEAT_ACK              0x06

/* Application Server Process Traffic Maintenance (ASPTM) */
#define SUA_MSG_ASPAC                 0x01
#define SUA_MSG_ASPIA                 0x02
#define SUA_MSG_ASPAC_ACK             0x03
#define SUA_MSG_ASPIA_ACK             0x04

/* Signaling network management messages (SSNM) */
#define SUA_MSG_DUNA                  0x01
#define SUA_MSG_DAVA                  0x02
#define SUA_MSG_DAUD                  0x03
#define SUA_MSG_SCON                  0x04
#define SUA_MSG_DUPU                  0x05
#define SUA_MSG_DRST                  0x06
/*#define SUA_MSG_SCMG                  0x06 removed in draft 9 */

/* Routing KeyManagement Messages */
#define SUA_REG_REQ                  0x01
#define SUA_REG_RSP                  0x02
#define SUA_DEREG_REQ                0x03
#define SUA_DEREG_RSP                0x04

/* SUA Connectionless messages */
#define SUA_MSG_CLDT                  0x01
#define SUA_MSG_CLDR                  0x02

/* SUA Connection Oriented messages */
#define SUA_MSG_CORE                  0x01
#define SUA_MSG_COAK                  0x02
#define SUA_MSG_COREF                 0x03
#define SUA_MSG_RELRE                 0x04
#define SUA_MSG_RELCO                 0x05
#define SUA_MSG_RESCO                 0x06
#define SUA_MSG_RESRE                 0x07
#define SUA_MSG_CODT                  0x08
#define SUA_MSG_CODA                  0x09
#define SUA_MSG_COERR                 0x0A
#define SUA_MSG_COIT                  0x0B


/* SUA common message Header */
typedef struct
{
    ITS_OCTET   version;
    ITS_OCTET   reserved;
    ITS_OCTET   msgClass;
    ITS_OCTET   msgType;
    ITS_UINT    msgLen;  /* msg data + sizeof(SUA_MSG_HDR) */   
}
SUA_MSG_HDR;


/* SUA Common Parameters */
#define SUA_PRM_MSG_HDR                0x0000    /* used by IntelliSS7 */
#define SUA_PRM_INFO_STR               0x0004
#define SUA_PRM_ROUT_CTX               0x0006
#define SUA_PRM_DIAG_INFO              0x0007
#define SUA_PRM_HEARTBEAT_DATA         0x0009
#define SUA_PRM_TRAFFIC_MODE           0x000B
#define SUA_PRM_ERROR_CODE             0x000C
#define SUA_PRM_STATUS_TYPE_ID         0x000D
#define SUA_PRM_ASP_ID                 0x0011
#define SUA_PRM_AFFECTED_PC            0x0012
#define SUA_PRM_COR_ID                 0x0013
#define SUA_PRM_REG_RES                0x0014
#define SUA_PRM_DEREG_RES              0x0015
#define SUA_PRM_REG_STATUS             0x0016
#define SUA_PRM_DEREG_STATUS           0x0017
#define SUA_PRM_LOCAL_RKID             0x0018

/* SUA Specific Parameters */
#define SUA_PRM_HOP_CNT                0x0101
#define SUA_PRM_SRC_ADDR               0x0102
#define SUA_PRM_DST_ADDR               0x0103
#define SUA_PRM_SRC_REF_NUM            0x0104
#define SUA_PRM_DST_REF_NUM            0x0105
#define SUA_PRM_SCCP_CAUSE             0x0106
#define SUA_PRM_SEQ_NUM                0x0107  /* SCCP seq/segment 3.9*/
#define SUA_PRM_REC_SEQ_NUM            0x0108  /* SCCP rec seq num 3.8*/
#define SUA_PRM_ASP_CAPAB              0x0109
#define SUA_PRM_CREDIT                 0x010A
#define SUA_PRM_DATA                   0x010B
#define SUA_PRM_CAUSE_USER             0x010C 
#define SUA_PRM_NET_APP                0x010D
#define SUA_PRM_RKEY                   0x010E
#define SUA_PRM_DRN_LABEL              0x010F
#define SUA_PRM_TID_LABEL              0x0110
#define SUA_PRM_ADDR_RANG              0x0111
#define SUA_PRM_SMI                    0x0112
#define SUA_PRM_IMPORTANCE             0x0113
#define SUA_PRM_MSG_PRIOR              0x0114
#define SUA_PRM_PROT_CLASS             0x0115
#define SUA_PRM_SEQ_CTL                0x0116
#define SUA_PRM_SEGMENTATION           0x0117
#define SUA_PRM_CONG_LEVEL             0x0118



/* SUA Destination/Source Address Subparameters */
#define SUA_SPRM_GT                    0x8001
#define SUA_SPRM_PC                    0x8002
#define SUA_SPRM_SSN                   0x8003
#define SUA_SPRM_IPV4_ADDR             0x8004
#define SUA_SPRM_HOSTNAME              0x8005
#define SUA_SPRM_IPV6_ADDR             0x8006



/* 
 * --------- Common UAL Messages --------
 */

/* 
 * Network apperance 
 */


typedef struct
{
    ITS_UINT    networkApp;
}
SUA_NET_APP;


/* 
 * Data parameter 
 */

#define SUA_MAX_DATA_SIZE   (254) 

typedef struct
{
    ITS_OCTET    data[SUA_MAX_DATA_SIZE]; 
}
SUA_DATA;


/*
 * Info String 
 */

#define SUA_MAX_INFO_STR_LEN   255 

typedef struct
{
    ITS_OCTET    infoStr[SUA_MAX_INFO_STR_LEN];
}
SUA_INFO_STR;


/* 
 * Affected PC 
 */

typedef struct
{
    ITS_OCTET           mask;
    ITS_OCTET           pc[3];
}
SUA_AFFECTED_DEST;



/* 
 * Routing Context 
 */

#define SUA_MAX_ROUT_CTX_LEN   1024 
#define SUA_MAX_RK_NUM         15


typedef struct
{
    ITS_OCTET    routCtx[SUA_MAX_ROUT_CTX_LEN];
}
SUA_ROUT_CTX;


/*
 * Routing Key
 */

#define SUA_MAX_ROUT_KEY_LEN   1024 

typedef struct
{
    ITS_OCTET    routKey[SUA_MAX_ROUT_KEY_LEN];
}
SUA_ROUT_KEY;


/*
 * Diagnostic Information
 */

#define SUA_MAX_DIAG_INFO_LEN   40

typedef struct
{
    ITS_OCTET   diagnosticInfo[SUA_MAX_DIAG_INFO_LEN];
}
SUA_DIAG_INFO;


/*
 * HeartBeat Data
 */

#define SUA_MAX_HB_DATA_LEN 254

typedef struct
{
    ITS_OCTET   HBData[SUA_MAX_HB_DATA_LEN];
}
SUA_HB_DATA;


/*
 * Cause-User
 */

typedef struct
{
    ITS_USHORT   cause;
    ITS_USHORT   user;
}
SUA_CAUSE_USER;

/* cause */
#define SUA_UNKNOWN_CAUSE           0x00
#define SUA_UNEQUIP_REMOTE_USR      0x01
#define SUA_INACCESS_REMOTE_USR     0x02

/* User Id */
#define SUA_USER_SCCP               0x03



/*
 * Reason
 */

typedef struct
{
    ITS_UINT    reason;
}
SUA_REASON;

#define SUA_UNSPEC_REASON        0x00
#define SUA_USR_UNAV_REASON      0x01
#define SUA_MGMT_BLOCK_REASON    0x02
#define SUA_ASP_FAULT            0x03


/* 
 * Traffic Mode Type
 */

typedef struct
{
    ITS_UINT    tm;
}
SUA_TRAFFIC_MODE;

#define SUA_OVERRIDE_MODE        0x01
#define SUA_LOADSHARE_MODE       0x02
#define SUA_OVERRIDE_SB_MODE     0x03
#define SUA_LOADSHARE_SB_MODE    0x04


/*
 * Error Code
 */

typedef struct
{
    ITS_UINT    errCode;
}
SUA_ERR_CODE;

#define SUA_ERR_INV_VER             0x01
#define SUA_ERR_INV_NET_APP         0x02
#define SUA_ERR_INV_ALI             0x03
#define SUA_ERR_INV_MSG_TYP         0x04
#define SUA_ERR_INV_THM             0x05
#define SUA_ERR_UNEXP_MSG           0x06
#define SUA_ERR_PROT_ERR            0x07
#define SUA_ERR_INV_ROUT_CTX        0x08
#define SUA_ERR_UNSUP_MSG           0x09



/*
 * Status Type
 */

typedef struct
{
    ITS_USHORT  type;
    ITS_USHORT  id;
}
SUA_STATUS_TYPE;

#define SUA_ST_TYPE_AS_STAT_CHG        0x01
#define SUA_ST_TYPE_OTHER              0x02

#define SUA_ST_ID_AS_INACTIVE          0x02
#define SUA_ST_ID_AS_ACTIVE            0x03
#define SUA_ST_ID_AS_PENDING           0x04

#define SUA_ST_ID_INSUF_ASP            0x01
#define SUA_ALT_ASP_ACTIVE             0x02


/*
 * Congestion Level
 */

typedef struct
{
    ITS_UINT    level;
}
SUA_CONG_LEVEL;

#define SUA_NO_CONG                    0x00
#define SUA_CONG_LEVEL_1               0x01
#define SUA_CONG_LEVEL_2               0x02
#define SUA_CONG_LEVEL_3               0x03




/* 
 * --------- SUA Specific Messages --------
 */

/* 
 * Flags
 */

typedef struct
{
    ITS_UINT value;
}
SUA_PROT_CLASS;

typedef struct
{
    ITS_UINT value;
}
SUA_IMPORTANCE;

typedef struct
{
    ITS_UINT value;
}
SUA_HOP_COUNT;

typedef struct
{
    ITS_UINT value;
}
SUA_SEQ_CTL;

typedef struct
{
    ITS_UINT   refNum;
}
SUA_REF_NUM;

typedef struct
{
    ITS_OCTET       flags;
    SUA_REF_NUM    localRef;
}
SUA_SEGMENTATION;

typedef struct
{
    ITS_UINT msgPrior;
}
SUA_MSG_PRIOR;

typedef struct
{
    ITS_UINT corId;
}
SUA_MSG_COR_ID;


/*
 * Registration Result 
 */

#define SUA_MAX_REG_RES_LEN               24

typedef struct
{
    ITS_OCTET regRes[SUA_MAX_REG_RES_LEN];
}
SUA_REG_RESULT;


/*
 * registration Status
 */
typedef struct
{
    ITS_UINT regStat;
}
SUA_REG_STATUS;

#define SUA_REG_STAT_SUCCESS            0x00
#define SUA_REG_STAT_ERR_UNKNOWN        0x01
#define SUA_REG_STAT_ERR_INV_DPC        0x02
#define SUA_REG_STAT_ERR_INV_NA         0x03
#define SUA_REG_STAT_ERR_INV_RK         0x04
#define SUA_REG_STAT_ERR_PERM_DNY       0x05
#define SUA_REG_STAT_ERR_NO_SUP_UNI_RK  0x06
#define SUA_REG_STAT_ERR_RK_NOT_PROV    0x07
#define SUA_REG_STAT_ERR_UNSUFF_RES     0x08
#define SUA_REG_STAT_ERR_NO_SUP_RK_FLD  0x09
#define SUA_REG_STAT_ERR_INVALID_THM    0x0A



/* bit 1-2 of the protocol class */
#define SUA_PROT_CLASS_0               0x00    /* connectionless service */
#define SUA_PROT_CLASS_1               0x01    /* connectionless service */
#define SUA_PROT_CLASS_2               0x02    /* connection-oriented service */
#define SUA_PROT_CLASS_3               0x03    /* connection-oriented service */

/* bit 8 of the protocol class */
#define SUA_NO_RET_OPTION              0x00
#define SUA_RET_ON_ERR_OPT             0x01    


#define SUA_MAX_ADDR_DATA              256

typedef struct
{
    ITS_OCTET len;   /* the len include the 2 indic + Data with padding */
    ITS_OCTET routIndic[2];
    ITS_OCTET addrIndic[2];
    ITS_OCTET addrData[SUA_MAX_ADDR_DATA];
}
SUA_ADDRS;



typedef struct
{
    ITS_OCTET data[SUA_MAX_ADDR_DATA];
}
SUA_ADDRS_RANGE;

/* SUA addr indicator masks */
#define SUA_CPA_HAS_SSN_MASK                   0x01
#define SUA_CPA_HAS_PC_MASK                    0x02
#define SUA_CPA_HAS_GT_MASK                    0x04

/* SUA routing indiactor */
#define SUA_CPA_ROUTE_ON_GT                    0x01
#define SUA_CPA_ROUTE_ON_SSN                   0x02
#define SUA_CPA_ROUTE_ON_HOST                  0x03
#define SUA_CPA_ROUTE_ON_IP                    0x04

#define SUA_GT_NUM_PLAN_MASK                   0x0F
#define SUA_GT_ODD_EVEN_MASK                   0x80


typedef struct
{
    ITS_OCTET           mask;
    ITS_OCTET           pc[3];
}
SUA_PC;

#if defined CCITT
/*
 * point code as value
 */
#define SUA_PC_SET_VALUE(x,v)                             \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),              \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0x3FU))) 

#define SUA_PC_GET_VALUE(x)                               \
    ((((x).pc[1] & 0x3FU) << 8) | ((x).pc[2]))

#elif defined ANSI
/*
 * point code as value
 */
#define SUA_PC_SET_VALUE(x,v)                             \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),              \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),       \
     ((x).pc[0] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))


#define SUA_PC_GET_VALUE(x)                               \
    ((x).pc[2] | ((x).pc[1] << 8) | ((x).pc[0] << 16))

#elif defined PRC
/*
 * point code as value
 */
#define SUA_PC_SET_VALUE(x,v)                             \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),              \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),       \
     ((x).pc[0] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))


#define SUA_PC_GET_VALUE(x)                               \
    ((x).pc[2] | ((x).pc[1] << 8) | ((x).pc[0] << 16))

#endif /* define ANSI */

typedef struct
{
    ITS_UINT ssn;
}
SUA_SSN;

#define SUA_MAX_GT_LEN                  255

typedef struct
{
    ITS_OCTET numOfDgts;
    ITS_OCTET transType;
    ITS_OCTET numPlan;
    ITS_OCTET natOfAddr;
    ITS_OCTET data[SUA_MAX_GT_LEN];
}
SUA_GT;

#define SUA_IP_ADDR_LEN                 32

typedef struct
{
    ITS_OCTET IPAddrs[SUA_IP_ADDR_LEN];
}
SUA_IP_ADDRS;

#define SUA_MAX_HOSTNAME_LEN            32

typedef struct
{
    ITS_USHORT len;
    ITS_OCTET hostName[SUA_MAX_HOSTNAME_LEN];
}
SUA_HOSTNAME;


/* 
 * reference number 
 */


/* 
 * SCCP Cause
 */

typedef struct
{
    ITS_USHORT spare;
    ITS_OCTET causeType;
    ITS_OCTET causeValue;
}
SUA_SCCP_CAUSE;

#define SUA_CAUSE_TYPE_RETURN           0x01
#define SUA_CAUSE_TPYE_REFUSAL          0x02
#define SUA_CAUSE_TYPE_RELEASE          0x03
#define SUA_CAUSE_TYPE_RESET            0x04
#define SUA_CAUSE_TYPE_ERROR            0x05

/* 
 * SCCP cause values are given in the SCCP specs
 * refer to that document for more information
 */

/* 
 * Sequence Number 
 */

/* 
 * this parameter is used to indicate whether more data will follow
 * in the subsequent CODT messages, and to number each CODT message 
 * sequentially for the purpose of flow control. contain the "More"
 * indicator and the P(R) and P(S) in Q713
 */

typedef struct
{
    ITS_USHORT spare;
    ITS_OCTET recSeqNum;
    ITS_OCTET sentSenqNum;
}
SUA_SEQ_NUM;

#define SUA_SNUM_MORE_DATA_MASK        0x01


/* 
 * Receive Sequence Number 
 */

/* 
 * This parameter is used only for Protocol class 3 messages
 * It indicates the lower edge of the receiving window 
 */

typedef struct
{
    ITS_OCTET spare[3];
    ITS_OCTET recSeqNum;
}
SUA_REC_SEQ_NUM;

/*
 *   ASP Label 
 */
typedef struct
{
    ITS_OCTET start;
    ITS_OCTET end;
    ITS_OCTET lvalue[2];
}SUA_ASP_LABEL;


/* 
 * ASP Capabilities 
 */

typedef struct
{
    ITS_USHORT spare;
    ITS_OCTET protClass;
    ITS_OCTET interWork;
}
SUA_ASP_CAPAB;

/*interworking types */
#define SUA_INTERWORK_NOSS7     0x00
#define SUA_INTERWORK_SS7       0x01
#define SUA_INTERWORK_SG        0x02
#define SUA_INTERWORK_RELAY     0x03

/*PROTOCOL CLASS FLAG */
#define SUA_PROT_CLASS0_FLAG    0x01
#define SUA_PROT_CLASS1_FLAG    0x02
#define SUA_PROT_CLASS2_FLAG    0x04
#define SUA_PROT_CLASS3_FLAG    0x08

/* 
 * Credit 
 */

typedef struct
{
    ITS_UINT credit;
}
SUA_CREDIT;


/* 
 * SCMG Format Identifier 
 */

typedef struct
{
    ITS_UINT formatId;
}
SUA_SCMG_FORM;

#define SUA_SCMG_FORMAT_SSA         0x01
#define SUA_SCMG_FORMAT_SSP         0x02
#define SUA_SCMG_FORMAT_SST         0x03
#define SUA_SCMG_FORMAT_SOR         0x04
#define SUA_SCMG_FORMAT_SOG         0x05
#define SUA_SCMG_FORMAT_SSC         0x06
#define SUA_SCMG_FORMAT_SNR         0xFD
#define SUA_SCMG_FORMAT_SBR         0xFE
#define SUA_SCMG_FORMAT_SRT         0xFF


/* 
 * SMI 
 */

typedef struct
{
    ITS_UINT smi;
}
SUA_SMI;

#define SUA_SMI_REPLICATED          0x01
#define SUA_SMI_SOLITARY            0x02
#define SUA_SMI_UNKNOWN             0x03



/*
 * SUA IES
 */
typedef struct
{
    ITS_USHORT   param_id;      
    ITS_USHORT   param_length;
    union
    {
        SUA_MSG_HDR         msgHeader;
        SUA_NET_APP         networkAppearance;
        SUA_DATA            data;
        SUA_INFO_STR        infoStr;
        SUA_AFFECTED_DEST   affectedPC;
        SUA_ROUT_CTX        routeCtx;
        SUA_DIAG_INFO       diagnostic;
        SUA_HB_DATA         hbData;
        SUA_CAUSE_USER      causeUsr;
        SUA_REASON          reason;
        SUA_TRAFFIC_MODE    trafMd;
        SUA_ERR_CODE        errorCode;
        SUA_STATUS_TYPE     statusType;
        SUA_CONG_LEVEL      congestion;
        /*SUA_FLAGS           flags; */
        SUA_ADDRS           srcAddrs;
        SUA_ADDRS           dstAddrs;
        SUA_REF_NUM         srcRefNum;
        SUA_REF_NUM         dstRefNum;
        SUA_SCCP_CAUSE      cause;
        SUA_SEQ_NUM         seqNum;
        SUA_REC_SEQ_NUM     rSeqNum;
        SUA_ASP_CAPAB       capab;
        SUA_CREDIT          cr;
        SUA_SCMG_FORM       scmg;
        SUA_SMI             smi;
        SUA_PROT_CLASS     pClass;
        SUA_HOP_COUNT       hopCount;
        SUA_IMPORTANCE      importance;
        SUA_SEQ_CTL         seqCtl;
        SUA_SEGMENTATION    segmentation;
        SUA_MSG_PRIOR       msgPrior;
        SUA_MSG_COR_ID      msgCorId;
        SUA_PC              pc;   /* sub parameter */
        SUA_SSN             ssn;  /* sub parameter */
        SUA_GT              gt;   /* sub parameter */
        SUA_ADDRS_RANGE     addrRange;
        SUA_ROUT_KEY        rkData;
    }
    param_data;
}
ITS_SUA_IE;


#define ITS_MAX_SUA_IES   32


typedef struct
{
    ITS_USHORT*    mParam;
    int           nmParam;
    ITS_USHORT*    oParam;
    int           noParam;
}
SUA_MSG_DESC;




/*********************************************************************/
/*
 * family independence
 */

#if defined(CCITT)

#if !defined(USE_ANSI_SCCP)


#define SUA_SUAEvtToSCCPEvt        SUA_SUAEvtToSCCPEvt_CCITT
#define SUA_SCCPEvtToSUAEvt        SUA_SCCPEvtToSUAEvt_CCITT

#define SUA_To_SCCP_Codec  SUA_To_SCCP_Codec_CCITT
#define SCCP_To_SUA_Codec  SCCP_To_SUA_Codec_CCITT

#define SUA_CLASS_NAME     "CCITT-SUA"

#define itsSUA_Class       itsSUA_CCITT_Class

#else /* !defined(USE_ANSI_SCCP) */



#define SUA_SUAEvtToSCCPEvt                         SUA_SUAEvtToSCCPEvt_ANSI
#define SUA_SCCPEvtToSUAEvt                         SUA_SCCPEvtToSUAEvt_ANSI

#define SUA_To_SCCP_Codec                           SUA_To_SCCP_Codec_ANSI
#define SCCP_To_SUA_Codec                           SCCP_To_SUA_Codec_ANSI

#define SUA_PrintSUA_IES                            SUA_PrintSUA_IES_ANSI

#define SUA_CLASS_NAME  "ANSI-SUA"

#define itsSUA_Class    itsSUA_ANSI_Class

#endif /* !defined(USE_ANSI_SCCP) */

#elif defined(ANSI)

#if !defined(USE_CCITT_SCCP)


#define SUA_SUAEvtToSCCPEvt                         SUA_SUAEvtToSCCPEvt_ANSI
#define SUA_SCCPEvtToSUAEvt                         SUA_SCCPEvtToSUAEvt_ANSI

#define SUA_To_SCCP_Codec                           SUA_To_SCCP_Codec_ANSI
#define SCCP_To_SUA_Codec                           SCCP_To_SUA_Codec_ANSI

#define SUA_PrintSUA_IES                            SUA_PrintSUA_IES_ANSI

#define SUA_CLASS_NAME  "ANSI-SUA"

#define itsSUA_Class    itsSUA_ANSI_Class

#else /* !defined(USE_CCITT_SCCP) */


#define SUA_SUAEvtToSCCPEvt                         SUA_SUAEvtToSCCPEvt_CCITT
#define SUA_SCCPEvtToSUAEvt                         SUA_SCCPEvtToSUAEvt_CCITT

#define SUA_To_SCCP_Codec                           SUA_To_SCCP_Codec_CCITT
#define SCCP_To_SUA_Codec                           SCCP_To_SUA_Codec_CCITT

#define SUA_PrintSUA_IES                            SUA_PrintSUA_IES_CCITT

#define SUA_CLASS_NAME  "CCITT-SUA"

#define itsSUA_Class    itsSUA_CCITT_Class

#endif /* !defined(USE_CCITT_SCCP) */
 
#endif /* defined(CCITT) */



/* message descriptors */
SUADLLAPI extern SUA_MSG_DESC SUA_DATA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DUNA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DAVA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DAUD_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_SCON_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DUPU_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPUP_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_UPACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPDN_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DNACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_HEARTBEAT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_HEARTBEAT_ACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPAC_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPAC_ACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPIA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPIA_ACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_NTFY_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ERR_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CLDT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CLDR_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CODT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CODA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CORE_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COAK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COREF_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RESRE_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RESCO_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RELRE_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RELCO_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COERR_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COIT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_SCMG_Desc;




/*
 * Codecs
 */

SUADLLAPI int SUA_EncodeMsg(ITS_SUA_IE *ies, int ieCount,ITS_EVENT *event,
                            SUA_MSG_DESC* desc);

SUADLLAPI int SUA_DecodeMsg(ITS_SUA_IE *ies, int *ieCount, ITS_EVENT *ev,
                            SUA_MSG_DESC *desc);

SUADLLAPI int SUA_To_SCCP_Codec(SCTPTRAN_Manager *m, ITS_EVENT *evt,
                                ITS_BOOLEAN *isMgmt, ITS_OCTET *sls);

SUADLLAPI int SCCP_To_SUA_Codec( SCTPTRAN_Manager *m, ITS_EVENT *evt,
                                ITS_BOOLEAN *isMgmt, ITS_OCTET *sls);


SUADLLAPI int SUA_EncodeAddress(SUA_ADDRS *suaAddr, ITS_OCTET routIndic, 
                                ITS_OCTET addrIndic, ITS_UINT pc, 
                                ITS_OCTET ssn, SUA_GT *gt, int gtLen);

SUADLLAPI int SUA_DecodeAddress(ITS_OCTET *suaAddr, int len, 
                                ITS_OCTET *routIndic, ITS_OCTET *addrIndic, 
                                ITS_UINT *pc, ITS_OCTET *ssn, SUA_GT *gt, 
                                int *gtLen);


/*
 * Helper functions
 */

SUADLLAPI ITS_SUA_IE* SUA_FindSUAIE(ITS_SUA_IE *ies, int ieCount, 
                                    ITS_USHORT paramId);

SUADLLAPI int SUA_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, 
                                       ITS_UINT *rkList, int size);

SUADLLAPI int SUA_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, 
                                       ITS_UINT *rkList, int *size);

SUADLLAPI int SUA_GetPadding(int size);

SUADLLAPI void SUA_HComHdrToN(SUA_MSG_HDR *msgHdr);

SUADLLAPI void SUA_NComHdrToH(SUA_MSG_HDR *msgHdr);

SUADLLAPI int SUA_SUAEvtToSCCPEvt(ITS_EVENT *evt, ITS_BOOLEAN toSCCP, 
                                  ITS_HDR *hdr, ITS_BOOLEAN *isMgmt);

SUADLLAPI int SUA_SCCPEvtToSUAEvt(SCTPTRAN_Manager *m, ITS_EVENT *evt, 
                                  ITS_BOOLEAN toUser, 
                                  ITS_HDR *hdr, ITS_OCTET *sls);

SUADLLAPI int
SUA_EncodeRoutingKey(SUA_ROUT_KEY *rkey, ITS_USHORT *rKeyLen, ITS_UINT rkid, 
                     SUA_TRAFFIC_MODE *tm, SUA_NET_APP *na, SUA_ADDRS *srcAddr, 
                     SUA_ADDRS *dstAddr, SUA_ADDRS_RANGE *addrRange, ITS_USHORT addrRangeLen);

SUADLLAPI int
SUA_EncodeAddressRange(SUA_ADDRS_RANGE *addrRange, ITS_OCTET *totLen, SUA_ADDRS *addr1, 
                       SUA_ADDRS *addr2, ITS_USHORT addrType);
/*
 * feature record
 */
SUADLLAPI extern ITS_Class   itsSUA_Class;

/*
 * user knows by which API they implemented with
 */
#define ITS_SUA     ITS_SCCP

#if defined(__cplusplus)
}
#endif

#endif /*SUA_H*/
