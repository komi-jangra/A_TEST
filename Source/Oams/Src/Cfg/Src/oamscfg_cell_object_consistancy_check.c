/***********************************File Header ***************************   
   File Name      : oamcfg_cell_object_consistancy_check.c
Purpose        : This file contains function definitions for consistency checks
performed by CFG during Cell Unlock procedure.
Project        : IMR OAM - BSC
Subsystem    : BSC
Author         : Aricent Banaglore
CSCI ID        :
Version        :
 ************************************* End **********************************/

#include <oamscfg_includes.h>

I_U8 validateCellParamDependency(CellPerTableApi *cellTablePtr)
{
   LOG_PRINT(LOG_INFO,"In function validateCellParamDependency()");

   LaTableIndices LAIndices;
   LaTableApi *la=PNULL;   
   ChnGrpTableApi *chnGrp=PNULL;
   ChnGrpTableApi *tempChnGrpTableApiPtr=PNULL;
   /* Max ARFCN per Channel Group = 18 
       Max TRX's = 18
       => MAX ARFCN poosible in system = 18*18=384 
       changed arfcnList size from 1000 to 400
       */
  //I_U32 arfcnList[400];
   I_U32 arfcnList[400]={0}; /*30677 Gaurav Sinha*/
	 I_U8 visited = I_FALSE; /*30677 Gaurav Sinha*/
   I_U32 chngrpRwoCount;
   I_U32 i,j,temp=0,band=0;
   I_S32 k;
   I_Bool foundBcchChannelGroup = 0;
   I_Bool foundBcchInBothChannelGroup[2] = {0};
   CsNeighCellsTableApi *csNeighCells=PNULL;
   CsNeighCellsTableApi *tempCsNeighCellsTableApiPtr=PNULL;
   PsCellTableIndices  pscellTableIndices;
   PsCellTableApi *pscellTable=PNULL;
   RaTableIndices RAIndices;
   RaTableApi *ra=PNULL;
   BssTableApi *bssTable=PNULL;
   BssPsPreConfigTableApi*bssPsPreConfigTableApiPtr = PNULL;
   CellPerTableApi *cellTable=PNULL;
   CellPerTableIndices cellTableIndices;
   I_U32 arfcnLentgh = 0;
   I_U32 bcchCount=0,bcchType=0;
   CsExternalCellTableIndices CSEXTERNALCELLIndices;
   CsExternalCellTableApi *csExternalCell=PNULL;
   ArfcnListTableIndices  ARFCNListIndices;
   ArfcnListTableApi  *ARFCNList=PNULL;
   /*CS3.0 Changes : Start */ 
   HoCtrlTableApi *hoCtrlTablePtr=PNULL;
   HoCtrlTableIndices hoCtrlTableIndex;
   CsPwrCtrlTableApi *csPwrCtrlTablePtr=PNULL;
   CsPwrCtrlTableIndices csPwrCtrlTableIndex;
   /*CS3.0 Changes : End */
   I_U32 count =0;
   I_U16 outSize;
   /*Get all the chngrps for this cell*/
   I_U8 bcch =1;
   I_U8 bcchSdcch4 = 2;
   I_U32 bcchChannelGroupIndex = 0;
   I_U32 numContiguousPdch = 0;
   I_S32 ret = CM_FAILURE;
   I_S32 numDualTrafficChn = 0;
   I_U32 sumOfChan;
   if(getallBssTable(&bssTable,&count,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"Error getting BSS Table ");
      return OAMS_RSLT_FAILURE; /* Bug Fixed : Mantis# 3676*/
   }

   /* If psAllowed = PS_ALLOWED in Cell table chck if no row exists in 
    * BSSPs table, return Failure.
    */
   if (PS_ALLOWED == cellTablePtr->psAllowed)
   {
      ret = getallBssPsPreConfigTable(&bssPsPreConfigTableApiPtr,&count,&outSize); 
      if (CLIB_SUCCESS == ret && 0 < count)
      {
         free(bssPsPreConfigTableApiPtr); 
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"Error getting BSSPsPreConfig Table, Error Code = [%d] ", ret);
         return OAMS_RSLT_FAILURE; /* Bug Fixed : Mantis# 3676*/
      }
   }

   if(getAllChnGrpForCellH(cellTablePtr->cellId,cellTablePtr->lac,&chnGrp,&chngrpRwoCount,&outSize) == CLIB_SUCCESS)
   {
      for(i=0;i<chngrpRwoCount;i++)
      { 
         foundBcchChannelGroup =0;
         /* Consistency check for 1 & 2 */
         tempChnGrpTableApiPtr = (ChnGrpTableApi*)((I_U8 *)chnGrp + (i *outSize));
         band = tempChnGrpTableApiPtr->band;

         /* Check if Cell Table Band and Channel group band are same or not */


         if (tempChnGrpTableApiPtr->band != cellTablePtr->freqBandBcch  )
         {

            LOG_PRINT(LOG_CRITICAL,"Cell Table Band and channel group band is not equal ,tempChnGrpTableApiPtr->band = %d ,cellTablePtr->freqBandBcch = %d ", tempChnGrpTableApiPtr->band, cellTablePtr->freqBandBcch);
            free(chnGrp); 
            free(bssTable); 
            return OAMS_RSLT_FAILURE;                 
         }
         //ExtendedCell - here change need to be done for only as BCCH+CCCH+SDCCH/4 
         //from here
        // this check to be  for ExtendedCell  
         if (tempChnGrpTableApiPtr->bcchCcch == 1 || tempChnGrpTableApiPtr->bcchCcch == 2 )
         {
            if(TRUE == cellTablePtr->isCellExtended)
            {
               LOG_PRINT(LOG_CRITICAL,"ExtendedCell-1:Configuration other than BCCH+CCCH+SDCCH/4 is not allowed");
               free(chnGrp); 
               free(bssTable); 
               return OAMS_RSLT_FAILURE;                 
            }  
            bcchCount++;
            foundBcchChannelGroup = 1;
            bcchChannelGroupIndex= i;
            bcchType = bcch;
            if (bcchCount > 1)
            {
               /* More than one BCCH Channel Group or BCCH Channel Group */
               /* contains both BCCH_CCCH and BCCH_CCCH_SDCCH_4          */
               LOG_PRINT(LOG_CRITICAL,"More than one BCCH Channel Group exist for the Cell");
               free(chnGrp); 
               free(bssTable); 
               return OAMS_RSLT_FAILURE;                 
            } /* End for bcchCount check */
         } /* End for check for finding BCCH Channel Group */ 
         if (tempChnGrpTableApiPtr->bcchCcchSdcch4 == 1)
         {
            bcchCount++;
            foundBcchChannelGroup = 1;
            bcchType = bcchSdcch4;
            if (bcchCount > 1)
            {
               /* More than one BCCH Channel Group or BCCH Channel Group */
               /* contains both BCCH_CCCH and BCCH_CCCH_SDCCH_4          */
               LOG_PRINT(LOG_CRITICAL,"More than one BCCH Channel Group exist for the Cell");
               free(chnGrp); 
               free(bssTable); 
               return OAMS_RSLT_FAILURE;
            } /* End for bcchCount check */
         } /* End for check for finding BCCH Channel Group */ 
         if (tempChnGrpTableApiPtr->bcchCcch > 0)
         {
            
            if(TRUE == cellTablePtr->isCellExtended)
            {
               LOG_PRINT(LOG_CRITICAL,"ExtendedCell-2:Configuration other than BCCH+CCCH+SDCCH/4 is not allowed");
               free(chnGrp); 
               free(bssTable); 
               return OAMS_RSLT_FAILURE;                 
            }  
           /* Code added by Sanjeev Fixed for Mantis #2085  Start..*/ 
            if( tempChnGrpTableApiPtr->sdcch8 ==  0)
            { 
               /* If bcchCcch is present then sdcch8 should be present...*/
               LOG_PRINT(LOG_CRITICAL,"SDCCH is not present in Channel Group, since bcchCcch is present.."); 
               free(chnGrp); free(bssTable); return OAMS_RSLT_FAILURE;

            }    
            /* Code added by Sanjeev Fixed for Mantis #2085  End..*/ 
            if ( i != bcchChannelGroupIndex)
            {
               /* BCCH_CCCH should be present in only BCCH Channel Group */
               LOG_PRINT(LOG_CRITICAL,"BCCH_CCCH is not present in only BCCH Channel Group"); 
               free(chnGrp); free(bssTable); return OAMS_RSLT_FAILURE;
            } /* End of check to ensure BCCH CHNGRP */
            else
            {
               /* BCCH_CCCH present in BCCH Channel Group */
               if (tempChnGrpTableApiPtr->bcchCcch > 2)
               {
                  /* In BCCH Channel Group, Max No of BCCH_CCCH allowed is 2 */
                  free(chnGrp); free(bssTable); return OAMS_RSLT_FAILURE;
               } /* End of check for Max BCCH_CCCH in BCCH CHNGRP */
            } /* End of else */
         } /* End of check if BCCH_CCCH >0 */

         if (tempChnGrpTableApiPtr->sdcch8> 0)
         {
            if(TRUE == cellTablePtr->isCellExtended)
            {
               LOG_PRINT(LOG_CRITICAL,"ExtendedCell -3 :Configuration other than BCCH+CCCH+SDCCH/4 is not allowed");
               free(chnGrp); 
               free(bssTable); 
               return OAMS_RSLT_FAILURE;                 
            }  
            if ( tempChnGrpTableApiPtr->bcchCcch ==0 && tempChnGrpTableApiPtr->bcchCcchSdcch4 == 0 )
            {
               /* SDCCH_8 should be present in only BCCH Channel Group */
               LOG_PRINT(LOG_CRITICAL,"SDCCH_8 is present in Non BCCH Channel Group");
               free(chnGrp); free(bssTable); return OAMS_RSLT_FAILURE;
            } /* End of check to ensure BCCH CHNGRP */
            else
            {
               /* SDCCH_8 present in BCCH Channel Group */
               if (tempChnGrpTableApiPtr->sdcch8 > 2)
               {
                  /* In BCCH Channel Group, Max No of SDCCH_8 allowed is 2 */
                  LOG_PRINT(LOG_CRITICAL,"SDCCH_8 value is > 2 ");
                  /* Fix for Mantis #4051 Start*/
                  free(chnGrp); 
                  free(bssTable); 
                  /* Fix for Mantis #4051 End*/
                  return OAMS_RSLT_FAILURE;
               } /* End of check for Max SDCCH_8 in BCCH CHNGRP */
            } /* End of else */
         } /* End of check if SDCCH_8 >0 */
        // Extended Cell - Till here 
         /* CHECK: Number of ARFCNs within a CHNGRP needs to be greater or equal than
             the number of all defined channels in the chnGrp divided by 8 (rounded
             up to next integer) */
         if ((tempChnGrpTableApiPtr->validArfcns) < 
               (I_U32)((tempChnGrpTableApiPtr->bcchCcchSdcch4 +
                            tempChnGrpTableApiPtr->bcchCcch +
                            tempChnGrpTableApiPtr->sdcch8 +
/*Changes PCU R2.5 Aricent -- Start*/
                            tempChnGrpTableApiPtr->dualTraffic) / 8.0 + 0.5))
/*Changes PCU R2.5 Aricent -- END*/
         {
            LOG_PRINT(LOG_CRITICAL," Number of ARFCNs within a CHNGRP is < all defined channels in the chnGrp divided by 8");
            /* Fix for Mantis #4051 Start*/
            free(chnGrp); 
            free(bssTable); 
            /* Fix for Mantis #4051 End*/
            return OAMS_RSLT_FAILURE; 
         } /* End of CHECK */

         /*Chnages done for Mantis 11778 Starts*/
         sumOfChan =  tempChnGrpTableApiPtr->bcchCcchSdcch4 + tempChnGrpTableApiPtr->bcchCcch +
                      tempChnGrpTableApiPtr->sdcch8 + tempChnGrpTableApiPtr->dualTraffic;   
         if(sumOfChan == 0)
         {
            LOG_PRINT(LOG_CRITICAL," Number of each channel in a CHNGRP is zero");
            free(chnGrp); 
            free(bssTable); 
            return OAMS_RSLT_FAILURE; 
         }  
         /*Chnages done for Mantis 11778 Ends*/

         /* Changes for MantiId:0011775*/  
         //Extended Cell checks to be addded should be to 4 instead of 8 )
            
           if((cellTablePtr->isCellExtended == TRUE) && (sumOfChan < 4) )
           {
              LOG_PRINT(LOG_CRITICAL," Extended Cell:Sum of channels in a CHNGRP is less than 4");
              free(chnGrp); 
              free(bssTable); 
              return OAMS_RSLT_FAILURE;                 
           }  
           else if((sumOfChan < 8) &&(FALSE == cellTablePtr->isCellExtended))
           { 
            LOG_PRINT(LOG_CRITICAL," Sum of channels in a CHNGRP is less than 8 but Extended Cell is not supported in Cell ");
            free(chnGrp); 
            free(bssTable); 
            return OAMS_RSLT_FAILURE; 
           }  
         /* Changes for MantiId:0011775*/  
          
          
/*Changes PCU R2.5 Aricent -- Start*/
/*
         if( 0 == tempChnGrpTableApiPtr->dualTraffic % 8)
         {
            numDualTrafficChn += tempChnGrpTableApiPtr->dualTraffic;
         }
         else
         {
            numDualTrafficChn += ( (tempChnGrpTableApiPtr->dualTraffic / 8) + 1) * 8;
         }
*/
/*Changes PCU R2.5 Aricent -- Stop*/
         if (foundBcchChannelGroup)
         {
            if (checkBCCHConsistency(cellTablePtr,tempChnGrpTableApiPtr,bcchType,numContiguousPdch) == OAMS_RSLT_FAILURE)
            {
               /* BCCH CHNGRP specific consistency check failed */
               LOG_PRINT(LOG_CRITICAL," BCCH CHNGRP specific consistency check failed");
               /* Fix for Mantis #4051 Start*/
               free(chnGrp); 
               free(bssTable); 
               /* Fix for Mantis #4051 End*/
               return OAMS_RSLT_FAILURE;
            } /* End of BCCH CHNGRP related consistency check*/
         } /* End of foundBcchChannelGroup = True */
         else
         {
            /* Non-BCCH CHNGRP, perform non-BCCH CHNGRP consistency check */

            /* Check for number of validArfcns in CHNGRP */
            if (tempChnGrpTableApiPtr->validArfcns > 18)
            {
               /* Only 18 validArfcns are allowed in non-BCCH CHNGRPs */
               LOG_PRINT(LOG_CRITICAL," validArfcns > 18 in non-BCCH CHNGRPs");
               free(chnGrp); free(bssTable); return OAMS_RSLT_FAILURE;
            } /* End of check for validArfcns */

         } /* End of else i.e foundBCCHChannelGroup = False */

         /* Create ARFCN list to check if all ARFCN are present in ARFCNList Table */
         /* 1. Check ARFCN should be present only once within the CHNGRPs of the cell */
         /* 2.Also check if the gap between 2 ARFCNs is greater than minChannelGap   */
         /* Creation of ARFCN List : Insertion Sort Technique is used to create the ARFCN List, So,before insertion, we are checking
             Abiove 1 & 2 coinditions.. */   
         for (j = 0;j < tempChnGrpTableApiPtr->validArfcns;j++)
         {
            if (i==0 && j==0)
            {
               arfcnList[0] = tempChnGrpTableApiPtr->arfcn1;
               LOG_PRINT(LOG_DEBUG,"1:: In this case arfcnList[0]::[%d],arfcnLentgh::[%d]",tempChnGrpTableApiPtr->arfcn1,arfcnLentgh);  /*30677 Gaurav Sinha*/
               arfcnLentgh++;
            }
            else
            {
               switch(j)
               {
                  case 0:
                     if(i!=0)
                        temp =tempChnGrpTableApiPtr->arfcn1;
                     LOG_PRINT(LOG_DEBUG,"2:: In this case temp::[%d]",tempChnGrpTableApiPtr->arfcn1); /*30677 Gaurav Sinha*/ 
                     break;
                  case 1:
                     temp =tempChnGrpTableApiPtr->arfcn2;
                     break;
                  case 2:
                     temp =tempChnGrpTableApiPtr->arfcn3;
                     break;
                  case 3:
                     temp =tempChnGrpTableApiPtr->arfcn4;
                     break;
                  case 4:
                     temp =tempChnGrpTableApiPtr->arfcn5;
                     break;
                  case 5:
                     temp =tempChnGrpTableApiPtr->arfcn6;
                     break;
                  case 6:
                     temp =tempChnGrpTableApiPtr->arfcn7;
                     break;
                  case 7:
                     temp =tempChnGrpTableApiPtr->arfcn8;
                     break;
                  case 8:
                     temp =tempChnGrpTableApiPtr->arfcn9;
                     break;
                  case 9:
                     temp =tempChnGrpTableApiPtr->arfcn10;
                     break;
                  case 10:
                     temp =tempChnGrpTableApiPtr->arfcn11;
                     break;
                  case 11:
                     temp =tempChnGrpTableApiPtr->arfcn12;
                     break;
                  case 12:
                     temp =tempChnGrpTableApiPtr->arfcn13;
                     break;
                  case 13:
                     temp =tempChnGrpTableApiPtr->arfcn14;
                     break;
                  case 14:
                     temp =tempChnGrpTableApiPtr->arfcn15;
                     break;
                  case 15:
                     temp =tempChnGrpTableApiPtr->arfcn16;
                     break;
                  case 16:
                     temp =tempChnGrpTableApiPtr->arfcn17;
                     break;
                  /*case 17:
                     temp =tempChnGrpTableApiPtr->arfcn18;
                     break; */
                  default :
                     LOG_PRINT(LOG_CRITICAL,"Error: All ARFCN are Not present in ARFCNList Table..");
                  /* Fix for Mantis #4051 Start*/
                     free(chnGrp); 
                     free(bssTable); 
                  /* Fix for Mantis #4051 End*/
                     return OAMS_RSLT_FAILURE;
               }
               k= arfcnLentgh;      
               /* Logic for Insertion sort..*/   
               while ((k-1 >= 0) && (arfcnList[k-1] >= temp) ) 
                  /* old: k >=0 ; new: k-1 >= 0 ; Mantis #3337 */ 
               {
                  /* Also check if the gap between 2 ARFCNs is greater than minChannelGap   */
                 /* remove equality check for Mantis 17659 */
                  if ((( abs(arfcnList[k-1]-temp) < bssTable->minChannelGap) ))      
                  {
                     LOG_PRINT(LOG_CRITICAL," The Gap between two Arfcn is less than minChannelGap defined in Bss Table.. ");
  //LOG_PRINT(LOG_CRITICAL,"1::arfcnList[k-1]::[%d] temp::[%d] arfcnLentgh::[%d] bssTable->minChannelGap::[%d]",arfcnList[k-1],temp,arfcnLentgh,bssTable->minChannelGap);
                     free(chnGrp); free(bssTable);
                     return OAMS_RSLT_FAILURE;

                  }
                  //LOG_PRINT(LOG_CRITICAL,"1::arfcnList[k-1]::[%d] temp::[%d] arfcnLentgh::[%d]",arfcnList[k-1],temp,arfcnLentgh);
                  /* Check ARFCN should be present only once within the CHNGRPs of the cell */  
                  if ((arfcnList[k-1]==temp))      
                  {
                     LOG_PRINT(LOG_CRITICAL," Duplicate Arfcn Found  (Same Arfcn is present more than once)... ");
                     free(chnGrp); free(bssTable);
                     return OAMS_RSLT_FAILURE;

                  }
                  arfcnList[k] = arfcnList[k-1];
                  k = k - 1;    
									visited=I_TRUE;/*30677 Gaurav Sinha*/  
                //LOG_PRINT(LOG_CRITICAL,"1::arfcnList[k-1]::[%d] temp::[%d] arfcnList[k]::[%d] k::[%d] arfcnLentgh::[%d]",arfcnList[k-1],temp,arfcnList[k],k,arfcnLentgh);
               }               
               /* Also check if the gap between 2 ARFCNs is greater than minChannelGap   */

                 /* remove equality check for Mantis 17659 */
               //if ((( abs(temp - arfcnList[k-1]) < bssTable->minChannelGap) ))      
							if(visited==I_TRUE) 
							{
							 visited=I_FALSE;
							 LOG_PRINT(LOG_CRITICAL,"visited flag is true, resetting it:: abs(temp:[%d] - arfcnList[k]:[%d]) performed /\ RESULT : %d",temp,arfcnList[k],abs(temp - arfcnList[k]));
               if ((( abs(temp - arfcnList[k]) < bssTable->minChannelGap) )) /*30677 Gaurav Sinha*/ 
               {
                  LOG_PRINT(LOG_CRITICAL," The Gap between two Arfcn is less than minChannelGap defined in Bss Table.. ");
                  //LOG_PRINT(LOG_CRITICAL,"2::arfcnList[k-1]::[%d] temp::[%d] bssTable->minChannelGap::[%d]",arfcnList[k-1],temp,bssTable->minChannelGap);
                  free(chnGrp); free(bssTable);
                  return OAMS_RSLT_FAILURE;

               }
               //LOG_PRINT(LOG_CRITICAL,"2::arfcnList[k-1]::[%d] temp::[%d] arfcnList[k]::[%d] k::[%d] arfcnLentgh::[%d]",arfcnList[k-1],temp,arfcnList[k],k,arfcnLentgh);
               arfcnList[k] = temp;                   
               arfcnLentgh++;    
               //LOG_PRINT(LOG_CRITICAL,"2::arfcnList[k-1]::[%d] temp::[%d] arfcnList[k]::[%d] k::[%d] arfcnLentgh::[%d] bssTable->minChannelGap::[%d]",arfcnList[k-1],temp,arfcnList[k],k,arfcnLentgh,bssTable->minChannelGap); /*30677 Gaurav Sinha*/ 
							}
							else
							{
								LOG_PRINT(LOG_CRITICAL,"visited flag is false:: abs(temp:[%d] - arfcnList[k-1]:[%d]) performed /\ RESULT : %d",temp,arfcnList[k-1],abs(temp - arfcnList[k-1]));
                	if ((( abs(temp - arfcnList[k-1]) < bssTable->minChannelGap) ))    
								{ 
                  LOG_PRINT(LOG_CRITICAL," The Gap between two Arfcn is less than minChannelGap defined in Bss Table.. ");
                  //LOG_PRINT(LOG_CRITICAL,"2::arfcnList[k-1]::[%d] temp::[%d] bssTable->minChannelGap::[%d]",arfcnList[k-1],temp,bssTable->minChannelGap);
                  free(chnGrp); free(bssTable);
                  return OAMS_RSLT_FAILURE;

                }
               //LOG_PRINT(LOG_CRITICAL,"2::arfcnList[k-1]::[%d] temp::[%d] arfcnList[k]::[%d] k::[%d] arfcnLentgh::[%d]",arfcnList[k-1],temp,arfcnList[k],k,arfcnLentgh);
               arfcnList[k] = temp;                   
               arfcnLentgh++;    
               //LOG_PRINT(LOG_CRITICAL,"2::arfcnList[k-1]::[%d] temp::[%d] arfcnList[k]::[%d] k::[%d] arfcnLentgh::[%d] bssTable->minChannelGap::[%d]",arfcnList[k-1],temp,arfcnList[k],k,arfcnLentgh,bssTable->minChannelGap); /*30677 Gaurav Sinha*/ 
							}
							
            }
         } /* Loop end for validArfns for a CHNGRP */
         foundBcchInBothChannelGroup[i] = foundBcchChannelGroup;
      } /* End for loop for CHNGRP count */
      
      /*R2.6 Changes Start, If no BCCH present in all Channel groups then cell unlock fails*/
      foundBcchChannelGroup = 0;
      for(i=0;i<chngrpRwoCount;i++)
      {
         foundBcchChannelGroup = foundBcchChannelGroup|foundBcchInBothChannelGroup[i];
      }
      if(foundBcchChannelGroup == 0)
      {
         LOG_PRINT(LOG_CRITICAL,"No Bcch channel defined in all Channel Groups");
         free(chnGrp); 
         free(bssTable);
         return OAMS_RSLT_FAILURE;
      }
      /* R2.6 Changes end*/
      
      /* To check all the arcfns are present in the arfcnlist table */
      for(i = 0 ; i< arfcnLentgh;i++)
      {
         LOG_PRINT(LOG_DEBUG," -----  ARFCN  = %d",arfcnList[i]);

         ARFCNListIndices.band = band;
         ARFCNListIndices.arfcn = arfcnList[i];
         if(getArfcnListTable(&ARFCNListIndices,&ARFCNList) != CLIB_SUCCESS)
         {
            /* Did not get ARFCN in ARFCNList table */
            LOG_PRINT(LOG_CRITICAL,"ARFCN is not present in ARFCNList table"); 
            free(chnGrp); free(bssTable); 
            return OAMS_RSLT_FAILURE;
         }
         switch(cellTablePtr->freqBandBcch)
         {
             case GSM850:
                if(arfcnList[i] < 128 || arfcnList[i] > 251)
                {
                LOG_PRINT(LOG_CRITICAL,"Arfcn %d is not in %d band",arfcnList[i],cellTablePtr->freqBandBcch);
                return OAMS_RSLT_FAILURE;
                }  
             break;  
             case GSM900:
               //if(arfcnList[i] < 1 || arfcnList[i] > 124) Temporary Patch for Tanzania E-GSM support 02-Jan-2017
               if(arfcnList[i] < 1 || arfcnList[i] > 1023)
               {
                  LOG_PRINT(LOG_CRITICAL,"Arfcn %d is not in %d band",arfcnList[i],cellTablePtr->freqBandBcch);
                  /* Fix for Mantis #4051 Start*/
                  free(chnGrp);
                  free(bssTable);
                  /* Fix for Mantis #4051 End*/

                  return OAMS_RSLT_FAILURE;
               }
             break;
             case GSM1800:
               if(arfcnList[i] < 512 || arfcnList[i] > 885)
               {
                  LOG_PRINT(LOG_CRITICAL,"Arfcn %d is not in %d band",arfcnList[i],cellTablePtr->freqBandBcch);
                  /* Fix for Mantis #4051 Start*/
                  free(chnGrp);
                  free(bssTable);
                  /* Fix for Mantis #4051 End*/
                  return OAMS_RSLT_FAILURE;
               }
             break;
             case GSM1900:
                   if(arfcnList[i] < 512 || arfcnList[i] > 810)
                   {
                   LOG_PRINT(LOG_CRITICAL,"Arfcn %d is not in %d band",arfcnList[i],cellTablePtr->freqBandBcch);
                   return OAMS_RSLT_FAILURE;
                   }
             break;  
             default:
               LOG_PRINT(LOG_CRITICAL,"Invalid freqBandBcch in cellTable");
         }
      } /* end of loop for arfcnLentgh */
      free(chnGrp);
   } /* end of if getChngrpForCell */

   /* Bug Fixed - Mantis #  : Start */
   else
   {
      /* ChnGrp is Not Present for a Cell */
      LOG_PRINT(LOG_MAJOR,"No ChnGrp Present for CellId : %u, Lac : %u",
				cellTablePtr->cellId, cellTablePtr->lac); 
      free(bssTable);
      return OAMS_RSLT_FAILURE;
   }
   /* Bug Fixed - Mantis #  : End */

   /* Check LAC defined for the cell is prsent in the LA table */
   LAIndices.lac = cellTablePtr->lac;
   if(getLaTable(&LAIndices,&la) != CLIB_SUCCESS)
   {
      /* LAC for the cell not there in LA table */
      LOG_PRINT(LOG_CRITICAL,"LAC for the cell is not present in LA table"); 
      free(bssTable);
      return OAMS_RSLT_FAILURE;
   }
   /* If PSStatus is allowed for this cell, check for corresponding entry in PSCell table */
   if(cellTablePtr->psAllowed == PS_ALLOWED)
   {
      pscellTableIndices.cellId = cellTablePtr->cellId;
      pscellTableIndices.lac = cellTablePtr->lac;
      if(getPsCellTable(&pscellTableIndices,&pscellTable) !=  CLIB_SUCCESS)
      {
         /* PSCell table does not have any entry corresponding to this cell */
         LOG_PRINT(LOG_CRITICAL,"PsCell is not configured for this cell PsCellTable"); 
         free(bssTable);
         return OAMS_RSLT_FAILURE;
      }
      else 
      {
         /* Check whether LAC and RAC of PSCell is there in RA table &*/
         /* PSCell table has entry corresponding to this cell */
         RAIndices.lac = pscellTable->lac;
         RAIndices.rac = pscellTable->rac;
         if (getRaTable(&RAIndices,&ra) != CLIB_SUCCESS)
         {  
            /* LAC+RAC for the PSCell is not there in RA table */
            LOG_PRINT(LOG_CRITICAL,"LAC+RAC for the PSCell is not present in RA table"); 
            free(bssTable);
            return OAMS_RSLT_FAILURE;
         } /* Check for getRA Success */
      } /* Check for getPSCellTable returning success */
      free(pscellTable);
   } /* Check for PSStatus Allowed in the cell */

   /* To check internal CS Neighbour cells are present in internal Cell Table */
   if (getCsInternalNeighCellsForCell(cellTablePtr->cellId,cellTablePtr->lac,&csNeighCells,&count,&outSize)== CLIB_SUCCESS)
   {     
      for (k = 0; k < count; k++)
      {
         tempCsNeighCellsTableApiPtr = (CsNeighCellsTableApi*)((I_U8*)csNeighCells + (k *outSize));
         cellTableIndices.cellId = tempCsNeighCellsTableApiPtr->neighborCellId;
         cellTableIndices.lac = tempCsNeighCellsTableApiPtr->neighborLac;

         if (getCellPerTable(&cellTableIndices,&cellTable) ==CLIB_SUCCESS)
         {
            if (tempCsNeighCellsTableApiPtr->neighborMnc !=  bssTable->mnc || tempCsNeighCellsTableApiPtr->neighborMcc != bssTable->mcc)
            {
               /* Internal CS Neighbor Cell's MNC and MCC not present in BSS table */
               LOG_PRINT(LOG_CRITICAL,"Internal CS Neighbor Cell's MNC and MCC not present in BSS table");
               free(bssTable); free(csNeighCells); free(cellTable); return OAMS_RSLT_FAILURE;
            } /* End of check for MNC and MCC */
         } /* End of getCellTable */
         else
         {
            /* Internal CS Neighbor Cell for the cell not present in Cell table */
            LOG_PRINT(LOG_CRITICAL,"Internal CS Neighbor Cell for the cell not present in Cell table");
            free(bssTable);
            return OAMS_RSLT_FAILURE;
         }
      } /* End of for loop for count of Internal CS Neighbor Cells */
      free(csNeighCells);
      free(cellTable);
   } /* End if condition for getCsInternalNeighCellsForCell */

   /* To check External CS Neighbour cells are present in CSExternal Table */
   if (getCsExternalNeighCellsForCell(cellTablePtr->cellId,cellTablePtr->lac,&csNeighCells,&count,&outSize) == CLIB_SUCCESS)
   {
      for (k = 0; k < count; k++)
      {
         tempCsNeighCellsTableApiPtr = (CsNeighCellsTableApi*)((I_U8*)csNeighCells + (k *outSize));

         CSEXTERNALCELLIndices.csExtCellId = tempCsNeighCellsTableApiPtr->neighborCellId;
         CSEXTERNALCELLIndices.lac = tempCsNeighCellsTableApiPtr->neighborLac;
         CSEXTERNALCELLIndices.mnc =tempCsNeighCellsTableApiPtr->neighborMnc;
         CSEXTERNALCELLIndices.mcc = tempCsNeighCellsTableApiPtr->neighborMcc;

         if (getCsExternalCellTable(&CSEXTERNALCELLIndices,&csExternalCell) != CLIB_SUCCESS)
         {
            /* External CS Neighbor Cell for the cell not present in Cell table */
            LOG_PRINT(LOG_CRITICAL,"External CS Neighbor Cell for the cell not present in Cell table");
            free(bssTable);
            free(csNeighCells);
            return OAMS_RSLT_FAILURE;
         } /* End of getCSEXTERNALCELL */
      } /* End of for loop for count of External CS Neighbor Cells */
      free(csNeighCells);
      free(csExternalCell);
   } /* End if condition for getCsInternalNeighCellsForCell */

   free(bssTable);
   /* CS3.0 Change - Start */ 
   csPwrCtrlTableIndex.cellId = cellTablePtr->cellId;
   csPwrCtrlTableIndex.lac = cellTablePtr->lac;
   hoCtrlTableIndex.cellId = cellTablePtr->cellId;
   hoCtrlTableIndex.lac = cellTablePtr->lac;
   if(getCsPwrCtrlTable(&csPwrCtrlTableIndex,&csPwrCtrlTablePtr) != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_CRITICAL,"getCsPwrCtrlTable DB call is geting failed..");
      return OAMS_RSLT_FAILURE;
   }
   if(getHoCtrlTable(&hoCtrlTableIndex,&hoCtrlTablePtr) != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_CRITICAL,"getHoCtrlTable DB call is geting failed..");
      return OAMS_RSLT_FAILURE;
   }
  
   /* CS3.0 Changes : End */
   LOG_PRINT(LOG_INFO,"Exiting function validateCellParamDependency()");
   return OAMS_RSLT_SUCCESS;
}

