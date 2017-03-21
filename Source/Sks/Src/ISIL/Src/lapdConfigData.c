#include <lapd_adaptation_layer.h>
#include <lapdif_handler.h>
#include <lapd_trace.h>

#include <its_types.h>
/*#include <its++.h>
#include <its_sctp.h>
#include <sctp_msgs.h>
#include "its_sctp_impl.h"
#include "its_sockets.h"*/


/* define flag for insert */
#define LAPD_TEIFLAG    1
#define APP_TEIFLAG     2
#define OML_SAPIFLAG    3
#define RSL_SAPIFLAG    4 
#define TSFLAG          5
#define IFCFLAG         6
#define LINKUPFLAG      7
#define TEIOFFSETFLAG   8
#define CONFIG_SUCCESS  1
#define CONFIG_FAIL     0
/* end flag define */
static int lapd_start = 1;
int  checkAndUpdateLapdCfgValue(char operation, op_conf_data *cfgPtr);
void get_key(unsigned short* key, unsigned short lapdts);
int  insert_value_in_hash_table(unsigned short key, op_conf_data *cfgPtr);
int  delete_value_from_config_table(unsigned short key, op_conf_data  *cfgPtr);
int  search_config_data(unsigned short key, op_conf_data  *cfgPtr);
int  modifyLapdlinkstatusConftable(unsigned short key, op_conf_data  *cfgPtr);
void delete_configTbl();
void checkConfig_flag(op_conf_data  *cfgPtr,int *CfgFlag);

extern int start_comm(ITS_OCTET ts, ITS_OCTET sapi, ITS_OCTET lapdTei, ITS_OCTET appTei);

extern struct conf_data *CONF_DATA[];
  
void checkConfig_flag(op_conf_data  *cfgPtr,int *CfgFlag)
{
 if(cfgPtr->lapdteiflag == 1)
 {
  *CfgFlag = LAPD_TEIFLAG;
 }
 else if(cfgPtr->appteiflag == 1) 
 {
  *CfgFlag = APP_TEIFLAG;
 }
 else if(cfgPtr->tsflag) 
 {
  *CfgFlag = TSFLAG;
 }
 else if((cfgPtr->link_status1== 1)||(cfgPtr->link_status2 == 1))
 {
  *CfgFlag = LINKUPFLAG;
 } 
 else
 {
  *CfgFlag = IFCFLAG;
 }
}

void init_lapdCfgData()
{
 unsigned short loop;
 for(loop = 0; loop<MAXTSVAL; loop++)
 {
  CONF_DATA[loop] = NULL;
 } 
 memset(lapGData.TS_DATA, 0xff, MAX_APPTEI * sizeof(int));
 lapGData.maxFd = 0;
 lapGData.noOfFd = 0;
 FD_ZERO(&lapGData.allLapdFd);
}

void get_key(unsigned short* key, unsigned short ts)
{
   unsigned short const_dev;
   const_dev = 9;
   *key = ts % const_dev;           
}


int  checkAndUpdateLapdCfgValue(char operation, op_conf_data  *cfgPtr)
{
 unsigned short key, ret;
 // get_key(&key, cfgPtr->ts);
 /* anand :- to make searching easy & fast I have used array of config data
    size of array should be equal to highest value of ts config i.e. pp port value*/
 key = cfgPtr->ts;
 switch(operation)
 {
   case LAPD_ADD:
        ret = insert_value_in_hash_table(key, cfgPtr);
        if(ret == 0)
         { 
          LAPD_TRACE_CRITICAL(("\nconfig data: INSERTION FAILURE"));
         }
        else
         {
          LAPD_TRACE_INFO(("\nlapd config data: INSERTION SUCCESSFUL"));
         }
       break;
   case LAPD_DEL:
        ret = delete_value_from_config_table(key, cfgPtr);
        if(ret == 0)
         { 
          LAPD_TRACE_CRITICAL(("\nlapd config data: DELETE FAILURE"));
         }
        else
         {
          LAPD_TRACE_INFO(("\nlapd config data: DELETE SUCCESSFUL"));
         } 
        break;
   case LAPD_GET: 
        ret = search_config_data(key, cfgPtr);
        if(ret == 0)
         { 
          LAPD_TRACE_INFO(("\nlapd config data: Entry not found in lapd conf tbl"));
         }
        else
         {
          //LAPD_TRACE_INFO(("\nlapd config data: ENTRY FOUND IN LAPD CONFIG LIST"))
         }
        break;
    case LAPD_MODIFY:
         ret = modifyLapdlinkstatusConftable(key, cfgPtr);
        if(ret == 0)
         {
          LAPD_TRACE_CRITICAL(("\nlapd config data: Ts Entry not found in Lapd config table"));
         }
        else
        {
         LAPD_TRACE_INFO(("\nlapd config data: linkStatus modified "));
        }
        break;

 } 
 return ret;
}


