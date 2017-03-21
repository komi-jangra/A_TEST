#include <sysxxx_typedef.h>
#include <nwstkscm_hashdefs.h>
#include <nwstkscm_msgdef.h>
#include <trace.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/times.h>
#include <bssap_pegs.h>
#include <its.h>
#include <its++.h>




//#include <its_route.h>
#include <its_route_rwlock.h>
#include <engine.h>

#include <its_timers.h>
#include <mtp2_cmn.h>
#include<mtp3_intern.h>
#include <its_redundancy.h>
/*Patch:Itika :8 oct-2010*/
extern ITS_UINT LocalRoutePc ;
extern ITS_UINT RemoteRoutePc ;
extern ITS_UINT RemoteRouteNi ;
/*Patch:Itika :end*/

/*Note :R2-HA:Start*/
extern int NODECARDSTATE ;
#ifdef PLATFORM_IMR
extern "C"
{
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
}
#endif
/*Note :R2-HA:End*/

#if defined (CCITT)
#define SCCP_SetSSEntry SCCP_SetSSEntry_CCITT 
#define SCCP_Alarm SCCP_Alarm_CCITT
#define SCCP_SetGeneralCfg SCCP_SetGeneralCfg_CCITT
#define SCCP_SetConcernedSS SCCP_SetConcernedSS_CCITT
#define SCCP_RemSSEntry SCCP_RemSSEntry_CCITT
#define SCCP_IsSSNAllowed SCCP_IsSSNAllowed_CCITT
#define SCCP_EnableUserPart SCCP_EnableUserPart_CCITT
#define SCCP_GetSSEntry SCCP_GetSSEntry_CCITT
#define MTP3_SetGeneralCfg MTP3_SetGeneralCfg_CCITT
#define SCCP_RemConcernedSS SCCP_RemConcernedSS_CCITT
#define MGMT_Main MGMT_Main_CCITT
#define MTP3_DisableUserPart MTP3_DisableUserPart_CCITT
#define MTP3_Timers  CCITT_MTP3_Timers
#define SCCP_Timers CCITT_SCCP_Timers
#define SCCP_Pegs   CCITT_SCCP_Pegs
#define MTP3_Pegs    CCITT_MTP3_Pegs
#define PEG_MTP3_NUM_PEGS       PEG_MTP3_NUM_PEGS_CCITT
#define FAMILY               FAMILY_ITU
#define __Protfamily_t1               __ccitt_t1
#define __Protfamily_t2               __ccitt_t2
#define __Protfamily_t3               __ccitt_t3
#define __Protfamily_t4               __ccitt_t4
#define __Protfamily_t5               __ccitt_t5
#define __Protfamily_t6               __ccitt_t6
#define __Protfamily_t7               __ccitt_t7
#define __Protfamily_t8               __ccitt_t8
#define __Protfamily_t9               __ccitt_t9
#define __Protfamily_t10               __ccitt_t10
#define __Protfamily_t11               __ccitt_t11
#define __Protfamily_t12               __ccitt_t12
#define __Protfamily_t13               __ccitt_t13
#define __Protfamily_t14               __ccitt_t14
#define __Protfamily_t15               __ccitt_t15
#define __Protfamily_t16               __ccitt_t16
#define __Protfamily_t17               __ccitt_t17
#define __Protfamily_t18               __ccitt_t18
#define __Protfamily_t19               __ccitt_t19
#define __Protfamily_t20               __ccitt_t20
#define __Protfamily_t21               __ccitt_t21
#define __Protfamily_t22               __ccitt_t22
#define __Protfamily_t23               __ccitt_t23
#else
#define SCCP_SetSSEntry SCCP_SetSSEntry_ANSI 
#define SCCP_Alarm SCCP_Alarm_ANSI
#define SCCP_SetGeneralCfg SCCP_SetGeneralCfg_ANSI
#define SCCP_SetConcernedSS SCCP_SetConcernedSS_ANSI
#define SCCP_RemSSEntry SCCP_RemSSEntry_ANSI
#define SCCP_IsSSNAllowed SCCP_IsSSNAllowed_ANSI
#define SCCP_EnableUserPart SCCP_EnableUserPart_ANSI
#define SCCP_GetSSEntry SCCP_GetSSEntry_ANSI
#define MTP3_SetGeneralCfg MTP3_SetGeneralCfg_ANSI
#define SCCP_RemConcernedSS SCCP_RemConcernedSS_ANSI
#define MGMT_Main MGMT_Main_ANSI
#define MTP3_DisableUserPart MTP3_DisableUserPart_ANSI
#define MTP3_Timers  ANSI_MTP3_Timers
#define SCCP_Timers ANSI_SCCP_Timers
#define SCCP_Pegs   ANSI_SCCP_Pegs
#define MTP3_Pegs    ANSI_MTP3_Pegs
#define PEG_MTP3_NUM_PEGS       PEG_MTP3_NUM_PEGS_ANSI
#define FAMILY               FAMILY_ANSI
#define __Protfamily_t1               __ansi_t1
#define __Protfamily_t2               __ansi_t2
#define __Protfamily_t3               __ansi_t3
#define __Protfamily_t4               __ansi_t4
#define __Protfamily_t5               __ansi_t5
#define __Protfamily_t6               __ansi_t6
#define __Protfamily_t7               __ansi_t7
#define __Protfamily_t8               __ansi_t8
#define __Protfamily_t9               __ansi_t9
#define __Protfamily_t10               __ansi_t10
#define __Protfamily_t11               __ansi_t11
#define __Protfamily_t12               __ansi_t12
#define __Protfamily_t13               __ansi_t13
#define __Protfamily_t14               __ansi_t14
#define __Protfamily_t15               __ansi_t15
#define __Protfamily_t16               __ansi_t16
#define __Protfamily_t17               __ansi_t17
#define __Protfamily_t18               __ansi_t18
#define __Protfamily_t19               __ansi_t19
#define __Protfamily_t20               __ansi_t20
#define __Protfamily_t21               __ansi_t21
#define __Protfamily_t22               __ansi_t22
#define __Protfamily_t23               __ansi_t23
#endif
extern ITS_OCTET NetworkInd;


extern unsigned int SwitchOver_Flag;/*Need to take decsion on this flag whether to reset internode flag or not*/
extern  "C"
{
 #include <tcap_clientapi.h>
 #include <tcap_clientimpl.h>
}

#include <ISIL_SCMInf.h>
extern  "C"
{
#include "GTT_ReadInfor.h"
}
//#include <interface.h>
extern ITS_HANDLE CL_Handle_SCM;
extern ITS_SEMAPHORE scm_sema;
extern ITS_SEMAPHORE mtp2_sema;
int
 NWSTK_SendRESP(I_S16, I_U8, I_U8);



#if defined(PRC) || defined (USE_PRC_SCCP)
#undef CCITT
#define PRC
#include <china/sccp.h>
#elif defined(TTC) || defined (USE_TTC_SCCP)
#undef CCITT
#define TTC
#include <japan/sccp.h>
#else
/*#include <itu/sccp.h>*/
#endif

#include "sccp_intern.h"

#define FIXED_RANGE 31
extern ITS_USHORT linkTransportMapDB[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
char  SP_RestartFlag=0;
typedef struct
{
    ITS_OCTET   linkSet;
    ITS_OCTET   linkCode;
}
LINK_Key;
static int isil_mtp2timer_modify(ITS_EVENT *ev);
/*******************************************************************
 * Purpose:   RESP HEADER BUILT
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

int
 BuildHeader(ITS_EVENT oldev,NwStkHdr *hdr)
{

  int cnt=0;
  int resp=0;


//  ISIL_DEBUG_TRACE(("BuildHeader:len=%d",newev->len));
  if(hdr->len)
  { 

  //  newev->data[ocnt++]=oldev.data[ncnt++];
    hdr->appid=oldev.data[cnt++];
    switch(oldev.data[cnt++])
    {
     case SCM_NWSTK_MTP3_GENPEG_GET:
          resp=NWSTK_SCM_MTP3_GENPEG_RESP;
     break; 
     case SCM_NWSTK_MTP3_LINKPEG_GET:
          resp=NWSTK_SCM_LINK_PEG_RESP;
     break; 
     case SCM_NWSTK_MTP3_ROUTEPEG_GET:
          resp=NWSTK_SCM_ROUTE_PEG_RESP;
     break; 
     case SCM_NWSTK_SCCP_GENPEG_GET:
          resp=NWSTK_SCM_SCCP_GENPEG_RESP;
     break; 
     case SCM_NWSTK_BSSAP_GENPEG_GET:
           resp=NWSTK_SCM_BSSAP_GENPEG_RESP;
     break;
     case SCM_NWSTK_LINK_STATUS_GET:
           resp=NWSTK_SCM_LINK_STATUS_RESP;
     break; 
     case SCM_NWSTK_LINKSET_STATUS_GET:
           resp=NWSTK_SCM_LINKSET_STATUS_RESP;
     break;
     case SCM_NWSTK_ROUTE_STATUS_GET:
           resp=NWSTK_SCM_ROUTE_STATUS_RESP;
     break;
     case SCM_NWSTK_SSN_STATUS_GET:
           resp=NWSTK_SCM_SSN_STATUS_RESP;
     break;
    }
 

    hdr->opcode=resp;
    hdr->trid=oldev.data[cnt++];
    
   /* newev->data[ocnt++]=resp;
    newev->data[ocnt++]=oldev.data[ncnt++];
    newev->data[ocnt++]=newev->len & 0x00ff;
    newev->data[ocnt++]=(newev->len & 0xff00) >> 8;*/
 }
 else
 {
  ISIL_ERROR_TRACE(("BuildHeader:Fail"));
  return NWSTK_BUILDHEAD_FAIL;  

 }
        return NWSTK_CMD_CNG_SUCCESS;
}

/*******************************************************************
 * Purpose:  LINKSET ADD Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int
isil_ls_add(ITS_EVENT *ev)
{
 ScmNwstkLinkSetConfig *LinkSetAdd = (ScmNwstkLinkSetConfig *)ev->data;
 ITS_UINT linkSet;
 char family[10];
 ITS_UINT lpc, apc;
 ITS_UINT ni;
 SS7_LinkSetPtr ls=NULL;
 SS7_LinkSet set;
 int ret=0;
 memset(&set, 0, sizeof(SS7_LinkSet));
 set.isUp = ITS_FALSE;

 if(LinkSetAdd==NULL)
 {
  ISIL_ERROR_TRACE(("ls_add:Fail"));
  return NWSTK_WRONG_PARAM;
 }

  ISIL_DEBUG_TRACE(("ls_add:"));

  ISIL_DEBUG_TRACE(("ls_add:linkset :%d ,RPC: %d Ni:%d ",LinkSetAdd->linkSetId,LinkSetAdd->adjacentPointCode,LinkSetAdd->networkIndicator));


 ls = LINKSET_FindLinkSet((ITS_OCTET)LinkSetAdd->linkSetId);
 if (ls!= NULL)
  {
     ISIL_ERROR_TRACE(("ls_add:linkset :%d already exist",LinkSetAdd->linkSetId));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
     return NWSTK_CMD_CNG_SUCCESS;
     /*return NWSTK_LNKSET_ALREADY_EXIST;*/
    /*R2-HA:End*/ 
  }

        set.linkSet  = LinkSetAdd->linkSetId;
        set.adjacent = LinkSetAdd->adjacentPointCode;
        set.lpc      = LinkSetAdd->localPointCode;
        set.ni       = LinkSetAdd->networkIndicator & ROUTE_NI_MASK;
        set.numToStart = 0;

 
  if(LinkSetAdd->family==1)
  {
    set.family=FAMILY_ANSI;
  }
 else if ( LinkSetAdd->family==0 )
  {
    set.family=FAMILY_ITU;
  }
  else if(LinkSetAdd->family== 2)
  {
    set.family=FAMILY_CHINA;
  }
 else if(LinkSetAdd->family== 3) 
 {
  set.family=FAMILY_JAPAN;
 } 
  else
 {
   ISIL_ERROR_TRACE(("ls_add:Family  must be itu ,ansi, china or japan "));
   return NWSTK_WRONG_PARAM;
 
 }
 if(ret = LINKSET_AddLinkSet(&set)!=ITS_SUCCESS)
   {
      if(ret==ITS_EDUPLENTRY)
      {
       ISIL_ERROR_TRACE(("ls_add:DUPLICAY "));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
       return NWSTK_CMD_CNG_SUCCESS;
       /*return NWSTK_LNKSET_ALREADY_EXIST;*/
     /*R2-HA:End*/ 
      }
     else  
      {
       ISIL_ERROR_TRACE(("ls_add:Fail "));
        return NWSTK_LNKSET_ADD_FAIL;
      }
   }
 else
   {
       ISIL_DEBUG_TRACE(("ls_add:SUCCESS "));
        return NWSTK_CMD_CNG_SUCCESS;

   }


}
/*******************************************************************
 * Purpose: LINKSET DEL Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_ls_del(ITS_EVENT *ev)
{

 SS7_LinkSetPtr ls=NULL;
 int ret;
 ScmNwstkLinkSetConfig *LinkSetdel = ( ScmNwstkLinkSetConfig *)ev->data;
 SS7_Destination* destPtr = NULL;
 ROUTE_MatchInfo rinfo;
 int routeId=0;
  if(LinkSetdel==NULL)
  {
   ISIL_ERROR_TRACE(("ls_del:Fail"));
   return NWSTK_WRONG_PARAM;
  }

 ISIL_DEBUG_TRACE(("ls_del:"));

 ISIL_DEBUG_TRACE(("ls_del:linkset :%d ,RPC: %d Ni:%d ",LinkSetdel->linkSetId,LinkSetdel->adjacentPointCode,LinkSetdel->networkIndicator));


 ls = LINKSET_FindLinkSet(LinkSetdel->linkSetId);
 if (ls == NULL)
  {
     ISIL_ERROR_TRACE(("ls_del:linkset :%d does not exist",LinkSetdel->linkSetId));
     return NWSTK_LNKSET_NOTFOUND;
  }

 if (ls->numLinks != 0)
  {
     ISIL_ERROR_TRACE(("ls_del:Linkset: %d has %d links. Delete them first",LinkSetdel->linkSetId,ls->numLinks));

  }

  if(ret = LINKSET_RemLinkSet(ls)!=ITS_SUCCESS)
  {
       ISIL_ERROR_TRACE(("ls_del:Fail "));
       return NWSTK_LNKSET_DEL_FAIL;
  } 
 else
  {
    ISIL_DEBUG_TRACE(("ls_del:SUCCESS "));
  }


        return NWSTK_CMD_CNG_SUCCESS;

 

}
/*******************************************************************
 * Purpose:    LINK ADD Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_ln_add(ITS_EVENT *ev)
{
 ScmNwstkLinkConfig *LinkAdd =( ScmNwstkLinkConfig *)ev->data;
 TRANSPORT_Control *tc=NULL;
 SS7_Link ln;
 SS7_LinkPtr    lp=NULL;
 SS7_LinkSetPtr ls=NULL;
// ITS_UINT linkCode, linkSet,timeslot;
 ITS_BOOLEAN isInterNode = ITS_FALSE;
 ITS_EVENT evt;
 int ret=0,i=0,Ret=0;
 ITS_OCTET COMMT_SUCCESS=0;
 LINK_Key lkey;
 ITS_EVENT OUT_SERVICE_EVENT;

  ENTRYDONE=0;
  memset(&ln, 0, sizeof(SS7_Link));
  ln.initActive = ITS_TRUE;
  ln.termFixed = ITS_TRUE;
  ln.linkFixed = ITS_TRUE;
  ln.isSAAL = ITS_FALSE;
  ln.next = NULL;
  ln.prev = NULL;

 if(LinkAdd==NULL)
 {
  ISIL_ERROR_TRACE(("ln_add:Fail"));
   return NWSTK_WRONG_PARAM;
 }

  ISIL_DEBUG_TRACE(("ln_add:"));

  ISIL_DEBUG_TRACE(("ln_add:instanceid :%d,linkset:%d ,linkCode:%d ",LinkAdd->instanceID,LinkAdd->linkSetId,LinkAdd->linkId));
  if(LinkAdd->instanceID == 20002)
    {
      linkTransportMapDB[(ITS_OCTET)LinkAdd->linkSetId][(ITS_OCTET)LinkAdd->linkId]=LinkAdd->instanceID;
      ISIL_DEBUG_TRACE(("ln_add:Sucessfully added instanceid :%d,linkset:%d ,linkCode:%d ",LinkAdd->instanceID,LinkAdd->linkSetId,LinkAdd->linkId));
      return NWSTK_CMD_CNG_SUCCESS;
    }

  tc = TRANSPORT_FindTransport(LinkAdd->instanceID);
  if (tc == NULL)
   {
     ISIL_ERROR_TRACE(("ln_add:Invalid Instance specified "));
     return NWSTK_INSTID_INVALID;
   }


 ls = LINKSET_FindLinkSet(LinkAdd->linkSetId);
 if (ls == NULL)
  {
     ISIL_ERROR_TRACE(("ln_add:linkset :%d does not exist",LinkAdd->linkSetId));
 
     return NWSTK_LINK_LNKSET_NOTFOUND;
  }


   ln.isUp = ITS_FALSE;
   ln.isAllowed = ITS_TRUE;
   ln.linkCode = (ITS_OCTET)LinkAdd->linkId;
   ln.id = LinkAdd->instanceID;
   ln.dsmNodeId = DSM_GetNodeId();
   ln.family = ls->family;
   ln.dataLink=LinkAdd->timeSlot;
   ln.stFlags |= LINK_FAILED;

 
   lp = LINK_FindLink((ITS_OCTET)LinkAdd->linkSetId, (ITS_OCTET)LinkAdd->linkId);
   if (lp != NULL)
   {
        ISIL_ERROR_TRACE((" Config LinkId  %d",lp->id));
      if(lp->id!=ln.id)
         {
            ISIL_ERROR_TRACE(("Number of Links %d",ls->numLinks));
            for (i = 0; i < ls->numLinks; i++)
             {  
                ISIL_ERROR_TRACE(("LinkCode %d LinkId=%d",ls->links[i]->linkCode,ls->links[i]->id));
                  if(ls->links[i]->linkCode == ln.linkCode)
                   {
                     ISIL_ERROR_TRACE(("Add Update Info For link %d",ls->links[i]->linkCode));
                     ls->links[i]->id=LinkAdd->instanceID;
                      ret = LINKSET_CommitLinkSet(ls);
                   }
             }

             lp->id = LinkAdd->instanceID;
            /*** Sandeep Code add for SwitchOver Flag Start */ 
               if(lp->id == 20002 && SwitchOver_Flag == 2)
                {
             /* Some need to update the plan as we will be generating OUT_OF_SERVICE for internode LINK only if configurtaion is not complete and peer stack leave*/
                           ITS_EVENT_INIT(&OUT_SERVICE_EVENT, ITS_MTP2_SRC,3 * sizeof(ITS_OCTET));
                           OUT_SERVICE_EVENT.data[0] = L2_L3_OUT_OF_SERVICE;
                           OUT_SERVICE_EVENT.data[1] = lp->linkSet->linkSet;
                           OUT_SERVICE_EVENT.data[2] = lp->linkCode;
                           TRANSPORT_PutEvent(ITS_MTP3_SRC, &OUT_SERVICE_EVENT);
                           ISIL_ERROR_TRACE(("Sucessfuly Sent OUT_OF_SERVICE to MTP3 for Internode ls|lc %d|%d \n",lp->linkSet->linkSet,lp->linkCode));

                }
            /*** Sandeep Code add for SwitchOver Flag Ends Here */ 

             if(LinkAdd->instanceID == ITS_MTP2_SRC)
             {
               LINK_AddLinkInfoToTransport(tc,lp);
             }
             ISIL_ERROR_TRACE(("link Activity State %d",lp->activityState));
             LINK_CommitLink(lp);
             linkTransportMapDB[(ITS_OCTET)LinkAdd->linkSetId][(ITS_OCTET)LinkAdd->linkId]=LinkAdd->instanceID;

             if (ret != ITS_SUCCESS)
             {
               return NWSTK_LNK_NOTFOUND;
             }
             else
              {
               ISIL_DEBUG_TRACE(("ln_add:linkset :%d linkCode %d Comnit Success ",LinkAdd->linkSetId,LinkAdd->linkId));
               COMMT_SUCCESS=1;

             }

           }
        else
           {
             ISIL_ERROR_TRACE(("ln_add:linkset :%d linkCode %d already exist",LinkAdd->linkSetId,LinkAdd->linkId));
               return NWSTK_LNK_NOTFOUND;
           }
     }


    if(COMMT_SUCCESS==0)
    {
      ISIL_DEBUG_TRACE(("ln_add:NEW Link Addition "));
      ret = LINK_AddLink(LinkAdd->linkSetId, &ln);
      if (ret != ITS_SUCCESS)
       {
     
        if(ret==ITS_EDUPLENTRY)
        {
         ISIL_ERROR_TRACE(("ln_add:DUPLICAY "));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
         return NWSTK_CMD_CNG_SUCCESS;
         /*return NW_STK_LNK_ALREADY_EXIST;*/
     /*R2-HA:End*/ 
        }
       else 
        {  
           ISIL_ERROR_TRACE(("ln_add: Fail to add link %d ",LinkAdd->linkId));
            return NWSTK_LNK_ADD_FAIL;
        }
     }

     lp = LINK_FindLink((ITS_OCTET)LinkAdd->linkSetId, (ITS_OCTET)LinkAdd->linkId);
      if (lp == NULL)
      {
         ISIL_ERROR_TRACE(("ln_add:linkset :%d linkCode %d does not exist",LinkAdd->linkSetId,LinkAdd->linkId));
         return NWSTK_LNK_NOTFOUND;
       }
     LINK_AddLinkInfoToTransport(tc, lp);
    }

     ISIL_DEBUG_TRACE(("ln_add:Indication for MTP2  "));
   if(LinkAdd->instanceID == ITS_MTP2_SRC)
    {
      ISIL_DEBUG_TRACE(("ln_add:Indication for MTP2  "));
            /*message for mtp2 link addtion */
       ITS_EVENT_INIT(&evt,ITS_MTP3_SRC,3*sizeof(ITS_OCTET));
       evt.data[0]=ln_add_cmd;
       evt.data[1]=LinkAdd->linkSetId;
       evt.data[2]=LinkAdd->linkId;
//       evt.data[3]=LinkAdd->crcFlag;

       ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, &evt);
       if (ret!=ITS_SUCCESS)
           {
             ITS_EVENT_TERM(&evt);
           }
          ISIL_DEBUG_TRACE(("Enter Sema Wait for Link Add semacntr=%d",scm_sema.semCounter));
					Ret=SEMA_WaitSemaphoreWithTimeOut(&scm_sema,3000);
          if(Ret!=ITS_SUCCESS)
          {
            ISIL_DEBUG_TRACE(("Sema Wait Fail for Link Add"));
          }
          ISIL_DEBUG_TRACE(("Sucess Sema Wait for Link Add"));


        if (ENTRYDONE==1)
         {
            ENTRYDONE=0;
            ISIL_DEBUG_TRACE(("ln_add:SUCCESS"));
            ITS_EVENT_TERM(&evt);
            return NWSTK_CMD_CNG_SUCCESS;
         }
        else
         { 
           ITS_EVENT_TERM(&evt);
           ITS_EVENT_INIT(&evt,ITS_MTP3_SRC,3*sizeof(ITS_OCTET));
           evt.data[0]=ln_del_cmd;
           evt.data[1]=LinkAdd->linkSetId;
           evt.data[2]=LinkAdd->linkId;
       //    evt.data[3]=LinkAdd->crcFlag;
           ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, &evt);
           if (ret!=ITS_SUCCESS)
            {
             ITS_EVENT_TERM(&evt);
            }
             ISIL_DEBUG_TRACE(("Enter Sema Wait for Link Del semcntr=%d",scm_sema.semCounter));
					   Ret=SEMA_WaitSemaphoreWithTimeOut(&scm_sema,3000);
             if(Ret!=ITS_SUCCESS)
             {
                 ISIL_DEBUG_TRACE(("Sema Wait Fail for Link Del"));
             }
            ISIL_DEBUG_TRACE(("Sucess Sema Wait for Link Del"));

            /*also delete the entry at mtp3 database*/
            ret = LINK_RemLink(LinkAdd->linkSetId, lp);
            if (ret != ITS_SUCCESS)
             {
               ISIL_DEBUG_TRACE(("ln_del:Fail"));
               ITS_EVENT_TERM(&evt);
               return NWSTK_LNK_DEL_FAIL;
             
             }
           else
             {
            //   return !NWSTK_CMD_CNG_SUCCESS;
                 return NWSTK_LNK_ADD_FAIL;

            }
         }
     }/*end of instance check*/
      return NWSTK_CMD_CNG_SUCCESS;
}
/*******************************************************************
 * Purpose: LINK DEL Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_ln_del(ITS_EVENT *ev)
{
 ScmNwstkLinkConfig *Linkdel =(ScmNwstkLinkConfig *)ev->data;
 TRANSPORT_Control *tc=NULL;
 SS7_LinkPtr    lp=NULL;
 SS7_LinkSetPtr ls=NULL;
 ITS_UINT linkCode, linkSet;
 int ret,Ret=0;
 ITS_EVENT evt;
 ENTRYDELETE=0;
  if(Linkdel==NULL)
  { 
   ISIL_ERROR_TRACE(("ln_del:Fail NULL"));
   return NWSTK_WRONG_PARAM;
  }
  ISIL_DEBUG_TRACE(("ln_del:"));


  ISIL_DEBUG_TRACE(("ln_del:instanceid :%d,linkset:%d ,linkCode:%d ",Linkdel->instanceID,Linkdel->linkSetId,Linkdel->linkId));
  if(Linkdel->instanceID == 20002)
    {
      ISIL_DEBUG_TRACE(("Sucessfully deleted Internode instanceid :%d,linkset:%d ,linkCode:%d ",Linkdel->instanceID,Linkdel->linkSetId,Linkdel->linkId));
       linkTransportMapDB[(ITS_OCTET)Linkdel->linkSetId][(ITS_OCTET)Linkdel->linkId]=0;
       return NWSTK_CMD_CNG_SUCCESS; 
     
    }

 ls = LINKSET_FindLinkSet(Linkdel->linkSetId);
 if (ls == NULL)
  {
     ISIL_ERROR_TRACE(("ln_del:linkset :%d does not exist",Linkdel->linkSetId));
 
     return NWSTK_LINK_LNKSET_NOTFOUND;
  }
  

   lp = LINK_FindLink((ITS_OCTET)Linkdel->linkSetId, (ITS_OCTET)Linkdel->linkId);
   if (lp == NULL)
   {
     if(Linkdel->instanceID == 20002)
      {
        if(linkTransportMapDB[(ITS_OCTET)Linkdel->linkSetId][(ITS_OCTET)Linkdel->linkId] > 0 )
        {
           ISIL_DEBUG_TRACE(("ln_del:Only Internode Transport Clear"));
           linkTransportMapDB[(ITS_OCTET)Linkdel->linkSetId][(ITS_OCTET)Linkdel->linkId]=0;
           return NWSTK_CMD_CNG_SUCCESS;
        }
      }
     ISIL_ERROR_TRACE(("ln_del:linkset :%d linkCode %d does not exist",Linkdel->linkSetId,Linkdel->linkId));
 
     return NWSTK_LNK_NOTFOUND;
   }

  if(Linkdel->instanceID == ITS_MTP2_SRC)
  {
    ITS_EVENT_INIT(&evt,ITS_MTP3_SRC,3*sizeof(ITS_OCTET));
    evt.data[0]=ln_del_cmd;
    evt.data[1]=Linkdel->linkSetId;
    evt.data[2]=Linkdel->linkId;
  //  evt.data[3]=Linkdel->crcFlag;

    ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, &evt);
    if (ret!=ITS_SUCCESS)
     {
         ISIL_ERROR_TRACE(("ln_del:Fail"));
         ITS_EVENT_TERM(&evt);
         return NWSTK_LNK_DEL_FAIL;
     }
          ISIL_DEBUG_TRACE(("Enter Sema Wait for Link Del"));
					Ret=SEMA_WaitSemaphoreWithTimeOut(&scm_sema,3000);
          if(Ret!=ITS_SUCCESS)
          {
            ISIL_DEBUG_TRACE(("Sema Wait Fail for Link Del"));
          }
          ISIL_DEBUG_TRACE(("Sucess Sema Wait for Link Del"));
      // usleep(500);
      if(ENTRYDELETE==1)
       {
          ENTRYDELETE=0;
          ret = LINK_RemLink(Linkdel->linkSetId, lp);
          if (ret != ITS_SUCCESS)
          {
            ISIL_ERROR_TRACE(("ln_del:Rem Fail"));
            ITS_EVENT_TERM(&evt);
            return NWSTK_LNK_DEL_FAIL;
          }
/*Patch:02-aug-2010:ln_add issue*/
           ISIL_DEBUG_TRACE(("ln_del:Clearing linkTransportMapDB InstanceID as zero \n"));
         linkTransportMapDB[(ITS_OCTET)Linkdel->linkSetId][(ITS_OCTET)Linkdel->linkId]=0;