I_U32 checkBCCHConsistency(CellPerTableApi *cellTable,ChnGrpTableApi *chnGrp,I_U32 bcchType , I_U32 numContiguousPdch)
{
   LOG_PRINT(LOG_INFO,"In function checkBCCHConsistency()");
   PsCellTableIndices pscellTableIndices;
   PsCellTableApi *pscellTable=NULL;
   I_Bool returnFlag = TRUE ;

   pscellTableIndices.cellId = chnGrp->cellId; 
   pscellTableIndices.lac = chnGrp->lac;

   if(getPsCellTable(&pscellTableIndices,&pscellTable) != CLIB_SUCCESS)
      LOG_PRINT(LOG_INFO,"checkBCCHConsistency: getPsCellTable Failed");
   /* check for number of valid arfcns in case of BCCH CHNGRP */
   if (chnGrp->validArfcns != 1)
   {
      /* Only 1 ARFCN is allowed in BCCH CHNGRP */ 
      LOG_PRINT(LOG_CRITICAL,"ARFCN allowed in BCCH CHNGRP is != 1");
      returnFlag = FALSE;
   } /* end for validArfcn check */

   /* Check for BCCH ARFCN same in Cell table and BCCH CHNGRP */ 
   if (cellTable->bcchArfcn != chnGrp->arfcn1)
   {
      /* bcchArfcn stored in Cell table should be same as arfcn in BCCH CHNGRP */
      LOG_PRINT(LOG_CRITICAL,"bcchArfcn stored in Cell table is not same as  arfcn in BCCH CHNGRP");
      returnFlag = FALSE;
   } /* end for BCCH ARFCN check */

   /*Check for the value of "tsc" in BCCH Channel group is same as "bcc" configured in Cell table*/
   if (cellTable->bcc != chnGrp->tsc)
   {
      /* bcchArfcn stored in Cell table should be same as arfcn in BCCH CHNGRP */
      LOG_PRINT(LOG_CRITICAL,"bcc stored in Cell table is not same as  tsc in BCCH CHNGRP");
      returnFlag = FALSE;
   } /* end for BCCH "tsc" check */
   /* R2.4 Changes End */

   /* Specific checks if BCCH CHNGRP contains BCCH_CCCH */
   if (bcchType == BCCH_CCCH_TYPE)
   {
      /* R2.8 Change Start: If CBCH is NOT mapped on CCCH+SDCCH/4 then BS_AG_BLKS_RES should be non-Zero */
      if (chnGrp->cbch == I_TRUE && cellTable->bsAgBlksRes == ZERO)
      {
         LOG_PRINT(LOG_CRITICAL,"CBCH is mapped on SDCCH/8 channel But BS_AG_BLKS_RES = 0");
         returnFlag = FALSE;
      }

      /* Check total number of channel types */
      if ((chnGrp->bcchCcch + chnGrp->sdcch8 + chnGrp->dualTraffic/*chnGrp->pdch + chnGrp->tch*/ ) > 8)
      {
         /* Addition of BCCH_CCCH, SDCCH_8 and PDCH should be less than 8 */ 
         LOG_PRINT(LOG_CRITICAL," Addition of BCCH_CCCH, SDCCH_8 and PDCH is > 8 ");
         returnFlag = FALSE;
      } /* End of check for total channels */

      /* Check for BS_AG_BLKS_RES */
      if ((cellTable->bsAgBlksRes > 7) || (cellTable->bsAgBlksRes < 0))
      { 
         /* If BCCH_CCCH, Range of BS_AG_BLS_RES is 0..7 */ 
         LOG_PRINT(LOG_CRITICAL,"For BCCH Channel Group Range of BS_AG_BLKS_RES is 0..7 ");
         returnFlag = FALSE;
      } /* End of check for BS_AG_BLS_RES */
   } /* End of check of bcchType = BCCH_CCCH */
   else if (bcchType == BCCH_CCCH_SDCCH_TYPE)
   {
     /* R2.8 Change Start: If CBCH is mapped on CCCH+SDCCH/4 then BS_AG_BLKS_RES should be checked */
     if (chnGrp->cbch == I_TRUE)
     {
        LOG_PRINT(LOG_CRITICAL,"CBCH is mapped on CCCH+SDCCH/4, No need to check value of BS_AG_BLKS_RES");
     }

     if ((I_TRUE == cellTable->isCellExtended)&&((chnGrp->bcchCcchSdcch4 + chnGrp->sdcch8 + chnGrp->dualTraffic /*chnGrp->pdch + chnGrp->tch*/ ) > 4))
     {
       LOG_PRINT(LOG_CRITICAL," Extended Cell:Sum of channels in a CHNGRP is > 4");
       return OAMS_RSLT_FAILURE;                 
     }  
     /* Check total number of channel types */
     else if ((chnGrp->bcchCcchSdcch4 + chnGrp->sdcch8 + chnGrp->dualTraffic /*chnGrp->pdch + chnGrp->tch*/ ) > 8)
     {
       /* Addition of BCCH_CCCH_SDCCH_4, SDCCH_8 and PDCH should be less than 8 */ 
       LOG_PRINT(LOG_CRITICAL,"Addition of BCCH_CCCH_SDCCH_4, SDCCH_8 and PDCH is > 8");
       returnFlag = FALSE;
     } /* End of check for total channels */

     /* Check for BS_AG_BLKS_RES */
     if ((cellTable->bsAgBlksRes > 2) || (cellTable->bsAgBlksRes < 0))
     {
       /* If BCCH_CCCH_SDCCH_4, Range of BS_AG_BLS_RES is 0..2 */ 
       LOG_PRINT(LOG_CRITICAL,"For  BCCH_CCCH_SDCCH_4, Range of BS_AG_BLKS_RES is 0..2");
       returnFlag = FALSE;
     } /* End of check for BS_AG_BLS_RES */
   } /* End of check of bcchType = CCCH_SDCCH_4 */


   LOG_PRINT(LOG_INFO,"Exiting function checkBCCHConsistency()");

   if(returnFlag == FALSE) 
      return OAMS_RSLT_FAILURE;
   else
   {
      return  OAMS_RSLT_SUCCESS;
   }
}