int modifyLapdlinkstatusConftable(unsigned short key, op_conf_data  *cfgPtr)
{
  struct conf_data *prv;
  struct conf_data *next;
  int CfgFlag, ret; 
  struct timeval wait;
  
  if(CONF_DATA[key] == NULL)
   {
     LAPD_TRACE_CRITICAL(("\n\tLapd config: lapd config table is empty"));
     return 0;
   }
  else
   {
    prv = CONF_DATA[key];
    next = prv;
    checkConfig_flag(cfgPtr, &CfgFlag);
    switch(CfgFlag)
    {
      case IFCFLAG:
         while(prv != NULL)
         {
           prv->nfd = cfgPtr->nfd;
           if(lapGData.maxFd < cfgPtr->nfd)
           { lapGData.maxFd = cfgPtr->nfd;}
           prv->ifc  = cfgPtr->ifc;
           prv->opflag = 1;
           prv = prv->nxt;       
         }
        return CONFIG_SUCCESS;
      case LAPD_TEIFLAG :
      case APP_TEIFLAG  :
         while(prv != NULL)
         {
          if((prv->lapdTei == cfgPtr->lapdTei) && (prv->appTei == cfgPtr->appTei) && (prv->teiflag == 0))
          {
           if((prv->sapi1 != 0xff)&&(prv->sapi2 != 0xff))
           { 
#ifdef MTP2SIM
            ret = ITS_SUCCESS;
#endif
#ifdef TMCC
            ret = start_comm(prv->ts, prv->sapi1, prv->lapdTei, prv->appTei);
            if(ret == ITS_SUCCESS)
            {
             if(lapd_start)
             { 
              if(Start_Module(prv->nfd) < 0)
              {
               LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
                                    "LAPD Start failed !!..."));
               return !ITS_SUCCESS;
              }
              lapd_start = 0; /* anand: lapd start is required only once 
                                        to init lapd for callback func */ 
             }  
             if(Establish_Link(prv->nfd, prv->ifc, prv->sapi2, prv->lapdTei) < 0)
             {
              LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
                 "Could not establish link for channel: %d ...", prv->ts));
              ret = !ITS_SUCCESS;
             }
#ifndef LAPD_HA
            /*wait.tv_sec = 0;
            wait.tv_usec =50000;
            select(0,  NULL, NULL, NULL, &wait);*/
#endif
            LAPD_TRACE_INFO(("\nLAPDIF_Init: Establish_Link() success .."));
           }
#endif 
           }
           else
           {
            int sapi;
            sapi = (prv->sapi1 != 0xff)?prv->sapi1:prv->sapi2;
#ifdef MTP2SIM
            ret = ITS_SUCCESS;
#endif
#ifdef TMCC 
            ret = start_comm(prv->ts, sapi, prv->lapdTei, prv->appTei);
#endif 
           }
           if(ret == ITS_SUCCESS)
           {
            prv->teiflag = 1;
            return CONFIG_SUCCESS;
           }
           else
           {
            return CONFIG_FAIL;
           }
          }       
          prv = prv->nxt;  
         }
         return CONFIG_SUCCESS;
 
      case LINKUPFLAG: 
         while(prv != NULL)
         {
           if((prv->lapdTei == cfgPtr->lapdTei) || (prv->appTei == cfgPtr->appTei))
          {
           if(cfgPtr->link_status1 == 1)   
             prv->link_status1 = cfgPtr->link_status;   
           else   
            prv->link_status2 = cfgPtr->link_status;   
           return CONFIG_SUCCESS;
          }
          prv = prv->nxt;
         }
         return CONFIG_FAIL;
