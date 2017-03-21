#include <stdio.h>
#include <dbc_serv.h>


#define IMR_TRUE  0x01
#define IMR_FALSE 0x00
#define IMR_GTT_GET_DPC_SSN_TABLE 0x01 
#define IMR_GTT_GET_DPC_TABLE     0x00
#define IMR_GTT_GET_SSN_TABLE     0x02

/*error case*/
#define IMR_ENTRYNOFOUND  100 
#define IMR_ENTRYFOUND    101
#define IMR_ENALRDYEXIST  102 
#define IMR_ENTRYADDSUCC  103 
#define IMR_ENTRYADDFAIL  104 
#define IMR_ENTRYREMSUCC  105 
#define IMR_ENTRYREMFAIL  106
#define NOSSNALLOW        00
#define SSNALLOW          01
#define ISIL_TRACE_DEBUG        0x01
#define ISIL_TRACE_ERROR        0x02
#define ISIL_TRACE_WARNING      0x03
/*char ISIL_ADDENTRY;
char ISIL_DELENTRY;
char ISIL_FREEENTRY;*/
typedef struct
{
 int primarydpc;
 int secondarydpc;
 int routeflag;
 char ssn;
 char str[16];
 char gttstring[16];
 
}
ISIL_gttInfo;

typedef struct  
{
  int primarydpc;
  int secondarydpc;
  int routeflag;
  char ssn;
  char primaryssnflag;
  char secondaryssnflag;
}ISIL_DPC_SSN ;

typedef struct gttlist
{
   struct gttlist *next[10];
//   ISIL_DPC_SSN  dpc_ssn;
   void *Entry;
}
ISIL_GTT_LIST;
//ISIL_GTT_LIST *gtt_list;

int ISIL_setgttentry(ISIL_gttInfo *gttInfo);
int ISIL_remgttentry(ISIL_gttInfo *gttInfo);

ISIL_GTT_LIST *ISIL_BuildTree(ISIL_GTT_LIST *gttentry,ISIL_gttInfo *gttInfo);
ISIL_GTT_LIST *ISIL_DeleteTree(ISIL_GTT_LIST *gttentry,ISIL_gttInfo *gttInfo,char index);
