/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 ****************************************************************************
 *
 *  LOG: $Log: not supported by cvs2svn $
 *  LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 *  LOG: init tree
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 *  LOG: BscCs2
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 *  LOG: BSC project
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:50:51  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.9  2005/02/22 10:13:07  adutta
 *  LOG: Fix for Bug#1542
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.8  2005/01/24 12:01:05  snagesh
 *  LOG: Windows compilation fixes
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.7  2005/01/11 12:30:48  craghavendra
 *  LOG: Syslog Enhancements.
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.6  2005/01/07 14:58:23  ssingh
 *  LOG: Changes in connection with  enhancement of ACTIVE-BACKUP redundancy.
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.5  2005/01/04 15:19:02  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.4  2004/12/20 13:38:25  dsatish
 *  LOG: Fix for Bug #1328
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.3  2004/12/15 16:11:37  dsatish
 *  LOG: Added more APIs for SHIM
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.2  2004/12/15 12:14:05  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2.4.1  2004/12/14 13:30:54  snagesh
 *  LOG: Modifications for Chinese variant
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.2  2004/10/06 08:27:43  mmanikandan
 *  LOG: Support for Windows Build.
 *  LOG:
 *  LOG: Revision 7.2.2.5.2.1  2004/05/03 12:25:15  ssingh
 *  LOG: Interworking Mode is made public to UAL as well as M3UA.
 *  LOG:
 *  LOG: Revision 7.2.2.5  2003/10/14 20:58:00  lbana
 *  LOG: remove begin and end tags for fixes.
 *  LOG:
 *  LOG: Revision 7.2.2.4  2003/09/08 19:31:46  lbana
 *  LOG: Added callback info for pause/resume when transport goes up/down
 *  LOG:
 *  LOG: Revision 7.2.2.3  2003/08/04 23:12:06  hcho
 *  LOG: add CANT_START state to the ASP
 *  LOG:
 *  LOG: Revision 7.2.2.2  2003/07/11 21:13:34  labuser
 *  LOG: DUNA/DAVA functionality is added
 *  LOG:
 *  LOG: Revision 7.2.2.1  2003/04/04 21:39:49  pmandal
 *  LOG: Port UAL callback changes.
 *  LOG:
 *  LOG: Revision 7.2  2002/12/30 17:30:31  lbana
 *  LOG: propagating bug fixes in PR6.1 to current.
 *  LOG:
 *  LOG: Revision 7.1.2.2  2003/03/19 21:48:27  lbana
 *  LOG: added context for the callback manager.
 *  LOG:
 *  LOG: Revision 7.1.2.1  2002/12/26 23:31:57  lbana
 *  LOG: ual debug string added to enable printing of AS/ASP table
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.9  2002/07/24 19:50:31  lbana
 *  LOG: add aspinfo element for as info in parser extension.
 *  LOG:
 *  LOG: Revision 6.8  2002/07/22 22:35:43  lbana
 *  LOG: v12 error codes
 *  LOG:
 *  LOG: Revision 6.7  2002/07/18 18:27:57  lbana
 *  LOG: add family string to the parse
 *  LOG:
 *  LOG: Revision 6.6  2002/07/18 15:30:03  labuser
 *  LOG: Add NI String for AS Info
 *  LOG:
 *  LOG: Revision 6.5  2002/07/12 18:46:48  ngoel
 *  LOG: dd function prototype
 *  LOG:
 *  LOG: Revision 6.4  2002/05/15 16:47:58  lbana
 *  LOG: added localPC in ual parser info
 *  LOG:
 *  LOG: Revision 6.3  2002/05/15 16:14:53  lbana
 *  LOG: Remove conflict and Add localPC string.
 *  LOG:
 *  LOG: Revision 6.2  2002/05/13 21:09:45  lbana
 *  LOG: uals in current starts from here
 *  LOG:
 *  LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 *  LOG: Begin PR7.
 *  LOG:
 *  LOG: Revision 5.2  2001/09/05 17:16:41  lbana
 *  LOG: parser strings are updated for PR5
 *  LOG:
 *  LOG: Revision 5.1  2001/08/16 20:45:58  mmiers
 *  LOG: Start PR6.
 *  LOG:
 *  LOG: Revision 4.3  2001/07/26 16:49:41  mmiers
 *  LOG: UAL needed engine parse help.  Added this as an example.
 *  LOG:
 *  LOG: Revision 4.2  2001/07/26 14:57:16  labuser
 *  LOG: Added SUA V5 to current.
 *  LOG:
 *  LOG: Revision 3.7.2.3  2001/06/22 20:56:28  labuser
 *  LOG: Include its_callback.h
 *  LOG:
 *  LOG: Revision 3.7.2.2  2001/06/22 20:52:50  labuser
 *  LOG: Added Callback Manager.
 *  LOG:
 *  LOG: Revision 3.7.2.1  2001/06/20 15:43:04  labuser
 *  LOG: Add reference to SUA Management Class.
 *  LOG:
 *  LOG: Revision 3.7  2001/04/11 18:54:36  omayor
 *  LOG: Added more stings to the INI file.
 *  LOG:
 *  LOG: Revision 3.6  2001/04/03 19:15:34  omayor
 *  LOG: Add the M3UA class and changed some INI strings.
 *  LOG:
 *  LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 *  LOG: Convert RCSID to ident.
 *  LOG:
 *  LOG: Revision 3.4  2001/02/05 22:05:02  mmiers
 *  LOG: Move log back (more complaints than applause).
 *  LOG: Make C service take event log.
 *  LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 *  LOG: bindings).
 *  LOG:
 *  LOG: Revision 3.3  2001/01/30 18:11:34  mmiers
 *  LOG: Demo log at bottom of file.
 *  LOG:
 *  LOG: Revision 3.2  2000/12/19 20:12:56  mmiers
 *  LOG: Spelling
 *  LOG:
 *  LOG: Revision 3.1  2000/12/19 17:43:33  mmiers
 *  LOG: Start testing.
 *  LOG:
 *                 
 ****************************************************************************/
