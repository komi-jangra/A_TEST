/*se ts=2************************************File Header*****
  File Name      :    bpmDiaglib.h 
Purpose        :		 
Project        :    DIAGNOSTIC
Subsystem      :    OAM	
Author         :    
CSCI id        :
Version        :    V0.1
 *************************************************************/
#ifndef DIAG_H
#define DIAG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_syslog.h>
/*#include <ipcfrm_extern.h> */
#include "sysxxx_slotid.h"
#include "oamsxxx_hashdef.h"
#include "oamxxx_tableapidefs.h"
#include "sysxxx_msgopcode.h"

#include <dbsxxx_tabledef.h>
#include <dbsxxx_commondefs.h>
#include <DBLIBError.h>
#include <CLIB.h>

#define BPM_FAILURE   9

/* Hash defs & structures used by diag lib internally */
#define CARD_SERIAL_NUM_SIZE     15
#define DIAG_REPORT_PATH_LEN     100
#define DIAG_FILE_LEN       50
#define MAX_TCT_ID          50
#define MAX_TEST_ID         12 
#define MAX_ARGS            8
#define DIAG_FAN_SPEED           3000 // TBD
#define FLASH_PATTERN       0x51
#define DATA_PATTERN        0x12
#define FLASH_DATA_SIZE     1024
#define EIC_DSP0            1
#define EIC_DSP1            2
#define DSP_CHAN_NUM        0
#define ICC_I2C_REG         1
#define EIC_EXT_IFC_PORT    8

#define ICC0                    3
#define ICC1                    4
#define EIC0                    5
#define EIC1                    6
#define PSU0                    0xE
#define PSU1                    0xF
#define FAN_TRAY_NORTH          1
#define FAN_TRAY_SOUTH          2

#define MAX_TCT_ID_STRING_LEN 20
#define MAX_TEST_RESULT 4
#define MAX_RESULT_STRING_LEN 20


#define TEST_COMPLETE  1
#define TEST_ABORT     2
#define TEST_CANCEL    3

/* Diagnostic Error Code String base and End */
#define ERR_CODE_DIAG_BASE     ERROR_PEER_CARD_NOT_CONNECTED 
#define ERR_CODE_DIAG_END      ERROR_PIPE_CREATE_FAILED

#define ERR_CODE_FRAMER_BASE (OAM_BPM_MF_ERROR_BASE - ERR_CODE_DIAG_END + ERR_CODE_DIAG_BASE)

#define NUM_DIAG_ERRCODE    200
#define ERROR_CODE_LEN      100

#define ACTIVE_PATTERN   0x55
#define STANDBY_PATTERN  0x00
#define UNUSED_PATTERN   0xFF

#define REPLACEPSUSLOTID(PSUSLOTID)  ((PSUSLOTID) == (PSU0) ? 1 : 2)

/* diagGlobal var struct */
typedef struct
{
  I_U8 filePath[DIAG_REPORT_PATH_LEN];
  I_U8 fileName[DIAG_FILE_LEN]; /* file name of last opened file */
  I_U8 repititionCnt; /* repetition count of last received request */
  I_U8 suppress; /* repetition count of last received request */
  I_U8 TCT_String[MAX_TCT_ID][MAX_TCT_ID_STRING_LEN];
  I_U8 TCID_String[MAX_TEST_ID][MAX_RESULT_STRING_LEN];
  I_U8 testResultString[MAX_TEST_RESULT][MAX_RESULT_STRING_LEN];
  I_U8 TestResp[2][20]; /* pass/fail */
  I_U16 errCode; /* error code from bpm, this will be used to declaire final result*/
  I_U16 ApiId; /* ICC/EIC/PSU/FAN TRAY */
  I_U32 fileAction;
  I_U8 errCodeString[NUM_DIAG_ERRCODE][ERROR_CODE_LEN];
  I_U32 duration;
}sLibGlobalParam;

typedef struct
{
  I_U8 paramBits;
}sParamKeySet;

