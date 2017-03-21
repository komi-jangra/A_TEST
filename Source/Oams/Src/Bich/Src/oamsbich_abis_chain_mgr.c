/** ts=3 ******************************************************* File Header **
FILE NAME         :  oamsbich_abis_chain_mgr.c
PURPOSE           :  Maintains the functionality to create and maintain Abis E1 List and BIC Tree
PROJECT           :  BSS CS2.2
SUBSYSTEM         :  OAMS
AUTHOR            :  Aricent
CSCI ID           :
VERSION           :  V0.1
 *******************************************************************************/

#include <oamsbich_abis_chain_mgr.h>
#include <oamsbich_proc_hdlr.h>

/*Global Data Structure */
OamsList gabisE1List;

/********************************* Function  Header********************************
Function Name      :allocateAbisE1Node
Parameters         :e1Id,bicTei
Return type        :AbisE1Node*
Purpose            :This functions allocates an Abis E1 Node and adds it to the abis chain
Other Note         :
 ************************************************************************************/
AbisE1Node *allocateAbisE1Node(I_U32 e1Id)
{   
   AbisE1Node *ptrE1Node = NULL;
  
   LOG_PRINT(INFO,"\n Entering allocateAbisE1Node function :[e1Id %d ]",e1Id);
   ptrE1Node = (AbisE1Node*)MALLOC(sizeof(AbisE1Node));
   /*HA change */
   LOG_PRINT(INFO,"Allocating AbisE1Node %p",ptrE1Node);
   if (NULL == ptrE1Node)
   {
      /* LOG error */
      LOG_PRINT(INFO,"\n Memory allocation failed for abis E1 node"); 
      return NULL;
   }
   ptrE1Node->e1Id = e1Id;
   INIT_OAMS_TS_LIST(&(ptrE1Node->abisChainList));
   LOG_PRINT(INFO,"\n Leaving allocateAbisE1Node function ::[e1Id %d]",e1Id);
   return ptrE1Node;
}

/********************************* Function  Header********************************
Function Name      :allocateTsNode
Parameters         :timeSlot,bicTei
Return type        :AbisE1TsNode*
Purpose            :This functions allocates a TimeSlot Node and adds it to the abis chain
Other Note         :
 ************************************************************************************/
AbisE1TsNode *allocateTsNode(I_U32 timeSlot,I_U32 bicTei)
{
   AbisE1TsNode *ptrTsNode = NULL;
   LOG_PRINT(INFO,"\n Entering allocateTsNode function :[timeSlot %d]",timeSlot);
   ptrTsNode = (AbisE1TsNode*)MALLOC(sizeof(AbisE1TsNode));
   /*HA change */
   LOG_PRINT(INFO,"Allocating AbisE1TsNode %p",ptrTsNode);
   if (NULL == ptrTsNode)
   {
      /* LOG error */
      LOG_PRINT(INFO,"\n Memory allocation failed for TS node"); 
      return NULL;
   }
   ptrTsNode->timeSlot =(I_U8)timeSlot;
   ptrTsNode->tei =  (I_U8)bicTei;
   ptrTsNode->status = ABIS_E1_STATUS_NO_BIC;
   INIT_OAMS_TREE(&(ptrTsNode->bicTreeRoot));
   LOG_PRINT(INFO,"\n Leaving allocateTsNode function ::[timeSlot %d]",timeSlot);
   return ptrTsNode;
}

/********************************* Function  Header********************************
Function Name      :getE1IdFromTei
Parameters         :abisChainList,bicTei
Return type        :I_S32
Purpose            :This functions returns the E1 id based on the tei
Other Note         :
 ************************************************************************************/
I_S32 getE1IdFromTei(OamsList *abisChainList,BicTei tei)
{
	OamsList     *ptr          = NULL;
   OamsList     *tmpPtr       = NULL;
   OamsList     *head         = NULL;
	OamsTsList	 *tsPtr	   	= NULL;
	OamsTsList	 *tstmpPtr  	= NULL;
	AbisE1TsNode *abisE1TsNode	= NULL;
	AbisE1Node	 *ptrE1Node    = NULL;
	
	if(IS_OAMS_LIST_EMPTY(abisChainList))
   {
      LOG_PRINT(INFO,"\n No abis E1 node in the list"); 
      return (-1);
   }
   head = abisChainList;
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,head)
   {
      if(ptr != NULL)
      {
			ptrE1Node = OAMS_LIST_ENTRY(ptr,AbisE1Node,e1List);
			if(IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
			{
				continue;
			}
			OAMS_TS_LIST_FOR_EACH(tsPtr, tstmpPtr, &(ptrE1Node->abisChainList))
			{
				if(tsPtr != NULL)
				{
					abisE1TsNode = OAMS_TS_LIST_ENTRY(tsPtr,AbisE1TsNode,tsList);
					if(abisE1TsNode->tei == tei)
					{
						ptrE1Node = OAMS_LIST_ENTRY(ptr,AbisE1Node,e1List);
						LOG_PRINT(INFO,"\n E1 Id found for tei %d is %d ",abisE1TsNode->tei,ptrE1Node->e1Id);	
						return (ptrE1Node->e1Id);
					}
				}
			}
		}
	}
	LOG_PRINT(INFO,"\n E1 Id not found for tei %d ",tei);
	return (-1);
}
/********************************* Function  Header********************************
Function Name      :initializeChain
Parameters         :None
Return type        :void
Purpose            :This functions initialize the abis chain
Other Note         :
 ************************************************************************************/	
void initializeChain()
{
	 /*the next of list head points to itself*/
   INIT_OAMS_LIST(&gabisE1List);
}

/********************************* Function  Header********************************
Function Name     :searchTsNodeOnTimeSlot
Parameters        :e1Id,timeSlot
Return type       :AbisE1TsNode *
Purpose           :This function search a AbisE1TsNode from E1Id and timeslot
Other Note        :
 ************************************************************************************/
AbisE1TsNode *searchTsNodeOnTimeSlot(I_U8 e1Id,I_U8 timeSlot)
{
   AbisE1Node     *ptrE1Node   	   = NULL;
   AbisE1TsNode	*abisE1TsNode	   = NULL;
   OamsTsList     *ptr       	      = NULL;
   OamsTsList     *tmpPtr    	      = NULL;

   LOG_PRINT(INFO,"\n Entering searchTsNode function for e1Id %d and Ts Id %d ",e1Id,timeSlot);

   if(IS_OAMS_TS_LIST_EMPTY(&gabisE1List))
   {
      LOG_PRINT(INFO,"\n No abis E1 node in the list"); 
      return NULL;
   }
   ptrE1Node = searchAbisE1Id(&gabisE1List,e1Id);
   if(ptrE1Node != NULL)
   {
   	OAMS_LIST_FOR_EACH(ptr,tmpPtr,&(ptrE1Node->abisChainList))
   	{
     		if(ptr != NULL)
        	{
         	/* use macro OAMS_LIST_ENTRY to find abisE1TsNode*  - compare TimeSlot*/
         	abisE1TsNode = OAMS_LIST_ENTRY(ptr,AbisE1TsNode,tsList);
       		/*if abisE1TsNode node with matching timeSlot found then return the abisE1TsNode*/
   		  	if(abisE1TsNode->timeSlot == timeSlot)
         	{
			   	LOG_PRINT(INFO,"\n Matching TimeSlot found in the list with e1 Id %d",e1Id);
	            /* return abisE1TsNode*   */
        	    	return (abisE1TsNode);
         	}
      	}
   	}
   }
   /*if abis E1 node with matching E1Id not found then return NULL*/
   return NULL;
}
/********************************* Function  Header********************************
Function Name     :searchTsNodeOnTei
Parameters        :e1Id,bicTei
Return type       :AbisE1TsNode *
Purpose           :This function search a AbisE1TsNode from E1Id and tei
Other Note        :
 ************************************************************************************/
AbisE1TsNode *searchTsNodeOnTei(I_U8 e1Id,I_U8 bicTei)
{
   AbisE1Node     *ptrE1Node       	= NULL;
   AbisE1TsNode	*abisE1TsNode	 	= NULL;
   OamsTsList     *ptr       		   = NULL;
   OamsTsList     *tmpPtr    		   = NULL;

   /* use macros IS_OAMS_LIST_EMPTY and BICH_LIST_FOR_EACH to search */
   LOG_PRINT(INFO,"\n Entering searchTsNode function for e1Id %d and tei %d ",e1Id,bicTei);

   if(IS_OAMS_TS_LIST_EMPTY(&gabisE1List))
   {
      LOG_PRINT(INFO,"\n No abis E1 node in the list"); 
      return NULL;
   }

	ptrE1Node = searchAbisE1Id(&gabisE1List,e1Id);
	if(ptrE1Node != NULL)
	{
		if(IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
      {
	      LOG_PRINT(INFO,"In function: searchTsNodeOnTei: &(ptrE1Node->abisChainList) is empty");
      }
  		OAMS_LIST_FOR_EACH(ptr,tmpPtr,&(ptrE1Node->abisChainList))
  		{
   		if(ptr != NULL)
   		{
            /* use macro OAMS_LIST_ENTRY to find abisE1TsNode*  - compare TimeSlot*/
      		abisE1TsNode = OAMS_LIST_ENTRY(ptr,AbisE1TsNode,tsList);
				/*if abisE1TsNode node with matching timeSlot found then return the abisE1TsNode*/
				LOG_PRINT(INFO,"AbisE1TsNode->tei %d ",abisE1TsNode->tei);
         	if(abisE1TsNode->tei == bicTei)
         	{
				   LOG_PRINT(INFO,"\n Matching Tei found in the list with e1 Id %d",e1Id);
            	/* return abisE1TsNode*   */
            	return (abisE1TsNode);
         	}
      	}
   	}
   /*if abis E1 node with matching E1Id not found then return NULL*/
	}
   else
	{
		LOG_PRINT(INFO,"searchTsNodeOnTei:searchAbisE1Id returns NULL");
	}
   return NULL;
}


/* Start , BB , CS40 E1 Usage Type Changes 19-05-09::17:22 */ 
/********************************* Function  Header******************************** 
Function Name     :deleteAbisChain 
Parameters        :I_U32 e1Id 
Return type       :void 
Purpose           :this function delete an abis chain for the given E1 Num 
Other Note        : 
************************************************************************************/ 
void deleteAbisChain(I_PVoid sndPtr) 
{ 
  AbisE1Node        *ptrE1Node    = NULL; 
  I_U32                   e1Id                  = ZERO; 
  OamsTsList        *ptr                = NULL; 
  OamsTsList            *tmpPtr         = NULL; 
  AbisE1TsNode        *rootTree       = NULL; 
        
  LOG_PRINT(INFO,"\n Entering deleteAbisChain function"); 
  
  e1Id= ((OamsCfgBichDeleteAbisE1 *)sndPtr)->e1Id ;    
  
  /*search for the e1 id ..if  found then*/    
  ptrE1Node = searchAbisE1Id(&gabisE1List,e1Id); 
  if(ptrE1Node != NULL) { 
    /*the e1 id is already added to the list so remove */ 
    /*all the ts for the e1 id and the bic's connected with it*/ 
    if(!IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList))) { 
      /*traverse through all the ts for the e1 id*/ 
      LOG_PRINT(INFO,"\n deleteAbisChain:Bic Ts List is not empty"); 
      OAMS_TS_LIST_FOR_EACH(ptr, tmpPtr, &(ptrE1Node->abisChainList)) { 
        /*if bic is connected with the ts then delete it */ 
        rootTree = OAMS_LIST_ENTRY(ptr,AbisE1TsNode,tsList); 
        if(!IS_OAMS_TREE_EMPTY(&(rootTree)->bicTreeRoot)) { 
          LOG_PRINT(INFO,"\n deleteAbisChain:Bic present in the tree for timeslot %d ",rootTree->timeSlot); 
          OAMS_TREE_DEL_N_FREE_CHILD_LIST(&(rootTree)->bicTreeRoot, BicNode, bicTree,FREE); 
          LOG_PRINT(INFO,"Freeing AbisE1TsNode %p",rootTree);
        } 
        else { 
          LOG_PRINT(INFO,"\n deleteAbisChain:No bic present in the tree for timeslot %d ",rootTree->timeSlot); 
        } 
        INIT_OAMS_TREE(&(rootTree->bicTreeRoot)); 
        OAMS_TS_LIST_DEL_N_FREE(ptr, AbisE1TsNode, tsList, FREE); 
      } 
      if(IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList))) { 
        LOG_PRINT(INFO,"\n deleteAbisChain:Initialize the TS List for e1 Id %d ",e1Id); 
        INIT_OAMS_TS_LIST(&(ptrE1Node->abisChainList)); 
      } 
    } 
    else { 
      LOG_PRINT(INFO,"\n deleteAbisChain:Bic Ts list empty"); 
    } 
  } 
  freeE1Node(e1Id);
} 
/* End , BB , CS40 E1 Usage Type Changes 19-05-09::17:22 */ 

