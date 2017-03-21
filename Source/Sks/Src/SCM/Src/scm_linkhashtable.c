#include "scm_localhashdef.h"
#include "scm_encaps.h"



int  checkAndUpdate_linkValue_in_linkHashTable(U8 operation, U32 instance_id, U16 linkId, U16 linkSetId, U8* cardFlag, U8 adminstate)
{
 U16 key, ret;
 strcpy(g_parameter.function_string, "checkAndUpdate_linkValue_in_linkHashTable()");

     get_key(&key, linkId);
 switch(operation)
 {
   case SCM_ADD:
        ret = insert_value_in_hash_table(key, instance_id, linkId, linkSetId);
        if(ret == 0)
         { 
          SCM_printf(SCM_CRITICAL,"\nlink hash table: INSERTION FAILURE");
         }
        else
         {
          SCM_printf(SCM_INFO,"\nlink hash table: INSERTION SUCCESSFUL");
         }
       break;
   case SCM_DELETE:
        ret = delete_value_from_hash_table(key, linkSetId);
        if(ret == 0)
         { 
          SCM_printf(SCM_CRITICAL,"\nlink hash table: DELETE FAILURE");
         }
        else
         {
          SCM_printf(SCM_INFO,"\nlink hash table: DELETE SUCCESSFUL");
         } 
        break;
   case SCM_GET: 
        ret = search_link_from_hash_table(key, linkSetId, cardFlag, adminstate);
        if(ret == 0)
         { 
          SCM_printf(SCM_CRITICAL,"\nlink hash table: ENTRY NOT FOUND IN LINK HASH TABLE");
         }
        else
         {
          SCM_printf(SCM_INFO,"\nlink hash table: ENTRY FOUND IN LINKHASH TABLEL");
         }
        break;
    case SCM_MODIFY:
         ret = modify_linkadminstate_in_linkHash_table(key, linkSetId, adminstate);
        if(ret == 0)
         {
          SCM_printf(SCM_CRITICAL,"\nlink hash table: ENTRY FOR LINK NOT FOUND IN HASH TABLE");
         }
        else
        {
         SCM_printf(SCM_INFO,"\nlink hash table: ADMINSTATE MODIFIED IN  LINKHASH TABLEL");
        }
        break;

 } 
 return ret;
}

int modify_linkadminstate_in_linkHash_table(U16 key, U16 linkSetId, U8 adminstate)
{
  link_information *prv;
  strcpy(g_parameter.function_string, "modify_linkadminstate_in_linkHash_table()");
  if(linkHashTbl[key] == NULL)
   {
     SCM_printf(SCM_CRITICAL,"\n\tSCM Link: hash table is empty");
     return 0;
   }
  else
   {
    prv = linkHashTbl[key];
    while(prv != NULL)
     {
      if(prv->linkSetId == linkSetId)
       {
        prv->adminState = adminstate;  
        memcpy(&prv->scmLinkAdminState, &g_linkConfigValue.scmLinkAdminState,  sizeof(OamScmLinkAdminState));
        return 1;
       }
      prv = prv->nxt;
     }
   }
    return 0;
}


void init_hash_table()
{
 strcpy(g_parameter.function_string, "init_hash_table()");
 U16 loop;
 for(loop = 0; loop<9; loop++)
   {
     linkHashTbl[loop] = NULL;
   } 
}

void get_key(U16* key, U16 linkId)
 {
   U16 const_dev;
   strcpy(g_parameter.function_string, "get_key()");
     

   const_dev = 9;
   *key = linkId % const_dev;           
}