/*Patch:End:ln_add issue*/
         ISIL_DEBUG_TRACE(("ln_del:SUCCESS"));
         return NWSTK_CMD_CNG_SUCCESS;

       }
      else
       {
         ISIL_DEBUG_TRACE(("ln_del:Fail"));
            return NWSTK_LNK_DEL_FAIL;
       }
   }
 else
   {
            ret = LINK_RemLink(Linkdel->linkSetId, lp);
            if (ret != ITS_SUCCESS)
             {
               ISIL_DEBUG_TRACE(("ln_del:Fail"));
               ITS_EVENT_TERM(&evt);
               return NWSTK_LNK_DEL_FAIL;
             
             }
         ISIL_DEBUG_TRACE(("ln_del:SUCCESS"));
         return NWSTK_CMD_CNG_SUCCESS;
   }
}
/*******************************************************************
 * Purpose:               ROUTE ADD Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_rt_add(ITS_EVENT *ev)
{
  ScmNwstkSs7RouteConfig *RouteAdd = 
                         (ScmNwstkSs7RouteConfig *)ev->data;

 ROUTE_MatchInfo rinfo;
 ITS_UINT dpc, opc;
 ITS_UINT sio;
 ITS_UINT ssn, beginSSN, endSSN;
 SS7_LinkSetPtr ls;
 int ret=0; 
 memset(&rinfo, '\0', sizeof(ROUTE_MatchInfo));
 
  if(RouteAdd==NULL)
  { 
   ISIL_ERROR_TRACE(("rt_add:Fail"));
   return NWSTK_WRONG_PARAM;
  }
 ISIL_DEBUG_TRACE(("rt_add:"));


 ISIL_DEBUG_TRACE(("rt_add:linkset :%d RPC :%d,SIO:%d,NI:%d LSSN %d RSSN :%d",RouteAdd->linkSetId,RouteAdd->destinationPointCode,RouteAdd->sio,RouteAdd->networkIndicator,RouteAdd->lssn ,RouteAdd->rssn));


 ls = LINKSET_FindLinkSet((ITS_OCTET)RouteAdd->linkSetId);
 if (ls == NULL)
  {
     ISIL_ERROR_TRACE(("rt_add:linkset :%d does not exist",RouteAdd->linkSetId));
 
     return NWSTK_ROUTE_LNKSET_NOTFOUND;
  }
  
 
 if(RouteAdd->direction == 0 )
  {
   rinfo.basic.type =ROUTE_TYPE( LOCAL_ROUTE ); 
   ISIL_DEBUG_TRACE(("Direction:LOCAL ROUTE"));
  }
 else if(RouteAdd->direction == 1)
  {
   rinfo.basic.type = ROUTE_TYPE(REMOTE_ROUTE);
  ISIL_DEBUG_TRACE(("Direction:REMOTE ROUTE"));
  }
 else 
  {
    ISIL_ERROR_TRACE(("rt_add:Direction must be local or remote"));
   return NWSTK_WRONG_PARAM;
  }

  if(RouteAdd->family==1)
  {
    rinfo.basic.family=FAMILY_ANSI;
   ISIL_DEBUG_TRACE(("Family:ANSI"));
  }
 else if ( RouteAdd->family==0 )
  {
   ISIL_DEBUG_TRACE(("Family:ITU"));
    rinfo.basic.family=FAMILY_ITU;
  }
  else if(RouteAdd->family== 2)
  {
   ISIL_DEBUG_TRACE(("Family:CHINA"));
    rinfo.basic.family=FAMILY_CHINA;
  }
 else if(RouteAdd->family== 3) 
 {
   ISIL_DEBUG_TRACE(("Family:JAPAN"));
  rinfo.basic.family=FAMILY_JAPAN;
 } 
 else
 {
   ISIL_ERROR_TRACE(("rt_add:Family  must be itu ,ansi, china or japan "));
   return NWSTK_WRONG_PARAM;
 
 }
   if(RouteAdd->style==0)
   {
    rinfo.basic.style=ROUTE_DPC_NI;
    NetworkInd=RouteAdd->networkIndicator;
    ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_NI and NI %d",NetworkInd));
   }
  else if(RouteAdd->style==1)
   {
   ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_SIO"));
    rinfo.basic.style=ROUTE_DPC_SIO;
   }
  else  if(RouteAdd->style==2)
   {
   ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_SIO_SSN"));
    rinfo.basic.style=ROUTE_DPC_SIO_SSN;
   }

   rinfo.basic.dpc = RouteAdd->destinationPointCode;
   
   if(rinfo.basic.style==ROUTE_DPC_NI )
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)RouteAdd->sio & ROUTE_NI_MASK;
     ISIL_DEBUG_TRACE(("Rt_add rinfo.basic.style %d \n",rinfo.basic.criteria.sio));

   }
   else if (rinfo.basic.style==ROUTE_DPC_SIO )
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)RouteAdd->sio ;

   }
  else if(rinfo.basic.style==ROUTE_DPC_SIO_SSN)
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)RouteAdd->sio ;
     rinfo.basic.criteria.ssn = (ITS_OCTET)RouteAdd->rssn;

   }
  else
   {
     ISIL_ERROR_TRACE(("rt_add:wrong style "));
     return NWSTK_WRONG_PARAM;

   }

     rinfo.linkSet = (ITS_OCTET)RouteAdd->linkSetId ;
     rinfo.linkCode = 0;
     rinfo.priority = 0;
     rinfo.sls  = 0;
     rinfo.rkey = 0;
     rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
/*Patch:Itika :8 oct-2010*/
         if(rinfo.basic.type == ROUTE_TYPE(REMOTE_ROUTE))
         {
             RemoteRoutePc =  rinfo.basic.dpc;
             RemoteRouteNi = RouteAdd->networkIndicator;
             ISIL_DEBUG_TRACE ((" Remote Route for RemoteRoutePc %d RemoteRouteNi %d style %d \n",RemoteRoutePc,RemoteRouteNi,rinfo.basic.style));
         }
         else if(rinfo.basic.type == ROUTE_TYPE(LOCAL_ROUTE))
         {
             LocalRoutePc =  rinfo.basic.dpc;
             ISIL_DEBUG_TRACE ((" Local Route for LocalRoutePc %d style %d \n",LocalRoutePc,rinfo.basic.style));
         }
/*Patch:Itika :end*/
     if ( (ret = ROUTE_AddRouteContextInfo(&rinfo)) != ITS_SUCCESS)
        {
          if(ret==ITS_EDUPLENTRY)
          {
              ISIL_ERROR_TRACE(("rt_add:Duplicay "));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
              return NWSTK_CMD_CNG_SUCCESS;
              /*return NWSTK_DUPLICATE_ROUTE;*/
     /*R2-HA:End*/ 

          }
         else
          {
              ISIL_ERROR_TRACE(("rt_add:Fail ret Value = %d",ret));
              return NWSTK_ROUTE_ADD_FAIL;
          }
        }
    else
       {
         if((rinfo.basic.style == ROUTE_DPC_SIO_SSN) && (rinfo.basic.type == ROUTE_TYPE(REMOTE_ROUTE)))
         { 
            if (ROUTE_SetRouteContextStatus (RouteAdd->destinationPointCode,ITS_FALSE,
                                       ROUTE_DPC_SIO_SSN,
                                       FAMILY,
                                       (RouteAdd->sio),
                                       rinfo.basic.criteria.ssn,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE,
                                       ITS_SS7_DEFAULT_PRI,
                                       ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
              /* Failed to set the route context status */
             ISIL_ERROR_TRACE ((" Failed to set the routecontext status\n"));
            }
         }

           ISIL_DEBUG_TRACE(("rt_add:SUCCESS "));
           return NWSTK_CMD_CNG_SUCCESS;

       }


} 
/*******************************************************************
 * Purpose:           ROUTE DEL Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
 
int
isil_rt_del(ITS_EVENT *ev)
{
 ScmNwstkSs7RouteConfig *Routedel = 
                         ( ScmNwstkSs7RouteConfig *)ev->data;
 ROUTE_MatchInfo rinfo;
 ITS_UINT opc, dpc;
 ITS_UINT sio;
 ITS_UINT ssn, beginSSN, endSSN;
 ITS_UINT cic, beginCIC, endCIC;
 SS7_LinkSetPtr ls;
 ITS_UINT linkSet;
 int ret=0;
 memset(&rinfo, 0, sizeof(ROUTE_MatchInfo));

 if(Routedel==NULL)
 { 
   ISIL_ERROR_TRACE(("rt_del:Fail"));
   return NWSTK_WRONG_PARAM;
 }
 
 ISIL_DEBUG_TRACE(("rt_del:"));

 ISIL_DEBUG_TRACE(("rt_del:linkset :%d RPC :%d,SIO :%d,NI :%d,RSSN :%d LSSN:%d",Routedel->linkSetId,Routedel->destinationPointCode,Routedel->sio,Routedel->networkIndicator,Routedel->rssn,Routedel->lssn));

 
 ls = LINKSET_FindLinkSet((ITS_OCTET)Routedel->linkSetId);
 if (ls == NULL)
  {
     ISIL_ERROR_TRACE(("rt_del:linkset :%d does not exist",Routedel->linkSetId));

     return NWSTK_ROUTE_LNKSET_NOTFOUND;
  }
  
 
 if(Routedel->direction == 0 )
  {
   ISIL_DEBUG_TRACE(("Direction:LOCAL ROUTE"));
   rinfo.basic.type= ROUTE_TYPE(LOCAL_ROUTE) ; 
   LocalRoutePc = 0;
   ISIL_DEBUG_TRACE(("rt_del:LOCAL ROUTE Deleted:Resetting LocalRoutePc[%d]",LocalRoutePc));
  }
 else if(Routedel->direction == 1)
  {
   ISIL_DEBUG_TRACE(("Direction:REMOTE ROUTE"));
   rinfo.basic.type=ROUTE_TYPE(REMOTE_ROUTE);
  }
 else 
  {
    ISIL_ERROR_TRACE(("rt_del:Direction must be local or remote"));
   return NWSTK_WRONG_PARAM;
  }
  if(Routedel->family==1)
  {
   ISIL_DEBUG_TRACE(("Family:ANSI"));
    rinfo.basic.family=FAMILY_ANSI;
  }
 else if ( Routedel->family==0 )
  {
   ISIL_DEBUG_TRACE(("Family:ITU"));
    rinfo.basic.family=FAMILY_ITU;
  }
  else if(Routedel->family== 2)
  {
   ISIL_DEBUG_TRACE(("Family:CHINA"));
    rinfo.basic.family=FAMILY_CHINA;
  }
 else if(Routedel->family== 3) 
 {
   ISIL_DEBUG_TRACE(("Family:JAPAN"));
  rinfo.basic.family=FAMILY_JAPAN;
 } 
 else
 {
   ISIL_ERROR_TRACE(("rt_del:Family  must be itu ,ansi, china or japan "));
   return NWSTK_WRONG_PARAM;
 
 }
   if(Routedel->style==0)
   {
    ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_NI"));
    rinfo.basic.style=ROUTE_DPC_NI;
   }
  else if(Routedel->style==1)
   {
    ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_SIO"));
    rinfo.basic.style=ROUTE_DPC_SIO;
   }
  else  if(Routedel->style==2)
   {
    ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_SIO_SSN"));
    rinfo.basic.style=ROUTE_DPC_SIO_SSN;
   }

   rinfo.basic.dpc = Routedel->destinationPointCode;
   
   if(rinfo.basic.style==ROUTE_DPC_NI )
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)Routedel->sio & ROUTE_NI_MASK;
     ISIL_DEBUG_TRACE(("rinfo.basic.style %d \n",rinfo.basic.criteria.sio));

   }
   else if (rinfo.basic.style==ROUTE_DPC_SIO )
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)Routedel->sio ;

   }
  else if(rinfo.basic.style==ROUTE_DPC_SIO_SSN)
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)Routedel->sio ;
     rinfo.basic.criteria.ssn = (ITS_OCTET)Routedel->rssn;
   }
  else
   {
     ISIL_ERROR_TRACE(("rt_del:wrong style "));
     return NWSTK_WRONG_PARAM;

   }

     rinfo.linkSet = (ITS_OCTET)Routedel->linkSetId ;
     rinfo.linkCode = 0;
     rinfo.priority = 0;
     rinfo.sls  = 0;
     rinfo.rkey = 0;
     rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

     if ( (ret = ROUTE_DeleteRouteContextInfo(&rinfo)) != ITS_SUCCESS)
        {
              ISIL_ERROR_TRACE(("rt_del:Fail ret= %d",ret));
              return NWSTK_ROUTE_DEL_FAIL;
        }
    else
       {
           ISIL_DEBUG_TRACE(("rt_del:SUCCESS "));
           return NWSTK_CMD_CNG_SUCCESS;

       }



}
/*******************************************************************
 * Purpose:             LSSN ADD Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_lssn_add(ITS_EVENT *ev)
{
 ScmNwstkSccpLssnConfig *lssnSet = (ScmNwstkSccpLssnConfig *)ev->data ;
 SCCPSubSystemInfo info;
 ITS_UINT linkset = 0;
 int ret=0;

 memset(&info, 0, sizeof(SCCPSubSystemInfo));

 if(lssnSet==NULL)
 {
  ISIL_ERROR_TRACE(("lssn_add:Fail"));
   return NWSTK_WRONG_PARAM;
 }
 ISIL_DEBUG_TRACE(("lssn_add:"));

 ISIL_DEBUG_TRACE(("lssn_add:LPC :%d ,SSN :%d,NI :%d",lssnSet->sccpConfigpc,lssnSet->sccpConfiglssn,lssnSet->sccpConfigni));


 if(lssnSet->sccpConfiglssn >256)
 {
     ISIL_ERROR_TRACE(("lssn_add:Invalid SSN "));
     return NWSTK_INVAILD_SSN;     
 }

  info.pointcode =lssnSet->sccpConfigpc;
  info.ni = lssnSet->sccpConfigni;
  info.ssn = lssnSet->sccpConfiglssn;
  info.linkSet = linkset;
  info.isLocal =ITS_TRUE;

  ret = SCCP_SetSSEntry(&info);
  if(ret!=ITS_SUCCESS)
  {
     if(ret== ITS_EDUPLENTRY)
      {
        ISIL_ERROR_TRACE(("lssn_add:Duplicate Entry SSN "));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
        return NWSTK_CMD_CNG_SUCCESS;
        /*return NWSTK_SSN_ALREADY_EXIST;*/
     /*R2-HA:End*/ 
      }
     else
      {
        ISIL_ERROR_TRACE(("lssn_add:Entry SSN Fail"));
        return NWSTK_SSNADD_FAIL;
      }

  }
return NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:          LSSN DEL Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_lssn_del(ITS_EVENT *ev)
{
 ScmNwstkSccpLssnConfig *lssndel = (ScmNwstkSccpLssnConfig *)ev->data ;
 SCCPSubSystemInfo info;
 ITS_UINT linkset = 0;
 int ret=0;

  if(lssndel==NULL)
  {
   ISIL_ERROR_TRACE(("lssn_del:Fail "));
   return NWSTK_WRONG_PARAM;
  }
 ISIL_DEBUG_TRACE(("lssn_del: "));

 ISIL_DEBUG_TRACE(("lssn_del:LPC :%d ,SSN %d,NI %d",lssndel->sccpConfigpc,lssndel->sccpConfiglssn,lssndel->sccpConfigni));


 memset(&info, 0, sizeof(SCCPSubSystemInfo));

 if(lssndel->sccpConfiglssn >256)
 {
     ISIL_ERROR_TRACE(("lssn_del:Invalid SSN "));
     return NWSTK_INVAILD_SSN;     
 }

  info.pointcode =lssndel->sccpConfigpc;
  info.ni = lssndel->sccpConfigni;
  info.ssn = lssndel->sccpConfiglssn;
  info.linkSet = linkset;
  info.isLocal =ITS_TRUE;
  

  ret = SCCP_RemSSEntry(&info);
  if(ret!=ITS_SUCCESS)
  {
     if(ret== ITS_EDUPLENTRY)
      {
        ISIL_ERROR_TRACE(("lssn_del:Duplicate Entry SSN "));
        return NWSTK_SSN_ALREADY_EXIST;
      }
     else
      {
        ISIL_ERROR_TRACE(("lssn_del:Entry SSN Fail"));
        return NWSTK_SSNADD_FAIL;
      }

  }
return NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:          RSSN ADD Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int 
isil_rssn_add(ITS_EVENT *ev)
{
  ScmNwstkSccpRssnConfig *RssnAdd = (ScmNwstkSccpRssnConfig *)ev->data ;
  SCCPSubSystemInfo info;
  ITS_INT linkset = -1;
  ITS_INT routeId;
  SS7_Destination* destPtr = NULL;
  int ret=0;
  memset(&info, 0, sizeof(SCCPSubSystemInfo));

   if(RssnAdd==NULL)
   {
     ISIL_ERROR_TRACE(("rssn_add:Fail "));
     return NWSTK_WRONG_PARAM;
   }
 ISIL_DEBUG_TRACE(("rssn_add: "));

 ISIL_DEBUG_TRACE(("rssn_add:RPC :%d ,SSN: %d,NI:%d",RssnAdd->sccpConfigpc,RssnAdd->sccpConfigrssn,RssnAdd->sccpConfigni));


 if(RssnAdd->sccpConfigrssn >256)
 {
     ISIL_ERROR_TRACE(("rssn_add:Invalid SSN "));
     return NWSTK_INVAILD_SSN;     
 }

 if (RssnAdd->sccpConfigni != MTP3_NIC_INTERNATIONAL &&
            RssnAdd->sccpConfigni != MTP3_NIC_SPARE    &&
              RssnAdd->sccpConfigni != MTP3_NIC_NATIONAL &&
                   RssnAdd->sccpConfigni != MTP3_NIC_RESERVED)
        {
          ISIL_ERROR_TRACE(("rssn_add:Invalid NI "));
          return NWSTK_INVAILD_BSCID;     
        }


    destPtr = ROUTE_FindDestination(RssnAdd->sccpConfigpc,
                RssnAdd->sccpConfigni, FAMILY);
    if (destPtr == NULL)
     {
         ISIL_ERROR_TRACE(("rssn_add:First Add Route"));
          return NWSTK_INVALID_ROUTE;
     }

   ROUTE_CommitDestination(destPtr, RssnAdd->sccpConfigpc,
     RssnAdd->sccpConfigni, FAMILY);
   if (linkset == -1)
   {
       for(routeId = 0; routeId < destPtr->numEntries; routeId++)
        {
         if (destPtr->entries[routeId]->basic.style == ROUTE_DPC_NI &&
                destPtr->entries[routeId]->basic.type == REMOTE_ROUTE)
           {
                linkset = destPtr->entries[routeId]->linkSet->linkSet;
           }
        }
   }

        if ((linkset == -1) && (routeId == destPtr->numEntries))
        {
            ISIL_ERROR_TRACE(("rssn_add:First Add Route"));
            return NWSTK_INVALID_ROUTE;
        }
  info.pointcode =RssnAdd->sccpConfigpc;
  info.ni = RssnAdd->sccpConfigni;
  info.ssn = RssnAdd->sccpConfigrssn;
  info.linkSet = linkset;
  info.isLocal =ITS_FALSE;


        ret = SCCP_SetSSEntry(&info);
        if (ret != ITS_SUCCESS)
        {
            ISIL_ERROR_TRACE(("rssn_add:SCCP SSN Set Entry Failed"));
            return NWSTK_SSNADD_FAIL;
        }
 SCCP_Alarm(500, __FILE__, __LINE__, "PC %x, SSN %d",info.pointcode ,info.ssn );
   return NWSTK_CMD_CNG_SUCCESS;


}


/*******************************************************************
 * Purpose:          RSSN DEL Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int    
isil_rssn_del(ITS_EVENT *ev)
{
 ScmNwstkSccpRssnConfig *Rssndel = (ScmNwstkSccpRssnConfig *)ev->data ;
 SCCPSubSystemInfo info;
 ITS_UINT linkset = 0;
 ITS_INT routeId;
 SS7_Destination* destPtr = NULL;
 int ret=0;
  if(Rssndel==NULL)
  { 
     ISIL_ERROR_TRACE(("rssn_del:Fail "));
     return NWSTK_WRONG_PARAM;
  }

 memset(&info, 0, sizeof(SCCPSubSystemInfo));
 ISIL_DEBUG_TRACE(("rssn_del: "));

 ISIL_DEBUG_TRACE(("rssn_del:RPC :%d ,SSN: %d,NI:%d",Rssndel->sccpConfigpc,Rssndel->sccpConfigrssn,Rssndel->sccpConfigni));


 if (Rssndel->sccpConfigrssn > 256)
  {
     ISIL_ERROR_TRACE(("Rssndel:Invalid SSN "));
     return NWSTK_INVAILD_SSN;     
 }
 if (Rssndel->sccpConfigni != MTP3_NIC_INTERNATIONAL &&
            Rssndel->sccpConfigni != MTP3_NIC_SPARE  &&
            Rssndel->sccpConfigni != MTP3_NIC_NATIONAL &&
            Rssndel->sccpConfigni != MTP3_NIC_RESERVED)
   {
          ISIL_ERROR_TRACE(("Rssndel:Invalid NI "));
          return NWSTK_INVAILD_BSCID;     
   }


    destPtr = ROUTE_FindDestination(Rssndel->sccpConfigpc,
                Rssndel->sccpConfigni, FAMILY);

    if (destPtr == NULL)
     {
         ISIL_ERROR_TRACE(("Rssndel:iNVAILD NI OR PC"));
          return NWSTK_WRONG_PARAM;
     }

   ROUTE_CommitDestination(destPtr, Rssndel->sccpConfigpc,
     Rssndel->sccpConfigni, FAMILY);

       for(routeId = 0; routeId < destPtr->numEntries; routeId++)
        {
         if (destPtr->entries[routeId]->basic.style == ROUTE_DPC_NI &&
                destPtr->entries[routeId]->basic.type == REMOTE_ROUTE)
           {
                linkset = destPtr->entries[routeId]->linkSet->linkSet;
           }
        }
        if ((linkset == 0) && (routeId == destPtr->numEntries))
        {
            ISIL_ERROR_TRACE(("Rssndel:Invaild Route"));
            return NWSTK_INVALID_ROUTE;
        }

  info.pointcode =Rssndel->sccpConfigpc;
  info.ni = Rssndel->sccpConfigni;
  info.ssn = Rssndel->sccpConfigrssn;
  info.linkSet = linkset;
  info.isLocal =ITS_FALSE;


        ret = SCCP_RemSSEntry(&info);

        if (ret != ITS_SUCCESS)
        {
            ISIL_ERROR_TRACE(("Rssndel:SCCP SSN Rem Entry Failed"));
            return NWSTK_SSNDEL_FAIL;
        }
   SCCP_Alarm(500, __FILE__, __LINE__, "PC %x, SSN %d",info.pointcode ,info.ssn );
   return NWSTK_CMD_CNG_SUCCESS;


}
/*******************************************************************
 * Purpose:              CSSN ADD Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_cssn_add(ITS_EVENT *ev)
{
 ScmNwstkSccpCssnConfig *AddCssn=(ScmNwstkSccpCssnConfig *)ev->data;
 SCCPConcernedSSInfo info;
 ITS_UINT  pc  = AddCssn->sccpConfigpc;
 ITS_OCTET ni  = AddCssn->sccpConfigni;
 ITS_OCTET ssn = AddCssn->sccpConfigssn;
 ITS_UINT cpc  = AddCssn->sccpConfigcpc;
 ITS_OCTET cssn= AddCssn->sccpConfigcssn;
 int ret=0;
 if(AddCssn==NULL)
 {
     ISIL_ERROR_TRACE(("cssn_add: "));
     return NWSTK_WRONG_PARAM;
 }
 
 memset(&info, 0, sizeof(SCCPConcernedSSInfo));
 ISIL_DEBUG_TRACE(("cssn_add: "));

 ISIL_DEBUG_TRACE(("cssn_add:LPC :%d ,LSSN: %d",AddCssn->sccpConfigpc,AddCssn->sccpConfigssn));

 ISIL_DEBUG_TRACE(("cssn_add:RPC :%d ,RSSN: %d,NI:%d",AddCssn->sccpConfigcpc,AddCssn->sccpConfigcssn,AddCssn->sccpConfigni));


    if ((ssn > 256) || (cssn > 256))
     {
         ISIL_ERROR_TRACE(("cssn_add:Invalid ssn"));
          return NWSTK_INVAILD_SSN;
     }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;

        ret = SCCP_SetConcernedSS(&info);
        if (ret == ITS_ENOTFOUND)
         {

           ISIL_ERROR_TRACE(("cssn_add:No Local Route Found For pc=%d, ni=%d, ssn=%d\n", pc, ni, ssn));
           return NWSTK_SSNADD_FAIL;

         }
       else if(ret==ITS_SUCCESS)
        {
           ISIL_ERROR_TRACE(("cssn_add:SCCP CSSN Set Entry Success"));

        }  
       else
        {
            ISIL_ERROR_TRACE(("cssn_add:SCCP CSSN Set Entry Failed"));
           return NWSTK_SSNADD_FAIL;

        }
    SCCP_Alarm(506, __FILE__, __LINE__, "PC %x, SSN %d", pc, ssn);
   return NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:           CSSN Del Command
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static int
isil_cssn_del(ITS_EVENT *ev)
{
 ScmNwstkSccpCssnConfig *DelCssn=(ScmNwstkSccpCssnConfig *)ev->data;
 SCCPConcernedSSInfo info;
 ITS_INT inservice = ITS_FALSE;
 MTP3_HEADER hdr;
 int ret=0;
 if(DelCssn==NULL)
 {
     ISIL_ERROR_TRACE(("cssn_del:Fail "));
     return NWSTK_WRONG_PARAM;
 }
 memset(&info, 0, sizeof(SCCPConcernedSSInfo));
 ISIL_DEBUG_TRACE(("cssn_del: "));

 ISIL_DEBUG_TRACE(("cssn_del:LPC :%d ,LSSN: %d",DelCssn->sccpConfigpc,DelCssn->sccpConfigssn));

ISIL_DEBUG_TRACE(("cssn_del:RPC :%d ,RSSN: %d,NI:%d",DelCssn->sccpConfigcpc,DelCssn->sccpConfigcssn,DelCssn->sccpConfigni));


 info.pc = DelCssn->sccpConfigpc;
 info.ni = DelCssn->sccpConfigni;
 info.ssn =DelCssn->sccpConfigssn;
 info.cpc = DelCssn->sccpConfigcpc;
 info.cssn = DelCssn->sccpConfigcssn;
 info.inservice = inservice;

 ret = SCCP_RemConcernedSS(&info);
        if(ret != ITS_SUCCESS)
        {
            ISIL_ERROR_TRACE(("cssn_del:SCCP CSSN Set Entry Failed"));
            return NWSTK_SSNADD_FAIL;

        }
    SCCP_Alarm(507, __FILE__, __LINE__, "PC %x SSN %d", info.pc ,info.cssn);
   return NWSTK_CMD_CNG_SUCCESS;



}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/


static   int
isil_ls_statemodify(ITS_EVENT *ev)
{

ScmNwstkLinkSetAdminStateModify *ls_state = (ScmNwstkLinkSetAdminStateModify *)ev->data;

SS7_LinkSetPtr ls=NULL;
int ret=0;
     if(ls_state==NULL)
     {
       ISIL_ERROR_TRACE(("ls_statemodify:Fail"));
       return NWSTK_WRONG_PARAM;
     }

     ISIL_DEBUG_TRACE(("ls_statemodify:"));

     ISIL_DEBUG_TRACE(("ls_statemodify:LinkSetId:%d",ls_state->linkSetId));

    if ((ls = LINKSET_FindLinkSet((ITS_OCTET)ls_state->linkSetId)) == NULL)
        {
            ISIL_ERROR_TRACE(("ls_statemodify:linkset not Found\n"));
            return NWSTK_LNKSET_NOTFOUND;
        }

       if(ls_state->adminState==1)
       {
           ISIL_DEBUG_TRACE(("ls_statemodify:Try to Activate linkset"));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
          if(ls->isUp  ==  ITS_TRUE)
          {
            ISIL_DEBUG_TRACE(("ls_statemodify: linkset isUp equals to ITS_TRUE, hence linkset already UP"));
            return NWSTK_CMD_CNG_SUCCESS;
          }
     /*R2-HA:End*/
           ret = MGMT_Main(MTP3_USER,
                              MGMT_TRIGGER_ACTIVATE_LINK_SET,
                              NULL, 0,
                              (ITS_OCTET)ls_state->linkSetId, ITS_SS7_DEFAULT_LINK_CODE);
        if (ret != ITS_SUCCESS)
        {
            ISIL_ERROR_TRACE(("ls_statemodify:linkset act  Fail\n"));
            return NWSTK_DEACTLINKSET_FAIL;
        }
       }
       else if(ls_state->adminState==0)
       {
           ISIL_DEBUG_TRACE(("ls_statemodify:Try to DeActivate linkset"));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
          if(ls->isUp  ==  ITS_FALSE)
          {
            ISIL_DEBUG_TRACE(("ls_statemodify: linkset isUp equals to ITS_FALSE, hence linkset already DOWN"));
            return NWSTK_CMD_CNG_SUCCESS;
          }
     /*R2-HA:End*/
           ret = MGMT_Main(MTP3_USER,
                              MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                              NULL, 0,
                              (ITS_OCTET)ls_state->linkSetId, ITS_SS7_DEFAULT_LINK_CODE);

       }

        if (ret != ITS_SUCCESS)
        {
            ISIL_ERROR_TRACE(("ls_statemodify::linkset act  Fail\n"));
            return  NWSTK_LINKSET_ACT_FAIL;
        }
return NWSTK_CMD_CNG_SUCCESS;
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static    int 
        isil_ln_statemodify(ITS_EVENT *ev)
{
ScmNwstkLinkAdminStateModify *ln_statemodify = (ScmNwstkLinkAdminStateModify *)ev->data;
 ITS_OCTET ls_id = 0;
 ITS_OCTET ln_id = 0;
int ret=0;

SS7_LinkPtr ln=NULL;

     if(ln_statemodify==NULL)
     {
       ISIL_ERROR_TRACE(("ln_statemodify:Fail"));
       return NWSTK_WRONG_PARAM;
     }
     ISIL_DEBUG_TRACE(("ln_statemodify:"));
     ISIL_DEBUG_TRACE(("ln_statemodify:LinkSetId:%d,LinkId:%d",ln_statemodify->linkSetId,ln_statemodify->linkId));
     ls_id = (ITS_OCTET)ln_statemodify->linkSetId;
     ln_id = (ITS_OCTET)ln_statemodify->linkId;


    if ((ln = LINK_FindLink((ITS_OCTET)ln_statemodify->linkSetId, (ITS_OCTET)ln_statemodify->linkId)) == NULL)
        {
            ISIL_ERROR_TRACE(("ln_statemodify:link not Found\n"));
            return NWSTK_LNK_NOTFOUND;
        }

       if(ln_statemodify->adminState==1)
       {    
           ISIL_DEBUG_TRACE(("ln_statemodify:Try to Activate link:ln->activityState[%d]",ln->activityState));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
	   if ((ln->activityState == LINK_ACTIVITY_INACTIVE) || (ln->activityState == LINK_ACTIVITY_DEACTIVE))
	   {
     /*R2-HA:End */
/*Itika changes-3-may-10 Start*/
          /* Send timer config command to mtp2*/
          ret=isil_mtp2timer_modify(ev);
          if(ret!=NWSTK_CMD_CNG_SUCCESS)
          {  
            ISIL_ERROR_TRACE(("ln_statemodify:modify mtp2 timer Fail\n"));
            return NWSTK_ACTLINK_FAIL;
          }
/*Itika changes-3-may-10 End*/

          /*change for SP restart*/
          if(SP_RestartFlag == 0)
           {
                ISIL_DEBUG_TRACE(("ln_statemodify:SP_Restart Start for linkset %d link %d",ls_id,ln_id));
                MGMT_Main(MTP3_USER,MGMT_TRIGGER_RESTART,NULL, 0,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE);
                SP_RestartFlag=1;
           }
            ret= MGMT_Main(MTP3_USER,
                             MGMT_TRIGGER_ACTIVATE_LINK,
                             NULL, 0,
                             ls_id, ln_id);
          /*change for SP restart
          if(SP_RestartFlag == 0)
           {
                ISIL_DEBUG_TRACE(("ls_statemodify:SP_Restart Start"));
                MGMT_Main_CCITT(MTP3_USER,MGMT_TRIGGER_RESTART,NULL, 0,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE);
                SP_RestartFlag=1;
           }*/
	  }
          else
	  {
               ISIL_DEBUG_TRACE(("ln_statemodify: link activity state neither Inactive nor deactive, hence link is already UP"));
	       return NWSTK_CMD_CNG_SUCCESS;

	  }
       }
       else if(ln_statemodify->adminState==0)
       { 
           ISIL_DEBUG_TRACE(("ln_statemodify:Try to DeActivate linkset %d link %d",ls_id,ln_id));
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
	   if (ln->activityState == LINK_ACTIVITY_INACTIVE || ln->activityState == LINK_ACTIVITY_DEACTIVE)
	   {
               ISIL_DEBUG_TRACE(("ln_statemodify: link is already DOWN"));
	       return NWSTK_CMD_CNG_SUCCESS;
	   }
     /*R2-HA:End */
           ret= MGMT_Main(MTP3_USER,
                             MGMT_TRIGGER_DEACTIVATE_LINK,
                             NULL, 0,
                             ls_id,ln_id);

       }
        if (ret != ITS_SUCCESS)
        {
            ISIL_ERROR_TRACE(("ln_statemodify:link act Fail\n"));
            return NWSTK_ACTLINK_FAIL;
        }
     ISIL_DEBUG_TRACE(("ln_statemodify:After Fnd"));
return NWSTK_CMD_CNG_SUCCESS;
}


#ifdef MSC_CODE
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static    int
  isil_gtt_add(ITS_EVENT *ev)
{
  ScmNwstkGttConfig *gtt_add =(ScmNwstkGttConfig *)ev->data;
//  IMR_Table table;
  int retn=0;
  int len=0;
  char i=0;
  ISIL_gttInfo gttInfo;

  gtt_add->digitString[20]='\0'; /*check for recevied null terminated string*/ 
 
  memset(gttInfo.str,'\0',sizeof(gttInfo.str));
 
   if(gtt_add ==NULL)
   {
      ISIL_ERROR_TRACE(("gtt_add:Fail"));
       return NWSTK_WRONG_PARAM;
   }
   ISIL_DEBUG_TRACE(("gtt_add:"));
   ISIL_DEBUG_TRACE(("gtt_add:data=%s\n",gtt_add->digitString));

   len=strlen((const char *)gtt_add->digitString);
   if(len >15 )
   {
      ISIL_ERROR_TRACE(("gtt_add:len Excedd"));
       return NWSTK_WRONG_PARAM;
   }
//   memcpy(gttInfo.str,gtt_add->digitString,len);
    strcpy(gttInfo.str,(const char *)gtt_add->digitString);

    ISIL_DEBUG_TRACE(("gtt_add:String=%s\n",gttInfo.str));
    ISIL_DEBUG_TRACE(("gtt_add:len=%d\n",strlen(gttInfo.str)));


    gttInfo.primarydpc=gtt_add->destinationPointCode;
//  gttInfo.secondarydpc=;
    gttInfo.ssn=gtt_add->ssn;
    gttInfo.routeflag=gtt_add->routeOn;
    ISIL_DEBUG_TRACE(("gtt_add:Route Flag=%d",gttInfo.routeflag));

     for(i=0;i<len;i++)
       {
          gttInfo.gttstring[i]=gtt_add->digitString[i]-48;
          ISIL_DEBUG_TRACE(("gtt_add:%d",gttInfo.gttstring[i]));
       }
      gttInfo.gttstring[i]='\0';
      ISIL_DEBUG_TRACE(("gtt_add:%d",i));
      retn=ISIL_setgttentry(&gttInfo);
         if (retn==IMR_ENTRYADDSUCC)
           { 
             ISIL_DEBUG_TRACE(("gtt_add:SUCCESS\n"));
            ISIL_DEBUG_TRACE(("Now The New update GT table Info\n"));
              return NWSTK_CMD_CNG_SUCCESS;
           }

         else if (retn==IMR_ENALRDYEXIST)
           {
             ISIL_ERROR_TRACE(("gtt_add:Already exist\n"));
            return NWSTK_GTTALREADY_EXIST;
           }


         else if (retn==IMR_ENTRYADDFAIL)
           {
            ISIL_ERROR_TRACE(("gtt_add:Add fail\n"));
            return NWSTK_GTTADD_FAIL;
           }




}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static    int
        isil_gtt_del(ITS_EVENT *ev)
{
  ScmNwstkGttConfig *gtt_del =(ScmNwstkGttConfig *)ev->data;
//  IMR_Table table;
  int retn=0;
  int len=0;
  char i=0;
  ISIL_gttInfo gttInfo;
  gtt_del->digitString[20]='\0'; /*check for recevied null terminated string*/
 
  memset(gttInfo.str,'\0',sizeof(gttInfo.str));
 
    if(gtt_del==NULL)
    {  
       ISIL_ERROR_TRACE(("gtt_del:Fail"));
       return NWSTK_WRONG_PARAM;
    }
  ISIL_DEBUG_TRACE(("gtt_del:"));
  ISIL_DEBUG_TRACE(("gtt_del:data=%s\n",gtt_del->digitString));

   if(len >15 )
   {
      ISIL_ERROR_TRACE(("gtt_del:len Excedd"));
       return NWSTK_WRONG_PARAM;
   }
  len=strlen((const char *)gtt_del->digitString);

 //  memcpy(gttInfo.str,gtt_del->digitString,len);
   strcpy(gttInfo.str,(const char *)gtt_del->digitString);
   gttInfo.primarydpc=gtt_del->destinationPointCode;
// gttInfo.secondarydpc=;
   gttInfo.ssn=gtt_del->ssn;
   gttInfo.routeflag=gtt_del->routeOn;
   ISIL_DEBUG_TRACE(("gtt_del:Route Flag=%d",gttInfo.routeflag));

    ISIL_DEBUG_TRACE(("gtt_del:String=%s\n",gttInfo.str));
    ISIL_DEBUG_TRACE(("gtt_del:len=%d\n",strlen(gttInfo.str)));

     for(i=0;i<len;i++)
       {
          gttInfo.gttstring[i]=gtt_del->digitString[i]-48;

       }
        gttInfo.gttstring[i]='\0';
         retn=ISIL_remgttentry(&gttInfo);

         if (retn==IMR_ENTRYREMSUCC)
           { 
             ISIL_ERROR_TRACE(("gtt_del:SUCCESS\n"));
              return NWSTK_CMD_CNG_SUCCESS;
          }

         else if (retn==IMR_ENTRYNOFOUND)
           {
             ISIL_ERROR_TRACE(("gtt_del:no exist\n"));
            return NWSTK_GTTNOT_EXIST;
           }

         else if (retn==IMR_ENTRYREMFAIL)
           {
            ISIL_ERROR_TRACE(("gtt_del:Del fail\n"));
            return NWSTK_GTTREM_FAIL;
           }

          ISIL_DEBUG_TRACE(("Now The New update GT table Info\n"));
//          IMR_GTT_Implemt();


}

