/*se ts=2************************************File Header*****
File Name      :    ToFromTB.c
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
#include<oamxxx_datastruct.h>
#include<oamxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>
#include<syspcu_typedefs.h>
#include<syspcu_datastruct.h>
#include<psappxxx_datastruct.h>
#include<psappxxx_msgstruct.h>
I_PVoid Build_PsappTbBichIpLinkDownMsg(I_U8,I_S32 *)  ;
I_PVoid Build_PsappTbBichIpLinkUpMsg(I_U8,I_S32 *)  ;
I_PVoid Build_PsappTbGrhmDataInd(I_U8,I_S32 *);
void ReceiveData();

main()
{
   I_PVoid bufferPtr;
   I_U8 tei;
   I_S32 srcId,result,size=0;
   I_SL32 priority;
   I_U32 ch=0 ;
   int choice ;
   srcId = (int)ENT_PSAPP_TBBSC ;
   if(RegisterWithIpcFrmwrk((int)ENT_PSAPP_TBBSC, (I_S8 *)"ENT_PSAPP_TB")!=0)
   {
      fprintf(stderr,"Counld not register with framework\n");
   }
   /* Check whether this call is necessary here */
   result = dbConnect();
   if (result != 0)
   {
      LOG_PRINT(CRITICAL,"BICHandler: Unable to Register itself with DBServer:Exiting");
      exit(0);
   }
   while(1)
   {
      fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
      fprintf(stderr, "-------->> 1.To Send PsappTbBichIpLinkDown \n");
      fprintf(stderr, "-------->> 2.To Send PsappTbBichIpLinkUp   \n");
      fprintf(stderr, "-------->> 3.To Send PsappTbGrhmDataInd    \n");
      fprintf(stderr, "-------->> 4.To Receive Data               \n"); 
      scanf("%d", &choice);
      switch(choice)
      {

         case 1 :
                fprintf(stderr, "-------->>Enter TEI, for which  IP_LINK_DOWN_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_PsappTbBichIpLinkDownMsg(tei, &size);
                ch = 1;
                break;
         
         case 2 :
                fprintf(stderr, "-------->>Enter TEI, for which  IP_LINK_UP_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_PsappTbBichIpLinkUpMsg(tei, &size);
                ch = 1;
                break;

        case 3 :
                fprintf(stderr, "-------->>Enter TEI, for which  DATA_IND is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_PsappTbGrhmDataInd(tei,&size);
                ch = 1;
                break; 

        case 4 :
                ReceiveData() ;
                ch = 0 ;
                break ;

        default :
               fprintf(stderr, "\n INVALID CHOICE \n");
               continue ;

      }// switch choice
      if(ch==1)
      {
         if (bufferPtr != NULL && size > 0)
         {
            if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
            {
               exit(0);
            }
          }
      }
   }// while 1
}// main


void ReceiveData()
{
   I_PVoid         rcvPtr ;
   I_S32           msgSize ;
   I_U16           msgType ;
   I_U8            entId;
   while(1)
   {
      rcvPtr = (I_PVoid)RecvMsg((int)ENT_PSAPP_TBBSC, &msgSize);
      fprintf(stderr,"No of Bytes received = [%d]\n",msgSize);
      if(msgSize <= 0)
      {
      //   continue ;
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
   entId = ((SysHdr *) rcvPtr)->dest.entity ;
   fprintf(stderr,"Received msg with msgType [%d]\n",msgType) ;
   fprintf(stderr,"Received msg with EntityId [%d]\n",entId) ;
   switch (msgType)
   {
      case OAMS_BICH_TB_ADD_BTS_IP:
           fprintf(stderr,"ADD BTS IP message received from BICH\n") ;
           break ;
      case OAMS_BICH_TB_IP_LINK_DOWN:
           fprintf(stderr,"IP LINK DOWN message received from BICH\n") ;
           break ;
      case OAMS_BICH_TB_DEL_BTS_IP:
           fprintf(stderr,"DELETE BTS IP message received from BICH\n") ;
           break ;
      case OAMS_TRXH_TB_ADD_BTS_TEI_MAPPING : 
           fprintf(stderr,"ADD BTS TEI MAPPING message received from TRXH\n") ;
           break ;
      case OAMS_TRXH_TB_DEL_BTS_TEI_MAPPING :
           fprintf(stderr,"DELETE BTS TEI MAPPING message received from TRXH\n") ;
           break ;
      case CSAPP_GRHM_TB_DATA_REQ :
           fprintf(stderr,"DATA REQ MESSAGE received from GRHM\n");
           break ;
      default:
           fprintf(stderr,"Invalid message received from SIM\n") ;
    }
    if (rcvPtr != NULL)
       DalocMsgBuf(rcvPtr) ;

}//End of ReceiveData()

I_PVoid Build_PsappTbBichIpLinkDownMsg(I_U8 tei , I_S32 *size)
{
 
   PsappTbBichIpLinkDown *ptr;
   I_U32 btsId=0;
   I_U16 len=0;
   len = sizeof(PsappTbBichIpLinkDown);
   if((ptr = (PsappTbBichIpLinkDown *)AlocMsgBuf(len) ) == (I_Void *)NULL)        
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   fprintf(stderr, "-------->>Enter btsId, for which  IP_LINK_DOWN message is  - ");
   scanf("%d",&btsId);
   ptr->btsId = btsId;
   ptr->btsApplTei = tei ;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_TB_BICH_IP_LINK_DOWN, 1,PRCR_CP, ENT_PSAPP_TBBSC ,0,PRCR_CP, ENT_OAMS_BICH,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

} /*end of Build_PsappTbBichIpLinkDownMsg */

I_PVoid Build_PsappTbBichIpLinkUpMsg(I_U8 tei , I_S32 *size)
{

   PsappTbBichIpLinkUp *ptr;
   I_U32 btsId=0;
   I_U16 len= 0;
   len = sizeof(PsappTbBichIpLinkUp);
   if((ptr = (PsappTbBichIpLinkUp *)AlocMsgBuf(len) ) == (I_Void *)NULL)       
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   fprintf(stderr, "-------->>Enter btsId, for which  IP_LINK_UP message is  - ");
   scanf("%d",&btsId);
   ptr->btsId = btsId;
   ptr->btsApplTei = tei ;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_TB_BICH_IP_LINK_UP, 1,PRCR_CP, ENT_PSAPP_TBBSC ,0,PRCR_CP, ENT_OAMS_BICH,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

} /*end of Build_PsappTbBichIpLinkUpMsg */


I_PVoid Build_PsappTbGrhmDataInd(I_U8 tei,I_S32 *size)
{
   PsappTbGrhmDataInd *ptr;
   I_U16    len=0;
   SyspcuTbHdr        tbHdr; 
   I_U32   pduType;
   I_U16   timeslot;

   tbHdr.nwTei        = 1;
   tbHdr.destEntityId = 1;
   tbHdr.instId       = 2;
   tbHdr.rfu          = 1;
   
   len = sizeof(PsappTbGrhmDataInd);
   if((ptr = (PsappTbGrhmDataInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)       
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   
   ptr->tbHdr.nwTei = tbHdr.nwTei;
   ptr->tbHdr.applTei = tei;
   ptr->tbHdr.destEntityId = tbHdr.destEntityId;
   fprintf(stderr, "-------->>Enter Timeslot)  -\n ");
   scanf("%u",&timeslot);
   ptr->tbHdr.instId  = timeslot;
   ptr->tbHdr.rfu  = tbHdr.rfu;
   fprintf(stderr, "-------->>Enter PDU TYPE(PDCH_ACT_ACK(0)/PDCH_ACT_NACK(1)/PDCH_DEACT_ACK(2))  -\n ");
   scanf("%u",&pduType);
   switch(pduType)
   {
      case 0 : 
        ptr->tbHdr.pduType = SYSPCU_PDU_TYPE_PDCH_ACT_ACK ;
        ptr->tbHdr.pduLen  = 0;
        break; 
      case 1 :
        ptr->tbHdr.pduType = SYSPCU_PDU_TYPE_PDCH_ACT_NACK;
        ptr->tbHdr.pduLen  = 1;
        break;
      case 2 :
        ptr->tbHdr.pduType = SYSPCU_PDU_TYPE_PDCH_DEACT_ACK;
        ptr->tbHdr.pduLen  = 0;
        break;  
      default :
        fprintf(stderr, "-------->>Enter Appropriate PDU TYPE  \n ");
  }
 
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_TB_GRHM_DATA_IND, 1,PRCR_CP, ENT_PSAPP_TBBSC ,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

} /*end of Build_PsappTbGrhmDataInd*/