/*      case TEIOFFSETFLAG: 
         while(prv != NULL)
         {
           if((prv->lapdTei == cfgPtr->lapdTei) || (prv->appTei == cfgPtr->appTei))
           {
            cfgPtr->teiOffsetval = cfgPtr->teiOffsetval;   
            return CONFIG_SUCCESS;
           }
          prv = prv->nxt;
         }
         return CONFIG_FAIL;*/
      default:
         LAPD_TRACE_MAJOR(("\n\tLapd config: config flag not set"));
         return CONFIG_FAIL;
    }                
    return 0;
   }
}

int insert_value_in_hash_table(unsigned short key, op_conf_data  *cfgPtr)
{
 struct conf_data *prv, *next;
 int CfgFlag, index = 0;
 if(cfgPtr->appTei > MAX_APPTEI)
 {
  LAPD_TRACE_MAJOR(("\n\t LAPD Tei config failure: cause appTei value out of range"));
  return CONFIG_FAIL;
 }
 if(CONF_DATA[key] == NULL)
   {
    CONF_DATA[key] = (struct conf_data*)malloc(sizeof(struct conf_data)); 
    memset(CONF_DATA[key], 0, sizeof(struct conf_data)); 
    CONF_DATA[key]->ts          = cfgPtr->ts;

    CONF_DATA[key]->lapdTei     = cfgPtr->lapdTei;
    CONF_DATA[key]->appTei      = cfgPtr->appTei;
    CONF_DATA[key]->sapi1       = cfgPtr->sapi1;
    CONF_DATA[key]->sapi2       = cfgPtr->sapi2;
    lapGData.TS_DATA[cfgPtr->appTei] = cfgPtr->ts;   
    CONF_DATA[key]->tsflag      = 1;
    CONF_DATA[key]->teiflag     = 0;
    CONF_DATA[key]->opflag      = cfgPtr->opflag;
    CONF_DATA[key]->nfd         = cfgPtr->nfd;
    CONF_DATA[key]->ifc         = cfgPtr->ifc;
    CONF_DATA[key]->link_status1= 0;
    CONF_DATA[key]->link_status2= 0;
    CONF_DATA[key]->nxt         = NULL;
  } 
 else
  {
   prv = CONF_DATA[key];
   checkConfig_flag(cfgPtr, &CfgFlag);
   switch(CfgFlag)
   {
    case LAPD_TEIFLAG:
    case APP_TEIFLAG:
         while(prv != NULL)
         {
          if((prv->lapdTei == 0xff) && (prv->appTei == 0xff))
          {
            prv->sapi1       = cfgPtr->sapi1;
            prv->sapi2       = cfgPtr->sapi2;
            prv->lapdTei = cfgPtr->lapdTei;
            prv->appTei  = cfgPtr->appTei;
            prv->opflag  = cfgPtr->opflag;
            prv->nfd     = cfgPtr->nfd;
            prv->ifc     = cfgPtr->ifc;
            lapGData.TS_DATA[cfgPtr->appTei] = cfgPtr->ts;   
            prv->tsflag  = 1;
            prv->teiflag = 0;
            prv->opflag      = cfgPtr->opflag;
            prv->nfd         = cfgPtr->nfd;
            prv->ifc         = cfgPtr->ifc;
            prv->link_status1= 0;
            prv->link_status2= 0;
            return CONFIG_SUCCESS;
          }
          else
          if(prv->nxt == NULL)
          {
            index++;
            prv->nxt = (struct conf_data*)malloc(sizeof(struct conf_data));
            next = prv->nxt;
            memcpy(next, CONF_DATA[key], sizeof(struct conf_data));
            next->sapi1   = cfgPtr->sapi1;
            next->sapi2   = cfgPtr->sapi2;
            next->lapdTei = cfgPtr->lapdTei;
            next->appTei  = cfgPtr->appTei;
            next->opflag  = cfgPtr->opflag;
            next->nfd     = prv->nfd; /* because fd is for all tei corresponding to unique ts val*/
            lapGData.TS_DATA[cfgPtr->appTei] = cfgPtr->ts;   
            if(lapGData.maxFd < cfgPtr->nfd)
            { lapGData.maxFd = cfgPtr->nfd;}
            next->tsflag  = 1;
            next->teiflag = 0;
            next->opflag      = prv->opflag;
            next->ifc         = prv->ifc;
            next->link_status1= 0;
            next->link_status2= 0;
            next->nxt = NULL;
            return CONFIG_SUCCESS;
           }    
          prv = prv->nxt;      
         }
         return CONFIG_FAIL;
  
    case IFCFLAG:
        while(prv != NULL)
         {
           prv->nfd = cfgPtr->nfd;
           prv->ifc   = cfgPtr->ifc;
           prv->tsflag   = 1;  
           prv->opflag   = 1; 
         } 
        return CONFIG_SUCCESS;

    default:
         LAPD_TRACE_MAJOR(("\n\tLapd config: config flag not set"));
         return CONFIG_FAIL;
   }
  }
 return CONFIG_SUCCESS; 
}