#endif // MSC_CODE
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static    int
    isil_bssapcic_add(ITS_EVENT *ev)
{

    ScmNwstkBssapCicConfig *bssapcic = (ScmNwstkBssapCicConfig *)ev->data;
    int ret=0;     
    ITS_INT pcm=0;
    BSSAP_CicDB cicdb;
    ITS_INT i=0;
    ITS_INT Sts=0;
    ITS_INT Fts=0;
    ISIL_DEBUG_TRACE(("bssapcic_add:"));
    if(bssapcic==NULL)
    { 
       ISIL_ERROR_TRACE(("bssapcic_add:"));
       return NWSTK_WRONG_PARAM;
    }

    ISIL_DEBUG_TRACE(("bssapcic_add:StartCIC:%d,EndCIC:%d ",bssapcic->startCic,bssapcic->endCic));
    ITS_INT Startpcm = ((bssapcic->startCic) & 0x0000ffe0 ) >> tshift;
    ITS_INT Endpcm = ((bssapcic->endCic) & 0x0000ffe0 ) >> tshift;
    ISIL_DEBUG_TRACE(("bssapcic_add:Startpcm:%d,EndPcm:%d ",Startpcm,Endpcm));

   if(Startpcm==Endpcm)
   {
       Sts = ((bssapcic->startCic) & 0x0000001f) ;
       Fts= ((bssapcic->endCic) & 0x0000001f) ;
       pcm=Startpcm;
       ISIL_DEBUG_TRACE(("bssapcic_add:pcm:%d,Sts:%d,Fts:%d ",pcm,Sts,Fts));

      if (pcm < 0 || Sts < 0)
      {
            ISIL_ERROR_TRACE(("bssapcic_add:Invalid Param "));
            return NWSTK_WRONG_PARAM;
      }

     if (pcm > (0x7FFU) || Fts > (0x1FU) || bssapcic->interfaceId > (0xFFU))
      {
           ISIL_ERROR_TRACE(("bssapcic_add:Invalid Param "));
           return NWSTK_WRONG_PARAM;
      }

    ret = cicdb.AddCIC(bssapcic->interfaceId, pcm, Sts, Fts);
    if (ret != ITS_SUCCESS)
     {
       if(ret== ITS_EDUPLENTRY)
         {
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
              ISIL_ERROR_TRACE(("bssapcic_add:already exists : Duplicate CIC Entry "));
              /*return NWSTK_CIC_ALREADY_EXIST;*/
               return NWSTK_CMD_CNG_SUCCESS;
     /*R2-HA:End*/
         }
        else
         {
             ISIL_ERROR_TRACE(("bssapcic_add:fail "));
              return NWSTK_BSSAPCFGADD_FAIL;
         }
      }
   return NWSTK_CMD_CNG_SUCCESS;
  }/*endof startpcm==endpcm */
 else 
  {
     ITS_INT Sts = ((bssapcic->startCic) & 0x0000001f) ;
     
    for(i=Startpcm; i <= Endpcm; i++)
    {
       pcm=i;

       if(pcm==Endpcm)
       {
         Fts = ((bssapcic->endCic) & 0x0000001f) ;
       }
       else
       { 
         Fts = FIXED_RANGE ;
       }
      ISIL_DEBUG_TRACE(("bssapcic_add:pcm:%d,Sts:%d,Fts:%d ",pcm,Sts,Fts));

      if (pcm < 0 || Sts < 0)
      {
            ISIL_ERROR_TRACE(("bssapcic_add:Invalid Param "));
            return NWSTK_WRONG_PARAM;
      }

     if (pcm > (0x7FFU) || Fts > (0x1FU) || bssapcic->interfaceId > (0xFFU))
      {
           ISIL_ERROR_TRACE(("bssapcic_add:Invalid Param "));
           return NWSTK_WRONG_PARAM;
      }

    ret = cicdb.AddCIC(bssapcic->interfaceId, pcm, Sts, Fts);
    if (ret != ITS_SUCCESS)
     {
       if(ret== ITS_EDUPLENTRY)
         {
              ISIL_ERROR_TRACE(("bssapcic_add:Duplicay "));
              return NWSTK_CIC_ALREADY_EXIST;

         }
        else
         {
             ISIL_ERROR_TRACE(("bssapcic_add:fail "));
              return NWSTK_BSSAPCFGADD_FAIL;
         }
      }
   Sts=0;/*reinit*/
   }
  return NWSTK_CMD_CNG_SUCCESS;

 }

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static    int
        isil_bssapcic_del(ITS_EVENT *ev)
{
    ScmNwstkBssapCicConfig *bssapcic = (ScmNwstkBssapCicConfig *)ev->data;
    ITS_INT ts=0; 
    ITS_INT Sts=0;
    ITS_INT Fts=0;
    ITS_INT pcm=0;
    ITS_INT i=0;

    ISIL_DEBUG_TRACE(("bssapcic_del:"));
 /*   ITS_INT pcm = ((bssapcic->startCic) & 0x0000ffe0 ) >> tshift;
    ITS_INT Sts = ((bssapcic->startCic) & 0x0000001f) ;
    ITS_INT Fts= ((bssapcic->endCic) & 0x0000001f) ;*/
  
    /*Note :R2-HA:Start: As CIC already got deleted by active card , so no need to delete on standby*/ 
    if(NODECARDSTATE == CARDSTATE_STANDBY)
    {
       ISIL_ERROR_TRACE(( " No need to process CIC DEL command on standby in case of redundancy,return success \n")); 
       return NWSTK_CMD_CNG_SUCCESS;
    }
    /*Note :R2-HA:END*/ 
    ITS_UINT cic = 0;
    int ret=0;
    BSSAP_CicDB cicdb;
    if(bssapcic==NULL)
    {
       ISIL_ERROR_TRACE(("bssapcic_del:"));
       return NWSTK_WRONG_PARAM;
    }

    ISIL_DEBUG_TRACE(("bssapcic_del:StartCIC:%d,EndCIC:%d ",bssapcic->startCic,bssapcic->endCic));
    ITS_INT Startpcm = ((bssapcic->startCic) & 0x0000ffe0 ) >> tshift;
    ITS_INT Endpcm = ((bssapcic->endCic) & 0x0000ffe0 ) >> tshift;
    ISIL_DEBUG_TRACE(("bssapcic_del:Startpcm:%d,EndPcm:%d ",Startpcm,Endpcm));

//    ISIL_DEBUG_TRACE(("bssapcic_del:pcm:%d ,Sts:%d,Fts:%d ",pcm,Sts,Fts));


    
  if(Startpcm==Endpcm)
  {
     Sts = ((bssapcic->startCic) & 0x0000001f) ;
     Fts= ((bssapcic->endCic) & 0x0000001f) ;
     pcm=Startpcm;
     ISIL_DEBUG_TRACE(("bssapcic_del:pcm:%d,Sts:%d,Fts:%d ",pcm,Sts,Fts));
    if (pcm < 0 || Sts < 0)
     {
            ISIL_ERROR_TRACE(("bssapcic_del:Invalid Param "));
            return NWSTK_WRONG_PARAM;
     }

   if (pcm > (0x7FFU) || Fts > (0x1FU) || bssapcic->interfaceId > (0xFFU))
    {
           ISIL_ERROR_TRACE(("bssapcic_del:Invalid Param "));
           return NWSTK_WRONG_PARAM;
    }

      for(ts = Sts ; ts <= Fts ;ts++)
       {
         cic = (bssapcic->interfaceId << 16) | ((pcm << 5) | (0x1FU & ts));

        ret = cicdb.RemoveCICRecord(cic, bssapcic->interfaceId);
         if (ret != ITS_SUCCESS)
         {
              ISIL_ERROR_TRACE(("bssapcic_del:fail "));
              return NWSTK_BSSAPCICDEL_FAIL;
         }
       }

  }
 else
  {   
    ITS_INT Sts = ((bssapcic->startCic) & 0x0000001f) ;
    for(i=Startpcm; i <= Endpcm; i++)
    {
       pcm=i;

       if(pcm==Endpcm)
       {
         Fts = ((bssapcic->endCic) & 0x0000001f) ;
       }
       else
       {
         Fts = FIXED_RANGE ;
       }
      ISIL_DEBUG_TRACE(("bssapcic_del:pcm:%d,Sts:%d,Fts:%d ",pcm,Sts,Fts));

      if (pcm < 0 || Sts < 0)
      {
            ISIL_ERROR_TRACE(("bssapcic_del:Invalid Param "));
            return NWSTK_WRONG_PARAM;
      }

     if (pcm > (0x7FFU) || Fts > (0x1FU) || bssapcic->interfaceId > (0xFFU))
      {
           ISIL_ERROR_TRACE(("bssapcic_del:Invalid Param "));
           return NWSTK_WRONG_PARAM;
      }
      for(ts = Sts ; ts <= Fts ;ts++)
       {
         cic = (bssapcic->interfaceId << 16) | ((pcm << 5) | (0x1FU & ts));
         ret = cicdb.RemoveCICRecord(cic, bssapcic->interfaceId);
         if (ret != ITS_SUCCESS)
         {
              ISIL_ERROR_TRACE(("bssapcic_del:fail "));
              return NWSTK_BSSAPCICDEL_FAIL;
         }
      } 
     Sts=0;/*reinit*/
    }
 }
   return NWSTK_CMD_CNG_SUCCESS;
}

/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static    int
  isil_bssapcfg_add(ITS_EVENT *ev)
{
ScmNwstkBssapcfgConfig *bssapcfg =(ScmNwstkBssapcfgConfig *)ev->data;
 ITS_INT lpc = 0;
 ITS_INT rpc = 0;
 ITS_INT lssn = 0xFE;
 ITS_INT rssn = 0xFE;
 int ret=0;
 BSSAP_CfgDB cfgdb;
 CFGData* cfg = NULL;
#ifdef MSC_CODE
 BSSAP_ResetDB Rdb;
#endif
  if(bssapcfg==NULL)
  {
    ISIL_ERROR_TRACE(("bssapcfg_add:Fail"));
    return NWSTK_WRONG_PARAM;
  }
    ISIL_DEBUG_TRACE(("bssapcfg_add:"));

    ISIL_DEBUG_TRACE(("bssapcfg_add:BscId:%d, lpc:%d,rpc:%d",bssapcfg->interfaceId,bssapcfg->lpc,bssapcfg->rpc));


   if (bssapcfg->interfaceId > (0xFFU))
        {
            ISIL_ERROR_TRACE(("bssapcfg_add:Invalid Param "));

            return NWSTK_WRONG_PARAM;
        }

        if (bssapcfg->lpc < 0 || bssapcfg->rpc < 0 || lssn < 0 || rssn < 0)
        {
            ISIL_ERROR_TRACE(("bssapcfg_add:Invalid Param "));

            return NWSTK_WRONG_PARAM;
        }

       ret=cfgdb.AddCfg(bssapcfg->interfaceId , bssapcfg->lpc, bssapcfg->rpc,lssn, rssn);

        if (ret != ITS_SUCCESS)
        {
          if(ret== ITS_EDUPLENTRY)
          {
     /* Note :R2-HA:Start:Return success in case of duplicate command receive from cfg */ 
              ISIL_ERROR_TRACE(("bssapcfg_add:already exists : Duplicate CFG Entry"));
              return NWSTK_CMD_CNG_SUCCESS;
              /*return NWSTK_CFG_ALREADY_EXIST;*/
     /*R2-HA:End*/
          }
         else
          {
              ISIL_ERROR_TRACE(("bssapcfg_add:fail "));
              return NWSTK_BSSAPCFGADD_FAIL;
          }
        }
#ifdef MSC_CODE
       ret=Rdb.AddResetData(bssapcfg->interfaceId);         
        if (ret != ITS_SUCCESS)
        {
              ISIL_ERROR_TRACE(("bssapcfg_del:fail "));
              return NWSTK_BSSAPCFGADD_FAIL;
        }
#endif 
   return NWSTK_CMD_CNG_SUCCESS;


}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static    int
        isil_bssapcfg_del(ITS_EVENT *ev)
{
ScmNwstkBssapcfgConfig *bssapcfg =(ScmNwstkBssapcfgConfig *)ev->data; ITS_INT rpc = 0;

 int ret=0;
 BSSAP_CfgDB cfgdb;
 CFGData* cfg = NULL;
#ifdef MSC_CODE
 BSSAP_ResetDB Rdb;
#endif

  if(bssapcfg==NULL)
  {
    ISIL_ERROR_TRACE(("bssapcfg_del:Fail"));
    return NWSTK_WRONG_PARAM;
  }
    ISIL_DEBUG_TRACE(("bssapcfg_del:"));

   ISIL_DEBUG_TRACE(("bssapcfg_del:BscId:%d, lpc:%d,rpc:%d",bssapcfg->interfaceId,bssapcfg->lpc,bssapcfg->rpc));

    /*Note :R2-HA:Start: As bssap interface already got deleted by active card , so no need to delete on standby*/ 
    if(NODECARDSTATE == CARDSTATE_STANDBY)
    {
       ISIL_ERROR_TRACE(( " No need to process BSSAP INTERFACE DEL command on standby in case of redundancy,return Success \n")); 
       return NWSTK_CMD_CNG_SUCCESS;
    }

   if (bssapcfg->interfaceId > (0xFFU))
   {
     ISIL_ERROR_TRACE(("bssapcfg_del:Invalid Param "));
     return NWSTK_WRONG_PARAM;
   }

   ret = cfgdb.RemoveRPCEntry(bssapcfg->interfaceId);

        if (ret != ITS_SUCCESS)
        {
              ISIL_ERROR_TRACE(("bssapcfg_del:fail "));
              return NWSTK_BSSAPCFGDEL_FAIL;
        }

   ret = cfgdb.RemoveNWIDEntry(bssapcfg->rpc);

        if (ret != ITS_SUCCESS)
        {
              ISIL_ERROR_TRACE(("bssapcfg_del:fail "));
              return NWSTK_BSSAPCFGDEL_FAIL;
        }

#ifdef MSC_CODE
   ret=  Rdb.RemoveResetData(bssapcfg->interfaceId);

        if (ret != ITS_SUCCESS)
        {
              ISIL_ERROR_TRACE(("bssapcfg_del:fail "));
              return NWSTK_BSSAPCFGDEL_FAIL;
        }
#endif
   return NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static    int
isil_rtmodify_state(ITS_EVENT *ev)

{

  ScmNwstkSs7RouteAdminStateModify *rtmodifystat = (ScmNwstkSs7RouteAdminStateModify *)ev->data;
 ROUTE_MatchInfo rinfo;
 int ret=0;

 if(rtmodifystat==NULL)
  {
    ISIL_ERROR_TRACE(("rtmodify_state:Fail"));
    return NWSTK_WRONG_PARAM;
  }
  ISIL_DEBUG_TRACE(("rtmodify_state:"));

  ISIL_DEBUG_TRACE(("rtmodifystat:linkset :%d RPC :%d",rtmodifystat->linkSetId,rtmodifystat->destinationPointCode));

 if(rtmodifystat->direction == 0 )
  {
    ISIL_DEBUG_TRACE(("Direction:LOCAL ROUTE"));
   rinfo.basic.type =ROUTE_TYPE( LOCAL_ROUTE ); 
  }
 else if(rtmodifystat->direction == 1)
  {
   rinfo.basic.type = ROUTE_TYPE(REMOTE_ROUTE);
    ISIL_DEBUG_TRACE(("Direction:REMOTE ROUTE"));
  }
 else 
  {
    ISIL_ERROR_TRACE(("rtmodify_state:Direction must be local or remote"));
   return NWSTK_WRONG_PARAM;
  }

  if(rtmodifystat->family==1)
  {
    rinfo.basic.family=FAMILY_ANSI;
     ISIL_DEBUG_TRACE(("Family:ANSI"));
  }
 else if ( rtmodifystat->family==0 )
  {
    rinfo.basic.family=FAMILY_ITU;
     ISIL_DEBUG_TRACE(("Family:ITU"));
  }
  else if(rtmodifystat->family== 2)
  {
    rinfo.basic.family=FAMILY_CHINA;
     ISIL_DEBUG_TRACE(("Family:CHINA"));
  }
 else if(rtmodifystat->family== 3) 
 {
  rinfo.basic.family=FAMILY_JAPAN;
     ISIL_DEBUG_TRACE(("Family:JAPAN"));
 } 
 else
 {
   ISIL_ERROR_TRACE(("rtmodify_state:Family  must be itu ,ansi, china or japan "));
   return NWSTK_WRONG_PARAM;
 
 }
   if(rtmodifystat->style==0)
   {
    ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_NI"));
    rinfo.basic.style=ROUTE_DPC_NI;
   }
  else if(rtmodifystat->style==1)
   {
    ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_SIO"));
    rinfo.basic.style=ROUTE_DPC_SIO;
   }
  else  if(rtmodifystat->style==2)
   {
    ISIL_DEBUG_TRACE(("Style:ROUTE_DPC_SIO_SSN"));
    rinfo.basic.style=ROUTE_DPC_SIO_SSN;
   }

   rinfo.basic.dpc = rtmodifystat->destinationPointCode;
   
   if(rinfo.basic.style==ROUTE_DPC_NI )
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)rtmodifystat->sio & ROUTE_NI_MASK;

   }
   else if (rinfo.basic.style==ROUTE_DPC_SIO )
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)rtmodifystat->sio ;

   }
  else if(rinfo.basic.style==ROUTE_DPC_SIO_SSN)
   {
     rinfo.basic.criteria.sio = (ITS_OCTET)rtmodifystat->sio ;
     rinfo.basic.criteria.ssn = (ITS_OCTET)rtmodifystat->rssn;


   }
  else
   {
     ISIL_ERROR_TRACE(("rtmodify_state:wrong style "));
     return NWSTK_WRONG_PARAM;

   }

   if(rtmodifystat->adminState==1)
   {
     ISIL_DEBUG_TRACE(("rtmodify_state:Try to unlock the route"));
     ret=ROUTE_SetRouteAdminStatus(rinfo.basic.dpc, ITS_TRUE,
                                    rinfo.basic.style,
                                    rinfo.basic.family,
                                    rinfo.basic.criteria.sio,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS);
        if(ret!=ITS_SUCCESS)
         {
             /* Failed to set the route context status */
             ISIL_ERROR_TRACE(("rtmodify_state: Failed to set the route"
                         " context status\n"));
             return NWSTK_SCM_ROUTE_ADMIN_STATE_NACK_RESP; 
         }
   }
   else if(rtmodifystat->adminState==0)
   {
     ISIL_DEBUG_TRACE(("rtmodify_state:Try to lock the route"));
     ret=ROUTE_SetRouteAdminStatus(rinfo.basic.dpc, ITS_FALSE,
                                    rinfo.basic.style,
                                    rinfo.basic.family,
                                    rinfo.basic.criteria.sio,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS);
    
        if(ret!=ITS_SUCCESS)
         {
             /* Failed to set the route context status */
             ISIL_ERROR_TRACE(("rtmodify_state: Failed to set the route"
                         " context status\n"));
             return NWSTK_SCM_ROUTE_ADMIN_STATE_NACK_RESP; 
	 }
    }
   return NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static  int
