#include <ansi-sccpstat.h>
#include <its_dsm.h>
extern HASH_Table _PC_Table;
extern ITS_BOOLEAN pauseFlag ;
extern ITS_BOOLEAN sspFlag;


#define RET_ENT   0xc1
#define SSNALLWD    0x01
#define SSNPROBH    0x02
ROUTE_Info *
        ROUTE_FindDest(ITS_UINT pointCode, ITS_OCTET ni, SS7_Family family);



/***************************************************************************
Purpose : To maintian the PC and SSN status .

Input     : PC and SSN 

Output   : None

return    : None
****************************************************************************/
int SCCP_SetGenConf(SCCP_StatInfo Sccp_Info)
{
//ITS_OCTET cnt=0;
ITS_UINT key;
  

    key=Sccp_Info.PC;	

    if (HASH_AddEntry(_PC_Table,RET_ENT,Sccp_Info.PC, (ITS_POINTER)&Sccp_Info) == ITS_SUCCESS)
       {
        SCCP_DEBUG(("SCCP_SetGenConf:DPC Status Entry"));
       }
return ITS_SUCCESS;
  }


/***************************************************************************
Purpose : To reteieve  the PC and SSN status .

Input     : PC and SSN 

Output   : None

return    : None
****************************************************************************/
int SCCP_GetGenConf(ITS_UINT PC,SCCP_StatInfo *Sccp_Info)
{ 
  SCCP_StatInfo SCCP_INFO;
  ITS_UINT key;
  SCCP_StatInfo *Sccp_Info_local=&SCCP_INFO;  
    key=PC;

      if (HASH_FindEntry(_PC_Table,RET_ENT,key,(ITS_POINTER *)&Sccp_Info_local) == ITS_SUCCESS)
        {
             Sccp_Info=Sccp_Info_local;

        }
	else
 	{ 
 	      Sccp_Info->PCFlag=ITS_FALSE;

 	}
  return ITS_SUCCESS;  

}


/***************************************************************************
Purpose : To reteieve  the PC and SSN status and return the event to App . 

Input     : PC and SSN 

Output   : None

return    : None
****************************************************************************/

#ifdef HASH_USE