#ifndef UAL_H
#define UAL_H


#include <its.h>
#include <its_callback.h>
#include <its_object.h>
#include <its_route.h>
#include <sua.h>
#include <its_trace.h>

#include <stdio.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined (WIN32)

#if defined UAL_IMPLEMENTATION
#define UALDLLAPI __declspec (dllexport)
#else
#define UALDLLAPI __declspec (dllimport)
#endif

#else
#define UALDLLAPI
#endif


/*
 * class name and Parser extension
 * parameters for ual.
 */
#define UAL_CLASS_NAME     "UAL Manager"


/*
 * resource file keys
 */

#define UAL_HEARTBEAT_STRING           "heartBeat"
#define UAL_HB_INTERVAL_STRING         "hbInterval"
#define UAL_ACK_TIMER_STRING           "ackTimer"
#define UAL_PENDING_TIMER_STRING       "pendingTimer"
#define UAL_AS_TRAFFIC_MODE_STRING     "asTrafficMode"
#define UAL_INTERWORK_MODE_STRING      "interworkingMode"
#define UAL_PROPAG_MGNT_MSG_STRING     "propagateMgnt"
#define UAL_AS_INFO_STRING             "asInfo"
#define UAL_APPL_SERVER_STRING         "AsInfo"
#define UAL_ASP_ID_STRING              "aspId"
#define UAL_N_REDUNDANCY_STRING        "n"
#define UAL_K_REDUNDANCY_STRING        "k"
#define UAL_RETRY_COUNTER_STRING       "retryCount"
#define UAL_IS_MEMBER_STRING           "isMember"
#define UAL_ASP_CAPABILITIES_STRING    "aspCapabilities"
/* 
 * Element Name 
 */
#define UAL_ASP_INFO_STRING            "AspInfo"
#define UAL_HOME_STRING                "Home"
/* 
 * member of HOME element 
 */
#define IP_ADDRESS_STRING              "ipAddress"
#define UAL_NI_STRING                  "networkIndicator"
       
#define UAL_LOAD_SHARE_MODE_STRING     "loadShareMode"
#define UAL_OVERIDE_MODE_STRING        "overRideMode"
#define UAL_BROADCAST_MODE_STRING      "broadcast"

#define UAL_SG_MODE_STRING             "sgMode"
#define UAL_ASP_MODE_STRING            "endPointMode"
#define UAL_IPSP_MODE                  "ipspMode"

#define UAL_CAPAB_CLASS0_STRING         "class0"
#define UAL_CAPAB_CLASS1_STRING         "class1"
#define UAL_CAPAB_CLASS2_STRING         "class2"
#define UAL_CAPAB_CLASS3_STRING         "class3"

#define UAL_VERSION_STRING             "version"
#define UAL_DEBUG_FLAG_STRING          "debug"

#define UAL_MGNT_CLASS_NAME            "UAL_Manager"
#define UAL_VALUE_STRING               "value"

#define UAL_LOCAL_PC_STRING            "localPointCode"

UALDLLAPI extern CALLBACK_Manager*     __UAL_MgntCallBack;
UALDLLAPI extern CALLBACK_Manager*     __UAL_MTP3MgntCallBack;

/*
 * class record
 */
UALDLLAPI extern ITS_Class itsUAL_Class;

#define UAL_PROT_VER1                   0x01

/* message class */
#define UAL_CLASS_MGMT                  0x00
#define UAL_CLASS_SNM                   0x02                 
#define UAL_CLASS_ASPSM                 0x03
#define UAL_CLASS_ASPTM                 0x04
#define UAL_CLASS_RKM                   0x09

/* management message */
#define UAL_MSG_ERR                     0x00
#define UAL_MSG_NOTIFY                  0x01


/* Application Server Process Maintenance messages (ASPM) */
#define UAL_MSG_ASPUP                   0x01
#define UAL_MSG_ASPDN                   0x02
#define UAL_MSG_BEAT                    0x03
#define UAL_MSG_ASPUP_ACK               0x04
#define UAL_MSG_ASPDN_ACK               0x05
#define UAL_MSG_BEAT_ACK                0x06

