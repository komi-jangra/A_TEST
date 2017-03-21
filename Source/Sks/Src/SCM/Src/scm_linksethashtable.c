#include "scm_localhashdef.h"
#include "scm_encaps.h"



int  checkAndUpdate_linksetValue_in_linksetHashTable(U8 operation, U16 linkSetId, U8 adminstate)
{
 U16 key, ret;
 strcpy(g_parameter.function_string, "checkAndUpdate_linksetValue_in_linksetHashTable()");

     get_key(&key, linkSetId);
 switch(operation)
 {
   case SCM_ADD:
        ret = insert_linksetvalue_in_hash_table(key, linkSetId);
        if(ret == 0)
         { 
          SCM_printf(SCM_CRITICAL,"\nlinkset hash table: INSERTION FAILURE");
         }
        else
         {
          SCM_printf(SCM_INFO,"\nlinkset hash table: INSERTION SUCCESSFUL");
         }
       break;
   case SCM_DELETE:
        ret = delete_linksetvalue_from_hash_table(key, linkSetId);
        if(ret == 0)
         { 
          SCM_printf(SCM_CRITICAL,"\nlinkset hash table: DELETE FAILURE");
         }
        else
         {
          SCM_printf(SCM_INFO,"\nlinkset hash table: DELETE SUCCESSFUL");
         } 
        break;
   case SCM_GET: 
        ret = search_linkset_from_hash_table(key, linkSetId);
        if(ret == 0)
         { 
          SCM_printf(SCM_CRITICAL,"\nlinkset hash table: ENTRY NOT FOUND IN LINKSET HASH TABLE");
         }
        else
         {
          SCM_printf(SCM_INFO,"\nlinkset hash table: ENTRY FOUND IN LINKSETHASH TABLEL");
         }
        break;
    case SCM_MODIFY:
         ret = modify_linksetadminstate_in_linksetHash_table(key, linkSetId, adminstate);
        if(ret == 0)
         {
          SCM_printf(SCM_CRITICAL,"\nlinkset hash table: ENTRY FOR LINKSET NOT FOUND IN HASH TABLE");
         }
        else
        {
         SCM_printf(SCM_INFO,"\nlinkset hash table: ADMINSTATE MODIFIED IN  LINKSETHASH TABLEL");
        }
        break;

 } 
 return ret;
}

int modify_linksetadminstate_in_linksetHash_table(U16 key, U16 linkSetId, U8 adminstate)
{
  linkset_information *prv;
  strcpy(g_parameter.function_string, "modify_linksetadminstate_in_linksetHash_table()");
  if(linksetHashTbl[key] == NULL)
   {
     SCM_printf(SCM_CRITICAL,"\n\tSCM Linkset: hash table is empty");
     return 0;
   }
  else
   {
    prv = linksetHashTbl[key];
    while(prv != NULL)
     {
      if(prv->linkSetId == linkSetId)
       {
        prv->adminState = adminstate;   
        return 1;
       }
      prv = prv->nxt;
     }
   }
    return 0;
}


void init_linkset_hash_table()
{
 strcpy(g_parameter.function_string, "init_linkset_hash_table()");
 U16 loop;
 for(loop = 0; loop<9; loop++)
   {
     linksetHashTbl[loop] = NULL;
   } 
}


/*int getAll_linkset_and_add_to_peerhash_table()
{
 int loop;
 U16 Length, ret_val;
 OamScmLinkSetConfig *scmLinkSetConfig;
 linkset_information *prv;
 SCM_printf(SCM_INFO,"\n Update peer linksetAdminState");

 for(loop = 0; loop<9; loop++)
   {
     if( linksetHashTbl[loop] == NULL )
      {
       continue;
      }
     else
      {
       prv = (linkset_information*)linksetHashTbl[loop];
       do
        {
         if(prv->adminState == 1)
         {
          SCM_printf(SCM_INFO,"\nupdating peer and self nwStack for 'LINKSET_ADMINSTATE_CONFIG'");
          scmLinkSetConfig = (OamScmLinkSetConfig*)malloc(sizeof(OamScmLinkSetConfig));
          scmLinkSetConfig->scmhdr.appid      = APP_ID_PEER_SCM; 
          scmLinkSetConfig->scmhdr.operation  = SCM_MODIFY;
          scmLinkSetConfig->scmhdr.opcode     = SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY;
          scmLinkSetConfig->scmhdr.trid      = 0;
          scmLinkSetConfig->scmhdr.spare     = 0;
          scmLinkSetConfig->scmhdr.len       = sizeof(OamScmLinkSetConfig); 
          scmLinkSetConfig->linkSetId  = prv->linkSetId;
          scmLinkSetConfig->adminState = prv->adminState;
          SCM_printf(SCM_INFO,"linkSetId: %d, adminState: %d,",
                              scmLinkSetConfig->linkSetId,
                              scmLinkSetConfig->adminState);
        
          
           Length  =  sizeof(OamScmLinkSetConfig);
           ret_val = scm_dispatch_buffer((U8*)scmLinkSetConfig, APP_ID_PEER_SCM, Length);
           free(scmLinkSetConfig);
           if(ret_val == 0)
            {
              SCM_printf(SCM_CRITICAL," Linkset admin state config update sending failed");
              return 0;
            }
          }
            prv = prv->nxt;
          }while(prv != NULL);
        }
   }
 SCM_printf(SCM_INFO," All linksetAdmingState config update successfully sent to peer");
 return 1;
 
 
}*/