/***************************************** ************************************
   Function Name  : validateCsPwrCtrlparameters
Description    : Contains functions for consistency checks performed by CFG
during CsPwrCtrl Table Update Procedure.
Return type    : I_U8
 ********************************* End *****************************************/

I_U8 validateCsPwrCtrlparameters(CsPwrCtrlTableApi *recievedMsg)
{
   I_U8 returnFlag = OAMS_RSLT_SUCCESS;
   I_S32 ret;
   I_U32 outRows = 0;
   I_U16 outSize;
   CsPwrCtrlPreconfigTableApi *pwrCtrlPreconfigData = PNULL;
   I_U8 *str = "CsPwrCtrlTable Consistency Check Failed:";
/*Start changes for Mantis 4115 */
   HoCtrlTableApi *hoCtrlTablePtr=PNULL;
   HoCtrlTableIndices hoCtrlTableIndex;
/*End changes for Mantis 4115*/
   ret = getallCsPwrCtrlPreconfigTable(&pwrCtrlPreconfigData, &outRows, &outSize);

   if(ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "validateCsPwrCtrlparameters(): getallCsPwrCtrlPreconfigTable() failed.");
      return OAMS_RSLT_FAILURE;
   }

   if(pwrCtrlPreconfigData == NULL)   
   {
      LOG_PRINT(LOG_CRITICAL, "validateCsPwrCtrlparameters(): getallCsPwrCtrlPreconfigTable(): No data in table.");
      return OAMS_RSLT_FAILURE;
   }

   if(!(recievedMsg->lRxLevUlP < recievedMsg->uRxLevUlP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected (lRxLevUlP < uRxLevUlP), Recd: lRxLevUlP=0x%x >= uRxLevUlP=0x%x",str, recievedMsg->lRxLevUlP, recievedMsg->uRxLevUlP);
      returnFlag = OAMS_RSLT_FAILURE;
   }

   if(!((recievedMsg->uRxLevUlP - recievedMsg->lRxLevUlP) > pwrCtrlPreconfigData->incrStepSizeP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected ((uRxLevUlP - lRxLevUlP) > incrStepSizeP),Recd: ((uRxLevUlP=0x%x - lRxLevUlP=0x%x)) <= incrStepSizeP=0x%x",str, recievedMsg->uRxLevUlP, recievedMsg->lRxLevUlP, pwrCtrlPreconfigData->incrStepSizeP);
      returnFlag = OAMS_RSLT_FAILURE;
   }

   if(!((recievedMsg->uRxLevUlP - recievedMsg->lRxLevUlP) > pwrCtrlPreconfigData->safetyMarginP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected ((uRxLevUlP - lRxLevUlP) > safetyMarginP), Recd: ((uRxLevUlP=0x%x - lRxLevUlP=0x%x)) <= safetyMarginP=0x%x ",str, recievedMsg->uRxLevUlP, recievedMsg->lRxLevUlP,pwrCtrlPreconfigData->safetyMarginP);
      returnFlag =  OAMS_RSLT_FAILURE;
   }

   if(!(recievedMsg->lRxQualUlP > recievedMsg->uRxQualUlP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected (lRxQualUlP > uRxQualUlP), Recd: lRxQualUlP= 0x%x <= uRxQualUlP=0x%x ",str, recievedMsg->lRxQualUlP,recievedMsg->uRxQualUlP);
      returnFlag =  OAMS_RSLT_FAILURE;
   }

   if(!(recievedMsg->lRxLevDlP < recievedMsg->uRxLevDlP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected (lRxLevDlP < uRxLevDlP), Recd: lRxLevDlP= 0x%x >= uRxLevDlP=0x%x ",str, recievedMsg->lRxLevDlP,recievedMsg->uRxQualUlP);
      returnFlag =  OAMS_RSLT_FAILURE;
   }              

   if(!((recievedMsg->uRxLevDlP - recievedMsg->lRxLevDlP) > pwrCtrlPreconfigData->incrStepSizeP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected ((uRxLevDlP - lRxLevDlP) > incrStepSizeP), Recd: ((uRxLevDlP= 0x%x - lRxLevDlP=0x%x) <= incrStepSizeP=0x%x) ",str, recievedMsg->uRxLevDlP,recievedMsg->lRxLevDlP,pwrCtrlPreconfigData->incrStepSizeP);
      returnFlag =  OAMS_RSLT_FAILURE;
   }

   if(!((recievedMsg->uRxLevDlP - recievedMsg->lRxLevDlP) > pwrCtrlPreconfigData->safetyMarginP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected ((uRxLevDlP - lRxLevDlP) > safetyMarginP), Recd: ((uRxLevDlP= 0x%x - lRxLevDlP=0x%x) <= safetyMarginP=0x%x) ",str, recievedMsg->uRxLevDlP, recievedMsg->lRxLevDlP,pwrCtrlPreconfigData->safetyMarginP);
      returnFlag =  OAMS_RSLT_FAILURE;
   }

   if(!(recievedMsg->lRxQualDlP > recievedMsg->uRxQualDlP))
   {
      LOG_PRINT(LOG_CRITICAL,"%s: Expected (lRxQualDlP > uRxQualDlP), Recd: lRxQualDlP=0x%x < uRxQualDlP=0x%x ",str, recievedMsg->lRxQualDlP,recievedMsg->uRxQualDlP);
      returnFlag =   OAMS_RSLT_FAILURE;
   }

   free(pwrCtrlPreconfigData);

    /* Mantis 4115 */
   hoCtrlTableIndex.cellId = recievedMsg->cellId;
   hoCtrlTableIndex.lac = recievedMsg->lac;

   if(getHoCtrlTable(&hoCtrlTableIndex,&hoCtrlTablePtr) != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO,"getHoCtrlTable DB call is geting failed..");
      return returnFlag;
   }

   if(!(hoCtrlTablePtr->lRxLevUlH < recievedMsg->lRxLevUlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxLevUlH(HoCtrlTable) is not lesser than lRxLevUlP(CsPwrCtrlTable)");
      returnFlag =   OAMS_RSLT_FAILURE;
   }
   if(!(hoCtrlTablePtr->lRxLevDlH < recievedMsg->lRxLevDlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxLevDlH(HoCtrlTable) is not lesser than lRxLevDlP(CsPwrCtrlTable)");
      returnFlag =   OAMS_RSLT_FAILURE;
   }
   if(!(hoCtrlTablePtr->lRxQualUlH > recievedMsg->lRxQualUlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxQualUlH(HoCtrlTable) is not greater than lRxQualUlP(CsPwrCtrlTable)");
      returnFlag =   OAMS_RSLT_FAILURE;
   }
   if(!(hoCtrlTablePtr->lRxQualDlH > recievedMsg->lRxQualDlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxQualDlH(HoCtrlTable) is not greater than lRxQualDlP(CsPwrCtrlTable)");
       returnFlag =   OAMS_RSLT_FAILURE;
   }
   /* Mantis 4115 */

   free(hoCtrlTablePtr);
   return returnFlag;
} 

/********************************* Function  Header*****************************
Function Name   : chkConsistencyForCsNeighCellTable()
Parameters   	: CsNeighCellsTableApi *rcvdMsgPtr
Return type   	: I_Bool
Purpose      	: It check consistency checks for the CsNeighCellsTable. 
		  Checks are following :
		  A. For cellType = 0
		     1. Check neighbourMcc & neighbourMnc received in request are 
			same as configured in BssTable.
		     2. Check neighbourCellId & neighbourLac is present in 
			CellPerTable.
		  B. For cellType = 1
		     1. Check corresponding to the neighbourCellId, neighbourLac, 
			neighbourMcc, neighbourMnc a entry must present in 
			CsExternalCellTable.
Other Note   	: Added For On The Fly Changes
 *******************************************************************************/
I_Bool chkConsistencyForCsNeighCellTable(CsNeighCellsTableApi *rcvdMsgPtr)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   CellPerTableIndices cellTableInd;
   CellPerTableApi *cellTableApiPtr = NULL;
   CellPerTableApi *cellTableApiPtrSelf = NULL;
   CsExternalCellTableIndices csExtCellTableInd;
   CsExternalCellTableApi *csExtCellTableApiPtr = NULL;
   CsNeighCellsTableApi *tempCsNeighCellTablePtr = PNULL;
   CsNeighCellsTableApi *pNeighCell = PNULL;
   BssTableApi *bssTableApiPtr = NULL;
   I_U32 allowedBand = 0;
   I_U32 neighbourBand = 0, wcdmaBand = 0;
   I_U32 selfBand = 0;
   I_U32 i = 0;
   I_U32 rowsCount = 0;
   I_U16 outSize;
   I_U32 numNeighbours = 0;
   I_U32 numWcdmaFddNeighbours = 0;
   I_Bool  count = FALSE;

   LOG_PRINT(LOG_INFO,"Entering Function : chkConsistencyForCsNeighCellTable");
   if(rcvdMsgPtr->cellType == INTERNAL)
   {
      /* Check MCC & MNC are Correct for Internal Cells */
      dbStatus = getallBssTable(&bssTableApiPtr, &outRow, &outSz);
      if(DBLIB_SUCCESS != dbStatus)
      {
    	    LOG_PRINT(LOG_MAJOR,"BssTable is not Configured at BSC");
          cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
          return FALSE;
      }
      else
      {
	       if( (rcvdMsgPtr->neighborMcc != bssTableApiPtr->mcc) ||
	          (rcvdMsgPtr->neighborMnc != bssTableApiPtr->mnc)  )
	       {
	          LOG_PRINT(LOG_DEBUG,"BSC is not Configured for MCC = %d, MNC = %d",
				         rcvdMsgPtr->neighborMcc, rcvdMsgPtr->neighborMnc);
            free(bssTableApiPtr);
            cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
            return FALSE;
         }
         free(bssTableApiPtr);
      }
      /* Check Neighbour Cell data present in CellPerTable */
      cellTableInd.cellId = rcvdMsgPtr->neighborCellId;
      cellTableInd.lac    = rcvdMsgPtr->neighborLac;
      dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
      if(dbStatus != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG,"CellId = %d, Lac = %d Not Configured at BSC",
     			rcvdMsgPtr->neighborCellId, rcvdMsgPtr->neighborLac);
         cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      	 return FALSE;
      }

      neighbourBand = cellTableApiPtr->freqBandBcch;
      
      cellTableInd.cellId = rcvdMsgPtr->cellId;
      cellTableInd.lac    = rcvdMsgPtr->lac;
      dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtrSelf);
      if(dbStatus != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG,"CellId = %d, Lac = %d Not Configured at BSC",
     			rcvdMsgPtr->cellId, rcvdMsgPtr->lac);
         free(cellTableApiPtr);
         cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      	 return FALSE;
      }

      selfBand = cellTableApiPtrSelf->freqBandBcch;
      if(  ( (selfBand == GSM1900) && (neighbourBand == GSM1800) ) ||
           ( (selfBand == GSM1800) && (neighbourBand == GSM1900) )  ||
           ( (selfBand == GSM850)  && (neighbourBand == GSM900) )  ||
           ( (selfBand == GSM900)  && (neighbourBand == GSM850) )  
         )
      {
         LOG_PRINT(DEBUG,"1900 and 1800 Band or 850 and 900 band Cells Can not be neighbours");
         free(cellTableApiPtrSelf);
         free(cellTableApiPtr);
         cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      	 return FALSE;
      }
      free(cellTableApiPtrSelf);
      free(cellTableApiPtr);
   }
   else
   {
      /* Check Neighbour Cell data present in CsExternalCellTable */
      csExtCellTableInd.csExtCellId = rcvdMsgPtr->neighborCellId;
      csExtCellTableInd.lac	    = rcvdMsgPtr->neighborLac;
      csExtCellTableInd.mnc	    = rcvdMsgPtr->neighborMnc;
      csExtCellTableInd.mcc	    = rcvdMsgPtr->neighborMcc;
      dbStatus = getCsExternalCellTable(&csExtCellTableInd, &csExtCellTableApiPtr);
      if(dbStatus != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG,"CellId = %d, Lac = %d, Mnc = %d, Mcc = %d Not Configured at BSC",
	    	 rcvdMsgPtr->neighborCellId, rcvdMsgPtr->neighborLac, 
				 rcvdMsgPtr->neighborMnc, rcvdMsgPtr->neighborMcc);
         cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
         return FALSE;
      }
      dbStatus = getallBssTable(&bssTableApiPtr, &outRow, &outSz);
      if(DBLIB_SUCCESS == dbStatus)
      {

        if( (rcvdMsgPtr->radioAccessType == WCDMA_FDD) && 
            (bssTableApiPtr->wcdma_FddHoAllowed == NOT_ALLOWED)
          )
         {
            LOG_PRINT(LOG_DEBUG,"Neighbour belonging to WCDMA_FDD is not allowed in BSS Table");
            cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
            free(bssTableApiPtr);
            return FALSE;
         }
         free(bssTableApiPtr);
      } 
      wcdmaBand = csExtCellTableApiPtr->bcchArfcn;
      neighbourBand = csExtCellTableApiPtr->freqBandBcch;

      cellTableInd.cellId = rcvdMsgPtr->cellId;
      cellTableInd.lac    = rcvdMsgPtr->lac;
      dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtrSelf);
      if(dbStatus != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG,"CellId = %d, Lac = %d Not Configured at BSC",
     			rcvdMsgPtr->cellId, rcvdMsgPtr->lac);
         free(csExtCellTableApiPtr);
         cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      	 return FALSE;
      }

      selfBand = cellTableApiPtrSelf->freqBandBcch;

      if(  ( (selfBand == GSM1900) && (neighbourBand == GSM1800) ) ||
           ( (selfBand == GSM1800) && (neighbourBand == GSM1900) )  ||
           ( (selfBand == GSM850)  && (neighbourBand == GSM900) )  ||
           ( (selfBand == GSM900)  && (neighbourBand == GSM850) )  
         )
      {
         LOG_PRINT(DEBUG,"1900 and 1800 Band Cells Can not be neighbours");
         free(cellTableApiPtrSelf);
         free(csExtCellTableApiPtr);
         cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      	 return FALSE;
      }
      free(cellTableApiPtrSelf);
      free(csExtCellTableApiPtr);
   }

   dbStatus = getallCsNeighCellsTable(&tempCsNeighCellTablePtr, &rowsCount, &outSize);
   if(dbStatus == CLIB_SUCCESS)
   {
      /*Changes for Mantis 2352 - There can be at most 18 neighbours of each cell*/
      for(i = 0; i < rowsCount; i++)
      {
         pNeighCell = (CsNeighCellsTableApi *) (((char *) tempCsNeighCellTablePtr ) + (outSize * i));
         if((pNeighCell->cellId == rcvdMsgPtr->cellId) && (pNeighCell->lac == rcvdMsgPtr->lac))
         {
            if(pNeighCell->radioAccessType == WCDMA_FDD)
            {
              numWcdmaFddNeighbours++;
            }  
            numNeighbours++;
            if(allowedBand == 0 )
            {
                if(INTERNAL == pNeighCell->cellType )
                { 
                   cellTableInd.cellId = pNeighCell->neighborCellId;
                   cellTableInd.lac    = pNeighCell->neighborLac;
                   dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
                   if(dbStatus == CLIB_SUCCESS)
                   {
                      if(selfBand != cellTableApiPtr->freqBandBcch)
                      {
                        allowedBand = cellTableApiPtr->freqBandBcch;
                      }   
                      free(cellTableApiPtr);
                   }
                }
                else    
                {
                   /* Check Neighbour Cell data present in CsExternalCellTable */
                   csExtCellTableInd.csExtCellId = pNeighCell->neighborCellId;
                   csExtCellTableInd.lac	    = pNeighCell->neighborLac;
                   csExtCellTableInd.mnc	    = pNeighCell->neighborMnc;
                   csExtCellTableInd.mcc	    = pNeighCell->neighborMcc;
                   dbStatus = getCsExternalCellTable(&csExtCellTableInd, &csExtCellTableApiPtr);
                   if(dbStatus == DBLIB_SUCCESS)
                   {
                      if((selfBand != csExtCellTableApiPtr->freqBandBcch) && (pNeighCell->radioAccessType != WCDMA_FDD))
                      {
                        allowedBand = csExtCellTableApiPtr->freqBandBcch;
                      }   
                      free(csExtCellTableApiPtr);
                   }
                }
            }  
         }
      }
      LOG_PRINT(LOG_DEBUG,"Neighbour Cells Count = %d, allowedBand:%d",numNeighbours, allowedBand);
      free(tempCsNeighCellTablePtr);
   }
   if (numNeighbours >= CFG_MAX_NEIGHBOUR_CELLS)
   {
      LOG_PRINT(LOG_INFO,"Max Neighbours for this Cell Already present in DB");
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      return FALSE;
   }
   if ((numWcdmaFddNeighbours >= CFG_MAX_NUM_NEIGHBOUR_WCDMA_FDD_CELL) && (rcvdMsgPtr->radioAccessType == WCDMA_FDD))
   {
      LOG_PRINT(LOG_INFO,"Max wcdma Neighbours for this Cell Already present in DB");
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES_WCDMA_FDD);
      return FALSE;
   }
   count = getCountValueForWcdma(rcvdMsgPtr,wcdmaBand);
   if (count == FALSE)
   {
      LOG_PRINT(LOG_INFO,"Max Neighbours for this Wcdma_Fdd Cell Already present in DB");
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES_WCDMA_FDD);
      return FALSE;
   }  
 
   if((allowedBand != 0) && (rcvdMsgPtr->radioAccessType == GSM))
   {
      if(  (allowedBand != neighbourBand) &&
           (selfBand != neighbourBand)  )   
      {
         LOG_PRINT(DEBUG,"NeighBour with band : %d can't be added, only band allowed :%d and %d",
            neighbourBand, allowedBand, selfBand);
         cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
         return FALSE;
      }
   } 
   LOG_PRINT(LOG_INFO,"Exiting Function : chkConsistencyForCsNeighCellTable");
   return TRUE;
}