/* Application Server Process Traffic Maintenance (ASPTM) */
#define UAL_MSG_ASPAC                   0x01
#define UAL_MSG_ASPIA                   0x02
#define UAL_MSG_ASPAC_ACK               0x03
#define UAL_MSG_ASPIA_ACK               0x04

/* Routing Key Management (RKM) */
#define UAL_MSG_REG_REQ                 0x01
#define UAL_MSG_REG_RSP                 0x02
#define UAL_MSG_DEREG_REQ               0x03
#define UAL_MSG_DEREG_RSP               0x04

/*  
 * Interworking Mode
 */ 
typedef enum 
{
    UAL_ITW_SG,
    UAL_ITW_ASP,
    UAL_ITW_IPSP
}
UAL_ITW_MODE;

/* UAL common message Header */
typedef struct
{
    ITS_OCTET   version;
    ITS_OCTET   reserved;  /* SHOULD be all 0 */
    ITS_OCTET   msgClass;
    ITS_OCTET   msgType;
    ITS_UINT    msgLen;    /* msg data + sizeof(UAL_MSG_HDR) */   
}
UAL_MSG_HDR;


/* UAL common (M3UA/SUA) parameters */
#define UAL_PRM_MSG_HDR                 0x0000
#define UAL_PRM_INFO_STR                0x0004
#define UAL_PRM_ROUT_CTX                0x0006
#define UAL_PRM_DIAGNOSTIC              0x0007
#define UAL_PRM_HEARTBEAT_DATA          0x0009
#define UAL_PRM_TRAFFIC_MODE            0x000B
#define UAL_PRM_ERROR_CODE              0x000C
#define UAL_PRM_STATUS                  0x000D
#define UAL_PRM_ASP_ID                  0x0011
#define UAL_PRM_AFFECTED_PC             0x0012

#define UAL_PRM_NET_APP                 0x0200
#define UAL_PRM_ROUTING_KEY             0x0207
#define UAL_PRM_REG_RES                 0x0208
#define UAL_PRM_DREG_RES                0x0209
#define UAL_PRM_LRK_ID                  0x020A
#define UAL_PRM_DPC                     0x020B
#define UAL_PRM_SI                      0x020C
#define UAL_PRM_SSN                     0x020D
#define UAL_PRM_OPC_LIST                0x020E
#define UAL_PRM_CIC_RANGE               0x020F
#define UAL_PRM_CORL_ID                 0x0211
#define UAL_PRM_REG_STATUS              0x0212
#define UAL_PRM_DREG_STATUS             0x0213


/*
 * Info String 
 */

#define UAL_MAX_INFO_STR_LEN   254 

typedef struct
{
    ITS_OCTET   infoStr[UAL_MAX_INFO_STR_LEN];
}
UAL_INFO_STR;

/*
 * ASP Identifier
 */

typedef struct
{
    ITS_UINT    aspId;
}
UAL_ASP_ID;

/*
 * HeartBeat Data
 */

#define UAL_MAX_HB_DATA_LEN 254

typedef struct
{
    ITS_OCTET   HBData[UAL_MAX_HB_DATA_LEN];
}
UAL_HB_DATA;


/*
 * Routing Key
 */

#define UAL_MAX_RK_LEN 256

typedef struct
{
    ITS_OCTET   RKData[UAL_MAX_RK_LEN];
}
UAL_RK;


/*
 * Local RK Identifier
 */

typedef struct
{
    ITS_UINT    localRKid;
}
UAL_LOCAL_RK_ID;

/*
 * Traffic Mode
 */

typedef struct
{
    ITS_UINT    tm;
}
UAL_TRAFFIC_MODE;

#define UAL_OVERRIDE_MODE               0x01
#define UAL_LOADSHARE_MODE              0x02
#define UAL_BROADCAST_MODE              0x03


/* 
 * UAL Point Code Representation 
 */

typedef struct
{
    ITS_OCTET           mask;
    ITS_OCTET           pc[3];
}
UAL_PC;


/* TODO we flipped the bytes here think about this more (bakeoff change) */
#define UAL_SET_PC_VALUE_CCITT(x,v)                                      \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),                             \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0x3FU)))

#define UAL_GET_PC_VALUE_CCITT(x)                                       \
    ((((x).pc[1] & 0x3FU) << 8) | ((x).pc[2]))

#define UAL_SET_PC_VALUE_ANSI(x,v)                                      \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),                           \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),                    \
     ((x).pc[0] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))

#define UAL_GET_PC_VALUE_ANSI(x)                                        \
    ((x).pc[2] | ((x).pc[1] << 8) | ((x).pc[1] << 16))

#define UAL_SET_PC_VALUE_PRC(x,v)                                      \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),                           \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),                    \
     ((x).pc[0] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))

#define UAL_GET_PC_VALUE_PRC(x)                                        \
    ((x).pc[2] | ((x).pc[1] << 8) | ((x).pc[0] << 16))


/* 
 * NetWork Appearance
 */

typedef struct
{
    ITS_UINT    na;
}
UAL_NET_APP;

/*
 * Service Indicator
 */

#define UAL_MAX_SI_NUM 256

typedef struct
{
    ITS_OCTET   siList[UAL_MAX_SI_NUM];
}
UAL_SI_LIST;