int getAll_linkAdminstate_and_modify_in_peer_nwstack()
{
 int loop;
 U16 Length, ret_val;
 OamScmLinkAdminState *scmLinkAdminState=NULL;
 link_information *prv=NULL;
 nano_sleep.tv_sec = 0;
 nano_sleep.tv_nsec = 100;
 SCM_printf(SCM_INFO,"\n Update peer linkAdminState");

 for(loop = 0; loop<9; loop++)
   {
     if( linkHashTbl[loop] == NULL )
      {
       continue;
      }
     else
      {
       prv = (link_information*)linkHashTbl[loop];
       do
        {
         if(prv->adminState == 1)
         {
          SCM_printf(SCM_INFO,"\nupdating peer and self nwStack for 'LINK_ADMINSTATE_CONFIG'");
          scmLinkAdminState = (OamScmLinkAdminState*)malloc(sizeof(OamScmLinkAdminState));
          scmLinkAdminState->scmhdr.appid      = APP_ID_PEER_SCM; 
          scmLinkAdminState->scmhdr.operation  = SCM_MODIFY;
          scmLinkAdminState->scmhdr.opcode     = SCM_NWSTK_LINK_ADMIN_STATE_MODIFY;/*opcode changed for
                                                                                    distinguishing scm 
                                                                                    update cmd from oam 
                                                                                    cmd*/
          scmLinkAdminState->scmhdr.trid      = 0;
          scmLinkAdminState->scmhdr.spare     = 0;
          scmLinkAdminState->scmhdr.len       = sizeof(OamScmLinkAdminState); 
          scmLinkAdminState->linkId     = prv->link_value;
          scmLinkAdminState->linkSetId  = prv->linkSetId;
          scmLinkAdminState->adminState = prv->adminState;
          memcpy(&scmLinkAdminState->mtp2TimerConfig, &prv->scmLinkAdminState.mtp2TimerConfig, 
                 sizeof(Mtp2TimerConfig));
          SCM_printf(SCM_INFO,"\nlinkId: %d, linkSetId: %d, adminState: %d,",
                              scmLinkAdminState->linkId, scmLinkAdminState->linkSetId,
                              scmLinkAdminState->adminState);
        
         /*if(prv->instaceId == 65524)
           { 
             g_parameter.noOam_resp_flag = 1; 
             NwstkLinkAdminStateModify.linkId = scmLinkAdminState->linkId;
             NwstkLinkAdminStateModify.linkSetId = scmLinkAdminState->linkSetId;
             NwstkLinkAdminStateModify.adminState = scmLinkAdminState->adminState;
             Length  =  sizeof(ScmNwstkLinkAdminStateModify);
             memcpy(cmd_buff, &NwstkLinkAdminStateModify, Length);
             form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_ADMIN_STATE_MODIFY,
                               transaction_Id[SCM_NWSTK_LINK_ADMIN_STATE_MODIFY], Length);
             ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
           }*/
          
           Length  =  sizeof(OamScmLinkAdminState);
           ret_val = scm_dispatch_buffer((U8*)scmLinkAdminState, APP_ID_PEER_SCM, Length);
           free(scmLinkAdminState);
           scmLinkAdminState = NULL;
           if(ret_val == 0)
            {
              SCM_printf(SCM_CRITICAL," Link admin state config update sending failed");
              return 0;
            }
            pselect(0,NULL,NULL,NULL,&nano_sleep,NULL);
          }
            prv = prv->nxt;
          }while(prv != NULL);
        }
   }
 SCM_printf(SCM_INFO," All linkAdmingState config update successfully sent to peer");
 return 1;
 
}


int insert_value_in_hash_table(U16 key, U32 instanceId, U16 linkId, U16 linkSetId)
{
 link_information *prv=NULL;
 strcpy(g_parameter.function_string, "insert_value_in_hash_table()");
 if(linkHashTbl[key] == NULL)
   {
    SCM_printf(SCM_INFO," 1st scm link hash table entry Info: linkId: %d, linkSetId: %d, InstanceId: %d, key: %d",
    linkId, linkSetId, instanceId, key);
    linkHashTbl[key] = (link_information*)malloc(sizeof(link_information)); 
    linkHashTbl[key]->link_value    = linkId;
    linkHashTbl[key]->linkSetId = linkSetId;
    linkHashTbl[key]->adminState = 0; 
    linkHashTbl[key]->instaceId     = instanceId;
    linkHashTbl[key]->nxt           = NULL;
     
   }
 else
  {
   prv = linkHashTbl[key];
   while(prv->nxt != NULL)
    {
     prv = prv->nxt;       
    }
   SCM_printf(SCM_INFO,"scm link hash table entry Info: linkId: %d, linkSetId: %d, InstanceId: %d, key: %d",
    linkId, linkSetId, instanceId, key);
   prv->nxt = (link_information*)malloc(sizeof(link_information));
   prv->nxt->link_value    = linkId;
   prv->nxt->linkSetId = linkSetId;
   prv->nxt->adminState = 0;
   prv->nxt->instaceId     = instanceId;
   prv->nxt->nxt           = NULL;
      

  }
 return 1; 
}