int SCCP_EventProcforReturn( ITS_SCCP_IE* ies, int ieCount,
	                                           SCCP_StatInfo *Sccp_Info,ITS_BOOLEAN IsGtt,ITS_OCTET Reason)
{
 int length=0,i,ret=0;
 int cnt=0;
 int noptr=3; /*because of three mandatroy var*/
 ITS_INT  cdalen ,cpalen; 
 ITS_EVENT event;
 SCCP_ADDR *cda,*cpa;	
  SCCP_GetGenConf(Sccp_Info->PC,Sccp_Info);
 
 
//    if (Sccp_Info->PCFlag==ITS_FALSE||IsGtt==ITS_FALSE)
    {
    length+=sizeof(ITS_OCTET)+sizeof(ITS_CTXT)+sizeof(MTP3_HEADER);
             length+=noptr;
             length++;          /*due to one mandatory fixed parameter reason of return*/	 	
	         /* msg type + connection ref+mtp3 header */
	 
          for (i=0;i< ieCount;i++)
   	     {
   	             if (ies[i].param_id==SCCP_PRM_CALLED_PARTY_ADDR)
                    {
                        length+=ies[i].param_length+1;
                    }
	            else if (ies[i].param_id==SCCP_PRM_CALLING_PARTY_ADDR)
	             {
                        length+=ies[i].param_length+1;
	             }
	            else if (ies[i].param_id==SCCP_PRM_DATA)
	            {
                      length+=ies[i].param_length+1;/*len filling byte 1*/

	            }
                   else if(ies[i].param_id==SCCP_PRM_LONG_DATA)
                    {
                       length+=ies[i].param_length+2;/*length filling byte are 2*/
                    }
   	    }

	  ITS_EVENT_INIT(&event,ITS_SCCP_ANSI_SRC,length*sizeof(ITS_OCTET));
	  
                event.data[cnt++]=SCCP_MSG_NOTICE;
                event.data[cnt++]= 0x00;
                event.data[cnt++]= 0x00;
                event.data[cnt++]= 0x00;
                event.data[cnt++]= 0x00;
 
         for (i=0;i<ieCount;i++) 
           {
                if (ies[i].param_id==SCCP_PRM_ROUTING_LABEL)
                {
                    memcpy(&event.data[cnt],&ies[i].param_data.routingLabel,ies[i].param_length);
                    cnt+=ies[i].param_length;
                     
                }
           }
         for (i=0;i<ieCount;i++)
   	   {
              if (ies[i].param_id==SCCP_PRM_CALLED_PARTY_ADDR)
              {
                  cdalen=ies[i].param_length;
                  cda=&ies[i].param_data.calledPartyAddr; 
              }	
            else if (ies[i].param_id==SCCP_PRM_CALLING_PARTY_ADDR)
             {
                 cpalen=ies[i].param_length;
                 cpa=&ies[i].param_data.callingPartyAddr;
             }
        }
	event.data[cnt++]=Reason;	 
		 
        event.data[cnt++]=noptr ;
        event.data[cnt++]=noptr+cpalen;
        event.data[cnt++]=noptr+cdalen+cpalen;
  
        for (i=0;i<ieCount;i++)
   	   {
              if (ies[i].param_id==SCCP_PRM_CALLED_PARTY_ADDR)
               {
                  event.data[cnt++]=cpalen;
                  memcpy(&event.data[cnt],cpa->data,cpalen);
                  cnt+=cpalen;
               }
	       else if (ies[i].param_id==SCCP_PRM_CALLING_PARTY_ADDR)
	        {
	          event.data[cnt++]=cdalen;
	          memcpy(&event.data[cnt],cda->data,cdalen);
                  cnt+=cdalen;
                }
	       else if (ies[i].param_id==SCCP_PRM_DATA)
	        {
	          event.data[cnt++]=ies[i].param_length;
                 memcpy(&event.data[cnt],&ies[i].param_data,ies[i].param_length);
                 cnt+=ies[i].param_length;
               }
	       else if (ies[i].param_id==SCCP_PRM_LONG_DATA)
	        {
                 event.data[cnt++]=ies[i].param_length && 0x00FF;
	          event.data[cnt++]=(ies[i].param_length>8) && 0x00FF;		
	          memcpy(&event.data[cnt],&ies[i].param_data.longData.data,ies[i].param_length);		 
                  cnt=+ies[i].param_length;
	        }	
   	  } 


      ret=TRANSPORT_PutEvent(ITS_ISUP_SRC,&event);
     if(ret!=ITS_SUCCESS) 
      {
       ITS_EVENT_TERM(&event);
      }
   return ret;
   }
/* else
  {
     return (!ITS_SUCCESS);
  }*/
}
#endif