/********************************* Function  Header*****************************
Function Name   : isCellUnBarred()
Parameters   	: CellPerTableApi *rcvdMsgPtr
Return type   	: I_Bool
Purpose      	: It return TRUE when a Cell is Unbarred and returns FALSE when 
		  a Cell is barred.
Other Note   	: Added For On The Fly Changes
 *******************************************************************************/
I_Bool isCellUnBarred(I_U32 cellId, I_U32 lac)
{
   I_S32 dbStatus = -1;
   I_Bool retStatus = FALSE;
   CellPerTableApi *cellTableApiPtr = NULL;
   CellPerTableIndices cellTableInd;

   LOG_PRINT(LOG_INFO,"Entering Function : isCellUnBarred");

   cellTableInd.lac = lac;
   cellTableInd.cellId = cellId;
   dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_INFO,"isCellUnBarred : Lac = %d, CellId = %d is not Configured at BSC",
					lac, cellId);
   }
   else
   {
      if(ZERO == cellTableApiPtr->cellBarAccess)
      {
	 retStatus = TRUE;
      }
      free(cellTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isCellUnBarred");
   return retStatus;
}

/********************************* Function  Header*****************************
Function Name   : sndCsNeighCellChangeMsgToCellh()
Parameters   	: I_U32 : cellId
		  I_U32 : lac
	  	  I_U16 : mcc
 		  I_U16 : mnc
Return type   	: I_Void
Purpose      	: It send CsNeighChange request to CELLH for those Cells having 
		  neighbours corresponding to the received cellId, lac, mcc, mnc.
Other Note   	: Added For On The Fly Changes
 *******************************************************************************/
I_Void sndCsNeighCellChangeMsgToCellh(I_U32 cellId, I_U32 lac, I_U16 mcc, I_U16 mnc)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO, index = ZERO;
   I_U16 outSz = ZERO;
   I_Bool isDataFound = FALSE;
   I_PVoid tmpPtr = NULL;
   CsNeighCellsTableApi *csNeighCellTableApiPtr = NULL;
   CellPerTableIndices cellTableInd;
   CellPerTableApi *cellTableApiPtr = NULL;
   I_U16 cellIndex = 0;
   OamsCfgCellhCsNeighCellsChange csNeighChangePtr;

   LOG_PRINT(LOG_INFO,"Entering Function : sndCsNeighCellChangeMsgToCellh");

   dbStatus = getallCsNeighCellsTable(&csNeighCellTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)   
   {
      LOG_PRINT(LOG_INFO,"sndCsNeighCellChangeMsgToCellh : No Data in CsNeighCellsTable");
   }
   else
   {
      tmpPtr = csNeighCellTableApiPtr;
      for(index = 0; index < outRow; index++)
      {
	 csNeighCellTableApiPtr = (CsNeighCellsTableApi *) (((I_U8 *)tmpPtr) + (outSz * index));
	 if((ZERO == mcc) &&
	    (ZERO == mnc)
	   )
	 {
	    if((csNeighCellTableApiPtr->neighborLac == lac) &&
	       (csNeighCellTableApiPtr->neighborCellId == cellId)
 	      )
	    {
	       isDataFound = TRUE;
	    }
	 }
	 else
	 {
	    if((lac == csNeighCellTableApiPtr->neighborLac) &&
               (cellId == csNeighCellTableApiPtr->neighborCellId) &&
	       (mcc == csNeighCellTableApiPtr->neighborMcc) &&
	       (mnc == csNeighCellTableApiPtr->neighborMnc)
              )
            {
               isDataFound = TRUE;
            }
	 }
	 if(TRUE == isDataFound)
	 {
	    /* Send Neighbour Change Msg to CELLH if Cell is Unlocked */
	    cellTableInd.cellId = csNeighCellTableApiPtr->cellId;
	    cellTableInd.lac    = csNeighCellTableApiPtr->lac;
	    dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
	    if(dbStatus != DBLIB_SUCCESS)
	    {
	       LOG_PRINT(LOG_INFO,"Cell is Not Configured at BSC");
	    }
	    else if(cellTableApiPtr->adminState == UNLOCKED)
	    {
	       free(cellTableApiPtr);
         getCellIndex(csNeighCellTableApiPtr->lac, csNeighCellTableApiPtr->cellId, &cellIndex);          
	       csNeighChangePtr.cellId = csNeighCellTableApiPtr->cellId;
	       csNeighChangePtr.lac    = csNeighCellTableApiPtr->lac;
               csNeighChangePtr.cellIndex = cellIndex;
	       LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE Msg to CELLH");
	       LOG_PRINT(LOG_DEBUG,"CellId = %d, Lac = %d",csNeighCellTableApiPtr->cellId, 
							   csNeighCellTableApiPtr->lac);
	       cfgSendMessage(&csNeighChangePtr, sizeof(OamsCfgCellhCsNeighCellsChange),
                        ENT_OAMS_CELLH, OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE, 0);
	    }
	    else
	    {
	       LOG_PRINT(LOG_INFO,"Cell is Locked. Not send OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE Msg to CELLH");
	       free(cellTableApiPtr);
	    }
	 }
	 isDataFound = FALSE;
      }
      free(tmpPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : sndCsNeighCellChangeMsgToCellh");
   return;
}


/********************************* Function  Header*****************************
Function Name   : isCellReferenceByNeighbours()
Parameters   	: I_U32 : cellId
		  I_U32 : lac
	  	  I_U16 : mcc
 		  I_U16 : mnc
Return type   	: I_Void
Purpose      	: It return TRUE if received cellId & lac has any reference in 
		  CsNeighCellsTable otherwise it returns FALSE.
Other Note   	: Added For On The Fly Changes
 *******************************************************************************/
I_Bool isCellReferenceByNeighbours(I_U32 cellId, I_U32 lac, I_U16 mcc, I_U16 mnc)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO, index = ZERO;
   I_U16 outSz = ZERO;
   I_Bool isDataFound = FALSE;
   I_PVoid tmpPtr = NULL;
   CsNeighCellsTableApi *csNeighCellTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"Entering Function : isCellReferenceByNeighbours");

   dbStatus = getallCsNeighCellsTable(&csNeighCellTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)   
   {
      LOG_PRINT(LOG_INFO,"isCellReferenceByNeighbours : No Data in CsNeighCellsTable");
   }
   else
   {
      tmpPtr = csNeighCellTableApiPtr;
      for(index = 0; index < outRow; index++)
      {
	 csNeighCellTableApiPtr = (CsNeighCellsTableApi *) (((I_U8 *)tmpPtr) + (outSz * index));
	 if((ZERO == mcc) &&
	    (ZERO == mnc)
	   )
	 {
	    if(((csNeighCellTableApiPtr->neighborLac == lac) &&
	        (csNeighCellTableApiPtr->neighborCellId == cellId)
	       ) ||
	       ((csNeighCellTableApiPtr->lac == lac) &&
		(csNeighCellTableApiPtr->cellId == cellId)
	       )
 	      )
	    {
	       isDataFound = TRUE;
	       break;
	    }
	 }
	 else
	 {
	    if((lac == csNeighCellTableApiPtr->neighborLac) &&
               (cellId == csNeighCellTableApiPtr->neighborCellId) &&
	       (mcc == csNeighCellTableApiPtr->neighborMcc) &&
	       (mnc == csNeighCellTableApiPtr->neighborMnc)
              )
            {
               isDataFound = TRUE;
	       break;
            }
	 }
      }
      free(tmpPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isCellReferenceByNeighbours");
   return isDataFound;
}

/********************************* Function  Header*****************************
Function Name   : isRefFoundForArfcnBsicOfNeigh()
Parameters   	: CsNeighCellsTableApi* rcvMsgPtr
Return type   	: I_Bool
Purpose      	: It return TRUE if received arfcn & bsic are same in serving 
		  cell & neighbour cell or any neighbour cell has same arfcn & 
		  bsic, otherwise it returns FALSE.
Other Note   	: Added For On The Fly Changes
 *******************************************************************************/
I_Bool isRefFoundForArfcnBsicOfNeigh(CsNeighCellsTableApi *rcvMsgPtr)
{
   I_S32 dbStatus = -1;
   I_Bool isRefFound = FALSE;
   I_U32 cellArfcn = ZERO, cellBcc = ZERO, cellNcc = ZERO;
   CellPerTableIndices cellTableInd;
   CellPerTableApi* cellTableApiPtr = NULL;
   CsExternalCellTableApi *csExtCellTableApiPtr = NULL;
   CsExternalCellTableIndices csExtCellTableInd;

   LOG_PRINT(LOG_INFO,"Entering Function : isRefFoundForArfcnBsicOfNeigh");

   /* Get BcchArfcn, Bcc & Ncc of Serving Cell */
   /* For Internal Cell */
   if(INTERNAL == rcvMsgPtr->cellType)
   {
      cellTableInd.lac		= rcvMsgPtr->neighborLac;
      cellTableInd.cellId 	= rcvMsgPtr->neighborCellId;
      dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"isRefFoundForArfcnBsicOfNeigh : CellId : %d, Lac : %d is not Configured",
				 cellTableInd.cellId, cellTableInd.lac);
	       return TRUE;
      }
      cellArfcn = cellTableApiPtr->bcchArfcn;
      cellBcc	= cellTableApiPtr->bcc;
      cellNcc   = gBssNcc;
      free(cellTableApiPtr);
   }
   /* For External Cell */
   if(EXTERNAL == rcvMsgPtr->cellType)
   {
      /* Get Neighbour Information from CsExternalCell Table */
      csExtCellTableInd.mcc		= rcvMsgPtr->neighborMcc;
      csExtCellTableInd.mnc 		= rcvMsgPtr->neighborMnc;
      csExtCellTableInd.lac 		= rcvMsgPtr->neighborLac;
      csExtCellTableInd.csExtCellId 	= rcvMsgPtr->neighborCellId;
      dbStatus = getCsExternalCellTable(&csExtCellTableInd, &csExtCellTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
	       return TRUE;
      }
      cellArfcn = csExtCellTableApiPtr->bcchArfcn;
      cellBcc	= csExtCellTableApiPtr->bcc;
      cellNcc   = csExtCellTableApiPtr->ncc;
      free(csExtCellTableApiPtr);
   }

   isRefFound = isArfcnBsicFoundInNeigh(rcvMsgPtr, cellBcc, cellNcc, cellArfcn);
   if(TRUE == isRefFound)
   {
      return isRefFound;
   }

   isRefFound = isArfcnBsicFoundInNeighTree(rcvMsgPtr->lac, rcvMsgPtr->cellId,
					    cellBcc, cellNcc, cellArfcn, FALSE);
   if(TRUE == isRefFound)
   {
      return isRefFound;
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isRefFoundForArfcnBsicOfNeigh");
   return isRefFound;
}

/********************************* Function  Header*****************************
Function Name   : isArfcnBsicFound()
Parameters   	: CsNeighCellsTableApi* rcvMsgPtr
		  I_U32 : bcc
		  I_U32 : ncc
		  I_U32 : arfcn
Return type   	: I_Bool
Purpose      	: It return TRUE if received arfcn & bsic are same in serving 
		  cell & neighbour cell or any neighbour cell has same arfcn & 
		  bsic, otherwise it returns FALSE.
Other Note   	: 
 *******************************************************************************/
I_Bool isArfcnBsicFound(CsNeighCellsTableApi* rcvMsgPtr, I_U32 bcc, I_U32 ncc, I_U32 arfcn)
{
   I_S32 dbStatus = -1;
   CsExternalCellTableApi *csExtCellTableApiPtr = NULL;
   CsExternalCellTableIndices csExtCellTableInd;
   CellPerTableApi* cellTableApiPtr = NULL;
   CellPerTableIndices cellTableInd;

   LOG_PRINT(LOG_INFO,"Entering Function : isArfcnBsicFound");
   LOG_PRINT(LOG_DEBUG,"isArfcnBsicFound : Received Bcc : %d, Ncc : %d, Arfcn : %d",
					   bcc, ncc, arfcn);

   /* For Internal Cell */
   if(INTERNAL == rcvMsgPtr->cellType)
   {
      cellTableInd.lac		= rcvMsgPtr->neighborLac;
      cellTableInd.cellId 	= rcvMsgPtr->neighborCellId;
      dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
         LOG_PRINT(LOG_MAJOR,"isArfcnBsicFound : CellId : %d, Lac : %d is not Configured",
					cellTableInd.cellId, cellTableInd.lac);
	 return TRUE;
      }
      if((arfcn == cellTableApiPtr->bcchArfcn) &&
         (bcc == cellTableApiPtr->bcc) &&
	 (ncc == gBssNcc)
        )
      {
	 LOG_PRINT(LOG_MAJOR,"isArfcnBsicFound : Received Add Neighbour Request has same Arfcn & Bsic");
         free(cellTableApiPtr);
	 return TRUE;
      }
      free(cellTableApiPtr);
   }
   /* For External Cell */
   if(EXTERNAL == rcvMsgPtr->cellType)
   {
      /* Get Neighbour Information from CsExternalCell Table */
      csExtCellTableInd.mcc		= rcvMsgPtr->neighborMcc;
      csExtCellTableInd.mnc 		= rcvMsgPtr->neighborMnc;
      csExtCellTableInd.lac 		= rcvMsgPtr->neighborLac;
      csExtCellTableInd.csExtCellId 	= rcvMsgPtr->neighborCellId;
      dbStatus = getCsExternalCellTable(&csExtCellTableInd, &csExtCellTableApiPtr);
      if(DBLIB_SUCCESS != dbStatus)
      {
	 return TRUE;
      }
	    LOG_PRINT(LOG_MAJOR,"isArfcnBsicFound : Received Radio Access Type is[%d]",csExtCellTableApiPtr->radioAccessType );
      
      if((arfcn == csExtCellTableApiPtr->bcchArfcn) &&
	 (bcc == csExtCellTableApiPtr->bcc) &&
	 (ncc == csExtCellTableApiPtr->ncc)&&(csExtCellTableApiPtr->radioAccessType != WCDMA_FDD) 
	)
      {
	 LOG_PRINT(LOG_MAJOR,"isArfcnBsicFound : Received Add Neighbour Request has same Arfcn & Bsic");
	 free(csExtCellTableApiPtr);
	 return TRUE;
      }
      free(csExtCellTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isArfcnBsicFound");
   return FALSE;
}

/********************************* Function  Header*****************************
Function Name   : isArfcnBsicFoundInNeighTree()
Parameters   	: I_U32 : lac
		  I_U32 : cellId
		  I_U32 : bcc
		  I_U32 : ncc
		  I_U32 : arfcn
Return type   	: I_Bool
Purpose      	: It return TRUE if received arfcn & bsic are same in serving 
		  cell & neighbour cell or any neighbour cell has same arfcn & 
		  bsic, otherwise it returns FALSE.
Other Note   	: 
 *******************************************************************************/
I_Bool isArfcnBsicFoundInNeighTree(I_U32 lac, I_U32 cellId, I_U32 bcc, I_U32 ncc, 
				   I_U32 arfcn, I_Bool nccChange
				  )
{
   CsNeighCellsTableApi* csNeighCellTableApiPtr = NULL;
   CsNeighCellsTableApi* pNeighCell = NULL;
   I_U32 i = ZERO;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_S32 dbStatus = -1;
   I_Bool isRefFound = FALSE;

   LOG_PRINT(LOG_INFO,"Entering Function : isArfcnBsicFoundInNeighTree");
   LOG_PRINT(LOG_DEBUG,"isArfcnBsicFoundInNeighTree : Received Lac : %d, cellId : %d, Bcc : %d, Ncc : %d, Arfcn : %d",	lac, cellId, bcc, ncc, arfcn);

   /* Check Arfcn & Bsic of all neighbour Cells of Received lac & cellId */
   dbStatus = getallCsNeighCellsTable(&csNeighCellTableApiPtr, &outRow, &outSz);
   if(dbStatus == DBLIB_SUCCESS)
   {
      for(i = 0; i < outRow; i++)
      {
         pNeighCell = (CsNeighCellsTableApi *) (((I_U8 *) csNeighCellTableApiPtr) + (outSz * i));
         if((pNeighCell->cellId == cellId) && 
            (pNeighCell->lac == lac))
         {
	    /* Fixed Mantis #5384 : Start */
	    if((pNeighCell->cellType == INTERNAL) &&
	       ((nccChange == TRUE) || 
		((pNeighCell->neighborLac == gLacOfRcvReq) && 
		 (pNeighCell->neighborCellId == gCellIdOfRcvReq))
	       )
	      )
	    {
	       continue;
	    }
	    /* Fixed Mantis #5384 : End */
   	    isRefFound = isArfcnBsicFound(pNeighCell, bcc, ncc, arfcn);
   	    if(TRUE == isRefFound)
   	    {
      	       free(csNeighCellTableApiPtr);
      	       return isRefFound;
   	    }
	 }
      }
      free(csNeighCellTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isArfcnBsicFoundInNeighTree");
   return isRefFound;
}

/********************************* Function  Header*****************************
Function Name   : isArfcnBsicFoundInNeigh()
Parameters   	: CsNeighCellsTableApi* rcvMsgPtr
		  I_U32 : bcc
		  I_U32 : ncc
		  I_U32 : arfcn
Return type   	: I_Bool
Purpose      	: It return TRUE if received arfcn & bsic are same in serving 
		  cell & neighbour cell or any neighbour cell has same arfcn & 
		  bsic, otherwise it returns FALSE.
Other Note   	: 
 *******************************************************************************/
I_Bool isArfcnBsicFoundInNeigh(CsNeighCellsTableApi* rcvMsgPtr, I_U32 bcc, I_U32 ncc, I_U32 arfcn)
{
   I_S32 dbStatus = -1;
   CellPerTableApi* cellTableApiPtr = NULL;
   CellPerTableIndices cellTableInd;

   LOG_PRINT(LOG_INFO,"Entering Function : isArfcnBsicFoundInNeigh");
   LOG_PRINT(LOG_DEBUG,"isArfcnBsicFoundInNeigh : Received Bcc : %d, Ncc : %d, Arfcn : %d",
					   bcc, ncc, arfcn);

   cellTableInd.lac	= rcvMsgPtr->lac;
   cellTableInd.cellId 	= rcvMsgPtr->cellId;
   dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_MAJOR,"isArfcnBsicFoundInNeigh : CellId : %d, Lac : %d is not Configured",
					cellTableInd.cellId, cellTableInd.lac);
      return TRUE;
   }
   if((arfcn == cellTableApiPtr->bcchArfcn) &&
      (bcc == cellTableApiPtr->bcc) &&
      (ncc == gBssNcc)
     )
   {
      LOG_PRINT(LOG_MAJOR,"isArfcnBsicFoundInNeigh : Received Add Neighbour Request has same Arfcn & Bsic");
      free(cellTableApiPtr);
      return TRUE;
   }
   free(cellTableApiPtr);

   LOG_PRINT(LOG_INFO,"Exiting Function : isArfcnBsicFoundInNeigh");
   return FALSE;
}

/********************************* Function  Header*****************************
Function Name   : isArfcnBsicFoundInNeighTable()
Parameters   	: I_PVoid : rcvPtr
		  I_U8    : reqType
Return type   	: I_Bool
Purpose      	: It return TRUE if received arfcn & bsic are same in serving 
		  cell & neighbour cell or any neighbour cell has same arfcn & 
		  bsic, otherwise it returns FALSE.
Other Note   	: 
 *******************************************************************************/
I_Bool isArfcnBsicFoundInNeighTable(I_PVoid rcvPtr, I_U8 reqType, I_Bool nccChange)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_Bool isRefFound = FALSE;
   I_U32 i = ZERO;
   I_U32 cellId = ZERO, lac = ZERO;
   I_U32 cellArfcn = ZERO, cellBcc = ZERO, cellNcc = ZERO;
   CsNeighCellsTableApi* csNeighCellTableApiPtr = NULL;
   CsNeighCellsTableApi* pNeighCell = NULL;

   LOG_PRINT(LOG_INFO,"Entering Function : isArfcnBsicFoundInNeighTable");
   LOG_PRINT(LOG_DEBUG,"isArfcnBsicFoundInNeighTable : Received Request Type : %d",reqType);

   /* Get BcchArfcn, Bcc & Ncc of Serving Cell */
   if(reqType == ZERO)  /* For Internl Cells */
   {
      CellPerTableApi* cellTableApiPtr = (CellPerTableApi *)(rcvPtr);
      cellId    =  cellTableApiPtr->cellId;
      lac       =  cellTableApiPtr->lac;
      cellArfcn =  cellTableApiPtr->bcchArfcn;
      cellBcc   =  cellTableApiPtr->bcc;
      cellNcc   =  gBssNcc;
   }
   else 	/* For External Cells */
   {
      CsExternalCellTableApi* csExternalTableApiPtr = (CsExternalCellTableApi *)(rcvPtr);
      cellId    =  csExternalTableApiPtr->csExtCellId;
      lac       =  csExternalTableApiPtr->lac;
      cellArfcn =  csExternalTableApiPtr->bcchArfcn;
      cellBcc   =  csExternalTableApiPtr->bcc;
      cellNcc   =  csExternalTableApiPtr->ncc;
   }
   
   dbStatus = getallCsNeighCellsTable(&csNeighCellTableApiPtr, &outRow, &outSz);
   if(dbStatus == DBLIB_SUCCESS)
   {
      for(i = 0; i < outRow; i++)
      {
         pNeighCell = (CsNeighCellsTableApi *) (((I_U8 *) csNeighCellTableApiPtr) + (outSz * i));
         if((pNeighCell->cellId == cellId) && 
            (pNeighCell->lac == lac))
         {
   	    isRefFound = isArfcnBsicFoundInNeighTree(lac, cellId, cellBcc, cellNcc, cellArfcn, nccChange);
   	    if(TRUE == isRefFound)
   	    {
      	       free(csNeighCellTableApiPtr);
      	       return isRefFound;
   	    }
	       }
	 else if((pNeighCell->neighborLac == lac) &&
                 (pNeighCell->neighborCellId == cellId))
	 {
   	    isRefFound = isArfcnBsicFoundInNeigh(pNeighCell, cellBcc, cellNcc, cellArfcn);
  	    if(TRUE == isRefFound)
   	    {
      	       free(csNeighCellTableApiPtr);
      	       return isRefFound;
   	    }
   	    isRefFound = isArfcnBsicFoundInNeighTree(pNeighCell->lac, pNeighCell->cellId, 
							cellBcc, cellNcc, cellArfcn, nccChange);
   	    if(TRUE == isRefFound)
   	    {
      	       free(csNeighCellTableApiPtr);
      	       return isRefFound;
   	    }
	 }
      }
      free(csNeighCellTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isArfcnBsicFoundInNeighTable");
   return isRefFound;
}

/********************************* Function  Header*****************************
Function Name   : chkArfcnBsicForNccChange()
Parameters   	: None
Return type   	: I_Bool
Purpose      	: It return TRUE if configured internal cells have arfcn & bsic 
		  are same in serving cell or any neighbour cell has same arfcn & 
		  bsic, otherwise it returns FALSE.
Other Note   	: 
 *******************************************************************************/
I_Bool chkArfcnBsicForNccChange()
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_Bool isRefFound = FALSE;
   I_U32 i = ZERO;
   I_U8  *tmpTablePtr = NULL;
   CellPerTableApi* cellTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"Entering Function : chkArfcnBsicForNccChange");

   dbStatus = getallCellPerTable(&cellTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS == dbStatus)
   {
      tmpTablePtr = (I_U8 *)(cellTableApiPtr);
      for(i = 0; i < outRow; i++)
      {
	       cellTableApiPtr = (CellPerTableApi *)(tmpTablePtr + (i * outSz));
         LOG_PRINT(LOG_DEBUG,"chkArfcnBsicForNccChange : Lac : %u, CellId : %u",
				         cellTableApiPtr->lac, cellTableApiPtr->cellId);
         isRefFound = isArfcnBsicFoundInNeighTable(cellTableApiPtr, ZERO, TRUE);
         if(TRUE == isRefFound)
         {
            /* bcchArfcn & BSIC is already configured */
            LOG_PRINT(LOG_MAJOR,"chkArfcnBsicForNccChange : BcchArfcn+Bsic is Already Configured for Neighbours");
            cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
	          break;
         }
      }
      free(tmpTablePtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : chkArfcnBsicForNccChange");
   return isRefFound;
}

/********************************* Function  Header*****************************
Function Name   : chkCnstForHoCtrlTable()
Parameters   	: CsNeighCellsTableApi *receivedMsgPtr
Return type   	: I_Bool
Purpose      	: It return TRUE if IRxLevDIH in HoCtrlTable < rxLevMinN in 
		  CsNeighCellsTable, otherwise it returns FALSE.
Other Note   	: 
 *******************************************************************************/
I_Bool chkCnstForHoCtrlTable(CsNeighCellsTableApi *receivedMsgPtr)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_U32 i = ZERO;
   I_U8  *tmpTablePtr = NULL;
   I_Bool status = FALSE;
   HoCtrlTableApi* hoCtrlTableApiPtr = NULL;
   HoCtrlTableIndices hoCtrlTableInd;
   CsNeighCellsTableApi* csNeighCellTableApiPtr = NULL;
   
   LOG_PRINT(LOG_INFO,"Entering Function : chkCnstForHoCtrlTable");

   hoCtrlTableInd.lac     = receivedMsgPtr->lac; 
   hoCtrlTableInd.cellId  = receivedMsgPtr->cellId;
   dbStatus = getHoCtrlTable(&hoCtrlTableInd, &hoCtrlTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      return TRUE;
   }
   else if(hoCtrlTableApiPtr->lRxLevDlH >= receivedMsgPtr->rxLevMinN && (receivedMsgPtr->radioAccessType!=WCDMA_FDD))
   {
      LOG_PRINT(LOG_MAJOR,"Consistancy failed: lRxLevDlH(HoCtrlTable) is not less than rxLevMinN(CsNeighCellsTable)");
      free(hoCtrlTableApiPtr);
      return TRUE;
   }
   free(hoCtrlTableApiPtr);

   dbStatus = getallCsNeighCellsTable(&csNeighCellTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS == dbStatus)
   {
      tmpTablePtr = (I_U8 *)(csNeighCellTableApiPtr);
      for(i = 0; i < outRow; i++)
      {
         csNeighCellTableApiPtr = (CsNeighCellsTableApi *)(tmpTablePtr + (i * outSz));
         if((csNeighCellTableApiPtr->neighborLac == receivedMsgPtr->neighborLac) &&
	    (csNeighCellTableApiPtr->neighborCellId == receivedMsgPtr->neighborCellId)
	   )
	 {
	    hoCtrlTableInd.lac     = csNeighCellTableApiPtr->lac; 
	    hoCtrlTableInd.cellId  = csNeighCellTableApiPtr->cellId;
            dbStatus = getHoCtrlTable(&hoCtrlTableInd, &hoCtrlTableApiPtr);
            if(DBLIB_SUCCESS != dbStatus)
	    {
	       free(tmpTablePtr);
	       return TRUE;
	    }
	    else if(hoCtrlTableApiPtr->lRxLevDlH >= receivedMsgPtr->rxLevMinN && (receivedMsgPtr->radioAccessType!=WCDMA_FDD))
	    {
         LOG_PRINT(LOG_MAJOR,"Consistancy failed: lRxLevDlH(HoCtrlTable) is not less than rxLevMinN(CsNeighCellsTable)");
	       free(tmpTablePtr);
	       free(hoCtrlTableApiPtr);
	       return TRUE;
	    }
	    free(hoCtrlTableApiPtr);
	 }
      } 
      free(tmpTablePtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : chkCnstForHoCtrlTable");
   return status;
}

/********************************* Function  Header*****************************
Function Name   : isCgiUnqInExtAndIntCellTable()
Parameters      : I_PVoid  : receivedMsgPtr 
                  I_U8     : cellType
Return type     : I_Bool
Purpose         : It return TRUE if CGI(CellId, Lac, Mcc, Mnc) is unique among 
                  external and internal cells, otherwise it return FALSE.
Other Note      : Fixed Mantis#6033
 *******************************************************************************/
I_Bool isCgiUnqInExtAndIntCellTable(I_PVoid receivedMsgPtr, I_U8 cellType)
{
   I_U16 mcc          = ZERO;
   I_U16 mnc          = ZERO;
   I_U16 rowSize      = ZERO;
   I_U16 retVal       = ZERO;
   I_U32 cellId       = ZERO;
   I_U32 lac          = ZERO; 
   I_U32 rowCount     = ZERO;
   BssTableApi                     *bssTableApiPtr = PNULL;
   CellPerTableIndices             cellTableInd;
   CellPerTableApi                 *cellTableApiPtr = PNULL;
   CsExternalCellTableIndices      csExtCellTableInd;
   CsExternalCellTableApi          *csExtCellTableApiPtr = PNULL;

   LOG_PRINT(LOG_INFO,"Entering Function : isCgiUnqInExtAndIntCellTable");
   LOG_PRINT(LOG_DEBUG,"isCgiUnqInExtAndIntCellTable : Received cellType : %d", cellType);
   
   if(INTERNAL == cellType)
   {
      /* If cellType is Internal then get cellId & lac from receivedMsgPtr and 
         values of mcc, mnc from BssTable */
      cellId = ((CellPerTableApi *)receivedMsgPtr)->cellId;
      lac    = ((CellPerTableApi *)receivedMsgPtr)->lac;
      retVal = getallBssTable(&bssTableApiPtr, &rowCount, &rowSize);
      if(DBLIB_SUCCESS == retVal)
      {
         mcc = bssTableApiPtr->mcc;
         mnc = bssTableApiPtr->mnc;
	 free(bssTableApiPtr);
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"Get On Bss Table Fail");
         return FALSE;
      }
      /* Check that received CGI value exists in External Cell Table or not */
      csExtCellTableInd.csExtCellId = cellId;
      csExtCellTableInd.lac	    = lac;
      csExtCellTableInd.mnc	    = mnc;
      csExtCellTableInd.mcc	    = mcc;
      retVal = getCsExternalCellTable(&csExtCellTableInd, &csExtCellTableApiPtr);
      if(DBLIB_SUCCESS == retVal)
      {
         free(csExtCellTableApiPtr);
         LOG_PRINT(LOG_MAJOR,"CGI with cellId : %d, lac : %d, mcc : %d, mnc : %d already exist in External cell Table",
                                                                    cellId, lac, mnc, mcc);
         return FALSE;
      }
      else
      {
         return TRUE;
      }
   }
   else
   {
      /* If cellType is External then get cellId,lac,mcc,mnc from receivedMsgPtr */
      cellId = ((CsExternalCellTableApi *)receivedMsgPtr)->csExtCellId;
      lac    = ((CsExternalCellTableApi *)receivedMsgPtr)->lac;
      mcc    = ((CsExternalCellTableApi *)receivedMsgPtr)->mcc;
      mnc    = ((CsExternalCellTableApi *)receivedMsgPtr)->mnc;

      /* Check that received CGI value exists in Internal Cell Table or not */
      cellTableInd.cellId = cellId;
      cellTableInd.lac    = lac;
      retVal = getCellPerTable(&cellTableInd,&cellTableApiPtr);
      if(DBLIB_SUCCESS == retVal)
      {
         free(cellTableApiPtr);
         retVal = getallBssTable(&bssTableApiPtr, &rowCount, &rowSize);
         if(DBLIB_SUCCESS == retVal)
         {
            if((mcc == bssTableApiPtr->mcc) && 
	       (mnc == bssTableApiPtr->mnc)
	      )
	    {
	       free(bssTableApiPtr);
               LOG_PRINT(LOG_MAJOR,"CGI with cellId : %d, lac : %d, mcc : %d, mnc : %d already exist in Internal cell Table",
                                                                    cellId, lac, mnc, mcc);
	       return FALSE;
	    }
	    else
	    {
	       free(bssTableApiPtr);
	       return TRUE;
	    }
         }
	 else
	 {
            LOG_PRINT(LOG_MAJOR,"Get on BssTable Fail");
	    return FALSE;
	 }
      }
      else
      {
         return TRUE;
      }
   }
} 

/*Changes PCU R2.5 Aricent -- START*/
/********************************* Function  Header*****************************
Function Name   : doConsistencyChecksOnSetOnPSCellTable()
Parameters      : PsCellTableApi  : receivedMsgPtr received in Set Request
Return type     : I_U32 : Error Code | CM_SUCCESS
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
I_U32 doConsistencyChecksOnSetOnPSCellTable(PsCellTableApi *receivedMsgPtr, I_Bool isAdd)
{
   PsCellTableApi* tempPsCellTablePtr = PNULL; 
   PsCellTableApi* tempPsCellTablePtr1 = PNULL;
   RaTableApi* raTblApiPtr = PNULL;
   RaTableIndices apiRaIndex;
   I_S32  ret = CM_FAILURE;
   I_U32  rowsCount = 0;
   I_U32  i = 0;
   I_U16  outSize;
   I_U16 minNumPDCHSum=ZERO;

   /* Mantis Id - 14079 Start*/ 
   BssPsPreConfigTableApi *bssPsPreConfigTableApiPtr = PNULL;
   PsAllocPreconfigTableApi *psAllocPreconfigTableApiPtr = PNULL;
   /* Mantis Id - 14079 End*/ 
   
   BssPsTableApi *bssPsTableApiPtr = PNULL;

   if (receivedMsgPtr->gprsCsInitial > receivedMsgPtr->gprsCsMax)
   {
      LOG_PRINT(LOG_DEBUG,"psCellTable Rangecheck failed gprsCsInitial [%u] > gprsCsMax [%u] in function:%s line:%d",
receivedMsgPtr->gprsCsInitial, receivedMsgPtr->gprsCsMax, __FUNCTION__, __LINE__);
      return CM_ERR_CELL_CONSIST_CHECK_FAILED;
   }
   
   /* Mantis Id 21194 Starts */
   if (receivedMsgPtr->egprsDla8PskMcsInitial > receivedMsgPtr->egprsDlaMcsMax)
   {
      LOG_PRINT(LOG_DEBUG,"psCellTable Rangecheck failed egprsDla8PskMcsInitial [%u] > egprsDlaMcsMax [%u] in function:%s line:%d",
receivedMsgPtr->egprsDla8PskMcsInitial, receivedMsgPtr->egprsDlaMcsMax, __FUNCTION__, __LINE__);
      return CM_ERR_CELL_CONSIST_CHECK_FAILED;
   }
   if (receivedMsgPtr->egprsDlaGmskMcsInitial > receivedMsgPtr->egprsDlaMcsMax)
   {
      LOG_PRINT(LOG_DEBUG,"psCellTable Rangecheck failed egprsDlaGmskMcsInitial [%u] > egprsDlaMcsMax [%u] in function:%s line:%d",
receivedMsgPtr->egprsDlaGmskMcsInitial, receivedMsgPtr->egprsDlaMcsMax, __FUNCTION__, __LINE__);
      return CM_ERR_CELL_CONSIST_CHECK_FAILED;
   }

   /* Mantis Id 21194 Ends */

    /* Fix for Mantis 15107 --Start*/ 
   if (receivedMsgPtr->percFreeCsChannels +  receivedMsgPtr->percFreeCsChannelsHyst > 100)
   {
      LOG_PRINT(LOG_DEBUG,"psCellTable consistency check (percFreeCsChannels + percFreeCsChannelsHyst <= 100) failed. percFreeCsChannels [%u], percFreeCsChannelsHyst [%u] in function:%s line:%d",
receivedMsgPtr->percFreeCsChannels, receivedMsgPtr->percFreeCsChannelsHyst, __FUNCTION__, __LINE__);
      return CM_ERR_CELL_CONSIST_CHECK_FAILED;
   }
   /* Fix for Mantis 15107 --End*/  

   ret = getallPsCellTable(&tempPsCellTablePtr, &rowsCount, &outSize);
   
   if ( CLIB_SUCCESS == ret)
   {       
      for(i = 0; i < rowsCount; i++)
      {
         tempPsCellTablePtr1 = (PsCellTableApi *) (((I_U8 *) tempPsCellTablePtr ) + (outSize * i));
         if(receivedMsgPtr->bvciId == tempPsCellTablePtr1->bvciId)
         {
            if(receivedMsgPtr->cellId != tempPsCellTablePtr1->cellId ||
               receivedMsgPtr->lac != tempPsCellTablePtr1->lac)
            {
               LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnPSCellTable : bvcId [%u] already present in Cell LAC[%u] and CellId[%u], Sending Nack", receivedMsgPtr->bvciId, tempPsCellTablePtr1->lac, tempPsCellTablePtr1->cellId);
               free(tempPsCellTablePtr);
               return CM_ERR_BVCI_ALREADY_PRESENT;
            }
         }
      }
      free(tempPsCellTablePtr);
   }
   else if(DBLIBERR_PTOPAGE_HAS_NO_ROWS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"DB call getallPsCellTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      return CM_ERR_GET_ALL_OPERATION_FAILED;
   }

   /* Check if entry is present in DB or not */
   apiRaIndex.rac =  receivedMsgPtr->rac;
   apiRaIndex.lac =  receivedMsgPtr->lac;

   ret = getRaTable(&apiRaIndex, &raTblApiPtr); 
   
   if (raTblApiPtr == PNULL)
   {
      LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnPSCellTable : LAC[%u] RAC[%u] Mapping not present in Ra Table for Cell LAC[%u] and CellId[%u], Sending Nack",receivedMsgPtr->lac,receivedMsgPtr->rac, receivedMsgPtr->lac, receivedMsgPtr->cellId);
      return CM_ERR_LAC_RAC_MAPPING_NOT_PRESENT;
   }
   
   free(raTblApiPtr);
   
   /* Mantis Id - 14079 Start*/ 
   ret = getallBssPsPreConfigTable(&bssPsPreConfigTableApiPtr, &rowsCount, &outSize);
   
   if ( CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"DB Call getallBssPsPreConfigTable() failed :%s line:%d", __FUNCTION__, __LINE__);
      return CM_ERR_GET_ALL_OPERATION_FAILED;
   } 
   if (receivedMsgPtr->maxNumTbfPdch > bssPsPreConfigTableApiPtr->maxNumTbfPerPdch)
   { 
        
      LOG_PRINT(LOG_MAJOR,"Consistency Check ( maxNumTbfPdch <= BssPsPreConfigTable.maxNumTbfPerPdch) Failed. maxNumTbfPdch = [%u]  BssPsPreConfigTable.maxNumTbfPerPdch = [%u] :%s line:%d", receivedMsgPtr->maxNumTbfPdch, bssPsPreConfigTableApiPtr->maxNumTbfPerPdch,  __FUNCTION__, __LINE__);
      return CM_ERR_CELL_CONSIST_CHECK_FAILED;
   }
   free(bssPsPreConfigTableApiPtr);

   ret = getallPsAllocPreconfigTable(&psAllocPreconfigTableApiPtr, &rowsCount, &outSize);
   
   if ( CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"DB Call getallPsAllocPreconfigTable() failed :%s line:%d", __FUNCTION__, __LINE__);
      return CM_ERR_GET_ALL_OPERATION_FAILED;
   } 
   if (receivedMsgPtr->maxNumTbfPdch < psAllocPreconfigTableApiPtr->avgMsPdchDl)
   { 
      LOG_PRINT(LOG_MAJOR,"Consistency Check ( maxNumTbfPdch >=  PsAllocPreconfigTable.avgMsPdchDl ) Failed. maxNumTbfPdch = [%u]  PsAllocPreconfigTable.avgMsPdchDl = [%u] :%s line:%d", receivedMsgPtr->maxNumTbfPdch, psAllocPreconfigTableApiPtr->avgMsPdchDl,  __FUNCTION__, __LINE__);
      return CM_ERR_CELL_CONSIST_CHECK_FAILED;
   }
 
   if (receivedMsgPtr->maxNumTbfPdch < psAllocPreconfigTableApiPtr->avgMsPdchUl)
   { 
      LOG_PRINT(LOG_MAJOR,"Consistency Check ( maxNumTbfPdch >=  PsAllocPreconfigTable.avgMsPdchUl) Failed. maxNumTbfPdch = [%u] PsAllocPreconfigTable.avgMsPdchUl = [%u] :%s line:%d", receivedMsgPtr->maxNumTbfPdch, psAllocPreconfigTableApiPtr->avgMsPdchUl,  __FUNCTION__, __LINE__);
      return CM_ERR_CELL_CONSIST_CHECK_FAILED;
   }
   free(psAllocPreconfigTableApiPtr);
   /* Mantis Id - 14079 End*/ 

  /* Changes for  mantis Id #19881 Starts */
   ret = getallBssPsTable(&bssPsTableApiPtr, &rowsCount, &outSize);
   if ( CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"DB Call getallBssPsTable() failed :%s line:%d", __FUNCTION__, __LINE__);
      return CM_ERR_GET_ALL_OPERATION_FAILED;
   }
   ret = getallPsCellTable(&tempPsCellTablePtr, &rowsCount, &outSize);
   
   if ( CLIB_SUCCESS == ret)
   {       
      for(i = 0; i < rowsCount; i++)
      {
         tempPsCellTablePtr1 = (PsCellTableApi *) (((I_U8 *) tempPsCellTablePtr ) + (outSize * i));
         if(isAdd==FALSE && receivedMsgPtr->cellId == tempPsCellTablePtr1->cellId &&
                 receivedMsgPtr->lac == tempPsCellTablePtr1->lac)  
          continue;
         else
           minNumPDCHSum+=tempPsCellTablePtr1->minNumPdchCell;     
      }
      if ((minNumPDCHSum+receivedMsgPtr->minNumPdchCell) >bssPsTableApiPtr->maxNumPdchBss)
         {
      LOG_PRINT(LOG_MAJOR,"PsCell Table consistency Check  failed ,Total minPDCH in all Cells %u \ 
          is greater than maxNumPdchBss [%u] in function:%s line:%d",(minNumPDCHSum+receivedMsgPtr->minNumPdchCell), bssPsTableApiPtr->maxNumPdchBss,__FUNCTION__,__LINE__);
      free(bssPsTableApiPtr);
      free(tempPsCellTablePtr);
      return(CM_ERR_CELL_CONSIST_CHECK_FAILED);
         }
      free(bssPsTableApiPtr);
      free(tempPsCellTablePtr);

   }
   else if(DBLIBERR_PTOPAGE_HAS_NO_ROWS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"DB call getallPsCellTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      free(bssPsTableApiPtr);
      return CM_ERR_GET_ALL_OPERATION_FAILED;
   }
   
   
  /* Changes for  mantis Id #19881 Ends */

   
   return CM_SUCCESS;
   
} /* end of doConsistencyChecksOnSetOnPSCellTable */