int delete_value_from_hash_table(U16 key, U16 linkSetId)
{
  link_information *prv=NULL;
  link_information *next=NULL;
  strcpy(g_parameter.function_string, "delete_value_from_hash_table()");
 
  if(linkHashTbl[key] == NULL)
   {
     SCM_printf(SCM_CRITICAL,"\n\tDELETE FAILURE: SCM LINK HASH TABLE EMPTY");
     return 0;
   }
  else
   {
    /*element to be delete is the first element*/
     next = linkHashTbl[key];
     prv = next;
     if(prv->linkSetId == linkSetId)
         {
          prv = next->nxt;
          if(prv == NULL)/*no other entry in table correspond to this entry*/
            { 
             linkHashTbl[key] = NULL;
             return 1;
            }
          if(next != NULL)
          { 
           free(next);
           next=NULL;  
          }
          linkHashTbl[key] = prv;
          return 1;
        } 
       else
        {
         while((prv->nxt) != NULL)
         {
            next = prv->nxt;
            if(next->linkSetId == linkSetId)
             { 
              prv->nxt = next->nxt;
              if(next != NULL)
              {  
               free(next);
               next=NULL;  
              } 
              return 1;
             } 
            else
             {
              prv = prv->nxt;  
             } 
         }
        }
   }
    return 0;
}

int search_link_from_hash_table(U16 key, U16 linkSet, U8* cardFlag, U8 adminState)
{
  link_information *prv;
  strcpy(g_parameter.function_string, "search_link_from_hash_table()");
  if(linkHashTbl[key] == NULL)
   {
     SCM_printf(SCM_CRITICAL,"\n\tSCM Link: hash table is empty: key %d", key);
     return 0;
   }
  else
   {
    SCM_printf(SCM_DEBUG,"Search Entry in link hash table ln Info: key: %d, linkSetId: %d, adminState: %d",
    key, linkSet, adminState);
    prv = linkHashTbl[key];  
    while(prv != NULL)
     {
      if(prv->linkSetId == linkSet)
       {
        if((prv->adminState == 1) && (adminState == 1))
        {
         SCM_printf(SCM_INFO,"Entry found Link in unlock state");
         *cardFlag = CARD_LINK_UP;
         return 1;  
        } 
        if(prv->instaceId == 20002)
          {
           *cardFlag = SCM_STANDBY;
           SCM_printf(SCM_DEBUG,"Entry found link is meant for peer card ");
          }
         else 
         {
           SCM_printf(SCM_DEBUG,"Entry found link is meant for self card ");
           *cardFlag = SCM_ACTIVE; 
         }   
        return 1;
       }
      prv = prv->nxt;
     }
   }
    return 0;
} 

void delete_link_hashTbl()
{
  U16 key = 0;
  link_information *prv=NULL;
  link_information *next=NULL;
  strcpy(g_parameter.function_string, "delete_link_hashTbl()");
    /*element to be delete is the first element*/
    for(key =0; key<9; key++)
     { 
      if(linkHashTbl[key] == NULL)
       { 
        continue;
       } 
      next = linkHashTbl[key];
      prv = next;
      while((prv->nxt) != NULL)
       {
        next = prv->nxt;
        prv->nxt = next->nxt;
        if(next != NULL)
          free(next);
          next = NULL;
       }
        if(linkHashTbl[key] != NULL)
         {
          free(linkHashTbl[key]);
          linkHashTbl[key] = NULL;
         }
     }    
   return;
}