int delete_value_from_config_table(unsigned short key, op_conf_data  *cfgPtr)
{
  struct conf_data *prv;
  struct conf_data *next;
  int CfgFlag, index = 1;
  if(CONF_DATA[key] == NULL)
  {
    LAPD_TRACE_CRITICAL(("\n\tDELETE FAILURE: LAPD CFG LIST EMPTY"));
    return 0;
  }
  else
  {
    /*element to be delete is the first element*/
     next = CONF_DATA[key];
     prv = next;
     checkConfig_flag(cfgPtr, &CfgFlag);
     switch(CfgFlag)
     {
       case LAPD_TEIFLAG:
       case APP_TEIFLAG:  
          if((next->lapdTei == cfgPtr->lapdTei) && (next->appTei == cfgPtr->appTei))
          {
           if(next->nxt == NULL)
           {
         
            next->lapdTei = 0xff;
            lapGData.TS_DATA[cfgPtr->appTei] = 0xff;   
            next->appTei  = 0xff;
            next->teiflag  = 0;
            return CONFIG_SUCCESS;
           }
           else
           {
            CONF_DATA[key]=next->nxt;
            free(next);
            return CONFIG_SUCCESS;
           }
          }
         while(next != NULL)
         {
          if((next->lapdTei == cfgPtr->lapdTei) && (next->appTei == cfgPtr->appTei))
          {
           prv->nxt = next->nxt;
           free(next);  
           return CONFIG_SUCCESS;
          }
          prv  = next;       
          next = next->nxt;
         }
         return CONFIG_FAIL;
      case IFCFLAG:
         while(next != NULL)
         {
          if((next->lapdTei == cfgPtr->lapdTei) && (next->appTei == cfgPtr->appTei))
          {
            next->nfd = 0xFF;
            next->ifc = 0xFF;
           return CONFIG_SUCCESS;
          }
          next = prv->nxt;
          prv  = prv->nxt;       
         }
         return CONFIG_FAIL;
    default:
         LAPD_TRACE_MAJOR(("\n\tLapd config: config flag not set"));
         return CONFIG_FAIL;
              
     }
  } 
  return CONFIG_FAIL;
}