/********************************* Function  Header********************************
Function Name     :delTsNodeFromAbisChain
Parameters        :I_PVoid
Return type       :void
Purpose           :this function delete Ts Node in Abis Chain
Other Note        :
 ************************************************************************************/
I_Void delTsNodeFromAbisChain(OamsBichContext *rcvPtr)
{
  AbisE1Node            *ptrE1Node    = NULL;
  I_U32                 counter       = ZERO;
  I_U32		              tsVal         = NULL;
  I_U32 		            bictei        = ZERO;
  I_U32 		            e1Id		      = ZERO;
  OamsTsList            *ptr		      = NULL;
  OamsTsList	          *tmpPtr	      = NULL;
  AbisE1TsNode 	        *rootTree	    = NULL;
  I_U32		              tsRecCount	  = ZERO;
  AbisE1TsNode 	        *abisE1TsNode	= NULL;
  I_U32                 returnVal		= ZERO;
  I_U32                 timeSlot		  = ZERO ;

  /* R2.8 Change Start */
  if ((GET_BTS_TYPE() == R3_BTS) || (GET_BTS_TYPE() == R2_BTS_IP))
  {
    return ;
  }
  /* R2.8 Changes End */

  LOG_PRINT(INFO,"\n Entering [%s]",__func__);

  if (!rcvPtr) {
    LOG_PRINT(INFO,"[%s:]Message Pointer is NULL",__func__);
    return ;
  }

  e1Id   = (I_U32)rcvPtr->e1Id ;   
  bictei = (I_U32)rcvPtr->bicTei ;   
  tsVal  = (I_U32)rcvPtr->e1Ts ;   

 	/*search for the e1 id ..if  found then*/ 
	ptrE1Node = searchAbisE1Id(&gabisE1List,e1Id);
	if(!ptrE1Node) {
	  LOG_PRINT(INFO,"\n[%s:] E1Id[%d] not found",e1Id);
    return ;
  }
  /*the e1 id is already added to the list so remove */
  /*all the ts for the e1 id and the bic's connected with it*/
  if(IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList))) {
	  LOG_PRINT(INFO,"\n[%s:] TS node is already empty");
    return ;
  }

  /*traverse through all the ts for the e1 id*/
  LOG_PRINT(INFO,"\n [%s]Bic Ts List is not empty",__func__);
  OAMS_TS_LIST_FOR_EACH(ptr, tmpPtr, &(ptrE1Node->abisChainList))
  {
    /*if bic is connected with the ts then delete it */
    rootTree = OAMS_LIST_ENTRY(ptr,AbisE1TsNode,tsList);
    if ((rootTree->timeSlot == tsVal) && (rootTree->tei == bictei)) {    
      if(!IS_OAMS_TREE_EMPTY(&(rootTree)->bicTreeRoot))
      {
        LOG_PRINT(INFO,"\n [%s]Bic present in the tree for timeslot %d ",__func__,rootTree->timeSlot);
        OAMS_TREE_DEL_N_FREE_CHILD_LIST(&(rootTree)->bicTreeRoot, BicNode, bicTree,FREE);
      }
      else
      {
        LOG_PRINT(INFO,"\n [%s]No bic present in the tree for timeslot %d ",__func__,rootTree->timeSlot);
      }
      INIT_OAMS_TREE(&(rootTree->bicTreeRoot));
      OAMS_TS_LIST_DEL_N_FREE(ptr, AbisE1TsNode, tsList, FREE);
      LOG_PRINT(INFO,"Freeing AbisE1TsNode %p",rootTree);        
    }
  }
  if(IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
  {
    LOG_PRINT(INFO,"\n initAbisChain:Initialize the TS List for e1 Id %d ",e1Id);
    INIT_OAMS_TS_LIST(&(ptrE1Node->abisChainList));
  }
  LOG_PRINT(INFO,"\n Exit [%s]",__func__);
}

/********************************* Function  Header********************************
Function Name     :addTsNodeInAbisChain
Parameters        :I_PVoid
Return type       :void
Purpose           :this function add Ts Nodel in Abis Chain
Other Note        :
 ************************************************************************************/
I_Bool addTsNodeInAbisChain(I_PVoid rcvPtr)
{
  OamsCfgBichAddBicReq *OamsCfgBichAddBicReqPtr = rcvPtr;
  AbisE1Node           *ptrE1Node               = NULL;
  I_U32 		           bictei                   = ZERO;
  AbisE1TsNode 	       *abisE1TsNode	          = NULL;
  I_U32                returnVal		            = ZERO;
  OamsTsList           *ptr		                  = NULL;
  OamsTsList	         *tmpPtr	                = NULL;
  AbisE1TsNode 	       *rootTree	              = NULL;  
       
  /* R2.8 Change Start */
  if ((OamsCfgBichAddBicReqPtr->btsType == R3_BTS) || (OamsCfgBichAddBicReqPtr->btsType == R2_BTS_IP))
  {
    return I_TRUE;
  }
  /* R2.8 Changes End */
  
  LOG_PRINT(INFO,"\n Entering [%s]",__func__);

  if (!rcvPtr) {
    LOG_PRINT(INFO,"[%s:]Message Pointer is NULL",__func__);
    return I_FALSE;    
  }
  /*search for the e1 id ..if  found then*/ 
  ptrE1Node = searchAbisE1Id(&gabisE1List,OamsCfgBichAddBicReqPtr->e1Id); 
  if (!ptrE1Node)  {
    LOG_PRINT(INFO,"[%s:] E1[%d] is not found in list",__func__,OamsCfgBichAddBicReqPtr->e1Id);
    return I_FALSE;    
  }

  bictei = OamsCfgBichAddBicReqPtr->applTei;

  LOG_PRINT(INFO,"[E1 Id: %d][Ts=%d][bicTei:%d]",
      OamsCfgBichAddBicReqPtr->e1Id,
      OamsCfgBichAddBicReqPtr->e1Ts,
      bictei);

  /*Check if TsNode for given e1Ts already exists*/
  OAMS_TS_LIST_FOR_EACH(ptr, tmpPtr, &(ptrE1Node->abisChainList))
  {
    /*if bic is connected with the ts then delete it */
    rootTree = OAMS_LIST_ENTRY(ptr,AbisE1TsNode,tsList);
    if (rootTree->timeSlot == OamsCfgBichAddBicReqPtr->e1Ts) {    
      LOG_PRINT(INFO,"\n [%s]Bts/Bic[%d] Tei[%d]already exists for TS[%d] ",
                     __func__,
                     getFirstBicFromTei(rootTree->tei),
                     rootTree->tei,
                     rootTree->timeSlot);
      return I_FALSE;  
    }
  }
  
  abisE1TsNode = allocateTsNode(OamsCfgBichAddBicReqPtr->e1Ts, bictei);  
  if(!abisE1TsNode) {
    LOG_PRINT(INFO,"[%s:]Allocation for Bic Ts node fails",__func__);
    return I_FALSE;    
  }

  /*Add the Ts node to the e1 List*/
  LOG_PRINT(INFO,"\n [%s:]Add the bic Ts node to the List",__func__);
  OAMS_TS_LIST_ADD(&(abisE1TsNode->tsList),&(ptrE1Node->abisChainList));

  LOG_PRINT(INFO,"BIC Ts Node added to list");

  LOG_PRINT(INFO,"\n Exit [%s]",__func__);
  return I_TRUE;
}

/********************************* Function  Header********************************
Function Name     :initAbisChain
Parameters        :I_U32 e1Id
Return type       :void
Purpose           :this function initializes an abis chain
Other Note        :
 ************************************************************************************/