isil_modify_mtp3tmr(ITS_EVENT *ev)
{
 int tr, value = 0;
 int ret=0;
 ScmNwstkMtp3TimerModify *mtp3tmr = (ScmNwstkMtp3TimerModify *)ev->data;

  ISIL_DEBUG_TRACE(("modify_mtp3tmr:"));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:Configured TimerValue will be 100*display value "));


  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T1 :%d",mtp3tmr->mtp3TimerT1));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T2 :%d",mtp3tmr->mtp3TimerT2));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T3 :%d",mtp3tmr->mtp3TimerT3));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T4 :%d",mtp3tmr->mtp3TimerT4));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T5 :%d",mtp3tmr->mtp3TimerT5));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T6 :%d",mtp3tmr->mtp3TimerT6));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T7 :%d",mtp3tmr->mtp3TimerT7));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T8 :%d",mtp3tmr->mtp3TimerT8));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T9 :%d",mtp3tmr->mtp3TimerT9));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T10 :%d",mtp3tmr->mtp3TimerT10));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T11 :%d",mtp3tmr->mtp3TimerT11));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T12 :%d",mtp3tmr->mtp3TimerT12));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T13 :%d",mtp3tmr->mtp3TimerT13));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T14 :%d",mtp3tmr->mtp3TimerT14));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T15 :%d",mtp3tmr->mtp3TimerT15));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T16 :%d",mtp3tmr->mtp3TimerT16));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T17 :%d",mtp3tmr->mtp3TimerT17));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T18 :%d",mtp3tmr->mtp3TimerT18));
 /* ISIL_DEBUG_TRACE(("modify_mtp3tmr:T19 :%d",mtp3tmr->mtp3TimerT19));not in use*/
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T19 : not in use"));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T20 :%d",mtp3tmr->mtp3TimerT20));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T21 :%d",mtp3tmr->mtp3TimerT21));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T22 :%d",mtp3tmr->mtp3TimerT22));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T23 :%d",mtp3tmr->mtp3TimerT23));
/* For ITU read form XML T23 to 34*/
/*
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T24 :%d",mtp3tmr->mtp3TimerT24));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T25 :%d",mtp3tmr->mtp3TimerT25));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T26 :%d",mtp3tmr->mtp3TimerT26));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T27 :%d",mtp3tmr->mtp3TimerT27));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T28 :%d",mtp3tmr->mtp3TimerT28));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T29 :%d",mtp3tmr->mtp3TimerT29));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T30 :%d",mtp3tmr->mtp3TimerT30));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T31 :%d",mtp3tmr->mtp3TimerT31));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T32 :%d",mtp3tmr->mtp3TimerT32));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T33 :%d",mtp3tmr->mtp3TimerT33));
  ISIL_DEBUG_TRACE(("modify_mtp3tmr:T34 :%d",mtp3tmr->mtp3TimerT34));
*/
   if(mtp3tmr->mtp3TimerT1 > 0)
    {extern int __Protfamily_t1; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T1,                                                                    mtp3tmr->mtp3TimerT1*100);
     __Protfamily_t1 = mtp3tmr->mtp3TimerT1*100;
    }
           
   if(mtp3tmr->mtp3TimerT2 >0)
    {extern int __Protfamily_t2; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T2,                                                                    mtp3tmr->mtp3TimerT2*100);
		__Protfamily_t2 = mtp3tmr->mtp3TimerT2*100;
    }
   if(mtp3tmr->mtp3TimerT3 >0)
    { extern int __Protfamily_t3; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T3,                                                                    mtp3tmr->mtp3TimerT3*100);
		  __Protfamily_t3 = mtp3tmr->mtp3TimerT3*100;
    }
   if(mtp3tmr->mtp3TimerT4 >0)
    {extern int __Protfamily_t4; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T4,                                                                    mtp3tmr->mtp3TimerT4*100);
		 __Protfamily_t4 = mtp3tmr->mtp3TimerT4*100;
    }
   if(mtp3tmr->mtp3TimerT5 >0)
    {  extern int __Protfamily_t5;
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T5,                                                                    mtp3tmr->mtp3TimerT5*100);
		  __Protfamily_t5 = mtp3tmr->mtp3TimerT5*100;
    }
   if(mtp3tmr->mtp3TimerT6 >0)
    {extern int __Protfamily_t6; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T6,                                                                    mtp3tmr->mtp3TimerT6*100);
		 __Protfamily_t6 = mtp3tmr->mtp3TimerT6*100;
    }
   if(mtp3tmr->mtp3TimerT7 >0)
    {extern int __Protfamily_t7; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T7,                                                                    mtp3tmr->mtp3TimerT7*100);
		 __Protfamily_t7 = mtp3tmr->mtp3TimerT7*100;
    }
   if(mtp3tmr->mtp3TimerT8 >0)
    {extern int __Protfamily_t8; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T8,                                                                    mtp3tmr->mtp3TimerT8*100);
		  __Protfamily_t8 = mtp3tmr->mtp3TimerT8*100;
    }
   if(mtp3tmr->mtp3TimerT9 >0)
    { extern int __Protfamily_t9; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T9,                                                                    mtp3tmr->mtp3TimerT9*100);
			__Protfamily_t9 = mtp3tmr->mtp3TimerT9*100;
    }
   if(mtp3tmr->mtp3TimerT10 >0)
    {extern int __Protfamily_t10; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T10,                                                                    mtp3tmr->mtp3TimerT10*100);
		 __Protfamily_t10 = mtp3tmr->mtp3TimerT10*100;
    }
   if(mtp3tmr->mtp3TimerT11 >0)
    {extern int __Protfamily_t11 ; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T11,                                                                    mtp3tmr->mtp3TimerT11*100);
		  __Protfamily_t11 = mtp3tmr->mtp3TimerT11*100;
    }
   if(mtp3tmr->mtp3TimerT12 >0)
    { extern int __Protfamily_t12 ;
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T12,                                                                    mtp3tmr->mtp3TimerT12*100);
		 __Protfamily_t12 = mtp3tmr->mtp3TimerT12*100;
    }
   if(mtp3tmr->mtp3TimerT13 >0)
    { extern int __Protfamily_t13 ; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T13,                                                                    mtp3tmr->mtp3TimerT13*100);
		 __Protfamily_t13 = mtp3tmr->mtp3TimerT13*100;
    }
   if(mtp3tmr->mtp3TimerT14 >0)
    {  extern int __Protfamily_t14 ;
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T14,                                                                    mtp3tmr->mtp3TimerT14*100);
		 __Protfamily_t14 = mtp3tmr->mtp3TimerT14*100;
    }
   if(mtp3tmr->mtp3TimerT15 >0)
    {extern int __Protfamily_t15 ; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T15,                                                                    mtp3tmr->mtp3TimerT15*100);
		 __Protfamily_t15 = mtp3tmr->mtp3TimerT15*100;
    }
   if(mtp3tmr->mtp3TimerT16 >0)
    {extern int __Protfamily_t16 ; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T16,                                                                    mtp3tmr->mtp3TimerT16*100);
			__Protfamily_t16 = mtp3tmr->mtp3TimerT16*100;
    }
   if(mtp3tmr->mtp3TimerT17 >0)
    { extern int __Protfamily_t17 ;
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T17,                                                                     mtp3tmr->mtp3TimerT17*100);
			__Protfamily_t17 = mtp3tmr->mtp3TimerT17*100;
    }
   if(mtp3tmr->mtp3TimerT18 >0)
    {extern int __Protfamily_t18 ; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T18,                                                                    mtp3tmr->mtp3TimerT18*100);
		 __Protfamily_t18 = mtp3tmr->mtp3TimerT18*100;
    }
/* Not in Use
   if(mtp3tmr->mtp3TimerT19 >0)
    { 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T19,                                                                    mtp3tmr->mtp3TimerT19*100);
    }
*/
   if(mtp3tmr->mtp3TimerT20 >0)
    {extern int __Protfamily_t20 ; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T20,                                                                    mtp3tmr->mtp3TimerT20*100);
		 __Protfamily_t20 = mtp3tmr->mtp3TimerT20*100;
    }
   if(mtp3tmr->mtp3TimerT21 >0)
    {extern int __Protfamily_t21; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T21,                                                                    mtp3tmr->mtp3TimerT21*100);
		  __Protfamily_t21 = mtp3tmr->mtp3TimerT21*100;
    }
   if(mtp3tmr->mtp3TimerT22 >0)
    {extern int __Protfamily_t22; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T22,                                                                    mtp3tmr->mtp3TimerT22*100);
		 __Protfamily_t22 = mtp3tmr->mtp3TimerT22*100;
    }
   if(mtp3tmr->mtp3TimerT23 >0)
    {extern int __Protfamily_t23; 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T23,                                                                    mtp3tmr->mtp3TimerT23*100);
		 __Protfamily_t23 = mtp3tmr->mtp3TimerT23*100;
    }
/* For ITU read from XML T23 to 34*/
/*
   if(mtp3tmr->mtp3TimerT24 >0)
    { 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T24,                                                                    mtp3tmr->mtp3TimerT24*100);
    }
   if(mtp3tmr->mtp3TimerT25 >0)
    { 
      TIMERS_SetTimerValue(&MTP3_Timers, MTP3_TIMER_T25,                                                                    mtp3tmr->mtp3TimerT25*100);
    }
   if(mtp3tmr->mtp3TimerT26 >0) 
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T26,                                                                    mtp3tmr->mtp3TimerT26*100);
    }
   if(mtp3tmr->mtp3TimerT27 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T27,                                                                    mtp3tmr->mtp3TimerT27*100);
    }
   if(mtp3tmr->mtp3TimerT28 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T28,                                                                    mtp3tmr->mtp3TimerT28*100);
    }
   if(mtp3tmr->mtp3TimerT29 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T29,                                                                    mtp3tmr->mtp3TimerT29*100);
    }
   if(mtp3tmr->mtp3TimerT30 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T30,                                                                    mtp3tmr->mtp3TimerT30*100);
    }
   if(mtp3tmr->mtp3TimerT31 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T31,                                                                    mtp3tmr->mtp3TimerT31*100);
    }
   if(mtp3tmr->mtp3TimerT32 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T32,                                                                    mtp3tmr->mtp3TimerT32*100);
    }
   if(mtp3tmr->mtp3TimerT33 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T33,                                                                    mtp3tmr->mtp3TimerT33*100);
    }
   if(mtp3tmr->mtp3TimerT34 >0)
    { 
      TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T34,                                                                    mtp3tmr->mtp3TimerT34*100);
    }

*/

   return NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static    int
isil_modify_sccptmr(ITS_EVENT *ev)
{

 ScmNwstkSccpTimerModify *sccptmr = (ScmNwstkSccpTimerModify *)ev->data;
 int ret=0;

 if(sccptmr==NULL)
 {
   ISIL_ERROR_TRACE(("modify_sccptmr:Fail"));
   return NWSTK_WRONG_PARAM;
 }
 ISIL_DEBUG_TRACE(("modify_sccptmr:"));
 ISIL_DEBUG_TRACE(("modify_sccptmr:TimerValue"));
 ISIL_DEBUG_TRACE(("modify_sccptmr:TStatInfo :%d",sccptmr->sccpTimerstatInfo));
 ISIL_DEBUG_TRACE(("modify_sccptmr:Tcordcfg  :%d",sccptmr->sccpTimercoordChg));
 ISIL_DEBUG_TRACE(("modify_sccptmr:Tigoresst :%d",sccptmr->sccpTimerig0reSST));
 ISIL_DEBUG_TRACE(("modify_sccptmr:TrtgStat  :%d",sccptmr->sccpTimerrtgStatInfor));
 ISIL_DEBUG_TRACE(("modify_sccptmr:Tconn     :%d",sccptmr->sccpTimerconn));
 ISIL_DEBUG_TRACE(("modify_sccptmr:Trelease  :%d",sccptmr->sccpTimerrelease ));
 ISIL_DEBUG_TRACE(("modify_sccptmr:Treset    :%d",sccptmr->sccpTimerreset));
 ISIL_DEBUG_TRACE(("modify_sccptmr:Tias      :%d",sccptmr->sccpTimerias));
 ISIL_DEBUG_TRACE(("modify_sccptmr:Tiar      :%d",sccptmr->sccpTimeriar));

 if(sccptmr->sccpTimerstatInfo >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_statInfo, sccptmr->sccpTimerstatInfo);
 }
 if(sccptmr->sccpTimercoordChg >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_coordChg, sccptmr->sccpTimercoordChg);


 }
 if(sccptmr->sccpTimerig0reSST >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers,SCCP_T_ignoreSST , sccptmr->sccpTimerig0reSST);


 }
 if(sccptmr->sccpTimerrtgStatInfor >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_rtgStatInfo, sccptmr->sccpTimerrtgStatInfor);


 }
 if(sccptmr->sccpTimerconn >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_conn, sccptmr->sccpTimerconn);

 }
 if(sccptmr->sccpTimerrelease >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_release, sccptmr->sccpTimerrelease);


 }
 if(sccptmr->sccpTimerreset)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_reset, sccptmr->sccpTimerreset);


 }
 if(sccptmr->sccpTimerias >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_ias, sccptmr->sccpTimerias);


 }
 if(sccptmr->sccpTimeriar >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_iar, sccptmr->sccpTimeriar);


 }
 if(sccptmr->sccpTimerguard >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_guard, sccptmr->sccpTimerguard);


 }
 if(sccptmr->sccpTimerreassembly >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_reassembly, sccptmr->sccpTimerreassembly);


 }
 if(sccptmr->sccpTimerinterval>0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers,SCCP_T_interval , sccptmr->sccpTimerinterval);


 }
 if(sccptmr->sccpTimerrepeatRelease >0)
 {
  TIMERS_SetTimerValue(&SCCP_Timers, SCCP_T_repeatRelease, sccptmr->sccpTimerrepeatRelease);


 }
   return NWSTK_CMD_CNG_SUCCESS;
}

/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/

static    int
isil_modify_bssaptmr(ITS_EVENT *ev)
{
ScmNwstkBssapTimerModify *bssaptmr = (ScmNwstkBssapTimerModify *)ev->data;

 int ret=0;
 if(bssaptmr==NULL)
 {
   ISIL_ERROR_TRACE(("modify_bssaptmr:Fail"));
   return NWSTK_WRONG_PARAM;
 }
 ISIL_DEBUG_TRACE(("modify_bssaptmr:"));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:TimerValue::::"));


 ISIL_DEBUG_TRACE(("modify_bssaptmr:T1  :%d",bssaptmr->bssapTimerT1));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T4  :%d",bssaptmr->bssapTimerT4));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T7  :%d",bssaptmr->bssapTimerT7));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T8 :%d",bssaptmr->bssapTimerT8));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T10 :%d",bssaptmr->bssapTimerT10));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T11 :%d",bssaptmr->bssapTimerT11));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T13 :%d",bssaptmr->bssapTimerT13));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T17 :%d",bssaptmr->bssapTimerT17));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T18 :%d",bssaptmr->bssapTimerT18));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T19 :%d",bssaptmr->bssapTimerT19));
 ISIL_DEBUG_TRACE(("modify_bssaptmr:T20 :%d",bssaptmr->bssapTimerT20));


 if(bssaptmr->bssapTimerT1 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_1,bssaptmr->bssapTimerT1 );

 }
 if(bssaptmr->bssapTimerT4 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_4, bssaptmr->bssapTimerT4);

 }

 if(bssaptmr->bssapTimerT7 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_7,bssaptmr->bssapTimerT7 );

 }
 if(bssaptmr->bssapTimerT8 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_8,bssaptmr->bssapTimerT8 );

 }
 if(bssaptmr->bssapTimerT10 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_10,bssaptmr->bssapTimerT10 );

 }
 if(bssaptmr->bssapTimerT11 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_11,bssaptmr->bssapTimerT11 );

 }
 if(bssaptmr->bssapTimerT13 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_13,bssaptmr->bssapTimerT13 );

 }
 if(bssaptmr->bssapTimerT17 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_17,bssaptmr->bssapTimerT17 );

 }
 if(bssaptmr->bssapTimerT18 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_18,bssaptmr->bssapTimerT18 );

 }
 if(bssaptmr->bssapTimerT19 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_19,bssaptmr->bssapTimerT19 );

 }
 if(bssaptmr->bssapTimerT20 >0)
 {
  TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_20, bssaptmr->bssapTimerT20);

 }

   return NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
        isil_get_sccpgenpegs(ITS_EVENT *evt)
{
 ScmNwstkSccpGenPegGet *sccppegsget = (ScmNwstkSccpGenPegGet *)evt->data;
 NwstkScmSccpGenPegResponse  sccppegs;
 NwStkHdr hdr;
 ITS_EVENT ev;
 int ret=0;

  if(sccppegsget==NULL)
  {
    ISIL_ERROR_TRACE(("get_sccpgenpegs:Fail"));
    return NWSTK_WRONG_PARAM;
  }

 ISIL_DEBUG_TRACE(("get_sccpgenpegs:"));
   sccppegs.sccpGenPegsUSERMSGSENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_MSG_SENT);;
   sccppegs.sccpGenPegsREMOTEMSGRECEIVED=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);
   sccppegs.sccpGenPegsROUTINGFAILURE= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_ROUTING_FAILURE);
   sccppegs.sccpGenPegsREMOTEGTTREQUEST=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_GTT_REQUEST);
   sccppegs.sccpGenPegsREMOTEGTTSUCCESS= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_GTT_SUCCESS);
   sccppegs.sccpGenPegsREMOTEGTTFAILURE=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_GTT_FAILURE);
   sccppegs.sccpGenPegsREMOTEMSGDECODEERR= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_MSG_DECODE_ERR);
   sccppegs.sccpGenPegsUSERMSGENCODEERR=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_MSG_ENCODE_ERR);
   sccppegs.sccpGenPegsREMOTEREASSEMBLEERR= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_REASSEMBLE_ERR);
   sccppegs.sccpGenPegsHOPCOUNTERVIOLATIONERR=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_HOP_COUNTER_VIOLATION_ERR)
;
   sccppegs.sccpGenPegsUSERSEGMENTATIONERR= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_SEGMENTATION_ERR);;
   sccppegs.sccpGenPegsTIMERTIAREXPIRY=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_TIMER_TIAR_EXPIRY);;
   sccppegs.sccpGenPegsUSERINITIATEDRLS=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_INITIATED_RLS);;
   sccppegs.sccpGenPegsUSERINITITATEDRESET= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_INITITATED_RESET);
   sccppegs.sccpGenPegsREMOTEUDTRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_UDT_RCVD);;
   sccppegs.sccpGenPegsREMOTEXUDTRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_XUDT_RCVD);;
   sccppegs.sccpGenPegsREMOTEUDTSRCVD=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_UDTS_RCVD);
   sccppegs.sccpGenPegsREMOTEXUDTSRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_XUDTS_RCVD);
   sccppegs.sccpGenPegsREMOTELUDTRCVD=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_LUDT_RCVD);
   sccppegs.sccpGenPegsREMOTELUDTSRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_LUDTS_RCVD);;
   sccppegs.sccpGenPegsUSERUDTSENT= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_UDT_SENT);
   sccppegs.sccpGenPegsUSERXUDTSENT= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_XUDT_SENT);;
   sccppegs.sccpGenPegsUSERUDTSSENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_UDTS_SENT);;
   sccppegs.sccpGenPegsUSERXUDTSSENT= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_XUDTS_SENT);
   sccppegs.sccpGenPegsUSERLUDTSENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_LUDT_SENT);;
   sccppegs.sccpGenPegsUSERLUDTSSENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_LUDTS_SENT);
   sccppegs.sccpGenPegsUSERCRSENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_CR_SENT);
   sccppegs.sccpGenPegsCREFTOREMOTESENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_CREF_TO_REMOTE_SENT);;
   sccppegs.sccpGenPegsRSRTOREMOTESENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_RSR_TO_REMOTE_SENT);
   sccppegs.sccpGenPegsERRTOREMOTESENT= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_ERR_TO_REMOTE_SENT);
   sccppegs.sccpGenPegsREMOTECRRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_CR_RCVD);
   sccppegs.sccpGenPegsREMOTECREFRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_CREF_RCVD);
   sccppegs.sccpGenPegsREMOTERSRRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_RSR_RCVD);
   sccppegs.sccpGenPegsREMOTEERRRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_ERR_RCVD);
   sccppegs.sccpGenPegsREMOTEMSGLOCALSSRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD);
   sccppegs.sccpGenPegsUSERDT1SENT= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_DT1_SENT);;
   sccppegs.sccpGenPegsREMOTEDT1RCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_DT1_RCVD);
   sccppegs.sccpGenPegsUSERDT2SENT= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_DT2_SENT);
   sccppegs.sccpGenPegsREMOTEDT2RCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_DT2_RCVD);;
   sccppegs.sccpGenPegsUSEREDSENT=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_USER_ED_SENT);;
   sccppegs.sccpGenPegsREMOTEEDRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_ED_RCVD);
   sccppegs.sccpGenPegsREMOTESSPRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_SSP_RCVD);
   sccppegs.sccpGenPegsREMOTESSARCVD=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_SSA_RCVD);
   sccppegs.sccpGenPegsREMOTESSCRCVD= PEG_GetPeg(SCCP_Pegs, PEG_SCCP_REMOTE_SSC_RCVD);
   sccppegs.sccpGenPegsLOCALSSPROHIBITED=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_LOCAL_SS_PROHIBITED);
   sccppegs.sccpGenPegsLOCALSSALLOWED=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_LOCAL_SS_ALLOWED);;
   sccppegs.sccpGenPegsLOCALSSCONGESTED=PEG_GetPeg(SCCP_Pegs, PEG_SCCP_LOCAL_SS_CONGESTED);
/*************************************************************************************/
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERMSGSENT %d:",sccppegs.sccpGenPegsUSERMSGSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEMSGRECEIVED %d:",sccppegs.sccpGenPegsREMOTEMSGRECEIVED));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsROUTINGFAILURE %d:",sccppegs.sccpGenPegsROUTINGFAILURE));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEGTTREQUEST %d:",sccppegs.sccpGenPegsREMOTEGTTREQUEST));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEGTTSUCCESS %d:",sccppegs.sccpGenPegsREMOTEGTTSUCCESS));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEGTTFAILURE %d:",sccppegs.sccpGenPegsREMOTEGTTFAILURE));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEMSGDECODEERR %d:",sccppegs.sccpGenPegsREMOTEMSGDECODEERR));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERMSGENCODEERR %d:",sccppegs.sccpGenPegsUSERMSGENCODEERR));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEREASSEMBLEERR %d:",sccppegs.sccpGenPegsREMOTEREASSEMBLEERR));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsHOPCOUNTERVIOLATIONERR %d:",sccppegs.sccpGenPegsHOPCOUNTERVIOLATIONERR));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERSEGMENTATIONERR %d:",sccppegs.sccpGenPegsUSERSEGMENTATIONERR));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsTIMERTIAREXPIRY %d:",sccppegs.sccpGenPegsTIMERTIAREXPIRY));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERINITIATEDRLS %d:",sccppegs.sccpGenPegsUSERINITIATEDRLS));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERINITITATEDRESET %d:",sccppegs.sccpGenPegsUSERINITITATEDRESET));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEUDTRCVD %d:",sccppegs.sccpGenPegsREMOTEUDTRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEXUDTRCVD %d:",sccppegs.sccpGenPegsREMOTEXUDTRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEUDTSRCVD %d:",sccppegs.sccpGenPegsREMOTEUDTSRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEXUDTSRCVD %d:",sccppegs.sccpGenPegsREMOTEXUDTSRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTELUDTRCVD %d:",sccppegs.sccpGenPegsREMOTELUDTRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTELUDTSRCVD %d:",sccppegs.sccpGenPegsREMOTELUDTSRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERUDTSENT %d:",sccppegs.sccpGenPegsUSERUDTSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERXUDTSENT %d:",sccppegs.sccpGenPegsUSERXUDTSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERUDTSSENT %d:",sccppegs.sccpGenPegsUSERUDTSSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERXUDTSSENT %d:",sccppegs.sccpGenPegsUSERXUDTSSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERLUDTSENT %d:",sccppegs.sccpGenPegsUSERLUDTSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERLUDTSSENT %d:",sccppegs.sccpGenPegsUSERLUDTSSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERCRSENT %d:",sccppegs.sccpGenPegsUSERCRSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsCREFTOREMOTESENT %d:",sccppegs.sccpGenPegsCREFTOREMOTESENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsRSRTOREMOTESENT %d:",sccppegs.sccpGenPegsRSRTOREMOTESENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsERRTOREMOTESENT %d:",sccppegs.sccpGenPegsERRTOREMOTESENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTECRRCVD %d:",sccppegs.sccpGenPegsREMOTECRRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTECREFRCVD %d:",sccppegs.sccpGenPegsREMOTECREFRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTERSRRCVD %d:",sccppegs.sccpGenPegsREMOTERSRRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEERRRCVD %d:",sccppegs.sccpGenPegsREMOTEERRRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEMSGLOCALSSRCVD %d:",sccppegs.sccpGenPegsREMOTEMSGLOCALSSRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERDT1SENT %d:",sccppegs.sccpGenPegsUSERDT1SENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEDT1RCVD %d:",sccppegs.sccpGenPegsREMOTEDT1RCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSERDT2SENT %d:",sccppegs.sccpGenPegsUSERDT2SENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEDT2RCVD %d:",sccppegs.sccpGenPegsREMOTEDT2RCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsUSEREDSENT %d:",sccppegs.sccpGenPegsUSEREDSENT));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTEEDRCVD %d:",sccppegs.sccpGenPegsREMOTEEDRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTESSPRCVD %d:",sccppegs.sccpGenPegsREMOTESSPRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTESSARCVD %d:",sccppegs.sccpGenPegsREMOTESSARCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsREMOTESSCRCVD %d:",sccppegs.sccpGenPegsREMOTESSCRCVD));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsLOCALSSPROHIBITED %d:",sccppegs.sccpGenPegsLOCALSSPROHIBITED));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsLOCALSSALLOWED %d:",sccppegs.sccpGenPegsLOCALSSALLOWED));
  ISIL_DEBUG_TRACE(("get_sccpgenpegs sccpGenPegsLOCALSSCONGESTED %d:",sccppegs.sccpGenPegsLOCALSSCONGESTED));