/*
 * OPC List
 */

#define UAL_MAX_OPC_LIST_LEN (4*68)

typedef struct
{
    UAL_PC   opcList[UAL_MAX_OPC_LIST_LEN];
}
UAL_OPC_LIST;


/*
 * CIC Ranges
 */

#define UAL_MAX_CIC_RG_LEN  (4*8)

typedef struct
{
    UAL_PC        opc;
    ITS_USHORT     loCIC;
    ITS_USHORT     hiCIC;
}
UAL_CIC_RANGE;

typedef struct
{
    UAL_CIC_RANGE  cicList[UAL_MAX_CIC_RG_LEN];
}
UAL_CIC_RG_LIST;


/*
 * Registration Result
 */
#define UAL_MAX_REG_RES_LEN               24

typedef struct
{
    ITS_OCTET regRes[UAL_MAX_REG_RES_LEN];    
}
UAL_REG_RESULT;


/* 
 * registration Status
 */
typedef struct
{
    ITS_UINT regStat;
}
UAL_REG_STATUS;

#define UAL_REG_STAT_SUCCESS            0x00
#define UAL_REG_STAT_ERR_UNKNOWN        0x01
#define UAL_REG_STAT_ERR_INV_DPC        0x02
#define UAL_REG_STAT_ERR_INV_NA         0x03
#define UAL_REG_STAT_ERR_INV_RK         0x04
#define UAL_REG_STAT_ERR_PERM_DNY       0x05
#define UAL_REG_STAT_ERR_NO_SUP_UNI_RK  0x06
#define UAL_REG_STAT_ERR_RK_NOT_PROV    0x07
#define UAL_REG_STAT_ERR_UNSUFF_RES     0x08
#define UAL_REG_STAT_ERR_NO_SUP_RK_FLD  0x09
#define UAL_REG_STAT_ERR_INVALID_THM    0x0A




#define UAL_MAX_RCTXT_LEN (4*4)

typedef struct
{
    ITS_OCTET rCtxt[UAL_MAX_RCTXT_LEN];
}
UAL_RCTXT;


/* 
 * Deregistration Status
 */

typedef struct
{
    ITS_UINT deregStat;
}
UAL_DEREG_STATUS;

#define UAL_DREG_STAT_SUCCESS           0x00
#define UAL_DREG_STAT_ERR_UNKNOWN       0x01
#define UAL_DREG_STAT_INV_RCTXT         0x02
#define UAL_DREG_STAT_PERM_DNY          0x03
#define UAL_DREG_STAT_NOT_REG           0x04
#define UAL_DREG_STAT_ASP_ACT_FOR_RCTX  0x05     


/*
 * Deregistration Result
 */

#define UAL_MAX_DREG_RES_LEN              16

typedef struct
{
    ITS_OCTET derRes[UAL_MAX_DREG_RES_LEN];    
}
UAL_DEREG_RESULT;



/* 
 * Error Code
 */

typedef struct
{
    ITS_UINT eCode;
}
UAL_ERROR_CODE;

#define UAL_ERR_INV_VESION              0x01
#define UAL_ERR_UNSUP_MSG_CLASS         0x03
#define UAL_ERR_UNSUP_MSG_TYPE          0x04
#define UAL_ERR_UNSU_THM                0x05
#define UAL_ERR_UNEPECTED_MSG           0x06
#define UAL_ERR_PROT_ERROR              0x07
#define UAL_ERR_INV_STREAM_ID           0x09
#define UAL_ERR_REF_MGNT_BLOCK          0x0D
#define UAL_ERR_ASP_ID_REQUIERED        0x0E
#define UAL_ERR_INV_ASP_ID              0x0F
#define UAL_ERR_INV_PARM_VALUE          0x11
#define UAL_ERR_PARM_FIELD_ERR          0x12
#define UAL_ERR_UNEXP_PARAM             0x13
#define UAL_ERR_DEST_STAT_UNKNOW        0x14
#define UAL_ERR_INV_NET_APP             0x15
#define UAL_ERR_MISSING_PARAM           0x16
#define UAL_ERR_RKEY_CHNG_REF           0x17
#define UAL_ERR_INV_ROUT_CTXT           0x19
#define UAL_ERR_NO_CONF_AS_FOR_ASP      0x1a
#define UAL_ERR_NO_SSN_UNKNOWN          0x1b

    

/*
 * Diagnostic Information
 */

#define UAL_MAX_DIAG_INFO_LEN           40

typedef struct
{
    ITS_OCTET   diagnosticInfo[UAL_MAX_DIAG_INFO_LEN];
}
UAL_DIAG_INFO;


/*
 * Status Type
 */

typedef struct
{
    ITS_USHORT  type;
    ITS_USHORT  id;
}
UAL_STATUS_TYPE;

#define UAL_ST_TYPE_AS_STAT_CHG         0x01
#define UAL_ST_TYPE_OTHER               0x02

#define UAL_ST_ID_AS_INACTIVE           0x02
#define UAL_ST_ID_AS_ACTIVE             0x03
#define UAL_ST_ID_AS_PENDING            0x04