typedef struct 
{
  I_U8    chassisFrameId;
  I_U8    slotId;
  I_U16    testReference;
  I_U32    iccTestType;
  I_U32    iccTestId;
  I_U16    action;
  I_U16    numArg;
  I_U32    args[12];
}IccDiagReq;

typedef struct 
{
  I_U8    chassisFrameId;
  I_U8    slotId;
  I_U16    testReference;
  I_U32    eicTestType;
  I_U32    eicTestId;
  I_U16    action;
  I_U16    numArg;
  I_U32    args[12];
}EicDiagReq;
typedef struct 
{
  I_U8    chassisFrameId;
  I_U8    slotId;
  I_U16    testReference;
  I_U32    psuTestType;
  I_U32    psuTestId;
  I_U16    action;
  I_U16    numArg;
  I_U32    args[12];
}PwrSupDiagReq;
typedef struct 
{
  I_U8    chassisFrameId;
  I_U8    fanTrayId;
  I_U8    fanId;
  I_U16    testReference;
  I_U32    fanTrayTestType;
  I_U32    fanTrayTestId;
  I_U16    action;
  I_U16    numArg;
  I_U32    args[12];
}FanTrayDiagReq;
typedef struct 
{
  I_U8    chassisFrameId;
  I_U8    slotId;
  I_U16    testReference;
  I_U32    obmTestType;
  I_U32    obmTestId;
  I_U16    action;
  I_U16    numArg;
  I_U32    args[12];
}ObmDiagReq;
typedef struct 
{
  I_U8    chassisFrameId;
  I_U8    slotId;
  I_U16    testReference;
  I_U32    obfTestType;
  I_U32    obfTestId;
  I_U16    action;
  I_U16    numArg;
  I_U32    args[12];
}ObfDiagReq;

/* end here */

/* hash define & structures exported to diag lib user application */
#define DIAG_LIBINIT_SUCCESS 1
#define DIAG_LIBINIT_FAILURE  0
#define DIAG_PARSE_SUCESS  1
/* diag test result response struct */
typedef struct
{
  I_U32                 testType;
  I_U32                 testID;
  I_U8                   frameID;
  I_U8                  slotID;
  I_U16                testRef;
  I_U8                  testResult;  /* TEST_PASS / TEST_FAIL / TEST_ABORTED / TEST_IN_PROGRESS */
  I_U8                   testReportPath[DIAG_REPORT_PATH_LEN];
  I_U8                   testReportFileName[DIAG_FILE_LEN];;
}sDiagnosticTestResult;

/* end here */ 

/* Diag lib api detail */


I_U32 initDiagLibrary();
/* api to initialize diag library */

I_U8* formBpmDiagMsg(I_U16 ApiId,  void *mibptr, I_U32 *respLen,  I_U32 fileAction); 
/* `here apiId is meant for ICC/EIC/PSU/FANTRAY, mibptr is equal to omc ptr & respLen 
   is return len for formed bpm cmd structure as input to api form api` , ` returning cmd ptr`
   & `fileAction param i.e. Append/Close` */

sDiagnosticTestResult* parseBpmDiagResp(void *BpmRespPtr, I_U32 action);
/* i/p ptr will be bpm response ptr */

void freeLibDiagPtr(void *ptr);
/* this is to free the returned diag test result pointer */

/* *** */


/* diag lib internal maniputalation functions */

void writeEicDetailInFile(void *BpmRespPtr);
void writeFanTrayDetailInFile(void *BpmRespPtr);
void writeIccDetailInFile(void *BpmRespPtr);
void writePsuDetailInFile(void *BpmRespPtr);
void initTestResultString();
void doFileResultManipulation(I_U32 slotId, I_U32 frameId);
I_U32 doFileOperation(void *BpmRespPtr, I_U8 testResult, I_U32 action);
I_U32 getCardSerialNum(I_U32 slotId, I_U32 frameId, I_U8* cardSerialNum);
void initTestCaseString();
void initParamData();
void  initGlobalStructData();
void printErrCode(void *BpmRespPtr);
void initErrCodeString();

/* ***** */

#endif /* DIAG_H */

