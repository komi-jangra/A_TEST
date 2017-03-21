/*******************************************************************************
**      FILE NAME:
**          bs_trace.x
**
**      DESCRIPTION:
**              Trace Related Macros defines required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/



#include "s7_typ.h" 

#define BSCORE(a,b,c,d,e,f,g,h)                                    \
 if(b==BSCNTRL_CORE_ENBSAP || b==BSCNTRL_CORE_DISSAP)               \
                  BsShCntrl_Print(a,b,f);                            \
            else  if(a==CRITICAL)                                     \
                     BsErr_Print(a,b,g,h);                             \
            else if( a== DEBUG )                                         \
                    BsDebug_Print(a,b,d,e,f);                             \
            else if(b==BSDATA_CORE_SEND || b==BSDATA_CORE_RECV)         \
                    BsData_Print(a,b,d,e);                               \
            else  BsConf_Print(a,b,c); 

#define  BSDEBUGPRINT(STR,args...)    LOG_PRINT(DEBUG,STR,##args)
#define  BSINFOPRINT(STR,args...)    LOG_PRINT(INFO,STR,##args)
#define  BSERRORPRINT(STR,args...)    LOG_PRINT(CRITICAL,STR,##args)


typedef struct _print
{
unsigned char timerId;
unsigned char resetRetryCount;
unsigned char resetIPRetryCount;
unsigned char resetCktRetryCount;
unsigned char BlockReqRetryCount;
unsigned char unBlockReqRetryCount;
unsigned char cktGrpblockReqRetryCount;
unsigned char cktGrpUnblockReqRetryCount;
unsigned char bndRetryCnt;
int dpc;
int intfId;
int opc;
int cic;
int callrefId;
int appId;
int sapId;
char pcstatus;
char ssnstatus;
char bscId;
char ssn;
char ni;
char pclass;
char swtch;
char disc;
S16bit suId;                   /* service user id */
S16bit spId;                   /* service provider id */
S16bit suInstId;             /* service user instance id */
S16bit spInstId;
U8bit selector;
U16bit dstProcId;              /* destination processor id (U16) */
U16bit srcProcId;
/*Pst pst;*//* Commented by Amaresh */
int len;
int msgType;
char buffer[250];
}
PrintData;

#if 0
int BsConf_Print(int typeflag,int stringtype,BsMngmt *cfg);
int BsData_Print(int typeflag,int stringType,PrintData *data,int cause);
int BsShCntrl_Print(int typeflag,int stringtype,ShtCntrlReqEvnt *reqInfo);
int BsErr_Print(int typeflag,int stringtype,char *str,int value);
void BS_Dump(unsigned char *arr,int len);
int BsDebug_Print(int typeflag,int stringType,PrintData *data,int cause,char *str);
#endif /* Commented by Amaresh */



