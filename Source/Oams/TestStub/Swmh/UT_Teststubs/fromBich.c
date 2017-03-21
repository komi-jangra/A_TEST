/*se ts=2************************************File Header*****
File Name      :    fromBich.c
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
#include<dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_msgstruct.h>
#include<oamsswmh_hashdefs.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>

I_PVoid Build_OamsBichSwmhBicHello(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_OamsBichSwmhBmHello(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_OamsBichSwmhLapdLinkDown(I_S32 *, I_U32, I_U32) ;
I_PVoid Build_OamsBichSwmhLapdLinkUp(I_S32 *, I_U32, I_U32) ; 

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

   srcId = (int)ENT_OAMS_BICH ;

   if (RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_OAMS_BICH")!=0)
   {
      fprintf(stderr,"Counld not register with framework\n") ;
   }
   LOG_PRINT(INFO, "BICH regigestered with IPC with entity ID =%d",ENT_OAMS_BICH);
   while (1)
   {
      fprintf (stderr, "\n---------------- ENTER UR CHOICE -------------- \n") ;
      fprintf (stderr, "-------->> 1.To Send OAMS_BICH_SWMH_BIC_HELLO \n") ;
      fprintf (stderr, "-------->> 2.To Send OAMS_BICH_SWMH_LAPD_LINK_DOWN \n") ;
      fprintf (stderr, "-------->> 3.To Send OAMS_BICH_SWMH_LAPD_LINK_UP \n") ;
      fprintf (stderr, "-------->> 4.To Send OAMS_BICH_SWMH_BM_HELLO \n") ;
      fprintf (stderr, "<<--------Give choice, nodeType, nodeId, applTei \n") ;

      scanf ("%d %d %d %d", &choice, &nodeType, &nodeId, &applTei);

      fprintf (stderr, " Given choice = %d\t, NodeType =%d\t,NodeIdentity = %d\t, applTei =%d\n " , choice,nodeType, nodeId, applTei);

      switch(choice)
      {
         case 1 :
                   bufferPtr = Build_OamsBichSwmhBicHello(&size, nodeType, nodeId, applTei) ;
                  fprintf(stderr, "Sent OAMS_BICH_SWMH_TRX_HELLO\n");
                   break ;

         case 2 :
                   bufferPtr = Build_OamsBichSwmhLapdLinkDown(&size, nodeType, nodeId) ;
                   fprintf(stderr,"OAMS_BICH_SWMH_LAPD_LINK_DOWN\n");
                   break ;

         case 3 :
                   bufferPtr = Build_OamsBichSwmhLapdLinkUp(&size, nodeType, nodeId) ;
                   fprintf(stderr,"OAMS_BICH_SWMH_LAPD_LINK_UP\n");
                   break ;
         case 4 :
                   bufferPtr = Build_OamsBichSwmhBmHello(&size, nodeType, nodeId, applTei) ;
                  fprintf(stderr, "Sent OAMS_BICH_SWMH_BM_HELLO\n");
                   break ;


         default :
                   fprintf(stderr, "\n INVALID CHOICE \n") ;
      } /* end of switch */
 
      if( choice == 1 || choice == 2 || choice == 3 || choice ==4 )
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