#define UAL_ST_ID_INSUF_ASP             0x01
#define UAL_ST_ALT_ASP_ACTIVE           0x02
#define UAL_ST_ASP_FAILURE              0x03


/*
 * Application Server structure
 */

typedef struct
{
    ROUTE_CRITERIA    style;          /* see its_route.h */
    UAL_PC            dpc;
    ITS_UINT          na;             /* network appearance */ 
    UAL_OPC_LIST      opc;
    ITS_OCTET         numOPC;
    UAL_SI_LIST       si;
    ITS_OCTET         numSI;
    UAL_CIC_RG_LIST   cicRange;
    ITS_OCTET         numCICRange;
    ITS_UINT          tm;             /* traffic Mode */
    SUA_ADDRS         *srcAddr;       /* SUA specific */
    SUA_ADDRS         *destAddr;      /* SUA specific */
    ITS_USHORT        addrRangeLen;   /* SUA specific */
    SUA_ADDRS_RANGE   *addrRange;     /* SUA specific */
    SUA_ASP_CAPAB     *aspCapab;      /* SUA specific */
}
UAL_AS_DEF;


/*
 * UAL IES
 */
typedef struct
{
    ITS_USHORT   param_id;      
    ITS_USHORT   param_length;
    union
    {
        UAL_MSG_HDR            msgHeader;
        UAL_INFO_STR           infoStr;
        UAL_ASP_ID             aspId;
        UAL_HB_DATA            hbData;
        UAL_RK                 rkData;
        UAL_LOCAL_RK_ID        localRkId;
        UAL_TRAFFIC_MODE       trafMode;
        UAL_PC                 dpc;
        UAL_NET_APP            netApp;
        UAL_SI_LIST            siList;
        UAL_OPC_LIST           opcList;
        UAL_CIC_RG_LIST        cicList;
        UAL_REG_RESULT         regResult;
        UAL_REG_STATUS         regStat;
        UAL_RCTXT              rCtxt;
        UAL_DEREG_STATUS       deregStat;
        UAL_DEREG_RESULT       deregRes;
        UAL_ERROR_CODE         errCode;
        UAL_DIAG_INFO          diagInfo;
        UAL_STATUS_TYPE        statusType;
    }
    param_data;
}
ITS_UAL_IE;

#define ITS_MAX_UAL_IES   32

typedef struct
{
    ITS_USHORT*    mParam;
    int           nmParam;
    ITS_USHORT*    oParam;
    int           noParam;
}
UAL_MSG_DESC;

/* message descriptors */
extern UALDLLAPI UAL_MSG_DESC UAL_ASPUP_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_UPACK_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_ASPDN_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_DNACK_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_HEARTBEAT_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_HEARTBEAT_ACK_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_ASPAC_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_ASPAC_ACK_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_ASPIA_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_ASPIA_ACK_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_NTFY_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_ERR_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_REGREQ_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_SUA_REGREQ_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_REGRSP_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_SUA_REGRSP_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_DREGREQ_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_DREGRSP_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_SUA_DUNA_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_SUA_DAVA_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_SUA_DAUD_Desc;
extern UALDLLAPI UAL_MSG_DESC UAL_SUA_SCON_Desc;


/*
 * Codecs
 */
UALDLLAPI int 
UAL_EncodeMsg(ITS_UAL_IE *ies, int ieCount,ITS_EVENT *event,
              UAL_MSG_DESC* desc);

UALDLLAPI int 
UAL_DecodeMsg(ITS_UAL_IE *ies, int *ieCount, ITS_EVENT *ev,
              UAL_MSG_DESC *desc);

UALDLLAPI int 
UAL_RegisterApplicationServer(UAL_AS_DEF *as, ITS_USHORT size, 
                              ITS_USHORT instance, ITS_UINT *rctxt);

UALDLLAPI int 
UAL_DeregisterApplicationServer(ITS_UINT *rCtxt, ITS_USHORT size,
                                ITS_USHORT instance);
/*
 * Helper functions
 */

UALDLLAPI ITS_UAL_IE* 
UAL_FindUALIE(ITS_UAL_IE *ies, int ieCount, ITS_USHORT paramId);

UALDLLAPI int 
UAL_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, 
                         ITS_UINT *rkList, int size);

UALDLLAPI int 
UAL_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, 
                         ITS_UINT *rkList, int *size);

UALDLLAPI int 
UAL_EncodeRoutingKey(UAL_AS_DEF *as, ITS_UAL_IE *ie, ITS_UINT *localRctxt);

UALDLLAPI void 
PRINT_EVENT(ITS_EVENT* evt);

/*
 * Dump functions for AS/ASP tables
 */
UALDLLAPI void 
UAL_DumpASTable(char** dump_str);
UALDLLAPI void 
UAL_DumpASPTable(char** dump_str);
UALDLLAPI void 
UAL_DumpCfg(char **dump_string);

/*
 * user knows by which API they implemented with
 */
#define ITS_UAL           ITS_UAL
#define UAL_MAX_HOME_NUM  8       /* num of ip addresses */
#define UAL_MAX_ASP_IN_AS 16

/*
 * Engine parser Information.
 */
