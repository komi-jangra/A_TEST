#ident "$Id: itu-sccpstat.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $"

#include <sccp_intern.h>

#if defined ANSI
#include <ansi/sccp.h>
#define ITS_ISUP_SRC ITS_ISUP_ANSI_SRC
#elif defined CCITT
#define ITS_ISUP_SRC ITS_ISUP_CCITT_SRC
#endif



typedef struct _SCCPInfo
 {
   struct _SCCPInfo *next;
   ITS_OCTET SSN;
   ITS_UINT PC;
   ITS_OCTET PCFlag;
   ITS_OCTET SSNFlag;
   ITS_OCTET Ind;
   ITS_BOOLEAN  IsSTP;
 }
 SCCP_StatInfo ;
 	
int SCCP_SetGenLocalConf(ITS_OCTET Ind,ITS_UINT PC);
int SCCP_SetGenConf(SCCP_StatInfo Sccp_Info);

//int SCCP_GetGenConf(ITS_UINT PC,ITS_OCTET SSN);

int SCCP_GetGenConf(ITS_UINT PC,SCCP_StatInfo *Sccp_Info);

int SCCP_GetNodeStatus(SCCP_StatInfo *Sccp_Info);
int GetSsnStatus_DSM (ITS_UINT DPC, ITS_UINT OPC, ITS_OCTET ni,
                  ITS_BOOLEAN * pauseFlag, ITS_BOOLEAN * sspFlag,
                  ITS_OCTET Ssn);

int SCCP_EventProcforReturn(ITS_SCCP_IE *ies, int ieCount,
	                                           SCCP_StatInfo *Sccp_Info,ITS_BOOLEAN IsGtt,ITS_OCTET Reason);