/*************************************************************************************/

  /*clear the overall flag*/
  if(sccppegsget->pegResetFlag==1)
  {
    PEG_ClearBlock(SCCP_Pegs);

  } 

        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmSccpGenPegResponse));
        memset(ev.data,0,sizeof(NwstkScmSccpGenPegResponse));
        hdr.len=sizeof(NwstkScmSccpGenPegResponse);
 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_sccpgenpegs:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&sccppegs,sizeof(NwstkScmSccpGenPegResponse));
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);

       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_sccpgenpegs:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;

 
return NWSTK_CMD_CNG_SUCCESS ;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
 isil_get_mtp3genpegs(ITS_EVENT *evt)
{
 ScmNwstkMtp3RoutePegGet *mtp2pegs = (ScmNwstkMtp3RoutePegGet *)evt->data;
 NwstkScmMtp3GenPegResponse peginfo;
 NwStkHdr hdr;
 ITS_EVENT ev;
 int ret=0;
 int i=0;

 if(mtp2pegs==NULL)
  {
    ISIL_ERROR_TRACE(("get_mtp3genpegs:Fail"));
    return NWSTK_WRONG_PARAM;
  }
 ISIL_DEBUG_TRACE(("get_mtp3genpegs:"));
  peginfo.mtp3GenPegsMSGPAUSE   = 
                           PEG_GetPeg(MTP3_Pegs, PEG_MTP3_MSG_PAUSE);
  peginfo.mtp3GenPegsMSGRESUME  = 
                           PEG_GetPeg(MTP3_Pegs, PEG_MTP3_MSG_RESUME);
  peginfo.mtp3GenPegsMSGSTATUS  =    
                         PEG_GetPeg(MTP3_Pegs, PEG_MTP3_MSG_STATUS); 
  peginfo.mtp3GenPegsMSGRECEIVEDINERROR = 
                        PEG_GetPeg(MTP3_Pegs, PEG_MTP3_MSG_RECEIVED_INERROR);
  peginfo.mtp3GenPegsCHANGEOVER = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_CHANGEOVER);
  peginfo.mtp3GenPegsCHANGEBACK = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_CHANGEBACK);
  peginfo.mtp3GenPegsSLUNAVAILABLE = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE);
  peginfo.mtp3GenPegsLINKINHIBIT = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);
  peginfo.mtp3GenPegsLINKUNINHIBIT = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);
  peginfo.mtp3GenPegsLINKFORCEUNINHIBIT = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);
  peginfo.mtp3GenPegsCONGESTION = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_CONGESTION);
  peginfo.mtp3GenPegsSLSUNAVAILABLE = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_SLS_UNAVAILABLE);
  peginfo.mtp3GenPegsTFCRECEIVED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_TFC_RECEIVED);
  peginfo.mtp3GenPegsTFARECEIVED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_TFA_RECEIVED);
  peginfo.mtp3GenPegsROUTESETUNAVAILABLE = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE); 
  peginfo.mtp3GenPegsADJECENTSPUNACCESIBLE = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE);
  peginfo.mtp3GenPegsUSERPARTENABLE = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_USERPART_ENABLE);
  peginfo.mtp3GenPegsT1EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T1_EXPIRED);
 ISIL_DEBUG_TRACE(("get_mtp3T1=%d:",PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T1_EXPIRED)));

  peginfo.mtp3GenPegsT2EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T2_EXPIRED);
  peginfo.mtp3GenPegsT3EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T3_EXPIRED);
  peginfo.mtp3GenPegsT4EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T4_EXPIRED);
  peginfo.mtp3GenPegsT5EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T5_EXPIRED);
  peginfo.mtp3GenPegsT6EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T6_EXPIRED);
  peginfo.mtp3GenPegsT7EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T7_EXPIRED);
  peginfo.mtp3GenPegsT8EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T8_EXPIRED);
  peginfo.mtp3GenPegsT9EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T9_EXPIRED);
  peginfo.mtp3GenPegsT10EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T10_EXPIRED);
  peginfo.mtp3GenPegsT11EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T11_EXPIRED);
  peginfo.mtp3GenPegsT12EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T12_EXPIRED);
  peginfo.mtp3GenPegsT13EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T13_EXPIRED);
  peginfo.mtp3GenPegsT14EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T14_EXPIRED);
  peginfo.mtp3GenPegsT15EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T15_EXPIRED);
  peginfo.mtp3GenPegsT16EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T16_EXPIRED);
  peginfo.mtp3GenPegsT17EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T17_EXPIRED);
  peginfo.mtp3GenPegsT18EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T18_EXPIRED);
  peginfo.mtp3GenPegsT19EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T19_EXPIRED);
  peginfo.mtp3GenPegsT20EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T20_EXPIRED);
  peginfo.mtp3GenPegsT21EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T21_EXPIRED);
  peginfo.mtp3GenPegsT22EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T22_EXPIRED);
  peginfo.mtp3GenPegsT23EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T23_EXPIRED);
  peginfo.mtp3GenPegsT24EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T24_EXPIRED);
  peginfo.mtp3GenPegsT25EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T25_EXPIRED);
  peginfo.mtp3GenPegsT26EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T26_EXPIRED);
  peginfo.mtp3GenPegsT27EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T27_EXPIRED);
  peginfo.mtp3GenPegsT28EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T28_EXPIRED);
  peginfo.mtp3GenPegsT29EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T29_EXPIRED);
  peginfo.mtp3GenPegsT30EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T30_EXPIRED);
  peginfo.mtp3GenPegsT31EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T31_EXPIRED);
  peginfo.mtp3GenPegsT32EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T32_EXPIRED);
  peginfo.mtp3GenPegsT33EXPIRED = 
               PEG_GetPeg(MTP3_Pegs, PEG_MTP3_T33_EXPIRED);

/*************************************************************************************/
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsMSGPAUSE %d:",peginfo.mtp3GenPegsMSGPAUSE));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsMSGRESUME %d:",peginfo.mtp3GenPegsMSGRESUME));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsMSGSTATUS %d:",peginfo.mtp3GenPegsMSGSTATUS));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsMSGRECEIVEDINERROR %d:",peginfo.mtp3GenPegsMSGRECEIVEDINERROR));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsCHANGEOVER %d:",peginfo.mtp3GenPegsCHANGEOVER));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsCHANGEBACK %d:",peginfo.mtp3GenPegsCHANGEBACK));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsSLUNAVAILABLE %d:",peginfo.mtp3GenPegsSLUNAVAILABLE));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsLINKINHIBIT %d:",peginfo.mtp3GenPegsLINKINHIBIT));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsLINKUNINHIBIT %d:",peginfo.mtp3GenPegsLINKUNINHIBIT));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsLINKFORCEUNINHIBIT %d:",peginfo.mtp3GenPegsLINKFORCEUNINHIBIT));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsCONGESTION %d:",peginfo.mtp3GenPegsCONGESTION));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsSLSUNAVAILABLE %d:",peginfo.mtp3GenPegsSLSUNAVAILABLE));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsTFCRECEIVED %d:",peginfo.mtp3GenPegsTFCRECEIVED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsTFARECEIVED %d:",peginfo.mtp3GenPegsTFARECEIVED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsROUTESETUNAVAILABLE %d:",peginfo.mtp3GenPegsROUTESETUNAVAILABLE));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsADJECENTSPUNACCESIBLE %d:",peginfo.mtp3GenPegsADJECENTSPUNACCESIBLE));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsUSERPARTENABLE %d:",peginfo.mtp3GenPegsUSERPARTENABLE));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT1EXPIRED %d:",peginfo.mtp3GenPegsT1EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT2EXPIRED %d:",peginfo.mtp3GenPegsT2EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT3EXPIRED %d:",peginfo.mtp3GenPegsT3EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT4EXPIRED %d:",peginfo.mtp3GenPegsT4EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT5EXPIRED %d:",peginfo.mtp3GenPegsT5EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT6EXPIRED %d:",peginfo.mtp3GenPegsT6EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT7EXPIRED %d:",peginfo.mtp3GenPegsT7EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT8EXPIRED %d:",peginfo.mtp3GenPegsT8EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT9EXPIRED %d:",peginfo.mtp3GenPegsT9EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT10EXPIRED %d:",peginfo.mtp3GenPegsT10EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT11EXPIRED %d:",peginfo.mtp3GenPegsT11EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT12EXPIRED %d:",peginfo.mtp3GenPegsT12EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT13EXPIRED %d:",peginfo.mtp3GenPegsT13EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT14EXPIRED %d:",peginfo.mtp3GenPegsT14EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT15EXPIRED %d:",peginfo.mtp3GenPegsT15EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT16EXPIRED %d:",peginfo.mtp3GenPegsT16EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT17EXPIRED %d:",peginfo.mtp3GenPegsT17EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT18EXPIRED %d:",peginfo.mtp3GenPegsT18EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT19EXPIRED %d:",peginfo.mtp3GenPegsT19EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT20EXPIRED %d:",peginfo.mtp3GenPegsT20EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT21EXPIRED %d:",peginfo.mtp3GenPegsT21EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT22EXPIRED %d:",peginfo.mtp3GenPegsT22EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT23EXPIRED %d:",peginfo.mtp3GenPegsT23EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT24EXPIRED %d:",peginfo.mtp3GenPegsT24EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT25EXPIRED %d:",peginfo.mtp3GenPegsT25EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT26EXPIRED %d:",peginfo.mtp3GenPegsT26EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT27EXPIRED %d:",peginfo.mtp3GenPegsT27EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT28EXPIRED %d:",peginfo.mtp3GenPegsT28EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT29EXPIRED %d:",peginfo.mtp3GenPegsT29EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT30EXPIRED %d:",peginfo.mtp3GenPegsT30EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT31EXPIRED %d:",peginfo.mtp3GenPegsT31EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT32EXPIRED %d:",peginfo.mtp3GenPegsT32EXPIRED));
  ISIL_DEBUG_TRACE(("get_mtp3genpegs mtp3GenPegsT33EXPIRED %d:",peginfo.mtp3GenPegsT33EXPIRED));
/*************************************************************************************/
  if(mtp2pegs->pegResetFlag==1)
  {
     for (i = 0; i < PEG_MTP3_NUM_PEGS; i++)
            {
                PEG_ClearPeg(MTP3_Pegs, i);
            }
  }


        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmMtp3GenPegResponse));
        memset(ev.data,0,sizeof(NwstkScmMtp3GenPegResponse)); 
        hdr.len=sizeof(NwstkScmMtp3GenPegResponse); 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_mtp3genpegs:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&peginfo,sizeof(NwstkScmMtp3GenPegResponse)); 
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

        ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_mtp3genpegs:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;
}

/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
        isil_get_rtpegs(ITS_EVENT *evt)
{
  ScmNwstkMtp3RoutePegGet *Route = (ScmNwstkMtp3RoutePegGet *)evt->data;
  NwstkScmMtp3RoutePegResponse routepegs;
 NwStkHdr hdr;
  int i=0;
  SS7_Destination* dest=NULL;
  ITS_EVENT ev;

  int ret=0;
  I_U8 Opcode=0;
  I_U8 cnt=1;
  I_U8 trid=0;

  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];
  if(Route==NULL)
   {
     ISIL_ERROR_TRACE(("get_rtpegs:Fail"));
     return NWSTK_WRONG_PARAM;
   }
  ISIL_DEBUG_TRACE(("get_rtpegs:"));
  ISIL_DEBUG_TRACE(("get_rtpegs:RPC:%d,NI:%d",Route->dpc,Route->ni));

   if ((dest = ROUTE_FindDestination(Route->dpc, Route->ni, FAMILY)) == NULL)
   {
           Opcode=NWSTK_SCM_ROUTE_PEG_NACK_RESP;
           ret=NWSTK_INVALID_ROUTE;
           ret= NWSTK_SendRESP((I_S16)ret,Opcode,trid);
           if(ret!=ITS_SUCCESS)
           {  
             ISIL_ERROR_TRACE(("get_rtpegs:Send RESP To SCM Fail:"));
           }
          ISIL_ERROR_TRACE(("get_rtpegs:Invaild Dest"));
          return NWSTK_INVALID_ROUTE;
   }

  routepegs.dpc=Route->dpc;
  routepegs.ni=Route->ni;
  routepegs.mtp3RoutePegsDPCTFATX= PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_TX);
  routepegs.mtp3RoutePegsDPCTFARX= PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_RX);
  routepegs.mtp3RoutePegsDPCTFPTX= PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX);
  routepegs.mtp3RoutePegsDPCTFPRX=  PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_RX);
  routepegs.mtp3RoutePegsDPCRSTTX=  PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_TX);
  routepegs.mtp3RoutePegsDPCRSTRX=  PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_RX);
  routepegs.mtp3RoutePegsDPCTFRRX=  PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFR_RX);
  routepegs.mtp3RoutePegsDPCTFCTX=  PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_TX);
  routepegs.mtp3RoutePegsDPCTFCRX=  PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_RX);
  routepegs.mtp3RoutePegsDPCSIFTX=  PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_SIF_TX);
/*****************************************************************************************/
  ISIL_DEBUG_TRACE(("get_rtpegs dpc %d:",routepegs.dpc));
  ISIL_DEBUG_TRACE(("get_rtpegs ni %d:",routepegs.ni));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCTFATX %d:",routepegs.mtp3RoutePegsDPCTFATX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCTFARX %d:",routepegs.mtp3RoutePegsDPCTFARX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCTFPTX %d:",routepegs.mtp3RoutePegsDPCTFPTX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCTFPRX %d:",routepegs.mtp3RoutePegsDPCTFPRX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCRSTTX %d:",routepegs.mtp3RoutePegsDPCRSTTX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCRSTRX %d:",routepegs.mtp3RoutePegsDPCRSTRX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCTFRRX %d:",routepegs.mtp3RoutePegsDPCTFRRX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCTFCTX %d:",routepegs.mtp3RoutePegsDPCTFCTX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCTFCRX %d:",routepegs.mtp3RoutePegsDPCTFCRX));
  ISIL_DEBUG_TRACE(("get_rtpegs mtp3RoutePegsDPCSIFTX %d:",routepegs.mtp3RoutePegsDPCSIFTX));

/*****************************************************************************************/

  if(Route->pegResetFlag==1)
  {
     for (i = 0; i <= PEG_MTP3_NUM_DPC_PEGS; i++)
            {
                PEG_ClearPeg(&dest->MTP3_DPC_PEGS, i);
            }


  }



        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmMtp3RoutePegResponse));
        memset(ev.data,0,sizeof(NwstkScmMtp3RoutePegResponse)); 
        hdr.len=sizeof(NwstkScmMtp3RoutePegResponse); 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_rtpegs:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&routepegs,sizeof(NwstkScmMtp3RoutePegResponse));
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_rtpegs:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
        isil_get_lnpegs(ITS_EVENT *evt)
{
 ScmNwstkMtp3LinkPegGet *link=(ScmNwstkMtp3LinkPegGet *)evt->data;
 NwstkScmMtp3LinkPegResponse lnpegs;
 NwStkHdr hdr;
 SS7_LinkPtr ln=NULL; 
 ITS_EVENT ev;
 int ret=0;
 int i=0;
 I_U8 Opcode=0;
 I_U8 cnt=1;
 I_U8 trid=0;

  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];
  if(link==NULL)
  { 
     ISIL_ERROR_TRACE(("get_lnpegs:Fail"));
     return NWSTK_WRONG_PARAM;
  }
  ISIL_DEBUG_TRACE(("get_lnpegs:"));
  ISIL_DEBUG_TRACE(("get_lnpegs:LinkSet:%d,Link:%d",link->linkSetId,link->linkId));


  if ((ln = LINK_FindLink((ITS_OCTET)link->linkSetId,
                    (ITS_OCTET)link->linkId)) == NULL)
        {
           Opcode=NWSTK_SCM_LINK_PEG_NACK_RESP;
           ret=NWSTK_LNK_NOTFOUND;
           ret= NWSTK_SendRESP(ret,Opcode,trid);
           if(ret!=ITS_SUCCESS)
           {  
             ISIL_ERROR_TRACE(("get_lnpegs:Send RESP To SCM Fail:"));
           }
            return NWSTK_LNK_NOTFOUND;
        }

  lnpegs.mtp3LinkPegslinksetID=link->linkSetId;
  lnpegs.mtp3LinkPegslinkCode=link->linkId;
  lnpegs.mtp3LinkPegsLINKCOOTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX);
  lnpegs.mtp3LinkPegsLINKCOORX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);
  lnpegs.mtp3LinkPegsLINKCOATX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);
  lnpegs.mtp3LinkPegsLINKCOARX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);
  lnpegs.mtp3LinkPegsLINKECOTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX);
  lnpegs.mtp3LinkPegsLINKECORX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX);
  lnpegs.mtp3LinkPegsLINKECATX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);
  lnpegs.mtp3LinkPegsLINKECARX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX);
  lnpegs.mtp3LinkPegsLINKCBDTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);
  lnpegs.mtp3LinkPegsLINKCBDRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX);
  lnpegs.mtp3LinkPegsLINKCBATX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX);
  lnpegs.mtp3LinkPegsLINKCBARX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX);
  lnpegs.mtp3LinkPegsLINKLINTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);
  lnpegs.mtp3LinkPegsLINKLINRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);
  lnpegs.mtp3LinkPegsLINKLIATX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);
  lnpegs.mtp3LinkPegsLINKLIARX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX);
  lnpegs.mtp3LinkPegsLINKLUNTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);
  lnpegs.mtp3LinkPegsLINKLUNRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);
  lnpegs.mtp3LinkPegsLINKLUATX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);
  lnpegs.mtp3LinkPegsLINKLUARX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX);
  lnpegs.mtp3LinkPegsLINKLIDTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);
  lnpegs.mtp3LinkPegsLINKLIDRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX);
  lnpegs.mtp3LinkPegsLINKLFUTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);
  lnpegs.mtp3LinkPegsLINKLFURX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_RX);
  lnpegs.mtp3LinkPegsLINKLLITX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX);
  lnpegs.mtp3LinkPegsLINKLLIRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_RX);
  lnpegs.mtp3LinkPegsLINKLRITX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX);
  lnpegs.mtp3LinkPegsLINKLR_RX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_RX);
  lnpegs.mtp3LinkPegsLINKDLCTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);
  lnpegs.mtp3LinkPegsLINKDLCRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_DLC_RX );
  lnpegs.mtp3LinkPegsLINKCSSTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);
  lnpegs.mtp3LinkPegsLINKCSSRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_RX);
  lnpegs.mtp3LinkPegsLINKCNSTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);
  lnpegs.mtp3LinkPegsLINKCNSRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_RX);
  lnpegs.mtp3LinkPegsLINKCNPTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);
  lnpegs.mtp3LinkPegsLINKCNPRX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_RX);
  lnpegs.mtp3LinkPegsLINKUPUTX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX);
  lnpegs.mtp3LinkPegsLINKUPURX=  PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_RX);
  lnpegs.mtp3LinkPegsLINKSLTMTX= PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);
  lnpegs.mtp3LinkPegsLINKSLTMRX= PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_RX);
  lnpegs.mtp3LinkPegsLINKSLTATX= PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_TX);
  lnpegs.mtp3LinkPegsLINKSLTARX= PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_RX);
/*#####################Trace ###############################*/
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegslinksetID %d:",lnpegs.mtp3LinkPegslinksetID));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegslinkCode %d:",lnpegs.mtp3LinkPegslinkCode));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCOOTX %d:",lnpegs.mtp3LinkPegsLINKCOOTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCOORX %d:",lnpegs.mtp3LinkPegsLINKCOORX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCOATX %d:",lnpegs.mtp3LinkPegsLINKCOATX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCOARX %d:",lnpegs.mtp3LinkPegsLINKCOARX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKECOTX %d:",lnpegs.mtp3LinkPegsLINKECOTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKECORX %d:",lnpegs.mtp3LinkPegsLINKECORX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKECATX %d:",lnpegs.mtp3LinkPegsLINKECATX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKECARX %d:",lnpegs.mtp3LinkPegsLINKECARX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCBDTX %d:",lnpegs.mtp3LinkPegsLINKCBDTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCBDRX %d:",lnpegs.mtp3LinkPegsLINKCBDRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCBATX %d:",lnpegs.mtp3LinkPegsLINKCBATX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCBARX %d:",lnpegs.mtp3LinkPegsLINKCBARX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLINTX %d:",lnpegs.mtp3LinkPegsLINKLINTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLINRX %d:",lnpegs.mtp3LinkPegsLINKLINRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLIATX %d:",lnpegs.mtp3LinkPegsLINKLIATX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLIARX %d:",lnpegs.mtp3LinkPegsLINKLIARX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLUNTX %d:",lnpegs.mtp3LinkPegsLINKLUNTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLUNRX %d:",lnpegs.mtp3LinkPegsLINKLUNRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLUATX %d:",lnpegs.mtp3LinkPegsLINKLUATX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLUARX %d:",lnpegs.mtp3LinkPegsLINKLUARX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLIDTX %d:",lnpegs.mtp3LinkPegsLINKLIDTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLIDRX %d:",lnpegs.mtp3LinkPegsLINKLIDRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLFUTX %d:",lnpegs.mtp3LinkPegsLINKLFUTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLFURX %d:",lnpegs.mtp3LinkPegsLINKLFURX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLLITX %d:",lnpegs.mtp3LinkPegsLINKLLITX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLLIRX %d:",lnpegs.mtp3LinkPegsLINKLLIRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLRITX %d:",lnpegs.mtp3LinkPegsLINKLRITX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKLR_RX %d:",lnpegs.mtp3LinkPegsLINKLR_RX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKDLCTX %d:",lnpegs.mtp3LinkPegsLINKDLCTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKDLCRX %d:",lnpegs.mtp3LinkPegsLINKDLCRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCSSTX %d:",lnpegs.mtp3LinkPegsLINKCSSTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCSSRX %d:",lnpegs.mtp3LinkPegsLINKCSSRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCNSTX %d:",lnpegs.mtp3LinkPegsLINKCNSTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCNSRX %d:",lnpegs.mtp3LinkPegsLINKCNSRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCNPTX %d:",lnpegs.mtp3LinkPegsLINKCNPTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKCNPRX %d:",lnpegs.mtp3LinkPegsLINKCNPRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKUPUTX %d:",lnpegs.mtp3LinkPegsLINKUPUTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKUPURX %d:",lnpegs.mtp3LinkPegsLINKUPURX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKSLTMTX %d:",lnpegs.mtp3LinkPegsLINKSLTMTX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKSLTMRX %d:",lnpegs.mtp3LinkPegsLINKSLTMRX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKSLTATX %d:",lnpegs.mtp3LinkPegsLINKSLTATX));
  ISIL_DEBUG_TRACE(("get_lnpegs mtp3LinkPegsLINKSLTARX %d:",lnpegs.mtp3LinkPegsLINKSLTARX));