typedef struct 
{
    ITS_UINT  aspId;
    char*     home[UAL_MAX_HOME_NUM];
    ITS_UINT  ipAddrCount;
}
ASPParserInfo;

typedef struct _ualKeyList
{
    struct _ualKeyList*  next;
    ITS_UINT             rkey;             /* AS routing context */
    char*                asTrafficMode;    /* AS traffic mode */
    ITS_BOOLEAN          isMember;         /* is member of AS */
    ITS_USHORT           nActives;         /* N+K redundant config */
    ITS_USHORT           kStandby;
    ITS_UINT             ni;
    char*                family;
    ASPParserInfo        asp_info[UAL_MAX_ASP_IN_AS];
    ITS_UINT             aspCount;
    SUA_ASP_CAPAB        aspCapab;
} 
UAL_KeyInfo;

typedef struct
{
    ITS_BOOLEAN  useSCMG;
    ITS_BOOLEAN  hb;              /* Heartbeat Set on/off */
    ITS_UINT     hbInterval;      /* Heartbeat interval in secs */
    ITS_UINT     ackTimer;        /* Ack timer interval in secs */
    ITS_UINT     pendingTimer;    /* Pending timer inerval in secs */
    char*        interworkingMode;/* Inetrworking mode (SG/ASP/IPSP) */
    ITS_UINT     version;         /* Version identifier */
    ITS_UINT     aspId;           /* ASP Id */
    ITS_UINT     localPC;         /* local pc for linksets */
    ITS_UINT     debug;           /* enable ual local debug info */
    UAL_KeyInfo* keyList;         /* List of AS in this ASP */
}
UAL_ParseInfo;

typedef enum _UAL_MTP3_TYPE
{
    UAL_MTP3_RESULT,    /* Callback Result type */
    UAL_MTP3_PAUSE,     /* DUNA invoked from M3UA */
    UAL_MTP3_RESUME,    /* DAVA invoked from M3UA */
    UAL_MTP3_STATUS,    /* SCON invoked from M3UA */
    UAL_TRANS_IND       /* Transport Up/Down Indication */
}
UAL_MTP3_TYPE;

typedef struct _UALMgntData
{
    UAL_MTP3_TYPE type;
    union
    {
        struct
        {
            ITS_UINT pc;
            ITS_UINT rkey;
        }
        mtp3_info;

        struct
        {
            ITS_INT   result;
            ITS_OCTET sio;
            ITS_OCTET pad[3];
            ITS_UINT  pc;
        }
        info;
    }
    cdata;
}
UALMgntData;

/*
 * ASP states
 */

typedef enum
{
    UAL_ASP_DOWN,
    UAL_ASP_INACTIVE,
    UAL_ASP_ACTIVE,
    UAL_ASP_CANT_START,
    UAL_ASP_UP
}
UAL_ASP_STATE;

/*
 * AS states
 */

typedef enum
{
    UAL_AS_DOWN,
    UAL_AS_INACTIVE,
    UAL_AS_ACTIVE,
    UAL_AS_PENDING,
    UAL_AS_REG,
    UAL_AS_DREG
}
UAL_AS_STATE;

typedef enum
{
    UAL_CB_INVALID_CTXT,
    UAL_CB_ASP_CTXT,
    UAL_CB_AS_CTXT,
    UAL_CB_RT_FAIL_CTXT
}
UAL_CB_CTXT_TYPE;

typedef struct
{
    UAL_CB_CTXT_TYPE  type;

    union
    {
        struct
        {
            UAL_ASP_STATE state;  /* ASP State */
            ITS_UINT      aspId;  /* ASP Identifier */
        }
        asp;

        struct
        {
            UAL_AS_STATE state;  /* UAL AS State */
        }
        as;
        struct
        {
            int len;
            ITS_OCTET data[500];
        }
        msu;
    }
    data;

    ITS_UINT   rkey;
    ITS_USHORT trId;
    ITS_OCTET  pad[2];
}
UAL_CB_Context;

typedef enum _UAL_PEG_ID
{
    UAL_PEG_UP_ID,
    UAL_PEG_UPACK_ID,
    UAL_PEG_DN_ID,
    UAL_PEG_DNACK_ID,
    UAL_PEG_AC_ID,
    UAL_PEG_ACACK_ID,
    UAL_PEG_IA_ID,
    UAL_PEG_IAACK_ID,
    UAL_PEG_NOTIFY_ID,
    UAL_PEG_DAUD_ID,
    UAL_PEG_DAVA_ID,
    UAL_PEG_DUPU_ID,
    UAL_PEG_DATA_IN_ID,
    UAL_PEG_DATA_OUT_ID,
    UAL_PEG_ERR_IN_ID,
    UAL_EEG_ERR_OUT_ID,
    UAL_PEG_SCON_IN_ID,
    UAL_PEG_SCON_OUT_ID,
    UAL_PEG_INVALID_ID,

    ALL_UAL_PEGS = 99
}
UAL_PEG_ID;

