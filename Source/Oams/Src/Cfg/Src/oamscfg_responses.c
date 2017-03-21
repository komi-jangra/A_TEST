/***********************************File Header ***************************
   File Name        : oamscfg_responses.c
Purpose          : This file contains function definitions for CFG
CM messages
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>
#define CM_FAILED -1  /*COMP_C*/

/********************************* Function  Header********************************
   Function Name:cfgSendNackToCm
Parameters   :errNum
Return type   :void
Purpose   :
Other Note   :
 ************************************************************************************/
void cfgSendNackToCm(I_U32 errNum)
{
   sCmMsg   *sndPtr;
   I_U16  sndMsgSize = sizeof(sCmMsg);
   LOG_PRINT(LOG_INFO,"\t Entering function cfgSendNackToCm().....");
   LOG_PRINT(LOG_INFO,"\t Erro number %d is sent to CM", errNum);

   if ((sndPtr = (sCmMsg *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      LOG_PRINT(LOG_CRITICAL,"Message Allaocation failed");
      return; /*Added during fix of Mantis 2284 - In mem allocation failure return from the function*/
   }

   sndPtr->sHdr.msgType = CM_API_APP_RESPONSE;
   sndPtr->sHdr.src.entity = ENT_OAMS_CFG;
   sndPtr->sHdr.dest.entity = ENT_OAM_CM;

   sndPtr->cmHdr.status = errNum;
   /* Bug Fixed : CS2.2_SSI_012 : End */

   sndPtr->cmHdr.size  = CM_NO_DATA;
   sndPtr->cmHdr.txnId  = gCmTrasId;

   LOG_PRINT(LOG_INFO," msgType = %d,Src entity =%d ,Dest entity=%d,status =%d,size=%s, ", sndPtr->sHdr.msgType, sndPtr->sHdr.src.entity,sndPtr->sHdr.dest.entity,sndPtr->cmHdr.status,sndPtr->cmHdr.size);
   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      /* Either call recovery or wait for some time - to be discussed */
      LOG_PRINT(LOG_CRITICAL," CFG : Message sending failed ");
   }
   return;
}

/********************************* Function  Header********************************
   Function Name   :cfgSendAckToCm()
Parameters   :void
Return type   :void
Purpose   :             
Other Note   :
 ************************************************************************************/
void cfgSendAckToCm()
{
   sCmMsg   *sndPtr=NULL;
   I_S16  sndMsgSize=0;

   LOG_PRINT(LOG_INFO,"\t Calling cfgSendAckToCm().....");
   sndMsgSize = sizeof(sCmMsg);

   if ((sndPtr = (sCmMsg *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      LOG_PRINT(LOG_CRITICAL,"AlocMsgBuf failue");   
      return; /* added during changes for Mantis 2284*/
   }

   sndPtr->sHdr.msgType = CM_API_APP_RESPONSE;

   sndPtr->cmHdr.status = CM_SUCCESS;
   sndPtr->cmHdr.size  = CM_NO_DATA;
   sndPtr->cmHdr.txnId  = gCmTrasId;
   sndPtr->sHdr.src.entity = ENT_OAMS_CFG;
   sndPtr->sHdr.dest.entity = ENT_OAM_CM;

   LOG_PRINT(LOG_INFO," msgType = %d,Src entity =%d ,Dest entity=%d,status =%d,size=%s, ", sndPtr->sHdr.msgType, sndPtr->sHdr.src.entity,sndPtr->sHdr.dest.entity,sndPtr->cmHdr.status,sndPtr->cmHdr.size);
   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      /* Either call recovery or wait for some time - to be discussed */
      LOG_PRINT(LOG_CRITICAL,"CFG: In func cfgSendAckToCm() - msg sending failed");
   }
   return;
}

/********************************* Change History ***************************
   Release     Patch       Author         Description

 ************************************** End *********************************/

