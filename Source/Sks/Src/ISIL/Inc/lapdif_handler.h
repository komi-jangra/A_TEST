/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.2  2007/10/22 01:43:08  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2007/09/24 05:33:45  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/06/25 12:04:19  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:19:28  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1  2006/01/25 05:33:56  yranade
 * LOG: First Cut (badri)
 * LOG:
 * LOG: Revision 1.1  2005/11/24 06:05:22  yranade
 * LOG: Create Baseline GSM-BSC Infrastructure.
 * LOG:
 *
 * ID: $Id: lapdif_handler.h,v 1.2 2007-10-22 06:04:12 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: lapdif_handler.h,v 1.2 2007-10-22 06:04:12 bsccs2 Exp $"
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BSC_LAPDIF_HANDLER_H
#define BSC_LAPDIF_HANDLER_H

/**
 * msgGroupId defines
 */
#define LAPD_LINK_MANAGEMENT_MESSAGE    0x01
#define LAPD_DATA_MESSAGE               0x02

/**
 * lapdLinkStatus defines
 */
#define LAPD_LINK_STATUS_REQ  0x64
#define LAPD_LINK_STATUS_RESP 0x65
#define LAPD_LINK_RELEASE     0x66
#define LAPD_LINK_ESTABLISH   0x67
#define LAPD_LINK_UP          0x68
#define LAPD_LINK_DOWN        0x69
#define MAX_TeiWithTs         5

#define LAPD_GET              1
#define LAPD_DEL              2
#define LAPD_MODIFY           3
#define LAPD_ADD              4
 
#define MAX_APPTEI 255
#define MAXTSVAL 128

struct conf_data  // Configuration data structure       
{
    struct conf_data* nxt;
    unsigned char  ts;          // Time Slot                 
    unsigned char  lapdTei;     // TEI towards LAPD Stack       
    unsigned char  appTei;      // TEI towards Application       
    unsigned char  sapi1;       // SAPI 1
    unsigned char  sapi2;       // SAPI 2
    unsigned char  tsflag;      // TS Flag 
    unsigned char  teiflag;     // Tei Flag 
    unsigned char  opflag;      // Operation flag
    unsigned int   nfd;         // File Descriptor
    unsigned int   ifc;
    unsigned int   link_status1;
    unsigned int   link_status2;
    unsigned int   link_status;
    //unsigned int   teiOffset;   // tei offset value to store at driver for each ts  
};

typedef struct   // Configuration data structure for list operation      
{
    unsigned char  ts;          // Time Slot                 
    unsigned char  lapdTei;     // TEI towards LAPD Stack       
    unsigned char  appTei;      // TEI towards Application       
    unsigned char  sapi1;       // SAPI 
    unsigned char  sapi2;       // SAPI 
    unsigned char  tsflag;      // TS Flag 
    unsigned char  lapdteiflag; // config flag set one to config lapd tei 
    unsigned char  appteiflag;  // config flag set one to config app tei 
    unsigned char  ifcFlag;     // Set flag to configure ifc 
    unsigned char  opflag;      // Operation flag
    unsigned int   nfd;         // File Descriptor
    unsigned int   ifc;
    unsigned int   link_status1; /* flag to modify status */
    unsigned int   link_status2; /* flag to modify status */ 
    unsigned int   link_status;  /* flag to modify status */ 
    //unsigned int   teiOffset;// tei offset value to store at driver for each tei of ts  
} op_conf_data;
#ifdef anand
typedef struct
{
    unsigned char  ts;          // Time Slot                 
    unsigned char  appTei;      // TEI towards Application       
    unsigned char  dummy1;      /* for packing */     
    unsigned char  dummy2;           
}ts_teiCfg;
#endif
// struct ts_teiCfg TS_DATA[]; /*temporary*/
typedef struct
{
    int  TS_DATA[MAX_APPTEI]; 
    int maxFd;          // max fd value                 
    int noOfFd;          // total fd opened                 
    fd_set  allLapdFd;  // lapd Fd set
} lapdGlobalData;

lapdGlobalData lapGData;       



/**
 * The ISIL Header structure 
 */
typedef struct
{
    unsigned char   api_id;	// Api Id fixed to 0xc2 for LAPD
    unsigned char   version;	// Version fixed to 0x01 
    unsigned char   element;	// Number of element fixed to 0x03	   
    unsigned short  length;	// Total Length of Message (Msg Header + Data)

} CS2_SYS_HDR;

/**
 * The structure that is exchanged between LAPD handler
 * and BSC Application throught socket events.
 */