int search_config_data(unsigned short key, op_conf_data  *cfgPtr)
{
 struct conf_data *prv;
 struct conf_data *next;
 int CfgFlag;
 checkConfig_flag(cfgPtr, &CfgFlag);
 next = CONF_DATA[key];
 prv = next;
 switch(CfgFlag)
 {
  case TSFLAG:/* here this will return ts config or not + flag status to get call */
        LAPD_TRACE_INFO(("\n\tSearch in LAPD hash tbl: for ts: %d", cfgPtr->ts));
       if(CONF_DATA[key]  == NULL)
       {
        LAPD_TRACE_INFO(("\n\tLapd config: ts list is empty"));
        return CONFIG_FAIL;
       }
       cfgPtr->lapdTei = next->lapdTei;  
       cfgPtr->appTei = next->appTei;  
       cfgPtr->opflag = next->opflag;
       cfgPtr->nfd = next->nfd;  
       cfgPtr->ifc = next->ifc;  
       cfgPtr->sapi1 = next->sapi1;  
       cfgPtr->sapi2 = next->sapi2;  
       cfgPtr->link_status1 =next->link_status1; 
       cfgPtr->link_status2 =next->link_status2; 
       return CONFIG_SUCCESS;   
       
  case LAPD_TEIFLAG:
  case APP_TEIFLAG:
         while(next != NULL)
         {
          if((((next->appTei == cfgPtr->appTei)|| (next->lapdTei == cfgPtr->lapdTei))
              &&((CfgFlag == LAPD_TEIFLAG) && (CfgFlag == APP_TEIFLAG)))   /* when both flags are set*/
              ||((next->appTei == cfgPtr->appTei) && (CfgFlag == APP_TEIFLAG))/*else app tei flag is set */  
              ||((next->lapdTei == cfgPtr->lapdTei) && (CfgFlag == LAPD_TEIFLAG))/*else lapd tei flag is set */  
             )
          {
           cfgPtr->opflag = next->opflag;
           cfgPtr->nfd = next->nfd;  
           cfgPtr->ifc = next->ifc;  
           cfgPtr->lapdTei = next->lapdTei;  
           cfgPtr->appTei = next->appTei;  
           cfgPtr->sapi1 = next->sapi1;  
           cfgPtr->sapi2 = next->sapi2;  
           cfgPtr->link_status1 =next->link_status1; 
           cfgPtr->link_status2 =next->link_status2; 
           /*LAPD_TRACE_INFO(("\n\tMapping found: for tei: %d, ts: %d, key: %d, appTei: %d", 
                          cfgPtr->lapdTei, cfgPtr->ts, key, cfgPtr->appTei));*/
           return CONFIG_SUCCESS;
          }
          next = next->nxt;
         }
         return CONFIG_FAIL;
              
        
  case IFCFLAG:
       while(next != NULL)
       {
        if((next->lapdTei == cfgPtr->lapdTei) && (next->appTei == cfgPtr->appTei) 
          && (next->ifc == cfgPtr->ifc))
        {
          return CONFIG_SUCCESS;
        }
        next = next->nxt;
       }
       return CONFIG_FAIL;
  default:
         LAPD_TRACE_MAJOR(("\n\tLapd config: config flag not set"));
         return CONFIG_FAIL;
 }
 return CONFIG_FAIL;
} 

void delete_configTbl()
{
  unsigned short key = 0;
  struct conf_data *prv;
  struct conf_data *next;
    for(key =0; key<MAXTSVAL; key++)
     { 
      if(CONF_DATA[key] == NULL)
       { 
        continue;
       } 
      next = CONF_DATA[key];
      prv = next;
      while((prv->nxt) != NULL)
       {
        next = prv->nxt;
        prv->nxt = next->nxt;
        if(next != NULL)
          free(next);
          next = NULL;
       }
        if(CONF_DATA[key] != NULL)
         {
          free(CONF_DATA[key]);
          CONF_DATA[key] = NULL;
         }
     }    
   return;
}