/*Changes PCU R2.5 Aricent -- END*/


/********************************* Function  Header*****************************
Function Name   : isChangesAllowedForWcdmaCell()
Parameters   	: CsExternalCellTableApi * rcvdMsgPtr
Return type   	: I_Void
Purpose      	: It send CsNeighChange request to CELLH for those Cells having 
		  neighbours corresponding to the received cellId, lac, mcc, mnc.
Other Note   	: Added For On The Fly Changes
 *******************************************************************************/
I_Bool isChangesAllowedForWcdmaCell(I_U32 cellId, I_U32 lac, I_U16 mcc, I_U16 mnc  )
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO, index = ZERO;
   I_U16 outSz = ZERO;
   I_Bool isDataFound = FALSE;
   I_PVoid tmpPtr = NULL;
   CsNeighCellsTableApi *csNeighCellTableApiPtr = NULL;
   CellPerTableIndices cellTableInd;
   CellPerTableApi *cellTableApiPtr = NULL;
   I_U16 cellIndex = 0;

   LOG_PRINT(LOG_INFO,"Entering Function : isChangesAllowedForWcdmaCell");

   dbStatus = getallCsNeighCellsTable(&csNeighCellTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)   
   {
      LOG_PRINT(LOG_INFO,"isChangesAllowedForWcdmaCell : No Data in CsNeighCellsTable");
      return TRUE;
   }
   else
   {
      tmpPtr = csNeighCellTableApiPtr;
      for(index = 0; index < outRow; index++)
      {
	      csNeighCellTableApiPtr = (CsNeighCellsTableApi *) (((I_U8 *)tmpPtr) + (outSz * index));
	      if(
            (ZERO == mcc) &&
	          (ZERO == mnc)
	        )
	        {
	         if(
               (csNeighCellTableApiPtr->neighborLac == lac) &&
	             (csNeighCellTableApiPtr->neighborCellId == cellId)
 	           )
	           {
	              isDataFound = TRUE;
                LOG_PRINT(LOG_INFO,"1Found in CsNeifhbour Cell table");
	           }
	        }
	        else
	        {
	           if(
                 (lac == csNeighCellTableApiPtr->neighborLac) &&
                 (cellId == csNeighCellTableApiPtr->neighborCellId) &&
                 (mcc == csNeighCellTableApiPtr->neighborMcc) &&
	               (mnc == csNeighCellTableApiPtr->neighborMnc)
               )
               {
                   isDataFound = TRUE;
                LOG_PRINT(LOG_INFO,"2Found in CsNeifhbour Cell table");
               }
	        }
	        if(
              TRUE == isDataFound
            )
	          {
	             /* Updation of CsExternal is not allowed if Cell is Unlocked */
       	      cellTableInd.cellId = csNeighCellTableApiPtr->cellId;
	            cellTableInd.lac    = csNeighCellTableApiPtr->lac;
	            dbStatus = getCellPerTable(&cellTableInd, &cellTableApiPtr);
	            if(dbStatus != DBLIB_SUCCESS)
	            {
	               LOG_PRINT(LOG_INFO,"Cell is Not Configured at BSC");
	            }
	            else if(
                       cellTableApiPtr->adminState == UNLOCKED
                     )
	            {
                   free(cellTableApiPtr);
          	       LOG_PRINT(LOG_DEBUG,"CellId = %d, Lac = %d is not in LOCKED state",
                   csNeighCellTableApiPtr->cellId,csNeighCellTableApiPtr->lac);
                   free(tmpPtr);
                   return TRUE;
	            }
          	  else
        	    {
	               LOG_PRINT(LOG_INFO,"Cell is Locked. Updation is allowed");
	               free(cellTableApiPtr);
	            }
	          }
	            isDataFound = FALSE;
      }
      free(tmpPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isChangesAllowedForWcdmaCell");
   return FALSE;
}


/********************************* Function  Header*****************************
Function Name   : getCountValueForWcdma()
Parameters   	: CsExternalCellTableApi * rcvdMsgPtr
Return type   	: I_Void
Purpose      	: It send CsNeighChange request to CELLH for those Cells having 
		  neighbours corresponding to the received cellId, lac, mcc, mnc.
Other Note   	: Added For On The Fly Changes
 *******************************************************************************/
I_Bool getCountValueForWcdma(CsNeighCellsTableApi *recvPtr ,I_U32 wcdmaBand )
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO, index = ZERO;
   I_U16 outSz = ZERO;
   I_PVoid tmpPtr = NULL;
   CsNeighCellsTableSecIndices csNeighCellIndices;
   CsNeighCellsTableApi *csNeighCellTableApiPtr = NULL;
   CsExternalCellTableIndices csExtCellIndices;
   CsExternalCellTableApi *csExtCellOutData = NULL;
   I_U32 bcchArfcn[18];
   I_U8 count = 0,i = 0,j = 0,k = 0;

   LOG_PRINT(LOG_INFO,"Entering Function : getCountValueForWcdma");
   memset(bcchArfcn,0,18);
   LOG_PRINT(LOG_INFO,"Value of wcdmaBand :%u",wcdmaBand);
   csNeighCellIndices.cellId = recvPtr->cellId;
   csNeighCellIndices.lac = recvPtr->lac;
  
   dbStatus = clib_get(SCM_DAO_CSNEIGHCELLSTABLE, SCM_MET_GET_SEC_CSNEIGHCELLSTABLE, (I_PVoid)&csNeighCellIndices, sizeof(CsNeighCellsTableSecIndices), (I_PVoid) &csNeighCellTableApiPtr, &outSz, &outRow); 

   LOG_PRINT(DEBUG," Number of neighbour Cells for cell %d",outRow);
   if (dbStatus != CLIB_SUCCESS)
   { 	
      LOG_PRINT(LOG_INFO,"getCountValueForWcdma : No Data in CsNeighCellsTable");
      return TRUE;
   }
   else
   {
      tmpPtr = csNeighCellTableApiPtr;
      for(index = 0; index < outRow; index++)
      {
	      csNeighCellTableApiPtr = (CsNeighCellsTableApi *) (((I_U8 *)tmpPtr) + (outSz * index));
        if (( csNeighCellTableApiPtr->cellType == EXTERNAL) && 
            (csNeighCellTableApiPtr->radioAccessType == WCDMA_FDD))
         {
            csExtCellIndices.csExtCellId = csNeighCellTableApiPtr->neighborCellId;
	          csExtCellIndices.lac = csNeighCellTableApiPtr->neighborLac;
	          csExtCellIndices.mnc = csNeighCellTableApiPtr->neighborMnc;
	          csExtCellIndices.mcc = csNeighCellTableApiPtr->neighborMcc;
            dbStatus = getCsExternalCellTable(&csExtCellIndices, &csExtCellOutData);
            if (dbStatus == CLIB_SUCCESS)
	          {
                LOG_PRINT(LOG_INFO,"getCountValueForWcdma : Get From CsExternal Cell Table with Arfcn :%d",csExtCellOutData->bcchArfcn);
                bcchArfcn[count] = csExtCellOutData->bcchArfcn;
                count++;
 	              free(csExtCellOutData);
	          }
         }   
      }
      
      free(tmpPtr);
   }
   LOG_PRINT(LOG_INFO,"Number of WCDMA_FDD Cells:%d",(count));
   /*Remove duplicate arfcn from array*/
   for(i=0;i<count;i++)
   {
    for(j=i+1;j<count;j++)
    {
      if(bcchArfcn[i]==bcchArfcn[j])
      {
        for(k=j;k<count;k++)
        {
          bcchArfcn[k]=bcchArfcn[k+1];
        }
        count=count-1;
      }
    }
  }
   LOG_PRINT(LOG_INFO,"Value of Count :%d",count);
   if(count < CFG_MAX_NUM_NEIGHBOUR_WCDMA_FDD_CELL)
   {
     return TRUE;
   }
   else if (count >= CFG_MAX_NUM_NEIGHBOUR_WCDMA_FDD_CELL)
   {  
     for(i = 0;i<count;i++)
     {
        if(wcdmaBand == bcchArfcn[i])
        {
          LOG_PRINT(INFO,"New Neighbour is same as other neighbours");
          return TRUE;
        }  
     }  
   }  

   LOG_PRINT(LOG_INFO,"Exiting Function : getCountValueForWcdma");
   return FALSE;
}



/************************************************************ Change History ***
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change

 ********************************************************************** End ***/
