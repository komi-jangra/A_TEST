/*******************************************************************************
**      FILE NAME:
**          bssap_msgstruct.h
**
**      DESCRIPTION:
**              Defines Datastructure used to define Bssap Interface messages.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
#ifndef __BSSAP_MSGSTRUCT_H_
#define __BSSAP_MSGSTRUCT_H_
#if 0
/*Comments: SysHdr will replace with SysHdr 
            New Message Opcode  Application -> BSSAP   #define CSAPP_BSSAP_UNIT_DATA_REQ  1
						New Message Opcode   BSSAP --> Application #define BSSAP_CSAPP_UNIT_DATA_IND  2 
*/ 
 
typedef struct
{
   I_U8         apiId;      /*  Api Id =0xC1  (fixed) */
   I_U8         version;    /*  Version =0x01 (fixed) */
   I_U8         noOfElement;/*  #Element =0x03 (fixed)  */
   I_U16        len;        /*  Length of message includes(Bssap Header + Data) */
} SysHdr;
#endif


typedef struct
{
  I_U8      rfu1;    /* Reserved for future use Default Value (0) */
  I_U8      entity;  /* entityId  - refer sysxxx_proc.h           */
  I_U8      clsId;   /* Tau Model specific - Default Value (0)    */
  I_U8      rfu2;    /* Reserved for future use Default Value (0) */
  I_U32     inst;    /* Tau Model Specific - Default Value (0)    */
}BsIfAddr;

typedef struct
{
  BsIfAddr    src;       /* Source Entity*/
  BsIfAddr    dest;      /* Destination Entity */
  I_U16      msgType;   /* message type  - refer sysxxx_msgopcode.h*/
  I_U8       verId;     /* version Id shall be used for Rolling S/W upgrade - default value(0)*/
  I_U8       priority;  /* SA_MSG_MESSAGE_HIGHEST_PRIORITY 0
                           SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  I_U32      msgLen;    /* Total Length of the message including SysHdr */
  I_U32      txId;      /* Interface specific - Default Value(0) */
}BsIfHdr;


typedef struct
{
    I_U8         gcnId;
    I_U32        callRefId;
    I_U32        appId;
    I_U8         msgDisc;
    I_U8         msgType;
    I_U8         len;           /*  Changed to I_U8 from I_U16 */
    I_U8         data[BSSAP_DATA_LEN];
} BssapData;

typedef struct
{
    I_U8        gcnId;
    I_U8        msgDisc;
    I_U32       callRefId;
    I_U32       appId;
    I_U8        refusalCause; /* cause for sccp con Refuse */
    I_U8        releaseCause; /* cause for sccp con Release  */
} SccpData;

typedef struct
{
    I_U8        elmtId;
    I_U16       cic;
} BssapCic;

typedef struct
{
    I_U8        elmtId;
    I_U8        length;
    I_U8        range;
    I_U8        status[32];
} BssapCicList;

typedef struct
{
    I_U8        elmtId;
    I_U32       callIdentifier;
} CallId;

typedef struct
{
    I_U8        elmtId;
    I_U8        length;
    I_U32       callIdentifier[62];
} CallIdList;

typedef struct
{
    I_U8        gcnId;
    I_U32       callRefId;
    I_U32       appId;
    I_U8        msgDisc;
    I_U8        msgType;
    I_U8        errorCode;
    union
    {
        BssapCic         cicInfo;      
        BssapCicList     cicList;       
        CallId      callIdentifier;        
        CallIdList  callIdList;     
    } e;
} ErrorData;

typedef struct
{ 
   I_U8        gcnId;
   I_U8        msgDisc;
   I_U8        msgType;
   I_U32       pointCode;
   I_U8        ssn;
} StatusData;

typedef struct
{ 
   I_U8        gcnId;
   I_U8        msgDisc;
   I_U8        msgType;
    union
    {
        BssapCic         cicInfo;      
        CallId      callIdentifier;        
        CallIdList  callIdList;     
    } t;
} TimeoutData;

typedef struct
{ 
   I_U8        ssn;
   I_U16       pointCode;
} SccpMgmtData;

typedef struct
{ 
   I_U16       pointCode;
} Mtp3MgmtData;

typedef struct
{ 
   I_U8       status;
   I_U8       cngLevel;
} Mtp3StatusData;

typedef struct
{ 
   I_U8        gcnId;
   I_U8        msgDisc;
   I_U8        statusCode;
   union
   {
       SccpMgmtData    sccpMgmtData;
       Mtp3MgmtData    mtp3MgmtData;
       Mtp3StatusData  mtp3StatusData;
   } m;
} MgmtData;

typedef struct
{
    I_U8         gcnId;
    I_U8         msgDisc;
    I_U8         msgType;
    I_U8         bssapCause;     
    I_U8         len;   
    I_U8         data[BSSAP_DATA_LEN];
} FailureData; 

typedef struct
{
    I_U8  msgTag;
    union
    {
        BssapData       bssapData;      /*  CP_BSSAP_MSG_TAG */
        SccpData        sccpData;       /*  CP_BSSAP_SCCP_TAG */
        ErrorData       errData;        /*  CP_BSSAP_PROTOCOL_TAG */
        StatusData      statusData;     /*  CP_BSSAP_NETWORK_TAG */
        TimeoutData     timeoutData;    /*  CP_BSSAP_TIMEOUT_TAG */
        MgmtData        mgmtData;       /*  CP_BSSAP_MANAGEMENT_TAG */
        FailureData     failureData;    /*  CP_BSSAP_FAILURE_TAG CS3.0*/
    } u;
} Data;

typedef struct
{
   SysHdr  syshdr;
/*   BsIfHdr  syshdr;*/
   Data      data;  
} BssapifMsg;


#endif /* __BSSAP_MSGSTRUCT_H */