/*#####################Trace ###############################*/

   if(link->pegResetFlag==1)
   {
     for (i = 0; i < PEG_MTP3_NUM_LINK_PEGS; i++)
            {
                PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
            }

   }

        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmMtp3LinkPegResponse));
        memset(ev.data,0,sizeof(NwstkScmMtp3LinkPegResponse)); 
        hdr.len=sizeof(NwstkScmMtp3LinkPegResponse); 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_lnpegs:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&lnpegs,sizeof(NwstkScmMtp3LinkPegResponse)); 
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_lnpegs:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
        isil_get_bssapgenpegs(ITS_EVENT *evt)
{
 ScmNwstkBssapGenPegGet *bssappegget =(ScmNwstkBssapGenPegGet *)evt->data;
 NwstkScmBssapGenPegResponse bssapgenpegs;
 NwStkHdr hdr;
 ITS_EVENT ev;
 int ret=0;
 ITS_OCTET bscid=0;
 BSSAP_CfgDB cfgdb;
 CFGData* cfg = NULL;

 I_U8 Opcode=0;
 I_U8 cnt=1;
 I_U8 trid=0;

   Opcode=evt->data[cnt++];
   trid=evt->data[cnt++];
   if(bssappegget==NULL)
   {
     ISIL_ERROR_TRACE(("get_bssapgenpegs:Fail"));
     return NWSTK_WRONG_PARAM;
   }
   ISIL_DEBUG_TRACE(("get_bssapgenpegs:"));
   ISIL_DEBUG_TRACE(("get_bssapgenpegs:PC :%d",bssappegget->bscPointCode));

    if (bssappegget->bscPointCode)
    {
        cfg = cfgdb.FetchNWIDEntry(bssappegget->bscPointCode);
        if (cfg)
        {
            bscid = cfg->Id;
            ISIL_DEBUG_TRACE(("get_bssapgenpegs:BSCID :%d",bscid));
        }
        else
        {
           Opcode=NWSTK_SCM_BSSAP_GENPEG_NACK_RESP;
           ret=NWSTK_WRONG_PARAM;
           ret= NWSTK_SendRESP(ret,Opcode,trid);
           if(ret!=ITS_SUCCESS)
           {
             ISIL_ERROR_TRACE(("get_bssapgenpegs:Send RESP To SCM Fail:"));
           }

            return (ITS_ENOTFOUND);
        }
    }


  bssapgenpegs.bscPointCode=bssappegget->bscPointCode;

  bssapgenpegs.bssapGenPegsCRRECV   = BSSAPPEG_GetPeg(PEG_BSSAP_CR_RECV,bscid);

  bssapgenpegs.bssapGenPegsDT1RECV  =  BSSAPPEG_GetPeg(PEG_BSSAP_DT1_RECV,bscid);
  bssapgenpegs.bssapGenPegsCRSEND   =  BSSAPPEG_GetPeg(PEG_BSSAP_CR_SEND,bscid);
  bssapgenpegs.bssapGenPegsDT1SEND  =  BSSAPPEG_GetPeg(PEG_BSSAP_DT1_SEND,bscid);
  bssapgenpegs.bssapGenPegsDTAPSEND =  BSSAPPEG_GetPeg(PEG_BSSAP_DTAP_SEND,bscid);
  bssapgenpegs.bssapGenPegsDTAPRECV =  BSSAPPEG_GetPeg(PEG_BSSAP_DTAP_RECV,bscid);
  bssapgenpegs.bssapGenPegsmapSEND  =  BSSAPPEG_GetPeg(PEG_BSSAP_MAP_SEND,bscid);
  bssapgenpegs.bssapGenPegsmapRECV  =  BSSAPPEG_GetPeg(PEG_BSSAP_MAP_RECV,bscid);
  bssapgenpegs.bssapGenPegsCONFSEND =  BSSAPPEG_GetPeg(PEG_BSSAP_CONF_SEND,bscid);
  bssapgenpegs.bssapGenPegsCONFRECV =  BSSAPPEG_GetPeg(PEG_BSSAP_CONF_RECV,bscid);
  bssapgenpegs.bssapGenPegsCMSERVSEND =BSSAPPEG_GetPeg(PEG_BSSAP_CMSERV_SEND,bscid);
  bssapgenpegs.bssapGenPegsPAGRSPSEND =BSSAPPEG_GetPeg(PEG_BSSAP_PAGRSP_SEND,bscid);

/***********************************************************************************/
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsCRRECV %d:",bssapgenpegs.bssapGenPegsCRRECV));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsDT1RECV %d:",bssapgenpegs.bssapGenPegsDT1RECV));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsCRSEND %d:",bssapgenpegs.bssapGenPegsCRSEND));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsDT1SEND %d:",bssapgenpegs.bssapGenPegsDT1SEND));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsDTAPSEND %d:",bssapgenpegs.bssapGenPegsDTAPSEND));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsDTAPRECV %d:",bssapgenpegs.bssapGenPegsDTAPRECV));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsmapSEND %d:",bssapgenpegs.bssapGenPegsmapSEND));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsmapRECV %d:",bssapgenpegs.bssapGenPegsmapRECV));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsCONFSEND %d:",bssapgenpegs.bssapGenPegsCONFSEND));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsCONFRECV %d:",bssapgenpegs.bssapGenPegsCONFRECV));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsCMSERVSEND %d:",bssapgenpegs.bssapGenPegsCMSERVSEND));
  ISIL_DEBUG_TRACE(("get_bssapgenpegs bssapGenPegsPAGRSPSEND %d:",bssapgenpegs.bssapGenPegsPAGRSPSEND));
/***********************************************************************************/


  if(bssappegget->pegResetFlag==1)
  {
   BSSAPPEG_ClearBlockPeg(bscid);

  }

        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmBssapGenPegResponse));
        memset(ev.data,0,sizeof(NwstkScmBssapGenPegResponse));
 
        hdr.len=sizeof(NwstkScmBssapGenPegResponse); 
        ret=BuildHeader(*evt,&hdr); 

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_bssapgenpegs:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&bssapgenpegs,sizeof(NwstkScmBssapGenPegResponse)); 
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_bssapgenpegs:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
        isil_mtp3_gencfg(ITS_EVENT *evt)
{
 sksGenSetConfig *mtp3gencfg = (sksGenSetConfig *)evt->data;
 MTP3GeneralCfg cfg;
 NwStkHdr hdr;
int ret=0;

 I_U8 Opcode=0;
 I_U8 cnt=1;
 I_U8 trid=0;

  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];
  if(mtp3gencfg==NULL)
  {
     ISIL_ERROR_TRACE(("mtp3_gencfg:Fail"));
     return NWSTK_WRONG_PARAM;
  }

 ISIL_DEBUG_TRACE(("mtp3_gencfg:"));

 ISIL_DEBUG_TRACE(("mtp3_gencfg:AlarmLevel :%d,Tracelevel:%d,Traceoutput:%d",mtp3gencfg->sksGenCfgAlarmLevel,mtp3gencfg->sksGenCfgTraceLevel,mtp3gencfg->sksGenCfgtraceOutput));

 if(mtp3gencfg->sksGenCfgAlarmLevel==0)
 {
   cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_CRIT;
 }
 else if(mtp3gencfg->sksGenCfgAlarmLevel==1)
 {
    cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_MAJOR;
 }
 else if(mtp3gencfg->sksGenCfgAlarmLevel==2)
 {
   cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_MINOR;
 }
 else if(mtp3gencfg->sksGenCfgAlarmLevel==3)
 {
    cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_INFO;
 }
 else
 {
        ISIL_ERROR_TRACE(("mtp3_gencfg:Invalid Alarm level"));
         return (ITS_ENOTFOUND);


 }


 if (mtp3gencfg->sksGenCfgTraceLevel==0)
 {
    strcpy(cfg.traceType, MTP3_CRITICAL_STRING);
 } 
 else if (mtp3gencfg->sksGenCfgTraceLevel==1)
 {
    strcpy(cfg.traceType, MTP3_DEBUG_STRING);
 }
 else if (mtp3gencfg->sksGenCfgTraceLevel==2)
 {
    strcpy(cfg.traceType, MTP3_WARNING_STRING);
 }
 else if (mtp3gencfg->sksGenCfgTraceLevel==3)
 {
    strcpy(cfg.traceType, MTP3_ERROR_STRING);
 }
 else if (mtp3gencfg->sksGenCfgTraceLevel==4)
 {
  strcpy(cfg.traceType, MTP3_EVENT_STRING);
 }
 else if (mtp3gencfg->sksGenCfgTraceLevel==5)
 {
    strcpy(cfg.traceType, "all");
 }
 else
 {
      ISIL_ERROR_TRACE(("mtp3_gencfg:Invalid traceType"));
        return (ITS_ENOTFOUND);
 }


 if(mtp3gencfg->sksGenCfgtraceOutput==0)
 {
   strcpy(cfg.traceOutput, MTP3_STDOUT_STRING);
 }
 else if(mtp3gencfg->sksGenCfgtraceOutput==1)
 {
    strcpy(cfg.traceOutput, MTP3_FILE_STRING);
 }
 else if(mtp3gencfg->sksGenCfgtraceOutput==2)
 {
    strcpy(cfg.traceOutput, MTP3_SYSLOG_STRING);
 }
 else
 {
      ISIL_ERROR_TRACE(("mtp3_gencfg:Invalid traceoutput"));
       return (ITS_ENOTFOUND);
 }

 
 if(mtp3gencfg->sksGenCfgtraceOnOff==0)
 {
    cfg.traceOn = ITS_FALSE;
 }
 else if(mtp3gencfg->sksGenCfgtraceOnOff==1)
 {
     cfg.traceOn = ITS_TRUE;
 }
else
 {
          ISIL_ERROR_TRACE(("mtp3_gencfg:Invalid Tracelevel"));
          return (ITS_ENOTFOUND);
 }
      ret =  MTP3_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return  ret;
        }

            return  NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
        isil_sccp_gencfg(ITS_EVENT *evt)
{
sksGenSetConfig *sccpgencfg = (sksGenSetConfig *)evt->data;
  SCCPGeneralCfg cfg;
int ret=0;

 I_U8 Opcode=0;
 I_U8 cnt=1;
 I_U8 trid=0;
  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];
  if(sccpgencfg==NULL)
  { 
     ISIL_ERROR_TRACE(("sccp_gencfg:"));
     return NWSTK_WRONG_PARAM;
  }

 ISIL_DEBUG_TRACE(("sccp_gencfg:"));

 ISIL_DEBUG_TRACE(("sccp:AlarmLevel :%d,Tracelevel:%d,Traceoutput:%d",sccpgencfg->sksGenCfgAlarmLevel,sccpgencfg->sksGenCfgTraceLevel,sccpgencfg->sksGenCfgtraceOutput));

 if(sccpgencfg->sksGenCfgAlarmLevel==0)
 {
   cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_CRIT;
 }
 else if(sccpgencfg->sksGenCfgAlarmLevel==1)
 {
    cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_MAJOR;
 }
 else if(sccpgencfg->sksGenCfgAlarmLevel==2)
 {
   cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_MINOR;
 }
 else if(sccpgencfg->sksGenCfgAlarmLevel==3)
 {
    cfg.alarmLevel = (MGMT_AlarmLevel)ALARM_LVL_INFO;
 }
 else
 {
      ISIL_ERROR_TRACE(("sccp_gencfg:Invalid Alarm level"));
       return (ITS_ENOTFOUND);


 }


 if (sccpgencfg->sksGenCfgTraceLevel==0)
 {
    strcpy(cfg.traceType, MTP3_CRITICAL_STRING);
 } 
 else if (sccpgencfg->sksGenCfgTraceLevel==1)
 {
    strcpy(cfg.traceType, MTP3_DEBUG_STRING);
 }
 else if (sccpgencfg->sksGenCfgTraceLevel==2)
 {
    strcpy(cfg.traceType, MTP3_WARNING_STRING);
 }
 else if (sccpgencfg->sksGenCfgTraceLevel==3)
 {
    strcpy(cfg.traceType, MTP3_ERROR_STRING);
 }
 else if (sccpgencfg->sksGenCfgTraceLevel==4)
 {
  strcpy(cfg.traceType, MTP3_EVENT_STRING);
 }
 else if (sccpgencfg->sksGenCfgTraceLevel==5)
 {
    strcpy(cfg.traceType, "all");
 }
 else
 {
      ISIL_ERROR_TRACE(("sccp_gencfg:Invalid traceType"));
       return (ITS_ENOTFOUND);
 }


 if(sccpgencfg->sksGenCfgtraceOutput==0)
 {
   strcpy(cfg.traceOutput, MTP3_STDOUT_STRING);
 }
 else if(sccpgencfg->sksGenCfgtraceOutput==1)
 {
    strcpy(cfg.traceOutput, MTP3_FILE_STRING);
 }
 else if(sccpgencfg->sksGenCfgtraceOutput==2)
 {
    strcpy(cfg.traceOutput, MTP3_SYSLOG_STRING);
 }
 else
 {
        ISIL_ERROR_TRACE(("sccp_gencfg:Invalid traceoutput"));
          return (ITS_ENOTFOUND);
 }

 
 if(sccpgencfg->sksGenCfgtraceOnOff==0)
 {
    cfg.traceOn = ITS_FALSE;
 }
 else if(sccpgencfg->sksGenCfgtraceOnOff==1)
 {
     cfg.traceOn = ITS_TRUE;
 }
else
 {
       ISIL_ERROR_TRACE(("sccp:Invalid Tracelevel"));
       return (ITS_ENOTFOUND);
 }

        ret =  SCCP_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }


            return  NWSTK_CMD_CNG_SUCCESS;


 
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int 
        isil_bssap_gencfg(ITS_EVENT *evt)
{
 sksGenSetConfig *bssapgencfg = (sksGenSetConfig *)evt->data;
 BSSAPGeneralCfg cfg;
 int ret=0;

 I_U8 Opcode=0;
 I_U8 cnt=1;
 I_U8 trid=0;
  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];
  if(bssapgencfg==NULL)
  {
     ISIL_ERROR_TRACE(("bssap_gencfg:Fail"));
     return NWSTK_WRONG_PARAM;
  }

 ISIL_DEBUG_TRACE(("bssap_gencfg:"));

 ISIL_DEBUG_TRACE(("bssap:AlarmLevel :%d,Tracelevel:%d,Traceoutput:%d",bssapgencfg ->sksGenCfgAlarmLevel,bssapgencfg ->sksGenCfgTraceLevel,bssapgencfg ->sksGenCfgtraceOutput));

 if(bssapgencfg->sksGenCfgAlarmLevel==0)
 {
   cfg.alarmLevel = ALARM_LVL_CRIT;
 }
 else if(bssapgencfg->sksGenCfgAlarmLevel==1)
 {
    cfg.alarmLevel = ALARM_LVL_MAJOR;
 }
 else if(bssapgencfg->sksGenCfgAlarmLevel==2)
 {
   cfg.alarmLevel = ALARM_LVL_MINOR;
 }
 else if(bssapgencfg->sksGenCfgAlarmLevel==3)
 {
    cfg.alarmLevel = ALARM_LVL_INFO;
 }
 else
 {
        ISIL_ERROR_TRACE(("bssap_gencfg:Invalid Alarm level"));
           return (ITS_ENOTFOUND);
 }

 if (bssapgencfg->sksGenCfgTraceLevel==0)
 {
    strcpy(cfg.traceType, MTP3_CRITICAL_STRING);
 } 
 else if (bssapgencfg->sksGenCfgTraceLevel==1)
 {
    strcpy(cfg.traceType, MTP3_DEBUG_STRING);
 }
 else if (bssapgencfg->sksGenCfgTraceLevel==2)
 {
    strcpy(cfg.traceType, MTP3_WARNING_STRING);
 }
 else if (bssapgencfg->sksGenCfgTraceLevel==3)
 {
    strcpy(cfg.traceType, MTP3_ERROR_STRING);
 }
 else if (bssapgencfg->sksGenCfgTraceLevel==4)
 {
  strcpy(cfg.traceType, MTP3_EVENT_STRING);
 }
 else if (bssapgencfg->sksGenCfgTraceLevel==5)
 {
    strcpy(cfg.traceType, "all");
 }
 else
 {
        ISIL_ERROR_TRACE(("bssap_gencfg:Invalid traceType"));
          return (ITS_ENOTFOUND);
 }


 if(bssapgencfg->sksGenCfgtraceOutput==0)
 {
   strcpy(cfg.traceOutput, MTP3_STDOUT_STRING);
 }
 else if(bssapgencfg->sksGenCfgtraceOutput==1)
 {
    strcpy(cfg.traceOutput, MTP3_FILE_STRING);
 }
 else if(bssapgencfg->sksGenCfgtraceOutput==2)
 {
    strcpy(cfg.traceOutput, MTP3_SYSLOG_STRING);
 }
 else
 {
         ISIL_ERROR_TRACE(("bssap_gencfg:Invalid traceoutput"));
          return (ITS_ENOTFOUND);
 }

 
 if(bssapgencfg->sksGenCfgtraceOnOff==0)
 {
    cfg.traceOn = ITS_FALSE;
 }
 else if(bssapgencfg->sksGenCfgtraceOnOff==1)
 {
     cfg.traceOn = ITS_TRUE;
 }
else
 {
        ISIL_ERROR_TRACE(("bssap_gencfg:Invalid Tracelevel"));
            return (ITS_ENOTFOUND);
 }
    ret =  BSSAP_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

            return  NWSTK_CMD_CNG_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int
isil_get_linkStatus(ITS_EVENT *evt)
{
 ScmNwstkLinkStatus *getstatus = (ScmNwstkLinkStatus *)evt->data;

 ScmNwstkLinkStatus linkresp;
 NwStkHdr hdr;
 SS7_LinkPtr ln=NULL;
 ITS_EVENT ev;
 int ret=0;

   I_U8 Opcode=0;
   I_U8 cnt=1;
   I_U8 trid=0;
  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];

   
   if(getstatus==NULL)
   {
     ISIL_ERROR_TRACE(("get_linkStatus:Fail"));
     return NWSTK_WRONG_PARAM;
   }
 ISIL_DEBUG_TRACE(("get_linkStatus:"));

 ISIL_DEBUG_TRACE(("get_linkStatus:LinkSet:%d,LinkId:%d",getstatus->linkSetId,getstatus->linkId));

 if ((ln = LINK_FindLink((ITS_OCTET)getstatus->linkSetId, (ITS_OCTET)getstatus->linkId)) == NULL)
     {
      ISIL_ERROR_TRACE(("get_linkStatus:linkset :%d linkCode %d does not exist",getstatus->linkSetId,getstatus->linkId));

           Opcode=NWSTK_SCM_LINK_STATUS_NACK_RESP;
           ret=NWSTK_LNK_NOTFOUND;
           ret= NWSTK_SendRESP((I_S16 )ret,Opcode,trid);
           if(ret!=ITS_SUCCESS)
           {  
             ISIL_ERROR_TRACE(("get_linkStatus:Send RESP To SCM Fail:"));
           }


     return NWSTK_LNK_NOTFOUND;

      }

    linkresp.linkId=getstatus->linkId;
    linkresp.linkSetId=getstatus->linkSetId;

   if(ln->isUp==ITS_TRUE)
   {
     linkresp.status=1;
   }
   else
   {
     linkresp.status=0;
   }

        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(ScmNwstkLinkStatus));
        memset(ev.data,0,sizeof(ScmNwstkLinkStatus)); 
        hdr.len=sizeof(ScmNwstkLinkStatus); 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_linkStatus:getPegs:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&linkresp,sizeof(ScmNwstkLinkStatus)); 
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_linkStatus:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
        //  return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;

}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int
isil_get_linkSetStatus(ITS_EVENT *evt)
{
 ScmNwstkLinkSetStatus *getstatus = (ScmNwstkLinkSetStatus *)evt->data;
 ScmNwstkLinkSetStatus linkSetresp;
 NwStkHdr hdr;
 ITS_BOOLEAN isUp=ITS_FALSE;
 SS7_LinkSetPtr ls=NULL;
 ITS_EVENT ev;
 int i=0,ret=0;

   I_U8 Opcode=0;
   I_U8 cnt=1;
   I_U8 trid=0;
  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];

   if(getstatus==NULL)
   {
     ISIL_ERROR_TRACE(("get_linkSetStatus:Fail"));
     return NWSTK_WRONG_PARAM;
   }
 ISIL_DEBUG_TRACE(("get_linkSetStatus:"));
 ISIL_DEBUG_TRACE(("get_linkSetStatus:LinkSet:%d",getstatus->linkSetId));
  ls=LINKSET_FindLinkSet(getstatus->linkSetId);
  if(ls==NULL)
     {
          ISIL_ERROR_TRACE(("get_linkSetStatus:linkset :%d does not exist",getstatus->linkSetId));

           Opcode=NWSTK_SCM_LINKSET_STATUS_NACK_RESP;
           ret=NWSTK_LNK_NOTFOUND;
           ret= NWSTK_SendRESP((I_S16)ret,Opcode,trid);
           if(ret!=ITS_SUCCESS)
           {  
             ISIL_ERROR_TRACE(("get_linkSetStatus:Send RESP To SCM Fail:"));
           }


         return NWSTK_LNK_NOTFOUND;
      }
     else
      {
          ISIL_ERROR_TRACE(("get_linkSetStatus:linkset :%d  exist",getstatus->linkSetId));

      } 
  
 linkSetresp.linkSetId=getstatus->linkSetId;
 if(ls->isUp==ITS_FALSE)
  {
   ISIL_DEBUG_TRACE(("get_linkSetStatus:LinkSet:%d DOWN",getstatus->linkSetId));
   linkSetresp.status=0;
  }
 else
  {
    for(i=0;i<ls->numLinks;i++)
    {
      if(ls->links[i]->isUp==ITS_TRUE)
       {
         isUp=ITS_TRUE;  
    
       }
   
    }
    if(isUp==ITS_TRUE)
    {
     ISIL_DEBUG_TRACE(("get_linkSetStatus:LinkSet:%d UP",getstatus->linkSetId));
      linkSetresp.status=1;

    } 
   else
    {
     ISIL_DEBUG_TRACE(("get_linkSetStatus:LinkSet:%d DOWN",getstatus->linkSetId));
      linkSetresp.status=0;

     }
   }
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(ScmNwstkLinkSetStatus));
        memset(ev.data,0,sizeof(ScmNwstkLinkSetStatus)); 
        hdr.len=sizeof(ScmNwstkLinkSetStatus); 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_linkSetStatus:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&linkSetresp,sizeof(ScmNwstkLinkSetStatus)); 
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ISIL_ERROR_TRACE(("get_linkSetStatus:SCM Write Event wth len=%d",ev.len));
       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_linkSetStatus:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;


 
}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int
isil_get_routeStatus(ITS_EVENT *evt)
{
ScmNwstkRouteStatus *getstatus = (ScmNwstkRouteStatus *)evt->data;

ScmNwstkRouteStatus routeresp;
 NwStkHdr hdr;
ITS_EVENT ev;
SS7_Destination* dest=NULL;
int index=0;
int ret=0;

   I_U8 Opcode=0;
   I_U8 cnt=1;
   I_U8 trid=0;
  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];

   if(getstatus==NULL)
   {
     ISIL_ERROR_TRACE(("get_routeStatus:"));
     return NWSTK_WRONG_PARAM;
   }
   ISIL_DEBUG_TRACE(("get_routeStatus:"));
   ISIL_DEBUG_TRACE(("get_routeStatus:RPC :%d NI :%d",getstatus->destinationPointCode,getstatus->networkIndicator));
   dest = ROUTE_FindDestination(getstatus->destinationPointCode,
                getstatus->networkIndicator, FAMILY);

    if (dest == NULL)
     {
           ISIL_ERROR_TRACE(("get_routeStatus:First Add Route"));
           Opcode=NWSTK_SCM_ROUTE_STATUS_NACK_RESP;
           ret=NWSTK_INVALID_ROUTE;
           ret= NWSTK_SendRESP((I_S16)ret,Opcode,trid);
           if(ret!=ITS_SUCCESS)
           {  
             ISIL_ERROR_TRACE(("get_routeStatus:Send RESP To SCM Fail:"));
           }
          return NWSTK_INVALID_ROUTE;
     }

   routeresp.destinationPointCode=getstatus->destinationPointCode;
   routeresp.family=getstatus->family;
   routeresp.networkIndicator=getstatus->networkIndicator;