void initAbisChain(I_PVoid sndPtr)
{
  	AbisE1Node        *ptrE1Node    = NULL;
	I_U32             counter       = ZERO;
	I_U32		  *tsVal        = NULL;
	I_U32 		   bictei       = ZERO;
	I_U32 		   e1Id		 = ZERO;
	OamsTsList        *ptr		 = NULL;
	OamsTsList	  *tmpPtr	 = NULL;
	AbisE1TsNode 	  *rootTree	 = NULL;
	I_U32		   tsRecCount	 = ZERO;
	AbisE1TsNode 	   *abisE1TsNode	 = NULL;
   	I_U32              returnVal		 = ZERO;
   	I_U32              timeSlot		 = ZERO ;
       
	OamsCfgBichInitAbisE1 *oamsCfgBichInitAbisChain ;
        oamsCfgBichInitAbisChain =(OamsCfgBichInitAbisE1 *)sndPtr ;
        e1Id=(I_U32)oamsCfgBichInitAbisChain->e1Id ;   
        LOG_PRINT(INFO,"\n Entering initAbisChain function");

 	/*search for the e1 id ..if  found then*/ 
	ptrE1Node = searchAbisE1Id(&gabisE1List,e1Id);
	if(ptrE1Node != NULL)
	{
		/*the e1 id is already added to the list so remove */
		/*all the ts for the e1 id and the bic's connected with it*/
		if(!IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
		{
			/*traverse through all the ts for the e1 id*/
			LOG_PRINT(INFO,"\n initAbisChain:Bic Ts List is not empty");
			OAMS_TS_LIST_FOR_EACH(ptr, tmpPtr, &(ptrE1Node->abisChainList))
			{
				/*if bic is connected with the ts then delete it */
				rootTree = OAMS_LIST_ENTRY(ptr,AbisE1TsNode,tsList);
				if(!IS_OAMS_TREE_EMPTY(&(rootTree)->bicTreeRoot))
   			{
					LOG_PRINT(INFO,"\n initAbisChain:Bic present in the tree for timeslot %d ",rootTree->timeSlot);
					OAMS_TREE_DEL_N_FREE_CHILD_LIST(&(rootTree)->bicTreeRoot, BicNode, bicTree,FREE);
          LOG_PRINT(INFO,"Freeing AbisE1TsNode %p",rootTree);
				}
				else
				{
					LOG_PRINT(INFO,"\n initAbisChain:No bic present in the tree for timeslot %d ",rootTree->timeSlot);
				}
				INIT_OAMS_TREE(&(rootTree->bicTreeRoot));
				OAMS_TS_LIST_DEL_N_FREE(ptr, AbisE1TsNode, tsList, FREE);
			}
			if(IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
			{
				LOG_PRINT(INFO,"\n initAbisChain:Initialize the TS List for e1 Id %d ",e1Id);
				INIT_OAMS_TS_LIST(&(ptrE1Node->abisChainList));
			}
		}
		else
		{
			LOG_PRINT(INFO,"\n initAbisChain:Bic Ts list empty");
		}
	}
	
   if(ptrE1Node != NULL && IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
   {
	   LOG_PRINT(INFO,"\n initAbisChain:Ts List empty");
   }
   /*-------------Allocate an AbisE1Node for each  E1Id  */
   if(ptrE1Node == NULL)
   {
      ptrE1Node = allocateAbisE1Node(e1Id);
      if(ptrE1Node != NULL)
      {
      	/* Add the AbisE1 in the OamsList */
         OAMS_LIST_ADD(&(ptrE1Node->e1List),&gabisE1List);
      }
      else
      {
 	      LOG_PRINT(MAJOR,"initAbisChain:Allocation for abis E1 node fails");
	      return;	
      }
   }
/*BB, Start, R22 , 17-09-09::14:54 , TS nodes are added at the time of add bic*/   
#if 0    
	/*DB-CALL get all the ts for e1 id and the counter*/
	/* and get all the tei from the bic tei map table*/
   returnVal = getAllE1TsBicE1TeiMapTable(e1Id,&tsVal,&tsRecCount);   
   if(returnVal == CLIB_SUCCESS)
   {  
        for(counter = 0;counter < tsRecCount;counter++)
   	{
         timeSlot = *(tsVal + counter);
	 LOG_PRINT(INFO,"[TimeSLot:%d]",timeSlot);
         returnVal = getTerBicE1TeiMapTable(e1Id,timeSlot,&bictei);
	 LOG_PRINT(INFO,"[E1 Id: %d][Ts=%d][bicTei:%d]",e1Id,timeSlot,bictei);
         if(returnVal == CLIB_SUCCESS)
         { 
	         LOG_PRINT(INFO,"[E1 Id: %d][timeSLot=%d][bicTei:%d]",e1Id,timeSlot,bictei);
	         abisE1TsNode = allocateTsNode(timeSlot,bictei);
	         LOG_PRINT(INFO,"[E1 Id: %d][bicTei:%d][timeSlot:%d]",e1Id,bictei,timeSlot);
		      if(abisE1TsNode != NULL)
		      {
			      /*Add the Ts node to the e1 List*/
			      LOG_PRINT(INFO,"\n initAbisChain:Add the bic Ts node to the List");
	            OAMS_TS_LIST_ADD(&(abisE1TsNode->tsList),&(ptrE1Node->abisChainList));
		      }
		      else
		      {
			      LOG_PRINT(INFO,"initAbisChain:Allocation for Bic Ts node fails");
		      }
            /* no need to free free(bictei);*/
         }
         else
         {
            LOG_PRINT(MAJOR,"Db call for getTerBicE1TeiMapTable fails");
         }
         LOG_PRINT(MAJOR,"BIC Ts Node added to list");
      }
      if(tsVal !=NULL)
      {
         FREE(tsVal);
      }
   }
   else
   {
     LOG_PRINT(INFO,"\ngetAllE1TsBicE1TeiMapTable call fail");
   }
#endif   
   LOG_PRINT(INFO,"\n Leaving initAllAbisChain function");
   return;
}
   
/********************************* Function  Header********************************
Function Name     :searchAbisE1Tei
Parameters        :abisChainList,bicTei
Return type       :AbisE1Node *
Purpose           :This function search an AbisE1Node from E1Id
Other Note        :
 ************************************************************************************/
AbisE1Node *searchAbisE1Id(OamsList *abisChainList, I_U8 e1Id)
{
   AbisE1Node   *ptrE1Node = NULL;
   OamsList     *ptr       = NULL;
   OamsList     *tmpPtr    = NULL;

   /* use macros IS_OAMS_LIST_EMPTY and BICH_LIST_FOR_EACH to search */
   LOG_PRINT(INFO,"\n Entering searchAbisE1Id function for e1Id %d",e1Id);
   
   if(IS_OAMS_LIST_EMPTY(abisChainList))
   {
      LOG_PRINT(INFO,"\n No abis E1 node in the list"); 
      return NULL;
   }
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,abisChainList)
   {
      /* use macro OAMS_LIST_ENTRY to find AbisE1Node*  - compare bicTei*/
      ptrE1Node = OAMS_LIST_ENTRY(ptr,AbisE1Node,e1List);
      if(ptrE1Node != NULL)
      {
         /*if abisE1 node with matching E1Id found then return the abisE1node*/
         if(ptrE1Node->e1Id == e1Id)
         {
            /* return AbisE1Node*   */
            return (ptrE1Node);
         }
      }
   }
   /*if abis E1 node with matching E1Id not found then return NULL*/
   return NULL;
}

/********************************* Function  Header********************************
Function Name     :allocateBicNode
Parameters        :bicId
Return type       :BicNode*
Purpose           :This functions allocates a BIC Node
Other Note        :
 ************************************************************************************/
BicNode *allocateBicNode(BicIdentifier bicId) 
{
   /* allocate memory for the BIC node on failure return NULL*/
   BicNode *bicNode = NULL;
   LOG_PRINT(INFO,"\n Entering allocateBicNode function for bic id %u ",bicId);
   
   bicNode = (BicNode*)MALLOC(sizeof(BicNode));
   /*HA change */
   LOG_PRINT(INFO,"Allocating BicNode %x",bicNode);
   if (NULL == bicNode)
   {
      /* LOG error */
      LOG_PRINT(CRITICAL,"\n Memory allocation for BicNode failed");
      return NULL;
   }
   /* Set the bicId */
   bicNode->bicId = bicId;
   /* return the BIC Node pointer */
   return bicNode;
}
/********************************* Function  Header********************************
Function Name     :findBicInTree
Parameters        :RootNode,bicId
Return type       :BicNode*
Purpose           :this function searches a bic and return the bic node pointer
Other Note        :
 ************************************************************************************/
BicNode *findBicInTree(OamsTree *RootNode,BicIdentifier bicId) 
{
   BicNode  *tempPtr = NULL;
   BicNode  *bicNode = NULL;
   OamsTree *ptr     = NULL;
   OamsTree *tmpPtr  = NULL;

   for (ptr = (RootNode)->firstChild, tmpPtr = ptr->nextChild;
         ptr != (RootNode);
         ptr = tmpPtr, tmpPtr = ptr->nextChild)
   {
      bicNode = findBicInTree(ptr,bicId);
      if(bicNode != NULL)
         return bicNode;

   }
   tempPtr = OAMS_TREE_ENTRY(RootNode, BicNode, bicTree);
   
   if(tempPtr->bicId == bicId)
   {
      bicNode = tempPtr;
      LOG_PRINT(INFO,"\n Search success for Bic id %u ",bicNode->bicId);   
   }
   return bicNode;
}

/********************************* Function  Header********************************
Function Name     :searchBic
Parameters        :bicId,bictei
Return type       :BicNode*
Purpose           :This function search a BIC in  an AbisChain
Other Note        :
 ************************************************************************************/
BicNode *searchBic(BicIdentifier bicId,BicTei bicTei) 
{
	AbisE1TsNode	*abisE1TsNode	 = NULL;
	I_S32 	         e1Id = -1;

   LOG_PRINT(INFO,"\n Entering searchBic function for bic id %u ",bicId);

	/*get the e1Id value on the basis of bicTei from the bicTeiMap table*/
	e1Id = getE1IdFromTei(&gabisE1List,bicTei);
	
	if(e1Id == -1)
	{
		LOG_PRINT(INFO,"\n E1 id not found for tei %d ",bicTei);
		return NULL;
	}
	
	abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
	
	if(abisE1TsNode == NULL)
		return NULL;

   if (IS_OAMS_TREE_EMPTY(&(abisE1TsNode->bicTreeRoot))) 
      return NULL;

	if(abisE1TsNode != NULL)
	   return findBicInTree(&(abisE1TsNode->bicTreeRoot),bicId);
	else
		return NULL;
}

/********************************* Function  Header********************************
Function Name     :getLapdTs
Parameters        :ptrxId,trxCount,*lapdTs
Return type       :void 
Purpose           :this function populates the lapdTs array to be used for sending
                   the slot connect or slot disconnect
Other Note        :
 ************************************************************************************/
I_U8 getLapdTs(I_U32 *ptrxId,I_U8 trxCount, I_U8 *lapdTs)
{
    I_U32 counter       = ZERO;
    I_U32 returnVal     = ZERO;
    I_U8 lapdTimeSlot   = ZERO;
    /*loop continues for each trx connected to the bic*/
    LOG_PRINT(INFO,"\n Entering getLapdTs function ");
    for(counter = ZERO;counter < trxCount;counter++)
    {
      /*get the lapd timeslot for ptrxId[counter] attached with the bic*/
      returnVal = getLapdTsTrxTsTeiTable(ptrxId[counter],&lapdTimeSlot);
      if(returnVal == CLIB_SUCCESS)
      {
          /*assign the lapd timeslot to the array*/
          lapdTs[counter] = lapdTimeSlot;
      }
      else
      {
         LOG_PRINT(INFO,"\n getLapdTsTrxTsTeiTable call failed ");
         return BICH_FAILURE;
      }
    }
   return BICH_SUCCESS;
}
/********************************* Function  Header********************************
Function Name     :getStartTs
Parameters        :ptrxId,trxCount,*startTs
Return type       :void 
Purpose           :this function returns the start timeslot to be used for 
                   sending the slot connect and slot disconnect
Other Note        :
 ************************************************************************************/
I_U8 getStartTs(I_U32 *ptrxId,I_U8 trxCount,I_U8 *startTs)
{
    I_U32 counter    = ZERO;
    I_U16 trxPos     = ZERO;
    I_S32 returnVal  = ZERO;
    BicTrxTsTableIndices bicTrxTsTableIndices;
    BicTrxTsTableApi *bicTrxTsTableApi = NULL;
   
    LOG_PRINT(INFO,"\n Entering getStartTs function ");
    
    /*loop continues for each trx connected to the bic*/
    for(counter = ZERO;counter < trxCount;counter++)
    {
      /*get the trx position based on the trx id*/
      returnVal  = getTrxPosTrxTable(ptrxId[counter], &trxPos);
      if(returnVal == CLIB_SUCCESS)
      {
          /*get the start timeslot for the trxid and assign the value in the
          startts array*/
         bicTrxTsTableIndices.trxPos = trxPos;
         bicTrxTsTableApi = NULL;
         returnVal = getBicTrxTsTable(&bicTrxTsTableIndices,&bicTrxTsTableApi);
         if(returnVal == CLIB_SUCCESS)
         {
            startTs[counter] = bicTrxTsTableApi->startTs;
         }
         else
         {
            LOG_PRINT(INFO,"\n getBicTrxTsTable call failed ");
            return BICH_FAILURE;
         }
         if(bicTrxTsTableApi != NULL)
            free(bicTrxTsTableApi);
      }
      else
      {
         LOG_PRINT(INFO,"\n getTrxPosTrxTable call failed ");
         return BICH_FAILURE;
      }
    }
   return BICH_SUCCESS;
}

/********************************* Function  Header********************************
Function Name     :getTrxTs
Parameters        :ptrxId,trxCount,*lapdTs,*firstTsTraffic,*secondTsTraffic
Return type       :void 
Purpose           :this function populates the lapdTs,firstTsTraffic,secondTsTraffic
                   array to be used for sending
                   the slot connect or slot disconnect
Other Note        :
 ************************************************************************************/
I_U8 getTrxTs(I_U32 *ptrxId,I_U8 trxCount,I_U8 *lapdTs, I_U8 *firstTsTraffic, I_U8 *secondTsTraffic)
{
    I_U32 counter       = ZERO;
    I_U32 returnVal     = ZERO;
    I_U8 lapdTimeSlot   = ZERO;
    TrxTsTeiTableIndices trxIndices;
    TrxTsTeiTableApi     *trxOutData = NULL;
    /*loop continues for each trx connected to the bic*/
    LOG_PRINT(INFO,"\n Entering getTrxTs function ");
    for(counter = ZERO;counter < trxCount;counter++)
    {
      trxIndices.ptrxId = ptrxId[counter];
      /*get the lapd timeslot for ptrxId[counter] attached with the bic*/
      returnVal = getTrxTsTeiTable(&trxIndices, &trxOutData);
      if(returnVal == CLIB_SUCCESS)
      {
          /*assign the lapd timeslot to the array*/
          lapdTs[counter] = trxOutData->lapdTs;
          /*assign the firstTsTraffic to the array*/
          firstTsTraffic[counter] = trxOutData->firstTsTraffic;
          /*assign the secondTsTraffic to the array*/
          secondTsTraffic[counter] = trxOutData->secondTsTraffic;
          free(trxOutData);
      }
      else
      {
         LOG_PRINT(INFO,"\n getLapdTsTrxTsTeiTable call failed ");
         return BICH_FAILURE;
      }
    }
   return BICH_SUCCESS;
}

/********************************* Function  Header********************************
Function Name     :sendSlotConnectMsg
Parameters        :forbicId,toBicId,dsBicId,trxCount,bicTei,*lapdTs,*startTs
Return type       :void 
Purpose           :this function creates the slot connect message and send 
                   the message to ABIHM slot disconnect
Other Note        :
 ************************************************************************************/
void sendSlotConnectMsg(BicIdentifier forbicId,BicIdentifier toBicId,BicIdentifier dsBicId,\
                        I_U8 trxCount,BicTei bicTei,I_U8 *lapdTs,I_U8 *startTs,I_U8 *firstTsTraffic, I_U8 *secondTsTraffic)
{
    I_U8 counter     =ZERO;
    I_PVoid *sndMsg  =NULL;
    I_U32 msgSize    =ZERO;
    I_U8 index       =ZERO;

    OamsBichAbihmSlotConnect *oamsBichAbihmSlotConnect;
        
    LOG_PRINT(INFO,"\n Entering sendSlotConnectMsg function ");
    for(counter = ZERO;counter < trxCount;counter++)
    {
      
      LOG_PRINT(INFO,"\nIn SlotConnect message: LapdTs %d  ForBicid %u Tobicid %u  DsBicid %u Counter %d",\
      lapdTs[counter],forbicId,toBicId,dsBicId,counter+1);
      /* R2.2 Changes start */

    /*  oamsBichAbihmSlotConnect = (OamsBichAbihmSlotConnect*)AlocMsgBuf(sizeof(OamsBichAbihmSlotConnect)\
                                 +sizeof(BicSlotConnectMap)); 

      if(oamsBichAbihmSlotConnect == NULL)
      {
        LOG_PRINT(CRITICAL,"\n Could not allocate memory for OamsBichAbihmSlotConnect ");
        return;
      }
*/
      msgSize = sizeof(OamsBichAbihmSlotConnect)+sizeof(BicSlotConnectMap);

      /*if slot connect message for any upstream bic*/
      if(forbicId != toBicId)
      {
          oamsBichAbihmSlotConnect = (OamsBichAbihmSlotConnect*)AlocMsgBuf(sizeof(OamsBichAbihmSlotConnect)\
                                 +sizeof(BicSlotConnectMap)); 

          if(oamsBichAbihmSlotConnect == NULL)
          {
             LOG_PRINT(CRITICAL,"\n Could not allocate memory for OamsBichAbihmSlotConnect ");
             return;
          }
         /*prepare the bic slot connect map*/
         oamsBichAbihmSlotConnect->slotConnMap[ZERO].slotNoUpStreamPort = lapdTs[counter];
         oamsBichAbihmSlotConnect->slotConnMap[ZERO].slotNoDownStreamPort = lapdTs[counter];
         oamsBichAbihmSlotConnect->slotConnMap[ZERO].noOfSlots = THREE;
         oamsBichAbihmSlotConnect->slotConnMap[ZERO].bicId = dsBicId;

         /*prepare the slot connect message to be sent to abihm */
         oamsBichAbihmSlotConnect->bicTei = bicTei;
         oamsBichAbihmSlotConnect->placementInd = PLACEMENT_IND;
         oamsBichAbihmSlotConnect->seqNum = SEQUENCE_NUM;
         oamsBichAbihmSlotConnect->objClass = OBJECT_CLASS;
         oamsBichAbihmSlotConnect->objInstance.bicObjInst[ZERO] = OBJECT_INST_OCTET1;
         oamsBichAbihmSlotConnect->objInstance.bicObjInst[1] = OBJECT_INST_OCTET2;
         oamsBichAbihmSlotConnect->objInstance.bicObjInst[2] = OBJECT_INST_OCTET3;
         oamsBichAbihmSlotConnect->bicId = toBicId;
         oamsBichAbihmSlotConnect->numSlotConMap = ONE;
         FILL_SYS_HDR(oamsBichAbihmSlotConnect,OAMS_BICH_ABIHM_BIC_SLOT_CONNECT,MSG_SUB_TYPE,PRCR_CP,\
         ENT_OAMS_BICH,ZERO,PRCR_PP,ENT_CSAPP_ABIHM,ZERO);
         sndMsg = (I_PVoid*)(oamsBichAbihmSlotConnect);
         if (SendMsg(sndMsg, 1, msgSize) < ZERO) 
         { 
            LOG_PRINT(LOG_CRITICAL,"\nIn function slotConnectMessage() - msg sending failed"); 
            return; 
         }
      }
      else /*if forbicid == tobicid*/
      {
          /*prepare the bic slot connect map*/
        for ( index = 0; index < THREE; index ++ )
        {

          oamsBichAbihmSlotConnect = (OamsBichAbihmSlotConnect*)AlocMsgBuf(sizeof(OamsBichAbihmSlotConnect)\
                                 +sizeof(BicSlotConnectMap)); 

          if(oamsBichAbihmSlotConnect == NULL)
          {
             LOG_PRINT(CRITICAL,"\n Could not allocate memory for OamsBichAbihmSlotConnect ");
             return;
          }

           if ( index == 0 )
              oamsBichAbihmSlotConnect->slotConnMap[ZERO].slotNoUpStreamPort = lapdTs[counter];
           if ( index == 1 )
              oamsBichAbihmSlotConnect->slotConnMap[ZERO].slotNoUpStreamPort = firstTsTraffic[counter];
           if ( index == 2 )
              oamsBichAbihmSlotConnect->slotConnMap[ZERO].slotNoUpStreamPort =secondTsTraffic[counter];

           oamsBichAbihmSlotConnect->slotConnMap[ZERO].slotNoDownStreamPort = startTs[counter ] + index;
           oamsBichAbihmSlotConnect->slotConnMap[ZERO].noOfSlots = ONE; //THREE
           /* R2.2 Changes End */
           oamsBichAbihmSlotConnect->slotConnMap[ZERO].bicId = forbicId;
           /*prepare the slot connect message to be sent to abihm */
           oamsBichAbihmSlotConnect->bicTei = bicTei;
           oamsBichAbihmSlotConnect->placementInd = PLACEMENT_IND;
           oamsBichAbihmSlotConnect->seqNum = SEQUENCE_NUM;
           oamsBichAbihmSlotConnect->objClass = OBJECT_CLASS;
           oamsBichAbihmSlotConnect->objInstance.bicObjInst[ZERO] = OBJECT_INST_OCTET1;
           oamsBichAbihmSlotConnect->objInstance.bicObjInst[1] = OBJECT_INST_OCTET2;
           oamsBichAbihmSlotConnect->objInstance.bicObjInst[2] = OBJECT_INST_OCTET3;
           oamsBichAbihmSlotConnect->bicId = forbicId;
           oamsBichAbihmSlotConnect->numSlotConMap = ONE;

           FILL_SYS_HDR(oamsBichAbihmSlotConnect,OAMS_BICH_ABIHM_BIC_SLOT_CONNECT,MSG_SUB_TYPE,PRCR_CP,\
           ENT_OAMS_BICH,ZERO,PRCR_PP,ENT_CSAPP_ABIHM,ZERO);
           sndMsg = (I_PVoid*)(oamsBichAbihmSlotConnect);
           if (SendMsg(sndMsg, 1, msgSize) < ZERO) 
           { 
              LOG_PRINT(LOG_CRITICAL,"\nIn function slotConnectMessage() - msg sending failed"); 
              return; 
           }
        } 
      }
    }
    /* R2.2 Changes End */
}

/********************************* Function  Header********************************
Function Name     :buildUpStreamSlotConnMap
Parameters        :OamsTree*,forbicId,toBicId,dsBicId,trxCount,bicTei,*lapdTs
Return type       :void 
Purpose           :this function traverses the tree and determine the bic id
                   for which the slot connect message needs to be created
Other Note        :
 ************************************************************************************/
void buildUpStreamSlotConnMap(OamsTree *ptr,BicIdentifier forbicId,BicIdentifier toBicId,\
                              BicIdentifier dsBicId,I_U8 trxCount,BicTei bicTei,I_U8 *lapdTs, I_U8 *firstTsTraffic,I_U8 *secondTsTraffic)
{
   BicNode 		   *tmpPtr          = NULL;
	AbisE1TsNode	*abisE1TsNode	  = NULL;
	I_S32 	   	e1Id			     = -1;
   
   LOG_PRINT(INFO,"\n Entering buildUpStreamSlotConnMap function ");

	/*get the e1Id value on the basis of bicTei from the bicTeiMap table*/
	e1Id = getE1IdFromTei(&gabisE1List,bicTei);
	
	if(e1Id == -1)
	{
		LOG_PRINT(INFO,"\n buildUpStreamSlotConnMap:E1 id not found for tei %d ",bicTei);
		return;
	}

	abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
   
   if(abisE1TsNode == NULL)
   {
      LOG_PRINT(INFO,"\nIn function buildUpStreamSlotConnMap : abisE1 node not found for bicTei %d",bicTei);
      return;
   }
   if(ptr->parent != &(abisE1TsNode->bicTreeRoot))  
   {
      tmpPtr = OAMS_TREE_ENTRY(ptr->parent, BicNode, bicTree);
      toBicId = tmpPtr->bicId;

      tmpPtr = OAMS_TREE_ENTRY(ptr, BicNode, bicTree);
      dsBicId = tmpPtr->bicId; 

      buildUpStreamSlotConnMap(ptr->parent,forbicId,toBicId,dsBicId,trxCount,bicTei,lapdTs,firstTsTraffic,secondTsTraffic);

      LOG_PRINT(INFO,"\n In function buildUpStreamSlotConnMap:create slot Connect \
      message for ToBic Id %u dsBicId %u ",toBicId,dsBicId);

      sendSlotConnectMsg(forbicId,toBicId,dsBicId,trxCount,bicTei,lapdTs,NULL,firstTsTraffic,secondTsTraffic);
    }
    return;
}
/********************************* Function  Header********************************
Function Name  :sendSlotDisconnMsg
Parameters     :forbicId,toBicId,dsBicId,trxCount,bicTei,*lapdTs
Return type    :void 
Purpose        :this function creates the slot disconnect message and 
                send the message to ABIHM needs to be created
Other Note     :
 ************************************************************************************/
void sendSlotDisconnMsg(BicIdentifier forbicId,BicIdentifier toBicId,BicIdentifier \
                        dsBicId,I_U8 trxCount,I_U8 bicTei,I_U8 *lapdTs)
{
    I_U8    counter     = ZERO;
    I_PVoid *sndMsg     = NULL;
    I_U32   msgSize;

    OamsBichAbihmSlotDisConnect *oamsBichAbihmSlotDiscConnect = NULL;
    
    LOG_PRINT(INFO,"\n Entering sendSlotDisconnMsg function ");
    for(counter = ZERO;counter < trxCount;counter++)
    {
       LOG_PRINT(INFO,"\nIn SlotDisConnect message: LapdTs %d  ForBicid %u Tobicid %u Ds BicId %u Counter %d",\
       lapdTs[counter],forbicId,toBicId,dsBicId,counter+1);

       oamsBichAbihmSlotDiscConnect = (OamsBichAbihmSlotDisConnect*)AlocMsgBuf(sizeof(OamsBichAbihmSlotDisConnect)\
                                       +sizeof(BicSlotConnectMap));
       if(oamsBichAbihmSlotDiscConnect == NULL)
       {
           LOG_PRINT(CRITICAL,"\n Could not allocate memory for OamsBichAbihmSlotDiscConnect ");
           return;
       }
       msgSize = sizeof(OamsBichAbihmSlotDisConnect)+sizeof(BicSlotConnectMap);
       oamsBichAbihmSlotDiscConnect->slotConnMap[ZERO].slotNoUpStreamPort = lapdTs[counter]; 
       oamsBichAbihmSlotDiscConnect->slotConnMap[ZERO].slotNoDownStreamPort = lapdTs[counter];
       oamsBichAbihmSlotDiscConnect->slotConnMap[ZERO].noOfSlots = THREE;
       oamsBichAbihmSlotDiscConnect->slotConnMap[ZERO].bicId = dsBicId; 
       oamsBichAbihmSlotDiscConnect->bicTei = bicTei;
       oamsBichAbihmSlotDiscConnect->placementInd = PLACEMENT_IND;
       oamsBichAbihmSlotDiscConnect->seqNum = SEQUENCE_NUM;
       oamsBichAbihmSlotDiscConnect->objClass = OBJECT_CLASS;
       oamsBichAbihmSlotDiscConnect->objInstance.bicObjInst[ZERO] = OBJECT_INST_OCTET1;
       oamsBichAbihmSlotDiscConnect->objInstance.bicObjInst[1] = OBJECT_INST_OCTET2;
       oamsBichAbihmSlotDiscConnect->objInstance.bicObjInst[2] = OBJECT_INST_OCTET3;
       oamsBichAbihmSlotDiscConnect->bicId = toBicId;
       oamsBichAbihmSlotDiscConnect->numSlotConMap = ONE;

       FILL_SYS_HDR(oamsBichAbihmSlotDiscConnect,OAMS_BICH_ABIHM_BIC_SLOT_DISCONNECT,MSG_SUB_TYPE,PRCR_CP,\
       ENT_OAMS_BICH,ZERO,PRCR_PP,ENT_CSAPP_ABIHM,ZERO);   
       sndMsg = (I_PVoid *)oamsBichAbihmSlotDiscConnect;
       if (SendMsg(sndMsg, 1, msgSize) < ZERO) 
       { 
          LOG_PRINT(LOG_CRITICAL,"\nIn func slotDisConnectMessage() - msg sending failed"); 
          return; 
       }
    }
}

/********************************* Function  Header********************************
Function Name     :buildSlotDisconnectMap
Parameters        :OamsTree *,forbicId,toBicId,dsBicId,trxCount,bicTei,*lapdTs
Return type       :void 
Purpose           :this function prepares the slot disconnect map and sends it
                   to the upstream bic's needs to be created
Other Note        :
 ************************************************************************************/
void buildSlotDisconnectMap(OamsTree *ptr,BicIdentifier forBicId,I_U8 trxCount,\
                           BicIdentifier dsBicId,I_U8 bicTei,I_U8 *lapdTs)
{
    BicIdentifier toBicId        = ZERO;
    BicIdentifier bicId          = ZERO;
    BicNode       *tmpPtr        = NULL;
	 AbisE1TsNode	*abisE1TsNode	= NULL;
	 I_S32 			e1Id			   = -1;
   
    LOG_PRINT(INFO,"\n Entering buildSlotDisconnectMap function ");
   
	/*get the e1Id value on the basis of bicTei from the bicTeiMap table*/
	e1Id = getE1IdFromTei(&gabisE1List,bicTei);
	if(e1Id == -1)
	{
		LOG_PRINT(INFO,"\n buildSlotDisconnectMap:E1 id not found for tei %d ",bicTei);
		return;
	}
	abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
   if(abisE1TsNode == NULL)
   {
      LOG_PRINT(INFO,"\n buildSlotDisconnectMap: Abis node not found in the abis chain list");
      return;
   }
   tmpPtr = OAMS_TREE_ENTRY(ptr, BicNode, bicTree);
   bicId = tmpPtr->bicId;

   for( ;ptr != &(abisE1TsNode->bicTreeRoot);ptr = ptr->parent)
   {
        tmpPtr = OAMS_TREE_ENTRY(ptr, BicNode, bicTree);
        toBicId = tmpPtr->bicId;

        LOG_PRINT(INFO,"\n In function buildSlotDisconnectMap:create slot DisConnect \
        message for ForBic Id %u To Bic Id %u ",forBicId,toBicId);

        sendSlotDisconnMsg(forBicId,toBicId,dsBicId,trxCount,bicTei,lapdTs);

        tmpPtr = OAMS_TREE_ENTRY(ptr, BicNode, bicTree);
        dsBicId= tmpPtr->bicId;
    }
}
/********************************* Function  Header********************************
Function Name     :traverseDisconnChildList
Parameters        :RootNode,*func(),parentBicId,dsBicId,bicTei
Return type       :void 
Purpose           :this function traverses the childlist 
                   needs to be created
Other Note        :
 ************************************************************************************/
void traverseDisconnChildList(OamsTree *RootNode,void (*func)(I_U32),BicIdentifier parentBicId,\
                              BicIdentifier dsBicId,BicTei bicTei)
{
   BicNode        *tempPtr = NULL;
   OamsTree       *ptr     = NULL;
   OamsTree       *tmpPtr  = NULL;
   BicIdentifier  bicid;
   
   LOG_PRINT(INFO,"\n Entering traverseDisconnChildList function ");

   for (ptr = (RootNode)->firstChild, tmpPtr = ptr->nextChild;
         ptr != (RootNode);
         ptr = tmpPtr, tmpPtr = ptr->nextChild)
   {
      if(ptr != NULL)
      {
         tempPtr = OAMS_TREE_ENTRY(ptr, BicNode, bicTree);
         bicid = tempPtr->bicId;
	      if(parentBicId != ZERO)
	      {
	 	      slotDisconnectForChild(bicid,parentBicId,dsBicId,bicTei);
	      }
         (*func)(bicid);
      }
      traverseDisconnChildList(ptr,func,parentBicId,dsBicId,bicTei);
   }
   return;
}
/********************************* Function  Header********************************
Function Name     :slotDisconnectForChild
Parameters        :forBicId,parentBicId,dsBicId,bicTei
Return type       :void 
Purpose           :this function gets all the data for the bic id for which the slot disconnect
                   map message has to be sent and calls the buildSlotDisconnectmap function to
                   build the slot disconnect map needs to be created
Other Note        :
 ************************************************************************************/
void slotDisconnectForChild(BicIdentifier forBicId,BicIdentifier parentBicId,\
                            BicIdentifier dsBicId,BicTei bicTei)
{
    BicNode       *bicNode      = NULL;
    OamsTree      *tree         = NULL;

    I_S32         returnVal     = ZERO;
    I_U32         *ptrxId       = NULL;
    I_U32         trxCount      = ZERO;
	 I_S32 			e1Id		     = -1;
	 AbisE1TsNode 	*abisE1TsNode = NULL;

    /*lapdTs maintains the lapd timeslot for all the trx attached with a bic*/
    I_U8          *lapdTs       = NULL;
 
    LOG_PRINT(INFO,"\nIn function slotDisconnectForChild : Prepare slot disconnect message for Bic Id\
    %u ParentBic id %u ",forBicId,parentBicId);

    bicNode = searchBic(forBicId,bicTei);
    if(bicNode == NULL)
    {
      LOG_PRINT(INFO,"\nIn function slotDisconnectForChild : Bic id %u not found in the chain",forBicId);
      return;
    }
    else
    {
      /*get all the trx id attached with the bic*/
      returnVal = getAllPtrxTrxTable(forBicId, &ptrxId, &trxCount);
      if(returnVal == CLIB_SUCCESS)
      {
         lapdTs = (I_U8*)malloc(sizeof(I_U8)*trxCount);
         if(lapdTs == NULL)
         {
            LOG_PRINT(CRITICAL,"Memory allocation failed for lapdTs");
            return;
         }
         /*get the lapd timeslot for all the trx attached with the bic and assign it to the
         lapdTs array*/
         if(getLapdTs(ptrxId,trxCount,lapdTs) == BICH_FAILURE)
         {
            LOG_PRINT(CRITICAL,"getLapdTs function failed :exiting slotDisconnectForChild");
            FREE(lapdTs);
            return;
         }
         if(parentBicId != ZERO)
         {
            bicNode = searchBic(parentBicId,bicTei);
			      if(bicNode == NULL)
    			  {
      		  	LOG_PRINT(INFO,"\nIn function slotDisconnectForChild : Bic id %u not found in the chain",forBicId);
     			    return;
   		 	    }
            tree = &(bicNode->bicTree);
         }
         else
         {
            /*get the e1Id value on the basis of bicTei from the bicTeiMap table */
				    e1Id = getE1IdFromTei(&gabisE1List,bicTei);
			    	if(e1Id == -1)
			    	{
				    	LOG_PRINT(INFO,"\n E1 id not found for tei %d ",bicTei);
				    	return;
				    }
			    	abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
			      if(abisE1TsNode == NULL)
   			    {
					    LOG_PRINT(INFO,"\n Abis node not found in the abis chain list");
			        return;
   			    }
			    	tree = (abisE1TsNode->bicTreeRoot.firstChild);
         }
         buildSlotDisconnectMap(tree,forBicId,trxCount,dsBicId,bicTei,lapdTs);
         free(ptrxId);
         FREE(lapdTs);
      }
      else
      {
          LOG_PRINT(INFO,"\n CLIB fail for getAllPtrxTrxTable");
      }
   } 
}

/********************************* Function  Header********************************
Function Name     :prepareDisconnectedChildList
Parameters        :parentBicId,BicId,bicTei,void (*sendBicParentNotAvail)
Return type       :void 
Purpose           :this function creates and sends the parent disconnected message
                   to all the childs
Other Note        :
 ************************************************************************************/
void prepareDisconnectedChildList(BicIdentifier parentbicid,BicIdentifier bicId,BicTei bicTei,\
            void (*sendBicParentNotAvail)(I_U32))
{
    BicNode    *bicNode    = NULL;
    OamsTree   *childTree  = NULL;

    LOG_PRINT(INFO,"\n Entering prepareDisconnectedChildList function for bic id %u parentBicid %u ",\
    parentbicid,bicId);

    bicNode = searchBic(bicId,bicTei);
	 if(bicNode == NULL)
	 {
       LOG_PRINT(INFO,"\n In function prepareDisconnectedChildList:\
       bic id %u  node not found for bicTei %d ",bicId,bicTei);
       return;
	 }	
    childTree = &(bicNode->bicTree);
    traverseDisconnChildList(childTree,sendBicParentNotAvail,parentbicid,bicId,bicTei);

    /*send the parent disconnected message to the downstream bic for tmpPtr->bicId*/
	 if(parentbicid != ZERO)
	    slotDisconnectForChild(bicId,parentbicid,bicId,bicTei);   
    return;
}   


/********************************* Function  Header********************************
Function Name     :addBicInAbisChain
Parameters        :I_PVoid sndPtr
Return type       :void 
Purpose           :This function add a BIC in  an AbisChain
Other Note        :
 ************************************************************************************/
void addBicInAbisChain(I_PVoid sndPtr)
{
    BicIdentifier bicId;
    BicIdentifier parentBicId;
    BicTei        bicTei;
    BicNode       *bicNode       = NULL;
    BicNode       *tmpPtr        = NULL;
    I_S32         toBeFreed;
    AbisE1TsNode	*abisE1TsNode	= NULL;
    I_U32 			e1Id			   = ZERO;/*E1 Id should be I_U32*/

   if ((GET_BTS_TYPE() == R3_BTS) || (GET_BTS_TYPE() == R2_BTS_IP))
   {
     return;
   }
    bicId = ((OamsBichContext*)sndPtr)->bicId;
    parentBicId = ((OamsBichContext*)sndPtr)->parentBicId;
    bicTei = ((OamsBichContext*)sndPtr)->bicTei;
    e1Id = ((OamsBichContext*)sndPtr)->e1Id;

    LOG_PRINT(INFO,"Memory freed for SndPtr");
   
    LOG_PRINT(INFO,"\n Entering addBicInAbisChain function for bic id %u parentBicId %u\
    ",bicId,parentBicId);
	
   abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
   if(abisE1TsNode == NULL)
   {
     LOG_PRINT(INFO,"\n In function addBicInAbisChain:abisE1TsNode node not \
     found for bicTei %d",bicTei);
     return;
   }

   /* if parentBic == ZERO then add the Bic as the first Bic in the Abis Chain. 
   Change the Abis E1 status as BIC_CONNECTED */
   if(parentBicId == ZERO)
   {
      bicNode = allocateBicNode(bicId);
      /* use macro INIT_OAMS_TREE to init the bicChildList */ 
      INIT_OAMS_TREE(&(bicNode->bicTree));
      abisE1TsNode->bicTreeRoot.firstChild = &(bicNode->bicTree);
      bicNode->bicTree.nextChild = &(abisE1TsNode->bicTreeRoot);
      bicNode->bicTree.parent = &(abisE1TsNode->bicTreeRoot);
   }
   if(parentBicId != ZERO)
   {
     tmpPtr = searchBic(parentBicId,bicTei);
     if(tmpPtr == NULL)
     {
        LOG_PRINT(INFO,"\n In function addBicInAbisChain:Parent Bic id \
        %u not found in the chain",parentBicId);
        return;
     }
     bicNode = allocateBicNode(bicId);
     if(bicNode == NULL)
     {
         LOG_PRINT(INFO,"\n In function addBicInAbisChain:Bic node could not be\
         allocated for bic id %u ",bicId);
         return;
     }
     /* use macro INIT_OAMS_TREE to init the bicChildList */ 
     INIT_OAMS_TREE(&(bicNode->bicTree));
     OAMS_TREE_ADD(&(bicNode->bicTree),&(tmpPtr->bicTree));
   }
}
/********************************* Function  Header********************************
Function Name      :deleteBicFromAbisChain
Parameters         :I_PVoid sndPtr
Return type        :void 
Purpose            :this function deletes the bic id and all the downstream bics
                    for the bic id
Other Note         :
 ************************************************************************************/
void deleteBicFromAbisChain(I_PVoid sndPtr)
{
    BicIdentifier    bicId;
    BicIdentifier    parentBicId;
    BicTei           bicTei;
    BicNode          *bicNode       = NULL;
    OamsTree         *parentTree    = NULL;
    OamsTree         *childTree     = NULL;
    I_S32            toBeFreed;
	 AbisE1TsNode 		*abisE1TsNode	 = NULL;
	 I_U32 				e1Id			    = ZERO;

   if ((GET_BTS_TYPE() == R3_BTS) || (GET_BTS_TYPE() == R2_BTS_IP))
   {
     return;
   }

    bicId = ((OamsBichContext*)sndPtr)->bicId;
    parentBicId = ((OamsBichContext*)sndPtr)->parentBicId;
    bicTei = ((OamsBichContext*)sndPtr)->bicTei;

    LOG_PRINT(INFO,"Memory freed for SndPtr");
   
    LOG_PRINT(INFO,"\n Entering deleteBicFromAbisChain function for bic id %u parentBicid %u bicTei %d \
    ",bicId,parentBicId,bicTei);

    bicNode = searchBic(bicId,bicTei);
    if(bicNode == NULL)
    {
      LOG_PRINT(INFO,"\n In function deleteBicFromAbisChain : Bic \
      id %u not found in the chain",bicId);
      return;
    }
    
    if(!IS_OAMS_TREE_EMPTY(&(bicNode)->bicTree))
    {
        LOG_PRINT(INFO,"\n In function deleteBicFromAbisChain :Delete operation\
        for all the childs of bic %u ",bicId);
        OAMS_TREE_DEL_N_FREE_CHILD_LIST(&(bicNode)->bicTree, BicNode, bicTree,FREE);
        LOG_PRINT(INFO,"Freeing BicNode %p",bicNode);
    }
    childTree = &(bicNode)->bicTree;
    parentTree = childTree->parent;
    LOG_PRINT(INFO,"\n In function deleteBicFromAbisChain :\
    Delete operation for  bic %u ",bicId);
    OAMS_TREE_DEL(childTree,parentTree);
	 
	 e1Id = ((OamsBichContext*)sndPtr)->e1Id ; 
	
	 if(e1Id == ZERO)
	 {
		LOG_PRINT(INFO,"\n In function deleteBicFromAbisChain:E1 id not found for tei %d ",bicTei);
                FREE(bicNode);   
		return;
	 }
	 /* get the e1Id value on the basis of bicTei from the bicTeiMap table */
    abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
	 
	 if(abisE1TsNode == NULL)
    {
      LOG_PRINT(INFO,"\n In function deleteBicFromAbisChain:abisE1TsNode node not \
      found for bicTei %d",bicTei);
      FREE(bicNode);   
      return;
    }

    /*if all the bic's has been removed from the abis E1 node then set the status
    as no bic*/
	 if(childTree->parent == &(abisE1TsNode->bicTreeRoot))
    {
      INIT_OAMS_TREE(&(abisE1TsNode->bicTreeRoot));
      abisE1TsNode->status = ABIS_E1_STATUS_NO_BIC;
    }
   
    FREE(bicNode);   

}
/********************************* Function  Header********************************
Function Name  :getAbisE1NodeStatus
Parameters     :bicTei
Return type    :I_U8 
Purpose        :this function returns the abis E1 node status
Other Note     :
 ************************************************************************************/
I_U8 getAbisChainStatus(BicTei bicTei)
{
    I_U8           status;
	 AbisE1TsNode 	 *abisE1TsNode	 = NULL;
	 I_S32 		    e1Id			    = -1;
   if ((GET_BTS_TYPE() == R3_BTS) || (GET_BTS_TYPE() == R2_BTS_IP))
   {
     return ZERO;
   }

    LOG_PRINT(INFO,"\n Entering getAbisChainStatus function for bic tei %d ",bicTei);
	 e1Id = getE1IdFromTei(&gabisE1List,bicTei);
    if(e1Id == -1)
    {
      LOG_PRINT(INFO,"\n In function getAbisChainStatus:E1 id not found for tei %d ",bicTei);
      return ZERO;
    }
    /*get the e1Id value on the basis of bicTei from the bicTeiMap table*/
    abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
    if(abisE1TsNode == NULL)
    {
      LOG_PRINT(INFO,"\n In function getAbisChainStatus:abisE1TsNode node not \
      found for bicTei %d",bicTei);
      return ZERO;
    }
    status = abisE1TsNode->status;
    LOG_PRINT(INFO,"\n In function getAbisE1NodeStatus :Abis E1 node status %d ",status);
    return status;
}
/********************************* Function  Header********************************
Function Name     :updateAbisChainStatus
Parameters        :bicTei,status
Return type       :void 
Purpose           :this function update the abis E1 node staus for the based on the
                   bicTei passed
Other Note        :
 ************************************************************************************/
void updateAbisChainStatus(BicTei bicTei,I_U8 status)
{
	 AbisE1TsNode 	 *abisE1TsNode	 = NULL;
	 I_S32 		    e1Id			    = -1;

   if ((GET_BTS_TYPE() == R3_BTS) || (GET_BTS_TYPE() == R2_BTS_IP))
   {
     return;
   }
    LOG_PRINT(INFO,"\n Entering updateAbisChainStatus function for bic tei %d ",bicTei);

	 e1Id = getE1IdFromTei(&gabisE1List,bicTei);
    if(e1Id == -1)
    {
      LOG_PRINT(INFO,"\n In function updateAbisChainStatus:E1 id not found for tei %d ",bicTei);
      return;
    }
    abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
    if(abisE1TsNode == NULL)
    {
      LOG_PRINT(INFO,"\n In function updateAbisChainStatus:abisE1TsNode node not \
      found for bicTei %d",bicTei);
      return;
    }
    abisE1TsNode->status = status;
    LOG_PRINT(INFO,"\n In function updateAbisE1NodeStatus :Abis E1 node \
    status updated to  %d ",abisE1TsNode->status);
}
/********************************* Function  Header********************************
Function Name     :getFirstBicFromTei
Parameters        :bicTei
Return type       :I_U32 
Purpose           :this function returns the first bic attached to an abis chain
                   with the given bicTei bicTei passed
Other Note        :
 ************************************************************************************/
I_U32 getFirstBicFromTei(BicTei bicTei)
{
    BicNode                     *bicNode       = NULL;
    OamsTree                    *tree          = NULL;
	 AbisE1TsNode 	 	            *abisE1TsNode	= NULL;
	 BicE1TeiMapTableIndices       bicE1TeiMapTableIndices;
   BicE1TeiMapTableApi          *bicE1TeiMapTableApi;
   I_S32                         errCode;
	 I_S32 		 	                   e1Id			   = -1;

    LOG_PRINT(INFO,"\n Entering getFirstBicFromTei function %d",bicTei);
    if ((bicTei >=TEI_RANGE_R2_TDM) && (bicTei <=TEI_MAX_VALUE))
    {
      bicE1TeiMapTableIndices.bicTei = bicTei;
      errCode=getBicE1TeiMapTable(&bicE1TeiMapTableIndices,&bicE1TeiMapTableApi);
      if ( errCode != CLIB_SUCCESS)
      { 
       LOG_PRINT(INFO,"Invalid BTS TEI not found in DB"); 
       return ZERO;
      }
      else
      {
       return bicE1TeiMapTableApi->btsId ;
      }
    }
/*  LOG_PRINT(INFO,"\n Entering getFirstBicFromTei function %d",bicTei);*/
   
	 e1Id = getE1IdFromTei(&gabisE1List,bicTei);
    if(e1Id == -1)
    {
      LOG_PRINT(INFO,"\n In function getFirstBicFromTei:E1 id not found for tei %d ",bicTei);
      return ZERO;
    }
    abisE1TsNode=searchTsNodeOnTei(e1Id,bicTei);
    if(abisE1TsNode == NULL)
    {
      LOG_PRINT(INFO,"\n In function getFirstBicFromTei:abisE1TsNode node not \
      found for bicTei %d",bicTei);
      return ZERO;
    }
    tree = abisE1TsNode->bicTreeRoot.firstChild;
    if(tree != &(abisE1TsNode->bicTreeRoot))
    {
      bicNode =  OAMS_TREE_ENTRY(tree, BicNode, bicTree);
      LOG_PRINT(INFO,"\nIn function getFirstBicFromTei : First Bic  id %u for abis E1 node with bicTei %d ",bicNode->bicId,bicTei);
      return bicNode->bicId;
    }
    else
    {
      LOG_PRINT(MAJOR,"\n In function getFirstBicFromTei : No Bic attached to the abis E1 node with bicTei %d ",bicTei);
      return ZERO;
    }
}
/********************************* Function  Header********************************
Function Name     :prepareSlotConnect
Parameters        :I_PVoid sndPtr
Return type       :void 
Purpose           :this function prepares the slot connect message for the bic id
                   and all the upstream bic's bicTei passed
Other Note        :
 ************************************************************************************/
void prepareSlotConnect(I_PVoid sndPtr)
{
    BicIdentifier bicId;
    BicIdentifier parentBicId;
    BicTei        bicTei;
    BicNode       *bicNode   = NULL;
    OamsTree      *tree      = NULL;
    I_S32         toBeFreed;

    I_S32         returnVal = ZERO;
    I_U32         *ptrxId   = NULL;
    I_U32         trxCount;

    /*lapdTs maintains the lapd timeslot for all the trx attached with a bic*/
    I_U8          *lapdTs   = NULL;
    /*firstTsTraffic maintains the lapd timeslot for all the trx attached with a bic*/
    I_U8          *firstTsTraffic   = NULL;
    /*secondTsTraffic maintains the lapd timeslot for all the trx attached with a bic*/
    I_U8          *secondTsTraffic   = NULL;
    /*startTs maintains the start timeslot for all the trx attached with the bic*/
    I_U8          *startTs  = NULL;


    bicId = ((OamsBichContext*)sndPtr)->bicId;
    parentBicId = ((OamsBichContext*)sndPtr)->parentBicId;
    bicTei = ((OamsBichContext*)sndPtr)->bicTei;

   
    LOG_PRINT(INFO,"\n Entering prepareSlotConnect function for bic id %u parentBicId %u Tei %d",\
    bicId,parentBicId,bicTei);


    bicNode = searchBic(bicId,bicTei);
    if(bicNode == NULL)
    {
      LOG_PRINT(INFO,"\n In function prepareSlotConnect :Bic id %u not found in the chain",bicId);
      return;
    }
    else
    {
      tree = &(bicNode->bicTree); 
      LOG_PRINT(INFO,"\nIn function prepareSlotConnect : Build slot connect map");
    
      /*get all the trx attached with the bic*/
      returnVal = getAllPtrxTrxTable(bicId, &ptrxId, &trxCount);
      if(returnVal == CLIB_SUCCESS)
      {
         lapdTs = (I_U8*)MALLOC(sizeof(I_U8)*trxCount); 
         firstTsTraffic = (I_U8*)MALLOC(sizeof(I_U8)*trxCount); 
         secondTsTraffic = (I_U8*)MALLOC(sizeof(I_U8)*trxCount); 
         startTs = (I_U8*)MALLOC(sizeof(I_U8)*trxCount); 
         if(lapdTs == NULL || startTs == NULL || firstTsTraffic == NULL || secondTsTraffic == NULL)
         {
            LOG_PRINT(CRITICAL,"\n Memory Allocation failure for startTs or lapdTs");
            if(lapdTs != NULL)
               FREE(lapdTs);
            if(startTs != NULL)
               FREE(startTs);
            if( firstTsTraffic != NULL)
               FREE(firstTsTraffic);
            if( secondTsTraffic != NULL)
               FREE(secondTsTraffic);
            return;
         }
          /*get the lapd timeslot for all the trx attached with bic and assign it to the 
          lapdTs array*/
          
          /*get the start timeslot for all the trx attached with bic and assign it to the 
          start ts array*/
         /* R2.2 Changes start */
         if((getStartTs(ptrxId,trxCount,startTs) && 
            getTrxTs(ptrxId,trxCount,lapdTs, firstTsTraffic, secondTsTraffic) ) == BICH_FAILURE )
         {
            LOG_PRINT(CRITICAL,"getStartTs or getLapdTs function failed :exiting prepareSlotConnect");
            FREE(lapdTs);
            FREE(startTs);
            FREE(firstTsTraffic);
            FREE(secondTsTraffic);
            return;
         }

          /*create the slot connect message for the bic and its upstream bic*/
         if(parentBicId == ZERO)
         {
            sendSlotConnectMsg(bicId,bicId,bicId,trxCount,bicTei,lapdTs,startTs,firstTsTraffic,secondTsTraffic);
         }
         else
         {
            buildUpStreamSlotConnMap(tree,bicId,bicId,bicId,trxCount,bicTei,lapdTs,firstTsTraffic,secondTsTraffic);
            sendSlotConnectMsg(bicId,bicId,bicId,trxCount,bicTei,lapdTs,startTs,firstTsTraffic,secondTsTraffic);
         }
         FREE(lapdTs);
         FREE(startTs);
         FREE(firstTsTraffic);
         FREE(secondTsTraffic);
         /* R2.2 Changes End */
         free(ptrxId);
       }
      else
      {
          LOG_PRINT(INFO,"\n CLIB fail for getAllPtrxTrxTable");
      }
   }
}

/********************************* Function  Header********************************
Function Name     :prepareSlotDisConnect
Parameters        :I_PVoid sndPtr,void (*sendBicParentNotAvail)
Return type       :void 
Purpose           :this function prepares the slot disconnect message for the bic id 
                   it also informs the bicid and all the downstream bic id of link failure
Other Note        :
 ************************************************************************************/
void prepareSlotDisConnect(I_PVoid sndPtr,void (*sendBicParentNotAvail)(I_U32) )
{
    BicIdentifier  bicId;
    BicIdentifier  parentBicId;
    BicTei         bicTei;
    I_S32          toBeFreed;
   
    if ((GET_BTS_TYPE() == R3_BTS) || (GET_BTS_TYPE() == R2_BTS_IP))
    {
        return;
    }
    bicId = ((OamsBichContext*)sndPtr)->bicId;
    parentBicId = ((OamsBichContext*)sndPtr)->parentBicId;
    bicTei = ((OamsBichContext*)sndPtr)->bicTei;
   

    LOG_PRINT(INFO,"\nIn function prepareSlotDisConnect : Prepare slot disconnect message for Bic Id \
    %u ParentBicId %u ",bicId,parentBicId);

    prepareDisconnectedChildList(parentBicId,bicId,bicTei,sendBicParentNotAvail);
}

/********************************* Function  Header********************************
Function Name     :getFirstDsBicFromBicList
Parameters        :I_PVoid rcvPtr
Return type       :I_U32 
Purpose           :This function search for the first Down Stream  BIC in the 
                   child List corresponding to the from BicId which detects DS_LINK_FAIL
Other Note        :
 ************************************************************************************/
I_U32 getFirstDsBicFromBicList(I_PVoid rcvPtr)
{
   CsappAbihmBichDsLinkFail *dsLinkFailPtr ;
   BicNode                  *bicNode          = NULL;
   BicNode                  *tmpPtr           = NULL;   
   BicTei                    bicTei;
   I_U32                     fromBicId;
   I_U8                      childListLength;
   I_U8                      counter;
   OamsTree                 *fromBicOamsTree  =NULL;
   OamsTree                 *dsBicOamsTree    =NULL;
   
   LOG_PRINT(DEBUG, "In function getFirstDsBicFromBicList");
   dsLinkFailPtr = (CsappAbihmBichDsLinkFail *)(rcvPtr);

   if(dsLinkFailPtr == NULL)
      return BICH_FAILURE;

   bicTei= dsLinkFailPtr->bicTei ;
   fromBicId =dsLinkFailPtr->bicId ;
   childListLength = dsLinkFailPtr->numBic ;
   LOG_PRINT(INFO,"getFirstDsBicFromBicList : ParentBic Id %u ChildlistLength %d ",\
   fromBicId,childListLength);
   bicNode = searchBic(fromBicId,bicTei);

   if(bicNode == NULL)
   {
      LOG_PRINT(MAJOR,"getFirstDsBicFromBicList:Search fail for parent bic id %u ",fromBicId);
      return BICH_FAILURE;
   }
   fromBicOamsTree = &(bicNode->bicTree);
   for(counter=ZERO ; counter<childListLength ; counter++)
   {
      tmpPtr = NULL;
      LOG_PRINT(INFO,"Inside Counter : dsLinkFailPtr->bicIdList[counter] %u ",dsLinkFailPtr->bicIdList[counter]);
      tmpPtr = searchBic(dsLinkFailPtr->bicIdList[counter],bicTei);
      if(tmpPtr == NULL)
         continue;
       dsBicOamsTree = &(tmpPtr->bicTree);
       if(dsBicOamsTree->parent ==fromBicOamsTree)
       {
           LOG_PRINT(DEBUG, "First DownStream Bic corresponding to from BIC ID [%u] is [%u]",fromBicId,tmpPtr->bicId);
           return(tmpPtr->bicId);
       }
   }
   return BICH_FAILURE;
}
/* CS4.0: Changes for HA Start */
I_Void oamsTreeDelFreeChilds(OamsTree *head, I_U32 memberOffset)
{
   OamsTree  *ptr, *tmpPtr;

   for (ptr = (head)->firstChild, tmpPtr = ptr->nextChild;
	ptr != (head);
	ptr = tmpPtr, tmpPtr = ptr->nextChild)
   {
      if(ptr->firstChild == ptr)
      {
         OAMS_TREE_DEL(ptr, head); 
         LOG_PRINT(INFO,"Freeing %x",(I_PVoid)((I_S8 *)ptr - memberOffset));
	 FREE((I_PVoid)((I_S8 *)ptr - memberOffset));
      }
      else
         oamsTreeDelFreeChilds(ptr,memberOffset);
   }
}

I_Void freeE1TsNode(I_U32 e1Id)
{
   AbisE1Node        *ptrE1Node = NULL;
   OamsTsList        *ptr = NULL;
   OamsTsList	     *tmpPtr = NULL;
   AbisE1TsNode      *rootTree = NULL;
   I_U32             memberOffset;
    
   memberOffset = (I_U32)(&((BicNode *)0)->bicTree);
   LOG_PRINT(INFO,"\n Entering freeE1TsNode function for e1Id %d",e1Id);
   ptrE1Node = searchAbisE1Id(&gabisE1List,e1Id);
   /*search for the e1 id ..if  found then*/ 
   if(ptrE1Node != NULL)
   {
      /*the e1 id is added to the list so remove */
      /*all the ts for the e1 id and the bic's connected with it*/
      if(!IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
      {
         /*traverse through all the ts for the e1 id*/
	 LOG_PRINT(INFO,"\n freeE1TsNode:Bic Ts List is not empty");
	 OAMS_TS_LIST_FOR_EACH(ptr, tmpPtr, &(ptrE1Node->abisChainList))
	 {
	    /*if bic is connected with the ts then delete it */
	    rootTree = OAMS_LIST_ENTRY(ptr,AbisE1TsNode,tsList);
	    while(!IS_OAMS_TREE_EMPTY(&(rootTree)->bicTreeRoot))
   	    {
		LOG_PRINT(INFO,"\n freeE1TsNode:Bic present in the tree for timeslot %d ",rootTree->timeSlot);
                oamsTreeDelFreeChilds ( &(rootTree)->bicTreeRoot, memberOffset);
	    }
           INIT_OAMS_TREE(&(rootTree->bicTreeRoot));
	   OAMS_TS_LIST_DEL_N_FREE(ptr, AbisE1TsNode, tsList, FREE);
         }
      }
      if(IS_OAMS_TS_LIST_EMPTY(&(ptrE1Node->abisChainList)))
      {
         LOG_PRINT(INFO,"\n freeE1TsNode:Initialize the TS List for e1 Id %d ",e1Id);
         INIT_OAMS_TS_LIST(&(ptrE1Node->abisChainList));
      }
   }
   else
   {
      LOG_PRINT(INFO,"\n freeE1TsNode:Bic Ts list empty");
   }
}
I_Void freeE1Node(I_U32 e1Id)
{
   AbisE1Node   *ptrE1Node = NULL;
   OamsList     *ptr       = NULL;
   OamsList     *tmpPtr    = NULL;
   OamsList     *abisChainList = &gabisE1List;

   if(IS_OAMS_LIST_EMPTY(abisChainList))
   {
      LOG_PRINT(INFO,"\n No abis E1 node in the list"); 
      return;
   }
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,abisChainList)
   {
      /* use macro OAMS_LIST_ENTRY to find AbisE1Node*  - compare bicTei*/
      ptrE1Node = OAMS_LIST_ENTRY(ptr,AbisE1Node,e1List);
      if(ptrE1Node != NULL)
      {
         LOG_PRINT(INFO," Comparing AbisE1Node for E1Id %d with ptrE1Node->e1Id %d", e1Id, ptrE1Node->e1Id );
         /*if abisE1 node with matching E1Id found then delete the abisE1node*/
         if(ptrE1Node->e1Id == e1Id)
         {
            /* return AbisE1Node */
            LOG_PRINT(INFO,"Freeing AbisE1Node %p",ptrE1Node);
            OAMS_LIST_DEL_N_FREE(ptr, AbisE1Node, e1List, FREE)
            //FREE(ptrE1Node);
            LOG_PRINT(INFO," Deleted AbisE1Node for E1Id %d", e1Id);
            return;
         }
      }
   }
   /*if abis E1 node with matching E1Id not found then return NULL*/
   LOG_PRINT(INFO,"AbisE1Node deletion failed for E1Id %d", e1Id);
   return;
}
/* CS4.0: Changes for HA End */


