/*************************************************************************
Purpose :define the structure used in GT Translation.

Input:

Output:



***************************************************************************/


#include <stdio.h>
/*#ifdef  CPLUSPLUS
extern "C"
{
#endif 
*/
#include "GTT_ReadInfor.h"

#define MAX_TRANSRULE (0x04U) 
#define  MAX_IND        0x04
/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
#define MAX_TRANSFUNC (0x0fU) 
#define  MAX_TT         0x0f
#define  MAX_EN_SH      0x0f
#define  MAX_NP         0x0f
#define  MAX_MAXD       0x0f
#define  MIN_MAXD       0x0f
#define  SKIP_DGT       0x0f
#endif
#ifdef ANSI
#define MAX_TRANSFUNC (0x5cU) 
#define  MAX_TT         0x5c
#define  MAX_EN_SH      0x5c
#define  MAX_NP         0x5c
#define  MAX_MAXD       0x5c
#define  MIN_MAXD       0x5c
#define  SKIP_DGT       0x5c
#endif
/*End:Updated for ANSI SCCP-CL*/

#define  MAX_NAI        0x0f
#define  MAX_GTI        0x04
#define  MAX_OPCODE     0x04

#define IMR_GTI_1   0x01
#define IMR_GTI_2   0x02
#define IMR_GTI_3   0x03
#define IMR_GTI_4   0x04

/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
#define  IMR_TT0     0x00
#define  IMR_TT1     0x01
#define  IMR_TT2     0x02
#define  IMR_TT3     0x03
#define  IMR_TT17    0x11
#define  IMR_TT40    0x28
#endif

#ifdef ANSI
#define  IMR_TT1     0x01
#define  IMR_TT2     0x02
#define  IMR_TT3     0x03
#define  IMR_TT4     0x04
#define  IMR_TT5     0x05
#define  IMR_TT6     0x06
#define  IMR_TT7     0x07
#define  IMR_TT8     0x08
#define  IMR_TT9     0x09
#define  IMR_TT10    0x0a
#define  IMR_TT11    0x0b
#define  IMR_TT12    0x0c
#define  IMR_TT13    0x0d
#define  IMR_TT14    0x0e
#define  IMR_TT15    0x0f
#define  IMR_TT16    0x10
#define  IMR_TT17    0x11
#define  IMR_TT28    0x1c
#define  IMR_TT29    0x1d
#define  IMR_TT30    0x1e
#define  IMR_TT31    0x1f
#define  IMR_TT251   0xfb
#define  IMR_TT253   0xfd
#endif
/*End:Updated for ANSI SCCP-CL*/

/*Patch:Itika:14-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
#define IS_DPC 0x01
#define IS_SSN 0x02
#endif

#ifdef ANSI
#define IS_DPC 0x02
#define IS_SSN 0x01
#endif
/*End:Updated for ANSI SCCP-CL*/

#define first_entry 0x03
#define next_entry 0x02

#define IMR_TRUE 0x01
#define IMR_FALSE 0x00

#define IMR_DPC_TABLE 0x02
#define IMR_DPC_SSN_TABLE 0x01
#define IMR_SSN_TABLE 0x03

#define  IMR_ENCODSCH_1  0x01 
#define  IMR_ENCODSCH_2  0x02
#define  IMR_ENCODSCH_3  0x03

#define  IMR_NUMPLAN_0   0x00
#define  IMR_NUMPLAN_1   0x01
#define  IMR_NUMPLAN_2   0x02
#define  IMR_NUMPLAN_6   0x06
#define  IMR_NUMPLAN_7   0x07

#define  IMR_NAI_4       0x04

#define IMR_MAXDIGT_8   0x08
#define IMR_MAXDIGT_4   0x04
#define IMR_MAXDIGT_6   0x06

#define IMR_MINDIGT_1  0x01
#define IMR_MINDIGT_2  0x02
#define IMR_MINDIGT_3  0x03
#define IMR_MINDIGT_5  0x05

#define IMR_SKIPDGT    0x00

#define ISIL_TRACE_DEBUG        0x01
#define ISIL_TRACE_ERROR        0x02
#define ISIL_TRACE_WARNING      0x03

typedef struct
{
ITS_OCTET gtt_digits[20];
}
IMR_GTT_GTAI;

typedef struct
{
  ITS_OCTET TransType;
  ITS_OCTET Encod_scheme;
  ITS_OCTET Num_Plan;
  ITS_OCTET NAI;
}
IMR_GTT_TransFunc_I0;


typedef struct
{
  ITS_OCTET Oper_code;
  ITS_OCTET  MinDigits;
  ITS_OCTET MaxDigits;
  ITS_OCTET Skipdigits;/*it will provide the last offset in the table*/
}
IMR_GTT_TransRule;

/*this structure will used for transFucns  per gti*/ 

typedef struct
{
  ITS_OCTET gti;
  ITS_OCTET AddIn;
  ITS_OCTET ssn;
  ITS_OCTET gt_len;
  IMR_GTT_TransFunc_I0 TF_in;
  IMR_GTT_GTAI gt_Info;
}
IMR_GTT_IN;


typedef struct
{
  ITS_OCTET gti;
  ITS_OCTET AddIn;
  ITS_OCTET dpc; 
  ITS_OCTET ssn;
  IMR_GTT_TransFunc_I0 TF_out;  
  ITS_OCTET gt_len;
  IMR_GTT_GTAI gt_Info; 
}
IMR_GTT_OUT;




/*Patch:Itika:14-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
typedef struct
{
ITS_OCTET TransType;
ITS_OCTET Encod_scheme;
ITS_OCTET Num_Plan;
ITS_OCTET NAI;
IMR_GTT_TransRule  TransRule[4];
}
IMR_GTT_TransFunc;


/*this structure will used for transFucns  per gti*/ 

typedef struct
{
ITS_OCTET Gti;
IMR_GTT_TransFunc TransFunc[15];
}
IMR_GTT_GTI;

IMR_GTT_GTI Set_GTI;


int
IMR_GTT_GetTransRule(IMR_GTT_TransFunc TransFunc ,IMR_GTT_TransRule *Rule);

#endif

#ifdef ANSI
typedef struct
{
ITS_OCTET TransType;
ITS_OCTET Encod_scheme;
ITS_OCTET Num_Plan;
IMR_GTT_TransRule  TransRule[4];
}
IMR_GTT_TransFunc;


/*this structure will used for transFucns  per gti*/ 

typedef struct
{
ITS_OCTET Gti;
IMR_GTT_TransFunc TransFunc[92];
}
IMR_GTT_GTI;

IMR_GTT_GTI Set_GTI;


int
IMR_GTT_GetTransRule_ANSI(IMR_GTT_TransFunc TransFunc ,IMR_GTT_TransRule *Rule);

#endif
/*End:Updated for ANSI SCCP-CL*/
int
IMR_GTT_GetTransFunc(IMR_GTT_IN Gtt_in, IMR_GTT_TransRule *Rule);

ISIL_DPC_SSN *
IMR_GTDigts_Translation(IMR_GTT_TransRule *Rule,ITS_OCTET  *gti_string);

int
IMR_GTT_Implemt();


int IMR_GTT_SetTransRulePerFunc();

int Free_MemList();