int
GetSsnStatus_DSM (ITS_UINT DPC, ITS_UINT OPC, ITS_OCTET ni,
		  ITS_BOOLEAN * pauseFlag, ITS_BOOLEAN * sspFlag,
		  ITS_OCTET Ssn)
{
  ITS_OCTET i = 0;
  SS7_Destination *dest = NULL;
  ROUTE_Info *destPtr = NULL, *rInfo = NULL;
  ITS_INT routeId = 0;
  ITS_UINT key;
  ITS_OCTET sio = 0;
  int ret = !ITS_SUCCESS;

  SCCP_DEBUG (("DPC->%d OPC->%d ni->%d SSN->ssn %d\n", DPC, OPC, ni, Ssn));
  destPtr = ROUTE_FindDest (OPC, ni, FAMILY_ANSI);
  if (destPtr == NULL)
    {
      *pauseFlag = ITS_TRUE;
      *sspFlag = ITS_TRUE;
      SCCP_DEBUG (("FILE :%s LINE %d destPtr is NULL", __FILE__, __LINE__));
      return (!ITS_SUCCESS);
    }

  for (rInfo = destPtr; rInfo != NULL; rInfo = rInfo->next)
    {
      SCCP_DEBUG (("SCCP_GetConfig:Style=%d\n", rInfo->basic.style));
      SCCP_DEBUG (("SCCP_GetConfig:basictype=%d\n", rInfo->basic.type));
      if (rInfo->basic.dpc == DPC && rInfo->basic.criteria.ssn == Ssn
      	  && rInfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
     	{
           	  SCCP_DEBUG (("SCCP_GetConfig:SSNFLAG=%d\n",
		                       rInfo->basic.criteria.ssnstatus));
       	  if (rInfo->basic.criteria.ssnstatus == SSNALLWD)
	        { 
    	      SCCP_DEBUG (("SCCP_GetConfig: SSN UP\n"));
	          *sspFlag = ITS_FALSE;
	        }
     	  else if (rInfo->basic.criteria.ssnstatus == SSNPROBH)
	        {
     	      SCCP_DEBUG (("SCCP_GetConfig: SSN DWN\n"));
	          *sspFlag = ITS_TRUE;
	        }
      	  sio = ni | MTP3_SIO_SCCP;
      	  ni = sio & MTP3_NIC_MASK;
       	  key = OPC | ((ni) << 24);
      	  SCCP_DEBUG (("SCCP_GetConfig: Key=%d\n", key));
      	  ret = DSM_Commit (DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC,
                      			(ITS_OCTET *) & key, sizeof (ITS_UINT), destPtr);
      	  if (ret != ITS_SUCCESS)
	        {
         	      SCCP_DEBUG (("SCCP_GetConfig: Fail\n"));
     	    }
	    }
    }


  dest = ROUTE_FindDestination (DPC, ni, FAMILY_ANSI);
/*Patch:Itika:14-jun-10:Fix in ANSI & ITU :Updated for ANSI SCCP  CL*/
  if (dest == NULL)
    {
      *pauseFlag = ITS_TRUE;
      *sspFlag = ITS_TRUE;
      SCCP_DEBUG (("FILE :%s LINE %d dest is NULL", __FILE__, __LINE__));
      return (!ITS_SUCCESS);
    }
/*End:Updated for ANSI SCCP  CL*/
  for (routeId = 0; routeId < dest->numEntries; routeId++)
    {
        if (dest->entries[routeId]->basic.dpc == DPC
	            && dest->entries[routeId]->basic.criteria.ssn == Ssn
              	  && dest->entries[routeId]->basic.style == ROUTE_DPC_SIO_SSN)
	       {
           	  SCCP_DEBUG (("SCCP_GetConfig:PCSTAUTS=%d\n", dest->status));
          	  if (dest->status == DESTINATION_AVAILABLE)
        	    {
            	      SCCP_DEBUG (("SCCP_GetConfig:PC UP \n"));
            	      *pauseFlag = ITS_FALSE;
	            }
         	  else if (dest->status == DESTINATION_UNAVAILABLE)
        	    {
            	      SCCP_DEBUG (("SCCP__getConfig:PC DWN \n"));
            	      *pauseFlag = ITS_TRUE;
	            }
	       }
    }

}

/******************************************************************
Purpose : To reteieve  the PC and SSN status and return the event to App .

Input     :ITS_UINT       DPC
           ITS_UINT       OPC
           ITS_OCTET      ni
           ITS_BOOLEAN    *pauseFlag
           ITS_BOOLEAN    *sspFlag
           ITS_OCTET      SSN 

Output    : None

return    : pauseFlag
            sspFlag

*******************************************************************/
int
SCCP_EventProcforReturn (ITS_SCCP_IE * ies, int ieCount,
			 SCCP_StatInfo * Sccp_Info, ITS_BOOLEAN IsGtt,
			 ITS_OCTET Reason)
{
  int length = 0, i, ret = 0;
  MTP3_HEADER *mtp3=NULL;
  int cnt = 0;
  int noptr = 3;		/*because of three mandatroy var */
  ITS_INT cdalen, cpalen;
  ITS_EVENT event;
  SCCP_ADDR *cdp, *clp;
  ITS_OCTET ROPT_FLAG = 0, Tmp;
  ITS_UINT j = 0;
  ITS_UINT pc;
  ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32] = { '\0', };
  ITS_USHORT gttLen = 0;

  SCCP_DEBUG (("ANSI:Sending N-Notice Indication\n"));
  for (j = 0; j < ieCount; j++)
    {
      if (ies[j].param_id == SCCP_PRM_PROTOCOL_CLASS)
        	{
             	  SCCP_DEBUG (("INSIDE SCCP_PRM_PROTOCOL_CLASS %d\n",
           		       ies[j].param_data.userData.data[0]));
            	  Tmp = ies[j].param_data.userData.data[0];
            	  if ((Tmp & 0x80)==0x80)
           	    ROPT_FLAG = 1;
            	  else
           	    ROPT_FLAG = 0;
	        }
    }
  if (ROPT_FLAG)
    {
       SCCP_DEBUG (("Sending N-Notice Indication\n"));
       length += sizeof (ITS_OCTET) + sizeof (ITS_CTXT) + sizeof (MTP3_HEADER);
       length += noptr;
       length++;			/*due to one mandatory fixed parameter reason of return */

      /* msg type + connection ref+mtp3 header */

      for (i = 0; i < ieCount; i++)
    	{
	      if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
	      {
            SCCP_ERROR(("SCRCDeliverByGTT:  iCalled Party len=%d\n",ies[i].param_length));
	         length += ies[i].param_length + 1;
	      }
    	  else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
	      {
	         length += ies[i].param_length + 1;
	      }
   	   else if (ies[i].param_id == SCCP_PRM_DATA)
	      {
	        length += ies[i].param_length + 1;	/*len filling byte 1 */
  	    }
	     else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
	      {
	         length += ies[i].param_length + 2;	/*length filling byte are 2 */
	      }
	   } 

      ITS_EVENT_INIT (&event, ITS_SCCP_ANSI_SRC, length * sizeof (ITS_OCTET));

      event.data[cnt++] = SCCP_MSG_NOTICE;
      event.data[cnt++] = 0x00;
      event.data[cnt++] = 0x00;
      event.data[cnt++] = 0x00;
      event.data[cnt++] = 0x00;

    for (i = 0; i < ieCount; i++)
	  {
	    if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
	     {
          SCCP_DEBUG (("mtp3=%x\n", mtp3));
	        mtp3 = &ies[i].param_data.routingLabel;
          SCCP_DEBUG (("mtp3=%x\n", mtp3));
          SCCP_DEBUG (("mtp3 sio =%x\n", mtp3->sio));
	        memcpy (&event.data[cnt], &ies[i].param_data.routingLabel,
		       ies[i].param_length);
	        cnt += ies[i].param_length;
	    }
	  }
    if(mtp3==NULL)
    {
       return (!ITS_SUCCESS);
    }    

    for (i = 0; i < ieCount; i++)
	  {
	    if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
	     {
	        cdalen = ies[i].param_length;
	        cdp = &ies[i].param_data.calledPartyAddr;
	     }
	    else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
	     {
	        cpalen = ies[i].param_length;
	        clp = &ies[i].param_data.callingPartyAddr;
	     }
	   }
      /* Decode Called Party address into component parts  */
     if (SCCP_DecodeAddr (cdp, &addrInd, &pc, &ssn, gttInfo, &gttLen) != ITS_SUCCESS)
	    {
	      SCCP_ERROR (("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));
	      return (ITS_EINVALIDARGS);
    	}
      SCCP_DEBUG (("SSN=%d\n", ssn));
      SCCP_DEBUG (("SCRCDeliverRemote: RoutingLabel: SIO %02x OPC %08x "
		   "DPC %08x SLS %02x\n",
		   mtp3->sio,
		   MTP3_RL_GET_OPC_VALUE (mtp3->label),
		   MTP3_RL_GET_DPC_VALUE (mtp3->label),
		   MTP3_RL_GET_SLS (mtp3->label)));

       SCCP_DEBUG (("ROPT_FLAG::::%d||||||||||Network Indicator ==%d\n",
		   ROPT_FLAG, (mtp3->sio & 0xc0)));

       GetSsnStatus_DSM (MTP3_RL_GET_DPC_VALUE (mtp3->label),
			 MTP3_RL_GET_OPC_VALUE (mtp3->label),
			 (mtp3->sio & 0xc0), &pauseFlag, &sspFlag, ssn);
       SCCP_DEBUG (("pauseFlag=%d sspFlag=%d\n", pauseFlag, sspFlag));
       event.data[cnt++] = Reason;

       event.data[cnt++] = noptr;
       event.data[cnt++] = noptr + cpalen;
       event.data[cnt++] = noptr + cdalen + cpalen;

      for (i = 0; i < ieCount; i++)
	     {
        	 if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
	         {
      	      event.data[cnt++] = cpalen;
      	      memcpy (&event.data[cnt], clp->data, cpalen);
	            cnt += cpalen;
	         }
      	  else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
	         {
       	      event.data[cnt++] = cdalen;
	            memcpy (&event.data[cnt], cdp->data, cdalen);
              cnt += cdalen;
	         }
      	  else if (ies[i].param_id == SCCP_PRM_DATA)
	         {
       	      event.data[cnt++] = ies[i].param_length;
	            memcpy (&event.data[cnt], &ies[i].param_data,
    		      ies[i].param_length);
	            cnt += ies[i].param_length;
	         }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
	        {
      	      event.data[cnt++] = ies[i].param_length && 0x00FF;
	            event.data[cnt++] = (ies[i].param_length > 8) && 0x00FF;
       	      memcpy (&event.data[cnt], &ies[i].param_data.longData.data,
		          ies[i].param_length);
       	      cnt = +ies[i].param_length;
	        }
	      }


      ret = TRANSPORT_PutEvent (ITS_ISUP_SRC, &event);
      if (ret != ITS_SUCCESS)
      {
	       ITS_EVENT_TERM (&event);
      }
      return ret;
    }

  else
    SCCP_DEBUG (("RETURN OPTION IS NOT PRESENT\n"));
}


/******************************************************************
Purpose : To set the Congestion level of SSN after receving SSC 

Input     :ITS_UINT       DPC
           ITS_UINT       OPC
           ITS_OCTET      ni
           ITS_OCTET      SSN
           ITS_OCTET      ssn_cong_level;

Output    : None

return    : None

*******************************************************************/
int
set_ssn_cong (ITS_UINT OPC, ITS_UINT DPC, ITS_OCTET Ssn,
	      ITS_OCTET cong_level, ITS_OCTET ni)
{
  ROUTE_Info *destPtr = NULL, *rInfo = NULL;
  ITS_INT routeId = 0;
  ITS_UINT key = 0, ret = 0;
  ITS_OCTET sio = 0;

  SCCP_DEBUG (("Setting the Congestion level for Ssn Start\n"));

  destPtr = ROUTE_FindDest (OPC, ni, FAMILY_ANSI);
  if (destPtr == NULL)
    {
      SCCP_DEBUG (("SCCP set_ssn_cong : Destination not Found\n"));
      return (!ITS_SUCCESS);
    }

  sio = ni | MTP3_SIO_SCCP;
  ni = sio & MTP3_NIC_MASK;

  for (rInfo = destPtr; rInfo != NULL; rInfo = rInfo->next)
    {
      if (rInfo->basic.dpc == DPC && rInfo->basic.criteria.ssn == Ssn)
      	{
           	  rInfo->basic.criteria.ssnstatus = cong_level;
          	  key = OPC | ((ni) << 24);
          	  SCCP_CRITICAL (("SCCP_SetConfig: Key=%d\n", key));
           	  ret = DSM_Commit (DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC, (ITS_OCTET *) & key, sizeof (ITS_UINT), destPtr);
          	  if (ret != ITS_SUCCESS)
              {
             	    SCCP_CRITICAL (("SCCP_SetSSNCONG LEVEL : Fail\n"));
              }
          	  else
              {
            	    SCCP_CRITICAL (("SCCP_SetSSNCONG LEVEL: SUCESS\n"));
              }
               	  SCCP_DEBUG (("SCCP set_ssn_cong:SSN=%d\n",
                		       rInfo->basic.criteria.ssn));
                  SCCP_DEBUG (("SCCP set_ssn_cong:SSN Status=%d\n",
         		       rInfo->basic.criteria.ssnstatus));
               	  SCCP_DEBUG (("SCCP set_ssn_cong:SSN Cong_level=%d\n",
           		       rInfo->basic.criteria.ssn_cong_level));
	    }
   }
  return (ITS_SUCCESS);
}



/******************************************************************
                                End 
*******************************************************************/
/*IN MSC THIS DEF AT BSSAP bssap-msc.cpp*/


ROUTE_Info *
ROUTE_FindDest(ITS_UINT pointCode, ITS_OCTET ni, SS7_Family family)
{
            ITS_INT key;
      //      SS7_Destination *ent;
           ROUTE_Info *ent = NULL;
            int error;
           ITS_OCTET sio=0;

            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;
            /* work out the pkey */
            key = pointCode | ((ni ) << 24) ;
      //       BSSAP_DEBUG(("BSSAP_getConfig:key=%d\n", key));

            ent = NULL;

            ent = (ROUTE_Info *)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_ANSI_SCCP_LPC,
                                 (ITS_OCTET *)&key,
                                 sizeof(ITS_INT),
                                 &error);


            if (error != ITS_SUCCESS)
            {
             SCCP_DEBUG(("SCCP_getConfig:PC Not Found\n"));
                return (NULL);
            }

            return (ent);
}

