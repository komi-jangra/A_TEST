/*************************************File Header*****
File Name      :    ToFromCFG.c
Purpose        :
Project        :    GSM
Subsystem      :    IPC
Author         :
CSCI id        :
Version        :    V0.1
*************************************************************/

/*******************************************Change History***
S.No.   Release        Patch        Author        Description
1.      Rel0.0         None         xxxxx         Creation
*************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sysxxx_macro.h>
#include<sysxxx_hashdefs.h>
#include<sysxxx_typedef.h>
#include<sysxxx_msgopcode.h>
#include<sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include<sysinst_hashdefs.h>
#include<sysxxx_msgstruct.h>
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>

I_PVoid Build_OamsCfgSwmhSwDnldReq(I_S32 *, I_U32, I_U32, I_U32 applTei) ;
I_PVoid Build_OamsCfgSwmhSwActReq(I_S32 *, I_U32, I_U32, I_U32 applTei) ;

void ReceiveData() ;

I_U16 srcinstG ;
I_U16 CallRef ;
//I_S32 reVal ;

main()
{
   I_S32 count = 0 ;
   I_S32 size  = 0 ;
   I_S32 i     = 0 ;
   I_S32 srcId ;    
   I_S32 dstId ;
   I_S32 interval ;
   I_SL32 priority ;
   I_S8 buffer[100] ;
   I_PVoid bufferPtr ;
   int choice     = 0 ;
   I_U32 nodeId   = 0 ;
   I_U32 nodeType = 0 ;
   I_U32 applTei  = 0 ;


//if((reVal = FreInstId(0x08dc16c8, ENT_OAMS_SWMH,1))<0)
//fprintf (stderr, "cannot free the instance 0x08dc16c8\n");
//LOG_PRINT(INFO, "cannot free the instance 0x08dc16c8\n") ;

   srcId = (int)ENT_OAMS_CFG ;

   if (RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_OAMS_CFG")!=0)
   {
      fprintf(stderr,"Counld not register with framework\n") ;
   }

   while (1)
   {
      fprintf (stderr, "\n---------------- ENTER UR CHOICE -------------- \n") ;
      fprintf (stderr, "-------->> 1.To Send OAMS_CFG_SWMH_SW_DNLD_REQ \n") ;
      fprintf (stderr, "-------->> 2.To Send OAMS_CFG_SWMH_SW_ACT_REQ \n") ;
      fprintf (stderr, "-------->> 3.To Receive Message \n") ;
      fprintf (stderr, "<<--------Give choice, nodeType, nodeId, applTei \n") ;

      scanf ("%d", &choice);
      if( choice == 1 || choice == 2 )
      {
         scanf ("%d %d %d", &nodeType,&nodeId,&applTei);
      }

      fprintf (stderr, " Given choice = %d\t, NodeType =%d\t,NodeIdentity = %d,applTei =%d\t " , choice,nodeType, nodeId,applTei);

      switch(choice)
      {
         case 1 :
                   bufferPtr = Build_OamsCfgSwmhSwDnldReq(&size, nodeType, nodeId, applTei ) ;
                   break ;

         case 2 :
                   bufferPtr = Build_OamsCfgSwmhSwActReq(&size, nodeType, nodeId, applTei) ;
                   break ;

         case 3 :
                   ReceiveData() ;
                   break ;

         default :
                   fprintf(stderr, "\n INVALID CHOICE \n") ;
      } /* end of switch */
 
      if( choice == 1 || choice == 2 )
      {
         if (bufferPtr != NULL && size > 0)
         {
            if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
            {
               exit(0) ;
            }
         }
      }
   } /* end of while (1) */

} /* end of main */

void ReceiveData()
{
   I_PVoid         rcvPtr ;
   I_S32           msgSize ;
   I_U16           msgType ;

   while(1)
   {
      rcvPtr = (I_PVoid)RecvMsg((int)(ENT_OAMS_CFG), &msgSize) ;
      fprintf(stderr,"No of Bytes received = [%d]\n", msgSize) ;
      if(msgSize <= 0)
      {
         continue ;
      }
      else
      {
         break ;
      }
   }
   if(rcvPtr == NULL)
   {
      fprintf(stderr,"Could not read from Framework\n") ;
      return ;
   }

   msgType = ((SysHdr *)rcvPtr)->msgType ;

   switch (msgType)
   {
      case OAMS_SWMH_CFG_SW_DNLD_ACK:
           DalocMsgBuf((I_PVoid)rcvPtr);
           LOG_PRINT(INFO, "Received OAMS_SWMH_CFG_SW_DNLD_ACK\n") ;
           fprintf(stderr,"Software Download Ack received from SWMH\n") ;
      break ;

      case OAMS_SWMH_CFG_SW_DNLD_NACK:
           LOG_PRINT(INFO,"OAMS_SWMH_CFG_SW_DNLD_NACK") ;
           fprintf(stderr,"Software Download Nack received from SWMH\n") ;
      break ;

      case OAMS_SWMH_CFG_SW_ACT_ACK:
           LOG_PRINT(INFO,"OAMS_SWMH_CFG_SW_ACT_ACK") ;
           fprintf(stderr,"Software Activation Ack received from SWMH\n") ;
      break ;

      case OAMS_SWMH_CFG_SW_ACT_NACK:
           LOG_PRINT(INFO,"OAMS_SWMH_CFG_SW_ACT_NACK") ;
           fprintf(stderr,"Software Activation Nack received from SWMH\n") ;
      break ;

      case OAMS_SWMH_CFG_ALARM_IND:
           LOG_PRINT(INFO,"OAMS_SWMH_CFG_ALARM_IND") ;
           fprintf(stderr,"Alarm Indication received from SWMH\n") ;
      break ;

      default:
           fprintf(stderr,"Invalid message received from SIM\n") ;
   }
   if (rcvPtr != NULL)
   DalocMsgBuf(rcvPtr) ;
}

I_PVoid Build_OamsCfgSwmhSwDnldReq(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   OamsCfgSwmhSwDnldReq    *swDnldReq ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(OamsCfgSwmhSwDnldReq);
   if((swDnldReq = (OamsCfgSwmhSwDnldReq *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   swDnldReq->nodeType = nodeType ;
   swDnldReq->nodeIdentity = nodeId ;
   swDnldReq->applTei = applTei ;
   strcpy(swDnldReq->swVersion, "20.10.3") ;
   pathLen = sizeof("/home/priya/20.10.3.txt") ;
   strcpy(swDnldReq->binaryPath, "/home/priya/20.10.3.txt") ;
   *size = len ;

   FILL_SYS_HDR(&(swDnldReq->sysHdr), OAMS_CFG_SWMH_SW_DNLD_REQ , 1, PRCR_CP, ENT_OAMS_CFG, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  swDnldReq ;

} /* Build_OamsCfgSwmhSwDnldReq() Complete */

I_PVoid Build_OamsCfgSwmhSwActReq(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   OamsCfgSwmhSwActReq    *swActReq ;

   I_U16 len = 0 ;
   
   len = sizeof(OamsCfgSwmhSwActReq);
   if((swActReq = (OamsCfgSwmhSwActReq *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   swActReq->nodeType = nodeType ;
   swActReq->nodeIdentity = nodeId ;
   swActReq->applTei = applTei ;
   strcpy(swActReq->swVersion, "20.10.6") ;
   *size = len ;
  
   FILL_SYS_HDR(&(swActReq->sysHdr), OAMS_CFG_SWMH_SW_ACT_REQ , 1, PRCR_CP, ENT_OAMS_CFG, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  swActReq ;

} /* Build_OamsCfgSwmhSwDnldReq() Complete */