typedef struct
{
    CS2_SYS_HDR     cs2SysHdr;	// ISIL Header
    unsigned char   msgGroupId; // to know the status of LAPD link
    unsigned char   TEI; // The TEI of the Abis message
    unsigned char   SAPI; // The SAPI, the message came from
    unsigned short  dataLen; // The length of data
    unsigned char   data[256]; // The actual Abis message as bytes

} LAPD_MSG_CS2;

typedef struct
{
unsigned short   lapdTimerT200;
unsigned short   lapdTimerT203;
unsigned short   N200; /*T200 timer retries */
unsigned short   dummy;
}LapdTmrCfg;


typedef struct
{
 unsigned char   ts;       /*LAPD PP-TS */
 unsigned char   satFlag;  /*1=True  0=False*/
 unsigned short  dummy;    /*padding */
}LapdTsParm;

typedef struct
{
unsigned char     msgGrpId;
unsigned char     msgType;
LapdTmrCfg  lapdTimerDefault;
LapdTmrCfg  lapdTimerSatellite;
unsigned int   noOfLapdTs;
LapdTsParm     lpdTsdetail[1];
}ISILLapdTimerConfig;

typedef struct
{
  unsigned char     msgGrpId;
  unsigned char     msgType;
  unsigned int      count;             /*Range 1..5 */
  unsigned char       appTeiInfo[5];
  unsigned char       pegResetFlag;

} LapdPegsShow_t;



typedef struct
{
unsigned char     sapi; /* 0 & 62 */
unsigned char     dummy;
unsigned short    dummy1;
unsigned int    pegLapdInfoSend;
unsigned int    pegLapdInfoRecv;
unsigned int    pegLapdUiSend;
unsigned int    pegLapdUiRecv;
unsigned int    pegLapdRrCSend;
unsigned int    pegLapdRrCRecv;
unsigned int    pegLapdRrRSend;
unsigned int    pegLapdRrRRecv;
unsigned int    pegLapdRejCSend;
unsigned int    pegLapdRejCRecv;
unsigned int    pegLapdRejRSend;
unsigned int    pegLapdRejRRecv;
unsigned int    pegLapdRnrCSend;
unsigned int    pegLapdRnrCRecv;
unsigned int    pegLapdRnrRSend;
unsigned int    pegLapdRnrRRecv;
unsigned int    pegLapdMsgDecodeFail;
unsigned int    pegLapdMsgEncodeFail;
}LapdPegInfo;


typedef struct
{
unsigned char              applTei;
unsigned char              dummy1;
unsigned short             dummy2;
LapdPegInfo pegInfo[2];
}LapdPeg;

typedef struct
{
unsigned int          count;                  /* Range 1..5 */
LapdPeg lapdPeg[5];       /* Max data. 156*5 = 780*/
}LapdPegResponse;


typedef struct
{
unsigned int          count;                  /* Range 1..5 */
LapdPeg lapdPeg[1];       /* Max data. 156*5 = 780*/
}LapdPegR;



/**
 *  APPID between SCM & LAPDIF
 */
#define LAPD_SCM_IF_ID	 0xD1

/**
 *  Msg Group Ids between SCM & LAPDIF    
 */

#define	LAPD_SCM_CFG_MSG     0x01
#define	LAPD_SCM_PEGS_MSG    0x02


#define	LAPD_SCM_TMR_MSG     0x03
#define	LAPD_SCM_ALARM_MSG   0x04
#define	LAPD_SCM_PEGS_NACK   0x06
#ifdef LAPD_HA
#define	LAPD_CONFIG_COMPLETE 0x05
#endif

/**
 *  Msg Types between SCM & LAPDIF	
 */

#define	LAPD_SCM_CFG_ADD_TS      0x01
#define	LAPD_SCM_CFG_REM_TS      0x02
#define	LAPD_SCM_CFG_ADD_TEI     0x03
#define	LAPD_SCM_CFG_REM_TEI     0x04
#define	LAPD_SCM_CFG_ADD_SAPI    0x05
#define	LAPD_SCM_CFG_REM_SAPI    0x06
#define	LAPD_SCM_PEGS_SHOW       0x07
#define	LAPD_SCM_PEGS_CLEAR      0x08
#define	LAPD_SCM_TMR_SET         0x09
#define	LAPD_SCM_TMR_TRY         0x0A
#define	LAPD_SCM_ALARM_IND       0x0B

/*  Response Value    */

#define   LAPD_SCM_SUCCESS              0x00
#define   LAPD_SCM_ERROR                0x01


/**
 * The structure that is exchanged between LAPD handler
 * and SCM throught socket events.
 */
typedef struct
{
    unsigned char  appId;  // APPID -> LAPD_SCM_IF_ID
    unsigned char  dataLen;  // The length of data
    unsigned char  data[256];  

} SCM_MSG_CS2;


#endif