/*
  for (index = 0; index < dest->numEntries; index++)
    {
      if (dest->entries[index]->isAllowed==ITS_TRUE &&
               dest->entries[index]->isRestricted==ITS_TRUE && 
                    dest->entries[index]->basic.style==ROUTE_DPC_NI)
      {
                
         routeresp.status=1;
         break;
                 
      }
     else
      {
         routeresp.status=0;        

      }


    }*/
   if(dest->status == DESTINATION_RESTRICTED || dest->status == DESTINATION_UNAVAILABLE)
   {
         routeresp.status=0;        

   }
  else 
   {
         routeresp.status=1;        

   }
   
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(ScmNwstkRouteStatus));
        memset(ev.data,0,sizeof(ScmNwstkRouteStatus)); 
        hdr.len=sizeof(ScmNwstkRouteStatus); 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_routeStatus:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&routeresp,sizeof(ScmNwstkRouteStatus)); 
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_routeStatus:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;



}
/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
static int
isil_get_ssnStatus(ITS_EVENT *evt)
{
ScmNwstkSsnStatus *getstatus = (ScmNwstkSsnStatus *)evt->data;

ScmNwstkSsnStatus Ssnresp;
 NwStkHdr hdr;
SCCPSubSystemInfo* info=NULL;
ITS_EVENT ev;
int ret=0;

   I_U8 Opcode=0;
   I_U8 cnt=1;
   I_U8 trid=0;
  Opcode=evt->data[cnt++];
  trid=evt->data[cnt++];
   if(getstatus==NULL)
   {
     ISIL_ERROR_TRACE(("get_ssnStatus:"));
     return NWSTK_WRONG_PARAM;
   }

   ISIL_DEBUG_TRACE(("get_ssnStatus:"));
   ISIL_DEBUG_TRACE(("get_ssnStatus:RPC :%d,SSN :%d,NI:%d",getstatus->destinationPointCode,getstatus->ssn,getstatus->networkIndicator))
   info = SCCP_GetSSEntry( (ITS_UINT)getstatus->destinationPointCode, 
                                   (ITS_OCTET)getstatus->networkIndicator, 
                                       (ITS_OCTET)getstatus->ssn);
  if(info==NULL)
  {
          ISIL_ERROR_TRACE(("get_ssnStatus:SSN Entry not Found"));

           Opcode=NWSTK_SCM_SSN_STATUS_NACK_RESP;
           ret=NWSTK_LNK_NOTFOUND;
           ret= NWSTK_SendRESP((I_S16)ret,Opcode,trid);
           if(ret!=ITS_SUCCESS)
           {  
             ISIL_ERROR_TRACE(("get_ssnStatus:Send RESP To SCM Fail:"));
           }
  }
  Ssnresp.destinationPointCode=getstatus->destinationPointCode;
  Ssnresp.networkIndicator=getstatus->networkIndicator;
  Ssnresp.ssn=getstatus->ssn;

  if(info->inService==ITS_FALSE)
  { 
   Ssnresp.status=0;
  }
 else
  {
   Ssnresp.status=1;

  }
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(ScmNwstkSsnStatus));
        memset(ev.data,0,sizeof(ScmNwstkSsnStatus)); 
        hdr.len=sizeof(ScmNwstkSsnStatus); 
        ret=BuildHeader(*evt,&hdr); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_ssnStatus:Build Header fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        }
        memcpy(&ev.data[0],&Ssnresp,sizeof(ScmNwstkSsnStatus)); 
        memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));

       ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
       if(ret!=ITS_SUCCESS)
        {
          ISIL_ERROR_TRACE(("get_ssnStatus:SCM Write Event Fail"));
          ITS_EVENT_TERM(&ev);
          return !ITS_SUCCESS;
        } 
     return ITS_SUCCESS;
  
} 

/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
int
NWSTK_SendRESP(I_S16 ret,I_U8 Opcode,I_U8 tid)
{

 NwStkConfigResp Resp;
 ITS_EVENT ev;

 ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwStkConfigResp));

 ISIL_ERROR_TRACE(("CMD_RESP To SCM:"));

 memset(&Resp,0,sizeof(NwStkConfigResp));
 
 Resp.nwstkhdr.appid=SCM_NWSTK_APPID;
 Resp.nwstkhdr.opcode=Opcode;
 Resp.nwstkhdr.trid=tid;
 Resp.nwstkhdr.len=sizeof(NwStkConfigResp);
 Resp.erro_code=ret;


  memset(ev.data,0,sizeof(NwStkConfigResp)); 
  memcpy(&ev.data[0],&Resp,sizeof(NwStkConfigResp));
 
 /* ev.data[3]=sizeof(NwStkConfigResp) & 0x00ff;
  ev.data[4]=(sizeof(NwStkConfigResp) & 0xff00) >> 8;*/

 /*  ISIL_ERROR_TRACE(("ev.len=%d",ev.len));
   ISIL_ERROR_TRACE(("ev.data[0]=%d",ev.data[0]));
   ISIL_ERROR_TRACE(("ev.data[1]=%d",ev.data[1]));
   ISIL_ERROR_TRACE(("ev.data[2]=%d",ev.data[2]));
   ISIL_ERROR_TRACE(("ev.data[3]=%d",ev.data[3]));
   ISIL_ERROR_TRACE(("ev.data[4]=%d",ev.data[4]));
*/ 


 ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
  if(ret!=ITS_SUCCESS)
  {
   ISIL_ERROR_TRACE(("SCM Write Event Fail"));
   ITS_EVENT_TERM(&ev);
   return !ITS_SUCCESS;
  }
   return ITS_SUCCESS;
 
 


}


/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
int
NWSTK_SendPEGRESP(I_S16 ret,I_U8 Opcode,void *pegs)
{
 NwstkScmMtp3GenPegResponse  mtp3genpegs;
 NwstkScmMtp3LinkPegResponse linkpegs;
 NwstkScmMtp3RoutePegResponse routepegs;
 NwstkScmSccpGenPegResponse  sccpgenpegs;
 NwstkScmBssapGenPegResponse bssapgenpegs;

 ITS_EVENT ev;

 switch(Opcode)
 {
   case SCM_NWSTK_MTP3_GENPEG_GET:
        
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmMtp3GenPegResponse));
        memset(ev.data,0,sizeof(NwstkScmMtp3GenPegResponse)); 
        memcpy(&ev.data[0],&mtp3genpegs,sizeof(NwstkScmMtp3GenPegResponse)); 
 
   break;
   case SCM_NWSTK_MTP3_LINKPEG_GET:
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmMtp3LinkPegResponse));
        memset(ev.data,0,sizeof(NwstkScmMtp3LinkPegResponse)); 
        memcpy(&ev.data[0],&linkpegs,sizeof(NwstkScmMtp3LinkPegResponse)); 
   break;
   case SCM_NWSTK_MTP3_ROUTEPEG_GET:
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmMtp3RoutePegResponse));
        memset(ev.data,0,sizeof(NwstkScmMtp3RoutePegResponse)); 
        memcpy(&ev.data[0],&routepegs,sizeof(NwstkScmMtp3RoutePegResponse)); 
   break;
   case SCM_NWSTK_SCCP_GENPEG_GET: 
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmSccpGenPegResponse));
        memset(ev.data,0,sizeof(NwstkScmSccpGenPegResponse)); 
        memcpy(&ev.data[0],&sccpgenpegs,sizeof(NwstkScmSccpGenPegResponse)); 
   break;
   case SCM_NWSTK_BSSAP_GENPEG_GET:
        ITS_EVENT_INIT(&ev ,ITS_SCM_SRC ,sizeof(NwstkScmBssapGenPegResponse));
        memset(ev.data,0,sizeof(NwstkScmBssapGenPegResponse)); 
        memcpy(&ev.data[0],&bssapgenpegs,sizeof(NwstkScmBssapGenPegResponse)); 
   break;
   //default:
 }
 
   ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
   if(ret!=ITS_SUCCESS)
   {
     ISIL_ERROR_TRACE(("SCM Write Event Fail"));
     ITS_EVENT_TERM(&ev);
     return !ITS_SUCCESS;
   }
   return ITS_SUCCESS;

 }
/*********************************************/


/*******************************************/


static int
isil_mtp2timer_modify(ITS_EVENT *ev)
{

//	ScmNwstkMtp2TimerModify *mtp2timer =( ScmNwstkMtp2TimerModify *)ev->data;
	ITS_UINT ret=0;
	ITS_UINT Ret=0;
	TIMERCONFIG=0;

	//ISIL_DEBUG_TRACE(("mtp2timer_modify:linkSet %d  linkCode %d",mtp2timer->linkSetId,mtp2timer->linkId));
	ev->src=ITS_DEFAULT_SRC;
	ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, ev);
	if (ret!=ITS_SUCCESS)
	{
             ISIL_ERROR_TRACE(("mtp2timer_modify:TRANSPORT_PutEvent failed "));
             return NWSTK_WRONG_PARAM; 
	}
	ISIL_DEBUG_TRACE(("Enter Sema Wait for  mtp2timer_modify semacntr=%d",mtp2_sema.semCounter));
	Ret=SEMA_WaitSemaphoreWithTimeOut(&mtp2_sema,3000);
	if(Ret!=ITS_SUCCESS)
	{
		ISIL_ERROR_TRACE(("Sema Wait Fail for mtp2timer_modify"));
	}
	ISIL_DEBUG_TRACE(("Sucess Sema Wait for mtp2timer_modify"));
	ITS_EVENT_TERM(ev);
	if(TIMERCONFIG==1)
	{ 
		return NWSTK_CMD_CNG_SUCCESS ;
	}
	else
	{
		return NWSTK_WRONG_PARAM;
	} 
}

static int
isil_mtp2Pegs_get(ITS_EVENT *ev)
{
ScmNwstkMtp2PegGet *mtp2peg = (ScmNwstkMtp2PegGet *)ev->data;
ITS_UINT ret,Ret;
PEGCONFIG=0;

       ISIL_DEBUG_TRACE(("mtp2Pegs_get:linkSet %d  linkCode %d",mtp2peg->linkSetId,mtp2peg->linkId));
       pegtrid=mtp2peg->nwstkhdr.trid;
       ev->src=ITS_DEFAULT_SRC;
       ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, ev);
       if (ret!=ITS_SUCCESS)
        {
             ITS_EVENT_TERM(ev);
        }
       ISIL_DEBUG_TRACE(("Enter Sema Wait for isil_mtp2Pegs_get  semacntr=%d",mtp2_sema.semCounter));
			 Ret=SEMA_WaitSemaphoreWithTimeOut(&mtp2_sema,3000);
       if(Ret!=ITS_SUCCESS)
        {
           ISIL_DEBUG_TRACE(("Sema Wait Fail for isil_mtp2Pegs_get"));
        }
       ISIL_DEBUG_TRACE(("Sucess Sema Wait for isil_mtp2Pegs_get"));
       if(PEGCONFIG==1)
       { 
         return NWSTK_CMD_CNG_SUCCESS ;
       }
       else
       {
         return NWSTK_WRONG_PARAM;
       } 


}











/*******************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/


int  ISILPro_SCMMsg(ITS_EVENT *ev)
{
   I_U8 Opcode=0;
   I_U8 cnt=1;
   I_S16 ret=0;
   I_U8 trid=0;

     

  Opcode=ev->data[cnt++];
  trid=ev->data[cnt++];
  
  switch(Opcode)
  {

   case SCM_NWSTK_MTP3_GENCFG:
        ret=isil_mtp3_gencfg(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:mtp3_gencfg Fail"));
        }
        Opcode=NWSTK_SCM_MTP3_GENCFG_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_BSSAP_GENCFG:
        ret=isil_bssap_gencfg(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:bssap_gencfg Fail"));
        }
        Opcode=NWSTK_SCM_BSSAP_GENCFG_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_SCCP_GENCFG:
        ret=isil_sccp_gencfg(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:sccp_gencfg Fail"));
        }
        Opcode=NWSTK_SCM_SCCP_GENCFG_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;

   case SCM_NWSTK_LINKSET_ADD:
         
        ret=isil_ls_add(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:ls_add Fail"));
        }
        Opcode=NWSTK_SCM_LINKSET_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
   case SCM_NWSTK_LINKSET_DEL:

        ret=isil_ls_del(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:ls_del Fail"));
        }
        Opcode=NWSTK_SCM_LINKSET_DEL_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
   case SCM_NWSTK_LINK_ADD:
  /*        if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_ITU_DIDS) != ITS_SUCCESS)
        {
             return (NULL);
        }
  */

        ret=isil_ln_add(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:ln_add Fail"));
        }
//        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_ITU_DIDS);
        Opcode=NWSTK_SCM_LINK_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_LINK_DEL:

         ret=isil_ln_del(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:ln_del Fail"));
        }
        Opcode=NWSTK_SCM_LINK_DEL_RESP; 
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_SS7ROUTE_ADD:
         
         ret=isil_rt_add(ev); 
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:rt_add Fail"));
        }

        Opcode=NWSTK_SCM_SS7ROUTE_ADD_RESP; 
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
   case SCM_NWSTK_SS7ROUTE_DEL:

         ret=isil_rt_del(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:rt_del Fail"));
        }
        Opcode=NWSTK_SCM_SS7ROUTE_DEL_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

        
   break;
   case SCM_NWSTK_SCCP_LSSN_ADD:

        ret=isil_lssn_add(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:lssn_add Fail"));
        }
        Opcode=NWSTK_SCM_SCCP_LSSN_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
   case SCM_NWSTK_SCCP_LSSN_DEL:

        ret=isil_lssn_del(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:lssn_del Fail"));
        }
        Opcode=NWSTK_SCM_SCCP_LSSN_DEL_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }


   break;
   case SCM_NWSTK_SCCP_RSSN_ADD:

        ret=isil_rssn_add(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:rssn_add Fail"));
        }
        Opcode=NWSTK_SCM_SCCP_RSSN_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
   case SCM_NWSTK_SCCP_RSSN_DEL:

        ret=isil_rssn_del(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:rssn_del Fail"));
        }
        Opcode=NWSTK_SCM__SCCP_RSSN_DEL_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
   case SCM_NWSTK_SCCP_CSSN_ADD:

        ret=isil_cssn_add(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:cssn_add Fail"));
        }
        Opcode=NWSTK_SCM_SCCP_CSSN_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
   case SCM_NWSTK_SCCP_CSSN_DEL:

        ret=isil_cssn_del(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:cssn_del Fail"));
        }
        Opcode=NWSTK_SCM_SCCP_CSSN_DEL_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_SS7ROUTE_ADMIN_STATE_MODIFY:

        ret=isil_rtmodify_state(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:rtmodifystat Fail"));
        }

        Opcode=NWSTK_SCM_SS7ROUTE_ADMIN_STATE_MODIFY_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
     case SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY:
        

        ret=isil_ls_statemodify(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:ls_act Fail"));
        }

        Opcode=NWSTK_SCM_LINKSET_ADMIN_STATE_MODIFY_RESP;

        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
     case SCM_NWSTK_LINK_ADMIN_STATE_MODIFY:
  /*      if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_ITU_DIDS) != ITS_SUCCESS)
        {
             return (NULL);
        }
   */

        ret=isil_ln_statemodify(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:ln_statemodify Fail"));
        }
    //    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_ITU_DIDS);

        Opcode=NWSTK_SCM_LINK_ADMIN_STATE_MODIFY_RESP;

        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
#ifdef MSC_CODE
   case SCM_NWSTK_GTT_ADD:

        ret=isil_gtt_add(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:gtt_add Fail"));
        }
        Opcode=NWSTK_SCM_GTT_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_GTT_REM:

        ret=isil_gtt_del(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:gtt_del Fail"));
        }
        Opcode=NWSTK_SCM_GTT_REM_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
#endif //MSC_CODE
   case SCM_NWSTK_BSSAP_CIC_ADD:

        ret=isil_bssapcic_add(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:bssapcic_add Fail"));
        }
        Opcode=NWSTK_SCM_BSSAP_CIC_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_BSSAP_CIC_DEL:
        ret=isil_bssapcic_del(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:bssapcic_add Fail"));
        }

        Opcode=NWSTK_SCM_BSSAP_CIC_DEL_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_BSSAP_CFG_ADD:

        ret=isil_bssapcfg_add(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:bssapcfg_add Fail"));
        }
        Opcode= NWSTK_SCM_BSSAP_CFG_ADD_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_BSSAP_CFG_DEL:

        ret=isil_bssapcfg_del(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:bssapcfg_del Fail"));
        }
        Opcode=NWSTK_SCM_BSSAP_CFG_DEL_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;
   case SCM_NWSTK_MTP3_TIMER_MODIFY:

        ret=isil_modify_mtp3tmr(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:mtp3_timermodify Fail"));
        }
       Opcode=NWSTK_SCM_MTP3_TIMER_MODIFY_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;

   case SCM_NWSTK_SCCP_TIMER_MODIFY:

        ret=isil_modify_sccptmr(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:sccp_timermodify Fail"));
        }
        Opcode=NWSTK_SCM_SCCP_TIMER_MODIFY_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }
   break;

   case SCM_NWSTK_BSSAP_TIMER_MODIFY:

        ret=isil_modify_bssaptmr(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:bssap_timermodify Fail"));
        }
        Opcode=NWSTK_SCM_BSSAP_TIMER_MODIFY_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        } 
   break;


   case SCM_NWSTK_MTP3_GENPEG_GET:

        ret=isil_get_mtp3genpegs(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:mtp3_genpegs Fail"));
        }
          
   break;
 
   break;
   case SCM_NWSTK_MTP3_LINKPEG_GET:

        ret=isil_get_lnpegs(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:get_mtp3linkpeg Fail"));
        }
   break;

   case SCM_NWSTK_MTP3_ROUTEPEG_GET:

        ret=isil_get_rtpegs(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:get_mtp3routepegs Fail"));
        }

   break;
   case SCM_NWSTK_SCCP_GENPEG_GET:
        ret=isil_get_sccpgenpegs(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:get_sccppegs Fail"));
        }
   break;

   case SCM_NWSTK_BSSAP_GENPEG_GET:
        ret=isil_get_bssapgenpegs(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:get_bssappegs Fail"));
        }
   break;
   case SCM_NWSTK_LINK_STATUS_GET:
        ret=isil_get_linkStatus(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:getln_status Fail"));
        }
   break;
   case SCM_NWSTK_LINKSET_STATUS_GET:
        ret=isil_get_linkSetStatus(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:getln_status Fail"));
        }
   break;
   case SCM_NWSTK_ROUTE_STATUS_GET:
        ret=isil_get_routeStatus(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:getrt_status Fail"));
        }
   break;
   case SCM_NWSTK_SSN_STATUS_GET:
        ret=isil_get_ssnStatus(ev);

        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:getssn_status Fail"));
        }
   break;
  case SCM_NWSTK_SCCP_SET_BEHAV:
        Opcode=NWSTK_SCM_SCCP_SET_BEHAV_RESP;
        ret=ITS_SUCCESS;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        } 
  break;
#if 0
   case SCM_NWSTK_MTP2_TIMER_MODIFY:

        ret=isil_mtp2timer_modify(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC:modify mtp2 timer Fail\n"));
        }
        Opcode=NWSTK_SCM_MTP2_TIMER_MODIFY_RESP;
        ret= NWSTK_SendRESP(ret,Opcode,trid);
        if(ret!=ITS_SUCCESS)
        {  
           ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
        }

   break;
#endif
   case SCM_NWSTK_MTP2_PEG_GET:

        ret=isil_mtp2Pegs_get(ev);
        if(ret!=NWSTK_CMD_CNG_SUCCESS)
        {  
          ISIL_ERROR_TRACE(("CMD_PROC: mtp2 peg get Fail\n"));
          Opcode=NWSTK_SCM_MTP2_PEG_RESP;
          ret= NWSTK_SendRESP(ret,Opcode,trid);
          if(ret!=ITS_SUCCESS)
          {  
            ISIL_ERROR_TRACE(("Send RESP To SCM Fail:"));
          }
        }

   break;
   default :
          ISIL_ERROR_TRACE(("Command Not Implemented:"));
   
 }
ITS_EVENT_TERM(ev);

       

}