typedef struct _UAL_MIB_STATS
{
    ITS_USHORT  transportID; /* Transport ID for the remote Association */
    ITS_USHORT  appMode;     /* Application runnin mode (ASP, SGP or IPSP) */
    ITS_UINT    aspUp;       /* count of ASP_UPs on this transport */
    ITS_UINT    aspUpAck;    /* count of ASP_UP_ACKs received on trid */
    ITS_UINT    aspDn;       /* count of ASP_DOWNs */
    ITS_UINT    aspDnAck;    /* count of ASP_DOWN_ACKs */
    ITS_UINT    aspAc;       /* count of ASP_ACTIVEs */
    ITS_UINT    aspAcAck;    /* count of ASP_ACTIVE_ACKs */
    ITS_UINT    aspIa;       /* count of ASP_INACTIVEs */
    ITS_UINT    aspIaAck;    /* count of ASP_INACTIVE_ACKs */
    ITS_UINT    aspNotify;   /* count of ASP_NOTIFYs */
    ITS_UINT    daud;        /* count of DAUDs */
    ITS_UINT    dava;        /* count of DAVAs */
    ITS_UINT    duna;        /* count of DUNAs */
    ITS_UINT    dupu;        /* count of DUPUs */
    ITS_UINT    drst;        /* count of DRSTs */
    ITS_UINT    dataIn;      /* count of DATA packets received */
    ITS_UINT    dataOut;     /* count of DATA packets sent */
    ITS_UINT    errIn;       /* count of ERRORs received */
    ITS_UINT    errOut;      /* count of ERRORs sent */
    ITS_UINT    sconIn;      /* count of SCONs received */
    ITS_UINT    sconOut;     /* count of SCONs sent */
}
UAL_MIB_STATS;

/************************************************************************
 *
 * INFO: This function returns statistics of MGMT, SSNM, ASPSM, ASPTM,
 *       and Transfer messages.
 *
 * Input parameters:
 *        trId   : Transport instance number for the remote association.
 * Input/Output parameters:
 *        *stats : Pointer to the sizeof(UAL_MIB_STATS) structure.
 * Return value:
 *        ITS_SUCCESS : On success it retrieves the data for the
 *        transport ID, and anyother value is considered as failure.
 *
 ***********************************************************************/
UALDLLAPI ITS_INT
UAL_GetMIBStats(ITS_USHORT trId, UAL_MIB_STATS *stats);

/************************************************************************
 *
 * INFO: This function returns statistics of MGMT, SSNM, ASPSM, ASPTM,
 *       and Transfer messages specific request.
 *
 * Input parameters:
 *        trId   : Transport instance number for the remote association.
 *        which  : Peg id to retrieve the count.
 * Input/Output parameters:
 *        *value : Pointer to the sizeof(ITS_INT).
 * Return value:
 *        ITS_SUCCESS : On success it retrieves the data for the
 *        matching transport ID, and peg id and anyother value
 *        is considered as failure.
 *
 ***********************************************************************/
UALDLLAPI ITS_INT
UAL_GetPegInfo(ITS_USHORT trid, UAL_PEG_ID which, ITS_INT *value);

/************************************************************************
 *
 * INFO: This function returns statistics of MGMT, SSNM, ASPSM, ASPTM,
 *       and Transfer messages.
 *
 * Input parameters:
 *        trId   : Transport instance number for the remote association.
 * Input/Output parameters:
 *        *value : Pointer to the sizeof(ITS_INT).
 * Return value:
 *        ITS_SUCCESS : On success it retrieves the data for the
 *        matching transport ID, and peg id and anyother value
 *        is considered as failure.
 *
 ***********************************************************************/
UALDLLAPI ITS_INT
UAL_GetAllPegInfo(ITS_USHORT trid, UAL_MIB_STATS *value);

/************************************************************************
 *
 * INFO: This function clears statistics of MGMT, SSNM, ASPSM, ASPTM,
 *       and Transfer messages for specific request.
 *
 * Input parameters:
 *        trId   : Transport instance number for the remote association.
 *        which  : Peg id for retrieving count.
 * Input/Output parameters:
 *        None
 * Return value:
 *        ITS_SUCCESS : On success it clears the data for the
 *        matching transport ID and peg id, and anyother value is
 *        considered as failure.
 *
 ***********************************************************************/
UALDLLAPI ITS_INT
UAL_ClearPegInfo(ITS_USHORT trid, UAL_PEG_ID which);

/************************************************************************
 *
 * INFO: This function clears statistics of MGMT, SSNM, ASPSM, ASPTM,
 *       and Transfer messages.
 *
 * Input parameters:
 *        trId   : Transport instance number for the remote association.
 * Input/Output parameters:
 *        None
 * Return value:
 *        ITS_SUCCESS : On success it clears the data for the
 *        matching transport ID and peg id, and anyother value is
 *        considered as failure.
 *
 ***********************************************************************/
UALDLLAPI ITS_INT
UAL_ClearAllPegInfo(ITS_USHORT trid);

