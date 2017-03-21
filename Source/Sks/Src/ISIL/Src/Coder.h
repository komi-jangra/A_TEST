#include<stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/times.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>


#include <its.h>
#include <its++.h>
#include <its_callback.h>
#include <its_assertion.h>
#include <engine++.h>
#include<mtp3_sn.h>
#include<mtp2_cmn.h>
#include <isup_variants.h>
#include <its_sctp.h>
#include <engine.h>
#include <sctp_msgs.h>
#include <its_route_rwlock.h>



extern"C"
{
#define USER_DATA (0X01U)
#define LONG_DATA (0X02U)
#define CDA_DATA (0X03U)
#define CPA_DATA (0X04U)
#ifdef CCITT
#define SCCP_HEADER (0x0aU)
#endif
#ifdef ANSI
#define SCCP_HEADER (0x0dU)
#endif
#define TCAP_HEADER (0x05U)
#define MAX_OFFSET (0x08U)
#define DEFAULT_OFFSET                       (0x03U)
//#define MAX_USERDATA_LEN                      255
#define MAX_USERDATA_LEN                      230
#define FIXEDLEN_OFFSET                       0x02 
#define MAX_VAR_ARGS                          0x03
#define MAND_ARGS_2                           0x02
#define MAND_ARGS_1                           0x01
#define ISIL_UDT_OFFSET_3                     0x03 
#define ISIL_UDT_OFFSET_4                     0x04
#define ISIL_PROTOCOLCLASS_0                  0x00
#define ISIL_PROTOCOLCLASS_1                  0x01
#define ISIL_DFLT_HOPCTR                      0x08
#define ISIL_DFLT_NOOPT                       0x01
#define ISIL_RETURNOPT_OP                     0x22
#define ISIL_SEQCONTRL_OP                     0x23
//#define ISIL_PROTOCLASS_OP                    0x28
#define ISIL_SEGMNT_OP                        0x10
#define ISIL_SEGMNT_OP_LEN                    0x04
#define ISIL_SEGMNT_VALUE                     0x80
#define OFFSET_0                              0x00 
#define OFFSET_1                              0x01  
#define OFFSET_2                              0x02
#define OFFSET_3                              0x03
#define OFFSET_4                              0x04
#define ISIL_GTT_MAX_DATA                     160
//#define ISIL_MAX_DATA                         255
#define ISIL_MAX_DATA                         230


/*ITS_OCTET M[3]={CDA_DATA ,CPA_DATA ,USER_DATA};*/


/*Structure for USER Data encoding and decoding the SCCP data*/


typedef struct

 {
  ITS_OCTET data[255];
 }
  ISIL_DATA;


 typedef struct
 {
  ITS_OCTET data[3954];
 }
  ISIL_LONG_DATA;


 typedef struct
 {
   ITS_OCTET protocolclass;
 }
  ISIL_PROT_CLASS;


 typedef struct
 {
   ITS_OCTET hopcount;
 }
  ISIL_HOP_COUNT;


typedef struct
{
 ITS_OCTET paramid;
 ITS_USHORT paramlength;
  union
 {
   ISIL_DATA userdata;
   ISIL_LONG_DATA longData;
   ISIL_PROT_CLASS protocolclass;
   ISIL_HOP_COUNT hopcount;
  }
 param_data;

} ISIL_IE;

typedef struct
 {

  ITS_OCTET total;
  ITS_OCTET mandargs;  
 }
 ISIL_ARGS;

int ISIL_Encoder(ITS_EVENT*,ISIL_IE*,ISIL_ARGS);
int ISIL_Decode(ITS_EVENT*,ISIL_IE*,ISIL_ARGS *args);
/*Patch:Itika:8-june-10:Updated for ANSI:SCCP CL*/
#ifdef CCITT
int ISILgethdr_CCITT(ISIL_IE *ie ,ITS_UINT* opc ,ITS_UINT* dpc,ITS_OCTET* sio ,ITS_OCTET *nicda ,ITS_OCTET *nicpa);
#endif
#ifdef ANSI
int ISILgethdr_ANSI(ISIL_IE *ie ,ITS_UINT* opc ,ITS_UINT* dpc,ITS_OCTET* sio ,ITS_OCTET *nicda ,ITS_OCTET *nicpa);
#endif
/*End:Updated for ANSI:SCCP CL*/

int
EVENT_Encoder(ITS_OCTET *cdaptr ,ITS_OCTET *cpaptr ,ITS_OCTET *Usrdatptr,ITS_OCTET **OPptr ,ITS_OCTET msgtype,ITS_EVENT *event,ITS_OCTET *noargs,ITS_OCTET *mandptr);

int
OP_Decoder(ITS_EVENT event ,ITS_OCTET **OPptr,ITS_OCTET *noargs);

int
Userdata_Decoder(ITS_EVENT event ,ITS_OCTET **Usrdatptr);

int
CPA_Decoder(ITS_EVENT event ,ITS_OCTET **cpaptr);

int
CDA_Decoder(ITS_EVENT event ,ITS_OCTET **cdaptr);

int
Args_Decoder(ITS_EVENT event,ITS_OCTET *nmargs);

int
MandFix_Decoder(ITS_EVENT event ,ITS_OCTET **mandptr);


int Segment(ITS_USHORT ,ITS_OCTET *,ITS_OCTET);




}