I_PVoid Build_OamsBichSwmhBicHello(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   OamsBichSwmhBicHello   *swmhBicHello ;

   I_U16 len = 0 ;
   I_U16 verLen = 0 ;
   len = sizeof(OamsBichSwmhBicHello);
   if((swmhBicHello = (OamsBichSwmhBicHello *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
/*   swmhBicHello->tei = bicTei ;  */
   swmhBicHello->nodeType = nodeType ;
   swmhBicHello->nodeIdentity = nodeId ;
   swmhBicHello->bicTei = applTei ;
   swmhBicHello->isBicSwDesInActiveSwPresent = 1;
   strcpy(swmhBicHello->swDesActiveSw.fileVer, "20.10.3") ;
   fprintf(stderr,"Active software in BIC_HELLO = %s",swmhBicHello->swDesActiveSw.fileVer );
   verLen = strlen("147.235.123");
   swmhBicHello->swDesActiveSw.len = verLen;
   strcpy(swmhBicHello->swDesInActiveSw.fileVer, "225.125.489") ;
   fprintf(stderr,"Inactive software in BIC_HELLO = %s",swmhBicHello->swDesInActiveSw.fileVer );
   verLen = strlen("225.125.489");
   swmhBicHello->swDesInActiveSw.len = verLen ;
   *size = len ;

   FILL_SYS_HDR(&(swmhBicHello->sysHdr), OAMS_BICH_SWMH_BIC_HELLO, 1, PRCR_CP, ENT_OAMS_BICH, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  swmhBicHello ;

} /* Build_OamsBichSwmhBicHello() Complete */

I_PVoid Build_OamsBichSwmhBmHello(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   OamsBichSwmhBmHello   *swmhBmHello ;

   I_U16 len = 0 ;
   I_U16 verLen = 0 ;
   len = sizeof(OamsBichSwmhBmHello);
   if((swmhBmHello = (OamsBichSwmhBmHello *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
/*   swmhBmHello->tei = bicTei ;  */
   swmhBmHello->nodeType = nodeType ;
   swmhBmHello->nodeIdentity = nodeId ;
   swmhBmHello->bicTei = applTei ;
   swmhBmHello->isBicSwDesInActiveSwPresent = 1;
   strcpy(swmhBmHello->swDesActiveSw.fileVer, "20.10.6") ;
   fprintf(stderr,"Active software in BIC_HELLO = %s",swmhBmHello->swDesActiveSw.fileVer );
   verLen = strlen("147.235.123");
   swmhBmHello->swDesActiveSw.len = verLen;
   strcpy(swmhBmHello->swDesInActiveSw.fileVer, "225.125.489") ;
   fprintf(stderr,"Inactive software in BIC_HELLO = %s",swmhBmHello->swDesInActiveSw.fileVer );
   verLen = strlen("225.125.489");
   swmhBmHello->swDesInActiveSw.len = verLen ;
   *size = len ;

   FILL_SYS_HDR(&(swmhBmHello->sysHdr), OAMS_BICH_SWMH_BIC_HELLO, 1, PRCR_CP, ENT_OAMS_BICH, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  swmhBmHello ;

} /* Build_OamsBichSwmhBmHello() Complete */

I_PVoid Build_OamsBichSwmhLapdLinkDown(I_S32 *size, I_U32 nodeType, I_U32 nodeId) 
{
  OamsBichSwmhLapdLinkDown   *lapdLinkDown ;

   I_U16 len = 0 ;
   len = sizeof(OamsBichSwmhLapdLinkDown);
   if((lapdLinkDown = (OamsBichSwmhLapdLinkDown *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   lapdLinkDown->nodeType = nodeType ;
   lapdLinkDown->nodeIdentity = nodeId ;
   *size = len ;

   FILL_SYS_HDR(&(lapdLinkDown->sysHdr), OAMS_BICH_SWMH_LAPD_LINK_DOWN, 1, PRCR_CP, ENT_OAMS_BICH, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  lapdLinkDown ;

} /* Build_OamsBichSwmhLapdLinkDown() Complete */

I_PVoid Build_OamsBichSwmhLapdLinkUp(I_S32 *size, I_U32 nodeType, I_U32 nodeId) 
{
  OamsTrxhSwmhLapdLinkUp   *lapdLinkUp ;

   I_U16 len = 0 ;
   len = sizeof(OamsBichSwmhLapdLinkUp);
   if((lapdLinkUp = (OamsBichSwmhLapdLinkUp *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   lapdLinkUp->nodeType = nodeType ;
   lapdLinkUp->nodeIdentity = nodeId ;
   *size = len ;

   FILL_SYS_HDR(&(lapdLinkUp->sysHdr), OAMS_BICH_SWMH_LAPD_LINK_UP, 1, PRCR_CP, ENT_OAMS_BICH, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  lapdLinkUp ;

} /* Build_OamsBichSwmhLapdLinkUp() Complete */