int getAll_linksetAdminstate_and_modify_in_peer_nwstack()
{
 int loop;
 U16 Length, ret_val;
 OamScmLinkSetAdminState *scmLinkSetAdminState=NULL;
 linkset_information *prv=NULL;
 SCM_printf(SCM_INFO,"\n Update peer linksetAdminState");

 for(loop = 0; loop<9; loop++)
   {
     if( linksetHashTbl[loop] == NULL )
      {
       continue;
      }
     else
      {
       prv = (linkset_information*)linksetHashTbl[loop];
       do
        {
          SCM_printf(SCM_INFO,"\nupdating peer scm & nwstk for 'LINKSET & LINKSET_ADMINSTATE_CONFIG'");
          scmLinkSetAdminState = (OamScmLinkSetAdminState*)malloc(sizeof(OamScmLinkSetAdminState));
          scmLinkSetAdminState->scmhdr.appid      = APP_ID_PEER_SCM; 
          scmLinkSetAdminState->scmhdr.operation  = SCM_MODIFY;
          scmLinkSetAdminState->scmhdr.opcode     = SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY;/*opcode changed for
                                                                                    distinguishing scm 
                                                                                    update cmd from oam 
                                                                                    cmd*/
          scmLinkSetAdminState->scmhdr.trid      = 0;
          scmLinkSetAdminState->scmhdr.spare     = 0;
          scmLinkSetAdminState->scmhdr.len       = sizeof(OamScmLinkSetAdminState); 
          scmLinkSetAdminState->linkSetId  = prv->linkSetId;
          scmLinkSetAdminState->adminState = prv->adminState;
          SCM_printf(SCM_INFO,"linkSetId: %d, adminState: %d,",
                              scmLinkSetAdminState->linkSetId,
                              scmLinkSetAdminState->adminState);
        
           Length  =  sizeof(OamScmLinkSetAdminState);
           ret_val = scm_dispatch_buffer((U8*)scmLinkSetAdminState, APP_ID_PEER_SCM, Length);
           free(scmLinkSetAdminState);
           scmLinkSetAdminState=NULL;
           if(ret_val == 0)
            {
              SCM_printf(SCM_CRITICAL," Linkset admin state config update sending failed");
              return 0;
            }
            prv = prv->nxt;
          }while(prv != NULL);
        }
   }
 SCM_printf(SCM_INFO," All linksetAdmingState config update successfully sent to peer");
 return 1;
 
}


int insert_linksetvalue_in_hash_table(U16 key, U16 linkSetId)
{
 linkset_information *prv=NULL;
 strcpy(g_parameter.function_string, "insert_linksetvalue_in_hash_table()");
 if(linksetHashTbl[key] == NULL)
   {
    linksetHashTbl[key] = (linkset_information*)malloc(sizeof(linkset_information)); 
    linksetHashTbl[key]->linkSetId = linkSetId;
    linksetHashTbl[key]->adminState = 0; 
    linksetHashTbl[key]->nxt           = NULL;
     
   }
 else
  {
   prv = linksetHashTbl[key];
   while(prv->nxt != NULL)
    {
     prv = prv->nxt;       
    }
   prv->nxt = (linkset_information*)malloc(sizeof(linkset_information));
   prv->nxt->linkSetId = linkSetId;
   prv->nxt->adminState = 0;
   prv->nxt->nxt           = NULL;
      

  }
 return 1; 
}

int delete_linksetvalue_from_hash_table(U16 key, U16 linkSetId)
{
  linkset_information *prv=NULL;
  linkset_information *next=NULL;
  strcpy(g_parameter.function_string, "delete_linksetvalue_from_hash_table()");
 
  if(linksetHashTbl[key] == NULL)
   {
     SCM_printf(SCM_CRITICAL,"\n\tDELETE FAILURE: SCM LINKSET HASH TABLE EMPTY");
     return 0;
   }
  else
   {
    /*element to be delete is the first element*/
     next = linksetHashTbl[key];
     prv = next;
     if(prv->linkSetId == linkSetId)
         {
          prv = next->nxt;
          if(prv == NULL)/*no other entry in table correspond to this entry*/
            { 
             linksetHashTbl[key] = NULL;
             return 1;
            }
          if(next != NULL)
          { 
           free(next);
           next=NULL;   
          } 
          linksetHashTbl[key] = prv;
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

int search_linkset_from_hash_table(U16 key, U16 linkSet)
{
  linkset_information *prv=NULL;
  strcpy(g_parameter.function_string, "search_linkset_from_hash_table()");
  if(linksetHashTbl[key] == NULL)
   {
     SCM_printf(SCM_CRITICAL,"\n\tSCM Linkset: hash table is empty");
     return 0;
   }
  else
   {
    prv = linksetHashTbl[key];  
    while(prv != NULL)
     {
      if(prv->linkSetId == linkSet)
       {
        return 1;
       }
      prv = prv->nxt;
     }
   }
    return 0;
} 

void delete_linkset_hashTbl()
{
  U16 key = 0;
  linkset_information *prv=NULL;
  linkset_information *next=NULL;
  strcpy(g_parameter.function_string, "delete_linkset_hashTbl()");
    /*element to be delete is the first element*/
    for(key =0; key<9; key++)
     { 
      if(linksetHashTbl[key] == NULL)
       { 
        continue;
       } 
      next = linksetHashTbl[key];
      prv = next;
      while((prv->nxt) != NULL)
       {
        next = prv->nxt;
        prv->nxt = next->nxt;
        if(next != NULL)
          free(next);
          next = NULL;
       }
        if(linksetHashTbl[key] != NULL)
         {
          free(linksetHashTbl[key]);
          linksetHashTbl[key] = NULL;
         }
     }    
   return;
}

