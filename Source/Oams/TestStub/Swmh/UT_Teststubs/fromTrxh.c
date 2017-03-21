/*se ts=2************************************File Header*****
File Name      :    fromTrxh.c
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

I_PVoid Build_OamsTrxhSwmhTrxHello(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_OamsTrxhSwmhLapdLinkDown(I_S32 *, I_U32, I_U32) ;
I_PVoid Build_OamsTrxhSwmhLapdLinkUp(I_S32 *, I_U32, I_U32) ; 

//I_U16 srcinstG ;


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

   srcId = (int)ENT_OAMS_TRXH ;

   if (RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_OAMS_TRXH")!=0)
   {
      fprintf(stderr,"Counld not register with framework\n") ;
      LOG_PRINT(INFO,"Counld not register with framework\n");
   }
   LOG_PRINT(INFO, "TRXH registered with IPC - %d\n", ENT_OAMS_TRXH);

   while (1)
   {
      fprintf (stderr, "\n---------------- ENTER UR CHOICE -------------- \n") ;
      fprintf (stderr, "-------->> 1.To Send OAMS_TRXH_SWMH_TRX_HELLO \n") ;
      fprintf (stderr, "-------->> 2.To Send OAMS_TRXH_SWMH_LAPD_LINK_DOWN \n") ;
      fprintf (stderr, "-------->> 3.To Send OAMS_TRXH_SWMH_LAPD_LINK_UP \n") ;
      fprintf (stderr, "<<--------Give choice, nodeType, nodeId, applTei \n") ;

      scanf ("%d %d %d %d", &choice, &nodeType, &nodeId, &applTei);

      fprintf (stderr, " Given choice = %d\t, NodeType =%d\t,NodeIdentity = %d\t, applTei = %d\n " , choice,nodeType, nodeId, applTei);
      LOG_PRINT(INFO," Given choice = %d\t, NodeType =%d\t,NodeIdentity = %d\t, applTei = %d\n", choice,nodeType, nodeId, applTei) ;

      switch(choice)
      {
         case 1 :
                   bufferPtr = Build_OamsTrxhSwmhTrxHello(&size, nodeType, nodeId, applTei) ;
                   LOG_PRINT(INFO,"Sending TRX_HELLO \n");
                   break ;

         case 2 :
                   bufferPtr = Build_OamsTrxhSwmhLapdLinkDown(&size, nodeType, nodeId) ;
                   LOG_PRINT(INFO,"Sending LAPD_LINK_DOWN\n");
                   break ;

         case 3 :
                   bufferPtr = Build_OamsTrxhSwmhLapdLinkUp(&size, nodeType, nodeId) ;
                   LOG_PRINT(INFO,"Sending LAPD_LINK_UP\n");
                   break ;

         default :
                   fprintf(stderr, "\n INVALID CHOICE \n") ;
      } /* end of switch */
 
      if( choice == 1 || choice == 2 || choice == 3)
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


I_PVoid Build_OamsTrxhSwmhTrxHello(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   OamsTrxhSwmhTrxHello   *swmhTrxHello ;

   I_U16 len = 0 ;
   I_U16 verLen = 0 ;
   len = sizeof(OamsTrxhSwmhTrxHello);
   if((swmhTrxHello = (OamsTrxhSwmhTrxHello *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      LOG_PRINT(INFO,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   swmhTrxHello->tei = applTei ;
   swmhTrxHello->nodeType = nodeType ;
   swmhTrxHello->nodeIdentity = nodeId ;
   strcpy(swmhTrxHello->swDes.fileVer, "20.10.3") ;
   LOG_PRINT(INFO,"Sending Active Version as %s in TRX_HELLO\n", swmhTrxHello->swDes.fileVer);
   verLen = strlen(swmhTrxHello->swDes.fileVer);
   LOG_PRINT(INFO,"Active Software Version length = %d", verLen);
   swmhTrxHello->swDes.len = verLen ;
   LOG_PRINT(INFO,"Length of active version= %d", verLen);
   swmhTrxHello->isInactiveSwDesPresent = 1;
   strcpy(swmhTrxHello->inactiveSwDes.fileVer, "210.240.43") ;
   LOG_PRINT(INFO,"Sending Inactive Version as %s in TRX_HELLO\n", swmhTrxHello->inactiveSwDes.fileVer);
   verLen = strlen(swmhTrxHello->inactiveSwDes.fileVer);
   LOG_PRINT(INFO,"Active Software Version length = %d", verLen);
   swmhTrxHello->inactiveSwDes.len = verLen ;

   *size = len ;

   FILL_SYS_HDR(&(swmhTrxHello->sysHdr), OAMS_TRXH_SWMH_TRX_HELLO, 1, PRCR_CP, ENT_OAMS_TRXH, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  swmhTrxHello ;

} /* Build_OamsTrxhSwmhTrxHello() Complete */

I_PVoid Build_OamsTrxhSwmhLapdLinkDown(I_S32 *size, I_U32 nodeType, I_U32 nodeId) 
{
  OamsTrxhSwmhLapdLinkDown   *lapdLinkDown ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(OamsTrxhSwmhLapdLinkDown);
   if((lapdLinkDown = (OamsTrxhSwmhLapdLinkDown *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      LOG_PRINT(INFO,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   lapdLinkDown->nodeType = nodeType ;
   lapdLinkDown->nodeIdentity = nodeId ;
   *size = len ;

   FILL_SYS_HDR(&(lapdLinkDown->sysHdr), OAMS_TRXH_SWMH_LAPD_LINK_DOWN, 1, PRCR_CP, ENT_OAMS_TRXH, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  lapdLinkDown ;

} /* Build_OamsTrxhSwmhLapdLinkDown() Complete */

I_PVoid Build_OamsTrxhSwmhLapdLinkUp(I_S32 *size, I_U32 nodeType, I_U32 nodeId) 
{
  OamsTrxhSwmhLapdLinkUp   *lapdLinkUp ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(OamsTrxhSwmhLapdLinkUp);
   if((lapdLinkUp = (OamsTrxhSwmhLapdLinkUp *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      LOG_PRINT(INFO,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   lapdLinkUp->nodeType = nodeType ;
   lapdLinkUp->nodeIdentity = nodeId ;
   *size = len ;

   FILL_SYS_HDR(&(lapdLinkUp->sysHdr), OAMS_TRXH_SWMH_LAPD_LINK_UP, 1, PRCR_CP, ENT_OAMS_TRXH, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  lapdLinkUp ;

} /* Build_OamsTrxhSwmhLapdLinkUp() Complete */