/*
 * Pegs for M3UA/SUA. Application user should not be using following
 * functions or data structes. For statistics user should look into
 * the following APIs and structures.
 *
 * typedef enum _UAL_PEG_ID
 * { } UAL_PEG_ID;
 *
 * typedef struct _UAL_MIB_STATS
 * { } UAL_MIB_STATS;
 *
 * ITS_INT
 * UAL_GetMIBStats(ITS_USHORT trId, UAL_MIB_STATS *stats);
 *
 * ITS_INT
 * UAL_GetPegInfo(ITS_USHORT trid, UAL_PEG_ID which, ITS_INT *value);
 *
 * ITS_INT
 * UAL_ClearPegInfo(ITS_USHORT trid, UAL_PEG_ID which, ITS_INT *value);
 *
 */
typedef struct _UAL_PEG_List
{
    struct _UAL_PEG_List *next;
    UAL_MIB_STATS        stats;
}
UAL_PEG_List;

typedef struct _UAL_PEG_Mgr
{
    char         *name; /* Manager name */
    ITS_INT      count; /* number of transports */
    UAL_PEG_List *list; /* list of stats for each transport */
}
UAL_PEG_Mgr;

extern UAL_PEG_Mgr *ualPegMgr;

UALDLLAPI ITS_INT
UALPEGMgr_CreatePegMgr();

UALDLLAPI ITS_INT
UALPEGMgr_DestroyPegMgr();

UALDLLAPI UAL_MIB_STATS*
UALPEGMgr_GetStats(ITS_USHORT trid);

UALDLLAPI ITS_INT
UALPEGMgr_AddElement(ITS_USHORT trid);

UALDLLAPI ITS_INT
UALPEGMgr_RemoveElement(ITS_USHORT trid);

#define UALPEGMGR_NUM_TRANS(x)  x->count
#define UALPEGMGR_NAME(x)       x->name
#define UALPEGMGR_STAT_LIST(x)  x->list
#define UAL_CB_CTXT_TYPE(ctx)      ((UAL_CB_Context *)ctx)->type
#define UAL_CB_CTXT_ASP_STATE(ctx) ((UAL_CB_Context *)ctx)->data.asp.state
#define UAL_CB_CTXT_ASP_ID(ctx)    ((UAL_CB_Context *)ctx)->data.asp.aspId
#define UAL_CB_CTXT_AS_STATE(ctx)  ((UAL_CB_Context *)ctx)->data.as.state
#define UAL_CB_CTXT_RKEY(ctx)      ((UAL_CB_Context *)ctx)->rkey
#define UAL_CB_CTXT_TRANS_ID(ctx)  ((UAL_CB_Context *)ctx)->trId
#define UAL_CB_CTXT_MSU_LEN(ctx)   ((UAL_CB_Context *)ctx)->data.msu.len
#define UAL_CB_CTXT_MSU_DATA(ctx)  ((UAL_CB_Context *)ctx)->data.msu.data

/* more helper functions */

UALDLLAPI int 
UAL_GetASPState(ITS_USHORT trid, UAL_ASP_STATE *state);

UALDLLAPI int SendASPActive(ITS_UINT rCtxt);
UALDLLAPI int SendASPInactive(ITS_UINT rCtxt);
UALDLLAPI int UAL_GetRoutingKeys(ITS_UINT *rkey, ITS_OCTET *rCount);

UALDLLAPI ITS_BOOLEAN 
UAL_IsRCtxtValid(ITS_UINT rctxt);

UALDLLAPI ITS_OCTET 
UAL_GetIntWorkingMode();


#define UAL_FILE_STRING                ITS_FILE_STRING
#define UAL_STDOUT_STRING              ITS_STDOUT_STRING
#define UAL_SYSLOG_STRING              ITS_SYSLOG_STRING

/*
 * tracing strings
 */
#define UAL_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define UAL_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define UAL_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define UAL_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING

#define UAL_CRITICAL_STRING        ITS_CRITICAL_STRING
#define UAL_ERROR_STRING           ITS_ERROR_STRING
#define UAL_WARNING_STRING         ITS_WARNING_STRING
#define UAL_DEBUG_STRING           ITS_DEBUG_STRING

/*
 * the global control flag defined for UAL
 */
extern TRACE_Data* UAL_TraceData;

/*
 * trace possibilities:
 */
#define UAL_TRACE_CRITICAL  0
#define UAL_TRACE_ERROR     1
#define UAL_TRACE_WARNING   2
#define UAL_TRACE_DEBUG     3

/* Macros for UAL traces */

#define UAL_CRITICAL(args) \
    TRACE(UAL_TraceData, UAL_TRACE_CRITICAL, args)

#define UAL_ERROR(args) \
    TRACE(UAL_TraceData, UAL_TRACE_ERROR, args)

#define UAL_WARNING(args) \
    TRACE(UAL_TraceData, UAL_TRACE_WARNING, args)

#define UAL_DEBUG(args) \
    TRACE(UAL_TraceData, UAL_TRACE_DEBUG, args)

#define UAL_TRACE_CRITICAL_FILE    ".ual-traceCritical"
#define UAL_TRACE_ERROR_FILE       ".ual-traceError"
#define UAL_TRACE_WARNING_FILE     ".ual-traceWarning"
#define UAL_TRACE_DEBUG_FILE       ".ual-traceDebug"


#if defined(__cplusplus)

}
#endif

#endif /*UAL_H*/
